#include <chrono>
#include <string>
#include <vector>
#include "bogosort.hpp"
#include "heapsort.hpp"
#include "insertionSort.hpp"
#include "introsort.hpp"
#include "quicksort.hpp"
#include "timeUtility.hpp"

using namespace std;
typedef chrono::nanoseconds DurationType;

struct DataRange {
	int first;
	int last;
};

void CreateRandomData(vector<int> *numbers, int dataLength, DataRange dataRange);
void STDSortTest(vector<int> numbers, DurationType *duration);
void HeapsortTest(vector<int> numbers, DurationType *duration);
void QuicksortTest(vector<int> numbers, DurationType *duration);
void IntrosortTest(vector<int> numbers, DurationType *duration);
void InsertionSortTest(vector<int> numbers, DurationType *duration);
void BogosortTest(vector<int> numbers, DurationType *duration);

int main() {
	for (auto length : { 	1, 10, 100, 1000, 10000, 100000 }) {
		vector<int> numbers;
		numbers.reserve(length);
		for (DataRange dataRange : { 	DataRange{1,1},
																	DataRange{1,10}, 
																	DataRange{1,100}, 
																	DataRange{1,1000}, 
																	DataRange{1,length*10} }) {
			CreateRandomData(&numbers, length, dataRange);
			
			DurationType stdDuration;
			DurationType heapsortDuration;
			DurationType quicksortDuration;
			DurationType introsortDuration;
			DurationType insertionSortDuration;
			DurationType bogosortDuration;

			STDSortTest(numbers, &stdDuration);
			HeapsortTest(numbers, &heapsortDuration);
			QuicksortTest(numbers, &quicksortDuration);
			IntrosortTest(numbers, &introsortDuration);
			InsertionSortTest(numbers, &insertionSortDuration);
			BogosortTest(numbers, &bogosortDuration);

			printf("Length = %d & Range = [%d-%d]\n",length, dataRange.first, dataRange.last);
			printf("         std::sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(stdDuration).count());
			printf("          Heapsort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(heapsortDuration).count());
			printf("         Quicksort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(quicksortDuration).count());
			printf("         Introsort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(introsortDuration).count());
			printf("    Insertion sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(insertionSortDuration).count());
			printf("          Bogosort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(bogosortDuration).count());
			cout << endl;
		}
	}

	return 0;
}

void STDSortTest(vector<int> numbers, DurationType *duration) {
	Timer<DurationType> timer(duration);
	sort(numbers.begin(), numbers.end());
	//Timer's destruction will set duration
}

void HeapsortTest(vector<int> numbers, DurationType *duration) {
	Timer<DurationType> timer(duration);
	Heapsort::Sort(numbers.begin(), numbers.end());
	//Timer's destruction will set duration
}

void QuicksortTest(vector<int> numbers, DurationType *duration) {
	Timer<DurationType> timer(duration);
	Quicksort::Sort(numbers.begin(), numbers.end());
	//Timer's destruction will set duration
}

void IntrosortTest(vector<int> numbers, DurationType *duration) {
	Timer<DurationType> timer(duration);
	Introsort::Sort(numbers.begin(), numbers.end());
	//Timer's destruction will set duration
}

void InsertionSortTest(vector<int> numbers, DurationType *duration) {
	Timer<DurationType> timer(duration);
	InsertionSort::Sort(numbers.begin(), numbers.end());
	//Timer's destruction will set duration
}

void BogosortTest(vector<int> numbers, DurationType *duration) {
	Timer<DurationType> timer(duration);
	Bogosort::Sort(numbers.begin(), numbers.end());
	//Timer's destruction will set duration
}

void CreateRandomData(vector<int> *numbers, int dataLength, DataRange dataRange) {
	numbers->clear();
	random_device rd;
	vector<unsigned int> seeds;
	for (unsigned int i=0; i<mt19937::state_size; ++i) {
		seeds.emplace_back(rd());
	}
	seed_seq s(seeds.begin(),seeds.end());
	mt19937 eng(s);
	uniform_int_distribution<int> dist(dataRange.first,dataRange.last);
	while (dataLength > 0) {
		numbers->emplace_back(dist(eng));
		--dataLength;
	}
}