#pragma once

#include "item.h"

/**
 * @file search_filtering.h
 * @brief Handles searching and filtering of facilities.
 * @details This file declares functions used to filter facilities
 * based on category and budget range, and free allocated memory.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */


 /**
  * @brief Filters facilities based on category and budget.
  * @details This function returns only facilities that match
  * the selected category and fall within the given budget range.
  * @author Oluwaloni Ayeni
  * @param list Pointer to facility list.
  * @param count Number of facilities.
  * @param category Selected category.
  * @param minBudget Minimum budget.
  * @param maxBudget Maximum budget.
  * @param filteredCount Pointer to store number of filtered results.
  * @return Facility* Pointer to filtered list or NULL if no match.
  * @date 2026-04-13
  */
Facility* filterByBudget(Facility* list, int count, const char* category, float minBudget, float maxBudget, int* filteredCount);


/**
 * @brief Frees filtered results memory.
 * @details This function releases dynamically allocated memory
 * used for filtered facilities.
 * @author Oluwaloni Ayeni
 * @param list Pointer to filtered facility list.
 * @return void
 * @date 2026-04-13
 */
void freeResults(Facility* list);