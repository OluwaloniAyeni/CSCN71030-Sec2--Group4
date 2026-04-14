#include <stdio.h>
#include <string.h>
#include "item.h"
#include "budget_handling.h"

/**
 * @file budget_handling.c
 * @brief Handles budget-based filtering of facilities.
 * @details This file contains functions used to filter facilities
 * based on the user's selected category and maximum budget.
 * @author Afsana Zaman
 * @date 2026-04-13
 */


 /**
  * @brief Filters facilities based on budget and category.
  * @details This function checks all facilities and returns only those
  * that match the selected category and are within the user's budget.
  * @author Oluwaloni Ayeni and Afsana Zaman
  * @param allItems Pointer to all facilities.
  * @param count Number of facilities.
  * @param req User request containing category and budget.
  * @param filteredCount Pointer to store number of filtered results.
  * @return Facility* Returns pointer to filtered facilities or NULL if no match.
  * @date 2026-04-13
  */
Facility* processBudget(Facility* allItems, int count, UserRequest req, int* filteredCount)
{
	// check for invalid input parameters and return null if any are invalid
    if (allItems == NULL || filteredCount == NULL) {
        return NULL;
	}

    static Facility filtered[100];
    int found = 0;


	// loop through all facilities.
    for (int i = 0; i < count; i++) {

		// check if the facility matches the user's selected category and is within the budget
        if (strcmp(allItems[i].category, req.category) == 0  &&
            allItems[i].price <= (float) req.budget) {
            
                {
					// store matching facility in the filtered array and increment found count
					filtered[found++] = allItems[i];
                }
      
        }

    }

    // store total number of matched results
	*filteredCount = found;
   
    // return results if found, otherwise return null
    return (found > 0) ? filtered : NULL;

}