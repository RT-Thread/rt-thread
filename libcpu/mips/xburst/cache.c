/*
 * File      : cache.c
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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
*/

#include "../xburst/cache.h"

#include <board.h>

#define CACHE_SIZE              16*1024
#define CACHE_LINE_SIZE         32
#define KSEG0                   0x80000000

#define K0_TO_K1()              \
do {                        \
    unsigned long __k0_addr;        \
                        \
    __asm__ __volatile__(           \
    "la %0, 1f\n\t"             \
    "or %0, %0, %1\n\t"         \
    "jr %0\n\t"             \
    "nop\n\t"               \
    "1: nop\n"              \
    : "=&r"(__k0_addr)          \
    : "r" (0x20000000) );           \
} while(0)

#define K1_TO_K0()              \
do {                        \
    unsigned long __k0_addr;        \
    __asm__ __volatile__(           \
    "nop;nop;nop;nop;nop;nop;nop\n\t"   \
    "la %0, 1f\n\t"             \
    "jr %0\n\t"             \
    "nop\n\t"               \
    "1: nop\n"              \
    : "=&r" (__k0_addr));           \
} while (0)

#define INVALIDATE_BTB()            \
do {                        \
    unsigned long tmp;          \
    __asm__ __volatile__(           \
    ".set mips32\n\t"           \
    "mfc0 %0, $16, 7\n\t"           \
    "nop\n\t"               \
    "ori %0, 2\n\t"             \
    "mtc0 %0, $16, 7\n\t"           \
    "nop\n\t"               \
    ".set mips2\n\t"            \
    : "=&r" (tmp));             \
} while (0)

#define SYNC_WB() __asm__ __volatile__ ("sync")

#define cache_op(op,addr)                       \
    __asm__ __volatile__(                       \
    "   .set    noreorder       \n"         \
    "   .set    mips32\n\t      \n"         \
    "   cache   %0, %1          \n"         \
    "   .set    mips0           \n"         \
    "   .set    reorder"                    \
    :                                       \
    : "i" (op), "m" (*(unsigned char *)(addr)))

void __icache_invalidate_all(void)
{
    unsigned int i;

    K0_TO_K1();

    asm volatile (".set noreorder\n"
              ".set mips32\n\t"
              "mtc0\t$0,$28\n\t"
              "mtc0\t$0,$29\n"
              ".set mips0\n"
              ".set reorder\n");
    for (i=KSEG0;i<KSEG0+CACHE_SIZE;i+=CACHE_LINE_SIZE)
        cache_op(Index_Store_Tag_I, i);

    K1_TO_K0();

    INVALIDATE_BTB();
}

void __dcache_writeback_all(void)
{
    unsigned int i;

    for (i=KSEG0;i<KSEG0+CACHE_SIZE;i+=CACHE_LINE_SIZE)
        cache_op(Index_Writeback_Inv_D, i);

    SYNC_WB();
}

void rt_hw_cache_init(void)
{
    __dcache_writeback_all();
    __icache_invalidate_all();
}

