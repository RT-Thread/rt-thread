/**
 *******************************************************************************
 * @file  hc32f4a0_aes.c
 * @brief This file provides firmware functions to manage the Advanced Encryption
 *        Standard(AES).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb          First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_aes.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_AES AES
 * @brief AES Driver Library
 * @{
 */

#if (DDL_AES_ENABLE == DDL_ON)

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
#define AES_TIMEOUT                       (30000UL)

/**
 * @defgroup AES_KEY_LENGTH AES key length in bytes
 * @{
 */
#define AES_KEY_LEN_128BIT            (16U)
#define AES_KEY_LEN_192BIT            (24U)
#define AES_KEY_LEN_256BIT            (32U)
/**
 * @}
 */

/**
 * @defgroup AES_Check_Parameters_Validity AES Check Parameters Validity
 * @{
 */
#define IS_AES_KEYLENGTH(x)                                                    \
(   ((x) == AES_KEY_LEN_128BIT)                  ||                            \
    ((x) == AES_KEY_LEN_192BIT)                  ||                            \
    ((x) == AES_KEY_LEN_256BIT))
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
static void AES_WriteData(const uint8_t *pu8Srcdata);
static void AES_ReadData(const uint8_t *pu8Result);
static void AES_WriteKey(const uint8_t *pu8Key, uint8_t u8KeyLength);

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup AES_Global_Functions AES Global Functions
 * @{
 */

/**
 * @brief  AES encryption.
 * @param  [in] au8Plaintext       Buffer of the plaintext(the source data which will be encrypted).
 * @param  [in] u32PlaintextSize   Length of plaintext in bytes.
 * @param  [in] pu8Key             Pointer to the AES key.
 * @param  [in] u8KeyLength        Buffer of the key in bytes.
 * @param  [out] au8Ciphertext     Buffer of the ciphertext.
 * @retval An en_result_t enumeration value:
 *         Ok: Encryption successfully.
 *         ErrorInvalidParameter: Invalid parameter
 *         ErrorTimeout: Encryption error timeout
 */
en_result_t AES_Encrypt(uint8_t au8Plaintext[],
                        uint32_t u32PlaintextSize,
                        const uint8_t *pu8Key,
                        uint8_t u8KeyLength,
                        uint8_t au8Ciphertext[])
{
    en_result_t   enRet = ErrorInvalidParameter;
    uint32_t u32TimeCount = 0UL;
    uint32_t u32Index = 0UL;
    uint8_t au8FillBuffer[16U] = {0U};
    if((au8Plaintext != NULL) && (u32PlaintextSize != 0UL)   \
          && (pu8Key != NULL) && (u8KeyLength != 0U)        \
          && (au8Ciphertext != NULL))
    {
        DDL_ASSERT(IS_AES_KEYLENGTH(u8KeyLength));
        enRet = Ok;
        while(u32PlaintextSize > 0UL)
        {
            /* Wait for AES to stop */
            while(READ_REG32_BIT(M4_AES->CR, AES_CR_START) == 1U)
            {
                if(u32TimeCount++ >= AES_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            if (enRet == Ok)
            {
                if (u32PlaintextSize >= AES_BLOCK_LEN)
                {
                    AES_WriteData(&au8Plaintext[u32Index]);
                }
                else
                {
                    (void)memcpy(au8FillBuffer, &au8Plaintext[u32Index], u32PlaintextSize);
                    AES_WriteData(&au8FillBuffer[0U]);
                }
                AES_WriteKey(pu8Key, u8KeyLength);
                switch (u8KeyLength)
                {
                case AES_KEY_LEN_128BIT:
                    MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_128BIT);
                    break;

                case AES_KEY_LEN_192BIT:
                    MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_192BIT);
                    break;

                case AES_KEY_LEN_256BIT:
                    MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_256BIT);
                    break;

                default:
                    break;
                }
                /* Set AES encrypt. */
                CLEAR_REG32_BIT(M4_AES->CR, AES_CR_MODE);
                /* Start AES calculating. */
                SET_REG32_BIT(M4_AES->CR, AES_CR_START);
                /* Wait for AES to stop */
                u32TimeCount = 0UL;
                while(READ_REG32_BIT(M4_AES->CR, AES_CR_START) == 1U)
                {
                    if(u32TimeCount++ > AES_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                        break;
                    }
                }
                if (enRet == Ok)
                {
                    AES_ReadData(&au8Ciphertext[u32Index]);
                    if (u32PlaintextSize < AES_BLOCK_LEN)
                    {
                        u32PlaintextSize = 0UL;
                    }
                    else
                    {
                        u32PlaintextSize -= AES_BLOCK_LEN;
                    }
                    u32Index += AES_BLOCK_LEN;
                }
            }
        }
    }
    return enRet;
}

/**
 * @brief  AES decryption.
 * @param  [in] au8Ciphertext       Buffer of the Ciphertext(the source data which will be decrypted).
 * @param  [in] u32CiphertextSize   Length of ciphertext in bytes.
 * @param  [in] pu8Key              Pointer to the AES key.
 * @param  [in] u8KeyLength         Length of key in bytes.
 * @param  [out] au8Plaintext       Buffer of the plaintext.
 * @retval An en_result_t enumeration value:
 *         Ok: Decryption successfully.
 *         ErrorInvalidParameter: Invalid parameter
 *         ErrorTimeout: Decryption error timeout
 */
en_result_t AES_Decrypt(uint8_t au8Ciphertext[],
                        uint32_t u32CiphertextSize,
                        const uint8_t *pu8Key,
                        uint8_t u8KeyLength,
                        uint8_t au8Plaintext[])
{
    en_result_t   enRet = Ok;
    uint32_t u32TimeCount = 0UL;
    uint32_t u32Index = 0UL;
    if((au8Plaintext != NULL) && (u32CiphertextSize != 0UL)   \
          && (pu8Key != NULL) && (u8KeyLength != 0U)          \
          && (au8Ciphertext != NULL))
    {
        DDL_ASSERT(IS_AES_KEYLENGTH(u8KeyLength));
        enRet = Ok;
        while(u32CiphertextSize > 0UL)
        {
            /* Wait for AES to stop */
            while(READ_REG32_BIT(M4_AES->CR, AES_CR_START) == 1U)
            {
                if(u32TimeCount++ > AES_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            if (enRet == Ok)
            {
                AES_WriteData(&au8Ciphertext[u32Index]);
                AES_WriteKey(pu8Key, u8KeyLength);
                switch (u8KeyLength)
                {
                case AES_KEY_LEN_128BIT:
                    MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_128BIT);
                    break;

                case AES_KEY_LEN_192BIT:
                    MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_192BIT);
                    break;

                case AES_KEY_LEN_256BIT:
                    MODIFY_REG32(M4_AES->CR, AES_CR_KEYSIZE, AES_KEY_SIZE_256BIT);
                    break;

                default:
                    break;
                }
                /* Set AES decrypt. */
                SET_REG32_BIT(M4_AES->CR, AES_CR_MODE);
                /* Start AES calculating. */
                SET_REG32_BIT(M4_AES->CR, AES_CR_START);
                /* Wait for AES to stop */
                u32TimeCount = 0UL;
                while(READ_REG32_BIT(M4_AES->CR, AES_CR_START) == 1UL)
                {
                    if(u32TimeCount++ >= AES_TIMEOUT)
                    {
                        enRet = ErrorTimeout;
                        break;
                    }
                }
                if (enRet == Ok)
                {
                    AES_ReadData(&au8Plaintext[u32Index]);
                    u32CiphertextSize -= AES_BLOCK_LEN;
                    u32Index += AES_BLOCK_LEN;
                }
            }
        }
    }
    return enRet;
}

/**
 * @brief  Write the input buffer in data register.
 * @param  [in] pu8Srcdata    Point to the source data buffer.
 * @retval None
 */
static void AES_WriteData(const uint8_t *pu8Srcdata)
{
    uint8_t  i;
    uint32_t u32DrAddr  = (uint32_t)&(M4_AES->DR0);
    uint32_t u32SrcAddr = (uint32_t)pu8Srcdata;

    for(i = 0U; i < 4U; i++)
    {
        RW_MEM32(u32DrAddr) = RW_MEM32(u32SrcAddr);
        u32SrcAddr += 4UL;
        u32DrAddr  += 4UL;
    }
}

/**
 * @brief  Read the from data register.
 * @param  [out] pu8Result    Point to the result buffer.
 * @retval None
 */
static void AES_ReadData(const uint8_t *pu8Result)
{
    uint8_t  i;
    uint32_t u32DrAddr   = (uint32_t)&(M4_AES->DR0);
    uint32_t u32ResultAddr = (uint32_t)pu8Result;
    for(i = 0U; i < 4U; i++)
    {
        RW_MEM32(u32ResultAddr) = RW_MEM32(u32DrAddr);
        u32DrAddr += 4U;
        u32ResultAddr += 4UL;
    }
}

/**
 * @brief  Write the input buffer in key register.
 * @param  [in] pu8Key        Pointer to the kry buffer.
 * @param  [in] u8KeyLength   Length of key in bytes.
 * @retval None
 */
static void AES_WriteKey(const uint8_t *pu8Key, uint8_t u8KeyLength)
{
    uint8_t i;
    uint8_t Length = 0U;
    uint32_t u32KeyAddr  = (uint32_t)&(M4_AES->KR0);
    uint32_t u32DataAddr = (uint32_t)pu8Key;
    switch (u8KeyLength)
    {
        case AES_KEY_LEN_128BIT:
            Length = 4U;
            break;
        case AES_KEY_LEN_192BIT:
            Length = 6U;
            break;
        case AES_KEY_LEN_256BIT:
            Length = 8U;
            break;
        default:
            break;
    }
    for(i = 0U; i < Length; i++)
    {
        RW_MEM32(u32KeyAddr) = RW_MEM32(u32DataAddr);
        u32DataAddr += 4UL;
        u32KeyAddr += 4UL;
    }
}
/**
 * @}
 */

#endif /* DDL_AES_ENABLE */

/**
 * @}
 */

/**
* @}
*/
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

