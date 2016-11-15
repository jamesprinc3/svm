#include "modsvm_2.h"
#include "unity.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_Sector_Calc_General(void)
{

    TEST_ASSERT_EQUAL(1, sector_calc(1,0));
    TEST_ASSERT_EQUAL(2, sector_calc(1,5));
    TEST_ASSERT_EQUAL(3, sector_calc(-1,5));
    TEST_ASSERT_EQUAL(4, sector_calc(-1,0));
    TEST_ASSERT_EQUAL(5, sector_calc(-1,-5));
    TEST_ASSERT_EQUAL(6, sector_calc(1,-5));

}

//be careful, use ints!
void test_Sector_Calc_Borders(void)
{

	TEST_ASSERT_EQUAL(1, sector_calc(100, 50));
	TEST_ASSERT_EQUAL(2, sector_calc(100, 60));

	TEST_ASSERT_EQUAL(2, sector_calc(10,  100));
	TEST_ASSERT_EQUAL(3, sector_calc(-10, 100));

	TEST_ASSERT_EQUAL(3, sector_calc(-100, 60));
	TEST_ASSERT_EQUAL(4, sector_calc(-100, 50));

	TEST_ASSERT_EQUAL(4, sector_calc(-100, -50));
	TEST_ASSERT_EQUAL(5, sector_calc(-100, -60));

	TEST_ASSERT_EQUAL(5, sector_calc(-10, -100));
	TEST_ASSERT_EQUAL(6, sector_calc( 10, -100));

	TEST_ASSERT_EQUAL(6, sector_calc(100, -60));
	TEST_ASSERT_EQUAL(1, sector_calc(100, -50));

}

void test_Pick_Vec(void)
{

	TEST_ASSERT_EQUAL(0, pickVec(10, 10,  9,  9));
	TEST_ASSERT_EQUAL(1, pickVec(10, 10, 11,  9));
	TEST_ASSERT_EQUAL(2, pickVec(10, 10,  9, 11));
	TEST_ASSERT_EQUAL(3, pickVec(10, 10, 11, 11));
	TEST_ASSERT_EQUAL(0, pickVec(0,   0,  0,  0));

}


void test_Set_Vec(void)
{
	TEST_IGNORE_MESSAGE("This is difficult to test since it is a macro");
}