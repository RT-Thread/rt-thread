/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
    .extern main                               /* 引入外部C入口 */

    .extern rt_interrupt_enter
    .extern rt_interrupt_leave
    .extern rt_thread_switch_interrupt_flag
    .extern rt_interrupt_from_thread
    .extern rt_interrupt_to_thread
    .extern rt_hw_trap_irq

    .global start
    .global endless_loop
    .global rt_hw_context_switch_interrupt_do

    /* Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs */
    .set  MODE_USR, 0x10            /* User Mode */
    .set  MODE_FIQ, 0x11            /* FIQ Mode */
    .set  MODE_IRQ, 0x12            /* IRQ Mode */
    .set  MODE_SVC, 0x13            /* Supervisor Mode */
    .set  MODE_ABT, 0x17            /* Abort Mode */
    .set  MODE_UND, 0x1B            /* Undefined Mode */
    .set  MODE_SYS, 0x1F            /* System Mode */

    .equ  I_BIT, 0x80               /* when I bit is set, IRQ is disabled */
    .equ  F_BIT, 0x40               /* when F bit is set, FIQ is disabled */
    .equ  I_Bit, 0x80               /* when I bit is set, IRQ is disabled */
    .equ  F_Bit, 0x40               /* when F bit is set, FIQ is disabled */

    /* VPBDIV definitions*/
    .equ  VPBDIV,       0xE01FC100
    .set  VPBDIV_VALUE, 0x00000000

    /* Phase Locked Loop (PLL) definitions*/
    .equ  PLL_BASE,      0xE01FC080  /* PLL Base Address */
    .equ  PLLCON_OFS,    0x00        /* PLL Control Offset */
    .equ  PLLCFG_OFS,    0x04        /* PLL Configuration Offset */
    .equ  PLLSTAT_OFS,   0x08        /* PLL Status Offset */
    .equ  PLLFEED_OFS,   0x0C        /* PLL Feed Offset */
    .equ  PLLCON_PLLE,   (1<<0)      /* PLL Enable */
    .equ  PLLCON_PLLC,   (1<<1)      /* PLL Connect */
    .equ  PLLCFG_MSEL,   (0x1F<<0)   /* PLL Multiplier */
    .equ  PLLCFG_PSEL,   (0x03<<5)   /* PLL Divider */
    .equ  PLLSTAT_PLOCK, (1<<10)     /* PLL Lock Status */
    .equ  PLLCFG_Val,    0x00000024  /* <o1.0..4>   MSEL: PLL Multiplier Selection,<o1.5..6>   PSEL: PLL Divider Selection */

    .equ  MEMMAP,       0xE01FC040     /*Memory Mapping Control*/


    /* Memory Accelerator Module (MAM) definitions*/
    .equ  MAM_BASE,     0xE01FC000
    .equ  MAMCR_OFS,    0x00
    .equ  MAMTIM_OFS,   0x04
    .equ  MAMCR_Val,    0x00000002
    .equ  MAMTIM_Val,   0x00000004

    .equ  VICIntEnClr,  0xFFFFF014
    .equ  VICIntSelect, 0xFFFFF00C
/************* 目标配置结束 *************/


/* Setup the operating mode & stack.*/
/* --------------------------------- */
    .global _reset
_reset:
    .code 32
    .align 0

/************************* PLL_SETUP **********************************/
        ldr     r0, =PLL_BASE
        mov     r1, #0xAA
        mov     r2, #0x55

/* Configure and Enable PLL */
        mov     r3, #PLLCFG_Val
        str     r3, [r0, #PLLCFG_OFS]
        mov     r3, #PLLCON_PLLE
        str     r3, [r0, #PLLCON_OFS]
        str     r1, [r0, #PLLFEED_OFS]
        str     r2, [r0, #PLLFEED_OFS]

/*  Wait until PLL Locked */
PLL_Locked_loop:
        ldr     r3, [r0, #PLLSTAT_OFS]
        ands    r3, r3, #PLLSTAT_PLOCK
        beq     PLL_Locked_loop

/*  Switch to PLL Clock */
        mov     r3, #(PLLCON_PLLE|PLLCON_PLLC)
        str     r3, [r0, #PLLCON_OFS]
        str     r1, [r0, #PLLFEED_OFS]
        str     R2, [r0, #PLLFEED_OFS]
/************************* PLL_SETUP **********************************/

/************************ Setup VPBDIV ********************************/
        ldr     r0, =VPBDIV
        ldr     r1, =VPBDIV_VALUE
        str     r1, [r0]
/************************ Setup VPBDIV ********************************/

/************** Setup MAM **************/
        ldr     r0, =MAM_BASE
        mov     r1, #MAMTIM_Val
        str     r1, [r0, #MAMTIM_OFS]
        mov     r1, #MAMCR_Val
        str     r1, [r0, #MAMCR_OFS]
/************** Setup MAM **************/

/************************ setup stack *********************************/
    ldr   r0, .undefined_stack_top
    sub   r0, r0, #4
    msr   CPSR_c, #MODE_UND|I_BIT|F_BIT /* Undefined Instruction Mode */
    mov   sp, r0

    ldr   r0, .abort_stack_top
    sub   r0, r0, #4
    msr   CPSR_c, #MODE_ABT|I_BIT|F_BIT /* Abort Mode */
    mov   sp, r0

    ldr   r0, .fiq_stack_top
    sub   r0, r0, #4
    msr   CPSR_c, #MODE_FIQ|I_BIT|F_BIT /* FIQ Mode */
    mov   sp, r0

    ldr   r0, .irq_stack_top
    sub   r0, r0, #4
    msr   CPSR_c, #MODE_IRQ|I_BIT|F_BIT /* IRQ Mode */
    mov   sp, r0

    ldr   r0, .svc_stack_top
    sub   r0, r0, #4
    msr   CPSR_c, #MODE_SVC|I_BIT|F_BIT  /* Supervisor Mode */
    mov   sp, r0
/************************ setup stack ********************************/

    /* copy .data to SRAM */
    ldr     r1, =_sidata            /* .data start in image */
    ldr     r2, =_edata             /* .data end in image   */
    ldr     r3, =_sdata             /* sram data start      */
data_loop:
    ldr     r0, [r1, #0]
    str     r0, [r3]

    add     r1, r1, #4
    add     r3, r3, #4

    cmp     r3, r2                   /* check if data to clear */
    blo     data_loop                /* loop until done        */

    /* clear .bss */
    mov     r0,#0                   /* get a zero */
    ldr     r1,=__bss_start         /* bss start  */
    ldr     r2,=__bss_end           /* bss end    */

bss_loop:
    cmp     r1,r2                   /* check if data to clear */
    strlo   r0,[r1],#4              /* clear 4 bytes          */
    blo     bss_loop                /* loop until done        */


    /* call C++ constructors of global objects */
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

    /* enter C code */
    bl      main

    .align 0
    .undefined_stack_top:
    .word   _undefined_stack_top
    .abort_stack_top:
    .word   _abort_stack_top
    .fiq_stack_top:
    .word   _fiq_stack_top
    .irq_stack_top:
    .word   _irq_stack_top
    .svc_stack_top:
    .word   _svc_stack_top
/*********************** END Clear BSS  ******************************/

.section .init,"ax"
.code 32
.align 0
.globl _start
_start:

    ldr   pc, __start                   /* reset - _start           */
    ldr   pc, _undf                     /* undefined - _undf        */
    ldr   pc, _swi                      /* SWI - _swi               */
    ldr   pc, _pabt                     /* program abort - _pabt    */
    ldr   pc, _dabt                     /* data abort - _dabt       */
    .word 0xB8A06F58                    /* reserved                 */
    ldr   pc, __IRQ_Handler             /* IRQ - read the VIC       */
    ldr   pc, _fiq                      /* FIQ - _fiq               */

__start:.word _reset
_undf:  .word __undf                    /* undefined                */
_swi:   .word __swi                     /* SWI                      */
_pabt:  .word __pabt                    /* program abort            */
_dabt:  .word __dabt                    /* data abort               */
temp1:  .word 0
__IRQ_Handler:  .word IRQ_Handler
_fiq:   .word __fiq                     /* FIQ                      */

__undf: b     .                         /* undefined                */
__swi : b     .
__pabt: b     .                         /* program abort            */
__dabt: b     .                         /* data abort               */
__fiq : b     .                         /* FIQ                      */

/* IRQ入口 */
IRQ_Handler :
        stmfd   sp!, {r0-r12,lr}               /* 对R0 – R12，LR寄存器压栈      */
        bl  rt_interrupt_enter                 /* 通知RT-Thread进入中断模式     */
        bl  rt_hw_trap_irq                     /* 相应中断服务例程处理        */
        bl  rt_interrupt_leave                 /* ; 通知RT-Thread要离开中断模式 */

        /* 如果设置了rt_thread_switch_interrupt_flag，进行中断中的线程上下文处理 */
        ldr r0, =rt_thread_switch_interrupt_flag
        ldr r1, [r0]
        cmp r1, #1
        beq rt_hw_context_switch_interrupt_do  /* 中断中切换发生 */
                                               /* 如果跳转了，将不会回来 */
        ldmfd   sp!, {r0-r12,lr}               /* 恢复栈 */
        subs    pc, lr, #4                     /* 从IRQ中返回 */

/*
* void rt_hw_context_switch_interrupt_do(rt_base_t flag)
* 中断结束后的上下文切换
*/
rt_hw_context_switch_interrupt_do:
                mov r1,  #0             /* clear flag */
                                        /* 清楚中断中切换标志 */
                str r1,  [r0]           /* */

                ldmfd   sp!, {r0-r12,lr}/* reload saved registers */
                                        /* 先恢复被中断线程的上下文 */
                stmfd   sp!, {r0-r3}    /* save r0-r3 */
                                        /* 对R0 – R3压栈，因为后面会用到 */
                mov r1,  sp             /* 把此处的栈值保存到R1 */
                add sp,  sp, #16        /* restore sp */
                                        /* 恢复IRQ的栈，后面会跳出IRQ模式 */
                sub r2,  lr, #4         /* save old task's pc to r2 */
                                        /* 保存切换出线程的PC到R2 */

                mrs r3,  spsr           /* disable interrupt 保存中断前的CPSR到R3寄存器 */
                                        /* 获得SPSR寄存器值 */
                orr r0,  r3, #I_BIT|F_BIT
                msr spsr_c, r0          /*  关闭SPSR中的IRQ/FIQ中断 */

                ldr r0,  =.+8           /* 把当前地址+8载入到R0寄存器中 switch to interrupted task's stack */
                movs pc,  r0            /* 退出IRQ模式，由于SPSR被设置成关中断模式 */
                                        /* 所以从IRQ返回后，中断并没有打开
                                        ; R0寄存器中的位置实际就是下一条指令，
                                        ; 即PC继续往下走
                                        ; 此时
                                        ; 模式已经换成中断前的SVC模式，
                                        ; SP寄存器也是SVC模式下的栈寄存器
                                        ; R1保存IRQ模式下的栈指针
                                        ; R2保存切换出线程的PC
                                        ; R3保存切换出线程的CPSR */
                stmfd   sp!, {r2}       /* push old task's pc */
                                        /* 保存切换出任务的PC */
                stmfd   sp!, {r4-r12,lr}/* push old task's lr,r12-r4 */
                                        /* 保存R4 – R12，LR寄存器 */
                mov r4,  r1             /* Special optimised code below */
                                        /* R1保存有压栈R0 – R3处的栈位置 */
                mov r5,  r3             /* R3切换出线程的CPSR */
                ldmfd   r4!, {r0-r3}    /* 恢复R0 – R3 */
                stmfd   sp!, {r0-r3}    /* push old task's r3-r0 */
                                        /*  R0 – R3压栈到切换出线程 */
                stmfd   sp!, {r5}       /* push old task's psr */
                                        /* 切换出线程CPSR压栈 */
                mrs r4,  spsr
                stmfd   sp!, {r4}       /* push old task's spsr */
                                        /* 切换出线程SPSR压栈 */

                ldr r4,  =rt_interrupt_from_thread
                ldr r5,  [r4]
                str sp,  [r5]           /* store sp in preempted tasks's TCB */
                                        /* 保存切换出线程的SP指针 */

                ldr r6,  =rt_interrupt_to_thread
                ldr r6,  [r6]
                ldr sp,  [r6]           /* get new task's stack pointer */
                                        /* 获得切换到线程的栈 */

                ldmfd   sp!, {r4}       /* pop new task's spsr */
                                        /* 恢复SPSR */
                msr SPSR_cxsf, r4
                ldmfd   sp!, {r4}       /* pop new task's psr */
                                        /* 恢复CPSR */
                msr CPSR_cxsf, r4

                ldmfd   sp!, {r0-r12,lr,pc} /* pop new task's r0-r12,lr & pc */
                                            /* 恢复R0 – R12，LR及PC寄存器 */

/* 代码加密功能 */
#if defined(CODE_PROTECTION)
.org 0x01FC
.word 0x87654321
#endif

