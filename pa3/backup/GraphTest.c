/*
------------------------------------------------
Class: CSE101
Project: pa3
Name: Anderson Compalas
CRUZID: 1793470
Filename: GraphTest.c
-------------------------------------------------
*/



#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);

   Graph DG = newGraph(100);
   List DL = newList();

   addArc(DG, 64, 4);
   addArc(DG, 64, 3); 
   addArc(DG, 42, 2);
   addArc(DG, 2, 64);
   addArc(DG, 4, 2);
   addArc(DG, 3, 42);
   for (int i = 1; i <= 100; i++) {
       prepend(DL, i);
   }
 
   DFS(DG, DL);
   fprintf(stdout, "  x:   d   f   p\n");
   for(i=1; i<= 100; i++){
	   fprintf(stdout, "%3d: %3d %3d %3d\n", i, getDiscover(DG, i), getFinish(DG, i), getParent(DG, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, DL);
   fprintf(stdout, "\n\n");

   DFS(DG, DL);
   fprintf(stdout, "  x:   d   f   p\n");
   for(i=1; i<= 100; i++){
      fprintf(stdout, "%3d: %3d %3d %3d\n", i, getDiscover(DG, i), getFinish(DG, i), getParent(DG, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, DL);
   fprintf(stdout, "\n\n");
  
   int dt = getDiscover(DG, 4);
   if(dt == 126){
 	 fprintf(stdout, "Discover time: %d\n", dt);
   }else{
	 fprintf(stdout, "Wrong time: %d\n", dt);
   }

   freeList(&DL);
   freeGraph(&DG);
  
   return(0);

}
