#variables
FLAGS=-c -O3 -std=c++17

all: main

main: main.o AVLTree.o BTree.o
	g++ -o main main.o AVLTree.o BTree.o -lstdc++fs

main.o: ../src/main.cpp
	g++ $(FLAGS) ../src/main.cpp

AVLTree.o: ../src/AVLTree.cpp
	g++ $(FLAGS) ../src/AVLTree.cpp

BTree.o: ../src/BTree.cpp
	g++ $(FLAGS) ../src/BTree.cpp

clean:
	rm -rf *.o main *~ sort_output.txt
