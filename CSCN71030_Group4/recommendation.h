#pragma once
#include "item.h"

Item* generateRecommendations(Item* filteredlist, int count, int* recommendationCount);
void sortByPrice(Item* list, int count);
void freeRecommendations(Item* list);
