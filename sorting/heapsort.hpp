#include <algorithm>
#include <vector>

#ifndef _HEAPSORT_HPP
#define _HEAPSORT_HPP 1

namespace HeapSort {
	template<typename RandomIt>
	bool HasChildren(RandomIt first, RandomIt root, RandomIt end) {
		//Return if a left child exists
		auto rootPos = root - first;
		auto length = end - first;
		return (rootPos*2 + 1) < length;
	}

	template<class RandomIt>
	void HeapifyDown(RandomIt first, RandomIt root, RandomIt end) {
		while (HasChildren(first, root, end)) {
			//Sift down until we reach a childless node
			auto rootPos = root - first;
			//Left child definitely exists, check if right child does
			auto leftChildPos = rootPos * 2 + 1;
			auto rightChildPos = leftChildPos + 1;
			bool rightChildIsBigger = false;
			if ((end - (first+rightChildPos)) > 0) {
				//Check if right child is bigger
				if (*(first+rightChildPos) > *(first+leftChildPos)) {
					rightChildIsBigger = true;
				}
			}
			auto maxChildPos = (rightChildIsBigger ? rightChildPos : leftChildPos);
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
		auto length = (end - first);
		//Element at (length/2 - 1) is guaranteed to be the last node with children
		for (auto i=(length/2)-1; i>=0; --i) {
			HeapifyDown(first, first+i, end);
		}
	}

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt end) {
		Heapify(first, end);
		while ((end - first) > 0) {
			//Top of the heap is the greatest, swap it with the back
			auto last = end-1;
			std::iter_swap(first, last);
			//Step the back down one because that element is now in the sorted position
			--end;
			//Now heapify down the new root element
			HeapifyDown(first, first, end);
		}
	}
}

#endif //_HEAPSORT_HPP