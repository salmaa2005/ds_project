#ifndef _DLIST_H
#define _DLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef char doubleLinkedEntry;

typedef struct node
{
	doubleLinkedEntry entry[1024];
	struct node *prev;
	struct node *next;
} Node;
typedef struct
{
	Node *head;
	Node *tail;
	int size;
} DList;
void createDList(DList *);
int DListFull(DList *);
int DListEmpty(DList *);
int insert(DList *pdl, doubleLinkedEntry e[], int pos);
int deleteFromDList(DList *pdl, doubleLinkedEntry e[], int pos);
int deleteFirst(DList *pdl, doubleLinkedEntry pe[]);
void traverse(DList *pdl, void (*pf)(doubleLinkedEntry e[]));

/* Additional functions */
void printNodeEntry(doubleLinkedEntry e[]);

/* Project-related functions: */
// all of them return 0 if file didn't open
// -1 if any other error
// 1 if successful
int addLineToDList(DList *pdl, char *line);
int readFile(DList *pdl, char *fileName);		 // R
int writeToFile(DList *pdl, char *fileName);	 // W
int ShowAllLines(char *fileName);				 // S
int ShowLineLength(char *fileName, int lineNum); // L
// calculates and returns the length of a line

#endif
