/*************************************************************************************************
* File: Queue_ListBased.hpp
* Description:
*       Basic Queue implementation for CPSC 131 SI @ CSUF.
*       Underlying container is a Singly Linked List
*       Requires C++ 14 or later (Smart Pointers)
*       (If using clang or g++ compiler specify with the flag: -std=c++17)
*
*       For the STL implementation, refer to the following:
*       Link: https://en.cppreference.com/w/cpp/container/queue/
*
* ===========================================$HISTORY$============================================
* Justin Stitt     04/30/2021   Inital Commit
* Justin Stitt     04/30/2021   entire implementation, operator<<
**************************************************************************************************/
/* Include Guard (create copy of translation unit ONCE) */
#pragma once

#include "Singly-Linked-List.hpp"
#include <iostream>

using std::ostream;

template <typename DATA>
class Queue{
private:
    /* Underlying data that our Queue will abstract from */
    SLL<DATA> container_;

    template <typename T>
    friend ostream& operator<<(ostream&, const Queue<T>&);
public:
    // Constructors, Rule of Three

    /* tell the compiler to create default constructor */
    Queue() = default; 
    /* Destructor */
    ~Queue(); 
    /* Copy Constructor */
    Queue(const Queue&);
    /* Assignment Operator */
    void operator=(const Queue&);

    // Mutators
    void enqueue(DATA);
    void dequeue();

    // Accessors
    bool empty();
    size_t size();
    DATA front();
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
 * Function: ~Queue
 * Description:
 *      Destructor. Served no purpose here.
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
Queue<DATA>::~Queue() {}

/*************************************************************************** 
 * Function: Queue
 * Description:
 *      Copy Constructor. Copy the contents of one Queue into ours
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
Queue<DATA>::Queue(const Queue& rhs){
    this->container_ = rhs.container_;
}

/*************************************************************************** 
 * Function: operator=
 * Description:
 *      Operator '=' overlaod to allow copying contents of one queue into
 *          another.
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void Queue<DATA>::operator=(const Queue& rhs){
    this->container_ = rhs.container;
}
/*====================================================================================================================*/
/* END OF CONSTRUCTORS, DESTRUCTOR AND COPY ASSIGNMENT OPERATOR                                                       */
/*====================================================================================================================*/


/*====================================================================================================================*/
/* MUTATORS                                                                                                           */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: enqueue
 * Description:
 *      enqueue (add) the desired element to the back of the Queue
 * Parameters:
 *      DATA element : The desired element to be inserted into the queue.
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void Queue<DATA>::enqueue(DATA element){
    if(this->empty()) { this->container_.push_front(element); return; }
    this->container_.insert_after(element, this->size() - 1);
}

/*************************************************************************** 
 * Function: dequeue
 * Description:
 *      dequeue (remove) off the element from the front of the Queue. 
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void Queue<DATA>::dequeue(){
    this->container_.pop_front();
}

/*====================================================================================================================*/
/* END OF MUTATORS                                                                                                    */
/*====================================================================================================================*/


/*====================================================================================================================*/
/* ACCESSORS                                                                                                          */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: empty
 * Description:
 *      Checks whether the queue is empty.
 * Parameters:
 *      None
 * Return:
 *      bool : the emptiness state of the queue
***************************************************************************/
template <typename DATA>
bool Queue<DATA>::empty(){
    /* If size is 0, negate it to get 1 (True). */
    return !this->container_.size();
}

/*************************************************************************** 
 * Function: size
 * Description:
 *      Return the size of the queue.
 * Parameters:
 *      None
 * Return:
 *      size_t : the number of elements in the queue.
***************************************************************************/
template <typename DATA>
size_t Queue<DATA>::size(){
    return this->container_.size();
}

/*************************************************************************** 
 * Function: front
 * Description:
 *      Returns the element at the front of the queue.
 * Parameters:
 *      None
 * Return:
 *      DATA : the element residing at the front of the queue. 
***************************************************************************/
template <typename DATA>
DATA Queue<DATA>::front(){
    return this->container_.front();
}

/*====================================================================================================================*/
/* END OF ACCESSORS                                                                                                   */
/*====================================================================================================================*/


/*====================================================================================================================*/
/* FRIEND FUNCTIONS                                                                                                           */
/*====================================================================================================================*/
/*************************************************************************** 
 * Function: operator<<
 * Description:
 *      Returns stream object with formatted Queue data
 * Parameters:
 *      ostream& and Queue&
 * Return:
 *      An output stream object reference
***************************************************************************/
template <typename DATA>
ostream& operator<<(ostream& os, const Queue<DATA>& obj){
    /* Create destructive copy of obj */
    Queue<DATA> to_print(obj);

    /* Formatting sugar */
    auto first = '[', last = ']', delim = ',';
    int sz = 1;

    while(!to_print.empty()){
        if(!(sz++^1)) os << "["; // if sz is 1 print opening square bracket

        /* only print commas if not last, else print closing square bracket */
        os << to_print.front() << 
                    (to_print.size()^1 ? delim : last); 
        to_print.dequeue();
    }
    
    /* If our original queue was empty, print message */
    if(!(sz^1)){
        os << "Empty Queue";
    }

    /* add new line to end of stream */
    os << "\n";
    return os;
}

/*====================================================================================================================*/
/* END OF FRIEND FUNCTIONS                                                                                                           */
/*====================================================================================================================*/
