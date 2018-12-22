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
///////////////////////////////////////////////////////////////////////////////
//! @addtogroup ddi_media_nand_hal_gpmi_internal
//! @{
//! @file    ddi_nand_gpmi_dma_isr.cpp
//! @brief   Routines for handling the DMA completion ISR for the NANDs.
//!
//! This file contains the NAND HAL DMA completion Interrupt Subroutine.
//!
////////////////////////////////////////////////////////////////////////////////

extern "C" {
#include "sdk_types.h"
#include "interrupt.h"
#include "irq_numbers.h"
}

#include "gpmi_internal.h"
#include "registers/regsapbh.h"
#include "registers/regsbch.h"

///////////////////////////////////////////////////////////////////////////////
// Prototypes
///////////////////////////////////////////////////////////////////////////////

void gpmi_dma_complete_isr();
void bch_complete_isr();

///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

static inline void gpmi_clear_dma_command_complete_irq(int chip)
{
    // Clear the command-complete IRQ for this chip...
    HW_APBH_CTRL1_CLR((BM_APBH_CTRL1_CH0_CMDCMPLT_IRQ << chip));
    
    // ...and do a dummy read-back to make sure the value has been written.
//     volatile uint32_t u32Dummy = HW_APBH_CTRL1_RD();
}

static inline void gpmi_set_dma_irq_enabled(int chip)
{
    HW_APBH_CTRL1_SET(BM_APBH_CTRL1_CH0_CMDCMPLT_IRQ_EN << chip);
}

void gpmi_clear_dma_isr_enable(uint16_t u16CurrentChip)
{
    // clear the APBH dma IRQ and re-enable the associated vector in icoll.

    gpmi_clear_dma_command_complete_irq(u16CurrentChip);

//     hw_icoll_EnableVector(VECTOR_IRQ_GPMI_DMA, true);
}

void gpmi_clear_ecc_isr_enable(void)
{
    // Clear the ECC Complete IRQ and re-enable the associated vector in icoll.

    bch_clear_complete_irq();
    bch_enable_complete_irq();

//     hw_icoll_EnableVector(VECTOR_IRQ_BCH, true);
}

void gpmi_init_interrupts(unsigned chipSelect)
{
//     UINT retCode;

    // Only need to register the handler for the first chip
    // since the same DMA interrupt is used for all channels.
    if (chipSelect == 0)
    {
        // Create the DMA complete spinlock. Lock it immediately.
        spinlock_init(&g_gpmi.dmaInfo.irqSpinlock);
        spinlock_lock(&g_gpmi.dmaInfo.irqSpinlock, kSpinlockNoWait);
        
        // setup and enable the isr for the BCH IRQ
        register_interrupt_routine(IMX_INT_BCH, bch_complete_isr);

        // setup and enable the isr for the GPMI DMA IRQ
        register_interrupt_routine(IMX_INT_APBHDMA, gpmi_dma_complete_isr);
    }

    // clear and enable the APBH DMA IRQs
    gpmi_clear_dma_command_complete_irq(chipSelect);
    gpmi_set_dma_irq_enabled(chipSelect);

    // clear and enable the ECC IRQs
    bch_clear_complete_irq();
    bch_enable_complete_irq();

    // Enable the IRQs.
    enable_interrupt(IMX_INT_BCH, CPU_0, 0);
    enable_interrupt(IMX_INT_APBHDMA, CPU_0, 0);
}

////////////////////////////////////////////////////////////////////////////////
//! @brief      ISR for the GPMI dma complete IRQ.
//!
//! Signals GPMI dma completed by signaling the NAND semaphore.
//! This is dependent on the state of pParam->u16DmaWaitMask.
//!
//! Then clears and enables the interrupt.
////////////////////////////////////////////////////////////////////////////////
void gpmi_dma_complete_isr()
{
    GpmiDmaInfo_t * pWaitStruct = &g_gpmi.dmaInfo;

    //
    // Aside: We cannot check the SEMA.PHORE register here.
    // The DMA engine in the 37xx can trigger the ISR at the end of the DMA, before decrementing
    // the SEMA.PHORE count, thus creating a race condition that lets us find a
    // nonzero SEMA.PHORE value here.
    //

    bool bSomeError = FALSE;
    
    // Check for an error on the DMA channel assigned to this chip
    if ((HW_APBH_CTRL2_RD() & (BM_APBH_CTRL2_CH0_ERROR_IRQ << (pWaitStruct->dmaChannel))) != 0)
    {
        // If an error occured, clear it.  The gpmi_wait_for_dma function
        // will reset the channel.
        HW_APBH_CTRL2_CLR(BP_APBH_CTRL2_CH0_ERROR_IRQ << pWaitStruct->dmaChannel);
        bSomeError = TRUE;
    }

    // Note that this ISR has run.
    pWaitStruct->u16DmaWaitStatus |= kNandGpmiDmaWaitMask_GpmiDma;

    // See if all criteria have been met, to declare the DMA finished.
    if (pWaitStruct->u16DmaWaitMask == pWaitStruct->u16DmaWaitStatus)
    {

        // There is code waiting for the completion of ECC.
        if ( !bSomeError )
        {
            // If there was no error, then signal the completion.
            spinlock_unlock(&g_gpmi.dmaInfo.irqSpinlock);
        }
    }

    // clear the APBH dma IRQ and re-enable the associated vector in icoll.
    gpmi_clear_dma_isr_enable( pWaitStruct->dmaChannel );
}


////////////////////////////////////////////////////////////////////////////////
//! @brief      ISR for the APBH BCH-complete IRQ.
//!
//! Possibly signals APBH ECC completed by signaling the NAND semaphore.
//! This is dependent on the state of pParam->u16DmaWaitMask.
//!
//! Then clears and enables the interrupt.
////////////////////////////////////////////////////////////////////////////////
void bch_complete_isr()
{
    GpmiDmaInfo_t * pWaitStruct = &g_gpmi.dmaInfo;

    // Note that this ISR has run.
    pWaitStruct->u16DmaWaitStatus |= kNandGpmiDmaWaitMask_Ecc;

    // See if all criteria have been met, to declare the DMA finished.
    if (pWaitStruct->u16DmaWaitMask == pWaitStruct->u16DmaWaitStatus)
    {
        bool    bSomeError = FALSE;

        // See if this interrupt came from a bus-error on APBH,
        // possibly because the address of the transaction was invalid.
        if (BF_RD(BCH_CTRL, BM_ERROR_IRQ))
        {
	        // If an error occured, clear it.  The gpmi_wait_for_dma function
	        // will reset the channel.
            HW_BCH_CTRL_CLR(BM_BCH_CTRL_BM_ERROR_IRQ);
            bSomeError = TRUE;
        }

	    // Check for an error on the DMA channel assigned to
	    // this chip
	    if ((HW_APBH_CTRL2_RD() & (BM_APBH_CTRL2_CH0_ERROR_IRQ << (pWaitStruct->dmaChannel))) != 0)
	    {
		    // If an error occured, clear it.  The gpmi_wait_for_dma function
		    // will reset the channel.
	        HW_APBH_CTRL2_CLR(BP_APBH_CTRL2_CH0_ERROR_IRQ << pWaitStruct->dmaChannel);

            bSomeError = TRUE;
 	    }

        // There is code waiting for the completion of ECC.
        if ( !bSomeError )
        {
            // If there was no error, then signal the completion.
            spinlock_unlock(&g_gpmi.dmaInfo.irqSpinlock);
        }
    }

    // At this point we DO NOT
    //  * Clear the ECC IRQ
    // Reason: The ECC STATUS must be preserved until the client
    // application can read it, to see the ECC results.
    // It is the client application's responsibility to
    // perform the aforementioned actions after the ECC STATUS
    // has been read.
	gpmi_clear_ecc_isr_enable();

}

// EOF
//! @}
