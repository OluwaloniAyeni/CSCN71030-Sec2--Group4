#include <stdio.h>
#include <string.h>
#include "user_input.h"
#include "input_validation.h"

int validateInput(UserRequest req) {
    if (req.budget < 0) {
        printf("Error: Budget cannot be negative.\n");
        return 0;
    }

    if (strcmp(req.category, "gym") != 0 
        && strcmp(req.category, "hotel") != 0 
        && strcmp(req.category, "restaurant") != 0
        && strcmp(req.category, "cafe") != 0) {

        return 0;
    }

    return 1;
}