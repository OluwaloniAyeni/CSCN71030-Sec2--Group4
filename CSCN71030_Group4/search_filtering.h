#pragma once

#include "item.h"

Facility* loadData(const char* filename, int* count);
Facility* filterByBudget(Facility* list, int count, const char* category, float minBudget, float maxBudget, int* filteredCount);
void freeResults(Facility* list);