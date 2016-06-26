#include <algorithm>
#include <iostream>
#include <stack>
#include "insertionSort.hpp"
#include "mergeSort.hpp"

#ifndef _TIMSORT_HPP
#define _TIMSORT_HPP 1

namespace Timsort {

	template<class RandomIt>
	struct Run {
		RandomIt begin;
		size_t length;
		Run(RandomIt b, size_t l) : begin(b), length(l) {};
	};

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

	template<class RandomIt, class Compare>
	size_t FindExistingRunLength(RandomIt begin, Compare Comp) {
		size_t runLength = 2; //guaranteed
		if (!Comp(*(begin+1), *(begin))) {
			//Increasing run
			while (!Comp(*(begin+runLength), *(begin+runLength-1))) {
				//Grow the run as long as the elements are increasing
				++runLength;
			}
		} else {
			//Strictly decreasing run
			while (Comp(*(begin+runLength), *(begin+runLength-1))) {
				//Grow the run as long as the elements are strictly decreasing
				++runLength;
			}
			// std::cout << "Reversing decreasing run of length " << runLength << std::endl;
			//Since they were strictly decreasing, we can easily reverse them to get an increasing run
			std::reverse(begin, (begin+runLength));
		}
		return runLength;
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt begin, RandomIt end, Compare Comp = Compare()) {
		size_t length = end-begin;
		const size_t minRunLength = CalculateMinrun(length);

		std::stack<Run<RandomIt>> runStack;

		size_t runStart = 0;
		size_t runLength = 0;
		while (runStart < length-1) {
			//Creating new run
			runLength = FindExistingRunLength(begin+runStart, Comp);

			if (runLength < minRunLength) {
				//The run we found isnt big enough
				if (runStart+minRunLength > length) {
					//The run is all the way up to the end
					runLength = length - runStart;
				} else {
					//The run is set equal to the min length
					runLength = minRunLength;
				}
				// std::cout << "Length " << (runStart+runLength)-(runStart) << std::endl;
				//Use insertion sort becase the run wasnt long enough
				InsertionSort::Sort((begin+runStart), (begin+runStart+runLength), Comp);
			}

			//New run is complete, put it on the stack
			// std::cout << "Pushing new run starting at " << *(begin+runStart) << " len " << runLength << std::endl;
			runStack.emplace((begin+runStart), runLength);
			//Merge any on the top of the stack if necessary
			//	this point of merging makes it more likely that runs will be merged
			//	while they are still in cache.
			// std::cout << "Pre-while stack size " << runStack.size() << std::endl;
			while (runStack.size() >= 3) {
				Run<RandomIt> a = runStack.top();
				runStack.pop();
				Run<RandomIt> b = runStack.top();
				runStack.pop();
				Run<RandomIt> c = runStack.top();
				runStack.pop();
				if (a.length + b.length > c.length) {
					size_t newLength = c.length+b.length;
					// std::cout << "Should merge b and c. B:" << *(b.begin) << "," << b.length << " & C:" << *(c.begin) << "," << c.length << std::endl;
					MergeSort::ExtraSpaceMerge(c.begin, c.begin+c.length, c.begin+newLength, Comp);
					if (!std::is_sorted(c.begin, c.begin+newLength, Comp)) {
						// std::cout << "(b and c) merge failed!" << std::endl;
					}
					runStack.emplace(c.begin, newLength);
					runStack.push(a);
				} else if (a.length > b.length) {
					size_t newLength = b.length+a.length;
					// std::cout << "Should merge a and b. A:" << *(a.begin) << "," << a.length << " & B:" << *(b.begin) << "," << b.length << std::endl;
					MergeSort::ExtraSpaceMerge(b.begin, b.begin+b.length, b.begin+newLength, Comp);
					if (!std::is_sorted(b.begin, b.begin+newLength, Comp)) {
						// std::cout << "(a and b) merge failed!" << std::endl;
					}
					runStack.push(c);
					runStack.emplace(b.begin, newLength);
				} else {
					//Condition not met
					// std::cout << "Conditions not met" << std::endl;
					runStack.push(c);
					runStack.push(b);
					runStack.push(a);
					break;
				}
			}
			// std::cout << "Post-while stack size " << runStack.size() << std::endl;
			//The next run starts at the end of this one
			runStart += runLength;
		}
		if (runStack.empty()) {
			// std::cout << "Seems all went well" << std::endl;
		} else {
			// std::cout << "Dumping run stack" << std::endl;
			while (runStack.size() >= 2) {
				//Merge everything remaining
				Run<RandomIt> a = runStack.top();
				runStack.pop();
				Run<RandomIt> b = runStack.top();
				runStack.pop();
				size_t newLength = a.length+b.length;
				MergeSort::ExtraSpaceMerge(b.begin, b.begin+b.length, b.begin+newLength, Comp);
				runStack.emplace(b.begin, newLength);
			}
		}
	}
}

#endif //_TIMSORT_HPP