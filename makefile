dict: dict.o linkedlist.o
	gcc -o dict dict.o linkedlist.o -g
    
linkedlist.o: linkedlist.c linkedlist.h
	gcc -c -Wall linkedlist.c
    
dict.o: dict.c dict.h
	gcc -c -Wall dict.c
