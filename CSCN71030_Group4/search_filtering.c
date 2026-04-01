#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_filtering.h"

Item*loadData(const char* filename, int* count)
{
	FILE* file = fopen(filename, "r");
	char line[200];

	if (file == NULL) {
		printf("Error opening file.\n");
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
