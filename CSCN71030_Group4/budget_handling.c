#include <stdio.h>
#include <string.h>
#include "item.h"
#include "budget_handling.h"

void processBudget(UserRequest req) {
    Facility items[5] = {
        {1, "GYM A", "gym", 15.0f, 4.2f, 1, 0},
        {2, "HOTEL B", "hotel", 40.0f, 4.5f, 1, 0},
        {3, "RESTAURANT C", "restaurant", 10.0f, 4.0f, 1, 0},
        {4, "GYM B", "gym", 25.0f, 4.3f, 1, 0},
        {5, "HOTEL C", "hotel", 60.0f, 4.6f, 1, 0}
    };

    int found = 0;

    printf("\nFiltered Results:\n");

    for (int i = 0; i < 5; i++) {
        if (strcmp(items[i].category, req.category) == 0  &&
            items[i].price <= (float) req.budget) {
            printf("%s - $%.2f\n", items[i].name, items[i].price);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching results found.\n");
    }
}