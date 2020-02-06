ALL: array.out linkedlist.out

array.out: array.cpp
	g++ -o array.out array.cpp

linkedlist.out: ll.cpp
	g++ -o linkedlist.out ll.cpp