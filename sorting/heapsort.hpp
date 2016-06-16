#include <algorithm>
#include <vector>

namespace HeapSort {
	template<typename RandomIt>
	bool HasChildren(RandomIt first, RandomIt root, RandomIt last) {
		//Return if a left child exists
		auto rootPos = root - first;
		auto length = last - first;
		return (rootPos*2 + 1) < length;
	}

	template<class RandomIt>
	void HeapifyDown(RandomIt first, RandomIt root, RandomIt last) {
		while (HasChildren(first, root, last)) {
			//Sift down until we reach a childless node
			auto rootPos = root - first;
			//Left child definitely exists, check if right child does
			auto leftChildPos = rootPos * 2 + 1;
			auto rightChildPos = leftChildPos + 1;
			bool rightChildIsBigger = false;
			if ((last - (first+rightChildPos)) > 0) {
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
	void Heapify(RandomIt first, RandomIt last) {
		auto length = (last - first);
		//Element at (length/2 - 1) is guaranteed to be the last node with children
		for (auto i=(length/2)-1; i>=0; --i) {
			HeapifyDown(first, first+i, last);
		}
	}

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt last) {
		Heapify(first, last);
		while ((last - first) > 0) {
			//Top of the heap is the greatest, swap it with the back
			std::iter_swap(first, last-1);
			//Step the back down one because that element is now in the sorted position
			--last;
			//Now heapify down the new root element
			HeapifyDown(first, first, last);
		}
	}
}
