#include <stdio.h>
#include <string.h>
#include "user_input.h"

/**
 * @file user_input.c
 * @brief Handles user input for category and budget.
 * @details This file contains functions used to collect and validate
 * the user's category choice and maximum budget input.
 * @author Afsana Zaman
 * @date 2026-04-13
 */


 /**
  * @brief Gets category and budget input from the user.
  * @details This function asks the user to select a category using a number
  * and enter a maximum budget. It validates the input before returning it.
  * @author Oluwaloni Ayeni and Afsana Zaman
  * @return UserRequest Returns a structure containing the selected category and budget.
  * @date 2026-04-13
  */
UserRequest getUserInput() {
    UserRequest req;
    int choice;

	// initialize category and budget to default values
	req.category[0] = '\0';
	req.budget = 0.0;

	// loop until valid category choice is made
    while (1) {
        printf("\nSelect Category:\n");
        printf("1. Gym\n");
        printf("2. Hotel\n");
        printf("3. Restaurant\n");
        printf("4. Cafe\n");
        printf("Enter choice: ");
        
        // check if input is a valid number.
        if (scanf_s("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');

            continue;

        }

		// check if selected number is within valid range for categories.
        if (choice < 1 || choice > 4)
        {
            printf("Invalid choice. Please select a number between 1 and 4.\n");
            while (getchar() != '\n');
            continue;
        }

        break;
    }

	// convert number choice into corresponding category string and store in user request structure
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

    // keep asking until budget input is valid.
    while(1) 
    {
    printf("Enter your budget: ");

    // check if budget is a valid number.
    if (scanf_s("%lf", &req.budget) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n');
        continue;
	}

    // check if budget is negative.
    if (req.budget < 0)
    {
        printf("Invalid budget. Please enter a non-negative number.\n");
        continue;
    }
    break;
	}

    return req;
}