/*
----------------------------------------
Class: CSE101
Project: pa4
Name: Anderson Compalas
CRUZID: 1793470
 Filename: Matrix.c
----------------------------------------
*/

//-------------------------------------------------------
//Libraries and Declarations
//-------------------------------------------------------
#include "Matrix.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

Entry newEntry(int col, double value);
void freeEntry(Entry* pE);
double vectorDot(List P, List Q);

//-------------------------------------------------------
//Matrix ADT
//-------------------------------------------------------

typedef struct MatrixObj{
	int size;
	int values;
	List*  elements;
}MatrixObj;

typedef struct EntryObj{
	int col;
	double value;
}EntryObj;


//--------------------------------------------------------
//Constructors/Destructors
//--------------------------------------------------------

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	//Allocate the Matrix
	Matrix A = malloc(sizeof(struct MatrixObj));
	A->size = n;
	A->values = 0;
	//Allocate the list array
	A->elements = calloc(n+1, sizeof(List*));
	for(int i = 1; i <= n; i++){
		//Allocate each list
		A->elements[i] = newList();
	}
	return A;
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	//Free entries and nodes in makeZero()
	if(pM != NULL && *pM != NULL){
        makeZero(*pM);
        //Free each list
        for (int i = 1; i <= (*pM)->size; i ++) {
            //List rows = (*pM)->elements[i];
            freeList(&((*pM)->elements[i]));
        }
        //Free list array
        free((*pM)->elements);

        //Free pointer to matrix
        free(*pM);
        *pM = NULL;
    }
}

//Allocates each entry
Entry newEntry(int col, double value){
	Entry e = (Entry)malloc(sizeof(struct EntryObj));
	e->col = col;
	e->value = value;
	return e;
}

//Free entry
void freeEntry(Entry* pE){
	if(pE != NULL && *pE != NULL){
         free(*pE);
         *pE = NULL;
    }
}

//--------------------------------------------------------
//Access functions
//--------------------------------------------------------

// Return the size of square Matrix M
int size(Matrix M){
	return M->size;
}

 // Return the number of non-zero elements in M.
int NNZ(Matrix M){
	return M->values;
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if(size(A) != size(B)){
		return 0;
	}
	if(NNZ(A) != NNZ(B)){
		return 0;
	}
	for(int i = 1; i <= size(A); i++){
		moveFront(A->elements[i]);
		moveFront(B->elements[i]);
		while(index(A->elements[i]) >= 0 && index(B->elements[i]) >= 0){
			Entry ea = (Entry)get(A->elements[i]);
			Entry eb = (Entry)get(B->elements[i]);
			if(ea->col != eb->col){
				return 0;
			}
			if(ea->value != eb->value){
				return 0;
			}
			moveNext(A->elements[i]);
			moveNext(B->elements[i]);
		}
	}
	return 1; 
}
	

//--------------------------------------------------------
//Manipulation functions
//--------------------------------------------------------

// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	//For each row change entry to 0 and then clear list
	for(int i = 1; i <= size(M); i++){
		moveFront(M->elements[i]);
		while(index(M->elements[i]) >= 0){
			Entry e = (Entry)get(M->elements[i]);
			freeEntry(&e);
			moveNext(M->elements[i]);
		}
		clear(M->elements[i]);
	}
	M->values = 0;
}

// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if(i > size(M)){
		printf("Error: Call to changeEntry() is undefined: Matrix is out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	if(j > size(M)){
		printf("Error: Call to changeEntry() is undefined: Matrix is out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	if(i < 1){
		printf("Error: Call to changeEntry() is undefined: Matrix is out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	if(j < 1){
		printf("Error: Call to changeEntry() is undefined: Matrix is out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	moveFront(M->elements[i]);
	Entry e = NULL;  
	while(index(M->elements[i]) >= 0){
		
		e = (Entry)get(M->elements[i]);
		if(e->col >= j){
			break;
		}
		moveNext(M->elements[i]);
	}
	if(e == NULL || index(M->elements[i]) < 0){
		if(x != 0){
			Entry ne = newEntry(j, x);
			append(M->elements[i], ne);
			M->values++;
		}
	}
	else if(j < e->col){
		if(x != 0){
			Entry ne = newEntry(j, x);
			insertBefore(M->elements[i], ne);
			M->values++;
		}
	}
	else{
		if(x != 0){
			e->value = x;
		}else{
			freeEntry(&e);
			delete(M->elements[i]);
			M->values--;
		}
	}
}

//--------------------------------------------------------
//Matrix Operations
//--------------------------------------------------------

// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	Matrix C = newMatrix(size(A));
	for(int i = 1; i <= size(C); i++){
		if(length(A->elements[i]) != 0){
			moveFront(A->elements[i]);
			while(index(A->elements[i]) >= 0){
				Entry eA = (Entry)get(A->elements[i]);
				changeEntry(C, i, eA->col, eA->value);
				moveNext(A->elements[i]);
			}
		}	
	}
	return C;
}

// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	Matrix T = newMatrix(size(A));
	for(int i = 1; i <= size(T); i++){
		if(length(A->elements[i]) != 0){
			moveFront(A->elements[i]);
			while(index(A->elements[i]) >= 0){
				Entry ea = (Entry)get(A->elements[i]);
				changeEntry(T, ea->col, i, ea->value);
				moveNext(A->elements[i]);
			}
		}
	}
	return T;			
}

// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	Matrix sM = copy(A);
	for(int i = 1; i <= size(sM); i++){
		moveFront(sM->elements[i]);
		while(index(sM->elements[i]) >= 0){
			Entry esM = (Entry)get(sM->elements[i]);
			esM->value = esM->value * x;
			moveNext(sM->elements[i]);
		}
	}
	return sM;
}

// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	Matrix Sum = newMatrix(size(A));
	Matrix Bc = copy(B);
	for(int i = 1; i <= size(Sum); i++){
		double x;
		List Alist = A->elements[i];
		List Blist = Bc->elements[i];
		moveFront(Alist);
		moveFront(Blist);
		//if there are items in both lists 
		if(length(Alist) !=0 && length(Blist) != 0){
			while(index(Alist) >= 0 && index(Blist) >= 0){
				Entry ea = (Entry)get(Alist);
				Entry eb   = (Entry)get(Blist);
				if(ea->col == eb->col){
					x = (ea->value) + (eb->value);
					moveNext(Alist);
					moveNext(Blist);
					changeEntry(Sum, i, ea->col, x);
				}
				else if(ea->col > eb->col){
					//insertBefore(Sum->elements[i], &eb);
					changeEntry(Sum, i, eb->col, eb->value);
					moveNext(Blist);
				}
				else if(ea->col < eb->col){
					changeEntry(Sum, i, ea->col, ea->value);
					moveNext(Alist);
				}
			}
		}
		while(index(Blist) >= 0){
				Entry eb = (Entry)get(Blist);
				//append(Sum->elements[i], &eb);	
				changeEntry(Sum, i, eb->col, eb->value);		
				moveNext(Blist);		
		}
		while(index(Alist) >= 0){
				Entry ea = (Entry)get(Alist);
				//append(Sum->elements[i], &eb);	
				changeEntry(Sum, i, ea->col, ea->value);		
				moveNext(Alist);
		}
		/*else if(length(Alist) == 0 && length(Blist) != 0){
			moveFront(Blist);
			while(index(Blist) >= 0){
				Entry eb = (Entry)get(Blist);
				//append(Sum->elements[i], &eb);	
				changeEntry(Sum, i, eb->col, eb->value);		
				moveNext(Blist);		
			}
		}
		else if(length(Blist) == 0 && length(Alist) != 0){
			moveFront(Alist);
			while(index(Alist) >= 0){
				Entry ea = (Entry)get(Alist);
				//append(Sum->elements[i], &eb);	
				changeEntry(Sum, i, ea->col, ea->value);		
				moveNext(Alist);		
			}
		}*/
	}
	freeMatrix(&Bc);
	return Sum;
}

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	/*
	Matrix Diff = newMatrix(size(A));
	//for each list in both Matrices
	for(int i = 1; i <= size(Diff); i++){
		double x;
		List Dlist = A->elements[i];
		List Blist = B->elements[i];
		//if there are items in both lists 
		if(length(Dlist) !=0 && length(Blist) != 0){
			moveFront(Dlist);
			moveFront(Blist);
			while(index(Dlist) >= 0 && index(Blist) >= 0){
				Entry ed = (Entry)get(Dlist);
				Entry eb = (Entry)get(Blist);
				if(ed->col == eb->col){
					x = (ed->value) - (eb->value);
					moveNext(Dlist);
					moveNext(Blist);
					changeEntry(Diff, i, ed->col, x);
				}
				else if(ed->col > eb->col && eb->col > 0){
					//D has a 0 row entry
					x = 0 - eb->value;
					moveNext(Blist);
					changeEntry(Diff, i, (eb->col), x);

				}
				else if(ed->col < eb->col && ed->col > 0){
					//B has a 0 row element
					changeEntry(Diff, i, ed->col, ed->value);
					moveNext(Dlist);
				}
			}
		}
		//if first list is empty and second list is full
		else if(length(Dlist) == 0 && length(Blist) != 0){
			//D row entries are all 0
			moveFront(Blist);
			while(index(Blist) >= 0){
				Entry eb = (Entry)get(Blist);
				x = 0 - eb->value;
				changeEntry(Diff, i, eb->col, x);			
				moveNext(Blist);	
			}	
		}
	}
	*/
	Matrix Neg = scalarMult(-1, B);

	Matrix Diff = sum(A, Neg);
	freeMatrix(&Neg);

	return Diff;
}

// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	Matrix Prod = newMatrix(size(A));
	Matrix BT = transpose(B);
	double x = 0;
	if(size(A) != size(B)){
		printf("Error: size(A) does not equal size(B) in call to product()\n");
		exit(-1);
	}

	//For each row in A
	//int counter;
	for(int i = 1; i <= size(A); i++){
		if(length(A->elements[i]) != 0){
			//For each row in B transpose
			for(int j = 1; j <= size(B); j++){
				if(length(BT->elements[j]) != 0){
					x = vectorDot(A->elements[i], BT->elements[j]);
					//printf("x: %.1f ",x);
					//counter++;
					//printf("NNZ: %d Added: %.1f\n", counter, x);
					changeEntry(Prod, i, j, x);
					/*if(x != 0.0){
						counter++;
						printf("NNZ: %d Added: %.1f\n", counter, x);
						changeEntry(Prod, i, j, x);
					}else{
						continue;
					}	*/
					
				}
			}
		}
	}	
	freeMatrix(&BT);
	return Prod;
}

//Returns dot product or row and column
double vectorDot(List P, List Q){
	double x = 0;
	moveFront(P);
	moveFront(Q);
	while(index(P) >= 0 && index(Q) >= 0){
		Entry ep = (Entry)get(P);
		Entry eq = (Entry)get(Q);
		if(ep->col == eq->col){
			double prod = ep->value * eq->value;
			x = x + prod;
			moveNext(P);
			moveNext(Q);
		}
		else if(ep->col < eq->col && ep->col > 0){
			moveNext(P);
		}
		else if(ep->col > eq->col && eq->col >0){
			moveNext(Q);
		}
	}
	return x;
}

//-------------------------------------------------------
//Output Functions
//-------------------------------------------------------

// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	for(int i = 1; i <= size(M); i++){
		moveFront(M->elements[i]);
		
		if(length(M->elements[i]) != 0){
			fprintf(out, "\n%d: ", i);
			while(index(M->elements[i]) >= 0){
				Entry e = (Entry)get(M->elements[i]);
				fprintf(out, "(%d, %.1f) ", e->col, e->value);
				moveNext(M->elements[i]);
			}
		}
		
		/*
		if(length(M->elements[i]) == 0){
			for(int j = 1; j < size(M)+1; j++){
				fprintf(out, "(%d, 0)", j);
			}
		}*/
		
	}
}
