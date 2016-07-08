#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP 1

#include <iostream>
#include <memory>

namespace BinaryTree {

	template<class T>
	class BinaryTree {
	private:
		struct Node {
			T data;
			std::shared_ptr<Node> leftChild{nullptr};
			std::shared_ptr<Node> rightChild{nullptr};
			Node(const T &d) : data(d) {};
		};
		std::shared_ptr<Node> root;
	public:
		BinaryTree();
		void Insert(const T &obj);
	};

	template<class T>
	BinaryTree<T>::BinaryTree() : root(nullptr) {
	}	

	template<class T>
	void BinaryTree<T>::Insert(const T &obj) {
		std::cout << "Inserting " << obj << std::endl;
		std::shared_ptr<Node> tempRoot = root;
		while (1) {
			if (!tempRoot) {
				//We've reached the point to create this node
				std::cout << "tempRoot " << static_cast<bool>(tempRoot) << std::endl;
				tempRoot.reset(new Node(obj));
				std::cout << "tempRoot " << static_cast<bool>(tempRoot) << std::endl;
				std::cout << "root " << static_cast<bool>(root) << std::endl;
				return;
			} else if (obj < tempRoot->data) {
				tempRoot = tempRoot->leftChild;
			} else {
				tempRoot = tempRoot->rightChild;
			}
		}
	}
} //namespace BinaryTree

#endif //BINARYTREE_HPP