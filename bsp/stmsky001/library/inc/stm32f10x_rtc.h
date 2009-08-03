/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_rtc.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      RTC firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_RTC_H
#define __STM32F10x_RTC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* RTC interrupts define -----------------------------------------------------*/
#define RTC_IT_OW            ((u16)0x0004)  /* Overflow interrupt */
#define RTC_IT_ALR           ((u16)0x0002)  /* Alarm interrupt */
#define RTC_IT_SEC           ((u16)0x0001)  /* Second interrupt */

#define IS_RTC_IT(IT) ((((IT) & (u16)0xFFF8) == 0x00) && ((IT) != 0x00))

#define IS_RTC_GET_IT(IT) (((IT) == RTC_IT_OW) || ((IT) == RTC_IT_ALR) || \
                           ((IT) == RTC_IT_SEC))
                                                                     
/* RTC interrupts flags ------------------------------------------------------*/
#define RTC_FLAG_RTOFF       ((u16)0x0020)  /* RTC Operation OFF flag */
#define RTC_FLAG_RSF         ((u16)0x0008)  /* Registers Synchronized flag */
#define RTC_FLAG_OW          ((u16)0x0004)  /* Overflow flag */
#define RTC_FLAG_ALR         ((u16)0x0002)  /* Alarm flag */
#define RTC_FLAG_SEC         ((u16)0x0001)  /* Second flag */

#define IS_RTC_CLEAR_FLAG(FLAG) ((((FLAG) & (u16)0xFFF0) == 0x00) && ((FLAG) != 0x00))

#define IS_RTC_GET_FLAG(FLAG) (((FLAG) == RTC_FLAG_RTOFF) || ((FLAG) == RTC_FLAG_RSF) || \
                               ((FLAG) == RTC_FLAG_OW) || ((FLAG) == RTC_FLAG_ALR) || \
                               ((FLAG) == RTC_FLAG_SEC))

#define IS_RTC_PRESCALER(PRESCALER) ((PRESCALER) <= 0xFFFFF)
                           
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RTC_ITConfig(u16 RTC_IT, FunctionalState NewState);
void RTC_EnterConfigMode(void);
void RTC_ExitConfigMode(void);
u32  RTC_GetCounter(void);
void RTC_SetCounter(u32 CounterValue);
void RTC_SetPrescaler(u32 PrescalerValue);
void RTC_SetAlarm(u32 AlarmValue);
u32  RTC_GetDivider(void);
void RTC_WaitForLastTask(void);
void RTC_WaitForSynchro(void);
FlagStatus RTC_GetFlagStatus(u16 RTC_FLAG);
void RTC_ClearFlag(u16 RTC_FLAG);
ITStatus RTC_GetITStatus(u16 RTC_IT);
void RTC_ClearITPendingBit(u16 RTC_IT);

#endif /* __STM32F10x_RTC_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
