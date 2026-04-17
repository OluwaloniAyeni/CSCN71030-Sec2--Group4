#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "data_storage.h"
#include "recommendation.h"

/*
 * integration_test.c
 * Tests module interaction:
 * Data Storage -> Filtering -> Recommendation
 */

void printRecommendations(Facility* list, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        printf("%d. %s | %s | %.2f | %.1f\n",
            i + 1,
            list[i].name,
            list[i].category,
            list[i].price,
            list[i].rating);
    }
}

int main(void)
{
    FacilityList list = { NULL, 0 };
    Facility* filteredResults = NULL;
    Facility* recommendations = NULL;
    size_t filteredCount = 0;
    int recommendationCount = 0;

    Facility f1 = { 1, "Cafe A", "cafe", 10.0f, 4.5f, 1, 1 };
    Facility f2 = { 2, "Cafe B", "cafe", 25.0f, 4.0f, 1, 0 };
    Facility f3 = { 3, "Cafe C", "cafe", 5.0f, 4.5f, 0, 1 };
    Facility f4 = { 4, "Hotel A", "hotel", 100.0f, 3.5f, 1, 1 };
    Facility f5 = { 5, "Gym A", "gym", 20.0f, 4.2f, 1, 1 };

    printf("=== INTEGRATION TEST START ===\n");

    addFacilityRecord(&list, &f1);
    addFacilityRecord(&list, &f2);
    addFacilityRecord(&list, &f3);
    addFacilityRecord(&list, &f4);
    addFacilityRecord(&list, &f5);

    /* IT-01: Data Storage -> Filter */
    printf("\nIT-01: Data Storage -> Filter\n");
    if (filterResults(&list, "cafe", 20.0, &filteredResults, &filteredCount) == 1 && filteredCount == 2)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    free(filteredResults);
    filteredResults = NULL;
    filteredCount = 0;

    /* IT-02: Filter -> Recommendation */
    printf("\nIT-02: Filter -> Recommendation\n");
    filterResults(&list, "cafe", 20.0, &filteredResults, &filteredCount);
    recommendations = generateRecommendations(filteredResults, (int)filteredCount, &recommendationCount);

    if (recommendations != NULL && recommendationCount == 2)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    free(filteredResults);
    freeRecommendations(recommendations);
    filteredResults = NULL;
    recommendations = NULL;
    filteredCount = 0;
    recommendationCount = 0;

    /* IT-03: Recommendation Ranking */
    printf("\nIT-03: Recommendation Ranking\n");
    filterResults(&list, "cafe", 30.0, &filteredResults, &filteredCount);
    recommendations = generateRecommendations(filteredResults, (int)filteredCount, &recommendationCount);

    if (recommendations != NULL &&
        recommendationCount == 3 &&
        recommendations[0].rating >= recommendations[1].rating &&
        recommendations[1].rating >= recommendations[2].rating)
    {
        printf("PASS\n");
        printRecommendations(recommendations, recommendationCount);
    }
    else
    {
        printf("FAIL\n");
    }
    free(filteredResults);
    freeRecommendations(recommendations);
    filteredResults = NULL;
    recommendations = NULL;
    filteredCount = 0;
    recommendationCount = 0;

    /* IT-04: Category and Budget Filtering */
    printf("\nIT-04: Category and Budget Filtering\n");
    if (filterResults(&list, "hotel", 150.0, &filteredResults, &filteredCount) == 1 && filteredCount == 1)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    free(filteredResults);
    filteredResults = NULL;
    filteredCount = 0;

    /* IT-05: Full Flow (Valid Input) */
    printf("\nIT-05: Full Flow (Valid Input)\n");
    filterResults(&list, "cafe", 30.0, &filteredResults, &filteredCount);
    recommendations = generateRecommendations(filteredResults, (int)filteredCount, &recommendationCount);

    if (recommendations != NULL && recommendationCount > 0)
    {
        printf("PASS\n");
        printRecommendations(recommendations, recommendationCount);
    }
    else
    {
        printf("FAIL\n");
    }
    free(filteredResults);
    freeRecommendations(recommendations);
    filteredResults = NULL;
    recommendations = NULL;
    filteredCount = 0;
    recommendationCount = 0;

    /* IT-06: No Match Case */
    printf("\nIT-06: No Match Case\n");
    if (filterResults(&list, "cafe", 1.0, &filteredResults, &filteredCount) == 1 && filteredCount == 0)
    {
        printf("PASS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    free(filteredResults);
    filteredResults = NULL;
    filteredCount = 0;

    /* IT-07: Repeated Flow */
    printf("\nIT-07: Repeated Flow\n");
    filterResults(&list, "cafe", 20.0, &filteredResults, &filteredCount);
    recommendations = generateRecommendations(filteredResults, (int)filteredCount, &recommendationCount);

    if (recommendations != NULL && recommendationCount > 0)
    {
        printf("PASS (First Run)\n");
    }
    else
    {
        printf("FAIL (First Run)\n");
    }
    free(filteredResults);
    freeRecommendations(recommendations);

    filteredResults = NULL;
    recommendations = NULL;
    filteredCount = 0;
    recommendationCount = 0;

    filterResults(&list, "hotel", 200.0, &filteredResults, &filteredCount);
    recommendations = generateRecommendations(filteredResults, (int)filteredCount, &recommendationCount);

    if (recommendations != NULL && recommendationCount > 0)
    {
        printf("PASS (Second Run)\n");
    }
    else
    {
        printf("FAIL (Second Run)\n");
    }
    free(filteredResults);
    freeRecommendations(recommendations);

    filteredResults = NULL;
    recommendations = NULL;
    filteredCount = 0;
    recommendationCount = 0;

    /* IT-08: Exit Simulation */
    printf("\nIT-08: Exit Simulation\n");
    printf("PASS\n");

    free(list.items);

    printf("\n=== INTEGRATION TEST COMPLETE ===\n");
    return 0;
}