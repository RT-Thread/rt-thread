/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-09-15     QiuYi        The first version
 * 2006-10-09     Bernard      add rt_hw_context_switch_to implementation
 */

 /**
 * @addtogroup ia32
 */
/*@{*/

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
    pushfl                  /*pushed eflags*/
/*
 *  add by ssslady@gmail.com 2009-10-14
 *      When we return again the esp should no be change.
 *  The old code change the esp to esp-4 :-(.
 *  A protection fault maybe occure for img created by some compiler,eg.gcc in the fedor-11
 *      -------------------------------------------------------------------------
 *  entry           old code            new code
 *  EIP ->return esp    EIP             FLAGS ->return esp
 *  ...         FLAGS    ->retern esp       CS
 *              CS              EIP
 *              EIP
 */
    popl %eax   /*get flags*/
    popl %ebx   /*get eip*/
    pushl %eax  /*push flags*/
    push %cs    /*push cs*/
    pushl %ebx  /*push eip*/

/*-------------------------------------------------------------------
 */

    /*push %cs*/                /*push cs register*/
    /*pushl 0x8(%esp)*/         /*pushed eip register*/

    pushl $0                /*fill irqno*/
    push %ds                /*push ds register*/
    push %es                /*push es register*/
    pushal                  /*push eax,ecx,edx,ebx,esp,ebp,esp,edi registers*/

    /*movl 0x40(%esp), %eax*/   /*to thread TCB*/
    /*movl 0x3c(%esp), %ebx*/   /*from thread TCB*/
    movl 0x3c(%esp), %eax   /*to thread TCB*/
    movl 0x38(%esp), %ebx   /*from thread TCB*/

    movl %esp, (%ebx)       /*store esp in preempted tasks TCB*/
    movl (%eax), %esp       /*get new task stack pointer*/

    popal                   /*restore new task TCB*/
    pop %es
    pop %ds
    add $4,%esp             /*skip irqno*/
    iret

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    push %ebp
    movl %esp, %ebp

    movl 0x8(%ebp), %eax    /* to thread TCB */
    movl (%eax), %esp       /* get new task stack pointer */

    popal                   /* restore new task TCB*/
    pop %es
    pop %ds
    add $4, %esp            /* skip irqno */
    iret
