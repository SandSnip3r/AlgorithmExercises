#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP 1

#include <algorithm>

namespace BubbleSort {

	template<class ForwardIt, class Compare = std::less<>, typename = std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<ForwardIt>::iterator_category>::value>>
	//std::distance, std::next, and std::prev require the passed iterator to be an InputIterator
	//std::iter_swap requires the passed iterator to be a ForwardIterator
	void Sort(ForwardIt begin, ForwardIt end, Compare Comp = Compare()) {
		ForwardIt tempEnd = end;

		while (std::distance(begin, tempEnd) > 1) {
			//A potentially unsorted list exist [begin,tempEnd) with length at least 2
			ForwardIt it = std::next(begin);
			ForwardIt newTempEnd = std::prev(tempEnd);
			while (it != tempEnd) {
				ForwardIt previousIt = std::prev(it);
				if (Comp(*it, *previousIt)) {
					//need to swap because 'previousIt' belongs to the right of 'it'
					std::iter_swap(it, previousIt);
					newTempEnd = std::next(it);
				}
				++it;
			}
			//move the end to the left up until the most recent swap
			tempEnd = newTempEnd;
		}
	}
}

#endif //BUBBLESORT_HPP