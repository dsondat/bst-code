#pragma once
#include<iostream>
using namespace std;

template <class B>
class BinaryTreeNode {
	template <class B> friend class BinarySearchTree;
public:
	BinaryTreeNode() {
		BinaryTreeNode(nullptr);
	}

	BinaryTreeNode(B data_param) {
		left = right = parent = nullptr;
		data = data_param;
		index = -1;
	}

	~BinaryTreeNode() { }

	void setData(B);
	B getData();
private:
	BinaryTreeNode *left;
	BinaryTreeNode *right;
	BinaryTreeNode *parent;
	B data;
	int index;
};

template <class B> void BinaryTreeNode<B>::setData(B data_param) {
	data = data_param;
}

template <class B> B BinaryTreeNode<B>::getData() {
	return data;
}