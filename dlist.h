#ifndef _DLIST_H
#define _DLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef char doubleLinkedEntry;

// struct created
typedef struct
{
	int Key;
	doubleLinkedEntry entry[1024]; // specified size edited
} Info;

typedef struct node
{
	Info info;
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
int insert(DList *pdl, Info info); // return and argument types edited
int deleteFromDList(DList *pdl, int pos,
					doubleLinkedEntry e[]);			 // return type edited
int deleteFirst(DList *pdl, doubleLinkedEntry pe[]); // return type edited
void traverse(DList *pdl, void (*pf)(Info)); // argument of the function changed

/* Additional functions */
void printNodeInfo(Info info);
void printNodeEntry(Info info);

/* Project-related functions: */
// all of them return 0 if file didn't open
// -1 if any other error
// 1 if successful
int addLineToDList(DList *pdl, char *line);
int readFile(DList *pdl, char *fileName);	 // R
int writeToFile(DList *pdl, char *fileName); // W
int ShowAllLines(char *fileName);			 // S
int ShowLineLength(char *fileName,
				   int lineNum); // returns the length of the line
// calculates and returns the length of a line

#endif
