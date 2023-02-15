/*
----------------------------------------
Class: CSE101
Project: pa4
Name: Anderson Compalas
CRUZID: 1793470
 Filename: List.c
----------------------------------------
*/

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>
#include <string.h>
#include <stdbool.h>

//---------------------------------------
//Structs
//---------------------------------------

typedef struct NodeObj{
	void* data;
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

Node newNode(void* data){
	Node N = malloc(sizeof(NodeObj));
	assert( N !=NULL );
	N->data = data;
	N->prev = NULL;
	N->next = NULL;
	return(N);
}

void freeNode(Node *fN){
	if(fN != NULL && *fN != NULL){
		free(*fN);
		*fN = NULL;
	}
}

List newList(void){
	List newL; 
	newL = malloc(sizeof(ListObj));
	assert(newL !=NULL);
	newL->len = 0;
	newL->index = -1;
	newL->cur = NULL;
	newL->front = NULL;
	newL->back = NULL;
	return (newL);
}

void freeList(List *pL){
	if(pL != NULL && *pL != NULL){
		while(length(*pL) != 0) { 
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
		printf("Error: calling length() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	return L->len;
}

int index(List L){
	if(L == NULL){
		printf("Error: calling index() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	return L->index;
}

void* front(List L){
	if(L == NULL){
		printf("Error: calling front() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	return(L->front->data);
}

void* back(List L){
	if(L == NULL){
		printf("Error: calling back() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	return(L->back->data);
}

void* get(List L){
	if(L == NULL){
		printf("Error: calling get() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("List Error:called get() but list is empty because index < 0\n");
		exit(EXIT_FAILURE);
	}
	if(L->len < 1){
		printf("List Error:called get() but list is empty because L->len < 1\n");
		exit(EXIT_FAILURE);		
	}
	return(L->cur->data);
}

//-----------------------------------------------	
//Manipulation functions
//-----------------------------------------------

void clear(List L){
	if(L == NULL){
		printf("Error: calling clear() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	while(length(L) > 0){
		Node F = L->front;
		Node B = L->back;
		if(F != B){
			deleteFront(L);
			deleteBack(L);
		}
		else{
			moveFront(L);
			delete(L);
		}
	}
	L->len = 0;
	L->index = -1;
	L->cur = NULL;
	L->front = NULL;
	L->back = NULL;
}

void moveFront(List L){
	if(L == NULL){
		printf("Error: callling moveFront() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->len > 0){
		L->cur = L->front;
		L->index = 0;
	}
}

void moveBack(List L){
	if(L == NULL){
		printf("Error: calling moveBack() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->len > 0){
		L->cur = L->back;
		L->index = L->len - 1;
	}
}

void moveNext(List L){
	if(L == NULL){
		printf("Error: calling moveNext() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->cur != NULL && L->cur != L->back){
		L->cur = L->cur->next;
		L->index += 1;
	}
	else{
		L->cur = NULL;
		L->index = -1;
	}
}

void movePrev(List L){
	if(L == NULL){
		printf("Error: calling movePrev() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->cur != NULL && L->cur != L->front){
		L->cur = L->cur->prev;
		L->index -= 1;
	}
	else{
		L->cur = NULL;
		L->index = -1;
	}
}

void prepend(List L, void* data){
	if(L == NULL){
		printf("Error: calling prepend() on NULL object\n");
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

void append(List L, void* data){
	if(L == NULL){
		printf("Error: calling append() on NULL object\n");
		exit(EXIT_FAILURE);
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

void insertBefore(List L, void* data){
	if(L == NULL){
		printf("Error: calling insertBefore() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->len < 1 || index(L) < 0){
		printf("Error:called insertBefore() but list is empty\n");
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
		L->cur->prev->next = to_add;
		to_add->next = L->cur;
		L->cur->prev = to_add;
	}
	L->len += 1;
	L->index += 1;
}

void insertAfter(List L, void* data){
	if(L == NULL){
		printf("Error: calling insertAfter() on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->len < 1){
		printf("Error:called insertAfter() but list is empty\n");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("Error:called insertAfter() but list is empty\n");
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
		L->cur->next = to_add;
	}
	L->len+= 1;
}

void deleteFront(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if(L->len < 1){
		printf("Error:called deleteFront() but list is empty\n");
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
	if(L->len < 1){
		printf("Error:called deleteBack() but list is empty\n");
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

void delete(List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	if((L->len < 1) || (index(L) < 0)){
		printf("Error:called delete() but list is empty\n");
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

/*void printList(FILE* out, List L){
	if(L == NULL){
		printf("Error: calling function on NULL object\n");
		exit(EXIT_FAILURE);
	}
	Node to_print = L->front;
	while(to_print != NULL){
		fprintf(out, "%d ", to_print->data);
		to_print = to_print->next;
	}
}*/

List copyList(List L){
	List copyL = newList();
	Node to_copy = L->front;
	while(to_copy != NULL){
		append(copyL, to_copy->data);
		to_copy = to_copy->next;
	}
	return copyL;
}


 	

/* ------------------------------------------------ END OF FILE ---------------------------------------------------------- */
