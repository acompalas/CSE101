/*
----------------------------------------
Class: CSE101
Project: pa4
Name: Anderson Compalas
CRUZID: 1793470
 Filename: MatrixTest.c
----------------------------------------
*/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "Matrix.h"
#include "List.h"
     
int main(){
   int n= 3;
   
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   
   Matrix C, D, E, F,G, H;
	
   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
   
   printf("A: %d %d", size(A), NNZ(A));
   printMatrix(stdout, A);
   printf("\n\n");
	
   printf("B: %d %d", size(B), NNZ(B));
   printMatrix(stdout, B);
   printf("\n\n");

   C = scalarMult(1.5, A);
   printf("C: %d %d", size(C), NNZ(C));
   printMatrix(stdout, C);
   printf("\n\n");

   D = sum(A, B);
   printf("D: %d %d",size(D), NNZ(D));
   printMatrix(stdout, D);
   printf("\n\n");

   E = diff(A, A);
   printf("E: %d %d",size(E), NNZ(E));
   printMatrix(stdout, E);
   printf("\n\n");


   F = transpose(B);
   printf("F: %d %d", size(F), NNZ(F));
   printMatrix(stdout, F);
   printf("\n\n");

   G = product(B, B);
   printf("G: %d %d",size(G), NNZ(G));
   printMatrix(stdout, G);
   printf("\n\n");

   H = copy(A);
   printf("H: %d %d",size(H), NNZ(H));
   printMatrix(stdout, H);
   printf("\n\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );
   printf("\n");

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   /*Matrix I = newMatrix(9);
   Matrix J = newMatrix(9);

   changeEntry(I, 1, 1, 4);
   changeEntry(I, 1, 2, 2);
   changeEntry(I, 1, 3, 0);
   changeEntry(I, 2, 1, 2);
   changeEntry(I, 3, 1, 0);
   changeEntry(I, 2, 2, 2);
   changeEntry(I, 3, 3, 0);

   changeEntry(J, 1, 1, -4);
   changeEntry(J, 1, 2, 0);
   changeEntry(J, 2, 1, 0);
   changeEntry(J, 2, 2, -2);
   changeEntry(J, 2, 4, 2);
   changeEntry(J, 3, 1, 0);
   changeEntry(J, 3, 2, 2);
   changeEntry(J, 7, 8, 5);

   printf("I: %d %d",size(I), NNZ(I));
   printMatrix(stdout, I);
   printf("\n\n");

   printf("J: %d %d",size(J), NNZ(J));
   printMatrix(stdout, J);
   printf("\n\n");

   Matrix K = sum(I, J);
   printf("K: %d %d",size(K), NNZ(K));
   printMatrix(stdout, K);
   printf("\n\n");

   freeMatrix(&I);
   freeMatrix(&J);
   freeMatrix(&K);*/
   
   return EXIT_SUCCESS;
}

