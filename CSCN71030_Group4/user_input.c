#include <stdio.h>
#include <string.h>
#include "user_input.h"

UserRequest getUserInput() {
    UserRequest req;
    int choice;

	req.category[0] = '\0';
	req.budget = 0.0;

    while (1) {
        printf("\nSelect Category:\n");
        printf("1. Gym\n");
        printf("2. Hotel\n");
        printf("3. Restaurant\n");
        printf("4. Cafe\n");
        printf("Enter choice: ");
        
        if (scanf_s("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');

            continue;

        }

        if (choice < 1 || choice > 4)
        {
            printf("Invalid choice. Please select a number between 1 and 4.\n");
            while (getchar() != '\n');
            continue;
        }

        break;
    }

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
    while(1) 
    {
    printf("Enter your maximum budget: ");
    if (scanf_s("%lf", &req.budget) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n');
        continue;
	}

    if (req.budget < 0)
    {
        printf("Invalid budget. Please enter a non-negative number.\n");
        continue;
    }
    break;
	}

    return req;
}