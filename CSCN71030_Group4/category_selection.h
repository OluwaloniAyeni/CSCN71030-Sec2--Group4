#pragma once

/**
 * @file category_selection.h
 * @brief Handles category processing and validation.
 * @details This header file declares functions used to convert
 * category input to lowercase and check if the category is valid.
 * @author Weiming Wang
 * @date 2026-04-13
 */


 /**
  * @brief Converts a string to lowercase.
  * @details This function changes all uppercase letters in the string
  * to lowercase letters for consistent comparison.
  * @param str Pointer to the string.
  * @return void
  */
void toLowerCase(char* str);


/**
 * @brief Checks if a category is valid.
 * @details This function compares the input category with valid categories
 * such as gym, hotel, restaurant, and cafe.
 * @param category Input category string.
 * @return int Returns 1 if valid, otherwise 0.
 */
int isValidCategory(const char* category);


/**
 * @brief Processes and validates category input.
 * @details This function converts the category to lowercase and checks
 * if it is valid. If invalid, an error is triggered.
 * @param category Pointer to category string.
 * @return void
 */
void processCategory(char* category);