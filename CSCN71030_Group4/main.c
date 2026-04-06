#include <stdio.h>
#include "main_control.h"


int main() 
{
	const char* filename = "data.txt";

	if (!startProgram(filename))
	{
		printf("Program failed to start:\n");
		return 1;
	}

	return 0;
}