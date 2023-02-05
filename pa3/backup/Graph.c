/*
-------------------------------------------------
Class: CSE101
Project: pa3
Name: Anderson Compalas
CRUZID: 1793470
Filename: Graph.c
-------------------------------------------------
*/

#include "Graph.h"
#include "List.h"
#include <stdlib.h>

#define COLOR_WHITE ((char)0)
#define COLOR_GRAY  ((char)1)
#define COLOR_BLACK ((char)2)

/*** Structs ***/

struct GraphObj {
    int   order; // order or the graph (number of vertices)
    int   size;  // size of the graph (number of undirected edges)
    List* neighbors;
    char* color;
    int*  parent;
    int*  d_time;
    int*  f_time;
}GraphObj;

/*** Constructors/Destructors ***/

Graph newGraph(int n) {
    Graph G      = (Graph)malloc(sizeof(struct GraphObj));
    G->order     = n;
	G->size      = 0;
    G->neighbors = (List*)malloc(sizeof(List) * (n + 1));
    G->color     = (char*)malloc(sizeof(char) * (n + 1));
    G->parent    = (int*) malloc(sizeof(int)  * (n + 1));
	G->d_time    = (int*) malloc(sizeof(int)  * (n + 1));
	G->f_time    = (int*) malloc(sizeof(int)  * (n + 1));
	for(int i = 1; i <= n; i++){
		G->neighbors[i] = newList();
		G->color[i] = COLOR_WHITE;
		G->parent[i] = NIL;
		G->d_time[i] = UNDEF;
		G->f_time[i] = UNDEF;
	}
    return G;
}

void freeGraph(Graph* pG) {
    for (int i = 1; i <= (*pG)->order; i ++) {
        List neighbors = (*pG)->neighbors[i];
        freeList(&neighbors);
    }
    free((*pG)->neighbors);
    free((*pG)->color);
    free((*pG)->parent);
	free((*pG)->d_time);
	free((*pG)->f_time);
    free(*pG);
    *pG = NULL;
}

/*** Access functions ***/

int getOrder(Graph G) {
    return G->order;
}

int getSize(Graph G) {
    return G->size;
}

int getParent(Graph G, int u) {
    if (u < 1 || u > getOrder(G)) {
        printf("getParent ERROR: u < 1 || u > G->getOrder()\n");
        exit(-1);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u) {
    if (u < 1 || u > getOrder(G)){
	   	printf("getParent ERROR: u < 1 || u > G->getOrder()\n");
		exit(-1);
	}
	return G->d_time[u];
}

int getFinish(Graph G, int u) {
	if(u < 1 || u > getOrder(G)){
		printf("getParent ERROR: u < 1 || u > G->getOrder()\n");
		exit(-1);
	}
	return G->f_time[u];    
}

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v) {
    if (u < 1 || u > getOrder(G)) {
        printf("addEdge ERROR: u < 1 || u > G->getOrder()\n");
        exit(-1);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("addEdge ERROR: v < 1 || v > G->getOrder()\n");
        exit(-1);
    }
    addArcHelper(G, u, v);
    addArcHelper(G, v, u);
	G->size--;
}

void addArc(Graph G, int u, int v) {
    addArcHelper(G, u, v);
}

// Adds directed edge without modifying size (addEdge and addArc use
// this and modify size differently below)
void addArcHelper(Graph G, int u, int v) {
    if (u < 1 || u > getOrder(G)) {
        printf("addArc ERROR: u < 1 || u > G->getOrder()\n");
        exit(-1);
    }
    if (v < 1 || v > getOrder(G)) {
        printf("addArc ERROR: v < 1 || v > G->getOrder()\n");
        exit(-1);
    }
    List neighbors = G->neighbors[u];
    moveFront(neighbors);
    while (index(neighbors) >= 0) {
        int k = get(neighbors);
        if (k > v) {
        	insertBefore(neighbors, v);
        	return;
        } else if (k == v) {
        	return;
        }
        moveNext(neighbors);
    }
    append(neighbors, v);
	G->size++;
}

int Visit(Graph G, List S, int u, int time){
    int t = time;
	t++;
    G->d_time[u] = t;
    G->color[u] = COLOR_GRAY;
    moveFront(G->neighbors[u]);
    while(index(G->neighbors[u]) >= 0){
        int x = get(G->neighbors[u]);
        if(G->color[x] == COLOR_WHITE){
            G->parent[x] = u;
			t = Visit(G, S, x, t);
        }
        moveNext(G->neighbors[u]);
    }
	//Finish and add to the stack
	G->color[u] = COLOR_BLACK;
	t++;
	G->f_time[u] = t;
	prepend(S, u);
	return t;	
}

void DFS(Graph G, List S){
    if (length(S) != getOrder(G)) {
        printf("DFS ERROR: s < 1 || s > G->getOrder()\n");
        exit(-1);
    }
    int time = 0;
    //Set all vertices to white
	for(int i = 1; i <= getOrder(G); i++){
		G->color[i] = COLOR_WHITE;
	}
    List newS = newList();
    //While the stack isn't empty
    while(length(S) > 0){
		//Pop from the stack
        int u = front(S);
		deleteFront(S);
		//If unvisited call visit function
        if(G->color[u] == COLOR_WHITE){
           time =  Visit(G, newS, u, time);
		}
    }
	//S is now empty

	//Copy newS to S
	moveFront(newS);
	while(index(newS) >= 0){
		int x = get(newS);
		append(S, x);
		moveNext(newS);
	}
	freeList(&newS);
}

/*** Other operations ***/

Graph transpose(Graph G){
    Graph T = newGraph(getOrder(G));
	for(int i = 1; i <= G->order; i++){
		List tmp = G->neighbors[i];
		moveFront(tmp);
		while(index(tmp) != -1){
			int k = get(tmp);
			addArc(T,k, i);
			moveNext(tmp);
		}
	}
    return T;
}

Graph copyGraph(Graph G){
	//New graph same size as G
    Graph copy = newGraph(getOrder(G));
	//Copy adjacency list of each vertex in G
	for(int i = 1; i <= getOrder(G); i++){
		copy->neighbors[i] = copyList(G->neighbors[i]);
	}
    return copy;
}

void printGraph(FILE* out, Graph G) {
    fprintf(out, "Adjacency list representation of G:\n");
    for (int i = 1; i <= G->order; i ++) {
        fprintf(out, "%d:", i);
        List neighbors = G->neighbors[i];
        moveFront(neighbors);
        while (index(neighbors) >= 0) {
            int v = get(neighbors);
            fprintf(out, " %d", v);
            moveNext(neighbors);
        }
        fprintf(out, "\n");
    }
}










