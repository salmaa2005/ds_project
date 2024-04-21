#include "dlist.h"

void createDList(DList *pdl)
{
	pdl->head = NULL;
	pdl->tail = NULL;
	pdl->size = 0;
}

int DListFull(DList *pdl)
{
	return 0;
}
int DListEmpty(DList *pdl)
{
	return pdl->head == NULL;
}

// returns -1 if allocation failed
// returns 0 when key is invalid (out of bounds)
// returns 1 if successful
int insert(DList *pdl, doubleLinkedEntry e[], int pos)
{
	Node *pn = (Node *)malloc(sizeof(Node));
	if (!pn)
		return -1;
	if (pos < 0 || pos > pdl->size + 1)
		return 0;

	strcpy(pn->entry, e);
	if (!pdl->head)
	{
		pn->next = NULL;
		pn->prev = NULL;
		pdl->head = pn;
		pdl->tail = pn;
	}
	else
	{
		int ctr = 1;
		Node *trav = pdl->head;

		while (pos > ctr && trav->next)
		{
			ctr++;
			trav = trav->next;
		}

		if (pos > ctr && !trav->next)
		{
			pn->next = NULL;
			pn->prev = trav;
			trav->next = pn;
			pdl->tail = pn;
		}
		else
		{
			pn->next = trav;
			pn->prev = trav->prev;
			if (pn->prev)
				trav->prev->next = pn;
			else
				pdl->head = pn;
		}
	}
	pdl->size++;
	return 1;
}

// returns -1 if list is empty
// returns 0 if position is out of bounds
// returns 1 if element is deleted successfully
int deleteFromDList(DList *pdl, doubleLinkedEntry pe[], int pos)
{
	if (!pdl->head)
		return -1;
	if (pos < 1 || pos > pdl->size)
		return 0;
	Node *trav = pdl->head;

	int ctr = 1;
	while (ctr < pos)
	{
		ctr++;
		trav = trav->next;
	}
	strcpy(pe, trav->entry);
	if (!trav->prev)
	{
		pdl->head = trav->next;
		pdl->head->prev = NULL;
	}
	else if (!trav->next)
	{
		pdl->tail = trav->prev;
		pdl->tail->next = NULL;
	}
	else
	{
		trav->prev->next = trav->next;
		trav->next->prev = trav->prev;
	}
	free(trav);
	pdl->size--;
	return 1;
}

// returns -1 if list is empty
// returns 1 if element is deleted successfully
int deleteFirst(DList *pdl, doubleLinkedEntry pe[])
{
	if (!pdl->head)
		return -1;
	Node *trav = pdl->head;
	strcpy(pe, trav->entry);

	if (pdl->size == 1)
	{
		pdl->head = NULL;
		pdl->tail = NULL;
	}
	else
	{
		pdl->head = trav->next;
		pdl->head->prev = NULL;
	}
	free(trav);
	pdl->size--;
	return 1;
}
void traverse(DList *pdl, void (*pf)(doubleLinkedEntry e[]))
{
	Node *trav = pdl->head;
	while (trav)
	{
		(*pf)(trav->entry);
		trav = trav->next;
	}
}

/**************** Additional functions: ****************/
void printNodeEntry(doubleLinkedEntry e[])
{
	printf("Entry: %s\n", e);
}

/**************** Project-related functions: ****************/

// returns 0 if allocation failed
// returns 1 if successful
// adds a line to the end of the list
int addLineToDList(DList *pdl, char *line)
{
	Node *pn = (Node *)malloc(sizeof(Node));
	if (!pn)
		return 0;
	strcpy(pn->entry, line);
	if (!pdl->head)
	{
		pdl->head = pn;
		pdl->tail = pn;
		pn->next = NULL;
		pn->prev = NULL;
	}
	else
	{
		pn->prev = pdl->tail;
		pn->next = NULL;
		pdl->tail->next = pn;
		pdl->tail = pn;
	}
	pdl->size++;
	return 1;
}

// returns 0 if file could not be opened
// returns 1 if file was successfully read
int readFile(DList *pdl, char *fileName)
{
	FILE *fp = fopen(fileName, "r");
	if (!fp)
		return 0;
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), fp))
	{
		for (int i = 0; i < strlen(buffer); i++)
		{
			if (buffer[i] == '\n')
			{
				buffer[i] = '\0';
				break;
			}
		}
		addLineToDList(pdl, buffer);
	}
	fclose(fp);
	return 1;
}
// returns 0 if file could not be opened
// returns 1 if file was successfully written
int writeToFile(DList *pdl, char *fileName)
{
	FILE *fp = fopen(fileName, "w");
	if (!fp)
		return 0;
	Node *trav = pdl->head;
	while (trav)
	{
		fprintf(fp, "%s\n", trav->entry); // writes the entry to the file
		trav = trav->next;
	}
	fclose(fp);
	return 1;
}

// returns 0 if file could not be opened
// returns 1 if file was successfully displayed
int ShowAllLines(char *fileName)
{
	int LineNum = 1;
	FILE *fp = fopen(fileName, "r");
	if (!fp)
		return 0;
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), fp))
	{
		printf("%d. %s", LineNum, buffer);
		LineNum++;
	}
	fclose(fp);
	return 1;
}

// returns -1 if line not found
// returns 0 if file could not be opened
// returns the length of the line if found
int ShowLineLength(char *fileName, int lineNum)
{
	FILE *fp = fopen(fileName, "r");
	if (!fp)
		return 0;
	char buffer[BUFFER_SIZE];
	int LineNumber = 1;
	while (fgets(buffer, sizeof(buffer), fp))
	{
		if (LineNumber == lineNum)
		{
			fclose(fp);
			return strlen(buffer) - 1; // because the last character is \n
		}
		LineNumber++;
	}
	fclose(fp);
	return -1;
}
