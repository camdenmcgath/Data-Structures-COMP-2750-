// C6VerseNumbers.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include <iostream>
#include "BSTree.cpp"

using namespace std;

void treeTest()
{
	BSTree<int>* p = nullptr;
	BSTree<int> tree;

	for (int i = 0; i < 10; i++) {
		tree.insert(i);
	}

	if (!tree.isEmpty()) {
		tree.print();
	}
	else {
		cout << "Tree is empty!\n";
	}
	tree.search(3);
}

int main()
{
	treeTest();

	return 0;
}
