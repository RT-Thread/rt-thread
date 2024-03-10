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

#include "gpmi_nand_dma.h"
#include <algorithm>

using namespace NandDma;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

__STATIC_TEXT void Component::CommandAddress::init(unsigned chipSelect, const uint8_t * buffer, unsigned aleCount)
{
//    tx_dma.nxt = 0;
    tx_dma.cmd.U = (BF_APBH_CHn_CMD_XFER_COUNT(1 + aleCount)
        | BF_APBH_CHn_CMD_CMDWORDS(3)
        | BF_APBH_CHn_CMD_HALTONTERMINATE(1)
        | BF_APBH_CHn_CMD_WAIT4ENDCMD(1)
        | BF_APBH_CHn_CMD_SEMAPHORE(0)
        | BF_APBH_CHn_CMD_NANDLOCK(1)
        | BF_APBH_CHn_CMD_CHAIN(1)
        | BV_FLD(APBH_CHn_CMD, COMMAND, DMA_READ));

    tx_dma.bar = nand_virtual_to_physical(buffer);

    // Need to set CLE high, then send command, then clear CLE, set ALE high
    // send # address bytes (Column then row).
    // Address increment is only enabled if there is at least one address byte.
    tx_dma.gpmi_ctrl0.U = (BV_FLD(GPMI_CTRL0, COMMAND_MODE, WRITE)
        | BF_GPMI_CTRL0_WORD_LENGTH(BV_GPMI_CTRL0_WORD_LENGTH__8_BIT)
        | BF_GPMI_CTRL0_LOCK_CS(1)
        | BF_GPMI_CTRL0_CS(chipSelect)
        | BV_FLD(GPMI_CTRL0, ADDRESS, NAND_CLE)
        | BF_GPMI_CTRL0_ADDRESS_INCREMENT((aleCount > 0) ? BV_GPMI_CTRL0_ADDRESS_INCREMENT__ENABLED : 0)
        | BF_GPMI_CTRL0_XFER_COUNT(1 + aleCount));
    
    tx_dma.gpmi_compare.U = 0;
    tx_dma.gpmi_eccctrl.U = 0;
}

__STATIC_TEXT void Component::CommandAddress::setChipSelect(unsigned chipSelect)
{
    tx_dma.gpmi_ctrl0.B.CS = chipSelect;
}

__STATIC_TEXT void Component::CommandAddress::setBufferAndCount(const uint8_t * buffer, unsigned addressCount)
{
    tx_dma.bar = nand_virtual_to_physical(buffer);
    
    // Rebuild the entire gpmi_ctrl0 value.
    tx_dma.gpmi_ctrl0.B.ADDRESS_INCREMENT = (addressCount > 0 ? BV_GPMI_CTRL0_ADDRESS_INCREMENT__ENABLED : 0);
    tx_dma.gpmi_ctrl0.B.XFER_COUNT = 1 + addressCount;
}

__STATIC_TEXT apbh_dma_t * Component::CommandAddress::getFirstDescriptor()
{
    return reinterpret_cast<apbh_dma_t *>(&tx_dma);
}

__STATIC_TEXT void Component::WaitForReady::init(unsigned chipSelect, Terminator * fail)
{
    // First we want to wait for Ready. Set GPMI wait for ready.
    wait.nxt = reinterpret_cast<apbh_dma_gpmi1_t *>(nand_virtual_to_physical(&sense));
    wait.cmd.U = (BF_APBH_CHn_CMD_CMDWORDS(1)
        | BF_APBH_CHn_CMD_HALTONTERMINATE(1)
        | BF_APBH_CHn_CMD_WAIT4ENDCMD(1)
        | BF_APBH_CHn_CMD_NANDWAIT4READY(1)
        | BF_APBH_CHn_CMD_NANDLOCK(0)
        | BF_APBH_CHn_CMD_CHAIN(1)
        | BV_FLD(APBH_CHn_CMD, COMMAND, NO_DMA_XFER));
    wait.bar = 0;
    wait.gpmi_ctrl0.U = (BV_FLD(GPMI_CTRL0, COMMAND_MODE, WAIT_FOR_READY)
        | BF_GPMI_CTRL0_WORD_LENGTH(BV_GPMI_CTRL0_WORD_LENGTH__8_BIT)
        | BV_FLD(GPMI_CTRL0, ADDRESS, NAND_DATA)
        | BF_GPMI_CTRL0_CS(chipSelect));
    
    // Now check for successful Ready. BAR points to alternate branch if timeout occurs.
//    sense.nxt = 0;
    sense.cmd.U = (BF_APBH_CHn_CMD_CMDWORDS(0)
        | BF_APBH_CHn_CMD_HALTONTERMINATE(1)
        | BF_APBH_CHn_CMD_SEMAPHORE(0)
        | BF_APBH_CHn_CMD_NANDLOCK(0)
        | BF_APBH_CHn_CMD_CHAIN(1)
        | BV_FLD(APBH_CHn_CMD, COMMAND, DMA_SENSE));
    sense.bar = nand_virtual_to_physical(&fail->failure);
    sense.gpmi_ctrl0.U = 0;
}

__STATIC_TEXT void Component::WaitForReady::setChipSelect(unsigned chipSelect)
{
    wait.gpmi_ctrl0.B.CS = chipSelect;
}

__STATIC_TEXT apbh_dma_t * Component::WaitForReady::getFirstDescriptor()
{
    return reinterpret_cast<apbh_dma_t *>(&wait);
}

void Component::Terminator::init()
{
    // No next descriptor in the chain.
    success.nxt = 0;
    failure.nxt = 0;

    // Decrement semaphore, set IRQ, no DMA transfer.
    success.cmd.U = (BF_APBH_CHn_CMD_IRQONCMPLT(1)
        | BF_APBH_CHn_CMD_WAIT4ENDCMD(0) //1)   XXX changed on MX6 
        | BF_APBH_CHn_CMD_SEMAPHORE(1)
        | BV_FLD(APBH_CHn_CMD, COMMAND, NO_DMA_XFER));

    // The failure descriptor uses exactly the same DMA command as success.
    failure.cmd.U = success.cmd.U;

    // The bar holds the result code, either success or an error code. It is up to
    // the DMA handling code to read the result code out of the APBH register.
    success.bar = (void *)SUCCESS;
    failure.bar = (void *)ERROR_DDI_NAND_GPMI_DMA_TIMEOUT;
}

__STATIC_TEXT apbh_dma_t * Component::Terminator::getFirstDescriptor()
{
    return reinterpret_cast<apbh_dma_t *>(&success);
}

__STATIC_TEXT void Component::ReceiveRawData::init(unsigned chipSelect, void * buffer, uint32_t readSize)
{
    // Don't set the next pointer yet.
//    receiveData.nxt = 0;
    
    // ECC is disabled. Configure DMA to write directly to memory.
    // Wait for end command from GPMI before next part of chain.
    // Lock GPMI to this NAND during transfer.
    receiveData.cmd.U = (BF_APBH_CHn_CMD_XFER_COUNT(readSize)
        | BF_APBH_CHn_CMD_CMDWORDS(1)
        | BF_APBH_CHn_CMD_HALTONTERMINATE(1)
        | BF_APBH_CHn_CMD_WAIT4ENDCMD(1)
        | BF_APBH_CHn_CMD_SEMAPHORE(0)
        | BF_APBH_CHn_CMD_NANDLOCK(0)
        | BF_APBH_CHn_CMD_CHAIN(1)
        | BV_FLD(APBH_CHn_CMD, COMMAND, DMA_WRITE));

    // Save Data into buffer.
    assert((((uint32_t)buffer) & 0x3) == 0);
    receiveData.bar = nand_virtual_to_physical(buffer);
    
    // Setup GPMI for 8-bit read.
    receiveData.gpmi_ctrl0.U = (BV_FLD(GPMI_CTRL0, COMMAND_MODE, READ)
        | BV_FLD(GPMI_CTRL0, WORD_LENGTH, 8_BIT)
        | BF_GPMI_CTRL0_CS(chipSelect)
        | BF_GPMI_CTRL0_LOCK_CS(0)
        | BV_FLD(GPMI_CTRL0, ADDRESS, NAND_DATA)
        | BF_GPMI_CTRL0_XFER_COUNT(readSize));
}

__STATIC_TEXT void Component::ReceiveRawData::setChipSelect(unsigned chipSelect)
{
    receiveData.gpmi_ctrl0.B.CS = chipSelect;
}

__STATIC_TEXT void Component::ReceiveRawData::setBufferAndSize(void * buffer, uint32_t readSize)
{
    // Update read size.
    receiveData.cmd.B.XFER_COUNT = readSize;
    receiveData.gpmi_ctrl0.B.XFER_COUNT = readSize;

    // Update buffer address.
    assert((((uint32_t)buffer) & 0x3) == 0);
    receiveData.bar = nand_virtual_to_physical(buffer);
}

__STATIC_TEXT apbh_dma_t * Component::ReceiveRawData::getFirstDescriptor()
{
    return reinterpret_cast<apbh_dma_t *>(&receiveData);
}

__STATIC_TEXT void Component::SendRawData::init(unsigned chipSelect, const void * buffer, uint32_t sendSize)
{
    // nxt pointer is not set here
    sendData.cmd.U = (BF_APBH_CHn_CMD_XFER_COUNT(sendSize)
        | BF_APBH_CHn_CMD_CMDWORDS(1)
        | BF_APBH_CHn_CMD_HALTONTERMINATE(1)
        | BF_APBH_CHn_CMD_WAIT4ENDCMD(1)
        | BF_APBH_CHn_CMD_NANDLOCK(1)
        | BF_APBH_CHn_CMD_SEMAPHORE(0)
        | BF_APBH_CHn_CMD_CHAIN(1)
        | BV_FLD(APBH_CHn_CMD, COMMAND, DMA_READ));
    sendData.bar = nand_virtual_to_physical(const_cast<void *>(buffer));
    sendData.gpmi_ctrl0.U = (BV_FLD(GPMI_CTRL0, COMMAND_MODE, WRITE)
        | BV_FLD(GPMI_CTRL0, WORD_LENGTH, 8_BIT)
        | BF_GPMI_CTRL0_LOCK_CS(1)
        | BF_GPMI_CTRL0_CS(chipSelect)
        | BV_FLD(GPMI_CTRL0, ADDRESS, NAND_DATA)
        | BF_GPMI_CTRL0_XFER_COUNT(sendSize));
}

__STATIC_TEXT void Component::SendRawData::setChipSelect(unsigned chipSelect)
{
    sendData.gpmi_ctrl0.B.CS = chipSelect;
}

__STATIC_TEXT void Component::SendRawData::setBufferAndSize(const void * buffer, uint32_t sendSize)
{
    // Update read size.
    sendData.cmd.B.XFER_COUNT = sendSize;
    sendData.gpmi_ctrl0.B.XFER_COUNT = sendSize;

    // Update buffer address.
    assert((((uint32_t)buffer) & 0x3) == 0);
    sendData.bar = nand_virtual_to_physical(const_cast<void *>(buffer));
}

__STATIC_TEXT apbh_dma_t * Component::SendRawData::getFirstDescriptor()
{
    return reinterpret_cast<apbh_dma_t *>(&sendData);
}

__STATIC_TEXT void Component::ReceiveEccData::init(unsigned chipSelect, void * dataBuffer, void * auxBuffer, uint32_t readSize, const BchEccLayout_t & ecc, uint32_t eccMask)
{
    // Link up to the next 
    receiveData.nxt = reinterpret_cast<apbh_dma_gpmi1_t *>(nand_virtual_to_physical(&waitForRead));

    // Get info about the given ECC type.
//     const EccTypeInfo_t * info = ecc.getTypeInfo();
//     assert(info);

    // Configure APBH DMA to NOT read any bytes from the NAND into memory using GPMI.  The ECC will
    // become the Bus Master and write the read data into memory. Wait for end command from GPMI
    // before next part of chain. Lock GPMI to this NAND during transfer.
    // NO_DMA_XFER - No DMA transfer occurs on APBH - see above.
    receiveData.cmd.U = (BF_APBH_CHn_CMD_XFER_COUNT(0)
        | BF_APBH_CHn_CMD_CMDWORDS(6)
        | BF_APBH_CHn_CMD_HALTONTERMINATE(1)
        | BF_APBH_CHn_CMD_WAIT4ENDCMD(1)
        | BF_APBH_CHn_CMD_SEMAPHORE(0)
        | BF_APBH_CHn_CMD_NANDLOCK(1)
        | BF_APBH_CHn_CMD_CHAIN(1)
        | BV_FLD(APBH_CHn_CMD, COMMAND, NO_DMA_XFER));

    // Save Data into buffer.
    receiveData.bar = 0;               // This field isn't used.
    receiveData.gpmi_compare.U = 0;    // This field isn't used.

    // Setup GPMI bus for Read Sector Result.
    // Note - althought the GPMI knows more than one byte/word may be
    //        sent, the APBH assumes bytes only.
    receiveData.gpmi_ctrl0.U = (BV_FLD(GPMI_CTRL0, COMMAND_MODE, READ)
        | BF_GPMI_CTRL0_WORD_LENGTH(BV_GPMI_CTRL0_WORD_LENGTH__8_BIT)
        | BF_GPMI_CTRL0_CS(chipSelect)
        | BF_GPMI_CTRL0_LOCK_CS(0)
        | BV_FLD(GPMI_CTRL0, ADDRESS, NAND_DATA)
        | BF_GPMI_CTRL0_XFER_COUNT(readSize));

//     receiveData.gpmi_eccctrl.U = (BW_GPMI_ECCCTRL_ECC_CMD(info->decodeCommand)
//         | BW_GPMI_ECCCTRL_ENABLE_ECC(BV_GPMI_ECCCTRL_ENABLE_ECC__ENABLE)
//         | BW_GPMI_ECCCTRL_BUFFER_MASK(eccMask) );
    receiveData.gpmi_eccctrl.U = (BV_FLD(GPMI_ECCCTRL, ECC_CMD, DECODE)
        | BV_FLD(GPMI_ECCCTRL, ENABLE_ECC, ENABLE)
        | BF_GPMI_ECCCTRL_BUFFER_MASK(eccMask) );
    receiveData.gpmi_ecccount.U = BF_GPMI_ECCCOUNT_COUNT(readSize);

    // Setup the data buffer.
    assert(((uint32_t)dataBuffer & 0x3) == 0);
    receiveData.gpmi_payload.U = reinterpret_cast<reg32_t>(nand_virtual_to_physical(dataBuffer));

    // And the Auxiliary buffer here.
    assert(((uint32_t)auxBuffer & 0x3) == 0);
    receiveData.gpmi_auxiliary.U = reinterpret_cast<reg32_t>(nand_virtual_to_physical(auxBuffer));
                       
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Don't set the next pointer for our last descriptor.
//    waitForRead.nxt = 0;

    // Configure to send 3 GPMI PIO reads.
    waitForRead.cmd.U = (BF_APBH_CHn_CMD_CMDWORDS(3)
        | BF_APBH_CHn_CMD_WAIT4ENDCMD(1)
        | BF_APBH_CHn_CMD_NANDWAIT4READY(1)
        | BF_APBH_CHn_CMD_CHAIN(1)
        | BF_APBH_CHn_CMD_NANDLOCK(1)
        | BV_FLD(APBH_CHn_CMD, COMMAND, NO_DMA_XFER));

    // Nothing to be sent.
    waitForRead.bar = NULL;

    // Disable the Chip Select and other outstanding GPMI things.
    waitForRead.gpmi_ctrl0.U = (BV_FLD(GPMI_CTRL0, COMMAND_MODE, WAIT_FOR_READY)
        | BF_GPMI_CTRL0_WORD_LENGTH(BV_GPMI_CTRL0_WORD_LENGTH__8_BIT)
        | BF_GPMI_CTRL0_LOCK_CS(0)
        | BF_GPMI_CTRL0_CS(chipSelect)
        | BV_FLD(GPMI_CTRL0, ADDRESS, NAND_DATA)
        | BF_GPMI_CTRL0_ADDRESS_INCREMENT(0)
        | BF_GPMI_CTRL0_XFER_COUNT(0));

    // Ignore the compare - we need to skip over it.
    waitForRead.gpmi_compare.U = 0;

    // Disable the ECC Block.
    waitForRead.gpmi_eccctrl.U = BF_GPMI_ECCCTRL_ENABLE_ECC(BV_GPMI_ECCCTRL_ENABLE_ECC__DISABLE);
}

__STATIC_TEXT void Component::ReceiveEccData::setChipSelect(unsigned chipSelect)
{
    receiveData.gpmi_ctrl0.B.CS = chipSelect;
    waitForRead.gpmi_ctrl0.B.CS = chipSelect;
}

__STATIC_TEXT void Component::ReceiveEccData::setBufferAndSize(void * dataBuffer, void * auxBuffer, uint32_t readSize, const BchEccLayout_t & ecc, uint32_t eccMask)
{
    // Change the size.
    receiveData.gpmi_ctrl0.B.XFER_COUNT = readSize;

    // Get info about the given ECC type.
//     const EccTypeInfo_t * info = ecc.getTypeInfo();
//     assert(info);

//     receiveData.gpmi_eccctrl.U = (BW_GPMI_ECCCTRL_ECC_CMD(info->decodeCommand)
//         | BW_GPMI_ECCCTRL_ENABLE_ECC(BV_GPMI_ECCCTRL_ENABLE_ECC__ENABLE)
//         | BW_GPMI_ECCCTRL_BUFFER_MASK(eccMask) );
    receiveData.gpmi_eccctrl.U = (BV_FLD(GPMI_ECCCTRL, ECC_CMD, DECODE)
        | BV_FLD(GPMI_ECCCTRL, ENABLE_ECC, ENABLE)
        | BF_GPMI_ECCCTRL_BUFFER_MASK(eccMask) );
    receiveData.gpmi_ecccount.U = BF_GPMI_ECCCOUNT_COUNT(readSize);
    
    // Setup the data buffer.
    assert(((uint32_t)dataBuffer & 0x3) == 0);
    receiveData.gpmi_payload.U = reinterpret_cast<reg32_t>(nand_virtual_to_physical(dataBuffer));

    // And the Auxiliary buffer here.
    assert(((uint32_t)auxBuffer & 0x3) == 0);
    receiveData.gpmi_auxiliary.U = reinterpret_cast<reg32_t>(nand_virtual_to_physical(auxBuffer));    
}

__STATIC_TEXT apbh_dma_t * Component::ReceiveEccData::getFirstDescriptor()
{
    return reinterpret_cast<apbh_dma_t *>(&receiveData);
}

__STATIC_TEXT void Component::SendEccData::init(unsigned chipSelect, const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize, const BchEccLayout_t & ecc, uint32_t eccMask)
{
    uint32_t u32EccMask = eccMask;
    uint32_t u32Data = dataSize;
    uint32_t u32Leftover = leftoverSize;
    uint32_t u32EccDataSize=0;

    // Start off linking to the send aux data descriptor.
    sendData.nxt = 0;
//     sendData.nxt = reinterpret_cast<apbh_dma_gpmi1_t *>(nand_virtual_to_physical(&sendAuxData));
//     skipSendAuxData = true; //false;

    // Configure APBH DMA to write size bytes into the NAND from
    // memory using GPMI.
    // Wait for end command from GPMI before next part of chain.
    // Lock GPMI to this NAND during transfer.
    // DMA_READ - Perform PIO word transfers then transfer
    //            from memory to peripheral for specified # of bytes.
    // Calculate the number of 512 byte packets we want.
//     sendSize = u32Data;

    // Setup the data buffer.
    sendData.gpmi_payload.U = reinterpret_cast<reg32_t>(nand_virtual_to_physical(const_cast<void *>(dataBuffer)));
    // And the Auxiliary buffer here.
    sendData.gpmi_auxiliary.U = reinterpret_cast<reg32_t>(nand_virtual_to_physical(const_cast<void *>(auxBuffer)));

    // if there are any leftovers, assume they are redundant area
    if (u32Leftover)
    {
//         u32EccDataSize = eccInfo->metadataSize;
        u32EccDataSize = ecc.metadataSize;
    }

    // In the case of a redundant only write, make this one do the actual write.
    if (!u32Data)
    {
        u32Data = u32EccDataSize;
        u32EccDataSize = 0;
    }

    // Set DMA command.
    // Applies to BCH ECC. (TransferSize,Semaphore,CommandWords,Wait4End,DmaType)
    sendData.cmd.U = (BF_APBH_CHn_CMD_XFER_COUNT(0)
        | BF_APBH_CHn_CMD_CMDWORDS(6)
        | BF_APBH_CHn_CMD_HALTONTERMINATE(1)
        | BF_APBH_CHn_CMD_WAIT4ENDCMD(1) // 
        | BF_APBH_CHn_CMD_NANDLOCK(1)
        | BF_APBH_CHn_CMD_SEMAPHORE(0)
        | BF_APBH_CHn_CMD_CHAIN(1)
        | BV_FLD(APBH_CHn_CMD, COMMAND, NO_DMA_XFER));

    // If there is no ECC data to send, skip that descriptor.
//     if (!u32EccDataSize)
//     {
//         skipSendAuxData = true;
// //        sendData.nxt = (apbh_dma_gpmi1_t *)nand_virtual_to_physical(&(pChain->tx_cle2_dma));
// 
//         // Wait for End on this descriptor.
//         // Applies to BCH ECC.
//         sendData.cmd.B.WAIT4ENDCMD = 1;
//         sendData.cmd.B.NANDWAIT4READY = 0;
//     }

    // Setup GPMI bus for Write Sector.  GPMI Write.
    // Write WriteSize words (16 or 8 bit) data
    // Note - althought the GPMI knows more than one byte/word may be
    //        sent, the APBH assumes bytes only.
    // Applies to BCH ECC.
    sendData.gpmi_ctrl0.U = (BV_FLD(GPMI_CTRL0, COMMAND_MODE, WRITE)
        | BF_GPMI_CTRL0_WORD_LENGTH(BV_GPMI_CTRL0_WORD_LENGTH__8_BIT)
        | BF_GPMI_CTRL0_LOCK_CS(1)
        | BF_GPMI_CTRL0_CS(chipSelect)
        | BV_FLD(GPMI_CTRL0, ADDRESS, NAND_DATA)
        | BF_GPMI_CTRL0_XFER_COUNT(0));

    // Compare isn't used.
    sendData.gpmi_compare.U = 0;

    // Setup ECC for the appropriate size.
    // Setup the mask for the ECC so it knows what to expect.
//     sendData.gpmi_eccctrl.U = (BW_GPMI_ECCCTRL_ECC_CMD(eccInfo->encodeCommand)
//         | BW_GPMI_ECCCTRL_ENABLE_ECC(BV_GPMI_ECCCTRL_ENABLE_ECC__ENABLE)
//         | BW_GPMI_ECCCTRL_BUFFER_MASK(u32EccMask) );
    sendData.gpmi_eccctrl.U = (BV_FLD(GPMI_ECCCTRL, ECC_CMD, ENCODE)
        | BV_FLD(GPMI_ECCCTRL, ENABLE_ECC, ENABLE)
        | BF_GPMI_ECCCTRL_BUFFER_MASK(u32EccMask) );

    // Select the total number of bytes being sent.
    sendData.gpmi_ecccount.U = BF_GPMI_ECCCOUNT_COUNT(sendSize);

    // Set Buffer Address Register to WriteBuffer.
    sendData.bar = 0; // nand_virtual_to_physical(const_cast<void *>(dataBuffer));
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Configure APBH DMA to write size bytes into the NAND from
    // memory using GPMI.
    // Wait for end command from GPMI before next part of chain.
    // Lock GPMI to this NAND during transfer.
    // DMA_READ - Perform PIO word transfers then transfer
    //            from memory to peripheral for specified # of bytes.
//     sendAuxData.cmd.U = (BF_APBH_CHn_CMD_XFER_COUNT(u32EccDataSize)
//         | BF_APBH_CHn_CMD_CMDWORDS(0)
//         | BF_APBH_CHn_CMD_HALTONTERMINATE(1)
//         | BF_APBH_CHn_CMD_WAIT4ENDCMD(0) // 1 
//         | BF_APBH_CHn_CMD_NANDLOCK(1)
//         | BF_APBH_CHn_CMD_SEMAPHORE(0)
//         | BF_APBH_CHn_CMD_CHAIN(1)
//         | BV_FLD(APBH_CHn_CMD, COMMAND, DMA_READ));
//     sendAuxData.bar = nand_virtual_to_physical(const_cast<void *>(auxBuffer));
//     sendAuxData.gpmi_ctrl0.U = 0;
}

__STATIC_TEXT void Component::SendEccData::setChipSelect(unsigned chipSelect)
{
    sendData.gpmi_ctrl0.B.CS = chipSelect;
//     sendAuxData.gpmi_ctrl0.B.CS = chipSelect;
}

__STATIC_TEXT void Component::SendEccData::setBufferAndSize(const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize, const BchEccLayout_t & ecc, uint32_t eccMask)
{
    // Grab the current chip select from one of our descriptors.
    unsigned cs = sendData.gpmi_ctrl0.B.CS;
    
    // Reinit the whole thing.
    init(cs, dataBuffer, auxBuffer, sendSize, dataSize, leftoverSize, ecc, eccMask);
}

__STATIC_TEXT apbh_dma_t * Component::SendEccData::getFirstDescriptor()
{
    return reinterpret_cast<apbh_dma_t *>(&sendData);
}

///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////
