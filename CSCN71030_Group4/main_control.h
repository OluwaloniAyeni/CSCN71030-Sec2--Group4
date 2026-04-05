#pragma once
#include "item.h"

int startProgram(const char* filename);
void manageFlow(Item* allItems, int count);
void displayResults(Item* recommendations, int count);
