#include <cmath>
#include <algorithm>
#include <vector>
#include "heapsort.hpp"
#include "insertionsort.hpp"
#include "quicksort.hpp"

#ifndef _INTROSORT_HPP
#define _INTROSORT_HPP 1

namespace IntroSort {

  enum { SortThreshold = 16 };

	template<class RandomIt, class SizeType>
	void SortLimitedDepth(RandomIt first, RandomIt end, SizeType depthLimit) {
		while ((end-first) > int(SortThreshold)) {
			if (depthLimit == 0) {
				//Hit our depth limit, do heapsort now
				HeapSort::Sort(first,end);
				return;
			}
			--depthLimit;
			//Didnt hit the depth limit yet, continue quicksort
			RandomIt partition = QuickSort::Partition(first, end);
			// SortLimitedDepth(first, partition, depthLimit);
			SortLimitedDepth(partition, end, depthLimit);
			end = partition;
		}
	}

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt end) {
		auto length = end-first;
		int maxDepth = 2 * static_cast<int>(log2(length));
		SortLimitedDepth(first, end, maxDepth);
		//This leaves unsorted chunks of no more than size 'SortThreshold'
		InsertionSort::Sort(first,end);
	}
}

#endif //_INTROSORT_HPP