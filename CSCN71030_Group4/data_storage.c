#include "data_storage.h"
#include "common.h"
#include "category_selection.h"
#include "item.h"
#include "error_handling.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ensureFacilityCapacity(FacilityList* list, size_t neededCount) {
    Facility* newItems;

    if (list == NULL) {
        return 0;
    }

    if (neededCount == 0) {
        return 1;
    }

    newItems = (Facility*)realloc(list->items, neededCount * sizeof(Facility));
    if (newItems == NULL) {
        handleError("DataStorage", "Memory allocation failed for facilities.");
        return 0;
    }

    list->items = newItems;
    return 1;
}

static int ensureBudgetCapacity(BudgetHistory* history, size_t neededCount) {
    BudgetRecord* newItems;

    if (history == NULL) {
        return 0;
    }

    if (neededCount == 0) {
        return 1;
    }

    newItems = (BudgetRecord*)realloc(history->items, neededCount * sizeof(BudgetRecord));
    if (newItems == NULL) {
        handleError("DataStorage", "Memory allocation failed for budget history.");
        return 0;
    }

    history->items = newItems;
    return 1;
}

int addFacilityRecord(FacilityList* list, const Facility* record) {
    if (list == NULL || record == NULL) {
        return 0;
    }

    if (!ensureFacilityCapacity(list, list->count + 1)) {
        return 0;
    }

    list->items[list->count] = *record;
    list->count++;
    return 1;
}

int addBudgetRecord(BudgetHistory* history, const char* category, double budget) {
    BudgetRecord record;

    if (history == NULL || category == NULL) {
        return 0;
    }

    if (!ensureBudgetCapacity(history, history->count + 1)) {
        return 0;
    }

    safe_strcpy(record.category, sizeof(record.category), category);
    record.budget = budget;
    history->items[history->count] = record;
    history->count++;

    return 1;
}

static int parseFacilityLine(const char* line, Facility* out) {
    char buffer[512];
    char* token;
    double price;
    double rating;

    if (line == NULL || out == NULL) {
        return 0;
    }

    char* context = NULL;

    safe_strcpy(buffer, sizeof(buffer), line);

    token = strtok_s(buffer, "|", &context);
    if (token == NULL) {
        return 0;
    }
    
    safe_strcpy(out->name, sizeof(out->name), token);

    

    token = strtok_s(NULL, "|", &context);
    if (token == NULL) {
        return 0;
	}
    safe_strcpy(out->category, sizeof(out->category), token);
	processCategory(out->category);
    if(!isValidCategory(out->category)) {
        return 0;
	}

	token = strtok_s(NULL, "|", &context);
    if(token == NULL || !parse_double_strict(token, &price)) {
        return 0;
	}
	out->price = price;

    token = strtok_s(NULL, "|", &context);
    if(token == NULL || !parse_double_strict(token, &rating)) {
        return 0;
	}
    out->rating = rating;
    token = strtok_s(NULL, "|", &context);
    if(token == NULL) {
        return 0;
	}   
	out->hasWifi = atoi(token) != 0;

    token = strtok_s(NULL, "|", &context);
    if(token == NULL) {
        return 0;
	}
    out->hasParking = atoi(token) != 0;
	return 1;
}

int loadFacilitiesData(const char* filePath, FacilityList* outList) {
    FILE* file = NULL;
    char line[512];

    if (filePath == NULL || outList == NULL) {
        return 0;
    }

    outList->items = NULL;
    outList->count = 0;

   if (fopen_s(&file,filePath, "r") != 0) {
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        Facility facility;

        trim_newline(line);
        trim_spaces(line);

        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

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

int loadBudgetData(const char* filePath, BudgetHistory* outHistory) {
    FILE* file;
    char line[256];

    char* context = NULL;

    if (filePath == NULL || outHistory == NULL) {
        return 0;
    }

    outHistory->items = NULL;
    outHistory->count = 0;

    if (fopen_s(&file, filePath, "r") != 0) {

   
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char temp[256];
        char* category;
        char* budgetText;
        double budget;

        trim_newline(line);
        trim_spaces(line);

        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        safe_strcpy(temp, sizeof(temp), line);
        category = strtok_s(temp, "|",&context);
        budgetText = strtok_s(NULL, "|", &context);

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

const Facility* getFacilitiesData(const FacilityList* list, size_t* count) {
    if (count != NULL) {
        *count = (list != NULL) ? list->count : 0;
    }
    return (list != NULL) ? list->items : NULL;
}

const BudgetRecord* getBudgetData(const BudgetHistory* history, size_t* count) {
    if (count != NULL) {
        *count = (history != NULL) ? history->count : 0;
    }
    return (history != NULL) ? history->items : NULL;
}

void freeDataMemory(FacilityList* list, BudgetHistory* history) {
    if (list != NULL) {
        free(list->items);
        list->items = NULL;
        list->count = 0;
    }

    if (history != NULL) {
        free(history->items);
        history->items = NULL;
        history->count = 0;
    }
}

int saveDataToFile(const char* filePath, const FacilityList* list) {
    FILE* file;
    size_t i;

    char* context = NULL;

    if (filePath == NULL || list == NULL) {
        return 0;
    }

    if (fopen_s(&file, filePath, "w") != 0) {
        handleError("DataStorage", "Could not open facilities output file for writing.");
        return 0;
    }

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

int saveBudgetDataToFile(const char* filePath, const BudgetHistory* history) {
    FILE* file;
    size_t i;
    char* context = NULL;

    if (filePath == NULL || history == NULL) {
        return 0;
    }

    if (fopen_s(&file, filePath, "w") != 0) {
        handleError("DataStorage", "Could not open budget history file for writing.");
        return 0;
    }

    for (i = 0; i < history->count; ++i) {
        fprintf(file, "%s|%.2f\n", history->items[i].category, history->items[i].budget);
    }

    fclose(file);
    return 1;
}

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

    if (list == NULL || category == NULL || outResults == NULL || outCount == NULL) {
        return 0;
    }

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
        {10,"The Walper Hotel", "hot el", 89.99f, 4.0f, 1, 0},
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

    if (list == NULL) {
        return;
    }

    list->items = NULL;
    list->count = 0;

    for (i = 0; i < sizeof(defaults) / sizeof(defaults[0]); ++i) {
        addFacilityRecord(list, &defaults[i]);
    }
}
