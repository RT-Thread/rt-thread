//*****************************************************************************
//
// bl_i2c.c - This file contains the function used to transfer data via the I2C
//            port.
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
#include "ti/devices/msp432e4/boot_loader/bl_i2c.h"

//*****************************************************************************
//
//! \addtogroup bl_i2c_api
//! @{
//
//*****************************************************************************
#if defined(I2C_ENABLE_UPDATE) || defined(DOXYGEN)

//*****************************************************************************
//
//! Sends data over the I2C port.
//!
//! \param pui8Data is the buffer containing the data to write out to the I2C
//! port.
//! \param ui32Size is the number of bytes provided in \e pui8Data buffer that
//! will be written out to the I2C port.
//!
//! This function sends \e ui32Size bytes of data from the buffer pointed to by
//! \e pui8Data via the I2C port.  The function will wait till the I2C Slave
//! port has been properly addressed by the I2C Master device before sending
//! the first byte.
//!
//! \return None.
//
//*****************************************************************************
void
I2CSend(const uint8_t *pui8Data, uint32_t ui32Size)
{
    //
    // Transmit the number of bytes requested on the UART port.
    //
    while(ui32Size--)
    {
        //
        // Wait for request to come in at slave.
        //
        while(!(I2Cx->SCSR & I2C_SCSR_TREQ))
        {
        }

        //
        // Send out the next byte.
        //
        I2Cx->SDR = *pui8Data++;
    }
}

//*****************************************************************************
//
//! Waits until all data has been transmitted by the I2C port.
//!
//! This function waits until all data written to the I2C port has been read by
//! the master.
//!
//! \return None.
//
//*****************************************************************************
void
I2CFlush(void)
{
    //
    // Wait until the I2C bus is no longer busy, meaning that the last byte has
    // been sent.
    //
    while(I2Cx->MCS & I2C_MCS_BUSBSY)
    {
    }
}

//*****************************************************************************
//
//! Receives data over the I2C port.
//!
//! \param pui8Data is the buffer to read data into from the I2C port.
//! \param ui32Size is the number of bytes provided in the \e pui8Data buffer
//! that should be written with data from the I2C port.
//!
//! This function reads back \e ui32Size bytes of data from the I2C port, into
//! the buffer that is pointed to by \e pui8Data.  This function will not
//! return until \e ui32Size number of bytes have been received.  This function
//! will wait till the I2C Slave port has been properly addressed by the I2C
//! Master before reading the first byte of data from the I2C port.
//!
//! \return None.
//
//*****************************************************************************
void
I2CReceive(uint8_t *pui8Data, uint32_t ui32Size)
{
    //
    // Send out the number of bytes requested.
    //
    while(ui32Size--)
    {
        //
        // Wait until the slave has received the character.
        //
        while(!(I2Cx->SCSR & I2C_SCSR_RREQ))
        {
        }

        //
        // Receive a byte from the I2C.
        //
        *pui8Data++ = I2Cx->SDR;
    }
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif
