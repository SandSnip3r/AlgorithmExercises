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
void BogosortRandomTest(vector<int> numbers, DurationType *duration);
void BogosortPermuteTest(vector<int> numbers, DurationType *duration);
void BubbleSortTest(vector<int> numbers, DurationType *duration);
void HeapsortTest(vector<int> numbers, DurationType *duration);
void InsertionSortTest(vector<int> numbers, DurationType *duration);
void IntrosortTest(vector<int> numbers, DurationType *duration);
void MergeSortExtraSpaceTest(vector<int> numbers, DurationType *duration);
void MergeSortInPlaceTest(vector<int> numbers, DurationType *duration);
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
	struct SortResult {
		string sortName;
		double duration;
		SortResult(string name, double d) : sortName(name), duration(d) {};
	};

	vector<SortResult> sortResults;

	DurationType duration;

	STDSortTest(numbers, &duration);
	sortResults.emplace_back("std::sort",chrono::duration_cast<chrono::duration<double>>(duration).count());
	if (numbers.size() <= 10) {
		BogosortRandomTest(numbers, &duration);
		sortResults.emplace_back("Bogosort random",chrono::duration_cast<chrono::duration<double>>(duration).count());
		BogosortPermuteTest(numbers, &duration);
		sortResults.emplace_back("Bogosort permute",chrono::duration_cast<chrono::duration<double>>(duration).count());
	}
	BubbleSortTest(numbers, &duration);
	sortResults.emplace_back("Bubble sort",chrono::duration_cast<chrono::duration<double>>(duration).count());
	HeapsortTest(numbers, &duration);
	sortResults.emplace_back("Heapsort",chrono::duration_cast<chrono::duration<double>>(duration).count());
	InsertionSortTest(numbers, &duration);
	sortResults.emplace_back("Insertion sort",chrono::duration_cast<chrono::duration<double>>(duration).count());
	IntrosortTest(numbers, &duration);
	sortResults.emplace_back("Introsort",chrono::duration_cast<chrono::duration<double>>(duration).count());
	MergeSortExtraSpaceTest(numbers, &duration);
	sortResults.emplace_back("Merge sort extra space",chrono::duration_cast<chrono::duration<double>>(duration).count());
	MergeSortInPlaceTest(numbers, &duration);
	sortResults.emplace_back("Merge sort in place",chrono::duration_cast<chrono::duration<double>>(duration).count());
	QuicksortTest(numbers, &duration);
	sortResults.emplace_back("Quicksort",chrono::duration_cast<chrono::duration<double>>(duration).count());
	SelectionSortTest(numbers, &duration);
	sortResults.emplace_back("Selection sort",chrono::duration_cast<chrono::duration<double>>(duration).count());

	sort(sortResults.begin(), sortResults.end(), [](const SortResult &a, const SortResult &b){ return a.duration < b.duration; });
	for (const SortResult &sortResult : sortResults) {
		printf("%26s time: %.8lf seconds\n", sortResult.sortName.c_str(), sortResult.duration);
	}
	cout << endl;

}

void STDSortTest(vector<int> numbers, DurationType *duration) {
	Timer<DurationType> timer(duration);
	sort(numbers.begin(), numbers.end());
}

void HeapsortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Heapsort::Sort(numbers.begin(), numbers.end(), ComparisonFuntion);
	}
	if (!is_sorted(numbers.begin(), numbers.end(), ComparisonFuntion)) {
		throw runtime_error("Heapsort failed!");
	}
}

void QuicksortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Quicksort::Sort(numbers.begin(), numbers.end());
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw runtime_error("Quicksort failed!");
	}
}

void IntrosortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Introsort::Sort(numbers.begin(), numbers.end());
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw runtime_error("Introsort failed!");
	}
}

void InsertionSortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		InsertionSort::Sort(numbers.begin(), numbers.end());
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw runtime_error("Insertion sort failed!");
	}
}

void BogosortRandomTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Bogosort::Sort(numbers.begin(), numbers.end(), Bogosort::ShuffleType::Random);
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw runtime_error("Bogosort failed!");
	}
}

void BogosortPermuteTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		Bogosort::Sort(numbers.begin(), numbers.end(), Bogosort::ShuffleType::Permute);
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw runtime_error("Bogosort failed!");
	}
}

void BubbleSortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		BubbleSort::Sort(numbers.begin(), numbers.end());
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw runtime_error("Bubble sort failed!");
	}
}

void MergeSortExtraSpaceTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		MergeSort::Sort(numbers.begin(), numbers.end(), MergeSort::MergeType::ExtraSpace);
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw runtime_error("Merge sort failed!");
	}
}

void MergeSortInPlaceTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		MergeSort::Sort(numbers.begin(), numbers.end(), MergeSort::MergeType::InPlace);
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw runtime_error("Merge sort failed!");
	}
}

void SelectionSortTest(vector<int> numbers, DurationType *duration) {
	{
		Timer<DurationType> timer(duration);
		SelectionSort::Sort(numbers.begin(), numbers.end());
	}
	if (!is_sorted(numbers.begin(), numbers.end())) {
		throw runtime_error("Selection sort failed!");
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