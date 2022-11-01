#include "DoublyLinkedList.h"

template<class T>
int DLList<T>::getSize()
{
	int size = 0;
	DLLNode<T>* countNode = getHead();
	while (countNode != nullptr)
	{
		countNode = countNode->next;
		size++;
	}
	delete countNode;
	return size;
}

//searches list to see if the given value exists
//returns the index if found, -1 if not in list
//Param: lambda to check equality
template<class T>
int DLList<T>::getPosition(std::function<bool(const T&)> fnEq)
{
	if (!isEmpty())
	{
		DLLNode<T>* temp = head;
		int position = 0;
		while (temp != nullptr)
		{
			if (fnEq((*temp).data))
			{
				return position;
			}
			else
			{
				temp = temp->next;
			}
			position++;
		}
		delete temp;
		return -1; //not found in list
	}
	else
	{
		return -1;
	}

}

//returns a pointer to the node containing the given data (nullptr if not found)
//Param: lambda to check equality
template<class T>
DLLNode<T>* DLList<T>::getNode(std::function<bool(const T&)> fnEq)
{
	if (!isEmpty())
	{
		DLLNode<T>* temp = head;

		do
		{
			if (fnEq((*temp).data))
			{
				return temp;
			}

			temp = temp->next;
		} while (temp != nullptr);

		return nullptr; //not found
	}
	else
	{
		return nullptr; //not found
	}

}

//inserts single node sorted into list
//no manual insertion is left up to the user to protect the integrity of automatic sorting
//Params: first lambda is to check equality, second lambda is for checking less than
template<class T>
void DLList<T>::insert(const T& newData, std::function<bool(const T&)> fnPos, std::function<bool(const T&)> fnLess)
{
	//check if node with data already exists
	if (getPosition(fnPos) == -1)
	{
		if (isEmpty())
		{
			//add first node
			head = tail = new DLLNode<T>(newData, nullptr, nullptr);
		}
		else if (fnLess((*head).data)) //newData < head->data
		{
			//add to front
			head = head->prev = new DLLNode<T>(newData, head, nullptr);
		}
		else
		{
			//inserting past the head
			DLLNode<T>* temp = head;
			for (int i = 0; i < getSize(); i++)
			{
				if (temp->next == nullptr)
				{
					//add to end of list (tail)
					tail = temp->next = new DLLNode<T>(newData, nullptr, temp);
					break;
				}
				else if (fnLess((*temp->next).data)) //newData < temp->next->data
				{
					//add between
					temp->next = temp->next->prev = new  DLLNode<T>(newData, temp->next, temp);
					break;
				}
				//move node checking to right one
				temp = temp->next;
			}
			//delete temp;
		}
	}
}

//removes single node containing the data given
//Params: lambda is for checking equality
template<class T>
void DLList<T>::remove(const T& deadData, std::function<bool(const T&)> fnEq)
{
	if (getPosition(fnEq) != -1 && !isEmpty())
	{
		DLLNode<T>* temp = head;
		for (int i = 0; i < getPosition(fnEq); i++)
		{
			temp = temp->next;
		}
		if (fnEq((*temp).data))
		{
			if (head == tail)
			{
				//if list has only one node
				delete head;
				head = tail = nullptr;
			}
			else if (temp == head)
			{
				//delete head of list bigger than 1
				head = temp->next;
				head->prev = nullptr;
				delete temp;
			}
			else if (temp == tail)
			{
				//delete tail of list bigger than 1
				tail = temp->prev;
				tail->next = nullptr;
				delete temp;
			}
			else
			{
				//delete in between nodes
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
			}
		}
	}
}