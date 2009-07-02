/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_gpio.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      GPIO firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_GPIO_H
#define __STM32F10x_GPIO_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
#define IS_GPIO_ALL_PERIPH(PERIPH) (((*(u32*)&(PERIPH)) == GPIOA_BASE) || \
                                    ((*(u32*)&(PERIPH)) == GPIOB_BASE) || \
                                    ((*(u32*)&(PERIPH)) == GPIOC_BASE) || \
                                    ((*(u32*)&(PERIPH)) == GPIOD_BASE) || \
                                    ((*(u32*)&(PERIPH)) == GPIOE_BASE) || \
                                    ((*(u32*)&(PERIPH)) == GPIOF_BASE) || \
                                    ((*(u32*)&(PERIPH)) == GPIOG_BASE))
                                     
/* Output Maximum frequency selection ----------------------------------------*/
typedef enum
{ 
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz, 
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;

#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_Speed_10MHz) || ((SPEED) == GPIO_Speed_2MHz) || \
                              ((SPEED) == GPIO_Speed_50MHz))
                                         
/* Configuration Mode enumeration --------------------------------------------*/
typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_AIN) || ((MODE) == GPIO_Mode_IN_FLOATING) || \
                            ((MODE) == GPIO_Mode_IPD) || ((MODE) == GPIO_Mode_IPU) || \
                            ((MODE) == GPIO_Mode_Out_OD) || ((MODE) == GPIO_Mode_Out_PP) || \
                            ((MODE) == GPIO_Mode_AF_OD) || ((MODE) == GPIO_Mode_AF_PP))
                              
/* GPIO Init structure definition */
typedef struct
{
  u16 GPIO_Pin;
  GPIOSpeed_TypeDef GPIO_Speed;
  GPIOMode_TypeDef GPIO_Mode;
}GPIO_InitTypeDef;

/* Bit_SET and Bit_RESET enumeration -----------------------------------------*/
typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;
#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))

/* Exported constants --------------------------------------------------------*/
/* GPIO pins define ----------------------------------------------------------*/
#define GPIO_Pin_0                 ((u16)0x0001)  /* Pin 0 selected */
#define GPIO_Pin_1                 ((u16)0x0002)  /* Pin 1 selected */
#define GPIO_Pin_2                 ((u16)0x0004)  /* Pin 2 selected */
#define GPIO_Pin_3                 ((u16)0x0008)  /* Pin 3 selected */
#define GPIO_Pin_4                 ((u16)0x0010)  /* Pin 4 selected */
#define GPIO_Pin_5                 ((u16)0x0020)  /* Pin 5 selected */
#define GPIO_Pin_6                 ((u16)0x0040)  /* Pin 6 selected */
#define GPIO_Pin_7                 ((u16)0x0080)  /* Pin 7 selected */
#define GPIO_Pin_8                 ((u16)0x0100)  /* Pin 8 selected */
#define GPIO_Pin_9                 ((u16)0x0200)  /* Pin 9 selected */
#define GPIO_Pin_10                ((u16)0x0400)  /* Pin 10 selected */
#define GPIO_Pin_11                ((u16)0x0800)  /* Pin 11 selected */
#define GPIO_Pin_12                ((u16)0x1000)  /* Pin 12 selected */
#define GPIO_Pin_13                ((u16)0x2000)  /* Pin 13 selected */
#define GPIO_Pin_14                ((u16)0x4000)  /* Pin 14 selected */
#define GPIO_Pin_15                ((u16)0x8000)  /* Pin 15 selected */
#define GPIO_Pin_All               ((u16)0xFFFF)  /* All pins selected */

#define IS_GPIO_PIN(PIN) ((((PIN) & (u16)0x00) == 0x00) && ((PIN) != (u16)0x00))

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_8) || \
                              ((PIN) == GPIO_Pin_9) || \
                              ((PIN) == GPIO_Pin_10) || \
                              ((PIN) == GPIO_Pin_11) || \
                              ((PIN) == GPIO_Pin_12) || \
                              ((PIN) == GPIO_Pin_13) || \
                              ((PIN) == GPIO_Pin_14) || \
                              ((PIN) == GPIO_Pin_15))
                            
/* GPIO Remap define ---------------------------------------------------------*/
#define GPIO_Remap_SPI1            ((u32)0x00000001)  /* SPI1 Alternate Function mapping */
#define GPIO_Remap_I2C1            ((u32)0x00000002)  /* I2C1 Alternate Function mapping */
#define GPIO_Remap_USART1          ((u32)0x00000004)  /* USART1 Alternate Function mapping */
#define GPIO_Remap_USART2          ((u32)0x00000008)  /* USART2 Alternate Function mapping */
#define GPIO_PartialRemap_USART3   ((u32)0x00140010)  /* USART3 Partial Alternate Function mapping */
#define GPIO_FullRemap_USART3      ((u32)0x00140030)  /* USART3 Full Alternate Function mapping */
#define GPIO_PartialRemap_TIM1     ((u32)0x00160040)  /* TIM1 Partial Alternate Function mapping */
#define GPIO_FullRemap_TIM1        ((u32)0x001600C0)  /* TIM1 Full Alternate Function mapping */
#define GPIO_PartialRemap1_TIM2    ((u32)0x00180100)  /* TIM2 Partial1 Alternate Function mapping */
#define GPIO_PartialRemap2_TIM2    ((u32)0x00180200)  /* TIM2 Partial2 Alternate Function mapping */
#define GPIO_FullRemap_TIM2        ((u32)0x00180300)  /* TIM2 Full Alternate Function mapping */
#define GPIO_PartialRemap_TIM3     ((u32)0x001A0800)  /* TIM3 Partial Alternate Function mapping */
#define GPIO_FullRemap_TIM3        ((u32)0x001A0C00)  /* TIM3 Full Alternate Function mapping */
#define GPIO_Remap_TIM4            ((u32)0x00001000)  /* TIM4 Alternate Function mapping */
#define GPIO_Remap1_CAN            ((u32)0x001D4000)  /* CAN Alternate Function mapping */
#define GPIO_Remap2_CAN            ((u32)0x001D6000)  /* CAN Alternate Function mapping */
#define GPIO_Remap_PD01            ((u32)0x00008000)  /* PD01 Alternate Function mapping */
#define GPIO_Remap_TIM5CH4_LSI     ((u32)0x00200001)  /* LSI connected to TIM5 Channel4 input capture for calibration */
#define GPIO_Remap_ADC1_ETRGINJ    ((u32)0x00200002)  /* ADC1 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC1_ETRGREG    ((u32)0x00200004)  /* ADC1 External Trigger Regular Conversion remapping */
#define GPIO_Remap_ADC2_ETRGINJ    ((u32)0x00200008)  /* ADC2 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC2_ETRGREG    ((u32)0x00200010)  /* ADC2 External Trigger Regular Conversion remapping */
#define GPIO_Remap_SWJ_NoJTRST     ((u32)0x00300100)  /* Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
#define GPIO_Remap_SWJ_JTAGDisable ((u32)0x00300200)  /* JTAG-DP Disabled and SW-DP Enabled */
#define GPIO_Remap_SWJ_Disable     ((u32)0x00300400)  /* Full SWJ Disabled (JTAG-DP + SW-DP) */


#define IS_GPIO_REMAP(REMAP) (((REMAP) == GPIO_Remap_SPI1) || ((REMAP) == GPIO_Remap_I2C1) || \
                              ((REMAP) == GPIO_Remap_USART1) || ((REMAP) == GPIO_Remap_USART2) || \
                              ((REMAP) == GPIO_PartialRemap_USART3) || ((REMAP) == GPIO_FullRemap_USART3) || \
                              ((REMAP) == GPIO_PartialRemap_TIM1) || ((REMAP) == GPIO_FullRemap_TIM1) || \
                              ((REMAP) == GPIO_PartialRemap1_TIM2) || ((REMAP) == GPIO_PartialRemap2_TIM2) || \
                              ((REMAP) == GPIO_FullRemap_TIM2) || ((REMAP) == GPIO_PartialRemap_TIM3) || \
                              ((REMAP) == GPIO_FullRemap_TIM3) || ((REMAP) == GPIO_Remap_TIM4) || \
                              ((REMAP) == GPIO_Remap1_CAN) || ((REMAP) == GPIO_Remap2_CAN) || \
                              ((REMAP) == GPIO_Remap_PD01) || ((REMAP) == GPIO_Remap_TIM5CH4_LSI) || \
                              ((REMAP) == GPIO_Remap_ADC1_ETRGINJ) ||((REMAP) == GPIO_Remap_ADC1_ETRGREG) || \
                              ((REMAP) == GPIO_Remap_ADC2_ETRGINJ) ||((REMAP) == GPIO_Remap_ADC2_ETRGREG) || \
                              ((REMAP) == GPIO_Remap_SWJ_NoJTRST) || ((REMAP) == GPIO_Remap_SWJ_JTAGDisable)|| \
                              ((REMAP) == GPIO_Remap_SWJ_Disable))
                              
/* GPIO Port Sources ---------------------------------------------------------*/
#define GPIO_PortSourceGPIOA       ((u8)0x00)
#define GPIO_PortSourceGPIOB       ((u8)0x01)
#define GPIO_PortSourceGPIOC       ((u8)0x02)
#define GPIO_PortSourceGPIOD       ((u8)0x03)
#define GPIO_PortSourceGPIOE       ((u8)0x04)
#define GPIO_PortSourceGPIOF       ((u8)0x05)
#define GPIO_PortSourceGPIOG       ((u8)0x06)

#define IS_GPIO_EVENTOUT_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == GPIO_PortSourceGPIOA) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOB) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOC) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOD) || \
                                                  ((PORTSOURCE) == GPIO_PortSourceGPIOE))
                                         
#define IS_GPIO_EXTI_PORT_SOURCE(PORTSOURCE) (((PORTSOURCE) == GPIO_PortSourceGPIOA) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOB) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOC) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOD) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOE) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOF) || \
                                              ((PORTSOURCE) == GPIO_PortSourceGPIOG))
                                       
/* GPIO Pin sources ----------------------------------------------------------*/
#define GPIO_PinSource0            ((u8)0x00)
#define GPIO_PinSource1            ((u8)0x01)
#define GPIO_PinSource2            ((u8)0x02)
#define GPIO_PinSource3            ((u8)0x03)
#define GPIO_PinSource4            ((u8)0x04)
#define GPIO_PinSource5            ((u8)0x05)
#define GPIO_PinSource6            ((u8)0x06)
#define GPIO_PinSource7            ((u8)0x07)
#define GPIO_PinSource8            ((u8)0x08)
#define GPIO_PinSource9            ((u8)0x09)
#define GPIO_PinSource10           ((u8)0x0A)
#define GPIO_PinSource11           ((u8)0x0B)
#define GPIO_PinSource12           ((u8)0x0C)
#define GPIO_PinSource13           ((u8)0x0D)
#define GPIO_PinSource14           ((u8)0x0E)
#define GPIO_PinSource15           ((u8)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE) (((PINSOURCE) == GPIO_PinSource0) || \
                                       ((PINSOURCE) == GPIO_PinSource1) || \
                                       ((PINSOURCE) == GPIO_PinSource2) || \
                                       ((PINSOURCE) == GPIO_PinSource3) || \
                                       ((PINSOURCE) == GPIO_PinSource4) || \
                                       ((PINSOURCE) == GPIO_PinSource5) || \
                                       ((PINSOURCE) == GPIO_PinSource6) || \
                                       ((PINSOURCE) == GPIO_PinSource7) || \
                                       ((PINSOURCE) == GPIO_PinSource8) || \
                                       ((PINSOURCE) == GPIO_PinSource9) || \
                                       ((PINSOURCE) == GPIO_PinSource10) || \
                                       ((PINSOURCE) == GPIO_PinSource11) || \
                                       ((PINSOURCE) == GPIO_PinSource12) || \
                                       ((PINSOURCE) == GPIO_PinSource13) || \
                                       ((PINSOURCE) == GPIO_PinSource14) || \
                                       ((PINSOURCE) == GPIO_PinSource15))
                          
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GPIO_DeInit(GPIO_TypeDef* GPIOx);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
u8 GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
u16 GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
u8 GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
u16 GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, u16 GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, u16 PortVal);
void GPIO_PinLockConfig(GPIO_TypeDef* GPIOx, u16 GPIO_Pin);
void GPIO_EventOutputConfig(u8 GPIO_PortSource, u8 GPIO_PinSource);
void GPIO_EventOutputCmd(FunctionalState NewState);
void GPIO_PinRemapConfig(u32 GPIO_Remap, FunctionalState NewState);
void GPIO_EXTILineConfig(u8 GPIO_PortSource, u8 GPIO_PinSource);

#endif /* __STM32F10x_GPIO_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
