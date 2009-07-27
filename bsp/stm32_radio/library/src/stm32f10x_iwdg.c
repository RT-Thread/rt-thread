/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_iwdg.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the IWDG firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_iwdg.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------- IWDG registers bit mask ------------------------ */
/* KR register bit mask */
#define KR_KEY_Reload    ((u16)0xAAAA)
#define KR_KEY_Enable    ((u16)0xCCCC)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : IWDG_WriteAccessCmd
* Description    : Enables or disables write access to IWDG_PR and IWDG_RLR
*                  registers.
* Input          : - IWDG_WriteAccess: new state of write access to IWDG_PR and
*                    IWDG_RLR registers.
*                    This parameter can be one of the following values:
*                       - IWDG_WriteAccess_Enable: Enable write access to 
*                         IWDG_PR and IWDG_RLR registers
*                       - IWDG_WriteAccess_Disable: Disable write access to
*                         IWDG_PR and IWDG_RLR registers
* Output         : None
* Return         : None
*******************************************************************************/
void IWDG_WriteAccessCmd(u16 IWDG_WriteAccess)
{
  /* Check the parameters */
  assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));

  IWDG->KR = IWDG_WriteAccess;
}

/*******************************************************************************
* Function Name  : IWDG_SetPrescaler
* Description    : Sets IWDG Prescaler value.
* Input          : - IWDG_Prescaler: specifies the IWDG Prescaler value.
*                    This parameter can be one of the following values:
*                       - IWDG_Prescaler_4: IWDG prescaler set to 4
*                       - IWDG_Prescaler_8: IWDG prescaler set to 8
*                       - IWDG_Prescaler_16: IWDG prescaler set to 16
*                       - IWDG_Prescaler_32: IWDG prescaler set to 32
*                       - IWDG_Prescaler_64: IWDG prescaler set to 64
*                       - IWDG_Prescaler_128: IWDG prescaler set to 128
*                       - IWDG_Prescaler_256: IWDG prescaler set to 256
* Output         : None
* Return         : None
*******************************************************************************/
void IWDG_SetPrescaler(u8 IWDG_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_IWDG_PRESCALER(IWDG_Prescaler));

  IWDG->PR = IWDG_Prescaler;
}

/*******************************************************************************
* Function Name  : IWDG_SetReload
* Description    : Sets IWDG Reload value.
* Input          : - Reload: specifies the IWDG Reload value.
*                    This parameter must be a number between 0 and 0x0FFF.
* Output         : None
* Return         : None
*******************************************************************************/
void IWDG_SetReload(u16 Reload)
{
  /* Check the parameters */
  assert_param(IS_IWDG_RELOAD(Reload));

  IWDG->RLR = Reload;
}

/*******************************************************************************
* Function Name  : IWDG_ReloadCounter
* Description    : Reloads IWDG counter with value defined in the reload register
*                  (write access to IWDG_PR and IWDG_RLR registers disabled).
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IWDG_ReloadCounter(void)
{
  IWDG->KR = KR_KEY_Reload;
}

/*******************************************************************************
* Function Name  : IWDG_Enable
* Description    : Enables IWDG (write access to IWDG_PR and IWDG_RLR registers
*                  disabled).
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void IWDG_Enable(void)
{
  IWDG->KR = KR_KEY_Enable;
}

/*******************************************************************************
* Function Name  : IWDG_GetFlagStatus
* Description    : Checks whether the specified IWDG flag is set or not.
* Input          : - IWDG_FLAG: specifies the flag to check.
*                    This parameter can be one of the following values:
*                       - IWDG_FLAG_PVU: Prescaler Value Update on going
*                       - IWDG_FLAG_RVU: Reload Value Update on going
* Output         : None
* Return         : The new state of IWDG_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus IWDG_GetFlagStatus(u16 IWDG_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_IWDG_FLAG(IWDG_FLAG));

  if ((IWDG->SR & IWDG_FLAG) != (u32)RESET)
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

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
