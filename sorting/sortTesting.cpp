#include <chrono>
#include <vector>
#include "heapsort.hpp"
#include "insertionsort.hpp"
#include "introsort.hpp"
#include "quicksort.hpp"
#include "timeUtility.hpp"

using namespace std;

void CreateRandomData(vector<int> *numbers, int dataLength, pair<int,int> dataRange);

int main() {
	for (int dataLength : { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000 }) {
		for (pair<int,int> dataRange : { 	pair<int,int>{1,1},
																			pair<int,int>{1,10}, 
																			pair<int,int>{1,100}, 
																			pair<int,int>{1,1000}, 
																			pair<int,int>{1,1000000} }) {
			vector<int> numbers;
			for (int i=0; i<dataLength; ++i) {
				numbers.emplace_back(i);
			}
			// CreateRandomData(&numbers, dataLength, dataRange);
			typedef chrono::nanoseconds DurationType;
			
			vector<int> stdNumbers(numbers);
			DurationType stdSortDuration;
			{
				Timer<DurationType> timer(&stdSortDuration);
				sort(stdNumbers.begin(), stdNumbers.end());
				//Timer's destruction will set duration
			}
			
			DurationType heapSortDuration;
			{
				vector<int> heapSortTempNumbers(numbers);
				{
					Timer<DurationType> timer(&heapSortDuration);
					HeapSort::Sort(heapSortTempNumbers.begin(), heapSortTempNumbers.end());
					//Timer's destruction will set duration
				}
				if (stdNumbers != heapSortTempNumbers) {
					throw runtime_error("heap sort failed!");
				}
			}
			
			DurationType quickSortDuration;
			{
				vector<int> quickSortTempNumbers(numbers);
				{
					Timer<DurationType> timer(&quickSortDuration);
					QuickSort::Sort(quickSortTempNumbers.begin(), quickSortTempNumbers.end());
					//Timer's destruction will set duration
				}
				if (stdNumbers != quickSortTempNumbers) {
					throw runtime_error("quick sort failed!");
				}
			}
			
			DurationType introSortDuration;
			{
				vector<int> introSortTempNumbers(numbers);
				{
					Timer<DurationType> timer(&introSortDuration);
					IntroSort::Sort(introSortTempNumbers.begin(), introSortTempNumbers.end());
					//Timer's destruction will set duration
				}
				if (stdNumbers != introSortTempNumbers) {
					throw runtime_error("intro sort failed!");
				}
			}
			
			DurationType insertionSortDuration;
			{
				vector<int> insertionSortTempNumbers(numbers);
				{
					Timer<DurationType> timer(&insertionSortDuration);
					InsertionSort::Sort(insertionSortTempNumbers.begin(), insertionSortTempNumbers.end());
					//Timer's destruction will set duration
				}
				if (stdNumbers != insertionSortTempNumbers) {
					throw runtime_error("insertion sort failed!");
				}
			}

			printf("List length:%d, range: [%d,%d]\n",dataLength, dataRange.first, dataRange.second);
			printf("    std::sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(stdSortDuration).count());
			printf("    Heap sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(heapSortDuration).count());
			printf("    Quick sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(quickSortDuration).count());
			printf("    Intro sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(introSortDuration).count());
			printf("    Insertion sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(insertionSortDuration).count());
			cout << endl;
		}
	}

	return 0;
}

void CreateRandomData(vector<int> *numbers, int dataLength, pair<int,int> dataRange) {
	random_device rd;
	vector<unsigned int> seeds;
	for (unsigned int i=0; i<mt19937::state_size; ++i) {
		seeds.emplace_back(rd());
	}
	seed_seq s(seeds.begin(),seeds.end());
	mt19937 eng(s);
	uniform_int_distribution<int> dist(dataRange.first,dataRange.second);
	while (dataLength > 0) {
		numbers->emplace_back(dist(eng));
		--dataLength;
	}
}