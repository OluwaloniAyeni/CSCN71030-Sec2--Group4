#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_filtering.h"
#include "error_handling.h"

Facility*loadData(const char* filename, int* count)
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

	Facility* items = (Facility*)malloc((*count) * sizeof(Facility));
	if (items == NULL) {
		fclose(file);
		*count = 0;
		return NULL;
	}

	int i = 0;
	while (fgets(line, sizeof(line), file) && i < *count) 
	{
	int fieldsRead = sscanf(line, "%d,%49[^,],%49[^,],%f,%f,%d,%d", &items[i].facilityID, 
			items[i].name, items[i].category, &items[i].price, &items[i].rating, 
		&items[i].hasWifi, &items[i].hasParking);

		if (fieldsRead == 7) 
		{
			continue;
		}

		i++;
	}
	fclose(file);
	return items;
}

Facility* filterByBudget(Facility* list, int count, const char* category, float minBudget,
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