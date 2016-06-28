#ifndef MERGESORT_HPP
#define MERGESORT_HPP 1

#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

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
				//      This moves 'middle' to the position of 'begin',
				//      and shifts [begin, middle) to the right one
				std::rotate(begin, middle, middle+1);
				++begin;
				++middle;
			}
		}
	}

	template<class RandomIt, class Compare>
	void ExtraSpaceMerge(RandomIt begin, RandomIt middle, RandomIt end, Compare Comp) {
		using ValueType = typename std::iterator_traits<RandomIt>::value_type;

		//Save the left list in a temp because we'll be overwriting it as we insert
		std::vector<ValueType> tempList(begin,middle);
		auto leftIt = tempList.begin();
		auto leftEnd = tempList.end();

		RandomIt rightIt = middle;
		RandomIt rightEnd = end;

		RandomIt insertIt = begin;

		while (leftIt != leftEnd && rightIt != rightEnd) {
			//While there are elements in both lists
			if (Comp(*leftIt,*rightIt)) {
				//Left list's begin element goes begin
				*insertIt = *leftIt;
				++leftIt;
			} else {
				//Right list's begin element goes begin
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

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt begin, RandomIt end, MergeType mergeType = MergeType::ExtraSpace, Compare Comp = Compare()) {
		std::function<void(RandomIt,RandomIt,RandomIt,Compare)> MergeFunction;
		
		if (mergeType == MergeType::ExtraSpace) {
			MergeFunction = ExtraSpaceMerge<RandomIt,Compare>;
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