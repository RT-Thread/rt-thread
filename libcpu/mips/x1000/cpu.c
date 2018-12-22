/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016Äê9ÔÂ8ÈÕ     Urey         the first version
 */


#include <rtthread.h>
#include <board.h>
#include <rthw.h>

#include "../common/mips.h"

mips32_core_cfg_t g_mips_core =
{
	.icache_line_size 	= 32,
	.icache_size		= 16384,

	.dcache_line_size 	= 32,
	.dcache_size		= 16384,

	.max_tlb_entries 	= 16,		/* max_tlb_entries */
};

void rt_hw_tlb_init(void)
{
//----------------------------------------------------------------------------------
//cchappy tlb  0x30000000 to 0xC0000000
//----------------------------------------------------------------------------------
	unsigned int pagemask = 0x007fe000;//0x01ffe000; /* 4MB */
	/* cached D:allow-W V:valid G */
	unsigned int entrylo0 = (0x30000000 >> 6) | (3 << 3) + (1 << 2) + (1 << 1) + 1;
	unsigned int entrylo1 = (0x30400000 >> 6) | (3 << 3) + (1 << 2) + (1 << 1) + 1;
	unsigned int entryhi 	= 0xc0000000; /* kseg2 base */
	int i;
	__write_32bit_c0_register($5, 4, 0xa9000000);
	write_c0_pagemask(pagemask);
	write_c0_wired(0);
/* indexed write 32 tlb entry */
	for(i = 0; i < 32; i++)
	{
		asm (
		".macro _ssnop; sll $0, $0, 1; .endm\n\t"
		".macro _ehb; sll $0, $0, 3; .endm\n\t"
		".macro mtc0_tlbw_hazard; _ssnop; _ssnop; _ehb; .endm\n\t"
		".macro tlbw_use_hazard; _ssnop; _ssnop; _ssnop; _ehb; .endm\n\t"
		"\n\t"
		"mtc0 %0, $0\n\t" /* write Index */
		"tlbw_use_hazard\n\t"
		"mtc0 %1, $5\n\t" /* write PageMask */
		"mtc0 %2, $10\n\t" /* write EntryHi */
		"mtc0 %3, $2\n\t" /* write EntryLo0 */
		"mtc0 %4, $3\n\t" /* write EntryLo1 */
		"mtc0_tlbw_hazard\n\t"
		"tlbwi \n\t" /* TLB indexed write */
		"tlbw_use_hazard\n\t"
		: : "Jr" (i), "r" (pagemask), "r" (entryhi),
		"r" (entrylo0), "r" (entrylo1)
		);
		entryhi += 0x0800000; /* 32MB */
		entrylo0 += (0x0800000 >> 6);
		entrylo1 += (0x0800000 >> 6);
	}
}

void rt_hw_cache_init(void)
{
	r4k_cache_flush_all();
}

/**
 * this function will reset CPU
 *
 */
RT_WEAK void rt_hw_cpu_reset()
{
    /* open the watch-dog */
    REG_WDT_TCSR  = WDT_TCSR_EXT_EN;
    REG_WDT_TCSR |= WDT_TCSR_PRESCALE_1024;
    REG_WDT_TDR   = 0x03;
    REG_WDT_TCNT  = 0x00;
    REG_WDT_TCER |= WDT_TCER_TCEN;

    rt_kprintf("reboot system...\n");
    rt_hw_interrupt_disable();
    while (1);
}

/**
 * this function will shutdown CPU
 *
 */
RT_WEAK void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");
	rt_hw_interrupt_disable();
	while (1);
}

/**
 * This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
RT_WEAK int __rt_ffs(int value)
{
    return __builtin_ffs(value);
}
