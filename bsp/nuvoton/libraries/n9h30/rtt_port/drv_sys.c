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
#define SYS_MAX_INT_SOURCE       62
#define SYS_NUM_OF_AICREG        16
#define INT_IRQ     0x00
#define INT_FIQ     0x01

extern rt_atomic_t rt_interrupt_nest;

rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

struct rt_irq_desc irq_desc[SYS_MAX_INT_SOURCE + 1];

void rt_hw_interrupt_dummy_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occurred!!!\n", vector);
    RT_ASSERT(0);
}

void rt_hw_interrupt_set_priority(int vector, int IntTypeLevel)
{
    sysSetInterruptPriorityLevel((IRQn_Type)vector, (UINT32)IntTypeLevel);
}

void rt_interrupt_dispatch(rt_uint32_t fiq_irq)
{
    rt_isr_handler_t isr_func;
    rt_uint32_t volatile _mIPER, _mISNR;
    void *param;

    /* Get irq number */
    _mIPER = (inpw(REG_AIC_IPER) >> 2) & 0x3f;
    _mISNR = inpw(REG_AIC_ISNR) & 0x3f;

    if (_mISNR != 0)
    {
        if (_mIPER == _mISNR)
        {
            /* Get interrupt service routine */
            isr_func = irq_desc[_mISNR].handler;
            param = irq_desc[_mISNR].param;

#ifdef RT_USING_INTERRUPT_INFO
            irq_desc[_mISNR].counter ++;
#endif

            /* Turn to interrupt service routine */
            isr_func(_mISNR, param);
        }
    }

    /* Handled the ISR. */
    outpw(REG_AIC_EOSCR, 1);
}

void rt_hw_interrupt_init(void)
{
    int i;

    outpw(REG_AIC_ISR, 0xFFFFFFFF);  // disable all interrupt channel
    outpw(REG_AIC_ISRH, 0xFFFFFFFF); // disable all interrupt channel
    outpw(REG_AIC_EOSCR, 1);

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest               = 0;
    rt_interrupt_from_thread        = 0;
    rt_interrupt_to_thread          = 0;
    rt_thread_switch_interrupt_flag = 0;

    for (i = SYS_MIN_INT_SOURCE; i <= SYS_MAX_INT_SOURCE; i++)
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
    sysSetInterruptType((IRQn_Type)vector, (UINT32) type);
}

void rt_low_level_init(void)
{
    /* Unlock write-protect */
    SYS_UnlockReg();

    /* Close WDT first, to avoid WDT timer is enabled IBR timeout reset. */
    WDT_Close();

    /* Lock write-protect */
    SYS_LockReg();
}

void nu_clock_base_init(void)
{
    nu_sys_ipclk_enable(CPUCKEN);
    nu_sys_ipclk_enable(HCLKCKEN);
    nu_sys_ipclk_enable(HCLK1CKEN);
    nu_sys_ipclk_enable(HCLK3CKEN);
    nu_sys_ipclk_enable(HCLK4CKEN);
    nu_sys_ipclk_enable(PCLKCKEN);
    nu_sys_ipclk_enable(SRAMCKEN);
    nu_sys_ipclk_enable(DDRCKEN);
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

    while (1);
}


void nu_sys_ip_reset(E_SYS_IPRST eIPRstIdx)
{
    uint32_t volatile u32IPRSTRegAddr;
    uint32_t u32IPRSTRegBit;
    rt_uint32_t level;

    if (eIPRstIdx >= SYS_IPRST_CNT)
        return;

    u32IPRSTRegAddr = REG_SYS_AHBIPRST + (4ul * (eIPRstIdx / 32));
    u32IPRSTRegBit  = eIPRstIdx % 32;

    /* Enter critical section */
    level = rt_hw_interrupt_disable();

    /* Unlock write-protect */
    SYS_UnlockReg();

    /* Enable IP reset */
    outpw(u32IPRSTRegAddr, inpw(u32IPRSTRegAddr) | (1 << u32IPRSTRegBit));

    /* Disable IP reset */
    outpw(u32IPRSTRegAddr, inpw(u32IPRSTRegAddr) & ~(1 << u32IPRSTRegBit));

    /* Wait it done. */
    while (inpw(u32IPRSTRegAddr) & (1 << u32IPRSTRegBit)) {}

    /* Lock write protect */
    SYS_LockReg();

    /* Leave critical section */
    rt_hw_interrupt_enable(level);
}

static void _nu_sys_ipclk(E_SYS_IPCLK eIPClkIdx, uint32_t bEnable)
{
    uint32_t volatile u32IPCLKRegAddr;
    uint32_t u32IPCLKRegBit;
    rt_uint32_t level;

    if (eIPClkIdx >= SYS_IPCLK_CNT)
        return;

    u32IPCLKRegAddr = REG_CLK_HCLKEN + (4ul * (eIPClkIdx / 32));
    u32IPCLKRegBit  = eIPClkIdx % 32;

    /* Enter critical section */
    level = rt_hw_interrupt_disable();

    SYS_UnlockReg();

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

    SYS_LockReg();

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

E_SYS_USB0_ID nu_sys_usb0_role(void)
{
    /* Check Role on USB0 dual-role port. */
    /*
        [17] USB0_IDS
           USB0_ID Status
           0 = USB port 0 used as a USB device port.
           1 = USB port 0 used as a USB host port.
      */
    return ((inpw(REG_SYS_MISCISR) & (1 << 17)) > 0) ? USB0_ID_HOST : USB0_ID_DEVICE;
}

#ifdef RT_USING_FINSH

#include <finsh.h>

#ifdef FINSH_USING_MSH
int cmd_reset(int argc, char **argv)
{
    rt_hw_cpu_reset();
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_reset, reset, restart the system);

int cmd_shutdown(int argc, char **argv)
{
    rt_hw_cpu_shutdown();
    return 0;
}
MSH_CMD_EXPORT_ALIAS(cmd_shutdown, shutdown, shutdown the system);

int nu_clocks(int argc, char **argv)
{
    rt_kprintf("SYS_UPLL = %d MHz\n", sysGetClock(SYS_UPLL));
    rt_kprintf("SYS_APLL = %d MHz\n", sysGetClock(SYS_APLL));
    rt_kprintf("SYS_SYSTEM = %d MHz\n", sysGetClock(SYS_SYSTEM));
    rt_kprintf("SYS_HCLK1 = %d MHz\n", sysGetClock(SYS_HCLK1));
    rt_kprintf("SYS_HCLK234 = %d MHz\n", sysGetClock(SYS_HCLK234));
    rt_kprintf("SYS_PCLK = %d MHz\n", sysGetClock(SYS_PCLK));
    rt_kprintf("SYS_CPU = %d MHz\n", sysGetClock(SYS_CPU));

    rt_kprintf("CLK_HCLKEN = %08X\n", inpw(REG_CLK_HCLKEN));
    rt_kprintf("CLK_PCLKEN0 = %08X\n", inpw(REG_CLK_PCLKEN0));
    rt_kprintf("CLK_PCLKEN1 = %08X\n", inpw(REG_CLK_PCLKEN1));

    return 0;
}
MSH_CMD_EXPORT(nu_clocks, Get all system clocks);

#ifdef RT_USING_INTERRUPT_INFO
int list_interrupt(int argc, char **argv)
{
    int i;

    for (i = SYS_MIN_INT_SOURCE; i <= SYS_MAX_INT_SOURCE; i++)
    {
        if (irq_desc[i].handler != rt_hw_interrupt_dummy_handler)
        {
            rt_kprintf("[%d] %s: %d\n", i, irq_desc[i].name, irq_desc[i].counter);
        }
    }

    return 0;
}
MSH_CMD_EXPORT(list_interrupt, list registered interrupts);
#endif

#endif

#endif
