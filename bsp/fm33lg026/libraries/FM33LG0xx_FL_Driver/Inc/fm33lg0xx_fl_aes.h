/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_aes.h
  * @author  FMSH Application Team
  * @brief   Head file of AES FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LG0XX_FL_AES_H
#define __FM33LG0XX_FL_AES_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup AES AES
  * @brief AES FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup AES_FL_ES_INIT AES Exported Init structures
  * @{
  */

/**
  * @brief FL AES Init Sturcture definition
  */
typedef struct
{
    /* 秘钥长度 */
    uint32_t keyLength;
    /* 数据流处理模式 */
    uint32_t cipherMode;
    /* AES工作模式 */
    uint32_t operationMode;
    /* 输入数据类型 */
    uint32_t dataType;

} FL_AES_InitTypeDef;
/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup AES_FL_Exported_Constants AES Exported Constants
  * @{
  */

#define    AES_CR_KEYLEN_Pos                                      (13U)
#define    AES_CR_KEYLEN_Msk                                      (0x3U << AES_CR_KEYLEN_Pos)
#define    AES_CR_KEYLEN                                          AES_CR_KEYLEN_Msk

#define    AES_CR_DMAOEN_Pos                                      (12U)
#define    AES_CR_DMAOEN_Msk                                      (0x1U << AES_CR_DMAOEN_Pos)
#define    AES_CR_DMAOEN                                          AES_CR_DMAOEN_Msk

#define    AES_CR_DMAIEN_Pos                                      (11U)
#define    AES_CR_DMAIEN_Msk                                      (0x1U << AES_CR_DMAIEN_Pos)
#define    AES_CR_DMAIEN                                          AES_CR_DMAIEN_Msk

#define    AES_CR_IVRSWAP_Pos                                     (9U)
#define    AES_CR_IVRSWAP_Msk                                     (0x3U << AES_CR_IVRSWAP_Pos)
#define    AES_CR_IVRSWAP                                         AES_CR_IVRSWAP_Msk

#define    AES_CR_CHMOD_Pos                                       (5U)
#define    AES_CR_CHMOD_Msk                                       (0x3U << AES_CR_CHMOD_Pos)
#define    AES_CR_CHMOD                                           AES_CR_CHMOD_Msk

#define    AES_CR_MODE_Pos                                        (3U)
#define    AES_CR_MODE_Msk                                        (0x3U << AES_CR_MODE_Pos)
#define    AES_CR_MODE                                            AES_CR_MODE_Msk

#define    AES_CR_DATATYP_Pos                                     (1U)
#define    AES_CR_DATATYP_Msk                                     (0x3U << AES_CR_DATATYP_Pos)
#define    AES_CR_DATATYP                                         AES_CR_DATATYP_Msk

#define    AES_CR_EN_Pos                                          (0U)
#define    AES_CR_EN_Msk                                          (0x1U << AES_CR_EN_Pos)
#define    AES_CR_EN                                              AES_CR_EN_Msk

#define    AES_IER_WRERR_IE_Pos                                   (2U)
#define    AES_IER_WRERR_IE_Msk                                   (0x1U << AES_IER_WRERR_IE_Pos)
#define    AES_IER_WRERR_IE                                       AES_IER_WRERR_IE_Msk

#define    AES_IER_RDERR_IE_Pos                                   (1U)
#define    AES_IER_RDERR_IE_Msk                                   (0x1U << AES_IER_RDERR_IE_Pos)
#define    AES_IER_RDERR_IE                                       AES_IER_RDERR_IE_Msk

#define    AES_IER_CCF_IE_Pos                                     (0U)
#define    AES_IER_CCF_IE_Msk                                     (0x1U << AES_IER_CCF_IE_Pos)
#define    AES_IER_CCF_IE                                         AES_IER_CCF_IE_Msk

#define    AES_ISR_WRERR_Pos                                      (2U)
#define    AES_ISR_WRERR_Msk                                      (0x1U << AES_ISR_WRERR_Pos)
#define    AES_ISR_WRERR                                          AES_ISR_WRERR_Msk

#define    AES_ISR_RDERR_Pos                                      (1U)
#define    AES_ISR_RDERR_Msk                                      (0x1U << AES_ISR_RDERR_Pos)
#define    AES_ISR_RDERR                                          AES_ISR_RDERR_Msk

#define    AES_ISR_CCF_Pos                                        (0U)
#define    AES_ISR_CCF_Msk                                        (0x1U << AES_ISR_CCF_Pos)
#define    AES_ISR_CCF                                            AES_ISR_CCF_Msk



#define    FL_AES_KEY0_OFFSET                                     (0x0U << 0U)
#define    FL_AES_KEY1_OFFSET                                     (0x1U << 0U)
#define    FL_AES_KEY2_OFFSET                                     (0x2U << 0U)
#define    FL_AES_KEY3_OFFSET                                     (0x3U << 0U)
#define    FL_AES_KEY4_OFFSET                                     (0x4U << 0U)
#define    FL_AES_KEY5_OFFSET                                     (0x5U << 0U)
#define    FL_AES_KEY6_OFFSET                                     (0x6U << 0U)
#define    FL_AES_KEY7_OFFSET                                     (0x7U << 0U)
#define    FL_AES_IVR0_OFFSET                                     (0x0U << 0U)
#define    FL_AES_IVR1_OFFSET                                     (0x1U << 0U)
#define    FL_AES_IVR2_OFFSET                                     (0x2U << 0U)
#define    FL_AES_IVR3_OFFSET                                     (0x3U << 0U)
#define    FL_AES_H0_OFFSET                                       (0x0U << 0U)
#define    FL_AES_H1_OFFSET                                       (0x1U << 0U)
#define    FL_AES_H2_OFFSET                                       (0x2U << 0U)
#define    FL_AES_H3_OFFSET                                       (0x3U << 0U)



#define    FL_AES_KEY_LENGTH_128B                                 (0x0U << AES_CR_KEYLEN_Pos)
#define    FL_AES_KEY_LENGTH_192B                                 (0x1U << AES_CR_KEYLEN_Pos)
#define    FL_AES_KEY_LENGTH_256B                                 (0x2U << AES_CR_KEYLEN_Pos)


#define    FL_AES_IVR_SWAP_32B                                    (0x0U << AES_CR_IVRSWAP_Pos)
#define    FL_AES_IVR_SWAP_16B                                    (0x1U << AES_CR_IVRSWAP_Pos)
#define    FL_AES_IVR_SWAP_8B                                     (0x2U << AES_CR_IVRSWAP_Pos)
#define    FL_AES_IVR_SWAP_1B                                     (0x3U << AES_CR_IVRSWAP_Pos)


#define    FL_AES_CIPHER_ECB                                      (0x0U << AES_CR_CHMOD_Pos)
#define    FL_AES_CIPHER_CBC                                      (0x1U << AES_CR_CHMOD_Pos)
#define    FL_AES_CIPHER_CTR                                      (0x2U << AES_CR_CHMOD_Pos)
#define    FL_AES_CIPHER_MULTH                                    (0x3U << AES_CR_CHMOD_Pos)


#define    FL_AES_OPERATION_MODE_ENCRYPTION                       (0x0U << AES_CR_MODE_Pos)
#define    FL_AES_OPERATION_MODE_KEYDERIVATION                    (0x1U << AES_CR_MODE_Pos)
#define    FL_AES_OPERATION_MODE_DECRYPTION                       (0x2U << AES_CR_MODE_Pos)
#define    FL_AES_OPERATION_MODE_KEYDERIVATION_DECRYPTION         (0x3U << AES_CR_MODE_Pos)


#define    FL_AES_DATA_TYPE_32B                                   (0x0U << AES_CR_DATATYP_Pos)
#define    FL_AES_DATA_TYPE_16B                                   (0x1U << AES_CR_DATATYP_Pos)
#define    FL_AES_DATA_TYPE_8B                                    (0x2U << AES_CR_DATATYP_Pos)
#define    FL_AES_DATA_TYPE_1B                                    (0x3U << AES_CR_DATATYP_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup AES_FL_Exported_Functions AES Exported Functions
  * @{
  */

/**
  * @brief    Set key size selection
  * @rmtoll   CR    KEYLEN    FL_AES_SetKeySize
  * @param    AESx AES instance
  * @param    keySize This parameter can be one of the following values:
  *           @arg @ref FL_AES_KEY_LENGTH_128B
  *           @arg @ref FL_AES_KEY_LENGTH_192B
  *           @arg @ref FL_AES_KEY_LENGTH_256B
  * @retval   None
  */
__STATIC_INLINE void FL_AES_SetKeySize(AES_Type *AESx, uint32_t keySize)
{
    MODIFY_REG(AESx->CR, AES_CR_KEYLEN_Msk, keySize);
}

/**
  * @brief    Get key size selection
  * @rmtoll   CR    KEYLEN    FL_AES_GetKeySize
  * @param    AESx AES instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_AES_KEY_LENGTH_128B
  *           @arg @ref FL_AES_KEY_LENGTH_192B
  *           @arg @ref FL_AES_KEY_LENGTH_256B
  */
__STATIC_INLINE uint32_t FL_AES_GetKeySize(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->CR, AES_CR_KEYLEN_Msk));
}

/**
  * @brief    DMA output enable
  * @rmtoll   CR    DMAOEN    FL_AES_EnableDMAReq_Output
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_EnableDMAReq_Output(AES_Type *AESx)
{
    SET_BIT(AESx->CR, AES_CR_DMAOEN_Msk);
}

/**
  * @brief    DMA output enable status
  * @rmtoll   CR    DMAOEN    FL_AES_IsEnabledDMAReq_Output
  * @param    AESx AES instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_AES_IsEnabledDMAReq_Output(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->CR, AES_CR_DMAOEN_Msk) == AES_CR_DMAOEN_Msk);
}

/**
  * @brief    DMA output disable
  * @rmtoll   CR    DMAOEN    FL_AES_DisableDMAReq_Output
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_DisableDMAReq_Output(AES_Type *AESx)
{
    CLEAR_BIT(AESx->CR, AES_CR_DMAOEN_Msk);
}

/**
  * @brief    DMA input enable
  * @rmtoll   CR    DMAIEN    FL_AES_EnableDMAReq_Input
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_EnableDMAReq_Input(AES_Type *AESx)
{
    SET_BIT(AESx->CR, AES_CR_DMAIEN_Msk);
}

/**
  * @brief    DMA input enable status
  * @rmtoll   CR    DMAIEN    FL_AES_IsEnabledDMAReq_Input
  * @param    AESx AES instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_AES_IsEnabledDMAReq_Input(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->CR, AES_CR_DMAIEN_Msk) == AES_CR_DMAIEN_Msk);
}

/**
  * @brief    DMA input disable
  * @rmtoll   CR    DMAIEN    FL_AES_DisableDMAReq_Input
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_DisableDMAReq_Input(AES_Type *AESx)
{
    CLEAR_BIT(AESx->CR, AES_CR_DMAIEN_Msk);
}

/**
  * @brief    Set IVR register read out swapping
  * @rmtoll   CR    IVRSWAP    FL_AES_SetIVRSwapType
  * @param    AESx AES instance
  * @param    type This parameter can be one of the following values:
  *           @arg @ref FL_AES_IVR_SWAP_32B
  *           @arg @ref FL_AES_IVR_SWAP_16B
  *           @arg @ref FL_AES_IVR_SWAP_8B
  *           @arg @ref FL_AES_IVR_SWAP_1B
  * @retval   None
  */
__STATIC_INLINE void FL_AES_SetIVRSwapType(AES_Type *AESx, uint32_t type)
{
    MODIFY_REG(AESx->CR, AES_CR_IVRSWAP_Msk, type);
}

/**
  * @brief    Get IVR register read out swapping
  * @rmtoll   CR    IVRSWAP    FL_AES_GetIVRSwapType
  * @param    AESx AES instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_AES_IVR_SWAP_32B
  *           @arg @ref FL_AES_IVR_SWAP_16B
  *           @arg @ref FL_AES_IVR_SWAP_8B
  *           @arg @ref FL_AES_IVR_SWAP_1B
  */
__STATIC_INLINE uint32_t FL_AES_GetIVRSwapType(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->CR, AES_CR_IVRSWAP_Msk));
}

/**
  * @brief    Set cipher mode
  * @rmtoll   CR    CHMOD    FL_AES_SetCipherMode
  * @param    AESx AES instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_AES_CIPHER_ECB
  *           @arg @ref FL_AES_CIPHER_CBC
  *           @arg @ref FL_AES_CIPHER_CTR
  *           @arg @ref FL_AES_CIPHER_MULTH
  * @retval   None
  */
__STATIC_INLINE void FL_AES_SetCipherMode(AES_Type *AESx, uint32_t mode)
{
    MODIFY_REG(AESx->CR, AES_CR_CHMOD_Msk, mode);
}

/**
  * @brief    Get cipher mode
  * @rmtoll   CR    CHMOD    FL_AES_GetCipherMode
  * @param    AESx AES instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_AES_CIPHER_ECB
  *           @arg @ref FL_AES_CIPHER_CBC
  *           @arg @ref FL_AES_CIPHER_CTR
  *           @arg @ref FL_AES_CIPHER_MULTH
  */
__STATIC_INLINE uint32_t FL_AES_GetCipherMode(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->CR, AES_CR_CHMOD_Msk));
}

/**
  * @brief    Set operation mode
  * @rmtoll   CR    MODE    FL_AES_SetOperationMode
  * @param    AESx AES instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_AES_OPERATION_MODE_ENCRYPTION
  *           @arg @ref FL_AES_OPERATION_MODE_KEYDERIVATION
  *           @arg @ref FL_AES_OPERATION_MODE_DECRYPTION
  *           @arg @ref FL_AES_OPERATION_MODE_KEYDERIVATION_DECRYPTION
  * @retval   None
  */
__STATIC_INLINE void FL_AES_SetOperationMode(AES_Type *AESx, uint32_t mode)
{
    MODIFY_REG(AESx->CR, AES_CR_MODE_Msk, mode);
}

/**
  * @brief    Get operation mode
  * @rmtoll   CR    MODE    FL_AES_GetOperationMode
  * @param    AESx AES instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_AES_OPERATION_MODE_ENCRYPTION
  *           @arg @ref FL_AES_OPERATION_MODE_KEYDERIVATION
  *           @arg @ref FL_AES_OPERATION_MODE_DECRYPTION
  *           @arg @ref FL_AES_OPERATION_MODE_KEYDERIVATION_DECRYPTION
  */
__STATIC_INLINE uint32_t FL_AES_GetOperationMode(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->CR, AES_CR_MODE_Msk));
}

/**
  * @brief    Set data type selection
  * @rmtoll   CR    DATATYP    FL_AES_SetDataType
  * @param    AESx AES instance
  * @param    rule This parameter can be one of the following values:
  *           @arg @ref FL_AES_DATA_TYPE_32B
  *           @arg @ref FL_AES_DATA_TYPE_16B
  *           @arg @ref FL_AES_DATA_TYPE_8B
  *           @arg @ref FL_AES_DATA_TYPE_1B
  * @retval   None
  */
__STATIC_INLINE void FL_AES_SetDataType(AES_Type *AESx, uint32_t rule)
{
    MODIFY_REG(AESx->CR, AES_CR_DATATYP_Msk, rule);
}

/**
  * @brief    Get data type selection
  * @rmtoll   CR    DATATYP    FL_AES_GetDataType
  * @param    AESx AES instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_AES_DATA_TYPE_32B
  *           @arg @ref FL_AES_DATA_TYPE_16B
  *           @arg @ref FL_AES_DATA_TYPE_8B
  *           @arg @ref FL_AES_DATA_TYPE_1B
  */
__STATIC_INLINE uint32_t FL_AES_GetDataType(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->CR, AES_CR_DATATYP_Msk));
}

/**
  * @brief    AES enable
  * @rmtoll   CR    EN    FL_AES_Enable
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_Enable(AES_Type *AESx)
{
    SET_BIT(AESx->CR, AES_CR_EN_Msk);
}

/**
  * @brief    Get AES enable status
  * @rmtoll   CR    EN    FL_AES_IsEnabled
  * @param    AESx AES instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_AES_IsEnabled(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->CR, AES_CR_EN_Msk) == AES_CR_EN_Msk);
}

/**
  * @brief    AES disable
  * @rmtoll   CR    EN    FL_AES_Disable
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_Disable(AES_Type *AESx)
{
    CLEAR_BIT(AESx->CR, AES_CR_EN_Msk);
}

/**
  * @brief    Write error interrupt enable
  * @rmtoll   IER    WRERR_IE    FL_AES_EnableIT_WriteError
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_EnableIT_WriteError(AES_Type *AESx)
{
    SET_BIT(AESx->IER, AES_IER_WRERR_IE_Msk);
}

/**
  * @brief    Get write error interrupt enable status
  * @rmtoll   IER    WRERR_IE    FL_AES_IsEnabledIT_WriteError
  * @param    AESx AES instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_AES_IsEnabledIT_WriteError(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->IER, AES_IER_WRERR_IE_Msk) == AES_IER_WRERR_IE_Msk);
}

/**
  * @brief    Write error interrupt disable
  * @rmtoll   IER    WRERR_IE    FL_AES_DisableIT_WriteError
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_DisableIT_WriteError(AES_Type *AESx)
{
    CLEAR_BIT(AESx->IER, AES_IER_WRERR_IE_Msk);
}

/**
  * @brief    Read error interrupt enable
  * @rmtoll   IER    RDERR_IE    FL_AES_EnableIT_ReadError
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_EnableIT_ReadError(AES_Type *AESx)
{
    SET_BIT(AESx->IER, AES_IER_RDERR_IE_Msk);
}

/**
  * @brief    Get read Error interrupt enable status
  * @rmtoll   IER    RDERR_IE    FL_AES_IsEnabledIT_ReadError
  * @param    AESx AES instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_AES_IsEnabledIT_ReadError(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->IER, AES_IER_RDERR_IE_Msk) == AES_IER_RDERR_IE_Msk);
}

/**
  * @brief    Read error interrupt disable
  * @rmtoll   IER    RDERR_IE    FL_AES_DisableIT_ReadError
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_DisableIT_ReadError(AES_Type *AESx)
{
    CLEAR_BIT(AESx->IER, AES_IER_RDERR_IE_Msk);
}

/**
  * @brief    Cipher complete interrupt enable
  * @rmtoll   IER    CCF_IE    FL_AES_EnableIT_Complete
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_EnableIT_Complete(AES_Type *AESx)
{
    SET_BIT(AESx->IER, AES_IER_CCF_IE_Msk);
}

/**
  * @brief    Get cipher complete interrupt enable status
  * @rmtoll   IER    CCF_IE    FL_AES_IsEnabledIT_Complete
  * @param    AESx AES instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_AES_IsEnabledIT_Complete(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->IER, AES_IER_CCF_IE_Msk) == AES_IER_CCF_IE_Msk);
}

/**
  * @brief    Cipher complete interrupt disable
  * @rmtoll   IER    CCF_IE    FL_AES_DisableIT_Complete
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_DisableIT_Complete(AES_Type *AESx)
{
    CLEAR_BIT(AESx->IER, AES_IER_CCF_IE_Msk);
}

/**
  * @brief    Get write error flag
  * @rmtoll   ISR    WRERR    FL_AES_IsActiveFlag_WriteError
  * @param    AESx AES instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_AES_IsActiveFlag_WriteError(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->ISR, AES_ISR_WRERR_Msk) == (AES_ISR_WRERR_Msk));
}

/**
  * @brief    Clear write error flag
  * @rmtoll   ISR    WRERR    FL_AES_ClearFlag_WriteError
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_ClearFlag_WriteError(AES_Type *AESx)
{
    WRITE_REG(AESx->ISR, AES_ISR_WRERR_Msk);
}

/**
  * @brief    Get read error flag
  * @rmtoll   ISR    RDERR    FL_AES_IsActiveFlag_ReadError
  * @param    AESx AES instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_AES_IsActiveFlag_ReadError(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->ISR, AES_ISR_RDERR_Msk) == (AES_ISR_RDERR_Msk));
}

/**
  * @brief    Clear read error flag
  * @rmtoll   ISR    RDERR    FL_AES_ClearFlag_ReadError
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_ClearFlag_ReadError(AES_Type *AESx)
{
    WRITE_REG(AESx->ISR, AES_ISR_RDERR_Msk);
}

/**
  * @brief    Get cipher complete flag
  * @rmtoll   ISR    CCF    FL_AES_IsActiveFlag_Complete
  * @param    AESx AES instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_AES_IsActiveFlag_Complete(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->ISR, AES_ISR_CCF_Msk) == (AES_ISR_CCF_Msk));
}

/**
  * @brief    Clear cipher complete flag
  * @rmtoll   ISR    CCF    FL_AES_ClearFlag_Complete
  * @param    AESx AES instance
  * @retval   None
  */
__STATIC_INLINE void FL_AES_ClearFlag_Complete(AES_Type *AESx)
{
    WRITE_REG(AESx->ISR, AES_ISR_CCF_Msk);
}

/**
  * @brief    Write AES data input register
  * @rmtoll   DIR        FL_AES_WriteInputData
  * @param    AESx AES instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_AES_WriteInputData(AES_Type *AESx, uint32_t data)
{
    MODIFY_REG(AESx->DIR, (0xffffffffU << 0U), (data << 0U));
}

/**
  * @brief    Read AES data output register
  * @rmtoll   DOR        FL_AES_ReadOutputData
  * @param    AESx AES instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_AES_ReadOutputData(AES_Type *AESx)
{
    return (uint32_t)(READ_BIT(AESx->DOR, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Set key registers
  * @rmtoll   KEY0        FL_AES_WriteKeys
  * @param    AESx AES instance
  * @param    offset This parameter can be one of the following values:
  *           @arg @ref FL_AES_KEY0_OFFSET
  *           @arg @ref FL_AES_KEY1_OFFSET
  *           @arg @ref FL_AES_KEY2_OFFSET
  *           @arg @ref FL_AES_KEY3_OFFSET
  *           @arg @ref FL_AES_KEY4_OFFSET
  *           @arg @ref FL_AES_KEY5_OFFSET
  *           @arg @ref FL_AES_KEY6_OFFSET
  *           @arg @ref FL_AES_KEY7_OFFSET
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_AES_WriteKeys(AES_Type *AESx, uint32_t offset, uint32_t data)
{
    WRITE_REG(*((&AESx->KEY0) + offset), data);
}

/**
  * @brief    Get key registers
  * @rmtoll   KEY0        FL_AES_ReadKeys
  * @param    AESx AES instance
  * @param    offset This parameter can be one of the following values:
  *           @arg @ref FL_AES_KEY0_OFFSET
  *           @arg @ref FL_AES_KEY1_OFFSET
  *           @arg @ref FL_AES_KEY2_OFFSET
  *           @arg @ref FL_AES_KEY3_OFFSET
  *           @arg @ref FL_AES_KEY4_OFFSET
  *           @arg @ref FL_AES_KEY5_OFFSET
  *           @arg @ref FL_AES_KEY6_OFFSET
  *           @arg @ref FL_AES_KEY7_OFFSET
  * @retval
  */
__STATIC_INLINE uint32_t FL_AES_ReadKeys(AES_Type *AESx, uint32_t offset)
{
    return (uint32_t)READ_REG(*((&AESx->KEY0) + offset));
}

/**
  * @brief    Write initialization vector registers
  * @rmtoll   DIR        FL_AES_WriteIVR
  * @param    AESx AES instance
  * @param    offset This parameter can be one of the following values:
  *           @arg @ref FL_AES_IVR0_OFFSET
  *           @arg @ref FL_AES_IVR1_OFFSET
  *           @arg @ref FL_AES_IVR2_OFFSET
  *           @arg @ref FL_AES_IVR3_OFFSET
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_AES_WriteIVR(AES_Type *AESx, uint32_t offset, uint32_t data)
{
    WRITE_REG(*((&AESx->IVR0) + offset), data);
}

/**
  * @brief    Read initialization vector registers
  * @rmtoll   DOR        FL_AES_ReadIVR
  * @param    AESx AES instance
  * @param    offset This parameter can be one of the following values:
  *           @arg @ref FL_AES_IVR0_OFFSET
  *           @arg @ref FL_AES_IVR1_OFFSET
  *           @arg @ref FL_AES_IVR2_OFFSET
  *           @arg @ref FL_AES_IVR3_OFFSET
  * @retval
  */
__STATIC_INLINE uint32_t FL_AES_ReadIVR(AES_Type *AESx, uint32_t offset)
{
    return (uint32_t)READ_REG(*((&AESx->IVR0) + offset));
}

/**
  * @brief    Set AES MultH parameter Register
  * @rmtoll   H0        FL_AES_WriteHParams
  * @param    AESx AES instance
  * @param    offset This parameter can be one of the following values:
  *           @arg @ref FL_AES_H0_OFFSET
  *           @arg @ref FL_AES_H1_OFFSET
  *           @arg @ref FL_AES_H2_OFFSET
  *           @arg @ref FL_AES_H3_OFFSET
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_AES_WriteHParams(AES_Type *AESx, uint32_t offset, uint32_t data)
{
    WRITE_REG(*((&AESx->H0) + offset), data);
}

/**
  * @brief    Get AES MultH parameter Register
  * @rmtoll   H0        FL_AES_ReadHParams
  * @param    AESx AES instance
  * @param    offset This parameter can be one of the following values:
  *           @arg @ref FL_AES_H0_OFFSET
  *           @arg @ref FL_AES_H1_OFFSET
  *           @arg @ref FL_AES_H2_OFFSET
  *           @arg @ref FL_AES_H3_OFFSET
  * @retval
  */
__STATIC_INLINE uint32_t FL_AES_ReadHParams(AES_Type *AESx, uint32_t offset)
{
    return (uint32_t)READ_REG(*((&AESx->H0) + offset));
}

/**
  * @}
  */

/** @defgroup AES_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_AES_DeInit(void);
void FL_AES_StructInit(FL_AES_InitTypeDef *AES_InitStructer);
FL_ErrorStatus FL_AES_Init(AES_Type *AESx, FL_AES_InitTypeDef *AES_InitStructer);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __FM33LG0XX_FL_AES_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-14*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
