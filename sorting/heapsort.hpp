#include <algorithm>
#include <vector>

#ifndef _HEAPSORT_HPP
#define _HEAPSORT_HPP 1

namespace Heapsort {
	template<typename RandomIt>
	bool HasChildren(RandomIt first, RandomIt root, RandomIt end) {
		//Return whether a left child exists or not
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;

		DiffType rootPos = root - first;
		DiffType length = end - first;

		return (rootPos*2 + 1) < length;
	}

	template<class RandomIt, class Compare>
	void HeapifyDown(RandomIt first, RandomIt root, RandomIt end, Compare Comp) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;

		while (HasChildren(first, root, end)) {
			//Sift down until we reach a childless node
			DiffType rootPos = root - first;
			//Left child definitely exists, check if right child does
			DiffType leftChildPos = rootPos * 2 + 1;
			DiffType rightChildPos = leftChildPos + 1;
			bool rightChildIsBigger = false;
			if ((end - (first+rightChildPos)) > 0) {
				//Right child exists, check if it is bigger
				if (Comp(*(first+leftChildPos), *(first+rightChildPos))) {
					rightChildIsBigger = true;
				}
			}
			DiffType maxChildPos = (rightChildIsBigger ? rightChildPos : leftChildPos);
			RandomIt maxChild = first + maxChildPos;
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
	void Heapify(RandomIt first, RandomIt end, Compare Comp) {
		using DiffType = typename std::iterator_traits<RandomIt>::difference_type;

		DiffType length = (end - first);

		//Element at (length/2 - 1) is guaranteed to be the last node with children
		for (DiffType i=(length/2)-1; i>=0; --i) {
			HeapifyDown(first, first+i, end, Comp);
		}
	}

	template<class RandomIt, class Compare = std::less<typename std::iterator_traits<RandomIt>::value_type>>
	void Sort(RandomIt first, RandomIt end, Compare Comp = Compare()) {
		Heapify(first, end, Comp);
		
		while ((end - first) > 0) {
			//Top of the heap is the greatest, swap it with the back
			RandomIt last = end-1;
			std::iter_swap(first, last);
			//Step the back down one because that element is now in the sorted position
			--end;
			//Now heapify down the new root element
			HeapifyDown(first, first, end, Comp);
		}
	}
}

#endif //_HEAPSORT_HPP