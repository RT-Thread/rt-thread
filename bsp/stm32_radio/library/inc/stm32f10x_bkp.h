/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_bkp.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      BKP firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_BKP_H
#define __STM32F10x_BKP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Tamper Pin active level */
#define BKP_TamperPinLevel_High           ((u16)0x0000)
#define BKP_TamperPinLevel_Low            ((u16)0x0001)

#define IS_BKP_TAMPER_PIN_LEVEL(LEVEL) (((LEVEL) == BKP_TamperPinLevel_High) || \
                                        ((LEVEL) == BKP_TamperPinLevel_Low))

/* RTC output source to output on the Tamper pin */
#define BKP_RTCOutputSource_None          ((u16)0x0000)
#define BKP_RTCOutputSource_CalibClock    ((u16)0x0080)
#define BKP_RTCOutputSource_Alarm         ((u16)0x0100)
#define BKP_RTCOutputSource_Second        ((u16)0x0300)

#define IS_BKP_RTC_OUTPUT_SOURCE(SOURCE) (((SOURCE) == BKP_RTCOutputSource_None) || \
                                          ((SOURCE) == BKP_RTCOutputSource_CalibClock) || \
                                          ((SOURCE) == BKP_RTCOutputSource_Alarm) || \
                                          ((SOURCE) == BKP_RTCOutputSource_Second))

/* Data Backup Register */
#define BKP_DR1                           ((u16)0x0004)
#define BKP_DR2                           ((u16)0x0008)
#define BKP_DR3                           ((u16)0x000C)
#define BKP_DR4                           ((u16)0x0010)
#define BKP_DR5                           ((u16)0x0014)
#define BKP_DR6                           ((u16)0x0018)
#define BKP_DR7                           ((u16)0x001C)
#define BKP_DR8                           ((u16)0x0020)
#define BKP_DR9                           ((u16)0x0024)
#define BKP_DR10                          ((u16)0x0028)
#define BKP_DR11                          ((u16)0x0040)
#define BKP_DR12                          ((u16)0x0044)
#define BKP_DR13                          ((u16)0x0048)
#define BKP_DR14                          ((u16)0x004C)
#define BKP_DR15                          ((u16)0x0050)
#define BKP_DR16                          ((u16)0x0054)
#define BKP_DR17                          ((u16)0x0058)
#define BKP_DR18                          ((u16)0x005C)
#define BKP_DR19                          ((u16)0x0060)
#define BKP_DR20                          ((u16)0x0064)
#define BKP_DR21                          ((u16)0x0068)
#define BKP_DR22                          ((u16)0x006C)
#define BKP_DR23                          ((u16)0x0070)
#define BKP_DR24                          ((u16)0x0074)
#define BKP_DR25                          ((u16)0x0078)
#define BKP_DR26                          ((u16)0x007C)
#define BKP_DR27                          ((u16)0x0080)
#define BKP_DR28                          ((u16)0x0084)
#define BKP_DR29                          ((u16)0x0088)
#define BKP_DR30                          ((u16)0x008C)
#define BKP_DR31                          ((u16)0x0090)
#define BKP_DR32                          ((u16)0x0094)
#define BKP_DR33                          ((u16)0x0098)
#define BKP_DR34                          ((u16)0x009C)
#define BKP_DR35                          ((u16)0x00A0)
#define BKP_DR36                          ((u16)0x00A4)
#define BKP_DR37                          ((u16)0x00A8)
#define BKP_DR38                          ((u16)0x00AC)
#define BKP_DR39                          ((u16)0x00B0)
#define BKP_DR40                          ((u16)0x00B4)
#define BKP_DR41                          ((u16)0x00B8)
#define BKP_DR42                          ((u16)0x00BC)

#define IS_BKP_DR(DR) (((DR) == BKP_DR1)  || ((DR) == BKP_DR2)  || ((DR) == BKP_DR3)  || \
                       ((DR) == BKP_DR4)  || ((DR) == BKP_DR5)  || ((DR) == BKP_DR6)  || \
                       ((DR) == BKP_DR7)  || ((DR) == BKP_DR8)  || ((DR) == BKP_DR9)  || \
                       ((DR) == BKP_DR10) || ((DR) == BKP_DR11) || ((DR) == BKP_DR12) || \
                       ((DR) == BKP_DR13) || ((DR) == BKP_DR14) || ((DR) == BKP_DR15) || \
                       ((DR) == BKP_DR16) || ((DR) == BKP_DR17) || ((DR) == BKP_DR18) || \
                       ((DR) == BKP_DR19) || ((DR) == BKP_DR20) || ((DR) == BKP_DR21) || \
                       ((DR) == BKP_DR22) || ((DR) == BKP_DR23) || ((DR) == BKP_DR24) || \
                       ((DR) == BKP_DR25) || ((DR) == BKP_DR26) || ((DR) == BKP_DR27) || \
                       ((DR) == BKP_DR28) || ((DR) == BKP_DR29) || ((DR) == BKP_DR30) || \
                       ((DR) == BKP_DR31) || ((DR) == BKP_DR32) || ((DR) == BKP_DR33) || \
                       ((DR) == BKP_DR34) || ((DR) == BKP_DR35) || ((DR) == BKP_DR36) || \
                       ((DR) == BKP_DR37) || ((DR) == BKP_DR38) || ((DR) == BKP_DR39) || \
                       ((DR) == BKP_DR40) || ((DR) == BKP_DR41) || ((DR) == BKP_DR42))

#define IS_BKP_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x7F)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void BKP_DeInit(void);
void BKP_TamperPinLevelConfig(u16 BKP_TamperPinLevel);
void BKP_TamperPinCmd(FunctionalState NewState);
void BKP_ITConfig(FunctionalState NewState);
void BKP_RTCOutputConfig(u16 BKP_RTCOutputSource);
void BKP_SetRTCCalibrationValue(u8 CalibrationValue);
void BKP_WriteBackupRegister(u16 BKP_DR, u16 Data);
u16 BKP_ReadBackupRegister(u16 BKP_DR);
FlagStatus BKP_GetFlagStatus(void);
void BKP_ClearFlag(void);
ITStatus BKP_GetITStatus(void);
void BKP_ClearITPendingBit(void);

#endif /* __STM32F10x_BKP_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
