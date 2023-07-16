//*****************************************************************************
//
// bl_crc32.c - CRC32 calculation functions used in the boot loader.
//
// Copyright (c) 2013-2017 Texas Instruments Incorporated.  All rights reserved.
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
#include "ti/devices/msp432e4/boot_loader/bl_crc32.h"

//*****************************************************************************
//
// Storage for the CRC32 calculation lookup table.
//
//*****************************************************************************
static uint32_t g_pui32CRC32Table[256];

//*****************************************************************************
//
// Initialize the CRC32 calculation table for the polynomial used.  We pick
// the commonly used ANSI X 3.66 polymonial.  This code was informed by an
// example found at http://www.createwindow.com/programming/crc32/index.htm.
//
//*****************************************************************************
static uint32_t
Reflect(uint32_t ui32Ref, uint8_t ui8Ch)
{
    uint_fast32_t ui32Value;
    int_fast16_t i16Loop;

    //
    // Clear our accumulator variable.
    //
    ui32Value = 0;

    //
    // Swap bit 0 for bit 7, bit 1 for bit 6, etc.
    //
    for(i16Loop = 1; i16Loop < (ui8Ch + 1); i16Loop++)
    {
        if(ui32Ref & 1)
        {
            ui32Value |= 1 << (ui8Ch - i16Loop);
        }
        ui32Ref >>= 1;
    }

    //
    // Return the reflected value.
    //
    return(ui32Value);
}

//*****************************************************************************
//
// Initialize the lookup table used in calculating the CRC32 value.
//
//*****************************************************************************
void
InitCRC32Table(void)
{
    uint_fast32_t ui32Polynomial;
    int_fast16_t i16Loop, i16Bit;

    //
    // This is the ANSI X 3.66 polynomial as required by the DFU
    // specification.
    //
    ui32Polynomial = 0x04c11db7;

    for(i16Loop = 0; i16Loop <= 0xFF; i16Loop++)
    {
        g_pui32CRC32Table[i16Loop]=Reflect(i16Loop, 8) << 24;
          for (i16Bit = 0; i16Bit < 8; i16Bit++)
          {
              g_pui32CRC32Table[i16Loop] = ((g_pui32CRC32Table[i16Loop] << 1) ^
                                            (g_pui32CRC32Table[i16Loop] &
                                             ((uint32_t)1 << 31) ?
                                             ui32Polynomial : 0));
          }
          g_pui32CRC32Table[i16Loop] = Reflect(g_pui32CRC32Table[i16Loop], 32);
    }
}

//*****************************************************************************
//
// Calculate the CRC for the supplied block of data.
//
//*****************************************************************************
uint32_t
CalculateCRC32(uint8_t *pui8Data, uint32_t ui32Length, uint32_t ui32CRC)
{
    uint32_t ui32Count;
    uint8_t *pui8Buffer;
    uint8_t ui8Char;

    //
    // Get a pointer to the start of the data and the number of bytes to
    // process.
    //
    pui8Buffer = pui8Data;
    ui32Count = ui32Length;

    //
    // Perform the algorithm on each byte in the supplied buffer using the
    // lookup table values calculated in InitCRC32Table().
    //
    while(ui32Count--)
    {
        ui8Char = *pui8Buffer++;
        ui32CRC = (ui32CRC >> 8) ^ g_pui32CRC32Table[(ui32CRC & 0xFF) ^
                  ui8Char];
    }

    //
    // Return the result.
    //
    return(ui32CRC);
}

//*****************************************************************************
//
//! Checks that the embedded CRC in the image matches the expected value.
//!
//! \param pui32Image points to the start of the firmware image in memory.
//!
//! This function finds the firmware image information header and verifies that
//! the embedded CRC32 matches one calculated over the image.
//!
//! \return Returns \b CHECK_CRC_OK if the CRC calculated matches the value
//! embedded in the image, \b CHECK_CRC_NO_HEADER if no image information
//! header was found at the top of the vector table, \b CHECK_CRC_BAD_CRC if
//! an embedded CRC was found but did not match the calculated value or \b
//! CHECK_CRC_ZERO_LENGTH if the length field of the image information header
//! contains 0 (likely indicating that the image had not been run through the
//! binpack tool which inserts the length and CRC values into the header).
//
//*****************************************************************************
uint32_t
CheckImageCRC32(uint32_t *pui32Image)
{
    uint32_t ui32Loop, ui32FlashSize, ui32CRC;

    //
    // Determine the size of flash (giving an upper bound for the image
    // size).
    //
    ui32FlashSize = ((2048 * ((FLASH_CTRL->PP & FLASH_PP_SIZE_M) + 1)) -
                     APP_START_ADDRESS);

    //
    // Scan for the image information header marker bytes.  Given that the
    // largest possible vector table includes 16 system exceptions and 240
    // IC-specific vectors, we only need to search 257 words into memory before
    // giving up.
    //
    for(ui32Loop = 0; ui32Loop < 257; ui32Loop++)
    {
        //
        // Have we found the header marker words?
        //
        if((pui32Image[ui32Loop] == 0xFF01FF02) &&
           (pui32Image[ui32Loop + 1] == 0xFF03FF04))
        {
            //
            // Yes.  Check to see if the length field is 0xFFFFFFFF.  This
            // likely indicates that the image has not been processed by the
            // binpack tool which adds the length and CRC information to the
            // image header.
            //
            if(pui32Image[ui32Loop + 2] == 0xFFFFFFFF)
            {
                //
                // The header reports an image size of 0 so we can't go on and
                // check the CRC.
                //
                return(CHECK_CRC_NO_LENGTH);
            }

            //
            // Extract the image length and ensure that it is sensible
            // given the flash size.  We assume the length is invalid if it
            // is larger than the available flash size or smaller than the
            // space taken up by the vector table and header we've already
            // scanned through.
            //
            if((pui32Image[ui32Loop + 2] > ui32FlashSize) ||
               (pui32Image[ui32Loop + 2] <
                ((ui32Loop + 4) * sizeof(uint32_t))))
            {
                //
                // The header reports an image size that is larger than the
                // available flash so this is obviously incorrect.  Fail the
                // check.
                //
                return(CHECK_CRC_BAD_LENGTH);
            }

            //
            // Calculate the CRC32 value for the image.  Note that we skip the
            // 4 bytes that hold the check CRC.
            //
            ui32CRC = CalculateCRC32((uint8_t *)pui32Image,
                                     (ui32Loop + 3) * sizeof(uint32_t),
                                     0xffffffff);
            ui32CRC = CalculateCRC32((uint8_t *)&pui32Image[ui32Loop + 4],
                                     (pui32Image[ui32Loop + 2] -
                                      ((ui32Loop + 4) * sizeof(uint32_t))),
                                      ui32CRC);
            ui32CRC ^= 0xffffffff;

            //
            // Determine whether the calculated CRC matches the value stored
            // in the image information header.
            //
            if(ui32CRC == pui32Image[ui32Loop + 3])
            {
                return(CHECK_CRC_OK);
            }
            else
            {
                return(CHECK_CRC_BAD_CRC);
            }
        }
    }

    //
    // If we drop out the loop, there was no image information header so
    // fail the call.
    //
    return(CHECK_CRC_NO_HEADER);
}
