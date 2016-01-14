#include "bst.h"
#include <stdlib.h>

int compare(void *x, void *y) {
	int x1 = *((int *)x);
	int y1 = *((int *)y);
	if (x1 < y1)
		return -1;
	else if (x1 == y1)
		return 0;
	else 
		return 1;
}

int main() {
	bst bsTree = bstCreate();
	bstSetCompare(bsTree, compare);
	int key = 5;
	bstInsert(bsTree, &key, NULL);
	int key2 = 0;
	bstInsert(bsTree, &key2, NULL);
	int key3 = 10;
	bstInsert(bsTree, &key3, NULL);
	int key4 = 2;
	bstInsert(bsTree, &key4, NULL);
	bstPrintKeys(bsTree);
	
	bstDelete(bsTree, &key3);
	bstPrintKeys(bsTree);
	bstDelete(bsTree, &key);
	bstPrintKeys(bsTree);
	bstDestroy(bsTree);

 return 0;
}
