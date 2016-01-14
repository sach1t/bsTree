#include "bst.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

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

	int *keys[10];
	char *data[10];
	char data_count = 'a';

	for (int i = 0; i < 10; i++) {
		keys[i] = malloc(sizeof(**keys));
		data[i] = malloc(sizeof(**data));
		assert(keys[i] != NULL);
		assert(data[i] != NULL);
		*(keys[i]) = rand() % 100;
		*(data[i]) = data_count++;
		printf("key = %d data = %c\n", *keys[i], *data[i]);
		bstInsert(bst, keys[i], data[i]);
	} 

	bstPrintKeys(bst);
	bstSetFreeData(bst, free);
	bstSetFreeKey(bst, free);
	bstDestroy(bst);

	return 0;
}
