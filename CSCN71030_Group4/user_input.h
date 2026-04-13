#pragma once

#include "item.h"

/**
 * @file user_input.h
 * @brief Handles user input.
 * @details This file declares the function used to collect
 * category selection and budget input from the user.
 * @author Afsana Zaman
 * @date 2026-04-13
 */


 /**
  * @brief Gets user input for category and budget.
  * @details This function prompts the user to select a category
  * and enter a maximum budget, then returns the input as a structure.
  * @author Afsana Zaman
  * @return UserRequest Structure containing category and budget.
  * @date 2026-04-13
  */
UserRequest getUserInput();