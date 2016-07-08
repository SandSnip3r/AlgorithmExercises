#include "gtest/gtest.h"

using namespace std;

TEST(TestCaseName, testName) {
	ASSERT_EQ(1,1<<0);
	ASSERT_EQ(2,1<<1);
	ASSERT_EQ(4,1<<2);
	ASSERT_EQ(8,1<<3);
	ASSERT_EQ(16,1<<4);
	ASSERT_EQ(32,1<<5);
	ASSERT_EQ(64,1<<6);
}

/*template<typename NumType>
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
}*/

/*class VectorOfStringsTest : public ::testing::Test {
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
			Bogosort::Sort(this->input.at(i).begin(), this->input.at(i).end(), Bogosort::ShuffleType::Random, this->StringComp);
			EXPECT_EQ(this->input.at(i), this->expected.at(i));
		}
	}
}*/