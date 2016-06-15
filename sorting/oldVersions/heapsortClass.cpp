#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class HeapSort {
private:
	vector<int> data;
	void Heapify();
	void HeapifyDown(int root, int bottom);
	bool HasChildren(int root, int bottom) const;
public:
	HeapSort(vector<int> input);
	void Sort();
};

void HeapSort::Heapify() {
	//Element at (length/2 - 1) is guaranteed to be the last node with children
	for (int i=(data.size()/2)-1; i>=0; --i) {
		HeapifyDown(i, data.size()-1);
	}
}

void HeapSort::HeapifyDown(int root, int bottom) {
	while (HasChildren(root, bottom)) {
		//Sift down until we reach a childless node
		int maxChild = root * 2 + 1;
		//Left child definitely exists, check if right child does
		int rightChildPos = root * 2 + 2;
		if (rightChildPos <= bottom) {
			//Check if right child is bigger
			if (data.at(rightChildPos) > data.at(maxChild)) {
				maxChild = rightChildPos;
			}
		}
		//Now we have the greatest child, check if it's larger than the root
		if (data.at(root) < data.at(maxChild)) {
			//Child is bigger, swap them
			iter_swap(data.begin()+root, data.begin()+maxChild);
			//Set the root now to that child
			root = maxChild;
		} else {
			//Root is already the largest, we're done
			return;
		}
	}
}

bool HeapSort::HasChildren(int root, int bottom) const {
	//Return if a left child exists
	return (root*2 + 1) <= bottom;
}

HeapSort::HeapSort(vector<int> input) : data(input) {}

void HeapSort::Sort() {
	Heapify();
	int endPos = data.size()-1;
	while (endPos >= 0) {
		//Top of the heap is the greatest, swap it with the back
		iter_swap(data.begin(), data.begin()+endPos);
		//Step the back down one because that element is now in the sorted position
		--endPos;
		//Now heapify down the new root element
		HeapifyDown(0, endPos);
	}
	for (auto i : data) {
		cout << i << " ";
	}
	cout << endl;
}

int main() {
	vector<int> inputNumbers;
	
	//Read numbers
	int num;
	while (cin >> num) {
		inputNumbers.emplace_back(num);
	}

	HeapSort heapSort(inputNumbers);
	heapSort.Sort();

	return 0;
}
