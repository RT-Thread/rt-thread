/**
 *******************************************************************************
 * @file  hc32_ll_hash.c
 * @brief This file provides firmware functions to manage the HASH
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_hash.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_HASH HASH
 * @brief HASH Driver Library
 * @{
 */

#if (LL_HASH_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup HASH_Local_Macros HASH Local Macros
 * @{
 */

/**
 * @defgroup HASH_Miscellaneous_Macros HASH Miscellaneous Macros
 * @{
 */
#define HASH_GROUP_SIZE                 (64U)
#define HASH_GROUP_SIZE_WORD            (HASH_GROUP_SIZE / 4U)
#define HASH_LAST_GROUP_SIZE_MAX        (56U)
#define HASH_TIMEOUT                    (6000U)
#define HASH_MSG_DIGEST_SIZE_WORD       (8U)

/**
 * @}
 */

/**
 * @defgroup HASH_Action HASH Action
 * @{
 */
#define HASH_ACTION_START               (HASH_CR_START)
/**
 * @}
 */

#define IS_HASH_PWC_UNLOCKED()          ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

/* HASH reset timeout */
#define HASH_RMU_TIMEOUT                (100UL)

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup HASH_Local_Functions HASH Local Functions
 * @{
 */

/**
 * @brief  Writes the input buffer in data register.
 * @param  [in] pu8Data       The buffer for source data
 * @retval None
 */
static void HASH_WriteData(const uint8_t *pu8Data)
{
    uint8_t i;
    __IO uint32_t *regDR = &CM_HASH->DR15;
    const uint32_t *pu32Data = (const uint32_t *)((uint32_t)pu8Data);

    for (i = 0U; i < HASH_GROUP_SIZE_WORD; i++) {
        regDR[i] = __REV(pu32Data[i]);
    }
}

/**
 * @brief  Memory copy.
 * @param  [in] pu8Dest                 Pointer to a destination address.
 * @param  [in] pu8Src                  Pointer to a source address.
 * @param  [in] u32Size                 Data size.
 * @retval None
 */
static void HASH_MemCopy(uint8_t *pu8Dest, const uint8_t *pu8Src, uint32_t u32Size)
{
    uint32_t i = 0UL;
    while (i < u32Size) {
        pu8Dest[i] = pu8Src[i];
        i++;
    }
}

/**
 * @brief  Memory set.
 * @param  [in] pu8Mem                  Pointer to an address.
 * @param  [in] u8Value                 Data value.
 * @param  [in] u32Size                 Data size.
 * @retval None
 */
static void HASH_MemSet(uint8_t *pu8Mem, uint8_t u8Value, uint32_t u32Size)
{
    uint32_t i = 0UL;
    while (i < u32Size) {
        pu8Mem[i] = u8Value;
        i++;
    }
}

/**
 * @brief  Wait for the HASH to stop
 * @param  [in]  u32Action              HASH action. This parameter can be a value of @ref HASH_Action.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred
 *           - LL_ERR_TIMEOUT:          Works timeout
 */
static int32_t HASH_Wait(uint32_t u32Action)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeCount = 0UL;

    /* Wait for the HASH to stop */
    while (READ_REG32_BIT(CM_HASH->CR, u32Action) != 0UL) {
        if (u32TimeCount++ > HASH_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief  HASH Filling data
 * @param  [in] pu8Data                 The source data buffer
 * @param  [in] u32DataSize             Length of the input buffer in bytes
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred
 *           - LL_ERR_TIMEOUT:          Works timeout
 */
static int32_t HASH_DoCalc(const uint8_t *pu8Data, uint32_t u32DataSize)
{
    uint8_t  u8FillBuffer[HASH_GROUP_SIZE];
    uint32_t u32BitLenHigh;
    uint32_t u32BitLenLow;
    uint32_t u32Index      = 0U;
    uint8_t  u8FirstGroup  = 1U;
    uint8_t  u8HashEnd     = 0U;
    uint8_t  u8DataEndMark = 0U;
    int32_t i32Ret;

    u32BitLenHigh = (u32DataSize >> 29U) & 0x7U;
    u32BitLenLow  = (u32DataSize << 3U);

    /* Stop hash calculating. */
    i32Ret = HASH_Wait(HASH_ACTION_START);

    while ((i32Ret == LL_OK) && (u8HashEnd == 0U)) {
        if (u32DataSize >= HASH_GROUP_SIZE) {
            HASH_WriteData(&pu8Data[u32Index]);
            u32DataSize -= HASH_GROUP_SIZE;
            u32Index += HASH_GROUP_SIZE;
        } else if (u32DataSize >= HASH_LAST_GROUP_SIZE_MAX) {
            HASH_MemSet(u8FillBuffer, 0, HASH_GROUP_SIZE);
            HASH_MemCopy(u8FillBuffer, &pu8Data[u32Index], u32DataSize);
            u8FillBuffer[u32DataSize] = 0x80U;
            u8DataEndMark = 1U;
            HASH_WriteData(u8FillBuffer);
            u32DataSize = 0U;
        } else {
            u8HashEnd = 1U;
        }

        if (u8HashEnd != 0U) {
            HASH_MemSet(u8FillBuffer, 0, HASH_GROUP_SIZE);
            if (u32DataSize > 0U) {
                HASH_MemCopy(u8FillBuffer, &pu8Data[u32Index], u32DataSize);
            }
            if (u8DataEndMark == 0U) {
                u8FillBuffer[u32DataSize] = 0x80U;
            }
            u8FillBuffer[63U] = (uint8_t)(u32BitLenLow);
            u8FillBuffer[62U] = (uint8_t)(u32BitLenLow >> 8U);
            u8FillBuffer[61U] = (uint8_t)(u32BitLenLow >> 16U);
            u8FillBuffer[60U] = (uint8_t)(u32BitLenLow >> 24U);
            u8FillBuffer[59U] = (uint8_t)(u32BitLenHigh);
            u8FillBuffer[58U] = (uint8_t)(u32BitLenHigh >> 8U);
            u8FillBuffer[57U] = (uint8_t)(u32BitLenHigh >> 16U);
            u8FillBuffer[56U] = (uint8_t)(u32BitLenHigh >> 24U);
            HASH_WriteData(u8FillBuffer);
        }

        /* First group and last group check */
        /* check if first group */
        if (u8FirstGroup != 0U) {
            u8FirstGroup = 0U;
            /* Set first group. */
            WRITE_REG32(bCM_HASH->CR_b.FST_GRP, 1U);
        } else {
            /* Set continuous group. */
            WRITE_REG32(bCM_HASH->CR_b.FST_GRP, 0U);
        }

        /* Start hash calculating. */
        WRITE_REG32(bCM_HASH->CR_b.START, 1U);
        i32Ret = HASH_Wait(HASH_ACTION_START);
    }
    /* Stop hash calculating. */
    WRITE_REG32(bCM_HASH->CR_b.START, 0U);

    return i32Ret;
}

/**
 * @brief  Read message digest.
 * @param  [out] pu8MsgDigest           Buffer for message digest.
 * @retval None
 */
static void HASH_ReadMsgDigest(uint8_t *pu8MsgDigest)
{
    uint8_t i;
    __IO uint32_t *regHR = &CM_HASH->HR7;
    uint32_t *pu32MsgDigest = (uint32_t *)((uint32_t)pu8MsgDigest);

    for (i = 0U; i < HASH_MSG_DIGEST_SIZE_WORD; i++) {
        pu32MsgDigest[i] = __REV(regHR[i]);
    }
}

/**
 * @}
 */

/**
 * @defgroup HASH_Global_Functions HASH Global Functions
 * @{
 */

/**
 * @brief  De-initializes HASH.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t HASH_DeInit(void)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeOut = 0U;

    /* Check parameters */
    DDL_ASSERT(IS_HASH_PWC_UNLOCKED());

    CLR_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_HASH);
    /* Ensure reset procedure is completed */
    while (RMU_FRST0_HASH != READ_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_HASH)) {
        u32TimeOut++;
        if (u32TimeOut > HASH_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief  HASH calculate.
 * @param  [in]  pu8SrcData             Pointer to the source data buffer.
 * @param  [in]  u32SrcDataSize         Length of the source data buffer in bytes.
 * @param  [out] pu8MsgDigest           Buffer of the digest. The size must be 32 bytes.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       Parameter error.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t HASH_Calculate(const uint8_t *pu8SrcData, uint32_t u32SrcDataSize, uint8_t *pu8MsgDigest)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if ((pu8SrcData != NULL) && (u32SrcDataSize != 0UL) && (pu8MsgDigest != NULL)) {
        /* Set HASH mode */
        i32Ret = HASH_DoCalc(pu8SrcData, u32SrcDataSize);
        if (i32Ret == LL_OK) {
            /* Get the message digest result */
            HASH_ReadMsgDigest(pu8MsgDigest);
        }
    }

    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_HASH_ENABLE */

/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
