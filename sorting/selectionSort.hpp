#include <algorithm>
#include <vector>

#ifndef _SELECTIONSORT_HPP
#define _SELECTIONSORT_HPP 1

namespace SelectionSort {

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		while (first != end) {
			std::iter_swap(first, std::min_element(first, end, Comp));
			++first;
		}
	}
}

#endif //_INSERTIONSORT_HPP