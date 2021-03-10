/*************************************************************************************************
* File: Stack_ListBased.hpp
* Description:
*       Basic Stack implementation for CPSC 131 SI @ CSUF.
*       Underlying container is a Singly Linked List
*       Requires C++ 14 or later (Smart Pointers)
*       (If using clang or g++ compiler specify with the flag: -std=c++17)
*
*       For the STL implementation, refer to the following:
*       Link: https://www.cplusplus.com/reference/stack/stack/
*
* ===========================================$HISTORY$============================================
* Ean McGilvery     03/09/2021   Inital Commit
**************************************************************************************************/
#ifndef STACK_LISTBASED_H
#define STACK_LISTBASED_H

#include "Singly-Linked-List.hpp"

template <typename DATA>
class Stack
{
    public:

        // Constructors, Rule of Three
        Stack() = default;
        ~Stack();
        Stack(const Stack&);
        void operator=(const Stack&);

        // Mutators
        void push(DATA);
        void pop();

        // Accessors
        bool empty();
        size_t size();
        DATA top();

    private:
        SLL<DATA> container_; // Underlying container that data will be held in
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
 * Function: Stack
 * Description:
 *      Destructor. Served no purpose here.
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
Stack<DATA>::~Stack() {}

/*************************************************************************** 
 * Function: Stack
 * Description:
 *      Copy Constructor. Copy the contents of one Stack into ours
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
Stack<DATA>::Stack(const Stack& rhs) 
{
    container_(rhs.container_);
}

/*************************************************************************** 
 * Function: operator=
 * Description:
 *      Operator '=' overlaod to allow copying contents of one stack into
 *          another.
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void Stack<DATA>::operator=(const Stack& rhs)
{
    container_ = rhs.container_;
}
/*====================================================================================================================*/
/* END OF CONSTRUCTORS, DESTRUCTOR AND COPY ASSIGNMENT OPERATOR                                                       */
/*====================================================================================================================*/


/*====================================================================================================================*/
/* MUTATORS                                                                                                           */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: push
 * Description:
 *      push a the desired element onto the top of the Stack
 * Parameters:
 *      DATA element : The desired element to be inserted into the stack.
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void Stack<DATA>::push(DATA element)
{
    container_.push_front(element);
}

/*************************************************************************** 
 * Function: pop
 * Description:
 *      Pop off the element from the top of the Stack. NOTE! does not return 
 *          the element
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void Stack<DATA>::pop()
{
    // Remove front element
    container_.pop_front();
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
 *      Checks whether the stack is empty.
 * Parameters:
 *      None
 * Return:
 *      bool : the 
***************************************************************************/
template <typename DATA>
bool Stack<DATA>::empty()
{
    // Because 0 == false in a boolean, this will still give us the correct
    //  info desired.
    return container_.size(); 
}

/*************************************************************************** 
 * Function: size
 * Description:
 *      Return the size of the stack.
 * Parameters:
 *      None
 * Return:
 *      size_t : the number of elements in the stack.
***************************************************************************/
template <typename DATA>
size_t Stack<DATA>::size()
{
    return container_.size();
}

/*************************************************************************** 
 * Function: top
 * Description:
 *      Returns the element on the top of the stack.
 * Parameters:
 *      None
 * Return:
 *      DATA : the element residing on the top of the stack. 
***************************************************************************/
template <typename DATA>
DATA Stack<DATA>::top()
{
    return container_.front();
}

/*====================================================================================================================*/
/* END OF ACCESSORS                                                                                                   */
/*====================================================================================================================*/

#endif // STACK_LISTBASED_H