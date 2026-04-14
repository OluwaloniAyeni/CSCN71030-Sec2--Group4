#include <stdio.h>
#include "item.h"
#include "output_display.h"

/**
 * @file output_display.c
 * @brief Displays search results to the user.
 * @details This file contains functions used to display filtered
 * and recommended facilities in a structured table format.
 * @author Evangeline Singh
 * @date 2026-04-13
 */


 /**
  * @brief Displays the final search results.
  * @details This function prints the user's selected category and budget,
  * and displays all matching facilities in a formatted table.
  *  If no results are found, a message is shown instead.
  * @author Oluwaloni Ayeni and Evangeline Singh
  * @param request Pointer to user request (category and budget).
  * @param items Pointer to list of facilities to display.
  * @param count Number of facilities.
  * @return void
  * @date 2026-04-13
  */
void displayResults(const UserRequest* request, const Facility* items, size_t count) {



	size_t i;

	// check if request pointer is valid before processing
	if (request == NULL) {
		return;

	}

	// display search summary.
	printf("\n==== Search Results ===");
	printf(" Category: %s\n", request->category);
	printf(" Budget: %.2f\n", request->budget);

	// check if no results are available.
	if (items == NULL || count == 0) {

		printf("\nNo facilities matched your selections\n");
		return;

	}

	// display table header for the results.
	printf("\n%-4s %-30s %-12s %-8s %-6s %-8s\n",
		"#", "Name", "Price", "Rating", "WI-FI", "Parking");
	printf("--------------------------------------------------------------------\n");

	// print each facility in the results with formatted columns for index, 
	// name, price, rating, Wi-Fi availability, and parking availability.
	for (i = 0; i < count; ++i) {
		printf("%4zu %-30s %-12.2f %-8.1f %-6s %-8s\n",
			i + 1,
			items[i].name,
			items[i].price,
			items[i].rating,
			items[i].hasWifi ? "Yes" : "No",
			items[i].hasParking ? "Yes" : "No");

	}

	printf("\n");



	}

