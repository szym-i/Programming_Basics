#include <CUnit.h>
#include "getEncryptedLine.c"

void getEncryptedLine_test(){
	char buffer[53];

	strcpy(buffer, "to be or not to be"); // strcpy(char *dest, const char *src) jest po to, aby nie definiować czterech stringów osobno
	getEncryptedLine(buffer);
	CU_ASSERT_STRING_EQUAL(buffer, "vq dg qt pqv vq dg");

	strcpy(buffer, "ala ma kota");// testy z treści
	getEncryptedLine(buffer);
	CU_ASSERT_STRING_EQUAL(buffer, "dod pd nrwd");

	strcpy(buffer, "abcdefghijklmnopqrstuvwxyz");
	getEncryptedLine(buffer);
	CU_ASSERT_STRING_EQUAL(buffer, "abcdefghijklmnopqrstuvwxyz");

	strcpy(buffer, " a b c d e f g h i j k l m n o p q r s t u v w x y z");
	getEncryptedLine(buffer);
	CU_ASSERT_STRING_EQUAL(buffer, " b c d e f g h i j k l m n o p q r s t u v w x y z a");

	strcpy(buffer, "ALA MA KOTA"); //test dla dużych liter
        getEncryptedLine(buffer);
        CU_ASSERT_STRING_EQUAL(buffer, "DOD PD NRWD");
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

	if (NULL == CU_add_test(pSuite, "getEncryptedLine_test", getEncryptedLine_test)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}
