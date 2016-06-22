#include <chrono>
#include <string>
#include <vector>
#include "bogosort.hpp"
#include "bubbleSort.hpp"
#include "heapsort.hpp"
#include "insertionSort.hpp"
#include "introsort.hpp"
#include "mergeSort.hpp"
#include "quicksort.hpp"
#include "selectionSort.hpp"
#include "timeUtility.hpp"

using namespace std;
typedef chrono::nanoseconds DurationType;

struct DataRange {
	int first;
	int last;
};

void TestSorts(const vector<int> &numbers);
void STDSortTest(vector<int> numbers, DurationType *duration);
void BogosortTest(vector<int> numbers, DurationType *duration);
void BubbleSortTest(vector<int> numbers, DurationType *duration);
void HeapsortTest(vector<int> numbers, DurationType *duration);
void InsertionSortTest(vector<int> numbers, DurationType *duration);
void IntrosortTest(vector<int> numbers, DurationType *duration);
void MergeSortTest(vector<int> numbers, DurationType *duration);
void QuicksortTest(vector<int> numbers, DurationType *duration);
void SelectionSortTest(vector<int> numbers, DurationType *duration);
bool ComparisonFuntion(const int &a, const int &b);
void CreateRandomData(vector<int> *numbers, int dataLength, DataRange dataRange);

int main() {
	//====================Test a list where all numbers are identical====================
	for (auto length : { 100, 10000, 100000 }) {
		vector<int> numbers(length,1);

		printf("Length = %d & all identical\n",length);
		TestSorts(numbers);
	}
	
	//===========================Test a list already in order============================
	for (auto length : { 100, 10000, 100000 }) {
		vector<int> numbers;
		numbers.resize(length);
		int i=0;
		generate(numbers.begin(), numbers.end(), [&i]{ return i++; });

		printf("Length = %d & in order\n",length);
		TestSorts(numbers);
	}
	
	//============================Test a list in reverse order===========================
	for (auto length : { 100, 10000, 100000 }) {
		vector<int> numbers;
		numbers.resize(length);
		int i=length;
		generate(numbers.begin(), numbers.end(), [&i]{ return --i; });

		printf("Length = %d & in reverse order\n",length);
		TestSorts(numbers);
	}

	//=============================Test some random numbers==============================
	for (auto length : { 10, 100, 1000, 10000, 100000 }) {
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
	DurationType duration;

	STDSortTest(numbers, &duration);
	printf("             std::sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(duration).count());
	// BogosortTest(numbers, &duration);
	// printf("          Bogosort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(duration).count());
	BubbleSortTest(numbers, &duration);
	printf("           Bubble sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(duration).count());
	HeapsortTest(numbers, &duration);
	printf("              Heapsort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(duration).count());
	InsertionSortTest(numbers, &duration);
	printf("        Insertion sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(duration).count());
	IntrosortTest(numbers, &duration);
	printf("             Introsort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(duration).count());
	MergeSortTest(numbers, &duration);
	printf("            Merge sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(duration).count());
	QuicksortTest(numbers, &duration);
	printf("             Quicksort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(duration).count());
	SelectionSortTest(numbers, &duration);
	printf("        Selection sort time: %.8lf seconds\n", chrono::duration_cast<chrono::duration<double>>(duration).count());
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
		Heapsort::Sort(numbers.begin(), numbers.end(), ComparisonFuntion);
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end(), ComparisonFuntion)) {
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
		throw std::runtime_error("Insertions ort failed!");
	}
}

void BogosortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Bogosort::Sort(numbers.begin(), numbers.end(), Bogosort::ShuffleType::Permute);
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw std::runtime_error("Bogosort failed!");
	}
}

void BubbleSortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		BubbleSort::Sort(numbers.begin(), numbers.end());
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw std::runtime_error("Bubble sort failed!");
	}
}

void MergeSortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		MergeSort::Sort(numbers.begin(), numbers.end());
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw std::runtime_error("Merge sort failed!");
	}
}

void SelectionSortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		SelectionSort::Sort(numbers.begin(), numbers.end());
		//Timer's destruction will set duration
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw std::runtime_error("Selection sort failed!");
	}
}

bool ComparisonFuntion(const int &a, const int &b) {
	return a < b;
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