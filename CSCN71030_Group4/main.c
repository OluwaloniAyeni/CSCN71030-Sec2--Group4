#include <stdio.h>
#include "main_control.h"
#include "error_handling.h"


int main() 
{
	printf("=========================================\n");
	printf(" Welcome to Budget-Based Recommendation System\n");
	printf("=========================================\n\n");

	const char* filename = "data.txt";

	if (!startProgram(filename))
	{
		handleError("Main Module", "Program failed to start");
		return 1;
	}

	return 0;
}