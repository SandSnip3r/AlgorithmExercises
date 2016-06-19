#include <algorithm>
#include <vector>

#ifndef _MERGESORT_HPP
#define _MERGESORT_HPP 1

namespace MergeSort {
	template<class RandomIt, class Compare>
	void Merge(RandomIt first, RandomIt middle, RandomIt end, Compare Comp) {
		while (middle != end) {
			while (first != middle && Comp(*first, *middle)) {
				++first;
			}
			if (first == middle) {
				//All good
				return;
			} else {
				//Need to do a rotate
				//	This moves 'middle' to the position of 'first',
				//	and shifts [first, middle) to the right one
				std::rotate(first, middle, middle+1);
				++first;
				++middle;
			}
		}
	}

	template<class RandomIt, class Compare>
	void SplitMerge(RandomIt first, RandomIt end, Compare Comp) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;
		DiffType length = end-first;
		if (length == 1) {
			return;
		}
		RandomIt middle = first + length/2;
		SplitMerge(first, middle, Comp);
		SplitMerge(middle, end, Comp);
		//Left half and right half are sorted, now merge them
		Merge(first, middle, end, Comp);
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		SplitMerge(first, end, Comp);
	}
}

#endif //_MERGESORT_HPP