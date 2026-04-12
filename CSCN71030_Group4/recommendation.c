#include <stdlib.h>
#include "recommendation.h"

Facility* generateRecommendations(Facility* filteredlist, int count, int* recommendationCount)
{
	if (filteredlist == NULL || count == 0) 
	{
		*recommendationCount = 0;
		return NULL;
	}

	Facility* recommendations = (Facility*)malloc(count * sizeof(Facility));
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

void sortByPrice(Facility* list, int count)
{
	for (int i = 0; i < count - 1; i++) 
	{
		for (int j = 0; j < count - i - 1; j++) 
		{
			if (list[j].price > list[j + 1].price) 
			{
				Facility temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
}

void freeRecommendations(Facility* recommendations)
{
	free(recommendations);
}
