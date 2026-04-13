#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "main_control.h"
#include "user_input.h"
#include "data_storage.h"
#include "input_validation.h"
#include "search_filtering.h"
#include "recommendation.h"
#include "sorting_and_ranking.h"
#include "output_display.h"
#include "category_selection.h"
#include "error_handling.h"

/**
 * @file main_control.c
 * @brief Controls the main program flow.
 * @details This file contains the main workflow of the system, including
 * loading data, handling repeated searches, validating input,
 * filtering results, generating recommendations, and displaying output.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */


 /**
  * @brief Starts the budget-based recommendation system.
  * @details This function loads facility data from file, runs the main search flow,
  * and asks the user whether to continue searching or exit the program.
  * @author Oluwaloni Ayeni
  * @param filename Name of the data file to load.
  * @return int Returns 1 if program runs successfully, otherwise 0.
  * @date 2026-04-13
  */

int startProgram(const char* filename)
{
	FacilityList list;
	int option = 1;

	//load facilities data from file
	if (loadFacilitiesData(filename, &list) != 1)
	{
		handleError("Data Storage Module", "Failed to load data");
		return 0;
	}

	// Keep running the program until user chooses to exit
	while (option == 1)
	
	{
		manageFlow(list.items, (int)list.count);

		// asks user if they want to perform another search
		while (1)
		{
			printf("\nDo you want to perform another search?\n");
			printf("1. Yes\n");
			printf("0. Exit\n");
			printf("Enter choice: ");

			// validate yes or no input
			if (scanf_s("%d", &option) != 1)
			{
				printf("Invalid input. Please enter 1 or 0.\n");
				while (getchar() != '\n');
				continue;
			}
			// continue with another search
			if (option == 1)
			{
				break;
			}

			// else exit the program
			else if (option == 0)
			{
				printf("Thank you for using the Budget-Based Recommendation System. Goodbye!\n");
				free(list.items);
				return 1;
			}

			// reject invalid number choice
			else
			{
				printf("Invalid choice. Please enter 0 or 1.\n");
			}
		}
	}

	// free loaded data before ending
	free(list.items);
	return 1;
}

/**
 * @brief Manages one complete search flow.
 * @details This function gets user input, validates it, filters facilities,
 * generates recommendations, sorts and ranks them, and displays results.
 * @author Oluwaloni Ayeni
 * @param allItems Pointer to all loaded facilities.
 * @param count Number of facilities in the list.
 * @return void
 * @date 2026-04-13
 */
void manageFlow(Facility* allItems, int count)
{
	int filteredCount = 0;

	// get user request for category and budget
	UserRequest request = getUserInput();

	// validate the user request
	if (!validateInput(request))
	{
		return;
	}

	// filter facilities based on category and budget
	Facility* filteredItems = filterByBudget(
		allItems, count, request.category, 0.0f,
		(float)request.budget, &filteredCount
	);

	// display message if no matching result
	if (filteredItems == NULL || filteredCount == 0)
	{
		handlemessage("\nNo matching results found for your selection.\n");
	}

	else
	{
		int recommendationCount = 0;

		// generate recommendations from filtered items
		Facility* recommendations = generateRecommendations(filteredItems, filteredCount,
			&recommendationCount);

		// check if recommendation generation failed
		if (recommendations == NULL || recommendationCount == 0)
		{
			handleError("Recommendation Module", "Could not generate recommendations");
		}

		else
		{
			// sort and rank final recommendations
			sortByPrice(recommendations, recommendationCount);
			rankByRating(recommendations, recommendationCount);

			// display final recommendation results
			displayResults(&request, recommendations, recommendationCount);

			// free recommendation memory
			freeResults(recommendations);
		}

		// free filtered results memory
		freeResults(filteredItems);
	}

}


