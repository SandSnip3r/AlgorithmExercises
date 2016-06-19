#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "bogosort.hpp"
#include "bubbleSort.hpp"
#include "heapsort.hpp"
#include "insertionSort.hpp"
#include "introsort.hpp"
#include "mergeSort.hpp"
#include "quicksort.hpp"

using namespace std;

#define INT_SORT_TEST(sort) \
TEST(sort##Test, VectorOfInts) { \
	vector<int> singleInput{ 1 }; \
	const vector<int> singleExpected{ 1 }; \
	sort::Sort(singleInput.begin(), singleInput.end()); \
	EXPECT_EQ(singleExpected, singleInput); \
 \
	vector<int> doubleInput{ 2, 1 }; \
	const vector<int> doubleExpected{ 1, 2 }; \
	sort::Sort(doubleInput.begin(), doubleInput.end()); \
	EXPECT_EQ(doubleExpected, doubleInput); \
 \
	vector<int> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 }; \
	const vector<int> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; \
	sort::Sort(tenInput.begin(), tenInput.end()); \
	EXPECT_EQ(tenExpected, tenInput); \
 \
	vector<int> allSameInput{ 1, 1, 1, 1, 1, 1, 1 }; \
	const vector<int> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 }; \
	sort::Sort(allSameInput.begin(), allSameInput.end()); \
	EXPECT_EQ(allSameExpected, allSameInput); \
 \
	vector<int> reversedInput{ 5, 4, 3, 2, 1 }; \
	const vector<int> reversedExpected{ 1, 2, 3, 4, 5 }; \
	sort::Sort(reversedInput.begin(), reversedInput.end()); \
	EXPECT_EQ(reversedExpected, reversedInput); \
} \

INT_SORT_TEST(Bogosort);
INT_SORT_TEST(BubbleSort);
INT_SORT_TEST(Heapsort);
INT_SORT_TEST(InsertionSort);
INT_SORT_TEST(Introsort);
INT_SORT_TEST(MergeSort);
INT_SORT_TEST(Quicksort);
#undef INT_SORT_TEST

#define DOUBLE_SORT_TEST(sort) \
TEST(sort##Test, VectorOfDoubles) { \
	vector<double> singleInput{ 1 }; \
	const vector<double> singleExpected{ 1 }; \
	sort::Sort(singleInput.begin(), singleInput.end()); \
	EXPECT_EQ(singleExpected, singleInput); \
 \
	vector<double> doubleInput{ 2, 1 }; \
	const vector<double> doubleExpected{ 1, 2 }; \
	sort::Sort(doubleInput.begin(), doubleInput.end()); \
	EXPECT_EQ(doubleExpected, doubleInput); \
 \
	vector<double> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 }; \
	const vector<double> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; \
	sort::Sort(tenInput.begin(), tenInput.end()); \
	EXPECT_EQ(tenExpected, tenInput); \
 \
	vector<double> allSameInput{ 1, 1, 1, 1, 1, 1, 1 }; \
	const vector<double> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 }; \
	sort::Sort(allSameInput.begin(), allSameInput.end()); \
	EXPECT_EQ(allSameExpected, allSameInput); \
 \
	vector<double> reversedInput{ 5, 4, 3, 2, 1 }; \
	const vector<double> reversedExpected{ 1, 2, 3, 4, 5 }; \
	sort::Sort(reversedInput.begin(), reversedInput.end()); \
	EXPECT_EQ(reversedExpected, reversedInput); \
} \

DOUBLE_SORT_TEST(Bogosort);
DOUBLE_SORT_TEST(BubbleSort);
DOUBLE_SORT_TEST(Heapsort);
DOUBLE_SORT_TEST(InsertionSort);
DOUBLE_SORT_TEST(Introsort);
DOUBLE_SORT_TEST(MergeSort);
DOUBLE_SORT_TEST(Quicksort);
#undef DOUBLE_SORT_TEST

#define STRING_SORT_TEST(sort) \
TEST(sort##Test, VectorOfStrings) { \
	auto StringComp = [](const string &s1, const string &s2) -> bool { \
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()); \
	}; \
	vector<string> singleInput{ "hey" }; \
	const vector<string> singleExpected{ "hey" }; \
	sort::Sort(singleInput.begin(), singleInput.end(), StringComp); \
	EXPECT_EQ(singleExpected, singleInput); \
 \
	vector<string> doubleInput{ "z", "a" }; \
	const vector<string> doubleExpected{ "a", "z" }; \
	sort::Sort(doubleInput.begin(), doubleInput.end(), StringComp); \
	EXPECT_EQ(doubleExpected, doubleInput); \
 \
	vector<string> tenInput{ "z", "g", "s", "y", "e", "j", "a", "k", "p", "o" }; \
	const vector<string> tenExpected{ "a", "e", "g", "j", "k", "o", "p", "s", "y", "z" }; \
	sort::Sort(tenInput.begin(), tenInput.end(), StringComp); \
	EXPECT_EQ(tenExpected, tenInput); \
 \
	vector<string> allSameInput{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" }; \
	const vector<string> allSameExpected{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" }; \
	sort::Sort(allSameInput.begin(), allSameInput.end(), StringComp); \
	EXPECT_EQ(allSameExpected, allSameInput); \
 \
	vector<string> reversedInput{ "z", "h", "e", "d", "b" }; \
	const vector<string> reversedExpected{ "b", "d", "e", "h", "z" }; \
	sort::Sort(reversedInput.begin(), reversedInput.end(), StringComp); \
	EXPECT_EQ(reversedExpected, reversedInput); \
} \

// STRING_SORT_TEST(Bogosort);
STRING_SORT_TEST(BubbleSort);
STRING_SORT_TEST(Heapsort);
// STRING_SORT_TEST(InsertionSort);
// STRING_SORT_TEST(Introsort);
STRING_SORT_TEST(MergeSort);
STRING_SORT_TEST(Quicksort);
#undef STRING_SORT_TEST

int main(int argc, char **argv) {
	::testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS();
}