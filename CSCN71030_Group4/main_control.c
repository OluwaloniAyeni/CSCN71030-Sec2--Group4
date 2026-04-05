#include <stdio.h>
#include <stdlib.h>
#include "main_control.h"
#include "search_filtering.h"
#include "recommendation.h"
#include "user_input.h"

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
	return 0;
}