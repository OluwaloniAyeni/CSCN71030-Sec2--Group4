 #include "feature_display.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @file feature_display.c
 * @brief Handles optional feature-based filtering.
 * @details This file contains functions that ask the user for optional
 * feature preferences such as Wi-Fi, parking, and minimum rating,
 * then filter facilities based on those selections.
 * @author Evangeline Singh.
 * @date 2026-04-13
 */


 /**
  * @brief Asks the user a yes/no optional question.
  * @details This function allows the user to choose yes, no, or skip
  * by pressing Enter. The result is stored in mustBeYes.
  * @author Oluwaloni Ayeni and Evangeline Singh
  * @param prompt Question shown to the user.
  * @param mustBeYes Pointer that stores 1 for yes, 0 for no, and -1 for skip.
  * @return int Returns 1 if input is valid, otherwise 0.
  * @date 2026-04-13
  */
static int askYesNoOptional(const char* prompt, int* mustBeYes) {
	char line[32] = " ";

	// check if output pointer is valid before processing
	if (mustBeYes == NULL) {

		return 0;
	}

	// ask user for yes, no, or skip input
	printf("%s Please answer [y, n, or press Enter to skip]: ", prompt);

	if (fgets(line, sizeof(line), stdin) == NULL) {

		return 0;
	}

	// clean the input string by removing newline, trimming spaces, and converting to lowercase
	trim_newline(line);
	trim_spaces(line);
	toLowercase(line);

	// if user skips the question by pressing Enter, set mustBeYes to -1 and return valid
	if (line[0] == '\0') {

		*mustBeYes = -1;
		return 1;
	}

	// if user answers yes, set mustBeYes to 1 and return valid
	if (strcmp(line, "y") == 0 || strcmp(line, "yes") == 0) {

		*mustBeYes = 1;
		return 1;
	}

	// if users answers no, set mustBeYes to 0 and return valid
	if (strcmp(line, "n") == 0 || strcmp(line, "no") == 0) {

		*mustBeYes = 0;
		return 1;
	}
	return  0;

}

/*
  * @brief Filters facilities based on optional features.
  * @details This function asks the user for optional feature preferences
  * such as Wi-Fi, parking, and minimum rating, then filters the facility list accordingly.
  * @author Oluwaloni Ayeni and Evangeline Singh
  * @param input Pointer to the input facility list.
  * @param inputCount Number of facilities in the input list.
  * @param output Pointer to store the pointer of the filtered results list.
  * @param outputCount Pointer to store the number of filtered facilities.
  * @return int Returns 1 if filtering is successful, otherwise 0.
  * @date 2026-04-13
  */
int filterFeatures(
    const Facility* input,
    size_t inputCount,
    Facility** output,
    size_t* outputCount
) {
    int wifiRequirement;
    int parkingRequirement;
    double minRating = -1.0;
    char ratingLine[64];
    Facility* results = NULL;
    size_t count = 0;
    size_t i;

	// check if output pointers are valid before processing
    if (output == NULL || outputCount == NULL) {
        return 0;
    }

    *output = NULL;
    *outputCount = 0;

	// check if input list is valid before processing
    if (input == NULL){
        return 0;
    }

    // if input list is empty, return success with no results
    if (inputCount == 0)
    {
        return 1;
    }
    
	// ask user for Wi-Fi requirement. Repeat until valid input is received.
    while (!askYesNoOptional("Require Wi-Fi?", &wifiRequirement)) {
        printf("\nInvalid input. Please answer y, n, or press Enter to skip.\n");
    }

	// ask user for parking requirement. Repeat until valid input is received.
    while (!askYesNoOptional("Require parking?", &parkingRequirement)) {
        printf("\nInvalid input. Please answer y, n, or press Enter to skip.\n");
    }

    // ask user for minimum rating.
    printf("Minimum rating 0.0-5.0 (Enter to skip): ");

    if (fgets(ratingLine, sizeof(ratingLine), stdin) != NULL) {
        trim_newline(ratingLine);
        trim_spaces(ratingLine);
        if (ratingLine[0] != '\0') {
            if (!parse_double_strict(ratingLine, &minRating) || minRating < 0.0 || minRating > 5.0) {
                minRating = -1.0;
                printf("Ignoring invalid minimum rating filter.\n");
            }
        }
    }

    // filter facilities based on selected features.
    for (i = 0; i < inputCount; ++i) {
        const Facility* f = &input[i];
        int passWifi = (wifiRequirement == -1) || (f->hasWifi == wifiRequirement);
        int passParking = (parkingRequirement == -1) || (f->hasParking == parkingRequirement);
        int passRating = (minRating < 0.0) || (f->rating >= minRating);

		// if the facility meets all selected criteria, add it to the results list
        if (passWifi && passParking && passRating) {
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

    // store final filtered results.
    *output = results;
    *outputCount = count;
    return 1;
}


