/*
 * File      : contex_ck802.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-01-01     Urey      first version
 * 2018-06-05     tanek     clean code
 */

.file     "contex_ck802.S"

#undef  VIC_TSPDR
#define VIC_TSPDR 0XE000EC08

.global  rt_thread_switch_interrupt_flag
.global  rt_interrupt_from_thread
.global  rt_interrupt_to_thread

.text
.align 2

/*
 * rt_base_t rt_hw_interrupt_disable(void);
 */
.global rt_hw_interrupt_disable
.type   rt_hw_interrupt_disable, %function
rt_hw_interrupt_disable:
mfcr    r0, psr
psrclr  ie
rts

/*
 * void rt_hw_interrupt_enable(rt_base_t psr);
 */
.global rt_hw_interrupt_enable
.type   rt_hw_interrupt_enable, %function
rt_hw_interrupt_enable:
mtcr    r0, psr
rts

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * R0 --> to
 */
.global rt_hw_context_switch_to
.type rt_hw_context_switch_to, %function
rt_hw_context_switch_to:
lrw     r2, rt_interrupt_to_thread
stw     r0, (r2)

/* set form thread = 0 */
lrw     r2, rt_interrupt_from_thread
movi    r0, 0
stw     r0, (r2)

psrclr  ie
jbr     __tspend_handler_nosave

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 */
.global rt_hw_context_switch_interrupt
.type   rt_hw_context_switch_interrupt, %function
rt_hw_context_switch_interrupt:
lrw    r2, rt_interrupt_from_thread     /* set rt_interrupt_from_thread */
stw    r0, (r2)

lrw    r2, rt_interrupt_to_thread       /* set rt_interrupt_to_thread */
stw    r1, (r2)

lrw    r0, VIC_TSPDR
bgeni  r1, 0
stw    r1, (r0)
rts

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to)
 * r0 --> from
 * r1 --> to
 */
.global rt_hw_context_switch
.type   rt_hw_context_switch, %function
rt_hw_context_switch:
lrw    r2, rt_interrupt_from_thread     /* set rt_interrupt_from_thread */
stw    r0, (r2)

lrw    r2, rt_interrupt_to_thread       /* set rt_interrupt_to_thread */
stw    r1, (r2)

lrw    r0, VIC_TSPDR
bgeni  r1, 0
stw    r1, (r0)
rts

.global PendSV_Handler
.type   PendSV_Handler, %function
PendSV_Handler:
subi    sp, 68
stm     r0-r13, (sp)
stw     r15, (sp, 56)
mfcr    r0, epsr
stw     r0, (sp, 60)
mfcr    r0, epc
stw     r0, (sp, 64)

lrw     r0, rt_interrupt_from_thread
ldw     r1, (r0)
stw     sp, (r1)

__tspend_handler_nosave:
lrw     r6, rt_interrupt_to_thread
lrw     r7, rt_interrupt_from_thread
ldw     r8, (r6)
stw     r8, (r7)

ldw     sp, (r8)

#ifdef CONFIG_STACK_GUARD
mfcr    r3, cr<0, 4>
bseti   r3, 0
bseti   r3, 1
mtcr    r3, cr<0, 4>
#endif

ldw     r0, (sp, 64)
mtcr    r0, epc
ldw     r0, (sp, 60)
bseti   r0, 6
mtcr    r0, epsr
ldw     r15, (sp, 56)
ldm     r0-r13, (sp)
addi    sp, 68
rte

