/*************************************************************************************************
* File: Vector.hpp
* Description:
*       Basic Vector implementation for CPSC 131 SI @ CSUF.
*       Requires C++ 14 or later (Smart Pointers)
*       (If using clang or g++ compiler specify with the flag: -std=c++17)
*
*       For the STL implementation, refer to the following:
*       Link: http://cplusplus.com/reference/vector/vector/
*
* ===========================================$HISTORY$============================================
* Ean McGilvery     01/28/2021   Inital Commit
* Justin Stitt      01/29/2021   Added empty() function 
* Ean McGilvery     10/30/2021   Added MCSTOR and Move operator=
**************************************************************************************************/

// INCLUDE GUARDS (You may also see, #pragma once)
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <memory>
#include <utility>

template<typename DATA>
class Vector
{
    public:
        // Default Constructor
        Vector();
        // Overloaded Constructor
        Vector(int);
        //Destructor
        ~Vector();
        // Copy Constructor
        Vector(const Vector & objectToCopy);
        // Move Constructor
        Vector(Vector&& objectToMove) noexcept;
        // Copy Assignment Operator
        Vector<DATA>& operator=(const Vector &objectToCopy);
        // Move Assignment Operator
        Vector<DATA>& operator=(Vector&& objectToMove) noexcept;

        // Mutators
        void push_back(DATA data);
        void insertAt(size_t index, DATA data);
        void clear();
        void pop_back();

        // Accessors
        DATA const& front();
        DATA const& back();
        size_t const& size();
        size_t const& capacity();
        bool empty();
        // Used for testing purposes
        void displayVector();

    private:
        // Main Container
        std::unique_ptr<DATA[]> array_; 

        // Used to keep track of contents
        size_t capacity_;
        size_t size_;

        // Called when expanding Vector
        void resize();
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
 * Function: Vector
 * Description:
 *      An overloaded constructor that creates a new Vector with a user
 *      defined capacity.
 * Parameters:
 *      int userDefinedCapacity : integer that will determine the initial
 *                                capacity of the vector.
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
Vector<DATA>::Vector(int userDefinedCapacity) : 
array_(new DATA[userDefinedCapacity]), capacity_(userDefinedCapacity), size_(0) {}
/*************************************************************************** 
 * Function: Vector (Default Constructor)
 * Description:
 *      The default constructor that creates a new Vector with a capacity 
 *      of 10.
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
Vector<DATA>::Vector() : Vector(10) {}

/*************************************************************************** 
 * Function: Vector (Copy Constructor)
 * Description:
 *      An overloaded constructor (AKA the copy constructor) that copys the 
 *      contents of a Vector that is already defined, into a new Vector 
 *      object.
 * Parameters:
 *      const Vector &objectToCopy : Vector to copy from (Note it's a reference)
 * Return:
 *      None 
***************************************************************************/
template<typename DATA>
Vector<DATA>::Vector(const Vector &objectToCopy) : 

array_(std::make_unique<DATA[]>(capacity_)), size_(objectToCopy.size_), capacity_(objectToCopy.capacity_)
{
    std::cout << "CSTOR was called...\n";
    // Copy each element into their respective space
    for(int index = 0; index < size_; index++)
        array_[index] = objectToCopy.array_[index];
}

/*************************************************************************** 
 * Function: Vector (Move Constructor)
 * Description:
 *      An overloaded constructor that moves the 
 *      contents of a Vector that is already defined, into a new Vector 
 *      object. The old Vector is reset to a default state.
 * Parameters:
 *      Vector&& objectToMove : Vector to move contents from
 * Return:
 *      None 
***************************************************************************/
template<typename DATA>
Vector<DATA>::Vector(Vector&& objectToMove) noexcept :

array_   (std::move(objectToMove.array_)), 
capacity_(std::move(objectToMove.capacity_)),
size_    (std::move(objectToMove.size_))
{
    std::cout << "Move CSTOR Called...\n";
    // Set Old Vec to valid state
    objectToMove.capacity_ = 10;
    objectToMove.array_ = std::make_unique<DATA[]>(objectToMove.capacity_);
    objectToMove.size_ = 0;
}

/*************************************************************************** 
 * Function: ~Vector
 * Description:
 *      The Destructor for the Vector, but serves little purpose as our Smart
 *      pointers will already clean up the memory!
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
Vector<DATA>::~Vector()
{ 
    std::cout << "Destrucor was called...\n";
}

/*************************************************************************** 
 * Function: operator=
 * Description:
 *      The copy assignment operator. This allows us to copy contents of one
 *      prieviously created Vector into another prieviously created Vector.
 * Parameters:
 *      Vector &objectToCopy : Vector to copy from (Note it's a reference)
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
Vector<DATA>& Vector<DATA>::operator=(const Vector<DATA>& objectToCopy)
{
    std::cout << "Copy Assign Op Called...\n";
    // Copy each member variable over into the new object that's being
    capacity_ = objectToCopy.capacity_;
    size_ = objectToCopy.size_;
    array_.reset(new DATA[capacity_]);

    // Copy each element into their respective space
    for(auto index = 0; index < size_; index++)
    {
        array_[index] = objectToCopy.array_[index];
    }

    return *this;
}

template <typename DATA>
Vector<DATA>& Vector<DATA>::operator=(Vector&& objectToMove) noexcept
{ 
    std::cout << "Move Assign Op Called...\n";
    if(&objectToMove != this)
    {
        this->array_    = std::move(objectToMove.array_);
        this->capacity_ = std::move(objectToMove.capacity_);
        this->size_     = std::move(objectToMove.size_);
    }

    return *this;   
}
/*====================================================================================================================*/
/* END OF CONSTRUCTORS, DESTRUCTOR AND COPY ASSIGNMENT OPERATOR                                                       */
/*====================================================================================================================*/



/*====================================================================================================================*/
/* MUTATORS                                                                                                           */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: push_back
 * Description:
 *      Pushes an element into the back of the vector.  
 * Parameters:
 *      DATA inputData : The desired element to be placed into the Vector
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void Vector<DATA>::push_back(DATA inputData)
{
    // Check to see that if we add another element that we have space
    // In this implementation, we double the capacity only if we try to add to an
    // already full Vector.
    if(size_ == capacity_)
        resize();

    // Add new element and, incriment our size variable
    array_[size_] = inputData;
    size_++;
}

/*************************************************************************** 
 * Function: insertAt
 * Description:
 *      Inserts an element at a specific location in the Vector. This 
 *      implementation will push the current contents back to make space, 
 *      instead of overwriting the data, if there is prexisting data.
 * Parameters:
 *      size_t index     : The location to insert the new element
 *      DATA   inputData : The desired element to be placed into the Vector 
 * Return:
 *      None 
***************************************************************************/
template <typename DATA>
void Vector<DATA>::insertAt(size_t index, DATA inputData)
{
    // Check to see if the index is valid
    if(index < capacity_ - 1 && index > 0)
    {
        // Resize the Vector if necessary
        if(size_ == capacity_)
            resize();

        // Push the contents of the Vector back to make space
        for(auto i = size_ + 1; i > index; i--)
            array_[i] = array_[i - 1];
        
        // Finally, insert the value at the desired index
        array_[index] = inputData;
    }
    else
        throw std::out_of_range("Not a valid Index to Insert.");
    
    // Update counter
    size_++;
}


/*************************************************************************** 
 * Function: pop_back
 * Description:
 *      Removes the element at the back of the vector.
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template<typename DATA>
void Vector<DATA>::pop_back()
{
    // Remove back element in Vector
    size_--;
}

/*************************************************************************** 
 * Function: pop_back
 * Description:
 *      Removes the element at the back of the vector.
 * Parameters:
 *      None
 * Return:
 *      None 
***************************************************************************/
template<typename DATA>
void Vector<DATA>::clear()
{
    // Call the reset method to release the old memory, and allocate new memory
     array_.reset(new DATA[10]);

     // Reset the counter variables
     capacity_ = 10;
     size_ = 0;
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
 *      Returns the value at the front of the vector
 * Parameters:
 *      None
 * Return:
 *      DATA : The front element in the vector 
***************************************************************************/
template<typename DATA>
DATA const& Vector<DATA>::front()
{
    return array_[0];
}

/*************************************************************************** 
 * Function: back
 * Description:
 *      Returns the value at the back of the vector
 * Parameters:
 *      None
 * Return:
 *      DATA : The back element in the vector 
***************************************************************************/
template<typename DATA>
DATA const& Vector<DATA>::back()
{
    return array_[size_ - 1];
}

/*************************************************************************** 
 * Function: size
 * Description:
 *      Returns the current size of the vector
 * Parameters:
 *      None
 * Return:
 *      size_t : The size of the vector 
***************************************************************************/
template<typename DATA>
size_t const& Vector<DATA>::size()
{
    return size_;
}

/*************************************************************************** 
 * Function: capacity
 * Description:
 *      Returns the total capacity of the vector
 * Parameters:
 *      None
 * Return:
 *      size_t : The capacity of the vector 
***************************************************************************/
template<typename DATA>
size_t const& Vector<DATA>::capacity()
{
    return capacity_;
}

/*************************************************************************** 
 * Function: empty
 * Description:
 *      Returns whether or not the vector is empty
 * Parameters:
 *      None
 * Return:
 *      bool : true = vector is empty, false = vector is not empty 
***************************************************************************/
template<typename DATA>
bool Vector<DATA>::empty()
{
    return (size_ > 0) ? false : true;
}

/*====================================================================================================================*/
/* END OF ACCESSORS                                                                                                   */
/*====================================================================================================================*/




/*====================================================================================================================*/
/* HELPER FUNCTIONS (NOT TO BE EXPLICITLY CALLED)                                                                     */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: resize
 * Description:
 *      Creates a temporary vector with double the capacity of the original,
 *      and then copies the contents over.
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
template <typename DATA>
void Vector<DATA>::resize()
{
    // create a temporary Array that's double the capacity
    std::unique_ptr<DATA[]> tempArr (new DATA[capacity_ * 2]);

    // Load the temporary array with what we have now
    for(auto index = 0; index < size_; index++)
        tempArr[index] = array_[index];

    // Reassign the class array to pointer to the new array's address
    array_ = std::move(tempArr);

    // Update the capacity
    capacity_ *= 2;
}

/*====================================================================================================================*/
/* END OF HELPER FUNCTIONS                                                                                            */
/*====================================================================================================================*/




/*====================================================================================================================*/
/* EXTRA FUNCTIONS USED FOR TESTING/DEBUGGING                                                                         */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: displayvector
 * Description:
 *      Prints out the contents of the vector to the console.
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
template<typename DATA>
void Vector<DATA>::displayVector()
{
    for(auto index = 0; index < size_; index++)
        std::cout << array_[index] << " ";

    std::cout << std::endl;
}
/*====================================================================================================================*/
/* END OF EXTRA FUNCTIONS                                                                                          */
/*====================================================================================================================*/
#endif //DATASTRUCTURES_VECTOR_H
