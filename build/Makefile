#variables
FLAGS=-c -O3 -std=c++17

all: main

main: main.o AVL.o BTree.o
	g++ -o main main.o AVL.o BTree.o -lstdc++fs

main.o: ../src/main.cpp
	g++ $(FLAGS) ../src/main.cpp

AVL.o: ../src/AVL.cpp
	g++ $(FLAGS) ../src/AVL.cpp

BTree.o: ../src/BTree.cpp
	g++ $(FLAGS) ../src/BTree.cpp

clean:
	rm -rf *.o main *~ sort_output.txt
