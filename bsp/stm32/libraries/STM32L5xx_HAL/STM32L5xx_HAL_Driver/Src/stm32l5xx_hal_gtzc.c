/**
  ******************************************************************************
  * @file    stm32l5xx_hal_gtzc.c
  * @author  MCD Application Team
  * @brief   GTZC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of GTZC peripheral:
  *           + TZSC Initialization and Configuration functions
  *           + TZSC-MPCWM Initialization and Configuration functions
  *           + MPCBB Initialization and Configuration functions
  *           + TZSC, TZSC-MPCWM and MPCBB Lock functions
  *           + TZIC Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
                ##### GTZC main features #####
  ==============================================================================
  [..]
    (+) Global TrustZone Controller (GTZC) composed of three sub-blocks:
      (++) TZSC: TrustZone security controller
            This sub-block defines the secure/privileged state of master and slave
            peripherals. It also controls the secure state of subregions
            for the watermark memory peripheral controller (MPCWM).
      (++) MPCBB: Block-Based memory protection controller
            This sub-block defines the secure state of all blocks
            (256-byte pages) of the associated SRAM.
      (++) TZIC: TrustZone illegal access controller
            This sub-block gathers all illegal access events in the system and
            generates a secure interrupt towards NVIC.

    (+) These sub-blocks are used to configure TrustZone system security in
        a product having bus agents with programmable-security and privileged
        attributes (securable) such as:
      (++) on-chip RAM with programmable secure blocks (pages)
      (++) AHB and APB peripherals with programmable security and/or privilege access
      (++) AHB master granted as secure and/or privilege
      (++) off-chip memories with secure areas

  [..]
    (+) TZIC accessible only with secure privileged transactions.
    (+) Secure and non-secure access supported for privileged and unprivileged
        part of TZSC and MPCBB

  ==============================================================================
                         ##### How to use this driver #####
  ==============================================================================
  [..]
    The GTZC HAL driver can be used as follows:

    (#) Configure or get back securable peripherals attributes using
        HAL_GTZC_TZSC_ConfigPeriphAttributes() / HAL_GTZC_TZSC_GetConfigPeriphAttributes()

    (#) Configure or get back MPCWM memories attributes using
        HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes() / HAL_GTZC_TZSC_MPCWM_GetConfigMemAttributes()

    (#) Lock TZSC sub-block or get lock status using HAL_GTZC_TZSC_Lock() /
        HAL_GTZC_TZSC_GetLock()

    (#) Configure or get back MPCBB memories complete configuration using
        HAL_GTZC_MPCBB_ConfigMem() / HAL_GTZC_MPCBB_GetConfigMem()

    (#) Configure or get back MPCBB memories attributes using
        HAL_GTZC_MPCBB_ConfigMemAttributes() / HAL_GTZC_MPCBB_GetConfigMemAttributes()

    (#) Lock MPCBB configuration or get lock status using HAL_GTZC_MPCBB_Lock() /
        HAL_GTZC_MPCBB_GetLock()

    (#) Lock MPCBB super-blocks or get lock status using HAL_GTZC_MPCBB_LockConfig() /
        HAL_GTZC_MPCBB_GetLockConfig()

    (#) Illegal access detection can be configured through TZIC sub-block using
        following functions: HAL_GTZC_TZIC_DisableIT() / HAL_GTZC_TZIC_EnableIT()

    (#) Illegal access flags can be retrieved through HAL_GTZC_TZIC_GetFlag() and
        HAL_GTZC_TZIC_ClearFlag() functions

    (#) Illegal access interrupt service routines are served by HAL_GTZC_IRQHandler()
        and user can add his own code using HAL_GTZC_TZIC_Callback()

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal.h"

/** @addtogroup STM32L5xx_HAL_Driver
  * @{
  */

/** @defgroup GTZC GTZC
  * @brief GTZC HAL module driver
  * @{
  */

#ifdef HAL_GTZC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/** @defgroup GTZC_Private_Constants GTZC Private Constants
  * @{
  */

/* Definitions for GTZC_TZSC_MPCWM */
#define GTZC_TZSC_MPCWM1_MEM_SIZE      0x10000000U    /* 256MB max size */
#define GTZC_TZSC_MPCWM2_MEM_SIZE      0x10000000U    /* 256MB max size */
#define GTZC_TZSC_MPCWM3_MEM_SIZE      0x10000000U    /* 256MB max size */

/* Definitions for GTZC TZSC & TZIC ALL register values */
#define TZSC_SECCFGR1_ALL       (0xFFFFFFFFUL)
#if defined (STM32L562xx)
#define TZSC_SECCFGR2_ALL       (0x0007FFFFUL)
#else
#define TZSC_SECCFGR2_ALL       (0x00076FFFUL)
#endif /* STM32L562xx */
#define TZSC_PRIVCFGR1_ALL      (0xFFFFFFFFUL)
#if defined (STM32L562xx)
#define TZSC_PRIVCFGR2_ALL      (0x0007FFFFUL)
#else
#define TZSC_PRIVCFGR2_ALL      (0x00076FFFUL)
#endif /* STM32L562xx */
#define TZIC_IER1_ALL           (0xFFFFFFFFUL)
#if defined (STM32L562xx)
#define TZIC_IER2_ALL           (0x3FFFFFFFUL)
#else
#define TZIC_IER2_ALL           (0x3FFF6FFFUL)
#endif /* STM32L562xx */
#define TZIC_IER3_ALL           (0x000000FFUL)
#define TZIC_FCR1_ALL           (0xFFFFFFFFUL)
#if defined (STM32L562xx)
#define TZIC_FCR2_ALL           (0x3FFFFFFFUL)
#else
#define TZIC_FCR2_ALL           (0x3FFF6FFFUL)
#endif /* STM32L562xx */
#define TZIC_FCR3_ALL           (0x000000FFUL)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup GTZC_Private_Macros GTZC Private Macros
  * @{
  */

#define IS_ADDRESS_IN(mem, address)\
  (   (   ( (uint32_t)(address) >= (uint32_t)GTZC_BASE_ADDRESS_NS(mem) )                                \
          && ( (uint32_t)(address) < ((uint32_t)GTZC_BASE_ADDRESS_NS(mem) + (uint32_t)GTZC_MEM_SIZE(mem) ) ) )  \
      || (   ( (uint32_t)(address) >= (uint32_t)GTZC_BASE_ADDRESS_S(mem) )                                \
             && ( (uint32_t)(address) < ((uint32_t)GTZC_BASE_ADDRESS_S(mem) + (uint32_t)GTZC_MEM_SIZE(mem) ) ) ) )

#define IS_ADDRESS_IN_S(mem, address)\
  (   ( (uint32_t)(address) >= (uint32_t)GTZC_BASE_ADDRESS_S(mem) )                                \
      && ( (uint32_t)(address) < ((uint32_t)GTZC_BASE_ADDRESS_S(mem) + (uint32_t)GTZC_MEM_SIZE(mem) ) ) )

#define IS_ADDRESS_IN_NS(mem, address)\
  (   ( (uint32_t)(address) >= (uint32_t)GTZC_BASE_ADDRESS_NS(mem) )                                \
      && ( (uint32_t)(address) < ((uint32_t)GTZC_BASE_ADDRESS_NS(mem) + (uint32_t)GTZC_MEM_SIZE(mem) ) ) )

#define GTZC_BASE_ADDRESS(mem)\
  ( mem ## _BASE )

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup GTZC_Exported_Functions GTZC Exported Functions
  * @{
  */

/** @defgroup GTZC_Exported_Functions_Group1  TZSC Configuration functions
  * @brief    TZSC Configuration functions
  *
  @verbatim
  ==============================================================================
            ##### TZSC Configuration functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure TZSC
    TZSC is TrustZone Security Controller
@endverbatim
  * @{
  */

/**
  * @brief  Configure TZSC on a single peripheral or on all peripherals.
  * @note   Secure and non-secure attributes can only be set from the secure
  *         state when the system implements the security (TZEN=1).
  * @note   Privilege and non-privilege attributes can only be set from the
  *         privilege state when TZEN=0 or TZEN=1
  * @note   Security and privilege attributes can be set independently.
  * @note   Default state is non-secure and unprivileged access allowed.
  * @param  PeriphId Peripheral identifier
  *         This parameter can be a value of @ref GTZC_TZSC_TZIC_PeriphId.
  *         Use GTZC_PERIPH_ALL to select all peripherals.
  * @param  PeriphAttributes Peripheral attributes, see @ref GTZC_TZSC_PeriphAttributes.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_TZSC_ConfigPeriphAttributes(uint32_t PeriphId,
                                                       uint32_t PeriphAttributes)
{
  uint32_t register_address;

  /* check entry parameters */
  if ((PeriphAttributes > (GTZC_TZSC_PERIPH_SEC | GTZC_TZSC_PERIPH_PRIV))
      || (HAL_GTZC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZSC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U) && (HAL_GTZC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* special case where same attributes are applied to all peripherals */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    /* secure configuration */
    if ((PeriphAttributes & GTZC_TZSC_PERIPH_SEC) == GTZC_TZSC_PERIPH_SEC)
    {
      SET_BIT(GTZC_TZSC->SECCFGR1, TZSC_SECCFGR1_ALL);
      SET_BIT(GTZC_TZSC->SECCFGR2, TZSC_SECCFGR2_ALL);
    }
    else if ((PeriphAttributes & GTZC_TZSC_PERIPH_NSEC) == GTZC_TZSC_PERIPH_NSEC)
    {
      CLEAR_BIT(GTZC_TZSC->SECCFGR1, TZSC_SECCFGR1_ALL);
      CLEAR_BIT(GTZC_TZSC->SECCFGR2, TZSC_SECCFGR2_ALL);
    }
    else
    {
      /* do nothing */
    }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

    /* privilege configuration */
    if ((PeriphAttributes & GTZC_TZSC_PERIPH_PRIV) == GTZC_TZSC_PERIPH_PRIV)
    {
      SET_BIT(GTZC_TZSC->PRIVCFGR1, TZSC_PRIVCFGR1_ALL);
      SET_BIT(GTZC_TZSC->PRIVCFGR2, TZSC_PRIVCFGR2_ALL);
    }
    else if ((PeriphAttributes & GTZC_TZSC_PERIPH_NPRIV) == GTZC_TZSC_PERIPH_NPRIV)
    {
      CLEAR_BIT(GTZC_TZSC->PRIVCFGR1, TZSC_PRIVCFGR1_ALL);
      CLEAR_BIT(GTZC_TZSC->PRIVCFGR2, TZSC_PRIVCFGR2_ALL);
    }
    else
    {
      /* do nothing */
    }
  }
  else
  {
    /* common case where only one peripheral is configured */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    /* secure configuration */
    register_address = (uint32_t) &(GTZC_TZSC->SECCFGR1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    if ((PeriphAttributes & GTZC_TZSC_PERIPH_SEC) == GTZC_TZSC_PERIPH_SEC)
    {
      SET_BIT(*(__IO uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
    }
    else if ((PeriphAttributes & GTZC_TZSC_PERIPH_NSEC) == GTZC_TZSC_PERIPH_NSEC)
    {
      CLEAR_BIT(*(__IO uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
    }
    else
    {
      /* do nothing */
    }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

    /* privilege configuration */
    register_address = (uint32_t) &(GTZC_TZSC->PRIVCFGR1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    if ((PeriphAttributes & GTZC_TZSC_PERIPH_PRIV) == GTZC_TZSC_PERIPH_PRIV)
    {
      SET_BIT(*(__IO uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
    }
    else if ((PeriphAttributes & GTZC_TZSC_PERIPH_NPRIV) == GTZC_TZSC_PERIPH_NPRIV)
    {
      CLEAR_BIT(*(__IO uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
    }
    else
    {
      /* do nothing */
    }
  }
  return HAL_OK;
}

/**
  * @brief  Get TZSC configuration on a single peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_TZSC_TZIC_PeriphId.
  *         Use GTZC_PERIPH_ALL to select all peripherals.
  * @param  PeriphAttributes Peripheral attribute pointer.
  *         This parameter can be a value of @ref GTZC_TZSC_PeriphAttributes.
  *         If PeriphId target a single peripheral, pointer on a single element.
  *         If all peripherals selected (GTZC_PERIPH_ALL), pointer to an array of
  *         GTZC_TZSC_PERIPH_NUMBER elements is to be provided.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_TZSC_GetConfigPeriphAttributes(uint32_t PeriphId,
                                                          uint32_t *PeriphAttributes)
{
  uint32_t i;
  uint32_t reg_value;
  uint32_t register_address;

  /* check entry parameters */
  if ((PeriphAttributes == NULL)
      || (HAL_GTZC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZSC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U) && (HAL_GTZC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* get secure configuration: read each register and deploy each bit value
     * of corresponding index in the destination array
     */
    reg_value = READ_REG(GTZC_TZSC->SECCFGR1);
    for (i = 0U; i < 32U; i++)
    {
      if (((reg_value & (1UL << i)) >> i) != 0U)
      {
        PeriphAttributes[i] = GTZC_TZSC_PERIPH_SEC;
      }
      else
      {
        PeriphAttributes[i] = GTZC_TZSC_PERIPH_NSEC;
      }
    }

    reg_value = READ_REG(GTZC_TZSC->SECCFGR2);
    for (/*i = 32U*/; i < GTZC_TZSC_PERIPH_NUMBER; i++)
    {
      if (((reg_value & (1UL << (i - 32U))) >> (i - 32U)) != 0U)
      {
        PeriphAttributes[i] = GTZC_TZSC_PERIPH_SEC;
      }
      else
      {
        PeriphAttributes[i] = GTZC_TZSC_PERIPH_NSEC;
      }
    }

    /* get privilege configuration: read each register and deploy each bit value
     * of corresponding index in the destination array
     */
    reg_value = READ_REG(GTZC_TZSC->PRIVCFGR1);
    for (i = 0U; i < 32U; i++)
    {
      if (((reg_value & (1UL << i)) >> i) != 0U)
      {
        PeriphAttributes[i] |= GTZC_TZSC_PERIPH_PRIV;
      }
      else
      {
        PeriphAttributes[i] |= GTZC_TZSC_PERIPH_NPRIV;
      }
    }

    reg_value = READ_REG(GTZC_TZSC->PRIVCFGR2);
    for (/*i = 32U*/; i < GTZC_TZSC_PERIPH_NUMBER; i++)
    {
      if (((reg_value & (1UL << (i - 32U))) >> (i - 32U)) != 0U)
      {
        PeriphAttributes[i] |= GTZC_TZSC_PERIPH_PRIV;
      }
      else
      {
        PeriphAttributes[i] |= GTZC_TZSC_PERIPH_NPRIV;
      }
    }

  }
  else
  {
    /* common case where only one peripheral is configured */

    /* secure configuration */
    register_address = (uint32_t) &(GTZC_TZSC->SECCFGR1) + (4U * GTZC_GET_REG_INDEX(PeriphId));

    if (((READ_BIT(*(__IO uint32_t *)register_address,
                   1UL << GTZC_GET_PERIPH_POS(PeriphId))) >> GTZC_GET_PERIPH_POS(PeriphId))
        != 0U)
    {
      *PeriphAttributes = GTZC_TZSC_PERIPH_SEC;
    }
    else
    {
      *PeriphAttributes = GTZC_TZSC_PERIPH_NSEC;
    }

    /* privilege configuration */
    register_address = (uint32_t) &(GTZC_TZSC->PRIVCFGR1) + (4U * GTZC_GET_REG_INDEX(PeriphId));

    if (((READ_BIT(*(__IO uint32_t *)register_address,
                   1UL << GTZC_GET_PERIPH_POS(PeriphId))) >> GTZC_GET_PERIPH_POS(PeriphId))
        != 0U)
    {
      *PeriphAttributes |= GTZC_TZSC_PERIPH_PRIV;
    }
    else
    {
      *PeriphAttributes |= GTZC_TZSC_PERIPH_NPRIV;
    }
  }
  return HAL_OK;
}

/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @defgroup GTZC_Exported_Functions_Group2 MPCWM Configuration functions
  * @brief    MPCWM Configuration functions
  *
  @verbatim
  ==============================================================================
            ##### MPCWM Configuration functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure MPCWM
    MPCWM is Memory Protection Controller WaterMark
@endverbatim
  * @{
  */

/**
  * @brief  Configure a TZSC-MPCWM area.
  * @param  MemBaseAddress WM identifier.
  * @param  pMPCWM_Desc TZSC-MPCWM descriptor pointer.
  *         The structure description is available in @ref GTZC_Exported_Types.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes(uint32_t MemBaseAddress,
                                                          MPCWM_ConfigTypeDef *pMPCWM_Desc)
{
  uint32_t register_address;
  uint32_t reg_value;
  uint32_t size;
  uint32_t start_pos, start_msk;
  uint32_t length_pos, length_msk;

  /* check entry parameters */
  if ((pMPCWM_Desc->AreaId > GTZC_TZSC_MPCWM_ID2)
      || ((MemBaseAddress == FMC_BANK3) && (pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID2))
      || ((pMPCWM_Desc->Offset % GTZC_TZSC_MPCWM_GRANULARITY) != 0U)
      || ((pMPCWM_Desc->Length % GTZC_TZSC_MPCWM_GRANULARITY) != 0U))
  {
    return HAL_ERROR;
  }

  /* check descriptor content vs. memory capacity */
  switch (MemBaseAddress)
  {
    case OCTOSPI1_BASE:
      size = GTZC_TZSC_MPCWM1_MEM_SIZE;
      if (pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID1)
      {
        register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM1_NSWMR1);
        start_pos = GTZC_TZSC_MPCWM1_NSWMR1_NSWM1STRT_Pos;
        start_msk = GTZC_TZSC_MPCWM1_NSWMR1_NSWM1STRT_Msk;
        length_pos = GTZC_TZSC_MPCWM1_NSWMR1_NSWM1LGTH_Pos;
        length_msk = GTZC_TZSC_MPCWM1_NSWMR1_NSWM1LGTH_Msk;
      }
      else
      {
        /* Here pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID2
         * (Parameter already checked)
         */
        register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM1_NSWMR2);
        start_pos = GTZC_TZSC_MPCWM1_NSWMR2_NSWM2STRT_Pos;
        start_msk = GTZC_TZSC_MPCWM1_NSWMR2_NSWM2STRT_Msk;
        length_pos = GTZC_TZSC_MPCWM1_NSWMR2_NSWM2LGTH_Pos;
        length_msk = GTZC_TZSC_MPCWM1_NSWMR2_NSWM2LGTH_Msk;
      }
      break;
    case FMC_BANK1:
      size = GTZC_TZSC_MPCWM1_MEM_SIZE;
      if (pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID1)
      {
        register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM2_NSWMR1);
        start_pos = GTZC_TZSC_MPCWM2_NSWMR1_NSWM1STRT_Pos;
        start_msk = GTZC_TZSC_MPCWM2_NSWMR1_NSWM1STRT_Msk;
        length_pos = GTZC_TZSC_MPCWM2_NSWMR1_NSWM1LGTH_Pos;
        length_msk = GTZC_TZSC_MPCWM2_NSWMR1_NSWM1LGTH_Msk;
      }
      else
      {
        /* Here pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID2
         * (Parameter already checked)
         */
        register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM2_NSWMR2);
        start_pos = GTZC_TZSC_MPCWM2_NSWMR2_NSWM2STRT_Pos;
        start_msk = GTZC_TZSC_MPCWM2_NSWMR2_NSWM2STRT_Msk;
        length_pos = GTZC_TZSC_MPCWM2_NSWMR2_NSWM2LGTH_Pos;
        length_msk = GTZC_TZSC_MPCWM2_NSWMR2_NSWM2LGTH_Msk;
      }
      break;
    case FMC_BANK3:
      /* Here pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID1
       * (Parameter already checked)
       */
      size = GTZC_TZSC_MPCWM3_MEM_SIZE;
      register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM3_NSWMR1);
      start_pos = GTZC_TZSC_MPCWM3_NSWMR1_NSWM1STRT_Pos;
      start_msk = GTZC_TZSC_MPCWM3_NSWMR1_NSWM1STRT_Msk;
      length_pos = GTZC_TZSC_MPCWM3_NSWMR1_NSWM1LGTH_Pos;
      length_msk = GTZC_TZSC_MPCWM3_NSWMR1_NSWM1LGTH_Msk;
      break;
    default:
      return HAL_ERROR;
      break;
  }

  if ((pMPCWM_Desc->Offset > size)
      || ((pMPCWM_Desc->Offset + pMPCWM_Desc->Length) > size))
  {
    return HAL_ERROR;
  }

  /* write descriptor value */
  reg_value = ((pMPCWM_Desc->Offset / GTZC_TZSC_MPCWM_GRANULARITY) << start_pos) & start_msk;
  reg_value |= ((pMPCWM_Desc->Length / GTZC_TZSC_MPCWM_GRANULARITY) << length_pos) & length_msk;
  MODIFY_REG(*(__IO uint32_t *)register_address, start_msk | length_msk, reg_value);

  return HAL_OK;
}

/**
  * @brief  Get a TZSC-MPCWM area configuration.
  * @param  MemBaseAddress WM identifier.
  * @param  pMPCWM_Desc pointer to a TZSC-MPCWM descriptor.
  *         The structure description is available in @ref GTZC_Exported_Types.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_GetConfigMemAttributes(uint32_t MemBaseAddress,
                                                             MPCWM_ConfigTypeDef *pMPCWM_Desc)
{
  uint32_t register_address;
  uint32_t reg_value;
  uint32_t start_pos, start_msk;
  uint32_t length_pos, length_msk;

  /* firstly take care of the first area, present on all MPCWM sub-blocks */
  switch (MemBaseAddress)
  {
    case OCTOSPI1_BASE:
      register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM1_NSWMR1);
      start_pos = GTZC_TZSC_MPCWM1_NSWMR1_NSWM1STRT_Pos;
      start_msk = GTZC_TZSC_MPCWM1_NSWMR1_NSWM1STRT_Msk;
      length_pos = GTZC_TZSC_MPCWM1_NSWMR1_NSWM1LGTH_Pos;
      length_msk = GTZC_TZSC_MPCWM1_NSWMR1_NSWM1LGTH_Msk;
      break;
    case FMC_BANK1:
      register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM2_NSWMR1);
      start_pos = GTZC_TZSC_MPCWM2_NSWMR1_NSWM1STRT_Pos;
      start_msk = GTZC_TZSC_MPCWM2_NSWMR1_NSWM1STRT_Msk;
      length_pos = GTZC_TZSC_MPCWM2_NSWMR1_NSWM1LGTH_Pos;
      length_msk = GTZC_TZSC_MPCWM2_NSWMR1_NSWM1LGTH_Msk;
      break;
    case FMC_BANK3:
      register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM3_NSWMR1);
      start_pos = GTZC_TZSC_MPCWM3_NSWMR1_NSWM1STRT_Pos;
      start_msk = GTZC_TZSC_MPCWM3_NSWMR1_NSWM1STRT_Msk;
      length_pos = GTZC_TZSC_MPCWM3_NSWMR1_NSWM1LGTH_Pos;
      length_msk = GTZC_TZSC_MPCWM3_NSWMR1_NSWM1LGTH_Msk;
      break;
    default:
      return HAL_ERROR;
      break;
  }

  /* read register and update the descriptor for first area*/
  reg_value = READ_REG(*(__IO uint32_t *)register_address);
  pMPCWM_Desc[0].AreaId = GTZC_TZSC_MPCWM_ID1;
  pMPCWM_Desc[0].Offset = ((reg_value & start_msk) >> start_pos) * GTZC_TZSC_MPCWM_GRANULARITY;
  pMPCWM_Desc[0].Length = ((reg_value & length_msk) >> length_pos) * GTZC_TZSC_MPCWM_GRANULARITY;

  if (MemBaseAddress != FMC_BANK3)
  {
    /* Here MemBaseAddress = OCTOSPI1_BASE
     * or FMC_BANK1 (already tested)
     * Now take care of the second area, present on these sub-blocks
     */
    switch (MemBaseAddress)
    {
      case OCTOSPI1_BASE:
        register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM1_NSWMR2);
        start_pos = GTZC_TZSC_MPCWM1_NSWMR2_NSWM2STRT_Pos;
        start_msk = GTZC_TZSC_MPCWM1_NSWMR2_NSWM2STRT_Msk;
        length_pos = GTZC_TZSC_MPCWM1_NSWMR2_NSWM2LGTH_Pos;
        length_msk = GTZC_TZSC_MPCWM1_NSWMR2_NSWM2LGTH_Msk;
        break;
      case FMC_BANK1:
        register_address = (uint32_t) &(GTZC_TZSC_S->MPCWM2_NSWMR2);
        start_pos = GTZC_TZSC_MPCWM2_NSWMR2_NSWM2STRT_Pos;
        start_msk = GTZC_TZSC_MPCWM2_NSWMR2_NSWM2STRT_Msk;
        length_pos = GTZC_TZSC_MPCWM2_NSWMR2_NSWM2LGTH_Pos;
        length_msk = GTZC_TZSC_MPCWM2_NSWMR2_NSWM2LGTH_Msk;
        break;
      default:
        return HAL_ERROR;
        break;
    }

    /* read register and update the descriptor for second area*/
    reg_value = READ_REG(*(__IO uint32_t *)register_address);
    pMPCWM_Desc[1].AreaId = GTZC_TZSC_MPCWM_ID2;
    pMPCWM_Desc[1].Offset = ((reg_value & start_msk) >> start_pos) * GTZC_TZSC_MPCWM_GRANULARITY;
    pMPCWM_Desc[1].Length = ((reg_value & length_msk) >> length_pos) * GTZC_TZSC_MPCWM_GRANULARITY;
  }

  return HAL_OK;
}

/**
  * @}
  */

#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/** @defgroup GTZC_Exported_Functions_Group3 TZSC and TZSC-MPCWM Lock functions
  * @brief    TZSC and TZSC-MPCWM Lock functions
  *
  @verbatim
  ==============================================================================
            ##### TZSC and TZSC-MPCWM Lock functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to manage the common TZSC and
    TZSC-MPCWM lock. It includes lock enable, and current value read.
    TZSC is TrustZone Security Controller
    MPCWM is Memory Protection Controller WaterMark
@endverbatim
  * @{
  */

/**
  * @brief  Lock TZSC and TZSC-MPCWM configuration.
  * @param  TZSC_Instance TZSC sub-block instance.
  */
#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

void HAL_GTZC_TZSC_Lock(GTZC_TZSC_TypeDef *TZSC_Instance)
{
  SET_BIT(TZSC_Instance->CR, GTZC_TZSC_CR_LCK_Msk);
}

#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @brief  Get TZSC and TZSC-MPCWM configuration lock state.
  * @param  TZSC_Instance TZSC sub-block instance.
  * @retval Lock State (GTZC_TZSC_LOCK_OFF or GTZC_TZSC_LOCK_ON)
  */
uint32_t HAL_GTZC_TZSC_GetLock(GTZC_TZSC_TypeDef *TZSC_Instance)
{
  return READ_BIT(TZSC_Instance->CR, GTZC_TZSC_CR_LCK_Msk);
}

/**
  * @}
  */

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @defgroup GTZC_Exported_Functions_Group4 MPCBB Configuration functions
  * @brief    MPCBB Configuration functions
  *
  @verbatim
  ==============================================================================
            ##### MPCBB Configuration functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure MPCBB
    MPCBB is  Memory Protection Controller Block Base
@endverbatim
  * @{
  */

/**
  * @brief  Set a complete MPCBB configuration on the SRAM passed as parameter.
  * @param  MemBaseAddress MPCBB identifier.
  * @param  pMPCBB_desc pointer to MPCBB descriptor.
  *         The structure description is available in @ref GTZC_Exported_Types.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_ConfigMem(uint32_t MemBaseAddress,
                                           MPCBB_ConfigTypeDef *pMPCBB_desc)
{
  GTZC_MPCBB_TypeDef *mpcbb_ptr;
  uint32_t reg_value;
  uint32_t mem_size;
  uint32_t size_mask;
  uint32_t size_in_superblocks;
  uint32_t i;

  /* check entry parameters */
  if ((!(IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
       &&  !(IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress)))
      || ((pMPCBB_desc->SecureRWIllegalMode != GTZC_MPCBB_SRWILADIS_ENABLE)
          && (pMPCBB_desc->SecureRWIllegalMode != GTZC_MPCBB_SRWILADIS_DISABLE))
      || ((pMPCBB_desc->InvertSecureState != GTZC_MPCBB_INVSECSTATE_NOT_INVERTED)
          && (pMPCBB_desc->InvertSecureState != GTZC_MPCBB_INVSECSTATE_INVERTED)))
  {
    return HAL_ERROR;
  }

  /* write InvertSecureState and SecureRWIllegalMode properties */
  /* assume their Position/Mask is identical for all sub-blocks */
  reg_value = pMPCBB_desc->InvertSecureState;
  reg_value |= pMPCBB_desc->SecureRWIllegalMode;
  if (IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
  {
    mpcbb_ptr = GTZC_MPCBB1_S;
    mem_size = GTZC_MEM_SIZE(SRAM1);
  }
  else
  {
    /* Here MemBaseAddress is inside SRAM2 (already tested) */
    mpcbb_ptr = GTZC_MPCBB2_S;
    mem_size = GTZC_MEM_SIZE(SRAM2);
  }

  /* write configuration and lock register information */
  MODIFY_REG(mpcbb_ptr->CR,
             GTZC_MPCBB_CR_INVSECSTATE_Msk | GTZC_MPCBB_CR_SRWILADIS_Msk, reg_value);
  size_mask = (1UL << (mem_size / GTZC_MPCBB_SUPERBLOCK_SIZE)) - 1U;
  /* limitation: code not portable with memory > 256K */
  MODIFY_REG(mpcbb_ptr->LCKVTR1, size_mask, pMPCBB_desc->AttributeConfig.MPCBB_LockConfig_array[0]);

  /* write vector register information */
  size_in_superblocks = (mem_size / GTZC_MPCBB_SUPERBLOCK_SIZE);
  for (i = 0U; i < size_in_superblocks; i++)
  {
    WRITE_REG(mpcbb_ptr->VCTR[i],
              pMPCBB_desc->AttributeConfig.MPCBB_SecConfig_array[i]);
  }

  return HAL_OK;
}

/**
  * @brief  Get a complete MPCBB configuration on the SRAM passed as parameter.
  * @param  MemBaseAddress MPCBB identifier.
  * @param  pMPCBB_desc pointer to a MPCBB descriptor.
  *         The structure description is available in @ref GTZC_Exported_Types.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetConfigMem(uint32_t MemBaseAddress,
                                              MPCBB_ConfigTypeDef *pMPCBB_desc)
{
  GTZC_MPCBB_TypeDef *mpcbb_ptr;
  uint32_t reg_value;
  uint32_t mem_size;
  uint32_t size_mask;
  uint32_t size_in_superblocks;
  uint32_t i;

  /* check entry parameters */
  if (!(IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
      && !(IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress)))
  {
    return HAL_ERROR;
  }

  /* read InvertSecureState and SecureRWIllegalMode properties */
  /* assume their Position/Mask is identical for all sub-blocks */
  if (IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
  {
    mpcbb_ptr = GTZC_MPCBB1_S;
    mem_size = GTZC_MEM_SIZE(SRAM1);
  }
  else
  {
    mpcbb_ptr = GTZC_MPCBB2_S;
    mem_size = GTZC_MEM_SIZE(SRAM2);
  }

  /* read configuration and lock register information */
  reg_value = READ_REG(mpcbb_ptr->CR);
  pMPCBB_desc->InvertSecureState = (reg_value & GTZC_MPCBB_CR_INVSECSTATE_Msk);
  pMPCBB_desc->SecureRWIllegalMode = (reg_value & GTZC_MPCBB_CR_SRWILADIS_Msk);
  size_mask = (1UL << (mem_size / GTZC_MPCBB_SUPERBLOCK_SIZE)) - 1U;
  /* limitation: code not portable with memory > 256K */
  pMPCBB_desc->AttributeConfig.MPCBB_LockConfig_array[0] = READ_REG(mpcbb_ptr->LCKVTR1)& size_mask;

  /* read vector register information */
  size_in_superblocks = (mem_size / GTZC_MPCBB_SUPERBLOCK_SIZE);
  for (i = 0U; i < size_in_superblocks; i++)
  {
    pMPCBB_desc->AttributeConfig.MPCBB_SecConfig_array[i] = mpcbb_ptr->VCTR[i];
  }

  return HAL_OK;
}

/**
  * @brief  Set a MPCBB attribute configuration on the SRAM passed as parameter
  *         for a number of blocks.
  * @param  MemAddress MPCBB identifier, and start block to configure
  *         (must be 256 Bytes aligned).
  * @param  NbBlocks Number of blocks to configure.
  * @param  pMemAttributes pointer to an array (containing "NbBlocks" elements),
  *         with each element must be GTZC_MCPBB_BLOCK_NSEC or GTZC_MCPBB_BLOCK_SEC.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_ConfigMemAttributes(uint32_t MemAddress,
                                                     uint32_t NbBlocks,
                                                     uint32_t *pMemAttributes)
{
  GTZC_MPCBB_TypeDef *mpcbb_ptr;
  uint32_t base_address, end_address;
  uint32_t block_start, offset_reg_start, offset_bit_start;
  uint32_t i;

  /* firstly check that MemAddress is well 256 Bytes aligned */
  if ((MemAddress % GTZC_MPCBB_BLOCK_SIZE) != 0U)
  {
    return HAL_ERROR;
  }

  /* check entry parameters and deduce physical base address */
  end_address = MemAddress + (NbBlocks * GTZC_MPCBB_BLOCK_SIZE) - 1U;
  if (((IS_ADDRESS_IN_NS(SRAM1, MemAddress))
       && (IS_ADDRESS_IN_NS(SRAM1, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB1_S;
    base_address = SRAM1_BASE_NS;
  }
  else if (((IS_ADDRESS_IN_S(SRAM1, MemAddress))
            && (IS_ADDRESS_IN_S(SRAM1, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB1_S;
    base_address = SRAM1_BASE_S;
  }
  else if (((IS_ADDRESS_IN_NS(SRAM2, MemAddress))
            && (IS_ADDRESS_IN_NS(SRAM2, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB2_S;
    base_address = SRAM2_BASE_NS;
  }
  else if (((IS_ADDRESS_IN_S(SRAM2, MemAddress))
            && (IS_ADDRESS_IN_S(SRAM2, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB2_S;
    base_address = SRAM2_BASE_S;
  }
  else
  {
    return HAL_ERROR;
  }

  /* get start coordinates of the configuration */
  block_start = (MemAddress - base_address) / GTZC_MPCBB_BLOCK_SIZE;
  offset_reg_start = block_start / 32U;
  offset_bit_start = block_start % 32U;

  for (i = 0U; i < NbBlocks; i++)
  {
    if (pMemAttributes[i] == GTZC_MCPBB_BLOCK_SEC)
    {
      SET_BIT(mpcbb_ptr->VCTR[offset_reg_start],
              1UL << (offset_bit_start % 32U));
    }
    else if (pMemAttributes[i] == GTZC_MCPBB_BLOCK_NSEC)
    {
      CLEAR_BIT(mpcbb_ptr->VCTR[offset_reg_start],
                1UL << (offset_bit_start % 32U));
    }
    else
    {
      break;
    }

    offset_bit_start++;
    if (offset_bit_start == 32U)
    {
      offset_bit_start = 0U;
      offset_reg_start++;
    }
  }

  /* an unexpected value in pMemAttributes array leads to error status */
  if (i != NbBlocks)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Get a MPCBB attribute configuration on the SRAM passed as parameter
  *         for a number of blocks.
  * @param  MemAddress MPCBB identifier, and start block to get configuration
  *         (must be 256 Bytes aligned).
  * @param  NbBlocks Number of blocks to get configuration.
  * @param  pMemAttributes pointer to an array (containing "NbBlocks" elements),
  *         with each element will be GTZC_MCPBB_BLOCK_NSEC or GTZC_MCPBB_BLOCK_SEC.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetConfigMemAttributes(uint32_t MemAddress,
                                                        uint32_t NbBlocks,
                                                        uint32_t *pMemAttributes)
{
  GTZC_MPCBB_TypeDef *mpcbb_ptr;
  uint32_t base_address, end_address;
  uint32_t block_start, offset_reg_start, offset_bit_start;
  uint32_t i;

  /* firstly check that MemAddress is well 256 Bytes aligned */
  if ((MemAddress % GTZC_MPCBB_BLOCK_SIZE) != 0U)
  {
    return HAL_ERROR;
  }

  /* check entry parameters and deduce physical base address */
  end_address = MemAddress + (NbBlocks * GTZC_MPCBB_BLOCK_SIZE) - 1U;
  if ((IS_ADDRESS_IN_NS(SRAM1, MemAddress))
      && (IS_ADDRESS_IN_NS(SRAM1, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB1_S;
    base_address = SRAM1_BASE_NS;
  }
  else if ((IS_ADDRESS_IN_S(SRAM1, MemAddress))
           && (IS_ADDRESS_IN_S(SRAM1, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB1_S;
    base_address = SRAM1_BASE_S;
  }
  else if ((IS_ADDRESS_IN_NS(SRAM2, MemAddress))
           && (IS_ADDRESS_IN_NS(SRAM2, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB2_S;
    base_address = SRAM2_BASE_NS;
  }
  else if ((IS_ADDRESS_IN_S(SRAM2, MemAddress))
           && (IS_ADDRESS_IN_S(SRAM2, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB2_S;
    base_address = SRAM2_BASE_S;
  }
  else
  {
    return HAL_ERROR;
  }

  /* get start coordinates of the configuration */
  block_start = (MemAddress - base_address) / GTZC_MPCBB_BLOCK_SIZE;
  offset_reg_start = block_start / 32U;
  offset_bit_start = block_start % 32U;

  for (i = 0U; i < NbBlocks; i++)
  {
    pMemAttributes[i] = READ_BIT(mpcbb_ptr->VCTR[offset_reg_start],
                                 1UL << (offset_bit_start % 32U))
                        >> (offset_bit_start % 32U);

    offset_bit_start++;
    if (offset_bit_start == 32U)
    {
      offset_bit_start = 0U;
      offset_reg_start++;
    }
  }

  return HAL_OK;
}

/**
  * @brief  Lock MPCBB super-blocks on the SRAM passed as parameter.
  * @param  MemAddress MPCBB identifier, and start super-block to configure
  *         (must be 8KBytes aligned).
  * @param  NbSuperBlocks Number of super-blocks to configure.
  * @param  pLockAttributes pointer to an array (containing "NbSuperBlocks" elements),
  *         with for each element:
  *         value 0 super-block is unlocked, value 1 super-block is locked
  *         (corresponds to GTZC_MCPBB_SUPERBLOCK_UNLOCKED and
  *         GTZC_MCPBB_SUPERBLOCK_LOCKED values).
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_LockConfig(uint32_t MemAddress,
                                            uint32_t NbSuperBlocks,
                                            uint32_t *pLockAttributes)
{
  __IO uint32_t *reg_mpcbb;
  uint32_t base_address;
  uint32_t superblock_start, offset_bit_start;
  uint32_t i;

  /* firstly check that MemAddress is well 8KBytes aligned */
  if ((MemAddress % GTZC_MPCBB_SUPERBLOCK_SIZE) != 0U)
  {
    return HAL_ERROR;
  }

  /* check entry parameters */
  if ((IS_ADDRESS_IN(SRAM1, MemAddress))
      && (IS_ADDRESS_IN(SRAM1, (MemAddress
                                + (NbSuperBlocks * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM1);
    /* limitation: code not portable with memory > 256K */
    reg_mpcbb = (__IO uint32_t *)&GTZC_MPCBB1_S->LCKVTR1;
  }
  else if ((IS_ADDRESS_IN(SRAM2, MemAddress))
           && (IS_ADDRESS_IN(SRAM2, (MemAddress
                                     + (NbSuperBlocks * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                     - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM2);
    /* limitation: code not portable with memory > 256K */
    reg_mpcbb = (__IO uint32_t *)&GTZC_MPCBB2_S->LCKVTR1;
  }
  else
  {
    return HAL_ERROR;
  }

  /* get start coordinates of the configuration */
  superblock_start = (MemAddress - base_address) / GTZC_MPCBB_SUPERBLOCK_SIZE;
  offset_bit_start = superblock_start % 32U;

  for (i = 0U; i < NbSuperBlocks; i++)
  {
    if (pLockAttributes[i] == GTZC_MCPBB_SUPERBLOCK_LOCKED)
    {
      SET_BIT(*reg_mpcbb, 1UL << (offset_bit_start % 32U));
    }
    else if (pLockAttributes[i] == GTZC_MCPBB_SUPERBLOCK_UNLOCKED)
    {
      CLEAR_BIT(*reg_mpcbb, 1UL << (offset_bit_start % 32U));
    }
    else
    {
      break;
    }

    offset_bit_start++;
  }

  /* an unexpected value in pLockAttributes array leads to an error status */
  if (i != NbSuperBlocks)
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Get MPCBB super-blocks lock configuration on the SRAM passed as parameter.
  * @param  MemAddress MPCBB identifier, and start super-block to get
  *         configuration (must be 8KBytes aligned).
  * @param  NbSuperBlocks Number of super-blocks to get configuration.
  * @param  pLockAttributes pointer to an array (size is NbSuperBlocks),
  *         with for each element:
  *         value 0 super-block is unlocked, value 1 super-block is locked
  *         (corresponds to GTZC_MCPBB_SUPERBLOCK_UNLOCKED and
  *         GTZC_MCPBB_SUPERBLOCK_LOCKED values).
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetLockConfig(uint32_t MemAddress,
                                               uint32_t NbSuperBlocks,
                                               uint32_t *pLockAttributes)
{
  uint32_t reg_mpcbb;
  uint32_t base_address;
  uint32_t superblock_start, offset_bit_start;
  uint32_t i;

  /* firstly check that MemAddress is well 8KBytes aligned */
  if ((MemAddress % GTZC_MPCBB_SUPERBLOCK_SIZE) != 0U)
  {
    return HAL_ERROR;
  }

  /* check entry parameters */
  if ((IS_ADDRESS_IN(SRAM1, MemAddress))
      && (IS_ADDRESS_IN(SRAM1, (MemAddress
                                + (NbSuperBlocks * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM1);
    /* limitation: code not portable with memory > 256K */
    reg_mpcbb = GTZC_MPCBB1_S->LCKVTR1;
  }
  else if ((IS_ADDRESS_IN(SRAM2, MemAddress))
           && (IS_ADDRESS_IN(SRAM2, (MemAddress
                                     + (NbSuperBlocks * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                     - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM2);
    /* limitation: code not portable with memory > 256K */
    reg_mpcbb = GTZC_MPCBB2_S->LCKVTR1;
  }
  else
  {
    return HAL_ERROR;
  }

  /* get start coordinates of the configuration */
  superblock_start = (MemAddress - base_address) / GTZC_MPCBB_SUPERBLOCK_SIZE;
  offset_bit_start = superblock_start % 32U;

  for (i = 0U; i < NbSuperBlocks; i++)
  {
    pLockAttributes[i] = (reg_mpcbb & (1UL << (offset_bit_start % 32U)))
                         >> (offset_bit_start % 32U);
    offset_bit_start++;
  }

  return HAL_OK;
}

/**
  * @brief  Lock a MPCBB configuration on the SRAM base address passed as parameter.
  * @param  MemBaseAddress MPCBB identifier.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_Lock(uint32_t MemBaseAddress)
{
  /* check entry parameters */
  if (IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
  {
    SET_BIT(GTZC_MPCBB1_S->CR, GTZC_MPCBB_CR_LCK_Msk);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress))
  {
    SET_BIT(GTZC_MPCBB2_S->CR, GTZC_MPCBB_CR_LCK_Msk);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @brief  Get MPCBB configuration lock state on the SRAM base address passed as parameter.
  * @param  MemBaseAddress MPCBB identifier.
  * @param  pLockState pointer to Lock State (GTZC_MCPBB_LOCK_OFF or GTZC_MCPBB_LOCK_ON).
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetLock(uint32_t MemBaseAddress,
                                         uint32_t *pLockState)
{
  /* check entry parameters */
  if (IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
  {
    *pLockState = READ_BIT(GTZC_MPCBB1_S->CR, GTZC_MPCBB_CR_LCK_Msk);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress))
  {
    *pLockState = READ_BIT(GTZC_MPCBB2_S->CR, GTZC_MPCBB_CR_LCK_Msk);
  }
  else
  {
    return HAL_ERROR;
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group5 TZIC Configuration and Control functions
  * @brief    TZIC Configuration and Control functions
  *
  @verbatim
  ==============================================================================
            ##### TZIC Configuration and Control functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to configure and control TZIC
    TZIC is Trust Zone Interrupt Controller
@endverbatim
  * @{
  */

/**
  * @brief  Disable the interrupt associated to a single TZIC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_TZSC_TZIC_PeriphId.
  *         Use GTZC_PERIPH_ALL to select all peripherals.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_TZIC_DisableIT(uint32_t PeriphId)
{
  uint32_t register_address;

  /* check entry parameters */
  if ((HAL_GTZC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZIC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U) && (HAL_GTZC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* same configuration is applied to all peripherals */
    WRITE_REG(GTZC_TZIC->IER1, 0U);
    WRITE_REG(GTZC_TZIC->IER2, 0U);
    WRITE_REG(GTZC_TZIC->IER3, 0U);
  }
  else
  {
    /* common case where only one peripheral is configured */
    register_address = (uint32_t) &(GTZC_TZIC->IER1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    CLEAR_BIT(*(__IO uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
  }

  return HAL_OK;
}

/**
  * @brief  Enable the interrupt associated to a single TZIC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_TZSC_TZIC_PeriphId.
  *         Use GTZC_PERIPH_ALL to select all peripherals.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_TZIC_EnableIT(uint32_t PeriphId)
{
  uint32_t register_address;

  /* check entry parameters */
  if ((HAL_GTZC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZIC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U) && (HAL_GTZC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* same configuration is applied to all peripherals */
    WRITE_REG(GTZC_TZIC->IER1, TZIC_IER1_ALL);
    WRITE_REG(GTZC_TZIC->IER2, TZIC_IER2_ALL);
    WRITE_REG(GTZC_TZIC->IER3, TZIC_IER3_ALL);
  }
  else
  {
    /* common case where only one peripheral is configured */
    register_address = (uint32_t) &(GTZC_TZIC->IER1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    SET_BIT(*(__IO uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
  }

  return HAL_OK;
}

/**
  * @brief  Get TZIC flag on a single TZIC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_TZSC_TZIC_PeriphId.
  *         Use GTZC_PERIPH_ALL to select all peripherals.
  * @param  pFlag Pointer to the flags.
  *         If PeriphId target a single peripheral, pointer on a single element.
  *         If all peripherals selected (GTZC_PERIPH_ALL), pointer to an array
  *         of GTZC_TZIC_PERIPH_NUMBER elements.
  *         Element content is either GTZC_TZIC_NO_ILA_EVENT
  *         or GTZC_TZSC_ILA_EVENT_PENDING.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_GTZC_TZIC_GetFlag(uint32_t PeriphId, uint32_t *pFlag)
{
  uint32_t i;
  uint32_t reg_value;
  uint32_t register_address;

  /* check entry parameters */
  if ((HAL_GTZC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZIC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U) && (HAL_GTZC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* special case where it is applied to all peripherals */
    reg_value = READ_REG(GTZC_TZIC->SR1);
    for (i = 0U; i < 32U; i++)
    {
      pFlag[i] = (reg_value & (1UL << i)) >> i;
    }

    reg_value = READ_REG(GTZC_TZIC->SR2);
    for (/*i = 32U*/; i < 64U; i++)
    {
      pFlag[i] = (reg_value & (1UL << (i - 32U))) >> (i - 32U);
    }

    reg_value = READ_REG(GTZC_TZIC->SR3);
    for (/*i = 64U*/; i < GTZC_TZIC_PERIPH_NUMBER; i++)
    {
      pFlag[i] = (reg_value & (1UL << (i - 64U))) >> (i - 64U);
    }
  }
  else
  {
    /* common case where only one peripheral is concerned */
    register_address = (uint32_t) &(GTZC_TZIC->SR1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    *pFlag = READ_BIT(*(__IO uint32_t *)register_address,
                      1UL << GTZC_GET_PERIPH_POS(PeriphId)) >> GTZC_GET_PERIPH_POS(PeriphId);
  }

  return HAL_OK;
}

/**
  * @brief  Clear TZIC flag on a single TZIC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_TZSC_TZIC_PeriphId.
  *         Use GTZC_PERIPH_ALL to select all peripherals.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_TZIC_ClearFlag(uint32_t PeriphId)
{
  uint32_t register_address;

  /* check entry parameters */
  if ((HAL_GTZC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZIC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U) && (HAL_GTZC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* same configuration is applied to all peripherals */
    WRITE_REG(GTZC_TZIC->FCR1, TZIC_FCR1_ALL);
    WRITE_REG(GTZC_TZIC->FCR2, TZIC_FCR2_ALL);
    WRITE_REG(GTZC_TZIC->FCR3, TZIC_FCR3_ALL);
  }
  else
  {
    /* common case where only one peripheral is configured */
    register_address = (uint32_t) &(GTZC_TZIC->FCR1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    SET_BIT(*(__IO uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group6 IRQ related functions
  * @brief    IRQ related functions
  *
  @verbatim
  ==============================================================================
            ##### TZIC IRQ Handler and Callback functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to treat ISR and provide user callback
  @endverbatim
  * @{
  */

/**
  * @brief  This function handles GTZC interrupt request.
  * @retval None.
  */
void HAL_GTZC_IRQHandler(void)
{
  uint32_t position;
  uint32_t flag;
  uint32_t ier_itsources;
  uint32_t sr_flags;

  /* Get current IT Flags and IT sources value on 1st register */
  ier_itsources = READ_REG(GTZC_TZIC->IER1);
  sr_flags      = READ_REG(GTZC_TZIC->SR1);

  /* Get Mask interrupt and then clear them */
  flag = ier_itsources & sr_flags;
  if (flag != 0U)
  {
    WRITE_REG(GTZC_TZIC->FCR1, flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0U;
    while ((flag >> position) != 0U)
    {
      if ((flag & (1UL << position)) != 0U)
      {
        HAL_GTZC_TZIC_Callback(GTZC_PERIPH_REG1 | position);
      }

      /* Position bit to be updated */
      position++;
    }
  }

  /* Get current IT Flags and IT sources value on 2nd register */
  ier_itsources = READ_REG(GTZC_TZIC->IER2);
  sr_flags      = READ_REG(GTZC_TZIC->SR2);

  /* Get Mask interrupt and then clear them */
  flag = ier_itsources & sr_flags;
  if (flag != 0U)
  {
    WRITE_REG(GTZC_TZIC->FCR2, flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0U;
    while ((flag >> position) != 0U)
    {
      if ((flag & (1UL << position)) != 0U)
      {
        HAL_GTZC_TZIC_Callback(GTZC_PERIPH_REG2 | position);
      }

      /* Position bit to be updated */
      position++;
    }
  }

  /* Get current IT Flags and IT sources value on 3rd register */
  ier_itsources = READ_REG(GTZC_TZIC->IER3);
  sr_flags      = READ_REG(GTZC_TZIC->SR3);

  /* Get Mask interrupt and then clear them */
  flag = ier_itsources & sr_flags;
  if (flag != 0U)
  {
    WRITE_REG(GTZC_TZIC->FCR3, flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0U;
    while ((flag >> position) != 0U)
    {
      if ((flag & (1UL << position)) != 0U)
      {
        HAL_GTZC_TZIC_Callback(GTZC_PERIPH_REG3 | position);
      }

      /* Position bit to be updated */
      position++;
    }
  }
}

/**
  * @brief  GTZC TZIC sub-block interrupt callback.
  * @param  PeriphId Peripheral identifier triggering the illegal access.
  *         This parameter can be a value of @ref GTZC_TZSC_TZIC_PeriphId
  * @retval None.
  */
__weak void HAL_GTZC_TZIC_Callback(uint32_t PeriphId)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(PeriphId);

  /* NOTE: This function should not be modified. When the callback is needed,
   * the HAL_GTZC_TZIC_Callback is to be implemented in the user file
   */
}

/**
  * @}
  */

#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

/**
  * @}
  */

#endif /*HAL_GTZC_MODULE_ENABLED*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
