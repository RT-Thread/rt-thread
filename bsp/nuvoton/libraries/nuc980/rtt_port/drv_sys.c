/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-11-11      Wayne            First version
*
******************************************************************************/

#include <rthw.h>
#include <rtthread.h>
#include "NuMicro.h"
#include "drv_sys.h"

#define SYS_MIN_INT_SOURCE       1
#define SYS_MAX_INT_SOURCE       63
#define SYS_NUM_OF_AICREG        16
#define INT_IRQ     0x00
#define INT_FIQ     0x01

extern rt_uint32_t rt_interrupt_nest;

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

struct rt_irq_desc irq_desc[SYS_MAX_INT_SOURCE + 1];

void rt_hw_interrupt_dummy_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occurred!!!\n", vector);

    RT_ASSERT(0);
}

rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq)
{
    rt_uint32_t   active = 0;
#if 0
    rt_uint32_t volatile _mIPER, _mISNR;

    _mIPER = (inpw(REG_AIC_IPER) >> 2) & 0x3f;
    _mISNR = inpw(REG_AIC_ISNR);
    if ((_mISNR != 0) && (_mIPER == _mISNR))
        active = _mISNR;

#else
    if (fiq_irq != INT_FIQ)
    {
        active = inpw(REG_AIC_IRQNUM);
    }
    else
        active = inpw(REG_AIC_FIQNUM);
#endif
    return active;
}


void rt_hw_interrupt_set_priority(int vector, int IntTypeLevel)
{
    rt_uint32_t   _mRegAddr;
    rt_uint32_t   shift;

    if ((vector > SYS_MAX_INT_SOURCE) || (vector < SYS_MIN_INT_SOURCE))
        return;

    _mRegAddr = REG_AIC_SRCCTL0 + ((vector / 4) * 4);
    shift = (vector % 4) * 8;
    IntTypeLevel &= 0x7;
    outpw(_mRegAddr, (inpw(_mRegAddr) & ~(0x07 << shift)) | (IntTypeLevel << shift));
}

void rt_hw_interrupt_ack(rt_uint32_t fiq_irq, rt_uint32_t id)
{
    if (fiq_irq != INT_FIQ)
        outpw(REG_AIC_EOIS, 1);
    else
        outpw(REG_AIC_EOFS, 1);
}

void rt_interrupt_dispatch(rt_uint32_t fiq_irq)
{
    rt_isr_handler_t isr_func;
    rt_uint32_t irq;
    void *param;

    /* get irq number */
    irq = rt_hw_interrupt_get_active(fiq_irq);

    /* get interrupt service routine */
    isr_func = irq_desc[irq].handler;
    param = irq_desc[irq].param;

    /* turn to interrupt service routine */
    isr_func(irq, param);

    rt_hw_interrupt_ack(fiq_irq, irq);
#ifdef RT_USING_INTERRUPT_INFO
    irq_desc[irq].counter ++;
#endif
}

void rt_hw_interrupt_init(void)
{
    int i;

    *((volatile unsigned int *)REG_AIC_INTDIS0) = 0xFFFFFFFF;   // disable all interrupt channel
    *((volatile unsigned int *)REG_AIC_INTDIS1) = 0xFFFFFFFF;   // disable all interrupt channel

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest               = 0;
    rt_interrupt_from_thread        = 0;
    rt_interrupt_to_thread          = 0;
    rt_thread_switch_interrupt_flag = 0;

    for (i = 1; i <= SYS_MAX_INT_SOURCE; i++)
    {
        rt_hw_interrupt_install(i, rt_hw_interrupt_dummy_handler, RT_NULL, (char *)"dummy");
        rt_hw_interrupt_mask(i);
    }
}

rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, void *param, const char *name)
{
    rt_isr_handler_t    old_handler = RT_NULL;

    if (vector > SYS_MAX_INT_SOURCE)
        return RT_NULL;

    /* Set default priority IRQ_LEVEL_7 */
    rt_hw_interrupt_set_priority(vector, IRQ_LEVEL_7);

    old_handler = irq_desc[vector].handler;
    if (handler != RT_NULL)
    {
        irq_desc[vector].handler = (rt_isr_handler_t)handler;
        irq_desc[vector].param = param;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s", name);
        irq_desc[vector].counter = 0;
#endif
    }

    return old_handler;
}

/* Disable interrupt */
void rt_hw_interrupt_mask(int vector)
{
    sysDisableInterrupt((IRQn_Type)vector);
}

void rt_hw_interrupt_umask(int vector)
{
    sysEnableInterrupt((IRQn_Type)vector);
}

/* TYPE
 *  #define LOW_LEVEL_SENSITIVE        0x00
 *  #define HIGH_LEVEL_SENSITIVE       0x40
 *  #define NEGATIVE_EDGE_TRIGGER      0x80
 *  #define POSITIVE_EDGE_TRIGGER      0xC0
 */
void rt_hw_interrupt_set_type(int vector, int type)
{
    rt_uint32_t     _mRegAddr;
    rt_uint32_t     shift;

    if ((vector > SYS_MAX_INT_SOURCE) || (vector < SYS_MIN_INT_SOURCE))
        return ;

    _mRegAddr = REG_AIC_SRCCTL0 + ((vector / 4) * 4);
    shift = (vector % 4) * 8;
    type &= 0xC0;
    outpw(_mRegAddr, (inpw(_mRegAddr) & ~(0xC0 << shift)) | (type << shift));
}

void rt_low_level_init(void)
{
}

void nu_clock_base_init(void)
{
    nu_sys_ipclk_enable(CPUCKEN);
    nu_sys_ipclk_enable(HCLKCKEN);
    nu_sys_ipclk_enable(HCLK1CKEN);
    nu_sys_ipclk_enable(HCLK3CKEN);
    nu_sys_ipclk_enable(HCLK4CKEN);
    nu_sys_ipclk_enable(PCLK0CKEN);
    nu_sys_ipclk_enable(PCLK1CKEN);
    nu_sys_ipclk_enable(SRAMCKEN);
    nu_sys_ipclk_enable(SDICCKEN);
    nu_sys_ipclk_enable(PCLK2CKEN);
    nu_sys_ipclk_enable(PCLKEN0_Reserved_3);
}

void machine_reset(void)
{
    rt_kprintf("machine_reset...\n");
    rt_hw_interrupt_disable();

    /* Unlock */
    SYS_UnlockReg();

    nu_sys_ip_reset(CHIPRST);

    while (1);
}

void machine_shutdown(void)
{
    rt_kprintf("machine_shutdown...\n");
    rt_hw_interrupt_disable();

    /* Unlock */
    SYS_UnlockReg();

    // TODO

    while (1);
}


void nu_sys_ip_reset(E_SYS_IPRST eIPRstIdx)
{
    uint32_t u32IPRSTRegAddr;
    uint32_t u32IPRSTRegBit;
    rt_uint32_t level;

    if (eIPRstIdx >= SYS_IPRST_CNT)
        return;

    u32IPRSTRegAddr = REG_SYS_AHBIPRST + (4ul * (eIPRstIdx / 32));
    u32IPRSTRegBit  = eIPRstIdx % 32;

    /* Enter critical section */
    level = rt_hw_interrupt_disable();

    /* Enable IP reset */
    outpw(u32IPRSTRegAddr, inpw(u32IPRSTRegAddr) | (1 << u32IPRSTRegBit));

    /* Disable IP reset */
    outpw(u32IPRSTRegAddr, inpw(u32IPRSTRegAddr) & ~(1 << u32IPRSTRegBit));

    /* Leave critical section */
    rt_hw_interrupt_enable(level);
}

static void _nu_sys_ipclk(E_SYS_IPCLK eIPClkIdx, uint32_t bEnable)
{
    uint32_t u32IPCLKRegAddr;
    uint32_t u32IPCLKRegBit;
    rt_uint32_t level;

    if (eIPClkIdx >= SYS_IPCLK_CNT)
        return;

    u32IPCLKRegAddr = REG_CLK_HCLKEN + (4ul * (eIPClkIdx / 32));
    u32IPCLKRegBit  = eIPClkIdx % 32;

    /* Enter critical section */
    level = rt_hw_interrupt_disable();

    if (bEnable)
    {
        /* Enable IP CLK */
        outpw(u32IPCLKRegAddr, inpw(u32IPCLKRegAddr) | (1 << u32IPCLKRegBit));
    }
    else
    {
        /* Disable IP CLK */
        outpw(u32IPCLKRegAddr, inpw(u32IPCLKRegAddr) & ~(1 << u32IPCLKRegBit));
    }

    /* Leave critical section */
    rt_hw_interrupt_enable(level);
}


void nu_sys_ipclk_enable(E_SYS_IPCLK eIPClkIdx)
{
    _nu_sys_ipclk(eIPClkIdx, 1);
}

void nu_sys_ipclk_disable(E_SYS_IPCLK eIPClkIdx)
{
    _nu_sys_ipclk(eIPClkIdx, 0);
}

#ifdef RT_USING_FINSH

#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(rt_hw_cpu_reset, reset, restart the system);

#ifdef FINSH_USING_MSH
int cmd_reset(int argc, char **argv)
{
    rt_hw_cpu_reset();
    return 0;
}

int cmd_shutdown(int argc, char **argv)
{
    rt_hw_cpu_shutdown();
    return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(cmd_reset, __cmd_reset, restart the system.);
FINSH_FUNCTION_EXPORT_ALIAS(cmd_shutdown, __cmd_shutdown, shutdown the system.);

#endif

#endif
