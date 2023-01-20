/*
-------------------------------------------------
Class: CSE101
Project: pa1
Name: Anderson Compalas
CRUZID: 1793470
Filename: Lex.c
-------------------------------------------------
*/

#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 300

int main(int argc, char *argv[]){
	int n = 0;
	FILE *in, *out;
	char line[MAX_LEN];

	// Check if command line received correct number of arguments
	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// Open files for reading and writing
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if(in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if(out == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	// Read each line of input file, store in array, and increment count.
	while(fgets(line, MAX_LEN, in) != NULL){
		n++;
	}
	rewind(in); //Resets input line to start of file.

	//Build array
	char** arr = calloc(n, sizeof(char*));
	for(int i = 0; i < n; i++){
		fgets(line, MAX_LEN, in);
		arr[i] = calloc(strlen(line)+1, sizeof(char));
		strcpy(arr[i], line);
	}

	//Build List
	List list = newList();
	append(list, 0);
	moveFront(list);
	for(int i = 1; i < n; i++){
		moveFront(list);
		int key = get(list);
		while(strcmp(arr[key], arr[i]) <= 0){
			moveNext(list);
			if(index(list) == -1){
				break;
			}
			key = get(list);
		}
		if(index(list) != -1){
			insertBefore(list, i);
		}
		else{
			append(list, i);
		}
	}	

	//Print to output file
	printList(stdout, list);
	printf("\n");
	moveFront(list);
	while(index(list) != -1){
		printf("%s", arr[get(list)]);
		fprintf(out, "%s", arr[get(list)]);
		moveNext(list);
	}

	// Close files and free memory
	fclose(in);
	fclose(out);
	for(int j = 0; j < n; j++){
		free(arr[j]);
	}
	free(arr);
	freeList(&list);
	exit(EXIT_SUCCESS);
}

/* ----------------------------------- END OF FILE ----------------------------------------------- */
