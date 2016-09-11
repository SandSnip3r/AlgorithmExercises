#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP 1

#include <algorithm>
#include <functional>
#include <iterator>

namespace InsertionSort {

	template<class BidirIt, class Compare = std::less<>, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//std::distance and std::find_if_not require the passed iterator to be an InputIterator
	//std::rotate requires the passed iterator to be an ForwardIterator
	//std::reverse_iterator requires the passed iterator to be an BidirectionalIterator
	void Sort(BidirIt begin, BidirIt end, Compare Comp = Compare()) {
		if (std::distance(begin,end) < 2) {
			return;
		}

		using RevIt = std::reverse_iterator<BidirIt>;

		for (BidirIt firstUnsorted=std::next(begin); firstUnsorted!=end; ++firstUnsorted) {
			//Find the first element where 'firstUnsorted' is not less than it
			const BidirIt insertionPoint = std::find_if_not(RevIt(firstUnsorted), RevIt(begin), [=](const auto &element) {
				return Comp(*firstUnsorted,element);
			}).base();
			//Rotate to move firstUnsorted into place
			std::rotate(insertionPoint, firstUnsorted, std::next(firstUnsorted));
		}
	}
} //namespace InsertionSort

#endif //INSERTIONSORT_HPP