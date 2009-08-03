/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_wwdg.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the WWDG firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_wwdg.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ----------- WWDG registers bit address in the alias region ----------- */
#define WWDG_OFFSET       (WWDG_BASE - PERIPH_BASE)

/* Alias word address of EWI bit */
#define CFR_OFFSET        (WWDG_OFFSET + 0x04)
#define EWI_BitNumber     0x09
#define CFR_EWI_BB        (PERIPH_BB_BASE + (CFR_OFFSET * 32) + (EWI_BitNumber * 4))

/* --------------------- WWDG registers bit mask ------------------------ */
/* CR register bit mask */
#define CR_WDGA_Set       ((u32)0x00000080)

/* CFR register bit mask */
#define CFR_WDGTB_Mask    ((u32)0xFFFFFE7F)
#define CFR_W_Mask        ((u32)0xFFFFFF80)

#define BIT_Mask          ((u8)0x7F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : WWDG_DeInit
* Description    : Deinitializes the WWDG  peripheral registers to their default
*                  reset values.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_DeInit(void)
{
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

/*******************************************************************************
* Function Name  : WWDG_SetPrescaler
* Description    : Sets the WWDG Prescaler.
* Input          : - WWDG_Prescaler: specifies the WWDG Prescaler.
*                    This parameter can be one of the following values:
*                       - WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
*                       - WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
*                       - WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
*                       - WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_SetPrescaler(u32 WWDG_Prescaler)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));

  /* Clear WDGTB[1:0] bits */
  tmpreg = WWDG->CFR & CFR_WDGTB_Mask;

  /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
  tmpreg |= WWDG_Prescaler;

  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/*******************************************************************************
* Function Name  : WWDG_SetWindowValue
* Description    : Sets the WWDG window value.
* Input          : - WindowValue: specifies the window value to be compared to
*                    the downcounter.
*                    This parameter value must be lower than 0x80.
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_SetWindowValue(u8 WindowValue)
{
  u32 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));

  /* Clear W[6:0] bits */
  tmpreg = WWDG->CFR & CFR_W_Mask;

  /* Set W[6:0] bits according to WindowValue value */
  tmpreg |= WindowValue & BIT_Mask;

  /* Store the new value */
  WWDG->CFR = tmpreg;
}

/*******************************************************************************
* Function Name  : WWDG_EnableIT
* Description    : Enables the WWDG Early Wakeup interrupt(EWI).
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_EnableIT(void)
{
  *(vu32 *) CFR_EWI_BB = (u32)ENABLE;
}

/*******************************************************************************
* Function Name  : WWDG_SetCounter
* Description    : Sets the WWDG counter value.
* Input          : - Counter: specifies the watchdog counter value.
*                    This parameter must be a number between 0x40 and 0x7F.
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_SetCounter(u8 Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));

  /* Write to T[6:0] bits to configure the counter value, no need to do
     a read-modify-write; writing a 0 to WDGA bit does nothing */
  WWDG->CR = Counter & BIT_Mask;
}

/*******************************************************************************
* Function Name  : WWDG_Enable
* Description    : Enables WWDG and load the counter value.
*                  - Counter: specifies the watchdog counter value.
*                    This parameter must be a number between 0x40 and 0x7F.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_Enable(u8 Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));

  WWDG->CR = CR_WDGA_Set | Counter;
}

/*******************************************************************************
* Function Name  : WWDG_GetFlagStatus
* Description    : Checks whether the Early Wakeup interrupt flag is set or not.
* Input          : None
* Output         : None
* Return         : The new state of the Early Wakeup interrupt flag (SET or RESET)
*******************************************************************************/
FlagStatus WWDG_GetFlagStatus(void)
{
  return (FlagStatus)(WWDG->SR);
}

/*******************************************************************************
* Function Name  : WWDG_ClearFlag
* Description    : Clears Early Wakeup interrupt flag.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_ClearFlag(void)
{
  WWDG->SR = (u32)RESET;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
