#include "sorting_and_ranking.h"
#include <stddef.h>

void sortByPrice(Facility* items, int count)
{

	if (items == NULL || count <= 1) {
		return;
	}

	for (int i = 0; i < count - 1; i++) 

	{
		for (int j = 0; j < count - i - 1; j++)
	 {
			if (items[j].price > items[j + 1].price) 
			
		{
				Facility temp = items[j];
				items[j] = items[j + 1];
				items[j + 1] = temp;
		}
		
	 }
	}
}

void rankByRating(Facility* items, int count)
{
	if (items == NULL || count <= 1) {
		return;
	}
	for (int i = 0; i < count - 1; i++) 
	{
		for (int j = 0; j < count - i - 1; j++)
	 {
			if (items[j].rating < items[j + 1].rating) 
			
		{
				Facility temp = items[j];
				items[j] = items[j + 1];
				items[j + 1] = temp;
		}
			else if (items[j].rating == items[j + 1].rating &&
				items[j].price > items[j + 1].price)
		{
				Facility temp = items[j];
				items[j] = items[j + 1];
				items[j + 1] = temp;
		}
	 }
	}
}
