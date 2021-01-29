/*************************************************************************************************
* File: Vector.hpp
* Description:
*       Basic Vector implementation for CPSC 131 SI @ CSUF.
*       Requires C++ 11 or later (Smart Pointers)
*       (If using clang or g++ compiler specify with the flag: -std=c++17)
*
*       For the STL implementation, refer to the following:
*       Link: http://cplusplus.com/reference/vector/vector/
*
* ===========$HISTORY=============
* Ean McGilvery     01/28/2021
**************************************************************************************************/

// INCLUDE GUARDS (You may also see, #pragma once)
#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <memory>

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
        // Copy Assignment Operator
        void operator=(const Vector &objectToCopy);

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
		bool const& empty();
        // Used for testing purposes
        void displayVector();

    private:
        // Main Container
        std::unique_ptr<DATA[]> _array; 

        // Used to keep track of contents
        size_t _capacity;
        size_t _size;

        // Called when expanding Vector
        void _resize();
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
Vector<DATA>::Vector(int userDefinedCapacity) : _capacity(userDefinedCapacity), _array(new DATA[userDefinedCapacity]),
                                                    _size(0) {}
/*************************************************************************** 
 * Function: Vector
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
 * Function: Vector
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
Vector<DATA>::Vector(const Vector &objectToCopy)
{
    // Copy each member variable over into the new object that's being
    _capacity = objectToCopy._capacity;
    _size = objectToCopy._size;
    _array = std::unique_ptr<DATA>(new DATA[_capacity]); // Note we need to create space

    // Copy each element into their respective space
    for(int index = 0; index < _size; index++)
        _array[index] = objectToCopy._array[index];
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
void Vector<DATA>::operator=(const Vector<DATA>& objectToCopy)
{
    // Copy each member variable over into the new object that's being
    _capacity = objectToCopy._capacity;
    _size = objectToCopy._size;
    _array.reset(new DATA[_capacity]);

    
    // Copy each element into their respective space
    for(auto index = 0; index < _size; index++)
    {
        _array[index] = objectToCopy._array[index];
    }
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
    if(_size == _capacity)
        _resize();

    // Add new element and, incriment our size variable
    _array[_size] = inputData;
    _size++;
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
    if(index < _capacity - 1 && index > 0)
    {
        // Resize the Vector if necessary
        if(_size == _capacity)
            _resize();

        // Push the contents of the Vector back to make space
        for(auto i = _size + 1; i > index; i--)
            _array[i] = _array[i - 1];
        
        // Finally, insert the value at the desired index
        _array[index] = inputData;
    }
    else
        throw std::out_of_range("Not a valid Index to Insert.");
    
    // Update counter
    _size++;
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
    _size--;
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
     _array.reset(new DATA[10]);

     // Reset the counter variables
     _capacity = 10;
     _size = 0;
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
    return _array[0];
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
    return _array[_size - 1];
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
    return _size;
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
    return _capacity;
}

/*************************************************************************** 
 * Function: empty
 * Description:
 *      Returns whether or not the vector is empty
 * Parameters:
 *      None
 * Return:
 *      bool : true = vectory is empty, false = vector is not empty 
***************************************************************************/
template<typename DATA>
bool const& Vector<DATA>::empty()
{
	return (_size > 0 ? false : true);
}

/*====================================================================================================================*/
/* END OF ACCESSORS                                                                                                   */
/*====================================================================================================================*/




/*====================================================================================================================*/
/* HELPER FUNCTIONS (NOT TO BE EXPLICITLY CALLED)                                                                     */
/*====================================================================================================================*/

/*************************************************************************** 
 * Function: _resize
 * Description:
 *      Creates a temporary vector with double the capacity of the original,
 *      and then copies the contents over.
 * Parameters:
 *      None
 * Return:
 *      None
***************************************************************************/
template <typename DATA>
void Vector<DATA>::_resize()
{
    // create a temporary Array that's double the capacity
    std::unique_ptr<DATA[]> tempArr (new DATA[_capacity * 2]);

    // Load the temporary array with what we have now
    for(auto index = 0; index < _size; index++)
        tempArr[index] = _array[index];

    // Reassign the class array to pointer to the new array's address
    _array = std::move(tempArr);

    // Update the capacity
    _capacity *= 2;
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
    for(auto index = 0; index < _size; index++)
        std::cout << _array[index] << " ";

    std::cout << std::endl;
}
/*====================================================================================================================*/
/* END OF EXTRA FUNCTIONS                                                                                          */
/*====================================================================================================================*/
#endif //DATASTRUCTURES_VECTOR_H
