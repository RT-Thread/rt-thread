/*
 * Copyright (c) 2023, lepustse@gmail.com
 *
 * License-Identifier: MIT
 *
 * Change Logs:
 * Date         Author		Notes
 * 2023-05-03   lepustse	the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

/**
 * @addtogroup ARM CPU
 */
/*@{*/

/** shutdown CPU */
rt_weak void rt_hw_cpu_shutdown()
{
    rt_base_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}

#ifdef RT_USING_CPU_FFS
/**
 * This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
int __rt_ffs(int value)
{
    return __builtin_ffs(value);
}
#endif

/*@}*/
