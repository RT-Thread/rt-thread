/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef __GICV2_GICD_H__
#define __GICV2_GICD_H__

#include <stdint.h>
#include <stdbool.h>

// [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.2 Interrupt Controller Type Register, GICD_TYPER
typedef struct {
    // Indicates the maximum number of interrupts that the GIC supports. 
    // If ITLinesNumber=N, the  maximum number of interrupts is 32(N + 1). The interrupt ID range is from 0 to (number of IDs ¨C 1).
    // For example: 0b00011 = Up to 128 interrupt lines, interrupt IDs 0-127
    // The maximum number of interrupts is 1020 (0b11111). interrupt IDs 1020-1023 are reserved for special purposes
    uint32_t ITLinesNumber : 5;
    // Indicates the number of implemented CPU interfaces. 
    // The number of implemented CPU interfaces is one more than the value of this field,
    // for example if this field is 0b011, there are four CPU interfaces
    uint32_t CPUNumber : 3;
    uint32_t rev0 : 2;
    // Indicates whether the GIC implements the Security Extensions
    // 0 = Security Extensions not implemented.
    // 1 = Security Extensions implemented.
    uint32_t SecurityExt : 1;
    // If the GIC implements the Security Extensions, the value of this field is the maximum number of implemented lockable SPIs, 
    // from 0 (0b00000) to 31 (0b11111)
    uint32_t LSPI : 5;
    uint32_t rev1 : 16;
} GICD_TYPER;

#define GIC_INTID_LIMIT 1020

// [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.1.2 Distributor register map
typedef struct
{                                                           // offset           type    Description
    volatile uint32_t CTLR;                                 // [0x000]          RW      Distributor Control Register.
    volatile GICD_TYPER TYPER;                              // [0x004]          RO      Interrupt Controller Type Register.
    volatile uint32_t IIDR;                                 // [0x008]          RO      Distributor Implementer Identification Register.
    volatile uint32_t rev0[(0x020 - 0x00C) / 4];            // [0x00C-0x01C]
    volatile uint32_t rev1[(0x040 - 0x020) / 4];            // [0x020-0x03C]
    volatile uint32_t rev2[(0x080 - 0x040) / 4];            // [0x040-0x07C]
    volatile uint32_t IGROUPRn[8];                          // [0x080-0x09C]    RW      Interrupt Group Registers.
    volatile uint32_t rev3[(0x100 - 0x0A0) / 4];            // [0x0A0-0x0FC]
    volatile uint32_t ISENABLERn[32];                       // [0x100-0x17C]    RW      Interrupt Set-Enable Registers.
    volatile uint32_t ICENABLERn[32];                       // [0x180-0x1FC]    RW      Interrupt Clear-Enable Registers.
    volatile uint32_t ISPENDRn[32];                         // [0x200-0x27C]    RW      Interrupt Set-Pending Registers.
    volatile uint32_t ICPENDRn[32];                         // [0x280-0x2FC]    RW      Interrupt Clear-Pending Registers.
    volatile uint32_t ICDABRn[32];                          // [0x300-0x37C]    RW      Active Bit Registers.
    volatile uint32_t ICACTIVERn[32];                       // [0x380-0x3FC]    RW      Interrupt Clear-Active Registers
    volatile uint8_t IPRIORITYRn[GIC_INTID_LIMIT];          // [0x400-0x7F8]    RW      Interrupt Priority Registers. (Byte accessible)
    volatile uint32_t rev4;                                 // [0x7FC]
    volatile uint8_t ITARGETSRn[GIC_INTID_LIMIT];           // [0x800-0xBF8]    RW      Interrupt Processor Targets Registers. (Byte accessible)
    volatile uint32_t rev5;                                 // [0xBFC]
    volatile uint32_t ICFGRn[64];                           // [0xC00-0xCFC]    RW      Interrupt Configuration Registers.
    volatile uint32_t rev6[64];                             // [0xD00-0xDFC]
    volatile uint32_t NSACRn[64];                           // [0xE00-0xEFC]    RW      Non-secure Access Control Registers, optional
    volatile uint32_t SGIR;                                 // [0xF00]          WO      Software Generated Interrupt Register
    volatile uint32_t rev7[(0xF10 - 0xF04) / 4];            // [0xF04-0xF0C]
    volatile uint32_t CPENDSGIRn[4];                        // [0xF10-0xF1C]    RW      SGI Clear-Pending Registers
    volatile uint32_t SPENDSGIRn[4];                        // [0xF20-0xF2C]    RW      SGI Set-Pending Registers
    volatile uint32_t rev8[(0xFD0 - 0xF30) / 4];            // [0xF30-0xFCC]
    volatile uint32_t rev9[(0xFE8 - 0xFD0) / 4];            // [0xFD0-0xFE4]    RO      IMPLEMENTATION DEFINED
    volatile uint32_t ICPIDR2;                              // [0xFE8]          RO      Peripheral ID2 Register
    volatile uint32_t rev10[(0x1000 - 0xFEC) / 4];          // [0xFEC-0xFFC]    RO      IMPLEMENTATION DEFINED
} GICD;

// [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.3.15 Software Generated Interrupt Register, GICD_SGIR
//      Bit     Field               Description
//      25-24   TargetListFilter    Determines how the distributor must process the requested SGI:
//                                  0b00 = Forward the interrupt to the CPU interfaces specified in the CPUTargetList field.
//                                  0b01 = Forward the interrupt to all CPU interfaces except that of the processor that requested the interrupt.
//                                  0b10 = Forward the interrupt only to the CPU interface of the processor that requested the interrupt.
//                                  0b11 = Reserved.
typedef enum {
    GICD_FILTER_TARGET_LIST_FILTER = 0,
    GICD_FILTER_OTHER_CPUS,
    GICD_FILTER_THIS_CPU,
} GICD_FILTER;

#if defined(__cplusplus)
extern "C" {
#endif

    void gicd_irq_enable(uint32_t irqId, uint32_t cpuId, bool isSecure, uint32_t priority);
    void gicd_irq_disable(uint32_t irqId, uint32_t cpuId);
    void gicd_sgi_gen(uint32_t irqId, GICD_FILTER targetListFilter, uint32_t cpuTagetList);
    void gicd_init(void);

#if defined(__cplusplus)
}
#endif

#endif // __GICV2_GICD_H__
