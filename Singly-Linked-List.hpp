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
* Justin Stitt      02/16/2021   Refactored unique ptrs, constructor, 
                                 pop_front, push_front, insert_after, 
                                 remove_after, size, print
**************************************************************************************************/

// INCLUDE GUARDS (You may also see, #pragma once)
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <memory>
#include <iostream>

template <typename DATA>
struct Node
{
    DATA data; // Element in the Node
    std::shared_ptr<Node<DATA>> next; // Pointer to the next Node in the list

    Node() = delete; // We don't want the user to Create a Node without providing a value; Compiler
                     // will throw an error if we try to invoke this
    Node(DATA element) : data(element), next(nullptr) {}
};

template <typename DATA>
class SLL
{
    public:
        // Default Constructor
        SLL();
        // Destructor
        ~SLL();         // to-do
        // Copy Constructor
        SLL(const SLL& objectToCopy); // to-do
        // Copy Assignment Operator
        void operator=(const SLL& objectToCopy); // to-do

        // Mutators
        void push_front(DATA);
        void pop_front();
        void insert_after(DATA, int);
        void remove();  // to-do
        void remove_after(int);
        void clear();   // to-do

        // Accessors
        DATA front();   // to-do
        DATA back();    // to-do
        size_t size();
        void print();

    private:
        std::shared_ptr<Node<DATA>> head_; // Keep tabs on first node of the list
        std::shared_ptr<Node<DATA>> tail_; // Keep tabs on the last node of the list

        size_t size_; // Size of our list
};



/*====================================================================================================================*/
/*====================================================================================================================*/
/*====================================================================================================================*/
/*                                              CLASS DEFINITIONS                                                     */
/*====================================================================================================================*/
/*====================================================================================================================*/
/*====================================================================================================================*/



/*====================================================================================================================*/
/* CONSTRUCTORS, DESTRUCTOR AND COPY ASSIGNMENT OPERATOR                                                              */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: SLL
 * Description:
 *      An overloaded constructor that creates a new SLL with a null head and tail
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
SLL<DATA>::SLL() : size_(0), head_(nullptr), tail_(nullptr){}// initialization list

/*************************************************************************** 
 * Function: ~SLL
 * Description:
 *      The Destructor for the SLL, but serves little purpose as our Smart
 *      pointers will already clean up the memory!
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
SLL<DATA>::~SLL()
{ 
    // nothing to do here!
}


/*************************************************************************** 
 * Function: SLL
 * Description:
 *      An overloaded constructor (AKA the copy constructor) that copys the 
 *      contents of a SLL that is already defined, into a new SLL object.
 * Parameters:
 *      const SLL &objectToCopy : SLL to copy from (Note it's a reference)
 * Return:
 *      None 
***************************************************************************/
template<typename DATA>
SLL<DATA>::SLL(const SLL &objectToCopy)
{
    // to-do ...
}

/*************************************************************************** 
 * Function: operator=
 * Description:
 *      The copy assignment operator. This allows us to copy contents of one
 *      prieviously created SLL into another prieviously created SLL.
 * Parameters:
 *      SLL &objectToCopy : SLL to copy from (Note it's a reference)
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::operator=(const SLL<DATA>& objectToCopy)
{
    // to-do ...
}

/*====================================================================================================================*/
/* END OF CONSTRUCTORS, DESTRUCTOR AND COPY ASSIGNMENT OPERATOR                                                       */
/*====================================================================================================================*/



/*====================================================================================================================*/
/* MUTATORS                                                                                                           */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: push_front
 * Description:
 *      Pushes an element into the front of the singly linked list.  
 * Parameters:
 *      DATA inputData : The desired element to be placed into the singly linked list
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::push_front(DATA d)
{
    // Dynamically create the new node
    std::shared_ptr<Node<DATA>> to_add = std::make_shared<Node<DATA>>(d);

    // If the SLL is empty, to_add is now our head
    if(this->size_ == 0){
        this->head_ = to_add;
    }
    else{
        // Reassign 'to_add's next ptr to point to head
        to_add->next = this->head_;
        // Redefine head as our new node
        this->head_ = to_add;
    } 
    ++this->size_;// increment size
}

/*************************************************************************** 
 * Function: insert_after
 * Description:
 *      Pushes an element into the front of the singly linked list.  
 * Parameters:
 *      DATA inputData : The desired element to be placed into the singly linked list
 *      int idx     : The index to insert after. (0:size_-1)
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::insert_after(DATA d, int idx)
{
    if(idx < -1 || idx > static_cast<int>(this->size_-1)){
        throw std::out_of_range("index out of bounds!");
    }

    // Node we want to add
    std::shared_ptr<Node<DATA>> to_add = std::make_shared<Node<DATA>>(d);
    // temp pointer used for iteration
    std::shared_ptr<Node<DATA>> tmp = this->head_;

    // Step through the SLL 'idx' times
    while(idx > 0){
        tmp = tmp->next;
        --idx;
    }
    
    if(idx == -1){// special case if intent is to add to the front
        this->push_front(d);
        return;
    }
    // rearrange pointers
    to_add->next = tmp->next;
    tmp->next = to_add;

    // increment size
    ++this->size_;
}

/*************************************************************************** 
 * Function: pop_front
 * Description:
 *      Remove the first element from the singly linked list
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::pop_front()
{
    // cannot remove from an empty list!
    if(this->size_ <= 0) return;

    // progress head pointer to its neighbour, use reset to remove old head
    this->head_ = this->head_->next;

    /*
        Notice here that although the 'old' head has zero pointers pointing to it
        smart pointers recognize this and will relinquish the memory. -- Yay, no leaks!
        (btw, this is what makes smart pointers 'smart')
    */

   --this->size_;// lastly, decrement size
}

/*************************************************************************** 
 * Function: remove_after
 * Description:
 *      Remove the element after given index from the singly linked list
 * Parameters:
 *      int idx : the index at which we remove the following node from the SLL
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::remove_after(int idx)
{
    if(idx < -1 || idx >= static_cast<int>(this->size_-1)){
        throw std::out_of_range("out of bounds!");
    }

    // temp pointer used for iteration
    std::shared_ptr<Node<DATA>> tmp = this->head_;

    // iterate through the SLL 'idx' times
    while(idx > 0){
        tmp = tmp->next;
        --idx;
    }
    if(idx == -1){// special case if removing front
        this->pop_front();
        return;
    }
    // jump past tmp's neighbour, effectively removing it
    tmp->next = tmp->next->next; // note that next->next may be null here (if idx == size_-1)
    
    --this->size_;// decrement size
}

/*====================================================================================================================*/
/* END OF MODIFIERS                                                                                                   */
/*====================================================================================================================*/



/*====================================================================================================================*/
/* ACCESSORS                                                                                                          */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: print
 * Description:
 *      Prints the singly linked list starting from the head
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::print()
{
    if(this->size_ <= 0) return;// cannot print an empty list!
    std::cout << "\n";// formatting

    // tmp pointer used for iteration
    std::shared_ptr<Node<DATA>> tmp = this->head_;
    while(tmp != nullptr){
        std::cout << tmp->data << " ";
        tmp = tmp->next;
    }
    std::cout << "\n";// formatting
}

/*************************************************************************** 
 * Function: size
 * Description:
 *      Returns the size of the singly linked list
 * Parameters:
 *      None
 * Return:
 *      size_t : size of the linked list 
***************************************************************************/
template <typename DATA>
size_t SLL<DATA>::size()
{
    return this->size_;
}

/*====================================================================================================================*/
/* END OF ACCESSORS                                                                                                   */
/*====================================================================================================================*/



#endif

