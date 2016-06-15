#include <algorithm>
#include <vector>

namespace QuickSort {
	template<class RandomIt>
	RandomIt Partition(RandomIt first, RandomIt last) {
		--last;
		auto pivot = *last;
		while (1) {
			while (*first < pivot) {
				++first;
			}
			while (*last > pivot) {
				--last;
			}
			if (std::distance(first, last) <= 0) {
				return first;
			}
			std::iter_swap(first,last);
			++first;
			--last;
		}
	}

	template<class RandomIt>
	void Sort(RandomIt first, RandomIt last) {
		auto length = std::distance(first, last);
		if (length > 1) {
			//At least 2 elements to sort
			RandomIt partition = Partition(first, last);
			Sort(first, partition);
			Sort(partition, last);
		}
	}
}
