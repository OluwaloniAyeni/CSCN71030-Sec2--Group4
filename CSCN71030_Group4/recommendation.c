#include <stdlib.h>
#include "recommendation.h"

Item* generateRecommendations(Item* filteredlist, int count, int* recommendationCount)
{
	if (filteredlist == NULL || count == 0) 
	{
		*recommendationCount = 0;
		return NULL;
	}

	Item* recommendations = (Item*)malloc(count * sizeof(Item));
	if (recommendations == NULL) 
	{
		*recommendationCount = 0;
		return NULL;
	}

	for (int i = 0; i < count; i++) 
	{
		recommendations[i] = filteredlist[i];
	}

	*recommendationCount = count;
	return recommendations;
}

void sortByPrice(Item* list, int count)
{
	for (int i = 0; i < count - 1; i++) 
	{
		for (int j = 0; j < count - i - 1; j++) 
		{
			if (list[j].price > list[j + 1].price) 
			{
				Item temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

void freeRecommendations(Item* recommendations)
{
	free(recommendations);
}
