/**
 *******************************************************************************
 * @file  hc32_ll_hash.c
 * @brief This file provides firmware functions to manage the HASH.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-06-30       CDT             Add HASH_DeInit function
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

#define HASH_KEY_LONG_SIZE              (64U)
/**
 * @}
 */

/**
 * @defgroup HASH_Action HASH Action
 * @{
 */
#define HASH_ACTION_START               (HASH_CR_START)
#define HASH_ACTION_HMAC_END            (HASH_CR_HMAC_END)
/**
 * @}
 */

/**
 * @defgroup HASH_Check_Parameters_Validity HASH Check Parameters Validity
 * @{
 */
#define IS_HASH_BIT_MASK(x, mask)   (((x) != 0U) && (((x) | (mask)) == (mask)))

#define IS_HASH_MD(x)               (((x) == HASH_MD_SHA256) || ((x) == HASH_MD_HMAC))

#define IS_HASH_KEY_SIZE_MD(x)      (((x) == HASH_KEY_MD_LONG_SIZE) || ((x) == HASH_KEY_MD_SHORT_SIZE))

#define IS_HASH_INT(x)              IS_HASH_BIT_MASK(x, HASH_INT_ALL)

#define IS_HASH_FLAG(x)             IS_HASH_BIT_MASK(x, HASH_FLAG_ALL)

#define IS_HASH_FLAG_CLR(x)         IS_HASH_BIT_MASK(x, HASH_FLAG_CLR_ALL)

#define IS_HASH_MSG_GRP(x)                                                     \
(   ((x) == HASH_MSG_GRP_FIRST)                 ||                             \
    ((x) == HASH_MSG_GRP_END)                   ||                             \
    ((x) == HASH_MSG_GRP_ONLY_ONE))
/**
 * @}
 */

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
    uint8_t u8LastGroup    = 0U;
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
            u8LastGroup = 1U;
        }

        /* First group and last group check */
        /* check if first group */
        if (u8FirstGroup != 0U) {
            u8FirstGroup = 0U;
            /* Set first group. */
            WRITE_REG32(bCM_HASH->CR_b.FST_GRP, 1U);
        }
        /* check if last group */
        if (u8LastGroup != 0U) {
            u8LastGroup = 0U;
            /* Set last group. */
            WRITE_REG32(bCM_HASH->CR_b.KMSG_END, 1U);
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
 */
int32_t HASH_DeInit(void)
{
    uint8_t i;
    __IO uint32_t *regDR = &CM_HASH->DR15;

    WRITE_REG32(CM_HASH->CR,  0UL);
    for (i = 0U; i < HASH_GROUP_SIZE_WORD; i++) {
        WRITE_REG32(regDR[i],  0UL);
    }
    return LL_OK;
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
        (void)HASH_SetMode(HASH_MD_SHA256);
        i32Ret = HASH_DoCalc(pu8SrcData, u32SrcDataSize);
        if (i32Ret == LL_OK) {
            /* Get the message digest result */
            HASH_ReadMsgDigest(pu8MsgDigest);
        }
    }

    return i32Ret;
}

/**
 * @brief  HMAC calculate.
 * @param  [in]  pu8SrcData             Pointer to the source data buffer.
 * @param  [in]  u32SrcDataSize         Length of the source data buffer in bytes.
 * @param  [in]  pu8Key                 Buffer of the secret key.
 * @param  [in]  u32KeySize             Size of the input secret key in bytes.
 * @param  [out] pu8MsgDigest           Buffer of the digest data buffer. The size must be 32 bytes.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       Parameter error.
 *           - LL_ERR_BUF_FULL:         Data filling error.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t HASH_HMAC_Calculate(const uint8_t *pu8SrcData, uint32_t u32SrcDataSize,
                            const uint8_t *pu8Key, uint32_t u32KeySize,
                            uint8_t *pu8MsgDigest)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    uint8_t u8FillBuffer[HASH_GROUP_SIZE] = {0U};

    if ((pu8SrcData != NULL) && (u32SrcDataSize != 0UL) && \
        (pu8Key != NULL) && (u32KeySize != 0UL) && (pu8MsgDigest != NULL)) {
        /* Set HMAC Mode */
        (void)HASH_SetMode(HASH_MD_HMAC);
        if (u32KeySize > HASH_KEY_LONG_SIZE) {
            /* Key size longer than 64 bytes. */
            WRITE_REG32(bCM_HASH->CR_b.LKEY, 1U);
            /* Write the key to the data register */
            i32Ret = HASH_DoCalc(pu8Key, u32KeySize);
        } else {
            HASH_MemCopy(u8FillBuffer, pu8Key, u32KeySize);
            /* Key size equal to or shorter than 64 bytes. */
            WRITE_REG32(bCM_HASH->CR_b.LKEY, 0U);
            /* Write the key to the data register */
            HASH_WriteData(u8FillBuffer);
            /* Only one group. */
            SET_REG32_BIT(CM_HASH->CR, HASH_MSG_GRP_ONLY_ONE);
            /* Start hash calculating. */
            WRITE_REG32(bCM_HASH->CR_b.START, 1U);
            /* Wait for operation completion */
            i32Ret = HASH_Wait(HASH_ACTION_START);
        }
        /* Clear operation completion flag */
        WRITE_REG32(bCM_HASH->CR_b.CYC_END, 0U);
        if (i32Ret == LL_OK) {
            i32Ret = HASH_DoCalc(pu8SrcData, u32SrcDataSize);
            /* Write the message to the data register */
            if (i32Ret == LL_OK) {
                i32Ret = HASH_Wait(HASH_ACTION_HMAC_END);
                if (i32Ret == LL_OK) {
                    /* Clear operation completion flag */
                    CLR_REG32_BIT(CM_HASH->CR, HASH_CR_CYC_END | HASH_CR_HMAC_END);
                    /* Get the message digest result */
                    HASH_ReadMsgDigest(pu8MsgDigest);
                }
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable HASH interrupt.
 * @param  [in] u32HashInt              Specifies the HASH interrupt to check.
 *                                      This parameter can be values of @ref HASH_Interrupt
 *   @arg  HASH_INT_GRP:                A set of data operations complete interrupt.
 *   @arg  HASH_INT_ALL_CPLT:           All data operations complete interrupt.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Works timeout.
 */
int32_t HASH_IntCmd(uint32_t u32HashInt, en_functional_state_t enNewState)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_HASH_INT(u32HashInt));

    /* Wait for the HASH to stop */
    i32Ret = HASH_Wait(HASH_ACTION_START);
    if (i32Ret == LL_OK) {
        if (enNewState == ENABLE) {
            SET_REG32_BIT(CM_HASH->CR, u32HashInt);
        } else {
            CLR_REG32_BIT(CM_HASH->CR, u32HashInt);
        }
    }

    return i32Ret;
}

/**
 * @brief  Get the status of the specified HASH flag.
 * @param  [in] u32Flag                 HASH status flag.
 *                                      This parameter can be a value of @ref HASH_Status_Flag
 *   @arg  HASH_FLAG_START:             Operation in progress.
 *   @arg  HASH_FLAG_BUSY:              Operation in progress.
 *   @arg  HASH_FLAG_CYC_END:           key or message operation completed.
 *   @arg  HASH_FLAG_HMAC_END:          HMAC operation completed.
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t HASH_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enStatus = RESET;

    DDL_ASSERT(IS_HASH_FLAG(u32Flag));
    if (READ_REG32_BIT(CM_HASH->CR, u32Flag) != 0UL) {
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief  Clear the status of the specified HASH flag.
 * @param  [in] u32Flag                 HASH status flag.
 *                                      This parameter can be a value of @ref HASH_Status_Flag
 *   @arg  HASH_FLAG_CYC_END:           Clear the key or message operation completed flag
 *   @arg  HASH_FLAG_HMAC_END:          Clear the HMAC operation completed flag
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred
 *           - LL_ERR_TIMEOUT:          Works timeout
 */
int32_t HASH_ClearStatus(uint32_t u32Flag)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_HASH_FLAG_CLR(u32Flag));
    /* Wait for the HASH to stop */
    i32Ret = HASH_Wait(HASH_ACTION_START);
    if (i32Ret == LL_OK) {
        CLR_REG32_BIT(CM_HASH->CR, u32Flag);
    }

    return i32Ret;
}

/**
 * @brief  Specifies HASH mode: SHA256 mode or HMAC mode.
 * @param  [in] u32HashMode             HASH mode selection.
 *                                      This parameter can be a value of @ref HASH_Mode
 *   @arg  HASH_MD_SHA256:              SHA256 mode
 *   @arg  HASH_MD_HMAC:                HMAC mode
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred
 *           - LL_ERR_TIMEOUT:          Works timeout
 */
int32_t HASH_SetMode(uint32_t u32HashMode)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_HASH_MD(u32HashMode));
    /* Wait for the HASH to stop */
    i32Ret = HASH_Wait(HASH_ACTION_START);
    if (i32Ret == LL_OK) {
        MODIFY_REG32(CM_HASH->CR, HASH_CR_MODE, u32HashMode);
    }

    return i32Ret;
}

/**
 * @brief  Set HASH key size mode.
 * @param  [in] u32SizeMode             Key size mode. This parameter can be a value of @ref HASH_Key_Size_Mode
 *   @arg  HASH_KEY_MD_LONG_SIZE:       Key size > 64 Bytes
 *   @arg  HASH_KEY_MD_SHORT_SIZE:      Key size <= 64 Bytes
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred
 *           - LL_ERR_TIMEOUT:          Works timeout
 */
int32_t HASH_SetKeySizeMode(uint32_t u32SizeMode)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_HASH_KEY_SIZE_MD(u32SizeMode));
    /* Wait for the HASH to stop */
    i32Ret = HASH_Wait(HASH_ACTION_START);
    if (i32Ret == LL_OK) {
        MODIFY_REG32(CM_HASH->CR, HASH_CR_LKEY, u32SizeMode);
    }

    return i32Ret;
}

/**
 * @brief  Set message group.
 * @param  [in] u32MsgGroup         First group or Last group of messages.
 *                                  This parameter can be a value of @ref HASH_Msg_Group

 *   @arg  HASH_MSG_GRP_FIRST:      The first group of messages or keys
 *   @arg  HASH_MSG_GRP_END:        The last group of messages or keys
 *   @arg  HASH_MSG_GRP_ONLY_ONE:   Only one set of message or key
 * @retval int32_t:
 *           - LL_OK:               No errors occurred
 *           - LL_ERR_TIMEOUT:      Works timeout
 */
int32_t HASH_SetMsgGroup(uint32_t u32MsgGroup)
{
    int32_t i32Ret;

    DDL_ASSERT(IS_HASH_MSG_GRP(u32MsgGroup));
    /* Wait for the HASH to stop */
    i32Ret = HASH_Wait(HASH_ACTION_START);
    if (i32Ret == LL_OK) {
        SET_REG32_BIT(CM_HASH->CR, u32MsgGroup);
    }

    return i32Ret;
}

/**
 * @brief  Start HASH.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:               No errors occurred
 *           - LL_ERR_TIMEOUT:      Works timeout
 */
int32_t HASH_Start(void)
{
    int32_t i32Ret;

    /* Wait for the HASH to stop */
    i32Ret = HASH_Wait(HASH_ACTION_START);
    if (i32Ret == LL_OK) {
        /* Start hash calculating. */
        SET_REG32_BIT(CM_HASH->CR, HASH_CR_START);
    }

    return i32Ret;
}

/**
 * @brief  Provides the message digest result.
 * @param  [out] pu8MsgDigest           Buffer for message digest.
 * @retval None
 */
void HASH_GetMsgDigest(uint8_t *pu8MsgDigest)
{
    HASH_ReadMsgDigest(pu8MsgDigest);
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
