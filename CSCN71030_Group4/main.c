#include <stdio.h>

#include "user_input.h"
#include "input_validation.h"
#include "budget_handling.h"

int main() {
    UserRequest req = getUserInput();

    if (validateInput(req)) {
        processBudget(req);
    }

    return 0;
}