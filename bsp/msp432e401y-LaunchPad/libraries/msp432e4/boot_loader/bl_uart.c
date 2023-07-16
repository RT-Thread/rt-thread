//*****************************************************************************
//
// bl_uart.c - Functions to transfer data via the UART port.
//
// Copyright (c) 2006-2017 Texas Instruments Incorporated.  All rights reserved.
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
//*****************************************************************************

#include <stdint.h>
#include "bl_config.h"
#include "ti/devices/msp432e4/inc/msp.h"
#include "ti/devices/msp432e4/boot_loader/bl_uart.h"

//*****************************************************************************
//
//! \addtogroup bl_uart_api
//! @{
//
//*****************************************************************************
#if defined(UART_ENABLE_UPDATE) || defined(DOXYGEN)

//*****************************************************************************
//
//! Sends data over the UART port.
//!
//! \param pui8Data is the buffer containing the data to write out to the UART
//! port.
//! \param ui32Size is the number of bytes provided in \e pui8Data buffer that
//! will be written out to the UART port.
//!
//! This function sends \e ui32Size bytes of data from the buffer pointed to by
//! \e pui8Data via the UART port.
//!
//! \return None.
//
//*****************************************************************************
void
UARTSend(const uint8_t *pui8Data, uint32_t ui32Size)
{
    //
    // Transmit the number of bytes requested on the UART port.
    //
    while(ui32Size--)
    {
        //
        // Make sure that the transmit FIFO is not full.
        //
        while(UARTx->FR & UART_FR_TXFF)
        {
        }

        //
        // Send out the next byte.
        //
        UARTx->DR = *pui8Data++;
    }

    //
    // Wait until the UART is done transmitting.
    //
    UARTFlush();
}

//*****************************************************************************
//
//! Waits until all data has been transmitted by the UART port.
//!
//! This function waits until all data written to the UART port has been
//! transmitted.
//!
//! \return None.
//
//*****************************************************************************
void
UARTFlush(void)
{
    //
    // Wait for the UART FIFO to empty and then wait for the shifter to get the
    // bytes out the port.
    //
    while(!(UARTx->FR & UART_FR_TXFE))
    {
    }

    //
    // Wait for the FIFO to not be busy so that the shifter completes.
    //
    while(UARTx->FR & UART_FR_BUSY)
    {
    }
}

//*****************************************************************************
//
//! Receives data over the UART port.
//!
//! \param pui8Data is the buffer to read data into from the UART port.
//! \param ui32Size is the number of bytes provided in the \e pui8Data buffer
//! that should be written with data from the UART port.
//!
//! This function reads back \e ui32Size bytes of data from the UART port, into
//! the buffer that is pointed to by \e pui8Data.  This function will not
//! return until \e ui32Size number of bytes have been received.
//!
//! \return None.
//
//*****************************************************************************
void
UARTReceive(uint8_t *pui8Data, uint32_t ui32Size)
{
    //
    // Send out the number of bytes requested.
    //
    while(ui32Size--)
    {
        //
        // Wait for the FIFO to not be empty.
        //
        while(UARTx->FR & UART_FR_RXFE)
        {
        }

        //
        // Receive a byte from the UART.
        //
        *pui8Data++ = UARTx->DR;
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif
