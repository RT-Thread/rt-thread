/*
 * File      : vfp_entry_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
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
 * 2014-11-07     weety    first version
 */

#include <rtconfig.h>

#ifdef RT_USING_VFP

#include "armv6.h"
#include "vfp.h"

//#define DEBUG

.macro	PRINT, str
#ifdef DEBUG
    stmfd sp!, {r0-r3, ip, lr}
    add   r0, pc, #4
    bl    rt_kprintf
    b     1f
    .asciz  "VFP: \str\n"
    .balign 4
1: ldmfd    sp!, {r0-r3, ip, lr}
#endif
    .endm

.macro  PRINT1, str, arg
#ifdef DEBUG
    stmfd sp!, {r0-r3, ip, lr}
    mov   r1, \arg
    add   r0, pc, #4
    bl    rt_kprintf
    b     1f
    .asciz  "VFP: \str\n"
    .balign 4
1:  ldmfd    sp!, {r0-r3, ip, lr}
#endif
    .endm

.macro  PRINT3, str, arg1, arg2, arg3
#ifdef DEBUG
    stmfd sp!, {r0-r3, ip, lr}
    mov   r3, \arg3
    mov   r2, \arg2
    mov   r1, \arg1
    add   r0, pc, #4
    bl    rt_kprintf
    b     1f
    .asciz  "VFP: \str\n"
    .balign 4
1:  ldmfd  sp!, {r0-r3, ip, lr}
#endif
    .endm

.macro get_vfpregs_offset, rd
    ldr \rd, .vfp_offset
    ldr \rd, [\rd]
    .endm

.vfp_offset:
    .word  vfpregs_offset

.macro vfp_restore_working_reg, base, rd0
    vldmia \base!, {d0-d15}
#ifdef RT_USING_VFPv3
    vmrs \rd0, mvfr0
    and  \rd0, \rd0, #MVFR0_A_SIMD_MASK @ A_SIMD registers
    cmp  \rd0, #2                       @ 0b0000  Not supported.
                                        @ 0b0001  Supported, 16 ¡Á64-bit registers.
                                        @ 0b0010  Supported, 32 ¡Á64-bit registers.
    vldmiaeq \base!, {d16-d31}
    addne    \base, \base, #32*4        @ skip unused registers
#endif
    .endm

.macro vfp_save_working_reg, base, rd0
    vstmia \base!, {d0-d15}             @ save the working registers
#ifdef RT_USING_VFPv3
    vmrs \rd0, mvfr0
    and  \rd0, \rd0, #MVFR0_A_SIMD_MASK @ A_SIMD registers
    cmp  \rd0, #2                       @ 0b0000  Not supported.
                                        @ 0b0001  Supported, 16 ¡Á64-bit registers.
                                        @ 0b0010  Supported, 32 ¡Á64-bit registers.
    vstmiaeq \base!, {d16-d31}
    addne    \base, \base, #32*4        @ skip unused registers
#endif
    .endm

.macro vfp_restore_state, base, fpexc_rd, rd0, rd1, rd2
    ldmia    \base, {\fpexc_rd, \rd0, \rd1, \rd2} @ load FPEXC, FPSCR, FPINST, FPINST2
    tst      \fpexc_rd, #FPEXC_EX                 @ vfp is in the exceptional state?
    beq      1f
    vmsr     fpinst, \rd1                         @ restore fpinst
    tst      \fpexc_rd, #FPEXC_FP2V               @ FPINST2 instruction valid
    beq      1f
    vmsr     fpinst2, \rd2                        @ restore fpinst2
1:
    vmsr     fpscr, \rd0                          @ restore fpscr
    .endm

.macro vfp_save_state, base, fpexc_rd, rd0, rd1, rd2
    vmrs  \rd0, fpscr                          @ current status
    tst   \fpexc_rd, #FPEXC_EX                 @ vfp is in the exceptional state?
    beq   1f
    vmrs  \rd1, fpinst                         @ get fpinst
    tst   \fpexc_rd, #FPEXC_FP2V               @ FPINST2 instruction valid
    beq   1f
    vmrs  \rd2, fpinst2                        @ get fpinst2
1:
    stmia \base, {\fpexc_rd, \rd0, \rd1, \rd2} @ save FPEXC, FPSCR, FPINST, FPINST2
    .endm


/*
 *  VFP hardware support entry point.
 *  r0  = faulted instruction
 *  r2  = faulted PC+4
 *  r9  = successful return
 *  r10 = rt_thread structure
 *  lr  = failure return
 */

.globl vfp_entry
vfp_entry:
    ldr  r1, =rt_interrupt_nest
    ldr  r1, [r1]                     @ get rt_interrupt_nest
    cmp  r1, #0                       @ rt_interrupt_nest == 0?
    bne  irq_vfp_entry                @ irq handler used VFP

    get_vfpregs_offset r11
    add  r10, r10, r11  @ r10 = vfpregs

    vmrs r1, fpexc
    tst  r1, #FPEXC_EN
    bne  __lookup_vfp_exceptions      @ if the VFP already enabled, now checking vfp exceptions

    ldr  r3, last_vfp_context_address
    orr  r1, r1, #FPEXC_EN            @ set VFP enable bit
    ldr  r4, [r3]                     @ get last_vfp_context pointer
    bic  r5, r1, #FPEXC_EX            @ clear exceptions status
    cmp  r4, r10
    beq  __switch_to_the_same_thread  @ switch to the same thread, checking pending exception.

    vmsr fpexc, r5                    @ enable VFP, clear any pending exceptions

    /* Save the current VFP registers to the old thread context */
    cmp  r4, #0
    beq  __no_last_vfp_context
    vfp_save_working_reg r4, r5       @ save the working registers
    vfp_save_state r4, r1, r5, r6, r8 @ save vfp state registers

__no_last_vfp_context:
    str    r10, [r3]                    @ update the last_vfp_context pointer

    vfp_restore_working_reg r10, r5     @ restore the working registers
    vfp_restore_state r10, r1, r5, r6, r8 @ restore vfp state registers

__switch_to_the_same_thread:
    tst      r1, #FPEXC_EX
    bne      __do_exception
    vmsr     fpexc, r1                  @ restore fpexc last
    sub      r2, r2, #4
    str      r2, [sp, #S_PC]            @ retry the faulted instruction
    PRINT1 "return instr=0x%08x", r2
    mov      pc, r9


__lookup_vfp_exceptions:
    tst   r1, #FPEXC_EX | FPEXC_DEX     @ Check for synchronous or asynchronous exception
    bne   __do_exception
    vmrs  r5, fpscr
    tst   r5, #FPSCR_IXE
    bne   __do_exception

    PRINT "__lookup_vfp_exceptions"
    mov   pc, lr

__do_exception:
    PRINT "__do_exception"
    push  {lr}
    mov   r5, r1
    bic   r5, #FPEXC_EX                 @ clear exception
    vmsr  fpexc, r5
    bl    vfp_exception                 @ r0 = faulted instruction, r1 = fpexc
    pop   {pc}
    @mov   pc, lr


irq_vfp_entry:
    vmrs r1, fpexc
    tst  r1, #FPEXC_EN
    bne  __lookup_vfp_exceptions        @ if the VFP already enabled, now checking vfp exceptions

    ldr  r3, last_vfp_context_address
    orr  r1, r1, #FPEXC_EN              @ set VFP enable bit
    ldr  r4, [r3]                       @ get last_vfp_context pointer
    bic  r5, r1, #FPEXC_EX              @ clear exceptions status

    vmsr fpexc, r5                      @ enable VFP, clear any pending exceptions

    /* Save the current VFP registers to the old thread context */
    cmp  r4, #0                         @ last_vfp_context != NULL ?
    beq  __no_save_vfp_context
    vfp_save_working_reg r4, r5         @ save the working registers
    vfp_save_state r4, r1, r5, r6, r8   @ save vfp state registers

    mov   r4, #0
    str   r4, [r3]                      @ update the last_vfp_context pointer
                                        @ last_vfp_context = NULL
__no_save_vfp_context:
    sub   r2, r2, #4
    str   r2, [sp, #S_PC]               @ retry the faulted instruction
    PRINT1 "return instr=0x%08x", r2
    mov   pc, r9

    .align
last_vfp_context_address:
    .word  last_vfp_context

#endif
