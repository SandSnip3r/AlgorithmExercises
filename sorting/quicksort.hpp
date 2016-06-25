#include <algorithm>
#include <vector>

#ifndef _QUICKSORT_HPP
#define _QUICKSORT_HPP 1

namespace Quicksort {
	template<class RandomIt, class Compare>
	RandomIt GetMedian(RandomIt first, RandomIt middle, RandomIt last, Compare Comp) {
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;

		if (middle == last) {
			//If there are 2 elements, there isnt really a middle
			//	there's either 1 or 2 elements
			return last;
		}

		ValueType firstValue = *first;
		ValueType middleValue = *middle;
		ValueType lastValue = *last;

		if (!Comp(lastValue, middleValue) && !Comp(middleValue, firstValue)) {
			//middle is the median
			return middle;
		} else if (!Comp(lastValue, firstValue) && !Comp(firstValue, middleValue)) {
			//first is the median
			return first;
		} else {
			//last must be the median
			return last;
		}
	}

	template<class RandomIt, class Compare>
	RandomIt Partition(RandomIt first, RandomIt end, Compare Comp) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;

		DiffType length = end-first;
		RandomIt last = end - 1;
		RandomIt middle = first + length/2;

		//For the pivot, use the median of the first, last, and middle element
		ValueType pivot = *GetMedian(first, middle, last, Comp);
		while (1) {
			while (Comp(*first, pivot)) {
				++first;
			}
			while (Comp(pivot, *last)) {
				--last;
			}
			if (last-first <= 0) {
				//The first and last iterators have crossed eachother
				//	everything is now on the correct side of the pivot
				return first;
			}
			std::iter_swap(first,last);
			++first;
			--last;
		}
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;
		
		DiffType length = end-first;

		if (length > 1) {
			//At least 2 elements to sort
			RandomIt partition = Partition(first, end, Comp);
			Sort(first, partition, Comp);
			Sort(partition, end, Comp);
		}
	}
}

#endif //_QUICKSORT_HPP