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