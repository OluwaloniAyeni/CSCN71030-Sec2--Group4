#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_filtering.h"

Item*loadData(const char* filename, int* count)
{
	FILE* file = fopen(filename, "r");
	char line[200];

	if (file == NULL) {
		handleError("Data Loading Module", "Failed to open file");
		*count = 0;
		return NULL;
	}
	*count = 0;
	while (fgets(line, sizeof(line), file)) {
		if (strlen(line) > 1) {
			(*count)++;
		}
	}
	if (*count == 0) {
		fclose(file);
		return NULL;
	}

	rewind(file);

	Item* items = (Item*)malloc((*count) * sizeof(Item));
	if (items == NULL) {
		fclose(file);
		*count = 0;
		return NULL;
	}

	int i = 0;
	while (fgets(line, sizeof(line), file) && i < *count) {
		sscanf(line, "%d,%49[^,],%49[^,],%f,%f", &items[i].itemID, 
			items[i].name, items[i].category, &items[i].price, &items[i].rating);
		i++;
	}
	fclose(file);
	return items;
}

Item* filterByBudget(Item* list, int count, const char* category, float minBudget,
	float maxBudget, int* filteredCount)
{
	*filteredCount = 0;

	for (int i = 0; i < count; i++) {
		if (strcmp(list[i].category, category) == 0 &&
			list[i].price >= minBudget && list[i].price <= maxBudget) {
			(*filteredCount)++;
		}
	}

	if (*filteredCount == 0) {
		return NULL;
	}

	Item* filtered = (Item*)malloc((*filteredCount) * sizeof(Item));
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

void freeResults(Item* list)
{
	free(list);
}