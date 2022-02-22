/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */



#ifndef __AIR105_GPIO_H
#define __AIR105_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"


/**
  * @brief  Configuration Mode enumeration
  */
typedef enum
{
    GPIO_Mode_IN_FLOATING   = 0x01,
    GPIO_Mode_IPU           = 0x02,
    GPIO_Mode_Out_OD        = 0x03,
    GPIO_Mode_Out_OD_PU     = 0x04,
    GPIO_Mode_Out_PP        = 0x05
}GPIO_ModeTypeDef;
#define IS_GPIO_MODE(MODE)              (((MODE) == GPIO_Mode_IN_FLOATING) || \
                                        ((MODE) == GPIO_Mode_IPU) || \
                                        ((MODE) == GPIO_Mode_Out_OD) || \
                                        ((MODE) == GPIO_Mode_Out_PP) || \
                                        ((MODE) == GPIO_Mode_Out_OD_PU))

/**
  * @brief  GPIO Remap Type definition
  */
typedef enum
{
    GPIO_Remap_0 = 0x01,
    GPIO_Remap_1 = 0x02,
    GPIO_Remap_2 = 0x03,
    GPIO_Remap_3 = 0x04,
}GPIO_RemapTypeDef;
#define IS_GET_GPIO_REMAP(REMAP)       (((REMAP) == GPIO_Remap_0) || \
                                        ((REMAP) == GPIO_Remap_1) || \
                                        ((REMAP) == GPIO_Remap_2) || \
                                        ((REMAP) == GPIO_Remap_3) )

/**
  * @brief  GPIO Init structure definition
  */
typedef struct
{
    uint32_t GPIO_Pin;             /*!< Specifies the GPIO pins to be configured.
                                      This parameter can be any value of @ref GPIO_pins_define */
    GPIO_ModeTypeDef GPIO_Mode;

    GPIO_RemapTypeDef GPIO_Remap;
}GPIO_InitTypeDef;

/**
  * @brief  Bit_SET and Bit_RESET enumeration
  */
typedef enum
{
    Bit_RESET = 0,
    Bit_SET
}BitAction;

/**
  * @}
  */

/** @defgroup GPIO_Exported_Constants
  * @{
  */

/** @defgroup GPIO_pins_define
  * @{
  */
#define IS_GPIO_PERIPH(PERIPH) (((PERIPH) == GPIOA) || \
                                    ((PERIPH) == GPIOB) || \
                                    ((PERIPH) == GPIOC) || \
                                    ((PERIPH) == GPIOD) || \
                                    ((PERIPH) == GPIOE) || \
                                    ((PERIPH) == GPIOF))

#define GPIO_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected */
#define GPIO_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected */
#define GPIO_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected */
#define GPIO_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected */
#define GPIO_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected */
#define GPIO_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected */
#define GPIO_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected */
#define GPIO_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected */
#define GPIO_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected */
#define GPIO_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected */
#define GPIO_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10 selected */
#define GPIO_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11 selected */
#define GPIO_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12 selected */
#define GPIO_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected */
#define GPIO_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14 selected */
#define GPIO_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15 selected */
#define GPIO_Pin_All               ((uint16_t)0xffff)  /*!< Pin All selected */

#define IS_GPIO_PIN(PIN) (((((PIN) & ~(uint16_t)0xFFFF)) == 0x00) && ((PIN) != (uint16_t)0x00))

#define IS_GET_GPIO_PIN(PIN)            (((PIN) == GPIO_Pin_0) || \
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
/**
  * @}
  */

#define GPIO_PinSource0         0x00
#define GPIO_PinSource1         0x01
#define GPIO_PinSource2         0x02
#define GPIO_PinSource3         0x03
#define GPIO_PinSource4         0x04
#define GPIO_PinSource5         0x05
#define GPIO_PinSource6         0x06
#define GPIO_PinSource7         0x07
#define GPIO_PinSource8         0x08
#define GPIO_PinSource9         0x09
#define GPIO_PinSource10        0x0A
#define GPIO_PinSource11        0x0B
#define GPIO_PinSource12        0x0C
#define GPIO_PinSource13        0x0D
#define GPIO_PinSource14        0x0E
#define GPIO_PinSource15        0x0F

/** @defgroup GPIO_Port_Sources
  * @{
  */
#define GPIO_PortSourceGPIOA       ((uint32_t)0x00)
#define GPIO_PortSourceGPIOB       ((uint32_t)0x01)
#define GPIO_PortSourceGPIOC       ((uint32_t)0x02)
#define GPIO_PortSourceGPIOD       ((uint32_t)0x03)
#define GPIO_PortSourceGPIOE       ((uint32_t)0x04)
#define GPIO_PortSourceGPIOF       ((uint32_t)0x05)


#define IS_GPIO_PORT_SOURCE(PORTSOURCE)     (((PORTSOURCE) == GPIO_PortSourceGPIOA) || \
                                            ((PORTSOURCE) == GPIO_PortSourceGPIOB) || \
                                            ((PORTSOURCE) == GPIO_PortSourceGPIOC) || \
                                            ((PORTSOURCE) == GPIO_PortSourceGPIOD) || \
                                            ((PORTSOURCE) == GPIO_PortSourceGPIOE) || \
                                            ((PORTSOURCE) == GPIO_PortSourceGPIOF))

/**
  * @}
  */

/** @defgroup GPIO_WakeMode
  * @{
  */
typedef enum
{
    GPIO_WakeMode_Now               = (uint32_t)0x00,
    GPIO_WakeMode_AfterGlitch       = (uint32_t)0x01
}GPIO_WakeModeTypeDef;

#define IS_GPIO_WAKE_MODE(MODE)     (((MODE) == GPIO_WakeMode_Now) || \
                                    ((MODE) == GPIO_WakeMode_AfterGlitch))
/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions
  * @{
  */

void GPIO_DeInit(void);
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);

uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);

uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);

void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
void GPIO_PullUpCmd(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, FunctionalState NewState);

void GPIO_PinRemapConfig(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_RemapTypeDef GPIO_Remap);

void GPIO_WakeEvenDeInit(void);
void GPIO_WakeEvenConfig(uint32_t GPIO_PortSource, uint32_t GPIO_Pin, FunctionalState NewState);
void GPIO_WakeModeConfig(GPIO_WakeModeTypeDef GPIO_WakeMode);

#ifdef __cplusplus
}
#endif

#endif

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
