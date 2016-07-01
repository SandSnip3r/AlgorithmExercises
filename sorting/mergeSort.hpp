#ifndef MERGESORT_HPP
#define MERGESORT_HPP 1

#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

#include <iostream>

namespace MergeSort {

	enum class MergeType { InPlace, ExtraSpace };

	template<class RandomIt, class Compare>
	void InPlaceMerge(RandomIt begin, RandomIt middle, RandomIt end, Compare Comp) {
		while (middle != end) {
			while (begin != middle && Comp(*begin, *middle)) {
				++begin;
			}
			if (begin == middle) {
				//All good
				return;
			} else {
				//Need to do a rotate
				//	This moves 'middle' to the position of 'begin',
				//	and shifts [begin, middle) to the right one
				std::rotate(begin, middle, middle+1);
				++begin;
				++middle;
			}
		}
	}

	template<class LeftRandomIt, class RightRandomIt, class InsertRandomIt, class Compare>
	void Merge(LeftRandomIt leftBegin, LeftRandomIt leftEnd, RightRandomIt rightBegin, RightRandomIt rightEnd, InsertRandomIt insertionPoint, Compare Comp) {
		while (leftBegin != leftEnd && rightBegin != rightEnd) {
			auto leftValue = *leftBegin;
			auto rightValue = *rightBegin;
			//While there are elements in both lists
			if (Comp(leftValue, rightValue)) {
				//Left list's begin element goes begin
				*insertionPoint = leftValue;
				++leftBegin;
			} else {
				//Right list's begin element goes begin
				*insertionPoint = rightValue;
				++rightBegin;
			}
			++insertionPoint;
		}
		//Now at least one list is empty
		if (leftBegin != leftEnd) {
			//Insert all of the left list into the list (right is empty)
			std::move(leftBegin, leftEnd, insertionPoint);
		} else if (rightBegin != rightEnd) {
			//Insert all of the right list into the list (left is empty)
			std::move(rightBegin, rightEnd, insertionPoint);
		}
	}

	template<class RandomIt, class Compare>
	void MergeLeft(RandomIt begin, RandomIt middle, RandomIt end, Compare Comp) {
		//Merging the right into the place of the left (left is smaller)
		
		//Determine if there are any leftmost positions that are already in place
		RandomIt newLeftBegin = std::upper_bound(begin, middle, *middle, Comp);
		if (newLeftBegin == middle) {
			//Everything in the left list is smaller than the first in the right list, we're done
			return;
		}

		// newLeftBegin saved std::distance(begin, newLeftBegin)*sizeof(RandomIt) bytes of extra space usage
		//Save the left list in a temp because we'll be overwriting it as we insert
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;
		std::vector<ValueType> tempList(newLeftBegin, middle);
		auto leftIt = tempList.begin();
		auto leftEnd = tempList.end();

		RandomIt rightIt = middle;
		RandomIt rightEnd = end;

		RandomIt insertIt = newLeftBegin;

		Merge(leftIt, leftEnd, rightIt, rightEnd, insertIt, Comp);
	}

	template<class RandomIt, class Compare>
	void MergeRight(RandomIt begin, RandomIt middle, RandomIt end, Compare Comp) {
		//Merging the left into the place of the right (right is smaller)
		
		using RevIt = std::reverse_iterator<RandomIt>;

		//Save the left list in a temp because we'll be overwriting it as we insert
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;
		std::vector<ValueType> tempList(middle, end);
		auto rightIt = std::reverse_iterator<typename std::vector<ValueType>::iterator>(tempList.end());
		auto rightEnd = std::reverse_iterator<typename std::vector<ValueType>::iterator>(tempList.begin());

		RevIt leftIt = RevIt(middle);
		RevIt leftEnd = RevIt(begin);

		RevIt insertIt = RevIt(end);

		auto NewComp = [&Comp](const auto &a, const auto &b) -> bool {
			return Comp(b, a);
		};

		Merge(leftIt, leftEnd, rightIt, rightEnd, insertIt, NewComp);
	}

	template<class RandomIt, class Compare>
	void Merge(RandomIt begin, RandomIt middle, RandomIt end, Compare Comp) {
		size_t leftLength = std::distance(begin, middle);
		size_t rightLength = std::distance(middle, end);

		//MergeLeft or MergeRight depending on whether the
		//	left or right is smaller
		if (leftLength <= rightLength) {
			MergeLeft(begin, middle, end, Comp);
		} else {
			MergeRight(begin, middle, end, Comp);
		}
	}

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt begin, RandomIt end, MergeType mergeType = MergeType::ExtraSpace, Compare Comp = Compare()) {
		std::function<void(RandomIt,RandomIt,RandomIt,Compare)> MergeFunction;
		
		if (mergeType == MergeType::ExtraSpace) {
			MergeFunction = Merge<RandomIt,Compare>;
		} else {
			MergeFunction = InPlaceMerge<RandomIt,Compare>;
		}

		size_t length = std::distance(begin,end);

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
				MergeFunction(begin+firstPos, begin+middlePos, begin+endPos, Comp);
			}
		}
	}
} //namespace MergeSort

#endif //MERGESORT_HPP