/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#include "gic_gicd.h"
#include "gic_gicc.h"
#include <rtthread.h>
#include <cp15.h>
#include <bitopr.h>

GICD* gicd_get(void)
{
    static GICD* s_gicd_base = 0;
    if (s_gicd_base == 0) {
        if (armv7_get_cortex_type() == CORTEX_TYPE_A9) {
            // [ref]cortex_a9_mpcore_trm_100486_0401_10_en.pdf: 1.5 Private Memory Region
            //      0x1000 - 0x1FFF Interrupt Distributor
            s_gicd_base = (GICD*)(rt_cpu_cbar_get() + 0x1000);
        }
        else {
            RT_ASSERT(false);
        }
    }
    return s_gicd_base;
}

#define IRQ_GEN(regIdx, idxInReg)           ((regIdx) * 32 + (idxInReg))
#define IRQ_SEP(irqId, regIdx, idxInReg)    (regIdx) = (irqId) >> 5, (idxInReg) = (irqId) & 0x1F

void _gicd_irq_ctrl(uint32_t irqId, uint32_t cpuId, bool isEn, bool isSecure, uint32_t priority)
{
    GICD* gicd = gicd_get();

    RT_ASSERT(irqId < GIC_INTID_LIMIT);
    uint32_t regIdx;
    uint32_t idxInReg;
    IRQ_SEP(irqId, regIdx, idxInReg);

    if (isEn) {
        // GICD_IGROUPR
        // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.4 Interrupt Group Registers, GICD_IGROUPRn
        //      Bit     Field               Description
        //      31-0    Group status bits   For each bit:
        //                                  0 = The corresponding interrupt is Group 0.
        //                                  1 = The corresponding interrupt is Group 1.
        if (!isSecure)
            gicd->IGROUPRn[regIdx] &= ~_B(idxInReg);
        else
            gicd->IGROUPRn[regIdx] |= _B(idxInReg);

        // GICD_IPRIORITYR
        // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.11 Interrupt Priority Registers, GICD_IPRIORITYRn
        //      The GICD_IPRIORITYRs provide an 8-bit priority field for each interrupt supported by the GIC.
        //      This field stores the priority of the corresponding interrupt.
        //      These registers are byte-accessible
        RT_ASSERT(priority <= 0xFF);
        gicd->IPRIORITYRn[irqId] = priority;
    }

    if (irqId >= 32) { // SPI
        // GICD_ITARGETSR
        // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.12 Interrupt Processor Targets Registers, GICD_ITARGETSRn
        //      TThe GICD_ITARGETSRs provide an 8-bit CPU targets field for each interrupt supported by the GIC.
        //      This field stores the list of target processors for the interrupt.
        //      That is, it holds the list of CPU interfaces to which the Distributor forwards the interrupt if it is asserted and has sufficient priority.
        RT_ASSERT(cpuId <= gicd->TYPER.CPUNumber);
        if (isEn)
            gicd->ITARGETSRn[irqId] |= _B(cpuId);
        else
            gicd->ITARGETSRn[irqId] &= ~_B(cpuId);
    }

    if (irqId >= 16) { // PPI/SPI
        // GICD_ISENABLER
        // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.5 Interrupt Set-Enable Registers, GICD_ISENABLERn
        //      Bit     Field               Description
        //      31-0    Set-enable bits     For SPIs and PPIs, each bit controls the forwarding of the corresponding interrupt from the 
        //                                  Distributor to the CPU interfaces :
        //                                  [Reads] 0 = Forwarding of the corresponding interrupt is disabled.
        //                                          1 = Forwarding of the corresponding interrupt is enabled.
        //                                  [Writes]0 = Has no effect.
        //                                          1 = Enables the forwarding of the corresponding interrupt.
        //                                              After a write of 1 to a bit, a subsequent read of the bit returns the value 1.
        // GICD_ICENABLER
        // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.6 Interrupt Clear-Enable Registers, GICD_ICENABLERn
        //      Bit     Field               Description
        //      31-0    Clear-enable bits   For SPIs and PPIs, each bit controls the forwarding of the corresponding interrupt from the 
        //                                  Distributor to the CPU interfaces :
        //                                  [Reads] 0 = Forwarding of the corresponding interrupt is disabled.
        //                                          1 = Forwarding of the corresponding interrupt is enabled.
        //                                  [Writes]0 = Has no effect.
        //                                          1 = Disables the forwarding of the corresponding interrupt.
        //                                              After a write of 1 to a bit, a subsequent read of the bit returns the value 0.
        if (isEn)
            gicd->ISENABLERn[regIdx] = _B(idxInReg);
        else
            gicd->ICENABLERn[regIdx] = _B(idxInReg);
    }
}

void gicd_irq_enable(uint32_t irqId, uint32_t cpuId, bool isSecure, uint32_t priority)
{
    _gicd_irq_ctrl(irqId, cpuId, true, isSecure, priority);
}

void gicd_irq_disable(uint32_t irqId, uint32_t cpuId)
{
    _gicd_irq_ctrl(irqId, cpuId, false, false, 0);
}

void gicd_sgi_gen(uint32_t irqId, GICD_FILTER targetListFilter, uint32_t cpuTagetList)
{
    GICD* gicd = gicd_get();
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 2.2.1 Interrupt IDs
    //      ID0-ID15 are used for SGIs
    RT_ASSERT(irqId <= _B_B(3, 0));
    RT_ASSERT(cpuTagetList <= _B_B(gicd->TYPER.CPUNumber, 0));
    RT_ASSERT(targetListFilter <= _B_B(25 - 24, 0));

    // GICD_SGIR
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.15 Software Generated Interrupt Register, GICD_SGIR
    //      Bit     Field               Description
    //      31-26   reverse
    //      25-24   TargetListFilter    Determines how the distributor must process the requested SGI:
    //                                  0b00 = Forward the interrupt to the CPU interfaces specified in the CPUTargetList field.
    //                                  0b01 = Forward the interrupt to all CPU interfaces except that of the processor that requested the interrupt.
    //                                  0b10 = Forward the interrupt only to the CPU interface of the processor that requested the interrupt.
    //                                  0b11 = Reserved.
    //      23-16   CPUTargetList       When TargetList Filter = 0b00, defines the CPU interfaces to which the Distributor must forward the interrupt.
    //                                  Each bit of CPUTargetList[7:0] refers to the corresponding CPU interface
    //      15      NSATT               Implemented only if the GIC includes the Security Extensions
    //                                  0/1 = Forward the SGI specified in the SGIINTID field to a specified CPU interface only 
    //                                        if the SGI is configured as Group 0/1 on that interface.
    //      14-4    reverse
    //      3-0     SGIINTID            The Interrupt ID of the SGI to forward to the specified CPU interfaces. 
    //                                  The value of this field is the Interrupt ID, in the range 0-15
    gicd->SGIR = _L(targetListFilter, 24) | _L(cpuTagetList, 16) | irqId;
}

void gicd_init(void)
{
    GICD* gicd = gicd_get();

    // Gourp 0/1
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 3.1 About interrupt handling and prioritization
    //      use the GIC interrupt grouping feature to support the handling of Secure and Non-secure interrupts, in which case:
    //      — Group 0 interrupts are Secure interrupts
    //      — Group 1 interrupts are Non-secure interrupts.
    //      With interrupt grouping:
    //      — by default, all interrupts are Group 0 interrupts, and are signaled to a connected processor using the IRQ interrupt request
    //      — each interrupt can be configured as Group 1 interrupt, or as a Group 0 interrupt
    //      — a CPU interface can be configured to signal Group 0 interrupts to a connected processor using the FIQ  interrupt request.

    // GICD_CTLR
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.1 Distributor Control Register, GICD_CTLR
    //      Bit     Field           Description
    //      31-3    reverse         
    //      1       EnableGrp1      Global enable for forwarding pending Group 1 interrupts from the Distributor to the CPU interfaces:
    //                              0 = Group 1 interrupts not forwarded.
    //                              1 = Group 1 interrupts forwarded, subject to the priority rules.
    //      0       EnableGrp0      Global enable for forwarding pending Group 0 interrupts from the Distributor to the CPU interfaces:
    //                              0 = Group 0 interrupts not forwarded.
    //                              1 = Group 0 interrupts forwarded, subject to the priority rules.
    gicd->CTLR = 0; // Set the default value of 0
    
    // GICD_ICPENDRn
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.8 Interrupt Clear-Pending Registers, GICD_ICPENDRn
    //      Bit     Field               Description
    //      31-0    Clear-pending bits  For each bit:
    //                                  [Reads] 0 = The corresponding interrupt is not pending on any processor.
    //                                          1 = For SGIs and PPIs, the corresponding interrupt is pendinga on this processor.
    //                                              For SPIs, the corresponding interrupt is pendinga on at least one processor.
    //                                  [Writes]For SPIs and PPIs:
    //                                              0 = Has no effect.
    //                                              1 = The effect depends on whether the interrupt is edge - triggered or level - sensitive
    //                                          For SGIs, the write is ignored. SGIs have their own Clear-Pending registers
    // Clear all pending interrupts.
    for (uint32_t i = 0; i < 32; i++)
        gicd->ICPENDRn[i] = 0xFFFFFFFF;
    
    // GICD_IGROUPR
    // [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.4 Interrupt Group Registers, GICD_IGROUPRn
    //      Bit     Field               Description
    //      31-0    Group status bits   For each bit:
    //                                  0 = The corresponding interrupt is Group 0.
    //                                  1 = The corresponding interrupt is Group 1.
    for (uint32_t i = 0; i < 8; i++)
        gicd->IGROUPRn[i] = 0; // Group 0 interrupts(Secure interrupts)

    // GICC initialization
    gicc_init();
    
    gicd->CTLR |= _B(1)/*EnableGrp1*/ | _B(0)/*EnableGrp0*/;
}
