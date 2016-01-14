#ifndef BST_H
#define BST_H

typedef struct bsTree* bst;

/* Create a new bsTree.
 *
 * Return a new bsTree on success, and NULL on error. */
bst bstCreate(void);

/* Free bst and its internal structures. If freeValue and freeKey functions
 * are specified (bstSetFreeValue(), bstSetFreeKey())  
 * they are used to free the key and value pointers.*/
void bstDestroy(bst bsTree);


/* Search for key in bst. If the compare function is specified (bstSetCompare())
 * it is used to compare keys.
 * 
 * Return the value associated with key on success and NULL on error. */
void *bstSearch(bst bsTree, void *key);

/* Insert key and value into bst. If the compare function is 
 * specified (bstSetCompare()) it is used to compare keys.
 * 
 * Return bst on success and NULL on error. */
void *bstInsert(bst bsTree, void *key, void *value);

/* Delete the given key and its associated value from bst. 
 * If freeValue and freeKey functions are specified 
 * (bstSetFreeValue(), bstSetFreeKey()) they are used to free 
 * the the key and value pointers in bst.
 *
 * Return bst on success and NULL on error.*/
void *bstDelete(bst bsTree, void *key);


/* Recursively print the keys in bst. */
void bstPrintKeys(bst bsTree);


/* Set the compare function to be used when modifying bst. */
void bstSetCompare(bst bsTree, int (*compare) (void *key1, void *key2));

/* Set the free function to be used when freeing value pointers in bst. */
void bstSetFreeValue(bst bsTree, void (*freeValue) (void *value));

/* Set the free function to be used when freeing key pointers in bst. */
void bstSetFreeKey(bst bsTree, void (*freeKey) (void *key));

#endif
