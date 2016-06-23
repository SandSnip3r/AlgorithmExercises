#include <algorithm>
#include <vector>
#include "insertionSort.hpp"

#ifndef _TIMSORT_HPP
#define _TIMSORT_HPP 1

namespace Timsort {
	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		typedef typename std::iterator_traits<RandomIt>::difference_type DiffType;
		DiffType length = end-first;
	}
}

#endif //_TIMSORT_HPP