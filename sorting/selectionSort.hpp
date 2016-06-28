#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP 1

#include <algorithm>

namespace SelectionSort {

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		while (first != end) {
			std::iter_swap(first, std::min_element(first, end, Comp));
			++first;
		}
	}
} //namespace SelectionSort

#endif //SELECTIONSORT_HPP