/*
----------------------------------------------------------
Class: CSE101
Project: pa3
Name: Anderson Compalas
CRUZID: 1793470
Filename: Graph.h
----------------------------------------------------------
*/

#ifndef GRAPH__H
#define GRAPH__H

#include "List.h"

typedef struct GraphObj *Graph;

#define UNDEF ((int)-1)
#define NIL ((int)0)

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void addArcHelper(Graph G, int u, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif
