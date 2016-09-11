#ifndef INTROSORT_HPP
#define INTROSORT_HPP 1

#include <algorithm>
#include <cmath>
#include <iterator>
#include "heapsort.hpp"
#include "insertionSort.hpp"
#include "quicksort.hpp"

namespace Introsort {

	const size_t SORT_THRESHOLD = 16;

	template<class BidirIt, class Compare, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//std::distance and std::find_if_not require the passed iterator to be an InputIterator
	//std::rotate requires the passed iterator to be an ForwardIterator
	//Heapsort::sort, std::reverse_iterator, and Quicksort::Partition require the passed iterator to be an BidirectionalIterator
	void SortLimitedDepth(BidirIt begin, BidirIt end, int depthLimit, Compare Comp) {
		//This method uses a while loop to continually sort the
		//	left half of the list and recursively sort the right,
		//	rather than recursively sorting both
		while (static_cast<size_t>(std::distance(begin,end)) > SORT_THRESHOLD) {
			//While the length of our list is greater than the specified threshold
			if (depthLimit == 0) {
				//Hit our depth limit(pivot selection was too unbalanced), do heapsort now
				Heapsort::Sort(begin, end, Comp);
				return;
			}
			--depthLimit;
			//Didnt hit the depth limit yet, continue quicksort
			BidirIt partition = Quicksort::Partition(begin, end, Comp);
			SortLimitedDepth(partition, end, depthLimit, Comp);
			end = partition;
		}
	}

	template<class BidirIt, class Compare = std::less<>, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//SortLimitedDepth and InsertionSort::Sort require the passed iterator to be an BidirectionalIterator
	void Sort(BidirIt begin, BidirIt end, Compare Comp = Compare()) {
		size_t length = std::distance(begin,end);

		if (length < 2) {
			return;
		}

		int maxDepth = 2 * static_cast<int>(log2(length));

		//Use Quicksort until it's repeatedly too unbalanced
		//	(maxDepth prevents too many recursions)
		SortLimitedDepth(begin, end, maxDepth, Comp);
		//This leaves unsorted chunks of no more than size 'SORT_THRESHOLD',
		//	insertion sort should do well here
		InsertionSort::Sort(begin, end, Comp);
	}
} //namespace Introsort

#endif //INTROSORT_HPP