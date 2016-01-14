#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "bst.h"

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
	// Simple example of usage 
	bsTree bst = bstCreate();
	bstSetCompare(bst, compare);

	int key_data[12] = {38, 13, 51, 10, 12, 40, 84, 25, 89, 37, 66, 95};
	int *keys[12];
	char *data[12];
	char data_count = 'a';

	for (int i = 0; i < 12; i++) {
		keys[i] = malloc(sizeof(**keys));
		data[i] = malloc(sizeof(**data));
		assert(keys[i] != NULL);
		assert(data[i] != NULL);
		*(keys[i]) = key_data[i];
		*(data[i]) = data_count++;
		printf("key = %d data = %c\n", *keys[i], *data[i]);
		bstInsert(bst, keys[i], data[i]);
	}

	printf("\ntree: ");
	bstPrintKeys(bst);
	printf("\n");


	printf("Checking tree data:\n");
	for (int i = 0; i < 12; i++) {
		assert(bstSearch(bst, keys[i]) == data[i]);
	}
	printf("Success\n\n");

	// remove key of root from tree
	// comparison to find key in tree is done using compare 
	// function defined above so no need to use original key
	// pointer
	int root = 38;
	printf("Deleting root (key = %d):\n", root);
	bstDelete(bst, &root);
	printf("tree: ");
	bstPrintKeys(bst);
	assert(bstSearch(bst, &root) == NULL);
	printf("Success\n\n");

	// key of what should be the new root
	// it is at index 5 of key_data so should have data at
	// index 5 of data array
	int new_root = 40;
	printf("Checking new root (key = %d):\n", new_root);
	assert(bstSearch(bst, &new_root) == data[5]);
	printf("Success\n");

	bstSetFreeData(bst, free);
	bstSetFreeKey(bst, free);
	bstDestroy(bst);

	return 0;
}
