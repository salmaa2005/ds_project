// test cases
#include "dlist.h"
int main()
{
	DList l;
	createDList(&l);
	traverse(&l, printNodeEntry);
	doubleLinkedEntry e[100];

	/*insert(&l, "salma", 1);
	insert(&l, "salalem", 2);
	insert(&l, "seleem", 3);
	insert(&l, "salem", 4);
	insert(&l, "saloma", 5);
  */

	/*
	 * deleteFirst(&l, e);
	 * deleteFirst(&l, e);
	 */
	// deleteFromDList(&l, e, 0);
	// deleteFromDList(&l, e, 6);
	// deleteFromDList(&l, e, 3);
	//  insert(&l, "saloma");

	// addLineToDList(&l, "lulu :3");
	// addLineToDList(&l, "saloom");
	// writeToFile(&l, "test.txt");
	//  DList dl;
	readFile(&l, "test.txt");
	/*
  ShowAllLines("test.txt");
	printf("Line 1 Length: %d\n", ShowLineLength("test.txt", 1));
	// printf("Line 2 Length: %d\n", ShowLineLength("test.txt", 2));
	printf("Line 3 Length: %d\n", ShowLineLength("test.txt", 3));
	printf("Line 4 Length: %d\n", ShowLineLength("test.txt", 4));
	// 	printf("Line 5 Length: %d\n", ShowLineLength("test.txt", 5));
	printf("Line 6 Length: %d\n", ShowLineLength("test.txt", 6));
	printf("Line 7 Length: %d\n", ShowLineLength("test.txt", 7));
  */

	traverse(&l, printNodeEntry);
}
