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


int startProgram(const char* filename)
{
	FacilityList list;
	int option = 1;

	if (loadFacilitiesData(filename, &list) != 1)
	{
		handleError("Data Storage Module", "Failed to load data");
		return 0;
	}

	while (option == 1)
	
	{
		manageFlow(list.items, (int)list.count);

		while (1)
		{
			printf("\nDo you want to perform another search?\n");
			printf("1. Yes\n");
			printf("0. Exit\n");
			printf("Enter choice: ");

			if (scanf_s("%d", &option) != 1)
			{
				printf("Invalid input. Please enter 1 or 0.\n");
				while (getchar() != '\n');
				continue;
			}
			if (option == 1)
			{
				break;
			}
			else if (option == 0)
			{
				printf("Thank you for using the Budget-Based Recommendation System. Goodbye!\n");
				return 1;
			}
			else
			{
				printf("Invalid choice. Please enter 0 or 1.\n");
			}
		}
	}
	free(list.items);
	return 1;
}

void manageFlow(Facility* allItems, int count)
{
	int filteredCount = 0;

	UserRequest request = getUserInput();

	if (!validateInput(request))
	{
		return;
	}

	Facility* filteredItems = filterByBudget(
		allItems, count, request.category, 0.0f,
		(float)request.budget, &filteredCount
	);

	if (filteredItems == NULL || filteredCount == 0)
	{
		handlemessage("\nNo matching results found for your selection.\n");
	}

	else
	{
		int recommendationCount = 0;

		Facility* recommendations = generateRecommendations(filteredItems, filteredCount,
			&recommendationCount);

		if (recommendations == NULL || recommendationCount == 0)
		{
			handleError("Recommendation Module", "Could not generate recommendations");
		}

		else
		{

			sortByPrice(recommendations, recommendationCount);
			rankByRating(recommendations, recommendationCount);

			displayResults(&request, recommendations, recommendationCount);

			freeResults(recommendations);
		}
		freeResults(filteredItems);
	}

}


