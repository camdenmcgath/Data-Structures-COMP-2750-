#pragma once
#include <vector>
#include <iostream>
#include <functional>

//abastract class for min/max heaps
template<typename T>
class Heap {
protected:
	std::vector<T> heap{};
public:
	Heap(std::vector<int> vec): heap(vec) {}
	void print(std::function<void(T&)>);
	//specific heapify function to be implemented in min/max heaps
	virtual void heapify(int, int) = 0;
	void heapSort();
};
template<typename T>
class MaxHeap : public Heap<T> {
public:
	MaxHeap(std::vector<int> vec) : Heap<T>::Heap(vec) {
		Heap<T>::heapSort();
	}
	virtual void heapify(int, int);
};
template<typename T>
class MinHeap : public Heap<T> {
public:
	MinHeap(std::vector<int> vec) : Heap<T>::Heap(vec) {
		Heap<T>::heapSort();
	}
	virtual void heapify(int, int);
};