#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP 1

#include <algorithm>

namespace BubbleSort {

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt begin, RandomIt end, Compare Comp = Compare()) {
		size_t length = std::distance(begin, end);
		size_t firstInOrderPosition = length;

		while (firstInOrderPosition > 0) {
			size_t newFirst = 0;
			for (size_t i=1; i<firstInOrderPosition; ++i) {
				//"Bubble" up the (i-1)th element to just before 'firstInOrderPosition'
				if (Comp(*(begin+i), *(begin+(i-1)))) {
					std::iter_swap(begin+(i-1), begin+i);
					newFirst = i;
				}
			}
			//Update 'firstInOrderPosition' for the next iteration
			firstInOrderPosition = newFirst;
		}
	}
}

#endif //BUBBLESORT_HPP