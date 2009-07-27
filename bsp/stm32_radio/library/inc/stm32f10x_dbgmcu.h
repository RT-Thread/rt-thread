/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : stm32f10x_dbgmcu.h
* Author             : MCD Application Team
* Version            : V2.0.3Patch1
* Date               : 04/06/2009
* Description        : This file contains all the functions prototypes for the
*                      DBGMCU firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_DBGMCU_H
#define __STM32F10x_DBGMCU_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define DBGMCU_SLEEP                 ((u32)0x00000001)
#define DBGMCU_STOP                  ((u32)0x00000002)
#define DBGMCU_STANDBY               ((u32)0x00000004)
#define DBGMCU_IWDG_STOP             ((u32)0x00000100)
#define DBGMCU_WWDG_STOP             ((u32)0x00000200)
#define DBGMCU_TIM1_STOP             ((u32)0x00000400)
#define DBGMCU_TIM2_STOP             ((u32)0x00000800)
#define DBGMCU_TIM3_STOP             ((u32)0x00001000)
#define DBGMCU_TIM4_STOP             ((u32)0x00002000)
#define DBGMCU_CAN_STOP              ((u32)0x00004000)
#define DBGMCU_I2C1_SMBUS_TIMEOUT    ((u32)0x00008000)
#define DBGMCU_I2C2_SMBUS_TIMEOUT    ((u32)0x00010000)
#define DBGMCU_TIM8_STOP             ((u32)0x00020000)
#define DBGMCU_TIM5_STOP             ((u32)0x00040000)
#define DBGMCU_TIM6_STOP             ((u32)0x00080000)
#define DBGMCU_TIM7_STOP             ((u32)0x00100000)
                                           
#define IS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0xFFE000F8) == 0x00) && ((PERIPH) != 0x00))

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
u32 DBGMCU_GetREVID(void);
u32 DBGMCU_GetDEVID(void);
void DBGMCU_Config(u32 DBGMCU_Periph, FunctionalState NewState);

#endif /* __STM32F10x_DBGMCU_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/


