
#pragma once

#include "item.h"

/**
 * @file feature_display.h
 * @brief Handles optional feature filtering.
 * @details This header file declares functions used to filter facilities
 * based on optional user preferences such as Wi-Fi, parking,
 * and minimum rating.
 * @author Evangeline Singh
 * @date 2026-04-13
 */


 /**
  * @brief Filters facilities based on optional features.
  * @details This function filters a list of facilities based on user-selected
  * features such as Wi-Fi, parking, and minimum rating.
  * @author Evangeline Singh
  * @param input Pointer to input facility list.
  * @param inputCount Number of facilities in the input list.
  * @param output Pointer to store filtered results.
  * @param outputCount Pointer to store number of filtered facilities.
  * @return int Returns 1 if filtering is successful, otherwise 0.
  */
int filterFeatures(
    const Facility* input,
    size_t inputCount,
    Facility** output,
    size_t* outputCount
);