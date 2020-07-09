/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

#include <registers/regsarmglobaltimer.h>
#include <registers/regsepit.h>

#include <imx_uart.h>
#include <epit.h>
#include <cortex_a.h>

#include <mmu.h>

struct mem_desc platform_mem_desc[] = {
    {0x00000000, 0x80000000, 0x00000000, DEVICE_MEM},
    {0x80000000, 0xFFF00000, 0x80000000, NORMAL_MEM}
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();
    epit_get_compare_event(HW_EPIT1);
}

int rt_hw_timer_init(void)
{
    uint32_t freq;

    // Make sure the timer is off.
    HW_ARMGLOBALTIMER_CONTROL.B.TIMER_ENABLE = 0;

    HW_ARMGLOBALTIMER_CONTROL.B.FCR0 =1;

    HW_ARMGLOBALTIMER_CONTROL.B.FCR1 =0;

    HW_ARMGLOBALTIMER_CONTROL.B.DBG_ENABLE =0;

    // Clear counter.
    HW_ARMGLOBALTIMER_COUNTER_HI_WR(0);
    HW_ARMGLOBALTIMER_COUNTER_LO_WR(0);

    // Now turn on the timer.
    HW_ARMGLOBALTIMER_CONTROL.B.TIMER_ENABLE = 1;

    freq = get_main_clock(IPG_CLK);

    epit_init(HW_EPIT1, CLKSRC_IPG_CLK, freq / 1000000,
              SET_AND_FORGET, 10000, WAIT_MODE_EN | STOP_MODE_EN);

    epit_counter_enable(HW_EPIT1, 10000, IRQ_MODE);

    rt_hw_interrupt_install(IMX_INT_EPIT1, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IMX_INT_EPIT1);

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

/**
 * This function will initialize hardware board
 */
void rt_hw_board_init(void)
{
    enable_neon_fpu();
    disable_strict_align_check();

    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
}

/*@}*/
