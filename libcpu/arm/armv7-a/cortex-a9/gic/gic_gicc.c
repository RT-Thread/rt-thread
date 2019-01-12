/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "gic_gicc.h"
#include <rtthread.h>
#include <cp15.h>
#include <bitopr.h>

GICC* gicc_get(void)
{
    static GICC* s_gicc_base = 0;
    if (s_gicc_base == 0) {
        if (armv7_get_cortex_type() == CORTEX_TYPE_A9) {
            // [ref]cortex_a9_mpcore_trm_100486_0401_10_en.pdf: 1.5 Private Memory Region
            //      0x0100 - 0x01FF Interrupt controller interfaces
            s_gicc_base = (GICC*)(rt_cpu_cbar_get() + 0x0100);
        }
        else {
            RT_ASSERT(false);
        }
    }
    return s_gicc_base;
}

GIC_IRQ gicc_irq_get(void)
{
    // GICC_IAR
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.4.4 Interrupt Acknowledge Register, GICC_IAR
    //      Bit     Field               Description
    //      31-13   reverse
    //      12-10   CPUID               For SGIs in a multiprocessor implementation, this field identifies the processor that requested the interrupt.
    //                                  It returns the number of the CPU interface that made the request.
    //      9-0     Interrupt ID        The interrupt ID.
    GICC* gicc = gicc_get();
    return gicc->IAR;
}

void gicc_irq_clr(GIC_IRQ irqIdx)
{
    // GICC_EOIR
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.4.5 End of Interrupt Register, GICC_EOIR
    //      Bit     Field               Description
    //      31-13   reverse
    //      12-10   CPUID               On a multiprocessor implementation, if the write refers to an SGI, this field contains
    //                                  the CPUID value from the corresponding GICC_IAR access.
    //      9-0     EOIINTID            The Interrupt ID value from the corresponding GICC_IAR access.
    GICC* gicc = gicc_get();
    gicc->EOIR = irqIdx;
}

void gicc_init(void)
{
    GICC* gicc = gicc_get();

    // GICC_CTLR
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.4.1 CPU Interface Control Register, GICC_CTLR
    //      Bit     Field               Description
    //      31-10   reverse
    //      10      EOImodeNS           Alias of EOImodeNS from the Non-secure copy of this register
    //      9       EOImodeS            Controls the behavior of accesses to GICC_EOIR and GICC_DIR registers
    //      8       IRQBypDisGrp1       Alias of IRQBypDisGrp1 from the Non-secure copy of this register
    //      7       FIQBypDisGrp1       Alias of FIQBypDisGrp1 from the Non-secure copy of this register
    //      6       IRQBypDisGrp0       When the signaling of IRQs by the CPU interface is disabled, 
    //                                  this bit partly controls whether the bypass IRQ signal is signaled to the processor
    //                                  0 = Bypass IRQ signal is signaled to the processor
    //                                  1 = Bypass IRQ signal is not signaled to the processor.
    //      5       FIQBypDisGrp0       When the signaling of FIQs by the CPU interface is disabled, 
    //                                  this bit partly controls whether the bypass FIQ signal is signaled to the processor
    //                                  0 = Bypass FIQ signal is signaled to the processor
    //                                  1 = Bypass FIQ signal is not signaled to the processor.
    //      4       CBPR                Controls whether the GICC_BPR provides common control to Group 0 and Group 1 interrupts
    //      3       FIQEn               0/1 = Signal Group 0 interrupts using the IRQ/FIQ signal.
    //                                  The GIC always signals Group 1 interrupts using the IRQ signal.
    //      2       AckCtl              0/1 = If the highest priority pending interrupt is a Group 1 interrupt, a read of the GICC_IAR
    //                                        or the GICC_HPPIR returns an Interrupt ID of 1022/the Interrupt ID of the Group 1 interrupt.
    //      1       EnableGrp1          0/1 = Disable/Enable signaling of Group 1 interrupts.
    //      0       EnableGrp0          0/1 = Disable/Enable signaling of Group 0 interrupts.
    gicc->CTLR = 0; // Set the default value of 0

    // GICC_PMR
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.4.2 Interrupt Priority Mask Register, GICC_PMR
    //      Bit     Field               Description
    //      31-8    reverse
    //      7-0     Priority            The priority mask level for the CPU interface
    gicc->PMR = _B_B(7, 0);

    // GICC_BPR
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.4.3 Binary Point Register, GICC_BPR
    //      Bit     Field               Description
    //      31-3    reverse
    //      2-0     Binary point        The value of this field controls how the 8-bit interrupt priority field is split into a group priority field, 
    //                                  used to determine interrupt preemption, and a subpriority field
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 3.3.3 Priority grouping
    //      Binary point value      Group priority field        Subpriority field       Field with binary point
    //      0                       [7:1]                       [0]                     ggggggg.s
    //      1                       [7:2]                       [1:0]                   gggggg.ss
    //      2                       [7:3]                       [2:0]                   ggggg.sss
    //      3                       [7:4]                       [3:0]                   gggg.ssss
    //      4                       [7:5]                       [4:0]                   ggg.sssss
    //      5                       [7:6]                       [5:0]                   gg.ssssss
    //      6                       [7]                         [6:0]                   g.sssssss
    //      7                       No preemption               [7:0]                   .ssssssss
    gicc->BPR = _B_B(2, 0); // No preemption

    // Enable signaling the CPU.
    gicc->CTLR = _B(1)/*EnableGrp1*/ | _B(0)/*EnableGrp0*/;
}
