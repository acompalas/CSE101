/*
 ----------------------------------------
 Class: CSE101
 Project: pa1
 Name: Anderson Compalas
 CRUZID: 1793470
 Filename: List.c
 ----------------------------------------
 */

#include "List.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------
//Structs
//---------------------------------------

typdef struct NodeObj{
	int data:
	struct NodeObj* prev;
	struct NodeObj* next;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
	Node front;
	Node back;
	Node cur;
	int len;
	int index;
}ListObj;

//---------------------------------------
//Constructors/Destructors
//---------------------------------------

Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data:
	N->prev = NULL;
	N->next = NULL;
	return N;
}

void freeNode(Node *fN){
	if(fN != NULL && *fN != NULL){
		free(*fN);
		*fn = NULL;
	}
}

List newList(void){
	List newL = malloc(sizeof(ListObj));
	newL->len = 0;
	newL->index = -1;
	newL->cur = NULL;
	newL->front = NULL;
	newL->back = NULL;
	return newL;
}

void freeList(List *pL){
	if(pL != NULL && *pL != NULL){
		if(length(*pL) != 0){
			clear(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

//---------------------------------------
//Access functions
//---------------------------------------

int length(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	return L->len;
}

int index(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	return L->index;
}

int front(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	return(L->front->data);
}

int back(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	return(L->back->data);
}

int get(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0 || L->len < 1){
		printf("List Error: list is empty\n");
		exit(EXIT_FAILURE);
	}
	return(L->cur->data);
}

bool equals(List A, List B){
	int eq = 0;
	Node x = NULL;
	Node y = NULL;
	
	if(A == NULL || B == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	
	eq = (A->len == B->len);
	x = A->front;
	y = B->front;
	while(eq && x!= NULL && y!= NULL){
		eq = (x->data = y->data);
		x = x->next;
		y = y->next;
	}
	if(eq == 1){
		return true;
	}
	return false;
}

//-----------------------------------------------	
//Manipulation functions
//-----------------------------------------------

void clear(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	while(L->length > 0){
		Node F = L->front;
		Node B = L->back;
		if(F != B){
			deleteFront(L);
			deleteBack(L);
		}
		else{
			moveFront(L);
			delete(L;
		}
	}
	L->len = 0;
	L->index = -1;
	L->cursor = NULL;
	L->front = NULL;
	L->back = NULL;
}

void moveFront(List L){
	if(L == NULL){
		print("Error: callling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->length = 0){
		L->cur = L->front;
		L->index = 0;
	}
}

void moveBack(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->len > 0){
		L->cur = L->back;
		L->index = L->len - 1;
	}
}

void moveNext(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->cur != NULL && L->cur != L->back){
		L-cur = L->cur->next;
		L->index += 1;
	}
	else{
		L->cur = NULL;
		L->index = -1;
	}
}

void prepend(List L, int data){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	Node to_add = newNode(data);
	if(L->len == 0){
		L->front = to_add;
		L->back = to_add;
	}
	else{
		to_add->next = L->front;
		L->front->prev = to_add;
		L->front = to_add;
	}
	L->len++;
	if(L->cur != NULL && L->index >= 0){
		L->index += 1;
	}
}

void append(List L, int data){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exti(EXIT_FAILURE);
	}
	Node to_add = newNode(data);
	if(L->len == 0){
		L->front = to_add;
		L->back = to_add;
	}
	else{
		L->back->next = to_add;
		to_add->prev = L->back;
		L->back = to_add;
	}
	L->len++;
}

void insertBefore(List L, int data){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->len < 1 || index(L) < 0){
		printf("Error: list is empty\n");
		exit(EXIT_FAILURE);
	}
	Node to_add = newNode(data);
	if(L->cur == L->front){
		L->front->prev = to_add;
		to_add->next = L->front;
		L->front = to_add;
	}
	else{
		to_add->prev = L->cur->prev;
		L->cur->prev = to_add;
		to_add->next = L->cur;
		L->cur->prev = to_add;
	}
	L->len += 1;
	L->index += 1;
}

void insertAfter(List L, int data){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE):
	}
	if(L->len < 1 || index(L) < 0){
		printf("Error: list is empty\n");
		exit(EXIT_FAILURE);
	}
	Node to_add = newNode(data);
	if(L->cur == L->back){
		L->back->next = to_add;
		to_add->prev = L->back;
		L->back = to_add;
	}
	else{
		L->cur->next->prev = to_add;
		to_add->next = L->cur->next;
		to_add->prev = L->cur;	
		L->back = to_add;
	}
	L->len+= 1;
}

void deleteFront(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exti(EXIT_FAILURE);
	}
	if(L->len < 1){
		printf("Error: list is empty\n");
		exit(EXIT_FAILURE);
	}
	Node to_delete = L->front;
	if(L->back == L->front){
		freeNode(&to_delete);
		L->front = NULL;
		L->back = NULL;
		L->cur = NULL;	
		L->len = 0;
		L->index = -1;
	}
	else{
		if(L->cur == L->front){
			L->cur = NULL;
			L->index = -1;
		}
		if((L->index > 0) && (L->cur != L->front)){
			L->index -= 1;
		}
		Node temp = L->front->next;
		temp->prev = NULL;
		L->front->next = NULL;
		L->front = temp;
		freeNode(&to_delete);
		L->len -= 1;
	}
}

void deleteBack(List L){
	if(L == NULL){
		printf("Error: calling fun ction on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->back == L->front){
		printf("Error: list is empty\n")"
		exit(EXIT_FAILURE);
	}
	Node to_delete = L->back;
	if(L->back == L->front){
		freeNode(&to_delete);
		L->front = NULL;
		L->back = NULL;
		L->cur = NULL;
		L->len = 0;
		L->index = -1;
	}
	else{
		if(L->cur == L->back){
			L->cur = NULL;
			L->index = -1;
		}
		Node temp = L->back->prev;
		L->back->prev->next = NULL;
		L->back->prev = NULL;
		L->back = temp;
		freeNode(&to_delete);
		L->len -= 1;
	}
}

void deleteCursor(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if((L->len < 1) || (index(L) < 0)){
		printf("Error: list is empty\n");
		exit(EXIT_FAILURE);
	}
	if(L->cur == L->front){
		deleteFront(L);
	}
	else if(L->cur == L->back){
		deleteBack(L);
	}
	else{
		Node to_delete = L->cur;
		Node temp = L->cur->prev;
		temp->next = L->cur->next;
		L->cur->next->prev = temp;
		L->cur->prev = NULL;
		L->cur->next = NULL;
		freeNode(&to_delete);
		L->len -= 1;
	}
	L->cur = NULL;
	L->index = -1;
}

//-----------------------------------------------
//Output functions
//-----------------------------------------------

void printList(FILE* out, List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	Node to_print = L->front;
	while(to_print != NULL){
		fprintf(out, "%d", to_print->data);
		to-print = to_print->next;
	}
}

List copyList(List L){
	List copyL = newList();
	Node to_copy = L->front;
	while(to_copy != NULL){
		append(copyL, to_copy->data);
		to_copy = to_copy->next;
	}
	return copyL;
}

List concatList(List A, List B){
	List concatL = newList();
	Node nA = A->front;
	Node nB = B->front;
	while(nA != NULL){
		append(concatL, nA->data);
		nA = nA->next;
	}
	while(nB != NULL){
		append(concatL, nB->data);
		nB = nB0>next;
	}
	return concatL;
}

 	

/* ------------------------------------------------ END OF FILE ---------------------------------------------------------- */

