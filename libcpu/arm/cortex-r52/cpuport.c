/*
 * Copyright (c) 2011-2024, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-29     RT-Thread    first version
 */

#include <rthw.h>
#include <rtthread.h>

int rt_hw_cpu_id(void)
{
    int cpu_id;
    __asm volatile (
            "mrc p15, 0, %0, c0, c0, 5"
            :"=r"(cpu_id)
    );
    cpu_id &= 0xf;
    return cpu_id;
}

/**
 * @addtogroup ARM CPU
 */
/*@{*/

/** shutdown CPU */
void rt_hw_cpu_shutdown()
{
    rt_uint32_t level;

    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}

/*@}*/
