/**
  ******************************************************************************
  * @file    stm32u5xx_hal_gtzc.c
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
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                ##### GTZC main features #####
  ==============================================================================
  [..]
    (+) Global TrustZone Controller (GTZC) composed of three sub-blocks:
      (++) TZSC: TrustZone security controller
            This sub-block defines the secure/privileged state of master and slave
            peripherals. It also controls the secure/privileged state of subregions
            for the watermark memory peripheral controller (MPCWM).
      (++) MPCBB: Block-Based memory protection controller
            This sub-block defines the secure/privileged state of all blocks
            (512-byte pages) of the associated SRAM.
      (++) TZIC: TrustZone illegal access controller
            This sub-block gathers all illegal access events in the system and
            generates a secure interrupt towards NVIC.

    (+) These sub-blocks are used to configure TrustZone system security in
        a product having bus agents with programmable-security and privileged
        attributes (securable) such as:
      (++) on-chip RAM with programmable secure and/or privilege blocks (pages)
      (++) AHB and APB peripherals with programmable security and/or privilege access
      (++) AHB master granted as secure and/or privilege
      (++) off-chip memories with secure and/or privilege areas

  [..]
    (+) TZIC accessible only with secure privileged transactions.
    (+) Secure and non-secure access supported for privileged and unprivileged
        part of TZSC and MPCBB
    (+) Set of registers to define product security settings:
      (++) Secure and privilege blocks for internal memories
      (++) Secure and privilege regions for external memories
      (++) Secure and privileged access mode for securable peripherals

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
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/** @addtogroup STM32U5xx_HAL_Driver
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

/* Definitions for TZSC_MPCWM */
#define TZSC_MPCWM1_MEM_SIZE      0x10000000U    /* 256MB max size */
#define TZSC_MPCWM2_MEM_SIZE      0x10000000U    /* 256MB max size */
#define TZSC_MPCWM3_MEM_SIZE      0x10000000U    /* 256MB max size */
#define TZSC_MPCWM4_MEM_SIZE      0x00000800U    /* 2KB max size   */
#define TZSC_MPCWM5_MEM_SIZE      0x10000000U    /* 256MB max size */

/* Definitions for GTZC TZSC & TZIC ALL register values */
/* TZSC1 / TZIC1 instances */
#define TZSC1_SECCFGR1_ALL       (0x001FFFFFUL)
#define TZSC1_SECCFGR2_ALL       (0x000001FFUL)
#define TZSC1_SECCFGR3_ALL       (0x007FFFFFUL)

#define TZSC1_PRIVCFGR1_ALL      (0x001FFFFFUL)
#define TZSC1_PRIVCFGR2_ALL      (0x000001FFUL)
#define TZSC1_PRIVCFGR3_ALL      (0x007FFFFFUL)

#define TZIC1_IER1_ALL           (0x001FFFFFUL)
#define TZIC1_IER2_ALL           (0x000001FFUL)
#define TZIC1_IER3_ALL           (0x007FFFFFUL)
#define TZIC1_IER4_ALL           (0x3F0FC01FUL)

#define TZIC1_FCR1_ALL           (0x001FFFFFUL)
#define TZIC1_FCR2_ALL           (0x000001FFUL)
#define TZIC1_FCR3_ALL           (0x007FFFFFUL)
#define TZIC1_FCR4_ALL           (0x3F0FC01FUL)

/* TZSC2 / TZIC2 instances */
#define TZSC2_SECCFGR1_ALL       (0x00001BFFUL)

#define TZSC2_PRIVCFGR1_ALL      (0x00001BFFUL)

#define TZIC2_IER1_ALL           (0x00001BFFUL)
#define TZIC2_IER2_ALL           (0x0300C07FUL)

#define TZIC2_FCR1_ALL           (0x00001BFFUL)
#define TZIC2_FCR2_ALL           (0x0300C07FUL)

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
    TZSC: TrustZone Security Controller
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
      || (HAL_GTZC_TZSC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZSC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U)
          && (HAL_GTZC_TZSC_GET_ARRAY_INDEX(PeriphId) != 0U)))
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
      SET_BIT(GTZC_TZSC1->SECCFGR1, TZSC1_SECCFGR1_ALL);
      SET_BIT(GTZC_TZSC1->SECCFGR2, TZSC1_SECCFGR2_ALL);
      SET_BIT(GTZC_TZSC1->SECCFGR3, TZSC1_SECCFGR3_ALL);
      SET_BIT(GTZC_TZSC2->SECCFGR1, TZSC2_SECCFGR1_ALL);
    }
    else if ((PeriphAttributes & GTZC_TZSC_PERIPH_NSEC) == GTZC_TZSC_PERIPH_NSEC)
    {
      CLEAR_BIT(GTZC_TZSC1->SECCFGR1, TZSC1_SECCFGR1_ALL);
      CLEAR_BIT(GTZC_TZSC1->SECCFGR2, TZSC1_SECCFGR2_ALL);
      CLEAR_BIT(GTZC_TZSC1->SECCFGR3, TZSC1_SECCFGR3_ALL);
      CLEAR_BIT(GTZC_TZSC2->SECCFGR1, TZSC2_SECCFGR1_ALL);
    }
    else
    {
      /* do nothing */
    }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

    /* privilege configuration */
    if ((PeriphAttributes & GTZC_TZSC_PERIPH_PRIV) == GTZC_TZSC_PERIPH_PRIV)
    {
      SET_BIT(GTZC_TZSC1->PRIVCFGR1, TZSC1_PRIVCFGR1_ALL);
      SET_BIT(GTZC_TZSC1->PRIVCFGR2, TZSC1_PRIVCFGR2_ALL);
      SET_BIT(GTZC_TZSC1->PRIVCFGR3, TZSC1_PRIVCFGR3_ALL);
      SET_BIT(GTZC_TZSC2->PRIVCFGR1, TZSC2_PRIVCFGR1_ALL);
    }
    else if ((PeriphAttributes & GTZC_TZSC_PERIPH_NPRIV) == GTZC_TZSC_PERIPH_NPRIV)
    {
      CLEAR_BIT(GTZC_TZSC1->PRIVCFGR1, TZSC1_PRIVCFGR1_ALL);
      CLEAR_BIT(GTZC_TZSC1->PRIVCFGR2, TZSC1_PRIVCFGR2_ALL);
      CLEAR_BIT(GTZC_TZSC1->PRIVCFGR3, TZSC1_PRIVCFGR3_ALL);
      CLEAR_BIT(GTZC_TZSC2->PRIVCFGR1, TZSC2_PRIVCFGR1_ALL);
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
    register_address = (uint32_t) &(HAL_GTZC_TZSC_GET_INSTANCE(PeriphId)->SECCFGR1)
                       + (4U * GTZC_GET_REG_INDEX_IN_INSTANCE(PeriphId));
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
    register_address = (uint32_t) &(HAL_GTZC_TZSC_GET_INSTANCE(PeriphId)->PRIVCFGR1)
                       + (4U * GTZC_GET_REG_INDEX_IN_INSTANCE(PeriphId));
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
      || (HAL_GTZC_TZSC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZSC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U)
          && (HAL_GTZC_TZSC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* get secure configuration: read each register and deploy each bit value
     * of corresponding index in the destination array
     */
    reg_value = READ_REG(GTZC_TZSC1->SECCFGR1);
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

    reg_value = READ_REG(GTZC_TZSC1->SECCFGR2);
    for (i = 32U; i < 64U; i++)
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

    reg_value = READ_REG(GTZC_TZSC1->SECCFGR3);
    for (i = 64U; i < 96U; i++)
    {
      if (((reg_value & (1UL << (i - 64U))) >> (i - 64U)) != 0U)
      {
        PeriphAttributes[i] = GTZC_TZSC_PERIPH_SEC;
      }
      else
      {
        PeriphAttributes[i] = GTZC_TZSC_PERIPH_NSEC;
      }
    }

    reg_value = READ_REG(GTZC_TZSC2->SECCFGR1);
    for (i = 96U; i < GTZC_TZSC_PERIPH_NUMBER; i++)
    {
      if (((reg_value & (1UL << (i - 96U))) >> (i - 96U)) != 0U)
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
    reg_value = READ_REG(GTZC_TZSC1->PRIVCFGR1);
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

    reg_value = READ_REG(GTZC_TZSC1->PRIVCFGR2);
    for (i = 32U; i < 64U; i++)
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

    reg_value = READ_REG(GTZC_TZSC1->PRIVCFGR3);
    for (i = 64U; i < 96U; i++)
    {
      if (((reg_value & (1UL << (i - 64U))) >> (i - 64U)) != 0U)
      {
        PeriphAttributes[i] |= GTZC_TZSC_PERIPH_PRIV;
      }
      else
      {
        PeriphAttributes[i] |= GTZC_TZSC_PERIPH_NPRIV;
      }
    }

    reg_value = READ_REG(GTZC_TZSC2->PRIVCFGR1);
    for (i = 96U; i < GTZC_TZSC_PERIPH_NUMBER; i++)
    {
      if (((reg_value & (1UL << (i - 96U))) >> (i - 96U)) != 0U)
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
    register_address = (uint32_t) &(HAL_GTZC_TZSC_GET_INSTANCE(PeriphId)->SECCFGR1)
                       + (4U * GTZC_GET_REG_INDEX_IN_INSTANCE(PeriphId));

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
    register_address = (uint32_t) &(HAL_GTZC_TZSC_GET_INSTANCE(PeriphId)->PRIVCFGR1)
                       + (4U * GTZC_GET_REG_INDEX_IN_INSTANCE(PeriphId));
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
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes(
  uint32_t MemBaseAddress,
  MPCWM_ConfigTypeDef *pMPCWM_Desc)
{
  uint32_t register_address;
  uint32_t reg_value;
  uint32_t size;
  /* granularity value depends on selected memory */
  uint32_t granularity = (MemBaseAddress == BKPSRAM_BASE) ? \
                         GTZC_TZSC_MPCWM_GRANULARITY_2 : GTZC_TZSC_MPCWM_GRANULARITY_1;

  /* check entry parameters */
  if ((pMPCWM_Desc->AreaId > GTZC_TZSC_MPCWM_ID2)
      || (((MemBaseAddress == FMC_BANK3) || (MemBaseAddress == BKPSRAM_BASE))
          && (pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID2))
      || ((pMPCWM_Desc->Offset % granularity) != 0U)
      || ((pMPCWM_Desc->Length % granularity) != 0U))
  {
    return HAL_ERROR;
  }

  /* check descriptor content vs. memory capacity */
  switch (MemBaseAddress)
  {
    case OCTOSPI1_BASE:
      size = TZSC_MPCWM1_MEM_SIZE;
      if (pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID1)
      {
        register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM1AR);
      }
      else
      {
        /* Here pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID2
         * (Parameter already checked)
         */
        register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM1BR);
      }
      break;
    case FMC_BANK1:
      size = TZSC_MPCWM1_MEM_SIZE;
      if (pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID1)
      {
        register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM2AR);
      }
      else
      {
        /* Here pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID2
         * (Parameter already checked)
         */
        register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM2BR);
      }
      break;
    case FMC_BANK3:
      /* Here pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID1
       * (Parameter already checked)
       */
      size = TZSC_MPCWM3_MEM_SIZE;
      register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM3AR);
      break;
    case BKPSRAM_BASE:
      /* Here pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID1
       * (Parameter already checked)
       */
      size = TZSC_MPCWM4_MEM_SIZE;
      register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM4AR);
      break;
    case OCTOSPI2_BASE:
      size = TZSC_MPCWM5_MEM_SIZE;
      if (pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID1)
      {
        register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM5AR);
      }
      else
      {
        /* Here pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_ID2
         * (Parameter already checked)
         */
        register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM5BR);
      }
      break;
    default:
      return HAL_ERROR;
      break;
  }

  if ((pMPCWM_Desc->Offset > size)
      || ((pMPCWM_Desc->Offset
           + pMPCWM_Desc->Length)
          > size))
  {
    return HAL_ERROR;
  }

  /* Write watermark start and length value */
  reg_value = ((pMPCWM_Desc->Offset / granularity)
               << GTZC_TZSC_MPCWMR_SUBZ_START_Pos) & GTZC_TZSC_MPCWMR_SUBZ_START_Msk;
  reg_value |= ((pMPCWM_Desc->Length / granularity)
                << GTZC_TZSC_MPCWMR_SUBZ_LENGTH_Pos) & GTZC_TZSC_MPCWMR_SUBZ_LENGTH_Msk;
  MODIFY_REG(*(__IO uint32_t *)register_address, GTZC_TZSC_MPCWMR_SUBZ_START_Msk | \
             GTZC_TZSC_MPCWMR_SUBZ_LENGTH_Msk, reg_value);

  /* Write watermark configuration value */
  reg_value = (pMPCWM_Desc->Attribute << GTZC_TZSC_MPCWM_CFGR_SEC_Pos) | \
              pMPCWM_Desc->Lock                                  | \
              pMPCWM_Desc->AreaStatus;
  MODIFY_REG(*(__IO uint32_t *)(register_address - 4U), (GTZC_TZSC_MPCWM_CFGR_PRIV | GTZC_TZSC_MPCWM_CFGR_SEC | \
                                                         GTZC_TZSC_MPCWM_CFGR_SRLOCK | GTZC_TZSC_MPCWM_CFGR_SREN), \
             reg_value);

  return HAL_OK;
}

/**
  * @brief  Get a TZSC-MPCWM area configuration.
  * @param  MemBaseAddress WM identifier.
  * @param  pMPCWM_Desc pointer to a TZSC-MPCWM descriptor.
  *         The structure description is available in @ref GTZC_Exported_Types.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_GetConfigMemAttributes(
  uint32_t MemBaseAddress,
  MPCWM_ConfigTypeDef *pMPCWM_Desc)
{
  uint32_t register_address;
  uint32_t reg_value;
  uint32_t granularity = (MemBaseAddress == BKPSRAM_BASE) ? \
                         GTZC_TZSC_MPCWM_GRANULARITY_2 : GTZC_TZSC_MPCWM_GRANULARITY_1;

  /* firstly take care of the first area, present on all MPCWM sub-blocks */
  switch (MemBaseAddress)
  {
    case OCTOSPI1_BASE:
      register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM1AR);
      break;
    case FMC_BANK1:
      register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM2AR);
      break;
    case FMC_BANK3:
      register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM3AR);
      break;
    case BKPSRAM_BASE:
      register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM4AR);
      break;
    case OCTOSPI2_BASE:
      register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM5AR);
      break;
    default:
      return HAL_ERROR;
      break;
  }

  /* read register and update the descriptor for first area*/
  reg_value = READ_REG(*(__IO uint32_t *)register_address);
  pMPCWM_Desc[0].AreaId = GTZC_TZSC_MPCWM_ID1;
  pMPCWM_Desc[0].Offset = ((reg_value & GTZC_TZSC_MPCWMR_SUBZ_START_Msk)
                           >> GTZC_TZSC_MPCWMR_SUBZ_START_Pos) * granularity;
  pMPCWM_Desc[0].Length = ((reg_value & GTZC_TZSC_MPCWMR_SUBZ_LENGTH_Msk)
                           >> GTZC_TZSC_MPCWMR_SUBZ_LENGTH_Pos) * granularity;

  /* read configuration register and update the descriptor for first area*/
  reg_value = READ_REG(*(__IO uint32_t *)(register_address - 4U));
  pMPCWM_Desc[0].Attribute = (reg_value & (GTZC_TZSC_MPCWM_CFGR_PRIV | \
                                           GTZC_TZSC_MPCWM_CFGR_SEC)) >> GTZC_TZSC_MPCWM_CFGR_SEC_Pos;
  pMPCWM_Desc[0].Lock = reg_value & GTZC_TZSC_MPCWM_CFGR_SRLOCK;
  pMPCWM_Desc[0].AreaStatus = reg_value & GTZC_TZSC_MPCWM_CFGR_SREN;

  if ((MemBaseAddress != FMC_BANK3) && (MemBaseAddress != BKPSRAM_BASE))
  {
    /* Here MemBaseAddress = OCTOSPI1_BASE, OCTOSPI2_BASE
     * or FMC_BANK1 (already checked)
     * Now take care of the second area, present on these sub-blocks
     */
    switch (MemBaseAddress)
    {
      case OCTOSPI1_BASE:
        register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM1BR);
        break;
      case FMC_BANK1:
        register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM2BR);
        break;
      case OCTOSPI2_BASE:
        register_address = (uint32_t) &(GTZC_TZSC1_S->MPCWM5BR);
        break;
      default:
        return HAL_ERROR;
        break;
    }

    /* read register and update the descriptor for second area*/
    reg_value = READ_REG(*(__IO uint32_t *)register_address);
    pMPCWM_Desc[1].AreaId = GTZC_TZSC_MPCWM_ID2;
    pMPCWM_Desc[1].Offset = ((reg_value & GTZC_TZSC_MPCWMR_SUBZ_START_Msk)
                             >> GTZC_TZSC_MPCWMR_SUBZ_START_Pos) * granularity;
    pMPCWM_Desc[1].Length = ((reg_value & GTZC_TZSC_MPCWMR_SUBZ_LENGTH_Msk)
                             >> GTZC_TZSC_MPCWMR_SUBZ_LENGTH_Pos) * granularity;

    /* read configuration register and update the descriptor for second area*/
    reg_value = READ_REG(*(__IO uint32_t *)(register_address - 4U));
    pMPCWM_Desc[1].Attribute = reg_value & (GTZC_TZSC_MPCWM_CFGR_PRIV | \
                                            GTZC_TZSC_MPCWM_CFGR_SEC);
    pMPCWM_Desc[1].Lock = reg_value & GTZC_TZSC_MPCWM_CFGR_SRLOCK;
    pMPCWM_Desc[1].AreaStatus = reg_value & GTZC_TZSC_MPCWM_CFGR_SREN;
  }

  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group3 TZSC Lock functions
  * @brief    TZSC Lock functions
  *
  @verbatim
  ==============================================================================
                   ##### TZSC Lock functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to manage the TZSC (TrustZone
    Security Controller) lock. It includes lock enable, and current value read.
@endverbatim
  * @{
  */

/**
  * @brief  Lock TZSC configuration.
  * @note   This function locks the configuration of TZSC_SECCFGRx and TZSC_PRIVCFGRx
  *         registers until next reset
  * @param  TZSC_Instance TZSC sub-block instance.
  */
void HAL_GTZC_TZSC_Lock(GTZC_TZSC_TypeDef *TZSC_Instance)
{
  SET_BIT(TZSC_Instance->CR, GTZC_TZSC_CR_LCK_Msk);
}

/**
  * @brief  Get TZSC configuration lock state.
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
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

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
  uint32_t mem_size;
  uint32_t size_in_superblocks;
  uint32_t i;

  /* check entry parameters */
  if ((!(IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
       &&  !(IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress))
       &&  !(IS_GTZC_BASE_ADDRESS(SRAM3, MemBaseAddress))
       &&  !(IS_GTZC_BASE_ADDRESS(SRAM4, MemBaseAddress)))
      || ((pMPCBB_desc->SecureRWIllegalMode
           != GTZC_MPCBB_SRWILADIS_ENABLE)
          && (pMPCBB_desc->SecureRWIllegalMode
              != GTZC_MPCBB_SRWILADIS_DISABLE))
      || ((pMPCBB_desc->InvertSecureState
           != GTZC_MPCBB_INVSECSTATE_NOT_INVERTED)
          && (pMPCBB_desc->InvertSecureState
              != GTZC_MPCBB_INVSECSTATE_INVERTED)))
  {
    return HAL_ERROR;
  }

  if (IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
  {
    mpcbb_ptr = GTZC_MPCBB1;
    mem_size = GTZC_MEM_SIZE(SRAM1);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress))
  {
    mpcbb_ptr = GTZC_MPCBB2;
    mem_size = GTZC_MEM_SIZE(SRAM2);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM3, MemBaseAddress))
  {
    mpcbb_ptr = GTZC_MPCBB3;
    mem_size = GTZC_MEM_SIZE(SRAM3);
  }
  else
  {
    /* Here MemBaseAddress is inside SRAM4 (parameter already checked) */
    mpcbb_ptr = GTZC_MPCBB4;
    mem_size = GTZC_MEM_SIZE(SRAM4);
  }

  /* translate mem_size in number of super-blocks  */
  size_in_superblocks = (mem_size / GTZC_MPCBB_SUPERBLOCK_SIZE);

  /* write PRIVCFGR register information */
  for (i = 0U; i < size_in_superblocks; i++)
  {
    WRITE_REG(mpcbb_ptr->PRIVCFGR[i],
              pMPCBB_desc->AttributeConfig.MPCBB_PrivConfig_array[i]);
  }

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  uint32_t size_mask;
  uint32_t reg_value;

  /* write SECCFGR register information */
  for (i = 0U; i < size_in_superblocks; i++)
  {
    WRITE_REG(mpcbb_ptr->SECCFGR[i],
              pMPCBB_desc->AttributeConfig.MPCBB_SecConfig_array[i]);
  }

#if defined (GTZC_MPCBB_CFGLOCKR2_SPLCK32_Msk)
  if (size_in_superblocks >= 32U)
  {
    size_mask = 0xFFFFFFFFU;
    MODIFY_REG(mpcbb_ptr->CFGLOCKR2, 0x000FFFFFUL, pMPCBB_desc->AttributeConfig.MPCBB_LockConfig_array[1]);
  }
  else
#endif /* GTZC_MPCBB_CFGLOCKR2_SPLCK32_Msk */
  {
    size_mask = (1UL << size_in_superblocks) - 1U;
  }
  /* limitation: code not portable with memory > 512K */
  MODIFY_REG(mpcbb_ptr->CFGLOCKR1, size_mask, pMPCBB_desc->AttributeConfig.MPCBB_LockConfig_array[0]);

  /* write InvertSecureState and SecureRWIllegalMode properties */
  reg_value = pMPCBB_desc->InvertSecureState;
  reg_value |= pMPCBB_desc->SecureRWIllegalMode;

  /* write configuration and lock register information */
  MODIFY_REG(mpcbb_ptr->CR,
             GTZC_MPCBB_CR_INVSECSTATE_Msk | GTZC_MPCBB_CR_SRWILADIS_Msk, reg_value);
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

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
  uint32_t mem_size;
  uint32_t size_in_superblocks;
  uint32_t i;

  /* check entry parameters */
  if (!(IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
      && !(IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress))
      && !(IS_GTZC_BASE_ADDRESS(SRAM3, MemBaseAddress))
      && !(IS_GTZC_BASE_ADDRESS(SRAM4, MemBaseAddress)))
  {
    return HAL_ERROR;
  }

  /* read InvertSecureState and SecureRWIllegalMode properties */
  /* assume their Position/Mask is identical for all sub-blocks */
  if (IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
  {
    mpcbb_ptr = GTZC_MPCBB1;
    mem_size = GTZC_MEM_SIZE(SRAM1);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress))
  {
    mpcbb_ptr = GTZC_MPCBB2;
    mem_size = GTZC_MEM_SIZE(SRAM2);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM3, MemBaseAddress))
  {
    mpcbb_ptr = GTZC_MPCBB3;
    mem_size = GTZC_MEM_SIZE(SRAM3);
  }
  else
  {
    mpcbb_ptr = GTZC_MPCBB4;
    mem_size = GTZC_MEM_SIZE(SRAM4);
  }

  /* translate mem_size in number of super-blocks  */
  size_in_superblocks = (mem_size / GTZC_MPCBB_SUPERBLOCK_SIZE);

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  uint32_t reg_value;
  uint32_t size_mask;

  /* read configuration and lock register information */
  reg_value = READ_REG(mpcbb_ptr->CR);
  pMPCBB_desc->InvertSecureState = (reg_value & GTZC_MPCBB_CR_INVSECSTATE_Msk);
  pMPCBB_desc->SecureRWIllegalMode = (reg_value & GTZC_MPCBB_CR_SRWILADIS_Msk);
  if (size_in_superblocks == 32U)
  {
    size_mask = 0xFFFFFFFFU;
  }
  else
  {
    size_mask = (1UL << size_in_superblocks) - 1U;
  }
  /* limitation: code not portable with memory > 512K */
  pMPCBB_desc->AttributeConfig.MPCBB_LockConfig_array[0] = READ_REG(mpcbb_ptr->CFGLOCKR1)
                                                           & size_mask;
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

  /* read SECCFGR / PRIVCFGR registers information */
  for (i = 0U; i < size_in_superblocks; i++)
  {
    pMPCBB_desc->AttributeConfig.MPCBB_SecConfig_array[i] = mpcbb_ptr->SECCFGR[i];
    pMPCBB_desc->AttributeConfig.MPCBB_PrivConfig_array[i] = mpcbb_ptr->PRIVCFGR[i];
  }

  return HAL_OK;
}

/**
  * @brief  Set a MPCBB attribute configuration on the SRAM passed as parameter
  *         for a number of blocks.
  * @param  MemAddress MPCBB identifier, and start block to configure
  *         (must be 512 Bytes aligned).
  * @param  NbBlocks Number of blocks to configure
  *         (Block size is 512 Bytes).
  * @param  pMemAttributes pointer to an array (containing "NbBlocks" elements),
  *         with each element must be GTZC_MCPBB_BLOCK_NSEC or GTZC_MCPBB_BLOCK_SEC,
  *         and GTZC_MCPBB_BLOCK_NPRIV or GTZC_MCPBB_BLOCK_PRIV.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_ConfigMemAttributes(uint32_t MemAddress,
                                                     uint32_t NbBlocks,
                                                     uint32_t *pMemAttributes)
{
  GTZC_MPCBB_TypeDef *mpcbb_ptr;
  uint32_t base_address;
  uint32_t end_address;
  uint32_t block_start;
  uint32_t offset_reg_start;
  uint32_t offset_bit_start;
  uint32_t i;
  uint32_t do_attr_change;

  /* firstly check that MemAddress is well 512 Bytes aligned */
  if ((MemAddress % GTZC_MPCBB_BLOCK_SIZE) != 0U)
  {
    return HAL_ERROR;
  }

  /* check entry parameters and deduce physical base address */
  end_address = MemAddress + (NbBlocks * GTZC_MPCBB_BLOCK_SIZE) - 1U;
  if (((IS_ADDRESS_IN_NS(SRAM1, MemAddress))
       && (IS_ADDRESS_IN_NS(SRAM1, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB1;
    base_address = SRAM1_BASE_NS;
  }
  else if (((IS_ADDRESS_IN_S(SRAM1, MemAddress))
            && (IS_ADDRESS_IN_S(SRAM1, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB1;
    base_address = SRAM1_BASE_S;
  }
  else if (((IS_ADDRESS_IN_NS(SRAM2, MemAddress))
            && (IS_ADDRESS_IN_NS(SRAM2, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB2;
    base_address = SRAM2_BASE_NS;
  }
  else if (((IS_ADDRESS_IN_S(SRAM2, MemAddress))
            && (IS_ADDRESS_IN_S(SRAM2, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB2;
    base_address = SRAM2_BASE_S;
  }
  else if (((IS_ADDRESS_IN_NS(SRAM3, MemAddress))
            && (IS_ADDRESS_IN_NS(SRAM3, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB3;
    base_address = SRAM3_BASE_NS;
  }
  else if (((IS_ADDRESS_IN_S(SRAM3, MemAddress))
            && (IS_ADDRESS_IN_S(SRAM3, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB3;
    base_address = SRAM3_BASE_S;
  }
  else if (((IS_ADDRESS_IN_NS(SRAM4, MemAddress))
            && (IS_ADDRESS_IN_NS(SRAM4, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB4;
    base_address = SRAM4_BASE_NS;
  }
  else if (((IS_ADDRESS_IN_S(SRAM4, MemAddress))
            && (IS_ADDRESS_IN_S(SRAM4, end_address))) != 0U)
  {
    mpcbb_ptr = GTZC_MPCBB4;
    base_address = SRAM4_BASE_S;
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
    /* Indicate change done for protection attributes */
    do_attr_change = 0U;

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    /* secure configuration */
    if ((pMemAttributes[i] & GTZC_MCPBB_BLOCK_SEC) == GTZC_MCPBB_BLOCK_SEC)
    {
      SET_BIT(mpcbb_ptr->SECCFGR[offset_reg_start],
              1UL << (offset_bit_start % 32U));
      do_attr_change = 1U;
    }
    else if ((pMemAttributes[i] & GTZC_MCPBB_BLOCK_NSEC) == GTZC_MCPBB_BLOCK_NSEC)
    {
      CLEAR_BIT(mpcbb_ptr->SECCFGR[offset_reg_start],
                1UL << (offset_bit_start % 32U));
      do_attr_change = 1U;
    }
    else
    {
      /* nothing to do */
    }
#endif /* defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

    /* privilege configuration */
    if ((pMemAttributes[i] & GTZC_MCPBB_BLOCK_PRIV) == GTZC_MCPBB_BLOCK_PRIV)
    {
      SET_BIT(mpcbb_ptr->PRIVCFGR[offset_reg_start],
              1UL << (offset_bit_start % 32U));
    }
    else if ((pMemAttributes[i] & GTZC_MCPBB_BLOCK_NPRIV) == GTZC_MCPBB_BLOCK_NPRIV)
    {
      CLEAR_BIT(mpcbb_ptr->PRIVCFGR[offset_reg_start],
                1UL << (offset_bit_start % 32U));
    }
    else
    {
      /* if no change is done for security and privilege attributes: break the loop */
      if (do_attr_change == 0U)
      {
        break;
      }
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
  *         (must be 512 Bytes aligned).
  * @param  NbBlocks Number of blocks to get configuration.
  * @param  pMemAttributes pointer to an array (containing "NbBlocks" elements),
  *         with each element will be GTZC_MCPBB_BLOCK_NSEC or GTZC_MCPBB_BLOCK_SEC,
  *         and GTZC_MCPBB_BLOCK_NPRIV or GTZC_MCPBB_BLOCK_PRIV.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_GetConfigMemAttributes(uint32_t MemAddress,
                                                        uint32_t NbBlocks,
                                                        uint32_t *pMemAttributes)
{
  GTZC_MPCBB_TypeDef *mpcbb_ptr;
  uint32_t base_address;
  uint32_t end_address;
  uint32_t block_start;
  uint32_t offset_reg_start;
  uint32_t offset_bit_start;
  uint32_t i;

  /* firstly check that MemAddress is well 512 Bytes aligned */
  if ((MemAddress % GTZC_MPCBB_BLOCK_SIZE) != 0U)
  {
    return HAL_ERROR;
  }

  /* check entry parameters and deduce physical base address */
  end_address = MemAddress + (NbBlocks * GTZC_MPCBB_BLOCK_SIZE) - 1U;
  if ((IS_ADDRESS_IN_NS(SRAM1, MemAddress))
      && (IS_ADDRESS_IN_NS(SRAM1, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB1_NS;
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
    mpcbb_ptr = GTZC_MPCBB2_NS;
    base_address = SRAM2_BASE_NS;
  }
  else if ((IS_ADDRESS_IN_S(SRAM2, MemAddress))
           && (IS_ADDRESS_IN_S(SRAM2, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB2_S;
    base_address = SRAM2_BASE_S;
  }
  else if ((IS_ADDRESS_IN_NS(SRAM3, MemAddress))
           && (IS_ADDRESS_IN_NS(SRAM3, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB3_NS;
    base_address = SRAM3_BASE_NS;
  }
  else if ((IS_ADDRESS_IN_S(SRAM3, MemAddress))
           && (IS_ADDRESS_IN_S(SRAM3, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB3_S;
    base_address = SRAM3_BASE_S;
  }
  else if ((IS_ADDRESS_IN_NS(SRAM4, MemAddress))
           && (IS_ADDRESS_IN_NS(SRAM4, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB4_NS;
    base_address = SRAM4_BASE_NS;
  }
  else if ((IS_ADDRESS_IN_S(SRAM4, MemAddress))
           && (IS_ADDRESS_IN_S(SRAM4, end_address)))
  {
    mpcbb_ptr = GTZC_MPCBB4_S;
    base_address = SRAM4_BASE_S;
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
    pMemAttributes[i] = (READ_BIT(mpcbb_ptr->SECCFGR[offset_reg_start],
                                  1UL << (offset_bit_start % 32U))
                         >> (offset_bit_start % 32U)) | GTZC_ATTR_SEC_MASK;
    pMemAttributes[i] |= (READ_BIT(mpcbb_ptr->PRIVCFGR[offset_reg_start],
                                   1UL << (offset_bit_start % 32U))
                          >> (offset_bit_start % 32U)) | GTZC_ATTR_PRIV_MASK;

    offset_bit_start++;
    if (offset_bit_start == 32U)
    {
      offset_bit_start = 0U;
      offset_reg_start++;
    }
  }

  return HAL_OK;
}

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/**
  * @brief  Lock MPCBB super-blocks on the SRAM passed as parameter.
  * @param  MemAddress MPCBB start-address of super-block to configure
  *         (must be 16KBytes aligned).
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
  uint32_t superblock_start;
  uint32_t offset_bit_start;
  uint32_t i;

  /* firstly check that MemAddress is well 16KBytes aligned */
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
    /* limitation: code not portable with memory > 512K */
    reg_mpcbb = (__IO uint32_t *)&GTZC_MPCBB1_S->CFGLOCKR1;
  }
  else if ((IS_ADDRESS_IN(SRAM2, MemAddress))
           && (IS_ADDRESS_IN(SRAM2, (MemAddress
                                     + (NbSuperBlocks * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                     - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM2);
    /* limitation: code not portable with memory > 512K */
    reg_mpcbb = (__IO uint32_t *)&GTZC_MPCBB2_S->CFGLOCKR1;
  }
  else if ((IS_ADDRESS_IN(SRAM3, MemAddress))
           && (IS_ADDRESS_IN(SRAM3, (MemAddress
                                     + (NbSuperBlocks * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                     - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM3);
    /* limitation: code not portable with memory > 512K */
    reg_mpcbb = (__IO uint32_t *)&GTZC_MPCBB3_S->CFGLOCKR1;
  }

  else if ((IS_ADDRESS_IN(SRAM4, MemAddress))
           && (IS_ADDRESS_IN(SRAM4, (MemAddress
                                     + (NbSuperBlocks * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                     - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM4);
    /* limitation: code not portable with memory > 512K */
    reg_mpcbb = (__IO uint32_t *)&GTZC_MPCBB4_S->CFGLOCKR1;
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
  * @param  MemAddress MPCBB start-address of super-block to get configuration
  *         (must be 16KBytes aligned).
  * @param  NbSuperBlocks Number of super-blocks to get configuration.
  * @param  pLockAttributes pointer to an array (containing "NbSuperBlocks" elements),
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
  uint32_t superblock_start;
  uint32_t offset_bit_start;
  uint32_t i;

  /* firstly check that MemAddress is well 16KBytes aligned */
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
    /* limitation: code not portable with memory > 512K */
    reg_mpcbb = GTZC_MPCBB1_S->CFGLOCKR1;
  }
  else if ((IS_ADDRESS_IN(SRAM2, MemAddress))
           && (IS_ADDRESS_IN(SRAM2, (MemAddress
                                     + (NbSuperBlocks
                                        * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                     - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM2);
    /* limitation: code not portable with memory > 512K */
    reg_mpcbb = GTZC_MPCBB2_S->CFGLOCKR1;
  }
  else if ((IS_ADDRESS_IN(SRAM3, MemAddress))
           && (IS_ADDRESS_IN(SRAM3, (MemAddress
                                     + (NbSuperBlocks
                                        * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                     - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM3);
    /* limitation: code not portable with memory > 512K */
    reg_mpcbb = GTZC_MPCBB3_S->CFGLOCKR1;
  }
  else if ((IS_ADDRESS_IN(SRAM4, MemAddress))
           && (IS_ADDRESS_IN(SRAM4, (MemAddress
                                     + (NbSuperBlocks
                                        * GTZC_MPCBB_SUPERBLOCK_SIZE)
                                     - 1U))))
  {
    base_address = GTZC_BASE_ADDRESS(SRAM4);
    /* limitation: code not portable with memory > 512K */
    reg_mpcbb = GTZC_MPCBB4_S->CFGLOCKR1;
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
  * @note   This functions locks the control register of the MPCBB until next reset.
  * @param  MemBaseAddress MPCBB identifier.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_MPCBB_Lock(uint32_t MemBaseAddress)
{
  /* check entry parameters */
  if (IS_GTZC_BASE_ADDRESS(SRAM1, MemBaseAddress))
  {
    SET_BIT(GTZC_MPCBB1_S->CR, GTZC_MPCBB_CR_GLOCK_Msk);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress))
  {
    SET_BIT(GTZC_MPCBB2_S->CR, GTZC_MPCBB_CR_GLOCK_Msk);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM3, MemBaseAddress))
  {
    SET_BIT(GTZC_MPCBB3_S->CR, GTZC_MPCBB_CR_GLOCK_Msk);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM4, MemBaseAddress))
  {
    SET_BIT(GTZC_MPCBB4_S->CR, GTZC_MPCBB_CR_GLOCK_Msk);
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
    *pLockState = READ_BIT(GTZC_MPCBB1_S->CR, GTZC_MPCBB_CR_GLOCK_Msk);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM2, MemBaseAddress))
  {
    *pLockState = READ_BIT(GTZC_MPCBB2_S->CR, GTZC_MPCBB_CR_GLOCK_Msk);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM3, MemBaseAddress))
  {
    *pLockState = READ_BIT(GTZC_MPCBB3_S->CR, GTZC_MPCBB_CR_GLOCK_Msk);
  }
  else if (IS_GTZC_BASE_ADDRESS(SRAM4, MemBaseAddress))
  {
    *pLockState = READ_BIT(GTZC_MPCBB4_S->CR, GTZC_MPCBB_CR_GLOCK_Msk);
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
  if ((HAL_GTZC_TZIC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZIC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U)
          && (HAL_GTZC_TZIC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* same configuration is applied to all peripherals */
    WRITE_REG(GTZC_TZIC1->IER1, 0U);
    WRITE_REG(GTZC_TZIC1->IER2, 0U);
    WRITE_REG(GTZC_TZIC1->IER3, 0U);
    WRITE_REG(GTZC_TZIC1->IER4, 0U);
    WRITE_REG(GTZC_TZIC2->IER1, 0U);
    WRITE_REG(GTZC_TZIC2->IER2, 0U);
  }
  else
  {
    /* common case where only one peripheral is configured */
    register_address = (uint32_t) &(HAL_GTZC_TZIC_GET_INSTANCE(PeriphId)->IER1)
                       + (4U * GTZC_GET_REG_INDEX_IN_INSTANCE(PeriphId));
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
  if ((HAL_GTZC_TZIC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZIC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U)
          && (HAL_GTZC_TZIC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* same configuration is applied to all peripherals */
    WRITE_REG(GTZC_TZIC1->IER1, TZIC1_IER1_ALL);
    WRITE_REG(GTZC_TZIC1->IER2, TZIC1_IER2_ALL);
    WRITE_REG(GTZC_TZIC1->IER3, TZIC1_IER3_ALL);
    WRITE_REG(GTZC_TZIC1->IER4, TZIC1_IER4_ALL);
    WRITE_REG(GTZC_TZIC2->IER1, TZIC2_IER1_ALL);
    WRITE_REG(GTZC_TZIC2->IER2, TZIC2_IER2_ALL);
  }
  else
  {
    /* common case where only one peripheral is configured */
    register_address = (uint32_t) &(HAL_GTZC_TZIC_GET_INSTANCE(PeriphId)->IER1)
                       + (4U * GTZC_GET_REG_INDEX_IN_INSTANCE(PeriphId));
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
  if ((HAL_GTZC_TZIC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZIC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U)
          && (HAL_GTZC_TZIC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* special case where it is applied to all peripherals */
    reg_value = READ_REG(GTZC_TZIC1->SR1);
    for (i = 0U; i < 32U; i++)
    {
      pFlag[i] = (reg_value & (1UL << i)) >> i;
    }

    reg_value = READ_REG(GTZC_TZIC1->SR2);
    for (i = 32U; i < 64U; i++)
    {
      pFlag[i] = (reg_value & (1UL << (i - 32U))) >> (i - 32U);
    }

    reg_value = READ_REG(GTZC_TZIC1->SR3);
    for (i = 64; i < 96U; i++)
    {
      pFlag[i] = (reg_value & (1UL << (i - 64U))) >> (i - 64U);
    }

    reg_value = READ_REG(GTZC_TZIC1->SR4);
    for (i = 96U; i < 128U; i++)
    {
      pFlag[i] = (reg_value & (1UL << (i - 96U))) >> (i - 96U);
    }

    reg_value = READ_REG(GTZC_TZIC2->SR1);
    for (i = 128U; i < 160U; i++)
    {
      pFlag[i] = (reg_value & (1UL << (i - 128U))) >> (i - 128U);
    }

    reg_value = READ_REG(GTZC_TZIC2->SR2);
    for (i = 160U; i < GTZC_TZIC_PERIPH_NUMBER; i++)
    {
      pFlag[i] = (reg_value & (1UL << (i - 160U))) >> (i - 160U);
    }
  }
  else
  {
    /* common case where only one peripheral is concerned */
    register_address = (uint32_t) &(HAL_GTZC_TZIC_GET_INSTANCE(PeriphId)->SR1)
                       + (4U * GTZC_GET_REG_INDEX_IN_INSTANCE(PeriphId));
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
  if ((HAL_GTZC_TZIC_GET_ARRAY_INDEX(PeriphId) >= GTZC_TZIC_PERIPH_NUMBER)
      || (((PeriphId & GTZC_PERIPH_ALL) != 0U)
          && (HAL_GTZC_TZIC_GET_ARRAY_INDEX(PeriphId) != 0U)))
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0U)
  {
    /* same configuration is applied to all peripherals */
    WRITE_REG(GTZC_TZIC1->FCR1, TZIC1_FCR1_ALL);
    WRITE_REG(GTZC_TZIC1->FCR2, TZIC1_FCR2_ALL);
    WRITE_REG(GTZC_TZIC1->FCR3, TZIC1_FCR3_ALL);
    WRITE_REG(GTZC_TZIC1->FCR4, TZIC1_FCR4_ALL);
    WRITE_REG(GTZC_TZIC2->FCR1, TZIC2_FCR1_ALL);
    WRITE_REG(GTZC_TZIC2->FCR2, TZIC2_FCR2_ALL);
  }
  else
  {
    /* common case where only one peripheral is configured */
    register_address = (uint32_t) &(HAL_GTZC_TZIC_GET_INSTANCE(PeriphId)->FCR1)
                       + (4U * GTZC_GET_REG_INDEX_IN_INSTANCE(PeriphId));
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
  * @brief  This function handles GTZC TZIC interrupt request.
  * @retval None.
  */
void HAL_GTZC_IRQHandler(void)
{
  uint32_t position;
  uint32_t flag;
  uint32_t ier_itsources;
  uint32_t sr_flags;

  /*********************************************************************/
  /******************************  TZIC1  ******************************/
  /*********************************************************************/

  /* Get current IT Flags and IT sources value on 1st register of TZIC1 */
  ier_itsources = READ_REG(GTZC_TZIC1_S->IER1);
  sr_flags      = READ_REG(GTZC_TZIC1_S->SR1);

  /* Get Mask interrupt and then clear them */
  flag = ier_itsources & sr_flags;
  if (flag != 0U)
  {
    WRITE_REG(GTZC_TZIC1_S->FCR1, flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0U;
    while ((flag >> position) != 0U)
    {
      if ((flag & (1UL << position)) != 0U)
      {
        HAL_GTZC_TZIC_Callback(GTZC1_PERIPH_REG1 | position);
      }

      /* Position bit to be updated */
      position++;
    }
  }

  /* Get current IT Flags and IT sources value on 2nd register of TZIC1 */
  ier_itsources = READ_REG(GTZC_TZIC1_S->IER2);
  sr_flags      = READ_REG(GTZC_TZIC1_S->SR2);

  /* Get Mask interrupt and then clear them */
  flag = ier_itsources & sr_flags;
  if (flag != 0U)
  {
    WRITE_REG(GTZC_TZIC1_S->FCR2, flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0U;
    while ((flag >> position) != 0U)
    {
      if ((flag & (1UL << position)) != 0U)
      {
        HAL_GTZC_TZIC_Callback(GTZC1_PERIPH_REG2 | position);
      }

      /* Position bit to be updated */
      position++;
    }
  }

  /* Get current IT Flags and IT sources value on 3rd register of TZIC1 */
  ier_itsources = READ_REG(GTZC_TZIC1_S->IER3);
  sr_flags      = READ_REG(GTZC_TZIC1_S->SR3);

  /* Get Mask interrupt and then clear them */
  flag = ier_itsources & sr_flags;
  if (flag != 0U)
  {
    WRITE_REG(GTZC_TZIC1_S->FCR3, flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0U;
    while ((flag >> position) != 0U)
    {
      if ((flag & (1UL << position)) != 0U)
      {
        HAL_GTZC_TZIC_Callback(GTZC1_PERIPH_REG3 | position);
      }

      /* Position bit to be updated */
      position++;
    }
  }

  /* Get current IT Flags and IT sources value on 4th register of TZIC1 */
  ier_itsources = READ_REG(GTZC_TZIC1_S->IER4);
  sr_flags      = READ_REG(GTZC_TZIC1_S->SR4);

  /* Get Mask interrupt and then clear them */
  flag = ier_itsources & sr_flags;
  if (flag != 0U)
  {
    WRITE_REG(GTZC_TZIC1_S->FCR4, flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0U;
    while ((flag >> position) != 0U)
    {
      if ((flag & (1UL << position)) != 0U)
      {
        HAL_GTZC_TZIC_Callback(GTZC1_PERIPH_REG4 | position);
      }

      /* Position bit to be updated */
      position++;
    }
  }

  /*********************************************************************/
  /******************************  TZIC2  ******************************/
  /*********************************************************************/

  /* Get current IT Flags and IT sources value on 1st register of TZIC2 */
  ier_itsources = READ_REG(GTZC_TZIC2_S->IER1);
  sr_flags      = READ_REG(GTZC_TZIC2_S->SR1);

  /* Get Mask interrupt and then clear them */
  flag = ier_itsources & sr_flags;
  if (flag != 0U)
  {
    WRITE_REG(GTZC_TZIC2_S->FCR1, flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0U;
    while ((flag >> position) != 0U)
    {
      if ((flag & (1UL << position)) != 0U)
      {
        HAL_GTZC_TZIC_Callback(GTZC2_PERIPH_REG1 | position);
      }

      /* Position bit to be updated */
      position++;
    }
  }

  /* Get current IT Flags and IT sources value on 2nd register of TZIC2 */
  ier_itsources = READ_REG(GTZC_TZIC2_S->IER2);
  sr_flags      = READ_REG(GTZC_TZIC2_S->SR2);

  /* Get Mask interrupt and then clear them */
  flag = ier_itsources & sr_flags;
  if (flag != 0U)
  {
    WRITE_REG(GTZC_TZIC2_S->FCR2, flag);

    /* Loop on flag to check, which ones have been raised */
    position = 0U;
    while ((flag >> position) != 0U)
    {
      if ((flag & (1UL << position)) != 0U)
      {
        HAL_GTZC_TZIC_Callback(GTZC2_PERIPH_REG2 | position);
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

