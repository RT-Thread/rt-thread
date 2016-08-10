/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#include "fsl_crc_hal.h"
#if FSL_FEATURE_SOC_CRC_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : CRC_HAL_Init
 * Description   : This function initializes the module to a known state.
 *
 *END**************************************************************************/
void CRC_HAL_Init(CRC_Type * base)
{
    uint32_t seedAndData = 0;

    CRC_BWR_CTRL_TCRC(base, kCrc32Bits);
    /*SetReadTranspose (no transpose)*/
    CRC_BWR_CTRL_TOTR(base, kCrcNoTranspose);
    /*SetWriteTranspose (no transpose)*/
    CRC_BWR_CTRL_TOT(base, kCrcNoTranspose);
    /*SetXorMode (xor mode disabled)*/
    CRC_BWR_CTRL_FXOR(base, false);
    /*SetSeedOrDataMode (seed selected)*/
    CRC_BWR_CTRL_WAS(base, true);

#if FSL_FEATURE_CRC_HAS_CRC_REG
    CRC_WR_CRC(base, seedAndData);
#else
    CRC_WR_DATA(base, seedAndData);
#endif
    /*SetSeedOrDataMode (seed selected)*/
    CRC_BWR_CTRL_WAS(base, false);

#if FSL_FEATURE_CRC_HAS_CRC_REG
    CRC_WR_CRC(base, seedAndData);
#else
    CRC_WR_DATA(base, seedAndData);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CRC_HAL_GetCrc32
 * Description   : This method appends 32-bit data to current CRC calculation
 *                 and returns new result
 *
 *END**************************************************************************/
uint32_t CRC_HAL_GetCrc32(CRC_Type * base, uint32_t data, bool newSeed, uint32_t seed)
{
    if (newSeed == true)
    {
        CRC_HAL_SetSeedOrDataMode(base, true);
        CRC_HAL_SetDataReg(base, seed);
        CRC_HAL_SetSeedOrDataMode(base, false);
        CRC_HAL_SetDataReg(base, data);
        return CRC_HAL_GetCrcResult(base);
    }
    else
    {
        CRC_HAL_SetDataReg(base, data);
        return CRC_HAL_GetCrcResult(base);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CRC_HAL_GetCrc16
 * Description   : This method appends 16-bit data to current CRC calculation
 *                 and returns new result
 *
 *END**************************************************************************/
uint32_t CRC_HAL_GetCrc16(CRC_Type * base, uint16_t data, bool newSeed, uint32_t seed)
{
    if (newSeed == true)
    {
        CRC_HAL_SetSeedOrDataMode(base, true);
        CRC_HAL_SetDataReg(base, seed);
        CRC_HAL_SetSeedOrDataMode(base, false);
        CRC_HAL_SetDataLReg(base, data);
        return CRC_HAL_GetCrcResult(base);
    }
    else
    {
        CRC_HAL_SetDataLReg(base, data);
        return CRC_HAL_GetCrcResult(base);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CRC_HAL_GetCrc8
 * Description   : This method appends 8-bit data to current CRC calculation
 *                 and returns new result
 *
 *END**************************************************************************/
uint32_t CRC_HAL_GetCrc8(CRC_Type * base, uint8_t data, bool newSeed, uint32_t seed)
{
    if (newSeed == true)
    {
        CRC_HAL_SetSeedOrDataMode(base, true);
        CRC_HAL_SetDataReg(base, seed);
        CRC_HAL_SetSeedOrDataMode(base, false);
        CRC_HAL_SetDataLLReg(base, data);
        return CRC_HAL_GetCrcResult(base);
    }
    else
    {
        CRC_HAL_SetDataLLReg(base, data);
        return CRC_HAL_GetCrcResult(base);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CRC_HAL_GetCrcResult
 * Description   : This method returns current result of CRC calculation
 *
 *END**************************************************************************/
uint32_t CRC_HAL_GetCrcResult(CRC_Type * base)
{
    uint32_t result = 0;
    crc_transpose_t transpose;
    crc_prot_width_t width;

    width = CRC_HAL_GetProtocolWidth(base);

    switch(width)
    {
    case kCrc16Bits:
        transpose = CRC_HAL_GetReadTranspose(base);

        if( (transpose == kCrcTransposeBoth) || (transpose == kCrcTransposeBytes) )
        {
            /* Return upper 16bits of CRC because of transposition in 16bit mode */
            result = CRC_HAL_GetDataHReg(base);
        }
        else
        {
            result = CRC_HAL_GetDataLReg(base);
        }
        break;
    case kCrc32Bits:
        result = CRC_HAL_GetDataReg(base);
        break;
    default:
        break;
    }
    return result;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/



