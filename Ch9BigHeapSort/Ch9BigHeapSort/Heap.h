#pragma once
#include <vector>

//template<typename T>
class Heap {
private:
	std::vector<int> heap{};
public:
	Heap() = default;

	[[nodiscard]] const std::vector<int>& getHeap() const noexcept { return heap; }
	void push(const int& val) { heap.push_back(val); }
	void insert(int idx, const int& val) noexcept { heap.at(idx) = val; }
};