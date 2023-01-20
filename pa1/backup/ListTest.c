//----------------------------------------------------------------
//Class: CSE101
//Project: pa1:
//Name:Anderson Compalas
//CRUZID: 1793470
//----------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

int main(int argc, char *argv[]){
	
	List A = newList();
	List B = newList();
	List C = NULL;
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

	clear(B);
	if(length(B) == 0){
		printf("clear() passed\n");
	}else{
		printf("clear() failed\n");
	}

	moveFront(A);
	moveNext(A);
	if(index(A) == 1){
		printf("moveNext() test1 passed\n");
	}else{
		printf("moveNext() test1 failed\n");
	}

	moveBack(A);
	moveNext(A);
	if(index(A) == -1){
		printf("moveNext() test2 passed\n");
	}else{
		printf("moveNext() test2 failed\n");
	}

	prepend(B, 4);
	if(front(B) == 4){
		printf("prepend() passed\n");
	}else{
		printf("prepend() failed\n");
	}

	append(B, 7);
	if(back(B) == 7){
		printf("append() passed\n");
	}else{
		printf("append() failed\n");
	}

	C = copyList(B);
	if(equals(B, C) == true){
		printf("copyList() passed\n");
	}else{
		printf("copyList() failed\n");
	}

	moveFront(A);
	for(i=0; i<5; i++) moveNext(A); // at index 5
	insertBefore(A, -7);            // at index 6
	for(i=0; i<9; i++) moveNext(A); // at index 15
   	insertAfter(A, -2);
   	for(i=0; i<5; i++) movePrev(A); // at index 10
   	delete(A);
   	printList(stdout,A);
   	printf("\n");
   	printf("%d\n", length(A));
   	clear(A);
   	printf("%d\n", length(A));

   	freeList(&A);
   	freeList(&B);
   	freeList(&C);


   	return(0);

}

	



