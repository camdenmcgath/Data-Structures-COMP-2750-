//Sources: https://www.techiedelight.com/delete-given-binary-tree-iterative-recursive/
//Data Structres and Algorithms in C++ A. Drozdek 4th Edition

#include "BSTree.h"
#include <iostream>
#include <functional>
#include <stack>

//returns pointer to node if value found, 0 otherwise
template<typename T>
typename BSTree<T>::BSTNode* BSTree<T>::search(const T& el)
{
	BSTNode* p = root;

	while (p != nullptr) {
		if (equalTo(el, p)) {
			return p;
		}
		else if (lessThan(el, p)) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	delete p;
	return 0;
}
//clears the entire tree
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
//function parameter determines what is done each visit at a node
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
//basic iterative insertion
template<typename T>
void BSTree<T>::insert(const T& el)
{
	if (search(el) == 0)
	{
		BSTNode* p = root, * prev = nullptr;
		// find a place for inserting new node
		while (p != nullptr) {
			prev = p;
			if (lessThan(el, p)) {
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
		else if (lessThan(el, prev)) {
			prev->left = new BSTNode(el);
		}
		else {
			prev->right = new BSTNode(el);
		}
	}
}