/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include <rthw.h>
#include <rtthread.h>
#include "interrupt.h"
#include "intc_reg.h"
#include <cp15.h>

#define MAX_HANDLERS	128

extern volatile uint8_t rt_interrupt_nest;
extern uint32_t system_vectors;

// exception and interrupt handler table
struct rt_irq_desc isr_table[MAX_HANDLERS];
uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
uint32_t rt_thread_switch_interrupt_flag;

// This function will initialize hardware interrupt
void rt_hw_interrupt_init(void)
{
    // [ref]spruh73p.pdf: spruh73p.pdf: 6.6.1.2 INTC_SYSCONFIG Register (offset = 10h) [reset = 0h]
    //      Bit     Field                   Default     Description
    //      31-2    Reserved                R-0h        
    //      1       SoftReset               R/W-0h      Software reset.Set this bit to trigger a module reset.
    //                                                  The bit is automatically reset by the hardware. During reads, it always returns 0.
    //                                                  0h(Read) = always_Always returns 0
    //                                                  1h(Read) = never_never happens
    //      0       Autoidle                R/W-0h      Internal OCP clock gating strategy
    //                                                  0h = clkfree : OCP clock is free running
    //                                                  1h = autoClkGate : Automatic OCP clock gating strategy is applied, bnased on the OCP interface activity
    INTC___S___(0x10, _B(1)/*SoftReset*/);

    // initialize vector table
    rt_cpu_vector_set_base((uint32_t)&system_vectors);

    // init exceptions table
    rt_memset(isr_table, 0x00, sizeof(isr_table));

    // init interrupt nest, and context in thread sp
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
}

#define IRQ_GEN(regIdx, idxInReg)           ((regIdx) * 32 + (idxInReg))
#define IRQ_SEP(irqId, regIdx, idxInReg)    (regIdx) = (irqId) >> 5, (idxInReg) = (irqId) & 0x1F

// This function will mask a interrupt.
// @param vector the interrupt number
void rt_hw_interrupt_mask(int vector)
{
    uint32_t regIdx;
    uint32_t idxInReg;
    IRQ_SEP(vector, regIdx, idxInReg);

    // [ref]spruh73p.pdf: 
    //      6.6.1.15 INTC_MIR_SET0 Register (offset = 8Ch) [reset = 0h]
    //      6.6.1.23 INTC_MIR_SET1 Register (offset = ACh) [reset = 0h]
    //      6.6.1.31 INTC_MIR_SET2 Register (offset = CCh) [reset = 0h]
    //      6.6.1.39 INTC_MIR_SET3 Register (offset = ECh) [reset = 0h]
    //      Bit     Field                   Default     Description
    //      31-0    MirSet                  W-X         Write 1 sets the mask bit to 1, reads return 0
    RT_ASSERT(regIdx < 4);
    INTC___S___(0x8C + 0x20 * regIdx, _B(idxInReg));
}

// This function will un-mask a interrupt.
// @param vector the interrupt number
void rt_hw_interrupt_umask(int vector)
{
    RT_ASSERT((vector >= 0) && (vector < MAX_HANDLERS));
    uint32_t regIdx;
    uint32_t idxInReg;
    IRQ_SEP(vector, regIdx, idxInReg);

    // [ref]spruh73p.pdf: 
    //      6.6.1.14 INTC_MIR_CLEAR0 Register (offset = 88h) [reset = 0h]
    //      6.6.1.22 INTC_MIR_CLEAR1 Register (offset = A8h) [reset = 0h]
    //      6.6.1.30 INTC_MIR_CLEAR2 Register (offset = C8h) [reset = 0h]
    //      6.6.1.38 INTC_MIR_CLEAR3 Register (offset = E8h) [reset = 0h]
    //      Bit     Field                   Default     Description
    //      31-0    MirClear                W-X         Write 1 clears the mask bit to 0, reads return 0
    INTC___S___(0x88 + 0x20 * regIdx, _B(idxInReg));
}

// This function will control the interrupt attribute.
// @param vector the interrupt number
// @param priority Interrupt priority
// @param route 0/1 = irq/fiq
void rt_hw_interrupt_control(int32_t vector, int32_t priority, int32_t route)
{
    RT_ASSERT((vector >= 0) && (vector < MAX_HANDLERS));
    RT_ASSERT((priority >= 0) && (priority <= _MB(7 - 2)));
    // [ref]spruh73p.pdf: 6.6.1.44 INTC_ILR_0 to INTC_ILR_127 Register (offset = 100h to 2FCh) [reset = 0h]
    //      Bit     Field                   Default     Description
    //      31-8    reverse
    //      7-2     Priority                R/W-0h      Interrupt priority
    //      1       reverse
    //      0       FIQnIRQ                 R/W-0h      0h = IntIRQ: Interrupt is routed to IRQ.
    //                                                  1h = IntFIQ: Interrupt is routed to FIQ (this selection is reserved on GP devices).
    INTC___S___(0x100 + 0x4 * vector, _L(priority, 2) | (route ? 1 : 0));
}

uint32_t rt_hw_interrupt_irq_get(void)
{
    // [ref]spruh73p.pdf: 6.6.1.4 INTC_SIR_IRQ Register (offset = 40h) [reset = FFFFFF80h]
    //      Bit     Field                   Default     Description
    //      31-7    SpuriousIRQ             R-1FFFFFFh  Spurious IRQ flag
    //      6-0     ActiveIRQ               R-0h        Active IRQ number
    return INTC_M_G___(0x40, _B_B(6, 0));
}

uint32_t rt_hw_interrupt_fiq_get(void)
{
    // [ref]spruh73p.pdf: 6.6.1.5 INTC_SIR_FIQ Register (offset = 44h) [reset = FFFFFF80h]
    //      Bit     Field                   Default     Description
    //      31-7    SpuriousFIQ             R-1FFFFFFh  Spurious FIQ flag
    //      6-0     ActiveFIQ               R-0h        Active FIQ number
    return INTC_M_G___(0x44, _B_B(6, 0));
}

// new interrupt agreement
// @param isFiq true/false = fiq/irq
rt_inline void new_interrupt_agreement(bool isFiq)
{
    // [ref]spruh73p.pdf: 6.6.1.6 INTC_CONTROL Register (offset = 48h) [reset = 0h]
    //      Bit     Field                   Default     Description
    //      31-2    reverse
    //      1       NewFIQAgr               R-0h        Reset FIQ output and enable new FIQ generation
    //                                                  0h(Write) = nofun_no function effect
    //                                                  1h(Write) = NewFiq_Reset FIQ output and enable new FIQ generation
    //      0       NewIRQAgr               R-0h        Reset IRQ output and enable new IRQ generation
    //                                                  0h(Write) = nofun_no function effect
    //                                                  1h(Write) = NewIrq_Reset IRQ output and enable new IRQ generation
    INTC___S___(0x48, isFiq ? _B(1) : _B(0));
}

void rt_hw_interrupt_irq_clr(void)
{
    new_interrupt_agreement(false);
}

void rt_hw_interrupt_fiq_clr(void)
{
    new_interrupt_agreement(true);
}


// This function will install a interrupt service routine to a interrupt.
// @param vector the interrupt number
// @param handler new handler
// @param param parameter
// @param name name
// @return old handler
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler, void *param, const char *name)
{
    rt_isr_handler_t old_handler = NULL;

    if(vector < MAX_HANDLERS) {
        old_handler = isr_table[vector].handler;

        if (handler != NULL) {
#ifdef RT_USING_INTERRUPT_INFO
            rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif
            isr_table[vector].handler = handler;
            isr_table[vector].param = param;
        }
    }

    return old_handler;
}

// This function will trigger an interrupt.
// @param vector the interrupt number
void rt_hw_interrupt_trigger(int32_t vector)
{
    RT_ASSERT((vector >= 0) && (vector < MAX_HANDLERS));
    uint32_t regIdx;
    uint32_t idxInReg;
    IRQ_SEP(vector, regIdx, idxInReg);

    // [ref]spruh73p.pdf: 
    //      6.6.1.16 INTC_ISR_SET0 Register (offset = 90h) [reset = 0h]
    //      6.6.1.24 INTC_ISR_SET1 Register (offset = B0h) [reset = 0h]
    //      6.6.1.32 INTC_ISR_SET2 Register (offset = D0h) [reset = 0h]
    //      6.6.1.40 INTC_ISR_SET3 Register (offset = F0h) [reset = 0h]
    //      Bit     Field                   Default     Description
    //      31-0    IsrSet                  R/W-0h      Reads returns the currently active software interrupts, 
    //                                                  Write 1 sets the software interrupt bits to 1
    INTC___S___(0x90 + 0x20 * regIdx, _B(idxInReg));
}

// clear interrupt
// @param vector the interrupt number
void rt_hw_interrupt_clear(int32_t vector)
{
    RT_ASSERT((vector >= 0) && (vector < MAX_HANDLERS));
    uint32_t regIdx;
    uint32_t idxInReg;
    IRQ_SEP(vector, regIdx, idxInReg);

    // [ref]spruh73p.pdf: 
    //      6.6.1.17 INTC_ISR_CLEAR0 Register (offset = 94h) [reset = 0h]
    //      6.6.1.25 INTC_ISR_CLEAR1 Register (offset = B4h) [reset = 0h]
    //      6.6.1.33 INTC_ISR_CLEAR2 Register (offset = D4h) [reset = 0h]
    //      6.6.1.41 INTC_ISR_CLEAR3 Register (offset = F4h) [reset = 0h]
    //      Bit     Field                   Default     Description
    //      31-0    IsrClear                W-X         Write 1 clears the software interrupt bits to 0, reads return 0
    INTC___S___(0x94 + 0x20 * regIdx, _B(idxInReg));
}
