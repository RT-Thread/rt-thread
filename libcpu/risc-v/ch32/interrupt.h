/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-09     WCH        the first version
 * 2023-01-04     WangShun   Remove redundant files
 */
#if defined (SOC_RISCV_SERIES_CH32V1)
#include "ch32v10x.h"
#elif defined (SOC_RISCV_SERIES_CH32V2)
#include "ch32v20x.h"
#elif defined (SOC_RISCV_SERIES_CH32V3)
#include "ch32v30x.h"
#else
#error "CH32 architecture doesn't support!"
#endif

/*
 * trigger soft interrupt
 */
void sw_setpend(void)
{
    /*CH32V103 does not support systick software interrupt*/
#if defined(SOC_RISCV_SERIES_CH32V1)
    NVIC_SetPendingIRQ(Software_IRQn);
#else
    SysTick->CTLR |= (1 << 31);
#endif
}

/*
 * clear soft interrupt
 */
void sw_clearpend(void)
{
    /*CH32V103 does not support systick software interrupt*/
#if defined(SOC_RISCV_SERIES_CH32V1)
    NVIC_ClearPendingIRQ(Software_IRQn);
#else
    SysTick->CTLR &= ~(1 << 31);
#endif
}

/*
 * disable interrupt and save mstatus
 */
rt_weak rt_base_t rt_hw_interrupt_disable(void)
{
    rt_base_t value=0;
#if defined(SOC_RISCV_SERIES_CH32V3)
    asm("csrrw %0, mstatus, %1":"=r"(value):"r"(0x7800));
#else
    asm("csrrw %0, mstatus, %1":"=r"(value):"r"(0x1800));
#endif
    return value;
}

/*
 * enable interrupt and resume mstatus
 */
rt_weak void rt_hw_interrupt_enable(rt_base_t level)
{
    asm("csrw mstatus, %0": :"r"(level));
}


