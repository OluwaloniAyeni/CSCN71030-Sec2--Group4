#include <stdio.h>
#include "main_control.h"
#include "error_handling.h"

/**
 * @file main.c
 * @brief Entry point of the budget-based recommendation system.
 * @details This file starts the application, displays the welcome message,
 * and calls the main program control function using the data file.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */


 /**
  * @brief Starts the program execution.
  * @details This function displays the system welcome message,
  * loads the data file through startProgram, and handles
  * startup failure if the program cannot begin properly.
  * @author Oluwaloni Ayeni
  * @param void No input parameter.
  * @return int Returns 0 if the program runs successfully, otherwise 1.
  * @date 2026-04-13
  */

int main() 
{
	// display welcome message to the user when the program starts
	printf("=========================================\n");
	printf(" Welcome to Budget-Based Recommendation System\n");
	printf("=========================================\n\n");

	// specify the data file name to load facility information from
	const char* filename = "data.txt";

	// start the main program control function with the specified data file
	if (!startProgram(filename))
	{
		handleError("Main Module", "Program failed to start");
		return 1;
	}

	return 0;
}