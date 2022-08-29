#include "CUnit/Basic.h"
#include "decompress.c"

void decompress_test(){
	char** test = malloc(3 * sizeof(char*));
	char* result;
	for (int i = 0; i < 3; i++)
		test[i] = malloc(200 * sizeof(char));
	
	strcpy(test[0], "aaaa b(9)\0");// test z treści
	strcpy(test[1], " (5)%28(12) %25(1)%29(1)\0");
	result = decompress(test, 2);
	CU_ASSERT_STRING_EQUAL(result, "aaaa bbbbbbbbb\n     (((((((((((( %)\0");
	free(result);
	
	strcpy(test[0], "a(18)b(9)\0");
	result = decompress(test, 1);
	CU_ASSERT_STRING_EQUAL(result, "aaaaaaaaaaaaaaaaaabbbbbbbbb\0");
	free(result);
	
	strcpy(test[0], "abc(20) %25(4) 1(5)\0");
	strcpy(test[1], "abcd\0");
	strcpy(test[2], "f(20)\0");
	result = decompress(test, 3);
	CU_ASSERT_STRING_EQUAL(result, "abcccccccccccccccccccc %%%% 11111\nabcd\nffffffffffffffffffff\0");
	free(result);
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

	if (NULL == CU_add_test(pSuite, "decompress_test", decompress_test)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}
