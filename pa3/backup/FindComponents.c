/*
-------------------------------------------------
Class: CSE101
Project: pa3
Name: Anderson Compalas
CRUZID: 1793470
Filename: FindComponents.c
-------------------------------------------------
*/

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 300

int main(int argc, char** argv) {
  int lines = 0;
  FILE *in, *out;
  char line[MAX_LEN];
  if (argc != 3) {
    printf("USAGE: FindPath <infile> <outfile>\n");
    exit(-1);
  }
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if (in == NULL) {
    printf("Error: Cannot open \"%s\" for reading.\n", argv[1]);
    exit(1);
  }
  if (out == NULL) {
    printf("Error: Cannot open \"%s\" for writing.\n", argv[2]);
    exit(1);
  }
  
  // Read each line of input file, store in array, and increment count.
  while(fgets(line, MAX_LEN, in) != NULL){
		lines++;
	}
  rewind(in); //Resets input line to start of file.

  //		Build array
  char** arr = calloc(lines, sizeof(char*));
  for(int i = 0; i < lines; i++){
		fgets(line, MAX_LEN, in);
		arr[i] = calloc(strlen(line)+1, sizeof(char));
		strcpy(arr[i], line);
	}
 
  //Assemble a graph object 𝐺 using newGraph() and addArc()
  int   order = atoi(arr[0]);
  Graph G     = newGraph(order);
  int i = 1;
  int u = -1;
  int v = -1;
  while (u != 0 && v != 0) {
    char* next;
    u = strtol(arr[i], &next, 10);
    v = strtol(next, NULL, 10);
    if (u != 0 && v != 0) {
      addArc(G, u, v);
    }
	i++;
  }
  
    
  //Print the adjacency list representation of G to the output file.
  printGraph(out, G);
  
  //Build initial Stack
  List S = newList();
  int k = 1;
  while(length(S) < getOrder(G)){
	  append(S, k);
	  k++;
  }

  //Run DFS on 𝐺 and 𝐺𝑇 processing the vertices in the second call by decreasing finish times from the first call.
  DFS(G, S);
  printList(stdout, S);
  printf("\n");
  Graph Gt = transpose(G);
  DFS(Gt, S);
  printList(stdout, S);
  printf("\n");

  //Determine the strong components of G
  int components = 0;
  moveBack(S);
  while(index(S) != -1){
	  if(getParent(Gt, get(S)) == NIL){
	  	components++;
	  }
	  movePrev(S);
  }

  //Print the strong components of 𝐺 to the output file in topologically sorted order
  fprintf(out, "\n");
  fprintf(out, "G contains %d strongly connected components:", components);
  int component = 0;
  printList(stdout, S);
  moveBack(S);
  List tmp = newList();
  while(index(S) != -1){
	prepend(tmp, get(S));
	if(getParent(Gt, get(S)) == NIL){
		component++;
		fprintf(out, "\nComponent %d: ", component);
		printList(out, tmp);
		clear(tmp);
	}
	movePrev(S);
  }
  freeList(&tmp);

  //Close files
  fclose(out);
  fclose(in);

  //Free memory
  freeGraph(&G);
  freeList(&S);
  for (int j = 0; j < lines; j ++) {
    free(arr[j]);
  }
  free(arr);
  return 0;
}
