#include "rtthread.h"
#include "unity.h"
#include "ci_tests.h"

#define TEST_MEMORY_SIZE 10240

static char test_memory[TEST_MEMORY_SIZE];

#define TEST_SMALL_MEM_SIZE 17
#define TEST_TO_LARGE_MEM_SIZE 10000000000
#define TEST_NOT_A_MEM_SIZE -17
#define TEST_ZERO_MEM_SIZE 0

#define __TEST_MALLOC_NULL(size) \
    void *pdata = RT_NULL; \
    pdata = rt_malloc(size); \
    TEST_ASSERT_NULL(pdata); \
    rt_free(pdata)

#define __TEST_MALLOC_NOT_NULL(size) \
    void *pdata = RT_NULL; \
    pdata = rt_malloc(size); \
    TEST_ASSERT_NOT_NULL(pdata); \
    rt_free(pdata)

void test_memory_setup(void)
{
   rt_system_heap_init(test_memory, &test_memory[TEST_MEMORY_SIZE-1]);
}

void test_memory_malloc_right(void)
{
   __TEST_MALLOC_NOT_NULL(TEST_SMALL_MEM_SIZE);
}

void test_memory_malloc_too_big(void)
{
   __TEST_MALLOC_NULL(TEST_TO_LARGE_MEM_SIZE);
}

void test_memory_malloc_zero(void)
{
   __TEST_MALLOC_NULL(TEST_ZERO_MEM_SIZE);
}

void test_memory_malloc_not_a_size(void)
{
   __TEST_MALLOC_NULL(TEST_NOT_A_MEM_SIZE);
}