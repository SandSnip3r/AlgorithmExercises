#include <algorithm>
#include <array>
#include <iostream>
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
class VectorOfNumbersTest : public ::testing::Test {
protected:
	vector<vector<NumType>> input;
	vector<vector<NumType>> expected;
	virtual void SetUp() {
		for (auto i : { vector<NumType>{1},
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

TYPED_TEST(VectorOfNumbersTest, BogosortRandom) {
	//Dont bother testing bogosort for large lists
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			auto inputCopy = this->input.at(i);
			Bogosort::Sort(inputCopy.begin(), inputCopy.end(), Bogosort::ShuffleType::Random);
			EXPECT_EQ(inputCopy, this->expected.at(i));
		}
	}
}

TYPED_TEST(VectorOfNumbersTest, BogosortPermute) {
	//Dont bother testing bogosort for large lists
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			auto inputCopy = this->input.at(i);
			Bogosort::Sort(inputCopy.begin(), inputCopy.end(), Bogosort::ShuffleType::Permute);
			EXPECT_EQ(inputCopy, this->expected.at(i));
		}
	}
}

TYPED_TEST(VectorOfNumbersTest, BubbleSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		BubbleSort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, Heapsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		Heapsort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, InsertionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		InsertionSort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, Introsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		Introsort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, MergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		MergeSort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, Quicksort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		Quicksort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TYPED_TEST(VectorOfNumbersTest, SelectionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		SelectionSort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

class VectorOfStringsTest : public ::testing::Test {
protected:
	vector<vector<string>> input;
	vector<vector<string>> expected;
	virtual void SetUp() {
		for (auto i : { vector<string>{"hey"},
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

TEST_F(VectorOfStringsTest, BogosortRandom) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			auto inputCopy = this->input.at(i);
			Bogosort::Sort(inputCopy.begin(), inputCopy.end(), Bogosort::ShuffleType::Random, this->StringComp);
			EXPECT_EQ(inputCopy, this->expected.at(i));
		}
	}
}

TEST_F(VectorOfStringsTest, BogosortPermute) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			auto inputCopy = this->input.at(i);
			Bogosort::Sort(inputCopy.begin(), inputCopy.end(), Bogosort::ShuffleType::Permute, this->StringComp);
			EXPECT_EQ(inputCopy, this->expected.at(i));
		}
	}
}

TEST_F(VectorOfStringsTest, BubbleSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		BubbleSort::Sort(inputCopy.begin(), inputCopy.end(), this->StringComp);
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, Heapsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		Heapsort::Sort(inputCopy.begin(), inputCopy.end(), this->StringComp);
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, InsertionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		InsertionSort::Sort(inputCopy.begin(), inputCopy.end(), this->StringComp);
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, Introsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		Introsort::Sort(inputCopy.begin(), inputCopy.end(), this->StringComp);
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, MergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		MergeSort::Sort(inputCopy.begin(), inputCopy.end(), this->StringComp);
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, Quicksort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		Quicksort::Sort(inputCopy.begin(), inputCopy.end(), this->StringComp);
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfStringsTest, SelectionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		SelectionSort::Sort(inputCopy.begin(), inputCopy.end(), this->StringComp);
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

class VectorOfDistancesTest : public ::testing::Test {
protected:
	vector<vector<Distance>> input;
	vector<vector<Distance>> expected;
	virtual void SetUp() {
		for (auto i : { vector<Distance>{ {1, 5.6789}, {2, 5.6789}, {3, 5.6789} },
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

TEST_F(VectorOfDistancesTest, BogosortRandom) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			auto inputCopy = this->input.at(i);
			Bogosort::Sort(inputCopy.begin(), inputCopy.end(), Bogosort::ShuffleType::Random);
			EXPECT_EQ(inputCopy, this->expected.at(i));
		}
	}
}

TEST_F(VectorOfDistancesTest, BogosortPermute) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		if (this->input.at(i).size() < 12) {
			auto inputCopy = this->input.at(i);
			Bogosort::Sort(inputCopy.begin(), inputCopy.end(), Bogosort::ShuffleType::Permute);
			EXPECT_EQ(inputCopy, this->expected.at(i));
		}
	}
}

TEST_F(VectorOfDistancesTest, BubbleSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		BubbleSort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, Heapsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		Heapsort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, InsertionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		InsertionSort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, Introsort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		Introsort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, MergeSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		MergeSort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, Quicksort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		Quicksort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}

TEST_F(VectorOfDistancesTest, SelectionSort) {
	for (unsigned int i=0; i<this->input.size(); ++i) {
		auto inputCopy = this->input.at(i);
		SelectionSort::Sort(inputCopy.begin(), inputCopy.end());
		EXPECT_EQ(inputCopy, this->expected.at(i));
	}
}