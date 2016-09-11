#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP 1

#include <algorithm>
#include <iterator>

namespace Heapsort {
	template<typename InputIt, typename = std::enable_if_t<std::is_base_of<std::input_iterator_tag, typename std::iterator_traits<InputIt>::iterator_category>::value>>
	//std::distance requires the passed iterator to be an InputIterator
	bool HasChildren(InputIt begin, InputIt root, InputIt end) {
		//Return whether a left child exists or not
		size_t rootPos = std::distance(begin, root);
		size_t length = std::distance(begin, end);

		return (rootPos*2 + 1) < length;
	}

	template<class ForwardIt, class Compare, typename = std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<ForwardIt>::iterator_category>::value>>
	//std::distance, std::next, and HasChildren require the passed iterator to be an InputIterator
	//std::iter_swap requires the passed iterator to be a ForwardIterator
	void HeapifyDown(ForwardIt begin, ForwardIt root, ForwardIt end, Compare Comp) {
		while (HasChildren(begin, root, end)) {
			//Sift down until we reach a childless node
			size_t rootPos = std::distance(begin, root);
			//Left child definitely exists, check if right child does
			size_t leftChildPos = rootPos * 2 + 1;
			size_t rightChildPos = leftChildPos + 1;
			bool rightChildIsBigger = false;
			if (std::distance(std::next(begin, rightChildPos), end) > 0) {
				//Right child exists, check if it is bigger
				if (Comp(*std::next(begin, leftChildPos), *std::next(begin, rightChildPos))) {
					rightChildIsBigger = true;
				}
			}
			size_t maxChildPos = (rightChildIsBigger ? rightChildPos : leftChildPos);
			ForwardIt maxChild = std::next(begin, maxChildPos);
			//Now we have the greatest child, check if it's larger than the root
			if (Comp(*root,*maxChild)) {
				//Child is bigger, swap them
				std::iter_swap(root, maxChild);
				//Set the root now to that child
				root = maxChild;
			} else {
				//Root is already the largest, we're done
				return;
			}
		}
	}

	template<class ForwardIt, class Compare, typename = std::enable_if_t<std::is_base_of<std::forward_iterator_tag, typename std::iterator_traits<ForwardIt>::iterator_category>::value>>
	//std::distance and std::next require the passed iterator to be an InputIterator
	//HeapifyDown requires the passed iterator to be a ForwardIterator
	void Heapify(ForwardIt begin, ForwardIt end, Compare Comp) {
		size_t length = std::distance(begin, end);

		//Element at (length/2 - 1) is guaranteed to be the last node with children
		for (int i=(length/2)-1; i>=0; --i) {
			HeapifyDown(begin, std::next(begin, i), end, Comp);
		}
	}

	template<class BidirIt, class Compare = std::less<>, typename = std::enable_if_t<std::is_base_of<std::bidirectional_iterator_tag, typename std::iterator_traits<BidirIt>::iterator_category>::value>>
	//std::distance requires the passed iterator to be an InputIterator
	//HeapifyDown requires the passed iterator to be a ForwardIterator
	//std::prev and iterator decrement require the passed iterator to be an BidirectionalIterator
	void Sort(BidirIt begin, BidirIt end, Compare Comp = Compare()) {
		Heapify(begin, end, Comp);

		while (std::distance(begin, end) > 0) {
			//Top of the heap is the greatest, swap it with the back
			BidirIt last = std::prev(end);
			std::iter_swap(begin, last);
			//Step the back down one because that element is now in the sorted position
			--end;
			//Now heapify down the new root element
			HeapifyDown(begin, begin, end, Comp);
		}
	}
}

#endif //HEAPSORT_HPP