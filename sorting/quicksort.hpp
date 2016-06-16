#include <algorithm>
#include <vector>

#ifndef _QUICKSORT_HPP
#define _QUICKSORT_HPP 1

namespace QuickSort {
	template<class RandomIt>
	RandomIt GetMedian(RandomIt first, RandomIt middle, RandomIt last) {
		if (middle == last) {
			//If there are 2 elements, there isnt really a middle
			return last;
		}
		auto firstValue = *first;
		auto middleValue = *middle;
		auto lastValue = *last;
		if (firstValue <= middleValue && middleValue <= lastValue) {
			//middle is the median
			return middle;
		} else if (middleValue <= firstValue && firstValue <= lastValue) {
			//first is the median
			return first;
		} else {
			//last must be the median
			return last;
		}
	}

	template<class RandomIt>
	RandomIt Partition(RandomIt first, RandomIt end) {
		RandomIt last = end - 1;
		RandomIt middle = first + (end-first)/2;
		//For the pivot, use the median of the first, last, and middle element
		auto pivot = *GetMedian(first, middle, last);
		while (1) {
			while (*first < pivot) {
				++first;
			}
			while (*last > pivot) {
				--last;
			}
			if (last-first <= 0) {
				return first;
			}
			std::iter_swap(first,last);
			++first;
			--last;
		}
	}

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt end) {
		auto length = end-first;
		if (length > 1) {
			//At least 2 elements to sort
			RandomIt partition = Partition(first, end);
			Sort(first, partition);
			Sort(partition, end);
		}
	}
}

#endif //_QUICKSORT_HPP