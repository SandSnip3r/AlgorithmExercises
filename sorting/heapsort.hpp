#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP 1

#include <algorithm>
#include <iterator>

namespace Heapsort {
	template<typename RandomIt>
	bool HasChildren(RandomIt begin, RandomIt root, RandomIt end) {
		//Return whether a left child exists or not
		size_t rootPos = std::distance(begin, root);
		size_t length = std::distance(begin, end);

		return (rootPos*2 + 1) < length;
	}

	template<class RandomIt, class Compare>
	void HeapifyDown(RandomIt begin, RandomIt root, RandomIt end, Compare Comp) {
		while (HasChildren(begin, root, end)) {
			//Sift down until we reach a childless node
			size_t rootPos = std::distance(begin, root);
			//Left child definitely exists, check if right child does
			size_t leftChildPos = rootPos * 2 + 1;
			size_t rightChildPos = leftChildPos + 1;
			bool rightChildIsBigger = false;
			if ((end - (begin+rightChildPos)) > 0) {
				//Right child exists, check if it is bigger
				if (Comp(*(begin+leftChildPos), *(begin+rightChildPos))) {
					rightChildIsBigger = true;
				}
			}
			size_t maxChildPos = (rightChildIsBigger ? rightChildPos : leftChildPos);
			RandomIt maxChild = begin + maxChildPos;
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

	template<class RandomIt, class Compare>
	void Heapify(RandomIt begin, RandomIt end, Compare Comp) {
		size_t length = std::distance(begin, end);

		//Element at (length/2 - 1) is guaranteed to be the last node with children
		for (int i=(length/2)-1; i>=0; --i) {
			HeapifyDown(begin, begin+i, end, Comp);
		}
	}

	template<class RandomIt, class Compare = std::less<>>
	void Sort(RandomIt begin, RandomIt end, Compare Comp = Compare()) {
		Heapify(begin, end, Comp);
		
		while (std::distance(begin, end) > 0) {
			//Top of the heap is the greatest, swap it with the back
			RandomIt last = std::prev(end);
			std::iter_swap(begin, last);
			//Step the back down one because that element is now in the sorted position
			--end;
			//Now heapify down the new root element
			HeapifyDown(begin, begin, end, Comp);
		}
	}
}

#endif //HEAPSORT_HPP