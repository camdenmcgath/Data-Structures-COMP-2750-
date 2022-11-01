#include "DoublyLinkedList.h"
#include <string>

class Flight
{
	int number;
	DLList<std::string>* manifest;
public:

	Flight(const int num)
		: number(num)
	{
		manifest = new DLList<std::string>();
	}

	DLList<std::string>* getManifest() { return manifest; }
	int getNum() const { return number; }
};