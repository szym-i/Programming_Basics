#include "CUnit/Basic.h"
#include "action.c"
#include <stdlib.h>
#include <stdio.h>
#define MAX_ARGUMENTS 10

void parse_test(){
        char** test = malloc(MAX_ARGUMENTS * sizeof(char*));
        char* result;
        for (int i = 0; i < MAX_ARGUMENTS; i++)
                test[i] = malloc( 2 * sizeof(char) );
        strcpy(test[0], "Mon");
	strcpy(test[1], "t-");
        strcpy(test[2], "d+");
	strcpy(test[3], "d+");
	strcpy(test[4], "d+");
        result = action(5,test);
        CU_ASSERT_STRING_EQUAL(result, "Czwartek");

        strcpy(test[0], "Mon");
	strcpy(test[1], "d-");
	strcpy(test[2], "d-");
        result = action(3,test);
        CU_ASSERT_STRING_EQUAL(result, "Sobota");

        strcpy(test[0], "Wed");
	strcpy(test[1], "d-");
	strcpy(test[2], "d+");
	strcpy(test[3], "d-");
	strcpy(test[4], "t+");
	strcpy(test[5], "t-");
	strcpy(test[6], "t+");
	strcpy(test[7], "d+");
	strcpy(test[8], "d+");
        result = action(9,test);
        CU_ASSERT_STRING_EQUAL(result, "Czwartek");
	free(test);
}

void Day__toString_test(){
        Day day1 = 1;
        CU_ASSERT_STRING_EQUAL("Poniedziałek", Day__toString(day1));

	Day day2 = 5;
	CU_ASSERT_STRING_EQUAL("Piątek", Day__toString(day2));
}

void Day__nextDay_test(){
	Day day3 = 6;

	day3 =  Day__nextDay(day3);
	CU_ASSERT_EQUAL(7,day3);

	day3 =  Day__nextDay(day3);
        CU_ASSERT_EQUAL(1,day3);
}

void Day__prevDay_test(){
        Day day4 = 2;

        day4 =  Day__prevDay(day4);
        CU_ASSERT_EQUAL(1,day4);

        day4 =  Day__prevDay(day4);
        CU_ASSERT_EQUAL(7,day4);
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

        if (NULL == CU_add_test(pSuite, "parse_test", parse_test)){
                CU_cleanup_registry();
                return CU_get_error();
        }

	if (NULL == CU_add_test(pSuite, "Day__toString_test", Day__toString_test)){
                CU_cleanup_registry();
                return CU_get_error();
        }

        if (NULL == CU_add_test(pSuite, "Day__nextDay_test", Day__nextDay_test)){
                CU_cleanup_registry();
                return CU_get_error();
        }

	if (NULL == CU_add_test(pSuite, "Day__prevDay_test", Day__prevDay_test)){
                CU_cleanup_registry();
                return CU_get_error();
        }



        CU_basic_set_mode(CU_BRM_VERBOSE);

        CU_basic_run_tests();
        return CU_get_error();
}




