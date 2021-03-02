/**
  ******************************************************************************
  * @file    stm32l0xx_hal_gpio_ex.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL Extension module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L0xx_HAL_GPIO_EX_H
#define __STM32L0xx_HAL_GPIO_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup GPIOEx GPIOEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/** @defgroup GPIOEx_Exported_Constants GPIOEx Exported Constants
  * @{
  */


/*----------------------------------------------------------------------------*/
/*------------------------- STM32L083xx/STM32L073xx---------------------------*/
/*----------------------------------------------------------------------------*/

#if defined (STM32L083xx) || defined (STM32L073xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */

/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |TSC     |USART2  |TIM2_TR |USART4  |COMP1   |
 * PA1 |EVENTOUT|LCD     |TIM2_C2 |TSC     |USART2  |TIM21_TR|USART4  |        |
 * PA2 |TIM21_C1|LCD     |TIM2_C3 |TSC     |USART2  |        |LPUART1 |COMP2   |
 * PA3 |TIM21_C2|LCD     |TIM2_C4 |TSC     |USART2  |        |LPUART1 |        |
 * PA4 |SPI1    |        |        |TSC     |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |TSC     |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |LCD     |TIM3_C1 |TSC     |LPUART1 |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |LCD     |TIM3_C2 |TSC     |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |LCD     |USB     |EVENTOUT|USART1  |        |        |I2C3    |
 * PA9 |MCO     |LCD     |        |TSC     |USART1  |        |I2C1    |I2C3    |
 * PA10|        |LCD     |        |TSC     |USART1  |        |I2C1    |        |
 * PA11|SPI1    |        |EVENTOUT|TSC     |USART1  |        |I2C2    |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|TSC     |USART1  |        |I2C2    |COMP2   |
 * PA13|SWDIO   |        |USB     |        |        |        |LPUART1 |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |LPUART1 |        |
 * PA15|SPI1    |LCD     |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |USART4  |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|LCD     |TIM3_C3 |TSC     |        |        |        |        |
 * PB1 |        |LCD     |TIM3_C4 |TSC     |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|TSC     |        |        |        |I2C3    |
 * PB3 |SPI1    |LCD     |TIM2_C2 |TSC     |EVENTOUT|USART1  |USART5  |        |
 * PB4 |SPI1    |LCD     |TIM3_C1 |TSC     |TIM22_C1|USART1  |USART5  |I2C3    |
 * PB5 |SPI1    |LCD     |LPTIM1_I|I2C1    |TIM3_C2 |USART1  |USART5  |        |
 *     |        |        |        |        |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|TSC     |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|TSC     |        |        |USART4  |        |
 * PB8 |        |LCD     |        |TSC     |I2C1    |        |        |        |
 * PB9 |        |LCD     |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |LCD     |TIM2_C3 |TSC     |LPUART1 |SPI2    |I2C2    |LPUART1 |
 * PB11|EVENTOUT|LCD     |TIM2_C4 |TSC     |LPUART1 |        |I2C2    |LPUART1 |
 * PB12|SPI2    |LCD     |LPUART1 |TSC     |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |LCD     |MCO     |TSC     |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |LCD     |RTC     |TSC     |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |LCD     |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|LCD     |EVENTOUT|TSC     |        |        |LPUART1 |I2C3    |
 * PC1 |LPTIM1_O|LCD     |EVENTOUT|TSC     |        |        |LPUART1 |I2C3    |
 * PC2 |LPTIM1_I|LCD     |SPI2    |TSC     |        |        |        |        |
 * PC3 |LPTIM1_T|LCD     |SPI2    |TSC     |        |        |        |        |
 * PC4 |EVENTOUT|LCD     |LPUART1 |        |        |        |        |        |
 * PC5 |        |LCD     |LPUART1 |TSC     |        |        |        |        |
 * PC6 |TIM22_C1|LCD     |TIM3_C1 |TSC     |        |        |        |        |
 * PC7 |TIM22_C2|LCD     |TIM3_C2 |TSC     |        |        |        |        |
 * PC8 |TIM22_TR|LCD     |TIM3_C3 |TSC     |        |        |        |        |
 * PC9 |TIM21_TR|LCD     |USB     |TSC     |        |        |        |I2C3    |
 *     |        |        |TIM3_C4 |        |        |        |        |        |
 * PC10|LPUART1 |LCD     |        |        |        |        |USART4  |        |
 * PC11|LPUART1 |LCD     |        |        |        |        |USART4  |        |
 * PC12|        |LCD     |USART5  |        |        |        |USART4  |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD0 |TIM21_C1|SPI2    |        |        |        |        |        |        |
 * PD1 |        |SPI2    |        |        |        |        |        |        |
 * PD2 |LPUART1 |LCD     |TIM3_TR |        |        |        |USART5  |        |
 * PD3 |USART2  |LCD     |SPI2    |        |        |        |        |        |
 * PD4 |USART2  |SPI2    |        |        |        |        |        |        |
 * PD5 |USART2  |        |        |        |        |        |        |        |
 * PD6 |USART2  |        |        |        |        |        |        |        |
 * PD7 |USART2  |TIM21_C2|        |        |        |        |        |        |
 * PD8 |LPUART1 |LCD     |        |        |        |        |        |        |
 * PD9 |LPUART1 |LCD     |        |        |        |        |        |        |
 * PD10|        |LCD     |        |        |        |        |        |        |
 * PD11|LPUART1 |LCD     |        |        |        |        |        |        |
 * PD12|LPUART1 |LCD     |        |        |        |        |        |        |
 * PD13|        |LCD     |        |        |        |        |        |        |
 * PD14|        |LCD     |        |        |        |        |        |        |
 * PD15|USB     |LCD     |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PE0 |        |LCD     |EVENTOUT|        |        |        |        |        |
 * PE1 |        |LCD     |EVENTOUT|        |        |        |        |        |
 * PE2 |        |LCD     |TIM3_TR |        |        |        |        |        |
 * PE3 |TIM22_C1|LCD     |TIM3_C1 |        |        |        |        |        |
 * PE4 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PE5 |TIM21_C1|        |TIM3_C3 |        |        |        |        |        |
 * PE6 |TIM21_C2|        |TIM3_C4 |        |        |        |        |        |
 * PE7 |        |LCD     |        |        |        |        |USART5  |        |
 * PE8 |        |LCD     |        |        |        |        |USART4  |        |
 * PE9 |TIM2_C1 |LCD     |TIM2_TR |        |        |        |USART4  |        |
 * PE10|TIM2_C2 |LCD     |        |        |        |        |USART5  |        |
 * PE11|TIM2_C3 |        |        |        |        |        |USART5  |        |
 * PE12|TIM2_C4 |        |SPI1    |        |        |        |        |        |
 * PE13|        |LCD     |SPI1    |        |        |        |        |        |
 * PE14|        |LCD     |SPI1    |        |        |        |        |        |
 * PE15|        |LCD     |SPI1    |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |USB     |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 * PH9 |        |        |        |        |        |        |        |        |
 * PH10|        |        |        |        |        |        |        |        |
 *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_USART1        ((uint8_t)0x00U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_SPI2          ((uint8_t)0x00U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TIM22         ((uint8_t)0x00U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_TIM2          ((uint8_t)0x00U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_USB           ((uint8_t)0x00U)  /* USB Alternate Function mapping      */
/**
 *
 */

/*
 * Alternate function AF1
 */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF1_SPI2          ((uint8_t)0x01U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF1_TIM21         ((uint8_t)0x01U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF1_LCD           ((uint8_t)0x01U)  /* LCD Alternate Function mapping      */
/**
 *
 */

/*
 * Alternate function AF2
 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF2_TIM3          ((uint8_t)0x02U)  /* TIM3 Alternate Function mapping     */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF2_MCO           ((uint8_t)0x02U)  /* MCO Alternate Function mapping      */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping      */
#define GPIO_AF2_SPI2          ((uint8_t)0x02U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF2_USART5        ((uint8_t)0x02U)  /* USART5 Alternate Function mapping   */
#define GPIO_AF2_SPI1          ((uint8_t)0x02U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF2_USB           ((uint8_t)0x00U)  /* USB Alternate Function mapping      */
/**
 *
 */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_TSC           ((uint8_t)0x03U)  /* TSC  Alternate Function mapping     */
/**
 *
 */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_USART2          ((uint8_t)0x04U)  /* USART2 Alternate Function mapping  */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping */
#define GPIO_AF4_USART1          ((uint8_t)0x04U)  /* USART1 Alternate Function mapping  */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping*/
#define GPIO_AF4_TIM22           ((uint8_t)0x04U)  /* TIM22 Alternate Function mapping   */
#define GPIO_AF4_TIM3            ((uint8_t)0x04U)  /* TIM3 Alternate Function mapping    */
#define GPIO_AF4_I2C1            ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping    */
/**
 *
 */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF5_USART1        ((uint8_t)0x05U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF5_SPI2          ((uint8_t)0x05U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_I2C2          ((uint8_t)0x05U)  /* I2C2 Alternate Function mapping     */
/**
 *
 */

/*
 * Alternate function AF6
 */

#define GPIO_AF6_USART4        ((uint8_t)0x06U)  /* USART4 Alternate Function mapping   */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF6_I2C1          ((uint8_t)0x06U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF6_I2C2          ((uint8_t)0x06U)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF6_USART5        ((uint8_t)0x06U)  /* USART5 Alternate Function mapping   */
#define GPIO_AF6_TIM21         ((uint8_t)0x06U)  /* TIM21 Alternate Function mapping    */
/**
 *
 */

/*
 * Alternate function AF7
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07U)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07U)  /* COMP2 Alternate Function mapping     */
#define GPIO_AF7_I2C3         ((uint8_t)0x07U)  /* I2C3 Alternate Function mapping      */
#define GPIO_AF7_LPUART1      ((uint8_t)0x07U)  /* LPUART1 Alternate Function mapping   */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */
/**
 *  IS_GPIO_AF macro definition
 */
#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

 /**
  * @}
  */
#endif /* (STM32L083xx) || (STM32L073xx) */

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L082xx and STM32L072xx-----------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L082xx) || defined (STM32L072xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 */


/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |TSC     |USART2  |TIM2_TR |USART4  |COMP1   |
 * PA1 |EVENTOUT|        |TIM2_C2 |TSC     |USART2  |TIM21_TR|USART4  |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |TSC     |USART2  |        |LPUART1 |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |TSC     |USART2  |        |LPUART1 |        |
 * PA4 |SPI1    |        |        |TSC     |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |TSC     |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |        |TIM3_C1 |TSC     |LPUART1 |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |        |TIM3_C2 |TSC     |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |USB     |EVENTOUT|USART1  |        |        |I2C3    |
 * PA9 |MCO     |        |        |TSC     |USART1  |        |I2C1    |I2C3    |
 * PA10|        |        |        |TSC     |USART1  |        |I2C1    |        |
 * PA11|SPI1    |        |EVENTOUT|TSC     |USART1  |        |I2C2    |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|TSC     |USART1  |        |I2C2    |COMP2   |
 * PA13|SWDIO   |        |USB     |        |        |        |LPUART1 |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |LPUART1 |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |USART4  |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|        |TIM3_C3 |TSC     |        |        |        |        |
 * PB1 |        |        |TIM3_C4 |TSC     |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|TSC     |        |        |        |I2C3    |
 * PB3 |SPI1    |        |TIM2_C2 |TSC     |EVENTOUT|USART1  |USART5  |        |
 * PB4 |SPI1    |        |TIM3_C1 |TSC     |TIM22_C1|USART1  |USART5  |I2C3    |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM3_C2 |USART1  |USART5  |        |
 *     |        |        |        |        |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|TSC     |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|TSC     |        |        |USART4  |        |
 * PB8 |        |        |        |TSC     |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |        |TIM2_C3 |TSC     |LPUART1 |SPI2    |I2C2    |LPUART1 |
 * PB11|EVENTOUT|        |TIM2_C4 |TSC     |LPUART1 |        |I2C2    |LPUART1 |
 * PB12|SPI2    |        |LPUART1 |TSC     |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |        |MCO     |TSC     |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |        |RTC     |TSC     |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|        |EVENTOUT|TSC     |        |        |LPUART1 |I2C3    |
 * PC1 |LPTIM1_O|        |EVENTOUT|TSC     |        |        |LPUART1 |I2C3    |
 * PC2 |LPTIM1_I|        |SPI2    |TSC     |        |        |        |        |
 * PC3 |LPTIM1_T|        |SPI2    |TSC     |        |        |        |        |
 * PC4 |EVENTOUT|        |LPUART1 |        |        |        |        |        |
 * PC5 |        |        |LPUART1 |TSC     |        |        |        |        |
 * PC6 |TIM22_C1|        |TIM3_C1 |TSC     |        |        |        |        |
 * PC7 |TIM22_C2|        |TIM3_C2 |TSC     |        |        |        |        |
 * PC8 |TIM22_TR|        |TIM3_C3 |TSC     |        |        |        |        |
 * PC9 |TIM21_TR|        |USB     |TSC     |        |        |        |I2C3    |
 *     |        |        |TIM3_C4 |        |        |        |        |        |
 * PC10|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC11|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC12|        |        |USART5  |        |        |        |USART4  |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD0 |TIM21_C1|SPI2    |        |        |        |        |        |        |
 * PD1 |        |SPI2    |        |        |        |        |        |        |
 * PD2 |LPUART1 |        |TIM3_TR |        |        |        |USART5  |        |
 * PD3 |USART2  |        |SPI2    |        |        |        |        |        |
 * PD4 |USART2  |SPI2    |        |        |        |        |        |        |
 * PD5 |USART2  |        |        |        |        |        |        |        |
 * PD6 |USART2  |        |        |        |        |        |        |        |
 * PD7 |USART2  |TIM21_C2|        |        |        |        |        |        |
 * PD8 |LPUART1 |        |        |        |        |        |        |        |
 * PD9 |LPUART1 |        |        |        |        |        |        |        |
 * PD10|        |        |        |        |        |        |        |        |
 * PD11|LPUART1 |        |        |        |        |        |        |        |
 * PD12|LPUART1 |        |        |        |        |        |        |        |
 * PD13|        |        |        |        |        |        |        |        |
 * PD14|        |        |        |        |        |        |        |        |
 * PD15|USB     |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PE0 |        |        |EVENTOUT|        |        |        |        |        |
 * PE1 |        |        |EVENTOUT|        |        |        |        |        |
 * PE2 |        |        |TIM3_TR |        |        |        |        |        |
 * PE3 |TIM22_C1|        |TIM3_C1 |        |        |        |        |        |
 * PE4 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PE5 |TIM21_C1|        |TIM3_C3 |        |        |        |        |        |
 * PE6 |TIM21_C2|        |TIM3_C4 |        |        |        |        |        |
 * PE7 |        |        |        |        |        |        |USART5  |        |
 * PE8 |        |        |        |        |        |        |USART4  |        |
 * PE9 |TIM2_C1 |        |TIM2_TR |        |        |        |USART4  |        |
 * PE10|TIM2_C2 |        |        |        |        |        |USART5  |        |
 * PE11|TIM2_C3 |        |        |        |        |        |USART5  |        |
 * PE12|TIM2_C4 |        |SPI1    |        |        |        |        |        |
 * PE13|        |        |SPI1    |        |        |        |        |        |
 * PE14|        |        |SPI1    |        |        |        |        |        |
 * PE15|        |        |SPI1    |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |USB     |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 * PH9 |        |        |        |        |        |        |        |        |
 * PH10|        |        |        |        |        |        |        |        |
 *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_USART1        ((uint8_t)0x00U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_SPI2          ((uint8_t)0x00U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TIM22         ((uint8_t)0x00U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_TIM2          ((uint8_t)0x00U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_USB           ((uint8_t)0x00U)  /* USB Alternate Function mapping      */
/**
  *
  */

/*
 * Alternate function AF1
 */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01U)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_TIM21         ((uint8_t)0x01U)  /* TIM21 Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF2
 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_TIM3          ((uint8_t)0x02U)  /* TIM3 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02U)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_MCO           ((uint8_t)0x02U)  /* MCO Alternate Function mapping        */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping        */
#define GPIO_AF2_SPI2          ((uint8_t)0x02U)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF2_USART5        ((uint8_t)0x02U)  /* USART5 Alternate Function mapping     */
#define GPIO_AF2_SPI1          ((uint8_t)0x02U)  /* SPI1 Alternate Function mapping       */
#define GPIO_AF2_USB           ((uint8_t)0x00U)  /* USB Alternate Function mapping        */
/**
  *
  */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping       */
#define GPIO_AF3_TSC           ((uint8_t)0x03U)  /* TSC  Alternate Function mapping       */
/**
  *
  */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_USART2          ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_USART1          ((uint8_t)0x04U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF4_TIM22           ((uint8_t)0x04U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_TIM3            ((uint8_t)0x04U)  /* TIM3 Alternate Function mapping     */
#define GPIO_AF4_I2C1            ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping     */
/**
  *
  */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF5_USART1        ((uint8_t)0x05U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF5_SPI2          ((uint8_t)0x05U)  /* SPI2 Alternate Function mapping      */
#define GPIO_AF5_I2C2          ((uint8_t)0x05U)  /* I2C2 Alternate Function mapping      */
/**
  *
  */

/*
  * Alternate function AF6
 */
#define GPIO_AF6_USART4        ((uint8_t)0x06U)  /* USART4 Alternate Function mapping    */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06U)  /* LPUART1 Alternate Function mapping   */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
#define GPIO_AF6_I2C1          ((uint8_t)0x06U)  /* I2C1 Alternate Function mapping      */
#define GPIO_AF6_I2C2          ((uint8_t)0x06U)  /* I2C2 Alternate Function mapping      */
#define GPIO_AF6_USART5        ((uint8_t)0x06U)  /* USART5 Alternate Function mapping    */
#define GPIO_AF6_TIM21         ((uint8_t)0x06U)  /* TIM21 Alternate Function mapping     */
/**
  *
  */

 /*
  * Alternate function AF7
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07U)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07U)  /* COMP2 Alternate Function mapping     */
#define GPIO_AF7_I2C3         ((uint8_t)0x07U)  /* I2C3 Alternate Function mapping      */
#define GPIO_AF7_LPUART1      ((uint8_t)0x07U)  /* LPUART1 Alternate Function mapping   */
/**
  *
  */

 /**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */
/**
 * @brief IS_GPIO_AF macro definition
 */
#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

 /**
  * @}
  */
#endif /* (STM32L082xx) || (STM32L072xx) */


/*----------------------------------------------------------------------------*/
/*------------------------- STM32L081xx and STM32L071xx-----------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L081xx) || defined (STM32L071xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */


/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |        |USART2  |TIM2_TR |USART4  |COMP1   |
 * PA1 |EVENTOUT|        |TIM2_C2 |        |USART2  |TIM21_TR|USART4  |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |        |USART2  |        |LPUART1 |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |        |USART2  |        |LPUART1 |        |
 * PA4 |SPI1    |        |        |        |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |        |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |        |TIM3_C1 |        |LPUART1 |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |        |TIM3_C2 |        |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |        |EVENTOUT|USART1  |        |        |I2C3    |
 * PA9 |MCO     |        |        |        |USART1  |        |I2C1    |I2C3    |
 * PA10|        |        |        |        |USART1  |        |I2C1    |        |
 * PA11|SPI1    |        |EVENTOUT|        |USART1  |        |I2C2    |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|        |USART1  |        |I2C2    |COMP2   |
 * PA13|SWDIO   |        |        |        |        |        |LPUART1 |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |LPUART1 |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |USART4  |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|        |TIM3_C3 |        |        |        |        |        |
 * PB1 |        |        |TIM3_C4 |        |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|        |        |        |        |I2C3    |
 * PB3 |SPI1    |        |TIM2_C2 |        |EVENTOUT|USART1  |USART5  |        |
 * PB4 |SPI1    |        |TIM3_C1 |        |TIM22_C1|USART1  |USART5  |I2C3    |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM3_C2 |USART1  |USART5  |        |
 *     |        |        |        |        |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|        |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|        |        |        |USART4  |        |
 * PB8 |        |        |        |        |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |        |TIM2_C3 |        |LPUART1 |SPI2    |I2C2    |LPUART1 |
 * PB11|EVENTOUT|        |TIM2_C4 |        |LPUART1 |        |I2C2    |LPUART1 |
 * PB12|SPI2    |        |LPUART1 |        |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |        |MCO     |        |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |        |RTC     |        |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|        |EVENTOUT|        |        |        |LPUART1 |I2C3    |
 * PC1 |LPTIM1_O|        |EVENTOUT|        |        |        |LPUART1 |I2C3    |
 * PC2 |LPTIM1_I|        |SPI2    |        |        |        |        |        |
 * PC3 |LPTIM1_T|        |SPI2    |        |        |        |        |        |
 * PC4 |EVENTOUT|        |LPUART1 |        |        |        |        |        |
 * PC5 |        |        |LPUART1 |        |        |        |        |        |
 * PC6 |TIM22_C1|        |TIM3_C1 |        |        |        |        |        |
 * PC7 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PC8 |TIM22_TR|        |TIM3_C3 |        |        |        |        |        |
 * PC9 |TIM21_TR|        |        |        |        |        |        |I2C3    |
 *     |        |        |TIM3_C4 |        |        |        |        |        |
 * PC10|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC11|LPUART1 |        |        |        |        |        |USART4  |        |
 * PC12|        |        |USART5  |        |        |        |USART4  |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD0 |TIM21_C1|SPI2    |        |        |        |        |        |        |
 * PD1 |        |SPI2    |        |        |        |        |        |        |
 * PD2 |LPUART1 |        |TIM3_TR |        |        |        |USART5  |        |
 * PD3 |USART2  |        |SPI2    |        |        |        |        |        |
 * PD4 |USART2  |SPI2    |        |        |        |        |        |        |
 * PD5 |USART2  |        |        |        |        |        |        |        |
 * PD6 |USART2  |        |        |        |        |        |        |        |
 * PD7 |USART2  |TIM21_C2|        |        |        |        |        |        |
 * PD8 |LPUART1 |        |        |        |        |        |        |        |
 * PD9 |LPUART1 |        |        |        |        |        |        |        |
 * PD10|        |        |        |        |        |        |        |        |
 * PD11|LPUART1 |        |        |        |        |        |        |        |
 * PD12|LPUART1 |        |        |        |        |        |        |        |
 * PD13|        |        |        |        |        |        |        |        |
 * PD14|        |        |        |        |        |        |        |        |
 * PD15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PE0 |        |        |EVENTOUT|        |        |        |        |        |
 * PE1 |        |        |EVENTOUT|        |        |        |        |        |
 * PE2 |        |        |TIM3_TR |        |        |        |        |        |
 * PE3 |TIM22_C1|        |TIM3_C1 |        |        |        |        |        |
 * PE4 |TIM22_C2|        |TIM3_C2 |        |        |        |        |        |
 * PE5 |TIM21_C1|        |TIM3_C3 |        |        |        |        |        |
 * PE6 |TIM21_C2|        |TIM3_C4 |        |        |        |        |        |
 * PE7 |        |        |        |        |        |        |USART5  |        |
 * PE8 |        |        |        |        |        |        |USART4  |        |
 * PE9 |TIM2_C1 |        |TIM2_TR |        |        |        |USART4  |        |
 * PE10|TIM2_C2 |        |        |        |        |        |USART5  |        |
 * PE11|TIM2_C3 |        |        |        |        |        |USART5  |        |
 * PE12|TIM2_C4 |        |SPI1    |        |        |        |        |        |
 * PE13|        |        |SPI1    |        |        |        |        |        |
 * PE14|        |        |SPI1    |        |        |        |        |        |
 * PE15|        |        |SPI1    |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |        |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 * PH9 |        |        |        |        |        |        |        |        |
 * PH10|        |        |        |        |        |        |        |        |
 *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 *
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_USART1        ((uint8_t)0x00U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_SPI2          ((uint8_t)0x00U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TIM22         ((uint8_t)0x00U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_TIM2          ((uint8_t)0x00U)  /* TIM2 Alternate Function mapping     */
/**
  *
  */

/*
 * Alternate function AF1
 *
 */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01U)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_TIM21         ((uint8_t)0x01U)  /* TIM21 Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF2
 *
 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF2_TIM3          ((uint8_t)0x02U)  /* TIM3 Alternate Function mapping     */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF2_MCO           ((uint8_t)0x02U)  /* MCO Alternate Function mapping      */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping      */
#define GPIO_AF2_SPI2          ((uint8_t)0x02U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF2_USART5        ((uint8_t)0x02U)  /* USART5 Alternate Function mapping   */
#define GPIO_AF2_SPI1          ((uint8_t)0x02U)  /* SPI1 Alternate Function mapping     */
/**
  *
  */

/*
 * Alternate function AF3
 * @{
 */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
/**
  *
  */

/*
 * Alternate function AF4
 *
 */
#define GPIO_AF4_USART2          ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_USART1          ((uint8_t)0x04U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF4_TIM22           ((uint8_t)0x04U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_TIM3            ((uint8_t)0x04U)  /* TIM3 Alternate Function mapping    */
#define GPIO_AF4_I2C1            ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF5
 *
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF5_USART1        ((uint8_t)0x05U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF5_SPI2          ((uint8_t)0x05U)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF5_I2C2          ((uint8_t)0x05U)  /* I2C2 Alternate Function mapping       */
/**
  *
  */

/*
 * Alternate function AF6
 *
 */
#define GPIO_AF6_USART4        ((uint8_t)0x06U)  /* USART4 Alternate Function mapping   */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
#define GPIO_AF6_I2C1          ((uint8_t)0x06U)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF6_I2C2          ((uint8_t)0x06U)  /* I2C2 Alternate Function mapping  */
#define GPIO_AF6_USART5        ((uint8_t)0x06U)  /* USART5 Alternate Function mapping   */
#define GPIO_AF6_TIM21         ((uint8_t)0x06U)  /* TIM21 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF7
 *
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07U)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07U)  /* COMP2 Alternate Function mapping     */
#define GPIO_AF7_I2C3         ((uint8_t)0x07U)  /* I2C3 Alternate Function mapping     */
#define GPIO_AF7_LPUART1      ((uint8_t)0x07U)  /* LPUART1 Alternate Function mapping     */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */

 /**
 * IS_GPIO_AF macro definition
 */
#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

 /**
  * @}
  */
#endif /* (STM32L081xx) || (STM32L071xx) */

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L053xx/STM32L063xx---------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L053xx) || defined (STM32L063xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |TSC     |USART2  |TIM2_TR |        |COMP1   |
 * PA1 |EVENTOUT|LCD     |TIM2_C2 |TSC     |USART2  |TIM21_TR|        |        |
 * PA2 |TIM21_C1|LCD     |TIM2_C3 |TSC     |USART2  |        |        |COMP2   |
 * PA3 |TIM21_C2|LCD     |TIM2_C4 |TSC     |USART2  |        |        |        |
 * PA4 |SPI1    |        |        |TSC     |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |TSC     |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |LCD     |        |TSC     |LPUART  |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |LCD     |        |TSC     |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |LCD     |USB     |EVENTOUT|USART1  |        |        |        |
 * PA9 |MCO     |LCD     |        |TSC     |USART1  |        |        |        |
 * PA10|        |LCD     |        |TSC     |USART1  |        |        |        |
 * PA11|SPI1    |        |EVENTOUT|TSC     |USART1  |        |        |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|TSC     |USART1  |        |        |COMP2   |
 * PA13|SWDIO   |        |USB     |        |        |        |        |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |        |        |
 * PA15|SPI1    |LCD     |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |        |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|LCD     |        |TSC     |        |        |        |        |
 * PB1 |        |LCD     |        |TSC     |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|TSC     |        |        |        |        |
 * PB3 |SPI1    |LCD     |TIM2_C2 |TSC     |EVENTOUT|        |        |        |
 * PB4 |SPI1    |LCD     |EVENTOUT|TSC     |TIM22_C1|        |        |        |
 * PB5 |SPI1    |LCD     |LPTIM1_I|I2C1    |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|TSC     |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|TSC     |        |        |        |        |
 * PB8 |        |LCD     |        |TSC     |I2C1    |        |        |        |
 * PB9 |        |LCD     |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |LCD     |TIM2_C3 |TSC     |LPUART1 |SPI2    |I2C2    |        |
 * PB11|EVENTOUT|LCD     |TIM2_C4 |TSC     |LPUART1 |        |I2C2    |        |
 * PB12|SPI2    |LCD     |LPUART1 |TSC     |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |LCD     |        |TSC     |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |LCD     |RTC     |TSC     |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |LCD     |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|LCD     |EVENTOUT|TSC     |        |        |        |        |
 * PC1 |LPTIM1_O|LCD     |EVENTOUT|TSC     |        |        |        |        |
 * PC2 |LPTIM1_I|LCD     |SPI2    |TSC     |        |        |        |        |
 * PC3 |LPTIM1_T|LCD     |SPI2    |TSC     |        |        |        |        |
 * PC4 |EVENTOUT|LCD     |LPUART  |        |        |        |        |        |
 * PC5 |        |LCD     |LPUART  |TSC     |        |        |        |        |
 * PC6 |TIM22_C1|LCD     |        |TSC     |        |        |        |        |
 * PC7 |TIM22_C2|LCD     |        |TSC     |        |        |        |        |
 * PC8 |TIM22_TR|LCD     |        |TSC     |        |        |        |        |
 * PC9 |TIM21_TR|LCD     |USB     |TSC     |        |        |        |        |
 * PC10|LPUART  |LCD     |        |        |        |        |        |        |
 * PC11|LPUART  |LCD     |        |        |        |        |        |        |
 * PC12|        |LCD     |        |        |        |        |        |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD2 |LPUART  |LCD     |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |USB     |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 *  *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_SPI2          ((uint8_t)0x00U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_USART1        ((uint8_t)0x00U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USB           ((uint8_t)0x00U)  /* USB Alternate Function mapping      */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TSC           ((uint8_t)0x00U)  /* TSC Alternate Function mapping      */
#define GPIO_AF0_TIM2          ((uint8_t)0x00U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_TIM22         ((uint8_t)0x00U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
/**
  *
  */

 /*
  * Alternate function AF1
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01U)  /* SPI1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01U)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF1_LCD           ((uint8_t)0x01U)  /* LCD Alternate Function mapping   */
/**
  *
  */

/*
 * Alternate function AF2
 */
#define GPIO_AF2_SPI2          ((uint8_t)0x02U)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02U)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_USB           ((uint8_t)0x02U)  /* USB Alternate Function mapping        */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping        */
/**
  *
  */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_TSC           ((uint8_t)0x03U)  /* TSC  Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_I2C1            ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_USART1          ((uint8_t)0x04U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_USART2          ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_TIM22           ((uint8_t)0x04U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

 /*
 * Alternate function AF5
 */
#define GPIO_AF5_SPI2          ((uint8_t)0x05U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_I2C2          ((uint8_t)0x05U)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05U)  /* TIM22 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF6
 */
#define GPIO_AF6_I2C2          ((uint8_t)0x06U)  /* I2C2 Alternate Function mapping      */
#define GPIO_AF6_TIM21         ((uint8_t)0x06U)  /* TIM21 Alternate Function mapping     */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF7
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07U)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07U)  /* COMP2 Alternate Function mapping     */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */
/**
 * @brief  IS_GPIO_AF macro definition
 */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

/**
  * @}
  */

#endif /* STM32L053xx || STM32L063xx */
/*------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L052xx/STM32L062xx---------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L052xx) || defined (STM32L062xx)

/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |TSC     |USART2  |TIM2_TR |        |COMP1   |
 * PA1 |EVENTOUT|        |TIM2_C2 |TSC     |USART2  |TIM21_TR|        |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |TSC     |USART2  |        |        |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |TSC     |USART2  |        |        |        |
 * PA4 |SPI1    |        |        |TSC     |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |TSC     |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |        |        |TSC     |LPUART  |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |        |        |TSC     |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |USB     |EVENTOUT|USART1  |        |        |        |
 * PA9 |MCO     |        |        |TSC     |USART1  |        |        |        |
 * PA10|        |        |        |TSC     |USART1  |        |        |        |
 * PA11|SPI1    |        |EVENTOUT|TSC     |USART1  |        |        |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|TSC     |USART1  |        |        |COMP2   |
 * PA13|SWDIO   |        |USB     |        |        |        |        |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |        |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |        |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|        |        |TSC     |        |        |        |        |
 * PB1 |        |        |        |TSC     |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|TSC     |        |        |        |        |
 * PB3 |SPI1    |        |TIM2_C2 |TSC     |EVENTOUT|        |        |        |
 * PB4 |SPI1    |        |EVENTOUT|TSC     |TIM22_C1|        |        |        |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|TSC     |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|TSC     |        |        |        |        |
 * PB8 |        |        |        |TSC     |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |        |TIM2_C3 |TSC     |LPUART1 |SPI2    |I2C2    |        |
 * PB11|EVENTOUT|        |TIM2_C4 |TSC     |LPUART1 |        |I2C2    |        |
 * PB12|SPI2    |        |LPUART1 |TSC     |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |        |        |TSC     |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |        |RTC     |TSC     |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|        |EVENTOUT|TSC     |        |        |        |        |
 * PC1 |LPTIM1_O|        |EVENTOUT|TSC     |        |        |        |        |
 * PC2 |LPTIM1_I|        |SPI2    |TSC     |        |        |        |        |
 * PC3 |LPTIM1_T|        |SPI2    |TSC     |        |        |        |        |
 * PC4 |EVENTOUT|        |LPUART  |        |        |        |        |        |
 * PC5 |        |        |LPUART  |TSC     |        |        |        |        |
 * PC6 |TIM22_C1|        |        |TSC     |        |        |        |        |
 * PC7 |TIM22_C2|        |        |TSC     |        |        |        |        |
 * PC8 |TIM22_TR|        |        |TSC     |        |        |        |        |
 * PC9 |TIM21_TR|        |USB     |TSC     |        |        |        |        |
 * PC10|LPUART  |        |        |        |        |        |        |        |
 * PC11|LPUART  |        |        |        |        |        |        |        |
 * PC12|        |        |        |        |        |        |        |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD2 |LPUART  |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |USB     |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 *  *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_SPI2          ((uint8_t)0x00U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_USART1        ((uint8_t)0x00U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_USB           ((uint8_t)0x00U)  /* USB Alternate Function mapping      */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TSC           ((uint8_t)0x00U)  /* TSC Alternate Function mapping      */
#define GPIO_AF0_TIM2          ((uint8_t)0x00U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_TIM22         ((uint8_t)0x00U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF1
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01U)  /* SPI1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01U)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping  */
/**
  *
  */

/**
 * Alternate function AF2
 */
#define GPIO_AF2_SPI2          ((uint8_t)0x02U)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02U)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_USB           ((uint8_t)0x02U)  /* USB Alternate Function mapping        */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping        */
/**
  *
  */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_TSC           ((uint8_t)0x03U)  /* TSC  Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_I2C1            ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_USART1          ((uint8_t)0x04U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_USART2          ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_TIM22           ((uint8_t)0x04U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_SPI2          ((uint8_t)0x05U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_I2C2          ((uint8_t)0x05U)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05U)  /* TIM22 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF6
 */
#define GPIO_AF6_I2C2          ((uint8_t)0x06U)  /* I2C2 Alternate Function mapping      */
#define GPIO_AF6_TIM21         ((uint8_t)0x06U)  /* TIM21 Alternate Function mapping     */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF7
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07U)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07U)  /* COMP2 Alternate Function mapping     */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */
/**
 * @brief  IS_GPIO_AF macro definition
 */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

/**
  * @}
  */
#endif /* STM32L052xx || STM32L062xx */
/*------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L051xx/STM32L061xx---------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L051xx)|| defined (STM32L061xx)
/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |        |TIM2_C1 |        |USART2  |TIM2_TR |        |COMP1   |
 * PA1 |EVENTOUT|        |TIM2_C2 |        |USART2  |TIM21_TR|        |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |        |USART2  |        |        |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |        |USART2  |        |        |        |
 * PA4 |SPI1    |        |        |        |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |        |TIM2_TR |        |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |        |        |        |LPUART  |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |        |        |        |        |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |        |EVENTOUT|USART1  |        |        |        |
 * PA9 |MCO     |        |        |        |USART1  |        |        |        |
 * PA10|        |        |        |        |USART1  |        |        |        |
 * PA11|SPI1    |        |EVENTOUT|        |USART1  |        |        |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|        |USART1  |        |        |COMP2   |
 * PA13|SWDIO   |        |        |        |        |        |        |        |
 * PA14|SWCLK   |        |        |        |USART2  |        |        |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |        |        |
 *______________________________________________________________________________
 * PB0 |EVENTOUT|        |        |        |        |        |        |        |
 * PB1 |        |        |        |        |LPUART1 |        |        |        |
 * PB2 |        |        |LPTIM1_O|        |        |        |        |        |
 * PB3 |SPI1    |        |TIM2_C2 |        |EVENTOUT|        |        |        |
 * PB4 |SPI1    |        |EVENTOUT|        |TIM22_C1|        |        |        |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM22_C2|        |        |        |
 * PB6 |USART1  |I2C1    |LPTIM1_T|        |        |        |        |        |
 * PB7 |USART1  |I2C1    |LPTIM1_I|        |        |        |        |        |
 * PB8 |        |        |        |        |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |SPI2    |        |        |
 * PB10|        |        |TIM2_C3 |        |LPUART1 |SPI2    |I2C2    |        |
 * PB11|EVENTOUT|        |TIM2_C4 |        |LPUART1 |        |I2C2    |        |
 * PB12|SPI2    |        |LPUART1 |        |        |I2C2    |EVENTOUT|        |
 * PB13|SPI2    |        |        |        |LPUART1 |I2C2    |TIM21_C1|        |
 * PB14|SPI2    |        |RTC     |        |LPUART1 |I2C2    |TIM21_C2|        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *______________________________________________________________________________
 * PC0 |LPTIM1_I|        |EVENTOUT|        |        |        |        |        |
 * PC1 |LPTIM1_O|        |EVENTOUT|        |        |        |        |        |
 * PC2 |LPTIM1_I|        |SPI2    |        |        |        |        |        |
 * PC3 |LPTIM1_T|        |SPI2    |        |        |        |        |        |
 * PC4 |EVENTOUT|        |LPUART  |        |        |        |        |        |
 * PC5 |        |        |LPUART  |        |        |        |        |        |
 * PC6 |TIM22_C1|        |        |        |        |        |        |        |
 * PC7 |TIM22_C2|        |        |        |        |        |        |        |
 * PC8 |TIM22_TR|        |        |        |        |        |        |        |
 * PC9 |TIM21_TR|        |        |        |        |        |        |        |
 * PC10|LPUART  |        |        |        |        |        |        |        |
 * PC11|LPUART  |        |        |        |        |        |        |        |
 * PC12|        |        |        |        |        |        |        |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PD2 |LPUART  |        |        |        |        |        |        |        |
 *______________________________________________________________________________
 * PH0 |        |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 *  *
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_SPI2          ((uint8_t)0x00U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF0_USART1        ((uint8_t)0x00U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TIM2          ((uint8_t)0x00U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_TIM22         ((uint8_t)0x00U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF1
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01U)  /* SPI1 Alternate Function mapping  */
#define GPIO_AF1_SPI2          ((uint8_t)0x01U)  /* SPI2 Alternate Function mapping  */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping  */
/**
  *
  */

 /*
  * Alternate function AF2
 */
#define GPIO_AF2_SPI2          ((uint8_t)0x02U)  /* SPI2 Alternate Function mapping       */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02U)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_USB           ((uint8_t)0x02U)  /* USB Alternate Function mapping        */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping        */
/**
  *
  */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_I2C1            ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_USART1          ((uint8_t)0x04U)  /* USART1 Alternate Function mapping   */
#define GPIO_AF4_USART2          ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_TIM22           ((uint8_t)0x04U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_SPI2          ((uint8_t)0x05U)  /* SPI2 Alternate Function mapping     */
#define GPIO_AF5_I2C2          ((uint8_t)0x05U)  /* I2C2 Alternate Function mapping     */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05U)  /* TIM22 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF6
 */
#define GPIO_AF6_I2C2          ((uint8_t)0x06U)  /* I2C2 Alternate Function mapping      */
#define GPIO_AF6_TIM21         ((uint8_t)0x06U)  /* TIM21 Alternate Function mapping     */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF7
 */
#define GPIO_AF7_COMP1        ((uint8_t)0x07U)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2        ((uint8_t)0x07U)  /* COMP2 Alternate Function mapping     */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */

/**
 * @brief  IS_GPIO_AF macro definition
 */
#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

/**
  * @}
  */
#endif /* STM32L051xx/STM32L061xx*/
/*------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L031xx/STM32L041xx---------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L031xx)|| defined (STM32L041xx)
/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0  |   AF1  |   AF2  |   AF3  |   AF4  |   AF5  |   AF6  |   AF7  |
 *______________________________________________________________________________
 * PA0 |        |LPTIM1  |TIM2_C1 |        |USART2  |TIM2_TR |        |COMP1   |
 * PA1 |EVENTOUT|LPTIM1  |TIM2_C2 |I2C1    |USART2  |TIM21_TR|        |        |
 * PA2 |TIM21_C1|        |TIM2_C3 |        |USART2  |        |LPUART1 |COMP2   |
 * PA3 |TIM21_C2|        |TIM2_C4 |        |USART2  |        |LPUART1 |        |
 * PA4 |SPI1    |LPTIM1  |        |        |USART2  |TIM22_TR|        |        |
 * PA5 |SPI1    |LPTIM1  |TIM2_TR |        |        |TIM2_C1 |        |        |
 * PA6 |SPI1    |LPTIM1  |        |        |LPUART  |TIM22_C1|EVENTOUT|COMP1   |
 * PA7 |SPI1    |LPTIM1  |        |        |USART2  |TIM22_C2|EVENTOUT|COMP2   |
 * PA8 |MCO     |        |LPTIM1  |EVENTOUT|USART2  |TIM2_C1 |        |        |
 * PA9 |MCO     |I2C1    |        |        |USART2  |TIM22_C1|        |        |
 * PA10|        |I2C1    |        |        |USART2  |TIM22_C2|        |        |
 * PA11|SPI1    |        |EVENTOUT|        |USART2  |TIM21_C2|        |COMP1   |
 * PA12|SPI1    |        |EVENTOUT|        |USART2  |        |        |COMP2   |
 * PA13|SWDIO   |LPTIM1  |        |        |        |        |LPUART1 |        |
 * PA14|SWCLK   |LPTIM1  |        |I2C1    |USART2  |        |LPUART1 |        |
 * PA15|SPI1    |        |TIM2_TR |EVENTOUT|USART2  |TIM2_C1 |        |        |
 *_____________________________________________________________________________|
 * PB0 |EVENTOUT|SPI1    |        |        |USART2  |TIM2_C3 |        |        |
 * PB1 |USART2  |SPI1    |        |        |LPUART1 |TIM2_C4 |        |        |
 * PB2 |        |        |LPTIM1_O|        |        |        |        |        |
 * PB3 |SPI1    |        |TIM2_C2 |        |EVENTOUT|        |        |        |
 * PB4 |SPI1    |        |EVENTOUT|        |TIM22_C1|        |        |        |
 * PB5 |SPI1    |        |LPTIM1_I|I2C1    |TIM22_C2|        |        |        |
 * PB6 |USART2  |I2C1    |LPTIM1_T|        |        |TIM21_C1|        |        |
 * PB7 |USART2  |I2C1    |LPTIM1_I|        |        |        |        |        |
 * PB8 |        |        |        |        |I2C1    |        |        |        |
 * PB9 |        |        |EVENTOUT|        |I2C1    |        |        |        |
 * PB10|        |        |TIM2_C3 |        |        |        |LPUART1 |        |
 * PB11|EVENTOUT|        |TIM2_C4 |        |        |        |LPUART1 |        |
 * PB12|SPI2    |        |        |        |        |        |EVENTOUT|        |
 * PB13|SPI2    |        |MCO     |        |        |TIM21_C1|LPUART1 |        |
 * PB14|SPI2    |        |RTC     |        |        |TIM21_C2|LPUART1 |        |
 * PB15|SPI2    |        |RTC     |        |        |        |        |        |
 *_____________________________________________________________________________|
 * PC0 |LPTIM1_I|        |EVENTOUT|        |        |        |LPUART1 |        |
 * PC13|        |        |        |        |        |        |        |        |
 * PC14|        |        |        |        |        |        |        |        |
 * PC15|        |        |        |        |        |        |        |        |
 *_____________________________________________________________________________|
 * PH0 |        |        |        |        |        |        |        |        |
 * PH1 |        |        |        |        |        |        |        |        |
 *_____________________________________________________________________________|
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF1
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01U)  /* SPI1 Alternate Function mapping   */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping   */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01U)  /* LPTIM1 Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF2
 */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_MCO           ((uint8_t)0x02U)  /* MCO Alternate Function mapping        */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping        */
/**
  *
  */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_I2C1          ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_USART2        ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1       ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_TIM22         ((uint8_t)0x04U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_EVENTOUT      ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05U)  /* TIM22 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF6
 */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF7
 */
#define GPIO_AF7_COMP1         ((uint8_t)0x07U)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2         ((uint8_t)0x07U)  /* COMP2 Alternate Function mapping     */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */
/**
 * @brief  IS_GPIO_AF macro definition
 */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

/**
  * @}
  */

#endif /* STM32L031xx/STM32L041xx*/
/*------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L011xx/STM32L021xx---------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L011xx)|| defined (STM32L021xx)
/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0   |   AF1    |   AF2  |   AF3   |   AF4    |   AF5  |   AF6     |   AF7   |
 *______________________________________________________________________________________
 * PA0 |USART2_RX|LPTIM1_IN1|TIM2_C1  |        |USART2_CTS|TIM2_ETR|LPUART1_RX |COMP1_OUT|
 * PA1 |EVENTOUT |LPTIM1_IN2|TIM2_C2  |I2C1    |USART2_RTS|TIM21_TR|LPUART1_TX |         |
 * PA2 |TIM21_C1 |          |TIM2_C3  |        |USART2_TX |        |LPUART1_TX |COMP2_OUT|
 * PA3 |TIM21_C2 |          |TIM2_C4  |        |USART2_RX |        |LPUART1_RX |         |
 * PA4 |SPI1     |LPTIM1_IN1|LPTIM1_TR|I2C1_SCL|USART2_CK |TIM2_TR |LPUART1_TX |COMP2_OUT|
 * PA5 |SPI1     |LPTIM1_IN2|TIM2_TR  |        |          |TIM2_C1 |           |         |
 * PA6 |SPI1     |LPTIM1_ETR|         |        |LPUART1_CT|        |EVENTOUT   |COMP1_OUT|
 * PA7 |SPI1     |LPTIM1_OUT|         |        |USART2_CTS|TIM21_T |EVENTOUT   |COMP2_OUT|
 * PA8 |MCO      |          |LPTIM1_I1|EVENTOUT|USART2_CK |TIM2_C1 |           |         |
 * PA9 |MCO      |I2C1_SCL  |LPTIM1_O |        |USART2_TX |TIM21_C2|           |COMP1_OUT|
 * PA10|TIM21_C1 |I2C1_SDA  |RTC_REFIN|        |USART2_RX |TIM2_C3 |           |COMP1_OUT|
 * PA11|SPI1     |LPTIM1_OUT|EVENTOUT |        |USART2_CTS|TIM21_C2|           |COMP1_OUT|
 * PA12|SPI1     |          |EVENTOUT |        |USART2_RTS|        |           |COMP2_OUT|
 * PA13|SWDIO    |LPTIM1_T  |         |I2C1_SDA|          |SPI1    |LPUART1_RX |COMP1_OUT|
 * PA14|SWCLK    |LPTIM1_O  |         |I2C1_SMB|USART2_TX |SPI1    |LPUART1_TX |COMP2_OUT|
 * PA15|SPI1     |          |TIM2_TR  |EVENTOUT|USART2_RX |TIM2_C1 |           |         |
 *______________________________________________________________________________________ |
 * PB0 |EVENTOUT |SPI1      |TIM2_C2  |        |USART2_RTS|TIM2_C3 |           |         |
 * PB1 |USART2_CK|SPI1      |LPTIM1_I1|        |LPUART1_RT|TIM2_C4 |           |         |
 * PB2 |         |          |LPTIM1_O |        |          |        |           |         |
 * PB3 |SPI1     |          |TIM2_C2  |        |EVENTOUT  |        |           |         |
 * PB4 |SPI1     |          |EVENTOUT |        |          |        |           |         |
 * PB5 |SPI1     |          |LPTIM1_I1|I2C1    |          |TIM21_C1|           |         |
 * PB6 |USART2_TX|I2C1_SCL  |LPTIM1_T |        |          |TIM2_C3 |LPUART1_TX |         |
 * PB7 |USART2_RX|I2C1      |LPTIM1_I2|        |          |TIM2_C4 |LPUART1_RX |         |
 * PB8 |USART2_TX|          |EVENTOUT |        |I2C1      |SPI1    |           |         |
 * PB9 |         |          |         |        |          |        |           |         |
 *______________________________________________________________________________________ |
 * PC14|         |          |         |        |          |        |           |         |
 * PC15|         |          |         |        |          |        |           |         |
 *______________________________________________________________________________________ |
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
/**
  *
  */

/*
 *  Alternate function AF1
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01U)  /* SPI1 Alternate Function mapping   */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping   */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01U)  /* LPTIM1 Alternate Function mapping */
/**
  *
  */

/*  Alternate function AF2
 *
 */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping        */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping   */
/**
  *
  */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_I2C1          ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_USART2        ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1       ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_EVENTOUT      ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_SPI1          ((uint8_t)0x05U)  /* SPI1 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF6
 */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF7
 */
#define GPIO_AF7_COMP1         ((uint8_t)0x07U)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2         ((uint8_t)0x07U)  /* COMP2 Alternate Function mapping     */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */
/**
 *  IS_GPIO_AF macro definition
 */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

/**
  * @}
  */

#endif /* STM32L011xx/STM32L021xx*/

/*----------------------------------------------------------------------------*/
/*----------------------------- STM32L010xB ----------------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L010xB)
/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*     |   AF0     |   AF1    |   AF2     |   AF3   |   AF4     |   AF5   |   AF6     |   AF7    |
 *_______________________________________________________________________________________________|
 * PA0 |           |          |TIM2_CH1   |         |USART2_CTS |TIM2_ETR |           |          |
 * PA1 |EVENTOUT   |          |TIM2_CH2   |         |USART2_RTS |TIM21_ETR|           |          |
 * PA2 |TIM21_CH1  |          |TIM2_CH3   |         |USART2_TX  |         |LPUART1_TX |          |
 * PA3 |TIM21_CH2  |          |TIM2_CH4   |         |USART2_RX  |         |LPUART1_RX |          |
 * PA4 |SPI1_NSS   |          |           |         |USART2_CK  |TIM22_ETR|           |          |
 * PA5 |SPI1_SCK   |          |TIM2_ETR   |         |           |TIM2_CH1 |           |          |
 * PA6 |SPI1_MISO  |          |           |         |LPUART1_CTS|TIM22_CH1|EVENTOUT   |          |
 * PA7 |SPI1_MOSI  |          |           |         |           |TIM22_CH2|EVENTOUT   |          |
 * PA8 |MCO        |          |           |EVENTOUT |           |         |           |          |
 * PA9 |MCO        |          |           |         |           |         |I2C1_SCL   |          |
 * PA10|           |          |           |         |           |         |I2C1_SDA   |          |
 * PA11|SPI1_MISO  |          |EVENTOUT   |         |           |         |           |          |
 * PA12|SPI1_MOSI  |          |EVENTOUT   |         |           |         |           |          |
 * PA13|SWDIO      |          |           |         |           |         |LPUART1_RX |          |
 * PA14|SWCLK      |          |           |         |USART2_TX  |         |LPUART1_TX |          |
 * PA15|SPI1_NSS   |          |TIM2_ETR   |EVENTOUT |USART2_RX  |TIM2_CH1 |           |          |
 *_______________________________________________________________________________________________|
 * PB0 |EVENTOUT   |          |           |         |           |         |           |          |
 * PB1 |           |          |           |         |LPUART1_RTS|         |           |          |
 * PB2 |           |          |LPTIM1_OUT |         |           |         |           |          |
 * PB3 |SPI1_SCK   |          |TIM2_CH2   |         |EVENTOUT   |         |           |          |
 * PB4 |SPI1_MISO  |          |           |         |TIM22_CH1  |         |           |          |
 * PB5 |SPI1_MOSI  |          |LPTIM1_IN1 |I2C1_SMBA|TIM22_CH2  |         |           |          |
 * PB6 |           |I2C1_SCL  |LPTIM1_ETR |         |           |         |           |          |
 * PB7 |           |I2C1_SDA  |LPTIM1_IN2 |         |           |         |           |          |
 * PB8 |           |          |           |         |I2C1_SCL   |         |           |          |
 * PB9 |           |          |EVENTOUT   |         |I2C1_SDA   |         |           |          |
 * PB10|           |          |TIM2_CH3   |         |LPUART1_TX |         |           |LPUART1_RX|
 * PB11|EVENTOUT   |          |TIM2_CH4   |         |LPUART1_RX |         |           |LPUART1_TX|
 * PB12|           |          |LPUART1_RTS|         |           |         |EVENTOUT   |          |
 * PB13|           |          |MCO        |         |LPUART1_CTS|         |TIM21_CH1  |          |
 * PB14|           |          |RTC_OUT    |         |LPUART1_RTS|         |TIM21_CH2  |          |
 * PB15|           |          |RTC_REFIN  |         |           |         |           |          |
 *_______________________________________________________________________________________________|
 * PC0 |LPTIM1_IN1 |          |EVENTOUT   |         |           |         |LPUART1_RX |          |
 * PC1 |LPTIM1_OUT |          |EVENTOUT   |         |           |         |LPUART1_TX |          |
 * PC2 |LPTIM1_IN2 |          |           |         |           |         |           |          |
 * PC3 |LPTIM1_ETR |          |           |         |           |         |           |          |
 * PC4 |EVENTOUT   |          |LPUART1_TX |         |           |         |           |          |
 * PC5 |           |          |LPUART1_RX |         |           |         |           |          |
 * PC6 |TIM22_CH1  |          |           |         |           |         |           |          |
 * PC7 |TIM22_CH2  |          |           |         |           |         |           |          |
 * PC8 |TIM22_ETR  |          |           |         |           |         |           |          |
 * PC9 |TIM21_ETR  |          |           |         |           |         |           |          |
 * PC10|LPUART1_TX |          |           |         |           |         |           |          |
 * PC11|LPUART1_RX |          |           |         |           |         |           |          |
 *_______________________________________________________________________________________________|
 * PD2 |LPUART1_RTS|          |           |         |           |         |           |          |
 *_______________________________________________________________________________________________|
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 *
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_TIM22         ((uint8_t)0x00U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00U)  /* LPUART1 Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF1
 *
 */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF2
 *
 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF2_MCO           ((uint8_t)0x02U)  /* MCO Alternate Function mapping      */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping      */
/**
  *
  */

/*
 * Alternate function AF3
 * @{
 */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
/**
  *
  */

/*
 * Alternate function AF4
 *
 */
#define GPIO_AF4_USART2          ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF4_TIM22           ((uint8_t)0x04U)  /* TIM22 Alternate Function mapping    */
#define GPIO_AF4_I2C1            ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF5
 *
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_TIM22         ((uint8_t)0x05U)  /* TIM22 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF6
 *
 */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
#define GPIO_AF6_I2C1          ((uint8_t)0x06U)  /* I2C1 Alternate Function mapping  */
#define GPIO_AF6_TIM21         ((uint8_t)0x06U)  /* TIM21 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF7
 *
 */
#define GPIO_AF7_LPUART1      ((uint8_t)0x07U)  /* LPUART1 Alternate Function mapping     */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */

 /**
 * IS_GPIO_AF macro definition
 */
#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x07)

/**
  * @}
  */

#endif /* STM32L010xB */

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L010x8 --------------------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L010x8)
/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*      |   AF0       |   AF1      |   AF2       |   AF3    |   AF4      |   AF5      |   AF6     |
 *________________________________________________________________________________________________|
 * PA0  |             |            | TIM2_CH1    |          | USART2_CTS  | TIM2_ETR  |           |
 * PA1  | EVENTOUT    |            | TIM2_CH2    |          | USART2_RTS  | TIM21_ETR |           |
 * PA2  | TIM21_CH1   |            | TIM2_CH3    |          | USART2_TX   |           |           |
 * PA3  | TIM21_CH2   |            | TIM2_CH4    |          | USART2_RX   |           |           |
 * PA4  | SPI1_NSS    |            |             |          | USART2_CK   |           |           |
 * PA5  | SPI1_SCK    |            | TIM2_ETR    |          |             | TIM2_CH1  |           |
 * PA6  | SPI1_MISO   |            |             |          | LPUART1_CTS |           | EVENTOUT  |
 * PA7  | SPI1_MOSI   |            |             |          |             |           | EVENTOUT  |
 * PA8  | MCO         |            |             | EVENTOUT |             |           |           |
 * PA9  | MCO         |            |             |          |             |           |           |
 * PA10 |             |            |             |          |             |           |           |
 * PA11 | SPI1_MISO   |            | EVENTOUT    |          |             |           |           |
 * PA12 | SPI1_MOSI   |            | EVENTOUT    |          |             |           |           |
 * PA13 | SWDIO       |            |             |          |             |           |           |
 * PA14 | SWCLK       |            |             |          | USART2_TX   |           |           |
 * PA15 | SPI1_NSS    |            | TIM2_ETR    | EVENTOUT | USART2_RX   | TIM2_CH1  |           |
 *________________________________________________________________________________________________|
 * PB0  | EVENTOUT    |            |             |          |             |           |           |
 * PB1  |             |            |             |          | LPUART1_RTS |           |           |
 * PB2  |             |            | LPTIM1_OUT  |          |             |           |           |
 * PB3  | SPI1_SCK    |            | TIM2_CH2    |          | EVENTOUT    |           |           |
 * PB4  | SPI1_MISO   | EVENTOUT   |             |          |             |           |           |
 * PB5  | SPI1_MOSI   | LPTIM1_IN1 | I2C1_SMBA   |          |             |           |           |
 * PB6  |             | I2C1_SCL   | LPTIM1_ETR  |          |             |           |           |
 * PB7  |             | I2C1_SDA   | LPTIM1_IN2  |          |             |           |           |
 * PB8  |             |            |             |          | I2C1_SCL    |           |           |
 * PB9  |             |            | EVENTOUT    |          | I2C1_SDA    |           |           |
 * PB10 |             |            | TIM2_CH3    |          | LPUART1_TX  |           |           |
 * PB11 | EVENTOUT    |            | TIM2_CH4    |          | LPUART1_RX  |           |           |
 * PB12 |             |            | LPUART1_RTS |          |             | EVENTOUT  |           |
 * PB13 |             |            |             |          | LPUART1_CTS |           | TIM21_CH1 |
 * PB14 |             |            | RTC_OUT     |          | LPUART1_RTS |           | TIM21_CH2 |
 * PB15 |             |            | RTC_REFIN   |          |             |           |           |
 *________________________________________________________________________________________________|
 * PC0  | LPTIM1_IN1  |            | EVENTOUT    |          |             |           |           |
 * PC1  | LPTIM1_OUT  |            | EVENTOUT    |          |             |           |           |
 * PC2  | LPTIM1_IN2  |            |             |          |             |           |           |
 * PC3  | LPTIM1_ETR  |            |             |          |             |           |           |
 * PC4  | EVENTOUT    |            | LPUART1_TX  |          |             |           |           |
 * PC5  |             |            | LPUART1_RX  |          |             |           |           |
 * PC9  | TIM21_ETR   |            |             |          |             |           |           |
 * PC10 | LPUART1_TX  |            |             |          |             |           |           |
 * PC11 | LPUART1_RX  |            |             |          |             |           |           |
 * PD2  | LPUART1_RTS |            |             |          |             |           |           |
 *________________________________________________________________________________________________|
 */

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
#define GPIO_AF0_LPUART1       ((uint8_t)0x00U)  /* LPUART1 Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF1
 */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping  */
/**
  *
  */

 /*
  * Alternate function AF2
 */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_LPUART1       ((uint8_t)0x02U)  /* LPUART1 Alternate Function mapping    */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping        */
/**
  *
  */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_USART2          ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1         ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_I2C1            ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_EVENTOUT        ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
/**
  *
  */

/*
 * Alternate function AF6
 */
#define GPIO_AF6_TIM21         ((uint8_t)0x06U)  /* TIM21 Alternate Function mapping     */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */


/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */

/**
 * @brief  IS_GPIO_AF macro definition
 */
#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x06)

/**
  * @}
  */
#endif /* STM32L010x8 */


/*----------------------------------------------------------------------------*/
/*------------------------- STM32L010x6 --------------------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L010x6)
/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*      |   AF0      |   AF1      |   AF2      |     AF3     |   AF4       |   AF5     |   AF6      |
 *__________________________________________________________________________________________________|
 * PA1  | EVENTOUT   | LPTIM1_IN2 | TIM2_CH2   | I2C1_SMBA   | USART2_RTS  | TIM21_ETR |            |
 * PA2  | TIM21_CH1  |            | TIM2_CH3   |             | USART2_TX   |           | LPUART1_TX |
 * PA3  | TIM21_CH2  |            | TIM2_CH4   |             | USART2_RX   |           | LPUART1_RX |
 * PA4  | SPI1_NSS   | LPTIM1_IN1 |            |             | USART2_CK   |           |            |
 * PA5  | SPI1_SCK   | LPTIM1_IN2 | TIM2_ETR   |             |             | TIM2_CH1  |            |
 * PA6  | SPI1_MISO  | LPTIM1_ETR |            |             | LPUART1_CTS |           | EVENTOUT   |
 * PA7  | SPI1_MOSI  | LPTIM1_OUT |            |             | USART2_CTS  |           | EVENTOUT   |
 * PA8  | MCO        |            | LPTIM1_IN1 | EVENTOUT    | USART2_CK   | TIM2_CH1  |            |
 * PA9  | MCO        | I2C1_SCL   |            |             | USART2_TX   |           |            |
 * PA10 |            | I2C1_SDA   |            |             | USART2_RX   |           |            |
 * PA11 | SPI1_MISO  |            | EVENTOUT   |             | USART2_CTS  | TIM21_CH2 |            |
 * PA12 | SPI1_MOSI  |            | EVENTOUT   |             | USART2_RTS  |           |            |
 * PA13 | SWDIO      | LPTIM1_ETR |            |             |             |           | LPUART1_RX |
 * PA14 | SWCLK      | LPTIM1_OUT |            | I2C1_SMBA   | USART2_TX   |           | LPUART1_TX |
 * PA15 | SPI1_NSS   |            | TIM2_ETR   | EVENTOUT    | USART2_RX   | TIM2_CH1  |            |
 *__________________________________________________________________________________________________|
 * PB0  | EVENTOUT   | SPI1_MISO  |            |             | USART2_RTS  | TIM2_CH3  |            |
 * PB1  | USART2_CK  | SPI1_MOSI  |            |             | LPUART1_RTS | TIM2_CH4  |            |
 * PB2  |            |            | LPTIM1_OUT |             |             |           |            |
 * PB3  | SPI1_SCK   |            | TIM2_CH2   |             | EVENTOUT    |           |            |
 * PB4  | SPI1_MISO  |            | EVENTOUT   |             |             |           |            |
 * PB5  | SPI1_MOSI  | LPTIM1_IN1 | I2C1_SMBA  |             |             |           |            |
 * PB6  | USART2_TX  | I2C1_SCL   | LPTIM1_ETR |             |             | TIM21_CH1 |            |
 * PB7  | USART2_RX  | I2C1_SDA   | LPTIM1_IN2 |             |             |           |            |
 * PB8  |            |            |            |             | I2C1_SCL    |           |            |
 * PB9  |            |            | EVENTOUT   |             | I2C1_SDA    |           |            |
 * PB10 |            |            | TIM2_CH3   |             |             |           | LPUART1_TX |
 * PB11 | EVENTOUT   |            | TIM2_CH4   |             |             |           | LPUART1_RX |
 * PB12 | SPI1_NSS   |            |            |             |             |           | EVENTOUT   |
 * PB13 | SPI1_SCK   |            | MCO        |             |             | TIM21_CH1 | LPUART1_CTS|
 * PB14 | SPI1_MISO  |            | RTC_OUT    |             |             | TIM21_CH2 | LPUART1_RTS|
 * PB15 | SPI1_MOSI  |            | RTC_REFIN  |             |             |           |            |
 *__________________________________________________________________________________________________|
 * PC0  | LPTIM1_IN1 |            | EVENTOUT   |             |             |           | LPUART1_RX |
 *__________________________________________________________________________________________________|
*/
/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_LPTIM1        ((uint8_t)0x00U)  /* LPTIM1 Alternate Function mapping   */
/**
  *
  */

/*
 * Alternate function AF1
 */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping   */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01U)  /* LPTIM1 Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF2
 */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_MCO           ((uint8_t)0x02U)  /* MCO Alternate Function mapping        */
#define GPIO_AF2_I2C1          ((uint8_t)0x02U)  /* I2C1 Alternate Function mapping       */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping   */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping        */
/**
  *
  */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_USART2        ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_LPUART1       ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_I2C1          ((uint8_t)0x04U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF4_EVENTOUT      ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
/**
  *
  */

/*
 * Alternate function AF6
 */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF6_EVENTOUT      ((uint8_t)0x06U)  /* EVENTOUT Alternate Function mapping  */
/**
  *
  */

/*
 * Alternate function AF7
 */
#define GPIO_AF7_COMP1         ((uint8_t)0x07U)  /* COMP1 Alternate Function mapping     */
#define GPIO_AF7_COMP2         ((uint8_t)0x07U)  /* COMP2 Alternate Function mapping     */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */
/**
 * @brief  IS_GPIO_AF macro definition
 */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x06)

/**
  * @}
  */

#endif /* STM32L010x6 */

/*----------------------------------------------------------------------------*/
/*------------------------- STM32L010x4 --------------------------------------*/
/*----------------------------------------------------------------------------*/
#if defined (STM32L010x4)
/* The table below gives an overview of the different alternate functions per port.
 * For more details refer yourself to the product data sheet.
 *
 */
/*      |   AF0     |   AF1      |   AF2      |     AF3     |   AF4       |   AF5     |   AF6      |
 *_______________________________________________________________________ _________________________|
 * PA0  | USART2_RX | LPTIM1_IN1 | TIM2_CH1   |             | USART2_CTS  | TIM2_ETR  | LPUART1_RX |
 * PA1  | EVENTOUT  | LPTIM1_IN2 | TIM2_CH2   | I2C1_SMBA   | USART2_RTS  | TIM21_ETR | LPUART1_TX |
 * PA2  | TIM21_CH1 |            | TIM2_CH3   |             | USART2_TX   |           | LPUART1_TX |
 * PA3  | TIM21_CH2 |            | TIM2_CH4   |             | USART2_RX   |           | LPUART1_RX |
 * PA4  | SPI1_NSS  | LPTIM1_IN1 | LPTIM1_ETR | I2C1_SCL    | USART2_CK   | TIM2_ETR  | LPUART1_TX |
 * PA5  | SPI1_SCK  | LPTIM1_IN2 | TIM2_ETR   |             |             | TIM2_CH1  |            |
 * PA6  | SPI1_MISO | LPTIM1_ETR |            | LPUART1_CTS |             | EVENTOUT  |            |
 * PA7  | SPI1_MOSI | LPTIM1_OUT |            | USART2_CTS  | TIM21_ETR   | EVENTOUT  |            |
 * PA8  | MCO       |            | LPTIM1_IN1 | EVENTOUT    | USART2_CK   | TIM2_CH1  |            |
 * PA9  | MCO       | I2C1_SCL   | LPTIM1_OUT |             | USART2_TX   | TIM21_CH2 |            |
 * PA10 | TIM21_CH1 | I2C1_SDA   | RTC_REFIN  |             | USART2_RX   | TIM2_CH3  |            |
 * PA11 | SPI1_MISO | LPTIM1_OUT | EVENTOUT   |             | USART2_CTS  | TIM21_CH2 |            |
 * PA12 | SPI1_MOSI |            | EVENTOUT   |             | USART2_RTS  |           |            |
 * PA13 | SWDIO     | LPTIM1_ETR |            | I2C1_SDA    |             | SPI1_SCK  | LPUART1_RX |
 * PA14 | SWCLK     | LPTIM1_OUT |            | I2C1_SMBA   | USART2_TX   | SPI1_MISO | LPUART1_TX |
 * PA15 | SPI1_NSS  |            | TIM2_ETR   | EVENTOUT    | USART2_RX   | TIM2_CH1  |            |
 *_________________________________________________________________________________________________|
 * PB0  | EVENTOUT  | SPI1_MISO  | TIM2_CH2   |             | USART2_RTS  | TIM2_CH3  |            |
 * PB1  | USART2_CK | SPI1_MOSI  | LPTIM1_IN1 |             | LPUART1_RTS | TIM2_CH4  |            |
 * PB3  | SPI1_SCK  |            | TIM2_CH2   |             | EVENTOUT    |           |            |
 * PB4  | SPI1_MISO |            | EVENTOUT   |             |             |           |            |
 * PB5  | SPI1_MOSI |            | LPTIM1_IN1 | I2C1_SMBA   |             | TIM21_CH1 |            |
 * PB6  | USART2_TX | I2C1_SCL   | LPTIM1_ETR |             |             | TIM2_CH3  | LPUART1_TX |
 * PB7  | USART2_RX | I2C1_SDA   | LPTIM1_IN2 |             |             | TIM2_CH4  | LPUART1_RX |
 *_________________________________________________________________________________________________|
*/

/** @defgroup GPIOEx_Alternate_function_selection Alternate function selection
 * @{
 */

/*
 * Alternate function AF0
 */
#define GPIO_AF0_USART2        ((uint8_t)0x00U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF0_EVENTOUT      ((uint8_t)0x00U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF0_TIM21         ((uint8_t)0x00U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF0_SPI1          ((uint8_t)0x00U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF0_MCO           ((uint8_t)0x00U)  /* MCO Alternate Function mapping      */
#define GPIO_AF0_SWDIO         ((uint8_t)0x00U)  /* SWDIO Alternate Function mapping    */
#define GPIO_AF0_SWCLK         ((uint8_t)0x00U)  /* SWCLK Alternate Function mapping    */
/**
  *
  */

/*
 *  Alternate function AF1
 */
#define GPIO_AF1_SPI1          ((uint8_t)0x01U)  /* SPI1 Alternate Function mapping   */
#define GPIO_AF1_I2C1          ((uint8_t)0x01U)  /* I2C1 Alternate Function mapping   */
#define GPIO_AF1_LPTIM1        ((uint8_t)0x01U)  /* LPTIM1 Alternate Function mapping */
/**
  *
  */

/*  Alternate function AF2
 *
 */
#define GPIO_AF2_LPTIM1        ((uint8_t)0x02U)  /* LPTIM1 Alternate Function mapping     */
#define GPIO_AF2_TIM2          ((uint8_t)0x02U)  /* TIM2 Alternate Function mapping       */
#define GPIO_AF2_RTC           ((uint8_t)0x02U)  /* RTC Alternate Function mapping        */
#define GPIO_AF2_EVENTOUT      ((uint8_t)0x02U)  /* EVENTOUT Alternate Function mapping   */
/**
  *
  */

/*
 * Alternate function AF3
 */
#define GPIO_AF3_I2C1          ((uint8_t)0x03U)  /* I2C1 Alternate Function mapping     */
#define GPIO_AF3_EVENTOUT      ((uint8_t)0x03U)  /* EVENTOUT Alternate Function mapping */
#define GPIO_AF3_LPUART1       ((uint8_t)0x03U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF3_USART2        ((uint8_t)0x03U)  /* USART2 Alternate Function mapping   */
/**
  *
  */

/*
 * Alternate function AF4
 */
#define GPIO_AF4_USART2        ((uint8_t)0x04U)  /* USART2 Alternate Function mapping   */
#define GPIO_AF4_TIM21         ((uint8_t)0x04U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF4_LPUART1       ((uint8_t)0x04U)  /* LPUART1 Alternate Function mapping  */
#define GPIO_AF4_EVENTOUT      ((uint8_t)0x04U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF5
 */
#define GPIO_AF5_TIM2          ((uint8_t)0x05U)  /* TIM2 Alternate Function mapping     */
#define GPIO_AF5_TIM21         ((uint8_t)0x05U)  /* TIM21 Alternate Function mapping    */
#define GPIO_AF5_SPI1          ((uint8_t)0x05U)  /* SPI1 Alternate Function mapping     */
#define GPIO_AF5_EVENTOUT      ((uint8_t)0x05U)  /* EVENTOUT Alternate Function mapping */
/**
  *
  */

/*
 * Alternate function AF6
 */
#define GPIO_AF6_LPUART1       ((uint8_t)0x06U)  /* LPUART1 Alternate Function mapping  */
/**
  *
  */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GPIOEx_Private  GPIOEx Private
 * @{
 */
/**
 *  IS_GPIO_AF macro definition
 */

#define IS_GPIO_AF(AF)         ((AF) <= (uint8_t)0x06)

/**
  * @}
  */

#endif /* STM32L010x4*/

#if defined (STM32L083xx) || defined (STM32L082xx) || defined (STM32L081xx) || \
    defined (STM32L073xx) || defined (STM32L072xx) || defined (STM32L071xx) || \
    defined (STM32L010xB)

 /** @addtogroup GPIOEx_Exported_Constants
 * @{
 */
 /** @defgroup GPIOEx_Pin_Available Pin available
 * @{
 */
#define GPIOA_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOB_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOC_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOD_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOE_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOH_PIN_AVAILABLE  (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_9 | GPIO_PIN_10)
/**
  * @}
  */
/**
  * @}
  */

 /** @addtogroup GPIOEx_Private
 * @{
 */
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U :\
                                      ((__GPIOx__) == (GPIOD))? 3U :\
                                      ((__GPIOx__) == (GPIOE))? 4U :\
                                      ((__GPIOx__) == (GPIOH))? 5U : 6U)

#define IS_GPIO_PIN_AVAILABLE(__INSTANCE__,__PIN__)  \
           ((((__INSTANCE__) == GPIOA) && (((__PIN__) & (GPIOA_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOA_PIN_AVAILABLE)) == (GPIOA_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOB) && (((__PIN__) & (GPIOB_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOB_PIN_AVAILABLE)) == (GPIOB_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOC) && (((__PIN__) & (GPIOC_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOC_PIN_AVAILABLE)) == (GPIOC_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOD) && (((__PIN__) & (GPIOD_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOD_PIN_AVAILABLE)) == (GPIOD_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOE) && (((__PIN__) & (GPIOE_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOE_PIN_AVAILABLE)) == (GPIOE_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOH) && (((__PIN__) & (GPIOH_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOH_PIN_AVAILABLE)) == (GPIOH_PIN_AVAILABLE))))
/**
  * @}
  */
#elif defined (STM32L031xx) || defined (STM32L041xx) || defined (STM32L010x6)

/** @addtogroup GPIOEx_Exported_Constants
 * @{
 */
/** @defgroup GPIOEx_Pin_Available Pin available
 * @{
 */

#define GPIOA_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOB_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOC_PIN_AVAILABLE  (GPIO_PIN_0 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15)
#define GPIOH_PIN_AVAILABLE  (GPIO_PIN_0 | GPIO_PIN_1)
/**
  * @}
  */
/**
  * @}
  */

/** @addtogroup GPIOEx_Private
 * @{
 */
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U :\
                                      ((__GPIOx__) == (GPIOH))? 5U : 6U)


#define IS_GPIO_PIN_AVAILABLE(__INSTANCE__,__PIN__)  \
           ((((__INSTANCE__) == GPIOA) && (((__PIN__) & (GPIOA_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOA_PIN_AVAILABLE)) == (GPIOA_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOB) && (((__PIN__) & (GPIOB_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOB_PIN_AVAILABLE)) == (GPIOB_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOC) && (((__PIN__) & (GPIOC_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOC_PIN_AVAILABLE)) == (GPIOC_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOH) && (((__PIN__) & (GPIOH_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOH_PIN_AVAILABLE)) == (GPIOH_PIN_AVAILABLE))))

/**
  * @}
  */

#elif defined (STM32L011xx) || defined (STM32L021xx) || defined (STM32L010x4)

/** @addtogroup GPIOEx_Exported_Constants
 * @{
 */
/** @defgroup GPIOEx_Pin_Available Pin available
 * @{
 */

#define GPIOA_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOB_PIN_AVAILABLE  (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | \
                              GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 )
#define GPIOC_PIN_AVAILABLE  (GPIO_PIN_14 | GPIO_PIN_15)

/**
  * @}
  */
/**
  * @}
  */

/** @addtogroup GPIOEx_Private
 * @{
 */
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U : 6U)


#define IS_GPIO_PIN_AVAILABLE(__INSTANCE__,__PIN__)  \
           ((((__INSTANCE__) == GPIOA) && (((__PIN__) & (GPIOA_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOA_PIN_AVAILABLE)) == (GPIOA_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOB) && (((__PIN__) & (GPIOB_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOB_PIN_AVAILABLE)) == (GPIOB_PIN_AVAILABLE))) || \
            (((__INSTANCE__) == GPIOC) && (((__PIN__) & (GPIOC_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOC_PIN_AVAILABLE)) == (GPIOC_PIN_AVAILABLE))))
/**
  * @}
  */

#elif defined (STM32L063xx) || defined (STM32L062xx) || defined (STM32L061xx) || \
      defined (STM32L053xx) || defined (STM32L052xx) || defined (STM32L051xx) || \
      defined (STM32L010x8)

/** @addtogroup GPIOEx_Exported_Constants
 * @{
 */
/** @defgroup GPIOEx_Pin_Available Pin available
 * @{
 */
#define GPIOA_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOB_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOC_PIN_AVAILABLE  GPIO_PIN_All
#define GPIOD_PIN_AVAILABLE  GPIO_PIN_2
#define GPIOH_PIN_AVAILABLE  GPIO_PIN_0 | GPIO_PIN_1
/**
  * @}
  */
/**
  * @}
  */

/** @addtogroup GPIOEx_Private
 * @{
 */
#define GPIO_GET_INDEX(__GPIOx__)    (((__GPIOx__) == (GPIOA))? 0U :\
                                      ((__GPIOx__) == (GPIOB))? 1U :\
                                      ((__GPIOx__) == (GPIOC))? 2U :\
                                      ((__GPIOx__) == (GPIOD))? 3U :\
                                      ((__GPIOx__) == (GPIOH))? 5U : 6U)

#define IS_GPIO_PIN_AVAILABLE(__INSTANCE__,__PIN__)  \
                ((((__INSTANCE__) == GPIOA) && (((__PIN__) & (GPIOA_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOA_PIN_AVAILABLE)) == (GPIOA_PIN_AVAILABLE))) || \
                 (((__INSTANCE__) == GPIOB) && (((__PIN__) & (GPIOB_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOB_PIN_AVAILABLE)) == (GPIOB_PIN_AVAILABLE))) || \
                 (((__INSTANCE__) == GPIOC) && (((__PIN__) & (GPIOC_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOC_PIN_AVAILABLE)) == (GPIOC_PIN_AVAILABLE))) || \
                 (((__INSTANCE__) == GPIOD) && (((__PIN__) & (GPIOD_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOD_PIN_AVAILABLE)) == (GPIOD_PIN_AVAILABLE))) || \
                 (((__INSTANCE__) == GPIOH) && (((__PIN__) & (GPIOH_PIN_AVAILABLE)) != 0U) && (((__PIN__) | (GPIOH_PIN_AVAILABLE)) == (GPIOH_PIN_AVAILABLE))))
/**
  * @}
  */

#endif /* STM32L083xx || STM32L082xx || STM32L081xx || STM32L073xx || STM32L072xx || STM32L071xx*/


/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_GPIO_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

