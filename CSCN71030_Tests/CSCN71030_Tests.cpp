#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "../CSCN71030_Group4/item.h"	
#include "../CSCN71030_Group4/search_filtering.h"
#include "../CSCN71030_Group4/recommendation.h"
#include "../CSCN71030_Group4/output_display.h"
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
			Item items[3] = {
				{1, "Hotel A", "hotel", 100.0, 4.5},
				{2, "Hotel B", "hotel", 200.0, 4.0},
				{3, "Hotel C", "hotel", 300.0, 3.5}
			};
			int filteredCount = 0;
			Item* result = filterByBudget(items, 3, "hotel", 0.0f, 200.0f, &filteredCount);

			Assert::IsNotNull(result);
			Assert::AreEqual(2, filteredCount);

			freeResults(result);
		}

		// No Match
		TEST_METHOD(FilterByBudget_NoResults)
		{
			Item items[2] = {
				{1, "Gym A", "gym", 500.0f, 4.5f},
				{2, "Gym B", "gym", 600.0f, 4.0f}
			};

			int filteredCount = 0;
			Item* result = filterByBudget(items, 2, "gym", 0.0f, 100.0f, &filteredCount);

			Assert::IsNotNull(result);
			Assert::AreEqual(0, filteredCount);
		}

		//NULL INPUT
		TEST_METHOD(FilterByBudget_NullInput)
		{
			int filteredCount = 0;

			Item* result = filterByBudget(NULL, 0, "hotel", 0.0f, 200.0f, &filteredCount);

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
			Item filteredItems[3] = {
				{1, "Hotel A", "hotel", 100.0f, 4.5f},
				{2, "Hotel B", "hotel", 150.0f, 4.0f},
				{3, "Hotel C", "hotel", 200.0f, 3.5f}
			};
			int recommendationCount = 0;

			Item* results = generateRecommendations(filteredItems, 3, &recommendationCount);

		Assert::IsNotNull(results);
		Assert::AreEqual(3, recommendationCount);

		freeRecommendations(results);
		
		}

		// empty input

		TEST_METHOD(GenerateRecommenedations_EmptyInput_ReturnsNull)
		{
			Item* filteredItems = NULL;
			int recommendationCount = 0;

			Item* results = generateRecommendations(filteredItems, 0, &recommendationCount);

			Assert::IsNull(results);
			Assert::AreEqual(0, recommendationCount);
		}

		// single matching result input
		TEST_METHOD(GenerateRecommendations_SingleMatchingResult)
		{
			Item filteredItems[1] = {
				{1, "Hotel A", "hotel", 100.0f, 4.5f} };

			int recommendationCount = 0;

			Item* results = generateRecommendations(filteredItems, 1, &recommendationCount);

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