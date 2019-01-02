/*
 * File      : start.S
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
 * Date                 Author          Notes
 * 2016/3/9 16:27:48    louis           first version
 */

#define CONFIG_STACKSIZE    512
#define S_FRAME_SIZE        72

#define S_OLD_R0            68
#define S_PSR               64
#define S_PC                60
#define S_LR                56
#define S_SP                52

#define S_IP                48
#define S_FP                44
#define S_R10               40
#define S_R9                36
#define S_R8                32
#define S_R7                28
#define S_R6                24
#define S_R5                20
#define S_R4                16
#define S_R3                12
#define S_R2                8
#define S_R1                4
#define S_R0                0

.equ    USERMODE,           0x10
.equ    FIQMODE,            0x11
.equ    IRQMODE,            0x12
.equ    SVCMODE,            0x13
.equ    ABORTMODE,          0x17
.equ    UNDEFMODE,          0x1b
.equ    MODEMASK,           0x1f
.equ    NOINT,              0xc0




    .text
    .section ".ARM1176START"
    .code 32


@*******************************************************************************
@** Common cpu modes
@*******************************************************************************

    .equ ARM1176_MODE_USR,   0x10  @ CPSR_c xxx10000
    .equ ARM1176_MODE_FIQ,   0x11  @ CPSR_c xxx10001
    .equ ARM1176_MODE_IRQ,   0x12  @ CPSR_c xxx10010
    .equ ARM1176_MODE_SVC,   0x13  @ CPSR_c xxx10011
    .equ ARM1176_MODE_ABT,   0x17  @ CPSR_c xxx10111
    .equ ARM1176_MODE_UND,   0x1B  @ CPSR_c xxx11011
    .equ ARM1176_MODE_SYS,   0x1F  @ CPSR_c xxx11111
    .equ ARM1176_CPSR_I_BIT, 0x80  @ CPSR_c 100xxxxx
    .equ ARM1176_CPSR_F_BIT, 0x40  @ CPSR_c 010xxxxx
    .equ ARM1176_CPSR_T_BIT, 0x20  @ CPSR_c 001xxxxx



.globl _start
.globl  ARM1176_Start
_start:
ARM1176_Start:
    msr cpsr_c,#(ARM1176_MODE_SYS | ARM1176_CPSR_I_BIT | ARM1176_CPSR_F_BIT)    @disable irq/fiq first
    ldr r0, =Reset          ;@load translation table base address
    mcr p15,0,r0,c12,c0,0   ;@write translation table base address req
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
Reset:
    ldr pc, =reset
    ldr pc, =vector_undef
    ldr pc, =vector_swi
    ldr pc, =vector_pabt
    ldr pc, =vector_dabt
    ldr pc, =vector_resv
    ldr pc, =vector_irq
    ldr pc, =vector_fiq
    nop
    nop


.balignl    16,0xdeadbeef

/*
 *************************************************************************
 *
 * Startup Code (reset vector)
 * relocate armboot to ram
 * setup stack
 * jump to second stage
 *
 *************************************************************************
 */


/*
 * rtthread bss start and end which are defined in linker script
 */


.extern __stack_start__



.equ Mode_USR,        0x10
.equ Mode_FIQ,        0x11
.equ Mode_IRQ,        0x12
.equ Mode_SVC,        0x13
.equ Mode_ABT,        0x17
.equ Mode_UND,        0x1B
.equ Mode_SYS,        0x1F

.equ I_Bit,           0x80            @ when I bit is set, IRQ is disabled
.equ F_Bit,           0x40            @ when F bit is set, FIQ is disabled

.equ UND_Stack_Size,  0x00000200
.equ SVC_Stack_Size,  0x00000200
.equ ABT_Stack_Size,  0x00000000
.equ FIQ_Stack_Size,  0x00000000
.equ IRQ_Stack_Size,  0x00000200
.equ USR_Stack_Size,  0x00000200

#define ISR_Stack_Size  (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                 FIQ_Stack_Size + IRQ_Stack_Size)

.globl stack_top
stack_top:
    .word __stack_start__



    .extern ARM1176_TcmInitialise
    .extern ARM1176_MmuInitialise
    .extern GH_VIC_set_EdgeClr
    .extern entry

/*
 *************************************************************************
 *
 * Jump vector table
 *
 *************************************************************************
 */

/* ----------------------------------entry------------------------------*/
reset:
    msr cpsr_c,#(ARM1176_MODE_SYS | ARM1176_CPSR_I_BIT | ARM1176_CPSR_F_BIT)    @disable irq/fiq first
    @/* First read in some misc registers */
    mrc p15, 0, r0, c0, c0, 0     @/* Read ID value {A5S=0x41 1 7 b36 5}*/
    mrc p15, 0, r1, c0, c0, 1     @/* Read cache type {0x1d152152}*/
    mrc p15, 0, r2, c0, c0, 2     @/* Read TCM status {0x10001}*/

#ifdef GK7102C    
    @mrc    p15, 0, r0, c15,c14,0  @ read CP15 register c15 into r0
    @orr    r0,  r0,#0x80000000    @ system bit enabled
    @bic    r0,  r0,#0x00000077    @
    @orr    r0,  r0,#0x00000055    @ specifies 16KB data cache
    @mcr    p15, 0, r0, c15,c14,0  @ wraite CP15 register c15 into r0

    mrc     p15, 0, r0, c1, c0, 1  @read CP15 register c1 into r0
    orr     r0,  r0,#0x00000040    @CZ bit enabled
    mcr     p15, 0, r0, c1, c0, 1  @read CP15 register c1 into r0
#endif
    
    @/* Turn on instrucion cache and disable MMU */
    mrc p15, 0, r0, c1, c0, 0     @/* Read control register {0x5327d}*/
    @bic r0, r0, #0x1000          @ Turn off bit 12 - I-cache
    orr    r0, r0, #0x1000        @ Turn on bit 12 - I-cache
    @bic r0, r0, #0x0004          @ Turn off bit 03 - D-cache
    orr    r0, r0, #0x0004        @ Turn on bit 03 - D-cache
    bic r0, r0, #0x2000           @ Turn off bit 13 - HV
    bic r0, r0, #0x0001           @ Turn off bit 1 - MMU

    @orr    r0, r0, #0x2    @ Turn on bit 1 - Alignment fault
    bic r0, r0, #0x400000   @ Turn off bit 22 - Unainged support

    @bic    r0, r0, #0x2        @ Turn off bit 1 - Alignment fault
    @orr    r0, r0, #0x400000   @ Turn on bit 22 - Unainged support

    mcr p15, 0, r0, c1, c0, 0   @/* Write control register */

    mov r0, #0x1
    mcr p15, 0, r0, c3, c0, 0   @/* Write domain access control reg */


    @bl switch_core_freq    @/* Change PLL for core if necessary */
    @bl memsetup5       @/* Initialize Memory */


    @/* -------------------------------------------------- */
    @/* Redirect peripheral port 0x60000000 - 0x7fffffff   */
    @/* -------------------------------------------------- */
    .if CPU_USE_GK710XS==1
    mov r0, #0x80000000
    orr r0, r0, #0x00000015 @0x14=512M
    .else
    mov r0, #0x60000000
    orr r0, r0, #0x00000014 @0x14=512M
    .endif
    mcr p15, 0, r0, c15, c2, 4

    @ clear the irq or fiq first
    mov r0,#0x0
    mov r1,#0xFFFFFFFF
    bl GH_VIC_set_EdgeClr
    mov r0,#0x1
    mov r1,#0xFFFFFFFF
    bl GH_VIC_set_EdgeClr

    nop

    @ bl ARM1176_TcmInitialise
    msr cpsr_c,#(ARM1176_MODE_SYS | ARM1176_CPSR_I_BIT | ARM1176_CPSR_F_BIT)    @disable irq/fiq first
    .if ARM1176_USE_VFP == 1
    bl ARM1176_VfpInitialise
    bl ARM1176_VfpSetFastmode
    .endif
    bl ARM1176_Invalid_Cache

    /* setup stack */
    ldr     r0, =stack_top
    ldr     r0, [r0]

    @  Enter Undefined Instruction Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_UND|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #UND_Stack_Size

    @  Enter Abort Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_ABT|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #ABT_Stack_Size

    @  Enter FIQ Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_FIQ|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #FIQ_Stack_Size

    @  Enter IRQ Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_IRQ|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #IRQ_Stack_Size

    @  Enter Supervisor Mode and set its Stack Pointer
    msr     cpsr_c, #Mode_SVC|I_Bit|F_Bit
    mov     sp, r0
    sub     r0, r0, #SVC_Stack_Size

    @  Enter User Mode and set its Stack Pointer
    mov     sp, r0
    sub     sl, sp, #USR_Stack_Size

    /* clear .bss */
    mov     r0,#0                   /* get a zero                       */
    ldr     r1,=__bss_start__         /* bss start                      */
    ldr     r2,=__bss_end__           /* bss end                            */

bss_loop:
    cmp     r1,r2                   /* check if data to clear           */
    strlo   r0,[r1],#4              /* clear 4 bytes                    */
    blo     bss_loop                /* loop until done                  */

    /* call C++ constructors of global objects                          */
    ldr     r0, =__ctors_start__
    ldr     r1, =__ctors_end__

ctor_loop:
    cmp     r0, r1
    beq     ctor_end
    ldr     r2, [r0], #4
    stmfd   sp!, {r0-r1}
    mov     lr, pc
    bx      r2
    ldmfd   sp!, {r0-r1}
    b       ctor_loop

ctor_end:


    @ need nocache buffer
    bl ARM1176_MmuInitialise

    /* start RT-Thread Kernel       */
    ldr     pc, =entry

    .global ARM1176_Invalid_Cache
    .func   ARM1176_Invalid_Cache

ARM1176_Invalid_Cache:
    stmfd sp!,{r0-r12,lr}
    mov r11,lr

    mov r0,#0x0        @Set [31:30]
    mov r1,#0x3
loop1:
    mov r2,#0x0
    mov r3,#0x80

loop2:
    mov r4,r0,LSL #30
    mov r5,r2,LSL #5        @Index [S+4:5] S=8 32K
    add r4,r4,r5
    mcr    p15, 0, r4, c7, c5, 2
    add r2,r2,#0x1
    cmp r2,r3
    bne loop2

    add r0,r0,#1
    cmp r0,r1
    bne loop1

    mov lr,r11            @ restore link register
    ldmfd sp!,{r0-r12,lr}
    bx lr                 @ branch back to caller

    .size ARM1176_Invalid_Cache, . - ARM1176_Invalid_Cache
    .endfunc


.global cpu_reset
cpu_reset:
    mov pc, lr

/*
 *************************************************************************
 *
 * Interrupt handling
 *
 *************************************************************************
 */

/* exception handlers               */
    .align  5
vector_undef:
    sub     sp, sp, #S_FRAME_SIZE
    stmia   sp, {r0 - r12}          /* Calling r0-r12                   */
    add     r8, sp, #S_PC
    stmdb   r8, {sp, lr}^           /* Calling SP, LR                   */
    str     lr, [r8, #0]            /* Save calling PC                  */
    mrs     r6, spsr
    str     r6, [r8, #4]            /* Save CPSR                        */
    str     r0, [r8, #8]            /* Save OLD_R0                      */
    mov     r0, sp

    bl      rt_hw_trap_udef

    .align  5
vector_swi:
    bl      rt_hw_trap_swi

    .align  5
vector_pabt:
    bl      rt_hw_trap_pabt

    .align  5
vector_dabt:
    sub     sp, sp, #S_FRAME_SIZE
    stmia   sp, {r0 - r12}          /* Calling r0-r12                   */
    add     r8, sp, #S_PC
    stmdb   r8, {sp, lr}^           /* Calling SP, LR                   */
    str     lr, [r8, #0]            /* Save calling PC                  */
    mrs     r6, spsr
    str     r6, [r8, #4]            /* Save CPSR                        */
    str     r0, [r8, #8]            /* Save OLD_R0                      */
    mov     r0, sp

    bl      rt_hw_trap_dabt

    .align  5
vector_resv:
    bl      rt_hw_trap_resv

    .align  5
.globl      rt_interrupt_enter
.globl      rt_interrupt_leave
.globl      rt_thread_switch_interrupt_flag
.globl      rt_interrupt_from_thread
.globl      rt_interrupt_to_thread
vector_irq:
    stmfd   sp!, {r0-r12,lr}
    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

    /* if rt_thread_switch_interrupt_flag set, jump to _interrupt_thread_switch and don't return */
    ldr     r0, =rt_thread_switch_interrupt_flag
    ldr     r1, [r0]
    cmp     r1, #1
    beq     _interrupt_thread_switch

    ldmfd   sp!, {r0-r12,lr}
    subs    pc, lr, #4

    .align  5
vector_fiq:
    stmfd   sp!,{r0-r7,lr}
    bl      rt_hw_trap_fiq
    ldmfd   sp!,{r0-r7,lr}
    subs    pc,lr,#4

_interrupt_thread_switch:
    mov     r1,  #0                 /* clear rt_thread_switch_interrupt_flag*/
    str     r1,  [r0]

    ldmfd   sp!, {r0-r12,lr}        /* reload saved registers           */
    stmfd   sp!, {r0-r3}            /* save r0-r3                       */
    mov     r1,  sp
    add     sp,  sp, #16            /* restore sp                       */
    sub     r2,  lr, #4             /* save old task's pc to r2         */

    mrs     r3,  spsr               /* disable interrupt                */
    orr     r0,  r3, #NOINT
    msr     spsr_c, r0

    ldr     r0,  =.+8               /* switch to interrupted task's stack*/
    movs    pc,  r0

    stmfd   sp!, {r2}               /* push old task's pc               */
    stmfd   sp!, {r4-r12,lr}        /* push old task's lr,r12-r4        */
    mov     r4,  r1                 /* Special optimised code below     */
    mov     r5,  r3
    ldmfd   r4!, {r0-r3}
    stmfd   sp!, {r0-r3}            /* push old task's r3-r0            */
    stmfd   sp!, {r5}               /* push old task's psr              */
    mrs     r4,  spsr
    stmfd   sp!, {r4}               /* push old task's spsr             */

    ldr     r4,  =rt_interrupt_from_thread
    ldr     r5,  [r4]
    str     sp,  [r5]               /* store sp in preempted tasks's TCB*/

    ldr r6,  =rt_interrupt_to_thread
    ldr r6,  [r6]
    ldr sp,  [r6]                   /* get new task's stack pointer     */

    ldmfd   sp!, {r4}               /* pop new task's spsr              */
    msr     SPSR_cxsf, r4
    ldmfd   sp!, {r4}               /* pop new task's psr               */
    msr     CPSR_cxsf, r4

    ldmfd   sp!, {r0-r12,lr,pc}     /* pop new task's r0-r12,lr & pc    */



@*******************************************************************************
@** End of file
@*******************************************************************************

