/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-15     Emuzit            first version
 */
#include <rthw.h>
#include <rtdebug.h>
#include "ch56x_pfic.h"
#include "ch56x_sys.h"
#include "isr_sp.h"

void rt_hw_interrupt_mask(int vector)
{
    pfic_interrupt_mask(vector);
}

void rt_hw_interrupt_umask(int vector)
{
    pfic_interrupt_umask(vector);
}

/**
 * @brief   Trigger software interrupt.
 */
void pfic_swi_pendset(void)
{
    volatile struct pfic_registers *pfic = (void *)PFIC_REG_BASE;
    _pfic_ireg_bit_set(pfic, IPSR, SWI_IRQn);
}

/**
 * @brief   Clear software interrupt.
 */
void pfic_swi_pendreset(void)
{
    volatile struct pfic_registers *pfic = (void *)PFIC_REG_BASE;
    _pfic_ireg_bit_set(pfic, IPRR, SWI_IRQn);
}

/**
 * @brief   Write PFIC interrupt configuration register.
 *
 * @param   key_bit is (PFIC_CFGR_KEYx + bit_position), one of the following :
 *          PFIC_CFGR_NMISET / PFIC_CFGR_NMIRESET
 *          PFIC_CFGR_EXCSET / PFIC_CFGR_EXCRESET
 *          PFIC_CFGR_PFICRESET
 *          PFIC_CFGR_SYSRESET
 *          All others are treated as NEST/HWSTK (B.1/B.0) write.
 */
void pfic_cfgr_set(uint32_t key_bit)
{
    volatile struct pfic_registers *pfic = (void *)PFIC_REG_BASE;
    uint32_t u32v;

    switch (key_bit)
    {
    case PFIC_CFGR_NMISET:
    case PFIC_CFGR_NMIRESET:
    case PFIC_CFGR_EXCSET:
    case PFIC_CFGR_EXCRESET:
    case PFIC_CFGR_PFICRESET:
    case PFIC_CFGR_SYSRESET:
        pfic->CFGR = key_bit;
    default:
        /* B.1/B.0 hold NEST/HWSTK, key ignored */
        u32v = key_bit & (CFGR_NESTCTRL_MASK | CFGR_HWSTKCTRL_MASK);
        pfic->CFGR = cfgr_nest_hwstk(u32v);
    }
}

/**
 * @brief   Make SysTick ready, systick/swi irq are enabled.
 *
 * @param   count is (HCLK/8) clocks count to generate systick irq.
 *          if 0 => calculate with current HCLK and RT_TICK_PER_SECOND
 */
void systick_init(uint32_t count)
{
    volatile struct systick_registers *systick = (void *)SysTick_REG_BASE;
    volatile struct pfic_registers *pfic = (void *)PFIC_REG_BASE;

    if (count == 0)
        count = sys_hclk_get() / 8 / RT_TICK_PER_SECOND;

    _pfic_irqn_disable(pfic, SysTick_IRQn);
    pfic->IPRIOR[SysTick_IRQn] = 0xe0;
    pfic->IPRIOR[SWI_IRQn] = 0xf0;
    systick->CTLR.reg = 0;
    systick->CNTL  = 0;
    systick->CNTH  = 0;
    systick->CMPLR = count - 1;
    systick->CMPHR = 0;
    systick->CNTFG.cntif = 0;
    /* enable & reload SysTick, with HCLK/8 */
    systick->CTLR.reg = RB_STKCTL_STRELOAD | RB_STKCTL_STIE | RB_STKCTL_STE;
    _pfic_irqn_enable(pfic, SysTick_IRQn);
    _pfic_irqn_enable(pfic, SWI_IRQn);
}

void systick_handler(void) __attribute__((interrupt()));
void systick_handler(void)
{
    volatile struct systick_registers *systick;

    isr_sp_enter();
    rt_interrupt_enter();

    rt_tick_increase();
    systick = (struct systick_registers *)SysTick_REG_BASE;
    /* clear count-to-zero flag */
    systick->CNTFG.cntif = 0;

    rt_interrupt_leave();
    isr_sp_leave();
}
