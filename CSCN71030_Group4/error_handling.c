#include <stdio.h>
#include "error_handling.h"

/**
 * @file error_handling.c
 * @brief Handles error and message output.
 * @details This file contains functions used to display error messages
 * and general system messages in a consistent format.
 * @author Oluwaloni Ayeni and Weiming Wang
 * @date 2026-04-13
 */


 /**
  * @brief Displays an error message.
  * @details This function prints formatted error messages depending
  * on whether module name or message is provided.
  * @author Oluwaloni Ayeni and Weiming Wang
  * @param moduleName Name of the module where error occurred.
  * @param message Error message to display.
  * @return void
  * @date 2026-04-13
  */
void handleError(const char* moduleName, const char* message)
{
	// if both module name and message are missing, print a generic error message
	if (moduleName == NULL && message == NULL)
	{
		printf("Error: Unknown error\n");
		return;
	}

	// if only module name is missing, print the error message without module context
	if (moduleName == NULL)
	{
		printf("Error: %s\n", message);
		return;
	}

	// if only message is missing, print a generic error message with module context
	if (message == NULL)
	{
		printf("Error in %s.\n", moduleName);
		return;
	}

	// if both module name and message are provided, print the full error message
	printf("Error in %s: %s\n", moduleName, message);
}

 /**
  * @brief Displays a general message.
  * @details This function prints a normal message if it is not NULL.
  * @author Oluwaloni Ayeni and Weiming Wang
  * @param message Message to display.
  * @return void
  * @date 2026-04-13
  */
void handleMessage(const char* message)
{
	// print message if valid.
	if(message != NULL)
	{
		printf("%s\n", message);
	}
}