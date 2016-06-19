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
void TestSorts(const vector<int> &numbers);
void STDSortTest(vector<int> numbers, DurationType *duration);
void HeapsortTest(vector<int> numbers, DurationType *duration);
void QuicksortTest(vector<int> numbers, DurationType *duration);
void IntrosortTest(vector<int> numbers, DurationType *duration);
void InsertionSortTest(vector<int> numbers, DurationType *duration);
void BogosortTest(vector<int> numbers, DurationType *duration);

int main() {
	//====================Test a list where all numbers are identical====================
	for (auto length : { 	100, 10000, 100000 }) {
		vector<int> numbers(length,1);

		printf("Length = %d & all identical\n",length);
		TestSorts(numbers);
	}
	
	//===========================Test a list already in order============================
	for (auto length : { 	100, 10000, 100000 }) {
		vector<int> numbers;
		numbers.reserve(length);
		for (int i=0; i<length; ++i) {
			numbers.emplace_back(i);
		}

		printf("Length = %d & in order\n",length);
		TestSorts(numbers);
	}
	
	//============================Test a list in reverse order===========================
	for (auto length : { 	100, 10000, 100000 }) {
		vector<int> numbers;
		numbers.reserve(length);
		for (int i=0; i<length; ++i) {
			numbers.emplace_back(length-i);
		}

		printf("Length = %d & in reverse order\n",length);
		TestSorts(numbers);
	}

	//=============================Test some random numbers==============================
	for (auto length : { 	10, 100, 1000, 10000, 100000 }) {
		vector<int> numbers;
		numbers.reserve(length);
		for (DataRange dataRange : { 	DataRange{1,10}, 
																	DataRange{1,100}, 
																	DataRange{1,1000}, 
																	DataRange{1,10000000} }) {
			CreateRandomData(&numbers, length, dataRange);

			printf("Length = %d & random range [%d-%d]\n",length, dataRange.first, dataRange.last);
			TestSorts(numbers);
		}
	}

	return 0;
}

void TestSorts(const vector<int> &numbers) {
	DurationType stdDuration;
	DurationType heapsortDuration;
	DurationType quicksortDuration;
	DurationType introsortDuration;
	DurationType insertionSortDuration;

	STDSortTest(numbers, &stdDuration);
	HeapsortTest(numbers, &heapsortDuration);
	QuicksortTest(numbers, &quicksortDuration);
	IntrosortTest(numbers, &introsortDuration);
	InsertionSortTest(numbers, &insertionSortDuration);

	printf("         std::sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(stdDuration).count());
	printf("          Heapsort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(heapsortDuration).count());
	printf("         Quicksort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(quicksortDuration).count());
	printf("         Introsort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(introsortDuration).count());
	printf("    Insertion sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(insertionSortDuration).count());
	cout << endl;

}

void STDSortTest(vector<int> numbers, DurationType *duration) {
	Timer<DurationType> timer(duration);
	sort(numbers.begin(), numbers.end());
	//Timer's destruction will set duration
}

void HeapsortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Heapsort::Sort(numbers.begin(), numbers.end());
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw std::runtime_error("Heapsort failed!");
	}
}

void QuicksortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Quicksort::Sort(numbers.begin(), numbers.end());
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw std::runtime_error("Quicksort failed!");
	}
}

void IntrosortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Introsort::Sort(numbers.begin(), numbers.end());
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw std::runtime_error("Introsort failed!");
	}
}

void InsertionSortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		InsertionSort::Sort(numbers.begin(), numbers.end());
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw std::runtime_error("InsertionSort failed!");
	}
}

void BogosortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Bogosort::Sort(numbers.begin(), numbers.end());
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw std::runtime_error("Bogosort failed!");
	}
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