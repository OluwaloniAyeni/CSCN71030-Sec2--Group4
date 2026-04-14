#pragma once

#include "item.h"

/**
 * @file input_validation.h
 * @brief Declares input validation functions.
 * @details This header file contains the function prototype used to
 * validate the user's category and budget input.
 * @author Afsana Zaman
 * @date 2026-04-13
 */

 /**
  * @brief Validates the user request.
  * @details Checks whether the user's budget is non-negative and
  * whether the category is one of the allowed values.
  * @author Afsana Zaman
  * @param req Structure containing user category and budget.
  * @return int Returns 1 if input is valid, otherwise 0.
  * @date 2026-04-13
  */

int validateInput(UserRequest req);