#include <cassert>
#include <chrono>
#include <vector>
#include "heapsort.hpp"
#include "timeUtility.hpp"

using namespace std;

void CreateRandomData(vector<int> *numbers, int dataLength, pair<int,int> dataRange);

int main() {
	for (int dataLength : { 10, 100, 1000, 10000 }) {
		for (pair<int,int> dataRange : { 	pair<int,int>{1,10},
																			pair<int,int>{1,100}, 
																			pair<int,int>{1,1000}, 
																			pair<int,int>{1,1000000} }) {

			vector<int> numbers;
			CreateRandomData(&numbers, dataLength, dataRange);

			chrono::nanoseconds duration;
			{
				Timer timer(&duration);
				HeapSort::Sort(numbers.begin(), numbers.end());
				//Timer's destruction will set duration
			}

			printf("Sorting a list, Length:%-5d, Range: [%d,%-7d], Time: %9lu nanoseconds\n",dataLength, dataRange.first, dataRange.second, duration.count());
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