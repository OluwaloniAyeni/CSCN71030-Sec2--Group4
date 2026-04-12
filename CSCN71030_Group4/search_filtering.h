#pragma once

#include "item.h"

Facility* filterByBudget(Facility* list, int count, const char* category, float minBudget, float maxBudget, int* filteredCount);
void freeResults(Facility* list);