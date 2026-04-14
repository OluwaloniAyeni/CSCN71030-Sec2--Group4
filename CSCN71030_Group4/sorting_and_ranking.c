#include "sorting_and_ranking.h"
#include <stddef.h>

/**
 * @file sorting_and_ranking.c
 * @brief Handles sorting and ranking of facilities.
 * @details This file contains functions used to sort facilities by price
 * and rank them by rating for better recommendation output.
 * @author Weiming Wang
 * @date 2026-04-13
 */


 /**
  * @brief Sorts facilities by price in ascending order.
  * @details This function uses bubble sort to arrange facilities
  * from the lowest price to the highest price.
  * @author Oluwaloni Ayeni and Weiming Wang
  * @param items Pointer to facility list.
  * @param count Number of facilities in the list.
  * @return void
  * @date 2026-04-13
  */
void sortByPrice(Facility* items, int count)
{
	// check if list is valid or too small to sort.
	if (items == NULL || count <= 1) {
		return;
	}

	// bubble sort algorithm to sort facilities by price in ascending order
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

/*
  * @brief Ranks facilities by rating in descending order.
  * @details This function uses bubble sort to arrange facilities
  * from the highest rating to the lowest rating. If ratings are equal,
  * it further sorts those facilities by price in ascending order.
  * @author Oluwaloni Ayeni and Weiming Wang
  * @param items Pointer to facility list.
  * @param count Number of facilities in the list.
  * @return void
  * @date 2026-04-13
  */
void rankByRating(Facility* items, int count)
{
	// check if list is valid or too small to sort.
	if (items == NULL || count <= 1) {
		return;
	}

	// bubble sort by rating, and by price if ratings are equal
	for (int i = 0; i < count - 1; i++) 
	{
		for (int j = 0; j < count - i - 1; j++)
	 {
			if (items[j].rating < items[j + 1].rating) 
			
		{
				// swap items if the current item has a lower rating than the next item
				Facility temp = items[j];
				items[j] = items[j + 1];
				items[j + 1] = temp;
		}
			// if ratings are equal, sort by price in ascending order
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
