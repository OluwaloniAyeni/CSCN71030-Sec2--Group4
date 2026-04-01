#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search_filtering.h"

int isWithinBudget(float price, float budget)
{
	return price <= budget;
}

int isValidItem(Item item)
{
	return item.price > 0;
}