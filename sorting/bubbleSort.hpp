#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP 1

#include <algorithm>

namespace BubbleSort {

	template<class ForwardIt, class Compare = std::less<>, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<ForwardIt>::iterator_category>::value>>
	//std::distance and std::next require the passed iterator to be an InputIterator
	//std::iter_swap requires the passed iterator to be a ForwardIterator
	void Sort(ForwardIt begin, ForwardIt end, Compare Comp = Compare()) {
		auto unsortedLength = std::distance(begin, end);

		while (unsortedLength > 1) {
			//A potentially unsorted list exists with length at least 2
			ForwardIt leftIt = begin;
			ForwardIt rightIt = std::next(begin);
			auto newUnsortedLength = 0;
			for (decltype(unsortedLength) i=1; i<unsortedLength; ++i) {
				if (Comp(*rightIt, *leftIt)) {
					//need to swap because 'leftIt' belongs to the right of 'rightIt'
					std::iter_swap(leftIt, rightIt);
					newUnsortedLength = i;
				}
				++leftIt;
				++rightIt;
			}
			unsortedLength = newUnsortedLength;
		}
	}
}

#endif //BUBBLESORT_HPP