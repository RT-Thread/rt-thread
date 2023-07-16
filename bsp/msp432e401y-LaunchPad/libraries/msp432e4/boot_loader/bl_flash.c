//*****************************************************************************
//
// bl_flash.c - Flash programming functions used by the boot loader.
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
#include "ti/devices/msp432e4/boot_loader/bl_flash.h"

//*****************************************************************************
//
//! Erases a single 1KB block of internal flash.
//!
//! \param ui32Address is the address of the block of flash to erase.
//!
//! This function erases a single 1KB block of the internal flash, blocking
//! until the erase has completed.
//!
//! \return None
//
//*****************************************************************************
void
BLInternalFlashErase(uint32_t ui32Address)
{
    //
    // Erase this block of the flash.
    //
    FLASH_CTRL->FMA = ui32Address;
    FLASH_CTRL->FMC = FLASH_FMC_WRKEY | FLASH_FMC_ERASE;

    //
    // Wait until the flash has been erased.
    //
    while(FLASH_CTRL->FMC & FLASH_FMC_ERASE)
    {
    }
}

//*****************************************************************************
//
//! Programs a block of data at a given address in the internal flash.
//!
//! \param ui32DstAddr is the address of the first word to be programmed in
//! flash.
//! \param pui8SrcData is a pointer to the first byte to be programmed.
//! \param ui32Length is the number of bytes to program.  This must be a
//! multiple of 4.
//!
//! This function writes a block of data to the internal flash at a given
//! address.  Since the flash is written a word at a time, the data must be a
//! multiple of 4 bytes and the destination address, ui32DstAddr, must be on a
//! word boundary.
//!
//! \return None
//
//*****************************************************************************
void
BLInternalFlashProgram(uint32_t ui32DstAddr, uint8_t *pui8SrcData,
                       uint32_t ui32Length)
{
    uint32_t ui32Loop;

    for(ui32Loop = 0; ui32Loop < ui32Length; ui32Loop += 4)
    {
        //
        // Program this word into flash.
        //
        FLASH_CTRL->FMA = ui32DstAddr + ui32Loop;
        FLASH_CTRL->FMD = *(uint32_t *)(pui8SrcData + ui32Loop);
        FLASH_CTRL->FMC = FLASH_FMC_WRKEY | FLASH_FMC_WRITE;

        //
        // Wait until the flash has been programmed.
        //
        while(FLASH_CTRL->FMC & FLASH_FMC_WRITE)
        {
        }
    }
}

//*****************************************************************************
//
//! Returns the size of the internal flash in bytes.
//!
//! This function returns the total number of bytes of internal flash in the
//! current part.  No adjustment is made for any sections reserved via
//! options defined in bl_config.h.
//!
//! \return Returns the total number of bytes of internal flash.
//
//*****************************************************************************
uint32_t
BLInternalFlashSizeGet(void)
{
    return(((FLASH_CTRL->PP & FLASH_PP_SIZE_M) + 1) << 11);
}

//*****************************************************************************
//
//! Checks whether a given start address is valid for a download.
//!
//! This function checks to determine whether the given address is a valid
//! download image start address given the options defined in bl_config.h.
//!
//! \return Returns non-zero if the address is valid or 0 otherwise.
//
//*****************************************************************************
uint32_t
BLInternalFlashStartAddrCheck(uint32_t ui32Addr, uint32_t ui32ImgSize)
{
    uint32_t ui32FlashSize;

    //
    // Determine the size of the flash available on the part in use.
    //
    ui32FlashSize = ((FLASH_CTRL->PP & FLASH_PP_SIZE_M) + 1) << 11;

    //
    // If we are reserving space at the top of flash then this space is not
    // available for application download but it is availble to be updated
    // directly.
    //
#ifdef FLASH_RSVD_SPACE
    if((ui32FlashSize - FLASH_RSVD_SPACE) != ui32Addr)
    {
        ui32FlashSize -= FLASH_RSVD_SPACE;
    }
#endif

    //
    // Is the address we were passed a valid start address?  We allow:
    //
    // 1. Address 0 if configured to update the boot loader.
    // 2. The start of the reserved block if parameter space is reserved (to
    //    allow a download of the parameter block contents).
    // 3. The application start address specified in bl_config.h.
    //
    // The function fails if the address is not one of these, if the image
    // size is larger than the available space or if the address is not word
    // aligned.
    //
    if((
#ifdef ENABLE_BL_UPDATE
        (ui32Addr != 0) &&
#endif
#ifdef FLASH_RSVD_SPACE
        (ui32Addr != (ui32FlashSize - FLASH_RSVD_SPACE)) &&
#endif
#ifndef ENABLE_BL_UPDATE
        (ui32Addr < APP_START_ADDRESS)) ||
#endif
       ((ui32Addr + ui32ImgSize) > ui32FlashSize) || ((ui32Addr & 3) != 0))
    {
        return(0);
    }
    else
    {
        return(1);
    }
}

//*****************************************************************************
//
//! Checks whether a flash access violation occurred.
//!
//! This function checks whether an access violation error occurred during
//! the previous program or erase operation.
//!
//! \return Returns 0 if no error occurred or a non-zero value if an error was
//! reported.
//
//*****************************************************************************
void
BLInternalFlashErrorClear(void)
{
    //
    // Clear the flash controller access interrupt.
    //
    FLASH_CTRL->FCMISC = FLASH_FCMISC_AMISC;
}

//*****************************************************************************
//
//! Checks whether a flash access violation occurred.
//!
//! This function checks whether an access violation error occurred since the
//! last call to BLInternalFlashErrorClear().
//!
//! \return Returns 0 if no error occurred or a non-zero value if an error was
//! reported.
//
//*****************************************************************************
uint32_t
BLInternalFlashErrorCheck(void)
{
    return(FLASH_CTRL->FCRIS & FLASH_FCRIS_ARIS);
}
