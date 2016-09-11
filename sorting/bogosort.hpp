#ifndef BOGOSORT_HPP
#define BOGOSORT_HPP 1

#include <algorithm>
#include <functional>
#include <iterator>
#include <random>
#include <vector>

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

	template<class RandomIt, class Compare, typename = std::enable_if_t<std::is_base_of<std::random_access_iterator_tag, typename std::iterator_traits<RandomIt>::iterator_category>::value>>
	//std::is_sorted requires the passed iterator to be a ForwardIterator
	//std::shuffle requires the passed iterator to be a RandomIterator
	void SortRandom(RandomIt begin, RandomIt end, Compare comp) {
		//While the list isn't in order, shuffle it
		std::mt19937 eng = CreateRandomEngine();
		while (!std::is_sorted(begin, end, comp)) {
			std::shuffle(begin, end, eng);
		}
	}

	template<class ForwardIt, class Compare, typename = std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<ForwardIt>::iterator_category>::value>>
	//std::distance requires the passed iterator to be an InputIterator
	//std::is_sorted and std::iter_swap require the passed iterator to be a ForwardIterator
	void SortPermute(ForwardIt begin, ForwardIt end, Compare comp) {
		//This method will iteratate through every permutation of the list possible
		// (not necessarily in lexicographical order)
		size_t length = std::distance(begin,end);

		//Create a vector to store the state of the permutation
		std::vector<size_t> p(length);
		{
			size_t i = 0;
			std::generate(p.begin(), p.end(), [&i]{return i++;});
		}

		size_t i=1;
		while (!std::is_sorted(begin, end, comp) && i<length) {
			//Advance to the next permutation
			--p.at(i);
			size_t j=0;
			if (i%2 == 1) {
				j = p.at(i);
			}
			std::iter_swap(std::next(begin,i), std::next(begin,j));
			i = 1;
			while (i < length && p.at(i) == 0) {
				p.at(i) = i;
				++i;
			}
		}
	}

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt begin, RandomIt end, ShuffleType shuffleType = ShuffleType::Random, Compare comp = Compare()) {
		if (shuffleType == ShuffleType::Random) {
			SortRandom(begin, end, comp);
		} else {
			SortPermute(begin, end, comp);
		}
	}
} //namespace Bogosort

#endif //BOGOSORT_HPP