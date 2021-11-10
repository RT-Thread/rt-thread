/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_hash.c
 **
 ** A detailed description is available at
 ** @link HashGroup HASH description @endlink
 **
 **   - 2018-10-18  CDT First version for Device Driver Library of HASH.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_hash.h"
#include "hc32f460_utility.h"

#if (DDL_HASH_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup HashGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* Constants definitions. */
#define HASH_GROUP_LEN                      (64u)
#define LAST_GROUP_MAX_LEN                  (56u)

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
static void HASH_WriteData(const uint8_t *pu8SrcData);
static void HASH_GetMsgDigest(uint8_t *pu8MsgDigest);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  Initialize the HASH.
 **
 ** \param  None
 **
 ** \retval None
 **
 ******************************************************************************/
void HASH_Init(void)
{
    /* Stop hash calculating */
    bM4_HASH_CR_START = 0u;
}

/**
 *******************************************************************************
 ** \brief  DeInitialize the HASH.
 **
 ** \param  None
 **
 ** \retval None
 **
 ******************************************************************************/
void HASH_DeInit(void)
{
    /* Stop hash calculating */
    bM4_HASH_CR_START = 0u;

    /* Reset register CR. */
    M4_HASH->CR = 0u;
}

/**
 *******************************************************************************
 ** \brief  HASH(SHA256) processes pu8SrcData.
 **
 ** \param  [in] pu8SrcData             Pointer to the source data buffer (buffer to
 **                                     be hashed).
 **
 ** \param  [in] u32SrcDataSize         Length of the input buffer in bytes.
 **
 ** \param  [out] pu8MsgDigest          Pointer to the computed digest. Its size
 **                                     must be 32 bytes.
 **
 ** \param  [in] u32Timeout             Timeout value.
 **
 ** \retval Ok                          No error occurred.
 ** \retval ErrorTimeout                HASH works timeout.
 ** \retval ErrorInvalidParameter       Parameter error.
 **
 ******************************************************************************/
en_result_t HASH_Start(const uint8_t *pu8SrcData,
                       uint32_t u32SrcDataSize,
                       uint8_t *pu8MsgDigest,
                       uint32_t u32Timeout)
{
    en_result_t   enRet = ErrorInvalidParameter;
    uint8_t       u8FillBuffer[HASH_GROUP_LEN];
    uint8_t       u8FirstGroup  = 0u;
    uint8_t       u8HashEnd     = 0u;
    uint8_t       u8DataEndMark = 0u;
    uint32_t      u32Index      = 0u;
    uint32_t      u32BitLenHi;
    uint32_t      u32BitLenLo;
    uint32_t      u32HashTimeout;
    __IO uint32_t u32TimeCount;

    if ((NULL != pu8SrcData)    &&
        (0u != u32SrcDataSize)  &&
        (NULL != pu8MsgDigest)  &&
        (0u != u32Timeout))
    {
        /* 10 is the number of required instructions cycles for the below loop statement. */
        u32HashTimeout = u32Timeout * (SystemCoreClock / 10u / 1000u);
        u32BitLenHi    = (u32SrcDataSize >> 29u) & 0x7u;
        u32BitLenLo    = (u32SrcDataSize << 3u);

        while (1u)
        {
            /* Stop hash calculating. */
            bM4_HASH_CR_START = 0u;

            if (u32SrcDataSize >= HASH_GROUP_LEN)
            {
                HASH_WriteData(&pu8SrcData[u32Index]);
                u32SrcDataSize -= HASH_GROUP_LEN;
                u32Index += HASH_GROUP_LEN;
            }
            else if (u32SrcDataSize >= LAST_GROUP_MAX_LEN)
            {
                memset(u8FillBuffer, 0, HASH_GROUP_LEN);
                memcpy(u8FillBuffer, &pu8SrcData[u32Index], u32SrcDataSize);
                u8FillBuffer[u32SrcDataSize] = 0x80u;
                u8DataEndMark = 1u;
                HASH_WriteData(u8FillBuffer);
                u32SrcDataSize = 0u;
            }
            else
            {
                u8HashEnd = 1u;
            }

            if (u8HashEnd != 0u)
            {
                memset(u8FillBuffer, 0, HASH_GROUP_LEN);
                if (u32SrcDataSize > 0u)
                {
                    memcpy(u8FillBuffer, &pu8SrcData[u32Index], u32SrcDataSize);
                }
                if (u8DataEndMark == 0u)
                {
                    u8FillBuffer[u32SrcDataSize] = 0x80u;
                }
                u8FillBuffer[63u] = (uint8_t)(u32BitLenLo);
                u8FillBuffer[62u] = (uint8_t)(u32BitLenLo >> 8u);
                u8FillBuffer[61u] = (uint8_t)(u32BitLenLo >> 16u);
                u8FillBuffer[60u] = (uint8_t)(u32BitLenLo >> 24u);
                u8FillBuffer[59u] = (uint8_t)(u32BitLenHi);
                u8FillBuffer[58u] = (uint8_t)(u32BitLenHi >> 8u);
                u8FillBuffer[57u] = (uint8_t)(u32BitLenHi >> 16u);
                u8FillBuffer[56u] = (uint8_t)(u32BitLenHi >> 24u);
                HASH_WriteData(u8FillBuffer);
            }

            /* check if first group */
            if (0u == u8FirstGroup)
            {
                u8FirstGroup = 1u;
                /* Set first group. */
                bM4_HASH_CR_FST_GRP = 1u;
            }
            else
            {
                /* Set continuous group. */
                bM4_HASH_CR_FST_GRP = 0u;
            }

            /* Start hash calculating. */
            bM4_HASH_CR_START = 1u;

            u32TimeCount = 0u;
            enRet = ErrorTimeout;
            while (u32TimeCount < u32HashTimeout)
            {
                if (bM4_HASH_CR_START == 0u)
                {
                    enRet = Ok;
                    break;
                }
                u32TimeCount++;
            }

            if ((ErrorTimeout == enRet) || (u8HashEnd != 0u))
            {
                break;
            }
        }

        if (Ok == enRet)
        {
            /* HASH calculated done */
            HASH_GetMsgDigest(pu8MsgDigest);
        }

        /* Stop hash calculating. */
        bM4_HASH_CR_START = 0u;
    }

    return enRet;
}

/*******************************************************************************
 * Function implementation - local ('static')
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief  Writes the input buffer in data register.
 **
 ** \param  [in] pu8SrcData             Pointer to source data buffer.
 **
 ** \retval None
 **
 ******************************************************************************/
static void HASH_WriteData(const uint8_t *pu8SrcData)
{
    uint8_t       i;
    uint8_t       j;
    uint32_t      u32Temp;
    __IO uint32_t *io32HashDr = &(M4_HASH->DR15);

    for (i = 0u; i < 16u; i++)
    {
        j = i * 4u + 3u;
        u32Temp  = (uint32_t)pu8SrcData[j];
        u32Temp |= ((uint32_t)pu8SrcData[j-1u]) << 8u;
        u32Temp |= ((uint32_t)pu8SrcData[j-2u]) << 16u;
        u32Temp |= ((uint32_t)pu8SrcData[j-3u]) << 24u;

        *io32HashDr = u32Temp;
        io32HashDr++;
    }
}

/**
 *******************************************************************************
 ** \brief  Provides the message digest result.
 **
 ** \param  [out] pu8MsgDigest              Pointer to the message digest.
 **
 ** \retval None
 **
 ******************************************************************************/
static void HASH_GetMsgDigest(uint8_t *pu8MsgDigest)
{
    uint8_t       i;
    uint8_t       j;
    uint32_t      u32Temp;
    __IO uint32_t *io32HashHr = &(M4_HASH->HR7);

    for (i = 0u; i < 8u; i++)
    {
        j = i * 4u + 3u;
        u32Temp = *io32HashHr;

        pu8MsgDigest[j]    = (uint8_t)u32Temp;
        pu8MsgDigest[j-1u] = (uint8_t)(u32Temp >> 8u);
        pu8MsgDigest[j-2u] = (uint8_t)(u32Temp >> 16u);
        pu8MsgDigest[j-3u] = (uint8_t)(u32Temp >> 24u);

        io32HashHr++;
    }
}

//@} // HashGroup

#endif /* DDL_HASH_ENABLE */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
