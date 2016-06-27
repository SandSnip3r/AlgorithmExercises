#include <algorithm>
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
		//Take the six most significant bits of the size of the array,
		//	adds one if any of the remaining bits are set, and uses
		//	that result as the minrun. This algorithm works for all arrays,
		//	including those smaller than 64.
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
	size_t FindExistingRunLength(RandomIt begin, RandomIt end, Compare Comp) {
		size_t length = end-begin;
		if (length < 2) {
			return length;
		}
		size_t runLength = 2; //guaranteed
		RandomIt runIt = begin;
		if (!Comp(*(runIt+1), *(runIt))) {
			//Increasing run
			runIt += runLength;
			while (runIt != end && !Comp(*(runIt), *(runIt-1))) {
				//Grow the run as long as the elements are increasing
				++runIt;
				++runLength;
			}
		} else {
			//Strictly decreasing run
			runIt += runLength;
			while (runIt != end && Comp(*(runIt), *(runIt-1))) {
				//Grow the run as long as the elements are strictly decreasing
				++runIt;
				++runLength;
			}
			//Since they were strictly decreasing, we can easily reverse them to get an increasing run
			std::reverse(begin, runIt);
		}
		return runLength;
	}

	template<class RandomIt, class Compare>
	void MaintainStackInvariants(std::stack<Run<RandomIt>> *runStack, Compare Comp) {
		while (runStack->size() >= 3) {
			Run<RandomIt> a = runStack->top();
			runStack->pop();
			Run<RandomIt> b = runStack->top();
			runStack->pop();
			Run<RandomIt> c = runStack->top();
			runStack->pop();

			if ((a.length<=(b.length+c.length)) || (b.length<=c.length)) {
				//Invariant fails
				if (a.length < c.length) {
					//Merge a and b
					size_t totalLength = a.length+b.length;
					MergeSort::ExtraSpaceMerge(b.begin, b.begin+b.length, b.begin+totalLength, Comp);
					runStack->push(c);
					runStack->emplace(b.begin, totalLength);
				} else {
					//Merge b and c
					//	ties favor c
					size_t totalLength = b.length+c.length;
					MergeSort::ExtraSpaceMerge(c.begin, c.begin+c.length, c.begin+totalLength, Comp);
					runStack->emplace(c.begin, totalLength);
					runStack->push(a);
				}
			}
		}
	}

	template<class RandomIt, class Compare>
	void MergeRemainingOnStack(std::stack<Run<RandomIt>> *runStack, Compare Comp) {
		while (runStack->size() >= 2) {
			Run<RandomIt> a = runStack->top();
			runStack->pop();
			Run<RandomIt> b = runStack->top();
			runStack->pop();

			size_t totalLength = a.length+b.length;
			MergeSort::ExtraSpaceMerge(b.begin, b.begin+b.length, b.begin+totalLength, Comp);
			runStack->emplace(b.begin, totalLength);
		}
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt begin, RandomIt end, Compare Comp = Compare()) {
		size_t length = end-begin;
		const size_t minRunLength = CalculateMinrun(length);

		std::stack<Run<RandomIt>> runStack;

		size_t runStart = 0;

		while (runStart < length) {
			//More array remaining
			size_t runLength = FindExistingRunLength(begin+runStart, end, Comp);
			if (runLength < minRunLength) {
				//Run isnt long enough
				if ((runStart+minRunLength) < length) {
					//There are at least minRunLength elements remaining
					runLength = minRunLength;
				} else {
					//There are less than minRunLength elements remaining
					runLength = length-runStart;
				}
				//Use insertion sort becase the run wasnt long enough
				InsertionSort::Sort(begin+runStart, begin+runStart+runLength, Comp);
			}
			//Push the current run onto the stack
			runStack.emplace(begin+runStart, runLength);
			//Ensure the stack invariants are maintained
			MaintainStackInvariants(&runStack, Comp);
			//Increase the start to after this run
			runStart += runLength;
		}

		MergeRemainingOnStack(&runStack, Comp);
	}
}

#endif //_TIMSORT_HPP