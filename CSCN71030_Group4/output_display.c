#include <stdio.h>
#include "output_display.h"


void displayResults(const UserRequest* request, const Facility* items, size_t count) {



	size_t i;

	if (request == NULL) {
		return;

	}

	printf("\n=== Search Results ===");
	printf(" Category: %s\n", request->category);
	printf(" Budget: %s\n", request->budget);

	if (items == NULL || count == 0) {

		printf("\nNo facilties matched your selections\n");
		return;

	}


	printf("\n%-4s %-30s %-12x %-8s %-6s %-8s\n "
	"#", "Name", "Price", "Rating" , "WI-FI" , "Parking");
	printf("--------------------------------------------------------------------\n");

	for (i = 0; i < count; ++i) {
		printf(" %-30s %-12.2f %-8.1f %-6s %-8s\n",
			i + 1,
			items[i].name,
			items[i].price,
			items[i].rating,
			items[i].hasWifi ? "Yes" : "No",
			items[i].hasParking ? "Yes" : "No");

	}

	printf("\n");






	}
















