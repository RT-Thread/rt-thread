/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_crc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_crc.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup CRC
 * @brief CRC driver modules
 * @{
 */

/** @addtogroup CRC_Private_TypesDefinitions
 * @{
 */

/**
 * @}
 */

/** @addtogroup CRC_Private_Defines
 * @{
 */

/**
 * @}
 */

/** @addtogroup CRC_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup CRC_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup CRC_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup CRC_Private_Functions
 * @{
 */

/**
 * @brief  Resets the CRC Data register (DAT).
 */
void CRC32_ResetCrc(void)
{
    /* Reset CRC generator */
    CRC->CRC32CTRL = CRC32_CTRL_RESET;
}

/**
 * @brief  Computes the 32-bit CRC of a given data word(32-bit).
 * @param Data data word(32-bit) to compute its CRC
 * @return 32-bit CRC
 */
uint32_t CRC32_CalcCrc(uint32_t Data)
{
    CRC->CRC32DAT = Data;

    return (CRC->CRC32DAT);
}

/**
 * @brief  Computes the 32-bit CRC of a given buffer of data word(32-bit).
 * @param pBuffer pointer to the buffer containing the data to be computed
 * @param BufferLength length of the buffer to be computed
 * @return 32-bit CRC
 */
uint32_t CRC32_CalcBufCrc(uint32_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index = 0;

    for (index = 0; index < BufferLength; index++)
    {
        CRC->CRC32DAT = pBuffer[index];
    }
    return (CRC->CRC32DAT);
}

/**
 * @brief  Returns the current CRC value.
 * @return 32-bit CRC
 */
uint32_t CRC32_GetCrc(void)
{
    return (CRC->CRC32DAT);
}

/**
 * @brief  Stores a 8-bit data in the Independent Data(ID) register.
 * @param IDValue 8-bit value to be stored in the ID register
 */
void CRC32_SetIDat(uint8_t IDValue)
{
    CRC->CRC32IDAT = IDValue;
}

/**
 * @brief  Returns the 8-bit data stored in the Independent Data(ID) register
 * @return 8-bit value of the ID register
 */
uint8_t CRC32_GetIDat(void)
{
    return (CRC->CRC32IDAT);
}

// CRC16 add
void __CRC16_SetLittleEndianFmt(void)
{
    CRC->CRC16CTRL = CRC16_CTRL_LITTLE | CRC->CRC16CTRL;
}
void __CRC16_SetBigEndianFmt(void)
{
    CRC->CRC16CTRL = CRC16_CTRL_BIG & CRC->CRC16CTRL;
}
void __CRC16_SetCleanEnable(void)
{
    CRC->CRC16CTRL = CRC16_CTRL_RESET | CRC->CRC16CTRL;
}
void __CRC16_SetCleanDisable(void)
{
    CRC->CRC16CTRL = CRC16_CTRL_NO_RESET & CRC->CRC16CTRL;
}

uint16_t __CRC16_CalcCrc(uint8_t Data)
{
    CRC->CRC16DAT = Data;
    return (CRC->CRC16D);
}

void __CRC16_SetCrc(uint8_t Data)
{
    CRC->CRC16DAT = Data;
}

uint16_t __CRC16_GetCrc(void)
{
    return (CRC->CRC16D);
}

void __CRC16_SetLRC(uint8_t Data)
{
    CRC->LRC = Data;
}

uint8_t __CRC16_GetLRC(void)
{
    return (CRC->LRC);
}

uint16_t CRC16_CalcBufCrc(uint8_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index = 0;

    CRC->CRC16D = 0x00;
    // CRC16_SetCleanEnable();
    for (index = 0; index < BufferLength; index++)
    {
        CRC->CRC16DAT = pBuffer[index];
    }
    return (CRC->CRC16D);
}

uint16_t CRC16_CalcCRC(uint8_t Data)
{
    CRC->CRC16DAT = Data;

    return (CRC->CRC16D);
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
