#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP 1

#include <algorithm>

namespace SelectionSort {

	template<class ForwardIt, class Compare = std::less<>, typename = std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<ForwardIt>::iterator_category>::value>>
	//std::iter_swap requires the passed iterator to be a ForwardIterator
	void Sort(ForwardIt first, ForwardIt end, Compare Comp = Compare()) {
		while (first != end) {
			std::iter_swap(first, std::min_element(first, end, Comp));
			++first;
		}
	}
} //namespace SelectionSort

#endif //SELECTIONSORT_HPP