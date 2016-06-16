#include <algorithm>
#include <vector>

#ifndef _HEAPSORT_HPP
#define _HEAPSORT_HPP 1

namespace InsertionSort {

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt end) {
		Heapify(first, end);
		while ((end - first) > 0) {
			//Top of the heap is the greatest, swap it with the back
			auto last = end-1;
			std::iter_swap(first, last);
			//Step the back down one because that element is now in the sorted position
			--end;
			//Now heapify down the new root element
			HeapifyDown(first, first, end);
		}
	}
}

#endif //_HEAPSORT_HPP