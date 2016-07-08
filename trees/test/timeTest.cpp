#include <iostream>
#include "timeUtility.hpp"
#include "binaryTree.hpp"

using namespace std;

typedef chrono::nanoseconds DurationType;

int main() {
	DurationType duration;
	{
		Timer<DurationType> t(&duration);
		BinaryTree::BinaryTree<int> tree;
		tree.Insert(1);
	}
	printf("%.10lf\n",chrono::duration_cast<chrono::duration<double>>(duration).count());
	return 0;
}
