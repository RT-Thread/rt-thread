/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-10-26  huanghe      first commit
 * 2022-10-26  zhugengyu    support aarch64
 *
 */

#include "rtconfig.h"
#include <rthw.h>
#include <rtthread.h>

#include <mmu.h>

#include <gicv3.h>
#if defined(TARGET_ARMV8_AARCH64)
    #include <psci.h>
    #include <gtimer.h>
    #include <cpuport.h>
#else
    #include "fgeneric_timer.h" /* for aarch32 */
#endif
#include <interrupt.h>
#include <board.h>

#include "fdebug.h"
#include "fprintk.h"
#include "fearly_uart.h"
#include "fcpu_info.h"
#include "fpsci.h"

#define LOG_DEBUG_TAG "BOARD"
#define BSP_LOG_ERROR(format, ...) FT_DEBUG_PRINT_E(LOG_DEBUG_TAG, format, ##__VA_ARGS__)
#define BSP_LOG_WARN(format, ...)  FT_DEBUG_PRINT_W(LOG_DEBUG_TAG, format, ##__VA_ARGS__)
#define BSP_LOG_INFO(format, ...)  FT_DEBUG_PRINT_I(LOG_DEBUG_TAG, format, ##__VA_ARGS__)
#define BSP_LOG_DEBUG(format, ...) FT_DEBUG_PRINT_D(LOG_DEBUG_TAG, format, ##__VA_ARGS__)

/* mmu config */
struct mem_desc platform_mem_desc[] =
#if defined(TARGET_E2000)
{
    {
        0x00U,
        0x00U + 0x40000000U,
        0x00U,
        DEVICE_MEM
    },
    {
        0x40000000U,
        0x40000000U + 0x10000000U,
        0x40000000U,
        DEVICE_MEM
    },
    {
        0x50000000U,
        0x50000000U + 0x30000000U,
        0x50000000U,
        DEVICE_MEM
    },
    {
        0x80000000U,
        0xffffffffU,
        0x80000000U,
        NORMAL_MEM
    },
#if defined(TARGET_ARMV8_AARCH64)
    {
        0x1000000000,
        0x1000000000 + 0x1000000000,
        0x1000000000,
        DEVICE_MEM
    },
    {
        0x2000000000,
        0x2000000000 + 0x2000000000,
        0x2000000000,
        NORMAL_MEM
    },
#endif
};
#elif defined(TARGET_F2000_4) || defined(TARGET_D2000)
{
    {
        0x80000000,
        0xFFFFFFFF,
        0x80000000,
        DDR_MEM
    },
    {
        0, //< QSPI
        0x1FFFFFFF,
        0,
        DEVICE_MEM
    },
    {
        0x20000000, //<! LPC
        0x27FFFFFF,
        0x20000000,
        DEVICE_MEM
    },
    {
        FT_DEV_BASE_ADDR, //<! Device register
        FT_DEV_END_ADDR,
        FT_DEV_BASE_ADDR,
        DEVICE_MEM
    },
    {
        0x30000000, //<! debug
        0x39FFFFFF,
        0x30000000,
        DEVICE_MEM
    },
    {
        0x3A000000, //<! Internal register space in the on-chip network
        0x3AFFFFFF,
        0x3A000000,
        DEVICE_MEM
    },
    {
        FT_PCI_CONFIG_BASEADDR,
        FT_PCI_CONFIG_BASEADDR + FT_PCI_CONFIG_REG_LENGTH,
        FT_PCI_CONFIG_BASEADDR,
        DEVICE_MEM
    },
    {
        FT_PCI_IO_CONFIG_BASEADDR,
        FT_PCI_IO_CONFIG_BASEADDR + FT_PCI_IO_CONFIG_REG_LENGTH,
        FT_PCI_IO_CONFIG_BASEADDR,
        DEVICE_MEM
    },
    {
        FT_PCI_MEM32_BASEADDR,
        FT_PCI_MEM32_BASEADDR + FT_PCI_MEM32_REG_LENGTH,
        FT_PCI_MEM32_BASEADDR,
        DEVICE_MEM
    }
#if defined(TARGET_ARMV8_AARCH64)
    {
        0x1000000000,
        0x1000000000 + 0x1000000000,
        0x1000000000,
        DEVICE_MEM
    },
    {
        0x2000000000,
        0x2000000000 + 0x2000000000,
        0x2000000000,
        NORMAL_MEM
    },
#endif
};
#endif


const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);



#if defined(TARGET_ARMV8_AARCH64) /* AARCH64 */

/* aarch64 use kernel gtimer */

void idle_wfi(void)
{
    asm volatile("wfi");
}

#else /* AARCH32 */

static rt_uint32_t timerStep;

void rt_hw_timer_isr(int vector, void *parameter)
{
    GenericTimerCompare(timerStep);
    rt_tick_increase();
}

int rt_hw_timer_init(void)
{
    rt_hw_interrupt_install(GENERIC_TIMER_NS_IRQ_NUM, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(GENERIC_TIMER_NS_IRQ_NUM);
    timerStep = GenericTimerFrequecy();
    timerStep /= RT_TICK_PER_SECOND;

    GenericTimerCompare(timerStep);
    GenericTimerInterruptEnable();
    GenericTimerStart();
    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);
#endif


#ifdef RT_USING_SMP
    void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);
#endif

/**
 * This function will initialize hardware board
 */
void rt_hw_board_init(void)
{

    /* mmu init */
#if defined(TARGET_ARMV8_AARCH64)
    rt_hw_init_mmu_table(platform_mem_desc, platform_mem_desc_size);
    rt_hw_mmu_init();
#endif

    /* interrupt init */
#if defined(TARGET_ARMV8_AARCH64)
    f_printk("aarch64 interrupt init \r\n");
#else
    f_printk("aarch32 interrupt init \r\n");

    extern int rt_hw_cpu_id(void);

    u32 cpu_id, cpu_offset = 0;
    GetCpuId(&cpu_id);
    f_printk("cpu_id is %d \r\n", cpu_id);

#if defined(FT_GIC_REDISTRUBUTIOR_OFFSET)
    cpu_offset = FT_GIC_REDISTRUBUTIOR_OFFSET ;
#endif
    f_printk("cpu_offset  is %d \r\n", cpu_offset);
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + (cpu_id + cpu_offset) * GICV3_RD_OFFSET, rt_hw_cpu_id());

#if defined(TARGET_E2000Q)

#if RT_CPUS_NR == 2
    f_printk("arm_gic_redist_address_set is 2 \r\n");
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + 3 * GICV3_RD_OFFSET, 1);
#elif RT_CPUS_NR == 3
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + 3 * GICV3_RD_OFFSET, 1);
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS, 2);
#elif RT_CPUS_NR == 4
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + 3 * GICV3_RD_OFFSET, 1);
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS, 2);
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + GICV3_RD_OFFSET, 3);
#endif

#else

#if RT_CPUS_NR == 2
    f_printk("arm_gic_redist_address_set is 2 \r\n");
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + (1 + cpu_offset) * GICV3_RD_OFFSET, 1);
#elif RT_CPUS_NR == 3
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + (1 + cpu_offset) * GICV3_RD_OFFSET, 1);
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + (2 + cpu_offset) * GICV3_RD_OFFSET, 2);
#elif RT_CPUS_NR == 4
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + (1 + cpu_offset) * GICV3_RD_OFFSET, 1);
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + (2 + cpu_offset) * GICV3_RD_OFFSET, 2);
    arm_gic_redist_address_set(0, GICV3_RD_BASEADDRESS + (3 + cpu_offset) * GICV3_RD_OFFSET, 3);
#endif

#endif

#endif
    rt_hw_interrupt_init();


    /* gtimer init  */
#if defined(TARGET_ARMV8_AARCH64)
    rt_hw_gtimer_init();
#endif

    /* compoent init */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

    /* shell init */

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    /* init memory pool */
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
    PsciCpuReset();
}
MSH_CMD_EXPORT_ALIAS(ft_reset, ft_reset, ft_reset);

/*@}*/
