#pragma once
#include <functional>

//doubly linked list prioritizing flexibility

template<class T>
class DLLNode
{
public:
	T data;
	DLLNode<T>* next{nullptr}, * prev{nullptr};

	DLLNode<T>(const T& info, DLLNode<T>* n, DLLNode<T>* p)
		: data(info), next(n), prev(p) 
	{}
};

template<class T>
class DLList
{
	DLLNode<T>* head{ nullptr }, * tail{ nullptr };
public:

	DLList<T>() {}

	bool isEmpty() { return head == nullptr; }
	int getSize();

	DLLNode<T>* getHead() const { return head; }
	DLLNode<T>* getTail() const { return tail; }

	T getHeadData() { return head->data; }
	T getTailData() { return tail->data; }

	//searches for value in list
    //returns its position if found, -1 if not in liat
	int getPosition(std::function<bool (const T&)>);

	//returns a pointer to the node containing the given data (nullptr if not found)
	DLLNode<T>* getNode(std::function<bool(const T&)>);

	//inserts single node sorted into list
	//no manual insertion is left up to the user to protect the integrity of automatic sorting
	//Params: first lambda is to check equality, second lambda is for checking less than
	void insert(const T&, std::function<bool (const T&)>, std::function<bool (const T&)>);

	//removes single node containing the data given
	//Params: lambda is for checking equality
	void remove (const T&, std::function<bool (const T&)>);

};



