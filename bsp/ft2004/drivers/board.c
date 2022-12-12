/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-03-04     Carl    the first version
 *
 */

#include <rtthread.h>
#include "ft_printf.h"
#include "ft_assert.h"
#include "ft_cpu.h"
#include "ft_psci.h"
#include "ft_parameters.h"
#include "board.h"
#include "gtimer.h"
#include "ft_generic_timer.h"
#include <gicv3.h>

#include "interrupt.h"
#include <mmu.h>
#include "cp15.h"
#include "ft2004.h"

#define DDR_MEM (SHARED | AP_RW | DOMAIN0 | MEMWT | DESC_SEC)

struct mem_desc platform_mem_desc[] = {
    {0x80000000,
     0x80000000 + 0x7f000000,
     0x80000000,
     DDR_MEM},
    {0, //< QSPI
     0x1FFFFFFF,
     0,
     DEVICE_MEM},
    {0x20000000, //<! LPC
     0x27FFFFFF,
     0x20000000,
     DEVICE_MEM},
    {FT_DEV_BASE_ADDR, //<! Device register
     FT_DEV_END_ADDR,
     FT_DEV_BASE_ADDR,
     DEVICE_MEM},
    {0x30000000, //<! debug
     0x39FFFFFF,
     0x30000000,
     DEVICE_MEM},
    {0x3A000000, //<! Internal register space in the on-chip network
     0x3AFFFFFF,
     0x3A000000,
     DEVICE_MEM},
    {FT_PCI_CONFIG_BASEADDR,
     FT_PCI_CONFIG_BASEADDR + FT_PCI_CONFIG_REG_LENGTH,
     FT_PCI_CONFIG_BASEADDR,
     DEVICE_MEM},
    {FT_PCI_IO_CONFIG_BASEADDR,
     FT_PCI_IO_CONFIG_BASEADDR + FT_PCI_IO_CONFIG_REG_LENGTH,
     FT_PCI_IO_CONFIG_BASEADDR,
     DEVICE_MEM},
    {FT_PCI_MEM32_BASEADDR,
     FT_PCI_MEM32_BASEADDR + FT_PCI_MEM32_REG_LENGTH,
     FT_PCI_MEM32_BASEADDR,
     DEVICE_MEM},
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);

static rt_uint32_t timerStep;

void rt_hw_timer_isr(int vector, void *parameter)
{
    gtimer_set_load_value(timerStep);
    rt_tick_increase();
}

int rt_hw_timer_init(void)
{
    rt_hw_interrupt_install(30, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(30);
    timerStep = gtimer_get_counter_frequency();
    timerStep /= RT_TICK_PER_SECOND;
    gtimer_set_load_value(timerStep);
    gtimer_set_control(1);
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

static void AssertCallback(const char *File, s32 Line)
{
    Ft_printf("Assert Error is %s : %d \r\n", File, Line);
}

#ifdef RT_USING_SMP
void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);
#endif

/**
 * This function will initialize hardware board
 */
void rt_hw_board_init(void)
{
    /* bsp debug */
    FCpu_SpinLockInit();
    Ft_GenericTimer_Init(0, RT_NULL);
    Ft_vsprintfRegister((vsprintf_p)rt_vsprintf);
    Ft_assertSetCallBack((Ft_assertCallback)AssertCallback);

    /* interrupt init */
    arm_gic_redist_address_set(0, FT_GICV3_RD_BASEADDRESS + 0, 0);

#if RT_CPUS_NR == 2
    Ft_printf("arm_gic_redist_address_set is 2 \r\n");
    arm_gic_redist_address_set(0, FT_GICV3_RD_BASEADDRESS + (2U << 16), 1);
#elif RT_CPUS_NR == 3
    arm_gic_redist_address_set(0, FT_GICV3_RD_BASEADDRESS + (2U << 16), 1);
    arm_gic_redist_address_set(0, FT_GICV3_RD_BASEADDRESS + 2 * (2U << 16), 2);
#elif RT_CPUS_NR == 4
    arm_gic_redist_address_set(0, FT_GICV3_RD_BASEADDRESS + (2U << 16), 1);
    arm_gic_redist_address_set(0, FT_GICV3_RD_BASEADDRESS + 2 * (2U << 16), 2);
    arm_gic_redist_address_set(0, FT_GICV3_RD_BASEADDRESS + 3 * (2U << 16), 3);
#endif

    rt_hw_interrupt_init();

    rt_components_board_init();
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

/* 初始化内存池 */
#ifdef RT_USING_HEAP
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
#endif

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_interrupt_set_priority(RT_SCHEDULE_IPI, 16);
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
#endif
}

static void ft_reset(void)
{
    FPsci_Reset();
}
MSH_CMD_EXPORT_ALIAS(ft_reset, ft_reset, ft_reset);

/*@}*/
