#include <algorithm>
#include <vector>

#ifndef _INSERTIONSORT_HPP
#define _INSERTIONSORT_HPP 1

namespace InsertionSort {

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt end) {
		auto length = end-first;
		for (int i=1; i<length; ++i) {
			auto val = *(first+i);
			auto newPos = i-1;
			while (newPos >= 0 && *(first+newPos) > val) {
				*(first+newPos+1) = *(first+newPos);
				--newPos;
			}
			*(first+newPos+1) = val;
		}
	}
}

#endif //_INSERTIONSORT_HPP