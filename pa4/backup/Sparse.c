/*
----------------------------------------
Class: CSE101
Project: pa4
Name: Anderson Compalas
CRUZID: 1793470
 Filename: Sparse.c
----------------------------------------
*/

//----------------------------------------
//Include Libraries and Definitions
//----------------------------------------

#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 300

int main(int argc, char** argv) {
    int lines = 0;
    FILE *in, *out;
    char line[MAX_LEN];

    //Check command line for correct number of arguments 

    if (argc != 3) {
        printf("USAGE: FindPath <infile> <outfile>\n");
        exit(-1);
    }

    //Open files for reading and writing
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
  
    // Count number of lines in file

    while(fgets(line, MAX_LEN, in) != NULL){
        lines++;
	}

    //Return to start of file
    rewind(in); 

    //Build array
    char** arr = calloc(lines, sizeof(char*));
    for(int i = 0; i < lines; i++){
        fgets(line, MAX_LEN, in);
        arr[i] = calloc(strlen(line)+1, sizeof(char));
		strcpy(arr[i], line);
	}
 
    //Assemble Matrix A and B
    
    int n, a, b;

    sscanf(arr[0], "%d %d %d", &n, &a, &b);
    //printf("Matrix size: %d\n", n);
    //printf("A values: %d\n", a);
    //printf("B values: %d\n", b);

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    //Populate Matrix A
    for(int j = 2; j <= a+1; j++){
        int row;
        int col;
        double x;
        sscanf(arr[j], "%d %d %lf", &row, &col, &x);
        //printf("row: %d col: %d x: %.1f \n", row, col, x);
		changeEntry(A, row, col, x);
    }
    //Populate Matrix B
    for(int k = a+3; k <= (a+b+2); k++){
        int row;
        int col;
        double x;
        sscanf(arr[k], "%d %d %lf", &row, &col, &x);
        //printf("row: %d col: %d x: %.1f \n", row, col, x);
		changeEntry(B, row, col, x);
    }

    //Print Matrix A
    fprintf(out, "A has %d non-zero entries:", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    //Print Matrix B
    fprintf(out, "\nB has %d non-zero entries:", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    
    //Print (1.5)A
    double s = (1.5);
    Matrix sM = scalarMult(s, A);
    fprintf(out, "\n(%.1f) *A = ", s);
    printMatrix(out, sM);
    fprintf(out, "\n");

    //Print A+B
    Matrix AB = sum(A, B);
    fprintf(out, "\nA+B = ");
    printMatrix(out, AB);
    fprintf(out, "\n");

    //Print A+A
    Matrix AA = sum(A, A);
    fprintf(out, "\nA+A = ");
    printMatrix(out, AA);
    fprintf(out, "\n");
    
    //Print B-A
    Matrix Ba = diff(B, A);
    fprintf(out, "\nB-A = ");
    printMatrix(out, Ba);
    fprintf(out, "\n");

    //Print A-A
    Matrix Aa = diff(A, A);
    fprintf(out, "\nA-A = ");
    printMatrix(out, Aa);
    fprintf(out, "\n");
    
    //Print Transpose(A)
    Matrix T = transpose(A);
    fprintf(out, "\nTranspose(A) = ");
    printMatrix(out, T);
    fprintf(out, "\n");

    //Print A*B
    Matrix AxB = product(A, B);
    fprintf(out, "\nA*B = ");
    printMatrix(out, AxB);
    fprintf(out, "\n");

    //Print B*B
    Matrix BxB = product(B, B);
    fprintf(out, "\nB*B = ");
    printMatrix(out, BxB);
    fprintf(out, "\n");
    
    //Free Memory
    
    //Free Matrices
    freeMatrix(&sM);
    freeMatrix(&AB);
    freeMatrix(&AA);
    freeMatrix(&Ba);
    freeMatrix(&Aa);
    freeMatrix(&T);
    freeMatrix(&AxB);
    freeMatrix(&BxB);
    freeMatrix(&A);
    freeMatrix(&B);

    //Free array
    for (int j = 0; j < lines; j ++) {
        free(arr[j]);
    }
    free(arr);

  return 0;
}
