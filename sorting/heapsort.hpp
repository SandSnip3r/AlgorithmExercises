#include <algorithm>
#include <vector>

namespace HeapSort {
	template<class RandomIt>
	void Sort(RandomIt first, RandomIt last);
	template<typename IntType>
	bool HasChildren(IntType root, IntType bottom) {
		//Return if a left child exists
		return (root*2 + 1) <= bottom;
	}

	template<class RandomIt, typename IntType>
	void HeapifyDown(RandomIt first, IntType root, IntType bottom) {
		while (HasChildren(root, bottom)) {
			//Sift down until we reach a childless node
			auto maxChild = root * 2 + 1;
			//Left child definitely exists, check if right child does
			auto rightChildPos = root * 2 + 2;
			if (rightChildPos <= bottom) {
				//Check if right child is bigger
				if (*(first+rightChildPos) > *(first+maxChild)) {
					maxChild = rightChildPos;
				}
			}
			//Now we have the greatest child, check if it's larger than the root
			if (*(first+root) < *(first+maxChild)) {
				//Child is bigger, swap them
				std::iter_swap((first+root), (first+maxChild));
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
		auto length = std::distance(first, last);
		//Element at (length/2 - 1) is guaranteed to be the last node with children
		for (auto i=(length/2)-1; i>=0; --i) {
			HeapifyDown(first, i, length-1);
		}
	}

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt last) {
		Heapify(first, last);

		auto endPos = std::distance(first, last) - 1;
		while (endPos >= 0) {
			//Top of the heap is the greatest, swap it with the back
			std::iter_swap(first, first+endPos);
			//Step the back down one because that element is now in the sorted position
			--endPos;
			//Now heapify down the new root element
			HeapifyDown(first, 0l, endPos);
		}
	}
}
