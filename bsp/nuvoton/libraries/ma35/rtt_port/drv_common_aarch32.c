/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2021-07-14      Wayne            First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(USE_MA35D1_AARCH32)

#include <rthw.h>
#include <stdio.h>

#include "drv_common.h"
#include "board.h"
#include "drv_uart.h"
#include "drv_sspcc.h"
#include "drv_ssmcc.h"
#include "drv_umctl2.h"

#define LOG_TAG    "drv.common"
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL      LOG_LVL_INFO
#define DBG_COLOR
#include <rtdbg.h>

#define NORMAL_MEM_UNCACHED        (SHARED|AP_RW|DOMAIN0|STRONGORDER|DESC_SEC)

/*
MMU TLB setting:
0xFFFFFFFF  ----------------------------
            |  1GB DDR(non-cacheable)  |
0xC0000000  ----------------------------
            |    1GB DDR(cacheable)    |
0x80000000  ----------------------------
            |      DEVICE_MEM          |
            |                          |
0x00000000  ----------------------------
*/
struct mem_desc platform_mem_desc[] =
{
    {0x00000000,   0x7FFFFFFF, 0x00000000, DEVICE_MEM},          // Peripherals
    {0x80000000,   DDR_LIMIT_SIZE - 1, 0x80000000, NORMAL_MEM},  // 1GB DDR, cacheable
    {0xC0000000,   0xFFFFFFFF, 0x80000000, NORMAL_MEM_UNCACHED}  // 1GB DDR, non-cacheable
};
const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc) / sizeof(platform_mem_desc[0]);
/**
 * This function will initialize board
 */

struct rt_aspace mmu_info;

extern size_t MMUTable[];

extern void nu_clock_dump(void);
extern void nu_clock_raise(void);
extern void nu_clock_init(void);
extern void nu_chipcfg_dump(void);
extern uint32_t nu_chipcfg_ddrsize(void);

volatile uint32_t secondary_cpu_entry __attribute__((aligned(32))) = 0;
static rt_uint32_t timerStep;

void rt_hw_systick_isr(int vector, void *parameter)
{
    gtimer_set_load_value(timerStep);
    rt_tick_increase();
}

int rt_hw_systick_init(void)
{
    rt_hw_interrupt_install(NonSecPhysicalTimer_IRQn, rt_hw_systick_isr, RT_NULL, "systick");
    rt_hw_interrupt_umask(NonSecPhysicalTimer_IRQn);
    timerStep = gtimer_get_counter_frequency();
    timerStep /= RT_TICK_PER_SECOND;
    gtimer_set_load_value(timerStep);
    gtimer_set_control(1);
    return 0;
}

void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    volatile rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t cmp = timerStep;    // 12000 count / 1ms

    ticks = us * (cmp / 1000);      // us * 12(count/1us)
    told = gtimer_get_current_value();

    while (1)
    {
        /* Timer counter is increment. */
        tnow = gtimer_get_current_value();
        if (tnow != told)
        {
            /* 0 -- now === old -------- cmp */
            if (tnow < told)
            {
                tcnt += (told - tnow);
            }
            else
            {
                /* 0 == old --- new ======== cmp */
                tcnt += (cmp - tnow + told);
            }
            told = tnow;

            /* Timeout */
            if (tcnt >= ticks)
            {
                break;
            }
        }
        __NOP();
    }
} /* rt_hw_us_delay */

void idle_wfi(void)
{
    asm volatile("wfi");
}

rt_weak void nutool_pincfg_init(void)
{
}

/**
 * This function will initial board.
 */
rt_weak void rt_hw_board_init(void)
{
    uint32_t u32BoardHeapEnd;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* initialize SSPCC */
    nu_sspcc_init();

    /* initialize SSMCC */
    nu_ssmcc_init();

    /* initialize UMCTL2 */
    nu_umctl2_init();

    /* initialize base clock */
    nu_clock_init();

    /* initialize peripheral pin function */
    nutool_pincfg_init();

    rt_hw_mmu_map_init(&mmu_info, (void*)0x80000000, 0x10000000, MMUTable, 0);
    rt_hw_mmu_ioremap_init(&mmu_info, (void*)0x80000000, 0x10000000);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

#if defined(RT_USING_HEAP)
    if (nu_chipcfg_ddrsize() > 0)
    {
        /* Get MCP DDR capacity in run-time. */
        u32BoardHeapEnd = 0x80000000 + nu_chipcfg_ddrsize();
    }
    else
    {
        /* Use board.h definition */
        u32BoardHeapEnd = (uint32_t)BOARD_HEAP_END;
    }
    rt_system_heap_init((void *)BOARD_HEAP_START, (void *)u32BoardHeapEnd);
#endif

    /* initialize uart */
    rt_hw_uart_init();

#if defined(RT_USING_CONSOLE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

    nu_clock_raise();

    /* initialize systick */
    rt_hw_systick_init();
    rt_thread_idle_sethook(idle_wfi);

#if defined(RT_USING_COMPONENTS_INIT)
    rt_components_board_init();
#endif

#if defined(RT_USING_HEAP)
    /* Dump heap information */
    LOG_I("Heap: Begin@%08x, END@%08x, SIZE: %d MB", BOARD_HEAP_START, u32BoardHeapEnd, ((rt_uint32_t)u32BoardHeapEnd - (rt_uint32_t)BOARD_HEAP_START) / 1024 / 1024);
#endif

    nu_chipcfg_dump();
    nu_clock_dump();

#if defined(RT_USING_SMP)
    /* install IPI handle */
    rt_hw_interrupt_set_priority(RT_SCHEDULE_IPI, 16);
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
#endif
}

#if defined(RT_USING_SMP)

extern void rt_secondary_cpu_entry(void);
void set_secondary_cpu_boot_address(void)
{
    secondary_cpu_entry = (uint32_t)&rt_secondary_cpu_entry;
    rt_kprintf("Wake up cpu-1 goto -> 0x%08x@0x%08x\n", secondary_cpu_entry, &secondary_cpu_entry);
}

void rt_hw_secondary_cpu_up(void)
{
    rt_uint32_t i;
    rt_uint32_t cpu_mask;

    rt_kprintf("rt_hw_secondary_cpu_up is processing \r\n");

    set_secondary_cpu_boot_address();

    /* Flush to memory */
    rt_cpu_dcache_clean_flush();

    for (i = 1; i < RT_CPUS_NR; i++)
    {
        rt_kprintf("Bring up cpu-%d\r\n", i);
        cpu_mask = 1 << i;
        __asm__ volatile("dsb" ::
                         : "memory");
        __asm__ volatile("isb" ::
                         : "memory");
        __asm__ volatile("sev");
        rt_hw_ipi_send(RT_SCHEDULE_IPI, cpu_mask);
    }
}

void rt_hw_secondary_cpu_bsp_start(void)
{
    rt_kprintf("[%s] cpu-%d\r\n", __func__, rt_hw_cpu_id());

    rt_hw_vector_init();

    rt_hw_spin_lock(&_cpus_lock);

    arm_gic_cpu_init(0, platform_get_gic_cpu_base());
    rt_hw_systick_init();

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    asm volatile("wfe" ::
                 : "memory", "cc");
}

#endif

#endif /* #if defined(USE_MA35D1_AARCH32) */
