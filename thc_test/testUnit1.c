
#include "unity.h"

void test_TheFirst(void)
{
    TEST_ASSERT_EQUAL_INT32( -1, 0xFFFFFFFF );
}
void test_TheSecond(void)
{
    TEST_ASSERT_EQUAL(2,2);
}
void test_TheThird(void)
{
    TEST_ASSERT_EQUAL_FLOAT(1.2,1.2);
}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_TheFirst);
    RUN_TEST(test_TheSecond);
    RUN_TEST(test_TheThird);
    return UNITY_END();
}
