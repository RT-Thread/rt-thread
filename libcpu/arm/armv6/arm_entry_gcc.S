/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-11-07     weety    first version
 */

#include <rtconfig.h>

#include "armv6.h"

//#define DEBUG

.macro  PRINT, str
#ifdef DEBUG
    stmfd   sp!, {r0-r3, ip, lr}
    add r0, pc, #4
    bl  rt_kprintf
    b   1f
    .asciz  "UNDEF: \str\n"
    .balign 4
1:  ldmfd   sp!, {r0-r3, ip, lr}
#endif
    .endm

.macro  PRINT1, str, arg
#ifdef DEBUG
    stmfd   sp!, {r0-r3, ip, lr}
    mov r1, \arg
    add r0, pc, #4
    bl  rt_kprintf
    b   1f
    .asciz  "UNDEF: \str\n"
    .balign 4
1:  ldmfd   sp!, {r0-r3, ip, lr}
#endif
    .endm

.macro  PRINT3, str, arg1, arg2, arg3
#ifdef DEBUG
    stmfd   sp!, {r0-r3, ip, lr}
    mov r3, \arg3
    mov r2, \arg2
    mov r1, \arg1
    add r0, pc, #4
    bl  rt_kprintf
    b   1f
    .asciz  "UNDEF: \str\n"
    .balign 4
1:  ldmfd   sp!, {r0-r3, ip, lr}
#endif
    .endm

.macro  get_current_thread, rd
    ldr \rd, .current_thread
    ldr \rd, [\rd]
    .endm

.current_thread:
    .word   rt_current_thread

#ifdef RT_USING_NEON
    .align  6

/* is the neon instuction on arm mode? */
.neon_opcode:
    .word   0xfe000000          @ mask
    .word   0xf2000000          @ opcode

    .word   0xff100000          @ mask
    .word   0xf4000000          @ opcode

    .word   0x00000000          @ end mask
    .word   0x00000000          @ end opcode
#endif

/* undefined instruction exception processing */
.globl undef_entry
undef_entry:
    PRINT1 "r0=0x%08x", r0
    PRINT1 "r2=0x%08x", r2
    PRINT1 "r9=0x%08x", r9
    PRINT1 "sp=0x%08x", sp

#ifdef RT_USING_NEON
    ldr r6, .neon_opcode
__check_neon_instruction:
    ldr r7, [r6], #4        @ load mask value
    cmp r7, #0              @ end mask?
    beq __check_vfp_instruction
    and r8, r0, r7
    ldr r7, [r6], #4        @ load opcode value
    cmp r8, r7              @ is NEON instruction?
    bne __check_neon_instruction
    b   vfp_entry
__check_vfp_instruction:
#endif
    tst r0, #0x08000000         @ only CDP/CPRT/LDC/STC instruction has bit 27
    tstne   r0, #0x04000000     @ bit 26 set on both ARM and Thumb-2 instruction
    moveq   pc, lr              @ no vfp coprocessor instruction, return
    get_current_thread r10
    and r8, r0, #0x00000f00     @ get coprocessor number
    PRINT1 "CP=0x%08x", r8
    add pc, pc, r8, lsr #6
    nop
    mov pc, lr              @ CP0
    mov pc, lr              @ CP1
    mov pc, lr              @ CP2
    mov pc, lr              @ CP3
    mov pc, lr              @ CP4
    mov pc, lr              @ CP5
    mov pc, lr              @ CP6
    mov pc, lr              @ CP7
    mov pc, lr              @ CP8
    mov pc, lr              @ CP9
    mov pc, lr              @ CP10 VFP
    mov pc, lr              @ CP11 VFP
    mov pc, lr              @ CP12
    mov pc, lr              @ CP13
    mov pc, lr              @ CP14 DEBUG
    mov pc, lr              @ CP15 SYS CONTROL


