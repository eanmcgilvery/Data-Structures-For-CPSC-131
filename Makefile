CC = g++

# Specify Here which Data Structs to test for in main.cpp
DATA_STRUCT_TESTS = -D VECTOR_TEST -D SLL_TEST -D STACK_LIST_TEST

# Feel free to add any other flags. Add before the -o option.
CFLAGS =  -g -Wall -std=c++17 -o

DATA_STRUCT_OBJS = Vector.o SLL.o Stack_List.o Stack_Vector.o

all: main.exe

main.exe: main.cpp $(DATA_STRUCT_OBJS)
	$(CC) $(DATA_STRUCT_TESTS) $(CFLAGS) main.exe main.cpp

Stack_Vector.o: Vector.o Stack_VectorBased.hpp
	$(CC) $(CFLAGS) Stack_Vector.o -c Stack_VectorBased.hpp

Stack_List.o: SLL.o Stack_ListBased.hpp
	$(CC) $(CFLAGS) Stack_List.o -c Stack_ListBased.hpp

SLL.o: Singly-Linked-List.hpp
	$(CC) $(CFLAGS) SLL.o -c Singly-Linked-List.hpp

Vector.o: Vector.hpp
	$(CC) $(CFLAGS) Vector.o -c Vector.hpp

clean:
	rm *.o *.exe