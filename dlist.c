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
// returns 0 when key is invalid
// returns 1 if successful
int insert(DList *pdl, Info info)
{
	Node *pn = (Node *)malloc(sizeof(Node));
	if (!pn || info.Key < 1)
		return 0;
	pn->info = info;
	if (!pdl->head)
	{
		pn->next = NULL;
		pn->prev = NULL;
		pdl->head = pn;
		pdl->tail = pn;
	}
	else
	{
		Node *trav = pdl->head;
		while (info.Key > trav->info.Key && trav->next)
			trav = trav->next;
		if (info.Key > trav->info.Key && !trav->next)
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
int deleteFromDList(DList *pdl, int pos, doubleLinkedEntry pe[])
{
	if (pdl->head == NULL)
		return -1;
	if (pos < 0 || pos > pdl->tail->info.Key || pos < pdl->head->info.Key)
		return 0;
	Node *trav = pdl->head;
	for (int i = 0; pe[i] != '\0'; i++)
		pe[i] = trav->info.entry[i];
	trav = pdl->head;
	while (trav->info.Key < pos)
		trav = trav->next;
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
	for (int i = 0; trav->info.entry[i] != '\0'; i++)
		pe[i] = trav->info.entry[i];
	trav = pdl->head;
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
void traverse(DList *pdl, void (*pf)(Info))
{
	Node *trav = pdl->head;
	while (trav)
	{
		(*pf)(trav->info);
		trav = trav->next;
	}
}

/* Additional functions: */
void printNodeInfo(Info info)
{
	printf("Key: %d\n", info.Key);
	printf("Entry: %s\n", info.entry);
}

void printNodeEntry(Info info)
{
	printf("Entry: %s\n", info.entry);
}

/* Project-related functions: */

// returns 0 if allocation failed
// returns 1 if successful
// adds a line to the end of the list
int addLineToDList(DList *pdl, char *line)
{
	Node *pn = (Node *)malloc(sizeof(Node));
	if (!pn)
		return 0;
	if (!pdl->head)
	{
		pdl->head = pn;
		pdl->tail = pn;
		pn->next = NULL;
		pn->prev = NULL;
		pn->info.Key = 1;
	}
	else
	{
		pn->prev = pdl->tail;
		pn->next = NULL;
		pdl->tail->next = pn;
		pdl->tail = pn;
		pn->info.Key = pdl->tail->info.Key + 1;
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
		fprintf(fp, "%s\n", trav->info.entry); // writes the entry to the file
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
