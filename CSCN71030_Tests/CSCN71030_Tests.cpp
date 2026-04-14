#include <assert.h>
#include "data_storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "../CSCN71030_Group4/item.h"	
#include "../CSCN71030_Group4/search_filtering.h"
#include "../CSCN71030_Group4/recommendation.h"
#include "../CSCN71030_Group4/data_storage.h"
}
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SearchFilteringTests
{
	TEST_CLASS(SearchFilteringTests)
	{
	public:
		
		TEST_METHOD(FilterByBudget_ReturnsMatchingItems)
		{
			Facility items[3] = {
				{1, "Hotel A", "hotel", 100.0, 4.5, 1, 1},
				{2, "Hotel B", "hotel", 200.0, 4.0, 1, 0},
				{3, "Hotel C", "hotel", 300.0, 3.5, 0, 1}
			};
			int filteredCount = 0;
			Facility* result = filterByBudget(items, 3, "hotel", 0.0f, 200.0f, &filteredCount);

			Assert::IsNotNull(result);
			Assert::AreEqual(2, filteredCount);

			freeResults(result);
		}

		// No Match
		TEST_METHOD(FilterByBudget_NoResults)
		{
			Facility items[2] = {
				{1, "Gym A", "gym", 500.0f, 4.5f, 1, 1},
				{2, "Gym B", "gym", 600.0f, 4.0f, 1, 0}
			};

			int filteredCount = 0;
			Facility* result = filterByBudget(items, 2, "gym", 0.0f, 100.0f, &filteredCount);	
			Assert::IsNull(result);
			Assert::AreEqual(0, filteredCount);
		}

		//NULL INPUT
		TEST_METHOD(FilterByBudget_NullInput)
		{
			int filteredCount = 0;

			Facility* result = filterByBudget(NULL, 0, "hotel", 0.0f, 200.0f, &filteredCount);

			Assert::IsNull(result);
			Assert::AreEqual(0, filteredCount);
		}
	};
}

namespace RecommendationTests
{
	TEST_CLASS(RecommendationTests)
	{
	public:
		TEST_METHOD(GenerateRecommendations_ReturnsItems)
		{
			Facility filteredItems[3] = {
				{1, "Hotel A", "hotel", 100.0f, 4.5f, 1, 1},
				{2, "Hotel B", "hotel", 150.0f, 4.0f, 1, 0},
				{3, "Hotel C", "hotel", 200.0f, 3.5f, 0, 1}
			};
			int recommendationCount = 0;

			Facility* results = generateRecommendations(filteredItems, 3, &recommendationCount);

		Assert::IsNotNull(results);
		Assert::AreEqual(3, recommendationCount);

		freeRecommendations(results);
		
		}

		// empty input

		TEST_METHOD(GenerateRecommenedations_EmptyInput_ReturnsNull)
		{
			Facility* filteredItems = NULL;
			int recommendationCount = 0;

			Facility* results = generateRecommendations(filteredItems, 0, &recommendationCount);

			Assert::IsNull(results);
			Assert::AreEqual(0, recommendationCount);
		}

		// single matching result input
		TEST_METHOD(GenerateRecommendations_SingleMatchingResult)
		{
			Facility filteredItems[1] = {
				{1, "Hotel A", "hotel", 100.0f, 4.5f} };

			int recommendationCount = 0;

			Facility* results = generateRecommendations(filteredItems, 1, &recommendationCount);

			Assert::IsNotNull(results);
			Assert::AreEqual(1, recommendationCount);

			freeRecommendations(results);
		}

		// check sorting by rating (highest first)

	};
}


namespace FeatureDisplayTests
{
	TEST_CLASS(FeatureDisplayTests)
	{
	public:
		TEST_METHOD(simpleFeatureTest)
		{
			int filterTest( const Facility * input, int wifiRequirement,int parkingRequirement,double minRating) {

				int passWifi = (wifiRequirement == -1) || (f->hasWifi == wifiRequirement);
				int passParking = (parkingRequirement == -1) || (f->hasParking == parkingRequirement);
				int passRating = (minRating < 0.0) || (f->rating >= minRating);

				return passWifi && passParking && passRating;
			};

			Facility f = { "Test", 1, 0, 4.5 };

			int result = filterTest(&f, 1, -1, 4.0);

			if (result == 1) {
				printf("Test passed!\n");
			}
			else {
				printf("Test failed!\n");
			}

			
		
		}

		

		// check sorting by rating (highest first)

	};
}

namespace OutputDisplayTests
{
	TEST_CLASS(OutputDisplayTests)
	{
	public:
		TEST_METHOD(simpleOutputDisplayTest)
		{

			// Mock structs (adjust if yours differ)
			typedef struct {
				char category[50];
				char budget[50];
			} UserRequest;

			typedef struct {
				char name[50];
				double price;
				double rating;
				int hasWifi;
				int hasParking;
			} Facility;

			// Function prototype
			void displayResults(const UserRequest * request, const Facility * items, size_t count);

			int main() {
				UserRequest req = { "Cafe", "Cheap" };

				Facility items[2] = {
					{"Cafe A", 10.0, 4.5, 1, 1},
					{"Cafe B", 15.0, 3.8, 0, 1}
				};

				displayResults(&req, items, 2);

				printf("\n✅ Check manually if output looks correct.\n");

				return 0;
			}



		}



		// check sorting by rating (highest first)

	};
}


/* -----------------------------
   addFacilityRecord Tests
--------------------------------*/

void test_addFacilityRecord() {
	FacilityList list = { NULL, 0 };

	Facility f = { 1, "Hotel A", "hotel", 120.0f, 4.2f, 1, 1 };

	int result = addFacilityRecord(&list, &f);

	assert(result == 1);
	assert(list.count == 1);
	assert(strcmp(list.items[0].name, "Hotel A") == 0);

	free(list.items);
}

void test_addFacilityRecord_invalid() {
	Facility f = { 1, "Test", "hotel", 100.0f, 4.0f, 1, 1 };

	assert(addFacilityRecord(NULL, &f) == 0);
	assert(addFacilityRecord(&(FacilityList) { 0 }, NULL) == 0);
}

/* -----------------------------
   addBudgetRecord Tests
--------------------------------*/

void test_addBudgetRecord() {
	BudgetHistory history = { NULL, 0 };

	int result = addBudgetRecord(&history, "hotel", 200.0);

	assert(result == 1);
	assert(history.count == 1);
	assert(strcmp(history.items[0].category, "hotel") == 0);

	free(history.items);
}

void test_addBudgetRecord_invalid() {
	BudgetHistory history = { NULL, 0 };

	assert(addBudgetRecord(NULL, "hotel", 100.0) == 0);
	assert(addBudgetRecord(&history, NULL, 100.0) == 0);
}

/* -----------------------------
   filterResults Tests
--------------------------------*/

void test_filterResults() {
	FacilityList list = { NULL, 0 };

	Facility f1 = { 1, "A", "hotel", 100.0f, 4.0f, 1, 1 };
	Facility f2 = { 2, "B", "hotel", 300.0f, 4.0f, 1, 1 };

	addFacilityRecord(&list, &f1);
	addFacilityRecord(&list, &f2);

	Facility* results = NULL;
	size_t count = 0;

	int res = filterResults(&list, "hotel", 150.0, &results, &count);

	assert(res == 1);
	assert(count == 1);
	assert(strcmp(results[0].name, "A") == 0);

	free(results);
	free(list.items);
}

void test_filterResults_noMatch() {
	FacilityList list = { NULL, 0 };

	Facility f = { 1, "A", "hotel", 500.0f, 4.0f, 1, 1 };
	addFacilityRecord(&list, &f);

	Facility* results = NULL;
	size_t count = 0;

	int res = filterResults(&list, "gym", 100.0, &results, &count);

	assert(res == 1);
	assert(count == 0);

	free(list.items);
}

/* -----------------------------
   get functions Tests
--------------------------------*/

void test_getFacilitiesData() {
	FacilityList list = { NULL, 0 };

	Facility f = { 1, "Test", "hotel", 100.0f, 4.0f, 1, 1 };
	addFacilityRecord(&list, &f);

	size_t count = 0;
	const Facility* data = getFacilitiesData(&list, &count);

	assert(data != NULL);
	assert(count == 1);

	free(list.items);
}

void test_getBudgetData() {
	BudgetHistory history = { NULL, 0 };

	addBudgetRecord(&history, "hotel", 100.0);

	size_t count = 0;
	const BudgetRecord* data = getBudgetData(&history, &count);

	assert(data != NULL);
	assert(count == 1);

	free(history.items);
}

/* -----------------------------
   freeDataMemory Test
--------------------------------*/

void test_freeDataMemory() {
	FacilityList list = { NULL, 0 };
	BudgetHistory history = { NULL, 0 };

	Facility f = { 1, "Test", "hotel", 100.0f, 4.0f, 1, 1 };
	addFacilityRecord(&list, &f);
	addBudgetRecord(&history, "hotel", 100.0);

	freeDataMemory(&list, &history);

	assert(list.items == NULL);
	assert(list.count == 0);
	assert(history.items == NULL);
	assert(history.count == 0);
}

/* -----------------------------
   MAIN
--------------------------------*/

int main() {
	test_addFacilityRecord();
	test_addFacilityRecord_invalid();

	test_addBudgetRecord();
	test_addBudgetRecord_invalid();

	test_filterResults();
	test_filterResults_noMatch();

	test_getFacilitiesData();
	test_getBudgetData();

	test_freeDataMemory();

	printf("All DataStorage tests passed!\n");
	return 0;
}