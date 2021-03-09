CC = g++

# Specify Here which Data Structs to test for in main.cpp
DATA_STRUCT_TESTS = -D VECTOR_TEST -D SLL_TEST

# Feel free to add any other flags. Add before the -o option.
CFLAGS =  -g -Wall -std=c++17 -o

DATA_STRUCT_OBJS = Vector.o SLL.o 

all: main.cpp $(DATA_STRUCT_OBJS)
	$(CC) $(DATA_STRUCT_TESTS) $(CFLAGS) main.exe main.cpp

SLL.o: Singly-Linked-List.hpp
	$(CC) $(CFLAGS) SLL.o -c Singly-Linked-List.hpp

Vector.o: Vector.hpp
	$(CC) $(CFLAGS) Vector.o -c Vector.hpp

clear: 
	rm *.o *.out