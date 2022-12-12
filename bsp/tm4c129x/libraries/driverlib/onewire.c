//*****************************************************************************
//
// onewire.c - Driver for OneWire master module.
//
// Copyright (c) 2012-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 2.2.0.295 of the Tiva Peripheral Driver Library.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup onewire_api
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_onewire.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/onewire.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
// A bit mask for all transaction related fields in the 1-Wire control
// register.
//
//*****************************************************************************
#define ONEWIRE_TXN_MASK        (ONEWIRE_CS_OP_M | ONEWIRE_CS_SZ_M |          \
                                 ONEWIRE_CS_BSIZE_M)

//*****************************************************************************
//
// Left-shift value for the control register's transaction size.
//
//*****************************************************************************
#define ONEWIRE_TXN_SIZE_LSHIFT 3

//*****************************************************************************
//
// Left-shift value for the control register's last byte bit size.
//
//*****************************************************************************
#define ONEWIRE_TXN_BSIZE_LSHIFT                                              \
                                16

//*****************************************************************************
//
//! Initializes the 1-Wire module.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//! \param ui32InitFlags provides the initialization flags.
//!
//! This function configures and initializes the 1-Wire interface for use.
//!
//! The \e ui32InitFlags parameter is a combination of the following:
//!
//! - \b ONEWIRE_INIT_SPD_STD - standard speed bus timings
//! - \b ONEWIRE_INIT_SPD_OD - overdrive speed bus timings
//! - \b ONEWIRE_INIT_READ_STD - standard read sampling timing
//! - \b ONEWIRE_INIT_READ_LATE - late read sampling timing
//! - \b ONEWIRE_INIT_ATR - standard answer-to-reset presence detect
//! - \b ONEWIRE_INIT_NO_ATR - no answer-to-reset presence detect
//! - \b ONEWIRE_INIT_STD_POL - normal signal polarity
//! - \b ONEWIRE_INIT_ALT_POL - alternate (reverse) signal polarity
//! - \b ONEWIRE_INIT_1_WIRE_CFG - standard 1-Wire (1 data pin) setup
//! - \b ONEWIRE_INIT_2_WIRE_CFG - alternate 2-Wire (2 data pin) setup
//!
//! \return None.
//
//*****************************************************************************
void
OneWireInit(uint32_t ui32Base, uint32_t ui32InitFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);

    //
    // Initialize control register.
    //
    HWREG(ui32Base + ONEWIRE_O_CS) = ui32InitFlags;
}

//*****************************************************************************
//
//! Issues a reset on the 1-Wire bus.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//!
//! This function causes the 1-Wire module to generate a reset signal on the
//! 1-Wire bus.
//!
//! \return None.
//
//*****************************************************************************
void
OneWireBusReset(uint32_t ui32Base)
{
    //
    // Check the argument.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);

    //
    // Issue a bus reset.
    //
    HWREG(ui32Base + ONEWIRE_O_CS) |= ONEWIRE_CS_RST;
}

//*****************************************************************************
//
//! Retrieves the 1-Wire bus condition status.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//!
//! This function returns the 1-Wire bus conditions reported by the 1-Wire
//! module.  These conditions could be a logical OR of any of the following:
//!
//! - \b ONEWIRE_BUS_STATUS_BUSY - A read, write, or reset is active.
//! - \b ONEWIRE_BUS_STATUS_NO_SLAVE - No slave presence pulses detected.
//! - \b ONEWIRE_BUS_STATUS_STUCK - The bus is being held low by non-master.
//!
//! \return Returns the 1-Wire bus conditions if detected else zero.
//
//*****************************************************************************
uint32_t
OneWireBusStatus(uint32_t ui32Base)
{
    //
    // Check the argument.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);

    //
    // Return the status bits from control and status register.
    //
    return(HWREG(ui32Base + ONEWIRE_O_CS) & (ONEWIRE_CS_BUSY |
                                             ONEWIRE_CS_NOATR |
                                             ONEWIRE_CS_STUCK));
}

//*****************************************************************************
//
//! Retrieves data from the 1-Wire interface.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//! \param pui32Data is a pointer to storage to hold the read data.
//!
//! This function reads data from the 1-Wire module once all active bus
//! operations are completed.  By protocol definition, bit data defaults to
//! a 1.  Thus if a slave did not signal any 0-bit data, this read returns
//! 0xffffffff.
//!
//! \return None.
//
//*****************************************************************************
void
OneWireDataGet(uint32_t ui32Base, uint32_t *pui32Data)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);
    ASSERT(pui32Data);

    //
    // Wait for any active operations to complete.
    //
    while(HWREG(ui32Base + ONEWIRE_O_CS) & ONEWIRE_CS_BUSY)
    {
    }

    //
    // Copy the data into the provided storage.
    //
    *pui32Data = HWREG(ui32Base + ONEWIRE_O_DATR);
}

//*****************************************************************************
//
//! Retrieves data from the 1-Wire interface.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//! \param pui32Data is a pointer to storage to hold the read data.
//!
//! This function reads data from the 1-Wire module if there are no active
//! operations on the bus.  Otherwise it returns without reading the data from
//! the module.
//!
//! By protocol definition, bit data defaults to a 1.  Thus if a slave did
//! not signal any 0-bit data, this read returns 0xffffffff.
//!
//! \return Returns \b true if a data read was performed, or \b false if the
//! bus was not idle and no data was read.
//
//*****************************************************************************
bool
OneWireDataGetNonBlocking(uint32_t ui32Base, uint32_t *pui32Data)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);
    ASSERT(pui32Data);

    //
    // If the bus is busy, return without reading.
    //
    if(HWREG(ui32Base + ONEWIRE_O_CS) & ONEWIRE_CS_BUSY)
    {
        return(false);
    }

    //
    // Copy the data into the provided storage.
    //
    *pui32Data = HWREG(ui32Base + ONEWIRE_O_DATR);

    //
    // Notify the caller data was read from the read register.
    //
    return(true);
}

//*****************************************************************************
//
//! Clears the 1-Wire module interrupt sources.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//! \param ui32IntFlags is a bit mask of the interrupt sources to be cleared.
//!
//! This function clears the specified 1-Wire interrupt sources so that they no
//! longer assert.  This function must be called in the interrupt handler to
//! keep the interrupts from being triggered again immediately upon exit.  The
//! \e ui32IntFlags parameter can be a logical OR of any of the following:
//!
//! - \b ONEWIRE_INT_RESET_DONE - Bus reset has just completed.
//! - \b ONEWIRE_INT_OP_DONE - Read or write operation completed.  If a
//!   combined write and read operation was set up, the interrupt signals the
//!   read is done.
//! - \b ONEWIRE_INT_NO_SLAVE - No presence detect was signaled by a slave.
//! - \b ONEWIRE_INT_STUCK - Bus is being held low by non-master.
//! - \b ONEWIRE_INT_DMA_DONE - DMA operation has completed.
//!
//! \note Because there is a write buffer in the Cortex-M processor, it may
//! take several clock cycles before the interrupt source is actually cleared.
//! Therefore, it is recommended that the interrupt source be cleared early in
//! the interrupt handler (as opposed to the very last action) to avoid
//! returning from the interrupt handler before the interrupt source is
//! actually cleared.  Failure to do so may result in the interrupt handler
//! being immediately reentered (because the interrupt controller still sees
//! the interrupt source asserted).
//!
//! \return None.
//
//*****************************************************************************
void
OneWireIntClear(uint32_t ui32Base, uint32_t ui32IntFlags)
{
    //
    // Check the argument.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);
    ASSERT((ui32IntFlags & ~(ONEWIRE_IM_RST | ONEWIRE_IM_OPC | ONEWIRE_IM_DMA |
                             ONEWIRE_IM_NOATR | ONEWIRE_IM_STUCK)) == 0);

    //
    // Clear the requested interrupts.
    //
    HWREG(ui32Base + ONEWIRE_O_ICR) = ui32IntFlags;
}

//*****************************************************************************
//
//! Disables individual 1-Wire module interrupt sources.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//! \param ui32IntFlags is a bit mask of the interrupt sources to be disabled.
//!
//! This function disables the indicated 1-Wire interrupt sources.  The
//! \e ui32IntFlags parameter can be a logical OR of any of the following:
//!
//! - \b ONEWIRE_INT_RESET_DONE - Bus reset has just completed.
//! - \b ONEWIRE_INT_OP_DONE - Read or write operation completed.  If a
//!   combined write and read operation was set up, the interrupt signals the
//!   read is done.
//! - \b ONEWIRE_INT_NO_SLAVE - No presence detect was signaled by a slave.
//! - \b ONEWIRE_INT_STUCK - Bus is being held low by non-master.
//! - \b ONEWIRE_INT_DMA_DONE - DMA operation has completed
//!
//! \return None.
//
//*****************************************************************************
void
OneWireIntDisable(uint32_t ui32Base, uint32_t ui32IntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);
    ASSERT((ui32IntFlags & ~(ONEWIRE_IM_RST | ONEWIRE_IM_OPC | ONEWIRE_IM_DMA |
                             ONEWIRE_IM_NOATR | ONEWIRE_IM_STUCK)) == 0);

    //
    // Disable the requested interrupts.
    //
    HWREG(ui32Base + ONEWIRE_O_IM) &= ~ui32IntFlags;
}

//*****************************************************************************
//
//! Enables individual 1-Wire module interrupt sources.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//! \param ui32IntFlags is a bit mask of the interrupt sources to be enabled.
//!
//! This function enables the indicated 1-Wire interrupt sources.  Only the
//! sources that are enabled can be reflected to the processor interrupt;
//! disabled sources have no effect on the processor.  The \e ui32IntFlags
//! parameter can be a logical OR of any of the following:
//!
//! - \b ONEWIRE_INT_RESET_DONE - Bus reset has just completed.
//! - \b ONEWIRE_INT_OP_DONE - Read or write operation completed.  If a
//!   combined write and read operation was set up, the interrupt signals the
//!   read is done.
//! - \b ONEWIRE_INT_NO_SLAVE - No presence detect was signaled by a slave.
//! - \b ONEWIRE_INT_STUCK - Bus is being held low by non-master.
//! - \b ONEWIRE_INT_DMA_DONE - DMA operation has completed
//!
//! \return None.
//
//*****************************************************************************
void
OneWireIntEnable(uint32_t ui32Base, uint32_t ui32IntFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);
    ASSERT((ui32IntFlags & ~(ONEWIRE_IM_RST | ONEWIRE_IM_OPC | ONEWIRE_IM_DMA |
                             ONEWIRE_IM_NOATR | ONEWIRE_IM_STUCK)) == 0);

    //
    // Enable the requested interrupts.
    //
    HWREG(ui32Base + ONEWIRE_O_IM) |= ui32IntFlags;
}

//*****************************************************************************
//
//! Gets the current 1-Wire interrupt status.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//! \param bMasked is \b false if the raw interrupt status is required or
//! \b true if the masked interrupt status is required.
//!
//! This function returns the interrupt status for the 1-Wire module.  Either
//! the raw interrupt status or the status of interrupts that are allowed to
//! reflect to the processor can be returned.
//!
//! \return Returns the masked or raw 1-Wire interrupt status, as a bit field
//! of any of the following values:
//!
//! - \b ONEWIRE_INT_RESET_DONE - Bus reset has just completed.
//! - \b ONEWIRE_INT_OP_DONE - Read or write operation completed.
//! - \b ONEWIRE_INT_NO_SLAVE - No presence detect was signaled by a slave.
//! - \b ONEWIRE_INT_STUCK - Bus is being held low by non-master.
//! - \b ONEWIRE_INT_DMA_DONE - DMA operation has completed
//
//*****************************************************************************
uint32_t
OneWireIntStatus(uint32_t ui32Base, bool bMasked)
{
    //
    // Check the argument.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);

    //
    // Return either the interrupt status or the raw interrupt status as
    // requested.
    //
    if(bMasked)
    {
        return(HWREG(ui32Base + ONEWIRE_O_MIS));
    }
    else
    {
        return(HWREG(ui32Base + ONEWIRE_O_RIS));
    }
}

//*****************************************************************************
//
//! Returns the 1-Wire controller interrupt number.
//!
//! \param ui32Base specifies the 1-Wire module base address.
//!
//! This function returns the interrupt number for the 1-Wire module with the
//! base address passed in the \e ui32Base parameter.
//!
//! \return Returns a 1-Wire interrupt number or 0 if the interrupt does not
//! exist.
//
//*****************************************************************************
static uint32_t
_OneWireIntNumberGet(uint32_t ui32Base)
{
    uint32_t ui32Int;

    ASSERT(ui32Base == ONEWIRE0_BASE);

    ui32Int = 0;

    //
    // Find the valid interrupt number for the 1-Wire module.
    //
    if(CLASS_IS_TM4C129)
    {
        ui32Int = INT_ONEWIRE0_TM4C129;
    }

    return(ui32Int);
}

//*****************************************************************************
//
//! Registers an interrupt handler for the 1-Wire module.
//!
//! \param ui32Base is the base address of the 1-Wire module.
//! \param pfnHandler is a pointer to the function to be called when the
//! 1-Wire interrupt occurs.
//!
//! This function sets the handler to be called when a 1-Wire interrupt occurs.
//! This function enables the global interrupt in the interrupt controller;
//! specific 1-Wire interrupts must be enabled via OneWireIntEnable().  If
//! necessary, it is the interrupt handler's responsibility to clear the
//! interrupt source via OneWireIntClear().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
OneWireIntRegister(uint32_t ui32Base, void (*pfnHandler)(void))
{
    uint32_t ui32Int;

    //
    // Check the argument.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);
    ASSERT(pfnHandler);

    //
    // Get the actual interrupt number for the 1-Wire module.
    //
    ui32Int = _OneWireIntNumberGet(ui32Base);

    ASSERT(ui32Int != 0);

    //
    // Register the interrupt handler.
    //
    IntRegister(ui32Int, pfnHandler);

    //
    // Enable the 1-Wire peripheral interrupt.
    //
    IntEnable(ui32Int);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the 1-Wire module.
//!
//! \param ui32Base is the base address of the 1-Wire module.
//!
//! This function clears the handler to be called when an 1-Wire interrupt
//! occurs.  This function also masks off the interrupt in the interrupt
//! controller so that the interrupt handler no longer is called.
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
OneWireIntUnregister(uint32_t ui32Base)
{
    uint32_t ui32Int;

    //
    // Check the argument.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);

    //
    // Get the actual interrupt number for the 1-Wire module.
    //
    ui32Int = _OneWireIntNumberGet(ui32Base);
    ASSERT(ui32Int != 0);

    //
    // Disable the 1-Wire peripheral interrupt.
    //
    IntDisable(ui32Int);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(ui32Int);
}

//*****************************************************************************
//
//! Disables 1-Wire DMA operations.
//!
//! \param ui32Base is the base address of the 1-Wire module.
//! \param ui32DMAFlags is a bit mask of the DMA features to disable.
//!
//! This function is used to disable 1-Wire DMA features that were enabled
//! by OneWireDMAEnable().  The specified 1-Wire DMA features are disabled.
//! The \e ui32DMAFlags parameter is a combination of the following:
//!
//! - \b ONEWIRE_DMA_BUS_RESET - Issue a 1-Wire bus reset before starting
//! - \b ONEWIRE_DMA_OP_READ - Read after each module transaction
//! - \b ONEWIRE_DMA_OP_MULTI_WRITE - Write after each previous write
//! - \b ONEWIRE_DMA_OP_MULTI_READ - Read after each previous read
//! - \b ONEWIRE_DMA_MODE_SG - Start DMA on enable then repeat on each
//!   completion
//! - \b ONEWIRE_DMA_OP_SZ_8 - Bus read/write of 8 bits
//! - \b ONEWIRE_DMA_OP_SZ_16 - Bus read/write of 16 bits
//! - \b ONEWIRE_DMA_OP_SZ_32 - Bus read/write of 32 bits
//!
//! \return None.
//
//*****************************************************************************
void
OneWireDMADisable(uint32_t ui32Base, uint32_t ui32DMAFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);
    ASSERT(ui32DMAFlags > 0);

    //
    // Clear the transaction size bits
    //
    HWREG(ui32Base + ONEWIRE_O_CS) = (HWREG(ui32Base + ONEWIRE_O_CS) &
                                      ~(ONEWIRE_TXN_MASK));

    //
    // Disable the DMA features as requested.
    //
    HWREG(ui32Base + ONEWIRE_O_DMA) &= ~(ui32DMAFlags & 0xff);
}

//*****************************************************************************
//
//! Enables 1-Wire DMA operations.
//!
//! \param ui32Base is the base address of the 1-Wire module.
//! \param ui32DMAFlags is a bit mask of the DMA features to enable.
//!
//! This function enables the specified 1-Wire DMA features.  The 1-Wire module
//! can be configured for write operations, read operations, small write and
//! read operations, and scatter-gather support of mixed operations.
//!
//! The \e ui32DMAFlags parameter is a combination of the following:
//!
//! - \b ONEWIRE_DMA_BUS_RESET - Issue a 1-Wire bus reset before starting
//! - \b ONEWIRE_DMA_OP_READ - Read after each module transaction
//! - \b ONEWIRE_DMA_OP_MULTI_WRITE - Write after each previous write
//! - \b ONEWIRE_DMA_OP_MULTI_READ - Read after each previous read
//! - \b ONEWIRE_DMA_MODE_SG - Start DMA on enable then repeat on each
//!   completion
//! - \b ONEWIRE_DMA_OP_SZ_8 - Bus read/write of 8 bits
//! - \b ONEWIRE_DMA_OP_SZ_16 - Bus read/write of 16 bits
//! - \b ONEWIRE_DMA_OP_SZ_32 - Bus read/write of 32 bits
//!
//! \note The uDMA controller must be properly configured before DMA can be
//! used with the 1-Wire module.
//!
//! \return None.
//
//*****************************************************************************
void
OneWireDMAEnable(uint32_t ui32Base, uint32_t ui32DMAFlags)
{
    //
    // Check the arguments.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);
    ASSERT(ui32DMAFlags > 0);

    //
    // set up the transaction size.
    //
    HWREG(ui32Base + ONEWIRE_O_CS) = ((HWREG(ui32Base + ONEWIRE_O_CS) &
                                       ~(ONEWIRE_TXN_MASK)) |
                                      (ui32DMAFlags >> 8));

    //
    // Enable DMA with the parameters provided.
    //
    HWREG(ui32Base + ONEWIRE_O_DMA) = (ui32DMAFlags & 0xf);

    //
    // If a read transaction was requested, seed the write data register.  This
    // will trigger the DMA reads to start.  This should not be done for
    // scatter-gather operations.
    //
    if((ui32DMAFlags & (ONEWIRE_DMA_DMAOP_RDSNG | ONEWIRE_DMA_DMAOP_RDMUL)) &&
       !(ui32DMAFlags & ONEWIRE_DMA_SG))
    {
        //
        // Workaround for Snowflake DMA receive trigger errata.
        //
        if(CLASS_IS_TM4C129)
        {
            SysCtlDelay(9);
        }

        //
        // Write DATW to trigger DMA receive start.
        //
        HWREG(ui32Base + ONEWIRE_O_DATW) = 0xffffffff;
    }
}

//*****************************************************************************
//
//! Performs a 1-Wire protocol transaction on the bus.
//!
//! \param ui32Base specifies the base address of the 1-Wire module.
//! \param ui32OpMode sets the transaction type.
//! \param ui32Data is the data for a write operation.
//! \param ui32BitCnt specifies the number of valid bits (1-32) for the
//! operation.
//!
//! This function performs a 1-Wire protocol transaction, read and/or write, on
//! the bus.  The application should confirm the bus is idle before starting a
//! read or write transaction.
//!
//! The \e ui32OpMode defines the activity for the bus operations and is a
//! logical OR of the following:
//!
//! - \b ONEWIRE_OP_RESET - Indicates the operation should be started with
//!   a bus reset.
//! - \b ONEWIRE_OP_WRITE - A write operation
//! - \b ONEWIRE_OP_READ - A read operation
//!
//! \note If both a read and write operation are requested, the write will be
//! performed prior to the read.
//!
//! \return None.
//
//*****************************************************************************
void
OneWireTransaction(uint32_t ui32Base, uint32_t ui32OpMode, uint32_t ui32Data,
                   uint32_t ui32BitCnt)
{
    uint32_t ui32Transaction;

    //
    // Check the arguments.
    //
    ASSERT(ui32Base == ONEWIRE0_BASE);
    ASSERT((ui32OpMode & (ONEWIRE_OP_RESET | ONEWIRE_OP_WRITE |
                          ONEWIRE_OP_READ)) > 0);
    ASSERT((ui32BitCnt >= 1) && (ui32BitCnt <= 32));

    //
    // Read the control register and clear any transaction related
    // bit fields.
    //
    ui32Transaction = HWREG(ui32Base + ONEWIRE_O_CS) & ~(ONEWIRE_TXN_MASK);

    //
    // Add the user specified operation flags.
    //
    ui32Transaction |= (ui32OpMode & (ONEWIRE_OP_RESET | ONEWIRE_OP_WRITE |
                                      ONEWIRE_OP_READ));

    //
    // set up for a read or write transaction.
    //
    if(ui32Transaction & (ONEWIRE_CS_OP_WR | ONEWIRE_CS_OP_RD))
    {
        //
        // Configure the 1-Wire module for the transaction size.  This is
        // specified as 1-4 bytes and the specific bit size for the last
        // byte therein.
        //
        ui32Transaction |= ((((ui32BitCnt % 8) ? (ui32BitCnt / 8) + 1 :
                              (ui32BitCnt / 8)) - 1) <<
                            ONEWIRE_TXN_SIZE_LSHIFT);
        ui32Transaction |= ((ui32BitCnt % 8) << ONEWIRE_TXN_BSIZE_LSHIFT);

        //
        // Write specific setup.
        //
        if(ui32Transaction & ONEWIRE_CS_OP_WR)
        {
            //
            // Load the data into the write register.
            //
            HWREG(ui32Base + ONEWIRE_O_DATW) = ui32Data;
        }
    }

    //
    // Start the transaction.
    //
    HWREG(ui32Base + ONEWIRE_O_CS) = ui32Transaction;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
