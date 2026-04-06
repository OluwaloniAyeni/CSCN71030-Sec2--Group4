#include <stdio.h>
#include "error_handling.h"

void handleError(const char* moduleName, const char* message)
{
	if (moduleName == NULL && message == NULL)
	{
		printf("Error: Unknown error\n");
		return;
	}

	if (moduleName == NULL)
	{
		printf("Error: %s\n", message);
		return;
	}

	if (message == NULL)
	{
		printf("Error in %s.\n", moduleName);
		return;
	}

	printf("Error in %s: %s\n", moduleName, message);
}