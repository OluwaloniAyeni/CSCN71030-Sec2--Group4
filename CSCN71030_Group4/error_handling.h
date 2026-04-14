#pragma once

/**
 * @file error_handling.h
 * @brief Handles error and message output.
 * @details This header file declares functions used to display
 * error messages and general system messages to the user.
 * @author Weiming Wang
 * @date 2026-04-13
 */


 /**
  * @brief Displays an error message.
  * @details Prints an error message with optional module name.
  * @author Weiming Wang
  * @param moduleName Name of the module where error occurred.
  * @param message Error message to display.
  * @return void
  */
void handleError(const char* moduleName, const char* message);


/**
 * @brief Displays a general message.
 * @details Prints a normal message to the user.
 * @author Weiming Wang
 * @param message Message to display.
 * @return void
 */
void handleMessage(const char* message);