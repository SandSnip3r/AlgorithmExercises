#include <algorithm>
#include <vector>

#ifndef _QUICKSORT_HPP
#define _QUICKSORT_HPP 1

namespace Quicksort {
	template<class RandomIt>
	RandomIt GetMedian(RandomIt first, RandomIt middle, RandomIt last) {
		if (middle == last) {
			//If there are 2 elements, there isnt really a middle
			return last;
		}
		typename std::iterator_traits<RandomIt>::value_type firstValue = *first;
		typename std::iterator_traits<RandomIt>::value_type middleValue = *middle;
		typename std::iterator_traits<RandomIt>::value_type lastValue = *last;
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
		typename std::iterator_traits<RandomIt>::difference_type length = end-first;
		RandomIt last = end - 1;
		RandomIt middle = first + length/2;
		//For the pivot, use the median of the first, last, and middle element
		typename std::iterator_traits<RandomIt>::value_type pivot = *GetMedian(first, middle, last);
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
		typename std::iterator_traits<RandomIt>::difference_type length = end-first;
		if (length > 1) {
			//At least 2 elements to sort
			RandomIt partition = Partition(first, end);
			Sort(first, partition);
			Sort(partition, end);
		}
	}
}

#endif //_QUICKSORT_HPP