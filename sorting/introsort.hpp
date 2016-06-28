#ifndef INTROSORT_HPP
#define INTROSORT_HPP 1

#include <algorithm>
#include <cmath>
#include <iterator>
#include "heapsort.hpp"
#include "insertionSort.hpp"
#include "quicksort.hpp"

namespace Introsort {

  const size_t SORT_THRESHOLD = 16;

	template<class RandomIt, class Compare>
	void SortLimitedDepth(RandomIt begin, RandomIt end, int depthLimit, Compare Comp) {
		//This method uses a while loop to continually sort the left
		//	half of the list and recursively sort the right,
		//	rather than recursively sorting both
		while (static_cast<size_t>(std::distance(begin,end)) > SORT_THRESHOLD) {
			//While the length of our list is greater than the specified threshold
			if (depthLimit == 0) {
				//Hit our depth limit(pivot selection was too unbalanced), do heapsort now
				Heapsort::Sort(begin, end, Comp);
				return;
			}
			--depthLimit;
			//Didnt hit the depth limit yet, continue quicksort
			RandomIt partition = Quicksort::Partition(begin, end, Comp);
			SortLimitedDepth(partition, end, depthLimit, Comp);
			end = partition;
		}
	}

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt begin, RandomIt end, Compare Comp = Compare()) {
		size_t length = std::distance(begin,end);

		if (length < 2) {
			return;
		}

		int maxDepth = 2 * static_cast<int>(log2(length));

		//Use Quicksort until it's repeatedly too unbalanced
		//	(maxDepth prevents too many recursions)
		SortLimitedDepth(begin, end, maxDepth, Comp);
		//This leaves unsorted chunks of no more than size 'SORT_THRESHOLD',
		//	insertion sort should do well here
		InsertionSort::Sort(begin, end, Comp);
	}
} //namespace Introsort

#endif //INTROSORT_HPP