//resource: Geeks for Geeks, Data Structures and Algorithms in C++ Drozdek
#include "Heap.h"
#include <iostream>
#include <functional>

template<typename T>
void Heap<T>::print(std::function<void(T& data)> fn)
{
	for (auto i : Heap<T>::heap) {
		fn(i);
	}
}
template<typename T>
void Heap<T>::heapSort()
{
	//build heap
	for (int i = (Heap<T>::heap.size() / 2) - 1; i >= 0; --i) {
		heapify(i, Heap<T>::heap.size() - 1);
	}
	//sort heap perfectly, sorts ascending for max heap, descending for min 
	for (int i = Heap<T>::heap.size() - 1; i >= 1; --i) {
		//put largest element at end for max heap, smallest at end for min
		std::swap(Heap<T>::heap.at(0), Heap<T>::heap.at(i));
		heapify(0, i - 1);
	}
}
template<typename T>
void MaxHeap<T>::heapify(int first, int last)
{
	//restore heap property between first and last in the array
	int largest = 2 * first + 1;
	while (largest <= last) {
		if (largest < last && Heap<T>::heap.at(largest) < Heap<T>::heap.at(largest + 1)) {
			largest++;
		}
		if (Heap<T>::heap.at(first) < Heap<T>::heap.at(largest)) {
			//swap child and parent
			std::swap(Heap<T>::heap.at(first), Heap<T>::heap.at(largest));
			first = largest;
			largest = 2 * first + 1;
		}
		//allows for exiting the loop
		else largest = last + 1;
	}
}
template<typename T>
void MinHeap<T>::heapify(int first, int last)
{
	//restore heap property between first and last in the array
	int smallest = 2 * first + 1;
	while (smallest <= last) {
		if (smallest < last && Heap<T>::heap.at(smallest) > Heap<T>::heap.at(smallest + 1)) {
			smallest++;
		}
		if (Heap<T>::heap.at(first) > Heap<T>::heap.at(smallest)) {
			//swap child and parent
			std::swap(Heap<T>::heap.at(first), Heap<T>::heap.at(smallest));
			first = smallest;
			smallest = 2 * first + 1;
		}
		//allows to exit loop
		else smallest = last + 1;
	}
}


