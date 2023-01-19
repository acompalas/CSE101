//----------------------------------------------------------------
//Class: CSE101
//Project: pa1:
//Name:Anderson Compalas
//CRUZID:
//----------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main(int argc, char *argv[]){
	
	List A = newList();
	List B = newList();

	int i;

	for(i = 1; i <= 20; i++){
		append(A, i);
		prepend(B, i);
	}
	
	printList(stdout, A);
	printf("\n");
	printList(stdout, B);
	printf("\n");

	if(length(A) == 20){
		printf("length() passed\n");
	}else{
		printf("lenght() failed\n");
	}

	moveFront(A);
	if(index(A) == 0){
		printf("moveFront() passed\n");
	}else{
		printf("moveFront() failed\n");
	}

	moveBack(A);
	if(index(A) == 19){
		printf("moveBack() passed\n");
	}else{
		printf("moveBack() failed\n");
	}

	clear(A);
	if(length(A) == 0){
		printf("clear() passed\n");
	}else{
		printf("clear() failed\n");
	}

	moveFront(B);
	moveNext(B);
	if(index(B) == 1){
		printf("moveNext() test1 passed\n");
	}else{
		printf("moveNext() test1 failed\n");
	}

	moveBack(B);
	moveNext(B);
	if(index(B) == -1){
		printf("moveNext() test2 passed\n");
	}else{
		printf("moveNext() test2 failed\n");
	}

	prepend(A, 4);
	if(front(A) == 4){
		printf("prepend() passed\n");
		
	return(0);

}

	



