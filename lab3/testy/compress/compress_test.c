#include "CUnit/Basic.h"
#include "compress.c"
#define MAX_LINE_LEN 200

void compress_test(){
	char** test = malloc(3 * sizeof(char*));
	char* result;
	for (int i = 0; i < 3; i++)
		test[i] = malloc( MAX_LINE_LEN * sizeof(char) );
	strcpy(test[0], "aaaa bbbbbbbbb\0");
	strcpy(test[1], "     (((((((((((( %)\0");
	result = compress(test, 2);
	CU_ASSERT_STRING_EQUAL(result, "aaaa b(9)\n (5)%28(12) %25(1)%29(1)\0");
	free(result);
	
	strcpy(test[0], "aaaaaaabbbbbbbbcd(((\0");
	result = compress(test, 1);
	CU_ASSERT_STRING_EQUAL(result, "a(7)b(8)cd%28(3)\0");
	free(result);
	
	strcpy(test[0], "a(10) \0");
	strcpy(test[1], "abcde\0");
	strcpy(test[2], "ffffffffffffffffffff\0");
	result = compress(test, 3);
	CU_ASSERT_STRING_EQUAL(result, "a%28(1)10%29(1) \nabcde\nf(20)\0");
	free(result);
	free(test);
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

	if (NULL == CU_add_test(pSuite, "compress_test", compress_test)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}
