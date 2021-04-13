#include "Singly-Linked-List.hpp"
#include "Vector.hpp"
#include "Binary-Search-Tree.hpp"
#include <ctime> // time(...)

/*
* Set Macro definitions in command line. The makefile provided
*   already will do this. See the makefile to configure specific tests.
*/

int main(int argc, char** argv)
{
    // Vector Test Section
    #ifdef VECTOR_TEST
    
    #endif // VECTOR_TEST

    // SLL Test Section
    #ifdef SLL_TEST
    SLL<int> myList;

    std::cout << "EXPECTED:\n[HEAD]-> ";
    // Add Nodes 1-100
    for(auto i = 1; i <= 10; i++)
    {
        std::cout << i << "-> "; 
        myList.push_front(i);
    }
    myList.reverse();
    std::cout << "[TAIL]-> nullptr\n";
    std::cout << "RECIEVED:"; 
    myList.print();

    // INSERT AFTER TEST
    int numToInsert = 777;
    int insertAfterVal = 10;
    std::cout << "\nINSERTING " << numToInsert << " after node with the value of " << insertAfterVal
              << "\n" ;

    myList.insert_after(777, myList.search(10));

    std::cout << "RESULT:";
    myList.print();

    #endif // SLL_TEST

    #ifdef BST_TEST
    
    BST<int, char> myTree;
    std::cout << "\nInit okay\n";

    #endif // BST_TEST
    
    return 0;
}