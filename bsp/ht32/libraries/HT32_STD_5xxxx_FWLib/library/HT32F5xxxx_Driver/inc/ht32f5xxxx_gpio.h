/*********************************************************************************************************//**
 * @file    ht32f5xxxx_gpio.h
 * @version $Rev:: 7115         $
 * @date    $Date:: 2023-08-11 #$
 * @brief   The header file of the GPIO and AFIO library.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F5XXXX_GPIO_H
#define __HT32F5XXXX_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32.h"

/** @addtogroup HT32F5xxxx_Peripheral_Driver HT32F5xxxx Peripheral Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */


/* Settings ------------------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Settings GPIO settings
  * @{
  */
#ifndef AUTO_CK_CONTROL
#define AUTO_CK_CONTROL      (0)
#endif
/**
  * @}
  */

/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Types GPIO exported types
  * @{
  */

/**
 * @brief  Enumeration of GPIO pull resistor.
 */
typedef enum
{
  GPIO_PR_UP = 0,        /*!< weak pull-up resistor                                                         */
  GPIO_PR_DOWN,          /*!< weak pull-down resistor                                                       */
  GPIO_PR_DISABLE,       /*!< Tri-state                                                                     */
  #if (LIBCFG_GPIO_PR_STRONG_UP)
  GPIO_PR_STRONG_UP,     /*!< strong pull-up resistor                                                       */
  GPIO_PR_STRONGEST_UP   /*!< strongest pull-up resistor                                                    */
  #endif
} GPIO_PR_Enum;
/**
 * @brief  Enumeration of GPIO output drive current.
 */
typedef enum
{
  GPIO_DV_4MA = 0,   /*!<  4mA source/sink current                                                          */
  GPIO_DV_8MA,       /*!<  8mA source/sink current                                                          */
  GPIO_DV_12MA,      /*!< 12mA source/sink current                                                          */
  GPIO_DV_16MA       /*!< 16mA source/sink current                                                          */
} GPIO_DV_Enum;
/**
 * @brief  Enumeration of GPIO direction.
 */
typedef enum
{
  GPIO_DIR_IN = 0,    /*!< input mode                                                                       */
  GPIO_DIR_OUT        /*!< output mode                                                                      */
} GPIO_DIR_Enum;
/**
 * @brief  Enumeration of AFIO for EXTI channel.
 */
typedef enum
{
  AFIO_EXTI_CH_0 = 0,     /*!< GPIO pin 0                                                                   */
  AFIO_EXTI_CH_1,         /*!< GPIO pin 1                                                                   */
  AFIO_EXTI_CH_2,         /*!< GPIO pin 2                                                                   */
  AFIO_EXTI_CH_3,         /*!< GPIO pin 3                                                                   */
  AFIO_EXTI_CH_4,         /*!< GPIO pin 4                                                                   */
  AFIO_EXTI_CH_5,         /*!< GPIO pin 5                                                                   */
  AFIO_EXTI_CH_6,         /*!< GPIO pin 6                                                                   */
  AFIO_EXTI_CH_7,         /*!< GPIO pin 7                                                                   */
  AFIO_EXTI_CH_8,         /*!< GPIO pin 8                                                                   */
  AFIO_EXTI_CH_9,         /*!< GPIO pin 9                                                                   */
  AFIO_EXTI_CH_10,        /*!< GPIO pin 10                                                                  */
  AFIO_EXTI_CH_11,        /*!< GPIO pin 11                                                                  */
  AFIO_EXTI_CH_12,        /*!< GPIO pin 12                                                                  */
  AFIO_EXTI_CH_13,        /*!< GPIO pin 13                                                                  */
  AFIO_EXTI_CH_14,        /*!< GPIO pin 14                                                                  */
  AFIO_EXTI_CH_15         /*!< GPIO pin 15                                                                  */
} AFIO_EXTI_CH_Enum;
/**
 * @brief Enumeration of AFIO_MODE.
 */
typedef enum
{
 AFIO_MODE_DEFAULT = 0,   /*!< Default AFIO mode                                                            */
 AFIO_MODE_1,             /*!< AFIO mode 1                                                                  */
 AFIO_MODE_2,             /*!< AFIO mode 2                                                                  */
 AFIO_MODE_3,             /*!< AFIO mode 3                                                                  */
 AFIO_MODE_4,             /*!< AFIO mode 4                                                                  */
 AFIO_MODE_5,             /*!< AFIO mode 5                                                                  */
 AFIO_MODE_6,             /*!< AFIO mode 6                                                                  */
 AFIO_MODE_7,             /*!< AFIO mode 7                                                                  */
 AFIO_MODE_8,             /*!< AFIO mode 8                                                                  */
 AFIO_MODE_9,             /*!< AFIO mode 9                                                                  */
 AFIO_MODE_10,            /*!< AFIO mode 10                                                                 */
 AFIO_MODE_11,            /*!< AFIO mode 11                                                                 */
 AFIO_MODE_12,            /*!< AFIO mode 12                                                                 */
 AFIO_MODE_13,            /*!< AFIO mode 13                                                                 */
 AFIO_MODE_14,            /*!< AFIO mode 14                                                                 */
 AFIO_MODE_15             /*!< AFIO mode 15                                                                 */
} AFIO_MODE_Enum;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Constants GPIO exported constants
  * @{
  */

/* Definitions of AFIO_FUN                                                                                  */
#define AFIO_FUN_DEFAULT    AFIO_MODE_DEFAULT  /*!< Default AFIO mode                                       */
#define AFIO_FUN_GPIO       AFIO_MODE_1        /*!< AFIO mode GPIO                                          */
#if (LIBCFG_AFIO_SYSTEM_MODE1)
#define AFIO_FUN_SYSTEM     AFIO_MODE_1        /*!< AFIO mode System                                        */
#else
#define AFIO_FUN_SYSTEM     AFIO_MODE_15       /*!< AFIO mode System                                        */
#endif
#if (LIBCFG_AFIO_DAC_MODE3)
#define AFIO_FUN_DAC0       AFIO_MODE_3        /*!< AFIO mode DAC0                                          */
#define AFIO_FUN_DAC1       AFIO_MODE_3        /*!< AFIO mode DAC1                                          */
#else
#define AFIO_FUN_DAC0       AFIO_MODE_2        /*!< AFIO mode DAC0                                          */
#endif
#define AFIO_FUN_ADC0       AFIO_MODE_2        /*!< AFIO mode ADC0                                          */
#define AFIO_FUN_ADC1       AFIO_MODE_3        /*!< AFIO mode ADC1                                          */
#if (LIBCFG_AFIO_LEDC_MODE3)
#define AFIO_FUN_LEDC       AFIO_MODE_3        /*!< AFIO mode LEDC                                          */
#else
#define AFIO_FUN_LEDC       AFIO_MODE_14       /*!< AFIO mode LEDC                                          */
#endif
#define AFIO_FUN_CMP        AFIO_MODE_3        /*!< AFIO mode CMP                                           */
#define AFIO_FUN_MCTM_GPTM  AFIO_MODE_4        /*!< AFIO mode MCTM/GPTM                                     */
#if (LIBCFG_AFIO_SCTM_MODE4)
#define AFIO_FUN_SCTM       AFIO_MODE_4        /*!< AFIO mode SCTM                                          */
#elif (LIBCFG_AFIO_SCTM_MODE9)
#define AFIO_FUN_SCTM       AFIO_MODE_9        /*!< AFIO mode SCTM                                          */
#else
#define AFIO_FUN_SCTM       AFIO_MODE_13       /*!< AFIO mode SCTM                                          */
#endif
#if (LIBCFG_AFIO_PWM_MODE4)
#define AFIO_FUN_PWM        AFIO_MODE_4        /*!< AFIO mode PWM                                           */
#else
#define AFIO_FUN_PWM        AFIO_MODE_13       /*!< AFIO mode PWM                                           */
#endif
#define AFIO_FUN_SPI        AFIO_MODE_5        /*!< AFIO mode SPI                                           */
#define AFIO_FUN_USART_UART AFIO_MODE_6        /*!< AFIO mode USART/UART                                    */
#define AFIO_FUN_I2C        AFIO_MODE_7        /*!< AFIO mode I2C                                           */
#define AFIO_FUN_SCI        AFIO_MODE_8        /*!< AFIO mode SCI                                           */
#define AFIO_FUN_CMP_OPA    AFIO_MODE_8        /*!< AFIO mode CMP/OPA                                       */
#define AFIO_FUN_EBI        AFIO_MODE_9        /*!< AFIO mode EBI                                           */
#define AFIO_FUN_I2S        AFIO_MODE_10       /*!< AFIO mode I2S                                           */
#define AFIO_FUN_CAN        AFIO_MODE_12       /*!< AFIO mode CAN                                           */
#define AFIO_FUN_TEKY       AFIO_MODE_12       /*!< AFIO mode TKEY                                          */
#define AFIO_FUN_LCD        AFIO_MODE_14       /*!< AFIO mode LCD                                           */
#define AFIO_FUN_SLED       AFIO_MODE_14       /*!< AFIO mode SLED                                          */

/* Definitions of AFIO_FUN alias                                                                            */
#define AFIO_FUN_MCTM0      AFIO_FUN_MCTM_GPTM

#define AFIO_FUN_GPTM0      AFIO_FUN_MCTM_GPTM
#define AFIO_FUN_GPTM1      AFIO_FUN_MCTM_GPTM
#define AFIO_FUN_GPTM2      AFIO_FUN_MCTM_GPTM
#define AFIO_FUN_GPTM3      AFIO_FUN_MCTM_GPTM

#define AFIO_FUN_PWM0       AFIO_FUN_PWM
#define AFIO_FUN_PWM1       AFIO_FUN_PWM
#define AFIO_FUN_PWM2       AFIO_FUN_PWM
#define AFIO_FUN_PWM3       AFIO_FUN_PWM

#define AFIO_FUN_SCTM0      AFIO_FUN_SCTM
#define AFIO_FUN_SCTM1      AFIO_FUN_SCTM
#define AFIO_FUN_SCTM2      AFIO_FUN_SCTM
#define AFIO_FUN_SCTM3      AFIO_FUN_SCTM

#define AFIO_FUN_ADC        AFIO_FUN_ADC0

/* Definitions of GPIO_Px                                                                                   */
#define GPIO_PORT_NUM   (6)
#define GPIO_PIN_NUM    (16)
#define GPIO_PA         (0)
#define GPIO_PB         (1)
#if (LIBCFG_GPIOC)
#define GPIO_PC         (2)
#endif
#if (LIBCFG_GPIOD)
#define GPIO_PD         (3)
#endif
#if (LIBCFG_GPIOE)
#define GPIO_PE         (4)
#endif
#if (LIBCFG_GPIOF)
#define GPIO_PF         (5)
#endif

/* Definitions of GPIO port source for EXTI channel                                                         */
#define AFIO_ESS_PA GPIO_PA  /*!< EXTI channel x source come from GPIO Port A                               */
#define AFIO_ESS_PB GPIO_PB  /*!< EXTI channel x source come from GPIO Port B                               */
#if (LIBCFG_GPIOC)
#define AFIO_ESS_PC GPIO_PC  /*!< EXTI channel x source come from GPIO Port C                               */
#endif
#if (LIBCFG_GPIOD)
#define AFIO_ESS_PD GPIO_PD  /*!< EXTI channel x source come from GPIO Port D                               */
#endif
#if (LIBCFG_GPIOE)
#define AFIO_ESS_PE GPIO_PE  /*!< EXTI channel x source come from GPIO Port E                               */
#endif
#if (LIBCFG_GPIOF)
#define AFIO_ESS_PF GPIO_PF  /*!< EXTI channel x source come from GPIO Port F                               */
#endif

/* Definitions of GPIO_PIN                                                                                  */
#define GPIO_PIN_0    0x0001   /*!< GPIO pin 0 selected                                                     */
#define GPIO_PIN_1    0x0002   /*!< GPIO pin 1 selected                                                     */
#define GPIO_PIN_2    0x0004   /*!< GPIO pin 2 selected                                                     */
#define GPIO_PIN_3    0x0008   /*!< GPIO pin 3 selected                                                     */
#define GPIO_PIN_4    0x0010   /*!< GPIO pin 4 selected                                                     */
#define GPIO_PIN_5    0x0020   /*!< GPIO pin 5 selected                                                     */
#define GPIO_PIN_6    0x0040   /*!< GPIO pin 6 selected                                                     */
#define GPIO_PIN_7    0x0080   /*!< GPIO pin 7 selected                                                     */
#define GPIO_PIN_8    0x0100   /*!< GPIO pin 8 selected                                                     */
#define GPIO_PIN_9    0x0200   /*!< GPIO pin 9 selected                                                     */
#define GPIO_PIN_10   0x0400   /*!< GPIO pin 10 selected                                                    */
#define GPIO_PIN_11   0x0800   /*!< GPIO pin 11 selected                                                    */
#define GPIO_PIN_12   0x1000   /*!< GPIO pin 12 selected                                                    */
#define GPIO_PIN_13   0x2000   /*!< GPIO pin 13 selected                                                    */
#define GPIO_PIN_14   0x4000   /*!< GPIO pin 14 selected                                                    */
#define GPIO_PIN_15   0x8000   /*!< GPIO pin 15 selected                                                    */
#define GPIO_PIN_ALL  0xFFFF   /*!< GPIO all pins selected                                                  */

/* Definitions of AFIO_PIN                                                                                  */
#define AFIO_PIN_0    0x0001   /*!< AFIO pin 0 selected                                                     */
#define AFIO_PIN_1    0x0002   /*!< AFIO pin 1 selected                                                     */
#define AFIO_PIN_2    0x0004   /*!< AFIO pin 2 selected                                                     */
#define AFIO_PIN_3    0x0008   /*!< AFIO pin 3 selected                                                     */
#define AFIO_PIN_4    0x0010   /*!< AFIO pin 4 selected                                                     */
#define AFIO_PIN_5    0x0020   /*!< AFIO pin 5 selected                                                     */
#define AFIO_PIN_6    0x0040   /*!< AFIO pin 6 selected                                                     */
#define AFIO_PIN_7    0x0080   /*!< AFIO pin 7 selected                                                     */
#define AFIO_PIN_8    0x0100   /*!< AFIO pin 8 selected                                                     */
#define AFIO_PIN_9    0x0200   /*!< AFIO pin 9 selected                                                     */
#define AFIO_PIN_10   0x0400   /*!< AFIO pin 10 selected                                                    */
#define AFIO_PIN_11   0x0800   /*!< AFIO pin 11 selected                                                    */
#define AFIO_PIN_12   0x1000   /*!< AFIO pin 12 selected                                                    */
#define AFIO_PIN_13   0x2000   /*!< AFIO pin 13 selected                                                    */
#define AFIO_PIN_14   0x4000   /*!< AFIO pin 14 selected                                                    */
#define AFIO_PIN_15   0x8000   /*!< AFIO pin 15 selected                                                    */
#define AFIO_PIN_ALL  0xFFFF   /*!< All AFIO pins selected                                                  */

/* Definitions of GPIO_PIN_NUM                                                                              */
#define GPIO_PIN_NUM_0    0x00   /*!< GPIO pin number 0 selected                                            */
#define GPIO_PIN_NUM_1    0x01   /*!< GPIO pin number 1 selected                                            */
#define GPIO_PIN_NUM_2    0x02   /*!< GPIO pin number 2 selected                                            */
#define GPIO_PIN_NUM_3    0x03   /*!< GPIO pin number 3 selected                                            */
#define GPIO_PIN_NUM_4    0x04   /*!< GPIO pin number 4 selected                                            */
#define GPIO_PIN_NUM_5    0x05   /*!< GPIO pin number 5 selected                                            */
#define GPIO_PIN_NUM_6    0x06   /*!< GPIO pin number 6 selected                                            */
#define GPIO_PIN_NUM_7    0x07   /*!< GPIO pin number 7 selected                                            */
#define GPIO_PIN_NUM_8    0x08   /*!< GPIO pin number 8 selected                                            */
#define GPIO_PIN_NUM_9    0x09   /*!< GPIO pin number 9 selected                                            */
#define GPIO_PIN_NUM_10   0x0A   /*!< GPIO pin number 10 selected                                           */
#define GPIO_PIN_NUM_11   0x0B   /*!< GPIO pin number 11 selected                                           */
#define GPIO_PIN_NUM_12   0x0C   /*!< GPIO pin number 12 selected                                           */
#define GPIO_PIN_NUM_13   0x0D   /*!< GPIO pin number 13 selected                                           */
#define GPIO_PIN_NUM_14   0x0E   /*!< GPIO pin number 14 selected                                           */
#define GPIO_PIN_NUM_15   0x0F   /*!< GPIO pin number 15 selected                                           */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Macro GPIO exported macro
  * @{
  */
/* check parameter of the GPIOx                                                                             */
#define IS_GPIO(x)           (IS_GPIO1(x) || IS_GPIO2(x) || IS_GPIO3(x) || IS_GPIO4(x) || IS_GPIO5(x))

#define IS_GPIO1(x)          ((x == HT_GPIOA) || (x == HT_GPIOB) )

#if (LIBCFG_GPIOC)
#define IS_GPIO2(x)          (x == HT_GPIOC)
#else
#define IS_GPIO2(x)          (0)
#endif
#if (LIBCFG_GPIOD)
#define IS_GPIO3(x)          (x == HT_GPIOD)
#else
#define IS_GPIO3(x)          (0)
#endif
#if (LIBCFG_GPIOE)
#define IS_GPIO4(x)          (x == HT_GPIOE)
#else
#define IS_GPIO4(x)          (0)
  #endif
#if (LIBCFG_GPIOF)
#define IS_GPIO5(x)          (x == HT_GPIOF)
#else
#define IS_GPIO5(x)          (0)
#endif

/* check parameter of the GPIO_Px                                                                           */
#define IS_GPIO_PORT(x)           (IS_GPIO_PORT1(x) || IS_GPIO_PORT2(x) || IS_GPIO_PORT3(x) || IS_GPIO_PORT4(x) || IS_GPIO_PORT5(x))

#define IS_GPIO_PORT1(x)          ((x == GPIO_PA) || (x == GPIO_PB))

#if (LIBCFG_GPIOC)
#define IS_GPIO_PORT2(x)          (x == GPIO_PC)
#else
#define IS_GPIO_PORT2(x)          (0)
#endif
#if (LIBCFG_GPIOD)
#define IS_GPIO_PORT3(x)          (x == GPIO_PD)
#else
#define IS_GPIO_PORT3(x)          (0)
#endif
#if (LIBCFG_GPIOE)
#define IS_GPIO_PORT4(x)          (x == GPIO_PE)
#else
#define IS_GPIO_PORT4(x)          (0)
#endif
#if (LIBCFG_GPIOF)
#define IS_GPIO_PORT5(x)          (x == GPIO_PF)
#else
#define IS_GPIO_PORT5(x)          (0)
#endif

/* check parameter of the GPIO_PIN_NUM                                                                      */
#define IS_GPIO_PIN_NUM(x)        (x < 16)


#define IS_GPIO_PR_UP(x)           (x == GPIO_PR_UP)
#define IS_GPIO_PR_DOWN(x)         (x == GPIO_PR_DOWN)
#define IS_GPIO_PR_DISABLE(x)      (x == GPIO_PR_DISABLE)

#if (LIBCFG_GPIO_PR_STRONG_UP)
#define IS_GPIO_PR_STRONG_UP(x)    (x == GPIO_PR_STRONG_UP)
#define IS_GPIO_PR_STRONGEST_UP(x) (x == GPIO_PR_STRONGEST_UP)
#else
#define IS_GPIO_PR_STRONG_UP(x)    (0)
#define IS_GPIO_PR_STRONGEST_UP(x) (0)
#endif

/* check parameter of the GPIOx pull resistor                                                               */
#define IS_GPIO_PR(x)        (IS_GPIO_PR_UP(x)        || \
                              IS_GPIO_PR_DOWN(x)      || \
                              IS_GPIO_PR_DISABLE(x)   || \
                              IS_GPIO_PR_STRONG_UP(x) || \
                              IS_GPIO_PR_STRONGEST_UP(x))

/* check parameter of the GPIOx driving current                                                             */
#define IS_GPIO_DV(x)        (((x) == GPIO_DV_4MA) || ((x) == GPIO_DV_8MA) || ((x) == GPIO_DV_12MA) || ((x) == GPIO_DV_16MA) )

/* check parameter of the GPIOx input/output direction                                                      */
#define IS_GPIO_DIR(x)       (((x) == GPIO_DIR_IN) || ((x) == GPIO_DIR_OUT))

/* check parameter of the EXTI source port                                                                  */
#define IS_AFIO_ESS(x)       (IS_AFIO_ESS1(x) || IS_AFIO_ESS2(x) || IS_AFIO_ESS3(x) || IS_AFIO_ESS4(x) || IS_AFIO_ESS5(x))

#define IS_AFIO_ESS1(x)      ((x == AFIO_ESS_PA) || (x == AFIO_ESS_PB))
#if (LIBCFG_GPIOC)
#define IS_AFIO_ESS2(x)      (x == AFIO_ESS_PC)
#else
#define IS_AFIO_ESS2(x)      (0)
#endif
#if (LIBCFG_GPIOD)
#define IS_AFIO_ESS3(x)      (x == AFIO_ESS_PD)
#else
#define IS_AFIO_ESS3(x)      (0)
#endif
#if (LIBCFG_GPIOE)
#define IS_AFIO_ESS4(x)      (x == AFIO_ESS_PE)
#else
#define IS_AFIO_ESS4(x)      (0)
#endif
#if (LIBCFG_GPIOF)
#define IS_AFIO_ESS5(x)      (x == AFIO_ESS_PF)
#else
#define IS_AFIO_ESS5(x)      (0)
#endif

/* check parameter of the EXTI channel                                                                      */
#if (LIBCFG_EXTI_8CH)
#define IS_AFIO_EXTI_CH(x)   ((x == AFIO_EXTI_CH_0)  || (x == AFIO_EXTI_CH_1)  || \
                              (x == AFIO_EXTI_CH_2)  || (x == AFIO_EXTI_CH_3)  || \
                              (x == AFIO_EXTI_CH_4)  || (x == AFIO_EXTI_CH_5)  || \
                              (x == AFIO_EXTI_CH_6)  || (x == AFIO_EXTI_CH_7))
#else
#define IS_AFIO_EXTI_CH(x)   ((x == AFIO_EXTI_CH_0)  || (x == AFIO_EXTI_CH_1)  || \
                              (x == AFIO_EXTI_CH_2)  || (x == AFIO_EXTI_CH_3)  || \
                              (x == AFIO_EXTI_CH_4)  || (x == AFIO_EXTI_CH_5)  || \
                              (x == AFIO_EXTI_CH_6)  || (x == AFIO_EXTI_CH_7)  || \
                              (x == AFIO_EXTI_CH_8)  || (x == AFIO_EXTI_CH_9)  || \
                              (x == AFIO_EXTI_CH_10) || (x == AFIO_EXTI_CH_11) || \
                              (x == AFIO_EXTI_CH_12) || (x == AFIO_EXTI_CH_13) || \
                              (x == AFIO_EXTI_CH_14) || (x == AFIO_EXTI_CH_15))
#endif

/* check parameter of the AFIO mode                                                                         */
#if (LIBCFG_AFIO_MODE_0_7)
#define IS_AFIO_MODE(x)      ((x == AFIO_MODE_DEFAULT) || (x == AFIO_MODE_1)  || \
                              (x == AFIO_MODE_2)       || (x == AFIO_MODE_3)  || \
                              (x == AFIO_MODE_4)       || (x == AFIO_MODE_5)  || \
                              (x == AFIO_MODE_6)       || (x == AFIO_MODE_7))
#else
#define IS_AFIO_MODE(x)      ((x == AFIO_MODE_DEFAULT) || (x == AFIO_MODE_1)  || \
                              (x == AFIO_MODE_2)       || (x == AFIO_MODE_3)  || \
                              (x == AFIO_MODE_4)       || (x == AFIO_MODE_5)  || \
                              (x == AFIO_MODE_6)       || (x == AFIO_MODE_7)  || \
                              (x == AFIO_MODE_8)       || (x == AFIO_MODE_9)  || \
                              (x == AFIO_MODE_10)      || (x == AFIO_MODE_11) || \
                              (x == AFIO_MODE_12)      || (x == AFIO_MODE_13) || \
                              (x == AFIO_MODE_14)      || (x == AFIO_MODE_15))
#endif
/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Functions GPIO exported functions
  * @{
  */

/* Prototype of related GPIO function                                                                       */
void GPIO_DeInit(HT_GPIO_TypeDef* HT_GPIOx);
void GPIO_DirectionConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, GPIO_DIR_Enum GPIO_DIR_INorOUT);
void GPIO_PullResistorConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, GPIO_PR_Enum GPIO_PR_x);
void GPIO_InputConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, ControlStatus Cmd);
void GPIO_DriveConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, GPIO_DV_Enum GPIO_DV_nMA);
void GPIO_OpenDrainConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, ControlStatus Cmd);
#if LIBCFG_GPIO_SINK_CURRENT_ENHANCED
void GPIO_SinkConfig(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_n, ControlStatus Cmd);
#endif
FlagStatus GPIO_ReadInBit(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_n);
FlagStatus GPIO_ReadOutBit(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_n);
u16 GPIO_ReadInData(HT_GPIO_TypeDef* HT_GPIOx);
u16 GPIO_ReadOutData(HT_GPIO_TypeDef* HT_GPIOx);
void GPIO_SetOutBits(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP);
void GPIO_ClearOutBits(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP);
void GPIO_WriteOutBits(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP, FlagStatus Status);
void GPIO_WriteOutData(HT_GPIO_TypeDef* HT_GPIOx, u16 Data);
void GPIO_PinLock(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_nBITMAP);
bool GPIO_IsPortLocked(HT_GPIO_TypeDef* HT_GPIOx);
bool GPIO_IsPinLocked(HT_GPIO_TypeDef* HT_GPIOx, u16 GPIO_PIN_n);
#if (LIBCFG_GPIO_DISABLE_DEBUG_PORT)
void GPIO_DisableDebugPort(void);
#endif
u32 GPIO_GetID(HT_GPIO_TypeDef* HT_GPIOx);

/* Prototype of related AFIO function                                                                       */
void AFIO_DeInit(void);
void AFIO_GPxConfig(u32 GPIO_Px, u32 AFIO_PIN_n, AFIO_MODE_Enum AFIO_MODE_n);
void AFIO_EXTISourceConfig(u32 GPIO_PIN_NUM_n, u32 GPIO_Px);
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
