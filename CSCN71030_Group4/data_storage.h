#pragma once

#include "item.h"

int loadFacilitiesData(const char* filePath, FacilityList* outList);
int loadBudgetData(const char* filePath, BudgetHistory* outHistory);
const Facility* getFacilitiesData(const FacilityList* list, size_t* count);
const BudgetRecord* getBudgetData(const BudgetHistory* history, size_t* count);
int addBudgetRecord(BudgetHistory* history, const char* category, double budget);
int addFacilityRecord(FacilityList* list, const Facility* record);
void freeDataMemory(FacilityList* list, BudgetHistory* history);
int saveDataToFile(const char* filePath, const FacilityList* list);
int saveBudgetDataToFile(const char* filePath, const BudgetHistory* history);
int filterResults(
    const FacilityList* list,
    const char* category,
    double budget,
    Facility** outResults,
    size_t* outCount
);
void initializeMockData(FacilityList* list);