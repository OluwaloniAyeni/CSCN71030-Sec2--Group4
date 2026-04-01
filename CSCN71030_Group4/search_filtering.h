#pragma once

#include "item.h"

Item* loadData(const char* filename, int* count);
Item* filterByBudget(Item* list, int count, const char* category, float minBudget, float maxBudget, int* filteredCount);
void freeResults(Item* list);