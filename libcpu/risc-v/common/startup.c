/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

/*
 * Generic startup preserves the firmware-provided FDT before entering the
 * kernel. The generic DM setup provides the strong implementation; a BSP with
 * custom setup may override this hook when it still uses the common startup.
 */
rt_weak void rt_hw_fdt_install_early(void *fdt)
{
    RT_UNUSED(fdt);
}

/*
 * This runs after gp and a temporary stack are ready, before normal C
 * runtime state is available.
 */
rt_weak void riscv_early_setup(void)
{
}

rt_weak void riscv_bss_init(void)
{
    extern rt_uint8_t __bss_start[];
    extern rt_uint8_t __bss_end[];
    volatile rt_uint8_t *ptr = __bss_start;
    rt_ubase_t *word, *word_end, word_start;

    word_start = RT_ALIGN((rt_ubase_t)__bss_start, sizeof(rt_ubase_t));

    while (ptr < __bss_end && (rt_ubase_t)ptr < word_start)
    {
        *ptr++ = 0;
    }

    word = (rt_ubase_t *)ptr;
    word_end = (rt_ubase_t *)RT_ALIGN_DOWN((rt_ubase_t)__bss_end, sizeof(rt_ubase_t));

    while (word < word_end)
    {
        *word++ = 0;
    }

    ptr = (rt_uint8_t *)word;
    while (ptr < __bss_end)
    {
        *ptr++ = 0;
    }
}
