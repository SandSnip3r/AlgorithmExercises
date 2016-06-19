#include <algorithm>
#include <functional>
#include <random>
#include <vector>

#ifndef _BOGOSORT_HPP
#define _BOGOSORT_HPP 1

namespace Bogosort {

	std::mt19937 CreateRandomEngine() {
		std::random_device rd;
		std::vector<int> seeds;
		for (unsigned int i=0; i<std::mt19937::state_size; ++i) {
			seeds.emplace_back(rd());
		}
		std::seed_seq s(seeds.begin(), seeds.end());
		return std::mt19937(s);
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare comp = Compare()) {
		std::mt19937 eng = CreateRandomEngine();
		while (!std::is_sorted(first,end, comp)) {
			std::shuffle(first, end, eng);
		}
	}
}

#endif //_BOGOSORT_HPP