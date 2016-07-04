#include <algorithm>
#include <array>
#include <deque>
#include <random>
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
#include "selectionSort.hpp"
#include "timsort.hpp"

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

template<typename NumType>
class ArrayOfNumbersTest : public ::testing::Test {
protected:
	array<NumType,0> input0, expected0;
	array<NumType,1> input1, expected1;
	array<NumType,2> input2, expected2;
	array<NumType,3> input3, expected3;
	array<NumType,7> input4, expected4;
	array<NumType,7> input5, expected5;
	array<NumType,11> input6, expected6;
	virtual void SetUp() {
		input0 = {};
		input1 = {1};
		input2 = {2, 1};
		input3 = {1, 1, 1};
		input4 = {1, 2, 3, 4, 5, 6, 7};
		input5 = {7, 6, 5, 4, 3, 2, 1};
		input6 = {10, 3, 9, 6, 7, 1, 2, 4, 5, 8, 11};
		expected0 = {};
		expected1 = {1};
		expected2 = {1, 2};
		expected3 = {1, 1, 1};
		expected4 = {1, 2, 3, 4, 5, 6, 7};
		expected5 = {1, 2, 3, 4, 5, 6, 7};
		expected6 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	}
};

typedef ::testing::Types<char, int, unsigned int, float, double> NumberTypes;
TYPED_TEST_CASE(ArrayOfNumbersTest, NumberTypes);

TYPED_TEST(ArrayOfNumbersTest, bogosortRandom) {
	Bogosort::Sort(this->input0.begin(), this->input0.end(), Bogosort::ShuffleType::Random);
	EXPECT_EQ(this->input0, this->expected0);
	Bogosort::Sort(this->input1.begin(), this->input1.end(), Bogosort::ShuffleType::Random);
	EXPECT_EQ(this->input1, this->expected1);
	Bogosort::Sort(this->input2.begin(), this->input2.end(), Bogosort::ShuffleType::Random);
	EXPECT_EQ(this->input2, this->expected2);
	Bogosort::Sort(this->input3.begin(), this->input3.end(), Bogosort::ShuffleType::Random);
	EXPECT_EQ(this->input3, this->expected3);
	Bogosort::Sort(this->input4.begin(), this->input4.end(), Bogosort::ShuffleType::Random);
	EXPECT_EQ(this->input4, this->expected4);
	Bogosort::Sort(this->input5.begin(), this->input5.end(), Bogosort::ShuffleType::Random);
	EXPECT_EQ(this->input5, this->expected5);
	Bogosort::Sort(this->input6.begin(), this->input6.end(), Bogosort::ShuffleType::Random);
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, bogosortPermute) {
	Bogosort::Sort(this->input0.begin(), this->input0.end(), Bogosort::ShuffleType::Permute);
	EXPECT_EQ(this->input0, this->expected0);
	Bogosort::Sort(this->input1.begin(), this->input1.end(), Bogosort::ShuffleType::Permute);
	EXPECT_EQ(this->input1, this->expected1);
	Bogosort::Sort(this->input2.begin(), this->input2.end(), Bogosort::ShuffleType::Permute);
	EXPECT_EQ(this->input2, this->expected2);
	Bogosort::Sort(this->input3.begin(), this->input3.end(), Bogosort::ShuffleType::Permute);
	EXPECT_EQ(this->input3, this->expected3);
	Bogosort::Sort(this->input4.begin(), this->input4.end(), Bogosort::ShuffleType::Permute);
	EXPECT_EQ(this->input4, this->expected4);
	Bogosort::Sort(this->input5.begin(), this->input5.end(), Bogosort::ShuffleType::Permute);
	EXPECT_EQ(this->input5, this->expected5);
	Bogosort::Sort(this->input6.begin(), this->input6.end(), Bogosort::ShuffleType::Permute);
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, bubbleSort) {
	BubbleSort::Sort(this->input0.begin(), this->input0.end());
	EXPECT_EQ(this->input0, this->expected0);
	BubbleSort::Sort(this->input1.begin(), this->input1.end());
	EXPECT_EQ(this->input1, this->expected1);
	BubbleSort::Sort(this->input2.begin(), this->input2.end());
	EXPECT_EQ(this->input2, this->expected2);
	BubbleSort::Sort(this->input3.begin(), this->input3.end());
	EXPECT_EQ(this->input3, this->expected3);
	BubbleSort::Sort(this->input4.begin(), this->input4.end());
	EXPECT_EQ(this->input4, this->expected4);
	BubbleSort::Sort(this->input5.begin(), this->input5.end());
	EXPECT_EQ(this->input5, this->expected5);
	BubbleSort::Sort(this->input6.begin(), this->input6.end());
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, heapsort) {
	Heapsort::Sort(this->input0.begin(), this->input0.end());
	EXPECT_EQ(this->input0, this->expected0);
	Heapsort::Sort(this->input1.begin(), this->input1.end());
	EXPECT_EQ(this->input1, this->expected1);
	Heapsort::Sort(this->input2.begin(), this->input2.end());
	EXPECT_EQ(this->input2, this->expected2);
	Heapsort::Sort(this->input3.begin(), this->input3.end());
	EXPECT_EQ(this->input3, this->expected3);
	Heapsort::Sort(this->input4.begin(), this->input4.end());
	EXPECT_EQ(this->input4, this->expected4);
	Heapsort::Sort(this->input5.begin(), this->input5.end());
	EXPECT_EQ(this->input5, this->expected5);
	Heapsort::Sort(this->input6.begin(), this->input6.end());
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, insertionSort) {
	InsertionSort::Sort(this->input0.begin(), this->input0.end());
	EXPECT_EQ(this->input0, this->expected0);
	InsertionSort::Sort(this->input1.begin(), this->input1.end());
	EXPECT_EQ(this->input1, this->expected1);
	InsertionSort::Sort(this->input2.begin(), this->input2.end());
	EXPECT_EQ(this->input2, this->expected2);
	InsertionSort::Sort(this->input3.begin(), this->input3.end());
	EXPECT_EQ(this->input3, this->expected3);
	InsertionSort::Sort(this->input4.begin(), this->input4.end());
	EXPECT_EQ(this->input4, this->expected4);
	InsertionSort::Sort(this->input5.begin(), this->input5.end());
	EXPECT_EQ(this->input5, this->expected5);
	InsertionSort::Sort(this->input6.begin(), this->input6.end());
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, introsort) {
	Introsort::Sort(this->input0.begin(), this->input0.end());
	EXPECT_EQ(this->input0, this->expected0);
	Introsort::Sort(this->input1.begin(), this->input1.end());
	EXPECT_EQ(this->input1, this->expected1);
	Introsort::Sort(this->input2.begin(), this->input2.end());
	EXPECT_EQ(this->input2, this->expected2);
	Introsort::Sort(this->input3.begin(), this->input3.end());
	EXPECT_EQ(this->input3, this->expected3);
	Introsort::Sort(this->input4.begin(), this->input4.end());
	EXPECT_EQ(this->input4, this->expected4);
	Introsort::Sort(this->input5.begin(), this->input5.end());
	EXPECT_EQ(this->input5, this->expected5);
	Introsort::Sort(this->input6.begin(), this->input6.end());
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, extraSpaceMergeSort) {
	MergeSort::Sort(this->input0.begin(), this->input0.end(), MergeSort::MergeType::ExtraSpace);
	EXPECT_EQ(this->input0, this->expected0);
	MergeSort::Sort(this->input1.begin(), this->input1.end(), MergeSort::MergeType::ExtraSpace);
	EXPECT_EQ(this->input1, this->expected1);
	MergeSort::Sort(this->input2.begin(), this->input2.end(), MergeSort::MergeType::ExtraSpace);
	EXPECT_EQ(this->input2, this->expected2);
	MergeSort::Sort(this->input3.begin(), this->input3.end(), MergeSort::MergeType::ExtraSpace);
	EXPECT_EQ(this->input3, this->expected3);
	MergeSort::Sort(this->input4.begin(), this->input4.end(), MergeSort::MergeType::ExtraSpace);
	EXPECT_EQ(this->input4, this->expected4);
	MergeSort::Sort(this->input5.begin(), this->input5.end(), MergeSort::MergeType::ExtraSpace);
	EXPECT_EQ(this->input5, this->expected5);
	MergeSort::Sort(this->input6.begin(), this->input6.end(), MergeSort::MergeType::ExtraSpace);
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, inPlaceMergeSort) {
	MergeSort::Sort(this->input0.begin(), this->input0.end(), MergeSort::MergeType::InPlace);
	EXPECT_EQ(this->input0, this->expected0);
	MergeSort::Sort(this->input1.begin(), this->input1.end(), MergeSort::MergeType::InPlace);
	EXPECT_EQ(this->input1, this->expected1);
	MergeSort::Sort(this->input2.begin(), this->input2.end(), MergeSort::MergeType::InPlace);
	EXPECT_EQ(this->input2, this->expected2);
	MergeSort::Sort(this->input3.begin(), this->input3.end(), MergeSort::MergeType::InPlace);
	EXPECT_EQ(this->input3, this->expected3);
	MergeSort::Sort(this->input4.begin(), this->input4.end(), MergeSort::MergeType::InPlace);
	EXPECT_EQ(this->input4, this->expected4);
	MergeSort::Sort(this->input5.begin(), this->input5.end(), MergeSort::MergeType::InPlace);
	EXPECT_EQ(this->input5, this->expected5);
	MergeSort::Sort(this->input6.begin(), this->input6.end(), MergeSort::MergeType::InPlace);
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, quicksort) {
	Quicksort::Sort(this->input0.begin(), this->input0.end());
	EXPECT_EQ(this->input0, this->expected0);
	Quicksort::Sort(this->input1.begin(), this->input1.end());
	EXPECT_EQ(this->input1, this->expected1);
	Quicksort::Sort(this->input2.begin(), this->input2.end());
	EXPECT_EQ(this->input2, this->expected2);
	Quicksort::Sort(this->input3.begin(), this->input3.end());
	EXPECT_EQ(this->input3, this->expected3);
	Quicksort::Sort(this->input4.begin(), this->input4.end());
	EXPECT_EQ(this->input4, this->expected4);
	Quicksort::Sort(this->input5.begin(), this->input5.end());
	EXPECT_EQ(this->input5, this->expected5);
	Quicksort::Sort(this->input6.begin(), this->input6.end());
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, selectionSort) {
	SelectionSort::Sort(this->input0.begin(), this->input0.end());
	EXPECT_EQ(this->input0, this->expected0);
	SelectionSort::Sort(this->input1.begin(), this->input1.end());
	EXPECT_EQ(this->input1, this->expected1);
	SelectionSort::Sort(this->input2.begin(), this->input2.end());
	EXPECT_EQ(this->input2, this->expected2);
	SelectionSort::Sort(this->input3.begin(), this->input3.end());
	EXPECT_EQ(this->input3, this->expected3);
	SelectionSort::Sort(this->input4.begin(), this->input4.end());
	EXPECT_EQ(this->input4, this->expected4);
	SelectionSort::Sort(this->input5.begin(), this->input5.end());
	EXPECT_EQ(this->input5, this->expected5);
	SelectionSort::Sort(this->input6.begin(), this->input6.end());
	EXPECT_EQ(this->input6, this->expected6);
}

TYPED_TEST(ArrayOfNumbersTest, timsort) {
	Timsort::Sort(this->input0.begin(), this->input0.end());
	EXPECT_EQ(this->input0, this->expected0);
	Timsort::Sort(this->input1.begin(), this->input1.end());
	EXPECT_EQ(this->input1, this->expected1);
	Timsort::Sort(this->input2.begin(), this->input2.end());
	EXPECT_EQ(this->input2, this->expected2);
	Timsort::Sort(this->input3.begin(), this->input3.end());
	EXPECT_EQ(this->input3, this->expected3);
	Timsort::Sort(this->input4.begin(), this->input4.end());
	EXPECT_EQ(this->input4, this->expected4);
	Timsort::Sort(this->input5.begin(), this->input5.end());
	EXPECT_EQ(this->input5, this->expected5);
	Timsort::Sort(this->input6.begin(), this->input6.end());
	EXPECT_EQ(this->input6, this->expected6);
}

template<typename NumType>
class DequeOfNumbersTest : public ::testing::Test {
protected:
	vector<deque<NumType>> input;
	vector<deque<NumType>> expected;
	virtual void SetUp() {
		for (auto i : { deque<NumType>{},
										deque<NumType>{1},
										deque<NumType>{2, 1},
										deque<NumType>{1, 1, 1},
										deque<NumType>{1, 2, 3, 4, 5, 6, 7},
										deque<NumType>{7, 6, 5, 4, 3, 2, 1},
										deque<NumType>{10, 3, 9, 6, 7, 1, 2, 4, 5, 8, 11} }) {
			input.emplace_back(i);
			sort(i.begin(), i.end());
			expected.emplace_back(i);
		}
		CreateLongRandomDeque();
	}
	void CreateLongRandomDeque() {
		random_device rd;
		vector<unsigned int> seeds;
		for (unsigned int i=0; i<mt19937::state_size; ++i) {
			seeds.emplace_back(rd());
		}
		seed_seq s(seeds.begin(),seeds.end());
		mt19937 eng(s);
		uniform_int_distribution<int> numOfNumbersDist(1000,9999);
		uniform_int_distribution<int> numberDist(0,1000000000);

		deque<NumType> numbers;

		int numOfNumbers = numOfNumbersDist(eng);
		for (int i=0; i<numOfNumbers; ++i) {
			numbers.emplace_back(numberDist(eng));
		}

		input.emplace_back(numbers);
		sort(numbers.begin(), numbers.end());
		expected.emplace_back(numbers);
	}
};

typedef ::testing::Types<char, int, unsigned int, float, double> NumberTypes;
TYPED_TEST_CASE(DequeOfNumbersTest, NumberTypes);

TYPED_TEST(DequeOfNumbersTest, bogosortRandom) {
	//Dont bother testing bogosort for large lists
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			// auto inputCopy = this->input.at(i);
			Bogosort::Sort(this->input.at(i).begin(), this->input.at(i).end(), Bogosort::ShuffleType::Random);
			EXPECT_EQ(this->input.at(i), this->expected.at(i));
		}
	}
}

TYPED_TEST(DequeOfNumbersTest, bogosortPermute) {
	//Dont bother testing bogosort for large lists
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			// auto inputCopy = this->input.at(i);
			Bogosort::Sort(this->input.at(i).begin(), this->input.at(i).end(), Bogosort::ShuffleType::Permute);
			EXPECT_EQ(this->input.at(i), this->expected.at(i));
		}
	}
}

TYPED_TEST(DequeOfNumbersTest, bubbleSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		BubbleSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(DequeOfNumbersTest, heapsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Heapsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(DequeOfNumbersTest, insertionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		InsertionSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(DequeOfNumbersTest, introsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Introsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(DequeOfNumbersTest, extraSpaceMergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::ExtraSpace);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(DequeOfNumbersTest, inPlaceMergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::InPlace);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(DequeOfNumbersTest, quicksort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Quicksort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(DequeOfNumbersTest, selectionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		SelectionSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(DequeOfNumbersTest, timsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Timsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

template<typename NumType>
class VectorOfNumbersTest : public ::testing::Test {
protected:
	vector<vector<NumType>> input;
	vector<vector<NumType>> expected;
	virtual void SetUp() {
		for (auto i : { vector<NumType>{},
										vector<NumType>{1},
										vector<NumType>{2, 1},
										vector<NumType>{1, 1, 1},
										vector<NumType>{1, 2, 3, 4, 5, 6, 7},
										vector<NumType>{7, 6, 5, 4, 3, 2, 1},
										vector<NumType>{10, 3, 9, 6, 7, 1, 2, 4, 5, 8, 11} }) {
			input.emplace_back(i);
			sort(i.begin(), i.end());
			expected.emplace_back(i);
		}
		CreateLongRandomList();
	}
	void CreateLongRandomList() {
		random_device rd;
		vector<unsigned int> seeds;
		for (unsigned int i=0; i<mt19937::state_size; ++i) {
			seeds.emplace_back(rd());
		}
		seed_seq s(seeds.begin(),seeds.end());
		mt19937 eng(s);
		uniform_int_distribution<int> numOfNumbersDist(1000,9999);
		uniform_int_distribution<int> numberDist(0,1000000000);

		vector<NumType> numbers;

		int numOfNumbers = numOfNumbersDist(eng);
		for (int i=0; i<numOfNumbers; ++i) {
			numbers.emplace_back(numberDist(eng));
		}

		input.emplace_back(numbers);
		sort(numbers.begin(), numbers.end());
		expected.emplace_back(numbers);
	}
};

typedef ::testing::Types<char, int, unsigned int, float, double> NumberTypes;
TYPED_TEST_CASE(VectorOfNumbersTest, NumberTypes);

TYPED_TEST(VectorOfNumbersTest, bogosortRandom) {
	//Dont bother testing bogosort for large lists
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			// auto inputCopy = this->input.at(i);
			Bogosort::Sort(this->input.at(i).begin(), this->input.at(i).end(), Bogosort::ShuffleType::Random);
			EXPECT_EQ(this->input.at(i), this->expected.at(i));
		}
	}
}

TYPED_TEST(VectorOfNumbersTest, bogosortPermute) {
	//Dont bother testing bogosort for large lists
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			// auto inputCopy = this->input.at(i);
			Bogosort::Sort(this->input.at(i).begin(), this->input.at(i).end(), Bogosort::ShuffleType::Permute);
			EXPECT_EQ(this->input.at(i), this->expected.at(i));
		}
	}
}

TYPED_TEST(VectorOfNumbersTest, bubbleSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		BubbleSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, heapsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Heapsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, insertionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		InsertionSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, introsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Introsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, extraSpaceMergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::ExtraSpace);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, inPlaceMergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::InPlace);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, quicksort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Quicksort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, selectionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		SelectionSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, timsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Timsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

class VectorOfStringsTest : public ::testing::Test {
protected:
	vector<vector<string>> input;
	vector<vector<string>> expected;
	virtual void SetUp() {
		for (auto i : { vector<string>{},
										vector<string>{"hey"},
										vector<string>{"z", "a"},
										vector<string>{"z", "g", "s", "y", "e", "j", "a", "k", "p", "o"},
										vector<string>{"abc", "abc", "abc", "abc", "abc", "abc", "abc"},
										vector<string>{"z", "h", "e", "d", "b"} }) {
			input.emplace_back(i);
			sort(i.begin(), i.end(), StringComp);
			expected.emplace_back(i);
		}
		CreateLongRandomList();
	}
	void CreateLongRandomList() {
		random_device rd;
		vector<unsigned int> seeds;
		for (unsigned int i=0; i<mt19937::state_size; ++i) {
			seeds.emplace_back(rd());
		}
		seed_seq s(seeds.begin(),seeds.end());
		mt19937 eng(s);
		uniform_int_distribution<int> listLengthDist(1000,9999);
		uniform_int_distribution<int> charsInStringDist(1,500);
		uniform_int_distribution<int> charsDist(' ','~');

		vector<string> strings;

		int length = listLengthDist(eng);
		for (int i=0; i<length; ++i) {
			int charCount = charsInStringDist(eng);
			std::string s;
			for (int j=0; j<charCount; ++j) {
				s += charsDist(eng);
			}
			strings.emplace_back(s);
		}

		input.emplace_back(strings);
		sort(strings.begin(), strings.end(), StringComp);
		expected.emplace_back(strings);
	}
	function<bool(string,string)> StringComp = [](const string &s1, const string &s2) -> bool {
		return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end());
	};
};

TEST_F(VectorOfStringsTest, bogosortRandom) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			// auto inputCopy = this->input.at(i);
			Bogosort::Sort(this->input.at(i).begin(), this->input.at(i).end(), Bogosort::ShuffleType::Random, this->StringComp);
			EXPECT_EQ(this->input.at(i), this->expected.at(i));
		}
	}
}

TEST_F(VectorOfStringsTest, bogosortPermute) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			// auto inputCopy = this->input.at(i);
			Bogosort::Sort(this->input.at(i).begin(), this->input.at(i).end(), Bogosort::ShuffleType::Permute, this->StringComp);
			EXPECT_EQ(this->input.at(i), this->expected.at(i));
		}
	}
}

TEST_F(VectorOfStringsTest, bubbleSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		BubbleSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), this->StringComp);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, heapsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Heapsort::Sort(this->input.at(i).begin(), this->input.at(i).end(), this->StringComp);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, insertionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		InsertionSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), this->StringComp);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, introsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Introsort::Sort(this->input.at(i).begin(), this->input.at(i).end(), this->StringComp);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, extraSpaceMergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::ExtraSpace, this->StringComp);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, inPlaceMergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::InPlace, this->StringComp);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, quicksort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Quicksort::Sort(this->input.at(i).begin(), this->input.at(i).end(), this->StringComp);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, selectionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		SelectionSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), this->StringComp);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, timsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Timsort::Sort(this->input.at(i).begin(), this->input.at(i).end(), this->StringComp);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

class VectorOfDistancesTest : public ::testing::Test {
protected:
	vector<vector<Distance>> input;
	vector<vector<Distance>> expected;
	virtual void SetUp() {
		for (auto i : { vector<Distance>{ },
										vector<Distance>{ {123, 32.1} },
										vector<Distance>{ {50, 3}, {50, 2} },
										vector<Distance>{ {1, 5.6789}, {2, 5.6789}, {3, 5.6789} },
										vector<Distance>{ {10, 10.123}, {10, 20.456}, {10, 30.789} },
										vector<Distance>{ {2, 2.3}, {3, 2.3}, {2, 2.2} },
										vector<Distance>{ {1, 100.5}, {1, 23.6363}, {9, 45634.22}, {9, 0.00001} } }) {
			input.emplace_back(i);
			sort(i.begin(), i.end());
			expected.emplace_back(i);
		}
		CreateLongRandomList();
	}
	void CreateLongRandomList() {
		random_device rd;
		vector<unsigned int> seeds;
		for (unsigned int i=0; i<mt19937::state_size; ++i) {
			seeds.emplace_back(rd());
		}
		seed_seq s(seeds.begin(),seeds.end());
		mt19937 eng(s);
		uniform_int_distribution<int> listLengthDist(1000,9999);
		uniform_int_distribution<int> intDist(0,1000);
		uniform_real_distribution<double> doubleDist(0,1000);

		vector<Distance> distances;

		int length = listLengthDist(eng);
		for (int i=0; i<length; ++i) {
			distances.emplace_back(intDist(eng), doubleDist(eng));
		}

		input.emplace_back(distances);
		sort(distances.begin(), distances.end());
		expected.emplace_back(distances);
	}
};

TEST_F(VectorOfDistancesTest, bogosortRandom) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			// auto inputCopy = this->input.at(i);
			Bogosort::Sort(this->input.at(i).begin(), this->input.at(i).end(), Bogosort::ShuffleType::Random);
			EXPECT_EQ(this->input.at(i), this->expected.at(i));
		}
	}
}

TEST_F(VectorOfDistancesTest, bogosortPermute) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			// auto inputCopy = this->input.at(i);
			Bogosort::Sort(this->input.at(i).begin(), this->input.at(i).end(), Bogosort::ShuffleType::Permute);
			EXPECT_EQ(this->input.at(i), this->expected.at(i));
		}
	}
}

TEST_F(VectorOfDistancesTest, bubbleSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		BubbleSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, heapsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Heapsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, insertionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		InsertionSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, introsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Introsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, extraSpaceMergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::ExtraSpace);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, inPlaceMergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::InPlace);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, quicksort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Quicksort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, selectionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		SelectionSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, timsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		// auto inputCopy = this->input.at(i);
		Timsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

class StableObject {
private:
public:
	int first, second;
	StableObject(int a, int b) : first(a), second(b) {};
};

bool operator<(const StableObject &left, const StableObject &right) {
	return left.first < right.first;
}

bool operator==(const StableObject &left, const StableObject &right) {
	return left.first == right.first && left.second == right.second;
}

ostream& operator<<(ostream &stream, const StableObject &so) {
	stream << "{" << so.first << "," << so.second << "}";
	return stream;
}

class StableSortTest : public ::testing::Test {
protected:
	vector<vector<StableObject>> input;
	vector<vector<StableObject>> expected;
	virtual void SetUp() {
		random_device rd;
		vector<unsigned int> seeds;
		for (unsigned int i=0; i<mt19937::state_size; ++i) {
			seeds.emplace_back(rd());
		}
		seed_seq s(seeds.begin(),seeds.end());
		mt19937 eng(s);

		uniform_int_distribution<int> intDist(0,100);

		for (int i=0; i<8; ++i) {
			uniform_int_distribution<int> lengthDist(1<<(i+7),1<<(i+8));
			input.push_back(vector<StableObject>());
			int length = lengthDist(eng);
			for (int j=0; j<length; ++j) {
				input.at(i).emplace_back(intDist(eng), j+1);
			}

			expected.push_back(input.at(i));
			stable_sort(expected.at(i).begin(), expected.at(i).end());
		}
	}
};

TEST_F(StableSortTest, bubbleSort) {
	for (size_t i=0; i<input.size(); ++i) {
		BubbleSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(StableSortTest, insertionSort) {
	for (size_t i=0; i<input.size(); ++i) {
		InsertionSort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(StableSortTest, extraSpaceMergeSort) {
	for (size_t i=0; i<input.size(); ++i) {
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::ExtraSpace);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(StableSortTest, inPlaceMergeSort) {
	for (size_t i=0; i<input.size(); ++i) {
		MergeSort::Sort(this->input.at(i).begin(), this->input.at(i).end(), MergeSort::MergeType::InPlace);
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}

TEST_F(StableSortTest, timsort) {
	for (size_t i=0; i<input.size(); ++i) {
		Timsort::Sort(this->input.at(i).begin(), this->input.at(i).end());
		EXPECT_EQ(this->input.at(i), this->expected.at(i));
	}
}