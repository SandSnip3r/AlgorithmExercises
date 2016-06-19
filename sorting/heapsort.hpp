#include <algorithm>
#include <vector>

#ifndef _HEAPSORT_HPP
#define _HEAPSORT_HPP 1

namespace Heapsort {
	template<typename RandomIt>
	bool HasChildren(RandomIt first, RandomIt root, RandomIt end) {
		//Return if a left child exists
		typename std::iterator_traits<RandomIt>::difference_type rootPos = root - first;
		typename std::iterator_traits<RandomIt>::difference_type length = end - first;
		return (rootPos*2 + 1) < length;
	}

	template<class RandomIt>
	void HeapifyDown(RandomIt first, RandomIt root, RandomIt end) {
		while (HasChildren(first, root, end)) {
			//Sift down until we reach a childless node
			typename std::iterator_traits<RandomIt>::difference_type rootPos = root - first;
			//Left child definitely exists, check if right child does
			typename std::iterator_traits<RandomIt>::difference_type leftChildPos = rootPos * 2 + 1;
			typename std::iterator_traits<RandomIt>::difference_type rightChildPos = leftChildPos + 1;
			bool rightChildIsBigger = false;
			if ((end - (first+rightChildPos)) > 0) {
				//Check if right child is bigger
				if (*(first+rightChildPos) > *(first+leftChildPos)) {
					rightChildIsBigger = true;
				}
			}
			typename std::iterator_traits<RandomIt>::difference_type maxChildPos = (rightChildIsBigger ? rightChildPos : leftChildPos);
			RandomIt maxChild = first + maxChildPos;
			//Now we have the greatest child, check if it's larger than the root
			if (*root < *maxChild) {
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

	template<class RandomIt>
	void Heapify(RandomIt first, RandomIt end) {
		typename std::iterator_traits<RandomIt>::difference_type length = (end - first);
		//Element at (length/2 - 1) is guaranteed to be the last node with children
		for (typename std::iterator_traits<RandomIt>::difference_type i=(length/2)-1; i>=0; --i) {
			HeapifyDown(first, first+i, end);
		}
	}

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt end) {
		Heapify(first, end);
		while ((end - first) > 0) {
			//Top of the heap is the greatest, swap it with the back
			RandomIt last = end-1;
			std::iter_swap(first, last);
			//Step the back down one because that element is now in the sorted position
			--end;
			//Now heapify down the new root element
			HeapifyDown(first, first, end);
		}
	}
}

#endif //_HEAPSORT_HPP