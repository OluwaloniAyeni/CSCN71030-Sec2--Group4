#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "../CSCN71030_Group4/item.h"	
#include "../CSCN71030_Group4/search_filtering.h"
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

		
	};
}
