 #include "feature_display.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int askYesNoOptional(const char* prompt, int* mustBeYes) {
	char line[32] = " ";

	if (mustBeYes == NULL) {

		return 0;
	}


	printf("%s [y/n, Enter to skip]: ", prompt);

	if (fget(line, sizeof(line), stdin) == NULL) {

		return 0;
	}

	trim_newline(line);
	trim_spaces(line);
	to_lowercase(line);

	if (line[0] == '\0') {

		*mustBeYes = -1;
		return 1;
	}

	if (strcmp(line, "y") == 0 || strcmp(line, "yes") == 0) {

		*mustBeYes = 1;
		return 1;
	}

	if (strcmp(line, "n") == 0 || strcmp(line, "no") == 0) {

		*mustBeYes = 0;
		return 1;
	}
	return  0;

}

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

    if (output == NULL || outputCount == NULL) {
        return 0;
    }

    *output = NULL;
    *outputCount = 0;

    if (input == NULL){
        return 0;
    }
    if (inputCount == 0)
    {
        return 1;
    }

    while (!askYesNoOptional("Require Wi-Fi?", &wifiRequirement)) {
        printf("Please answer y, n, or press Enter to skip.\n");
    }

    while (!askYesNoOptional("Require parking?", &parkingRequirement)) {
        printf("Please answer y, n, or press Enter to skip.\n");
    }

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

    for (i = 0; i < inputCount; ++i) {
        const Facility* f = &input[i];
        int passWifi = (wifiRequirement == -1) || (f->hasWifi == wifiRequirement);
        int passParking = (parkingRequirement == -1) || (f->hasParking == parkingRequirement);
        int passRating = (minRating < 0.0) || (f->rating >= minRating);

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

    *output = results;
    *outputCount = count;
    return 1;
}


