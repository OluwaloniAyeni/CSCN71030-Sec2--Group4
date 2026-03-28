#include <stdio.h>
#include "user_input.h"

UserRequest getUserInput() {
    UserRequest req;
    int choice;

    printf("Select Category:\n1. Gym\n2. Hotel\n3. Restaurant\n");
    scanf_s("%d", &choice);

    if (choice == 1) req.category = GYM;
    else if (choice == 2) req.category = HOTEL;
    else req.category = RESTAURANT;

    printf("Enter your budget: ");
    scanf_s("%f", &req.maxBudget);

    return req;
}