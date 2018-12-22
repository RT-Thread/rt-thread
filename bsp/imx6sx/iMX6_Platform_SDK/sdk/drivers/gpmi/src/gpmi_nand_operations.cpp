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

/*!
 * @file gpmi.c
 * @brief The driver source for the GPMI controller.
 *
 * @ingroup diag_nand
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <assert.h>
#include "gpmi/gpmi.h"
#include "gpmi_internal.h"
#include "gpmi_nand_dma.h"

////////////////////////////////////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////////////////////////////////////

//! \brief Timeout Constants
//!
//! The following constants describe how much patience we have when waiting for
//! particular operations to finish.
//!
enum _nand_timeouts
{
    kNandResetTimeout = 2000000,       //!< The time, in microseconds, to wait for a reset to finish. (2 sec)
    kNandReadPageTimeout = 500000,     //!< The time, in microseconds, to wait for a page read to finish. (0.5 sec)
    kNandWritePageTimeout = 1000000,   //!< The time, in microseconds, to wait for a page write to finish. (1 sec)
    kNandEraseBlockTimeout = 2000000   //!< The time, in microseconds, to wait for block erase to finish. (2 sec)
};

//! @brief NAND hardware command codes.
enum _nand_command_codes
{
    kNandCommand_Reset = 0xff,
    kNandCommand_ReadID = 0x90,
    kNandCommand_ReadONFIParamPage = 0xec,
    kNandCommand_ReadStatus = 0x70,
    kNandCommand_ReadPage1 = 0x00,
    kNandCommand_ReadPage2 = 0x30,
    kNandCommand_SerialDataInput = 0x80,
    kNandCommand_WritePage = 0x10,
    kNandCommand_AddressInput = 0x60,
    kNandCommand_BlockErase = 0xd0
};

//! \brief Simple macro to convert a number of bits into bytes, rounded up
//!     to the nearest byte.
#define BITS_TO_BYTES(bits) ((bits + 7) / 8)

////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

//! @brief Details about a NAND.
typedef struct _nand_info {
    BchEccLayout_t ecc;
    uint32_t dataSize;
    uint32_t auxSize;
    uint32_t rowAddressBytes;
    uint32_t columnAddressBytes;
    uint32_t totalAddressBytes;
    uint32_t pagesPerBlock;
} NandInfo_t;

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

static int gpmi_nand_check_status(uint8_t statusValue);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Saved information about the NAND we're talking to.
NandInfo_t g_nandInfo;

//! @brief Shared result buffer for status reads.
static uint8_t s_resultBuffer[64] __ALIGN4__;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

int gpmi_nand_configure(unsigned rowBytes, unsigned columnBytes, unsigned pagesPerBlock, const BchEccLayout_t * ecc)
{
    g_nandInfo.ecc = *ecc;
    g_nandInfo.rowAddressBytes = rowBytes;
    g_nandInfo.columnAddressBytes = columnBytes;
    g_nandInfo.totalAddressBytes = rowBytes + columnBytes;
    g_nandInfo.pagesPerBlock = pagesPerBlock;
    
    // Aux size is metadata plus all parity bytes. Parity bytes are rounded up to the
    // next byte.
    g_nandInfo.auxSize = ecc->metadataSize
        + BITS_TO_BYTES((ecc->block0Level * ecc->block0GaloisField)
            + (ecc->blockNCount * (ecc->blockNLevel * ecc->blockNGaloisField)));
    
    // Data size is the actual data bytes.
    g_nandInfo.dataSize = ecc->block0Size + ecc->blockNCount * ecc->blockNSize;
    
    bch_set_layout(&g_nandInfo.ecc);
    bch_set_erase_threshold(0);
    
    return SUCCESS;
}

int gpmi_nand_reset(unsigned chipSelect)
{
    NandDma::Reset resetDma(chipSelect, kNandCommand_Reset);

//     hw_core_invalidate_clean_DCache();
    
    return resetDma.run(kNandResetTimeout);
}

int gpmi_nand_read_id(unsigned chipSelect, uint8_t * resultID)
{
    NandDma::ReadId readIdDma(chipSelect, kNandCommand_ReadID, 0, resultID);

//     hw_core_invalidate_clean_DCache();

    return readIdDma.run(kNandResetTimeout);
}

int gpmi_nand_erase_block(unsigned chipSelect, uint32_t blockNumber)
{
    int ret;

    // Enable writes to this NAND for this scope.
    gpmi_enable_writes(true);
    
    // Use the 1st page of the block to calculate the Row address, then adjust as/if necessary.
    uint32_t wRowAddr = blockNumber * g_nandInfo.pagesPerBlock;

    // The resulting status byte is stored here on the stack, and must be word aligned.
    NandDma::BlockErase eraseDma(
        chipSelect,
        kNandCommand_AddressInput,
        wRowAddr,
        g_nandInfo.rowAddressBytes,
        kNandCommand_BlockErase);
    
    // Init the status read DMA.
    NandDma::ReadStatus statusDma(chipSelect, kNandCommand_ReadStatus, s_resultBuffer);
    
    // Chain the status read DMA onto our erase DMA.
    eraseDma >> statusDma;

    // Flush cache.
//     hw_core_invalidate_clean_DCache();

    // Initiate DMA and wait for completion.
    ret = eraseDma.run(kNandEraseBlockTimeout);

    if (SUCCESS == ret)
    {
        if (gpmi_nand_check_status(s_resultBuffer[0]) != SUCCESS)
        {
            ret = ERROR_DDI_NAND_HAL_WRITE_FAILED;
        }
    }

    gpmi_enable_writes(false);

    return ret;
}

int gpmi_nand_read_raw(unsigned chipSelect, uint32_t pageNumber, uint8_t * buffer, uint32_t offset, uint32_t count)
{
    NandDma::ReadRawData rawReadDma(
        chipSelect, // chipSelect,
        kNandCommand_ReadPage1, // command1,
        NULL, // addressBytes,
        g_nandInfo.totalAddressBytes, // addressByteCount,
        kNandCommand_ReadPage2, // command2,
        NULL, //pBuf, // dataBuffer,
        0, //readByteCount, // dataReadSize,
        NULL, // auxBuffer,
        0); // auxReadSize);
    rawReadDma.setAddress(offset, pageNumber);
    rawReadDma.setBuffers(buffer, count, NULL, 0);
    
    // Flush the data cache to ensure that the DMA descriptor chain is in memory.
//     hw_core_invalidate_clean_DCache();

    return rawReadDma.run(kNandReadPageTimeout);
}

//! 70h status bits:
//! -  Bit 0 - Total Pass(0)/Fail(1)
//! -  Bit 1 - Don't Care
//! -  Bit 2 - Don't Care
//! -  Bit 3 - Don't Care
//! -  Bit 4 - Don't Care
//! -  Bit 5 - Reserved (Must be Don't Care)
//! -  Bit 6 - Ready(1)/Busy(0)
//! -  Bit 7 - Write Protect (0=Protected)
int gpmi_nand_check_status(uint8_t statusValue)
{
    return (statusValue & 1) == 0 ? SUCCESS : -1;
}

int gpmi_nand_write_raw(unsigned chipSelect, uint32_t pageNumber, const uint8_t * buffer, uint32_t offset, uint32_t count)
{
    // Enable writes to this NAND for this scope.
    gpmi_enable_writes(true);

    // Construct the raw write DMA descriptor.
    NandDma::WriteRawData rawWriteDma(
        chipSelect, // chipSelect,
        kNandCommand_SerialDataInput, // command1,
        NULL, // addressBytes,
        g_nandInfo.totalAddressBytes, // addressByteCount,
        kNandCommand_WritePage, // command2,
        NULL, //data, // dataBuffer,
        0, //writeByteCount, // dataSize,
        NULL, // auxBuffer,
        0); // auxSize);
    rawWriteDma.setAddress(offset, pageNumber);
    rawWriteDma.setBuffers(buffer, count, NULL, 0);
    
    // Init the status read DMA.
    NandDma::ReadStatus statusDma(chipSelect, kNandCommand_ReadStatus, s_resultBuffer);
     
    // Chain our global status read DMA onto this raw write DMA.
    rawWriteDma >> statusDma;

    // Flush data cache and run DMA.
//     hw_core_clean_DCache();
    int rtCode = rawWriteDma.run(kNandWritePageTimeout);

    // Check the write status result.
    if (rtCode == SUCCESS)
    {
        if (gpmi_nand_check_status(s_resultBuffer[0]) != SUCCESS)
        {
            rtCode = ERROR_DDI_NAND_HAL_WRITE_FAILED;
        }
    }
    
    // Disable writes.
    gpmi_enable_writes(false);
    
    return SUCCESS;
}

int gpmi_nand_read_page(unsigned chipSelect, uint32_t pageNumber, uint8_t * buffer, uint8_t * auxBuffer)
{
    int retval;
    
    // Prepare some info.
    uint32_t readSize = g_nandInfo.dataSize + g_nandInfo.auxSize;
    uint32_t eccMask = bch_get_buffer_mask(false, readSize, &g_nandInfo.ecc);

    // Construct the DMA descriptor chain.
    NandDma::ReadEccData readDma(
        chipSelect,  // chip enable
        kNandCommand_ReadPage1,
        NULL, // addressBytes
        g_nandInfo.totalAddressBytes,  // addressByteCount
        kNandCommand_ReadPage2,
        buffer,  //dataBuffer
        auxBuffer,   //auxBuffer
        readSize,  //readSize
        g_nandInfo.ecc,    //ecc
        eccMask);   //eccMask
    
    // Update the DMA. By providing a valid aux buffer and aux read size, the DMA will use
    // two separate read DMA descriptors.
    readDma.setAddress(0, pageNumber);

    printf("Read DMA:\n");
    readDma.dumpChain();
    
    // Make sure the BCH complete IRQ is cleared.
    bch_clear_complete_irq();
    
    // Flush the data cache to ensure that the DMA descriptor chain is in memory.
//         hw_core_invalidate_clean_DCache();

    // Start the DMA and wait for it to finish.
    retval = readDma.run(kNandReadPageTimeout);

    if (retval == SUCCESS)
    {
        // Check the ECC results.
        BchEccCorrectionInfo_t correctionInfo;
        int correctionStatus = bch_read_correction_status(auxBuffer, &correctionInfo);
        
        if (correctionStatus == kUncorrectableBitErrors)
        {
            retval = ERROR_DDI_NAND_GPMI_UNCORRECTABLE_ECC;
        }
    }

    // Clear and reenable the BCH IRQ.
    bch_clear_complete_irq();

    return retval;
}

int gpmi_nand_read_metadata(unsigned chipSelect, uint32_t pageNumber, uint8_t * buffer)
{
    int retval = SUCCESS;

    // Prepare some info. Read size is the size of metadata, block 0 data, and block 0 parity.
    uint32_t readSize = g_nandInfo.ecc.block0Size + g_nandInfo.ecc.metadataSize + BITS_TO_BYTES(g_nandInfo.ecc.block0Level * g_nandInfo.ecc.block0GaloisField);
    uint32_t eccMask = bch_get_buffer_mask(false, readSize, &g_nandInfo.ecc);

    // Allocate a temp buffer to hold block 0. We can only assume the buffer passed in as an
    // argument is large enough to hold metadata, but we have to read in all of block 0.
    uint8_t * pDataBuffer = (uint8_t *)malloc(readSize);
    assert(pDataBuffer);

    // Create DMA descriptor.
    NandDma::ReadEccData readMetadataDma(
        chipSelect,  // chip enable
        kNandCommand_ReadPage1,
        NULL, // addressBytes
        g_nandInfo.totalAddressBytes,  // addressByteCount
        kNandCommand_ReadPage2,
        pDataBuffer, //dataBuffer
        buffer,   //auxBuffer
        readSize,  //readSize
        g_nandInfo.ecc,    //ecc
        eccMask);   //eccMask

    readMetadataDma.setAddress(0, pageNumber);

    // Make sure the BCH complete IRQ is cleared.
    bch_clear_complete_irq();
    
//         hw_core_invalidate_clean_DCache();
    retval = readMetadataDma.run(kNandReadPageTimeout);

    if (retval == SUCCESS)
    {
        BchEccCorrectionInfo_t correctionInfo;
        int correctionStatus = bch_read_correction_status(buffer, &correctionInfo);
        
        if (correctionStatus == kUncorrectableBitErrors)
        {
            retval = ERROR_DDI_NAND_GPMI_UNCORRECTABLE_ECC;
        }
    }

    // Clear and reenable the BCH IRQ.
    bch_clear_complete_irq();
    
    // Free our temp buffer.
    free(pDataBuffer);

    return retval;
}

int gpmi_nand_write_page(unsigned chipSelect, uint32_t pageNumber, const uint8_t * buffer, const uint8_t * auxBuffer)
{
    int rtCode = SUCCESS;

    // Enable writes to this NAND for this scope.
    gpmi_enable_writes(true);

    // Prepare some info.
    uint32_t sendSize = g_nandInfo.dataSize + g_nandInfo.auxSize;
    uint32_t eccMask = bch_get_buffer_mask(true, sendSize, &g_nandInfo.ecc);

    // Construct the write DMA descriptor chain.
    NandDma::WriteEccData writeDma(
        chipSelect, // chipSelect,
        kNandCommand_SerialDataInput, // command1,
        NULL, // addressBytes,
        g_nandInfo.totalAddressBytes, // addressByteCount,
        kNandCommand_WritePage, // command2,
        buffer, // dataBuffer,
        auxBuffer, // auxBuffer,
        sendSize, // sendSize,
        g_nandInfo.dataSize, // dataSize,
        g_nandInfo.auxSize, // leftoverSize,
        g_nandInfo.ecc,
        eccMask);

    // Update shared DMA descriptors.
    writeDma.setAddress(0, pageNumber);
    
    // Init status read DMA.
    NandDma::ReadStatus statusDma(chipSelect, kNandCommand_ReadStatus, s_resultBuffer);
    
    // Chain the status read onto the page write.
    writeDma >> statusDma;

    printf("Write DMA:\n");
    writeDma.dumpChain();
    
    // Make sure the BCH complete IRQ is cleared.
    bch_clear_complete_irq();
    
    // Flush data cache and run DMA.
//     hw_core_clean_DCache();
    rtCode = writeDma.run(kNandWritePageTimeout);

    // Check the write status result.
    if (rtCode == SUCCESS)
    {
        if (gpmi_nand_check_status(s_resultBuffer[0]) != SUCCESS)
        {
            rtCode = ERROR_DDI_NAND_HAL_WRITE_FAILED;
        }
    }

    // Clear and reenable the BCH IRQ.
    bch_clear_complete_irq();

    // Disable writes.
    gpmi_enable_writes(false);

    // Return.
    return rtCode;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
