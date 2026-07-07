/*
 * Copyright (c) 2022-2026, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-24     CDT          first version
 */

/**
 * menuconfig:
 * Hardware Drivers Config ---> On-Chip Peripheral Driver---> [*] Enable PM
 * RT-Thread Kernel ---> (1024) The stack size of idle thread
 */

#include <stdlib.h>
#include "board.h"
#include "drv_wktm.h"

#if defined(BSP_USING_PM)

#define WKTM_IRQn                   (INT131_IRQn)

static volatile rt_uint32_t last_tick;

void PWC_WakeupTimer_IrqHandler(void)
{
    static rt_uint32_t delta_tick;

    rt_interrupt_enter();

    delta_tick = rt_tick_get() - last_tick;
    last_tick = rt_tick_get();

    /* 打印出的tick值由于printf原因可能有误差 */
    rt_kprintf("Wakeup-timer irq interval ticks: approximate %d.\r\n", delta_tick);

    rt_interrupt_leave();
}

void wktm_sample(int argc, char **argv)
{
    rt_base_t level;
    rt_uint32_t cmp_value;
    rt_uint32_t cmp_max = hc32_wktm_get_tick_max();

    if (argc >= 2)
    {
        cmp_value = atol(argv[1]);
        if (0UL == cmp_value)
        {
            /*********************** Stop wakeup-timer ************************/
            hc32_wktm_stop();

            NVIC_DisableIRQ(WKTM_IRQn);
            NVIC_ClearPendingIRQ(WKTM_IRQn);

            rt_kprintf("Stop Wakeup-timer\n\n");
        }
        else if (cmp_value > cmp_max)
        {
            /*********************** Hold the wakeup timer configuration ******/
            rt_kprintf("compare value %d is out of %d(max), so hold the wakeup timer configuration \n\n", cmp_value, cmp_max);
        }
        else if (cmp_value < (cmp_max/2))
        {
            /*********************** Hold the wakeup timer configuration ******/
            rt_kprintf("compare value %d is less of %d(max/2), so hold the wakeup timer configuration: ", cmp_value, cmp_max/2);
            rt_kprintf("to avoid frequent interruptions: too much printed information affcets console commands \n\n");
        }
        else
        {
            /*********************** Start wakeup-timer ***********************/
            /* Wakeup timer NVIC config */
            (void)INTC_ShareIrqCmd(INT_SRC_WKTM_PRD, ENABLE);
            NVIC_ClearPendingIRQ(WKTM_IRQn);
            NVIC_SetPriority(WKTM_IRQn, DDL_IRQ_PRIO_DEFAULT);
            NVIC_EnableIRQ(WKTM_IRQn);

            if (RT_EOK == hc32_wktm_start(cmp_value))
            {
                level = rt_hw_interrupt_disable();
                last_tick = rt_tick_get();
                rt_hw_interrupt_enable(level);
                rt_kprintf("Update wakeup-timer compare value = %d, and start timer \n\n", cmp_value);
            }
            else
            {
                rt_kprintf("Fail to set wakeup-timer compare value \n\n", cmp_value);
            }
        }
    }
    else
    {
        rt_kprintf("wktm_sample 0: stop wakeup-timer \n");
        rt_kprintf("wktm_sample %d~%d: set wakeup-timer compare value and start timer \n\n", cmp_max/2, cmp_max);
    }
}
MSH_CMD_EXPORT(wktm_sample, wktm_sample compare-value);
#endif
