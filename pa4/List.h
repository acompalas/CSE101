/*
----------------------------------------------------------
Class: CSE101
Project: pa4
Name: Anderson Compalas
CRUZID: 1793470
Filename: List.h
----------------------------------------------------------
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#ifndef _LIST_H_
#define _LIST_H_

//--------------------------------------------------------
//Types
//-------------------------------------------------------

typedef struct ListObj *List;

//--------------------------------------------------------
//Constructors/Destructors
//--------------------------------------------------------

List newList(void); 
void freeList(List* pL);

//--------------------------------------------------------
//Access functions
//--------------------------------------------------------

int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);

//--------------------------------------------------------
//Manipulation functions
//--------------------------------------------------------

void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* data);
void append(List L, void* data);
void insertBefore(List L, void* data);
void insertAfter(List L, void* data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

//-------------------------------------------------------
//Output Functions
//-------------------------------------------------------

void printList(FILE* out, List L);


#endif



