#include <cmath>
#include <algorithm>
#include "heapsort.hpp"
#include "insertionSort.hpp"
#include "quicksort.hpp"

#ifndef _INTROSORT_HPP
#define _INTROSORT_HPP 1

namespace Introsort {

  enum { SortThreshold = 16 };

	template<class RandomIt, class SizeType, class Compare>
	void SortLimitedDepth(RandomIt first, RandomIt end, SizeType depthLimit, Compare Comp) {
		//This method uses a while loop to continually sort the left
		//	half of the list and recursively sort the right,
		//	rather than recursively sorting both
		while ((end-first) > static_cast<typename std::iterator_traits<RandomIt>::difference_type>(SortThreshold)) {
			//While the length of our list is greater than the specified threshold
			if (depthLimit == 0) {
				//Hit our depth limit(pivot selection was too unbalanced), do heapsort now
				Heapsort::Sort(first, end, Comp);
				return;
			}
			--depthLimit;
			//Didnt hit the depth limit yet, continue quicksort
			RandomIt partition = Quicksort::Partition(first, end, Comp);
			SortLimitedDepth(partition, end, depthLimit, Comp);
			end = partition;
		}
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;

		DiffType length = end-first;
		int maxDepth = 2 * static_cast<int>(log2(length));

		//Use Quicksort unless if it's repeatedly too unbalanced
		//	(maxDepth prevents too many recursions)
		SortLimitedDepth(first, end, maxDepth, Comp);
		//This leaves unsorted chunks of no more than size 'SortThreshold',
		//	insertion sort should do well here
		InsertionSort::Sort(first, end, Comp);
	}
}

#endif //_INTROSORT_HPP