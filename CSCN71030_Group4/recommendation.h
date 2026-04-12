#pragma once
#include "item.h"

Facility* generateRecommendations(Facility* filteredlist, int count, int* recommendationCount);
void sortByPrice(Facility* list, int count);
void freeRecommendations(Facility* list);
