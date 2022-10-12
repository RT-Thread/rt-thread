/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard      first version
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define INT_IRQ     0x00
#define INT_FIQ     0x01

/*************************************************************************\
 * Registers Definition
\*************************************************************************/
#define INTC_REVISION(hw_base)          REG32((hw_base) + 0x0)
#define INTC_SYSCONFIG(hw_base)         REG32((hw_base) + 0x10)
#define INTC_SYSSTATUS(hw_base)         REG32((hw_base) + 0x14)
#define INTC_SIR_IRQ(hw_base)           REG32((hw_base) + 0x40)
#define INTC_SIR_FIQ(hw_base)           REG32((hw_base) + 0x44)
#define INTC_CONTROL(hw_base)           REG32((hw_base) + 0x48)
#define INTC_PROTECTION(hw_base)        REG32((hw_base) + 0x4c)
#define INTC_IDLE(hw_base)              REG32((hw_base) + 0x50)
#define INTC_IRQ_PRIORITY(hw_base)      REG32((hw_base) + 0x60)
#define INTC_FIQ_PRIORITY(hw_base)      REG32((hw_base) + 0x64)
#define INTC_THRESHOLD(hw_base)         REG32((hw_base) + 0x68)
#define INTC_SICR(hw_base)              REG32((hw_base) + 0x6c)
#define INTC_SCR(hw_base, n)            REG32((hw_base) + 0x70 + ((n) * 0x04))
#define INTC_ITR(hw_base, n)            REG32((hw_base) + 0x80 + ((n) * 0x20))
#define INTC_MIR(hw_base, n)            REG32((hw_base) + 0x84 + ((n) * 0x20))
#define INTC_MIR_CLEAR(hw_base, n)      REG32((hw_base) + 0x88 + ((n) * 0x20))
#define INTC_MIR_SET(hw_base, n)        REG32((hw_base) + 0x8c + ((n) * 0x20))
#define INTC_ISR_SET(hw_base, n)        REG32((hw_base) + 0x90 + ((n) * 0x20))
#define INTC_ISR_CLEAR(hw_base, n)      REG32((hw_base) + 0x94 + ((n) * 0x20))
#define INTC_PENDING_IRQ(hw_base, n)    REG32((hw_base) + 0x98 + ((n) * 0x20))
#define INTC_PENDING_FIQ(hw_base, n)    REG32((hw_base) + 0x9c + ((n) * 0x20))
#define INTC_ILR(hw_base, n)            REG32((hw_base) + 0x100 + ((n) * 0x04))

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* REVISION */
#define INTC_REVISION_REV    (0x000000FFu)
#define INTC_REVISION_REV_SHIFT  (0x00000000u)

/* SYSCONFIG */
#define INTC_SYSCONFIG_SOFTRESET    (0x00000002u)
#define INTC_SYSCONFIG_SOFTRESET_SHIFT  (0x00000001u)

#define INTC_SYSCONFIG_AUTOIDLE    (0x00000001u)
#define INTC_SYSCONFIG_AUTOIDLE_SHIFT  (0x00000000u)

/* SYSSTATUS */
#define INTC_SYSSTATUS_RESETDONE    (0x00000001u)
#define INTC_SYSSTATUS_RESETDONE_SHIFT  (0x00000000u)

/* SIR_IRQ */
#define INTC_SIR_IRQ_SPURIOUSIRQ    (0xFFFFFF80u)
#define INTC_SIR_IRQ_SPURIOUSIRQ_SHIFT  (0x00000007u)

#define INTC_SIR_IRQ_ACTIVEIRQ    (0x0000007F)
#define INTC_SIR_IRQ_ACTIVEIRQ_SHIFT  (0x00000000)

/* SIR_FIQ */
#define INTC_SIR_FIQ_SPURIOUSFIQ    (0xFFFFFF80)
#define INTC_SIR_FIQ_SPURIOUSFIQ_SHIFT  (0x00000007)

#define INTC_SIR_FIQ_ACTIVEFIQ    (0x0000007F)
#define INTC_SIR_FIQ_ACTIVEFIQ_SHIFT  (0x00000000)

/* CONTROL */
#define INTC_CONTROL_NEWFIQAGR    (0x00000002)
#define INTC_CONTROL_NEWFIQAGR_SHIFT  (0x00000001)

#define INTC_CONTROL_NEWIRQAGR    (0x00000001)
#define INTC_CONTROL_NEWIRQAGR_SHIFT  (0x00000000)

/* PROTECTION */
#define INTC_PROTECTION_PROTECTION    (0x00000001u)
#define INTC_PROTECTION_PROTECTION_SHIFT  (0x00000000u)

/* IDLE */
#define INTC_IDLE_TURBO    (0x00000002u)
#define INTC_IDLE_TURBO_SHIFT  (0x00000001u)

#define INTC_IDLE_FUNCIDLE    (0x00000001u)
#define INTC_IDLE_FUNCIDLE_SHIFT  (0x00000000u)

/* IRQ_PRIORITY */
#define INTC_IRQ_PRIORITY_SPURIOUSIRQFLAG    (0xFFFFFFC0u)
#define INTC_IRQ_PRIORITY_SPURIOUSIRQFLAG_SHIFT  (0x00000006u)

#define INTC_IRQ_PRIORITY_IRQPRIORITY    (0x0000003Fu)
#define INTC_IRQ_PRIORITY_IRQPRIORITY_SHIFT  (0x00000000u)

/* FIQ_PRIORITY */
#define INTC_FIQ_PRIORITY_SPURIOUSFIQFLAG    (0xFFFFFFC0u)
#define INTC_FIQ_PRIORITY_SPURIOUSFIQFLAG_SHIFT  (0x00000006u)

#define INTC_FIQ_PRIORITY_FIQPRIORITY    (0x0000003Fu)
#define INTC_FIQ_PRIORITY_FIQPRIORITY_SHIFT  (0x00000000u)

/* THRESHOLD */
#define INTC_THRESHOLD_PRIORITYTHRESHOLD    (0x000000FFu)
#define INTC_THRESHOLD_PRIORITYTHRESHOLD_SHIFT  (0x00000000u)

/* SICR */
#define INTC_SICR_GLOBALMASK    (0x00000040u)
#define INTC_SICR_GLOBALMASK_SHIFT  (0x00000006u)

#define INTC_SICR_SOFTRESETINH    (0x00000020u)
#define INTC_SICR_SOFTRESETINH_SHIFT  (0x00000005u)

#define INTC_SICR_PUBLICMASKFEEDBACK    (0x00000010u)
#define INTC_SICR_PUBLICMASKFEEDBACK_SHIFT  (0x00000004u)

#define INTC_SICR_PUBLICINHIBIT    (0x00000008u)
#define INTC_SICR_PUBLICINHIBIT_SHIFT  (0x00000003u)

#define INTC_SICR_AUTOINHIBIT    (0x00000004u)
#define INTC_SICR_AUTOINHIBIT_SHIFT  (0x00000002u)

#define INTC_SICR_SSMFIQENABLE    (0x00000002u)
#define INTC_SICR_SSMFIQENABLE_SHIFT  (0x00000001u)

#define INTC_SICR_SSMFIQSTATUS    (0x00000001u)
#define INTC_SICR_SSMFIQSTATUS_SHIFT  (0x00000000u)

/* SCR0 */
#define INTC_SCR0_SECUREENABLE    (0xFFFFFFFFu)
#define INTC_SCR0_SECUREENABLE_SHIFT  (0x00000000u)

/* SCR1 */
#define INTC_SCR1_SECUREENABLE    (0xFFFFFFFFu)
#define INTC_SCR1_SECUREENABLE_SHIFT  (0x00000000u)

/* SCR2 */
#define INTC_SCR2_SECUREENABLE    (0xFFFFFFFFu)
#define INTC_SCR2_SECUREENABLE_SHIFT  (0x00000000u)

/* ITR0 */
#define INTC_ITR0_ITR    (0xFFFFFFFFu)
#define INTC_ITR0_ITR_SHIFT  (0x00000000u)

/* MIR0 */
#define INTC_MIR0_MIR    (0xFFFFFFFFu)
#define INTC_MIR0_MIR_SHIFT  (0x00000000u)

/* MIR_CLEAR0 */
#define INTC_MIR_CLEAR0_MIRCLEAR    (0xFFFFFFFFu)
#define INTC_MIR_CLEAR0_MIRCLEAR_SHIFT  (0x00000000u)

/* MIR_SET0 */
#define INTC_MIR_SET0_MIRSET    (0xFFFFFFFFu)
#define INTC_MIR_SET0_MIRSET_SHIFT  (0x00000000u)

/* ISR_SET0 */
#define INTC_ISR_SET0_ISRSET    (0xFFFFFFFFu)
#define INTC_ISR_SET0_ISRSET_SHIFT  (0x00000000u)

/* ISR_CLEAR0 */
#define INTC_ISR_CLEAR0_ISRCLEAR    (0xFFFFFFFFu)
#define INTC_ISR_CLEAR0_ISRCLEAR_SHIFT  (0x00000000u)

/* PENDING_IRQ0 */
#define INTC_PENDING_IRQ0_PENDING_IRQ    (0xFFFFFFFFu)
#define INTC_PENDING_IRQ0_PENDING_IRQ_SHIFT  (0x00000000u)

/* PENDING_FIQ0 */
#define INTC_PENDING_FIQ0_PENDING_FIQ    (0xFFFFFFFFu)
#define INTC_PENDING_FIQ0_PENDING_FIQ_SHIFT  (0x00000000u)

/* ITR1 */
#define INTC_ITR1_ITR    (0xFFFFFFFFu)
#define INTC_ITR1_ITR_SHIFT  (0x00000000u)

/* MIR1 */
#define INTC_MIR1_MIR    (0xFFFFFFFFu)
#define INTC_MIR1_MIR_SHIFT  (0x00000000u)

/* MIR_CLEAR1 */
#define INTC_MIR_CLEAR1_MIRCLEAR    (0xFFFFFFFFu)
#define INTC_MIR_CLEAR1_MIRCLEAR_SHIFT  (0x00000000u)

/* MIR_SET1 */
#define INTC_MIR_SET1_MIRSET    (0xFFFFFFFFu)
#define INTC_MIR_SET1_MIRSET_SHIFT  (0x00000000u)

/* ISR_SET1 */
#define INTC_ISR_SET1_ISRSET    (0xFFFFFFFFu)
#define INTC_ISR_SET1_ISRSET_SHIFT  (0x00000000u)

/* ISR_CLEAR1 */
#define INTC_ISR_CLEAR1_ISRCLEAR    (0xFFFFFFFFu)
#define INTC_ISR_CLEAR1_ISRCLEAR_SHIFT  (0x00000000u)

/* PENDING_IRQ1 */
#define INTC_PENDING_IRQ1_PENDING_IRQ    (0xFFFFFFFFu)
#define INTC_PENDING_IRQ1_PENDING_IRQ_SHIFT  (0x00000000u)

/* PENDING_FIQ1 */
#define INTC_PENDING_FIQ1_PENDING_FIQ    (0xFFFFFFFFu)
#define INTC_PENDING_FIQ1_PENDING_FIQ_SHIFT  (0x00000000u)

/* ITR2 */
#define INTC_ITR2_ITR    (0xFFFFFFFFu)
#define INTC_ITR2_ITR_SHIFT  (0x00000000u)

/* MIR2 */
#define INTC_MIR2_MIR    (0xFFFFFFFFu)
#define INTC_MIR2_MIR_SHIFT  (0x00000000u)

/* MIR_CLEAR2 */
#define INTC_MIR_CLEAR2_MIRCLEAR    (0xFFFFFFFFu)
#define INTC_MIR_CLEAR2_MIRCLEAR_SHIFT  (0x00000000u)

/* MIR_SET2 */
#define INTC_MIR_SET2_MIRSET    (0xFFFFFFFFu)
#define INTC_MIR_SET2_MIRSET_SHIFT  (0x00000000u)

/* ISR_SET2 */
#define INTC_ISR_SET2_ISRSET    (0xFFFFFFFFu)
#define INTC_ISR_SET2_ISRSET_SHIFT  (0x00000000u)

/* ISR_CLEAR2 */
#define INTC_ISR_CLEAR2_ISRCLEAR    (0xFFFFFFFFu)
#define INTC_ISR_CLEAR2_ISRCLEAR_SHIFT  (0x00000000u)

/* PENDING_IRQ2 */
#define INTC_PENDING_IRQ2_PENDING_IRQ    (0xFFFFFFFFu)
#define INTC_PENDING_IRQ2_PENDING_IRQ_SHIFT  (0x00000000u)

/* PENDING_FIQ2 */
#define INTC_PENDING_FIQ2_PENDING_FIQ    (0xFFFFFFFFu)
#define INTC_PENDING_FIQ2_PENDING_FIQ_SHIFT  (0x00000000u)

/* ILR */
#define INTC_ILR_PRIORITY    (0x000001FCu)
#define INTC_ILR_PRIORITY_SHIFT  (0x00000002u)

#define INTC_ILR_FIQNIRQ    (0x00000001u)
#define INTC_ILR_FIQNIRQ_SHIFT  (0x00000000u)

void rt_hw_interrupt_control(int vector, int priority, int route);
int rt_hw_interrupt_get_active(int fiq_irq);
void rt_hw_interrupt_ack(int fiq_irq);
void rt_hw_interrupt_trigger(int vector);
void rt_hw_interrupt_clear(int vector);

#endif
