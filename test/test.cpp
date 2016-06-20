#include <algorithm>
#include <array>
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

class Distance {
	int feet;
	double inches;
public:
	Distance(int x, double y) : feet(x), inches(y) {};
	friend bool operator<(const Distance &a, const Distance &b);
	friend bool operator==(const Distance &a, const Distance &b);
};

bool operator<(const Distance &a, const Distance &b) {
	if (a.feet == b.feet) {
		return a.inches < b.inches;
	} else {
		return a.feet < b.feet;
	}
}

bool operator==(const Distance &a, const Distance &b) {
	return (a.feet == b.feet && a.inches == b.inches);
}

TEST(BogosortTest, RandomShuffleType) {
	vector<int> randomInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8, 11 };
	const vector<int> randomExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	Bogosort::Sort(randomInput.begin(), randomInput.end(), Bogosort::ShuffleType::Random);
	EXPECT_EQ(randomExpected, randomInput);
}

TEST(BogosortTest, PermuteShuffleType) {
	vector<int> permuteInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8, 11 };
	const vector<int> permuteExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	Bogosort::Sort(permuteInput.begin(), permuteInput.end(), Bogosort::ShuffleType::Permute);
	EXPECT_EQ(permuteExpected, permuteInput);
}

TEST(BogosortTest, VectorOfInts) {
	vector<int> singleInput{ 1 };
	const vector<int> singleExpected{ 1 };
	Bogosort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<int> doubleInput{ 2, 1 };
	const vector<int> doubleExpected{ 1, 2 };
	Bogosort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<int> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<int> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Bogosort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<int> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<int> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Bogosort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<int> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<int> reversedExpected{ 1, 2, 3, 4, 5 };
	Bogosort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(BogosortTest, VectorOfDoubles) {
	vector<double> singleInput{ 1 };
	const vector<double> singleExpected{ 1 };
	Bogosort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<double> doubleInput{ 2, 1 };
	const vector<double> doubleExpected{ 1, 2 };
	Bogosort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<double> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<double> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Bogosort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<double> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<double> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Bogosort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<double> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<double> reversedExpected{ 1, 2, 3, 4, 5 };
	Bogosort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(BogosortTest, VectorOfStrings) {
	auto StringComp = [](const string &s1, const string &s2) -> bool {
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	};
	vector<string> singleInput{ "hey" };
	const vector<string> singleExpected{ "hey" };
	Bogosort::Sort(singleInput.begin(), singleInput.end(), Bogosort::ShuffleType::Random, StringComp);
	EXPECT_EQ(singleExpected, singleInput);

	vector<string> doubleInput{ "z", "a" };
	const vector<string> doubleExpected{ "a", "z" };
	Bogosort::Sort(doubleInput.begin(), doubleInput.end(), Bogosort::ShuffleType::Random, StringComp);
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<string> tenInput{ "z", "g", "s", "y", "e", "j", "a", "k", "p", "o" };
	const vector<string> tenExpected{ "a", "e", "g", "j", "k", "o", "p", "s", "y", "z" };
	Bogosort::Sort(tenInput.begin(), tenInput.end(), Bogosort::ShuffleType::Random, StringComp);
	EXPECT_EQ(tenExpected, tenInput);

	vector<string> allSameInput{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	const vector<string> allSameExpected{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	Bogosort::Sort(allSameInput.begin(), allSameInput.end(), Bogosort::ShuffleType::Random, StringComp);
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<string> reversedInput{ "z", "h", "e", "d", "b" };
	const vector<string> reversedExpected{ "b", "d", "e", "h", "z" };
	Bogosort::Sort(reversedInput.begin(), reversedInput.end(), Bogosort::ShuffleType::Random, StringComp);
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(BogosortTest, ArrayOfInts) {
	array<int,1> singleInput{ 1 };
	const array<int,1> singleExpected{ 1 };
	Bogosort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	array<int,2> doubleInput{ 2, 1 };
	const array<int,2> doubleExpected{ 1, 2 };
	Bogosort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	array<int,10> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const array<int,10> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Bogosort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	array<int,7> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const array<int,7> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Bogosort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	array<int,5> reversedInput{ 5, 4, 3, 2, 1 };
	const array<int,5> reversedExpected{ 1, 2, 3, 4, 5 };
	Bogosort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(BogosortTest, VectorOfDistances) {
	vector<Distance> distanceInput{ {2, 2.3}, {3, 2.3}, {2, 2.2} };
	const vector<Distance> distanceExpected{ {2, 2.2}, {2, 2.3}, {3, 2.3} };
	Bogosort::Sort(distanceInput.begin(), distanceInput.end());
	EXPECT_EQ(distanceExpected, distanceInput);
}

//===================================================================================
//====================================Bubble sort====================================
//===================================================================================

TEST(BubbleSortTest, VectorOfInts) {
	vector<int> singleInput{ 1 };
	const vector<int> singleExpected{ 1 };
	BubbleSort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<int> doubleInput{ 2, 1 };
	const vector<int> doubleExpected{ 1, 2 };
	BubbleSort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<int> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<int> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	BubbleSort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<int> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<int> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	BubbleSort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<int> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<int> reversedExpected{ 1, 2, 3, 4, 5 };
	BubbleSort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(BubbleSortTest, VectorOfDoubles) {
	vector<double> singleInput{ 1 };
	const vector<double> singleExpected{ 1 };
	BubbleSort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<double> doubleInput{ 2, 1 };
	const vector<double> doubleExpected{ 1, 2 };
	BubbleSort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<double> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<double> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	BubbleSort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<double> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<double> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	BubbleSort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<double> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<double> reversedExpected{ 1, 2, 3, 4, 5 };
	BubbleSort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(BubbleSortTest, VectorOfStrings) {
	auto StringComp = [](const string &s1, const string &s2) -> bool {
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	};
	vector<string> singleInput{ "hey" };
	const vector<string> singleExpected{ "hey" };
	BubbleSort::Sort(singleInput.begin(), singleInput.end(), StringComp);
	EXPECT_EQ(singleExpected, singleInput);

	vector<string> doubleInput{ "z", "a" };
	const vector<string> doubleExpected{ "a", "z" };
	BubbleSort::Sort(doubleInput.begin(), doubleInput.end(), StringComp);
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<string> tenInput{ "z", "g", "s", "y", "e", "j", "a", "k", "p", "o" };
	const vector<string> tenExpected{ "a", "e", "g", "j", "k", "o", "p", "s", "y", "z" };
	BubbleSort::Sort(tenInput.begin(), tenInput.end(), StringComp);
	EXPECT_EQ(tenExpected, tenInput);

	vector<string> allSameInput{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	const vector<string> allSameExpected{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	BubbleSort::Sort(allSameInput.begin(), allSameInput.end(), StringComp);
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<string> reversedInput{ "z", "h", "e", "d", "b" };
	const vector<string> reversedExpected{ "b", "d", "e", "h", "z" };
	BubbleSort::Sort(reversedInput.begin(), reversedInput.end(), StringComp);
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(BubbleSortTest, ArrayOfInts) {
	array<int,1> singleInput{ 1 };
	const array<int,1> singleExpected{ 1 };
	BubbleSort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	array<int,2> doubleInput{ 2, 1 };
	const array<int,2> doubleExpected{ 1, 2 };
	BubbleSort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	array<int,10> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const array<int,10> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	BubbleSort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	array<int,7> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const array<int,7> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	BubbleSort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	array<int,5> reversedInput{ 5, 4, 3, 2, 1 };
	const array<int,5> reversedExpected{ 1, 2, 3, 4, 5 };
	BubbleSort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(BubbleSortTest, VectorOfDistances) {
	vector<Distance> distanceInput{ {2, 2.3}, {3, 2.3}, {2, 2.2} };
	const vector<Distance> distanceExpected{ {2, 2.2}, {2, 2.3}, {3, 2.3} };
	BubbleSort::Sort(distanceInput.begin(), distanceInput.end());
	EXPECT_EQ(distanceExpected, distanceInput);
}

//===================================================================================
//=====================================Heapsort======================================
//===================================================================================

TEST(HeapsortTest, VectorOfInts) {
	vector<int> singleInput{ 1 };
	const vector<int> singleExpected{ 1 };
	Heapsort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<int> doubleInput{ 2, 1 };
	const vector<int> doubleExpected{ 1, 2 };
	Heapsort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<int> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<int> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Heapsort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<int> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<int> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Heapsort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<int> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<int> reversedExpected{ 1, 2, 3, 4, 5 };
	Heapsort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(HeapsortTest, VectorOfDoubles) {
	vector<double> singleInput{ 1 };
	const vector<double> singleExpected{ 1 };
	Heapsort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<double> doubleInput{ 2, 1 };
	const vector<double> doubleExpected{ 1, 2 };
	Heapsort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<double> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<double> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Heapsort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<double> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<double> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Heapsort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<double> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<double> reversedExpected{ 1, 2, 3, 4, 5 };
	Heapsort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(HeapsortTest, VectorOfStrings) {
	auto StringComp = [](const string &s1, const string &s2) -> bool {
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	};
	vector<string> singleInput{ "hey" };
	const vector<string> singleExpected{ "hey" };
	Heapsort::Sort(singleInput.begin(), singleInput.end(), StringComp);
	EXPECT_EQ(singleExpected, singleInput);

	vector<string> doubleInput{ "z", "a" };
	const vector<string> doubleExpected{ "a", "z" };
	Heapsort::Sort(doubleInput.begin(), doubleInput.end(), StringComp);
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<string> tenInput{ "z", "g", "s", "y", "e", "j", "a", "k", "p", "o" };
	const vector<string> tenExpected{ "a", "e", "g", "j", "k", "o", "p", "s", "y", "z" };
	Heapsort::Sort(tenInput.begin(), tenInput.end(), StringComp);
	EXPECT_EQ(tenExpected, tenInput);

	vector<string> allSameInput{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	const vector<string> allSameExpected{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	Heapsort::Sort(allSameInput.begin(), allSameInput.end(), StringComp);
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<string> reversedInput{ "z", "h", "e", "d", "b" };
	const vector<string> reversedExpected{ "b", "d", "e", "h", "z" };
	Heapsort::Sort(reversedInput.begin(), reversedInput.end(), StringComp);
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(HeapsortTest, ArrayOfInts) {
	array<int,1> singleInput{ 1 };
	const array<int,1> singleExpected{ 1 };
	Heapsort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	array<int,2> doubleInput{ 2, 1 };
	const array<int,2> doubleExpected{ 1, 2 };
	Heapsort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	array<int,10> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const array<int,10> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Heapsort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	array<int,7> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const array<int,7> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Heapsort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	array<int,5> reversedInput{ 5, 4, 3, 2, 1 };
	const array<int,5> reversedExpected{ 1, 2, 3, 4, 5 };
	Heapsort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(HeapsortTest, VectorOfDistances) {
	vector<Distance> distanceInput{ {2, 2.3}, {3, 2.3}, {2, 2.2} };
	const vector<Distance> distanceExpected{ {2, 2.2}, {2, 2.3}, {3, 2.3} };
	Heapsort::Sort(distanceInput.begin(), distanceInput.end());
	EXPECT_EQ(distanceExpected, distanceInput);
}

//===================================================================================
//==================================Insertion sort===================================
//===================================================================================

TEST(InsertionSortTest, VectorOfInts) {
	vector<int> singleInput{ 1 };
	const vector<int> singleExpected{ 1 };
	InsertionSort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<int> doubleInput{ 2, 1 };
	const vector<int> doubleExpected{ 1, 2 };
	InsertionSort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<int> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<int> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	InsertionSort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<int> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<int> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	InsertionSort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<int> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<int> reversedExpected{ 1, 2, 3, 4, 5 };
	InsertionSort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(InsertionSortTest, VectorOfDoubles) {
	vector<double> singleInput{ 1 };
	const vector<double> singleExpected{ 1 };
	InsertionSort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<double> doubleInput{ 2, 1 };
	const vector<double> doubleExpected{ 1, 2 };
	InsertionSort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<double> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<double> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	InsertionSort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<double> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<double> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	InsertionSort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<double> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<double> reversedExpected{ 1, 2, 3, 4, 5 };
	InsertionSort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(InsertionSortTest, VectorOfStrings) {
	auto StringComp = [](const string &s1, const string &s2) -> bool {
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	};
	vector<string> singleInput{ "hey" };
	const vector<string> singleExpected{ "hey" };
	InsertionSort::Sort(singleInput.begin(), singleInput.end(), StringComp);
	EXPECT_EQ(singleExpected, singleInput);

	vector<string> doubleInput{ "z", "a" };
	const vector<string> doubleExpected{ "a", "z" };
	InsertionSort::Sort(doubleInput.begin(), doubleInput.end(), StringComp);
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<string> tenInput{ "z", "g", "s", "y", "e", "j", "a", "k", "p", "o" };
	const vector<string> tenExpected{ "a", "e", "g", "j", "k", "o", "p", "s", "y", "z" };
	InsertionSort::Sort(tenInput.begin(), tenInput.end(), StringComp);
	EXPECT_EQ(tenExpected, tenInput);

	vector<string> allSameInput{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	const vector<string> allSameExpected{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	InsertionSort::Sort(allSameInput.begin(), allSameInput.end(), StringComp);
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<string> reversedInput{ "z", "h", "e", "d", "b" };
	const vector<string> reversedExpected{ "b", "d", "e", "h", "z" };
	InsertionSort::Sort(reversedInput.begin(), reversedInput.end(), StringComp);
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(InsertionSortTest, ArrayOfInts) {
	array<int,1> singleInput{ 1 };
	const array<int,1> singleExpected{ 1 };
	InsertionSort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	array<int,2> doubleInput{ 2, 1 };
	const array<int,2> doubleExpected{ 1, 2 };
	InsertionSort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	array<int,10> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const array<int,10> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	InsertionSort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	array<int,7> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const array<int,7> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	InsertionSort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	array<int,5> reversedInput{ 5, 4, 3, 2, 1 };
	const array<int,5> reversedExpected{ 1, 2, 3, 4, 5 };
	InsertionSort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(InsertionSortTest, VectorOfDistances) {
	vector<Distance> distanceInput{ {2, 2.3}, {3, 2.3}, {2, 2.2} };
	const vector<Distance> distanceExpected{ {2, 2.2}, {2, 2.3}, {3, 2.3} };
	InsertionSort::Sort(distanceInput.begin(), distanceInput.end());
	EXPECT_EQ(distanceExpected, distanceInput);
}

//===================================================================================
//=====================================Introsort=====================================
//===================================================================================

TEST(IntrosortTest, VectorOfInts) {
	vector<int> singleInput{ 1 };
	const vector<int> singleExpected{ 1 };
	Introsort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<int> doubleInput{ 2, 1 };
	const vector<int> doubleExpected{ 1, 2 };
	Introsort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<int> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<int> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Introsort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<int> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<int> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Introsort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<int> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<int> reversedExpected{ 1, 2, 3, 4, 5 };
	Introsort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(IntrosortTest, VectorOfDoubles) {
	vector<double> singleInput{ 1 };
	const vector<double> singleExpected{ 1 };
	Introsort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<double> doubleInput{ 2, 1 };
	const vector<double> doubleExpected{ 1, 2 };
	Introsort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<double> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<double> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Introsort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<double> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<double> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Introsort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<double> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<double> reversedExpected{ 1, 2, 3, 4, 5 };
	Introsort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(IntrosortTest, VectorOfStrings) {
	auto StringComp = [](const string &s1, const string &s2) -> bool {
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	};
	vector<string> singleInput{ "hey" };
	const vector<string> singleExpected{ "hey" };
	Introsort::Sort(singleInput.begin(), singleInput.end(), StringComp);
	EXPECT_EQ(singleExpected, singleInput);

	vector<string> doubleInput{ "z", "a" };
	const vector<string> doubleExpected{ "a", "z" };
	Introsort::Sort(doubleInput.begin(), doubleInput.end(), StringComp);
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<string> tenInput{ "z", "g", "s", "y", "e", "j", "a", "k", "p", "o" };
	const vector<string> tenExpected{ "a", "e", "g", "j", "k", "o", "p", "s", "y", "z" };
	Introsort::Sort(tenInput.begin(), tenInput.end(), StringComp);
	EXPECT_EQ(tenExpected, tenInput);

	vector<string> allSameInput{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	const vector<string> allSameExpected{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	Introsort::Sort(allSameInput.begin(), allSameInput.end(), StringComp);
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<string> reversedInput{ "z", "h", "e", "d", "b" };
	const vector<string> reversedExpected{ "b", "d", "e", "h", "z" };
	Introsort::Sort(reversedInput.begin(), reversedInput.end(), StringComp);
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(IntrosortTest, ArrayOfInts) {
	array<int,1> singleInput{ 1 };
	const array<int,1> singleExpected{ 1 };
	Introsort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	array<int,2> doubleInput{ 2, 1 };
	const array<int,2> doubleExpected{ 1, 2 };
	Introsort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	array<int,10> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const array<int,10> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Introsort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	array<int,7> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const array<int,7> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Introsort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	array<int,5> reversedInput{ 5, 4, 3, 2, 1 };
	const array<int,5> reversedExpected{ 1, 2, 3, 4, 5 };
	Introsort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(IntrosortTest, VectorOfDistances) {
	vector<Distance> distanceInput{ {2, 2.3}, {3, 2.3}, {2, 2.2} };
	const vector<Distance> distanceExpected{ {2, 2.2}, {2, 2.3}, {3, 2.3} };
	Introsort::Sort(distanceInput.begin(), distanceInput.end());
	EXPECT_EQ(distanceExpected, distanceInput);
}

//===================================================================================
//=====================================Merge sort====================================
//===================================================================================

TEST(MergeSortTest, VectorOfInts) {
	vector<int> singleInput{ 1 };
	const vector<int> singleExpected{ 1 };
	MergeSort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<int> doubleInput{ 2, 1 };
	const vector<int> doubleExpected{ 1, 2 };
	MergeSort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<int> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<int> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	MergeSort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<int> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<int> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	MergeSort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<int> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<int> reversedExpected{ 1, 2, 3, 4, 5 };
	MergeSort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(MergeSortTest, VectorOfDoubles) {
	vector<double> singleInput{ 1 };
	const vector<double> singleExpected{ 1 };
	MergeSort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<double> doubleInput{ 2, 1 };
	const vector<double> doubleExpected{ 1, 2 };
	MergeSort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<double> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<double> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	MergeSort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<double> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<double> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	MergeSort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<double> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<double> reversedExpected{ 1, 2, 3, 4, 5 };
	MergeSort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(MergeSortTest, VectorOfStrings) {
	auto StringComp = [](const string &s1, const string &s2) -> bool {
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	};
	vector<string> singleInput{ "hey" };
	const vector<string> singleExpected{ "hey" };
	MergeSort::Sort(singleInput.begin(), singleInput.end(), StringComp);
	EXPECT_EQ(singleExpected, singleInput);

	vector<string> doubleInput{ "z", "a" };
	const vector<string> doubleExpected{ "a", "z" };
	MergeSort::Sort(doubleInput.begin(), doubleInput.end(), StringComp);
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<string> tenInput{ "z", "g", "s", "y", "e", "j", "a", "k", "p", "o" };
	const vector<string> tenExpected{ "a", "e", "g", "j", "k", "o", "p", "s", "y", "z" };
	MergeSort::Sort(tenInput.begin(), tenInput.end(), StringComp);
	EXPECT_EQ(tenExpected, tenInput);

	vector<string> allSameInput{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	const vector<string> allSameExpected{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	MergeSort::Sort(allSameInput.begin(), allSameInput.end(), StringComp);
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<string> reversedInput{ "z", "h", "e", "d", "b" };
	const vector<string> reversedExpected{ "b", "d", "e", "h", "z" };
	MergeSort::Sort(reversedInput.begin(), reversedInput.end(), StringComp);
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(MergeSortTest, ArrayOfInts) {
	array<int,1> singleInput{ 1 };
	const array<int,1> singleExpected{ 1 };
	MergeSort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	array<int,2> doubleInput{ 2, 1 };
	const array<int,2> doubleExpected{ 1, 2 };
	MergeSort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	array<int,10> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const array<int,10> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	MergeSort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	array<int,7> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const array<int,7> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	MergeSort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	array<int,5> reversedInput{ 5, 4, 3, 2, 1 };
	const array<int,5> reversedExpected{ 1, 2, 3, 4, 5 };
	MergeSort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(MergeSortTest, VectorOfDistances) {
	vector<Distance> distanceInput{ {2, 2.3}, {3, 2.3}, {2, 2.2} };
	const vector<Distance> distanceExpected{ {2, 2.2}, {2, 2.3}, {3, 2.3} };
	MergeSort::Sort(distanceInput.begin(), distanceInput.end());
	EXPECT_EQ(distanceExpected, distanceInput);
}

//===================================================================================
//=====================================Quick sort====================================
//===================================================================================

TEST(QuicksortTest, VectorOfInts) {
	vector<int> singleInput{ 1 };
	const vector<int> singleExpected{ 1 };
	Quicksort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<int> doubleInput{ 2, 1 };
	const vector<int> doubleExpected{ 1, 2 };
	Quicksort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<int> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<int> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Quicksort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<int> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<int> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Quicksort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<int> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<int> reversedExpected{ 1, 2, 3, 4, 5 };
	Quicksort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(QuicksortTest, VectorOfDoubles) {
	vector<double> singleInput{ 1 };
	const vector<double> singleExpected{ 1 };
	Quicksort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	vector<double> doubleInput{ 2, 1 };
	const vector<double> doubleExpected{ 1, 2 };
	Quicksort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<double> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const vector<double> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Quicksort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	vector<double> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const vector<double> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Quicksort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<double> reversedInput{ 5, 4, 3, 2, 1 };
	const vector<double> reversedExpected{ 1, 2, 3, 4, 5 };
	Quicksort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(QuicksortTest, VectorOfStrings) {
	auto StringComp = [](const string &s1, const string &s2) -> bool {
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	};
	vector<string> singleInput{ "hey" };
	const vector<string> singleExpected{ "hey" };
	Quicksort::Sort(singleInput.begin(), singleInput.end(), StringComp);
	EXPECT_EQ(singleExpected, singleInput);

	vector<string> doubleInput{ "z", "a" };
	const vector<string> doubleExpected{ "a", "z" };
	Quicksort::Sort(doubleInput.begin(), doubleInput.end(), StringComp);
	EXPECT_EQ(doubleExpected, doubleInput);

	vector<string> tenInput{ "z", "g", "s", "y", "e", "j", "a", "k", "p", "o" };
	const vector<string> tenExpected{ "a", "e", "g", "j", "k", "o", "p", "s", "y", "z" };
	Quicksort::Sort(tenInput.begin(), tenInput.end(), StringComp);
	EXPECT_EQ(tenExpected, tenInput);

	vector<string> allSameInput{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	const vector<string> allSameExpected{ "abc", "abc", "abc", "abc", "abc", "abc", "abc" };
	Quicksort::Sort(allSameInput.begin(), allSameInput.end(), StringComp);
	EXPECT_EQ(allSameExpected, allSameInput);

	vector<string> reversedInput{ "z", "h", "e", "d", "b" };
	const vector<string> reversedExpected{ "b", "d", "e", "h", "z" };
	Quicksort::Sort(reversedInput.begin(), reversedInput.end(), StringComp);
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(QuicksortTest, ArrayOfInts) {
	array<int,1> singleInput{ 1 };
	const array<int,1> singleExpected{ 1 };
	Quicksort::Sort(singleInput.begin(), singleInput.end());
	EXPECT_EQ(singleExpected, singleInput);

	array<int,2> doubleInput{ 2, 1 };
	const array<int,2> doubleExpected{ 1, 2 };
	Quicksort::Sort(doubleInput.begin(), doubleInput.end());
	EXPECT_EQ(doubleExpected, doubleInput);

	array<int,10> tenInput{ 10, 3, 9, 6, 7, 1, 2, 4, 5, 8 };
	const array<int,10> tenExpected{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Quicksort::Sort(tenInput.begin(), tenInput.end());
	EXPECT_EQ(tenExpected, tenInput);

	array<int,7> allSameInput{ 1, 1, 1, 1, 1, 1, 1 };
	const array<int,7> allSameExpected{ 1, 1, 1, 1, 1, 1, 1 };
	Quicksort::Sort(allSameInput.begin(), allSameInput.end());
	EXPECT_EQ(allSameExpected, allSameInput);

	array<int,5> reversedInput{ 5, 4, 3, 2, 1 };
	const array<int,5> reversedExpected{ 1, 2, 3, 4, 5 };
	Quicksort::Sort(reversedInput.begin(), reversedInput.end());
	EXPECT_EQ(reversedExpected, reversedInput);
}

TEST(QuicksortTest, VectorOfDistances) {
	vector<Distance> distanceInput{ {2, 2.3}, {3, 2.3}, {2, 2.2} };
	const vector<Distance> distanceExpected{ {2, 2.2}, {2, 2.3}, {3, 2.3} };
	Quicksort::Sort(distanceInput.begin(), distanceInput.end());
	EXPECT_EQ(distanceExpected, distanceInput);
}