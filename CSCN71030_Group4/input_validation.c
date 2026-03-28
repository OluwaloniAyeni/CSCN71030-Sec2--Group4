#include <stdio.h>
#include "input_validation.h"

int validateInput(UserRequest req) {
    if (req.maxBudget < 0) {
        printf("Invalid budget!\n");
        return 0;
    }
    return 1;
}