//Sources: https://www.techiedelight.com/delete-given-binary-tree-iterative-recursive/

#include "BSTree.h"
#include <iostream>
#include <functional>
#include <queue>

template<typename T>
T* BSTree<T>::search(const T& el)
{
	BSTNode* p = root;
	std::queue<BSTNode*> generations;

	while (p != nullptr) {
		generations.push(p);
		if (el == p->el) {
			rotate(generations, p);
			return &p->el;
		}
		else if (el < p->el) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
}

template<typename T>
void BSTree<T>::rotate(std::queue<BSTNode*> prevs, BSTNode* child)
{
	BSTNode* parent = prevs.pop();
	BSTNode* grandparent = prevs.pop();
	if (grandparent != nullptr) {
		grandparent->right = child;
	}
	parent->left = child->right;
	child->right = parent;
}

template<typename T>
void BSTree<T>::clear(BSTNode*& root)
{
	if (root == nullptr) { return; }

	std::queue<BSTNode*> nodes;
	nodes.push(root);

	BSTNode* parent = nullptr;

	while (!nodes.empty()) {
		parent = nodes.front();
		nodes.pop();
		if (parent->left != nullptr) {
			nodes.push(parent->left);
		}
		if (parent->right != nullptr) {
			nodes.push(parent->right);
		}
		delete parent;
	}
	root = nullptr;
}

//traversal using the morris algoithm 
template<typename T>
void BSTree<T>::traverse(std::function<void(BSTNode*& node)> visit)
{
	BSTNode* p = root, * tmp;
	while (p != nullptr) {
		if (p->left == nullptr) {
			visit(p);
			p = p->right;
		}
		else {
			tmp = p->left;
			while (tmp->right != nullptr && tmp->right != p) {
				tmp = tmp->right;
			}
			if (tmp->right == nullptr) {
				tmp->right = p;
				p = p->left;
			}
			else {
				visit(p);
				tmp->right = nullptr;
				p = p->right;
			}
		}
	}
}

template<typename T>
void BSTree<T>::insert(const T& el)
{
	BSTNode* p = root, * prev = nullptr;
	// find a place for inserting new node
	while (p != nullptr) {
		prev = p;
		if (el < p->el) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	//tree is empty
	if (root == nullptr) {
		root = new BSTNode(el);
	}
	else if (el < prev->el) {
		prev->left = new BSTNode(el);
	}
	else {
		prev->right = new BSTNode(el);
	}
}

//delete alorithm implemented with copying 
template<typename T>
void BSTree<T>::remove(BSTNode*& node)
{
	BSTNode* previous, * tmp = node;
	//node has no right child
	if (node->right == nullptr) {
		node = node->left;
	}
	//node has no left child
	else if (node->left == nullptr) {
		node = node->right;
	}
	//node has 2 children
	else {
		tmp = node->left;
		previous = node;
		while (tmp->right != nullptr) {
			previous = tmp;
			tmp = tmp->right;
		}
		node->el = tmp->el;
		if (previous == node) {
			previous->left = tmp->left;
		}
		else {
			previous->right = tmp->left;
		}
	}
	delete tmp;
}