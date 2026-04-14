#include <stdio.h>
#include <string.h>
#include "user_input.h"
#include "input_validation.h"

/**
 * @file input_validation.c
 * @brief Validates user input.
 * @details This file contains functions used to check whether the
 * user's category and budget input are valid before processing.
 * @author Afsana Zaman
 * @date 2026-04-13
 */


 /**
  * @brief Validates the user request.
  * @details This function checks that the budget is not negative and
  * the selected category is one of the allowed categories.
  * @author Oluwaloni Ayeni and Afsana Zaman
  * @param req User request containing category and budget.
  * @return int Returns 1 if input is valid, otherwise 0.
  * @date 2026-04-13
 */
int validateInput(UserRequest req) {

	// check if budget is negative, if so print error message and return invalid
    if (req.budget < 0) {
        printf("Error: Budget cannot be negative.\n");
        return 0;
    }

	// check if category is valid, if not print error message and return invalid
    if (strcmp(req.category, "gym") != 0 
        && strcmp(req.category, "hotel") != 0 
        && strcmp(req.category, "restaurant") != 0
        && strcmp(req.category, "cafe") != 0) {
        printf("Error: Invalid category.\n");
        return 0;
    }

    return 1;
}