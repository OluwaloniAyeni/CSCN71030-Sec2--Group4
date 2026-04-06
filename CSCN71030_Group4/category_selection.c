#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "category_selection.h"

void toLowerCase(char* str)
{
	for (int i = 0; str[i]; i++)
	{
		str[i] = tolower(str[i]);
	}
}
int isValidCategory(const char* category)
{
	if (category == NULL)
	{
		return 0;
	}
	if (strcmp(category, "gym") == 0 ||
		strcmp(category, "hotel") == 0 ||
		strcmp(category, "restaurant") == 0)
	{
		return 1;
	}
	return 0;
}

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