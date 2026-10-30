/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <board.h>

#ifdef BSP_USING_SDRAM_HEAP_TEST
static int sdram_heap_test(void)
{
    const rt_size_t size = 2U * 1024U * 1024U;
    const rt_size_t words = size / sizeof(rt_uint32_t);
    volatile rt_uint32_t *buffer;
    rt_size_t i;
    int result = RT_EOK;

    buffer = (volatile rt_uint32_t *)rt_malloc(size);
    if (buffer == RT_NULL)
    {
        rt_kprintf("allocate failed\n");
        return -RT_ENOMEM;
    }

    rt_kprintf("buffer: %p\n", buffer);
    if ((rt_ubase_t)buffer < EXT_SDRAM_BEGIN ||
        (rt_ubase_t)buffer + size > EXT_SDRAM_END)
    {
        rt_kprintf("not allocated from SDRAM\n");
        rt_free((void *)buffer);
        return -RT_ERROR;
    }

    for (i = 0; i < words; i++)
        buffer[i] = 0x55AA0000U ^ (rt_uint32_t)i;

    for (i = 0; i < words; i++)
    {
        if (buffer[i] != (0x55AA0000U ^ (rt_uint32_t)i))
        {
            rt_kprintf("failed at %p\n", &buffer[i]);
            result = -RT_ERROR;
            break;
        }
    }

    rt_free((void *)buffer);
    rt_kprintf(result == RT_EOK ? "SDRAM heap test passed\n" :
                                 "SDRAM heap test failed\n");
    return result;
}
MSH_CMD_EXPORT(sdram_heap_test, test SDRAM heap);
#endif
