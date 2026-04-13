#pragma once

#include "item.h"

/**
 * @file sorting_and_ranking.h
 * @brief Handles sorting and ranking of facilities.
 * @details This file declares functions used to sort facilities
 * by price and rank them based on rating for better recommendations.
 * @author Weiming Wang
 * @date 2026-04-13
 */


 /**
  * @brief Sorts facilities by price.
  * @details This function arranges facilities in ascending order
  * from lowest price to highest price.
  * @author Weiming Wang
  * @param items Pointer to facility list.
  * @param count Number of facilities.
  * @return void
  * @date 2026-04-13
  */
void sortByPrice(Facility* items, int count);


/**
 * @brief Ranks facilities by rating.
 * @details This function arranges facilities in descending order
 * based on rating. If two facilities have the same rating,
 * the cheaper one is placed first.
 * @author Weiming Wang
 * @param items Pointer to facility list.
 * @param count Number of facilities.
 * @return void
 * @date 2026-04-13
 */
void rankByRating(Facility* items, int count);