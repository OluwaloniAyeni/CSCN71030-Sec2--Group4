#pragma once

#include "item.h"
#include "user_input.h"

/**
 * @file budget_handling.h
 * @brief Handles filtering facilities based on user budget.
 * @details This header file declares the function used to filter
 * facilities according to the user's selected category
 * and maximum budget.
 * @author Afsana Zaman
 * @date 2026-04-13
 */


 /**
  * @brief Filters facilities based on category and budget.
  * @details This function checks all facilities and returns only those
  * that match the user’s category and are within the budget.
  * @author Afsana Zaman
  * @param allItems Pointer to all facility records.
  * @param count Number of facility records.
  * @param req User request containing category and budget.
  * @param filteredCount Pointer to store number of filtered results.
  * @return Facility* Returns pointer to filtered facilities or NULL if none found.
  * @date 2026-04-13
  */

Facility* processBudget(Facility* allItems, int count, UserRequest req, int* filteredCount);
