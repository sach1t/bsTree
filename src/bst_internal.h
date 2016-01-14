#ifndef BST_INTERNAL_H
#define BST_INTERNAL_H

/* NOTE: 
 * THIS HEADER IS ONLY FOR TESTING PURPOSES */

struct bsTreeNode {
	struct bsTreeNode *left;
	struct bsTreeNode *right;
	struct bsTreeNode *parent;
	void *key;
	void *value;
};

struct bsTree {
	struct bsTreeNode *root;
	int (*compare) (void *key1, void *key2);
	void (*freeValue) (void *value);
	void (*freeKey) (void *key);
};

#endif