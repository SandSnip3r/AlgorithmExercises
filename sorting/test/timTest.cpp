#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include "../timsort.hpp"

using namespace std;

void Print(vector<int> list);

int main() {
	random_device rd;
	vector<uint> seeds;
	for (uint i=0; i<mt19937::state_size; ++i) {
		seeds.emplace_back(rd());
	}
	seed_seq s(seeds.begin(), seeds.end());
	mt19937 eng(s);

	vector<int> list;
	uniform_int_distribution<int> lengthDist(100,500);
	// normal_distribution<> numDist(100,1);
	int length = lengthDist(eng);
	for (int i=1; i<length; ++i) {
		uniform_int_distribution<int> numDist(i,i+2);
		list.emplace_back(std::round(numDist(eng)));
	}

	Print(list);
	Timsort::Sort(list.begin(),list.end());
	Print(list);
	return 0;
}

void Print(vector<int> list) {
	for (int i : list) {
		cout << i << " ";
	}
	cout << endl;
}
