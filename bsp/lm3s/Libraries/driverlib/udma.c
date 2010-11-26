//*****************************************************************************
//
// udma.c - Driver for the micro-DMA controller.
//
// Copyright (c) 2007-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 6459 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

//*****************************************************************************
//
//! \addtogroup udma_api
//! @{
//
//*****************************************************************************

#include "inc/hw_types.h"
#include "inc/hw_udma.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/udma.h"

//*****************************************************************************
//
//! Enables the uDMA controller for use.
//!
//! This function enables the uDMA controller.  The uDMA controller must be
//! enabled before it can be configured and used.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAEnable(void)
{
    //
    // Set the master enable bit in the config register.
    //
    HWREG(UDMA_CFG) = UDMA_CFG_MASTEN;
}

//*****************************************************************************
//
//! Disables the uDMA controller for use.
//!
//! This function disables the uDMA controller.  Once disabled, the uDMA
//! controller will not operate until re-enabled with uDMAEnable().
//!
//! \return None.
//
//*****************************************************************************
void
uDMADisable(void)
{
    //
    // Clear the master enable bit in the config register.
    //
    HWREG(UDMA_CFG) = 0;
}

//*****************************************************************************
//
//! Gets the uDMA error status.
//!
//! This function returns the uDMA error status.  It should be called from
//! within the uDMA error interrupt handler to determine if a uDMA error
//! occurred.
//!
//! \return Returns non-zero if a uDMA error is pending.
//
//*****************************************************************************
unsigned long
uDMAErrorStatusGet(void)
{
    //
    // Return the uDMA error status.
    //
    return(HWREG(UDMA_ERRCLR));
}

//*****************************************************************************
//
//! Clears the uDMA error interrupt.
//!
//! This function clears a pending uDMA error interrupt.  It should be called
//! from within the uDMA error interrupt handler to clear the interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAErrorStatusClear(void)
{
    //
    // Clear the uDMA error interrupt.
    //
    HWREG(UDMA_ERRCLR) = 1;
}

//*****************************************************************************
//
//! Enables a uDMA channel for operation.
//!
//! \param ulChannel is the channel number to enable.
//!
//! This function enables a specific uDMA channel for use.  This function must
//! be used to enable a channel before it can be used to perform a uDMA
//! transfer.
//!
//! When a uDMA transfer is completed, the channel will be automatically
//! disabled by the uDMA controller.  Therefore, this function should be called
//! prior to starting up any new transfer.
//!
//! The \e ulChannel parameter must be one of the following:
//!
//! - \b UDMA_CHANNEL_UART0RX for UART 0 receive channel
//! - \b UDMA_CHANNEL_UART0TX for UART 0 transmit channel
//! - \b UDMA_CHANNEL_UART1RX for UART 1 receive channel
//! - \b UDMA_CHANNEL_UART1TX for UART 1 transmit channel
//! - \b UDMA_CHANNEL_SSI0RX for SSI 0 receive channel
//! - \b UDMA_CHANNEL_SSI0TX for SSI 0 transmit channel
//! - \b UDMA_CHANNEL_SSI1RX for SSI 1 receive channel
//! - \b UDMA_CHANNEL_SSI1TX for SSI 1 transmit channel
//! - \b UDMA_CHANNEL_SW for the software dedicated uDMA channel
//!
//! And for microcontrollers that have a USB peripheral:
//!
//! - \b UDMA_CHANNEL_USBEP1RX for USB endpoint 1 receive
//! - \b UDMA_CHANNEL_USBEP1TX for USB endpoint 1 transmit
//! - \b UDMA_CHANNEL_USBEP2RX for USB endpoint 2 receive
//! - \b UDMA_CHANNEL_USBEP2TX for USB endpoint 2 transmit
//! - \b UDMA_CHANNEL_USBEP3RX for USB endpoint 3 receive
//! - \b UDMA_CHANNEL_USBEP3TX for USB endpoint 3 transmit
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelEnable(unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 32);

    //
    // Set the bit for this channel in the enable set register.
    //
    HWREG(UDMA_ENASET) = 1 << ulChannel;
}

//*****************************************************************************
//
//! Disables a uDMA channel for operation.
//!
//! \param ulChannel is the channel number to disable.
//!
//! This function disables a specific uDMA channel.  Once disabled, a channel
//! will not respond to uDMA transfer requests until re-enabled via
//! uDMAChannelEnable().
//!
//! The \e ulChannel parameter must be one of the following:
//!
//! - \b UDMA_CHANNEL_UART0RX for UART 0 receive channel
//! - \b UDMA_CHANNEL_UART0TX for UART 0 transmit channel
//! - \b UDMA_CHANNEL_UART1RX for UART 1 receive channel
//! - \b UDMA_CHANNEL_UART1TX for UART 1 transmit channel
//! - \b UDMA_CHANNEL_SSI0RX for SSI 0 receive channel
//! - \b UDMA_CHANNEL_SSI0TX for SSI 0 transmit channel
//! - \b UDMA_CHANNEL_SSI1RX for SSI 1 receive channel
//! - \b UDMA_CHANNEL_SSI1TX for SSI 1 transmit channel
//! - \b UDMA_CHANNEL_SW for the software dedicated uDMA channel
//!
//! And for microcontrollers that have a USB peripheral:
//!
//! - \b UDMA_CHANNEL_USBEP1RX for USB endpoint 1 receive
//! - \b UDMA_CHANNEL_USBEP1TX for USB endpoint 1 transmit
//! - \b UDMA_CHANNEL_USBEP2RX for USB endpoint 2 receive
//! - \b UDMA_CHANNEL_USBEP2TX for USB endpoint 2 transmit
//! - \b UDMA_CHANNEL_USBEP3RX for USB endpoint 3 receive
//! - \b UDMA_CHANNEL_USBEP3TX for USB endpoint 3 transmit
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelDisable(unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 32);

    //
    // Set the bit for this channel in the enable clear register.
    //
    HWREG(UDMA_ENACLR) = 1 << ulChannel;
}

//*****************************************************************************
//
//! Checks if a uDMA channel is enabled for operation.
//!
//! \param ulChannel is the channel number to check.
//!
//! This function checks to see if a specific uDMA channel is enabled.  This
//! can be used to check the status of a transfer, since the channel will
//! be automatically disabled at the end of a transfer.
//!
//! The \e ulChannel parameter must be one of the following:
//!
//! - \b UDMA_CHANNEL_UART0RX for UART 0 receive channel
//! - \b UDMA_CHANNEL_UART0TX for UART 0 transmit channel
//! - \b UDMA_CHANNEL_UART1RX for UART 1 receive channel
//! - \b UDMA_CHANNEL_UART1TX for UART 1 transmit channel
//! - \b UDMA_CHANNEL_SSI0RX for SSI 0 receive channel
//! - \b UDMA_CHANNEL_SSI0TX for SSI 0 transmit channel
//! - \b UDMA_CHANNEL_SSI1RX for SSI 1 receive channel
//! - \b UDMA_CHANNEL_SSI1TX for SSI 1 transmit channel
//! - \b UDMA_CHANNEL_SW for the software dedicated uDMA channel
//!
//! And for microcontrollers that have a USB peripheral:
//!
//! - \b UDMA_CHANNEL_USBEP1RX for USB endpoint 1 receive
//! - \b UDMA_CHANNEL_USBEP1TX for USB endpoint 1 transmit
//! - \b UDMA_CHANNEL_USBEP2RX for USB endpoint 2 receive
//! - \b UDMA_CHANNEL_USBEP2TX for USB endpoint 2 transmit
//! - \b UDMA_CHANNEL_USBEP3RX for USB endpoint 3 receive
//! - \b UDMA_CHANNEL_USBEP3TX for USB endpoint 3 transmit
//!
//! \return Returns \b true if the channel is enabled, \b false if disabled.
//
//*****************************************************************************
tBoolean
uDMAChannelIsEnabled(unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 32);

    //
    // AND the specified channel bit with the enable register, and return the
    // result.
    //
    return((HWREG(UDMA_ENASET) & (1 << ulChannel)) ? true : false);
}

//*****************************************************************************
//
//! Sets the base address for the channel control table.
//!
//! \param pControlTable is a pointer to the 1024 byte aligned base address
//! of the uDMA channel control table.
//!
//! This function sets the base address of the channel control table.  This
//! table resides in system memory and holds control information for each uDMA
//! channel.  The table must be aligned on a 1024 byte boundary.  The base
//! address must be set before any of the channel functions can be used.
//!
//! The size of the channel control table depends on the number of uDMA
//! channels, and which transfer modes are used.  Refer to the introductory
//! text and the microcontroller datasheet for more information about the
//! channel control table.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAControlBaseSet(void *pControlTable)
{
    //
    // Check the arguments.
    //
    ASSERT(((unsigned long)pControlTable & ~0x3FF) ==
            (unsigned long)pControlTable);
    ASSERT((unsigned long)pControlTable >= 0x20000000);

    //
    // Program the base address into the register.
    //
    HWREG(UDMA_CTLBASE) = (unsigned long)pControlTable;
}

//*****************************************************************************
//
//! Gets the base address for the channel control table.
//!
//! This function gets the base address of the channel control table.  This
//! table resides in system memory and holds control information for each uDMA
//! channel.
//!
//! \return Returns a pointer to the base address of the channel control table.
//
//*****************************************************************************
void *
uDMAControlBaseGet(void)
{
    //
    // Read the current value of the control base register, and return it to
    // the caller.
    //
    return((void *)HWREG(UDMA_CTLBASE));
}

//*****************************************************************************
//
//! Requests a uDMA channel to start a transfer.
//!
//! \param ulChannel is the channel number on which to request a uDMA transfer.
//!
//! This function allows software to request a uDMA channel to begin a
//! transfer.  This could be used for performing a memory to memory transfer,
//! or if for some reason a transfer needs to be initiated by software instead
//! of the peripheral associated with that channel.
//!
//! The \e ulChannel parameter must be one of the following:
//!
//! - \b UDMA_CHANNEL_UART0RX for UART 0 receive channel
//! - \b UDMA_CHANNEL_UART0TX for UART 0 transmit channel
//! - \b UDMA_CHANNEL_UART1RX for UART 1 receive channel
//! - \b UDMA_CHANNEL_UART1TX for UART 1 transmit channel
//! - \b UDMA_CHANNEL_SSI0RX for SSI 0 receive channel
//! - \b UDMA_CHANNEL_SSI0TX for SSI 0 transmit channel
//! - \b UDMA_CHANNEL_SSI1RX for SSI 1 receive channel
//! - \b UDMA_CHANNEL_SSI1TX for SSI 1 transmit channel
//! - \b UDMA_CHANNEL_SW for the software dedicated uDMA channel
//!
//! And for microcontrollers that have a USB peripheral:
//!
//! - \b UDMA_CHANNEL_USBEP1RX for USB endpoint 1 receive
//! - \b UDMA_CHANNEL_USBEP1TX for USB endpoint 1 transmit
//! - \b UDMA_CHANNEL_USBEP2RX for USB endpoint 2 receive
//! - \b UDMA_CHANNEL_USBEP2TX for USB endpoint 2 transmit
//! - \b UDMA_CHANNEL_USBEP3RX for USB endpoint 3 receive
//! - \b UDMA_CHANNEL_USBEP3TX for USB endpoint 3 transmit
//!
//! \note If the channel is \b UDMA_CHANNEL_SW and interrupts are used, then
//! the completion will be signaled on the uDMA dedicated interrupt.  If a
//! peripheral channel is used, then the completion will be signaled on the
//! peripheral's interrupt.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelRequest(unsigned long ulChannel)
{
    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 32);

    //
    // Set the bit for this channel in the software uDMA request register.
    //
    HWREG(UDMA_SWREQ) = 1 << ulChannel;
}

//*****************************************************************************
//
//! Enables attributes of a uDMA channel.
//!
//! \param ulChannel is the channel to configure.
//! \param ulAttr is a combination of attributes for the channel.
//!
//! The \e ulChannel parameter must be one of the following:
//!
//! - \b UDMA_CHANNEL_UART0RX for UART 0 receive channel
//! - \b UDMA_CHANNEL_UART0TX for UART 0 transmit channel
//! - \b UDMA_CHANNEL_UART1RX for UART 1 receive channel
//! - \b UDMA_CHANNEL_UART1TX for UART 1 transmit channel
//! - \b UDMA_CHANNEL_SSI0RX for SSI 0 receive channel
//! - \b UDMA_CHANNEL_SSI0TX for SSI 0 transmit channel
//! - \b UDMA_CHANNEL_SSI1RX for SSI 1 receive channel
//! - \b UDMA_CHANNEL_SSI1TX for SSI 1 transmit channel
//! - \b UDMA_CHANNEL_SW for the software dedicated uDMA channel
//!
//! And for microcontrollers that have a USB peripheral:
//!
//! - \b UDMA_CHANNEL_USBEP1RX for USB endpoint 1 receive
//! - \b UDMA_CHANNEL_USBEP1TX for USB endpoint 1 transmit
//! - \b UDMA_CHANNEL_USBEP2RX for USB endpoint 2 receive
//! - \b UDMA_CHANNEL_USBEP2TX for USB endpoint 2 transmit
//! - \b UDMA_CHANNEL_USBEP3RX for USB endpoint 3 receive
//! - \b UDMA_CHANNEL_USBEP3TX for USB endpoint 3 transmit
//!
//! The \e ulAttr parameter is the logical OR of any of the following:
//!
//! - \b UDMA_ATTR_USEBURST is used to restrict transfers to use only a burst
//!   mode.
//! - \b UDMA_ATTR_ALTSELECT is used to select the alternate control structure
//!   for this channel.
//! - \b UDMA_ATTR_HIGH_PRIORITY is used to set this channel to high priority.
//! - \b UDMA_ATTR_REQMASK is used to mask the hardware request signal from the
//!   peripheral for this channel.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelAttributeEnable(unsigned long ulChannel, unsigned long ulAttr)
{
    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 32);
    ASSERT((ulAttr & ~(UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT |
                       UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK)) == 0);

    //
    // Set the useburst bit for this channel if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_USEBURST)
    {
        HWREG(UDMA_USEBURSTSET) = 1 << ulChannel;
    }

    //
    // Set the alternate control select bit for this channel,
    // if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_ALTSELECT)
    {
        HWREG(UDMA_ALTSET) = 1 << ulChannel;
    }

    //
    // Set the high priority bit for this channel, if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_HIGH_PRIORITY)
    {
        HWREG(UDMA_PRIOSET) = 1 << ulChannel;
    }

    //
    // Set the request mask bit for this channel, if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_REQMASK)
    {
        HWREG(UDMA_REQMASKSET) = 1 << ulChannel;
    }
}

//*****************************************************************************
//
//! Disables attributes of a uDMA channel.
//!
//! \param ulChannel is the channel to configure.
//! \param ulAttr is a combination of attributes for the channel.
//!
//! This function is used to disable attributes of a uDMA channel.
//!
//! The \e ulChannel parameter must be one of the following:
//!
//! - \b UDMA_CHANNEL_UART0RX for UART 0 receive channel
//! - \b UDMA_CHANNEL_UART0TX for UART 0 transmit channel
//! - \b UDMA_CHANNEL_UART1RX for UART 1 receive channel
//! - \b UDMA_CHANNEL_UART1TX for UART 1 transmit channel
//! - \b UDMA_CHANNEL_SSI0RX for SSI 0 receive channel
//! - \b UDMA_CHANNEL_SSI0TX for SSI 0 transmit channel
//! - \b UDMA_CHANNEL_SSI1RX for SSI 1 receive channel
//! - \b UDMA_CHANNEL_SSI1TX for SSI 1 transmit channel
//! - \b UDMA_CHANNEL_SW for the software dedicated uDMA channel
//!
//! And for microcontrollers that have a USB peripheral:
//!
//! - \b UDMA_CHANNEL_USBEP1RX for USB endpoint 1 receive
//! - \b UDMA_CHANNEL_USBEP1TX for USB endpoint 1 transmit
//! - \b UDMA_CHANNEL_USBEP2RX for USB endpoint 2 receive
//! - \b UDMA_CHANNEL_USBEP2TX for USB endpoint 2 transmit
//! - \b UDMA_CHANNEL_USBEP3RX for USB endpoint 3 receive
//! - \b UDMA_CHANNEL_USBEP3TX for USB endpoint 3 transmit
//!
//! The \e ulAttr parameter is the logical OR of any of the following:
//!
//! - \b UDMA_ATTR_USEBURST is used to restrict transfers to use only a burst
//!   mode.
//! - \b UDMA_ATTR_ALTSELECT is used to select the alternate control structure
//!   for this channel.
//! - \b UDMA_ATTR_HIGH_PRIORITY is used to set this channel to high priority.
//! - \b UDMA_ATTR_REQMASK is used to mask the hardware request signal from the
//!   peripheral for this channel.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelAttributeDisable(unsigned long ulChannel, unsigned long ulAttr)
{
    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 32);
    ASSERT((ulAttr & ~(UDMA_ATTR_USEBURST | UDMA_ATTR_ALTSELECT |
                       UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK)) == 0);

    //
    // Clear the useburst bit for this channel if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_USEBURST)
    {
        HWREG(UDMA_USEBURSTCLR) = 1 << ulChannel;
    }

    //
    // Clear the alternate control select bit for this channel, if set in
    // ulConfig.
    //
    if(ulAttr & UDMA_ATTR_ALTSELECT)
    {
        HWREG(UDMA_ALTCLR) = 1 << ulChannel;
    }

    //
    // Clear the high priority bit for this channel, if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_HIGH_PRIORITY)
    {
        HWREG(UDMA_PRIOCLR) = 1 << ulChannel;
    }

    //
    // Clear the request mask bit for this channel, if set in ulConfig.
    //
    if(ulAttr & UDMA_ATTR_REQMASK)
    {
        HWREG(UDMA_REQMASKCLR) = 1 << ulChannel;
    }
}

//*****************************************************************************
//
//! Gets the enabled attributes of a uDMA channel.
//!
//! \param ulChannel is the channel to configure.
//!
//! This function returns a combination of flags representing the attributes of
//! the uDMA channel.
//!
//! The \e ulChannel parameter must be one of the following:
//!
//! - \b UDMA_CHANNEL_UART0RX for UART 0 receive channel
//! - \b UDMA_CHANNEL_UART0TX for UART 0 transmit channel
//! - \b UDMA_CHANNEL_UART1RX for UART 1 receive channel
//! - \b UDMA_CHANNEL_UART1TX for UART 1 transmit channel
//! - \b UDMA_CHANNEL_SSI0RX for SSI 0 receive channel
//! - \b UDMA_CHANNEL_SSI0TX for SSI 0 transmit channel
//! - \b UDMA_CHANNEL_SSI1RX for SSI 1 receive channel
//! - \b UDMA_CHANNEL_SSI1TX for SSI 1 transmit channel
//! - \b UDMA_CHANNEL_SW for the software dedicated uDMA channel
//!
//! And for microcontrollers that have a USB peripheral:
//!
//! - \b UDMA_CHANNEL_USBEP1RX for USB endpoint 1 receive
//! - \b UDMA_CHANNEL_USBEP1TX for USB endpoint 1 transmit
//! - \b UDMA_CHANNEL_USBEP2RX for USB endpoint 2 receive
//! - \b UDMA_CHANNEL_USBEP2TX for USB endpoint 2 transmit
//! - \b UDMA_CHANNEL_USBEP3RX for USB endpoint 3 receive
//! - \b UDMA_CHANNEL_USBEP3TX for USB endpoint 3 transmit
//!
//! \return Returns the logical OR of the attributes of the uDMA channel, which
//! can be any of the following:
//! - \b UDMA_ATTR_USEBURST is used to restrict transfers to use only a burst
//!   mode.
//! - \b UDMA_ATTR_ALTSELECT is used to select the alternate control structure
//!   for this channel.
//! - \b UDMA_ATTR_HIGH_PRIORITY is used to set this channel to high priority.
//! - \b UDMA_ATTR_REQMASK is used to mask the hardware request signal from the
//!   peripheral for this channel.
//
//*****************************************************************************
unsigned long
uDMAChannelAttributeGet(unsigned long ulChannel)
{
    unsigned long ulAttr = 0;

    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 32);

    //
    // Check to see if useburst bit is set for this channel.
    //
    if(HWREG(UDMA_USEBURSTSET) & (1 << ulChannel))
    {
        ulAttr |= UDMA_ATTR_USEBURST;
    }

    //
    // Check to see if the alternate control bit is set for this channel.
    //
    if(HWREG(UDMA_ALTSET) & (1 << ulChannel))
    {
        ulAttr |= UDMA_ATTR_ALTSELECT;
    }

    //
    // Check to see if the high priority bit is set for this channel.
    //
    if(HWREG(UDMA_PRIOSET) & (1 << ulChannel))
    {
        ulAttr |= UDMA_ATTR_HIGH_PRIORITY;
    }

    //
    // Check to see if the request mask bit is set for this channel.
    //
    if(HWREG(UDMA_REQMASKSET) & (1 << ulChannel))
    {
        ulAttr |= UDMA_ATTR_REQMASK;
    }

    //
    // Return the configuration flags.
    //
    return(ulAttr);
}

//*****************************************************************************
//
//! Sets the control parameters for a uDMA channel.
//!
//! \param ulChannel is the logical OR of the uDMA channel number with
//! \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT.
//! \param ulControl is logical OR of several control values to set the control
//! parameters for the channel.
//!
//! This function is used to set control parameters for a uDMA transfer.  These
//! are typically parameters that are not changed often.
//!
//! The \e ulChannel parameter is one of the choices documented in the
//! uDMAChannelEnable() function.  It should be the logical OR of the channel
//! with one of \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT to choose whether
//! the primary or alternate data structure is used.
//!
//! The \e ulControl parameter is the logical OR of five values: the data size,
//! the source address increment, the destination address increment, the
//! arbitration size, and the use burst flag.  The choices available for each
//! of these values is described below.
//!
//! Choose the data size from one of \b UDMA_SIZE_8, \b UDMA_SIZE_16, or
//! \b UDMA_SIZE_32 to select a data size of 8, 16, or 32 bits.
//!
//! Choose the source address increment from one of \b UDMA_SRC_INC_8,
//! \b UDMA_SRC_INC_16, \b UDMA_SRC_INC_32, or \b UDMA_SRC_INC_NONE to select
//! an address increment of 8-bit bytes, 16-bit halfwords, 32-bit words, or
//! to select non-incrementing.
//!
//! Choose the destination address increment from one of \b UDMA_DST_INC_8,
//! \b UDMA_DST_INC_16, \b UDMA_DST_INC_32, or \b UDMA_DST_INC_NONE to select
//! an address increment of 8-bit bytes, 16-bit halfwords, 32-bit words, or
//! to select non-incrementing.
//!
//! The arbitration size determines how many items are transferred before
//! the uDMA controller re-arbitrates for the bus.  Choose the arbitration size
//! from one of \b UDMA_ARB_1, \b UDMA_ARB_2, \b UDMA_ARB_4, \b UDMA_ARB_8,
//! through \b UDMA_ARB_1024 to select the arbitration size from 1 to 1024
//! items, in powers of 2.
//!
//! The value \b UDMA_NEXT_USEBURST is used to force the channel to only
//! respond to burst requests at the tail end of a scatter-gather transfer.
//!
//! \note The address increment cannot be smaller than the data size.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelControlSet(unsigned long ulChannel, unsigned long ulControl)
{
    tDMAControlTable *pCtl;

    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 64);
    ASSERT(HWREG(UDMA_CTLBASE) != 0);

    //
    // Get the base address of the control table.
    //
    pCtl = (tDMAControlTable *)HWREG(UDMA_CTLBASE);

    //
    // Get the current control word value and mask off the fields to be
    // changed, then OR in the new settings.
    //
    pCtl[ulChannel].ulControl = ((pCtl[ulChannel].ulControl &
                                  ~(UDMA_CHCTL_DSTINC_M |
                                    UDMA_CHCTL_DSTSIZE_M |
                                    UDMA_CHCTL_SRCINC_M |
                                    UDMA_CHCTL_SRCSIZE_M |
                                    UDMA_CHCTL_ARBSIZE_M |
                                    UDMA_CHCTL_NXTUSEBURST)) |
                                 ulControl);
}

//*****************************************************************************
//
//! Sets the transfer parameters for a uDMA channel.
//!
//! \param ulChannel is the logical or of the uDMA channel number with either
//! \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT.
//! \param ulMode is the type of uDMA transfer.
//! \param pvSrcAddr is the source address for the transfer.
//! \param pvDstAddr is the destination address for the transfer.
//! \param ulTransferSize is the number of data items to transfer.
//!
//! This function is used to set the parameters for a uDMA transfer.  These are
//! typically parameters that are changed often.  The function
//! uDMAChannelControlSet() MUST be called at least once for this channel prior
//! to calling this function.
//!
//! The \e ulChannel parameter is one of the choices documented in the
//! uDMAChannelEnable() function.  It should be the logical OR of the channel
//! with either \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT to choose whether the
//! primary or alternate data structure is used.
//!
//! The \e ulMode parameter should be one of the following values:
//!
//! - \b UDMA_MODE_STOP stops the uDMA transfer.  The controller sets the mode
//!   to this value at the end of a transfer.
//! - \b UDMA_MODE_BASIC to perform a basic transfer based on request.
//! - \b UDMA_MODE_AUTO to perform a transfer that will always complete once
//!   started even if request is removed.
//! - \b UDMA_MODE_PINGPONG to set up a transfer that switches between the
//!   primary and alternate control structures for the channel.  This allows
//!   use of ping-pong buffering for uDMA transfers.
//! - \b UDMA_MODE_MEM_SCATTER_GATHER to set up a memory scatter-gather
//!   transfer.
//! - \b UDMA_MODE_PER_SCATTER_GATHER to set up a peripheral scatter-gather
//!   transfer.
//!
//! The \e pvSrcAddr and \e pvDstAddr parameters are pointers to the first
//! location of the data to be transferred.  These addresses should be aligned
//! according to the item size.  The compiler will take care of this if the
//! pointers are pointing to storage of the appropriate data type.
//!
//! The \e ulTransferSize parameter is the number of data items, not the number
//! of bytes.
//!
//! The two scatter/gather modes, memory and peripheral, are actually different
//! depending on whether the primary or alternate control structure is
//! selected.  This function will look for the \b UDMA_PRI_SELECT and
//! \b UDMA_ALT_SELECT flag along with the channel number and will set the
//! scatter/gather mode as appropriate for the primary or alternate control
//! structure.
//!
//! The channel must also be enabled using uDMAChannelEnable() after calling
//! this function.  The transfer will not begin until the channel has been set
//! up and enabled.  Note that the channel is automatically disabled after the
//! transfer is completed, meaning that uDMAChannelEnable() must be called
//! again after setting up the next transfer.
//!
//! \note Great care must be taken to not modify a channel control structure
//! that is in use or else the results will be unpredictable, including the
//! possibility of undesired data transfers to or from memory or peripherals.
//! For BASIC and AUTO modes, it is safe to make changes when the channel is
//! disabled, or the uDMAChannelModeGet() returns \b UDMA_MODE_STOP.  For
//! PINGPONG or one of the SCATTER_GATHER modes, it is safe to modify the
//! primary or alternate control structure only when the other is being used.
//! The uDMAChannelModeGet() function will return \b UDMA_MODE_STOP when a
//! channel control structure is inactive and safe to modify.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelTransferSet(unsigned long ulChannel, unsigned long ulMode,
                       void *pvSrcAddr, void *pvDstAddr,
                       unsigned long ulTransferSize)
{
    tDMAControlTable *pControlTable;
    unsigned long ulControl;
    unsigned long ulSize;
    unsigned long ulInc;

    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 64);
    ASSERT(HWREG(UDMA_CTLBASE) != 0);
    ASSERT(ulMode <= UDMA_MODE_PER_SCATTER_GATHER);
    ASSERT((unsigned long)pvSrcAddr >= 0x20000000);
    ASSERT((unsigned long)pvDstAddr >= 0x20000000);
    ASSERT((ulTransferSize != 0) && (ulTransferSize <= 1024));

    //
    // Get the base address of the control table.
    //
    pControlTable = (tDMAControlTable *)HWREG(UDMA_CTLBASE);

    //
    // Get the current control word value and mask off the mode and size
    // fields.
    //
    ulControl = (pControlTable[ulChannel].ulControl &
                 ~(UDMA_CHCTL_XFERSIZE_M | UDMA_CHCTL_XFERMODE_M));

    //
    // Adjust the mode if the alt control structure is selected.
    //
    if(ulChannel & UDMA_ALT_SELECT)
    {
        if((ulMode == UDMA_MODE_MEM_SCATTER_GATHER) ||
           (ulMode == UDMA_MODE_PER_SCATTER_GATHER))
        {
            ulMode |= UDMA_MODE_ALT_SELECT;
        }
    }

    //
    // Set the transfer size and mode in the control word (but dont write the
    // control word yet as it could kick off a transfer).
    //
    ulControl |= ulMode | ((ulTransferSize - 1) << 4);

    //
    // Get the data item size from the control word (set previously).
    //
    ulSize = (ulControl & UDMA_CHCTL_DSTSIZE_M) >> 28;

    //
    // Convert the transfer size to be in units of bytes.  Shift (multiply) to
    // get the value in bytes, based on the data item size.
    //
    ulTransferSize = ulTransferSize << ulSize;

    //
    // Get the address increment value for the source, from the control word.
    //
    ulInc = (ulControl & UDMA_CHCTL_SRCINC_M);

    //
    // Compute the ending source address of the transfer.  If the source
    // increment is set to none, then the ending address is the same as the
    // beginning.
    //
    if(ulInc != UDMA_SRC_INC_NONE)
    {
        pvSrcAddr = (void *)((unsigned long)pvSrcAddr + ulTransferSize - 1);
    }

    //
    // Load the source ending address into the control block.
    //
    pControlTable[ulChannel].pvSrcEndAddr = pvSrcAddr;

    //
    // Get the address increment value for the destination, from the control
    // word.
    //
    ulInc = (ulControl & UDMA_CHCTL_DSTINC_M);

    //
    // Compute the ending destination address of the transfer.  If the
    // destination increment is set to none, then the ending address is the
    // same as the beginning.
    //
    if(ulInc != UDMA_DST_INC_NONE)
    {
        pvDstAddr = (void *)((unsigned long)pvDstAddr + ulTransferSize - 1);
    }

    //
    // Load the destination ending address into the control block.
    //
    pControlTable[ulChannel].pvDstEndAddr = pvDstAddr;

    //
    // Write the new control word value.
    //
    pControlTable[ulChannel].ulControl = ulControl;
}

//*****************************************************************************
//
//! Gets the current transfer size for a uDMA channel.
//!
//! \param ulChannel is the logical or of the uDMA channel number with either
//! \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT.
//!
//! This function is used to get the uDMA transfer size for a channel.  The
//! transfer size is the number of items to transfer, where the size of an item
//! might be 8, 16, or 32 bits.  If a partial transfer has already occurred,
//! then the number of remaining items will be returned.  If the transfer is
//! complete, then 0 will be returned.
//!
//! The \e ulChannel parameter is one of the choices documented in the
//! uDMAChannelEnable() function.  It should be the logical OR of the channel
//! with either \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT to choose whether
//! the primary or alternate data structure is used.
//!
//! \return Returns the number of items remaining to transfer.
//
//*****************************************************************************
unsigned long
uDMAChannelSizeGet(unsigned long ulChannel)
{
    tDMAControlTable *pControlTable;
    unsigned long ulControl;

    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 64);
    ASSERT(HWREG(UDMA_CTLBASE) != 0);

    //
    // Get the base address of the control table.
    //
    pControlTable = (tDMAControlTable *)HWREG(UDMA_CTLBASE);

    //
    // Get the current control word value and mask off all but the size field
    // and the mode field.
    //
    ulControl = pControlTable[ulChannel].ulControl &
                (UDMA_CHCTL_XFERSIZE_M | UDMA_CHCTL_XFERMODE_M);

    //
    // If the size field and mode field are 0 then the transfer is finished
    // and there are no more items to transfer
    //
    if(ulControl == 0)
    {
        return(0);
    }

    //
    // Otherwise, if either the size field or more field is non-zero, then
    // not all the items have been transferred.
    //
    else
    {
        //
        // Shift the size field and add one, then return to user.
        //
        return((ulControl >> 4) + 1);
    }
}

//*****************************************************************************
//
//! Gets the transfer mode for a uDMA channel.
//!
//! \param ulChannel is the logical or of the uDMA channel number with either
//! \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT.
//!
//! This function is used to get the transfer mode for the uDMA channel.  It
//! can be used to query the status of a transfer on a channel.  When the
//! transfer is complete the mode will be \b UDMA_MODE_STOP.
//!
//! The \e ulChannel parameter is one of the choices documented in the
//! uDMAChannelEnable() function.  It should be the logical OR of the channel
//! with either \b UDMA_PRI_SELECT or \b UDMA_ALT_SELECT to choose whether the
//! primary or alternate data structure is used.
//!
//! \return Returns the transfer mode of the specified channel and control
//! structure, which will be one of the following values: \b UDMA_MODE_STOP,
//! \b UDMA_MODE_BASIC, \b UDMA_MODE_AUTO, \b UDMA_MODE_PINGPONG,
//! \b UDMA_MODE_MEM_SCATTER_GATHER, or \b UDMA_MODE_PER_SCATTER_GATHER.
//
//*****************************************************************************
unsigned long
uDMAChannelModeGet(unsigned long ulChannel)
{
    tDMAControlTable *pControlTable;
    unsigned long ulControl;

    //
    // Check the arguments.
    //
    ASSERT(ulChannel < 64);
    ASSERT(HWREG(UDMA_CTLBASE) != 0);

    //
    // Get the base address of the control table.
    //
    pControlTable = (tDMAControlTable *)HWREG(UDMA_CTLBASE);

    //
    // Get the current control word value and mask off all but the mode field.
    //
    ulControl = pControlTable[ulChannel].ulControl & UDMA_CHCTL_XFERMODE_M;

    //
    // Check if scatter/gather mode, and if so, mask off the alt bit.
    //
    if(((ulControl & ~UDMA_MODE_ALT_SELECT) == UDMA_MODE_MEM_SCATTER_GATHER) ||
       ((ulControl & ~UDMA_MODE_ALT_SELECT) == UDMA_MODE_PER_SCATTER_GATHER))
    {
        ulControl &= ~UDMA_MODE_ALT_SELECT;
    }

    //
    // Return the mode to the caller.
    //
    return(ulControl);
}

//*****************************************************************************
//
//! Selects the secondary peripheral for a set of uDMA channels.
//!
//! \param ulSecPeriphs is the logical or of the uDMA channels for which to
//! use the secondary peripheral, instead of the default peripheral.
//!
//! This function is used to select the secondary peripheral assignment for
//! a set of uDMA channels.  By selecting the secondary peripheral assignment
//! for a channel, the default peripheral assignment is no longer available
//! for that channel.
//!
//! The parameter \e ulSecPeriphs can be the logical OR of any of the
//! following macros.  If one of the macros below is in the list passed
//! to this function, then the secondary peripheral (marked as \b _SEC_)
//! will be selected.
//!
//! - \b UDMA_DEF_USBEP1RX_SEC_UART2RX
//! - \b UDMA_DEF_USBEP1TX_SEC_UART2TX
//! - \b UDMA_DEF_USBEP2RX_SEC_TMR3A
//! - \b UDMA_DEF_USBEP2TX_SEC_TMR3B
//! - \b UDMA_DEF_USBEP3RX_SEC_TMR2A
//! - \b UDMA_DEF_USBEP3TX_SEC_TMR2B
//! - \b UDMA_DEF_ETH0RX_SEC_TMR2A
//! - \b UDMA_DEF_ETH0TX_SEC_TMR2B
//! - \b UDMA_DEF_UART0RX_SEC_UART1RX
//! - \b UDMA_DEF_UART0TX_SEC_UART1TX
//! - \b UDMA_DEF_SSI0RX_SEC_SSI1RX
//! - \b UDMA_DEF_SSI0TX_SEC_SSI1TX
//! - \b UDMA_DEF_RESERVED_SEC_UART2RX
//! - \b UDMA_DEF_RESERVED_SEC_UART2TX
//! - \b UDMA_DEF_ADC00_SEC_TMR2A
//! - \b UDMA_DEF_ADC01_SEC_TMR2B
//! - \b UDMA_DEF_ADC02_SEC_RESERVED
//! - \b UDMA_DEF_ADC03_SEC_RESERVED
//! - \b UDMA_DEF_TMR0A_SEC_TMR1A
//! - \b UDMA_DEF_TMR0B_SEC_TMR1B
//! - \b UDMA_DEF_TMR1A_SEC_EPI0RX
//! - \b UDMA_DEF_TMR1B_SEC_EPI0TX
//! - \b UDMA_DEF_UART1RX_SEC_RESERVED
//! - \b UDMA_DEF_UART1TX_SEC_RESERVED
//! - \b UDMA_DEF_SSI1RX_SEC_ADC10
//! - \b UDMA_DEF_SSI1TX_SEC_ADC11
//! - \b UDMA_DEF_RESERVED_SEC_ADC12
//! - \b UDMA_DEF_RESERVED_SEC_ADC13
//! - \b UDMA_DEF_I2S0RX_SEC_RESERVED
//! - \b UDMA_DEF_I2S0TX_SEC_RESERVED
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelSelectSecondary(unsigned long ulSecPeriphs)
{
    //
    // Select the secondary peripheral for the specified channels.
    //
    HWREG(UDMA_CHALT) |= ulSecPeriphs;
}

//*****************************************************************************
//
//! Selects the default peripheral for a set of uDMA channels.
//!
//! \param ulDefPeriphs is the logical or of the uDMA channels for which to
//! use the default peripheral, instead of the secondary peripheral.
//!
//! This function is used to select the default peripheral assignment for
//! a set of uDMA channels.
//!
//! The parameter \e ulDefPeriphs can be the logical OR of any of the
//! following macros.  If one of the macros below is in the list passed
//! to this function, then the default peripheral (marked as \b _DEF_)
//! will be selected.
//!
//! - \b UDMA_DEF_USBEP1RX_SEC_UART2RX
//! - \b UDMA_DEF_USBEP1TX_SEC_UART2TX
//! - \b UDMA_DEF_USBEP2RX_SEC_TMR3A
//! - \b UDMA_DEF_USBEP2TX_SEC_TMR3B
//! - \b UDMA_DEF_USBEP3RX_SEC_TMR2A
//! - \b UDMA_DEF_USBEP3TX_SEC_TMR2B
//! - \b UDMA_DEF_ETH0RX_SEC_TMR2A
//! - \b UDMA_DEF_ETH0TX_SEC_TMR2B
//! - \b UDMA_DEF_UART0RX_SEC_UART1RX
//! - \b UDMA_DEF_UART0TX_SEC_UART1TX
//! - \b UDMA_DEF_SSI0RX_SEC_SSI1RX
//! - \b UDMA_DEF_SSI0TX_SEC_SSI1TX
//! - \b UDMA_DEF_RESERVED_SEC_UART2RX
//! - \b UDMA_DEF_RESERVED_SEC_UART2TX
//! - \b UDMA_DEF_ADC00_SEC_TMR2A
//! - \b UDMA_DEF_ADC01_SEC_TMR2B
//! - \b UDMA_DEF_ADC02_SEC_RESERVED
//! - \b UDMA_DEF_ADC03_SEC_RESERVED
//! - \b UDMA_DEF_TMR0A_SEC_TMR1A
//! - \b UDMA_DEF_TMR0B_SEC_TMR1B
//! - \b UDMA_DEF_TMR1A_SEC_EPI0RX
//! - \b UDMA_DEF_TMR1B_SEC_EPI0TX
//! - \b UDMA_DEF_UART1RX_SEC_RESERVED
//! - \b UDMA_DEF_UART1TX_SEC_RESERVED
//! - \b UDMA_DEF_SSI1RX_SEC_ADC10
//! - \b UDMA_DEF_SSI1TX_SEC_ADC11
//! - \b UDMA_DEF_RESERVED_SEC_ADC12
//! - \b UDMA_DEF_RESERVED_SEC_ADC13
//! - \b UDMA_DEF_I2S0RX_SEC_RESERVED
//! - \b UDMA_DEF_I2S0TX_SEC_RESERVED
//!
//! \return None.
//
//*****************************************************************************
void
uDMAChannelSelectDefault(unsigned long ulDefPeriphs)
{
    //
    // Select the default peripheral for the specified channels.
    //
    HWREG(UDMA_CHALT) &= ~ulDefPeriphs;
}

//*****************************************************************************
//
//! Registers an interrupt handler for the uDMA controller.
//!
//! \param ulIntChannel identifies which uDMA interrupt is to be registered.
//! \param pfnHandler is a pointer to the function to be called when the
//! interrupt is activated.
//!
//! This sets and enables the handler to be called when the uDMA controller
//! generates an interrupt.  The \e ulIntChannel parameter should be one of the
//! following:
//!
//! - \b UDMA_INT_SW to register an interrupt handler to process interrupts
//!   from the uDMA software channel (UDMA_CHANNEL_SW)
//! - \b UDMA_INT_ERR to register an interrupt handler to process uDMA error
//!   interrupts
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \note The interrupt handler for uDMA is for transfer completion when the
//! channel UDMA_CHANNEL_SW is used, and for error interrupts.  The
//! interrupts for each peripheral channel are handled through the individual
//! peripheral interrupt handlers.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAIntRegister(unsigned long ulIntChannel, void (*pfnHandler)(void))
{
    //
    // Check the arguments.
    //
    ASSERT(pfnHandler);
    ASSERT((ulIntChannel == UDMA_INT_SW) || (ulIntChannel == UDMA_INT_ERR));

    //
    // Register the interrupt handler.
    //
    IntRegister(ulIntChannel, pfnHandler);

    //
    // Enable the memory management fault.
    //
    IntEnable(ulIntChannel);
}

//*****************************************************************************
//
//! Unregisters an interrupt handler for the uDMA controller.
//!
//! \param ulIntChannel identifies which uDMA interrupt to unregister.
//!
//! This function will disable and clear the handler to be called for the
//! specified uDMA interrupt.  The \e ulIntChannel parameter should be one of
//! \b UDMA_INT_SW or \b UDMA_INT_ERR as documented for the function
//! uDMAIntRegister().
//!
//! \sa IntRegister() for important information about registering interrupt
//! handlers.
//!
//! \return None.
//
//*****************************************************************************
void
uDMAIntUnregister(unsigned long ulIntChannel)
{
    //
    // Disable the interrupt.
    //
    IntDisable(ulIntChannel);

    //
    // Unregister the interrupt handler.
    //
    IntUnregister(ulIntChannel);
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
