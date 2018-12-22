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
#ifndef _NAND_DMA_H
#define _NAND_DMA_H

#include <stdint.h>
#include <assert.h>
#include "registers/regsapbh.h"
#include "registers/regsgpmi.h"
#include "gpmi/gpmi.h"
#include "gpmi/bch_ecc.h"
#include "gpmi_internal.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Macro to word align a variable or struct member.
#define __ALIGN4__ __attribute__((aligned(4)))

#define __STATIC_TEXT

//! @name APBH DMA Structures
//@{

//! Define the APBH DMA structure without GPMI transfers.
typedef struct _apbh_dma_t
{
    struct _apbh_dma_t*   nxt;
    hw_apbh_chn_cmd_t     cmd;
    void*                 bar;
} apbh_dma_t;

//! Define the APBH DMA structure with 1 GPMI Parameter word writes.
typedef struct _apbh_dma_gpmi1_t
{
    struct _apbh_dma_gpmi1_t*	nxt;
    hw_apbh_chn_cmd_t           cmd;
    void*                       bar;
    hw_gpmi_ctrl0_t       gpmi_ctrl0;
} apbh_dma_gpmi1_t;

//! Define the APBH DMA structure with 3 GPMI Parameter word writes.
typedef struct _apbh_dma_gpmi3_t
{
    struct _apbh_dma_gpmi1_t*	  nxt;
    hw_apbh_chn_cmd_t             cmd;
    void*                         bar;
    hw_gpmi_ctrl0_t       gpmi_ctrl0;
    hw_gpmi_compare_t     gpmi_compare;
    hw_gpmi_eccctrl_t     gpmi_eccctrl;
} apbh_dma_gpmi3_t;

//! Define the APBH DMA structure with 6 GPMI Parameter word writes.
typedef struct _apbh_dma_gpmi6_t
{
    struct _apbh_dma_gpmi1_t*	  nxt;
    hw_apbh_chn_cmd_t             cmd;
    void*                         bar;
    hw_gpmi_ctrl0_t       gpmi_ctrl0;
    hw_gpmi_compare_t     gpmi_compare;
    hw_gpmi_eccctrl_t     gpmi_eccctrl;
    hw_gpmi_ecccount_t    gpmi_ecccount;
    hw_gpmi_payload_t     gpmi_payload;
    hw_gpmi_auxiliary_t   gpmi_auxiliary;
} apbh_dma_gpmi6_t;

//@}

//! @name NAND address constants
//@{
#define MAX_COLUMNS     2       //!< Current NANDs only use 2 bytes for column.
#define MAX_ROWS        4       //!< Current raw NANDs use a max of 3 bytes for row. LBA-NANDs can have 4 row bytes.
//@}

//! @brief Size in bytes of a Read ID command result.
#define NAND_READ_ID_RESULT_SIZE (6)

#if defined(__cplusplus)

//! @brief Contains GPMI NAND DMA classes.
namespace NandDma
{

//! @brief Contains the NAND DMA component classes.
namespace Component
{
    
/*!
 * @brief Base class for DMA components.
 *
 * This base class serves to provide a common superclass for all DMA component
 * classes. It also provides a method for getting the address of the first DMA
 * descriptor in the component, and it provides the base chaining operator declaration
 * and implementation.
 */
class Base
{
public:
    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor()=0;
    
    //! @brief Chaining operator.
    //!
    //! This operator has to be virtual because of the way we return the right-hand
    //! side of the binary operator expression (as a base type). Yet, we need the correct
    //! implementation of operator>> to be called so it can modify its DMA descriptor.
    //!
    //! The default implementation of this chaining operator will assert if called.
    //! Subclasses need to provide their own implementation if intended to be called.
    virtual Base & operator >> (Base & rhs) { assert(0); return rhs; }
};

/*!
 * @brief Command and address DMA component.
 *
 * CLE + ALE*
 * One command byte followed by zero or more address bytes.
 */
class CommandAddress : public Base
{
public:
    apbh_dma_gpmi3_t tx_dma;    //!< Command/address descriptor.
    
    //! @brief Component initializer.
    void init(unsigned chipSelect, const uint8_t * buffer, unsigned aleCount);
    
    //! @brief Change only the chip select number.
    void setChipSelect(unsigned chipSelect);
    
    //! @brief Modify the command/address buffer and address byte count.
    void setBufferAndCount(const uint8_t * buffer, unsigned addressCount);

    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
        tx_dma.nxt = (apbh_dma_gpmi1_t *)nand_virtual_to_physical(rhs.getFirstDescriptor());
        return rhs;
    }
};

/*!
 * @brief DMA terminator.
 */
class Terminator : public Base
{
public:
    apbh_dma_t success; //!< Successful DMA termination descriptor.
    apbh_dma_t failure; //!< Failed DMA termination descriptor (usually timeout).

    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Component initializer.
    void init();
};

/*!
 * @brief Wait for ready DMA component.
 */
class WaitForReady : public Base
{
public:
    apbh_dma_gpmi1_t wait;  //!< Wait for ready descriptor.
    apbh_dma_gpmi1_t sense; //!< Sense ready descriptor.
    
    //! @brief Component initializer.
    void init(unsigned chipSelect, Terminator * fail);
    
    //! @brief Change only the chip select number.
    void setChipSelect(unsigned chipSelect);

    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
        sense.nxt = (apbh_dma_gpmi1_t *)nand_virtual_to_physical(rhs.getFirstDescriptor());
        return rhs;
    }
};

/*!
 * @brief Read raw data DMA component.
 */
class ReceiveRawData : public Base
{
public:
    apbh_dma_gpmi1_t receiveData;   //!< Receive data descriptor.
    
    //! @brief Component initializer.
    void init(unsigned chipSelect, void * buffer, uint32_t readSize);
    
    //! @brief Change only the chip select number.
    void setChipSelect(unsigned chipSelect);
    
    //! @brief Update buffers.
    void setBufferAndSize(void * buffer, uint32_t readSize);

    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
        receiveData.nxt = (apbh_dma_gpmi1_t *)nand_virtual_to_physical(rhs.getFirstDescriptor());
        return rhs;
    }
};

/*!
 * @brief Send raw data DMA component.
 */
class SendRawData : public Base
{
public:
    apbh_dma_gpmi1_t sendData;  //!< Descriptor to send raw data.
    
    //! @brief Component initializer.
    void init(unsigned chipSelect, const void * buffer, uint32_t sendSize);
    
    //! @brief Change only the chip select number.
    void setChipSelect(unsigned chipSelect);
    
    //! @brief Update buffers.
    void setBufferAndSize(const void * buffer, uint32_t sendSize);

    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
        sendData.nxt = (apbh_dma_gpmi1_t *)nand_virtual_to_physical(rhs.getFirstDescriptor());
        return rhs;
    }
};

/*!
 * @brief Receive data through the ECC engine.
 */
class ReceiveEccData : public Base
{
public:
    apbh_dma_gpmi6_t receiveData;   //!< Receive data descriptor.
    apbh_dma_gpmi3_t waitForRead;   //!< Descriptor to wait for the read to complete and disable ECC.
    
    //! @brief Component initializer.
    void init(unsigned chipSelect, void * dataBuffer, void * auxBuffer, uint32_t readSize, const BchEccLayout_t & ecc, uint32_t eccMask);
    
    //! @brief Change only the chip select number.
    void setChipSelect(unsigned chipSelect);
    
    //! @brief Update buffers.
    void setBufferAndSize(void * dataBuffer, void * auxBuffer, uint32_t readSize, const BchEccLayout_t & ecc, uint32_t eccMask);

    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
        waitForRead.nxt = (apbh_dma_gpmi1_t *)nand_virtual_to_physical(rhs.getFirstDescriptor());
        return rhs;
    }
};

/*!
 * @brief DMA component to send data through the ECC engine.
 */
class SendEccData : public Base
{
public:
    apbh_dma_gpmi6_t sendData;  //!< Descriptor to send data with ECC.
//     apbh_dma_gpmi1_t sendAuxData;   //!< Descriptor to send aux data for certain ECC types.
    
//     bool skipSendAuxData;   //!< Set to true if the sendAuxData descriptor is unused.
    
    //! @brief Component initializer.
    void init(unsigned chipSelect, const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize, const BchEccLayout_t & ecc, uint32_t eccMask);
    
    //! @brief Change only the chip select number.
    void setChipSelect(unsigned chipSelect);
    
    //! @brief Update buffers.
    //!
    //! @note Because of how whether or not the #sendAuxData descriptor is used depends on the
    //! buffers, you should relink the chain from this component and the next one any time you
    //! call this method.
    void setBufferAndSize(const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize, const BchEccLayout_t & ecc, uint32_t eccMask);

    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
//         (skipSendAuxData ? sendData.nxt : sendAuxData.nxt) = (apbh_dma_gpmi1_t *)nand_virtual_to_physical(rhs.getFirstDescriptor());
        sendData.nxt = (apbh_dma_gpmi1_t *)nand_virtual_to_physical(rhs.getFirstDescriptor());
        return rhs;
    }
};

} // namespace Component

/*!
 * @brief DMA sequence base class.
 *
 * This class provides some common functionality for all DMA sequences. This class is
 * derived from the DMA component base class, so all DMA sequences are also DMA
 * components.
 *
 * This class is abstract. Subclasses must implement the getFirstDescriptor() method.
 */
class Sequence : public Component::Base
{
public:

    //! The chip select on which this DMA will execute.
    unsigned m_chipSelect;
    
    //! @brief Default constructor.
    inline Sequence() : m_chipSelect(0) {}
    
    //! @brief Constructor taking the chip select.
    inline Sequence(unsigned chipSelect) : m_chipSelect(chipSelect) {}
    
    //! @brief Initializer.
    void init(unsigned chipSelect);
    
    //! @brief Start DMA and wait for it to complete.
    virtual int run(uint32_t timeoutMicroseconds);
    
    //! @brief Returns the wait mask required for this DMA.
    virtual uint16_t getDmaWaitMask() const { return kNandGpmiDmaWaitMask_GpmiDma; }
    
    //! @brief Print descriptor info.
    void dumpChain();
};

/*!
 * @brief Wraps an arbitrary DMA descriptor chain.
 *
 * Use this class to wrap up a DMA that is composed of arbitrary DMA component instances not
 * collected into their own Sequence subclass. Doing so lets you use the Sequence::start()
 * and Sequence::startAndWait() methods.
 */
class WrappedSequence : public Sequence
{
public:
    apbh_dma_t * m_dmaStart; //!< The first DMA descriptor.
    uint16_t m_dmaMask;     //!< DMA wait mask. #kNandGpmiDmaWaitMask_GpmiDma is always added to this value!
    
    //! @brief Default constructor.
    inline WrappedSequence() : Sequence(), m_dmaStart(0), m_dmaMask(0) {}
    
    //! @brief Constructor.
    inline WrappedSequence(unsigned chipSelect, apbh_dma_t * dma, uint16_t theMask=0)
    :   Sequence(chipSelect), m_dmaStart(dma), m_dmaMask(theMask)
    {
    }
    
    //! @brief Constructor taking a NandDma::Component instance.
    inline WrappedSequence(unsigned chipSelect, Component::Base & component, uint16_t theMask=0)
    :   Sequence(chipSelect), m_dmaStart(component.getFirstDescriptor()), m_dmaMask(theMask)
    {
    }
    
    //! @name DMA start
    //@{
    ///! @brief Returns the DMA start descriptor.
    inline apbh_dma_t * getDmaStart() { return m_dmaStart; }
    
    //! @brief Change the DMA start descriptor.
    inline void setDmaStart(apbh_dma_t * theDma) { m_dmaStart = theDma; }
    
    //! @brief Change the DMA start descriptor to a component.
    inline void setDmaStart(Component::Base & theDma) { m_dmaStart = theDma.getFirstDescriptor(); }
    //@}
    
    //! @name Wait mask
    //@{
    //! @brief Change the DMA wait mask to use for this DMA.
    inline void setDmaWaitMask(uint16_t theMask) { m_dmaMask = theMask; }
    
    //! @brief Returns the wait mask required for this DMA.
    //!
    //! The returned wait mask will always have #kNandGpmiDmaWaitMask_GpmiDma set, in addition
    //! to whatever bits are set in the mask optionally passed into the constructor or set
    //! with a call to setDmaWaitMask().
    inline virtual uint16_t getDmaWaitMask() const { return kNandGpmiDmaWaitMask_GpmiDma | m_dmaMask; }
    //@}

    //! @brief Returns the address of the first DMA descriptor.
    inline virtual apbh_dma_t * getFirstDescriptor() { return m_dmaStart; }
    
};

/*!
 * @brief Reset command.
 */
class Reset : public Sequence
{
public:
    //! @name DMA Components
    //@{
    Component::WaitForReady m_wait1;
    Component::CommandAddress m_cmd;
    Component::WaitForReady m_wait2;
    Component::Terminator m_done;
    //@}
    
    //! @brief The reset command value.
    uint8_t m_commandBuffer __ALIGN4__;
    
    //! @brief Default constructor.
    inline Reset() {}
    
    //! @brief Constructor.
    inline Reset(unsigned chipSelect, uint8_t resetCommand)
    {
        init(chipSelect, resetCommand);
    }
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t resetCommand);
    
    //! @brief Sets the DMA to not wait for ready after sending the reset command.
    void skipPostWait();
    
    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Operator to provide easy access to the first DMA descriptor.
    inline operator apbh_dma_t * () { return getFirstDescriptor(); }
};

/*!
 * @brief Abstract class for a command that reads data with no wait for ready.
 *
 * This class is designed to provide a base for all DMA sequences that send a single command
 * byte followed by an optional address byte, and then read back a few bytes of data. The
 * key distinguishing factor is that these sequences read the data without performing a
 * wait for ready before the read.
 */
class ImmediateRead : public Sequence
{
public:
    //! @name DMA Components
    //@{
    Component::WaitForReady m_wait;
    Component::CommandAddress m_sendCommand;
    Component::ReceiveRawData m_readResult;
    Component::Terminator m_done;
    //@}
    
    uint8_t m_commandAddressBuffer[2] __ALIGN4__;
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command, uint8_t address, unsigned addressSize, void * buffer, unsigned resultSize);
    
    //! @name Modifiers
    //@{
    void setChipSelect(unsigned chipSelect);
    //@}
    
    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
        m_readResult >> rhs;
        return rhs;
    }
};

/*!
 * @brief Read ID command.
 *
 * This DMA sequence sends one command byte followed by one address byte (almost always 0),
 * and then reads back 6 bytes of the NAND ID. Based on the ImmediateRead class. 
 */
class ReadId : public ImmediateRead
{
public:

    //! @brief Default constructor.
    inline ReadId() {}
    
    //! @brief Constructor.
    inline ReadId(unsigned chipSelect, uint8_t command, uint8_t address, void * idBuffer)
    {
        init(chipSelect, command, address, idBuffer);
    }
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command, uint8_t address, void * idBuffer);
    
    //! @brief Operator to provide easy access to the first DMA descriptor.
    inline operator apbh_dma_t * () { return getFirstDescriptor(); }        
};

/*!
 * @brief Read status.
 *
 * The purpose of this DMA sequence is to send a single status command byte, and then
 * immediately read back a single status result byte from the NAND. There is no wait for
 * ready in between the command and reading the result, so this class is based on the
 * ImmediateRead class. 
 */
class ReadStatus : public ImmediateRead
{
public:

    //! @brief Default constructor.
    inline ReadStatus() {}
    
    //! @brief Constructor.
    inline ReadStatus(unsigned chipSelect, uint8_t command, void * statusBuffer)
    {
        init(chipSelect, command, statusBuffer);
    }
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command, void * statusBuffer);
    
    //! @brief Operator to provide easy access to the first DMA descriptor.
    inline operator apbh_dma_t * () { return getFirstDescriptor(); }        
};

/*!
 * @brief Block erase.
 */
class BlockErase : public Sequence
{
public:
    //! @name DMA Components
    //@{
    Component::CommandAddress m_cle1Address;
    Component::CommandAddress m_cle2;
    Component::WaitForReady m_wait;
    Component::Terminator m_done;
    //@}
    
    uint8_t m_cle1AddressBuffer[1+MAX_ROWS] __ALIGN4__;
    uint8_t m_cle2Buffer __ALIGN4__;
    
    //! @brief Default constructor.
    inline BlockErase() {}
    
    //! @brief Constructor.
    inline BlockErase(unsigned chipSelect, uint8_t command1, uint32_t address, unsigned addressByteCount, uint8_t command2)
    {
        init(chipSelect, command1, address, addressByteCount, command2);
    }
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command1, uint32_t address, unsigned addressByteCount, uint8_t command2);
    
    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
    
    //! @brief Operator to provide easy access to the first DMA descriptor.
    inline operator apbh_dma_t * () { return getFirstDescriptor(); }        
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
        m_wait >> rhs;
        return rhs;
    }
};

/*!
 * @brief Block erase variant that sends two adddresses.
 */
class MultiBlockErase : public BlockErase
{
public:
    Component::CommandAddress m_cle1Address2;
    uint8_t m_cle1AddressBuffer2[1+MAX_ROWS] __ALIGN4__;

    //! @brief Default constructor.
    inline MultiBlockErase() {}
    
    //! @brief Constructor.
    inline MultiBlockErase(unsigned chipSelect, uint8_t command1, uint32_t address, uint32_t address2, unsigned addressByteCount, uint8_t command2)
    {
        init(chipSelect, command1, address, address2, addressByteCount, command2);
    }
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command1, uint32_t address, uint32_t address2, unsigned addressByteCount, uint8_t command2);
    
    //! @brief Operator to provide easy access to the first DMA descriptor.
    inline operator apbh_dma_t * () { return getFirstDescriptor(); }        
};

/*!
 * @brief Base class for read and write DMAs.
 */
class ReadWriteBase : public Sequence
{
public:
    //! @name DMA Components
    //@{
    Component::CommandAddress m_cle1Address;
    Component::CommandAddress m_cle2;
    Component::WaitForReady m_wait;
    Component::Terminator m_done;
    //@}
    
    //! @name Buffers
    //@{
    uint8_t m_cle1AddressBuffer[1+MAX_ROWS+MAX_COLUMNS] __ALIGN4__;
    uint8_t m_cle2Buffer __ALIGN4__;
    //@}
    
    //! @brief Number of bytes used for the page address.
    unsigned m_addressByteCount;
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2);
    
    //! @name Modifiers
    //@{
    void setChipSelect(unsigned chipSelect);
    void setCommands(uint8_t command1, uint8_t command2);
    void setAddress(uint8_t * addressBytes);
    void setAddress(uint32_t col, uint32_t row);
    void setAddressByteCount(uint8_t addressByteCount);
    //@}
    
    //! @brief Returns the address of the first DMA descriptor.
    virtual apbh_dma_t * getFirstDescriptor();
};

/*!
 * @brief Read a page from the NAND with ECC disabled.
 */
class ReadRawData : public ReadWriteBase
{
public:
    //! @name DMA Components
    //@{
    Component::ReceiveRawData m_readData;
    Component::ReceiveRawData m_readAux;
    //@}
    
    //! @name Read sizes
    //@{
    uint32_t m_dataReadSize;
    uint32_t m_auxReadSize;
    //@}
    
    //! @brief Default constructor.
    inline ReadRawData() {}
    
    //! @brief Constructor.
    inline ReadRawData(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, void * dataBuffer, uint32_t dataReadSize, void * auxBuffer, uint32_t auxReadSize)
    {
        init(chipSelect, command1, addressBytes, addressByteCount, command2, dataBuffer, dataReadSize, auxBuffer, auxReadSize);
    }
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, void * dataBuffer, uint32_t dataReadSize, void * auxBuffer, uint32_t auxReadSize);
    
    //! @name Modifiers
    //@{
    void setChipSelect(unsigned chipSelect);
    void setBuffers(void * dataBuffer, uint32_t dataReadSize, void * auxBuffer, uint32_t auxReadSize);
    void chainReadCommands();
    //@}
    
    //! @brief Operator to provide easy access to the first DMA descriptor.
    inline operator apbh_dma_t * () { return getFirstDescriptor(); }        
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs);
};

/*!
 * @brief Read a page from the NAND with ECC enabled.
 */
class ReadEccData : public ReadWriteBase
{
public:
    //! @name DMA Components
    //@{
    Component::ReceiveEccData m_readData;
    //@}
    
    //! @name Save read info
    //@{
    uint32_t m_readSize;
    BchEccLayout_t m_ecc;
    uint32_t m_eccMask;
    //@}
    
    //! @brief Default constructor.
    inline ReadEccData() {}
    
    //! @brief Constructor.
    inline ReadEccData(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, void * dataBuffer, void * auxBuffer, uint32_t readSize, const BchEccLayout_t & ecc, uint32_t eccMask)
    {
        init(chipSelect, command1, addressBytes, addressByteCount, command2, dataBuffer, auxBuffer, readSize, ecc, eccMask);
    }
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, void * dataBuffer, void * auxBuffer, uint32_t readSize, const BchEccLayout_t & ecc, uint32_t eccMask);
    
    //! @name Modifiers
    //@{
    void setChipSelect(unsigned chipSelect);
    void setBuffers(void * dataBuffer, void * auxBuffer);
    void setBuffers(void * dataBuffer, void * auxBuffer, uint32_t readSize);
    void setBuffers(void * dataBuffer, void * auxBuffer, uint32_t readSize, const BchEccLayout_t & ecc, uint32_t eccMask);
    //@}
    
    //! @brief Returns the wait mask required for this DMA.
    virtual uint16_t getDmaWaitMask() const;
    
    //! @brief Operator to provide easy access to the first DMA descriptor.
    inline operator apbh_dma_t * () { return getFirstDescriptor(); }        
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
        m_readData >> rhs;
        return rhs;
    }
};

/*!
 * @brief Write a page to the NAND with ECC disabled.
 */
class WriteRawData : public ReadWriteBase
{
public:
    //! @name DMA Components
    //@{
    Component::SendRawData m_writeData;
    Component::SendRawData m_writeAux;
    //@}
    
    //! @name Write sizes
    //@{
    uint32_t m_dataWriteSize;
    uint32_t m_auxWriteSize;
    //@}
    
    //! @brief Default constructor.
    inline WriteRawData() {}
    
    //! @brief Constructor.
    inline WriteRawData(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, const void * dataBuffer, uint32_t dataSize, const void * auxBuffer, uint32_t auxSize)
    {
        init(chipSelect, command1, addressBytes, addressByteCount, command2, dataBuffer, dataSize, auxBuffer, auxSize);
    }
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, const void * dataBuffer, uint32_t dataSize, const void * auxBuffer, uint32_t auxSize);
    
    //! @name Modifiers
    //@{
    void setChipSelect(unsigned chipSelect);
    void setBuffers(const void * dataBuffer, uint32_t dataSize, const void * auxBuffer, uint32_t auxSize);
    void chainWriteCommands();
    //@}
    
    //! @brief Operator to provide easy access to the first DMA descriptor.
    inline operator apbh_dma_t * () { return getFirstDescriptor(); }        
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs);
};

/*!
 * @brief Write a page to the NAND with ECC enabled.
 */
class WriteEccData : public ReadWriteBase
{
public:
    //! @name DMA Components
    //@{
    Component::SendEccData m_writeData;
    //@}
    
    //! @name Saved info
    //@{
    uint32_t m_sendSize;
    uint32_t m_dataSize;
    uint32_t m_leftoverSize;
    BchEccLayout_t m_ecc;
    uint32_t m_eccMask;
    //@}
    
    //! @brief Default constructor.
    inline WriteEccData() {}
    
    //! @brief Constructor.
    inline WriteEccData(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize, const BchEccLayout_t & ecc, uint32_t eccMask)
    {
        init(chipSelect, command1, addressBytes, addressByteCount, command2, dataBuffer, auxBuffer, sendSize, dataSize, leftoverSize, ecc, eccMask);
    }
    
    //! @brief Initializer.
    void init(unsigned chipSelect, uint8_t command1, uint8_t * addressBytes, unsigned addressByteCount, uint8_t command2, const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize, const BchEccLayout_t & ecc, uint32_t eccMask);
    
    //! @name Modifiers
    //@{
    void setChipSelect(unsigned chipSelect);
    void setBuffers(const void * dataBuffer, const void * auxBuffer);
    void setBuffers(const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize);
    void setBuffers(const void * dataBuffer, const void * auxBuffer, uint32_t sendSize, uint32_t dataSize, uint32_t leftoverSize, const BchEccLayout_t & ecc, uint32_t eccMask);
    //@}
    
    //! @brief Returns the wait mask required for this DMA.
    virtual uint16_t getDmaWaitMask() const;
    
    //! @brief Operator to provide easy access to the first DMA descriptor.
    inline operator apbh_dma_t * () { return getFirstDescriptor(); }        
    
    //! @brief Chaining operator.
    virtual Base & operator >> (Base & rhs)
    {
        m_writeData >> rhs;
        return rhs;
    }
};

} // namespace NandDma

#endif // defined(__cplusplus)

#endif // _NAND_DMA_H
///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////
