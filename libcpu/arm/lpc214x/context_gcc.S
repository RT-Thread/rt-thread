/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
.global rt_hw_interrupt_disable
.global rt_hw_interrupt_enable
.global rt_hw_context_switch
.global rt_hw_context_switch_to
.global rt_hw_context_switch_interrupt

.equ  NOINT, 0xc0

/*
 * rt_base_t rt_hw_interrupt_disable();
 关闭中断，关闭前返回CPSR寄存器值
 */
rt_hw_interrupt_disable:
    //EXPORT rt_hw_interrupt_disable
    MRS r0, cpsr
    ORR r1, r0, #NOINT
    MSR cpsr_c, r1
    BX  lr
    //ENDP

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
  恢复中断状态
 */
rt_hw_interrupt_enable:
    //EXPORT rt_hw_interrupt_enable
    MSR cpsr_c, r0
    BX  lr
    //ENDP

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 进行线程的上下文切换
 */
rt_hw_context_switch:
    //EXPORT rt_hw_context_switch
    STMFD   sp!, {lr}           /* push pc (lr should be pushed in place of PC) */
                                /* 把LR寄存器压入栈（这个函数返回后的下一个执行处） */
    STMFD   sp!, {r0-r12, lr}   /* push lr & register file */
                                /*  把R0 – R12以及LR压入栈 */

    MRS     r4, cpsr            /*  读取CPSR寄存器到R4寄存器 */
    STMFD   sp!, {r4}           /* push cpsr */
                                /* 把R4寄存器压栈（即上一指令取出的CPSR寄存器） */
    MRS     r4, spsr            /* 读取SPSR寄存器到R4寄存器 */
    STMFD   sp!, {r4}           /* push spsr */
                                /* 把R4寄存器压栈（即SPSR寄存器） */

    STR sp, [r0]                /* store sp in preempted tasks TCB */
                                /*  把栈指针更新到TCB的sp，是由R0传入此函数 */
                                /*  到这里换出线程的上下文都保存在栈中 */
    LDR sp, [r1]                /* get new task stack pointer */
                                /*  载入切换到线程的TCB的sp */
                                /*  从切换到线程的栈中恢复上下文，次序和保存的时候刚好相反 */

    LDMFD   sp!, {r4}           /* pop new task spsr */
                                /* 出栈到R4寄存器（保存了SPSR寄存器） */
    MSR spsr_cxsf, r4           /* 恢复SPSR寄存器 */
    LDMFD   sp!, {r4}           /* pop new task cpsr */
                                /* 出栈到R4寄存器（保存了CPSR寄存器） */
    MSR cpsr_cxsf, r4           /*  恢复CPSR寄存器 */

    LDMFD   sp!, {r0-r12, lr, pc}   /* pop new task r0-r12, lr & pc */
                                    /* 对R0 – R12及LR、PC进行恢复 */
    //ENDP

rt_hw_context_switch_to:
    //EXPORT rt_hw_context_switch_to
    LDR sp, [r0]                /* get new task stack pointer */
                                /* 获得切换到线程的SP指针 */

    LDMFD   sp!, {r4}           /* pop new task spsr */
                                /* 出栈R4寄存器（保存了SPSR寄存器值） */
    MSR spsr_cxsf, r4           /* 恢复SPSR寄存器 */
    LDMFD   sp!, {r4}           /* pop new task cpsr */
                                /* 出栈R4寄存器（保存了CPSR寄存器值） */
    MSR cpsr_cxsf, r4           /* 恢复CPSR寄存器 */

    LDMFD   sp!, {r0-r12, lr, pc}   /* pop new task r0-r12, lr & pc */
                                    /* 恢复R0 – R12，LR及PC寄存器 */
    //ENDP

rt_hw_context_switch_interrupt:
    //EXPORT rt_hw_context_switch_interrupt
    LDR r2, =rt_thread_switch_interrupt_flag
    LDR r3, [r2]                        /* 载入中断中切换标致地址 */
    CMP r3, #1                          /* 等于 1 ？*/
    BEQ _reswitch                       /* 如果等于1，跳转到_reswitch*/
    MOV r3, #1                          /* set rt_thread_switch_interrupt_flag to 1*/
                                        /* 设置中断中切换标志位1 */
    STR r3, [r2]                        /* */
    LDR r2, =rt_interrupt_from_thread   /* set rt_interrupt_from_thread*/
    STR r0, [r2]                        /* 保存切换出线程栈指针*/
_reswitch:
    LDR r2, =rt_interrupt_to_thread     /* set rt_interrupt_to_thread*/
    STR r1, [r2]                        /* 保存切换到线程栈指针*/
    BX  lr
    //ENDP

    //END
