#include <stdio.h>
#include "user_input.h"

UserRequest getUserInput() {
    UserRequest req;
    int choice;

    printf("Select Category:\n");
    printf("1. Gym\n");
    printf("2. Hotel\n");
    printf("3. Restaurant\n");
    printf("Enter choice: ");
    scanf_s("%d", &choice);

    switch (choice) {
    case 1:
        req.category = GYM;
        break;
    case 2:
        req.category = HOTEL;
        break;
    case 3:
        req.category = RESTAURANT;
        break;
    default:
        req.category = RESTAURANT;
    }

    printf("Enter your maximum budget: ");
    scanf_s("%f", &req.maxBudget);

    return req;
}