#include <stdio.h>
#include <string.h>
#include "user_input.h"

UserRequest getUserInput() {
    UserRequest req;
    int choice;

    printf("Select Category:\n");
    printf("1. Gym\n");
    printf("2. Hotel\n");
    printf("3. Restaurant\n");
	printf("4. Cafe\n");
    printf("Enter choice: ");
    scanf_s("%d", &choice);

    switch (choice) {
    case 1:
        strcpy_s(req.category, sizeof(req.category), "gym");
        break;
    case 2:
        strcpy_s(req.category, sizeof(req.category), "hotel");
        break;
    case 3:
        strcpy_s(req.category, sizeof(req.category), "restaurant");
        break;
	case 4:
        strcpy_s(req.category, sizeof(req.category), "cafe");
		break;
    default:
        strcpy_s(req.category, sizeof(req.category), "restaurant");
    }

    printf("Enter your maximum budget: ");
    scanf_s("%lf", &req.budget);

    return req;
}