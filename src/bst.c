#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "bst_internal.h"

/* Default comparison for keys in the tree. */
static int pointerCompare(void *key1, void *key2) {
	if (key1 < key2) return -1;
	else if (key1 == key2) return 0;
	else return 1;
}

/* Create a new bsTree.
 *
 * Return a new bsTree on success, and NULL on error. */
struct bsTree *bstCreate(void) {
	struct bsTree *bst;

	if((bst = malloc(sizeof(*bst))) ==  NULL)
		return NULL;
	bst->root = NULL;
	bst->compare = pointerCompare;
	bst->freeData = NULL;
	bst->freeKey = NULL;
	return bst;
}

/* Free all nodes in bst. If freeData and freeKey functions
 * are specified (bstSetFreeData(), bstSetFreeKey()) 
 * they are used to free the node's key and data pointers. */
static void freeTreeNodes(struct bsTree *bst, struct bsTreeNode *node) {
	if (node == NULL)
		return;
	
	freeTreeNodes(bst, node->left);
	freeTreeNodes(bst, node->right);
	if (bst->freeData)
		bst->freeData(node->data);
	if (bst->freeKey)
		bst->freeKey(node->key);
	free(node);
}

/* Free bst and its internal structures. If freeData and freeKey functions
 * are specified (bstSetFreeData(), bstSetFreeKey())  
 * they are used to free the key and data pointers.*/
void bstDestroy(struct bsTree *bst) {
	freeTreeNodes(bst, bst->root);
	free(bst);
}

/* Search for key in bst. If the compare function is specified (bstSetCompare())
 * it is used to compare keys.
 * 
 * Return the data associated with key on success and NULL on error. */
void *bstSearch(struct bsTree *bst, void *key) {
	struct bsTreeNode *node = bst->root;
	int comparison;

	while (node) {
		comparison = bst->compare(key, node->key);
		if (comparison == 0)
			return node->data;
		else if (comparison < 0)
			node = node->left;
		else
			node = node->right;
	}

	return NULL;
}

/* Search for a node with the key specified in bst.
 * If the compare function is specified (bstSetCompare())
 * it is used to compare keys.
 *
 * Return the node associated with key on success and NULL on error.*/
static void *bstSearchNode(struct bsTree *bst, void *key) {
	struct bsTreeNode *node = bst->root;
	int comparison;

	while (node) {
		comparison = bst->compare(key, node->key);
		if (comparison == 0)
			return node;
		else if (comparison < 0)
			node = node->left;
		else
			node = node->right;
	}

	return NULL;
}

/* Insert key and data into bst. If the compare function is 
 * specified (bstSetCompare()) it is used to compare keys.
 * 
 * Return bst on success and NULL on error. */
void *bstInsert(struct bsTree *bst, void *key, void *data) {
	// create new node
	struct bsTreeNode *newNode;
	if((newNode = malloc(sizeof(*newNode))) == NULL)
		return NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->key = key;
	newNode->data = data;

	struct bsTreeNode *node = bst->root;
	struct bsTreeNode *parent = NULL;
	while (node) {
		parent = node;
		if (bst->compare(newNode->key, node->key) < 0)
			node = node->left;
		else
			node = node->right;
	}

	newNode->parent = parent;
	if (parent == NULL)
		bst->root = newNode;
	else if (bst->compare(newNode->key, parent->key) < 0)
		parent->left = newNode;
	else
		parent->right = newNode;

	return bst;
}

/* Find the minimum key in the subtree.
 * 
 * Return the minimum node in the subtree.*/
static struct bsTreeNode *bstMin(struct bsTreeNode *subtree) {
	struct bsTreeNode *node = subtree;

	while(node && node->left)
		node = node->left;

	return node;
}

/* Find the maximum key in the subtree.
 * 
 * Return the maximum node in the subtree.*/
static struct bsTreeNode *bstMax(struct bsTreeNode *subtree) {
	struct bsTreeNode *node = subtree;

	while(node && node->right)
		node = node->right;
	

	return node;
}

/* Replace node u with node v in bst. */
static void bstTransplant(struct bsTree *bst, struct bsTreeNode *u, struct bsTreeNode *v) {
	if (u->parent == NULL)
		bst->root = v; 
	else 
		if (u->parent->left == u)
			u->parent->left = v;
		else if (u->parent->right == u)
			u->parent->right = v; 

	if (v != NULL)
		v->parent = u->parent;
}

/* Delete the given key and its associated data from bst. 
 * If freeData and freeKey functions are specified 
 * (bstSetFreeData(), bstSetFreeKey()) they are used to free 
 * the the key and data pointers in bst.
 *
 * Return bst on success and NULL on error.*/
void *bstDelete(struct bsTree *bst, void *key) {
	struct bsTreeNode *node = bstSearchNode(bst, key);

	if (node == NULL) {
		return NULL;
	}

	if (node->left == NULL) {
		bstTransplant(bst, node, node->right);
	} else if (node->right == NULL) {
		bstTransplant(bst, node, node->left);
	} else {
		struct bsTreeNode *successor = bstMin(node->right);
		if (node->right != successor) {
			bstTransplant(bst, successor, successor->right);
			successor->right = node->right;
			successor->right->parent = successor;
		}
		bstTransplant(bst, node, successor);
		successor->left = node->left;
		successor->left->parent = successor;	
	}

	if (bst->freeData)
		bst->freeData(node->data);
	if (bst->freeKey)
		bst->freeKey(node->key);
	free(node);

	return bst;
}

/* Recursively print the keys in the subtree specified 
 * by the given node. */
static void bstPrintRec(struct bsTreeNode *node) {
	if (node == NULL) {
		printf("-");
		return;
	}

	printf("%d", *((int *)node->key));

	if (node->left == NULL && node->right == NULL)
		return;

	printf(" [");
	bstPrintRec(node->left);
	printf(", ");
	bstPrintRec(node->right);
	printf("] ");
}

/* Recursively print the keys in bst. */
void bstPrintKeys(struct bsTree *bst) {
	bstPrintRec(bst->root);
	printf("\n");
}

/* Set the compare function to be used when modifying bst. */
void bstSetCompare(struct bsTree *bst, int (*compare) (void *key1, void *key2)) {
	if (compare)
		bst->compare = compare; 
}

/* Set the free function to be used when freeing data pointers in bst. */
void bstSetFreeData(struct bsTree *bst, void (*freeData) (void *data)) {
	if (freeData)
		bst->freeData = freeData;
}

/* Set the free function to be used when freeing key pointers in bst. */
void bstSetFreeKey(struct bsTree *bst, void (*freeKey) (void *key)) {
	if (freeKey)
		bst->freeKey = freeKey; 
}
