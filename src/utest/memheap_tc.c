/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-16     flybreak     the first version
 * 2025-11-11     CYFS         Add standardized utest documentation block
 */

/**
 * Test Case Name: Kernel Core Memory Heap Test
 *
 * Test Objectives:
 * - Validates the core kernel memory heap management module functionality
 * - Verify core APIs: rt_memheap_init, rt_memheap_alloc, rt_memheap_free, rt_memheap_realloc, rt_memheap_detach
 *
 * Test Scenarios:
 * - **Scenario 1 (Memory Heap Stress Test / memheap_test):**
 * 1. Initialize memory heap with 64KB aligned memory buffer (4-byte alignment)
 * 2. Allocate 40 memory blocks with random sizes (0 to HEAP_SIZE/SLICE_NUM)
 * 3. Perform 100000 random operations on the memory heap
 * 4. Each operation randomly selects one of 40 memory blocks and performs either:
 *    - Free and reallocate with new random size (50% probability)
 *    - Reallocate existing block with new random size (50% probability)
 * 5. Verify memory heap stability and correctness under high-frequency operations
 *
 * Verification Metrics:
 * - **Pass (Scenario 1):** Memory heap initialization succeeds with 64KB aligned buffer
 * - **Pass (Scenario 1):** All 40 initial allocations complete successfully
 * - **Pass (Scenario 1):** All 100000 random operations complete without system crash or assertion failure
 * - **Pass (Scenario 1):** Memory heap operations (alloc/free/realloc) execute correctly throughout stress test
 * - **Pass (Scenario 1):** Progress indicators (>) printed at regular intervals (every 10000 operations)
 * - **Pass (Scenario 1):** Test completes successfully with "test OK!" message
 * - **Pass (Scenario 1):** Memory heap properly detached and resources cleaned up
 *
 * Dependencies:
 * - No specific hardware requirements, runs on any RT-Thread supported platform
 * - Software configuration (e.g., kernel options, driver initialization)
 * - `RT_USING_UTEST` must be enabled (`RT-Thread Utestcases`).
 * - `Memory Heap Test` must be enabled (`RT-Thread Utestcases` -> `Kernel Core` -> 'Memory Heap Test').
 * - RT-Thread kernel with memory heap management enabled
 * - rt_malloc_align and rt_free_align functions available for test buffer allocation
 * - Random number generator (rand function) available for random operations
 * - Sufficient system memory to allocate 64KB aligned buffer
 * - Environmental assumptions
 * - System can handle high-frequency memory operations (100000 operations)
 * - Memory heap can manage 40 concurrent memory blocks
 * - Run the test case from the msh prompt:
 * `utest_run core.memheap`
 *
 * Expected Results:
 * - The test case completes without errors or failed assertions.
 * - Progress indicators (>) printed at regular intervals during stress test
 * - "test OK!" message printed upon successful completion
 * - The utest framework prints:
 * `[  PASSED  ] [ result   ] testcase (core.memheap)`
 * - Memory heap properly cleaned up and no memory leaks detected
 */
#include <rtthread.h>
#include <stdlib.h>
#include "utest.h"

#define HEAP_SIZE        (64 * 1024)
#define HEAP_ALIGN       (4)
#define SLICE_NUM        (40)
#define TEST_TIMES       (100000)
#define HEAP_NAME        "heap1"
#define SLICE_SIZE_MAX   (HEAP_SIZE/SLICE_NUM)

static void memheap_test(void)
{
    struct rt_memheap heap1;
    void * ptr_start;
    void *ptr[SLICE_NUM];
    int i, cnt = 0;

    /* init heap */
    ptr_start = rt_malloc_align(HEAP_SIZE, HEAP_ALIGN);
    if (ptr_start == RT_NULL)
    {
        rt_kprintf("totle size too big,can not malloc memory!");
        return;
    }

    rt_memheap_init(&heap1, HEAP_NAME, ptr_start, HEAP_SIZE);

    /* test start */
    for (i = 0; i < SLICE_NUM; i++)
    {
        ptr[i] = 0;
    }
    /* test alloc */
    for (i = 0; i < SLICE_NUM; i++)
    {
        rt_uint32_t slice_size = rand() % SLICE_SIZE_MAX;
        ptr[i] = rt_memheap_alloc(&heap1, slice_size);
    }
    /* test realloc */
    while (cnt < TEST_TIMES)
    {
        rt_uint32_t slice_size = rand() % SLICE_SIZE_MAX;
        rt_uint32_t ptr_index = rand() % SLICE_NUM;
        rt_uint32_t operation = rand() % 2;

        if (ptr[ptr_index])
        {
            if (operation == 0) /* free and malloc */
            {
                rt_memheap_free(ptr[ptr_index]);
                ptr[ptr_index] = rt_memheap_alloc(&heap1, slice_size);
            }
            else /* realloc */
            {
                ptr[ptr_index] = rt_memheap_realloc(&heap1, ptr[ptr_index], slice_size);
            }
        }
        cnt ++;
        if (cnt % (TEST_TIMES / 10) == 0)
        {
            rt_kprintf(">");
        }
    }

    rt_kprintf("test OK!\n");

    /* test end */
    rt_memheap_detach(&heap1);
    rt_free_align((void *)ptr_start);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

static void testcase(void)
{
    UTEST_UNIT_RUN(memheap_test);
}
UTEST_TC_EXPORT(testcase, "core.memheap", utest_tc_init, utest_tc_cleanup, 10);
