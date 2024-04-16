// test cases
#include "dlist.h"
int main()
{
	DList l;
	createDList(&l);
	traverse(&l, printNodeInfo);
	doubleLinkedEntry e[100];
	Info info[] = {{1, "saloma"}, {2, "B"}, {3, "C"}, {4, "D"},
				   {5, "E"},	  {6, "F"}, {7, "G"}};
	insert(&l, info[1]);
	insert(&l, info[0]);
	insert(&l, info[5]);
	insert(&l, info[4]);
	insert(&l, info[3]);
	insert(&l, info[6]);
	insert(&l, info[2]);
	/*deleteFirst(&l, e);
	deleteFirst(&l, e);
	deleteFromDList(&l, 8, e);
	deleteFromDList(&l, 0, e);
	deleteFromDList(&l, 3, e);
	insert(&l, info[0]);*/
	writeToFile(&l, "test.txt");
	DList dl;
	readFile(&dl, "test.txt");
	ShowAllLines("test.txt");
	printf("%d\n", ShowLineLength("test.txt", 1));
	printf("%d\n", ShowLineLength("test.txt", 2));

	// traverse(&dl, printNodeInfo);
	//  traverse(&l, printNodeEntry);
}
