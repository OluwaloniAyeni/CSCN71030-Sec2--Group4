#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_filtering.h"
#include "error_handling.h"



Facility* filterByBudget(Facility* list, int count, const char* category, float minBudget,
	float maxBudget, int* filteredCount)
{
	int i;
	int j;
	Facility* filtered;

	*filteredCount = 0;

	if (list == NULL || category == NULL || filteredCount == NULL) {
		return NULL;
	}

	for (i = 0; i < count; i++) {
		if (strcmp(list[i].category, category) == 0 &&
			list[i].price >= minBudget && list[i].price <= maxBudget) {
			(*filteredCount)++;
		}
	}

	if (*filteredCount == 0) {
		return NULL;
	}

	Facility* filtered = (Facility*)malloc((*filteredCount) * sizeof(Facility));
	if (filtered == NULL)
		{
		*filteredCount = 0;
		return NULL;
	}

	int j = 0;

	for (int i = 0; i < count; i++) {
		if (strcmp(list[i].category, category) == 0 &&
			list[i].price >= minBudget && list[i].price <= maxBudget) {
			filtered[j++] = list[i];
		}
	}
	return filtered;
}

void freeResults(Facility* list)
{
	free(list);
}