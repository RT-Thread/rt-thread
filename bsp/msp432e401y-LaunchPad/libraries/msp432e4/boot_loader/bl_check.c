//*****************************************************************************
//
// bl_check.c - Code to check for a forced update.
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
#include <stdbool.h>
#include "bl_config.h"
#include "ti/devices/msp432e4/inc/msp.h"
#include "ti/devices/msp432e4/boot_loader/bl_check.h"
#include "ti/devices/msp432e4/boot_loader/bl_hooks.h"
#ifdef CHECK_CRC
#include "ti/devices/msp432e4/boot_loader/bl_crc32.h"
#endif

//*****************************************************************************
//
//! \addtogroup bl_check_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// This global is used to remember if a forced update occurred.
//
//*****************************************************************************
#ifdef ENABLE_UPDATE_CHECK
uint32_t g_ui32Forced;
#endif

//*****************************************************************************
//
// A prototype for the function (in the startup code) for a predictable length
// delay.
//
//*****************************************************************************
extern void Delay(uint32_t ui32Count);

//*****************************************************************************
//
//! Checks a GPIO for a forced update.
//!
//! This function checks the state of a GPIO to determine if a update is being
//! requested.
//!
//! \return Returns a non-zero value if an update is being requested and zero
//! otherwise.
//
//*****************************************************************************
#ifdef ENABLE_UPDATE_CHECK
uint32_t
CheckGPIOForceUpdate(void)
{
    //
    // Enable the required GPIO module.
    //
    SYSCTL->RCGCGPIO |= FORCED_UPDATE_PERIPH;

    //
    // Wait a while before accessing the peripheral.
    //
    Delay(3);

#ifdef FORCED_UPDATE_KEY
    //
    // Unlock the GPIO Access.
    //
    FORCED_UPDATE_PORT->LOCK = FORCED_UPDATE_KEY;
    FORCED_UPDATE_PORT->CR   = 1 << FORCED_UPDATE_PIN;
#endif

    //
    // Enable the pin used to see if an update is being requested.
    //
    FORCED_UPDATE_PORT->DEN |= 1 << FORCED_UPDATE_PIN;
#ifdef FORCED_UPDATE_WPU
    //
    // Set the output drive strength.
    //
    FORCED_UPDATE_PORT->DR2R |= 1 << FORCED_UPDATE_PIN;

    //
    // Enable the weak pull up.
    //
    FORCED_UPDATE_PORT->PUR |= 1 << FORCED_UPDATE_PIN;

    //
    // Make sure that the analog mode select register is clear for this pin.
    //
    FORCED_UPDATE_PORT->AMSEL &= ~(1 << FORCED_UPDATE_PIN);
#endif
#ifdef FORCED_UPDATE_WPD
    //
    // Set the output drive strength.
    //
    FORCED_UPDATE_PORT->DR2R |= 1 << FORCED_UPDATE_PIN;

    //
    // Enable the weak pull down.
    //
    FORCED_UPDATE_PORT->PDR |= 1 << FORCED_UPDATE_PIN;

    //
    // Make sure that the analog mode select register is clear for this pin.
    // This register only appears in DustDevil-class (and later) devices, but
    // is a harmless write on Sandstorm- and Fury-class devices.
    //
    FORCED_UPDATE_PORT->AMSEL &= ~(1 << FORCED_UPDATE_PIN);
#endif

#ifdef FORCED_UPDATE_KEY
    //
    // Unlock the GPIO Access.
    //
    FORCED_UPDATE_PORT->LOCK = FORCED_UPDATE_KEY;
    FORCED_UPDATE_PORT->CR   = 0;
#endif

    //
    // Wait a while before reading the pin.
    //
    Delay(1000);

    //
    // Check the pin to see if an update is being requested.
    //
    if((FORCED_UPDATE_PORT->DATA & (1 << FORCED_UPDATE_PIN)) ==
       (FORCED_UPDATE_POLARITY << FORCED_UPDATE_PIN))
    {
        //
        // Remember that this was a forced update.
        //
        g_ui32Forced = 1;

        return(1);
    }

    //
    // No update is being requested so return 0.
    //
    return(0);
}
#endif

//*****************************************************************************
//
//! Checks if an update is needed or is being requested.
//!
//! This function detects if an update is being requested or if there is no
//! valid code presently located on the microcontroller.  This is used to tell
//! whether or not to enter update mode.
//!
//! \return Returns a non-zero value if an update is needed or is being
//! requested and zero otherwise.
//
//*****************************************************************************
uint32_t
CheckForceUpdate(void)
{
#ifdef CHECK_CRC
    uint32_t ui32Retcode;
#endif

#ifdef BL_CHECK_UPDATE_FN_HOOK
    //
    // If the update check function is hooked, call the application to determine
    // how to proceed.
    //
    return(BL_CHECK_UPDATE_FN_HOOK());
#else
    uint32_t *pui32App;

#ifdef ENABLE_UPDATE_CHECK
    g_ui32Forced = 0;
#endif

    //
    // See if the first location is 0xfffffffff or something that does not
    // look like a stack pointer, or if the second location is 0xffffffff or
    // something that does not look like a reset vector.
    //
    pui32App = (uint32_t *)APP_START_ADDRESS;
    if((pui32App[0] == 0xffffffff) ||
       ((pui32App[0] & 0xfff00000) != 0x20000000) ||
       (pui32App[1] == 0xffffffff) ||
       ((pui32App[1] & 0xfff00001) != 0x00000001))
    {
        return(1);
    }

    //
    // If required, scan the image for an embedded CRC and ensure that it
    // matches the current CRC of the image.
    //
#ifdef CHECK_CRC
    InitCRC32Table();
    ui32Retcode = CheckImageCRC32(pui32App);

    //
    // If ENFORCE_CRC is defined, we only boot the image if the CRC is
    // present in the image information header and the value calculated
    // matches the value in the header.  If ENFORCE_CRC is not defined, we
    // the image if the CRC is good but also if the length field of the header
    // is zero (which typically indicates that the post-build step of running
    // binpack to add the length and CRC to the header was not run).
    //
#ifdef ENFORCE_CRC
    if(ui32Retcode != CHECK_CRC_OK)
#else
    if((ui32Retcode != CHECK_CRC_OK) && (ui32Retcode != CHECK_CRC_NO_LENGTH))
#endif
    {
        //
        // The CRC32 image check failed indicating that the image is
        // corrupt (or doesn't have the CRC embedded correctly).  Either way,
        // fail the update check and force the boot loader to retain control.
        //
        return(2);
    }
#endif

#ifdef ENABLE_UPDATE_CHECK
    //
    // If simple GPIO checking is configured, determine whether or not to force
    // an update.
    //
    return(CheckGPIOForceUpdate());
#else
    //
    // GPIO checking is not required so, if we get here, a valid image exists
    // and no update is needed.
    //
    return(0);
#endif
#endif
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
