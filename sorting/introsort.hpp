#include <cmath>
#include <algorithm>
#include <vector>
#include "heapsort.hpp"
#include "insertionSort.hpp"
#include "quicksort.hpp"

#ifndef _INTROSORT_HPP
#define _INTROSORT_HPP 1

namespace Introsort {

  enum { SortThreshold = 16 };

	template<class RandomIt, class SizeType, class Compare>
	void SortLimitedDepth(RandomIt first, RandomIt end, SizeType depthLimit, Compare Comp) {
		typedef typename std::iterator_traits<RandomIt>::difference_type DiffType;
		while ((end-first) > static_cast<DiffType>(SortThreshold)) {
			if (depthLimit == 0) {
				//Hit our depth limit, do heapsort now
				Heapsort::Sort(first, end, Comp);
				return;
			}
			--depthLimit;
			//Didnt hit the depth limit yet, continue quicksort
			RandomIt partition = Quicksort::Partition(first, end, Comp);
			// SortLimitedDepth(first, partition, depthLimit);
			SortLimitedDepth(partition, end, depthLimit, Comp);
			end = partition;
		}
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		typedef typename std::iterator_traits<RandomIt>::difference_type DiffType;
		DiffType length = end-first;
		int maxDepth = 2 * static_cast<int>(log2(length));
		SortLimitedDepth(first, end, maxDepth, Comp);
		//This leaves unsorted chunks of no more than size 'SortThreshold'
		InsertionSort::Sort(first, end, Comp);
	}
}

#endif //_INTROSORT_HPP