//Stack implemented with an STL List

#pragma once
#include <list>

template<typename T>
class LLStack
{
	std::list<T> lst;

public:
	LLStack() {}

	void clear() { lst.clear; }
	bool isEmpty() const { return lst.empty(); }
	T& topEl() { return lst.back(); }
	T pop()
	{
		T el = lst.back();
		lst.pop_back();
		return el;
	}
	void push(const T& el) { lst.push_back(el); }
};