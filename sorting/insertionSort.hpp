#include <algorithm>
#include <vector>

#ifndef _INSERTIONSORT_HPP
#define _INSERTIONSORT_HPP 1

namespace InsertionSort {

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;

		DiffType length = end-first;
		
		for (unsigned int i=1; i<length; ++i) {
			ValueType val = *(first+i);
			int newPos = i;
			while (newPos > 0 && Comp(val, *(first+newPos-1))) {
				--newPos;
			}
			std::rotate(first+newPos, first+i, first+i+1);
		}
	}
}

#endif //_INSERTIONSORT_HPP