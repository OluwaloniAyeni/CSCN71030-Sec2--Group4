#pragma once

#include "item.h"

/**
 * @file recommendation.h
 * @brief Handles recommendation generation.
 * @details This file declares functions used to generate recommendation
 * lists from filtered facilities and free allocated memory.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */


 /**
  * @brief Generates recommendation list.
  * @details This function creates a new dynamic list of facilities
  * based on the filtered results.
  * @author Oluwaloni Ayeni
  * @param filteredlist Pointer to filtered facilities.
  * @param count Number of filtered facilities.
  * @param recommendationCount Pointer to store number of recommendations.
  * @return Facility* Pointer to recommendation list or NULL if error.
  * @date 2026-04-13
  */
Facility* generateRecommendations(Facility* filteredlist, int count, int* recommendationCount);


/**
 * @brief Frees recommendation memory.
 * @details This function releases dynamically allocated memory
 * used to store recommendation results.
 * @author Oluwaloni Ayeni
 * @param list Pointer to recommendation list.
 * @return void
 * @date 2026-04-13
 */
void freeRecommendations(Facility* list);