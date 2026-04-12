#include <stdlib.h>
#include "recommendation.h"

Facility* generateRecommendations(Facility* filteredlist, int count, int* recommendationCount)
{
	if (recommendationCount == NULL) 
	{
		return NULL;
	}

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


void freeRecommendations(Facility* recommendations)
{
	free(recommendations);
}
