#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_filtering.h"
#include "error_handling.h"

/**
 * @file search_filtering.c
 * @brief Handles searching and filtering of facilities.
 * @details This file contains functions that filter facilities
 * based on category and budget range, and free memory after use.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */


 /**
  * @brief Filters facilities based on category and budget range.
  * @details This function checks all facilities and returns only those
  * that match the selected category and fall within the given budget.
  * @author Oluwaloni Ayeni
  * @param list Pointer to facility list.
  * @param count Number of facilities.
  * @param category Selected category (e.g., cafe, gym).
  * @param minBudget Minimum budget.
  * @param maxBudget Maximum budget.
  * @param filteredCount Pointer to store number of filtered results.
  * @return Facility* Returns pointer to filtered array, or NULL if no match/error.
  * @date 2026-04-13
  */

Facility* filterByBudget(Facility* list, int count, const char* category, float minBudget,
	float maxBudget, int* filteredCount)
{
	int i;
	int j;
	Facility* filtered;

	// Initialize filtered count to 0
	*filteredCount = 0;

	// checks for invalid input parameters and returns null if any are invalid
	if (list == NULL || category == NULL || filteredCount == NULL) {
		return NULL;
	}

	// first loop: counts how many items match the 
	// category and budget criteria to determine the size of the filtered array
	for (i = 0; i < count; i++) {
		if (strcmp(list[i].category, category) == 0 &&
			list[i].price >= minBudget && list[i].price <= maxBudget) {
			(*filteredCount)++;
		}
	}

	// if no results are found, return null and set filtered count to 0
	if (*filteredCount == 0) {
		return NULL;
	}

	// allocate memory for filtered results based on the count of matching items
	filtered = (Facility*)malloc((*filteredCount) * sizeof(Facility));
	if (filtered == NULL)
		{
		*filteredCount = 0;
		return NULL;
	}

	j = 0;

	// second loop: copy matching items into new array.
	for (i = 0; i < count; i++) {
		if (strcmp(list[i].category, category) == 0 &&
			list[i].price >= minBudget && list[i].price <= maxBudget) {
			filtered[j++] = list[i];
		}
	}
	return filtered;
}

/*
 * @brief Frees memory allocated for filtered results.
 * @details This function releases dynamically allocated memory used for filtered facilities
 * to prevent memory leaks.
 * @author Oluwaloni Ayeni
 * @param list Pointer to filtered facility list to be freed.
 * @return void
 * @date 2026-04-13
 */ 
void freeResults(Facility* list)
{
	//free alocated memory.
	free(list);
}