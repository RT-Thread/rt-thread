/**
  ******************************************************************************
  * @file    stm32l5xx_hal_exti.c
  * @author  MCD Application Team
  * @brief   EXTI HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Extended Interrupts and event controller
  *          (EXTI) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *
  @verbatim
  ==============================================================================
                    ##### EXTI Peripheral features #####
  ==============================================================================
  [..]
    (+) Each Exti line can be configured within this driver.

    (+) Exti line can be configured in 3 different modes
        (++) Interrupt
        (++) Event
        (++) Both of them

    (+) Configurable Exti lines can be configured with 3 different triggers
        (++) Rising
        (++) Falling
        (++) Both of them

    (+) When set in interrupt mode, configurable Exti lines have two different
        interrupt pending registers which allow to distinguish which transition
        occurs:
        (++) Rising edge pending interrupt
        (++) Falling

    (+) Exti lines 0 to 15 are linked to gpio pin number 0 to 15. Gpio port can
        be selected through multiplexer.

                     ##### How to use this driver #####
  ==============================================================================
  [..]

    (#) Configure the EXTI line using HAL_EXTI_SetConfigLine().
        (++) Choose the interrupt line number by setting "Line" member from
             EXTI_ConfigTypeDef structure.
        (++) Configure the interrupt and/or event mode using "Mode" member from
             EXTI_ConfigTypeDef structure.
        (++) For configurable lines, configure rising and/or falling trigger
             "Trigger" member from EXTI_ConfigTypeDef structure.
        (++) For Exti lines linked to gpio, choose gpio port using "GPIOSel"
             member from GPIO_InitTypeDef structure.

    (#) Get current Exti configuration of a dedicated line using
        HAL_EXTI_GetConfigLine().
        (++) Provide exiting handle as parameter.
        (++) Provide pointer on EXTI_ConfigTypeDef structure as second parameter.

    (#) Clear Exti configuration of a dedicated line using HAL_EXTI_GetConfigLine().
        (++) Provide exiting handle as parameter.

    (#) Register callback to treat Exti interrupts using HAL_EXTI_RegisterCallback().
        (++) Provide exiting handle as first parameter.
        (++) Provide which callback will be registered using one value from
             EXTI_CallbackIDTypeDef.
        (++) Provide callback function pointer.

    (#) Get interrupt pending bit using HAL_EXTI_GetPending().

    (#) Clear interrupt pending bit using HAL_EXTI_GetPending().

    (#) Generate software interrupt using HAL_EXTI_GenerateSWI().

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

/** @addtogroup EXTI
  * @{
  */

#ifdef HAL_EXTI_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private defines ------------------------------------------------------------*/
/** @defgroup EXTI_Private_Constants EXTI Private Constants
  * @{
  */
#define EXTI_MODE_OFFSET                    0x04U   /* byte offset between IMR/EMR registers */
#define EXTI_CONFIG_OFFSET                  0x08U   /* byte offset between Rising/Falling configuration registers */
#define EXTI_PRIVCFGR_OFFSET                0x04U   /* byte offset between PRIVCFGR1/PRIVCFGR2 registers */
#define EXTI_SECCFGR_OFFSET                 0x04U   /* byte offset between SECCFGR1/SECCFGR2 registers */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup EXTI_Exported_Functions
  * @{
  */

/** @addtogroup EXTI_Exported_Functions_Group1
 *  @brief    Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Configuration functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Set configuration of a dedicated Exti line.
  * @param  hexti Exti handle.
  * @param  pExtiConfig Pointer on EXTI configuration to be set.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig)
{
  __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;
  uint32_t offset;

  /* Check null pointer */
  if((hexti == NULL) || (pExtiConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_EXTI_LINE(pExtiConfig->Line));
  assert_param(IS_EXTI_MODE(pExtiConfig->Mode));

  /* Assign line number to handle */
  hexti->Line = pExtiConfig->Line;

  /* compute line register offset and line mask */
  offset = ((pExtiConfig->Line & EXTI_REG_MASK) >> EXTI_REG_SHIFT);
  linepos = (pExtiConfig->Line & EXTI_PIN_MASK);
  maskline = (1UL << linepos);

  /* Configure triggers for configurable lines */
  if((pExtiConfig->Line & EXTI_CONFIG) != 0U)
  {
    assert_param(IS_EXTI_TRIGGER(pExtiConfig->Trigger));

    /* Configure rising trigger */
    regaddr = (&EXTI->RTSR1 + (EXTI_CONFIG_OFFSET * offset));
    regval = *regaddr;

    /* Mask or set line */
    if((pExtiConfig->Trigger & EXTI_TRIGGER_RISING) != 0U)
    {
      regval |= maskline;
    }
    else
    {
      regval &= ~maskline;
    }

    /* Store rising trigger mode */
    *regaddr = regval;

    /* Configure falling trigger */
    regaddr = (&EXTI->FTSR1 + (EXTI_CONFIG_OFFSET * offset));
    regval = *regaddr;

    /* Mask or set line */
    if((pExtiConfig->Trigger & EXTI_TRIGGER_FALLING) != 0U)
    {
      regval |= maskline;
    }
    else
    {
      regval &= ~maskline;
    }

    /* Store falling trigger mode */
    *regaddr = regval;

    /* Configure gpio port selection in case of gpio exti line */
    if((pExtiConfig->Line & EXTI_GPIO) == EXTI_GPIO)
    {
      assert_param(IS_EXTI_GPIO_PORT(pExtiConfig->GPIOSel));
      assert_param(IS_EXTI_GPIO_PIN(linepos));

      regval = EXTI->EXTICR[linepos >> 2U];
      regval &= ~(0xFFU << (EXTI_EXTICR1_EXTI1_Pos * (linepos & 0x03U)));
      regval |= (pExtiConfig->GPIOSel << (EXTI_EXTICR1_EXTI1_Pos * (linepos & 0x03U)));
      EXTI->EXTICR[linepos >> 2U] = regval;
    }
  }

  /* Configure interrupt mode : read current mode */
  regaddr = (&EXTI->IMR1 + (EXTI_MODE_OFFSET * offset));
  regval = *regaddr;

  /* Mask or set line */
  if((pExtiConfig->Mode & EXTI_MODE_INTERRUPT) != 0U)
  {
    regval |= maskline;
  }
  else
  {
    regval &= ~maskline;
  }

  /* Store interrupt mode */
  *regaddr = regval;

  /* Configure event mode : read current mode */
  regaddr = (&EXTI->EMR1 + (EXTI_MODE_OFFSET * offset));
  regval = *regaddr;

  /* Mask or set line */
  if((pExtiConfig->Mode & EXTI_MODE_EVENT) != 0U)
  {
    regval |= maskline;
  }
  else
  {
    regval &= ~maskline;
  }

  /* Store event mode */
  *regaddr = regval;

  return HAL_OK;
}


/**
  * @brief  Get configuration of a dedicated Exti line.
  * @param  hexti Exti handle.
  * @param  pExtiConfig Pointer on structure to store Exti configuration.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig)
{
  __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;
  uint32_t offset;

  /* Check null pointer */
  if((hexti == NULL) || (pExtiConfig == NULL))
  {
    return HAL_ERROR;
  }

  /* Check the parameter */
  assert_param(IS_EXTI_LINE(hexti->Line));

  /* Store handle line number to configiguration structure */
  pExtiConfig->Line = hexti->Line;

  /* compute line register offset and line mask */
  offset = ((pExtiConfig->Line & EXTI_REG_MASK) >> EXTI_REG_SHIFT);
  linepos = (pExtiConfig->Line & EXTI_PIN_MASK);
  maskline = (1UL << linepos);

  /* 1] Get core mode : interrupt */
  regaddr = (&EXTI->IMR1 + (EXTI_MODE_OFFSET * offset));
  regval = *regaddr;

  /* Check if selected line is enable */
  if((regval & maskline) != 0U)
  {
    pExtiConfig->Mode = EXTI_MODE_INTERRUPT;
  }
  else
  {
    pExtiConfig->Mode = EXTI_MODE_NONE;
  }

  /* Get event mode */
  regaddr = (&EXTI->EMR1 + (EXTI_MODE_OFFSET * offset));
  regval = *regaddr;

  /* Check if selected line is enable */
  if((regval & maskline) != 0U)
  {
    pExtiConfig->Mode |= EXTI_MODE_EVENT;
  }

  /* 2] Get trigger for configurable lines : rising */
  if((pExtiConfig->Line & EXTI_CONFIG) != 0U)
  {
    regaddr = (&EXTI->RTSR1 + (EXTI_CONFIG_OFFSET * offset));
    regval = *regaddr;

    /* Check if configuration of selected line is enable */
    if((regval & maskline) != 0U)
    {
      pExtiConfig->Trigger = EXTI_TRIGGER_RISING;
    }
    else
    {
      pExtiConfig->Trigger = EXTI_TRIGGER_NONE;
    }

    /* Get falling configuration */
    regaddr = (&EXTI->FTSR1 + (EXTI_CONFIG_OFFSET * offset));
    regval = *regaddr;

    /* Check if configuration of selected line is enable */
    if((regval & maskline) != 0U)
    {
      pExtiConfig->Trigger |= EXTI_TRIGGER_FALLING;
    }

    /* Get Gpio port selection for gpio lines */
    if((pExtiConfig->Line & EXTI_GPIO) == EXTI_GPIO)
    {
      assert_param(IS_EXTI_GPIO_PIN(linepos));

      regval = EXTI->EXTICR[linepos >> 2U];
      pExtiConfig->GPIOSel = ((regval << (EXTI_EXTICR1_EXTI1_Pos * (3U - (linepos & 0x03U)))) >> 24U);
    }
    else
    {
      pExtiConfig->GPIOSel = 0U;
    }
  }
  else
  {
    pExtiConfig->Trigger = EXTI_TRIGGER_NONE;
    pExtiConfig->GPIOSel = 0U;
  }

  return HAL_OK;
}


/**
  * @brief  Clear whole configuration of a dedicated Exti line.
  * @param  hexti Exti handle.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti)
{
  __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;
  uint32_t offset;

  /* Check null pointer */
  if(hexti == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameter */
  assert_param(IS_EXTI_LINE(hexti->Line));

  /* compute line register offset and line mask */
  offset = ((hexti->Line & EXTI_REG_MASK) >> EXTI_REG_SHIFT);
  linepos = (hexti->Line & EXTI_PIN_MASK);
  maskline = (1UL << linepos);

  /* 1] Clear interrupt mode */
  regaddr = (&EXTI->IMR1 + (EXTI_MODE_OFFSET * offset));
  regval = (*regaddr & ~maskline);
  *regaddr = regval;

  /* 2] Clear event mode */
  regaddr = (&EXTI->EMR1 + (EXTI_MODE_OFFSET * offset));
  regval = (*regaddr & ~maskline);
  *regaddr = regval;

  /* 3] Clear triggers in case of configurable lines */
  if((hexti->Line & EXTI_CONFIG) != 0U)
  {
    regaddr = (&EXTI->RTSR1 + (EXTI_CONFIG_OFFSET * offset));
    regval = (*regaddr & ~maskline);
    *regaddr = regval;

    regaddr = (&EXTI->FTSR1 + (EXTI_CONFIG_OFFSET * offset));
    regval = (*regaddr & ~maskline);
    *regaddr = regval;

    /* Get Gpio port selection for gpio lines */
    if((hexti->Line & EXTI_GPIO) == EXTI_GPIO)
    {
      assert_param(IS_EXTI_GPIO_PIN(linepos));

      regval = EXTI->EXTICR[linepos >> 2U];
      regval &= ~(0xFFU << (EXTI_EXTICR1_EXTI1_Pos * (linepos & 0x03U)));
      EXTI->EXTICR[linepos >> 2U] = regval;
    }
  }

  return HAL_OK;
}


/**
  * @brief  Register callback for a dedicaated Exti line.
  * @param  hexti Exti handle.
  * @param  CallbackID User callback identifier.
  *         This parameter can be one of @arg @ref EXTI_CallbackIDTypeDef values.
  * @param  pPendingCbfn function pointer to be stored as callback.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void))
{
  HAL_StatusTypeDef status = HAL_OK;

  switch (CallbackID)
  {
    case  HAL_EXTI_COMMON_CB_ID:
      hexti->RisingCallback = pPendingCbfn;
      hexti->FallingCallback = pPendingCbfn;
      break;

    case  HAL_EXTI_RISING_CB_ID:
      hexti->RisingCallback = pPendingCbfn;
      break;

    case  HAL_EXTI_FALLING_CB_ID:
      hexti->FallingCallback = pPendingCbfn;
      break;

    default:
      status = HAL_ERROR;
      break;
  }

  return status;
}


/**
  * @brief  Store line number as handle private field.
  * @param  hexti Exti handle.
  * @param  ExtiLine Exti line number.
  *         This parameter can be from 0 to @ref EXTI_LINE_NB.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine)
{
  /* Check null pointer */
  if(hexti == NULL)
  {
    return HAL_ERROR;
  }

  /* Check parameters */
  assert_param(IS_EXTI_LINE(ExtiLine));

  /* Store line number as handle private field */
  hexti->Line = ExtiLine;

  return HAL_OK;
}


/**
  * @}
  */

/** @addtogroup EXTI_Exported_Functions_Group2
 *  @brief EXTI IO functions.
 *
@verbatim
 ===============================================================================
                       ##### IO operation functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Handle EXTI interrupt request.
  * @param  hexti Exti handle.
  * @retval none.
  */
void HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti)
{
  __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t maskline;
  uint32_t offset;

  /* Compute line register offset and line mask */
  offset = ((hexti->Line & EXTI_REG_MASK) >> EXTI_REG_SHIFT);
  maskline = (1UL << (hexti->Line & EXTI_PIN_MASK));

  /* Get rising edge pending bit  */
  regaddr = (&EXTI->RPR1 + (EXTI_CONFIG_OFFSET * offset));
  regval = (*regaddr & maskline);

  if(regval != 0U)
  {
    /* Clear pending bit */
    *regaddr = maskline;

    /* Call rising callback */
    if(hexti->RisingCallback != NULL)
    {
      hexti->RisingCallback();
    }
  }

  /* Get falling edge pending bit  */
  regaddr = (&EXTI->FPR1 + (EXTI_CONFIG_OFFSET * offset));
  regval = (*regaddr & maskline);

  if(regval != 0U)
  {
    /* Clear pending bit */
    *regaddr = maskline;

    /* Call rising callback */
    if(hexti->FallingCallback != NULL)
    {
      hexti->FallingCallback();
    }
  }
}


/**
  * @brief  Get interrupt pending bit of a dedicated line.
  * @param  hexti Exti handle.
  * @param  Edge Specify which pending edge as to be checked.
  *         This parameter can be one of the following values:
  *           @arg @ref EXTI_TRIGGER_RISING
  *           @arg @ref EXTI_TRIGGER_FALLING
  * @retval 1 if interrupt is pending else 0.
  */
uint32_t HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti, uint32_t Edge)
{
  __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_EXTI_LINE(hexti->Line));
  assert_param(IS_EXTI_CONFIG_LINE(hexti->Line));
  assert_param(IS_EXTI_PENDING_EDGE(Edge));

  /* compute line register offset and line mask */
  offset = ((hexti->Line & EXTI_REG_MASK) >> EXTI_REG_SHIFT);
  linepos = (hexti->Line & EXTI_PIN_MASK);
  maskline = (1UL << linepos);

  if(Edge != EXTI_TRIGGER_RISING)
  {
    /* Get falling edge pending bit */
    regaddr = (&EXTI->FPR1 + (EXTI_CONFIG_OFFSET * offset));
  }
  else
  {
    /* Get rising edge pending bit */
    regaddr = (&EXTI->RPR1 + (EXTI_CONFIG_OFFSET * offset));
  }

  /* return 1 if bit is set else 0 */
  regval = ((*regaddr & maskline) >> linepos);
  return regval;
}


/**
  * @brief  Clear interrupt pending bit of a dedicated line.
  * @param  hexti Exti handle.
  * @param  Edge Specify which pending edge as to be clear.
  *         This parameter can be one of the following values:
  *           @arg @ref EXTI_TRIGGER_RISING
  *           @arg @ref EXTI_TRIGGER_FALLING
  * @retval None.
  */
void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge)
{
  __IO uint32_t *regaddr;
  uint32_t maskline;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_EXTI_LINE(hexti->Line));
  assert_param(IS_EXTI_CONFIG_LINE(hexti->Line));
  assert_param(IS_EXTI_PENDING_EDGE(Edge));

  /* compute line register offset and line mask */
  offset = ((hexti->Line & EXTI_REG_MASK) >> EXTI_REG_SHIFT);
  maskline = (1UL << (hexti->Line & EXTI_PIN_MASK));

  if(Edge != EXTI_TRIGGER_RISING)
  {
    /* Get falling edge pending register address */
    regaddr = (&EXTI->FPR1 + (EXTI_CONFIG_OFFSET * offset));
  }
  else
  {
    /* Get falling edge pending register address */
    regaddr = (&EXTI->RPR1 + (EXTI_CONFIG_OFFSET * offset));
  }

  /* Clear Pending bit */
  *regaddr =  maskline;
}


/**
  * @brief  Generate a software interrupt for a dedicated line.
  * @param  hexti Exti handle.
  * @retval None.
  */
void HAL_EXTI_GenerateSWI(EXTI_HandleTypeDef *hexti)
{
  __IO uint32_t *regaddr;
  uint32_t maskline;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_EXTI_LINE(hexti->Line));
  assert_param(IS_EXTI_CONFIG_LINE(hexti->Line));

  /* compute line register offset and line mask */
  offset = ((hexti->Line & EXTI_REG_MASK) >> EXTI_REG_SHIFT);
  maskline = (1UL << (hexti->Line & EXTI_PIN_MASK));

  regaddr = (&EXTI->SWIER1 + (EXTI_CONFIG_OFFSET * offset));
  *regaddr = maskline;
}


/**
  * @}
  */

/** @defgroup EXTI_Exported_Functions_Group3 EXTI line attributes management functions
 *  @brief EXTI attributes management functions.
 *
@verbatim
 ===============================================================================
                       ##### EXTI attributes functions #####
 ===============================================================================

@endverbatim
  * @{
  */

/**
  * @brief  Configure the EXTI line attribute(s).
  * @note   Available attributes are to secure EXTI line and set EXT line as privileged.
  *         Default state is not secure and unprivileged access allowed.
  * @note   Secure and non-secure attributes can only be set from the secure
  *         state when the system implements the security (TZEN=1).
  * @note   Security and privilege attributes can be set independently.
  * @param  ExtiLine Exti line number.
  *         This parameter can be from 0 to @ref EXTI_LINE_NB.
  * @param  LineAttributes can be one or a combination of the following values:
  *            @arg @ref EXTI_LINE_PRIV         Privileged-only access
  *            @arg @ref EXTI_LINE_NPRIV        Privileged/Non-privileged access
  *            @arg @ref EXTI_LINE_SEC          Secure-only access
  *            @arg @ref EXTI_LINE_NSEC         Secure/Non-secure access
  * @retval None
  */
void HAL_EXTI_ConfigLineAttributes(uint32_t ExtiLine, uint32_t LineAttributes)
{
  __IO uint32_t *regaddr;
  uint32_t regval;
  uint32_t linepos;
  uint32_t maskline;
  uint32_t offset;

  /* Check the parameters */
  assert_param(IS_EXTI_LINE(ExtiLine));
  assert_param(IS_EXTI_LINE_ATTRIBUTES(LineAttributes));

  /* compute line register offset and line mask */
  offset = ((ExtiLine & EXTI_REG_MASK) >> EXTI_REG_SHIFT);
  linepos = (ExtiLine & EXTI_PIN_MASK);
  maskline = (1UL << linepos);

  /* Configure privilege or non-privilege attributes */
  regaddr = (&EXTI->PRIVCFGR1 + (EXTI_PRIVCFGR_OFFSET * offset));
  regval = *regaddr;

  /* Mask or set line */
  if((LineAttributes & EXTI_LINE_PRIV) == EXTI_LINE_PRIV)
  {
    regval |= maskline;
  }
  else if((LineAttributes & EXTI_LINE_NPRIV) == EXTI_LINE_NPRIV)
  {
    regval &= ~maskline;
  }
  else
  {
    /* do nothing */
  }

  /* Store privilege or non-privilege attribute */
  *regaddr = regval;

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

  /* Configure secure or non-secure attributes */
  regaddr = (&EXTI->SECCFGR1 + (EXTI_SECCFGR_OFFSET * offset));
  regval = *regaddr;

  /* Mask or set line */
  if((LineAttributes & EXTI_LINE_SEC) == EXTI_LINE_SEC)
  {
    regval |= maskline;
  }
  else if((LineAttributes & EXTI_LINE_NSEC) == EXTI_LINE_NSEC)
  {
    regval &= ~maskline;
  }
  else
  {
    /* do nothing */
  }

  /* Store secure or non-secure attribute */
  *regaddr = regval;

#endif /* __ARM_FEATURE_CMSE */
}

/**
  * @brief  Get the EXTI line attribute(s).
  * @note   Secure and non-secure attributes are only available from secure state
  *         when the system implements the security (TZEN=1)
  * @param  ExtiLine Exti line number.
  *         This parameter can be from 0 to @ref EXTI_LINE_NB.
  * @param  pLineAttributes: pointer to return line attributes.
  * @retval HAL Status.
  */
HAL_StatusTypeDef HAL_EXTI_GetConfigLineAttributes(uint32_t ExtiLine, uint32_t *pLineAttributes)
{
  __IO uint32_t *regaddr;
  uint32_t linepos;
  uint32_t maskline;
  uint32_t offset;
  uint32_t attributes;

  /* Check null pointer */
  if(pLineAttributes == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_EXTI_LINE(ExtiLine));

  /* Compute line register offset and line mask */
  offset = ((ExtiLine & EXTI_REG_MASK) >> EXTI_REG_SHIFT);
  linepos = (ExtiLine & EXTI_PIN_MASK);
  maskline = (1UL << linepos);

  /* Get privilege or non-privilege attribute */
  regaddr = (&EXTI->PRIVCFGR1 + (EXTI_PRIVCFGR_OFFSET * offset));

  if((*regaddr & maskline) != 0U)
  {
    attributes = EXTI_LINE_PRIV;
  }
  else
  {
    attributes = EXTI_LINE_NPRIV;
  }

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

  /* Get secure or non-secure attribute */
  regaddr = (&EXTI->SECCFGR1 + (EXTI_SECCFGR_OFFSET * offset));

  if((*regaddr & maskline) != 0U)
  {
    attributes |= EXTI_LINE_SEC;
  }
  else
  {
    attributes |= EXTI_LINE_NSEC;
  }

#endif /* __ARM_FEATURE_CMSE */

  /* return value */
  *pLineAttributes = attributes;

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_EXTI_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
