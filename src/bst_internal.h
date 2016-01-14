#ifndef BST_INTERNAL_H
#define BST_INTERNAL_H

/* NOTE: 
 * THIS HEADER IS ONLY FOR TESTING PURPOSES 
 * (see tests directory) */

struct bsTreeNode {
	struct bsTreeNode *left;
	struct bsTreeNode *right;
	struct bsTreeNode *parent;
	void *key;
	void *data;
};

struct bsTree {
	struct bsTreeNode *root;
	int (*compare) (void *key1, void *key2);
	void (*freeData) (void *data);
	void (*freeKey) (void *key);
};

#endif