/*************************************************************************************************
* File: Binary-Search-Tree.hpp
* Description:
*       Basic Binary Search Tree implementation for CPSC 131 SI @ CSUF.
*       Follows Similar behavior with the STL's std::map container
*       Requires C++ 14 or later (Smart Pointers)
*       (If using clang or g++ compiler specify with the flag: -std=c++17)
*
*       For the STL implementation, refer to the following:
*       Link: https://www.cplusplus.com/reference/map/map/
*
* ===========================================$HISTORY$============================================
* Ean McGilvery     04/12/2021   Inital Commit
**************************************************************************************************/

// INCLUDE GUARDS (You may also see, #pragma once)
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <memory>

template <typename KEY, typename VALUE>
struct BST_Node
{
    // Key Value Pair
    KEY   first;
    VALUE second;

    // Pointers to other BST_Nodes in the Tree
    std::shared_ptr<BST_Node<KEY, VALUE>> parent; 
    std::shared_ptr<BST_Node<KEY, VALUE>> left;
    std::shared_ptr<BST_Node<KEY, VALUE>> right;

    BST_Node() = default;
    BST_Node(KEY key, VALUE val) : first(key), second(val), parent(nullptr), 
                               left(nullptr), right(nullptr) {}
};

template <typename KEY, typename VALUE>
class BST
{
    public:
        BST() : root_(nullptr), size_(0) {}

        // Traversals
        // void Preorder();
        // void Preorder(std::shared_ptr<BST_Node<KEY, VALUE>>);
        // void Inorder();
        // void Inorder(std::shared_ptr<BST_Node<KEY, VALUE>>);
        // void Postorder();
        // void Postorder(std::shared_ptr<BST_Node<KEY, VALUE>>);



    private:
        std::shared_ptr<BST_Node<KEY, VALUE>> root_;
        size_t size_;
};
#endif //BINARY_SEARCH_TREE_H