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
	struct target_branch {
		friend void BinarySearchTree<A>::searchBranch(target_branch *);
		friend void BinarySearchTree<A>::add(BinaryTreeNode<A> *);
		BinaryTreeNode<A> *target;
		BinaryTreeNode<A> *node;
		bool left_target;
	};
	BinaryTreeNode<A> *root;
	int size;
	vector<BinaryTreeNode<A>*> *orderList;
	void searchBranch(target_branch *);
	compare_func<A> *cp;
	void add(BinaryTreeNode<A> *);
	void preOrder(BinaryTreeNode<A> *);
	void postOrder(BinaryTreeNode<A> *);
	void inOrder(BinaryTreeNode<A> *);
};

template <class A> void BinarySearchTree<A>::setCompare(compare_func<A> *cp_param) {
	cp = cp_param;
}

template <class A> void BinarySearchTree<A>::add(BinaryTreeNode<A> *node) {
	if (node == nullptr) {
		cout << "Null object parameter!";
		return;
	}
	if (root == nullptr) {
		size++;
		root = node;
		return;
	}
	target_branch branch;
	branch.node = node;
	searchBranch(&branch);
	size++;
	if (branch.left_target) {
		branch.target->left = node;
	}
	else {
		branch.target->right = node;
	}
}

template <class A> void BinarySearchTree<A>::add(A element) {
	add(new BinaryTreeNode<A>(element));
}

template <class A> bool BinarySearchTree<A>::remove(A element) {
	
}

template <class A> bool BinarySearchTree<A>::search(A element) {

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

template <class A> void BinarySearchTree<A>::searchBranch(target_branch *branch) {
	BinaryTreeNode<A> *temp = root;
	BinaryTreeNode<A> *node = branch->node;
	do {
		branch->target = temp;
		if (cp->compare(node->data, temp->data) == compare_func<A>::GREATER) {
			temp = temp->right;
			branch->left_target = false;
		}
		else if (cp->compare(node->data, temp->data) == compare_func<A>::SMALLER) {
			temp = temp->left;
			branch->left_target = false;
		}
		else {
			return;
		}
	} while (temp != nullptr);
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