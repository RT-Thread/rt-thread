/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-25     Bernard      first version
 * 2011-08-08     lgnq            modified for Loongson LS1B
 * 2015-07-06     chinesebear  modified for Loongson LS1C
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"
#include "drv_uart.h"
#include "ls1c.h"

#define A_K0BASE		0x80000000

extern unsigned char __bss_end;


extern void tlb_refill_exception(void);
extern void general_exception(void);
extern void irq_exception(void);
extern void rt_hw_cache_init(void);
extern void invalidate_writeback_dcache_all(void);
extern void invalidate_icache_all(void);

/**
 * This is the timer interrupt service routine.
 */
void rt_hw_timer_handler(void)
{
	unsigned int count;

	count = read_c0_compare();
	write_c0_compare(count);
	write_c0_count(0);

	/* increase a OS tick */
	rt_tick_increase();
}

/**
 * This function will initial OS timer
 */
void rt_hw_timer_init(void)
{
	write_c0_compare(CPU_HZ/2/RT_TICK_PER_SECOND);
	write_c0_count(0);
}


/**
 * init hardware FPU
 */
void rt_hw_fpu_init(void)
{
    rt_uint32_t c0_status = 0;
    rt_uint32_t c1_status = 0;

    // 使能协处理器1--FPU
    c0_status = read_c0_status();
    c0_status |= (ST0_CU1 | ST0_FR);
    write_c0_status(c0_status);

    // 配置FPU
    c1_status = read_c1_status();
    c1_status |= (FPU_CSR_FS | FPU_CSR_FO | FPU_CSR_FN);    // set FS, FO, FN
    c1_status &= ~(FPU_CSR_ALL_E);                          // disable exception
    c1_status = (c1_status & (~FPU_CSR_RM)) | FPU_CSR_RN;   // set RN
    write_c1_status(c1_status);

    return ;
}


/**
 * This function will initial sam7s64 board.
 */
void rt_hw_board_init(void)
{
	/* init cache */
	rt_hw_cache_init();
	
	/* init hardware interrupt */
	rt_hw_interrupt_init();

	/* clear bev */
	write_c0_status(read_c0_status()&(~(1<<22)));

	/* copy vector */
	rt_memcpy((void *)A_K0BASE, tlb_refill_exception, 0x80);
	rt_memcpy((void *)(A_K0BASE + 0x180), general_exception, 0x80);
	rt_memcpy((void *)(A_K0BASE + 0x200), irq_exception, 0x80);

	invalidate_writeback_dcache_all();
	invalidate_icache_all();
	
#ifdef RT_USING_HEAP
	rt_system_heap_init((void*)&__bss_end, (void*)RT_HW_HEAP_END);
#endif

#ifdef RT_USING_SERIAL
	/* init hardware UART device */
	rt_hw_uart_init();
#endif

#ifdef RT_USING_CONSOLE
	/* set console device */
	rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
    /* init operating system timer */
    rt_hw_timer_init();

#ifdef RT_USING_FPU
    /* init hardware fpu */
    rt_hw_fpu_init();
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

    rt_kprintf("current sr: 0x%08x\n", read_c0_status());
}

/*@}*/
