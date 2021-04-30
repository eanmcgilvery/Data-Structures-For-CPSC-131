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
* Ean McGilvery     03/08/2021   Added overloaded insert_after, remove_after, destuctor, clear.
*                                   Refactored previous functions to use sentinel nodes.
* Janeen Yamak      03/08/2021   Added reverse.
* Justin Stitt      03/09/2021   Added operator=
* Justin Stitt      04/30/2021   Added front(), back(), copy constructor
**************************************************************************************************/

// INCLUDE GUARDS (You may also see, #pragma once)
#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <memory>
#include <iostream>
#include <stdexcept>

template <typename DATA>
struct Node
{
    DATA data; // Element in the Node
    std::shared_ptr<Node<DATA>> next; // Pointer to the next Node in the list

    Node() = default;
    Node(DATA element) : data(element), next(nullptr) {}
};

template <typename DATA>
class SLL
{
    public:
        // Default Constructor
        SLL();
        // Destructor
        ~SLL();
        // Copy Constructor
        SLL(const SLL& objectToCopy);
        // Copy Assignment Operator
        void operator=(const SLL& objectToCopy);

        // Mutators
        void push_front(DATA);
        void pop_front();
        void insert_after(DATA, int); // Insert After Given an "Index"
        void insert_after(DATA, std::shared_ptr<Node<DATA>>); // Insert After given a Pointer
        void remove();  // to-do
        void remove_after(int);
        void remove_after(std::shared_ptr<Node<DATA>>);
        void clear();   
        

        // Accessors
        DATA front();
        DATA back();
        size_t size();
        void print();
        std::shared_ptr<Node<DATA>> search(DATA);
        
        // Fun Functions!  :)
        void reverse();

    private:
        std::shared_ptr<Node<DATA>> head_; // Keep tabs on first node of the list
        std::shared_ptr<Node<DATA>> tail_; // Keep tabs on the last node of the list

        // Mutators
        void clear(std::shared_ptr<Node<DATA>>); // Helper to Clear

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
 *      An overloaded constructor that creates a new SLL with Sentinel Nodes
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
SLL<DATA>::SLL() : head_(new Node<DATA>()), tail_(new Node<DATA>()), size_(0) 
{
    // Create an empty list (using Sentinel Nodes)
    head_->next = tail_;
}

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
    clear();
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
SLL<DATA>::SLL(const SLL& objectToCopy)
{
    this = objectToCopy;
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
void SLL<DATA>::operator=(const SLL<DATA>& rhs)
{
    // Empty out this linked list before copying over right-hand side list
    this->clear();

    // Pointer to the source and destination
    auto src = rhs.head_, dst = this->head_;

    for(; src->next != rhs.tail_; src = src->next, dst = dst->next, ++this->size_){
        // copy old data
        DATA old = src->next->data;
        // allocate new memory based off old data
        std::shared_ptr<Node<DATA>> to_add(new Node<DATA>(old));
        // place this new node into 'this' list
        dst->next = to_add;
        to_add->next = this->tail_;
    }

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
 *      DATA element : The desired element to be placed into the singly linked list
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::push_front(DATA element)
{
    // Dynamically create the new node
    std::shared_ptr<Node<DATA>> to_add(new Node<DATA> (element));

    // Reassign 'to_add's next ptr to point to head
    to_add->next = head_->next;
    
    // Redefine head as our new node
    head_->next = to_add;
    
    size_++;// increment size
}

/*************************************************************************** 
 * Function: insert_after
 * Description:
 *      Pushes an element into the front of the singly linked list.  
 * Parameters:
 *      DATA d  : The desired element to be placed into the singly linked list
 *      int idx : The index to insert after. (0 : size_-1)
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::insert_after(DATA d, int idx)
{
    if(idx < 0 || idx > static_cast<int>(this->size_-1)){
        throw std::out_of_range("ERROR: index out of bounds!");
    }

    // Node we want to add
    std::shared_ptr<Node<DATA>> to_add = std::make_shared<Node<DATA>>(d);

    // temp pointer used for iteration. Begins at first node.
    std::shared_ptr<Node<DATA>> tmp(head_->next);

    // Step through the SLL 'idx' times
    while(idx > 0)
    {
        tmp = tmp->next;
        idx--;
    }

    // rearrange pointers
    to_add->next = tmp->next;
    tmp->next = to_add;

    // increment size
    size_++;
}

/*************************************************************************** 
 * Function: insert_after
 * Description:
 *      Inserts an element into a list after a given node within the list.  
 * Parameters:
 *      DATA inputData : The desired element to be placed into the singly linked list
 *      std::shared_ptr<Node<DATA>> position   : The index to insert after.
 * Return:  
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::insert_after(DATA element, std::shared_ptr<Node<DATA>> position)
{
    // Bounds checking! Make sure the 
    if(!position || position == this->tail_)
        throw std::out_of_range("INVALID POSITION GIVEN!");

    // Encapsualte the ele into a Node
    std::shared_ptr<Node<DATA>> nodeToInsert(new Node<DATA>(element)); 

    // Attach our new node to hold onto the list, before we detach 'position'
    nodeToInsert->next = position->next;

    // Have 'position' point to the new Node
    position->next = nodeToInsert;

    // Update the Size of our linked list
    size_++; 
}

/*************************************************************************** 
 * Function: remove_after
 * Description:
 *      Removes in a list at a given place within the list.  
 * Parameters:
 *      DATA inputData : The desired element to be placed into the singly linked list
 *      std::shared_ptr<Node<DATA>> position   : The index to insert after. (0:size_-1)
 * Return:  
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::remove_after(std::shared_ptr<Node<DATA>> position)
{
    if(position == head_ || position == tail_ || !position)
        return;

    position->next = position->next->next;
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
    if(size_ <= 0) return;

    // progress head pointer to its neighbour, use reset to remove old head
    head_->next = head_->next->next;

    /*
        Notice here that although the 'old' head has zero pointers pointing to it
        smart pointers recognize this and will relinquish the memory. -- Yay, no leaks!
        (btw, this is what makes smart pointers 'smart')
    */

   size_--; // lastly, decrement size
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
    if(idx < 0 || idx >= static_cast<int>(this->size_-1))
        throw std::out_of_range("ERROR: index out of bounds!");


    // temp pointer used for iteration
    std::shared_ptr<Node<DATA>> tmp(head_);

    // iterate through the SLL 'idx' times
    while(idx > 0)
    {
        tmp = tmp->next;
        --idx;
    }
    
    // jump past tmp's neighbour, effectively removing it
    tmp->next = tmp->next->next; // note that next->next may be null here (if idx == size_-1)
    
    --this->size_;// decrement size
}

/*************************************************************************** 
 * Function: clear
 * Description:
 *      Removes all the nodes within a linked list, leaving only the sentinel 
 *          nodes. This is the user facing wrapper.
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::clear()
{
    // Pass in the first Node in the list
    clear(head_->next); 

    /*
    *  Note! We could also have iteratively used pop_front to clear!
    *  We implemented this way to get some good ol' recursion practice in. 
    */
}

/*************************************************************************** 
 * Function: clear
 * Description:
 *      Removes all the nodes within a linked list, leaving only the sentinel 
 *          nodes. 
 * Parameters:
 *      std::shared_ptr<Node<DATA>> position : the node in which to begin removal.
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::clear(std::shared_ptr<Node<DATA>> position)
{
    // Base Case: Check to see if list is empty or at the end of the list
    if (position == tail_ || size_ == 0)
        return;
    
    // Recursive call, till we get to the last node
    clear(position->next);

    /*
    * Break the chain to the node we're pointing at. The Smart pointers will
    * clean up the allocated memory and wipe the node. 
    */
    position->next = nullptr;

    // Update the size;
    size_--;
}

/*====================================================================================================================*/
/* END OF MODIFIERS                                                                                                   */
/*====================================================================================================================*/



/*====================================================================================================================*/
/* ACCESSORS                                                                                                          */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: front
 * Description:
 *      Returns the front element of the sinlgy linked list.
 * Parameters:
 *      None
 * Return:
 *      Element of type DATA at the front of the list 
***************************************************************************/
template <typename DATA>
DATA SLL<DATA>::front(){
    if(!this->size()){
        throw std::out_of_range("ERROR: cannot access the front of empty Queue");
    }
    return this->head_->next->data;
}

/*************************************************************************** 
 * Function: back
 * Description:
 *      Returns the back element of the sinlgy linked list.
 * Parameters:
 *      None
 * Return:
 *      Element of type DATA at the back of the list 
***************************************************************************/
template <typename DATA>
DATA SLL<DATA>::back(){
    if(!this->size()){
        throw std::out_of_range("ERROR: cannot access the back of empty Queue");
    }
    return this->tail_->data;
}

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
    std::shared_ptr<Node<DATA>> tmp(head_->next);

    std::cout << "[HEAD]-> ";
    while(tmp != tail_)
    {
        std::cout << tmp->data << "-> ";
        tmp = tmp->next;
    }
    std::cout << "[TAIL]-> nullptr\n";
}

/*************************************************************************** 
 * Function: size
 * Description:
 *      Returns the size of the Singly linked list
 * Parameters:
 *      None
 * Return:
 *      size_t : size of the linked list 
***************************************************************************/
template <typename DATA>
size_t SLL<DATA>::size()
{
    return size_;
}

/*====================================================================================================================*/
/* END OF ACCESSORS                                                                                                   */
/*====================================================================================================================*/


/*************************************************************************** 
 * Function: search
 * Description:
 *      Looks for the given element in the list, and returns a pointer to the location
 * Parameters:
 *      DATA element : the element to try to find in the list.
 * Return:
 *      std::shared_ptr<Node<DATA>> : pointer to the postion of the ele in the list. 
 *                                      nullptr if the element is not found.
***************************************************************************/
template <typename DATA>
std::shared_ptr<Node<DATA>> SLL<DATA>::search(DATA element) 
{
    // Create a pointer to move through the list. Start at the first element.
    std::shared_ptr<Node<DATA>> position(head_->next);

    // Step through each element until position reachs the end of the list.
    while(position != tail_)
    {
        // Look to see if we found the desired data.
        if(position->data == element)
            return position;

        position = position->next;
    }
    return nullptr;
}

/*====================================================================================================================*/
/* FUN FUNCTIONS                                                                                                      */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: reverse
 * Description:
 *      Reverses the contents of a Linked List! 
 * Parameters:
 *      none 
 * Return:
 *      none 
***************************************************************************/
template <typename DATA>
void SLL<DATA>::reverse()
{
    // Nothing to Reverse!
    if(size_ <= 1)
        return;
    
    // Create three pointers, initially at the first three elements in the list
    std::shared_ptr<Node<DATA>> p1 = head_->next;
    std::shared_ptr<Node<DATA>> p2 = p1->next;
    std::shared_ptr<Node<DATA>> p3 = p2->next;


    p1->next = tail_;
    
    while(p3!=tail_)
    {
        p2->next = p1;

        p1 = p2;
        p2 = p3;
        p3 = p3->next;
    }

    p2->next = p1;
    head_->next = p2;
}

/*====================================================================================================================*/
/* END OF FUN FUNCTIONS                                                                                               */
/*====================================================================================================================*/
#endif