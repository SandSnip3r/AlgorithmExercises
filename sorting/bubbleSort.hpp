#include <algorithm>
#include <vector>

#ifndef _BUBBLESORT_HPP
#define _BUBBLESORT_HPP 1

namespace BubbleSort {

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt end) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;
		DiffType length = end-first;
		DiffType firstInOrderPosition = length;
		while (firstInOrderPosition > 0) {
			unsigned newFirst = 0;
			for (unsigned int i=1; i<firstInOrderPosition; ++i) {
				if (*(first+(i-1)) > *(first+i)) {
					std::iter_swap(first+(i-1), first+i);
					newFirst = i;
				}
			}
			firstInOrderPosition = newFirst;
		}
	}
}

#endif //_BUBBLESORT_HPP