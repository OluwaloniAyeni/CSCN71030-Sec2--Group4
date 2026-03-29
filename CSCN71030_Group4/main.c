#include <stdio.h>
#include "user_input.h"
#include "input_validation.h"
#include "budget_handling.h"

void showWelcomeMessage()
{
	printf("Welcome to the system\n");
}

void showExitMessage()
{
printf("Thank you for using our system\n");
}


int main() {
    UserRequest req = getUserInput();

    if (validateInput(req)) {
        processBudget(req);
    }

    return 0;
}