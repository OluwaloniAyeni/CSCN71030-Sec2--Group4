#include <stdio.h>
#include "input_validation.h"

int validateInput(UserRequest req) {
    if (req.maxBudget < 0) {
        printf("Error: Budget cannot be negative.\n");
        return 0;
    }

    if (req.category < GYM || req.category > RESTAURANT) {
        printf("Error: Invalid category.\n");
        return 0;
    }

    return 1;
}