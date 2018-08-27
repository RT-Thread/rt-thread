/*
 * File      : interrupt.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard      first version
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define INT_IRQ     0x00
#define INT_FIQ     0x01

#define INTC_REVISION(hw_base) 		    REG32((hw_base) + 0x0)
#define INTC_SYSCONFIG(hw_base) 		REG32((hw_base) + 0x10)
#define INTC_SYSSTATUS(hw_base) 		REG32((hw_base) + 0x14)
#define INTC_SIR_IRQ(hw_base) 		    REG32((hw_base) + 0x40)
#define INTC_SIR_FIQ(hw_base) 		    REG32((hw_base) + 0x44)
#define INTC_CONTROL(hw_base) 		    REG32((hw_base) + 0x48)
#define INTC_PROTECTION(hw_base) 	    REG32((hw_base) + 0x4c)
#define INTC_IDLE(hw_base)  			REG32((hw_base) + 0x50)
#define INTC_IRQ_PRIORITY(hw_base) 	    REG32((hw_base) + 0x60)
#define INTC_FIQ_PRIORITY(hw_base) 	    REG32((hw_base) + 0x64)
#define INTC_THRESHOLD(hw_base) 		REG32((hw_base) + 0x68)
#define INTC_SICR(hw_base)  			REG32((hw_base) + 0x6c)
#define INTC_SCR(hw_base, n) 		    REG32((hw_base) + 0x70 + ((n) * 0x04))
#define INTC_ITR(hw_base, n) 		    REG32((hw_base) + 0x80 + ((n) * 0x20))
#define INTC_MIR(hw_base, n) 		    REG32((hw_base) + 0x84 + ((n) * 0x20))
#define INTC_MIR_CLEAR(hw_base, n)  	REG32((hw_base) + 0x88 + ((n) * 0x20))
#define INTC_MIR_SET(hw_base, n) 	    REG32((hw_base) + 0x8c + ((n) * 0x20))
#define INTC_ISR_SET(hw_base, n) 	    REG32((hw_base) + 0x90 + ((n) * 0x20))
#define INTC_ISR_CLEAR(hw_base, n) 	    REG32((hw_base) + 0x94 + ((n) * 0x20))
#define INTC_PENDING_IRQ(hw_base, n)    REG32((hw_base) + 0x98 + ((n) * 0x20))
#define INTC_PENDING_FIQ(hw_base, n)    REG32((hw_base) + 0x9c + ((n) * 0x20))
#define INTC_ILR(hw_base, n)  		    REG32((hw_base) + 0x100 + ((n) * 0x04))

void rt_hw_interrupt_control(int vector, int priority, int route);
int rt_hw_interrupt_get_active(int fiq_irq);
void rt_hw_interrupt_ack(int fiq_irq);
void rt_hw_interrupt_trigger(int vector);
void rt_hw_interrupt_clear(int vector);

#endif
