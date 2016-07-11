#include <iostream>
#include <random>
#include <vector>
#include "timeUtility.hpp"
#include "binaryTree.hpp"

using namespace std;

typedef chrono::nanoseconds DurationType;

int main() {
	random_device rd;
	vector<unsigned int> seeds;
	seeds.reserve(mt19937::state_size);
	for (size_t i=0; i<mt19937::state_size; ++i) {
		seeds.emplace_back(rd());
	}
	seed_seq s(seeds.begin(), seeds.end());
	mt19937 eng(s);

	DurationType duration;
	{
		Timer<DurationType> t(&duration);
		BinaryTree::BinaryTree<int> tree;
		for (int i=0; i<1000000; ++i) {
			uniform_int_distribution<int> dist(0,1000000000);
			tree.Insert(dist(eng));
		}
		cout << "size " << tree.Size() << " & height " << tree.Height() << endl;
	}
	printf("%.10lf\n",chrono::duration_cast<chrono::duration<double>>(duration).count());
	return 0;
}