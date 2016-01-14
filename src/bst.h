#ifndef BST_H
#define BST_H

typedef struct bsTree* bsTree;

/* Create a new bsTree.
 *
 * Return a new bsTree on success, and NULL on error. */
bsTree bstCreate(void);

/* Free bst and its internal structures. If freeData and freeKey functions
 * are specified (bstSetFreeData(), bstSetFreeKey())  
 * they are used to free the key and data pointers.*/
void bstDestroy(bsTree bst);


/* Search for key in bst. If the compare function is specified (bstSetCompare())
 * it is used to compare keys.
 * 
 * Return the data associated with key on success and NULL on error. */
void *bstSearch(bsTree bst, void *key);

/* Insert key and data into bst. If the compare function is 
 * specified (bstSetCompare()) it is used to compare keys.
 * 
 * Return bst on success and NULL on error. */
void *bstInsert(bsTree bst, void *key, void *data);

/* Delete the given key and its associated data from bst. 
 * If freeData and freeKey functions are specified 
 * (bstSetFreeData(), bstSetFreeKey()) they are used to free 
 * the the key and data pointers in bst.
 *
 * Return bst on success and NULL on error.*/
void *bstDelete(bsTree bst, void *key);


/* Recursively print the keys in bst. */
void bstPrintKeys(bsTree bst);


/* Set the compare function to be used when modifying bst. */
void bstSetCompare(bsTree bst, int (*compare) (void *key1, void *key2));

/* Set the free function to be used when freeing data pointers in bst. */
void bstSetFreeData(bsTree bst, void (*freeData) (void *data));

/* Set the free function to be used when freeing key pointers in bst. */
void bstSetFreeKey(bsTree bst, void (*freeKey) (void *key));

#endif
