#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>
#include "lessons.c"
#define MAX_ARGUMENTS 30

void Lesson__create_test(){
	Lesson *l = Lesson__create("Podstawy programowania",Term__create(12,50,90,3));
	
	CU_ASSERT_EQUAL(l->subject, "Podstawy programowania");
	CU_ASSERT_EQUAL(l->term->hour, 12);
	CU_ASSERT_EQUAL(l->term->minute, 50);
	CU_ASSERT_EQUAL(l->term->duration, 90);
	CU_ASSERT_EQUAL(l->term->day, 3);

	Lesson__destroy(l);

	Lesson *l1 = Lesson__create("Algebra",Term__create(8,10,90,5));

	CU_ASSERT_EQUAL(l1->subject, "Algebra");
	CU_ASSERT_EQUAL(l1->term->hour, 8);
	CU_ASSERT_EQUAL(l1->term->minute, 10);
	CU_ASSERT_EQUAL(l1->term->duration, 90);
	CU_ASSERT_EQUAL(l1->term->day, 5);

	Lesson__destroy(l1);
}

void Lesson__toString_test(){
        Lesson *l2 = Lesson__create("Podstawy programowania",Term__create(12,50,90,3));
        CU_ASSERT_STRING_EQUAL("Podstawy programowania, Środa 12:50 [90]", Lesson__toString(l2));
	
	Lesson__destroy(l2);
	
	Lesson *l3 = Lesson__create("Algebra",Term__create(8,10,90,5));
	CU_ASSERT_STRING_EQUAL("Algebra, Piątek 8:10 [90]", Lesson__toString(l3));
	
	Lesson__destroy(l3);
}

void Lesson__earlierDay_test(){
	Lesson *l4 = Lesson__create("Podstawy programowania",Term__create(12,50,90,3));
	Lesson__earlierDay(l4);
	CU_ASSERT_EQUAL(l4->term->day, 2);

	Lesson__destroy(l4);

        Lesson *l5 = Lesson__create("Algebra",Term__create(12,50,90,1));
        Lesson__earlierDay(l5);
        CU_ASSERT_EQUAL(l5->term->day, 1);

        Lesson__destroy(l5);
}

void Lesson__laterDay_test(){
        Lesson *l6 = Lesson__create("Podstawy programowania",Term__create(12,50,90,3));
        
	Lesson__laterDay(l6);
        CU_ASSERT_EQUAL(l6->term->day, 4);
	Lesson__destroy(l6);

	Lesson *l7 = Lesson__create("Algebra",Term__create(12,50,90,5));
	Lesson__laterDay(l7);
        CU_ASSERT_EQUAL(l7->term->day, 5);

        Lesson__destroy(l7);

	Lesson *l8 = Lesson__create("Algebra",Term__create(16,50,90,4));
        Lesson__laterDay(l8);
        CU_ASSERT_EQUAL(l8->term->day, 4);

        Lesson__destroy(l8);

}

void Lesson__earlierTime_test(){
	Lesson *l9 = Lesson__create("Podstawy programowania",Term__create(12,50,90,3));

        Lesson__earlierTime(l9);
	CU_ASSERT_EQUAL(l9->term->hour, 11);
        CU_ASSERT_EQUAL(l9->term->minute, 20);
        CU_ASSERT_EQUAL(l9->term->duration, 90);
        CU_ASSERT_EQUAL(l9->term->day, 3);
        Lesson__destroy(l9);

	Lesson *l10 = Lesson__create("Algebra",Term__create(8,0,90,3));

        Lesson__earlierTime(l10);
        CU_ASSERT_EQUAL(l10->term->hour, 8);
        CU_ASSERT_EQUAL(l10->term->minute, 0);
        CU_ASSERT_EQUAL(l10->term->duration, 90);
        CU_ASSERT_EQUAL(l10->term->day, 3);
        Lesson__destroy(l10);
}

void Lesson__laterTime_test(){
	Lesson *l11 = Lesson__create("Podstawy programowania",Term__create(12,50,90,3));

        Lesson__laterTime(l11);
        CU_ASSERT_EQUAL(l11->term->hour, 14);
        CU_ASSERT_EQUAL(l11->term->minute, 20);
        CU_ASSERT_EQUAL(l11->term->duration, 90);
        CU_ASSERT_EQUAL(l11->term->day, 3);
        Lesson__destroy(l11);

	Lesson *l12 = Lesson__create("Algebra",Term__create(14,20,90,5));

        Lesson__laterTime(l12);
        CU_ASSERT_EQUAL(l12->term->hour, 14);
        CU_ASSERT_EQUAL(l12->term->minute, 20);
        CU_ASSERT_EQUAL(l12->term->duration, 90);
        CU_ASSERT_EQUAL(l12->term->day, 5);
        Lesson__destroy(l12);
}

void Lesson__go_test(){
	char** test = malloc(MAX_ARGUMENTS * sizeof(char*));
        char* result;
        for (int i = 0; i < MAX_ARGUMENTS; i++)
                test[i] = malloc( 3 * sizeof(char));

	Lesson *l13 = Lesson__create("Podstawy programowania",Term__create(12,50,90,3));

        strcpy(test[0], "d+");
        strcpy(test[1], "t-");
        strcpy(test[2], "d+");
        strcpy(test[3], "d-");
        result = lesson(l13,test,4);
        CU_ASSERT_STRING_EQUAL(result, "Podstawy programowania, Czwartek 11:20 [90]");
	Lesson__destroy(l13);
	
	Lesson *l14 = Lesson__create("Podstawy programowania",Term__create(12,50,90,3));

        strcpy(test[0], "d-");
        strcpy(test[1], "t+");
        strcpy(test[2], "t-");
        strcpy(test[3], "t+");
        strcpy(test[4], "d+");
        strcpy(test[5], "d+");
        result = lesson(l14,test,6);
        CU_ASSERT_STRING_EQUAL(result, "Podstawy programowania, Czwartek 14:20 [90]");
        free(test);
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

	if (NULL == CU_add_test(pSuite, "Lesson__create_test", Lesson__create_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "Lesson__earlierDay_test", Lesson__earlierDay_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "Lesson__laterDay_test", Lesson__laterDay_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if (NULL == CU_add_test(pSuite, "Lesson__toString_test", Lesson__toString_test))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite, "Lesson__earlierTime_test", Lesson__earlierTime_test))
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

	if (NULL == CU_add_test(pSuite, "Lesson__laterTime_test", Lesson__laterTime_test))
        {
                CU_cleanup_registry();
                return CU_get_error();
        }
	
	if (NULL == CU_add_test(pSuite, "Lesson__go_test", Lesson__go_test))
        {
                CU_cleanup_registry();
                return CU_get_error();
        }

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}
