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
#include <rthw.h>
#include <stdio.h>

#include "drv_common.h"
#include "board.h"
#include "drv_uart.h"

#define LOG_TAG    "drv.common"
#undef  DBG_ENABLE
#define DBG_SECTION_NAME   LOG_TAG
#define DBG_LEVEL      LOG_LVL_DBG
#define DBG_COLOR
#include <rtdbg.h>

#if defined(USE_MA35D1_AARCH32)
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
#endif

static void nu_mmu_initialize(void)
{
#if defined(USE_MA35D1_AARCH64)
    mmu_init();
    /* device memory 0x0000_0000 - 0x3FFF_FFFF */
    armv8_map(0x00000000, 0x00000000, 0x40000000, MEM_ATTR_IO);
    /* device memory 0x4000_0000 - 0x7FFF_FFFF */
    armv8_map(0x40000000, 0x40000000, 0x40000000, MEM_ATTR_IO);
    /* system memory 0x8000_0000 - 0xFFFF_FFFF */
    armv8_map(0x80000000, 0x80000000, 0x80000000, MEM_ATTR_MEMORY);
    mmu_enable();
#endif
}

#if !defined(USE_MA35D1_SUBM)

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

void nu_sspcc_init(void)
{
    int i, j;

    CLK->APBCLK2 |= CLK_APBCLK2_SSPCCEN_Msk;
    /* Set all GPIO security set to TZNS. */
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 14; j++)
        {
            SSPCC_SetRealm_GPIO(GPIO_BASE + (j * 0x40), i, SSPCC_SSET_TZNS);
        }
    }
}

void nu_ssmcc_init(void)
{
    CLK->APBCLK2 |= CLK_APBCLK2_SSMCCEN_Msk;

    /* set region 0 to secure region, non-secure and m4 all can access */
    SSMCC_SetRegion0(SSMCC_SECURE_READ | SSMCC_SECURE_WRITE | SSMCC_NONSECURE_READ | SSMCC_NONSECURE_WRITE | SSMCC_M4NS_READ | SSMCC_M4NS_WRITE);
}

void nu_ddr_init(void)
{
    UMCTL2->PCTRL_0 = UMCTL2_PCTRL_0_port_en_Msk;  //[0x0490]
    UMCTL2->PCTRL_1 = UMCTL2_PCTRL_1_port_en_Msk;  //[0x0540]
    UMCTL2->PCTRL_2 = UMCTL2_PCTRL_2_port_en_Msk;  //[0x05f0]
    UMCTL2->PCTRL_3 = UMCTL2_PCTRL_3_port_en_Msk;  //[0x06a0]

    UMCTL2->PCTRL_4 = UMCTL2_PCTRL_4_port_en_Msk;  //[0x0750]
    UMCTL2->PCTRL_5 = UMCTL2_PCTRL_5_port_en_Msk;  //[0x0800]
    UMCTL2->PCTRL_6 = UMCTL2_PCTRL_6_port_en_Msk;  //[0x08b0]
    UMCTL2->PCTRL_7 = UMCTL2_PCTRL_7_port_en_Msk;  //[0x0960]
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

#else

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

int rt_hw_systick_init(void)
{
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Configure SysTick */
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);


    return 0;
}

/**
 * The time delay function.
 *
 * @param microseconds.
 */
void rt_hw_us_delay(rt_uint32_t us)
{
    rt_uint32_t ticks;
    rt_uint32_t told, tnow, tcnt = 0;
    rt_uint32_t reload = SysTick->LOAD;

    ticks = us * reload / (1000000 / RT_TICK_PER_SECOND);
    told = SysTick->VAL;
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

#endif


void devmem(int argc, char *argv[])
{
    volatile unsigned int u32Addr;
    unsigned int value = 0, mode = 0;

    if (argc < 2 || argc > 3)
    {
        goto exit_devmem;
    }

    if (argc == 3)
    {
        if (sscanf(argv[2], "0x%x", &value) != 1)
            goto exit_devmem;
        mode = 1; //Write
    }

    if (sscanf(argv[1], "0x%x", &u32Addr) != 1)
        goto exit_devmem;
    else if (u32Addr & (4 - 1))
        goto exit_devmem;

    if (mode)
    {
        *((volatile uint32_t *)u32Addr) = value;
    }
    rt_kprintf("0x%08x\n", *((volatile uint32_t *)u32Addr));

    return;
exit_devmem:
    rt_kprintf("Read: devmem <physical address in hex>\n");
    rt_kprintf("Write: devmem <physical address in hex> <value in hex format>\n");
    return;
}
MSH_CMD_EXPORT(devmem, dump device registers);

void devmem2(int argc, char *argv[])
{
    volatile unsigned int u32Addr;
    unsigned int value = 0, word_count = 1;

    if (argc < 2 || argc > 3)
    {
        goto exit_devmem;
    }

    if (argc == 3)
    {
        if (sscanf(argv[2], "%d", &value) != 1)
            goto exit_devmem;
        word_count = value;
    }

    if (sscanf(argv[1], "0x%x", &u32Addr) != 1)
        goto exit_devmem;
    else if (u32Addr & (4 - 1))
        goto exit_devmem;

    if (word_count > 0)
    {
        LOG_HEX("devmem", 16, (void *)u32Addr, word_count * sizeof(rt_base_t));
    }

    return;
exit_devmem:
    rt_kprintf("devmem2: <physical address in hex> <count in dec>\n");
    return;
}
MSH_CMD_EXPORT(devmem2, dump device registers);

void idle_wfi(void)
{
#if defined(USE_MA35D1_SUBM)
    __WFI();
#else
    asm volatile("wfi");
#endif
}

extern void nu_clock_dump(void);
extern void nu_clock_raise(void);

RT_WEAK void nutool_pincfg_init(void)
{

}

/**
 * This function will initial board.
 */
RT_WEAK void rt_hw_board_init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

#if !defined(USE_MA35D1_SUBM)
    /* initialize SSPCC */
    nu_sspcc_init();

    /* initialize SSMCC */
    nu_ssmcc_init();

    /* initialize UMCTL2 */
    nu_ddr_init();

#endif

    /* initialize base clock */
    nu_clock_init();


    /* initialize peripheral pin function */
    nutool_pincfg_init();

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();

    /* initialize MMU */
    nu_mmu_initialize();

#if defined(RT_USING_HEAP)
    rt_system_heap_init((void *)BOARD_HEAP_START, (void *)BOARD_HEAP_END);
#endif

    /* initialize uart */
    rt_hw_uart_init();

#if defined(RT_USING_CONSOLE)
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#if !defined(USE_MA35D1_SUBM)
#if !defined(USE_MA35D1_AARCH64)
    //TOFIX
    nu_clock_raise();
#endif
    nu_clock_dump();
#endif

#if defined(RT_USING_HEAP)
    /* Dump heap information */
    rt_kprintf("Heap: Begin@%08x, END@%08x, SIZE: %d KiB\n", BOARD_HEAP_START, BOARD_HEAP_END, ((rt_uint32_t)BOARD_HEAP_END - (rt_uint32_t)BOARD_HEAP_START) / 1024);
#endif

    /* initialize systick */
    rt_hw_systick_init();
    rt_thread_idle_sethook(idle_wfi);

#if defined(RT_USING_COMPONENTS_INIT)
    rt_components_board_init();
#endif

#if defined(RT_USING_SMP)
    /* install IPI handle */
    rt_hw_interrupt_set_priority(RT_SCHEDULE_IPI, 16);
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
#endif

}

#if defined(RT_USING_SMP)

extern void secondary_cpu_start(void);
void set_secondary_cpu_boot_address(void)
{
    secondary_cpu_entry = (uint32_t)&secondary_cpu_start;
    rt_kprintf("Wake up cpu-1 goto -> 0x%08x\n", secondary_cpu_entry);
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

void secondary_cpu_c_start(void)
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
