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
	bsTree bst = bstCreate();
	bstSetCompare(bst, compare);
	int key = 5;
	bstInsert(bst, &key, NULL);
	int key2 = 0;
	bstInsert(bst, &key2, NULL);
	int key3 = 10;
	bstInsert(bst, &key3, NULL);
	int key4 = 2;
	bstInsert(bst, &key4, NULL);
	bstPrintKeys(bst);
	
	bstDelete(bst, &key3);
	bstPrintKeys(bst);
	bstDelete(bst, &key);
	bstPrintKeys(bst);
	bstDestroy(bst);

 return 0;
}
