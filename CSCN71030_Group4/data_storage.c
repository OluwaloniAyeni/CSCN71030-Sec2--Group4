#include "data_storage.h"
#include "common.h"
#include "category_selection.h"
#include "item.h"
#include "error_handling.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file data_storage.c
 * @brief Handles loading, saving, storing, and filtering facility data.
 * @details This file contains functions used to manage facility records
 * and budget history records, including loading from files,
 * saving to files, filtering results, and initializing mock data.
 * @author Evangeline Singh
 * @date 2026-04-13
 */


 /**
  * @brief Ensures enough memory for facility records.
  * @details This function resizes the facility list memory when more
  * records need to be stored.
  * @author Oluwaloni Ayeni and Evangeline Singh
  * @param list Pointer to facility list.
  * @param neededCount Required number of records.
  * @return int Returns 1 if successful, otherwise 0.
  * @date 2026-04-13
  */
static int ensureFacilityCapacity(FacilityList* list, size_t neededCount) {
    Facility* newItems;

	// check if list pointer is valid before processing
    if (list == NULL) {
        return 0;
    }

	// no allocation needed for zero count, return success
    if (neededCount == 0) {
        return 1;
    }

	// resize facility array to accommodate needed count of records
    newItems = (Facility*)realloc(list->items, neededCount * sizeof(Facility));
    if (newItems == NULL) {
        handleError("DataStorage", "Memory allocation failed for facilities.");
        return 0;
    }

    list->items = newItems;
    return 1;
}

/**
 * @brief Ensures enough memory for budget history records.
 * @details This function resizes the budget history array when more
 * budget records need to be stored.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param history Pointer to budget history.
 * @param neededCount Required number of records.
 * @return int Returns 1 if successful, otherwise 0.
 * @date 2026-04-13
 */
static int ensureBudgetCapacity(BudgetHistory* history, size_t neededCount) {
    BudgetRecord* newItems;

	// checks if history pointer is valid before processing
    if (history == NULL) {
        return 0;
    }
    
    // no allocation needed for zero count, return success
    if (neededCount == 0) {
        return 1;
    }

	// resize budget history array to accommodate needed count of records
    newItems = (BudgetRecord*)realloc(history->items, neededCount * sizeof(BudgetRecord));
    if (newItems == NULL) {
        handleError("DataStorage", "Memory allocation failed for budget history.");
        return 0;
    }

    history->items = newItems;
    return 1;
}

/**
 * @brief Adds a facility record to the list.
 * @details This function appends one facility record into the facility list,
 * resizing the list if necessary.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param list Pointer to facility list.
 * @param record Pointer to the facility record to add.
 * @return int Returns 1 if successful, otherwise 0.
 * @date 2026-04-13
 */
int addFacilityRecord(FacilityList* list, const Facility* record) {

    // validate input
    if (list == NULL || record == NULL) {
        return 0;
    }

    // make sure there is enough memory.
    if (!ensureFacilityCapacity(list, list->count + 1)) {
        return 0;
    }

    // store new record
    list->items[list->count] = *record;
    list->count++;
    return 1;
}

/**
 * @brief Adds a budget record to budget history.
 * @details This function appends one category-budget record into the budget history list.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param history Pointer to budget history list.
 * @param category Category name.
 * @param budget Budget value.
 * @return int Returns 1 if successful, otherwise 0.
 * @date 2026-04-13
 */
int addBudgetRecord(BudgetHistory* history, const char* category, double budget) {
    BudgetRecord record;

    // validate input
    if (history == NULL || category == NULL) {
        return 0;
    }

    // make sure there is enough memory
    if (!ensureBudgetCapacity(history, history->count + 1)) {
        return 0;
    }

    // save category and budget
    safe_strcpy(record.category, sizeof(record.category), category);
    record.budget = budget;
    history->items[history->count] = record;
    history->count++;

    return 1;
}

/**
 * @brief Parses one line of facility data.
 * @details This function reads one text line, separates the values,
 * validates them, and stores them in a Facility structure.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param line Input line from file.
 * @param out Pointer to facility output record.
 * @return int Returns 1 if parsing is successful, otherwise 0.
 * @date 2026-04-13
 */
static int parseFacilityLine(const char* line, Facility* out) {
    char buffer[512];
    char* token;
    double price;
    double rating;

    // validate input
    if (line == NULL || out == NULL) {
        return 0;
    }

    char* context = NULL;

    // copy line into tenporary buffer
    safe_strcpy(buffer, sizeof(buffer), line);

    // parse facility name
    token = strtok_s(buffer, "|", &context);
    if (token == NULL) {
        return 0;
    }
    
    safe_strcpy(out->name, sizeof(out->name), token);

    
    // parse category
    token = strtok_s(NULL, "|", &context);
    if (token == NULL) {
        return 0;
	}
    safe_strcpy(out->category, sizeof(out->category), token);
	processCategory(out->category);

    // validate category
    if(!isValidCategory(out->category)) {
        return 0;
	}

    // parse price
	token = strtok_s(NULL, "|", &context);
    if(token == NULL || !parse_double_strict(token, &price)) {
        return 0;
	}
	out->price = (float)price;

    // parse rating
    token = strtok_s(NULL, "|", &context);
    if(token == NULL || !parse_double_strict(token, &rating)) {
        return 0;
	}
    out->rating = (float)rating;

    //parse Wi-fi flag
    token = strtok_s(NULL, "|", &context);
    if(token == NULL) {
        return 0;
	}   
	out->hasWifi = atoi(token) != 0;

    // parse parking
    token = strtok_s(NULL, "|", &context);
    if(token == NULL) {
        return 0;
	}
    out->hasParking = atoi(token) != 0;
	return 1;
}

/**
 * @brief Loads facility data from file.
 * @details This function reads facility records from a text file.
 * If the file cannot be opened, mock data is initialized instead.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param filePath Path to input file.
 * @param outList Pointer to facility list output.
 * @return int Returns 1 if loading succeeds, otherwise 0.
 * @date 2026-04-13
 */
int loadFacilitiesData(const char* filePath, FacilityList* outList) {
    FILE* file = NULL;
    char line[512];

    // validating input
    if (filePath == NULL || outList == NULL) {
        return 0;
    }

    // initialise output list
    outList->items = NULL;
    outList->count = 0;

    // open file, or fall back to mock data
   if (fopen_s(&file,filePath, "r") != 0) {
	   handleError("Data Storage Module", "Could not access data file. Using mock data.");
	   initializeMockData(outList);
        return 1;
    }

   // read file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        Facility facility;

        trim_newline(line);
        trim_spaces(line);

        // skip empty lines and comments
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        // parse and add valid facility records
        if (parseFacilityLine(line, &facility)) {
            if (!addFacilityRecord(outList, &facility)) {
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    return 1;
}

/**
 * @brief Loads budget history data from file.
 * @details This function reads category-budget records from a file
 * and stores them in budget history.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param filePath Path to budget history file.
 * @param outHistory Pointer to budget history output.
 * @return int Returns 1 if loading succeeds, otherwise 0.
 * @date 2026-04-13
 */
int loadBudgetData(const char* filePath, BudgetHistory* outHistory) {
    FILE* file;
    char line[256];

    char* context = NULL;

    //validate input
    if (filePath == NULL || outHistory == NULL) {
        return 0;
    }

    // initialise output directory
    outHistory->items = NULL;
    outHistory->count = 0;

    if (fopen_s(&file, filePath, "r") != 0) {

   
        return 0;
    }

    // read budget line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        char temp[256];
        char* category;
        char* budgetText;
        double budget;

        trim_newline(line);
        trim_spaces(line);

        // skip empty lines and comments
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        safe_strcpy(temp, sizeof(temp), line);
        category = strtok_s(temp, "|",&context);
        budgetText = strtok_s(NULL, "|", &context);

        // skip invalid records
        if (category == NULL || budgetText == NULL) {
            continue;
        }

        processCategory(category);
        if (!parse_double_strict(budgetText, &budget)) {
            continue;
        }

        addBudgetRecord(outHistory, category, budget);
    }

    fclose(file);
    return 1;
}

/**
 * @brief Gets facility data pointer and count.
 * @details This function returns the facility array and optionally stores its size.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param list Pointer to facility list.
 * @param count Pointer to store number of records.
 * @return const Facility* Returns facility array pointer.
 * @date 2026-04-13
 */
const Facility* getFacilitiesData(const FacilityList* list, size_t* count) {
    if (count != NULL) {
        *count = (list != NULL) ? list->count : 0;
    }
    return (list != NULL) ? list->items : NULL;
}

/**
 * @brief Gets budget history data pointer and count.
 * @details This function returns the budget history array and optionally stores its size.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param history Pointer to budget history.
 * @param count Pointer to store number of records.
 * @return const BudgetRecord* Returns budget history array pointer.
 * @date 2026-04-13
 */
const BudgetRecord* getBudgetData(const BudgetHistory* history, size_t* count) {
    if (count != NULL) {
        *count = (history != NULL) ? history->count : 0;
    }
    return (history != NULL) ? history->items : NULL;
}

/**
 * @brief Frees facility and budget memory.
 * @details This function releases dynamically allocated memory
 * used for facilities and budget history.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param list Pointer to facility list.
 * @param history Pointer to budget history.
 * @return void
 * @date 2026-04-13
 */
void freeDataMemory(FacilityList* list, BudgetHistory* history) {

    // free facility list memory
    if (list != NULL) {
        free(list->items);
        list->items = NULL;
        list->count = 0;
    }

    // free budget history memory
    if (history != NULL) {
        free(history->items);
        history->items = NULL;
        history->count = 0;
    }
}

/**
 * @brief Saves facility data to file.
 * @details This function writes all facility records to an output file.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param filePath Output file path.
 * @param list Pointer to facility list.
 * @return int Returns 1 if successful, otherwise 0.
 * @date 2026-04-13
 */
int saveDataToFile(const char* filePath, const FacilityList* list) {
    FILE* file;
    size_t i;

    
    // validate input
    if (filePath == NULL || list == NULL) {
        return 0;
    }

    // open the output file
    if (fopen_s(&file, filePath, "w") != 0) {
        handleError("DataStorage", "Could not open facilities output file for writing.");
        return 0;
    }

    // writing each facility record
    for (i = 0; i < list->count; ++i) {
        const Facility* f = &list->items[i];
        fprintf(file, "%s|%s|%.2f|%.1f|%d|%d\n",
            f->name,
            f->category,
            f->price,
            f->rating,
            f->hasWifi,
            f->hasParking);
    }

    fclose(file);
    return 1;
}

/**
 * @brief Saves budget history data to file.
 * @details This function writes all budget history records to an output file.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param filePath Output file path.
 * @param history Pointer to budget history.
 * @return int Returns 1 if successful, otherwise 0.
 * @date 2026-04-13
 */
int saveBudgetDataToFile(const char* filePath, const BudgetHistory* history) {
    FILE* file;
    size_t i;
    
    // validating input
    if (filePath == NULL || history == NULL) {
        return 0;
    }

    // open the output file
    if (fopen_s(&file, filePath, "w") != 0) {
        handleError("DataStorage", "Could not open budget history file for writing.");
        return 0;
    }

    // write each budget record
    for (i = 0; i < history->count; ++i) {
        fprintf(file, "%s|%.2f\n", history->items[i].category, history->items[i].budget);
    }

    fclose(file);
    return 1;
}

/**
 * @brief Filters results by category and budget.
 * @details This function creates a new result list containing only facilities
 * that match the category and are within the given budget.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param list Pointer to facility list.
 * @param category Category to match.
 * @param budget Maximum budget.
 * @param outResults Pointer to store filtered results.
 * @param outCount Pointer to store number of filtered results.
 * @return int Returns 1 if filtering is successful, otherwise 0.
 * @date 2026-04-13
 */
int filterResults(
    const FacilityList* list,
    const char* category,
    double budget,
    Facility** outResults,
    size_t* outCount
) {
    Facility* results = NULL;
    size_t count = 0;
    size_t i;

    // validate inputs
    if (list == NULL || category == NULL || outResults == NULL || outCount == NULL) {
        return 0;
    }

    // check each facility record
    for (i = 0; i < list->count; ++i) {
        const Facility* f = &list->items[i];
        if (strings_equal_ignore_case(f->category, category) && f->price <= budget) {
            Facility* newResults = (Facility*)realloc(results, (count + 1) * sizeof(Facility));
            if (newResults == NULL) {
                free(results);
                return 0;
            }
            results = newResults;
            results[count] = *f;
            count++;
        }
    }

    *outResults = results;
    *outCount = count;
    return 1;
}

/**
 * @brief Initializes mock facility data.
 * @details This function fills the facility list with default records
 * when the real data file is not available.
 * @author Oluwaloni Ayeni and Evangeline Singh
 * @param list Pointer to facility list.
 * @return void
 * @date 2026-04-13
 */
void initializeMockData(FacilityList* list) {
    Facility defaults[] = {
        {1,"Maple Stay Hotel", "hotel", 145.00f, 4.5f, 1, 1},
        {2,"Delta Hotel", "hotel", 333.00f, 4.0f, 1, 0},
         {3,"Courtyard Hotel", "hotel", 95.00f, 4.5f, 1, 1},
        {4,"Staybridge Hotel", "hotel", 250.00f, 4.0f, 1, 0},
        {5,"Maple Stay Hotel", "hotel", 145.00f, 4.5f, 1, 1},
        {6,"Holiday Inn Express & Suite Hotel", "hotel", 89.99f, 4.0f , 1, 0},
         {7,"Best Western Plus Cambridge Hotel", "hotel", 145.00f, 4.5f, 1, 1},
        {8,"Waterloo Suites Hotel", "hotel", 89.99f, 4.0f, 1, 0},
        {9,"Hampton Inn & Suites by Hilton", "hotel", 145.00f, 4.0f, 1, 1},
        {10,"The Walper Hotel", "hotel", 89.99f, 4.0f, 1, 0},
        {11,"Sun", "restaurant", 25.00f, 4.3f, 1, 1},
        {12,"The Bauer Kitchen", "restaurant", 100.00f, 3.9f, 1, 1},
        {13,"The Poké Box", "restaurant", 35.00f, 4.3f, 1, 1},
        {14,"The Grand Malabar", "restaurant", 30.00f, 5.0f, 1, 1},
        {15,"Princess Cafe", "restaurant", 20.00f, 4.6f, 1, 0},
        {16," King Tin Restaurant", "restaurant", 25.00f, 3.4f, 0, 0},
        {17,"Prime Grill", "restaurant", 60.00f, 4.7f, 1, 1},
        {18,"The Jane Bond", "restaurant", 50.00f, 3.9f, 0, 0},
        {19,"Pulse Fitness", "gym", 35.00f, 4.2f, 1, 1},
        {20,"Core Strength Gym", "gym", 22.00f, 3.9f, 0, 1},
        {21,"Crunch Fitness", "gym", 26.00f, 4.0f, 1, 1},
        {22,"Orangetheory Fitness", "gym", 10.00f, 3.9f, 0, 1},
        {23,"Lil's Gym", "gym", 20.00f, 5.0f, 1, 1},
        {24,"Pursuit OCR", "gym", 22.00f, 4.4f, 0, 0},
        {25,"Pulse Fitness", "gym", 35.00f, 4.2f, 1, 1},
        {26,"Core Strength Gym", "gym", 22.00f, 3.9f, 0, 1},
        {27,"Princess Cafe", "cafe", 15.00f, 4.6f, 1, 0},
        {28,"Seven Shores Cafe", "cafe", 15.00f, 4.5f, 1, 1},
        {29,"Midnight Run Cafe", "cafe", 12.00f, 4.4f, 1, 0},
        {30,"Cafe 1842", "cafe", 10.00f, 4.3f, 1, 1},
        {31,"Williams Fresh Cafe", "cafe", 12.00f, 4.2f, 1, 1},
        {32,"Smile Tiger Coffee Roasters", "cafe", 15.00f, 4.6f, 1, 1},
        {33,"Monigram Coffee Roasters", "cafe", 15.00f, 4.5f, 1, 0},
        
    };
    size_t i;

    // validate input
    if (list == NULL) {
        return;
    }

    // initialise empty list
    list->items = NULL;
    list->count = 0;

    // add all default facility records
    for (i = 0; i < sizeof(defaults) / sizeof(defaults[0]); ++i) {
        addFacilityRecord(list, &defaults[i]);
    }
}
