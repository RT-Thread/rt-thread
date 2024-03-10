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
#include "gpmi/bch_ecc.h"
#include "gpmi/gpmi.h"
#include "registers/regsbch.h"
#include "registers/regsgpmi.h"

enum _bch_constants
{
    //! Maximum value for the erase threshold.
    kMaxEraseThreshold = 0xff,
    
    kNandPayloadSize_GF13 = 512,
    kNandPayloadSize_GF14 = 1024,
    kNandMetadataSize = 10
};

//! @brief Converts a number of bits to a number of bytes, rounding up.
#define BITS_TO_BYTES(bits) (((bits) + 7) / 8)

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void bch_init()
{
//     HW_BCH_CTRL_CLR(BF_BCH_CTRL_SFTRST(1));  //b34918
//     HW_BCH_CTRL_CLR(BF_BCH_CTRL_CLKGATE(1));
//     HW_BCH_CTRL_SET(BF_BCH_CTRL_SFTRST(1));
//     while (!(HW_BCH_CTRL_RD() & BM_BCH_CTRL_CLKGATE));

//     bch_enable();
    
    HW_BCH_CTRL_CLR(BM_BCH_CTRL_SFTRST);
    HW_BCH_CTRL_CLR(BM_BCH_CTRL_CLKGATE);
    
    HW_BCH_CTRL_SET(BM_BCH_CTRL_SFTRST);
    while (!HW_BCH_CTRL.B.CLKGATE);

    HW_BCH_CTRL_CLR(BM_BCH_CTRL_SFTRST);
    HW_BCH_CTRL_CLR(BM_BCH_CTRL_CLKGATE);
}

void bch_enable(void)
{
    HW_BCH_CTRL_CLR( BM_BCH_CTRL_CLKGATE );

    // Remove the clock gate.
//     HW_BCH_CTRL_CLR( BM_BCH_CTRL_CLKGATE);
// 
//     // Poll until clock is in the NON-gated state.
//     while (HW_BCH_CTRL.B.CLKGATE)
//     {
//         ; // busy wait
//     }
// 
//     // Remove Soft Reset.
//     HW_BCH_CTRL_CLR( BM_BCH_CTRL_SFTRST );
// 
//     // Poll until soft reset is clear.
//     while (HW_BCH_CTRL.B.SFTRST)
//     {
//         ; // busy wait
//     }
}

void bch_disable(void)
{
    // Gate the BCH block
    HW_BCH_CTRL_SET( BM_BCH_CTRL_CLKGATE );
}

void bch_set_erase_threshold(unsigned threshold)
{
    // Make sure the threshold is valid.
    if (threshold > kMaxEraseThreshold)
    {
        threshold = kMaxEraseThreshold;
    }
    
    // This is the only field of the register, so just write it all.
    HW_BCH_MODE_WR(BF_BCH_MODE_ERASE_THRESHOLD(threshold));
}

void bch_set_layout(const BchEccLayout_t * ecc)
{
    // Fill in layout 0 from the values in the layout struct.
    HW_BCH_FLASH0LAYOUT0_WR(
        BF_BCH_FLASH0LAYOUT0_DATA0_SIZE((ecc->block0Size)>>2)
        | BF_BCH_FLASH0LAYOUT0_GF13_0_GF14_1(ecc->block0GaloisField == kGaloisField_14bit)
        | BF_BCH_FLASH0LAYOUT0_ECC0(ecc->block0Level / 2)
        | BF_BCH_FLASH0LAYOUT0_META_SIZE(ecc->metadataSize)
        | BF_BCH_FLASH0LAYOUT0_NBLOCKS(ecc->blockNCount) );

    HW_BCH_FLASH0LAYOUT1_WR(
        BF_BCH_FLASH0LAYOUT1_DATAN_SIZE((ecc->blockNSize)>>2)
        | BF_BCH_FLASH0LAYOUT1_GF13_0_GF14_1(ecc->blockNGaloisField == kGaloisField_14bit)
        | BF_BCH_FLASH0LAYOUT1_ECCN(ecc->blockNLevel / 2)
        | BF_BCH_FLASH0LAYOUT1_PAGE_SIZE(ecc->fullPageSize) );
    
    // Set all chip enables to use layout 0 by clearing the layout select register.
    HW_BCH_LAYOUTSELECT_WR(0);
}

int bch_calculate_best_level(uint32_t pageDataSize, uint32_t pageMetadataSize, BchEccLayout_t * resultEcc)
{
    uint32_t pageTotalSize = pageDataSize + pageMetadataSize;
    unsigned blockNCount = (pageDataSize / kNandPayloadSize_GF13) - 1;
    unsigned block0Size = kNandPayloadSize_GF13 + kNandMetadataSize;
    unsigned bchLevel = kMaxBchLevel;
    
    while (bchLevel > 0)
    {
        uint32_t totalSize = BITS_TO_BYTES((bchLevel * kGaloisField_13bit) + (blockNCount * bchLevel * kGaloisField_13bit)) + block0Size + (blockNCount * kNandPayloadSize_GF13);
        if (totalSize <= pageTotalSize)
        {
            break;
        }
        
        bchLevel -= 2;
    }
    
    // Return an error if nothing fits in the page.
    if (bchLevel == 0)
    {
        return -1; //ERROR_GENERIC;
    }
    
    // Fill in the resulting ECC descriptor.
    resultEcc->fullPageSize = pageDataSize + pageMetadataSize;
    resultEcc->block0GaloisField = kGaloisField_13bit;
    resultEcc->block0Level = bchLevel;
    resultEcc->block0Size = kNandPayloadSize_GF13;
    resultEcc->metadataSize = kNandMetadataSize;
    resultEcc->blockNGaloisField = kGaloisField_13bit;
    resultEcc->blockNLevel = bchLevel;
    resultEcc->blockNSize = kNandPayloadSize_GF13;
    resultEcc->blockNCount = blockNCount;
    
    return SUCCESS;
}

void bch_enable_complete_irq()
{
    BF_SET(BCH_CTRL, COMPLETE_IRQ_EN);
}

void bch_clear_complete_irq()
{
    BF_CLR(BCH_CTRL, COMPLETE_IRQ);
}

int bch_read_correction_status(const uint8_t * auxBuffer, BchEccCorrectionInfo_t * correctionInfo)
{
    unsigned i;
//     unsigned validPayloadCount = 0;
    unsigned maxErrors = 0;
    unsigned indexToAuxBuffer;
//     uint32_t payload;
    
    // Get payload directly from flash layout register. We look up which chip select just finished,
    // then get its flash layout number.
    unsigned completedChip = HW_BCH_STATUS0.B.COMPLETED_CE;
    unsigned whichLayout = (HW_BCH_LAYOUTSELECT_RD() >> (completedChip * BP_BCH_LAYOUTSELECT_CS1_SELECT)) & BM_BCH_LAYOUTSELECT_CS0_SELECT;
    assert(whichLayout <= 3);
    
    unsigned payloadCount;
    unsigned metadataLength;
    switch (whichLayout)
    {
        case 0:
            payloadCount = HW_BCH_FLASH0LAYOUT0.B.NBLOCKS + 1;
            metadataLength = HW_BCH_FLASH0LAYOUT0.B.META_SIZE;
            break;
        case 1:
            payloadCount = HW_BCH_FLASH1LAYOUT0.B.NBLOCKS + 1;
            metadataLength = HW_BCH_FLASH1LAYOUT0.B.META_SIZE;
            break;
        case 2:
            payloadCount = HW_BCH_FLASH2LAYOUT0.B.NBLOCKS + 1;
            metadataLength = HW_BCH_FLASH2LAYOUT0.B.META_SIZE;
            break;
        case 3:
            payloadCount = HW_BCH_FLASH3LAYOUT0.B.NBLOCKS + 1;
            metadataLength = HW_BCH_FLASH3LAYOUT0.B.META_SIZE;
            break;
    }

    // Get the errors from auxillary pointer at offset after metadata bytes.

    // Get the status of Blocks. Each block's status is in a byte, starts at the beginning of a
    // new word where metadata ends.
    indexToAuxBuffer = metadataLength + (metadataLength % sizeof(uint32_t));
    
    // Now get the max ecc corrections of data blocks including metadata ecc.
    bool wasUncorrectable = false;
    bool isAllOnes = true;
    for (i = 0; i < payloadCount; i++) 
    {
        uint8_t payload = auxBuffer[indexToAuxBuffer + i];

        // Convert uncorrectable and erased results to generic constants while tracking the
        // maximum number of errors for all payloads.
        switch (payload)
        {
            case BV_BCH_STATUS0_STATUS_BLK0__UNCORRECTABLE:
                payload = kUncorrectableBitErrors;
                wasUncorrectable = true;
                isAllOnes = false;
                break;
                
            case BV_BCH_STATUS0_STATUS_BLK0__ERASED:
                payload = kAllOnes;
                break;
            
            default:
                isAllOnes = false;

                // Track the maximum number of errors for all payloads.
                if (payload > maxErrors)
                {
                    maxErrors = payload;
                }
        }
        
        // Fill in correction info structure.
        if (correctionInfo)
        {
            correctionInfo->payloadStatus[i] = payload;
        }
    }
    
    // Figure out the return status.
    uint8_t combinedStatus =
        (wasUncorrectable ? kUncorrectableBitErrors :
            (isAllOnes ? kAllOnes :
                (maxErrors > 0 ? kCorrectedBitErrors : kNoBitErrors)));
    
    // Fill in correction info.
    if (correctionInfo)
    {
        correctionInfo->combinedStatus = combinedStatus;
        correctionInfo->maxBitErrors = maxErrors;
        correctionInfo->payloadCount = payloadCount;
    }
    
    return combinedStatus;
}

// BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_PAGE
// BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_AUXONLY
uint16_t bch_get_buffer_mask(bool isWrite, uint32_t dataSize, const BchEccLayout_t * ecc)
{
    // Writes are always full-page.
    if (isWrite)
    {
        return BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_PAGE;
    }
    // Use the special aux-only read mode if the number of bytes is less than or
    // equal to the size of block 0 plus the metadata.
    else if (dataSize <= ecc->block0Size + ecc->metadataSize)
    {
        return BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_AUXONLY;
    }
    
    // Otherwise...
    return BV_GPMI_ECCCTRL_BUFFER_MASK__BCH_PAGE;
}

// EOF
