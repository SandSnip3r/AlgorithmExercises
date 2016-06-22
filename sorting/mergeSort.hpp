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

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;
		DiffType length = end-first;
		for (int width=1; width<length; width*=2) {
			//We are going to merge lists of length 'width'
			for (int listStart=0; listStart<length; listStart+=(width*2)) {
				//These 2 lists are [listStart, listStart+width) and [listStart+width, listStart+(width*2))
				int firstPos = listStart;
				int middlePos = listStart+width;
				int endPos = listStart+(width*2);
				if (middlePos >= length) {
					middlePos = length;
					endPos = length;
				} else if (endPos >= length) {
					endPos = length;
				}
				Merge(first+firstPos, first+middlePos, first+endPos, Comp);
			}
		}
	}
}

#endif //_MERGESORT_HPP