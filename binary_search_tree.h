#pragma once
#include<iostream>
#include<vector>
#include"binary_tree_node.h"
#include"compare.h"
using namespace std;

typedef void(*func_ptr)(void *);

template <class A>
class BinarySearchTree {
public:
	BinarySearchTree() {
		root = nullptr;
		size = 0;
		orderList = new vector<BinarySearchTree<A*>>;
	}

	~BinarySearchTree() {
		for (int i = 0; i < orderList->size(); i++) {
			delete orderList->pop_back();
		}
	}

	void setCompare(compare_func *);
	void setOrderFunc(func_ptr)
	void add(A);
	bool remove(A);
	bool search(A);
	vector<BinarySearchTree<A>*> preOrder();
	vector<BinarySearchTree<A>*> postOrder();
	vector<BinarySearchTree<A>*> inOrder();
	bool isEmpty();
	int getSize();

private:
	BinaryTreeNode<A> *root;
	int size;
	vector<BinarySearchTree<A>*> *orderList;
	compare_func *cp;
	void add(BinaryTreeNode<A> *);
	void preOrder(BinaryTreeNode<A> *);
	void postOrder(BinaryTreeNode<A> *);
	void inOrder(BinaryTreeNode<A> *);
};

template <class A> void BinarySearchTree<A>::setCompare(compare_func *cp_param) {
	cp = cp_param;
}

template <class A> void BinarySearchTree<A>::add(BinaryTreeNode<A> *node) {
	if (node == nullptr) {
		cout << "Null object parameter!";
		return;
	}
	BinaryTreeNode<A> *temp = root;
	BinaryTreeNode<A> *temp_parent;
	bool insert_left = true;
	while (temp != nullptr) {
		temp_parent = temp;
		if (cp->compare(node->data, temp->data) == compare_func<A>::GREATER) {
			temp = temp->right;
			insert_left = false;
		}
		else if (cp->compare(node->data, temp->data) == compare_func<A>::SMALLER) {
			temp = temp->left;
			insert_left = true;
		}
		else {
			return;
		}
	}
	size++;
	if (insert_left) {
		temp_parent->left = node;
	}
	else {
		temp_parent->right = node;
	}
}

template <class A> void BinarySearchTree<A>::add(A element) {
	add(new BinaryTreeNode<A>(element));
}

template <class A> bool BinarySearchTree<A>::remove(A element) {
	
}

template <class A> bool BinarySearchTree<A>::search(A element) {

}

template <class A> vector<BinarySearchTree<A>*> BinarySearchTree<A>::preOrder() {
	if (root == null) {
		return;
	}
	preOrder(root);
	return orderList;
}

template <class A> void BinarySearchTree<A>::preOrder(BinaryTreeNode<A> *node) {
	orderList->push_back(node);
	if (node->left != nullptr) {
		preOrder(node->left);
	}
	if (!orderList->empty()) {
		orderList->clear();
	}
	if (node->right != nullptr) {
		preOrder(node->right);
	}
}

template <class A> vector<BinarySearchTree<A>*> BinarySearchTree<A>::postOrder() {
	if (root == null) {
		return;
	}
	if (!orderList->empty()) {
		orderList->clear();
	}
	postOrder(root);
	return orderList;
}

template <class A> void BinarySearchTree<A>::postOrder(BinaryTreeNode<A> *node) {
	if (node->left != nullptr) {
		postOrder(node->left);
	}
	if (node->right != nullptr) {
		postOrder(node->right);
	}
	orderList->push_back(node);
}

template <class A> vector<BinarySearchTree<A>*> BinarySearchTree<A>::inOrder() {
	if (root == null) {
		return;
	}
	if (!orderList->empty()) {
		orderList->clear();
	}
	inOrder(root);
	return orderList;
}

template <class A> void BinarySearchTree<A>::inOrder(BinaryTreeNode<A> *node) {
	if (node->left != nullptr) {
		inOrder(node->left);
	}
	orderList->push_back(node);
	if (node->right != nullptr) {
		inOrder(node->right);
	}
}

template <class A> bool BinarySearchTree<A>::isEmpty() {
	return size == 0;
}

template <class A> int BinarySearchTree<A>::getSize() {
	return size;
}