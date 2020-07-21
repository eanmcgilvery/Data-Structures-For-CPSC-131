// Basic Vector implementation
// Requires C++ 11 or later
// (If using clang compiler specify with the flag: -std=c++17)
//
// For the STL implementation, refer to the following:
//
// Link: http://cplusplus.com/reference/vector/vector/
//*====================================================================================================================*
#include <iostream>

// INCLUDE GUARDS (You may also see, #pragma once)
#ifndef VECTOR_H
#define VECTOR_H


template<typename DATA>
class Vector
{
    private:

        // Main Container
        DATA* _array;

        // Used to keep track of contents
        size_t _capacity;
        size_t _size;

        // Called when expanding Vector
        void _resize();

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

    /*---------------------------------------------------------------------------------------------*/
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

        // Used for testing
        void displayVector();
};

#endif //DATASTRUCTURES_VECTOR_H
