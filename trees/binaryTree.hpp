#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP 1

#include <iostream>
#include <queue>
#include <memory>

namespace BinaryTree {

	template<class T>
	class BinaryTree {
	private:
		struct Node {
			T data;
			std::unique_ptr<Node> leftChild;
			std::unique_ptr<Node> rightChild;
			Node(const T &d) : data(d) {};
		};
		std::unique_ptr<Node> root;
		size_t size{0}, height{0};
		void PrintInOrder(std::unique_ptr<Node> &n);
	public:
		void Insert(const T &obj);
		size_t Size() const;
		size_t Height() const;
		void PrintInOrder();
		void PrintBreadth();
	};

	template<class T>
	void BinaryTree<T>::Insert(const T &obj) {
		std::unique_ptr<Node> *tempRoot = &root;
		size_t insertionDepth = 1;
		while (1) {
			if (!(*tempRoot)) {
				//We've reached the point to create this node
				tempRoot->reset(new Node(obj));
				++size;
				if (insertionDepth > height) {
					height = insertionDepth;
				}
				return;
			} else if (obj < (*tempRoot)->data) {
				tempRoot = &((*tempRoot)->leftChild);
				++insertionDepth;
			} else {
				tempRoot = &((*tempRoot)->rightChild);
				++insertionDepth;
			}
		}
	}

	template<class T>
	size_t BinaryTree<T>::Size() const {
		return size;
	}

	template<class T>
	size_t BinaryTree<T>::Height() const {
		return height;
	}

	template<class T>
	void BinaryTree<T>::PrintBreadth() {
		std::queue<std::unique_ptr<Node>*> nodes;
		nodes.emplace(&root);
		while (!nodes.empty()) {
			std::unique_ptr<Node> *n = nodes.front();
			nodes.pop();
			if (*n) {
				std::cout << (*n)->data << " ";
				nodes.push(&((*n)->leftChild));
				nodes.push(&((*n)->rightChild));
			} else {
				//Nothing here
			}
		}
		std::cout << std::endl;
	}

	template<class T>
	void BinaryTree<T>::PrintInOrder() {
		PrintInOrder(root);
		std::cout << std::endl;
	}

	template<class T>
	void BinaryTree<T>::PrintInOrder(std::unique_ptr<Node> &n) {
		if (n) {
			PrintInOrder(n->leftChild);
			std::cout << n->data << " ";
			PrintInOrder(n->rightChild);
		} else {
			//Nothing here
		}
	}

} //namespace BinaryTree

#endif //BINARYTREE_HPP