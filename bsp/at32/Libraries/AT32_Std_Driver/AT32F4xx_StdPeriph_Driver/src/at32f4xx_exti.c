/**
 **************************************************************************
 * File Name    : at32f4xx_exti.c
 * Description  : at32f4xx EXTI source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_exti.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup EXTI
  * @brief EXTI driver modules
  * @{
  */

/** @defgroup EXTI_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Private_Defines
  * @{
  */

#define EXTI_LINENONE           ((uint32_t)0x00000)  /* No interrupt selected */

/**
  * @}
  */

/** @defgroup EXTI_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup EXTI_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the EXTI peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void EXTI_Reset(void)
{
  EXTI->INTEN = 0x00000000;
  EXTI->EVTEN = 0x00000000;
  EXTI->RTRSEL = 0x00000000;
  EXTI->FTRSEL = 0x00000000;
  EXTI->PND = 0x007FFFFF;
}

/**
  * @brief  Initializes the EXTI peripheral according to the specified
  *         parameters in the EXTI_InitStruct.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitType structure
  *         that contains the configuration information for the EXTI peripheral.
  * @retval None
  */
void EXTI_Init(EXTI_InitType* EXTI_InitStruct)
{
  uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_EXTI_MODE(EXTI_InitStruct->EXTI_Mode));
  assert_param(IS_EXTI_TRIGGER(EXTI_InitStruct->EXTI_Trigger));
  assert_param(IS_EXTI_LINE(EXTI_InitStruct->EXTI_Line));
  assert_param(IS_FUNCTIONAL_STATE(EXTI_InitStruct->EXTI_LineEnable));

  tmp = (uint32_t)EXTI_BASE;

  if (EXTI_InitStruct->EXTI_LineEnable != DISABLE)
  {
    /* Clear EXTI line configuration */
    EXTI->INTEN &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->EVTEN &= ~EXTI_InitStruct->EXTI_Line;

    tmp += EXTI_InitStruct->EXTI_Mode;

    *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;

    /* Clear Rising Falling edge configuration */
    EXTI->RTRSEL &= ~EXTI_InitStruct->EXTI_Line;
    EXTI->FTRSEL &= ~EXTI_InitStruct->EXTI_Line;

    /* Select the trigger for the selected external interrupts */
    if (EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
    {
      /* Rising Falling edge */
      EXTI->RTRSEL |= EXTI_InitStruct->EXTI_Line;
      EXTI->FTRSEL |= EXTI_InitStruct->EXTI_Line;
    }
    else
    {
      tmp = (uint32_t)EXTI_BASE;
      tmp += EXTI_InitStruct->EXTI_Trigger;

      *(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;
    }
  }
  else
  {
    tmp += EXTI_InitStruct->EXTI_Mode;

    /* Disable the selected external lines */
    *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;
  }
}

/**
  * @brief  Fills each EXTI_InitStruct member with its reset value.
  * @param  EXTI_InitStruct: pointer to a EXTI_InitType structure which will
  *         be initialized.
  * @retval None
  */
void EXTI_StructInit(EXTI_InitType* EXTI_InitStruct)
{
  EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
  EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStruct->EXTI_LineEnable = DISABLE;
}

/**
  * @brief  Generates a Software interrupt.
  * @param  EXTI_Line: specifies the EXTI lines to be enabled or disabled.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
  * @retval None
  */
void EXTI_GenerateSWInt(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->SWIE |= EXTI_Line;
}

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  EXTI_Line: specifies the EXTI line flag to check.
  *   This parameter can be:
  *     @arg EXTI_Linex: External interrupt line x where x(0..19)
  * @retval The new state of EXTI_Line (SET or RESET).
  */
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));

  if ((EXTI->PND & EXTI_Line) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
  * @brief  Clears the EXTI's line pending flags.
  * @param  EXTI_Line: specifies the EXTI lines flags to clear.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
  * @retval None
  */
void EXTI_ClearFlag(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->PND = EXTI_Line;
}

/**
  * @brief  Checks whether the specified EXTI line is asserted or not.
  * @param  EXTI_Line: specifies the EXTI line to check.
  *   This parameter can be:
  *     @arg EXTI_Linex: External interrupt line x where x(0..19)
  * @retval The new state of EXTI_Line (SET or RESET).
  */
ITStatus EXTI_GetIntStatus(uint32_t EXTI_Line)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  /* Check the parameters */
  assert_param(IS_GET_EXTI_LINE(EXTI_Line));

  enablestatus =  EXTI->INTEN & EXTI_Line;

  if (((EXTI->PND & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
  * @brief  Clears the EXTI's line pending bits.
  * @param  EXTI_Line: specifies the EXTI lines to clear.
  *   This parameter can be any combination of EXTI_Linex where x can be (0..19).
  * @retval None
  */
void EXTI_ClearIntPendingBit(uint32_t EXTI_Line)
{
  /* Check the parameters */
  assert_param(IS_EXTI_LINE(EXTI_Line));

  EXTI->PND = EXTI_Line;
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


