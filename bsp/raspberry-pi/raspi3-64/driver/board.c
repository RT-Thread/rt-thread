/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"
#include "drv_timer.h"

#include "cp15.h"

#ifdef RT_USING_SMP
extern void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler);

void ipi_handler(){
    rt_scheduler_ipi_handler(0,RT_NULL);
}
#endif

void rt_hw_timer_isr(int vector, void *parameter)
{
    ARM_TIMER_IRQCLR = 0;
    rt_tick_increase();
}

int rt_hw_timer_init()
{
    __DSB();
    rt_hw_interrupt_install(IRQ_ARM_TIMER, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IRQ_ARM_TIMER);
    /* timer_clock = apb_clock/(pre_divider + 1) */
    ARM_TIMER_PREDIV = (250 - 1);

    ARM_TIMER_RELOAD = 0;
    ARM_TIMER_LOAD   = 0;
    ARM_TIMER_IRQCLR = 0;
    ARM_TIMER_CTRL   = 0;

    ARM_TIMER_RELOAD = 10000;
    ARM_TIMER_LOAD   = 10000;

    /* 23-bit counter, enable interrupt, enable timer */
    ARM_TIMER_CTRL   = (1 << 1) | (1 << 5) | (1 << 7);
    return 0;
}

void idle_wfi(void)
{
    asm volatile ("wfi");
}

#define MMU_LEVEL_MASK 0x1ffUL
#define MMU_MAP_ERROR_VANOTALIGN  -1
#define MMU_MAP_ERROR_PANOTALIGN  -2
#define MMU_MAP_ERROR_NOPAGE      -3
#define MMU_MAP_ERROR_CONFLICT    -4

unsigned char main_tbl[4096] __attribute__((aligned (4096)));
unsigned char __page_start[4096*100] __attribute__((aligned (4096)));
unsigned long __page_off = 0;
unsigned long get_free_page(void) {
    __page_off += 4096;
    return (unsigned long)(__page_start + __page_off - 4096);
}

#define MEM_ATTR_MEM ((0x1UL << 10) | (0x2UL << 8) | (0x0UL << 6) | (0x1UL << 2))
#define MEM_ATTR_IO ((0x1UL << 10) | (0x2UL << 8) | (0x0UL << 6) | (0x2UL << 2))

static int map_single_page_2M(unsigned long* lv0_tbl, unsigned long va, unsigned long pa, unsigned long attr) {
    int level;
    unsigned long* cur_lv_tbl = lv0_tbl;
    unsigned long page;
    unsigned long off;
    int level_shift = 39;

    if (va & (0x200000UL - 1)) {
        return MMU_MAP_ERROR_VANOTALIGN;
    }
    if (pa & (0x200000UL - 1)) {
        return MMU_MAP_ERROR_PANOTALIGN;
    }
    for (level = 0; level < 2; level++) {
        off = (va >> level_shift);
        off &= MMU_LEVEL_MASK;
        if ((cur_lv_tbl[off] & 1) == 0) {
            page = get_free_page();
            if (!page) {
                return MMU_MAP_ERROR_NOPAGE;
            }
            rt_memset((void *)page, 0, 4096);
            cur_lv_tbl[off] = page | 0x3UL;
        }
        page = cur_lv_tbl[off];
        if (!(page & 0x2)) {
            //is block! error!
            return MMU_MAP_ERROR_CONFLICT;
        }
        cur_lv_tbl = (unsigned long*)(page & 0x0000fffffffff000UL);
        level_shift -= 9;
    }
    attr &= 0xfff0000000000ffcUL;
    pa |= (attr | 0x1UL); //block
    off = (va >> 21);
    off &= MMU_LEVEL_MASK;
    cur_lv_tbl[off] = pa;
    return 0;
}

int armv8_map_2M(unsigned long* lv0_tbl, unsigned long va, unsigned long pa, int count, unsigned long attr)
{
	int i;
    int ret;

	if (va & (0x200000 - 1))
	{
		return -1;
	}
	if (pa & (0x200000 - 1))
	{
		return -1;
	}
	for (i = 0; i < count; i++)
	{
		ret = map_single_page_2M(lv0_tbl, va, pa, attr);
		va += 0x200000;
		pa += 0x200000;
        if (ret != 0)
        {
            return ret;
        }
	}
    return 0;
}

/**
 *  Initialize the Hardware related stuffs. Called from rtthread_startup() 
 *  after interrupt disabled.
 */
void rt_hw_board_init(void)
{
    /* mmu set */
    unsigned long val64;
    unsigned long val32; //val32不是uint32_t,val32只是表示相关的那个寄存器是32位的
    int ret;

    val64 = 0x007f6eUL;
    asm volatile("msr MAIR_EL1, %0\n dsb sy\n"::"r"(val64));
    asm volatile("mrs %0, MAIR_EL1\n dsb sy\n":"=r"(val64));

    //TCR_EL1
    val32 = (16UL << 0)
        | (0x0UL << 6)
        | (0x0UL << 7)
        | (0x3UL << 8)
        | (0x3UL << 10)
        | (0x2UL << 12)
        | (0x0UL << 14)
        | (0x0UL << 16)
        | (0x0UL << 22)
        | (0x1UL << 23)
        | (0x2UL << 30)
        | (0x1UL << 32)
        | (0x0UL << 35)
        | (0x0UL << 36)
        | (0x0UL << 37)
        | (0x0UL << 38);
    asm volatile("msr TCR_EL1, %0\n"::"r"(val32));
    asm volatile("mrs %0, TCR_EL1\n":"=r"(val32));

    asm volatile("msr TTBR0_EL1, %0\n dsb sy\n"::"r"(main_tbl));
    asm volatile("mrs %0, TTBR0_EL1\n dsb sy\n":"=r"(val64));

    rt_memset(main_tbl, 0, 4096);

	ret = armv8_map_2M((unsigned long *)main_tbl, 0x0, 0x0, 32, MEM_ATTR_MEM); //32*2M = 64M
    if (ret)
    {
        goto skip_mmu;
    }
	ret = armv8_map_2M((unsigned long *)main_tbl, 0x3f000000, 0x3f000000, 8, MEM_ATTR_IO); //8*2M = 16M
    if (ret)
    {
        goto skip_mmu;
    }

	//关闭指令cache
	__asm__ volatile("mrs %0, SCTLR_EL1\n":"=r"(val64));
	val64 &= ~0x1000; //disable I
	__asm__ volatile("dmb sy\n msr SCTLR_EL1, %0\n isb sy\n"::"r"(val64));

	//清除指令cache
	__asm__ volatile("IC IALLUIS\n dsb sy\n isb sy\n");
	//清除tlb
	__asm__ volatile("tlbi vmalle1\n dsb sy\n isb sy\n");

	//SCTLR_EL1, turn on mmu
	asm volatile("mrs %0, SCTLR_EL1\n":"=r"(val32));
	val32 |= 0x1005; //enable mmu, I C M
	asm volatile("dmb sy\n msr SCTLR_EL1, %0\nisb sy\n"::"r"(val32));

skip_mmu:

    /* initialize hardware interrupt */
    rt_hw_interrupt_init(); // in libcpu/interrupt.c. Set some data structures, no operation on device
    rt_hw_vector_init();    // in libcpu/interrupt.c. == rt_cpu_vector_set_base((rt_ubase_t)&system_vectors);

    /* initialize uart */
    rt_hw_uart_init();      // driver/drv_uart.c
    /* initialize timer for os tick */
    rt_hw_timer_init();
    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_CONSOLE
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif /* RT_USING_CONSOLE */

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_kprintf("heap: 0x%08x - 0x%08x\n", RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
	rt_kprintf("__page_off = %x\n", __page_off);
}

#ifdef RT_USING_SMP
void _reset(void);
void secondary_cpu_start(void);

void rt_hw_secondary_cpu_up(void)
{
    int i;
    int retry,val;
    rt_cpu_dcache_clean_flush();
    rt_cpu_icache_flush();
    /*TODO maybe, there is some bug */
    for(i=RT_CPUS_NR-1; i>0; i-- )
    {
        rt_kprintf("boot cpu:%d\n", i);
        setup_bootstrap_addr(i, (int)_reset);
        __SEV();
        __DSB();
        __ISB();
        retry = 10;
        rt_thread_delay(RT_TICK_PER_SECOND/1000);
        do
        {
            val = CORE_MAILBOX3_CLEAR(i);
            if (val == 0)
            {
                rt_kprintf("start OK: CPU %d \n",i);
                break;
            }
            rt_thread_delay(RT_TICK_PER_SECOND);

            retry --;
            if (retry <= 0)
            {
                rt_kprintf("can't start for CPU %d \n",i);
                break;
            }
        }while (1);
    }
    __DSB();
    __SEV();
}

void secondary_cpu_c_start(void)
{
    uint32_t id;
    id = rt_hw_cpu_id();
    rt_kprintf("cpu = 0x%08x\n",id);
    rt_hw_timer_init();
    rt_kprintf("cpu %d startup.\n",id);
    rt_hw_vector_init();
    enable_cpu_ipi_intr(id);
    rt_hw_spin_lock(&_cpus_lock);
    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    __WFE();
}

#endif
