#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "../CSCN71030_Group4/item.h"	
#include "../CSCN71030_Group4/search_filtering.h"
#include "../CSCN71030_Group4/recommendation.h"
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

			Item* results = generateRecommendations(filteredItems, 3, 
				"hotel", 0.0f, 200.0f, &recommendationCount);

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

	};
}