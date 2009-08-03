/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_exti.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      EXTI firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_EXTI_H
#define __STM32F10x_EXTI_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* EXTI mode enumeration -----------------------------------------------------*/
typedef enum
{
  EXTI_Mode_Interrupt = 0x00,
  EXTI_Mode_Event = 0x04
}EXTIMode_TypeDef;

#define IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event))
                            
/* EXTI Trigger enumeration --------------------------------------------------*/
typedef enum
{
  EXTI_Trigger_Rising = 0x08,
  EXTI_Trigger_Falling = 0x0C,  
  EXTI_Trigger_Rising_Falling = 0x10
}EXTITrigger_TypeDef;

#define IS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || \
                                  ((TRIGGER) == EXTI_Trigger_Falling) || \
                                  ((TRIGGER) == EXTI_Trigger_Rising_Falling))

/* EXTI Init Structure definition --------------------------------------------*/
typedef struct
{
  u32 EXTI_Line;
  EXTIMode_TypeDef EXTI_Mode;
  EXTITrigger_TypeDef EXTI_Trigger;
  FunctionalState EXTI_LineCmd;
}EXTI_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
/* EXTI Lines ----------------------------------------------------------------*/
#define EXTI_Line0       ((u32)0x00001)  /* External interrupt line 0 */
#define EXTI_Line1       ((u32)0x00002)  /* External interrupt line 1 */
#define EXTI_Line2       ((u32)0x00004)  /* External interrupt line 2 */
#define EXTI_Line3       ((u32)0x00008)  /* External interrupt line 3 */
#define EXTI_Line4       ((u32)0x00010)  /* External interrupt line 4 */
#define EXTI_Line5       ((u32)0x00020)  /* External interrupt line 5 */
#define EXTI_Line6       ((u32)0x00040)  /* External interrupt line 6 */
#define EXTI_Line7       ((u32)0x00080)  /* External interrupt line 7 */
#define EXTI_Line8       ((u32)0x00100)  /* External interrupt line 8 */
#define EXTI_Line9       ((u32)0x00200)  /* External interrupt line 9 */
#define EXTI_Line10      ((u32)0x00400)  /* External interrupt line 10 */
#define EXTI_Line11      ((u32)0x00800)  /* External interrupt line 11 */
#define EXTI_Line12      ((u32)0x01000)  /* External interrupt line 12 */
#define EXTI_Line13      ((u32)0x02000)  /* External interrupt line 13 */
#define EXTI_Line14      ((u32)0x04000)  /* External interrupt line 14 */
#define EXTI_Line15      ((u32)0x08000)  /* External interrupt line 15 */
#define EXTI_Line16      ((u32)0x10000)  /* External interrupt line 16
                                            Connected to the PVD Output */
#define EXTI_Line17      ((u32)0x20000)  /* External interrupt line 17 
                                            Connected to the RTC Alarm event */
#define EXTI_Line18      ((u32)0x40000)  /* External interrupt line 18 
                                            Connected to the USB Wakeup from 
                                            suspend event */

#define IS_EXTI_LINE(LINE) ((((LINE) & (u32)0xFFF80000) == 0x00) && ((LINE) != (u16)0x00))

#define IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0) || ((LINE) == EXTI_Line1) || \
                            ((LINE) == EXTI_Line2) || ((LINE) == EXTI_Line3) || \
                            ((LINE) == EXTI_Line4) || ((LINE) == EXTI_Line5) || \
                            ((LINE) == EXTI_Line6) || ((LINE) == EXTI_Line7) || \
                            ((LINE) == EXTI_Line8) || ((LINE) == EXTI_Line9) || \
                            ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || \
                            ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || \
                            ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || \
                            ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || \
                            ((LINE) == EXTI_Line18))
                                 
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct);
void EXTI_GenerateSWInterrupt(u32 EXTI_Line);
FlagStatus EXTI_GetFlagStatus(u32 EXTI_Line);
void EXTI_ClearFlag(u32 EXTI_Line);
ITStatus EXTI_GetITStatus(u32 EXTI_Line);
void EXTI_ClearITPendingBit(u32 EXTI_Line);

#endif /* __STM32F10x_EXTI_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
