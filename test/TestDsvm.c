#include "dsvm.h"
#include "unity.h"

/* These should be ignored because they are commented out in various ways:
#include "whatever.h" 
#include "somethingelse.h"
*/

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Torque_Level(void)
{

    TEST_ASSERT_EQUAL(2,  torque_level(100,  70));
    TEST_ASSERT_EQUAL(1,  torque_level(100,  89));
    TEST_ASSERT_EQUAL(0,  torque_level(100,  95));
    TEST_ASSERT_EQUAL(0,  torque_level(100, 105));
    TEST_ASSERT_EQUAL(-1, torque_level(100, 111));
    TEST_ASSERT_EQUAL(-2, torque_level(100, 130));

}

void test_Sector_Calc_Low_Speed(void) {

	TEST_ASSERT_EQUAL(1, sector_calc(100, 50, low_speed));
	TEST_ASSERT_EQUAL(2, sector_calc(100, 60, low_speed));

	TEST_ASSERT_EQUAL(2, sector_calc(10,  100, low_speed));
	TEST_ASSERT_EQUAL(3, sector_calc(-10, 100, low_speed));

	TEST_ASSERT_EQUAL(3, sector_calc(-100, 60, low_speed));
	TEST_ASSERT_EQUAL(4, sector_calc(-100, 50, low_speed));

	TEST_ASSERT_EQUAL(4, sector_calc(-100, -50, low_speed));
	TEST_ASSERT_EQUAL(5, sector_calc(-100, -60, low_speed));

	TEST_ASSERT_EQUAL(5, sector_calc(-10, -100, low_speed));
	TEST_ASSERT_EQUAL(6, sector_calc( 10, -100, low_speed));

	TEST_ASSERT_EQUAL(6, sector_calc(100, -60, low_speed));
	TEST_ASSERT_EQUAL(1, sector_calc(100, -50, low_speed));
}

void test_Sector_Calc_Med_Speed(void) 
{
	TEST_ASSERT_EQUAL(1, sector_calc(100, 50, med_speed));
	TEST_ASSERT_EQUAL(2, sector_calc(100, 60, med_speed));

	TEST_ASSERT_EQUAL(2, sector_calc(10,  100, med_speed));
	TEST_ASSERT_EQUAL(3, sector_calc(-10, 100, med_speed));

	TEST_ASSERT_EQUAL(3, sector_calc(-100, 60, med_speed));
	TEST_ASSERT_EQUAL(4, sector_calc(-100, 50, med_speed));

	TEST_ASSERT_EQUAL(4, sector_calc(-100, -50, med_speed));
	TEST_ASSERT_EQUAL(5, sector_calc(-100, -60, med_speed));

	TEST_ASSERT_EQUAL(5, sector_calc(-10, -100, med_speed));
	TEST_ASSERT_EQUAL(6, sector_calc( 10, -100, med_speed));

	TEST_ASSERT_EQUAL(6, sector_calc(100, -60, med_speed));
	TEST_ASSERT_EQUAL(1, sector_calc(100, -50, med_speed));
}

void test_Sector_Calc_High_Speed(void) 
{
	TEST_ASSERT_EQUAL(7, sector_calc(100, 50, high_speed));
	TEST_ASSERT_EQUAL(2, sector_calc(100, 60, high_speed));

	TEST_ASSERT_EQUAL(8, sector_calc(10,  100, high_speed));
	TEST_ASSERT_EQUAL(3, sector_calc(-10, 100, high_speed));

	TEST_ASSERT_EQUAL(9, sector_calc(-100, 60, high_speed));
	TEST_ASSERT_EQUAL(4, sector_calc(-100, 50, high_speed));

	TEST_ASSERT_EQUAL(10, sector_calc(-100, -50, high_speed));
	TEST_ASSERT_EQUAL(5, sector_calc(-100, -60, high_speed));

	TEST_ASSERT_EQUAL(11, sector_calc(-10, -100, high_speed));
	TEST_ASSERT_EQUAL(6, sector_calc( 10, -100, high_speed));

	TEST_ASSERT_EQUAL(12, sector_calc(100, -60, high_speed));
	TEST_ASSERT_EQUAL(1, sector_calc(100, -50, high_speed));
}

void test_Speed_Region(void)
{
	TEST_ASSERT_EQUAL(0, speed_region(200 ));
	TEST_ASSERT_EQUAL(1, speed_region(1000));
	TEST_ASSERT_EQUAL(2, speed_region(1800));
}

// void test_Set_Vec(void)
// {
// 	TEST_IGNORE_MESSAGE("This is difficult to test since it is a macro");
// }