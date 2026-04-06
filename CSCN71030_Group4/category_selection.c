#include <string.h>
#include "category_selection.h"

const char* processCategory(const char* categoryInput)
{
	if (categoryInput == NULL)
	{
		return NULL;
	}

	if (strcmp(categoryInput, "gym") == 0)
	{
		return "gym";
	}

	else if (strcmp(categoryInput, "hotel") == 0)
	{
		return "hotel";
	}

	else if (strcmp(categoryInput, "restaurant") == 0)
	{
		return "restaurant";
	}

	return NULL;
}