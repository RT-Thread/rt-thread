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
#include <stdio.h>

using namespace NandDma;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void Sequence::init(unsigned chipSelect)
{
    m_chipSelect = chipSelect;
}

int Sequence::run(uint32_t timeoutMicroseconds)
{
    gpmi_set_busy_timeout(timeoutMicroseconds);
    
    return gpmi_run_dma(this->getFirstDescriptor(), m_chipSelect, getDmaWaitMask(), timeoutMicroseconds);
}

void Sequence::dumpChain()
{
    apbh_dma_t * desc = getFirstDescriptor();
    unsigned nodeNumber = 0;
    while (desc)
    {
        printf("%d: [@0x%08x] cmd=0x%08x, bar=0x%08x", nodeNumber, (uint32_t)desc, desc->cmd.U, (uint32_t)desc->bar);
        
        unsigned pioWords = desc->cmd.B.CMDWORDS;
        if (pioWords)
        {
            apbh_dma_gpmi1_t * pioDesc = (apbh_dma_gpmi1_t *)desc;
            uint32_t * pio = (uint32_t *)&(pioDesc->gpmi_ctrl0.U);
            
            printf(", pio=(");
            while (pioWords--)
            {
                printf("0x%08x%s", *pio, pioWords ? ", " : ")");
                ++pio;
            }
        }
        printf("\n");
        
        // Move to next descriptor.
        desc = desc->nxt;
        ++nodeNumber;
    }
}

void Reset::init(unsigned chipSelect, uint8_t resetCommand)
{
    // Init superclass.
    Sequence::init(chipSelect);
    
    // Store command value.
    m_commandBuffer = resetCommand;
    
    // Init each of the components.
    m_wait1.init(chipSelect, &m_done);
    m_cmd.init(chipSelect, &m_commandBuffer, 0);
    m_wait2.init(chipSelect, &m_done);
    m_done.init();
    
    // Chain up the components.
    m_wait1 >> m_cmd >> m_wait2 >> m_done;
}

void Reset::skipPostWait()
{
    // Relink the chain to skip the second wait for ready.
    m_cmd >> m_done;
}

apbh_dma_t * Reset::getFirstDescriptor()
{
    return m_wait1.getFirstDescriptor();
}

void ImmediateRead::init(unsigned chipSelect, uint8_t command, uint8_t address, unsigned addressSize, void * buffer, unsigned resultSize)
{
    // Init superclass.
    Sequence::init(chipSelect);
    
    // Save command and address values.
    m_commandAddressBuffer[0] = command;
    m_commandAddressBuffer[1] = address;
    
    // Init components.
    m_wait.init(chipSelect, &m_done);
    m_sendCommand.init(chipSelect, m_commandAddressBuffer, addressSize);
    m_readResult.init(chipSelect, buffer, resultSize);
    m_done.init();
    
    // Chain the sequence together.
    m_wait >> m_sendCommand >> m_readResult >> m_done;
}

apbh_dma_t * ImmediateRead::getFirstDescriptor()
{
    return m_wait.getFirstDescriptor();
}

void ImmediateRead::setChipSelect(unsigned chipSelect)
{
    m_wait.setChipSelect(chipSelect);
    m_sendCommand.setChipSelect(chipSelect);
    m_readResult.setChipSelect(chipSelect);
}

void ReadId::init(unsigned chipSelect, uint8_t command, uint8_t address, void * idBuffer)
{
    // Init with 1 address bytes and 6 result bytes.
    ImmediateRead::init(chipSelect, command, address, 1, idBuffer, NAND_READ_ID_RESULT_SIZE);
}

void ReadStatus::init(unsigned chipSelect, uint8_t command, void * statusBuffer)
{
    // Init with 0 address bytes and 1 result byte.
    ImmediateRead::init(chipSelect, command, 0, 0, statusBuffer, 1);
}

void BlockErase::init(unsigned chipSelect, uint8_t command1, uint32_t address, unsigned addressByteCount, uint8_t command2)
{
    // Init superclass.
    Sequence::init(chipSelect);
    
    // Fill in command and address buffers.
    m_cle1AddressBuffer[0] = command1;
    
    assert(addressByteCount <= 4);
    m_cle1AddressBuffer[1] = address & 0xff;
    m_cle1AddressBuffer[2] = (address >> 8) & 0xff;
    m_cle1AddressBuffer[3] = (address >> 16) & 0xff;
    m_cle1AddressBuffer[4] = (address >> 24) & 0xff;
    
    m_cle2Buffer = command2;
    
    // Init components.
    m_cle1Address.init(chipSelect, m_cle1AddressBuffer, addressByteCount);
    m_cle2.init(chipSelect, &m_cle2Buffer, 0);
    m_wait.init(chipSelect, &m_done);
    m_done.init();
    
    // Chain everything together.
    m_cle1Address >> m_cle2 >> m_wait >> m_done;
}

apbh_dma_t * BlockErase::getFirstDescriptor()
{
    return m_cle1Address.getFirstDescriptor();
}

void MultiBlockErase::init(unsigned chipSelect, uint8_t command1, uint32_t address, uint32_t address2, unsigned addressByteCount, uint8_t command2)
{
    // Init the parent.
    BlockErase::init(chipSelect, command1, address, addressByteCount, command2);
    
    // Fill in command. Use the same command as for m_cle1Address.
    m_cle1AddressBuffer2[0] = command1;
    
    // Fill in address.
    assert(addressByteCount <= 4);
    m_cle1AddressBuffer2[1] = address2 & 0xff;
    m_cle1AddressBuffer2[2] = (address2 >> 8) & 0xff;
    m_cle1AddressBuffer2[3] = (address2 >> 16) & 0xff;
    m_cle1AddressBuffer2[4] = (address2 >> 24) & 0xff;
    
    // Init our second command/address descriptor.
    m_cle1Address2.init(chipSelect, m_cle1AddressBuffer2, addressByteCount);
    
    // Relink the chain to insert m_cle1Address2.
    m_cle1Address >> m_cle1Address2 >> m_cle2;
}

void ReadWriteBase::init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2)
{
    // Init superclass.
    Sequence::init(chipSelect);
    
    // Fill in commands.
    setCommands(command1, command2);
    
    // Fill in address bytes.
    assert(addressByteCount <= MAX_ROWS+MAX_COLUMNS);
    m_addressByteCount = addressByteCount;
    if (addressBytes)
    {
        memcpy(&m_cle1AddressBuffer[1], addressBytes, addressByteCount);
    }
    
    // Init the components.
    m_cle1Address.init(chipSelect, m_cle1AddressBuffer, addressByteCount);
    m_cle2.init(chipSelect, &m_cle2Buffer, 0);
    m_wait.init(chipSelect, &m_done);
    m_done.init();
}

void ReadWriteBase::setChipSelect(unsigned chipSelect)
{
    m_chipSelect = chipSelect;
    
    // Update the chip select in each of our components.
    m_cle1Address.setChipSelect(chipSelect);
    m_cle2.setChipSelect(chipSelect);
    m_wait.setChipSelect(chipSelect);
}

void ReadWriteBase::setCommands(uint8_t command1, uint8_t command2)
{
    m_cle1AddressBuffer[0] = command1;
    m_cle2Buffer = command2;
}

void ReadWriteBase::setAddress(uint8_t * addressBytes)
{
    assert(addressBytes);
    memcpy(&m_cle1AddressBuffer[1], addressBytes, m_addressByteCount);
}

void ReadWriteBase::setAddress(uint32_t col, uint32_t row)
{
    m_cle1AddressBuffer[1] = col & 0xff;
    m_cle1AddressBuffer[2] = (col >> 8) & 0xff;
    m_cle1AddressBuffer[3] = row & 0xff;
    m_cle1AddressBuffer[4] = (row >> 8) & 0xff;
    m_cle1AddressBuffer[5] = (row >> 16) & 0xff;
    m_cle1AddressBuffer[6] = (row >> 24) & 0xff;
}

void ReadWriteBase::setAddressByteCount(uint8_t addressByteCount)
{
    assert(addressByteCount <= MAX_ROWS+MAX_COLUMNS);
    m_addressByteCount = addressByteCount;
    m_cle1Address.setBufferAndCount(m_cle1AddressBuffer, addressByteCount);
}

apbh_dma_t * ReadWriteBase::getFirstDescriptor()
{
    return m_cle1Address.getFirstDescriptor();
}

void ReadRawData::init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, void * dataBuffer, uint32_t dataReadSize, void * auxBuffer, uint32_t auxReadSize)
{
    // Init superclass.
    ReadWriteBase::init(chipSelect, command1, addressBytes, addressByteCount, command2);
    
    // Chain up common components.
    m_cle1Address >> m_cle2 >> m_wait;
    
    // Init read components and chain them up.
    setBuffers(dataBuffer, dataReadSize, auxBuffer, auxReadSize);
}

void ReadRawData::setChipSelect(unsigned chipSelect)
{
    // Update superclass' components.
    ReadWriteBase::setChipSelect(chipSelect);
    
    // Update the chip select in each of our components.
    m_readData.setChipSelect(chipSelect);
    m_readAux.setChipSelect(chipSelect);
}

void ReadRawData::setBuffers(void * dataBuffer, uint32_t dataReadSize, void * auxBuffer, uint32_t auxReadSize)
{
    m_dataReadSize = dataReadSize;
    m_auxReadSize = auxReadSize;
    
    // Update read component buffers. We have to fully init these components in case they
    // weren't inited the first time through (if we started out with no buffers).
    if (dataReadSize)
    {
        m_readData.init(m_chipSelect, dataBuffer, dataReadSize);
    }
    if (auxReadSize)
    {
        m_readAux.init(m_chipSelect, auxBuffer, auxReadSize);
    }
    
    // Re-link chain depending on what buffers are being used.
    chainReadCommands();
}

void ReadRawData::chainReadCommands()
{
    if (m_dataReadSize)
    {
        m_wait >> m_readData;
        
        if (!m_auxReadSize)
        {
            m_readData >> m_done;
        }
    }
    if (m_auxReadSize)
    {
        if (m_dataReadSize)
        {
            m_readData >> m_readAux;
        }
        else
        {
            m_wait >> m_readAux;
        }
        
        m_readAux >> m_done;
    }
    
    // If no data is to be transferred, just link the terminator onto the wait.
    if (!m_dataReadSize && !m_auxReadSize)
    {
        m_wait >> m_done;
    }
}

Component::Base & ReadRawData::operator >> (Component::Base & rhs)
{
    // Chain the rhs onto the DMA descriptor prior to the terminator.
    if (m_dataReadSize && !m_auxReadSize)
    {
        m_readData >> rhs;
    }
    else if (m_auxReadSize)
    {
        m_readAux >> rhs;
    }
    else
    {
        m_wait >> rhs;
    }
    return rhs;
}

void ReadEccData::init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, void * dataBuffer, void * auxBuffer, uint32_t readSize, const BchEccLayout_t & ecc, uint32_t eccMask)
{
    // Init superclass.
    ReadWriteBase::init(chipSelect, command1, addressBytes, addressByteCount, command2);
    
    // Save the read info.
    m_readSize = readSize;
    m_ecc = ecc;
    m_eccMask = eccMask;
    
    // Init read component.
    m_readData.init(chipSelect, dataBuffer, auxBuffer, readSize, ecc, eccMask);
    
    // Chain up components.
    m_cle1Address >> m_cle2 >> m_wait >> m_readData >> m_done;
}

void ReadEccData::setChipSelect(unsigned chipSelect)
{
    // Update superclass' components.
    ReadWriteBase::setChipSelect(chipSelect);
    
    // Update the chip select in each of our components.
    m_readData.setChipSelect(chipSelect);
}

void ReadEccData::setBuffers(void * dataBuffer, void * auxBuffer)
{
    setBuffers(dataBuffer, auxBuffer, m_readSize, m_ecc, m_eccMask);
}

void ReadEccData::setBuffers(void * dataBuffer, void * auxBuffer, uint32_t readSize)
{
    setBuffers(dataBuffer, auxBuffer, readSize, m_ecc, m_eccMask);
}

void ReadEccData::setBuffers(void * dataBuffer, void * auxBuffer, uint32_t readSize, const BchEccLayout_t & ecc, uint32_t eccMask)
{
    // Update read component buffers. We have to fully init these components in case they
    // weren't inited the first time through (if we started out with no buffers).
    m_readData.setBufferAndSize(dataBuffer, auxBuffer, readSize, ecc, eccMask);
    
    // Save the read info.
    m_readSize = readSize;
    m_ecc = ecc;
    m_eccMask = eccMask;
}

uint16_t ReadEccData::getDmaWaitMask() const
{
    // The BCH engine generates interrupts for read completion.
    return kNandGpmiDmaWaitMask_GpmiDma ;
}

void WriteRawData::init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, const void * dataBuffer, uint32_t dataSize, const void * auxBuffer, uint32_t auxSize)
{
    // Init superclass.
    ReadWriteBase::init(chipSelect, command1, addressBytes, addressByteCount, command2);
    
    // Chain up common components.
    m_cle2 >> m_wait >> m_done;
    
    // Init write components and chain them up.
    setBuffers(dataBuffer, dataSize, auxBuffer, auxSize);
}

void WriteRawData::setChipSelect(unsigned chipSelect)
{
    // Update superclass' components.
    ReadWriteBase::setChipSelect(chipSelect);
    
    // Update the chip select in each of our components.
    m_writeData.setChipSelect(chipSelect);
    m_writeAux.setChipSelect(chipSelect);
}

void WriteRawData::setBuffers(const void * dataBuffer, uint32_t dataSize, const void * auxBuffer, uint32_t auxSize)
{
    m_dataWriteSize = dataSize;
    m_auxWriteSize = auxSize;
    
    // Update write component buffers. We have to fully init these components in case they
    // weren't inited the first time through (if we started out with no buffers).
    if (dataSize)
    {
        m_writeData.init(m_chipSelect, dataBuffer, dataSize);
    }
    if (auxSize)
    {
        m_writeAux.init(m_chipSelect, auxBuffer, auxSize);
    }
    
    // Re-link chain depending on what buffers are being used.
    chainWriteCommands();
}

void WriteRawData::chainWriteCommands()
{
    if (m_dataWriteSize)
    {
        m_cle1Address >> m_writeData;
        
        if (!m_auxWriteSize)
        {
            m_writeData >> m_cle2;
        }
    }
    if (m_auxWriteSize)
    {
        if (m_dataWriteSize)
        {
            m_writeData >> m_writeAux;
        }
        else
        {
            m_cle1Address >> m_writeAux;
        }
        
        m_writeAux >> m_cle2;
    }
    
    // If no data is to be transferred, just link the terminator onto the wait.
    if (!m_dataWriteSize && !m_auxWriteSize)
    {
        m_cle1Address >> m_cle2;
    }
}

Component::Base & WriteRawData::operator >> (Component::Base & rhs)
{
    // Chain the rhs onto the DMA descriptor prior to the terminator.
    m_wait >> rhs;
    return rhs;
}

void WriteEccData::init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize, const BchEccLayout_t & ecc, uint32_t eccMask)
{
    // Init superclass.
    ReadWriteBase::init(chipSelect, command1, addressBytes, addressByteCount, command2);
    
    // Save info.
    m_sendSize = sendSize;
    m_dataSize = dataSize;
    m_leftoverSize = leftoverSize;
    m_ecc = ecc;
    m_eccMask = eccMask;
    
    // Init write component.
    m_writeData.init(chipSelect, dataBuffer, auxBuffer, sendSize, dataSize, leftoverSize, ecc, eccMask);
    
    // Chain up components.
    m_cle1Address >> m_writeData >> m_cle2 >> m_wait >> m_done;
}

void WriteEccData::setChipSelect(unsigned chipSelect)
{
    // Update superclass' components.
    ReadWriteBase::setChipSelect(chipSelect);
    
    // Update the chip select in each of our components.
    m_writeData.setChipSelect(chipSelect);
}

void WriteEccData::setBuffers(const void * dataBuffer, const void * auxBuffer)
{
    setBuffers(dataBuffer, auxBuffer, m_sendSize, m_dataSize, m_leftoverSize, m_ecc, m_eccMask);
}

void WriteEccData::setBuffers(const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize)
{
    setBuffers(dataBuffer, auxBuffer, sendSize, dataSize, leftoverSize, m_ecc, m_eccMask);
}

void WriteEccData::setBuffers(const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize, const BchEccLayout_t & ecc, uint32_t eccMask)
{
    // Update write component buffers. We have to fully init these components in case they
    // weren't inited the first time through (if we started out with no buffers).
    m_writeData.setBufferAndSize(dataBuffer, auxBuffer, sendSize, dataSize, leftoverSize, ecc, eccMask);
    
    // Save info.
    m_sendSize = sendSize;
    m_dataSize = dataSize;
    m_leftoverSize = leftoverSize;
    m_ecc = ecc;
    m_eccMask = eccMask;
    
    // Must relink the descriptor chain. Changing the buffers could change whether the aux data
    // send descriptor is used.
    m_writeData >> m_cle2;
}

uint16_t WriteEccData::getDmaWaitMask() const
{
    // The BCH engine generates interrupts for write completion.
    return kNandGpmiDmaWaitMask_GpmiDma | kNandGpmiDmaWaitMask_Ecc;
}

////////////////////////////////////////////////////////////////////////////////
// End of file
////////////////////////////////////////////////////////////////////////////////

