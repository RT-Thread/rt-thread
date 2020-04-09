/*
 * File      : cache.c
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
 * 2016/11/02     Urey         the first version
 */

#include <rtthread.h>
#include <board.h>
#include <rthw.h>

#include "../common/mips.h"


#define CONFIG_SYS_DCACHE_SIZE      16384
#define CONFIG_SYS_ICACHE_SIZE      16384
#define CONFIG_SYS_CACHELINE_SIZE   32

#define K0_TO_K1()                      \
do {                                    \
    unsigned long __k0_addr;            \
                                        \
    __asm__ __volatile__(               \
    "la %0, 1f\n\t"                     \
    "or %0, %0, %1\n\t"                 \
    "jr %0\n\t"                         \
    "nop\n\t"                           \
    "1: nop\n"                          \
    : "=&r"(__k0_addr)                  \
    : "r" (0x20000000) );               \
} while(0)

#define K1_TO_K0()                      \
do {                                    \
    unsigned long __k0_addr;            \
    __asm__ __volatile__(               \
    "nop;nop;nop;nop;nop;nop;nop\n\t"       \
    "la %0, 1f\n\t"             \
    "jr %0\n\t"                 \
    "nop\n\t"                   \
    "1: nop\n"                  \
    : "=&r" (__k0_addr));       \
} while (0)

#define INVALIDATE_BTB()        \
do {                            \
    unsigned long tmp;         \
    __asm__ __volatile__(     \
    ".set mips32\n\t"           \
    "mfc0 %0, $16, 7\n\t"       \
    "nop\n\t"                   \
    "ori %0, 2\n\t"             \
    "mtc0 %0, $16, 7\n\t"       \
    "nop\n\t"                   \
    ".set mips2\n\t"            \
    : "=&r" (tmp));             \
} while (0)

#define __sync()                \
    __asm__ __volatile__(           \
        ".set   push\n\t"       \
        ".set   noreorder\n\t"      \
        ".set   mips2\n\t"      \
        "sync\n\t"          \
        ".set   pop"            \
        : /* no output */       \
        : /* no input */        \
        : "memory")

#if defined(JZ4775) || defined(X1000)
#define SYNC_WB()               \
do {                        \
    __asm__ __volatile__ (          \
    "sync\n\t"              \
    "lw $0, %0\n\t"             \
    :                   \
    :"m"(*(int *)0xa0000000)        \
    :"memory");             \
} while (0)
#else
#error "not define sync wb"
#define SYNC_WB() __asm__ __volatile__ ("sync")
#endif


#undef cache_op
#define cache_op(op, addr)      \
    __asm__ __volatile__(       \
        ".set   push\n"     \
        ".set   noreorder\n"    \
        ".set   mips3\n"    \
        "cache  %0, %1\n"   \
        ".set   pop\n"      \
        :           \
        : "i" (op), "R" (*(unsigned char *)(addr)))


void rt_hw_dcache_flush_line(rt_uint32_t addr)
{
	cache_op(HIT_WRITEBACK_INV_D, addr);
	SYNC_WB();
}

void rt_hw_dcache_flush_range(rt_uint32_t start_addr, rt_uint32_t size)
{
    rt_uint32_t lsize = CONFIG_SYS_CACHELINE_SIZE;
    rt_uint32_t addr = start_addr & ~(lsize - 1);
    rt_uint32_t aend = (start_addr + size - 1) & ~(lsize - 1);
    rt_uint32_t writebuffer;

    for (; addr <= aend; addr += lsize)
    {
        cache_op(HIT_WRITEBACK_INV_D, addr);
    }
    SYNC_WB();
}

void rt_hw_dcache_flush_all(void)
{
    rt_uint32_t addr;

    for (addr = CKSEG0; addr < CKSEG0 + CONFIG_SYS_DCACHE_SIZE; addr += CONFIG_SYS_CACHELINE_SIZE)
    {
        cache_op(INDEX_WRITEBACK_INV_D, addr);
    }

    SYNC_WB();
}

void rt_hw_dcache_invalidate_range(rt_uint32_t start_addr,rt_uint32_t size)
{
    rt_uint32_t lsize = CONFIG_SYS_CACHELINE_SIZE;
    rt_uint32_t addr = start_addr & ~(lsize - 1);
    rt_uint32_t aend = (start_addr + size - 1) & ~(lsize - 1);

    for (; addr <= aend; addr += lsize)
        cache_op(HIT_INVALIDATE_D, addr);
}

void rt_hw_dcache_invalidate_all(void)
{
    rt_uint32_t addr;

    for (addr = CKSEG0; addr < CKSEG0 + CONFIG_SYS_DCACHE_SIZE; addr += CONFIG_SYS_CACHELINE_SIZE)
    {
        cache_op(INDEX_STORE_TAG_D, addr);
    }

    SYNC_WB();
}

void rt_hw_icache_flush_line(rt_uint32_t addr)
{
    cache_op(HIT_INVALIDATE_I, addr);
}

void rt_hw_icache_flush_all(void)
{
    rt_uint32_t addr;

    asm volatile ("mtc0 $0, $28"); /* Clear Taglo */
    asm volatile ("mtc0 $0, $29"); /* Clear TagHi */

    for (addr = CKSEG0; addr < CKSEG0 + CONFIG_SYS_DCACHE_SIZE; addr += CONFIG_SYS_CACHELINE_SIZE)
    {
        cache_op(INDEX_STORE_TAG_I, addr);
    }

    INVALIDATE_BTB();
}

void rt_hw_icache_invalidate_all(void)
{
    rt_uint32_t i;

    K0_TO_K1();

    asm volatile (".set noreorder\n"
              ".set mips32\n\t"
              "mtc0\t$0,$28\n\t"
              "mtc0\t$0,$29\n"
              ".set mips0\n"
              ".set reorder\n");
    for (i = CKSEG0; i < CKSEG0 + CONFIG_SYS_ICACHE_SIZE; i += CONFIG_SYS_CACHELINE_SIZE)
        cache_op(INDEX_STORE_TAG_I, i);

    K1_TO_K0();

    INVALIDATE_BTB();
}


void rt_hw_flush_cache_all(void)
{
    rt_hw_dcache_flush_all();
    rt_hw_icache_flush_all();
}



