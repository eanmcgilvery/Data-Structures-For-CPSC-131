// Implementation of the Vector Class

#include <stdexcept>
#include "Vector.h"

/*====================================================================================================================*/
/* CONSTRUCTORS, DESTRUCTOR AND COPY ASSIGNMENT OPERATOR                                                              */
/*====================================================================================================================*/

// Overloaded Constructor
template <typename DATA>
Vector<DATA>::Vector(int userDefinedCapacity) : _capacity(userDefinedCapacity), _array(new DATA[userDefinedCapacity]),
                                                    _size(0) {}
// Default Constructor
template <typename DATA>
Vector<DATA>::Vector() : Vector(10) {}

// Copy Constructor
template<typename DATA>
Vector<DATA>::Vector(const Vector &objectToCopy)
{
    // Copy each member variable over into the new object that's being
    _capacity = objectToCopy._capacity;
    _size = objectToCopy._size;
    _array = new DATA[_capacity];

    // Copy each element into their respective space
    for(auto index = 0; index < _size; index++)
    {
        _array[index] = objectToCopy._array[index];
    }
}

// Destructor
template <typename DATA>
Vector<DATA>::~Vector()
{
    // Free memory
    delete []_array;

    // Prevent Dangling Pointer
    _array = nullptr;
}

// Copy Assignment Operator
template <typename DATA>
void Vector<DATA>::operator=(const Vector<DATA>& objectToCopy)
{
    // Copy each member variable over into the new object that's being
    _capacity = objectToCopy._capacity;
    _size = objectToCopy._size;

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

// Push element into the back of the Vector
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

// Inserts Element before the specified index
template <typename DATA>
void Vector<DATA>::insertAt(size_t index, DATA data)
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
        _array[index] = data;
    }
    else
        throw std::out_of_range("Not a valid Index to Insert.");
    
    // Update counter
    _size++;
}


// Remove all elements from the Vector and reset everything to default values
template<typename DATA>
void Vector<DATA>::pop_back()
{
    // Remove back element in Vector
    _size--;
}

// Remove all elements from the Vector and reset everything to default values
template<typename DATA>
void Vector<DATA>::clear()
{
    // Create space on heap for _array to point to
     DATA* temp = new DATA[10];

     // Free contents of old Vector
     delete []_array;

     // Point our Array to the allocated space on the Heap
     _array = temp;

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

// Return the first element in the Vector
template<typename DATA>
DATA const& Vector<DATA>::front()
{
    return _array[0];
}

// Return the last item in the Vector
template<typename DATA>
DATA const& Vector<DATA>::back()
{
    return _array[_size - 1];
}

// Return the current number of elements stored in the Vector
template<typename DATA>
size_t const& Vector<DATA>::size()
{
    return _size;
}

template<typename DATA>
size_t const& Vector<DATA>::capacity()
{
    return _capacity;
}

/*====================================================================================================================*/
/* END OF ACCESSORS                                                                                                   */
/*====================================================================================================================*/




/*====================================================================================================================*/
/* HELPER FUNCTIONS (NOT TO BE EXPLICITLY CALLED)                                                                     */
/*====================================================================================================================*/

// Resize the vector by doubling it's capacity
template <typename DATA>
void Vector<DATA>::_resize()
{
    // create a temporary Array that's double the capacity
    DATA* tempArr = new DATA[_capacity * 2];

    // Load the temporary array with what we have now
    for(auto index = 0; index < _size; index++)
        tempArr[index] = _array[index];

    // Reassign the class array to pointer to the new array's address
    _array = tempArr;

    // Update the capacity
    _capacity *= 2;
}

/*====================================================================================================================*/
/* END OF HELPER FUNCTIONS                                                                                            */
/*====================================================================================================================*/




/*====================================================================================================================*/
/* EXTRA FUNCTIONS USED FOR TESTING/DEBUGGING                                                                         */
/*====================================================================================================================*/
template<typename DATA>
void Vector<DATA>::displayVector()
{
    for(auto index = 0; index < _size; index++)
        std::cout << _array[index] << " ";

    std::cout << std::endl;
}
/*====================================================================================================================*/
/* END OF EXTRA FUNCTIONS TO                                                                                          */
/*====================================================================================================================*/