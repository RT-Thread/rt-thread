/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-16     flybreak     the first version
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
    rt_ubase_t ptr_start;
    void *ptr[SLICE_NUM];
    int i, cnt = 0;

    /* init heap */
    ptr_start = (rt_ubase_t)rt_malloc_align(HEAP_SIZE, HEAP_ALIGN);
    if (ptr_start == RT_NULL)
    {
        rt_kprintf("totle size too big,can not malloc memory!");
        return;
    }

    rt_memheap_init(&heap1, HEAP_NAME, (void *)ptr_start, HEAP_SIZE);

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
                if (ptr[ptr_index])
                {
                    rt_memheap_free(ptr[ptr_index]);
                }
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
UTEST_TC_EXPORT(testcase, "testcases.kernel.memheap_tc", utest_tc_init, utest_tc_cleanup, 10);
