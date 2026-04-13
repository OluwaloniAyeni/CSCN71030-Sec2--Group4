#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "category_selection.h"
#include "error_handling.h"

/**
 * @file category_selection.c
 * @brief Handles category processing and validation.
 * @details This file contains functions used to convert category input
 * to lowercase and check if the category is valid.
 * @author Weiming Wang.
 * @date 2026-04-13
 */


 /**
  * @brief Converts a string to lowercase.
  * @details This function changes all uppercase characters in the string
  * to lowercase characters for consistent comparison.
  * @author Weiming Wang and Oluwaloni Ayeni
  * @param str Pointer to the string to modify.
  * @return void
  * @date 2026-04-13
  */
void toLowerCase(char* str)
{
	// check if string is NULL before processing
	if(str == NULL)
	{
		return;
	}
	// convert each character to lowercase using tolower function
	for (int i = 0; str[i]; i++)
	{
		str[i] = tolower(str[i]);
	}
}

/**
 * @brief Checks if a category is valid.
 * @details This function compares the input category with valid categories such as
 * gym, hotel, restaurant and cafe.
 * @author Weiming Wang and Oluwaloni Ayeni
 * @param category Input category string.
 * @return int Returns 1 if valid, otherwise 0.
 * @date 2026-04-13
 */
int isValidCategory(const char* category)
{
	// check if category is null before processing
	if (category == NULL)
	{
		return 0;
	}

	// check if category matches allowed values.
	if (strcmp(category, "gym") == 0 ||
		strcmp(category, "hotel") == 0 ||
		strcmp(category, "restaurant") == 0 ||
		strcmp(category, "cafe") == 0)
	{
		return 1;
	}
	return 0;
}

/**
 * @brief Processes and validates the category input.
 * @details This function converts the category to lowercase and checks if it is valid.
 * If the category is invalid, it triggers an error message.
 * @author Weiming Wang and Oluwaloni Ayeni
 * @param category Pointer to category string.
 * @return void
 * @date 2026-04-13
 */
void processCategory(char* category)
{
	// convert category to lowercase for consistent validation
	toLowerCase(category);

	// check if category is valid.
	if (!isValidCategory(category))
	{
		handleError("Category Selection Module", "Invalid category selected");
		return;
	}

}