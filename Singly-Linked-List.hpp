/*************************************************************************************************
* File: Singly-Linked-List.hpp
* Description:
*       Basic Singly Linked List implementation for CPSC 131 SI @ CSUF.
*       Requires C++ 14 or later (Smart Pointers)
*       (If using clang or g++ compiler specify with the flag: -std=c++17)
*
*       For the STL implementation, refer to the following:
*       Link: http://www.cplusplus.com/reference/forward_list/forward_list/
*
* ===========================================$HISTORY$============================================
* Ean McGilvery     02/04/2021   Inital Commit
**************************************************************************************************/

// INCLUDE GUARDS (You may also see, #pragma once)
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <memory>

template <typename DATA>
struct Node
{
    DATA data; // Element in the Node
    std::shared_ptr<DATA> next; // Pointer to the next Node in the list

    Node() = delete; // We don't want the user to Create a Node without providing a value; Compiler
                     // will throw an error if we try to invoke this
    Node(DATA element) : data(element), next(nullptr) {}
};

template <typename DATA>
class SLL
{
    public:
        // Default Constructor
        SLL() = default;
        // Destructor
        ~SLL();
        // Copy Constructor
        SLL(const SLL& objectToCopy);
        // Copy Assignment Operator
        void operator=(const SLL& objectToCopy);

        // Mutators
        void push_front(DATA);
        void pop_front();
        void insert_after(DATA, Node);
        void remove(); 
        void remove_after(Node);
        void clear();

        // Accessors
        DATA front();
        DATA back();

    private:
        std::shared_ptr<DATA> head_; // Keep tabs on first node of the list
        std::shared_ptr<DATA> tail_; // Keep tabs on the last node of the list

        size_t size_; // Size of our list
};

#endif