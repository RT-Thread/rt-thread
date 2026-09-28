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
#include "rtconfig.h"
#if defined (SOC_RISCV_SERIES_CH32V1)
#include "ch32v10x.h"
#elif defined (SOC_RISCV_SERIES_CH32V2)
#include "ch32v20x.h"
#elif defined (SOC_RISCV_SERIES_CH32V3)
#include "ch32v30x.h"
#else
#error "CH32 architecture doesn't support!"
#endif
void rt_trigger_software_interrupt(void)
{
    /*CH32V103 does not support systick software interrupt*/
#if defined(SOC_RISCV_SERIES_CH32V1)
    NVIC_SetPendingIRQ(Software_IRQn);
#else
    SysTick->CTLR |= (1 << 31);
#endif
}

void rt_hw_do_after_save_above(void)
{
    __asm volatile ("li t0,0x20" );
    __asm volatile ("csrs 0x804, t0");
    /*CH32V103 does not support systick software interrupt*/
#if defined(SOC_RISCV_SERIES_CH32V1)
    NVIC_ClearPendingIRQ(Software_IRQn);
#else
    SysTick->CTLR &= ~(1 << 31);
#endif
}