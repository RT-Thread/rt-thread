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
#if !defined(__gpmi_internal_h__)
#define __gpmi_internal_h__

#include "gpmi/gpmi.h"
#include "utility/spinlock.h"
#include "timer/timer.h"

/*!
 * @file gpmi.h
 * @brief Header file for shared internal declarations for the GPMI driver.
 *
 * @ingroup diag_nand
 */

//! @addtogroup diag_nand
//! @{

/*!
 * @brief Structure for holding information used to start and stop DMAs to the NAND(s).
 *
 * The functions ddi_gpmi_start_dma() and ddi_gpmi_wait_for_dma() use this information
 * to manage DMAs with the NAND chips.
 */
typedef struct GpmiDmaInfo {
    //! @brief Spinlock used for synchronization with interrupts.
    spinlock_t irqSpinlock;

    //! @brief Index of the chip-enable for this DMA.  Range [0..number-of-CEs).
    uint16_t u16CurrentChip;
    
    //! @brief The DMA channel currently in use.
    uint16_t dmaChannel;

    //! @brief A bitmask used to indicate criteria for terminating the DMA.
    //!
    //! See #_nand_gpmi_dma_wait_mask.
    uint16_t u16DmaWaitMask;

    //! @brief A bitmask used to indicate status of the DMA.
    //!
    //! See #_nand_gpmi_dma_wait_mask.
    //! When (u16DmaWaitStatus == u16DmaWaitMask) the DMA is complete.
    uint16_t u16DmaWaitStatus;

    uint64_t uStartDMATime; //!< Only used for non-ThreadX builds.
} GpmiDmaInfo_t;

/*!
 * @brief Global GPMI driver state.
 */
typedef struct GpmiState {
    //! Current GPMI timings.
    GpmiNandTimings_t currentTimings;
    
    //! Minimum propagation delay in nanosecnds of GPMI signals to and from the NAND.
    uint32_t propDelayMin_ns;
    
    //! Maximum propagation delay in nanosecnds of GPMI signals to and from the NAND.
    uint32_t propDelayMax_ns;
    
    //! Information about the active DMA transaction.
    GpmiDmaInfo_t dmaInfo;
} GpmiState_t;

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief The current GPMI driver state information.
extern GpmiState_t g_gpmi;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

//! @brief Initialize interrupts for a GPMI chip select.
void gpmi_init_interrupts(unsigned chipSelect);

void gpmi_clear_dma_isr_enable(uint16_t u16CurrentChip);

void gpmi_clear_ecc_isr_enable(void);

//! @}
#endif //__gpmi_internal_h__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
