#include <stdio.h>

int isWithinBudget(float price, float budget)
{
	return price <= budget;
}

int isValidItem(Item item)
{
	return item.price > 0;
}