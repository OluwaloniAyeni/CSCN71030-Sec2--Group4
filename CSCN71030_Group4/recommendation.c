#include <stdlib.h>
#include "recommendation.h"

Item* generateRecommendations(Item* filteredlist, int count, int* recommendationCount)
{
	if (filteredlist == NULL || count == 0) 
	{
		*recommendationCount = 0;
		return NULL;
	}

	Item* recommended = (Item*)malloc(count * sizeof(Item));
	if (recommended == NULL) 
	{
		*recommendationCount = 0;
		return NULL;
	}

	for (int i = 0; i < count; i++) 
	{
		recommended[i] = filteredlist[i];
	}

	*recommendationCount = count;
	return recommended;
}
