/**
 **************************************************************************
 * File Name    : at32f4xx_iwdg.c
 * Description  : at32f4xx IWDG source file
 * Date         : 2018-02-26
 * Version      : V1.0.4
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_iwdg.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup IWDG
  * @brief IWDG driver modules
  * @{
  */

/** @defgroup IWDG_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Private_Defines
  * @{
  */

/* ---------------------- IWDG registers bit mask ----------------------------*/

/* KR register bit mask */
#define KR_KEY_Reload           ((uint16_t)0xAAAA)
#define KR_KEY_Enable           ((uint16_t)0xCCCC)

/**
  * @}
  */

/** @defgroup IWDG_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup IWDG_Private_Functions
  * @{
  */

/**
  * @brief  Enables or disables write access to IWDG_PR and IWDG_RLR registers.
  * @param  IWDG_WriteAccess: new state of write access to IWDG_PR and IWDG_RLR registers.
  *   This parameter can be one of the following values:
  *     @arg IWDG_KeyRegWrite_Enable: Enable write access to IWDG_PR and IWDG_RLR registers
  *     @arg IWDG_KeyRegWrite_Disable: Disable write access to IWDG_PR and IWDG_RLR registers
  * @retval None
  */
void IWDG_KeyRegWrite(uint16_t IWDG_WriteAccess)
{
  /* Check the parameters */
  assert_param(IS_IWDG_KEY_REG_WRITE(IWDG_WriteAccess));
  IWDG->KEY = IWDG_WriteAccess;
}

/**
  * @brief  Sets IWDG Prescaler value.
  * @param  IWDG_Prescaler: specifies the IWDG Prescaler value.
  *   This parameter can be one of the following values:
  *     @arg IWDG_Psc_4: IWDG prescaler set to 4
  *     @arg IWDG_Psc_8: IWDG prescaler set to 8
  *     @arg IWDG_Psc_16: IWDG prescaler set to 16
  *     @arg IWDG_Psc_32: IWDG prescaler set to 32
  *     @arg IWDG_Psc_64: IWDG prescaler set to 64
  *     @arg IWDG_Psc_128: IWDG prescaler set to 128
  *     @arg IWDG_Psc_256: IWDG prescaler set to 256
  * @retval None
  */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_IWDG_PSC(IWDG_Prescaler));
  IWDG->PSC = IWDG_Prescaler;
}

/**
  * @brief  Sets IWDG Reload value.
  * @param  Reload: specifies the IWDG Reload value.
  *   This parameter must be a number between 0 and 0x0FFF.
  * @retval None
  */
void IWDG_SetReload(uint16_t Reload)
{
  /* Check the parameters */
  assert_param(IS_IWDG_RLD(Reload));
  IWDG->RLD = Reload;
}

/**
  * @brief  Reloads IWDG counter with value defined in the reload register
  *   (write access to IWDG_PR and IWDG_RLR registers disabled).
  * @param  None
  * @retval None
  */
void IWDG_ReloadCounter(void)
{
  IWDG->KEY = KR_KEY_Reload;
}

/**
  * @brief  Enables IWDG (write access to IWDG_PR and IWDG_RLR registers disabled).
  * @param  None
  * @retval None
  */
void IWDG_Enable(void)
{
  IWDG->KEY = KR_KEY_Enable;
}

/**
  * @brief  Checks whether the specified IWDG flag is set or not.
  * @param  IWDG_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg IWDG_FLAG_PSCF: Prescaler Value Update on going
  *     @arg IWDG_FLAG_RLDF: Reload Value Update on going
  * @retval The new state of IWDG_FLAG (SET or RESET).
  */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_IWDG_FLAG(IWDG_FLAG));

  if ((IWDG->STS & IWDG_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  /* Return the flag status */
  return bitstatus;
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


