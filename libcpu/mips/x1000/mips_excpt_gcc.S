/*
 * File      : mips_excpt_asm.S
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
 * 2016年9月7日     Urey         the first version
 */

#ifndef __ASSEMBLY__
#	define __ASSEMBLY__
#endif

#include "../common/mips.h"

#define _EXC_STKSIZE 	20*1024

;/*********************************************************************************************************
;  PTE BASE 相关定义
;*********************************************************************************************************/

#define PTE_BASE_OFFSET                 23
#define PTE_BASE_SIZE                   9
#define MIPS32_BADVPN2_SHIFT            2


    .section ".text", "ax"
    .set	noreorder

LEAF(mips_tlb_refill_handlerx)
    .set    push
    .set    noat
    .set    noreorder
    .set    volatile

    ;/*
    ; * K1 = CP0_CTXT
    ; * K0 = K1
    ; */
    mfc0    k1 , CP0_CONTEXT                                            ;/*  K1 等于 Context 寄存器      */
    ehb
    move    k0 , k1                                                     ;/*  K0 等于 Context 寄存器      */

    ;/*
    ; * K1 <<= PTE_BASE_SIZE
    ; * K1 >>= PTE_BASE_SIZE
    ; * K1 >>= 4
    ; * K1 >>= MIPS32_BADVPN2_SHIFT
    ; * K1 <<= 3
    ; */
    sll     k1 , PTE_BASE_SIZE
    srl     k1 , (PTE_BASE_SIZE + 4 + MIPS32_BADVPN2_SHIFT)             ;/*  K1 为 BAD VPN2              */
    sll     k1 , (4 - 1)

    ;/*
    ; * K0 >>= PTE_BASE_OFFSET
    ; * K0 <<= PTE_BASE_OFFSET
    ; */
    srl     k0 , PTE_BASE_OFFSET
    sll     k0 , PTE_BASE_OFFSET                                        ;/*  K0 为 PTE BASE              */

    ;/*
    ; * K1 = K1 | K0
    ; */
    or      k1 , k1 , k0                                                ;/*  合成                        */

    ;/*
    ; * K0 = *K1
    ; * K1 = *(K1 + 4)
    ; */
    lw      k0 , 0(k1)
    lw      k1 , 4(k1)

    ;/*
    ; * CP0_TLBLO0 = K0
    ; * CP0_TLBLO1 = K1
    ; */
    mtc0    k0 , CP0_ENTRYLO0                                             ;/*  EntryLo0                    */
    mtc0    k1 , CP0_ENTRYLO1                                             ;/*  EntryLo1                    */
    ehb

    tlbwr                                                               ;/*  TLB 随机替换                */

    eret                                                                ;/*  异常返回                    */

    .set    pop
END(mips_tlb_refill_handlerx)
