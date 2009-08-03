/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_dbgmcu.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the DBGMCU firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_dbgmcu.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IDCODE_DEVID_Mask    ((u32)0x00000FFF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : DBGMCU_GetREVID
* Description    : Returns the device revision identifier.
* Input          : None
* Output         : None
* Return         : Device revision identifier
*******************************************************************************/
u32 DBGMCU_GetREVID(void)
{
   return(DBGMCU->IDCODE >> 16);
}

/*******************************************************************************
* Function Name  : DBGMCU_GetDEVID
* Description    : Returns the device identifier.
* Input          : None
* Output         : None
* Return         : Device identifier
*******************************************************************************/
u32 DBGMCU_GetDEVID(void)
{
   return(DBGMCU->IDCODE & IDCODE_DEVID_Mask);
}

/*******************************************************************************
* Function Name  : DBGMCU_Config
* Description    : Configures the specified peripheral and low power mode behavior
*                  when the MCU under Debug mode.
* Input          : - DBGMCU_Periph: specifies the peripheral and low power mode.
*                    This parameter can be any combination of the following values:
*                       - DBGMCU_SLEEP: Keep debugger connection during SLEEP mode              
*                       - DBGMCU_STOP: Keep debugger connection during STOP mode               
*                       - DBGMCU_STANDBY: Keep debugger connection during STANDBY mode            
*                       - DBGMCU_IWDG_STOP: Debug IWDG stopped when Core is halted          
*                       - DBGMCU_WWDG_STOP: Debug WWDG stopped when Core is halted          
*                       - DBGMCU_TIM1_STOP: TIM1 counter stopped when Core is halted          
*                       - DBGMCU_TIM2_STOP: TIM2 counter stopped when Core is halted          
*                       - DBGMCU_TIM3_STOP: TIM3 counter stopped when Core is halted          
*                       - DBGMCU_TIM4_STOP: TIM4 counter stopped when Core is halted          
*                       - DBGMCU_CAN_STOP: Debug CAN stopped when Core is halted           
*                       - DBGMCU_I2C1_SMBUS_TIMEOUT: I2C1 SMBUS timeout mode stopped
*                                                    when Core is halted
*                       - DBGMCU_I2C2_SMBUS_TIMEOUT: I2C2 SMBUS timeout mode stopped
*                                                    when Core is halted
*                       - DBGMCU_TIM5_STOP: TIM5 counter stopped when Core is halted          
*                       - DBGMCU_TIM6_STOP: TIM6 counter stopped when Core is halted          
*                       - DBGMCU_TIM7_STOP: TIM7 counter stopped when Core is halted          
*                       - DBGMCU_TIM8_STOP: TIM8 counter stopped when Core is halted          
*                  - NewState: new state of the specified peripheral in Debug mode.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void DBGMCU_Config(u32 DBGMCU_Periph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_DBGMCU_PERIPH(DBGMCU_Periph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    DBGMCU->CR |= DBGMCU_Periph;
  }
  else
  {
    DBGMCU->CR &= ~DBGMCU_Periph;
  }
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
