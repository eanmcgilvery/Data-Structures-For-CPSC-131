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
        DATA* _array;
        size_t _capacity;
        size_t _size;

        void _resize();

    public:
        // Default Constructor
        Vector();
        Vector(int);

        //Destructor
        ~Vector();
        // Copy Constructor
        Vector(const Vector & objectToCopy);
        // Copy Assignment Operator
        Vector& operator=(const Vector &objectToCopy);
    /*---------------------------------------------------------------------------------------------*/

        void push_back(DATA data);
        void pop_back();
        DATA front();
        DATA back();
        size_t size();
        void clear();
        void displayVector();


};

#endif //DATASTRUCTURES_VECTOR_H
