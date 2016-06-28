#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP 1

#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

namespace InsertionSort {

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt begin, RandomIt end, Compare Comp = Compare()) {
		if (std::distance(begin,end) < 2) {
			return;
		}

		using RevIt = std::reverse_iterator<RandomIt>;

		for (RandomIt firstUnsorted=std::next(begin); firstUnsorted!=end; ++firstUnsorted) {
			//Find the first element where 'firstUnsorted' is not less than it
			const RandomIt insertionPoint = std::find_if_not(RevIt(firstUnsorted), RevIt(begin), [=](const auto &element) {
				return Comp(*firstUnsorted,element);
			}).base();
			//Rotate to move firstUnsorted into place
			std::rotate(insertionPoint, firstUnsorted, std::next(firstUnsorted));
		}
	}
} //namespace InsertionSort

#endif //INSERTIONSORT_HPP