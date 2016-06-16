#include <cmath>
#include <algorithm>
#include <vector>
#include "heapsort.hpp"
#include "quicksort.hpp"

#ifndef _INTROSORT_HPP
#define _INTROSORT_HPP 1

namespace IntroSort {

  enum { SortThreshold = 16 };

	template<class RandomIt, class SizeType>
	void SortLimitedDepth(RandomIt first, RandomIt end, SizeType depthLimit) {
		auto length = end-first;
		if (length > 1) {
			//At least 2 elements to sort
			if (depthLimit == 0) {
				//Hit our depth limit, do heapsort now
				HeapSort::Sort(first,end);
				return;
			}
			--depthLimit;
			//Didnt hit the depth limit yet, continue quicksort
			RandomIt partition = QuickSort::Partition(first, end);
			SortLimitedDepth(first, partition, depthLimit);
			SortLimitedDepth(partition, end, depthLimit);
		}
	}

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt end) {
		auto length = end-first;
		int maxDepth = 2 * static_cast<int>(log2(length));
		SortLimitedDepth(first, end, maxDepth);
	}
}

#endif //_INTROSORT_HPP