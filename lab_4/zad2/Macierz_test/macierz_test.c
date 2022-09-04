#include "CUnit/Basic.h"
#include "macierz.c"
#include <stdlib.h>
#include <stdio.h>

void macierz_test(){
	char* result = malloc(200 * sizeof(char));
	macierz("MacierzA1.txt", "MacierzB1.txt", "MacierzC1.txt");
	result = file2char("MacierzC1.txt");
	CU_ASSERT_STRING_EQUAL(result, "102 70 \n54 18 \0");
	free(result);

	macierz("MacierzA2.txt", "MacierzB2.txt", "MacierzC2.txt");
	result = file2char("MacierzC2.txt");
	CU_ASSERT_STRING_EQUAL(result, "48 36 117 \n44 30 97 \n71 41 129 \0");
	free(result);

	macierz("MacierzA3.txt", "MacierzB3.txt", "MacierzC3.txt");
	result = file2char("MacierzC3.txt");
	CU_ASSERT_STRING_EQUAL(result, "30 82 14 \n15 41 7 \n2 14 2 \n16 32 6 \0");
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

	if (NULL == CU_add_test(pSuite, "macierz_test", macierz_test)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}
