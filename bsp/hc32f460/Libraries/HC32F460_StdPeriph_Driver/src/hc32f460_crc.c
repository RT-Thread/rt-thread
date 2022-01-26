/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_crc.c
 **
 ** A detailed description is available at
 ** @link CrcGroup Crc description @endlink
 **
 **   - 2019-03-07  CDT First version for Device Driver Library of Crc.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_crc.h"
#include "hc32f460_utility.h"

#if (DDL_CRC_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup CrcGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Definition of CRC16 data register. */
#define M4_CRC16_DAT        (*((__IO uint16_t *)&M4_CRC->DAT0))

/* Definition of CRC16 checksum register. */
#define M4_CRC16_RSLT       (*((__IO uint16_t *)&M4_CRC->RESLT))

/* Definition of CRC16 initial value register. */
#define M4_CRC16_INIT       (M4_CRC16_RSLT)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static uint32_t CRC_ProcChecksum(uint32_t u32Checksum);
static uint32_t CRC_ReverseBits(uint32_t u32Data);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  Initialize the CRC.
 **
 ** \param  [in] u32Config          Bit[1]: CRC_SEL_16B or CRC_SEL_32B.
 **                                 Bit[2]: CRC_REFIN_DISABLE or CRC_REFIN_ENABLE.
 **                                 Bit[3]: CRC_REFOUT_DISABLE or CRC_REFOUT_ENABLE.
 **                                 Bit[4]: CRC_XOROUT_DISABLE or CRC_XOROUT_ENABLE.
 **                                 See the definitions for details.
 **
 ** \retval None
 **
 ******************************************************************************/
void CRC_Init(uint32_t u32Config)
{
    u32Config &= CRC_CONFIG_MASK;

    M4_CRC->CR = u32Config;
}

/**
 *******************************************************************************
 ** \brief  CRC16 calculation.
 **
 ** \param  [in] u16InitVal         Initial value of CRC16.
 **
 ** \param  [in] pu16Data           Pointer to the buffer containing the data to be computed.
 **
 ** \param  [in] u32Length          Length of the buffer to be computed.
 **
 ** \retval 16-bit CRC checksum.
 **
 ******************************************************************************/
uint16_t CRC_Calculate16B(uint16_t u16InitVal, const uint16_t *pu16Data, uint32_t u32Length)
{
    uint16_t u16Ret = 0u;
    uint32_t u32Count;

    if (NULL != pu16Data)
    {
        M4_CRC16_INIT = u16InitVal;

        for (u32Count = 0u; u32Count < u32Length; u32Count++)
        {
            M4_CRC16_DAT = pu16Data[u32Count];
        }

        u16Ret = M4_CRC16_RSLT;
    }

    return u16Ret;
}

/**
 *******************************************************************************
 ** \brief  CRC32 calculation.
 **
 ** \param  [in] u32InitVal         Initial value of CRC32.
 **
 ** \param  [in] pu32Data           Pointer to the buffer containing the data to be computed.
 **
 ** \param  [in] u32Length          Length of the buffer to be computed.
 **
 ** \retval 32-bit CRC checksum.
 **
 ******************************************************************************/
uint32_t CRC_Calculate32B(uint32_t u32InitVal, const uint32_t *pu32Data, uint32_t u32Length)
{
    uint32_t u32Ret = 0u;
    uint32_t u32Count;

    M4_CRC->RESLT = u32InitVal;

    if (NULL != pu32Data)
    {
        for (u32Count = 0u; u32Count < u32Length; u32Count++)
        {
            M4_CRC->DAT0 = pu32Data[u32Count];
        }

        u32Ret = M4_CRC->RESLT;
    }

    return u32Ret;
}

/**
 *******************************************************************************
 ** \brief  CRC16 check.
 **
 ** \param  [in] u16InitVal         Initial value of CRC16.
 **
 ** \param  [in] u16Checksum        CRC16 checksum of the source data.
 **
 ** \param  [in] pu16Data           Pointer to the buffer containing the data to be checked.
 **
 ** \param  [in] u32Length          Length of the buffer to be checked.
 **
 ** \retval true                    CRC16 checks successfully.
 ** \retval false                   CRC16 checks unsuccessfully.
 **
 ******************************************************************************/
bool CRC_Check16B(uint16_t u16InitVal, uint16_t u16Checksum, const uint16_t *pu16Data, uint32_t u32Length)
{
    bool bRet = false;
    uint32_t u32Count;
    uint16_t u16CrcChecksum;

    if (NULL != pu16Data)
    {
        u16CrcChecksum = (uint16_t)CRC_ProcChecksum((uint32_t)u16Checksum);
        M4_CRC16_INIT  = u16InitVal;

        for (u32Count = 0u; u32Count < u32Length; u32Count++)
        {
            M4_CRC16_DAT = pu16Data[u32Count];
        }

        M4_CRC16_DAT = u16CrcChecksum;

        if (bM4_CRC_FLG_FLAG)
        {
            bRet = true;
        }
    }

    return bRet;
}

/**
 *******************************************************************************
 ** \brief  CRC32 check.
 **
 ** \param  [in] u32InitVal         Initial value of CRC32.
 **
 ** \param  [in] u32Checksum        CRC32 checksum of the source data.
 **
 ** \param  [in] pu32Data           Pointer to the buffer containing the data to be checked.
 **
 ** \param  [in] u32Length          Length of the buffer to be checked.
 **
 ** \retval true                    CRC32 checks successfully.
 ** \retval false                   CRC32 checks unsuccessfully.
 **
 ******************************************************************************/
bool CRC_Check32B(uint32_t u32InitVal, uint32_t u32Checksum, const uint32_t *pu32Data, uint32_t u32Length)
{
    bool bRet = false;
    uint32_t u32Count;
    uint32_t u32CrcChecksum;

    if (NULL != pu32Data)
    {
        u32CrcChecksum = CRC_ProcChecksum(u32Checksum);
        M4_CRC->RESLT = u32InitVal;

        for (u32Count = 0u; u32Count < u32Length; u32Count++)
        {
            M4_CRC->DAT0 = pu32Data[u32Count];
        }

        M4_CRC->DAT0 = u32CrcChecksum;

        if (bM4_CRC_FLG_FLAG)
        {
            bRet = true;
        }
    }

    return bRet;
}

/*******************************************************************************
 * Function implementation - local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  Processes the checksum of CRC.
 **
 ** \param  [in] u32Checksum            The checksum of CRC16 or CRC32.
 **
 ** \retval 32-bit new checksum will be used by CRC checking.
 **
 ******************************************************************************/
static uint32_t CRC_ProcChecksum(uint32_t u32Checksum)
{
    uint8_t i;
    uint8_t u8Size = 16u;
    uint8_t u8Offset;
    uint32_t u32Config;
    uint32_t u32FinalChecksum;
    uint32_t u32Temp;

    u32Config = M4_CRC->CR;
    u32FinalChecksum = u32Checksum;

    if ((u32Config & CRC_SEL_32B) == CRC_SEL_32B)
    {
        u8Size = 32u;
    }

    if ((u32Config & CRC_REFOUT_ENABLE) == CRC_REFOUT_DISABLE)
    {
        /* Bits reversing. */
        u32FinalChecksum = CRC_ReverseBits(u32Checksum);
        if (u8Size == 16u)
        {
            u32FinalChecksum >>= 16u;
            u32FinalChecksum &= 0xFFFFu;
        }
    }

    if ((u32Config & CRC_XOROUT_ENABLE) == CRC_XOROUT_DISABLE)
    {
        /* Bits NOT. */
        u32FinalChecksum = ~u32FinalChecksum;
    }

    if ((u32Config & CRC_REFIN_ENABLE) == CRC_REFIN_DISABLE)
    {
        u8Size /= 8u;
        /* Bits reversing in bytes. */
        for (i = 0u; i < u8Size; i++)
        {
            u8Offset = i * 8u;
            u32Temp  = (u32FinalChecksum >> u8Offset) & 0xFFul;
            u32Temp  = CRC_ReverseBits(u32Temp);
            u32Temp  = u32Temp >> (24u - u8Offset);
            u32FinalChecksum &= ~((uint32_t)0xFF << u8Offset);
            u32FinalChecksum |= u32Temp;
        }
    }

    return u32FinalChecksum;
}

/**
 *******************************************************************************
 ** \brief  Reverse bits.
 **
 ** \param  [in] u32Data                The data to be reversed bits.
 **
 ** \retval 32-bit new data.
 **
 ******************************************************************************/
static uint32_t CRC_ReverseBits(uint32_t u32Data)
{
    u32Data = (((u32Data & 0xAAAAAAAAul) >> 1u) | ((u32Data & 0x55555555ul) << 1u));
    u32Data = (((u32Data & 0xCCCCCCCCul) >> 2u) | ((u32Data & 0x33333333ul) << 2u));
    u32Data = (((u32Data & 0xF0F0F0F0ul) >> 4u) | ((u32Data & 0x0F0F0F0Ful) << 4u));
    u32Data = (((u32Data & 0xFF00FF00ul) >> 8u) | ((u32Data & 0x00FF00FFul) << 8u));

    return ((u32Data >> 16u) | (u32Data << 16u));
}

//@} // CrcGroup

#endif /* DDL_CRC_ENABLE */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
