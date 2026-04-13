#pragma once

#include "item.h"

/**
 * @file output_display.h
 * @brief Handles displaying results to the user.
 * @details This file declares the function used to display
 * filtered and recommended facilities in a structured format.
 * @author Weiming Wang
 * @date 2026-04-13
 */


 /**
  * @brief Displays search results.
  * @details This function prints the selected category and budget,
  * and displays the list of facilities in a formatted table.
  * @author Weiming Wang
  * @param request Pointer to user request (category and budget).
  * @param items Pointer to facility list.
  * @param count Number of facilities to display.
  * @return void
  * @date 2026-04-13
  */
void displayResults(const UserRequest* request, const Facility* items, size_t count);