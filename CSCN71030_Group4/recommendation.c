#include <stdlib.h>
#include "recommendation.h"

/**
 * @file recommendation.c
 * @brief Handles recommendation generation.
 * @details This file contains functions used to generate recommendations
 * from filtered facility results and free allocated memory.
 * @author Oluwaloni Ayeni
 * @date 2026-04-13
 */


 /**
  * @brief Generates recommendations from filtered facilities.
  * @details This function creates a new dynamic array and copies all
  * filtered facilities into it as recommendations.
  * @author Oluwaloni Ayeni
  * @param filteredlist Pointer to filtered facility list.
  * @param count Number of facilities in filtered list.
  * @param recommendationCount Pointer to store number of recommendations.
  * @return Facility* Returns pointer to recommendation array, or NULL if error occurs.
  * @date 2026-04-13
  */
Facility* generateRecommendations(Facility* filteredlist, int count, int* recommendationCount)
{
	// check if the recommendation count pointer is valid
	if (recommendationCount == NULL) 
	{
		return NULL;
	}

	// checks if the filtered list is empty or invalid, 
	// if so return null and set recommendation count to 0
	if (filteredlist == NULL || count == 0) 
	{
		*recommendationCount = 0;
		return NULL;
	}

	// allocate memory for the recommendations array based on the count of filtered facilities
	Facility* recommendations = (Facility*)malloc(count * sizeof(Facility));
	if (recommendations == NULL) 
	{
		*recommendationCount = 0;
		return NULL;
	}

	// copy the filtered facilities into the recommendations array
	for (int i = 0; i < count; i++) 
	{
		recommendations[i] = filteredlist[i];
	}

	// set the total number of recommendations
	*recommendationCount = count;
	return recommendations;
}

/*
* @brief Frees recommendation memory.
* @details This function frees the dynamically allocated memory used for storing recommendations.
* @author Oluwaloni Ayeni
* @param recommendations Pointer to the recommendation list.
* @return void
* @date 2026-04-13
*/
void freeRecommendations(Facility* recommendations)
{
	// free the allocated recommendation memory.
	free(recommendations);
}
