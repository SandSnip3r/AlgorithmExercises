#include <algorithm>
#include <functional>
#include <random>
#include <vector>

#ifndef _BOGOSORT_HPP
#define _BOGOSORT_HPP 1

namespace Bogosort {

	enum class ShuffleType { Random, Permute };

	std::mt19937 CreateRandomEngine() {
		std::random_device rd;
		std::vector<int> seeds;
		for (unsigned int i=0; i<std::mt19937::state_size; ++i) {
			seeds.emplace_back(rd());
		}
		std::seed_seq s(seeds.begin(), seeds.end());
		return std::mt19937(s);
	}

	template<class RandomIt, class Compare>
	void SortRandom(RandomIt first, RandomIt end, Compare comp) {
		std::mt19937 eng = CreateRandomEngine();
		while (!std::is_sorted(first,end, comp)) {
			std::shuffle(first, end, eng);
		}
	}

	template<class RandomIt, class Compare>
	void SortPermute(RandomIt first, RandomIt end, Compare comp) {
		//This method will iteratate through every permutation of the list possible
		// (not necessarily in lexicographical order)
		using DifferenceType = typename std::iterator_traits<RandomIt>::difference_type;

		DifferenceType length = end - first;

		std::vector<int> p(length);
		{
			int i = 0;
			std::generate(p.begin(), p.end(), [&i]{return i++;});
		}

		int i=1;
		while (!std::is_sorted(first, end, comp) && i<length) {
			--p.at(i);
			int j=0;
			if (i%2 == 1) {
				j = p.at(i);
			}
			std::iter_swap((first+i), (first+j));
			i = 1;
			while (i < length && p.at(i) == 0) {
				p.at(i) = i;
				++i;
			}
		}
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, ShuffleType shuffleType = ShuffleType::Random, Compare comp = Compare()) {
		if (shuffleType == ShuffleType::Random) {
			SortRandom(first, end, comp);
		} else {
			SortPermute(first, end, comp);
		}
	}
}

#endif //_BOGOSORT_HPP