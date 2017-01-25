#pragma once
#include<iostream>
#include<vector>
#include"binary_tree_node.h"
#include"compare.h"
using namespace std;

template <class A>
class BinarySearchTree {
public:
	BinarySearchTree() {
		root = nullptr;
		size = 0;
		orderList = new vector<BinaryTreeNode<A>*>;
	}

	~BinarySearchTree() {
		if ((int)(orderList->size()) != size) {
			orderList->clear();
			preOrder();
		}
		int list_size = (int)(orderList->size());
		for (int i = 0; i < list_size; i++) {
			BinaryTreeNode<A> *temp = (BinaryTreeNode<A> *)(orderList->back());
			orderList->pop_back();
			delete temp;
		}
		delete orderList;
	}

	void setCompare(compare_func<A> *);
	void add(A);
	bool remove(A);
	bool search(A);
	vector<BinaryTreeNode<A>*> *preOrder();
	vector<BinaryTreeNode<A>*> *postOrder();
	vector<BinaryTreeNode<A>*> *inOrder();
	bool isEmpty();
	int getSize();

private:
	BinaryTreeNode<A> *root;
	int size;
	vector<BinaryTreeNode<A>*> *orderList;
	compare_func<A> *cp;
	void preOrder(BinaryTreeNode<A> *);
	void postOrder(BinaryTreeNode<A> *);
	void inOrder(BinaryTreeNode<A> *);
};

template <class A> void BinarySearchTree<A>::setCompare(compare_func<A> *cp_param) {
	cp = cp_param;
}

template <class A> void BinarySearchTree<A>::add(A element) {
	if (root == nullptr) {
		size++;
		root = new BinaryTreeNode<A>(element);
		return;
	}
	BinaryTreeNode<A> *temp = root;
	BinaryTreeNode<A> *target;
	bool take_left;
	do {
		target = temp;
		if (cp->compare(element, temp->data) == compare_unit::GREATER) {
			temp = temp->right;
			take_left = false;
		}
		else if (cp->compare(element, temp->data) == compare_unit::SMALLER) {
			temp = temp->left;
			take_left = true;
		}
		else {
			cout << "Duplicate data detected!\n";
			return;
		}
	} while (temp != nullptr);
	size++;
	BinaryTreeNode<A> *node = new BinaryTreeNode<A>(element);
	node->parent = target;
	if (take_left) {
		target->left = node;
	}
	else {
		target->right = node;
	}
}

template <class A> bool BinarySearchTree<A>::remove(A element) {
	if (root == nullptr) {
		return false;
	}
	BinaryTreeNode<A> *temp = root;
	BinaryTreeNode<A> *target;
	bool take_left;
	bool equal = false;
	do {
		target = temp;
		if (cp->compare(element, temp->data) == compare_unit::GREATER) {
			temp = temp->right;
			take_left = false;
		}
		else if (cp->compare(element, temp->data) == compare_unit::SMALLER) {
			temp = temp->left;
			take_left = true;
		}
		else {
			equal = true;
			break;
		}
	} while (temp != nullptr);
	if (!equal) {
		cout << "No such element found!";
		return false;
	}
	size--;
	if (target->left == nullptr && target->right == nullptr) {
		if (target == root) {
			delete root;
		}
		else {
			if (take_left) {
				target->parent->left = nullptr;
			}
			else {
				target->parent->right = nullptr;
			}
			target->parent = nullptr;
			delete target;
		}
	}
	else if (target->right != nullptr) {
		BinaryTreeNode<A> *prev = nullptr;
		temp = target->right;
		do {
			prev = temp;
			temp = temp->left;
		} while (temp != nullptr);
		target->data = prev->data;
		if (prev == target->right) {
			if (prev->right != nullptr) {
				prev->right->parent = prev->parent;
				prev->parent->right = prev->right;
			}
			else {
				prev->parent->right = nullptr;
			}
		}
		else {
			if (prev->right != nullptr) {
				prev->parent->left = prev->right;
				prev->right->parent = prev->parent;
			}
			else {
				prev->parent->left = nullptr;
			}
		}
		prev->parent = nullptr;
		delete prev;
	}
	else {
		BinaryTreeNode<A> *prev = nullptr;
		temp = target->left;
		while (temp != nullptr) {
			prev = temp;
			temp = temp->right;
		}
		target->data = prev->data;
		if (prev == target->left) {
			if (prev->left != nullptr) {
				prev->left->parent = prev->parent;
				prev->parent->left = prev->left;
			}
			else {
				prev->parent->left = nullptr;
			}
		}
		else {
			if (prev->left!= nullptr) {
				prev->parent->right = prev->left;
				prev->left->parent = prev->parent;
			}
			else {
				prev->parent->right = nullptr;
			}
		}
		prev->parent = nullptr;
		delete prev;
	}
	return true;
}

template <class A> bool BinarySearchTree<A>::search(A element) {
	if (root == nullptr) {
		return false;
	}
	BinaryTreeNode<A> *temp = root;
	bool take_left;
	do {
		if (cp->compare(element, temp->data) == compare_unit::GREATER) {
			temp = temp->right;
			take_left = false;
		}
		else if (cp->compare(element, temp->data) == compare_unit::SMALLER) {
			temp = temp->left;
			take_left = true;
		}
		else {
			return true;
		}
	} while (temp != nullptr);
	return false;
}

template <class A> vector<BinaryTreeNode<A>*> *BinarySearchTree<A>::preOrder() {
	if (root == nullptr) {
		return nullptr;
	}
	if (!orderList->empty()) {
		orderList->clear();
	}
	preOrder(root);
	return orderList;
}

template <class A> void BinarySearchTree<A>::preOrder(BinaryTreeNode<A> *node) {
	orderList->push_back(node);
	if (node->left != nullptr) {
		preOrder(node->left);
	}
	if (node->right != nullptr) {
		preOrder(node->right);
	}
}

template <class A> vector<BinaryTreeNode<A>*> *BinarySearchTree<A>::postOrder() {
	if (root == nullptr) {
		return nullptr;
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

template <class A> vector<BinaryTreeNode<A>*> *BinarySearchTree<A>::inOrder() {
	if (root == nullptr) {
		return nullptr;
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