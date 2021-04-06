#include "unity.h"
#include "ci_tests.h"
#include "rtthread.h"
#include "board_mock.h"

void setUp(void) {
    // set stuff up here
    stdouSpy_Clear();
}

void tearDown(void) {
    // clean stuff up here
    stdouSpy_Clear();
}

void test_test(void)
{
    rt_kprintf("hello world");
    TEST_ASSERT_EQUAL_STRING("hello world", stdouSpy_getOutput());
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();

    // run tests
    RUN_TEST(test_test);

    // board mock
    RUN_TEST(test_stdoutSpy);

    // memory
    test_memory_setup();
    RUN_TEST(test_memory_malloc_right);
    RUN_TEST(test_memory_malloc_too_big);
    RUN_TEST(test_memory_malloc_zero);
    RUN_TEST(test_memory_malloc_not_a_size);

    return UNITY_END();
}

