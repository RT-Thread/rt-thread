/**
 *******************************************************************************
 * @file  hc32_ll_aes.c
 * @brief This file provides firmware functions to manage the Advanced Encryption
 *        Standard(AES).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-06-30       CDT             Add API AES_DeInit()
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
#include "hc32_ll_aes.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_AES AES
 * @brief AES Driver Library
 * @{
 */

#if (LL_AES_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup AES_Local_Macros AES Local Macros
 * @{
 */
/* Delay count for timeout */
#define AES_TIMEOUT                     (30000UL)

/* AES block size */
#define AES_BLOCK_SIZE                  (16U)

/**
 * @defgroup AES_Check_Parameters_Validity AES Check Parameters Validity
 * @{
 */
#define IS_AES_KEY_SIZE(x)                                                     \
(   ((x) == AES_KEY_SIZE_16BYTE)        ||                                     \
    ((x) == AES_KEY_SIZE_24BYTE)        ||                                     \
    ((x) == AES_KEY_SIZE_32BYTE))
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
 * @defgroup AES_Local_Functions AES Local Functions
 * @{
 */
/**
 * @brief  Write the input buffer in data register.
 * @param  [in] pu8SrcData              Point to the source data buffer.
 * @retval None
 */
static void AES_WriteData(const uint8_t *pu8SrcData)
{
    uint8_t i;
    __IO uint32_t *regDR = &CM_AES->DR0;
    const uint32_t *pu32Data = (const uint32_t *)((uint32_t)pu8SrcData);

    for (i = 0U; i < 4U; i++) {
        regDR[i] = pu32Data[i];
    }
}

/**
 * @brief  Read the from data register.
 * @param  [out] pu8Result              Point to the result buffer.
 * @retval None
 */
static void AES_ReadData(uint8_t *pu8Result)
{
    uint8_t i;
    __IO uint32_t *regDR = &CM_AES->DR0;
    uint32_t *pu32Result = (uint32_t *)((uint32_t)pu8Result);

    for (i = 0U; i < 4U; i++) {
        pu32Result[i] = regDR[i];
    }
}

/**
 * @brief  Write the input buffer in key register.
 * @param  [in]  pu8Key                 Pointer to the key buffer.
 * @param  [in]  u8KeySize              AES key size. This parameter can be a value of @ref AES_Key_Size
 * @retval None
 */
static void AES_WriteKey(const uint8_t *pu8Key, uint8_t u8KeySize)
{
    uint8_t i;
    uint8_t u8KeyWordSize = u8KeySize / 4U;
    __IO uint32_t *regKR = &CM_AES->KR0;
    const uint32_t *pu32Key = (const uint32_t *)((uint32_t)pu8Key);

    for (i = 0U; i < u8KeyWordSize; i++) {
        regKR[i] = pu32Key[i];
    }
    switch (u8KeySize) {
        case 16U:
            u8KeySize = 0U;
            break;
        case 24U:
            u8KeySize = 1U;
            break;
        case 32U:
            u8KeySize = 2U;
            break;
        default:
            break;
    }
    MODIFY_REG32(CM_AES->CR, AES_CR_KEYSIZE, ((uint32_t)u8KeySize << AES_CR_KEYSIZE_POS));
}

/**
 * @brief  Wait AES operation done.
 * @param  None
 * @retval None
 */
static int32_t AES_WaitDone(void)
{
    __IO uint32_t u32TimeCount = 0UL;
    int32_t i32Ret = LL_OK;

    while (bCM_AES->CR_b.START != 0UL) {
        if (u32TimeCount++ >= AES_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}
/**
 * @}
 */

/**
 * @defgroup AES_Global_Functions AES Global Functions
 * @{
 */

/**
 * @brief  AES encryption.
 * @param  [in]  pu8Plaintext           Buffer of the plaintext(the source data which will be encrypted).
 * @param  [in]  u32PlaintextSize       Length of plaintext in bytes.
 * @param  [in]  pu8Key                 Pointer to the AES key.
 * @param  [in]  u8KeySize              AES key size. This parameter can be a value of @ref AES_Key_Size
 * @param  [out] pu8Ciphertext          Buffer of the ciphertext.
 * @retval int32_t:
 *           - LL_OK:                   Encrypt successfully.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_TIMEOUT:              Encrypt timeout.
 */
int32_t AES_Encrypt(const uint8_t *pu8Plaintext, uint32_t u32PlaintextSize,
                    const uint8_t *pu8Key, uint8_t u8KeySize,
                    uint8_t *pu8Ciphertext)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    uint32_t u32Index = 0UL;

    DDL_ASSERT(IS_AES_KEY_SIZE(u8KeySize));
    DDL_ASSERT((u32PlaintextSize % AES_BLOCK_SIZE) == 0U);

    if ((pu8Plaintext != NULL) && (u32PlaintextSize > 0UL) && \
        (pu8Key != NULL) && (pu8Ciphertext != NULL)) {
        AES_WriteKey(pu8Key, u8KeySize);
        /* Set AES encrypt. */
        WRITE_REG32(bCM_AES->CR_b.MODE, 0UL);
        while (u32Index < u32PlaintextSize) {
            AES_WriteData(&pu8Plaintext[u32Index]);
            /* Start AES calculating. */
            WRITE_REG32(bCM_AES->CR_b.START, 1UL);
            /* Wait for AES to stop */
            i32Ret = AES_WaitDone();
            if (i32Ret != LL_OK) {
                break;
            }
            AES_ReadData(&pu8Ciphertext[u32Index]);
            u32Index += AES_BLOCK_SIZE;
        }
    }

    return i32Ret;
}

/**
 * @brief  AES decryption.
 * @param  [in]  pu8Ciphertext          Buffer of the Ciphertext(the source data which will be decrypted).
 * @param  [in]  u32CiphertextSize      Length of ciphertext in bytes.
 * @param  [in]  pu8Key                 Pointer to the AES key.
 * @param  [in]  u8KeySize              AES key size. This parameter can be a value of @ref AES_Key_Size
 * @param  [out] pu8Plaintext           Buffer of the plaintext.
 * @retval int32_t:
 *           - LL_OK:                   Decrypt successfully.
 *           - LL_ERR_INVD_PARAM:       Invalid parameter.
 *           - LL_TIMEOUT:              Decrypt timeout.
 */
int32_t AES_Decrypt(const uint8_t *pu8Ciphertext, uint32_t u32CiphertextSize,
                    const uint8_t *pu8Key, uint8_t u8KeySize,
                    uint8_t *pu8Plaintext)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    uint32_t u32Index = 0UL;

    DDL_ASSERT(IS_AES_KEY_SIZE(u8KeySize));
    DDL_ASSERT((u32CiphertextSize % AES_BLOCK_SIZE) == 0U);

    if ((pu8Plaintext != NULL) && (u32CiphertextSize > 0UL) && \
        (pu8Key != NULL) && (pu8Ciphertext != NULL)) {
        AES_WriteKey(pu8Key, u8KeySize);
        /* Set AES decrypt. */
        WRITE_REG32(bCM_AES->CR_b.MODE, 1UL);
        while (u32Index < u32CiphertextSize) {
            AES_WriteData(&pu8Ciphertext[u32Index]);
            /* Start AES calculating. */
            WRITE_REG32(bCM_AES->CR_b.START, 1UL);
            /* Wait for AES to stop */
            i32Ret = AES_WaitDone();
            if (i32Ret != LL_OK) {
                break;
            }
            AES_ReadData(&pu8Plaintext[u32Index]);
            u32Index += AES_BLOCK_SIZE;
        }
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize AES function.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   De-Initialize success.
 *           - LL_ERR_TIMEOUT:          Timeout.
 */
int32_t AES_DeInit(void)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeOut = 0U;
    uint8_t i;
    __IO uint32_t *regDR = &CM_AES->DR0;
    __IO uint32_t *regKR = &CM_AES->KR0;
    /* Wait generating done */
    while (0UL != READ_REG32(bCM_AES->CR_b.START)) {
        u32TimeOut++;
        if (u32TimeOut > AES_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }
    if (LL_OK == i32Ret) {
        /* Configures the registers to reset value. */
        WRITE_REG32(CM_AES->CR, 0x00000000UL);
        for (i = 0U; i < 4U; i++) {
            regDR[i] = 0x00000000UL;
        }
        for (i = 0U; i < 8U; i++) {
            regKR[i] = 0x00000000UL;
        }
    }
    return i32Ret;
}
/**
 * @}
 */

#endif /* LL_AES_ENABLE */

/**
 * @}
 */

/**
 * @}
 */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

