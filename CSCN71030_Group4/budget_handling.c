#include <stdio.h>
#include <string.h>
#include "item.h"
#include "budget_handling.h"

Facility* processBudget(Facility* allItems, int count, UserRequest req, int* filteredCount)
{
    
    static Facility filtered[100];
    int found = 0;

    printf("\nFiltered Results:\n");

    for (int i = 0; i < count; i++) {
        if (strcmp(allItems[i].category, req.category) == 0  &&
            allItems[i].price <= (float) req.budget) {
            
                {
					filtered[found++] = allItems[i];
                }
      
        }

    }

	*filteredCount = found;
   
	return (found > 0) ? filtered : NULL;
  
}