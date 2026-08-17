/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-01     RTT          the first version, generic i.MX RT DWT driver
 */

#include "drv_dwt.h"

#ifdef BSP_USING_DWT

#include <rtthread.h>

/* CMSIS standard variable updated by SystemCoreClockUpdate() in the SDK's
 * system_<device>.c. Declared extern here to stay device-family-agnostic. */
extern uint32_t SystemCoreClock;

/* CoreDebug and DWT register base addresses (Cortex-M, ARMv7-M / ARMv8-M) */
#define DWT_CTRL    (*(volatile rt_uint32_t *)0xE0001000UL)  /* DWT Control */
#define DWT_CYCCNT  (*(volatile rt_uint32_t *)0xE0001004UL)  /* Cycle Count */
#define CoreDebug_DEMCR (*(volatile rt_uint32_t *)0xE000EDFCUL) /* DEMCR */

/* DEMCR: enable DWT and ITM trace */
#define CoreDebug_DEMCR_TRCENA_Msk  (1UL << 24)
/* DWT_CTRL: enable cycle counter */
#define DWT_CTRL_CYCCNTENA_Msk      (1UL << 0)
/* DWT_CTRL: NOCYCCNT - set if the cycle counter is not implemented */
#define DWT_CTRL_NOCYCCNT_Msk       (1UL << 25)

/**
 * Initialize the DWT cycle counter.
 */
rt_err_t dwt_init(void)
{
    /* Enable DWT trace by setting TRCENA in DEMCR */
    CoreDebug_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    /* Check that the cycle counter is implemented on this device */
    if (DWT_CTRL & DWT_CTRL_NOCYCCNT_Msk)
    {
        return -RT_ERROR;
    }

    /* Reset then enable the cycle counter */
    DWT_CYCCNT = 0U;
    DWT_CTRL  |= DWT_CTRL_CYCCNTENA_Msk;

    return RT_EOK;
}

/**
 * Read the current DWT cycle counter value.
 */
rt_uint32_t dwt_get_cycles(void)
{
    return DWT_CYCCNT;
}

/**
 * Convert a cycle count to microseconds using SystemCoreClock.
 */
rt_uint32_t dwt_cycles_to_us(rt_uint32_t cycles)
{
    return (rt_uint32_t)((rt_uint64_t)cycles * 1000000UL / SystemCoreClock);
}

/**
 * Busy-wait for the requested number of microseconds.
 */
void dwt_delay_us(rt_uint32_t us)
{
    rt_uint32_t start = DWT_CYCCNT;
    rt_uint32_t ticks = (rt_uint32_t)((rt_uint64_t)us * SystemCoreClock / 1000000UL);

    /* Unsigned subtraction handles counter wrap-around correctly */
    while ((DWT_CYCCNT - start) < ticks)
    {
        /* busy wait */
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>

/**
 * MSH command: dwt_test
 * Tests the DWT cycle counter by measuring rt_thread_mdelay(100) and
 * a 200 us busy-wait delay, then prints the results over the console.
 */
static void dwt_test(int argc, char **argv)
{
    rt_uint32_t t0, t1, elapsed_us;

    if (dwt_init() != RT_EOK)
    {
        rt_kprintf("[DWT] init FAILED: cycle counter not implemented on this device\r\n");
        return;
    }
    rt_kprintf("[DWT] init OK, cycle counter started\r\n");

    /* test 1: measure a 100 ms OS delay */
    t0 = dwt_get_cycles();
    rt_thread_mdelay(100);
    t1 = dwt_get_cycles();
    elapsed_us = dwt_cycles_to_us(t1 - t0);
    rt_kprintf("[DWT] rt_thread_mdelay(100) took %u us\r\n", elapsed_us);

    /* test 2: busy-wait 200 us and measure it back */
    t0 = dwt_get_cycles();
    dwt_delay_us(200);
    t1 = dwt_get_cycles();
    elapsed_us = dwt_cycles_to_us(t1 - t0);
    rt_kprintf("[DWT] dwt_delay_us(200) measured %u us\r\n", elapsed_us);
}
MSH_CMD_EXPORT(dwt_test, test DWT cycle counter and us delay);

#endif /* RT_USING_FINSH */

#endif /* BSP_USING_DWT */
