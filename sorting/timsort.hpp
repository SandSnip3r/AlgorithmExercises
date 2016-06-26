#include <algorithm>
#include <iostream>
#include "insertionSort.hpp"

#ifndef _TIMSORT_HPP
#define _TIMSORT_HPP 1

namespace Timsort {

	size_t CalculateMinrun(size_t length) {
		//The final algorithm takes the six most significant bits
		//	of the size of the array, adds one if any of the
		//	remaining bits are set, and uses that result as the minrun.
		//	This algorithm works for all arrays, including those smaller than 64.
		size_t mostSignificant6 = length;
		size_t extraBit = 0;
		while (mostSignificant6 >= (1<<6)) {
			//While there are more than 6 significan bits
			//[Or] the least significan bit with 1
			extraBit |= mostSignificant6 & 1;
			//[Right shift] the main number
			mostSignificant6 >>= 1;
		}
		return mostSignificant6 + extraBit;
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt begin, RandomIt end, Compare Comp = Compare()) {
		size_t length = end-begin;
		const size_t minRunLength = CalculateMinrun(length);

		size_t runStart = 0;
		size_t runLength = 0;
		while (runStart < length-1) {
			//Creating new run
			if (*(begin+runStart) <= *(begin+runStart+1)) {
				//Increasing run
				runLength = 2;
				while (*(begin+(runStart+runLength)-1) <= *(begin+(runStart+runLength))) {
					//Grow the run as long as the elements are increasing
					++runLength;
				}
				std::cout << "Found increasing runLength " << runLength << " starting at " << runStart << std::endl;
			} else {
				//Strictly decreasing run
				runLength = 2;
				while (*(begin+(runStart+runLength)-1) > *(begin+(runStart+runLength))) {
					//Grow the run as long as the elements are strictly decreasing
					++runLength;
				}
				std::cout << "Found s_decreasing runLength " << runLength << " starting at " << runStart << std::endl;
				std::cout << "Reversing decreasing run" << std::endl;
				//Since they were strictly decreasing, we can easily reverse them to get an increasing run
				std::reverse((begin+runStart), (begin+runStart+runLength));
			}
			if (runLength < minRunLength) {
				//The run we found isnt big enough
				std::cout << "Run length is " << runLength << " but min is " << minRunLength << ". Calling insertion" << std::endl;
				if (runStart+minRunLength > length) {
					//The run is all the way up to the end
					runLength = length - runStart;
				} else {
					//The run is set equal to the min length
					runLength = minRunLength;
				}
				std::cout << (runStart+runLength)-(runStart) << std::endl;
				//Use insertion sort becase the run wasnt long enough
				InsertionSort::Sort((begin+runStart), (begin+runStart+runLength));
			}
			//The next run starts at the end of this one
			runStart += runLength;
		}
	}
}

#endif //_TIMSORT_HPP