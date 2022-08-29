#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>
#include "Term.c"

void Term__create_test() {
	Term* t = Term__create(1, 2, 3);
	CU_ASSERT_EQUAL(t->hour, 1);
	CU_ASSERT_EQUAL(t->minute, 2);
	CU_ASSERT_EQUAL(t->duration, 3);
	
	Term__init(t, 4, 5, 6);
	CU_ASSERT_EQUAL(t->hour, 4);
	CU_ASSERT_EQUAL(t->minute, 5);
	CU_ASSERT_EQUAL(t->duration, 6);
	
	Term__destroy(t);
}

void Term__toString_test() {
        Term* t1 = Term__create(12, 30, 100);
        CU_ASSERT_STRING_EQUAL("12:30 [100]", Term__toString(t1));

	Term__init(t1, 9, 0, 90);
        CU_ASSERT_STRING_EQUAL("9:00 [90]", Term__toString(t1));
        
	Term__destroy(t1);
}


void bool_functions_test() {
	Term* t1 = Term__create(9, 0, 60);
	Term* t2 = Term__create(12, 30, 90);
	
	CU_ASSERT_EQUAL(Term__equals(t1, t1), 1);
	CU_ASSERT_EQUAL(Term__equals(t2, t2), 1);
	CU_ASSERT_EQUAL(Term__equals(t1, t2), 0);
	
	CU_ASSERT_EQUAL(Term__earlierThan(t1, t2), 1);
	CU_ASSERT_EQUAL(Term__earlierThan(t2, t1), 0);
	CU_ASSERT_EQUAL(Term__earlierThan(t1, t1), 0);
	CU_ASSERT_EQUAL(Term__earlierThan(t2, t2), 0);
	
	CU_ASSERT_EQUAL(Term__laterThan(t1, t2), 0);
	CU_ASSERT_EQUAL(Term__laterThan(t2, t1), 1);
	CU_ASSERT_EQUAL(Term__laterThan(t1, t1), 0);
	CU_ASSERT_EQUAL(Term__laterThan(t2, t2), 0);
	
	Term__destroy(t1);
	Term__destroy(t2);
}

void Term__endTerm_test() {
	Term* t1 = Term__create(9, 45, 90);
	Term* t2 = Term__create(10, 15, 90);
	Term* t3 = Term__endTerm(t1, t2);
	
	CU_ASSERT_EQUAL(t3->hour, 9);
	CU_ASSERT_EQUAL(t3->minute, 45);
	CU_ASSERT_EQUAL(t3->duration, 30);
	
	Term__destroy(t1);
	Term__destroy(t2);
	Term__destroy(t3);
}

int main() {
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("test_suite", 0, 0);

	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "Term__create_test", Term__create_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "bool_funciotns_test", bool_functions_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "Term__endTerm_test", Term__endTerm_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "Term__toString_test", Term__toString_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}
