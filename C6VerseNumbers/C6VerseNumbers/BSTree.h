#pragma once
// TODO: look at auto adjusting (use queue in search to store parents and then rotate), add comments

#include <functional>
#include <iostream>
#include <queue>


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

    BSTree() : root(nullptr) {}
    ~BSTree() { clear(root); }

    bool isEmpty() const { return root == nullptr; }
    void clear(BSTNode*&);
    void clear() { clear(root); }
    void print()
    {
        traverse([](BSTNode*& node) { std::cout << node->el << " "; });
    }
    int size()
    {
        int size = 0;
        traverse([&](BSTNode*& node) { size++; });
        return size;
    }
    T* search(const T&);
    void rotate(std::queue<BSTNode*>, BSTNode*);
    void traverse(std::function<void(BSTNode*&)>);
    void insert(const T&);
    void remove(BSTNode*&);
};
