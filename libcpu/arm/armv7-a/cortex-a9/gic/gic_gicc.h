/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#ifndef __GIC_GICC_H__
#define __GIC_GICC_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint32_t rev : 19;
    uint32_t cpuId : 3;
    uint32_t irqId : 10;
} GIC_IRQ;

// [ref]IHI0048B_b_gic_architecture_specification.pdf: 4.1.3 CPU interface register map
//      cortex_a9_mpcore_trm_100486_0401_10_en.pdf: 3.4.1 Processor interface register summary
typedef struct
{                                                   // offset           type    Description                                                         Cortex-A9
    volatile uint32_t CTLR;                         // [0x0000]         RW      CPU Interface Control Register.                                     supported
    volatile uint32_t PMR;                          // [0x0004]         RW      Interrupt Priority Mask Register.                                   supported
    volatile uint32_t BPR;                          // [0x0008]         RW      Binary Point Register.                                              supported
    volatile GIC_IRQ IAR;                           // [0x000C]         RO      Interrupt Acknowledge Register.                                     supported
    volatile GIC_IRQ EOIR;                          // [0x0010]         WO      End of Interrupt Register.                                          supported
    volatile uint32_t RPR;                          // [0x0014]         RO      Running Priority Register.                                          supported
    volatile uint32_t HPPIR;                        // [0x0018]         RO      Highest Priority Pending Interrupt Register.                        supported
    volatile uint32_t ABPR;                         // [0x001C]         RW      Aliased Binary Point Register. (only visible with a secure access)  supported
    volatile uint32_t AIAR;                         // [0x0020]         RO      Aliased Interrupt Acknowledge Register(GICv2 only)
    volatile uint32_t AEOIR;                        // [0x0024]         WO      Aliased End of Interrupt Register(GICv2 only)
    volatile uint32_t AHPPIR;                       // [0x0028]         RO      Aliased Highest Priority Pending Interrupt Register(GICv2 only)
    volatile uint32_t rev0[(0x0040 - 0x002C) / 4];  // [0x002C-0x003C]
    volatile uint32_t rev1[(0x00D0 - 0x0040) / 4];  // [0x0040-0x00CF]
    volatile uint32_t APRn[4];                      // [0x00D0-0x00DC]  RW      Active Priorities Registers(GICv2 only)
    volatile uint32_t NSAPRn[4];                    // [0x00E0-0x00EC]  RW      Non-secure Active Priorities Registers(GICv2 only)
    volatile uint32_t rev2[(0x00FC - 0x00ED) / 4];  // [0x00ED-0x00F8]
    volatile uint32_t IIDR;                         // [0x00FC]         RO      CPU Interface Identification Register.                              supported
    volatile uint32_t rev3[(0x1000 - 0x0100) / 4];  // [0x0100-0x0FFC]  NA
    volatile uint32_t DIR;                          // [0x1000]         WO      Deactivate Interrupt Register(GICv2 only)
} GICC;

#if defined(__cplusplus)
extern "C" {
#endif

    GIC_IRQ gicc_irq_get(void);
    void gicc_irq_clr(GIC_IRQ irqIdx);
    void gicc_init(void);

#if defined(__cplusplus)
}
#endif

#endif // __GIC_GICC_H__
