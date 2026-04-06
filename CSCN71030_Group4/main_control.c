#include <stdio.h>
#include <stdlib.h>

#include "main_control.h"
#include "user_input.h"
#include "input_validation.h"
#include "search_filtering.h"
#include "recommendation.h"
#include "sorting_and_ranking.h"
#include "output_display.h"
#include "category_selection.h"

int startProgram(const char* filename)
{
	int count = 0;
	Item* allItems = loadData(filename, &count);

	if (allItems == NULL || count <= 0)
	{
		printf("Error: Could not load data from file:\n");
		return 1;
	}

	manageFlow(allItems, count);

	freeResults(allItems);
	return 1;
}

void manageFlow(Item* allItems, int count)
{
	int filteredCount = 0;

	UserRequest request = getUserInput();

	if(!validateInput(request))
	{
		printf("Error: Invalid user input:\n");
		return;
	}

	Item* filteredItems = filterByBudget(
		allItems, count, request.category, 0.0f, request.maxBudget, &filteredCount
	);

	if (filteredItems == NULL || filteredCount == 0)
	{
		printf("No matching results found within your budget:\n");
		return;
	}

	int recommendationCount = 0;
	Item* recommendations = generateRecommendations(filteredItems, filteredCount,
		&recommendationCount);

	if (recommendations == NULL)
	{
		printf("Error: Could not generate recommendations:\n");
		freeResults(filteredItems);
		return;
	}

	displayResults(recommendations, recommendationCount);
	freeResults(filteredItems);
	freeResults(recommendations);
}

void displayResults(Item* recommendations, int count)
{
	if (recommendations == NULL || count <= 0)
	{
		printf("No results to display:\n");
		return;
	}

	printf("\nRecommended Results:\n");

	for (int i = 0; i < count; i++)
	{
		printf("%d. %s | Category: %s | Price: $%.2f | Rating: %.1f\n",
			i + 1,
			recommendations[i].name,
			recommendations[i].category,
			recommendations[i].price,
			recommendations[i].rating);
	}
}