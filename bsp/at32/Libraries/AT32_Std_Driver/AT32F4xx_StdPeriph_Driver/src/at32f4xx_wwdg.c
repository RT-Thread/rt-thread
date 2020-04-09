/**
 **************************************************************************
 * File Name    : at32f4xx_wwdg.c
 * Description  : at32f4xx WWDG source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_wwdg.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
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
#define WWDG_OFFSET         (WWDG_BASE - PERIPH_BASE)

/* Alias word address of EWI bit */
#define CFG_OFFSET          (WWDG_OFFSET + 0x04)
#define EWIEN_BitPos        0x09
#define CFG_EWIEN_BBMAP     (PERIPH_BB_BASE + (CFG_OFFSET * 32) + (EWIEN_BitPos * 4))

/* --------------------- WWDG registers bit mask ------------------------ */

/* CR register bit mask */
#define CTRL_EN_Set         ((uint32_t)0x00000080)

/* CFR register bit mask */
#define CFG_PSC_Mask        ((uint32_t)0xFFFFFE7F)
#define CFG_WCNTR_Mask      ((uint32_t)0xFFFFFF80)
#define BIT_Mask            ((uint8_t)0x7F)

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
  * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WWDG_Reset(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_WWDG, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_WWDG, DISABLE);
}

/**
  * @brief  Sets the WWDG Prescaler.
  * @param  WWDG_Prescaler: specifies the WWDG Prescaler.
  *   This parameter can be one of the following values:
  *     @arg WWDG_Psc_1: WWDG counter clock = (PCLK1/4096)/1
  *     @arg WWDG_Psc_2: WWDG counter clock = (PCLK1/4096)/2
  *     @arg WWDG_Psc_4: WWDG counter clock = (PCLK1/4096)/4
  *     @arg WWDG_Psc_8: WWDG counter clock = (PCLK1/4096)/8
  * @retval None
  */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
  uint32_t tmpreg = 0;
  /* Check the parameters */
  assert_param(IS_WWDG_PSC(WWDG_Prescaler));
  /* Clear WDGTB[1:0] bits */
  tmpreg = WWDG->CFG & CFG_PSC_Mask;
  /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
  tmpreg |= WWDG_Prescaler;
  /* Store the new value */
  WWDG->CFG = tmpreg;
}

/**
  * @brief  Sets the WWDG window value.
  * @param  WindowValue: specifies the window value to be compared to the downcounter.
  *   This parameter value must be lower than 0x80.
  * @retval None
  */
void WWDG_SetWindowCounter(uint8_t WindowValue)
{
  __IO uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_WWDG_WCNTR(WindowValue));
  /* Clear W[6:0] bits */

  tmpreg = WWDG->CFG & CFG_WCNTR_Mask;

  /* Set W[6:0] bits according to WindowValue value */
  tmpreg |= WindowValue & (uint32_t) BIT_Mask;

  /* Store the new value */
  WWDG->CFG = tmpreg;
}

/**
  * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
  * @param  None
  * @retval None
  */
void WWDG_EnableINT(void)
{
  *(__IO uint32_t *) CFG_EWIEN_BBMAP = (uint32_t)ENABLE;
}

/**
  * @brief  Sets the WWDG counter value.
  * @param  Counter: specifies the watchdog counter value.
  *   This parameter must be a number between 0x40 and 0x7F.
  * @retval None
  */
void WWDG_SetCounter(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_CNTR(Counter));
  /* Write to T[6:0] bits to configure the counter value, no need to do
     a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->CTRL = Counter & BIT_Mask;
}

/**
  * @brief  Enables WWDG and load the counter value.
  * @param  Counter: specifies the watchdog counter value.
  *   This parameter must be a number between 0x40 and 0x7F.
  * @retval None
  */
void WWDG_Enable(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_CNTR(Counter));
  WWDG->CTRL = CTRL_EN_Set | Counter;
}

/**
  * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
  * @param  None
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET)
  */
FlagStatus WWDG_GetFlagStatus(void)
{
  return (FlagStatus)(WWDG->STS);
}

/**
  * @brief  Clears Early Wakeup interrupt flag.
  * @param  None
  * @retval None
  */
void WWDG_ClearFlag(void)
{
  WWDG->STS = (uint32_t)RESET;
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


