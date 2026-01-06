#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auto_test.h"
#include "rtconfig.h"

#define MAX_TESTS 100

typedef int (*TestFunc)(void);

typedef struct {
    const char* name;
    TestFunc func;
    rt_err_t passed;
} TestCase;

TestCase test_cases[MAX_TESTS];
int test_count = 0;

// 注册测试用例
void register_test(const char* name, TestFunc func) {
    if (test_count < MAX_TESTS) {
        test_cases[test_count].name = name;
        test_cases[test_count].func = func;
        test_cases[test_count].passed = 0;
        test_count++;
    } else {
        rt_kprintf("Exceeded the maximum number of test cases(%d)\n", MAX_TESTS);
    }
}

// 运行所有测试
void run_all_tests() {
    int passed_count = 0;

    rt_kprintf("Run tests...\n");
    for (int i = 0; i < test_count; i++) {
        rt_err_t result = test_cases[i].func();
        test_cases[i].passed = result;
        if (result == RT_EOK) {
            rt_kprintf("[PASS] %s\n", test_cases[i].name);
            passed_count++;
        } else {
            rt_kprintf("[FAIL] %s %d\n", test_cases[i].name, result);
        }
    }
#if defined(TARGET_ARMV8_AARCH64)
    rt_kprintf("\n%s aarch64 test results: \n", BOARD_NAME);
#else
    rt_kprintf("\n%s aarch32 test results: \n", BOARD_NAME);
#endif
    rt_kprintf("PASS: %d / %d\n", passed_count, test_count);
    if (passed_count < test_count)
    {
        rt_kprintf("[test_failure] example:\n");
        for (int i = 0; i < test_count; i++) {
            if (test_cases[i].passed != RT_EOK) {
                rt_kprintf("  - %s\n", test_cases[i].name);
            }
        }
    }
    else
    {
        rt_kprintf("[test_success]\n");
    }
    rt_kprintf("[rtthread_test_end]\n");
}

int auto_test() {

#if defined BSP_USING_CAN
    register_test("can_loopback_sample", can_loopback_sample);
#endif
#if defined BSP_USING_SPI
    register_test("spi_sample", fspim_test_sample);
#endif
#if defined BSP_USING_GPIO
    register_test("gpio_sample", gpio_toggle_sample);
#endif
#if defined BSP_USING_I2C
#if defined (PD2408_TEST_A_BOARD) || defined (PD2408_TEST_B_BOARD)
    register_test("i2c_msg_sample", i2c_msg_sample);
#else
    register_test("i2c_sample", i2c_sample);
#endif
#endif
#if defined BSP_USING_QSPI
#if !defined(TARGET_PD2408)
    register_test("qspi_sample", qspi_sample);
#endif
#endif

    // 运行测试
    run_all_tests();

    return 0;
}
