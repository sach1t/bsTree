#include <stdio.h>
#include "bst.h"
#include "unity.h"
#include "unity_fixture.h"
#include "bst_internal.h"

TEST_GROUP(Basic);

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

bst bsTree;

TEST_SETUP(Basic)
{
	bsTree = bstCreate();
	bstSetCompare(bsTree, compare);
}

TEST_TEAR_DOWN(Basic)
{
	bstDestroy(bsTree);	
}

TEST(Basic, SearchEmptyTree)
{
    int key = 0;
    TEST_ASSERT(NULL == bstSearch(bsTree, &key));
}

TEST(Basic, SearchRootMatch)
{
    int key = 0;
    int val = 1;
    bstInsert(bsTree, &key, &val);
    TEST_ASSERT(&val == bstSearch(bsTree, &key));
}

TEST(Basic, SearchNoMatch)
{
    int key = 0;
    int val = 1;
    bstInsert(bsTree, &key, &val);

    int key2 = 5;
    TEST_ASSERT(NULL == bstSearch(bsTree, &key2));
}

TEST(Basic, SearchSmallTreeMatch)
{
    int key = 1;
    int val = 0;
    bstInsert(bsTree, &key, &val);

    int key2 = 0;
    int val2 = 0;
    bstInsert(bsTree, &key2, &val2);

    int key3 = 5;
    int val3 = 0;
    bstInsert(bsTree, &key3, &val3);
    
    int key4 = 2;
    int val4 = 0;
    bstInsert(bsTree, &key4, &val4);

    TEST_ASSERT(&val4 == bstSearch(bsTree, &key4));
}

TEST(Basic, InsertReplaceRoot)
{
	int key = 0;
	int val = 1;
    bstInsert(bsTree, &key, &val);
	TEST_ASSERT(&val == bstSearch(bsTree, &key));
}

TEST(Basic, InsertionRight)
{
    int key = 1;
    int val = 1;
    bstInsert(bsTree, &key, &val);

    int key2 = 2;
    int val2 = 2;
    bstInsert(bsTree, &key2, &val2);
    
    TEST_ASSERT(bsTree->root->right->key == &key2);
}

TEST(Basic, InsertionLeft)
{
    int key = 1;
    int val = 1;
    bstInsert(bsTree, &key, &val);

    int key2 = 0;
    int val2 = 2;
    bstInsert(bsTree, &key2, &val2);
    
    TEST_ASSERT(bsTree->root->left->key == &key2);
}

TEST(Basic, InsertionNonRootParent)
{
    int key = 1;
    int val = 1;
    bstInsert(bsTree, &key, &val);

    int key2 = 0;
    int val2 = 2;
    bstInsert(bsTree, &key2, &val2);

    int key3 = 5;
    int val3 = 2;
    bstInsert(bsTree, &key3, &val3);

    int key4 = 4;
    int val4 = 2;
    bstInsert(bsTree, &key4, &val4);
    
    TEST_ASSERT(bsTree->root->right->left->key == &key4);
}

TEST(Basic, DeletionNonExistent)
{
    int key = 0;
    int val = 2;
    bstInsert(bsTree, &key, &val);
    
    int key2 = 1;
    TEST_ASSERT(NULL == bstDelete(bsTree, &key2));
}

TEST(Basic, DeletionRoot)
{
    int key = 0;
    int val = 2;
    bstInsert(bsTree, &key, &val);
    
    TEST_ASSERT(bsTree == bstDelete(bsTree, &key));
    TEST_ASSERT(bsTree->root == NULL);
}

TEST(Basic, DeletionNoChildrenNonRoot)
{
    int key = 1;
    int val = 0;
    bstInsert(bsTree, &key, &val);

    int key2 = 0;
    int val2 = 0;
    bstInsert(bsTree, &key2, &val2);

    int key3 = 2;
    int val3 = 0;
    bstInsert(bsTree, &key3, &val3);
    
    TEST_ASSERT(bsTree == bstDelete(bsTree, &key3));
    TEST_ASSERT(bsTree->root->key == &key);
    TEST_ASSERT(bsTree->root->left->key == &key2);
    TEST_ASSERT(bsTree->root->right == NULL);
}

TEST(Basic, DeletionOneChild)
{
    int key = 1;
    int val = 0;
    bstInsert(bsTree, &key, &val);

    int key2 = 0;
    int val2 = 0;
    bstInsert(bsTree, &key2, &val2);
    
    TEST_ASSERT(bsTree == bstDelete(bsTree, &key));
    TEST_ASSERT(bsTree->root->key == &key2);
    TEST_ASSERT(bsTree->root->left == NULL);
    TEST_ASSERT(bsTree->root->right == NULL);
}

TEST(Basic, DeleteTwoChildrenDirectRightSuccessor)
{
    int key = 1;
    int val = 0;
    bstInsert(bsTree, &key, &val);

    int key2 = 0;
    int val2 = 0;
    bstInsert(bsTree, &key2, &val2);

    int key3 = 2;
    int val3 = 0;
    bstInsert(bsTree, &key3, &val3);
    
    TEST_ASSERT(bsTree == bstDelete(bsTree, &key));
    TEST_ASSERT(bsTree->root->key == &key3);
    TEST_ASSERT(bsTree->root->left->key == &key2);
    TEST_ASSERT(bsTree->root->right == NULL);
}

TEST(Basic, DeleteTwoChildrenNonDirectRightSuccessor)
{
    int key = 1;
    int val = 0;
    bstInsert(bsTree, &key, &val);

    int key2 = 0;
    int val2 = 0;
    bstInsert(bsTree, &key2, &val2);

    int key3 = 5;
    int val3 = 0;
    bstInsert(bsTree, &key3, &val3);
    
    int key4 = 2;
    int val4 = 0;
    bstInsert(bsTree, &key4, &val4);

    TEST_ASSERT(bsTree == bstDelete(bsTree, &key));
    TEST_ASSERT(bsTree->root->key == &key4);
    TEST_ASSERT(bsTree->root->left->key == &key2);
    TEST_ASSERT(bsTree->root->right->key == &key3);
}