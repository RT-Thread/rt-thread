/**
  ******************************************************************************
  * @file    stm32h5xx_hal_cryp_ex.c
  * @author  MCD Application Team
  * @brief   CRYPEx HAL module driver.
  *          This file provides firmware functions to manage the extended
  *          functionalities of the Cryptography (CRYP) peripheral.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

/** @addtogroup CRYPEx
  * @{
  */

#if defined(AES)

#ifdef HAL_CRYP_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/** @addtogroup CRYPEx_Private_Defines
  * @{
  */

#define CRYP_PHASE_INIT                              0x00000000U             /*!< GCM/GMAC (or CCM) init phase */
#define CRYP_PHASE_HEADER                            AES_CR_GCMPH_0          /*!< GCM/GMAC or CCM header phase */
#define CRYP_PHASE_PAYLOAD                           AES_CR_GCMPH_1          /*!< GCM(/CCM) payload phase   */
#define CRYP_PHASE_FINAL                             AES_CR_GCMPH            /*!< GCM/GMAC or CCM  final phase  */

#define CRYP_OPERATINGMODE_ENCRYPT                   0x00000000U             /*!< Encryption mode   */
#define CRYP_OPERATINGMODE_KEYDERIVATION             AES_CR_MODE_0           /*!< Key derivation mode  only used when performing ECB and CBC decryptions  */
#define CRYP_OPERATINGMODE_DECRYPT                   AES_CR_MODE_1           /*!< Decryption       */
#define CRYP_OPERATINGMODE_KEYDERIVATION_DECRYPT     AES_CR_MODE             /*!< Key derivation and decryption only used when performing ECB and CBC decryptions  */

#define  CRYPEx_PHASE_PROCESS       0x02U     /*!< CRYP peripheral is in processing phase */
#define  CRYPEx_PHASE_FINAL         0x03U     /*!< CRYP peripheral is in final phase this is relevant only with CCM and GCM modes */

/*  CTR0 information to use in CCM algorithm */
#define CRYP_CCM_CTR0_0            0x07FFFFFFU
#define CRYP_CCM_CTR0_3            0xFFFFFF00U

/**
  * @}
  */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static HAL_StatusTypeDef CRYPEx_KeyDecrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYPEx_KeyEncrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
static HAL_StatusTypeDef CRYPEx_KeyGeneration(CRYP_HandleTypeDef *hcryp, uint32_t Timeout);
/* Exported functions---------------------------------------------------------*/
/** @addtogroup CRYPEx_Exported_Functions
  * @{
  */

/** @defgroup CRYPEx_Exported_Functions_Group1 Extended AES processing functions
  *  @brief   Extended processing functions.
  *
@verbatim
  ==============================================================================
              ##### Extended AES processing functions #####
  ==============================================================================
    [..]  This section provides functions allowing to generate the authentication
          TAG in Polling mode
      (#)HAL_CRYPEx_AESGCM_GenerateAuthTAG
      (#)HAL_CRYPEx_AESCCM_GenerateAuthTAG
         they should be used after Encrypt/Decrypt operation.

@endverbatim
  * @{
  */

/**
  * @brief  generate the GCM authentication TAG.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pAuthTag Pointer to the authentication buffer
  *         the pAuthTag generated here is 128bits length, if the TAG length is
  *         less than 128bits, user should consider only the valid part of pAuthTag
  *         buffer which correspond exactly to TAG length.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYPEx_AESGCM_GenerateAuthTAG(CRYP_HandleTypeDef *hcryp, const uint32_t *pAuthTag,
                                                    uint32_t Timeout)
{
  /* Assume first Init.HeaderSize is in words */
  uint64_t headerlength = (uint64_t)hcryp->Init.HeaderSize * 32U; /* Header length in bits */
  uint64_t inputlength = (uint64_t)hcryp->SizesSum * 8U; /* Input length in bits */
  uint32_t tagaddr = (uint32_t)pAuthTag;
  uint32_t i;
  uint32_t tickstart;

  /* Correct headerlength if Init.HeaderSize is actually in bytes */
  if (hcryp->Init.HeaderWidthUnit == CRYP_HEADERWIDTHUNIT_BYTE)
  {
    headerlength /= 4U;
  }

  if (hcryp->State == HAL_CRYP_STATE_READY)
  {
    __HAL_LOCK(hcryp);

    /* Change the CRYP peripheral state */
    hcryp->State = HAL_CRYP_STATE_BUSY;

    /* Check if initialization phase has already been performed */
    if (hcryp->Phase == CRYPEx_PHASE_PROCESS)
    {
      /* Change the CRYP phase */
      hcryp->Phase = CRYPEx_PHASE_FINAL;

      /* Select final phase */
      MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, CRYP_PHASE_FINAL);

      /* Write into the AES_DINR register the number of bits in header (64 bits)
      followed by the number of bits in the payload */
      hcryp->Instance->DINR = 0U;
      hcryp->Instance->DINR = (uint32_t)(headerlength);
      hcryp->Instance->DINR = 0U;
      hcryp->Instance->DINR = (uint32_t)(inputlength);

      /* Wait for CCF flag to be raised */
      tickstart = HAL_GetTick();
      while (HAL_IS_BIT_CLR(hcryp->Instance->ISR, AES_ISR_CCF))
      {
        /* Check for the Timeout */
        if (Timeout != HAL_MAX_DELAY)
        {
          if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
          {
            /* Disable the CRYP peripheral clock */
            __HAL_CRYP_DISABLE(hcryp);

            /* Change state */
            hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
            hcryp->State = HAL_CRYP_STATE_READY;
            __HAL_UNLOCK(hcryp);
            return HAL_ERROR;
          }
        }
      }

      /* Read the authentication TAG in the output FIFO */
      for (i = 0U; i < 4U; i++)
      {
        *(uint32_t *)(tagaddr) = hcryp->Instance->DOUTR;
        tagaddr += 4U;
      }

      /* Clear CCF flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEAR_CCF);

      /* Disable the peripheral */
      __HAL_CRYP_DISABLE(hcryp);

      /* Change the CRYP peripheral state */
      hcryp->State = HAL_CRYP_STATE_READY;
      __HAL_UNLOCK(hcryp);
    }
    else /* Initialization phase has not been performed */
    {
      /* Disable the Peripheral */
      __HAL_CRYP_DISABLE(hcryp);

      /* Sequence error code field */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_AUTH_TAG_SEQUENCE;

      /* Change the CRYP peripheral state */
      hcryp->State = HAL_CRYP_STATE_READY;
      __HAL_UNLOCK(hcryp);
      return HAL_ERROR;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    return HAL_ERROR;
  }
  /* Return function status */
  return HAL_OK;
}

/**
  * @brief  AES CCM Authentication TAG generation.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pAuthTag Pointer to the authentication buffer
  *         the pAuthTag generated here is 128bits length, if the TAG length is
  *         less than 128bits, user should consider only the valid part of pAuthTag
  *         buffer which correspond exactly to TAG length.
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYPEx_AESCCM_GenerateAuthTAG(CRYP_HandleTypeDef *hcryp, const uint32_t *pAuthTag,
                                                    uint32_t Timeout)
{
  uint32_t tagaddr = (uint32_t)pAuthTag;
  uint32_t i;
  uint32_t tickstart;

  if (hcryp->State == HAL_CRYP_STATE_READY)
  {
    __HAL_LOCK(hcryp);

    /* Disable interrupts in case they were kept enabled to proceed
       a single message in several iterations */
    __HAL_CRYP_DISABLE_IT(hcryp, CRYP_IT_CCFIE | CRYP_IT_RWEIE | CRYP_IT_KEIE);

    /* Change the CRYP peripheral state */
    hcryp->State = HAL_CRYP_STATE_BUSY;

    /* Check if initialization phase has already been performed */
    if (hcryp->Phase == CRYPEx_PHASE_PROCESS)
    {
      /* Change the CRYP phase */
      hcryp->Phase = CRYPEx_PHASE_FINAL;
      /* Select final phase */
      MODIFY_REG(hcryp->Instance->CR, AES_CR_GCMPH, CRYP_PHASE_FINAL);

      /* Wait for CCF flag to be raised */
      tickstart = HAL_GetTick();
      while (HAL_IS_BIT_CLR(hcryp->Instance->ISR, AES_ISR_CCF))
      {
        /* Check for the Timeout */
        if (Timeout != HAL_MAX_DELAY)
        {
          if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
          {
            /* Disable the CRYP peripheral Clock */
            __HAL_CRYP_DISABLE(hcryp);

            /* Change state */
            hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
            hcryp->State = HAL_CRYP_STATE_READY;
            __HAL_UNLOCK(hcryp);
            return HAL_ERROR;
          }
        }
      }

      /* Read the authentication TAG in the output FIFO */
      for (i = 0U; i < 4U; i++)
      {
        *(uint32_t *)(tagaddr) = hcryp->Instance->DOUTR;
        tagaddr += 4U;
      }

      /* Clear CCF Flag */
      __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEAR_CCF);

      /* Change the CRYP peripheral state */
      hcryp->State = HAL_CRYP_STATE_READY;
      __HAL_UNLOCK(hcryp);

      /* Disable CRYP */
      __HAL_CRYP_DISABLE(hcryp);
    }
    else /* Initialization phase has not been performed */
    {
      /* Disable the peripheral */
      __HAL_CRYP_DISABLE(hcryp);

      /* Sequence error code field */
      hcryp->ErrorCode |= HAL_CRYP_ERROR_AUTH_TAG_SEQUENCE;

      /* Change the CRYP peripheral state */
      hcryp->State = HAL_CRYP_STATE_READY;
      __HAL_UNLOCK(hcryp);
      return HAL_ERROR;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode = HAL_CRYP_ERROR_BUSY;
    return HAL_ERROR;
  }
  /* Return function status */
  return HAL_OK;
}

/**
  * @}
  */


/** @defgroup CRYPEx_Exported_Functions_Group2 Wrap and Unwrap key functions
  * @brief    Wrap and Unwrap key functions.
  *
@verbatim
  ==============================================================================
                      ##### Wrap and Unwrap key #####
  ==============================================================================
    [..]  This section provides API allowing to wrap (encrypt) and unwrap (decrypt)
          key using one of the following keys, and AES Algorithm.
          Key selection :
           - Derived hardware unique key (DHUK)
           - XOR of DHUK and BHK
           - Boot hardware key (BHK)

@endverbatim
  * @{
  */

/**
  * @brief  Wrap (encrypt) application keys.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pInput Pointer to the Key buffer to encrypt in case of ECB or CBC
  * @param  pOutput Pointer to the Key buffer encrypted in case of ECB or CBC
  * @param  Timeout Specify Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYPEx_WrapKey(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint32_t *pOutput, uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t algo;

  if (hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    __HAL_LOCK(hcryp);

    /* Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters*/
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = pInput;
    hcryp->pCrypOutBuffPtr = pOutput;

    /* Disable the CRYP peripheral clock */
    __HAL_CRYP_DISABLE(hcryp);

    /* Set the operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_KMOD, CRYP_KEYMODE_WRAPPED);

    /* Encryption operating mode(Mode 0)*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT);


    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {
      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
        /* AES decryption */
        status = CRYPEx_KeyEncrypt(hcryp, Timeout);
        break;
      case CRYP_AES_CTR:
        /* AES Key generation */
        status = CRYPEx_KeyGeneration(hcryp, Timeout);
        break;
      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  Unwrap (Decrypt) application keys.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pInput Pointer to the Key buffer to decrypt or generated key in case of CTR.
  * @param  Timeout Specify Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYPEx_UnwrapKey(CRYP_HandleTypeDef *hcryp, uint32_t *pInput, uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t algo;

  if (hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;

    __HAL_LOCK(hcryp);

    /* Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters */
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = pInput;

    /* Disable the CRYP peripheral clock */
    __HAL_CRYP_DISABLE(hcryp);

    /* Set the operating mode*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_KMOD, CRYP_KEYMODE_WRAPPED);

    /* Decryption operating mode(Mode 3)*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {
      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
        /* AES decryption */
        status = CRYPEx_KeyDecrypt(hcryp, Timeout);
        break;

      case CRYP_AES_CTR:
        /* AES Key generation */
        status = CRYPEx_KeyGeneration(hcryp, Timeout);
        break;
      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @}
  */

/** @defgroup CRYPEx_Exported_Functions_Group3 Encrypt and Decrypt Shared key functions
  * @brief    Encrypt and Decrypt Shared key functions.
  *
@verbatim
  ==============================================================================
                      ##### Encrypt and Decrypt Shared key functions #####
  ==============================================================================
    [..]  This section provides API allowing to Encrypt and Decrypt Shared key

@endverbatim
  * @{
  */

/**
  * @brief  Encrypt Shared key.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pKey Pointer to the Key buffer to share
  * @param  pOutput Pointer to the Key buffer encrypted
  * @param  ID Key share identification
  * @param  Timeout Specify Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYPEx_EncryptSharedKey(CRYP_HandleTypeDef *hcryp, uint32_t *pKey, uint32_t *pOutput, uint32_t ID,
                                              uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t algo;

  if (hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    __HAL_LOCK(hcryp);

    /* Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters */
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = pKey;
    hcryp->pCrypOutBuffPtr = pOutput;

    /* Disable the CRYP peripheral clock */
    __HAL_CRYP_DISABLE(hcryp);

    /* Set the operating mode */
    MODIFY_REG(hcryp->Instance->CR, AES_CR_KMOD | AES_CR_KSHAREID, CRYP_KEYMODE_SHARED | ID);

    /* Encryption operating mode(Mode 0)*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_ENCRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {
      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
        /* AES decryption */
        status = CRYPEx_KeyEncrypt(hcryp, Timeout);
        break;
      case CRYP_AES_CTR:
        /* AES CTR key generation */
        status = CRYPEx_KeyGeneration(hcryp, Timeout);
        break;
      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @brief  Decrypt Shared key.
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure that contains
  *         the configuration information for CRYP module
  * @param  pKey Pointer to the Key buffer to share
  * @param  ID Key share identification
  * @param  Timeout Specify Timeout value
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_CRYPEx_DecryptSharedKey(CRYP_HandleTypeDef *hcryp, uint32_t *pKey, uint32_t ID, uint32_t Timeout)
{
  HAL_StatusTypeDef status;
  uint32_t algo;

  if (hcryp->State == HAL_CRYP_STATE_READY)
  {
    /* Change state Busy */
    hcryp->State = HAL_CRYP_STATE_BUSY;
    __HAL_LOCK(hcryp);

    /* Reset CrypInCount, CrypOutCount and Initialize pCrypInBuffPtr and pCrypOutBuffPtr parameters */
    hcryp->CrypInCount = 0U;
    hcryp->CrypOutCount = 0U;
    hcryp->pCrypInBuffPtr = pKey;

    /* Disable the CRYP peripheral clock */
    __HAL_CRYP_DISABLE(hcryp);

    /* Set the operating mode */
    MODIFY_REG(hcryp->Instance->CR, AES_CR_KMOD | AES_CR_KSHAREID, CRYP_KEYMODE_SHARED | ID);

    /* Decryption operating mode(Mode 3)*/
    MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);

    /* algo get algorithm selected */
    algo = hcryp->Instance->CR & AES_CR_CHMOD;

    switch (algo)
    {
      case CRYP_AES_ECB:
      case CRYP_AES_CBC:
        /* AES decryption */
        status = CRYPEx_KeyDecrypt(hcryp, Timeout);
        break;
      case CRYP_AES_CTR:
        /* AES CTR key generation */
        status = CRYPEx_KeyGeneration(hcryp, Timeout);
        break;
      default:
        hcryp->ErrorCode |= HAL_CRYP_ERROR_NOT_SUPPORTED;
        status = HAL_ERROR;
        break;
    }
  }
  else
  {
    /* Busy error code field */
    hcryp->ErrorCode |= HAL_CRYP_ERROR_BUSY;
    status = HAL_ERROR;
  }
  /* Return function status */
  return status;
}

/**
  * @}
  */

/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @addtogroup CRYP_Private_Functions
  * @{
  */
/**
  * @brief  Key Decryption
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure
  * @param  Timeout specify Timeout value
  * @note   It is strongly recommended to select hardware secret keys
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYPEx_KeyDecrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t incount; /* Temporary CrypInCount Value */
  uint32_t i;
  uint32_t tickstart;

  /* key preparation for decryption, operating mode 2*/
  MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_KEYDERIVATION);

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  /* Wait for CCF flag to be raised */
  tickstart = HAL_GetTick();
  while (HAL_IS_BIT_CLR(hcryp->Instance->ISR, AES_ISR_CCF))
  {
    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);

        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;
        __HAL_UNLOCK(hcryp);
        return HAL_ERROR;
      }
    }
  }
  /* Clear CCF Flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEAR_CCF);

  /*  End of Key preparation for ECB/CBC */
  /* Return to decryption operating mode(Mode 3)*/
  MODIFY_REG(hcryp->Instance->CR, AES_CR_MODE, CRYP_OPERATINGMODE_DECRYPT);

  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector */
    hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
    hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
    hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
  }
  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  /* Set the phase */
  hcryp->Phase = CRYPEx_PHASE_PROCESS;

  if (hcryp->Init.KeySize == CRYP_KEYSIZE_128B)
  {
    incount = 4U;
  }
  else
  {
    incount = 8U;
  }
  while (hcryp->CrypInCount < incount)
  {
    /* Write four times to input the key to encrypt */
    for (i = 0U; i < 4U; i++)
    {
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }
    /* Wait for CCF flag to be raised */
    tickstart = HAL_GetTick();
    while (HAL_IS_BIT_CLR(hcryp->Instance->ISR, AES_ISR_CCF))
    {
      /* Check for the Timeout */
      if (Timeout != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
        {
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);

          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY;
          __HAL_UNLOCK(hcryp);
          return HAL_ERROR;
        }
      }
    }

    /* Clear CCF Flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEAR_CCF);
  }

  /* Disable the CRYP peripheral clock */
  __HAL_CRYP_DISABLE(hcryp);

  /* Change the CRYP peripheral state */
  hcryp->State = HAL_CRYP_STATE_READY;
  __HAL_UNLOCK(hcryp);
  return HAL_OK;
}

/**
  * @brief  Key Encryption
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure
  * @param  Timeout specify Timeout value
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYPEx_KeyEncrypt(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t incount; /* Temporary CrypInCount Value */
  uint32_t i;
  uint32_t tickstart;
  uint32_t temp; /* Temporary CrypOutBuff */

  if (hcryp->Init.Algorithm != CRYP_AES_ECB)
  {
    /* Set the Initialization Vector */
    hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
    hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
    hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
  }

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  /* Set the phase */
  hcryp->Phase = CRYPEx_PHASE_PROCESS;

  if (hcryp->Init.KeySize == CRYP_KEYSIZE_128B)
  {
    incount = 4U;
  }
  else
  {
    incount = 8U;
  }
  while (hcryp->CrypInCount < incount)
  {
    for (i = 0U; i < 4U; i++)
    {
      hcryp->Instance->DINR  = *(uint32_t *)(hcryp->pCrypInBuffPtr + hcryp->CrypInCount);
      hcryp->CrypInCount++;
    }
    /* Wait for CCF flag to be raised */
    tickstart = HAL_GetTick();
    while (HAL_IS_BIT_CLR(hcryp->Instance->ISR, AES_ISR_CCF))
    {
      /* Check for the Timeout */
      if (Timeout != HAL_MAX_DELAY)
      {
        if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
        {
          /* Disable the CRYP peripheral clock */
          __HAL_CRYP_DISABLE(hcryp);

          /* Change state */
          hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
          hcryp->State = HAL_CRYP_STATE_READY;
          __HAL_UNLOCK(hcryp);
          return HAL_ERROR;
        }
      }
    }

    /* Clear CCF Flag */
    __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEAR_CCF);

    /* Read the output block from the output FIFO and put them in temporary buffer then
       get CrypOutBuff from temporary buffer */
    for (i = 0U; i < 4U; i++)
    {
      temp  = hcryp->Instance->DOUTR;
      *(uint32_t *)(hcryp->pCrypOutBuffPtr + hcryp->CrypOutCount) = temp;
      hcryp->CrypOutCount++;
    }
  }

  /* Disable the CRYP peripheral clock */
  __HAL_CRYP_DISABLE(hcryp);

  /* Change the CRYP peripheral state */
  hcryp->State = HAL_CRYP_STATE_READY;
  __HAL_UNLOCK(hcryp);
  return HAL_OK;
}
/**
  * @brief  Key Generation
  * @param  hcryp pointer to a CRYP_HandleTypeDef structure
  * @param  Timeout specify Timeout value
  * @retval HAL status
  */
static HAL_StatusTypeDef CRYPEx_KeyGeneration(CRYP_HandleTypeDef *hcryp, uint32_t Timeout)
{
  uint32_t tickstart;

  /* No swap, DATATYPE must be kept to 0x0.*/
  MODIFY_REG(hcryp->Instance->CR, AES_CR_DATATYPE, CRYP_NO_SWAP);

  /*Writes initialization vector in IV registers*/
  if (hcryp->Init.pInitVect != NULL)
  {
    /* Set the Initialization Vector*/
    hcryp->Instance->IVR3 = *(uint32_t *)(hcryp->Init.pInitVect);
    hcryp->Instance->IVR2 = *(uint32_t *)(hcryp->Init.pInitVect + 1U);
    hcryp->Instance->IVR1 = *(uint32_t *)(hcryp->Init.pInitVect + 2U);
    /* Keeping the two least significant bit of SAES_IVR0 to 00 */
    hcryp->Instance->IVR0 = *(uint32_t *)(hcryp->Init.pInitVect + 3U);
    hcryp->Instance->IVR0 &= 0xFFFFFFFCU ;
  }
  else
  {
    return HAL_ERROR;
  }

  /* Enable CRYP */
  __HAL_CRYP_ENABLE(hcryp);

  /* Wait for CCF flag to be raised */
  tickstart = HAL_GetTick();
  while (HAL_IS_BIT_CLR(hcryp->Instance->ISR, AES_ISR_CCF))
  {
    /* Check for the Timeout */
    if (Timeout != HAL_MAX_DELAY)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0U))
      {
        /* Disable the CRYP peripheral clock */
        __HAL_CRYP_DISABLE(hcryp);

        /* Change state */
        hcryp->ErrorCode |= HAL_CRYP_ERROR_TIMEOUT;
        hcryp->State = HAL_CRYP_STATE_READY;
        __HAL_UNLOCK(hcryp);
        return HAL_ERROR;
      }
    }
  }
  /* Clear CCF Flag */
  __HAL_CRYP_CLEAR_FLAG(hcryp, CRYP_CLEAR_CCF);

  /* Disable the CRYP peripheral clock */
  __HAL_CRYP_DISABLE(hcryp);

  /* Change the CRYP peripheral state */
  hcryp->State = HAL_CRYP_STATE_READY;
  __HAL_UNLOCK(hcryp);

  return HAL_OK;
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

#endif /* HAL_CRYP_MODULE_ENABLED */

#endif /* AES */
/**
  * @}
  */

/**
  * @}
  */
