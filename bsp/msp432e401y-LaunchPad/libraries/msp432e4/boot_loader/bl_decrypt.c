//*****************************************************************************
//
// bl_decrypt.c - Code for performing an in-place decryption of the firmware
//                image as it is downloaded.
//
// Copyright (c) 2007-2017 Texas Instruments Incorporated.  All rights reserved.
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
#include "ti/devices/msp432e4/boot_loader/bl_decrypt.h"

//*****************************************************************************
//
//! \addtogroup bl_decrypt_api
//! @{
//
//*****************************************************************************
#if defined(ENABLE_DECRYPTION) || defined(DOXYGEN)

//*****************************************************************************
//
//! Performs an in-place decryption of downloaded data.
//!
//! \param pui8Buffer is the buffer that holds the data to decrypt.
//! \param ui32Size is the size, in bytes, of the buffer that was passed in via
//! the \e pui8Buffer parameter.
//!
//! This function is a stub that could provide in-place decryption of the data
//! that is being downloaded to the device.
//!
//! \return None.
//
//*****************************************************************************
void
DecryptData(uint8_t *pui8Buffer, uint32_t ui32Size)
{
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
#endif

