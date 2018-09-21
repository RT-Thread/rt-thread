//*****************************************************************************
//
//  am_hal_ttp.c
//! @file
//!
//! @brief Functions for handling the "two time program" interface.
//!
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************
#include "am_mcu_apollo.h"
#include "am_hal_ttp.h"

//*****************************************************************************
//
// Local constants
//
//*****************************************************************************
#define TTP_ADDR                0x50020000

//*****************************************************************************
//
// Local prototypes
//
//*****************************************************************************
#if !defined(__GNUC__)
void __breakpoint(int val);
#endif

//*****************************************************************************
//
// A function to verify that the TTP was saved and/or restored properly.
//
//*****************************************************************************
int
verifyTTPSaved(uint32_t *pSaveArray, int iNumWords)
{
    int ix, iErrCnt = 0;
    uint32_t *pDataSpace = (uint32_t*)TTP_ADDR;

    for (ix = 0; ix<iNumWords; ix++)
    {
        if ( *pSaveArray != am_hal_flash_load_ui32((uint32_t)pDataSpace) )
        {
            iErrCnt++;
        }
        pSaveArray++;
        pDataSpace++;
    }

    //
    // Hopefully returning 0.
    //
    return iErrCnt;
}

//*****************************************************************************
//
//! @brief TTP unlock.
//!
//! @param ui32Keyval - The key value to unlock the interface.
//! @param pui8_1024Bytes - A pointer to a 1024 bytes array, used for
//!                         temporary data storage.
//!                         WARNING This area must be 32-bit aligned and at
//!                         least 1024 bytes long.
//!
//! This function is used to unlock the TTP ability.
//!
//! @return None.
//
//*****************************************************************************
int
am_hal_ttp_unlock(uint32_t ui32Keyval, uint8_t *pui8_1024Bytes)
{
    int iErrCnt = 0;
    int ix, iRet;
    int iNumWords = 1024 / 4;
    uint32_t *pSaveArray, *pDataSpace;
    int (*pTTPClear)(uint32_t, uint32_t) = (int (*)(uint32_t, uint32_t))0x080002EF;
    int (*pTTPSet)(uint32_t, uint32_t, uint32_t*, uint32_t, uint32_t) =
        (int (*)(uint32_t, uint32_t, uint32_t*, uint32_t, uint32_t))0x080006FF;

    //
    // Save off the data.
    //
    pSaveArray = (uint32_t*)pui8_1024Bytes;
    pDataSpace = (uint32_t*)TTP_ADDR;
    for (ix = 0; ix < iNumWords; ix++)
    {
        *pSaveArray = am_hal_flash_load_ui32((uint32_t)pDataSpace);
        pSaveArray++;
        pDataSpace++;
    }

    //
    // Before proceeding, make sure that we captured the data correctly.
    //
    iErrCnt += verifyTTPSaved((uint32_t*)pui8_1024Bytes, iNumWords);
    if ( iErrCnt )
    {
        return 0x10000001;
    }

    //
    // Erase the TTP area.
    //
    iRet = (*pTTPClear)(0, ui32Keyval);
    if ( iRet != 0 )
    {
        iErrCnt++;
        return 0x10000002;
    }

    //
    // The point of no return!  The TTP space is successfully erased.
    // Let's make sure.
    //
    pDataSpace = (uint32_t*)TTP_ADDR;
    for (ix = 0; ix < iNumWords; ix++)
    {
        if ( am_hal_flash_load_ui32((uint32_t)pDataSpace) != 0xffffffff )
        {
            iErrCnt++;
        }
        pDataSpace++;
    }

    if ( iErrCnt )
    {
        return 0x10000003;
    }

    //
    // Restore the TTP block from the saved data.
    //
    iRet = (*pTTPSet)(ui32Keyval, 0, (uint32_t*)pui8_1024Bytes, 0, iNumWords);
    if ( iRet != 0 )
    {
        iErrCnt++;
        return 0x10000004;
    }

    //
    // Now, check the restored INFO data.
    //
    iRet = verifyTTPSaved((uint32_t*)pui8_1024Bytes, iNumWords);
    if ( iRet )
    {
        iErrCnt++;
        return 0x10000005;
    }
    else
    {
        //
        // All good.  The device was successfully recovered.
        //
    }


    //
    // Return with error count (hopefully 0).
    //
    return iErrCnt;
}

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
