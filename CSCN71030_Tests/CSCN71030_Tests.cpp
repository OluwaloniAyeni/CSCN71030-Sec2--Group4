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

#include "../CSCN71030_Group4/user_input.h"
#include "../CSCN71030_Group4/input_validation.h"
#include "../CSCN71030_Group4/budget_handling.h"
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

namespace InputValidationTests
{
	TEST_CLASS(InputValidationTests)
	{
	public:

		TEST_METHOD(ValidInput_ReturnsTrue)
		{
			UserRequest req = { "gym", 20.0 };

			int result = validateInput(req);

			Assert::AreEqual(1, result);
		}

		TEST_METHOD(NegativeBudget_ReturnsFalse)
		{
			UserRequest req = { "gym", -5.0 };

			int result = validateInput(req);

			Assert::AreEqual(0, result);
		}

		TEST_METHOD(ZeroBudget_ReturnsTrue)
		{
			UserRequest req = { "hotel", 0.0 };

			int result = validateInput(req);

			Assert::AreEqual(1, result);
		}

		TEST_METHOD(EmptyCategory_ReturnsFalse)
		{
			UserRequest req = { "", 20.0 };

			int result = validateInput(req);

			Assert::AreEqual(0, result);
		}
	};
}

namespace BudgetHandlingTests
{
	TEST_CLASS(BudgetHandlingTests)
	{
	public:


		TEST_METHOD(ProcessBudget_ReturnsMatchingItems)
		{
			Facility items[3] = {
				{1, "Gym A", "gym", 15.0f, 4.5f, 1, 1},
				{2, "Gym B", "gym", 25.0f, 4.0f, 1, 0},
				{3, "Hotel A", "hotel", 50.0f, 4.2f, 1, 1}
			};
			UserRequest req;
			strcpy_s(req.category, 50, "gym");
			req.budget = 20.0;

			int filteredCount = 0;
			Facility* result = processBudget(items, 3, req, &filteredCount);

			Assert::IsNotNull(result);
			Assert::AreEqual(1, filteredCount);

		}

		TEST_METHOD(ProcessBudget_ReturnsNullWhenNoneMatch)
		{
			Facility items[3] = {
				{1, "Gym A", "gym", 50.0f, 4.5f, 1, 1},
				{2, "Gym B", "gym", 60.0f, 4.0f, 1, 0},
				{3, "Gym C", "gym", 70.0f, 4.2f, 1, 1}
			};
			UserRequest req;
			strcpy_s(req.category, 50, "gym");
			req.budget = 10.0;

			int filteredCount = 0;
			Facility* result = processBudget(items, 3, req, &filteredCount);

			Assert::IsNull(result);
			Assert::AreEqual(0, filteredCount);

		}

		TEST_METHOD(ProcessBudget_NullInput_ReturnsNull)
		{
			UserRequest req;
			strcpy_s(req.category, 50, "gym");
			req.budget = 20.0;

			int filteredCount = 0;
			Facility* result = processBudget(NULL, 0, req, &filteredCount);

			Assert::IsNull(result);

		}
	};
}
