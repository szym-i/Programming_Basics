#include "CUnit/Basic.h"
#include "getHexAscii.c"

void getHexAscii_test(){
	char* result=getHexAscii('(');
	CU_ASSERT_STRING_EQUAL(result, "28");

	strcpy(result, getHexAscii('a'));
	CU_ASSERT_STRING_EQUAL(result, "61");

	strcpy(result, getHexAscii('q'));
	CU_ASSERT_STRING_EQUAL(result, "71");

	strcpy(result,getHexAscii('#'));
	CU_ASSERT_STRING_EQUAL(result, "23");

	strcpy(result,getHexAscii('T'));
        CU_ASSERT_STRING_EQUAL(result, "54");

        strcpy(result,getHexAscii('\0'));
        CU_ASSERT_STRING_EQUAL(result, "0");

	strcpy(result,getHexAscii('6'));
	CU_ASSERT_STRING_EQUAL(result, "36");
}

int main(){
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("test_suite", 0, 0);

	if (NULL == pSuite){
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "getHexAscii_test", getHexAscii_test)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}
