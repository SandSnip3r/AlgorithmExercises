#include <algorithm>
#include <vector>

#ifndef _BUBBLESORT_HPP
#define _BUBBLESORT_HPP 1

namespace BubbleSort {

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;

		DiffType length = end-first;
		DiffType firstInOrderPosition = length;

		while (firstInOrderPosition > 0) {
			unsigned newFirst = 0;
			for (unsigned int i=1; i<firstInOrderPosition; ++i) {
				//"Bubble" up the (i-1)th element to just before 'firstInOrderPosition'
				if (Comp(*(first+i), *(first+(i-1)))) {
					std::iter_swap(first+(i-1), first+i);
					newFirst = i;
				}
			}
			//Update 'firstInOrderPosition' for the next iteration
			firstInOrderPosition = newFirst;
		}
	}
}

#endif //_BUBBLESORT_HPP