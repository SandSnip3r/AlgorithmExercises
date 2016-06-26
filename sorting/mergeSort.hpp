#include <algorithm>
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
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;

		DiffType length = end-first;
		RandomIt leftIt = first;
		RandomIt rightIt = middle;

		std::vector<ValueType> tempList;
		tempList.reserve(length);

		while (leftIt != middle && rightIt != end) {
			//While there are elements in both lists
			if (Comp(*leftIt,*rightIt)) {
				//Left list's first element goes first
				tempList.emplace_back(*leftIt);
				++leftIt;
			} else {
				//Right list's first element goes first
				tempList.emplace_back(*rightIt);
				++rightIt;
			}
		}
		//Now at least one list is empty
		if (leftIt != middle) {
			//Insert all of the left list into the list (right is empty)
			std::move(leftIt, middle, std::back_inserter(tempList));
		} else if (rightIt != end) {
			//Insert all of the right list into the list (left is empty)
			std::move(rightIt, end, std::back_inserter(tempList));
		}
		//Move temp into the given container
		std::move(tempList.begin(), tempList.end(), first);
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, MergeType mergeType = MergeType::ExtraSpace, Compare Comp = Compare()) {
		std::function<void(RandomIt,RandomIt,RandomIt,Compare)> MergeFunction;
		
		if (mergeType == MergeType::ExtraSpace) {
			MergeFunction = ExtraSpaceMerge<RandomIt,Compare>;
		} else {
			MergeFunction = InPlaceMerge<RandomIt,Compare>;
		}

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
				MergeFunction(first+firstPos, first+middlePos, first+endPos, Comp);
			}
		}
	}
}

#endif //_MERGESORT_HPP