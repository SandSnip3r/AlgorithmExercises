#include <algorithm>
#include <vector>

#ifndef _SELECTIONSORT_HPP
#define _SELECTIONSORT_HPP 1

namespace SelectionSort {

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;
		DiffType length = end-first;
		for (unsigned int firstUnsortedElement=0; firstUnsortedElement<length; ++firstUnsortedElement) {
			RandomIt min = std::min_element(first+firstUnsortedElement, end);
			if ((first+firstUnsortedElement) != min) {
				std::iter_swap((first+firstUnsortedElement), min);
			}
		}
	}
}

#endif //_INSERTIONSORT_HPP