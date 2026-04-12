#include <stdio.h>
#include "budget_handling.h"

void processBudget(UserRequest req) {
    Item items[5] = {
        {1, GYM, 15.0, "Gym A"},
        {2, HOTEL, 40.0, "Hotel B"},
        {3, RESTAURANT, 10.0, "Restaurant C"},
        {4, GYM, 25.0, "Gym B"},
        {5, HOTEL, 60.0, "Hotel C"}
    };

    int found = 0;

    printf("\nFiltered Results:\n");

    for (int i = 0; i < 5; i++) {
        if (items[i].category == req.category &&
            items[i].price <= req.maxBudget) {
            printf("%s - $%.2f\n", items[i].name, items[i].price);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching results found.\n");
    }
}