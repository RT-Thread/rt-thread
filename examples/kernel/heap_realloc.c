#include <rtthread.h>
#include "tc_comm.h"

/*
 * This is an example for heap malloc
 */

static rt_bool_t mem_check(rt_uint8_t *ptr, rt_uint8_t value, rt_uint32_t len)
{
    while (len)
    {
        if (*ptr != value) return RT_FALSE;

        ptr ++;
        len --;
    }

    return RT_TRUE;
}

static void heap_realloc_init()
{
    rt_uint8_t res = TC_STAT_PASSED;
    rt_uint8_t *ptr1, *ptr2, *ptr3, *ptr4, *ptr5;

    ptr1 = rt_malloc(1);
    ptr2 = rt_malloc(13);
    ptr3 = rt_malloc(31);
    ptr4 = rt_malloc(127);
    ptr5 = rt_malloc(0);

    memset(ptr1, 1, 1);
    memset(ptr2, 2, 13);
    memset(ptr3, 3, 31);
    memset(ptr4, 4, 127);

    if (mem_check(ptr1, 1, 1)   == RT_FALSE)
    {
        res = TC_STAT_FAILED;
        goto _free;
    }
    if (mem_check(ptr2, 2, 13)  == RT_FALSE)
    {
        res = TC_STAT_FAILED;
        goto _free;
    }
    if (mem_check(ptr3, 3, 31)  == RT_FALSE)
    {
        res = TC_STAT_FAILED;
        goto _free;
    }
    if (mem_check(ptr4, 4, 127) == RT_FALSE)
    {
        res = TC_STAT_FAILED;
        goto _free;
    }

    ptr1 = rt_realloc(ptr1, 13);
    ptr2 = rt_realloc(ptr2, 31);
    ptr3 = rt_realloc(ptr3, 127);
    ptr4 = rt_realloc(ptr4, 1);
    ptr5 = rt_realloc(ptr5, 0);
    if (ptr5)
    {
        rt_kprintf("realloc(ptr, 0) should return NULL\n");
        res = TC_STAT_FAILED;
    }

    if (mem_check(ptr1, 1, 1)   == RT_FALSE)
        res = TC_STAT_FAILED;
    if (mem_check(ptr2, 2, 13)  == RT_FALSE)
        res = TC_STAT_FAILED;
    if (mem_check(ptr3, 3, 31)  == RT_FALSE)
        res = TC_STAT_FAILED;
    if (mem_check(ptr4, 4, 1)    == RT_FALSE)
        res = TC_STAT_FAILED;

_free:
    rt_free(ptr4);
    rt_free(ptr3);
    rt_free(ptr2);
    rt_free(ptr1);

    tc_done(res);
}

#ifdef RT_USING_TC
int _tc_heap_realloc()
{
    heap_realloc_init();

    return 0;
}
FINSH_FUNCTION_EXPORT(_tc_heap_realloc, a heap re-malloc test);
#else
int rt_application_init()
{
    heap_realloc_init();

    return 0;
}
#endif
