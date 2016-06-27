#include <algorithm>
#include <functional>
#include <vector>

#ifndef _MERGESORT_HPP
#define _MERGESORT_HPP 1

namespace MergeSort {

	enum class MergeType { InPlace, ExtraSpace };

	template<class RandomIt, class Compare>
	void InPlaceMerge(RandomIt first, RandomIt middle, RandomIt end, Compare Comp) {
		while (middle != end) {
			while (first != middle && Comp(*first, *middle)) {
				++first;
			}
			if (first == middle) {
				//All good
				return;
			} else {
				//Need to do a rotate
				//      This moves 'middle' to the position of 'first',
				//      and shifts [first, middle) to the right one
				std::rotate(first, middle, middle+1);
				++first;
				++middle;
			}
		}
	}

	template<class RandomIt, class Compare>
	void ExtraSpaceMerge(RandomIt first, RandomIt middle, RandomIt end, Compare Comp) {
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;

		//Save the left list in a temp because we'll be overwriting it as we insert
		std::vector<ValueType> tempList(first,middle);
		auto leftIt = tempList.begin();
		auto leftEnd = tempList.end();

		RandomIt rightIt = middle;
		RandomIt rightEnd = end;

		RandomIt insertIt = first;

		while (leftIt != leftEnd && rightIt != rightEnd) {
			//While there are elements in both lists
			if (Comp(*leftIt,*rightIt)) {
				//Left list's first element goes first
				*insertIt = *leftIt;
				++leftIt;
			} else {
				//Right list's first element goes first
				*insertIt = *rightIt;
				++rightIt;
			}
			++insertIt;
		}
		//Now at least one list is empty
		if (leftIt != leftEnd) {
			//Insert all of the left list into the list (right is empty)
			std::move(leftIt, leftEnd, insertIt);
		} else if (rightIt != rightEnd) {
			//Insert all of the right list into the list (left is empty)
			std::move(rightIt, rightEnd, insertIt);
		}
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, MergeType mergeType = MergeType::ExtraSpace, Compare Comp = Compare()) {
		std::function<void(RandomIt,RandomIt,RandomIt,Compare)> MergeFunction;
		
		if (mergeType == MergeType::ExtraSpace) {
			MergeFunction = ExtraSpaceMerge<RandomIt,Compare>;
		} else {
			MergeFunction = InPlaceMerge<RandomIt,Compare>;
		}

		size_t length = end-first;

		for (size_t width=1; width<length; width*=2) {
			//We are going to merge lists of length 'width'
			for (size_t listStart=0; listStart<length; listStart+=(width*2)) {
				//These 2 lists are [listStart, listStart+width) and [listStart+width, listStart+(width*2))
				size_t firstPos = listStart;
				size_t middlePos = listStart+width;
				size_t endPos = listStart+(width*2);
				if (middlePos >= length) {
					middlePos = length;
					endPos = length;
				} else if (endPos >= length) {
					endPos = length;
				}
				MergeFunction(first+firstPos, first+middlePos, first+endPos, Comp);
			}
		}
	}
}

#endif //_MERGESORT_HPP