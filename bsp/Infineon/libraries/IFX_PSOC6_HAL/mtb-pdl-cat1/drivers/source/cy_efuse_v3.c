/***************************************************************************//**
* \file cy_efuse_v3.c
* \version 2.20
*
* \brief
* Provides API implementation of the eFuse version_3 driver.
*
********************************************************************************
* \copyright
* Copyright 2017-2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"

#if defined (CY_IP_MXEFUSE) && (CY_IP_MXEFUSE_VERSION >= 3)

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "cy_efuse.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/
/** \cond INTERNAL */
#define EFUSE_MACRO_NUM             (EFUSE_EFUSE_NR)
#define EFUSE_MACRO_SIZE            (32UL)
#define EFUSE_SIZE                  (EFUSE_MACRO_SIZE * EFUSE_MACRO_NUM)
#define CY_EFUSE_WRITE_TIMEOUT_US   (10UL)
/** \endcond */

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/


/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/


/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/**
 *****************************************************************************
 ** Cy_EFUSE_Enable
 ** Enables the EFUSE block.
 *****************************************************************************/
void Cy_EFUSE_Enable(EFUSE_Type *base)
{
    EFUSE_CTL(base) = EFUSE_CTL_ENABLED_Msk;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_Disable
 ** Disables the EFUSE block. All non-retention registers (command and status
 ** registers) are reset to their default values when the IP is disabled.
 *****************************************************************************/
void Cy_EFUSE_Disable(EFUSE_Type *base)
{
    EFUSE_CTL(base) = 0UL;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_IsEnabled
 ** Checks if EFUSE block is enabled or not.
 *****************************************************************************/
bool Cy_EFUSE_IsEnabled(EFUSE_Type *base)
{
    return (0U != _FLD2VAL(EFUSE_CTL_ENABLED, EFUSE_CTL(base)));
}


/**
 *****************************************************************************
 ** Cy_EFUSE_Init
 ** This function enables the EFUSE block and initializes the registers with
 ** the default values.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_Init(EFUSE_Type *base)
{
    /* Input parameter verification */
    if (NULL == base)
    {
        return CY_EFUSE_BAD_PARAM;
    }
    Cy_EFUSE_Disable(base);
    Cy_EFUSE_Enable(base);

    return CY_EFUSE_SUCCESS;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_DeInit
 ** Disables the EFUSE block. All non-retention registers (command and status
 ** registers) are reset to their default values when the IP is disabled.
 *****************************************************************************/
void Cy_EFUSE_DeInit(EFUSE_Type *base)
{
    Cy_EFUSE_Disable(base);
}

/**
 *****************************************************************************
 ** Cy_EFUSE_WriteBit
 ** Writes a bit to EFUSE by blowing a fuse, so this function is able to write
 ** 1s only. Before write operations you must call \ref Cy_EFUSE_Init().
 ** It is recommended to disable the block when not using it.
 ** Call \ref Cy_EFUSE_Disable() to disable the EFUSE block.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteBit(EFUSE_Type *base, uint32_t bitPos, uint32_t offset)
{
    if((offset > EFUSE_SIZE) || (bitPos > CY_EFUSE_BITS_PER_BYTE))
    {
        return CY_EFUSE_BAD_PARAM;
    }

    cy_en_efuse_status_t ret = CY_EFUSE_WRITE_BUSY;
    uint32_t timeout = CY_EFUSE_WRITE_TIMEOUT_US;

    /* Check whether EFUSE is busy or not. If the sequencer is busy, wait for a 10us */
    while ((0UL != (EFUSE_CMD(base) & EFUSE_CMD_START_Msk)) && (0UL < timeout))
    {
        Cy_SysLib_DelayUs(1U);
        --timeout;
    }

    if (0UL == (EFUSE_CMD(base) & EFUSE_CMD_START_Msk))
    {
        uint8_t readByte;
        /* NOTE: This only supports 4 EFUSE macros */
        uint32_t byteAddr  = offset / EFUSE_MACRO_NUM;
        uint32_t macroAddr = offset % EFUSE_MACRO_NUM;
        EFUSE_CMD(base) = _VAL2FLD(EFUSE_CMD_BIT_DATA, 1UL)         | /* Bit data must be 1 to blow fuse */
                          _VAL2FLD(EFUSE_CMD_BIT_ADDR, bitPos)      | /* Bit position within byte */
                          _VAL2FLD(EFUSE_CMD_BYTE_ADDR, byteAddr)   | /* Byte address within EFUSE macro */
                          _VAL2FLD(EFUSE_CMD_MACRO_ADDR, macroAddr) | /* EFUSE macro number */
                          EFUSE_CMD_START_Msk;

        /* Wait for program access to complete */
        timeout = CY_EFUSE_WRITE_TIMEOUT_US;
        while ((0UL != (EFUSE_CMD(base) & EFUSE_CMD_START_Msk)) && (0UL < timeout))
        {
            Cy_SysLib_DelayUs(1U);
            --timeout;
        }

        if(0UL == timeout)
        {
            /* The program access is not completed */
            return CY_EFUSE_WRITE_TIMEOUT_ERROR;
        }

        /* This delay is required by the IP to operate at 48MHz(clk_sys) as suggested in the CDT:363011
           The delay value will later be updated based on the design team recommendation. */
        Cy_SysLib_DelayUs(100U);

        /* Check whether the program operation succeeded */
        (void)Cy_EFUSE_ReadByte(base, &readByte, offset);
        ret = (0UL != (readByte & (1UL << bitPos))) ? CY_EFUSE_SUCCESS : CY_EFUSE_WRITE_ERROR;
    }

    return ret;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_WriteByte
 ** Writes one byte.
 ** Before write operations you must call \ref Cy_EFUSE_Init().
 ** It is recommended to disable the block when not using it.
 ** Call \ref Cy_EFUSE_Disable() to disable the EFUSE block.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteByte(EFUSE_Type *base, uint32_t src, uint32_t offset)
{
    cy_en_efuse_status_t ret = CY_EFUSE_BAD_PARAM;

    if ((offset < EFUSE_SIZE) && (src <= 0xFFUL))
    {
        uint32_t bitPos = 0UL;
        /* Clear the src bits that are already set */
        uint8_t readByte;
        /* No error check since the function parameters are already checked */
        (void)Cy_EFUSE_ReadByte(base, &readByte, offset);
        src &= (~((uint32_t)readByte));

        ret = CY_EFUSE_SUCCESS;
        while ((0U != src) && (CY_EFUSE_SUCCESS == ret))
        {
            if (0UL != (src & 0x01UL))
            {
                ret = Cy_EFUSE_WriteBit(base, bitPos, offset);
            }
            src >>= 1UL;
            ++bitPos;
        }
    }
    return ret;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_WriteWord
 ** Writes every bit set in src that was not already programmed.
 ** Before write operations you must call \ref Cy_EFUSE_Init().
 ** It is recommended to disable the block when not using it.
 ** Call \ref Cy_EFUSE_Disable() to disable the EFUSE block.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteWord(EFUSE_Type *base, uint32_t src, uint32_t offset)
{
    cy_en_efuse_status_t ret = CY_EFUSE_BAD_PARAM;

    if (offset < EFUSE_SIZE)
    {
        /* Clear the src bits that are already set */
        uint32_t readWord;
        /* No error check since the function parameters are already checked */
        (void)Cy_EFUSE_ReadWord(base, &readWord, offset);
        src &= (uint32_t)~readWord;

        /* Perform a sequence of byte writes to write a word */
        ret = CY_EFUSE_SUCCESS;
        while ((0U != src) && (CY_EFUSE_SUCCESS == ret))
        {
            uint32_t val = src & 0xFFUL;
            if (0UL != val)
            {
                ret = Cy_EFUSE_WriteByte(base, val, offset);
            }
            src >>= 8UL;
            ++offset;
        }
    }
    return ret;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_WriteWordArray
 ** Writes the values of num 32-bit words from the location pointed to by src
 ** to the EFUSE location pointed to by offset.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteWordArray(EFUSE_Type *base, const uint32_t *src, uint32_t offset, uint32_t num)
{
    cy_en_efuse_status_t ret = CY_EFUSE_BAD_PARAM;

    if ((offset < EFUSE_SIZE) && ((EFUSE_SIZE - offset) >= (num * sizeof(uint32_t))))
    {
        ret = CY_EFUSE_SUCCESS;
        for(; 0UL != num; --num)
        {
            if (0UL != *src)
            {
                ret = Cy_EFUSE_WriteWord(base, *src, offset);
            }
            if(CY_EFUSE_SUCCESS != ret)
            {
                return ret;
            }
            ++src;
            offset += 4UL; /* One 4-byte word is written at a time */
        }
    }
    return ret;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_ReadBit
 ** Reads a bit from EFUSE.
 ** Before read operations you must call \ref Cy_EFUSE_Init().
 ** It is recommended to disable the block when not using it.
 ** Call \ref Cy_EFUSE_Disable() to disable the EFUSE block.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadBit(EFUSE_Type *base, uint8_t *dst, uint32_t bitPos, uint32_t offset)
{
    cy_en_efuse_status_t ret = CY_EFUSE_BAD_PARAM;
    if ((offset < EFUSE_SIZE) && (bitPos < CY_EFUSE_BITS_PER_BYTE))
    {
        uint8_t byte;

        /* No error check since the function parameters are already checked */
        (void) Cy_EFUSE_ReadByte(base, &byte, offset);

        /* Extract the bit using the bit position value */
        *dst = (byte >> bitPos) & 0x01U;
        ret = CY_EFUSE_SUCCESS;
    }
    return ret;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_ReadByte
 ** Reads byte from EFUSE.
 ** Before read operations you must call \ref Cy_EFUSE_Init().
 ** It is recommended to disable the block when not using it.
 ** Call \ref Cy_EFUSE_Disable() to disable the EFUSE block.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadByte(EFUSE_Type *base, uint8_t *dst, uint32_t offset)
{
    cy_en_efuse_status_t ret = CY_EFUSE_BAD_PARAM;
    if (offset < EFUSE_SIZE)
    {
        uint32_t word = 0UL;

        /* Byte number within a 4-byte word */
        uint32_t byteNum = offset & 3UL;

        /* Offset must be 4-byte aligned for addressing MMIO space */
        offset &= ~3UL;

        /* No error check since the function parameters are already checked */
        (void) Cy_EFUSE_ReadWord(base, &word, offset);

        /* Extract the byte using the byte number */
        *dst = (uint8_t)(word >> (byteNum * 8UL));
        ret = CY_EFUSE_SUCCESS;
    }
    return ret;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_ReadWord
 ** Reads a 32-bit word from EFUSE.
 ** Before read operations you must call \ref Cy_EFUSE_Init().
 ** It is recommended to disable the block when not using it.
 ** Call \ref Cy_EFUSE_Disable() to disable the EFUSE block.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadWord(EFUSE_Type *base, uint32_t *dst, uint32_t offset)
{
    /* Suppress a compiler warning about unused variables */
    (void) base;

    cy_en_efuse_status_t ret = CY_EFUSE_BAD_PARAM;
    if (offset < EFUSE_SIZE)
    {
        *dst = CY_GET_REG32(CY_EFUSE_BASE + offset);
        ret = CY_EFUSE_SUCCESS;
    }
    return ret;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_ReadWordArray
 ** Reads an array of 32-bit words from EFUSE.
 ** Before read operations you must call \ref Cy_EFUSE_Init().
 ** It is recommended to disable the block when not using it.
 ** Call \ref Cy_EFUSE_Disable() to disable the EFUSE block.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadWordArray(EFUSE_Type *base, uint32_t *dst, uint32_t offset, uint32_t num)
{
    /* Suppress a compiler warning about unused variables */
    (void) base;

    cy_en_efuse_status_t ret = CY_EFUSE_BAD_PARAM;

    if ((offset < EFUSE_SIZE) && ((EFUSE_SIZE - offset) >= (num * sizeof(uint32_t))))
    {
        for (; num != 0UL; --num)
        {
            *dst = CY_GET_REG32(CY_EFUSE_BASE + offset);
            ++dst;
            offset += 4UL; /* One 4-byte word is read at a time */
        }
        ret = CY_EFUSE_SUCCESS;
    }
    return ret;
}

/**
 *****************************************************************************
 ** Cy_EFUSE_WriteBootRow
 ** Writes data into BOsOTROW.
 ** Before write operations you must call \ref Cy_EFUSE_Init().
 ** It is recommended to disable the block when not using it.
 ** Call \ref Cy_EFUSE_Disable() to disable the EFUSE block.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteBootRow(EFUSE_Type *base, uint32_t bootrow)
{
    /* Boot row is stored at address 0 of EFUSE macros 3-0 */
    return Cy_EFUSE_WriteWord(base, bootrow, 0UL);
}

/**
 *****************************************************************************
 ** Cy_EFUSE_ReadBootRow
 ** Reads data from BOOTROW.
 ** The BOOTROW information is latched upon system reset and is readable as
 ** MMIO register.
 *****************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadBootRow(EFUSE_Type *base, uint32_t *bootrow)
{
    *bootrow = EFUSE_BOOTROW(base);
    return CY_EFUSE_SUCCESS;
}


#endif /* #ifdef (CY_IP_MXEFUSE) && (CY_IP_MXEFUSE_VERSION >= 3) */

/* [] END OF FILE */
