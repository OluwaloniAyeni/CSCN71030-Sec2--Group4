#pragma once

#include "item.h"

/**
 * @file data_storage.h
 * @brief Handles data loading, saving, and storage.
 * @details This header file declares functions used to load facility
 * and budget data, store records, filter results, and manage memory.
 * @author Evangeline Singh
 * @date 2026-04-13
 */


 /**
  * @brief Loads facility data from file.
  * @author Evangeline Singh
  * @param filePath Path to data file.
  * @param outList Pointer to facility list.
  * @return int Returns 1 if successful, otherwise 0.
  */
int loadFacilitiesData(const char* filePath, FacilityList* outList);


/**
 * @brief Loads budget history data from file.
 * @author Evangeline Singh
 * @param filePath Path to budget file.
 * @param outHistory Pointer to budget history.
 * @return int Returns 1 if successful, otherwise 0.
 */
int loadBudgetData(const char* filePath, BudgetHistory* outHistory);


/**
 * @brief Gets facility data and count.
 * @author Evangeline Singh
 * @param list Pointer to facility list.
 * @param count Pointer to store number of records.
 * @return const Facility* Pointer to facility array.
 */
const Facility* getFacilitiesData(const FacilityList* list, size_t* count);


/**
 * @brief Gets budget history data and count.
 * @author Evangeline Singh
 * @param history Pointer to budget history.
 * @param count Pointer to store number of records.
 * @return const BudgetRecord* Pointer to budget array.
 */
const BudgetRecord* getBudgetData(const BudgetHistory* history, size_t* count);


/**
 * @brief Adds a budget record.
 * @author Evangeline Singh
 * @param history Pointer to budget history.
 * @param category Category name.
 * @param budget Budget value.
 * @return int Returns 1 if successful, otherwise 0.
 */
int addBudgetRecord(BudgetHistory* history, const char* category, double budget);


/**
 * @brief Adds a facility record.
 * @author Evangeline Singh
 * @param list Pointer to facility list.
 * @param record Pointer to facility record.
 * @return int Returns 1 if successful, otherwise 0.
 */
int addFacilityRecord(FacilityList* list, const Facility* record);


/**
 * @brief Frees allocated data memory.
 * @author Evangeline Singh
 * @param list Pointer to facility list.
 * @param history Pointer to budget history.
 * @return void
 */
void freeDataMemory(FacilityList* list, BudgetHistory* history);


/**
 * @brief Saves facility data to file.
 * @author Evangeline Singh
 * @param filePath Output file path.
 * @param list Pointer to facility list.
 * @return int Returns 1 if successful, otherwise 0.
 */
int saveDataToFile(const char* filePath, const FacilityList* list);


/**
 * @brief Saves budget history to file.
 * @author Evangeline Singh
 * @param filePath Output file path.
 * @param history Pointer to budget history.
 * @return int Returns 1 if successful, otherwise 0.
 */
int saveBudgetDataToFile(const char* filePath, const BudgetHistory* history);


/**
 * @brief Filters facilities based on category and budget.
 * @author Evangeline Singh
 * @param list Pointer to facility list.
 * @param category Selected category.
 * @param budget Maximum budget.
 * @param outResults Pointer to filtered results.
 * @param outCount Pointer to number of results.
 * @return int Returns 1 if successful, otherwise 0.
 */
int filterResults(
    const FacilityList* list,
    const char* category,
    double budget,
    Facility** outResults,
    size_t* outCount
);


/**
 * @brief Initializes mock facility data.
 * @author Evangeline Singh
 * @param list Pointer to facility list.
 * @return void
 */
void initializeMockData(FacilityList* list);