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

bsTree bst;

TEST_SETUP(Basic)
{
	bst = bstCreate();
	bstSetCompare(bst, compare);
}

TEST_TEAR_DOWN(Basic)
{
	bstDestroy(bst);	
}

TEST(Basic, SearchEmptyTree)
{
    int key = 0;
    TEST_ASSERT(NULL == bstSearch(bst, &key));
}

TEST(Basic, SearchRootMatch)
{
    int key = 0;
    int data = 1;
    bstInsert(bst, &key, &data);
    TEST_ASSERT(&data == bstSearch(bst, &key));
}

TEST(Basic, SearchNoMatch)
{
    int key = 0;
    int data = 1;
    bstInsert(bst, &key, &data);

    int key2 = 5;
    TEST_ASSERT(NULL == bstSearch(bst, &key2));
}

TEST(Basic, SearchSmallTreeMatch)
{
    int key = 1;
    int data = 0;
    bstInsert(bst, &key, &data);

    int key2 = 0;
    int data2 = 0;
    bstInsert(bst, &key2, &data2);

    int key3 = 5;
    int data3 = 0;
    bstInsert(bst, &key3, &data3);
    
    int key4 = 2;
    int data4 = 0;
    bstInsert(bst, &key4, &data4);

    TEST_ASSERT(&data4 == bstSearch(bst, &key4));
}

TEST(Basic, InsertReplaceRoot)
{
	int key = 0;
	int data = 1;
    bstInsert(bst, &key, &data);
	TEST_ASSERT(&data == bstSearch(bst, &key));
}

TEST(Basic, InsertionRight)
{
    int key = 1;
    int data = 1;
    bstInsert(bst, &key, &data);

    int key2 = 2;
    int data2 = 2;
    bstInsert(bst, &key2, &data2);
    
    TEST_ASSERT(bst->root->right->key == &key2);
}

TEST(Basic, InsertionLeft)
{
    int key = 1;
    int data = 1;
    bstInsert(bst, &key, &data);

    int key2 = 0;
    int data2 = 2;
    bstInsert(bst, &key2, &data2);
    
    TEST_ASSERT(bst->root->left->key == &key2);
}

TEST(Basic, InsertionNonRootParent)
{
    int key = 1;
    int data = 1;
    bstInsert(bst, &key, &data);

    int key2 = 0;
    int data2 = 2;
    bstInsert(bst, &key2, &data2);

    int key3 = 5;
    int data3 = 2;
    bstInsert(bst, &key3, &data3);

    int key4 = 4;
    int data4 = 2;
    bstInsert(bst, &key4, &data4);
    
    TEST_ASSERT(bst->root->right->left->key == &key4);
}

TEST(Basic, InsertionDuplicateKey)
{
    int key = 1;
    int data = 1;
    bstInsert(bst, &key, &data);

    int key2 = 1;
    int data2 = 2;
    bstInsert(bst, &key2, &data2);
    
    TEST_ASSERT(bst->root->data == &data);
    TEST_ASSERT(bst->root->right->data == &data2);
    TEST_ASSERT(bst->root->left == NULL);
}

TEST(Basic, DeletionNonExistent)
{
    int key = 0;
    int data = 2;
    bstInsert(bst, &key, &data);
    
    int key2 = 1;
    TEST_ASSERT(NULL == bstDelete(bst, &key2));
}

TEST(Basic, DeletionRoot)
{
    int key = 0;
    int data = 2;
    bstInsert(bst, &key, &data);
    
    TEST_ASSERT(bst == bstDelete(bst, &key));
    TEST_ASSERT(bst->root == NULL);
}

TEST(Basic, DeletionNoChildrenNonRoot)
{
    int key = 1;
    int data = 0;
    bstInsert(bst, &key, &data);

    int key2 = 0;
    int data2 = 0;
    bstInsert(bst, &key2, &data2);

    int key3 = 2;
    int data3 = 0;
    bstInsert(bst, &key3, &data3);
    
    TEST_ASSERT(bst == bstDelete(bst, &key3));
    TEST_ASSERT(bst->root->key == &key);
    TEST_ASSERT(bst->root->left->key == &key2);
    TEST_ASSERT(bst->root->right == NULL);
}

TEST(Basic, DeletionOneChild)
{
    int key = 1;
    int data = 0;
    bstInsert(bst, &key, &data);

    int key2 = 0;
    int data2 = 0;
    bstInsert(bst, &key2, &data2);
    
    TEST_ASSERT(bst == bstDelete(bst, &key));
    TEST_ASSERT(bst->root->key == &key2);
    TEST_ASSERT(bst->root->left == NULL);
    TEST_ASSERT(bst->root->right == NULL);
}

TEST(Basic, DeleteTwoChildrenDirectRightSuccessor)
{
    int key = 1;
    int data = 0;
    bstInsert(bst, &key, &data);

    int key2 = 0;
    int data2 = 0;
    bstInsert(bst, &key2, &data2);

    int key3 = 2;
    int data3 = 0;
    bstInsert(bst, &key3, &data3);
    
    TEST_ASSERT(bst == bstDelete(bst, &key));
    TEST_ASSERT(bst->root->key == &key3);
    TEST_ASSERT(bst->root->left->key == &key2);
    TEST_ASSERT(bst->root->right == NULL);
}

TEST(Basic, DeleteTwoChildrenNonDirectRightSuccessor)
{
    int key = 1;
    int data = 0;
    bstInsert(bst, &key, &data);

    int key2 = 0;
    int data2 = 0;
    bstInsert(bst, &key2, &data2);

    int key3 = 5;
    int data3 = 0;
    bstInsert(bst, &key3, &data3);
    
    int key4 = 2;
    int data4 = 0;
    bstInsert(bst, &key4, &data4);

    TEST_ASSERT(bst == bstDelete(bst, &key));
    TEST_ASSERT(bst->root->key == &key4);
    TEST_ASSERT(bst->root->left->key == &key2);
    TEST_ASSERT(bst->root->right->key == &key3);
}