/**
******************************************************************************
* @file  HAL_wwdg.c
* @author  IC Applications Department
* @version  V0.8
* @date  2019_08_02
* @brief  This file provides all the WWDG firmware functions.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT,HOLOCENE SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2016 HOLOCENE</center></h2>
*/

/* Includes ------------------------------------------------------------------*/
#include "HAL_wwdg.h"
#include "HAL_rcc.h"

//WWDG_BASE 未定义
#ifdef 0

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @defgroup WWDG
* @brief WWDG driver modules
* @{
*/

/** @defgroup WWDG_Private_TypesDefinitions
* @{
*/

/**
* @}
*/

/** @defgroup WWDG_Private_Defines
* @{
*/

/* ----------- WWDG registers bit address in the alias region ----------- */
#define WWDG_OFFSET       (WWDG_BASE - PERIPH_BASE)

/* Alias word address of EWI bit */
#define CFR_OFFSET        (WWDG_OFFSET + 0x04)
#define EWI_BitNumber     0x09
#define CFR_EWI_BB        (PERIPH_BB_BASE + (CFR_OFFSET * 32) + (EWI_BitNumber * 4))

/* --------------------- WWDG registers bit mask ------------------------ */

/* CR register bit mask */
#define CR_WDGA_Set       ((uint32_t)0x00000080)

/* CFR register bit mask */
#define CFR_WDGTB_Mask    ((uint32_t)0xFFFFFE7F)
#define CFR_W_Mask        ((uint32_t)0xFFFFFF80)
#define BIT_Mask          ((uint8_t)0x7F)

/**
* @}
*/

/** @defgroup WWDG_Private_Macros
* @{
*/

/**
* @}
*/

/** @defgroup WWDG_Private_Variables
* @{
*/

/**
* @}
*/

/** @defgroup WWDG_Private_FunctionPrototypes
* @{
*/

/**
* @}
*/

/** @defgroup WWDG_Private_Functions
* @{
*/

/**
* @brief  Deinitializes the WWDG  peripheral registers to their default
*   reset values.
* @param  None
* @retval : None
*/
void WWDG_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

/**
* @brief  Sets the WWDG Prescaler.
* @param WWDG_Prescaler: specifies the WWDG Prescaler.
*   This parameter can be one of the following values:
* @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
* @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
* @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
* @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
* @retval : None
*/
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
  /* Clear WDGTB[1:0] bits */
  tmpreg = WWDG->CFR & CFR_WDGTB_Mask;
  /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
  tmpreg |= WWDG_Prescaler;
  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/**
* @brief  Sets the WWDG window value.
* @param WindowValue: specifies the window value to be compared to
*   the downcounter.
*   This parameter value must be lower than 0x80.
* @retval : None
*/
void WWDG_SetWindowValue(uint8_t WindowValue)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
  /* Clear W[6:0] bits */
  tmpreg = WWDG->CFR & CFR_W_Mask;
  /* Set W[6:0] bits according to WindowValue value */
  tmpreg |= WindowValue & BIT_Mask;
  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/**
* @brief  Enables the WWDG Early Wakeup interrupt(EWI).
* @param  None
* @retval : None
*/
void WWDG_EnableIT(void)
{
  WWDG->CFR |= (uint32_t)0x200;
}

/**
* @brief  Sets the WWDG counter value.
* @param Counter: specifies the watchdog counter value.
*   This parameter must be a number between 0x40 and 0x7F.
* @retval : None
*/
void WWDG_SetCounter(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));
  /* Write to T[6:0] bits to configure the counter value, no need to do
  a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->CR = Counter & BIT_Mask;
}

/**
* @brief  Enables WWDG and load the counter value.
* @param Counter: specifies the watchdog counter value.
*   This parameter must be a number between 0x40 and 0x7F.
* @retval : None
*/
void WWDG_Enable(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));
  WWDG->CR = CR_WDGA_Set | Counter;
}

/**
* @brief  Checks whether the Early Wakeup interrupt flag is set or not.
* @param  None
* @retval : The new state of the Early Wakeup interrupt flag (SET or RESET)
*/
FlagStatus WWDG_GetFlagStatus(void)
{
  return (FlagStatus)(WWDG->SR);
}

/**
* @brief  Clears Early Wakeup interrupt flag.
* @param  None
* @retval : None
*/
void WWDG_ClearFlag(void)
{
  WWDG->SR = (uint32_t)RESET;
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
#endif // 0
/*-------------------------(C) COPYRIGHT 2016 HOLOCENE ----------------------*/
