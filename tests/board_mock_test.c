#include "unity.h"
#include "board_mock.h"
#include "ci_tests.h"

void rt_hw_console_output(const char *str);

void test_stdoutSpy()
{
    stdouSpy_Clear();
    rt_hw_console_output("hello world\n");
    TEST_ASSERT_EQUAL(1, stdouSpy_Length());

    rt_hw_console_output("need help\n");
    TEST_ASSERT_EQUAL(2, stdouSpy_Length());

    TEST_ASSERT_EQUAL_STRING("hello world\n", stdouSpy_getOutput());
    stdouSpy_Pop();

    TEST_ASSERT_EQUAL_STRING("need help\n", stdouSpy_getOutput());
    TEST_ASSERT_EQUAL(1, stdouSpy_Length());

    stdouSpy_Clear();
    TEST_ASSERT_EQUAL(0, stdouSpy_Length());
}