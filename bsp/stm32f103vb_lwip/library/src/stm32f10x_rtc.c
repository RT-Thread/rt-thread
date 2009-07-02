/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_rtc.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the RTC firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_rtc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define CRL_CNF_Set      ((u16)0x0010)      /* Configuration Flag Enable Mask */
#define CRL_CNF_Reset    ((u16)0xFFEF)      /* Configuration Flag Disable Mask */
#define RTC_LSB_Mask     ((u32)0x0000FFFF)  /* RTC LSB Mask */
#define PRLH_MSB_Mask    ((u32)0x000F0000)  /* RTC Prescaler MSB Mask */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : RTC_ITConfig
* Description    : Enables or disables the specified RTC interrupts.
* Input          : - RTC_IT: specifies the RTC interrupts sources to be enabled
*                    or disabled.
*                    This parameter can be any combination of the following values:
*                       - RTC_IT_OW: Overflow interrupt
*                       - RTC_IT_ALR: Alarm interrupt
*                       - RTC_IT_SEC: Second interrupt
*                  - NewState: new state of the specified RTC interrupts.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_ITConfig(u16 RTC_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RTC_IT(RTC_IT));  
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    RTC->CRH |= RTC_IT;
  }
  else
  {
    RTC->CRH &= (u16)~RTC_IT;
  }
}

/*******************************************************************************
* Function Name  : RTC_EnterConfigMode
* Description    : Enters the RTC configuration mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_EnterConfigMode(void)
{
  /* Set the CNF flag to enter in the Configuration Mode */
  RTC->CRL |= CRL_CNF_Set;
}

/*******************************************************************************
* Function Name  : RTC_ExitConfigMode
* Description    : Exits from the RTC configuration mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_ExitConfigMode(void)
{
  /* Reset the CNF flag to exit from the Configuration Mode */
  RTC->CRL &= CRL_CNF_Reset;
}

/*******************************************************************************
* Function Name  : RTC_GetCounter
* Description    : Gets the RTC counter value.
* Input          : None
* Output         : None
* Return         : RTC counter value.
*******************************************************************************/
u32 RTC_GetCounter(void)
{
  u16 tmp = 0;
  tmp = RTC->CNTL;

  return (((u32)RTC->CNTH << 16 ) | tmp) ;
}

/*******************************************************************************
* Function Name  : RTC_SetCounter
* Description    : Sets the RTC counter value.
* Input          : - CounterValue: RTC counter new value.
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_SetCounter(u32 CounterValue)
{ 
  RTC_EnterConfigMode();

  /* Set RTC COUNTER MSB word */
  RTC->CNTH = CounterValue >> 16;
  /* Set RTC COUNTER LSB word */
  RTC->CNTL = (CounterValue & RTC_LSB_Mask);

  RTC_ExitConfigMode();
}

/*******************************************************************************
* Function Name  : RTC_SetPrescaler
* Description    : Sets the RTC prescaler value.
* Input          : - PrescalerValue: RTC prescaler new value.
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_SetPrescaler(u32 PrescalerValue)
{
  /* Check the parameters */
  assert_param(IS_RTC_PRESCALER(PrescalerValue));
  
  RTC_EnterConfigMode();

  /* Set RTC PRESCALER MSB word */
  RTC->PRLH = (PrescalerValue & PRLH_MSB_Mask) >> 16;
  /* Set RTC PRESCALER LSB word */
  RTC->PRLL = (PrescalerValue & RTC_LSB_Mask);

  RTC_ExitConfigMode();
}

/*******************************************************************************
* Function Name  : RTC_SetAlarm
* Description    : Sets the RTC alarm value.
* Input          : - AlarmValue: RTC alarm new value.
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_SetAlarm(u32 AlarmValue)
{  
  RTC_EnterConfigMode();

  /* Set the ALARM MSB word */
  RTC->ALRH = AlarmValue >> 16;
  /* Set the ALARM LSB word */
  RTC->ALRL = (AlarmValue & RTC_LSB_Mask);

  RTC_ExitConfigMode();
}

/*******************************************************************************
* Function Name  : RTC_GetDivider
* Description    : Gets the RTC divider value.
* Input          : None
* Output         : None
* Return         : RTC Divider value.
*******************************************************************************/
u32 RTC_GetDivider(void)
{
  u32 tmp = 0x00;

  tmp = ((u32)RTC->DIVH & (u32)0x000F) << 16;
  tmp |= RTC->DIVL;

  return tmp;
}

/*******************************************************************************
* Function Name  : RTC_WaitForLastTask
* Description    : Waits until last write operation on RTC registers has finished.
*                  This function must be called before any write to RTC registers.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_WaitForLastTask(void)
{
  /* Loop until RTOFF flag is set */
  while ((RTC->CRL & RTC_FLAG_RTOFF) == (u16)RESET)
  {
  }
}

/*******************************************************************************
* Function Name  : RTC_WaitForSynchro
* Description    : Waits until the RTC registers (RTC_CNT, RTC_ALR and RTC_PRL)
*                  are synchronized with RTC APB clock.
*                  This function must be called before any read operation after
*                  an APB reset or an APB clock stop.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_WaitForSynchro(void)
{
  /* Clear RSF flag */
  RTC->CRL &= (u16)~RTC_FLAG_RSF;

  /* Loop until RSF flag is set */
  while ((RTC->CRL & RTC_FLAG_RSF) == (u16)RESET)
  {
  }
}

/*******************************************************************************
* Function Name  : RTC_GetFlagStatus
* Description    : Checks whether the specified RTC flag is set or not.
* Input          : - RTC_FLAG: specifies the flag to check.
*                    This parameter can be one the following values:
*                       - RTC_FLAG_RTOFF: RTC Operation OFF flag
*                       - RTC_FLAG_RSF: Registers Synchronized flag
*                       - RTC_FLAG_OW: Overflow flag
*                       - RTC_FLAG_ALR: Alarm flag
*                       - RTC_FLAG_SEC: Second flag
* Output         : None
* Return         : The new state of RTC_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus RTC_GetFlagStatus(u16 RTC_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  /* Check the parameters */
  assert_param(IS_RTC_GET_FLAG(RTC_FLAG)); 
  
  if ((RTC->CRL & RTC_FLAG) != (u16)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : RTC_ClearFlag
* Description    : Clears the RTC’s pending flags.
* Input          : - RTC_FLAG: specifies the flag to clear.
*                    This parameter can be any combination of the following values:
*                       - RTC_FLAG_RSF: Registers Synchronized flag. This flag
*                         is cleared only after an APB reset or an APB Clock stop.
*                       - RTC_FLAG_OW: Overflow flag
*                       - RTC_FLAG_ALR: Alarm flag
*                       - RTC_FLAG_SEC: Second flag
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_ClearFlag(u16 RTC_FLAG)
{
  /* Check the parameters */
  assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG)); 
    
  /* Clear the coressponding RTC flag */
  RTC->CRL &= (u16)~RTC_FLAG;
}

/*******************************************************************************
* Function Name  : RTC_GetITStatus
* Description    : Checks whether the specified RTC interrupt has occured or not.
* Input          : - RTC_IT: specifies the RTC interrupts sources to check.
*                    This parameter can be one of the following values:
*                       - RTC_IT_OW: Overflow interrupt
*                       - RTC_IT_ALR: Alarm interrupt
*                       - RTC_IT_SEC: Second interrupt
* Output         : None
* Return         : The new state of the RTC_IT (SET or RESET).
*******************************************************************************/
ITStatus RTC_GetITStatus(u16 RTC_IT)
{
  ITStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_RTC_GET_IT(RTC_IT)); 
  
  bitstatus = (ITStatus)(RTC->CRL & RTC_IT);

  if (((RTC->CRH & RTC_IT) != (u16)RESET) && (bitstatus != (u16)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : RTC_ClearITPendingBit
* Description    : Clears the RTC’s interrupt pending bits.
* Input          : - RTC_IT: specifies the interrupt pending bit to clear.
*                    This parameter can be any combination of the following values:
*                       - RTC_IT_OW: Overflow interrupt
*                       - RTC_IT_ALR: Alarm interrupt
*                       - RTC_IT_SEC: Second interrupt
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_ClearITPendingBit(u16 RTC_IT)
{
  /* Check the parameters */
  assert_param(IS_RTC_IT(RTC_IT));  
  
  /* Clear the coressponding RTC pending bit */
  RTC->CRL &= (u16)~RTC_IT;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
