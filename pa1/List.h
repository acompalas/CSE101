/*
----------------------------------------------------------
Class: CSE101
Project: pa1
Name: Anderson Compalas
CRUZID: 1793470
Filename: List.h
----------------------------------------------------------
*/

#include <stdio.h>
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
void freeList(List* pL)

//--------------------------------------------------------
//Access functions
//--------------------------------------------------------

int length(List L);
int indext(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);

//--------------------------------------------------------
//Manipulation functions
//--------------------------------------------------------

void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void deleteCursor(List L);

//-------------------------------------------------------
//Output Functions
//-------------------------------------------------------

void printList(FILE* out, List L);
List copyList(List L);
List concatList(List A, List B);

#endif



