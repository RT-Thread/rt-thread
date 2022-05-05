/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-17     nl1031       first implementation for MicroBlaze.
 */

.equ    STACK_RMSR,   	0x00
.equ    STACK_R02,    	0x04
.equ    STACK_R03,    	0x08
.equ    STACK_R04,    	0x0C
.equ    STACK_R05,    	0x10
.equ    STACK_R06,    	0x14
.equ    STACK_R07,    	0x18
.equ    STACK_R08,    	0x1C
.equ    STACK_R09,    	0x20
.equ    STACK_R10,    	0x24
.equ    STACK_R11,    	0x28
.equ    STACK_R12,    	0x2C
.equ    STACK_R13,    	0x30
.equ    STACK_R14,    	0x34
.equ    STACK_R15,    	0x38
.equ    STACK_R17,    	0x3C
.equ    STACK_R18,    	0x40
.equ    STACK_R19,    	0x44
.equ    STACK_R20,    	0x48
.equ    STACK_R21,    	0x4C
.equ    STACK_R22,    	0x50
.equ    STACK_R23,    	0x54
.equ    STACK_R24,    	0x58
.equ    STACK_R25,    	0x5C
.equ    STACK_R26,    	0x60
.equ    STACK_R27,    	0x64
.equ    STACK_R28,    	0x68
.equ    STACK_R29,    	0x6C
.equ    STACK_R30,    	0x70
.equ    STACK_R31,    	0x74

.equ    STACK_SIZE,   	0x78
.equ    IE_BIT,       	0x02

.macro PUSH_ALL 
    ADDIK   r1,  r1, -STACK_SIZE
    SWI     r2,  r1,  STACK_R02
    SWI     r3,  r1,  STACK_R03
    SWI     r4,  r1,  STACK_R04
    SWI     r5,  r1,  STACK_R05
    SWI     r6,  r1,  STACK_R06
    SWI     r7,  r1,  STACK_R07
    SWI     r8,  r1,  STACK_R08
    SWI     r9,  r1,  STACK_R09
    SWI     r10, r1,  STACK_R10
    SWI     r11, r1,  STACK_R11
    SWI     r12, r1,  STACK_R12
    SWI     r13, r1,  STACK_R13
    SWI     r14, r1,  STACK_R14
    SWI     r15, r1,  STACK_R15
    SWI     r17, r1,  STACK_R17
    SWI     r18, r1,  STACK_R18
    SWI     r19, r1,  STACK_R19
    SWI     r20, r1,  STACK_R20
    SWI     r21, r1,  STACK_R21
    SWI     r22, r1,  STACK_R22
    SWI     r23, r1,  STACK_R23
    SWI     r24, r1,  STACK_R24
    SWI     r25, r1,  STACK_R25
    SWI     r26, r1,  STACK_R26
    SWI     r27, r1,  STACK_R27
    SWI     r28, r1,  STACK_R28
    SWI     r29, r1,  STACK_R29
    SWI     r30, r1,  STACK_R30
    SWI     r31, r1,  STACK_R31
.endm

.macro POP_ALL
    LWI     r31, r1, STACK_R31
    LWI     r30, r1, STACK_R30
    LWI     r29, r1, STACK_R29
    LWI     r28, r1, STACK_R28
    LWI     r27, r1, STACK_R27
    LWI     r26, r1, STACK_R26
    LWI     r25, r1, STACK_R25
    LWI     r24, r1, STACK_R24
    LWI     r23, r1, STACK_R23
    LWI     r22, r1, STACK_R22
    LWI     r21, r1, STACK_R21
    LWI     r20, r1, STACK_R20
    LWI     r19, r1, STACK_R19
    LWI     r18, r1, STACK_R18
    LWI     r17, r1, STACK_R17
    LWI     r15, r1, STACK_R15
    LWI     r14, r1, STACK_R14
    LWI     r13, r1, STACK_R13
    LWI     r12, r1, STACK_R12
    LWI     r11, r1, STACK_R11
    LWI     r10, r1, STACK_R10
    LWI     r9,  r1, STACK_R09
    LWI     r8,  r1, STACK_R08
    LWI     r7,  r1, STACK_R07
    LWI     r6,  r1, STACK_R06
    LWI     r5,  r1, STACK_R05
    LWI     r4,  r1, STACK_R04
    LWI     r3,  r1, STACK_R03
    LWI     r2,  r1, STACK_R02
.endm

