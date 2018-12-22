/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <assert.h>
#include "core/gic.h"
#include "gic_registers.h"
#include "core/cortex_a9.h"

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static inline gicd_t * gic_get_gicd(void);
static inline gicc_t * gic_get_gicc(void);
static inline uint32_t irq_get_register_offset(uint32_t irqID);
static inline uint32_t irq_get_bit_offset(uint32_t irqID);
static inline uint32_t irq_get_bit_mask(uint32_t irqID);

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

static inline gicd_t * gic_get_gicd(void)
{
    uint32_t base = get_arm_private_peripheral_base() + kGICDBaseOffset;
    return (gicd_t *)base;
}

static inline gicc_t * gic_get_gicc(void)
{
    uint32_t base = get_arm_private_peripheral_base() + kGICCBaseOffset;
    return (gicc_t *)base;
}

static inline uint32_t irq_get_register_offset(uint32_t irqID)
{
    return irqID / 32;
}

static inline uint32_t irq_get_bit_offset(uint32_t irqID)
{
    return irqID & 0x1f;
}

static inline uint32_t irq_get_bit_mask(uint32_t irqID)
{
    return 1 << irq_get_bit_offset(irqID);    
}

void gic_enable(bool enableIt)
{
    gicd_t * gicd = gic_get_gicd();
    
    if (enableIt)
    {
        // Enable both secure and non-secure.
        gicd->CTLR |= kBM_GICD_CTLR_EnableGrp0 | kBM_GICD_CTLR_EnableGrp1;
    }
    else
    {
        // Clear the enable bits.
        gicd->CTLR &= ~(kBM_GICD_CTLR_EnableGrp0 | kBM_GICD_CTLR_EnableGrp1);
    }
}

void gic_set_irq_security(uint32_t irqID, bool isSecure)
{
    gicd_t * gicd = gic_get_gicd();
    
    uint32_t reg = irq_get_register_offset(irqID);
    uint32_t mask = irq_get_bit_mask(irqID);
    
    uint32_t value = gicd->IGROUPRn[reg];
    if (!isSecure)
    {
        value &= ~mask;
    }
    else
    {
        value |= mask;
    }
    gicd->IGROUPRn[reg] = value;
}

void gic_enable_irq(uint32_t irqID, bool isEnabled)
{
    gicd_t * gicd = gic_get_gicd();
    
    uint32_t reg = irq_get_register_offset(irqID);
    uint32_t mask = irq_get_bit_mask(irqID);
    
    // Select set-enable or clear-enable register based on enable flag.
    if (isEnabled)
    {
        gicd->ISENABLERn[reg] = mask;
    }
    else
    {
        gicd->ICENABLERn[reg] = mask;
    }
}

void gic_set_irq_priority(uint32_t ID, uint32_t priority)
{
    gicd_t * gicd = gic_get_gicd();
    
    // Update the priority register. The priority registers are byte accessible, and the register
    // struct has the priority registers as a byte array, so we can just index directly by the
    // interrupt ID.
    gicd->IPRIORITYRn[ID] = priority & 0xff;
}

void gic_set_cpu_target(uint32_t irqID, unsigned cpuNumber, bool enableIt)
{
    // Make sure the CPU number is valid.
    assert(cpuNumber <= 7);
    
    gicd_t * gicd = gic_get_gicd();
    uint8_t cpuMask = 1 << cpuNumber;
    
    // Like the priority registers, the target registers are byte accessible, and the register
    // struct has the them as a byte array, so we can just index directly by the
    // interrupt ID.
    if (enableIt)
    {
        gicd->ITARGETSRn[irqID] |= (cpuMask & 0xff);
    }
    else
    {
        gicd->ITARGETSRn[irqID] &= ~(cpuMask & 0xff);
    }
}

void gic_send_sgi(uint32_t irqID, uint32_t target_list, uint32_t filter_list)
{
    gicd_t * gicd = gic_get_gicd();
    
    gicd->SGIR = (filter_list << kBP_GICD_SGIR_TargetListFilter)
                    | (target_list << kBP_GICD_SGIR_CPUTargetList)
                    | (irqID & 0xf);
}

void gic_cpu_enable(bool enableIt)
{
    gicc_t * gicc = gic_get_gicc();
    
    if (enableIt)
    {
        gicc->CTLR |= kBM_GICC_CTLR_EnableS | kBM_GICC_CTLR_EnableNS;
    }
    else
    {
        gicc->CTLR &= ~(kBM_GICC_CTLR_EnableS | kBM_GICC_CTLR_EnableNS);
    }
}

void gic_set_cpu_priority_mask(uint32_t priority)
{
    gicc_t * gicc = gic_get_gicc();
    gicc->PMR = priority & 0xff;    
}

uint32_t gic_read_irq_ack(void)
{
    gicc_t * gicc = gic_get_gicc();
    return gicc->IAR;
}

void gic_write_end_of_irq(uint32_t irqID)
{
    gicc_t * gicc = gic_get_gicc();
    gicc->EOIR = irqID;
}

void gic_init(void)
{
    gicd_t * gicd = gic_get_gicd();

    // First disable the distributor.
    gic_enable(false);
    
    // Clear all pending interrupts.
    int i;
    for (i = 0; i < 32; ++i)
    {
        gicd->ICPENDRn[i] = 0xffffffff;
    }
    
    // Set all interrupts to secure.
    for (i = 0; i < 8; ++i)
    {
        gicd->IGROUPRn[i] = 0;
    }

    // Init the GIC CPU interface.
    gic_init_cpu();
    
    // Now enable the distributor.
    gic_enable(true);
}

void gic_init_cpu(void)
{
    // Init the GIC CPU interface.
    gic_set_cpu_priority_mask(0xff);

    // Disable preemption.
    gicc_t * gicc = gic_get_gicc();
    gicc->BPR = 7;

    // Enable signaling the CPU.
    gic_cpu_enable(true);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
