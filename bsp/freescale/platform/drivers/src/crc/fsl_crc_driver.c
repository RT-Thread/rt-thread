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

#include "fsl_crc_driver.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_CRC_COUNT

/*FUNCTION*********************************************************************
 *
 * Function Name : CRC_DRV_Init
 * Description   : Initialize the CRC module. This API with initial configuration
 * should be called before any other operations to the CRC module.
 *
 *END*************************************************************************/
crc_status_t CRC_DRV_Init(uint32_t instance, const crc_user_config_t *userConfigPtr)
{
    if (!userConfigPtr)
    {
        return kStatus_CRC_InvalidArgument;
    }
    /* Enable clock for CRC. */
    if (!CLOCK_SYS_GetCrcGateCmd(instance))
    {
        CLOCK_SYS_EnableCrcClock(instance);
    }

    return CRC_DRV_Configure(instance, userConfigPtr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CRC_DRV_Deinit
 * Description   : Shutdown a CRC instance.
 *
 *END**************************************************************************/
void CRC_DRV_Deinit(uint32_t instance)
{
    /* Gate the clock for CRC.*/
    CLOCK_SYS_DisableCrcClock(instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CRC_DRV_GetCrcBlock
 * Description   : This method appends block of bytes to current CRC calculation
 *                 and returns new result
 *
 *END**************************************************************************/
uint32_t CRC_DRV_GetCrcBlock(uint32_t instance, uint8_t *data, uint32_t dataLen)
{
    crc_transpose_t oldInputTranspose;
    uint32_t *data32;
    uint8_t *data8;
    uint32_t result;

    assert(data != NULL);
    assert(dataLen != 0);

    /* flip bytes because of little endian architecture */
    oldInputTranspose = CRC_HAL_GetWriteTranspose(g_crcBase[instance]);

    switch (oldInputTranspose) {
        case kCrcNoTranspose:
             CRC_HAL_SetWriteTranspose(g_crcBase[instance], kCrcTransposeBytes);
             break;
        case kCrcTransposeBits:
             CRC_HAL_SetWriteTranspose(g_crcBase[instance], kCrcTransposeBoth);
             break;
        case kCrcTransposeBoth:
             CRC_HAL_SetWriteTranspose(g_crcBase[instance], kCrcTransposeBits);
             break;
        case kCrcTransposeBytes:
             CRC_HAL_SetWriteTranspose(g_crcBase[instance], kCrcNoTranspose);
             break;
        default:
             break;
    }

    /* Start the checksum calculation */
    /* If address is not word-aligned, then read initial bytes in 8bit mode till word-aligned */
    while (((uint32_t)data & 3U) && (dataLen > 0))
    {
        CRC_HAL_SetDataLLReg(g_crcBase[instance], *(data++));
        dataLen--;
    }

    data32 = (uint32_t *)data;
    while (dataLen >= sizeof(uint32_t))
    {
        CRC_HAL_SetDataReg(g_crcBase[instance], *(data32++)); /* 32bit access */
        dataLen -= sizeof(uint32_t);
    }

    data8 = (uint8_t *)data32;

    switch(dataLen)
    {
        case 3U:
            CRC_HAL_SetDataLReg(g_crcBase[instance], *(uint16_t *)data8);   /* 16 bit */
            CRC_HAL_SetDataLLReg(g_crcBase[instance], *(data8 + 2U));         /* 8 bit */
            break;
        case 2U:
            CRC_HAL_SetDataLReg(g_crcBase[instance], *(uint16_t *)data8);   /* 16 bit */
            break;
        case 1U:
            CRC_HAL_SetDataLLReg(g_crcBase[instance], *data8);         /* 8 bit */
            break;
        default:
            break;
    }

    result = CRC_HAL_GetCrcResult(g_crcBase[instance]);
    CRC_HAL_SetWriteTranspose(g_crcBase[instance], oldInputTranspose);

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CRC_DRV_Configure
 * Description   : Configure CRC module from a user configuration.
 *
 *END**************************************************************************/
crc_status_t CRC_DRV_Configure(uint32_t instance, const crc_user_config_t *userConfigPtr)
{
    if((!userConfigPtr))
    {
        return kStatus_CRC_InvalidArgument;
    }

    /* 1. set 16 or 32-bit crc width */
    CRC_HAL_SetProtocolWidth(g_crcBase[instance], userConfigPtr->crcWidth);

    /* 2. set transpose and complement options */
    CRC_HAL_SetWriteTranspose(g_crcBase[instance], userConfigPtr->writeTranspose);
    CRC_HAL_SetReadTranspose(g_crcBase[instance], userConfigPtr->readTranspose);
    CRC_HAL_SetXorMode(g_crcBase[instance], userConfigPtr->complementRead);

    /* 3. Write polynomial */
    CRC_HAL_SetPolyReg(g_crcBase[instance], userConfigPtr->polynomial);

    /* 4. Set seed value */
    CRC_HAL_SetSeedOrDataMode(g_crcBase[instance], true);
    CRC_HAL_SetDataReg(g_crcBase[instance], userConfigPtr->seed);
    CRC_HAL_SetSeedOrDataMode(g_crcBase[instance], false);

    return kStatus_CRC_Success;
}
#endif

/******************************************************************************
 * EOF
 *****************************************************************************/
