/**
  ******************************************************************************
  * @file    stm32wlxx_hal_gtzc.c
  * @author  MCD Application Team
  * @brief   GTZC HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of GTZC peripheral:
  *           + TZSC Initialization and Configuration functions
  *           + MPCWM Initialization and Configuration functions
  *           + TZSC and TZSC-MPCWM Lock functions
  *           + TZIC Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
                ##### GTZC main features #####
  ==============================================================================
  [..]
    (+) Global Security Controller (GTZC) composed of two sub-blocks:
      (++) TZSC: Security controller
            This sub-block defines the secure/privileged state of slave
            peripherals. It also controls the unprivileged area size for the
            watermark memory peripheral controller (MPCWM).
      (++) TZIC: Security Illegal access controller
            This sub-block gathers all illegal access events in the system and
            generates a secure interrupt towards the secure CPU2 NVIC.

    (+) These sub-blocks are used to configure system security and
        privilege such as:
      (++) on-chip Flash memory and RAM with programmable secure or privilege or
      both area
      (++) AHB and APB peripherals with programmable security and/or privileged
      access

  [..]
    (+) TZIC accessible only with secure privileged transactions.
        When the system is non-secure (ESE = 0), TZIC is not accessible.
    (+) Secure and non-secure access supported for privileged and unprivileged
        part of TZSC
    (+) Set of registers to define product security settings:
      (++) Privileged watermark for internal memories
      (++) Secure and privileged access mode for securable peripherals

  ==============================================================================
                  ##### How to use this driver #####
  ==============================================================================
  [..]
    The GTZC HAL driver can be used as follows:

    (#) Configure or get back securable peripherals attributes using
        HAL_GTZC_TZSC_ConfigPeriphAttributes() / HAL_GTZC_TZSC_GetConfigPeriphAttributes()

    (#) Configure or get back ecurable peripherals attributes using
        HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes() / HAL_GTZC_TZSC_MPCWM_GetConfigMemAttributes()
    (#) Lock TZSC sub-block or get lock status using HAL_GTZC_TZSC_Lock() /
        HAL_GTZC_TZSC_GetLock()

    (#) Illegal access detection can be configured through TZIC sub-block using
        following functions: HAL_GTZC_TZIC_DisableIT() / HAL_GTZC_TZIC_EnableIT()

    (#) Illegal access flags can be retrieved through HAL_GTZC_TZIC_GetFlag() and
        HAL_GTZC_TZIC_ClearFlag() functions

    (#) Illegal access interrupt service routing is served by HAL_GTZC_IRQHandler()
        and user can add his own code using HAL_GTZC_TZIC_ILA_Callback()

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32wlxx_hal.h"

#if defined(GTZC_TZSC)
/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @defgroup GTZC GTZC
  * @brief GTZC HAL module driver
  * @{
  */

#ifdef HAL_GTZC_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private Constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @defgroup GTZC_Exported_Functions GTZC Exported Functions
  * @{
  */

/** @defgroup GTZC_Exported_Functions_Group1 TZSC Initialization and Configuration functions
  * @brief    TZSC Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
            ##### TZSC Initialization and Configuration functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to initialize/configure TZSC
    TZSC: Security Controller
  @endverbatim
  * @{
  */

/**
  * @brief  Configure TZSC on a single peripheral or on all peripherals
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_Peripheral_Identification
  * @param  PeriphAttributes Periph attribute  (see structure in stm32wlxx_hal_gtzc.h).
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_GTZC_TZSC_ConfigPeriphAttributes(uint32_t PeriphId, uint32_t PeriphAttributes)
{
  uint32_t periphpos;

  /* check entry parameters */
  assert_param(IS_GTZC_TZSC_PERIPHERAL(PeriphId));
  assert_param(IS_GTZC_ATTRIBUTE(PeriphAttributes));

  if ((PeriphId & GTZC_PERIPH_ALL) != 0x00U)
  {
    /* special case where the same configuration is applied to all peripherals */

#if defined(CORE_CM0PLUS)
    /* secure configuration */
    if ((PeriphAttributes & GTZC_TZSC_ATTRIBUTE_SEC) != 0x00U)
    {
      GTZC_TZSC->SECCFGR1 = TZSC_SECCFGR1_ALL_Msk;
    }
    else
    {
      GTZC_TZSC->SECCFGR1 = 0x00U;
    }
#endif

    /* privilege configuration */
    if ((PeriphAttributes & GTZC_TZSC_ATTRIBUTE_PRIV) != 0x00U)
    {
      GTZC_TZSC->PRIVCFGR1 = TZSC_PRIVCFGR1_ALL_Msk;
    }
    else
    {
      GTZC_TZSC->PRIVCFGR1 = 0x00U;
    }
  }
  else
  {
    /* common case where only one peripheral is configured */
    periphpos = (1UL << GTZC_GET_PERIPH_POS(PeriphId));

#if defined(CORE_CM0PLUS)
    /* secure configuration. Make sure not to configure SUBGHZ SPI which is securable by option byte. */
    if ((PeriphId != GTZC_PERIPH_SUBGHZSPI) && ((PeriphAttributes & GTZC_TZSC_ATTRIBUTE_SEC) != 0x00U))
    {
      GTZC_TZSC->SECCFGR1 |= periphpos;
    }
    else
    {
      GTZC_TZSC->SECCFGR1 &= ~periphpos;
    }
#endif

    /* privilege configuration */
    if ((PeriphAttributes & GTZC_TZSC_ATTRIBUTE_PRIV) != 0x00U)
    {
      GTZC_TZSC->PRIVCFGR1 |= periphpos;
    }
    else
    {
      GTZC_TZSC->PRIVCFGR1 &= ~periphpos;
    }
  }

  return HAL_OK;
}


/**
  * @brief  Get TZSC configuration on a single peripheral or on all peripherals
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_Peripheral_Identification
  * @param  PeriphAttributes Pointer to the periph attributes (see structure in stm32wlxx_hal_gtzc.h).
  *         If PeriphId target a single peripheral, pointer on a single element.
  *         If all peripherals selected, pointer to an array of GTZC_PERIPH_TZSC_MAX elements
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_GTZC_TZSC_GetConfigPeriphAttributes(uint32_t PeriphId, uint32_t *PeriphAttributes)
{
  uint32_t reg_value;
  uint32_t periphpos;
  uint32_t index;

  /* check entry parameters */
  assert_param(IS_GTZC_TZSC_PERIPHERAL(PeriphId));

  /* check null pointer */
  if (PeriphAttributes == NULL)
  {
    return HAL_ERROR;
  }

  if ((PeriphId & GTZC_PERIPH_ALL) != 0x00U)
  {

    /* special case where the configuration getting is requested for all peripherals */
    /* get secure configuration: read each register and deploy each bit value */
    /* in bit0 of corresponding index in the destination array */
    reg_value = (GTZC_TZSC->SECCFGR1 & TZSC_SECCFGR1_ALL_Msk);
    periphpos = 0;
    for (index = 0U; index < GTZC_TZSC_PERIPH_NUMBER; index++)
    {
      /* Check what are TZSC peripheral position. Here use privilege mask as
        reference because SPISUBGHZ is securable by option byte */
      while((TZSC_PRIVCFGR1_ALL_Msk & (1UL << periphpos)) == 0x00U)
      {
        /* increment peripheral position */
        periphpos++;
      }

      if ((reg_value & (1UL << periphpos)) != 0x00U)
      {
        PeriphAttributes[index] = GTZC_TZSC_ATTRIBUTE_SEC;
      }
      else
      {
        PeriphAttributes[index] = GTZC_TZSC_ATTRIBUTE_NSEC;
      }

      /* increment peripheral position */
        periphpos++;
    }

    /* do the same for get privilege configuration but on bit1 */
    reg_value = (GTZC_TZSC->PRIVCFGR1 & TZSC_PRIVCFGR1_ALL_Msk);
    periphpos = 0;
    for (index = 0U; index < GTZC_TZSC_PERIPH_NUMBER; index++)
    {
      /* Check what are TZSC peripheral position */
      while((TZSC_PRIVCFGR1_ALL_Msk & (1UL << periphpos)) == 0x00U)
      {
        /* increment peripheral position */
        periphpos++;
      }

      if ((reg_value & (1UL << periphpos)) != 0x00U)
      {
        PeriphAttributes[index] |= GTZC_TZSC_ATTRIBUTE_PRIV;
      }
      else
      {
        /* do nothing */
      }

      /* increment peripheral position */
        periphpos++;
    }
  }
  else
  {
    /* common case where only one peripheral is configured */
    /* secure configuration */
    reg_value = GTZC_TZSC->SECCFGR1;

    if ((reg_value & (1UL << GTZC_GET_PERIPH_POS(PeriphId))) != 0x00U)
    {
      *PeriphAttributes = GTZC_TZSC_ATTRIBUTE_SEC;
    }
    else
    {
      *(PeriphAttributes) = GTZC_TZSC_ATTRIBUTE_NSEC;
    }

    /* privilege configuration */
    reg_value = GTZC_TZSC->PRIVCFGR1;

    if ((reg_value & (1UL << GTZC_GET_PERIPH_POS(PeriphId))) != 0x00U)
    {
      *PeriphAttributes |= GTZC_TZSC_ATTRIBUTE_PRIV;
    }
    else
    {
      /* do nothing */
    }
  }
  return HAL_OK;
}

/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group2 MPCWM Initialization and Configuration functions
  * @brief    MPCWM Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
            ##### MPCWM Initialization and Configuration functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to initialize/configure MPCWM
    MPCWM: Memory Protection Controller WaterMark
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
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_ConfigMemAttributes(uint32_t MemBaseAddress, MPCWM_ConfigTypeDef *pMPCWM_Desc)
{
  __IO uint32_t *pregister;
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t reg_value;
  uint32_t length_pos;
  uint32_t length_msk;
  uint32_t gran_offset;

  /* check entry parameters */
  assert_param(IS_GTZC_MPCWM_MEMORY_BASEADDRESS(MemBaseAddress));

  switch (MemBaseAddress)
  {
    case FLASH_BASE:
      /* check descriptor content vs. memory capacity */
      assert_param(IS_GTZC_MPCWM_FLASH_AREAID(pMPCWM_Desc->AreaId));
      assert_param(IS_GTZC_MPCWM_FLASH_LENGTH(pMPCWM_Desc->Length));

      /* Set local variable with Flash MPCWM characteristics */
      gran_offset = GTZC_TZSC_MPCWM_GRANULARITY_FLASH_OFFSET;
      if (pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_AREAID_UNPRIV)
      {
        pregister = &(GTZC_TZSC->MPCWM1_UPWMR);
        length_pos = TZSC_MPCWM1_UPWMR_LGTH_Pos;
        length_msk = TZSC_MPCWM1_UPWMR_LGTH_Msk;
      }
      else
      {
        pregister = &(GTZC_TZSC->MPCWM1_UPWWMR);
        length_pos = TZSC_MPCWM1_UPWWMR_LGTH_Pos;
        length_msk = TZSC_MPCWM1_UPWWMR_LGTH_Msk;
      }
      break;

    case SRAM1_BASE:
      /* check descriptor content vs. memory capacity */
      assert_param(IS_GTZC_MPCWM_SRAM1_AREAID(pMPCWM_Desc->AreaId));
      assert_param(IS_GTZC_MPCWM_SRAM1_LENGTH(pMPCWM_Desc->Length));

      /* Set local variable with Sram1 MPCWM characteristics */
      gran_offset = GTZC_TZSC_MPCWM_GRANULARITY_SRAM1_OFFSET;
      pregister = &(GTZC_TZSC->MPCWM2_UPWMR);
      length_pos = TZSC_MPCWM2_UPWMR_LGTH_Pos;
      length_msk = TZSC_MPCWM2_UPWMR_LGTH_Msk;
      break;

    case SRAM2_BASE:
      /* check descriptor content vs. memory capacity */
      assert_param(IS_GTZC_MPCWM_SRAM2_AREAID(pMPCWM_Desc->AreaId));
      assert_param(IS_GTZC_MPCWM_SRAM2_LENGTH(pMPCWM_Desc->Length));

      /* Set local variable with Sram2 MPCWM characteristics */
      gran_offset = GTZC_TZSC_MPCWM_GRANULARITY_SRAM2_OFFSET;
      pregister = &(GTZC_TZSC->MPCWM3_UPWMR);
      length_pos = TZSC_MPCWM3_UPWMR_LGTH_Pos;
      length_msk = TZSC_MPCWM3_UPWMR_LGTH_Msk;
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  if(status != HAL_ERROR)
  {
    /* Store length */
    reg_value = *pregister & ~length_msk;
    *pregister = (reg_value | ((pMPCWM_Desc->Length >> gran_offset) << length_pos));
  }
  else
  {
    /* Do nothing */
  }

  return status;
}


/**
  * @brief  Get a TZSC-MPCWM area configuration.
  * @param  MemBaseAddress WM identifier.
  * @param  pMPCWM_Desc pointer to a TZSC-MPCWM descriptor.
  *         The structure description is available in @ref GTZC_Exported_Types.
  * @retval HAL status.
  */
HAL_StatusTypeDef HAL_GTZC_TZSC_MPCWM_GetConfigMemAttributes(uint32_t MemBaseAddress, MPCWM_ConfigTypeDef *pMPCWM_Desc)
{
  __IO uint32_t *pregister;
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t reg_value;
  uint32_t length_pos;
  uint32_t length_msk;
  uint32_t gran_offset;

  /* check entry parameters */
  assert_param(IS_GTZC_MPCWM_MEMORY_BASEADDRESS(MemBaseAddress));

  /* depending on targted memory */
  switch (MemBaseAddress)
  {
    case FLASH_BASE:
      /* check descriptor content vs. memory capacity */
      assert_param(IS_GTZC_MPCWM_FLASH_AREAID(pMPCWM_Desc->AreaId));

      /* Set local variable with Flash MPCWM characteristics */
      gran_offset = GTZC_TZSC_MPCWM_GRANULARITY_FLASH_OFFSET;
      if (pMPCWM_Desc->AreaId == GTZC_TZSC_MPCWM_AREAID_UNPRIV)
      {
        pregister = &(GTZC_TZSC->MPCWM1_UPWMR);
        length_pos = TZSC_MPCWM1_UPWMR_LGTH_Pos;
        length_msk = TZSC_MPCWM1_UPWMR_LGTH_Msk;
      }
      else
      {
        pregister = &(GTZC_TZSC->MPCWM1_UPWWMR);
        length_pos = TZSC_MPCWM1_UPWWMR_LGTH_Pos;
        length_msk = TZSC_MPCWM1_UPWWMR_LGTH_Msk;
      }
      break;

    case SRAM1_BASE:
      /* check descriptor content vs. memory capacity */
      assert_param(IS_GTZC_MPCWM_SRAM1_AREAID(pMPCWM_Desc->AreaId));

      /* Set local variable with Sram1 MPCWM characteristics */
      gran_offset = GTZC_TZSC_MPCWM_GRANULARITY_SRAM1_OFFSET;
      pregister = &(GTZC_TZSC->MPCWM2_UPWMR);
      length_pos = TZSC_MPCWM2_UPWMR_LGTH_Pos;
      length_msk = TZSC_MPCWM2_UPWMR_LGTH_Msk;

      break;

    case SRAM2_BASE:
      /* check descriptor content vs. memory capacity */
      assert_param(IS_GTZC_MPCWM_SRAM2_AREAID(pMPCWM_Desc->AreaId));

      /* Set local variable with Sram2 MPCWM characteristics */
      gran_offset = GTZC_TZSC_MPCWM_GRANULARITY_SRAM2_OFFSET;
      pregister = &(GTZC_TZSC->MPCWM3_UPWMR);
      length_pos = TZSC_MPCWM3_UPWMR_LGTH_Pos;
      length_msk = TZSC_MPCWM3_UPWMR_LGTH_Msk;
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  if(status != HAL_ERROR)
  {
    /* Store length */
    reg_value = (*pregister & length_msk) >> length_pos;
    pMPCWM_Desc->Length = (reg_value << gran_offset);
  }
  else
  {
    /* Do nothing */
  }

  return status;
}


/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group3 TZSC and TZSC-MPCWM Lock functions
  * @brief    TZSC-MPCWM Lock functions
  *
  @verbatim
  ==============================================================================
            ##### TZSC and TZSC-MPCWM Lock functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to manage the common TZSC and TZSC-MPCWM lock.
    It includes lock enable, and current value read.
    TZSC: Security Controller
    MPCWM: Memory Protection Controller WaterMark
  @endverbatim
  * @{
  */

/**
  * @brief  Get TZSC and TZSC-MPCWM configuration lock state.
  * @param  TZSCx TZSC sub-block instance.
  * @retval Lock State (GTZC_TZSC_LOCK_OFF or GTZC_TZSC_LOCK_ON)
  */
uint32_t HAL_GTZC_TZSC_GetLock(GTZC_TZSC_TypeDef *TZSCx)
{
  return (READ_BIT(TZSCx->CR, TZSC_CR_LCK_Msk) >> TZSC_CR_LCK_Pos);
}


#if defined(CORE_CM0PLUS)
/**
  * @brief  Lock TZSC and TZSC-MPCWM configuration.
  * @param  TZSCx TZSC sub-block instance.
  * @retval None
  */
void HAL_GTZC_TZSC_Lock(GTZC_TZSC_TypeDef *TZSCx)
{
  SET_BIT(TZSCx->CR, TZSC_CR_LCK_Msk);
}

/**
  * @}
  */

/** @defgroup GTZC_Exported_Functions_Group4 TZIC Initialization and Configuration functions
  * @brief    TZIC Initialization and Configuration functions
  *
  @verbatim
  ==============================================================================
            ##### TZIC Initialization and Configuration functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to initialize/configure TZIC
    TZIC: Security Interrupt Controller
  @endverbatim
  * @{
  */

/**
  * @brief  Disable an IT on a single TZIC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_Peripheral_Identification
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_GTZC_TZIC_DisableIT(uint32_t PeriphId)
{
  /* check entry parameter */
  assert_param(IS_GTZC_TZIC_PERIPHERAL(PeriphId));

  if ((PeriphId & GTZC_PERIPH_ALL) != 0x00U)
  {
    /* special case where the same configuration is applied to all peripherals */
    WRITE_REG(GTZC_TZIC->IER1, 0U);
  }
  else
  {
    uint32_t register_address;

    /* common case where only one peripheral is configured */
    register_address = (uint32_t)&(GTZC_TZIC->IER1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    CLEAR_BIT(*(uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
  }

  return HAL_OK;
}

/**
  * @brief  Enable an interrupt on a single TZIC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_Peripheral_Identification
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_GTZC_TZIC_EnableIT(uint32_t PeriphId)
{
  /* check entry parameter */
  assert_param(IS_GTZC_TZIC_PERIPHERAL(PeriphId));

  if ((PeriphId & GTZC_PERIPH_ALL) != 0x00U)
  {
    /* special case where the same configuration is applied to all peripherals */
    WRITE_REG(GTZC_TZIC->IER1, TZIC_IER1_ALL_Msk);
  }
  else
  {
    uint32_t register_address;

    /* common case where only one peripheral is configured */
    register_address = (uint32_t)&(GTZC_TZIC->IER1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    SET_BIT(*(uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
  }

  return HAL_OK;
}


/**
  * @brief  Get interrupt flag on a single TZIC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_Peripheral_Identification
  * @param  pFlag Pointer to the flags.
  *         If PeriphId target a single peripheral, pointer on a single element.
  *         If all peripherals selected, pointer to an array of GTZC_PERIPH_TZIC_MAX elements
  *         Element content is either GTZC_TZIC_NO_ILA_EVENT or GTZC_TZIC_ILA_EVENT_PENDING
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_GTZC_TZIC_GetFlag(uint32_t PeriphId, uint32_t *pFlag)
{
  /* check entry parameter */
  assert_param(IS_GTZC_TZIC_PERIPHERAL(PeriphId));

  if ((PeriphId & GTZC_PERIPH_ALL) != 0x00U)
  {
    uint32_t i;
    uint32_t reg_value;

    /* special case where it is applied to all peripherals */
    reg_value = READ_REG(GTZC_TZIC->MISR1);
    for (i = 0U; i < GTZC_TZIC_PERIPH_NUMBER; i++)
    {
      pFlag[i] = (reg_value & (1UL << i)) >> i;
    }
  }
  else
  {
    uint32_t register_address;

    /* common case where only one peripheral is concerned */
    register_address = (uint32_t)&(GTZC_TZIC->MISR1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    *pFlag = READ_BIT(*(uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId)) >> GTZC_GET_PERIPH_POS(PeriphId);
  }

  return HAL_OK;
}


/**
  * @brief  Clear interrupt flag on a single TZIC peripheral or on all peripherals.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_Peripheral_Identification
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_GTZC_TZIC_ClearFlag(uint32_t PeriphId)
{
  /* check entry parameter */
  assert_param(IS_GTZC_TZIC_PERIPHERAL(PeriphId));

  if ((PeriphId & GTZC_PERIPH_ALL) != 0x00U)
  {
    /* special case where the same configuration is applied to all peripherals */
    WRITE_REG(GTZC_TZIC->ICR1, TZIC_IER1_ALL_Msk);
  }
  else
  {
    uint32_t register_address;

    /* common case where only one peripheral is configured */
    register_address = (uint32_t)&(GTZC_TZIC->ICR1) + (4U * GTZC_GET_REG_INDEX(PeriphId));
    SET_BIT(*(uint32_t *)register_address, 1UL << GTZC_GET_PERIPH_POS(PeriphId));
  }

  return HAL_OK;
}

/**
  * @}
  */


/** @defgroup GTZC_Exported_Functions_Group5 TZIC IRQ Handler and Callback
  * @brief    TZIC IRQ Handler and Callback
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
  * @brief  Handle GTZC TZIC interrupt request.
  * @param  none
  * @retval None
  */
void HAL_GTZC_IRQHandler(void)
{
  uint32_t position = 0x00u;
  uint32_t flag;

  /* Get Mask interrupt and then clear them */
  flag = GTZC_TZIC->MISR1;
  GTZC_TZIC->ICR1 = flag;

  /* Loop on flag to check, which ones have been raised */
  while ((flag >> position) != 0x00u)
  {
    if ((flag & (1UL << position)) != 0x00u)
    {
      HAL_GTZC_TZIC_Callback(GTZC_PERIPH_REG1 | position);
    }

    /* Position bit to be updated */
    position++;
  }
}


/**
  * @brief  GTZC TZIC Illegal Access callback.
  * @param  PeriphId Peripheral identifier.
  *         This parameter can be a value of @ref GTZC_Peripheral_Identification
  * @retval None
  */
__weak void HAL_GTZC_TZIC_Callback(uint32_t PeriphId)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(PeriphId);

  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GTZC_TZIC_Callback could be implemented in the user file
   */
}

#endif
/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_GTZC_MODULE_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
#endif /* GTZC_TZSC */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
