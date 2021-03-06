#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP 1

#include <algorithm>
#include <iterator>
#include <vector>

namespace Quicksort {
	template<class InputIt, class Compare, typename = std::enable_if_t<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>>
	InputIt GetMedian(InputIt begin, InputIt middle, InputIt last, Compare Comp) {
		if (middle == last) {
			//If there are 2 elements, there isnt really a middle
			//	there's either 1 or 2 elements
			return last;
		}

		auto beginValue = *begin;
		auto middleValue = *middle;
		auto lastValue = *last;

		if (!Comp(lastValue, middleValue) && !Comp(middleValue, beginValue)) {
			//middle is the median
			return middle;
		} else if (!Comp(lastValue, beginValue) && !Comp(beginValue, middleValue)) {
			//begin is the median
			return begin;
		} else {
			//last must be the median
			return last;
		}
	}

	template<class BidirIt, class Compare, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//std::distance, std::next, and GetMedian require the passed iterator to be an InputIterator
	//std::iter_swap requires the passed iterator to be a ForwardIterator
	//std::prev requires the passed iterator to be an BidirectionalIterator
	BidirIt Partition(BidirIt begin, BidirIt end, Compare Comp) {
		size_t length = std::distance(begin,end);
		auto middle = std::next(begin, length/2);

		auto left = std::prev(begin);
		auto right = end;

		//For the pivot, use the median of the begin, right, and middle element
		auto pivotValue = *GetMedian(begin, middle, std::prev(end), Comp);
		while (1) {
			do {
				++left;
			} while (left != right && Comp(*left, pivotValue));

			if (left == right) {
				//The left and right iterators have crossed eachother
				//	everything is now on the correct side of the pivot
				return left;
			}

			do {
				--right;
			} while (left != right && Comp(pivotValue, *right));

			if (left == right) {
				//The left and right iterators have crossed eachother
				//	everything is now on the correct side of the pivot
				return left;
			}
			//Both left and right are on opposite sides
			//	of the pivot that they should be
			std::iter_swap(left,right);
		}
	}

	template<class BidirIt, class Compare = std::less<>, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//std::distance requires the passed iterator to be an InputIterator
	//Partition requires the passed iterator to be an BidirectionalIterator
	void Sort(BidirIt begin, BidirIt end, Compare Comp = Compare()) {
		while (std::distance(begin,end) > 1) {
			//At least 2 elements to sort
			auto partition = Partition(begin, end, Comp);
			Sort(partition, end, Comp);
			end = partition;
		}
	}
}

#endif //QUICKSORT_HPP