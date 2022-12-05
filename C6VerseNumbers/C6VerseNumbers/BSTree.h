#pragma once

#include <functional>
#include <iostream>
#include <stack>
#include <queue>

//generic binary search tree 
template <typename T>
class BSTree {
public:
    struct BSTNode {
        T el;
        BSTNode* left, * right;
        BSTNode() : left(nullptr), right(nullptr) {}
        BSTNode(const T& el, BSTNode* left = nullptr,
            BSTNode* right = nullptr)
            : el(el), left(left), right(right) {}
    };

    BSTNode* root{};
    //functions for comparisons in member functions
    //especially useful when data used is a class
    std::function<bool(const T& el, BSTNode*)> lessThan;
    std::function<bool(const T& el, BSTNode*)> equalTo;


    BSTree(std::function<bool(const T& el, BSTNode*)> fnLessThan, std::function<bool(const T& el, BSTNode*)> fnEqTo) 
        : root(nullptr), lessThan(fnLessThan), equalTo(fnEqTo) {}
    ~BSTree() { clear(root); }

    bool isEmpty() const { return root == nullptr; }
    void clear(BSTNode*&);
    void clear() { clear(root); }
    void print(std::function<void(BSTNode*&)> fn)
    {
        traverse(fn);
    }
    int size()
    {
        int size = 0;
        traverse([&](BSTNode*& node) { size++; });
        return size;
    }
    BSTree<T>::BSTNode* search(const T&);
    void traverse(std::function<void(BSTNode*&)>);
    void insert(const T&);
};
