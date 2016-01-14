#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Basic)
{
	RUN_TEST_CASE(Basic, SearchEmptyTree); 
	RUN_TEST_CASE(Basic, SearchRootMatch); 
	RUN_TEST_CASE(Basic, SearchNoMatch); 
	RUN_TEST_CASE(Basic, SearchSmallTreeMatch); 

	RUN_TEST_CASE(Basic, InsertReplaceRoot); 
	RUN_TEST_CASE(Basic, InsertionRight); 
	RUN_TEST_CASE(Basic, InsertionLeft); 
	RUN_TEST_CASE(Basic, InsertionNonRootParent); 
	RUN_TEST_CASE(Basic, InsertionDuplicateKey); 

	RUN_TEST_CASE(Basic, DeletionNonExistent); 
	RUN_TEST_CASE(Basic, DeletionRoot); 
	RUN_TEST_CASE(Basic, DeletionNoChildrenNonRoot); 
	RUN_TEST_CASE(Basic, DeletionOneChild); 
	RUN_TEST_CASE(Basic, DeleteTwoChildrenDirectRightSuccessor); 
	RUN_TEST_CASE(Basic, DeleteTwoChildrenNonDirectRightSuccessor); 
	RUN_TEST_CASE(Basic, DeletionDuplicateKey);
}
