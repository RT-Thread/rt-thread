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
#include "sdk_types.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Offsets to the GIC registers.
enum _gic_base_offsets
{
    kGICDBaseOffset = 0x1000,   //!< GIC distributor offset.
#if defined(CHIP_MX6UL)
    kGICCBaseOffset = 0x2000     //!< GIC CPU interface offset.
#else    
    kGICCBaseOffset = 0x100     //!< GIC CPU interface offset.
#endif    
};

//! @brief GIC distributor registers.
//!
//! Uses the GICv2 register names, but does not include GICv2 registers.
//!
//! The IPRIORITYRn and ITARGETSRn registers are byte accessible, so their types are uint8_t
//! instead of uint32_t to reflect this. These members are indexed directly with the interrupt
//! number.
struct _gicd_registers
{
    uint32_t CTLR;              //!< Distributor Control Register.
    uint32_t TYPER;             //!< Interrupt Controller Type Register.
    uint32_t IIDR;              //!< Distributor Implementer Identification Register.
    uint32_t _reserved0[29];
    uint32_t IGROUPRn[8];       //!< Interrupt Group Registers.
    uint32_t _reserved1[24];
    uint32_t ISENABLERn[32];    //!< Interrupt Set-Enable Registers.
    uint32_t ICENABLERn[32];    //!< Interrupt Clear-Enable Registers.
    uint32_t ISPENDRn[32];      //!< Interrupt Set-Pending Registers.
    uint32_t ICPENDRn[32];      //!< Interrupt Clear-Pending Registers.
    uint32_t ICDABRn[32];       //!< Active Bit Registers.
    uint32_t _reserved2[32];
    uint8_t IPRIORITYRn[255 * sizeof(uint32_t)];  //!< Interrupt Priority Registers. (Byte accessible)
    uint32_t _reserved3;
    uint8_t ITARGETSRn[255 * sizeof(uint32_t)];   //!< Interrupt Processor Targets Registers. (Byte accessible)
    uint32_t _reserved4;
    uint32_t ICFGRn[64];        //!< Interrupt Configuration Registers.
    uint32_t _reserved5[128];
    uint32_t SGIR;              //!< Software Generated Interrupt Register
};

//! @brief Bitfields constants for the GICD_CTLR register.
enum _gicd_ctlr_fields
{
    kBM_GICD_CTLR_EnableGrp1 = (1 << 1),
    kBM_GICD_CTLR_EnableGrp0 = (1 << 0)
};

//! @brief Bitfields constants for the GICD_SGIR register.
enum _gicd_sgir_fields
{
    kBP_GICD_SGIR_TargetListFilter = 24,
    kBM_GICD_SGIR_TargetListFilter = (0x3 << kBP_GICD_SGIR_TargetListFilter),
    
    kBP_GICD_SGIR_CPUTargetList = 16,
    kBM_GICD_SGIR_CPUTargetList = (0xff << kBP_GICD_SGIR_CPUTargetList),
    
    kBP_GICD_SGIR_NSATT = 15,
    kBM_GICD_SGIR_NSATT = (1 << kBP_GICD_SGIR_NSATT),
    
    kBP_GICD_SGIR_SGIINTID = 0,
    kBM_GICD_SGIR_SGIINTID = 0xf
};

//! @brief GIC CPU interface registers.
//!
//! Uses the GICv2 register names. Does not include GICv2 registers.
struct _gicc_registers
{
    uint32_t CTLR;  //!< CPU Interface Control Register.
    uint32_t PMR;   //!< Interrupt Priority Mask Register.
    uint32_t BPR;   //!< Binary Point Register.
    uint32_t IAR;   //!< Interrupt Acknowledge Register.
    uint32_t EOIR;  //!< End of Interrupt Register.
    uint32_t RPR;   //!< Running Priority Register.
    uint32_t HPPIR; //!< Highest Priority Pending Interrupt Register.
    uint32_t ABPR;  //!< Aliased Binary Point Register. (only visible with a secure access)
    uint32_t _reserved[56];
    uint32_t IIDR;  //!< CPU Interface Identification Register.
};

//! @brief Bitfields constants for the GICC_CTLR register.
enum _gicc_ctlr_fields
{
    kBP_GICC_CTLR_EnableS = 0,
    kBM_GICC_CTLR_EnableS = (1 << 0),
    
    kBP_GICC_CTLR_EnableNS = 1,
    kBM_GICC_CTLR_EnableNS = (1 << 1),
    
    kBP_GICC_CTLR_AckCtl = 2,
    kBM_GICC_CTLR_AckCtl = (1 << 2),
    
    kBP_GICC_CTLR_FIQEn = 3,
    kBM_GICC_CTLR_FIQEn = (1 << 3),
    
    kBP_GICC_CTLR_SBPR = 4,
    kBM_GICC_CTLR_SBPR = (1 << 4)
};

//! @brier Type for the GIC distributor registers.
typedef volatile struct _gicd_registers gicd_t;

//! @brier Type for the GIC CPU interface registers.
typedef volatile struct _gicc_registers gicc_t;

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
