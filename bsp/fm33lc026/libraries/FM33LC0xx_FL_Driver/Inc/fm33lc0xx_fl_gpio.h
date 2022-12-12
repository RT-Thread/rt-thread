/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_gpio.h
  * @author  FMSH Application Team
  * @brief   Head file of GPIO FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LC0XX_FL_GPIO_H
#define __FM33LC0XX_FL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup GPIO GPIO
  * @brief GPIO FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup GPIO_FL_ES_INIT GPIO Exported Init structures
  * @{
  */
/**
  * @brief FL GPIO Init Sturcture definition
  */
typedef struct
{
    /*! PIN */
    uint32_t pin;

    /*! 功能模式 */
    uint32_t mode;

    /*! 输出类型 */
    uint32_t outputType;

    /*! 上拉使能 */
    uint32_t pull;

    /*! 数字功能重定向 */
    uint32_t remapPin;

} FL_GPIO_InitTypeDef;

/**
  * @brief FL GPIO WKUP Init Sturcture definition
  */
typedef struct
{
    /*! 触发边沿 */
    uint32_t polarity;

} FL_WKUP_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup GPIO_FL_Exported_Constants GPIO Exported Constants
  * @{
  */

#define    GPIO_FCR_Pos                                           (0U)
#define    GPIO_FCR_Msk                                           (0x3U << GPIO_FCR_Pos)
#define    GPIO_FCR                                               GPIO_FCR_Msk

#define    GPIO_EXTIEDS_Pos                                       (0U)
#define    GPIO_EXTIEDS_Msk                                       (0x3U << GPIO_EXTIEDS_Pos)
#define    GPIO_EXTIEDS                                           GPIO_EXTIEDS_Msk

#define    GPIO_FOUTSEL_FOUT0_Pos                                 (0U)
#define    GPIO_FOUTSEL_FOUT0_Msk                                 (0xfU << GPIO_FOUTSEL_FOUT0_Pos)
#define    GPIO_FOUTSEL_FOUT0                                     GPIO_FOUTSEL_FOUT0_Msk

#define    GPIO_FOUTSEL_FOUT1_Pos                                 (4U)
#define    GPIO_FOUTSEL_FOUT1_Msk                                 (0xfU << GPIO_FOUTSEL_FOUT1_Pos)
#define    GPIO_FOUTSEL_FOUT1                                     GPIO_FOUTSEL_FOUT1_Msk

#define    GPIO_EXTISEL_EXTI0_Pos                                 (0U)
#define    GPIO_EXTISEL_EXTI0_Msk                                 (0x3U << GPIO_EXTISEL_EXTI0_Pos)
#define    GPIO_EXTISEL_EXTI0                                     GPIO_EXTISEL_EXTI0_Msk

#define    GPIO_EXTISEL_EXTI1_Pos                                 (2U)
#define    GPIO_EXTISEL_EXTI1_Msk                                 (0x3U << GPIO_EXTISEL_EXTI1_Pos)
#define    GPIO_EXTISEL_EXTI1                                     GPIO_EXTISEL_EXTI1_Msk

#define    GPIO_EXTISEL_EXTI2_Pos                                 (4U)
#define    GPIO_EXTISEL_EXTI2_Msk                                 (0x3U << GPIO_EXTISEL_EXTI2_Pos)
#define    GPIO_EXTISEL_EXTI2                                     GPIO_EXTISEL_EXTI2_Msk

#define    GPIO_EXTISEL_EXTI3_Pos                                 (6U)
#define    GPIO_EXTISEL_EXTI3_Msk                                 (0x3U << GPIO_EXTISEL_EXTI3_Pos)
#define    GPIO_EXTISEL_EXTI3                                     GPIO_EXTISEL_EXTI3_Msk

#define    GPIO_EXTISEL_EXTI4_Pos                                 (8U)
#define    GPIO_EXTISEL_EXTI4_Msk                                 (0x3U << GPIO_EXTISEL_EXTI4_Pos)
#define    GPIO_EXTISEL_EXTI4                                     GPIO_EXTISEL_EXTI4_Msk

#define    GPIO_EXTISEL_EXTI5_Pos                                 (10U)
#define    GPIO_EXTISEL_EXTI5_Msk                                 (0x3U << GPIO_EXTISEL_EXTI5_Pos)
#define    GPIO_EXTISEL_EXTI5                                     GPIO_EXTISEL_EXTI5_Msk

#define    GPIO_EXTISEL_EXTI6_Pos                                 (12U)
#define    GPIO_EXTISEL_EXTI6_Msk                                 (0x3U << GPIO_EXTISEL_EXTI6_Pos)
#define    GPIO_EXTISEL_EXTI6                                     GPIO_EXTISEL_EXTI6_Msk

#define    GPIO_EXTISEL_EXTI7_Pos                                 (14U)
#define    GPIO_EXTISEL_EXTI7_Msk                                 (0x3U << GPIO_EXTISEL_EXTI7_Pos)
#define    GPIO_EXTISEL_EXTI7                                     GPIO_EXTISEL_EXTI7_Msk

#define    GPIO_EXTISEL_EXTI8_Pos                                 (16U)
#define    GPIO_EXTISEL_EXTI8_Msk                                 (0x3U << GPIO_EXTISEL_EXTI8_Pos)
#define    GPIO_EXTISEL_EXTI8                                     GPIO_EXTISEL_EXTI8_Msk

#define    GPIO_EXTISEL_EXTI9_Pos                                 (18U)
#define    GPIO_EXTISEL_EXTI9_Msk                                 (0x3U << GPIO_EXTISEL_EXTI9_Pos)
#define    GPIO_EXTISEL_EXTI9                                     GPIO_EXTISEL_EXTI9_Msk

#define    GPIO_EXTISEL_EXTI10_Pos                                (20U)
#define    GPIO_EXTISEL_EXTI10_Msk                                (0x3U << GPIO_EXTISEL_EXTI10_Pos)
#define    GPIO_EXTISEL_EXTI10                                    GPIO_EXTISEL_EXTI10_Msk

#define    GPIO_EXTISEL_EXTI11_Pos                                (22U)
#define    GPIO_EXTISEL_EXTI11_Msk                                (0x3U << GPIO_EXTISEL_EXTI11_Pos)
#define    GPIO_EXTISEL_EXTI11                                    GPIO_EXTISEL_EXTI11_Msk

#define    GPIO_EXTISEL_EXTI12_Pos                                (24U)
#define    GPIO_EXTISEL_EXTI12_Msk                                (0x3U << GPIO_EXTISEL_EXTI12_Pos)
#define    GPIO_EXTISEL_EXTI12                                    GPIO_EXTISEL_EXTI12_Msk

#define    GPIO_EXTISEL_EXTI13_Pos                                (26U)
#define    GPIO_EXTISEL_EXTI13_Msk                                (0x3U << GPIO_EXTISEL_EXTI13_Pos)
#define    GPIO_EXTISEL_EXTI13                                    GPIO_EXTISEL_EXTI13_Msk

#define    GPIO_EXTISEL_EXTI14_Pos                                (28U)
#define    GPIO_EXTISEL_EXTI14_Msk                                (0x3U << GPIO_EXTISEL_EXTI14_Pos)
#define    GPIO_EXTISEL_EXTI14                                    GPIO_EXTISEL_EXTI14_Msk

#define    GPIO_PINWKEN_EN_Pos                                    (0U)
#define    GPIO_PINWKEN_EN_Msk                                    (0xffU << GPIO_PINWKEN_EN_Pos)
#define    GPIO_PINWKEN_EN                                        GPIO_PINWKEN_EN_Msk

#define    GPIO_PINWKEN_WKISEL_Pos                                (31U)
#define    GPIO_PINWKEN_WKISEL_Msk                                (0x1U << GPIO_PINWKEN_WKISEL_Pos)
#define    GPIO_PINWKEN_WKISEL                                    GPIO_PINWKEN_WKISEL_Msk

#define    GPIO_PINWKEN_SEL_Pos                                   (8U)
#define    GPIO_PINWKEN_SEL_Msk                                   (0x1U << GPIO_PINWKEN_SEL_Pos)
#define    GPIO_PINWKEN_SEL                                       GPIO_PINWKEN_SEL_Msk



#define    FL_GPIO_PIN_0                                          (0x1U << 0U)
#define    FL_GPIO_PIN_1                                          (0x1U << 1U)
#define    FL_GPIO_PIN_2                                          (0x1U << 2U)
#define    FL_GPIO_PIN_3                                          (0x1U << 3U)
#define    FL_GPIO_PIN_4                                          (0x1U << 4U)
#define    FL_GPIO_PIN_5                                          (0x1U << 5U)
#define    FL_GPIO_PIN_6                                          (0x1U << 6U)
#define    FL_GPIO_PIN_7                                          (0x1U << 7U)
#define    FL_GPIO_PIN_8                                          (0x1U << 8U)
#define    FL_GPIO_PIN_9                                          (0x1U << 9U)
#define    FL_GPIO_PIN_10                                         (0x1U << 10U)
#define    FL_GPIO_PIN_11                                         (0x1U << 11U)
#define    FL_GPIO_PIN_12                                         (0x1U << 12U)
#define    FL_GPIO_PIN_13                                         (0x1U << 13U)
#define    FL_GPIO_PIN_14                                         (0x1U << 14U)
#define    FL_GPIO_PIN_15                                         (0x1U << 15U)
#define    FL_GPIO_PIN_ALL                                        (0xffffU << 0U)
#define    FL_GPIO_PIN_ALL_EXCEPTSWD                              0xFE7FU
#define    FL_GPIO_EXTI_LINE_0                                    (0x1U << 0U)
#define    FL_GPIO_EXTI_LINE_1                                    (0x1U << 1U)
#define    FL_GPIO_EXTI_LINE_2                                    (0x1U << 2U)
#define    FL_GPIO_EXTI_LINE_3                                    (0x1U << 3U)
#define    FL_GPIO_EXTI_LINE_4                                    (0x1U << 4U)
#define    FL_GPIO_EXTI_LINE_5                                    (0x1U << 5U)
#define    FL_GPIO_EXTI_LINE_6                                    (0x1U << 6U)
#define    FL_GPIO_EXTI_LINE_7                                    (0x1U << 7U)
#define    FL_GPIO_EXTI_LINE_8                                    (0x1U << 8U)
#define    FL_GPIO_EXTI_LINE_9                                    (0x1U << 9U)
#define    FL_GPIO_EXTI_LINE_10                                   (0x1U << 10U)
#define    FL_GPIO_EXTI_LINE_11                                   (0x1U << 11U)
#define    FL_GPIO_EXTI_LINE_12                                   (0x1U << 12U)
#define    FL_GPIO_EXTI_LINE_13                                   (0x1U << 13U)
#define    FL_GPIO_EXTI_LINE_14                                   (0x1U << 14U)
#define    FL_GPIO_EXTI_LINE_15                                   (0x1U << 15U)
#define    FL_GPIO_EXTI_LINE_ALL                                  (0xffffU << 0U)
#define    FL_GPIO_EXTI_LINE_0_PA0                                (0x0U << 0U)
#define    FL_GPIO_EXTI_LINE_0_PA1                                (0x1U << 0U)
#define    FL_GPIO_EXTI_LINE_0_PA2                                (0x2U << 0U)
#define    FL_GPIO_EXTI_LINE_0_PA3                                (0x3U << 0U)
#define    FL_GPIO_EXTI_LINE_1_PA4                                (0x0U << 2U)
#define    FL_GPIO_EXTI_LINE_1_PA5                                (0x1U << 2U)
#define    FL_GPIO_EXTI_LINE_1_PA6                                (0x2U << 2U)
#define    FL_GPIO_EXTI_LINE_1_PA7                                (0x3U << 2U)
#define    FL_GPIO_EXTI_LINE_2_PA8                                (0x0U << 4U)
#define    FL_GPIO_EXTI_LINE_2_PA9                                (0x1U << 4U)
#define    FL_GPIO_EXTI_LINE_2_PA10                               (0x2U << 4U)
#define    FL_GPIO_EXTI_LINE_2_PA11                               (0x3U << 4U)
#define    FL_GPIO_EXTI_LINE_3_PA12                               (0x0U << 6U)
#define    FL_GPIO_EXTI_LINE_3_PA13                               (0x1U << 6U)
#define    FL_GPIO_EXTI_LINE_3_PA14                               (0x2U << 6U)
#define    FL_GPIO_EXTI_LINE_3_PA15                               (0x3U << 6U)
#define    FL_GPIO_EXTI_LINE_4_PB0                                (0x0U << 8U)
#define    FL_GPIO_EXTI_LINE_4_PB1                                (0x1U << 8U)
#define    FL_GPIO_EXTI_LINE_4_PB2                                (0x2U << 8U)
#define    FL_GPIO_EXTI_LINE_4_PB3                                (0x3U << 8U)
#define    FL_GPIO_EXTI_LINE_5_PB4                                (0x0U << 10U)
#define    FL_GPIO_EXTI_LINE_5_PB5                                (0x1U << 10U)
#define    FL_GPIO_EXTI_LINE_5_PB6                                (0x2U << 10U)
#define    FL_GPIO_EXTI_LINE_5_PB7                                (0x3U << 10U)
#define    FL_GPIO_EXTI_LINE_6_PB8                                (0x0U << 12U)
#define    FL_GPIO_EXTI_LINE_6_PB9                                (0x1U << 12U)
#define    FL_GPIO_EXTI_LINE_6_PB10                               (0x2U << 12U)
#define    FL_GPIO_EXTI_LINE_6_PB11                               (0x3U << 12U)
#define    FL_GPIO_EXTI_LINE_7_PB12                               (0x0U << 14U)
#define    FL_GPIO_EXTI_LINE_7_PB13                               (0x1U << 14U)
#define    FL_GPIO_EXTI_LINE_7_PB14                               (0x2U << 14U)
#define    FL_GPIO_EXTI_LINE_7_PB15                               (0x3U << 14U)
#define    FL_GPIO_EXTI_LINE_8_PC0                                (0x0U << 16U)
#define    FL_GPIO_EXTI_LINE_8_PC1                                (0x1U << 16U)
#define    FL_GPIO_EXTI_LINE_8_PC2                                (0x2U << 16U)
#define    FL_GPIO_EXTI_LINE_8_PC3                                (0x3U << 16U)
#define    FL_GPIO_EXTI_LINE_9_PC4                                (0x0U << 18U)
#define    FL_GPIO_EXTI_LINE_9_PC5                                (0x1U << 18U)
#define    FL_GPIO_EXTI_LINE_9_PC6                                (0x2U << 18U)
#define    FL_GPIO_EXTI_LINE_9_PC7                                (0x3U << 18U)
#define    FL_GPIO_EXTI_LINE_10_PC8                               (0x0U << 20U)
#define    FL_GPIO_EXTI_LINE_10_PC9                               (0x1U << 20U)
#define    FL_GPIO_EXTI_LINE_10_PC10                              (0x2U << 20U)
#define    FL_GPIO_EXTI_LINE_10_PC11                              (0x3U << 20U)
#define    FL_GPIO_EXTI_LINE_12_PD0                               (0x0U << 24U)
#define    FL_GPIO_EXTI_LINE_12_PD1                               (0x1U << 24U)
#define    FL_GPIO_EXTI_LINE_12_PD2                               (0x2U << 24U)
#define    FL_GPIO_EXTI_LINE_12_PD3                               (0x3U << 24U)
#define    FL_GPIO_EXTI_LINE_13_PD4                               (0x0U << 26U)
#define    FL_GPIO_EXTI_LINE_13_PD5                               (0x1U << 26U)
#define    FL_GPIO_EXTI_LINE_13_PD6                               (0x2U << 26U)
#define    FL_GPIO_EXTI_LINE_13_PD7                               (0x3U << 26U)
#define    FL_GPIO_EXTI_LINE_14_PD8                               (0x0U << 28U)
#define    FL_GPIO_EXTI_LINE_14_PD9                               (0x1U << 28U)
#define    FL_GPIO_EXTI_LINE_14_PD10                              (0x2U << 28U)
#define    FL_GPIO_EXTI_LINE_14_PD11                              (0x3U << 28U)
#define    FL_GPIO_WAKEUP_0                                       (0x1U << 0U)
#define    FL_GPIO_WAKEUP_1                                       (0x1U << 1U)
#define    FL_GPIO_WAKEUP_2                                       (0x1U << 2U)
#define    FL_GPIO_WAKEUP_3                                       (0x1U << 3U)
#define    FL_GPIO_WAKEUP_4                                       (0x1U << 4U)
#define    FL_GPIO_WAKEUP_5                                       (0x1U << 5U)
#define    FL_GPIO_WAKEUP_6                                       (0x1U << 6U)
#define    FL_GPIO_WAKEUP_7                                       (0x1U << 7U)
#define    FL_GPIO_OUTPUT_PUSHPULL                                0x0U
#define    FL_GPIO_OUTPUT_OPENDRAIN                               0x1U



#define    FL_GPIO_MODE_INPUT                                     (0x0U << GPIO_FCR_Pos)
#define    FL_GPIO_MODE_OUTPUT                                    (0x1U << GPIO_FCR_Pos)
#define    FL_GPIO_MODE_DIGITAL                                   (0x2U << GPIO_FCR_Pos)
#define    FL_GPIO_MODE_ANALOG                                    (0x3U << GPIO_FCR_Pos)


#define    FL_GPIO_EXTI_TRIGGER_EDGE_RISING                       (0x0U << GPIO_EXTIEDS_Pos)
#define    FL_GPIO_EXTI_TRIGGER_EDGE_FALLING                      (0x1U << GPIO_EXTIEDS_Pos)
#define    FL_GPIO_EXTI_TRIGGER_EDGE_BOTH                         (0x2U << GPIO_EXTIEDS_Pos)
#define    FL_GPIO_EXTI_TRIGGER_EDGE_DISABLE                      (0x3U << GPIO_EXTIEDS_Pos)


#define    FL_GPIO_FOUT0_SELECT_XTLF                              (0x0U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_LPOSC                             (0x1U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_RCHF_DIV64                        (0x2U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_LSCLK                             (0x3U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_AHBCLK_DIV64                      (0x4U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_RTCTM                             (0x5U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_PLLOUTPUT_DIV64                   (0x6U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_RTCCLK64Hz                        (0x7U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_APB1CLK_DIV64                     (0x8U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_PLLOUTPUT                         (0x9U << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_RCMF_PSC                          (0xaU << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_RCHF                              (0xbU << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_XTHF_DIV64                        (0xcU << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_COMP1_OUTPUT                      (0xdU << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_CLK_8K                            (0xeU << GPIO_FOUTSEL_FOUT0_Pos)
#define    FL_GPIO_FOUT0_SELECT_ADC_CLK                           (0xfU << GPIO_FOUTSEL_FOUT0_Pos)


#define    FL_GPIO_FOUT1_SELECT_XTLF                              (0x0U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_LPOSC                             (0x1U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_RCHF_DIV64                        (0x2U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_LSCLK                             (0x3U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_AHBCLK_DIV64                      (0x4U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_RTCTM                             (0x5U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_PLLOUTPUT_DIV64                   (0x6U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_RTCCLK64Hz                        (0x7U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_APB1CLK_DIV64                     (0x8U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_PLLOUTPUT                         (0x9U << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_RCMF_PSC                          (0xaU << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_RCHF                              (0xbU << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_XTHF_DIV64                        (0xcU << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_ADCCLK_DIV64                      (0xdU << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_CLK_8K                            (0xeU << GPIO_FOUTSEL_FOUT1_Pos)
#define    FL_GPIO_FOUT1_SELECT_COMP2_OUTPUT                      (0xfU << GPIO_FOUTSEL_FOUT1_Pos)


#define    FL_GPIO_WAKEUP_INT_ENTRY_NMI                           (0x0U << GPIO_PINWKEN_WKISEL_Pos)
#define    FL_GPIO_WAKEUP_INT_ENTRY_38                            (0x1U << GPIO_PINWKEN_WKISEL_Pos)


#define    FL_GPIO_WAKEUP_TRIGGER_RISING                          (0x1U << GPIO_PINWKEN_SEL_Pos)
#define    FL_GPIO_WAKEUP_TRIGGER_FALLING                         (0x0U << GPIO_PINWKEN_SEL_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup GPIO_FL_Exported_Functions GPIO Exported Functions
  * @{
  */

/**
  * @brief    GPIOx input enable
  * @rmtoll   INEN        FL_GPIO_EnablePinInput
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_EnablePinInput(GPIO_Type *GPIOx, uint32_t pin)
{
    SET_BIT(GPIOx->INEN, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    CPIOx input disable
  * @rmtoll   INEN        FL_GPIO_DisablePinInput
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_DisablePinInput(GPIO_Type *GPIOx, uint32_t pin)
{
    CLEAR_BIT(GPIOx->INEN, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Get GPIOx input enable status
  * @rmtoll   INEN        FL_GPIO_IsEnabledPinInput
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_IsEnabledPinInput(GPIO_Type *GPIOx, uint32_t pin)
{
    return (uint32_t)(READ_BIT(GPIOx->INEN, ((pin & 0xffff) << 0x0U)) == ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    GPIOx Pull-Up enable
  * @rmtoll   PUEN        FL_GPIO_EnablePinPullup
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_EnablePinPullup(GPIO_Type *GPIOx, uint32_t pin)
{
    SET_BIT(GPIOx->PUEN, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    GPIOx Pull-Up disable
  * @rmtoll   PUEN        FL_GPIO_DisablePinPullup
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_DisablePinPullup(GPIO_Type *GPIOx, uint32_t pin)
{
    CLEAR_BIT(GPIOx->PUEN, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Get GPIOx Pull-Up enable status
  * @rmtoll   PUEN        FL_GPIO_IsEnabledPinPullup
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_IsEnabledPinPullup(GPIO_Type *GPIOx, uint32_t pin)
{
    return (uint32_t)(READ_BIT(GPIOx->PUEN, ((pin & 0xffff) << 0x0U)) == ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    GPIOx Open-Drain enable
  * @rmtoll   ODEN        FL_GPIO_EnablePinOpenDrain
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_EnablePinOpenDrain(GPIO_Type *GPIOx, uint32_t pin)
{
    SET_BIT(GPIOx->ODEN, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Open-Drain disable
  * @rmtoll   ODEN        FL_GPIO_DisablePinOpenDrain
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_DisablePinOpenDrain(GPIO_Type *GPIOx, uint32_t pin)
{
    CLEAR_BIT(GPIOx->ODEN, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Get Open-Drain enable status
  * @rmtoll   ODEN        FL_GPIO_IsEnabledPinOpenDrain
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_IsEnabledPinOpenDrain(GPIO_Type *GPIOx, uint32_t pin)
{
    return (uint32_t)(READ_BIT(GPIOx->ODEN, ((pin & 0xffff) << 0x0U)) == ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    GPIOx digital function enable
  * @rmtoll   DFS        FL_GPIO_EnablePinRemap
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_EnablePinRemap(GPIO_Type *GPIOx, uint32_t pin)
{
    SET_BIT(GPIOx->DFS, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    GPIOx digital function disable
  * @rmtoll   DFS        FL_GPIO_DisablePinRemap
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_DisablePinRemap(GPIO_Type *GPIOx, uint32_t pin)
{
    CLEAR_BIT(GPIOx->DFS, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Get GPIOx digital function enable status
  * @rmtoll   DFS        FL_GPIO_IsEnabledPinRemap
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_IsEnabledPinRemap(GPIO_Type *GPIOx, uint32_t pin)
{
    return (uint32_t)(READ_BIT(GPIOx->DFS, ((pin & 0xffff) << 0x0U)) == ((pin & 0xffff) << 0x0U));
}

/**
  * @brief     GPIOx analog channel enable
  * @rmtoll   ANEN        FL_GPIO_EnablePinAnalogSwitch
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  *           @arg @ref FL_GPIO_EXTI_LINE_0
  *           @arg @ref FL_GPIO_EXTI_LINE_1
  *           @arg @ref FL_GPIO_EXTI_LINE_2
  *           @arg @ref FL_GPIO_EXTI_LINE_3
  *           @arg @ref FL_GPIO_EXTI_LINE_4
  *           @arg @ref FL_GPIO_EXTI_LINE_7
  *           @arg @ref FL_GPIO_EXTI_LINE_8
  *           @arg @ref FL_GPIO_EXTI_LINE_9
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_EnablePinAnalogSwitch(GPIO_Type *GPIOx, uint32_t pin)
{
    SET_BIT(GPIOx->ANEN, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief     GPIOx analog channel disable
  * @rmtoll   ANEN        FL_GPIO_DisablePinAnalogSwitch
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_DisablePinAnalogSwitch(GPIO_Type *GPIOx, uint32_t pin)
{
    CLEAR_BIT(GPIOx->ANEN, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Get  GPIOx analog channel enable status
  * @rmtoll   ANEN        FL_GPIO_IsEnabledPinAnalogSwitch
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_IsEnabledPinAnalogSwitch(GPIO_Type *GPIOx, uint32_t pin)
{
    return (uint32_t)(READ_BIT(GPIOx->ANEN, ((pin & 0xffff) << 0x0U)) == ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Set Portx mode
  * @rmtoll   FCR        FL_GPIO_SetPinMode
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_MODE_INPUT
  *           @arg @ref FL_GPIO_MODE_OUTPUT
  *           @arg @ref FL_GPIO_MODE_DIGITAL
  *           @arg @ref FL_GPIO_MODE_ANALOG
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetPinMode(GPIO_Type *GPIOx, uint32_t pin, uint32_t mode)
{
    MODIFY_REG(GPIOx->FCR, ((pin * pin) * GPIO_FCR), ((pin * pin) * mode));
}

/**
  * @brief    Get Portx mode
  * @rmtoll   FCR        FL_GPIO_GetPinMode
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPIO_MODE_INPUT
  *           @arg @ref FL_GPIO_MODE_OUTPUT
  *           @arg @ref FL_GPIO_MODE_DIGITAL
  *           @arg @ref FL_GPIO_MODE_ANALOG
  */
__STATIC_INLINE uint32_t FL_GPIO_GetPinMode(GPIO_Type *GPIOx, uint32_t pin)
{
    return (uint32_t)(READ_BIT(GPIOx->FCR, ((pin * pin) * GPIO_FCR)) / (pin * pin));
}

/**
  * @brief    Set GPIO output data
  * @rmtoll   DO        FL_GPIO_WriteOutputPort
  * @param    GPIOx GPIO Port
  * @param    output Level value for each pin of the port
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_WriteOutputPort(GPIO_Type *GPIOx, uint32_t output)
{
    MODIFY_REG(GPIOx->DO, (0xffffU << 0U), (output << 0U));
}

/**
  * @brief    Get GPIO output data
  * @rmtoll   DO        FL_GPIO_ReadOutputPort
  * @param    GPIOx GPIO Port
  * @retval   Output data register value of port
  */
__STATIC_INLINE uint32_t FL_GPIO_ReadOutputPort(GPIO_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->DO, 0xffffU) >> 0U);
}

/**
  * @brief    Get GPIO output pin status
  * @rmtoll   DO        FL_GPIO_GetOutputPin
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_GetOutputPin(GPIO_Type *GPIOx, uint32_t pin)
{
    return (uint32_t)(READ_BIT(GPIOx->DO, ((pin & 0xffff) << 0x0U)) == ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Toggle output pin
  * @rmtoll   DO        FL_GPIO_ToggleOutputPin
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_ToggleOutputPin(GPIO_Type *GPIOx, uint32_t pin)
{
    if(pin&GPIOx->DO)
    {
      WRITE_REG(GPIOx->DRST, pin);
    }
    else
    {
      WRITE_REG(GPIOx->DSET, pin);
    }
}

/**
  * @brief    Get input data
  * @rmtoll   DIN        FL_GPIO_ReadInputPort
  * @param    GPIOx GPIO Port
  * @retval   Input data register value of port
  */
__STATIC_INLINE uint32_t FL_GPIO_ReadInputPort(GPIO_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->DIN, 0xffffU) >> 0U);
}

/**
  * @brief    Get GPIO input set status
  * @rmtoll   DIN        FL_GPIO_GetInputPin
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_GetInputPin(GPIO_Type *GPIOx, uint32_t pin)
{
    return (uint32_t)(READ_BIT(GPIOx->DIN, ((pin & 0xffff) << 0x0U)) == ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Set pin output 1
  * @rmtoll   DSET        FL_GPIO_SetOutputPin
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetOutputPin(GPIO_Type *GPIOx, uint32_t pin)
{
    SET_BIT(GPIOx->DSET, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    Set pin output 0
  * @rmtoll   DRST        FL_GPIO_ResetOutputPin
  * @param    GPIOx GPIO Port
  * @param    pin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  *           @arg @ref FL_GPIO_PIN_1
  *           @arg @ref FL_GPIO_PIN_2
  *           @arg @ref FL_GPIO_PIN_3
  *           @arg @ref FL_GPIO_PIN_4
  *           @arg @ref FL_GPIO_PIN_5
  *           @arg @ref FL_GPIO_PIN_6
  *           @arg @ref FL_GPIO_PIN_7
  *           @arg @ref FL_GPIO_PIN_8
  *           @arg @ref FL_GPIO_PIN_9
  *           @arg @ref FL_GPIO_PIN_10
  *           @arg @ref FL_GPIO_PIN_11
  *           @arg @ref FL_GPIO_PIN_12
  *           @arg @ref FL_GPIO_PIN_13
  *           @arg @ref FL_GPIO_PIN_14
  *           @arg @ref FL_GPIO_PIN_15
  *           @arg @ref FL_GPIO_PIN_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_ResetOutputPin(GPIO_Type *GPIOx, uint32_t pin)
{
    SET_BIT(GPIOx->DRST, ((pin & 0xffff) << 0x0U));
}

/**
  * @brief    EXTI edge select
  * @rmtoll   EXTIEDS        FL_GPIO_SetTriggerEdge
  * @param    GPIOx GPIO Port
  * @param    line This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_0
  *           @arg @ref FL_GPIO_EXTI_LINE_1
  *           @arg @ref FL_GPIO_EXTI_LINE_2
  *           @arg @ref FL_GPIO_EXTI_LINE_3
  *           @arg @ref FL_GPIO_EXTI_LINE_4
  *           @arg @ref FL_GPIO_EXTI_LINE_5
  *           @arg @ref FL_GPIO_EXTI_LINE_6
  *           @arg @ref FL_GPIO_EXTI_LINE_7
  *           @arg @ref FL_GPIO_EXTI_LINE_8
  *           @arg @ref FL_GPIO_EXTI_LINE_9
  *           @arg @ref FL_GPIO_EXTI_LINE_10
  *           @arg @ref FL_GPIO_EXTI_LINE_11
  *           @arg @ref FL_GPIO_EXTI_LINE_12
  *           @arg @ref FL_GPIO_EXTI_LINE_13
  *           @arg @ref FL_GPIO_EXTI_LINE_14
  *           @arg @ref FL_GPIO_EXTI_LINE_15
  * @param    edge This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_TRIGGER_EDGE_RISING
  *           @arg @ref FL_GPIO_EXTI_TRIGGER_EDGE_FALLING
  *           @arg @ref FL_GPIO_EXTI_TRIGGER_EDGE_BOTH
  *           @arg @ref FL_GPIO_EXTI_TRIGGER_EDGE_DISABLE
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetTriggerEdge(GPIO_COMMON_Type *GPIOx, uint32_t line, uint32_t edge)
{
    MODIFY_REG(GPIOx->EXTIEDS, ((line * line) * GPIO_EXTIEDS), ((line * line) * edge));
}

/**
  * @brief    Get EXTI edge select
  * @rmtoll   EXTIEDS        FL_GPIO_GetTriggerEdge
  * @param    GPIOx GPIO Port
  * @param    line This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_0
  *           @arg @ref FL_GPIO_EXTI_LINE_1
  *           @arg @ref FL_GPIO_EXTI_LINE_2
  *           @arg @ref FL_GPIO_EXTI_LINE_3
  *           @arg @ref FL_GPIO_EXTI_LINE_4
  *           @arg @ref FL_GPIO_EXTI_LINE_5
  *           @arg @ref FL_GPIO_EXTI_LINE_6
  *           @arg @ref FL_GPIO_EXTI_LINE_7
  *           @arg @ref FL_GPIO_EXTI_LINE_8
  *           @arg @ref FL_GPIO_EXTI_LINE_9
  *           @arg @ref FL_GPIO_EXTI_LINE_10
  *           @arg @ref FL_GPIO_EXTI_LINE_11
  *           @arg @ref FL_GPIO_EXTI_LINE_12
  *           @arg @ref FL_GPIO_EXTI_LINE_13
  *           @arg @ref FL_GPIO_EXTI_LINE_14
  *           @arg @ref FL_GPIO_EXTI_LINE_15
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_TRIGGER_EDGE_RISING
  *           @arg @ref FL_GPIO_EXTI_TRIGGER_EDGE_FALLING
  *           @arg @ref FL_GPIO_EXTI_TRIGGER_EDGE_BOTH
  *           @arg @ref FL_GPIO_EXTI_TRIGGER_EDGE_DISABLE
  */
__STATIC_INLINE uint32_t FL_GPIO_GetTriggerEdge(GPIO_COMMON_Type *GPIOx, uint32_t line)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTIEDS, ((line * line) * GPIO_EXTIEDS)) / (line * line));
}

/**
  * @brief    EXTI digital filter enable
  * @rmtoll   EXTIDF        FL_GPIO_EnableDigitalFilter
  * @param    GPIOx GPIO Port
  * @param    line This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_0
  *           @arg @ref FL_GPIO_EXTI_LINE_1
  *           @arg @ref FL_GPIO_EXTI_LINE_2
  *           @arg @ref FL_GPIO_EXTI_LINE_3
  *           @arg @ref FL_GPIO_EXTI_LINE_4
  *           @arg @ref FL_GPIO_EXTI_LINE_5
  *           @arg @ref FL_GPIO_EXTI_LINE_6
  *           @arg @ref FL_GPIO_EXTI_LINE_7
  *           @arg @ref FL_GPIO_EXTI_LINE_8
  *           @arg @ref FL_GPIO_EXTI_LINE_9
  *           @arg @ref FL_GPIO_EXTI_LINE_10
  *           @arg @ref FL_GPIO_EXTI_LINE_11
  *           @arg @ref FL_GPIO_EXTI_LINE_12
  *           @arg @ref FL_GPIO_EXTI_LINE_13
  *           @arg @ref FL_GPIO_EXTI_LINE_14
  *           @arg @ref FL_GPIO_EXTI_LINE_15
  *           @arg @ref FL_GPIO_EXTI_LINE_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_EnableDigitalFilter(GPIO_COMMON_Type *GPIOx, uint32_t line)
{
    SET_BIT(GPIOx->EXTIDF, ((line & 0xffff) << 0x0U));
}

/**
  * @brief    EXTI digital filter disable
  * @rmtoll   EXTIDF        FL_GPIO_DisableDigitalFilter
  * @param    GPIOx GPIO Port
  * @param    line This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_0
  *           @arg @ref FL_GPIO_EXTI_LINE_1
  *           @arg @ref FL_GPIO_EXTI_LINE_2
  *           @arg @ref FL_GPIO_EXTI_LINE_3
  *           @arg @ref FL_GPIO_EXTI_LINE_4
  *           @arg @ref FL_GPIO_EXTI_LINE_5
  *           @arg @ref FL_GPIO_EXTI_LINE_6
  *           @arg @ref FL_GPIO_EXTI_LINE_7
  *           @arg @ref FL_GPIO_EXTI_LINE_8
  *           @arg @ref FL_GPIO_EXTI_LINE_9
  *           @arg @ref FL_GPIO_EXTI_LINE_10
  *           @arg @ref FL_GPIO_EXTI_LINE_11
  *           @arg @ref FL_GPIO_EXTI_LINE_12
  *           @arg @ref FL_GPIO_EXTI_LINE_13
  *           @arg @ref FL_GPIO_EXTI_LINE_14
  *           @arg @ref FL_GPIO_EXTI_LINE_15
  *           @arg @ref FL_GPIO_EXTI_LINE_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_DisableDigitalFilter(GPIO_COMMON_Type *GPIOx, uint32_t line)
{
    CLEAR_BIT(GPIOx->EXTIDF, ((line & 0xffff) << 0x0U));
}

/**
  * @brief    Get EXTI digital filter enable status
  * @rmtoll   EXTIDF        FL_GPIO_IsEnabledDigitalFilter
  * @param    GPIOx GPIO Port
  * @param    line This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_0
  *           @arg @ref FL_GPIO_EXTI_LINE_1
  *           @arg @ref FL_GPIO_EXTI_LINE_2
  *           @arg @ref FL_GPIO_EXTI_LINE_3
  *           @arg @ref FL_GPIO_EXTI_LINE_4
  *           @arg @ref FL_GPIO_EXTI_LINE_5
  *           @arg @ref FL_GPIO_EXTI_LINE_6
  *           @arg @ref FL_GPIO_EXTI_LINE_7
  *           @arg @ref FL_GPIO_EXTI_LINE_8
  *           @arg @ref FL_GPIO_EXTI_LINE_9
  *           @arg @ref FL_GPIO_EXTI_LINE_10
  *           @arg @ref FL_GPIO_EXTI_LINE_11
  *           @arg @ref FL_GPIO_EXTI_LINE_12
  *           @arg @ref FL_GPIO_EXTI_LINE_13
  *           @arg @ref FL_GPIO_EXTI_LINE_14
  *           @arg @ref FL_GPIO_EXTI_LINE_15
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_IsEnabledDigitalFilter(GPIO_COMMON_Type *GPIOx, uint32_t line)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTIDF, ((line & 0xffff) << 0x0U)) == ((line & 0xffff) << 0x0U));
}

/**
  * @brief    Get external interrupt flag status
  * @rmtoll   EXTIISR        FL_GPIO_IsActiveFlag_EXTI
  * @param    GPIOx GPIO Port
  * @param    line This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_0
  *           @arg @ref FL_GPIO_EXTI_LINE_1
  *           @arg @ref FL_GPIO_EXTI_LINE_2
  *           @arg @ref FL_GPIO_EXTI_LINE_3
  *           @arg @ref FL_GPIO_EXTI_LINE_4
  *           @arg @ref FL_GPIO_EXTI_LINE_5
  *           @arg @ref FL_GPIO_EXTI_LINE_6
  *           @arg @ref FL_GPIO_EXTI_LINE_7
  *           @arg @ref FL_GPIO_EXTI_LINE_8
  *           @arg @ref FL_GPIO_EXTI_LINE_9
  *           @arg @ref FL_GPIO_EXTI_LINE_10
  *           @arg @ref FL_GPIO_EXTI_LINE_11
  *           @arg @ref FL_GPIO_EXTI_LINE_12
  *           @arg @ref FL_GPIO_EXTI_LINE_13
  *           @arg @ref FL_GPIO_EXTI_LINE_14
  *           @arg @ref FL_GPIO_EXTI_LINE_15
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_IsActiveFlag_EXTI(GPIO_COMMON_Type *GPIOx, uint32_t line)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTIISR, ((line & 0xffff) << 0x0U)) == ((line & 0xffff) << 0x0U));
}

/**
  * @brief    Clear external interrupt flag
  * @rmtoll   EXTIISR        FL_GPIO_ClearFlag_EXTI
  * @param    GPIOx GPIO Port
  * @param    line This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_0
  *           @arg @ref FL_GPIO_EXTI_LINE_1
  *           @arg @ref FL_GPIO_EXTI_LINE_2
  *           @arg @ref FL_GPIO_EXTI_LINE_3
  *           @arg @ref FL_GPIO_EXTI_LINE_4
  *           @arg @ref FL_GPIO_EXTI_LINE_5
  *           @arg @ref FL_GPIO_EXTI_LINE_6
  *           @arg @ref FL_GPIO_EXTI_LINE_7
  *           @arg @ref FL_GPIO_EXTI_LINE_8
  *           @arg @ref FL_GPIO_EXTI_LINE_9
  *           @arg @ref FL_GPIO_EXTI_LINE_10
  *           @arg @ref FL_GPIO_EXTI_LINE_11
  *           @arg @ref FL_GPIO_EXTI_LINE_12
  *           @arg @ref FL_GPIO_EXTI_LINE_13
  *           @arg @ref FL_GPIO_EXTI_LINE_14
  *           @arg @ref FL_GPIO_EXTI_LINE_15
  *           @arg @ref FL_GPIO_EXTI_LINE_ALL
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_ClearFlag_EXTI(GPIO_COMMON_Type *GPIOx, uint32_t line)
{
    WRITE_REG(GPIOx->EXTIISR, ((line & 0xffff) << 0x0U));
}

/**
  * @brief    Get EXTI input set status
  * @rmtoll   EXTIDI        FL_GPIO_GetEXTILine
  * @param    GPIOx GPIO Port
  * @param    line This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_0
  *           @arg @ref FL_GPIO_EXTI_LINE_1
  *           @arg @ref FL_GPIO_EXTI_LINE_2
  *           @arg @ref FL_GPIO_EXTI_LINE_3
  *           @arg @ref FL_GPIO_EXTI_LINE_4
  *           @arg @ref FL_GPIO_EXTI_LINE_5
  *           @arg @ref FL_GPIO_EXTI_LINE_6
  *           @arg @ref FL_GPIO_EXTI_LINE_7
  *           @arg @ref FL_GPIO_EXTI_LINE_8
  *           @arg @ref FL_GPIO_EXTI_LINE_9
  *           @arg @ref FL_GPIO_EXTI_LINE_10
  *           @arg @ref FL_GPIO_EXTI_LINE_11
  *           @arg @ref FL_GPIO_EXTI_LINE_12
  *           @arg @ref FL_GPIO_EXTI_LINE_13
  *           @arg @ref FL_GPIO_EXTI_LINE_14
  *           @arg @ref FL_GPIO_EXTI_LINE_15
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_GetEXTILine(GPIO_COMMON_Type *GPIOx, uint32_t line)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTIDI, ((line & 0xffff) << 0x0U)) == ((line & 0xffff) << 0x0U));
}

/**
  * @brief    Get EXTI input status
  * @rmtoll   EXTIDI        FL_GPIO_ReadEXTILines
  * @param    GPIOx GPIO Port
  * @retval   EXTI data register value of port
  */
__STATIC_INLINE uint32_t FL_GPIO_ReadEXTILines(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTIDI, 0xffffU) >> 0U);
}

/**
  * @brief    Set PD11 frequency output
  * @rmtoll   FOUTSEL    FOUT0    FL_GPIO_SetFOUT0
  * @param    GPIOx GPIO Port
  * @param    select This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_FOUT0_SELECT_XTLF
  *           @arg @ref FL_GPIO_FOUT0_SELECT_LPOSC
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RCHF_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_LSCLK
  *           @arg @ref FL_GPIO_FOUT0_SELECT_AHBCLK_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RTCTM
  *           @arg @ref FL_GPIO_FOUT0_SELECT_PLLOUTPUT_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RTCCLK64Hz
  *           @arg @ref FL_GPIO_FOUT0_SELECT_APB1CLK_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_PLLOUTPUT
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RCMF_PSC
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RCHF
  *           @arg @ref FL_GPIO_FOUT0_SELECT_XTHF_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_COMP1_OUTPUT
  *           @arg @ref FL_GPIO_FOUT0_SELECT_CLK_8K
  *           @arg @ref FL_GPIO_FOUT0_SELECT_ADC_CLK
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetFOUT0(GPIO_COMMON_Type *GPIOx, uint32_t select)
{
    MODIFY_REG(GPIOx->FOUTSEL, GPIO_FOUTSEL_FOUT0_Msk, select);
}

/**
  * @brief    Get PD11 frequency output
  * @rmtoll   FOUTSEL    FOUT0    FL_GPIO_GetFOUT0
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPIO_FOUT0_SELECT_XTLF
  *           @arg @ref FL_GPIO_FOUT0_SELECT_LPOSC
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RCHF_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_LSCLK
  *           @arg @ref FL_GPIO_FOUT0_SELECT_AHBCLK_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RTCTM
  *           @arg @ref FL_GPIO_FOUT0_SELECT_PLLOUTPUT_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RTCCLK64Hz
  *           @arg @ref FL_GPIO_FOUT0_SELECT_APB1CLK_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_PLLOUTPUT
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RCMF_PSC
  *           @arg @ref FL_GPIO_FOUT0_SELECT_RCHF
  *           @arg @ref FL_GPIO_FOUT0_SELECT_XTHF_DIV64
  *           @arg @ref FL_GPIO_FOUT0_SELECT_COMP1_OUTPUT
  *           @arg @ref FL_GPIO_FOUT0_SELECT_CLK_8K
  *           @arg @ref FL_GPIO_FOUT0_SELECT_ADC_CLK
  */
__STATIC_INLINE uint32_t FL_GPIO_GetFOUT0(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->FOUTSEL, GPIO_FOUTSEL_FOUT0_Msk));
}

/**
  * @brief    Set PB12 frequency output
  * @rmtoll   FOUTSEL    FOUT1    FL_GPIO_SetFOUT1
  * @param    GPIOx GPIO Port
  * @param    select This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_FOUT1_SELECT_XTLF
  *           @arg @ref FL_GPIO_FOUT1_SELECT_LPOSC
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RCHF_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_LSCLK
  *           @arg @ref FL_GPIO_FOUT1_SELECT_AHBCLK_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RTCTM
  *           @arg @ref FL_GPIO_FOUT1_SELECT_PLLOUTPUT_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RTCCLK64Hz
  *           @arg @ref FL_GPIO_FOUT1_SELECT_APB1CLK_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_PLLOUTPUT
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RCMF_PSC
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RCHF
  *           @arg @ref FL_GPIO_FOUT1_SELECT_XTHF_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_ADCCLK_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_CLK_8K
  *           @arg @ref FL_GPIO_FOUT1_SELECT_COMP2_OUTPUT
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetFOUT1(GPIO_COMMON_Type *GPIOx, uint32_t select)
{
    MODIFY_REG(GPIOx->FOUTSEL, GPIO_FOUTSEL_FOUT1_Msk, select);
}

/**
  * @brief    Get PB12 frequency output
  * @rmtoll   FOUTSEL    FOUT1    FL_GPIO_GetFOUT1
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPIO_FOUT1_SELECT_XTLF
  *           @arg @ref FL_GPIO_FOUT1_SELECT_LPOSC
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RCHF_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_LSCLK
  *           @arg @ref FL_GPIO_FOUT1_SELECT_AHBCLK_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RTCTM
  *           @arg @ref FL_GPIO_FOUT1_SELECT_PLLOUTPUT_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RTCCLK64Hz
  *           @arg @ref FL_GPIO_FOUT1_SELECT_APB1CLK_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_PLLOUTPUT
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RCMF_PSC
  *           @arg @ref FL_GPIO_FOUT1_SELECT_RCHF
  *           @arg @ref FL_GPIO_FOUT1_SELECT_XTHF_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_ADCCLK_DIV64
  *           @arg @ref FL_GPIO_FOUT1_SELECT_CLK_8K
  *           @arg @ref FL_GPIO_FOUT1_SELECT_COMP2_OUTPUT
  */
__STATIC_INLINE uint32_t FL_GPIO_GetFOUT1(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->FOUTSEL, GPIO_FOUTSEL_FOUT1_Msk));
}

/**
  * @brief    Set EXTI0 interrupt input
  * @rmtoll   EXTISEL    EXTI0    FL_GPIO_SetExtiLine0
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_0_PA0
  *           @arg @ref FL_GPIO_EXTI_LINE_0_PA1
  *           @arg @ref FL_GPIO_EXTI_LINE_0_PA2
  *           @arg @ref FL_GPIO_EXTI_LINE_0_PA3
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine0(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI0_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI0 interrupt input
  * @rmtoll   EXTISEL    EXTI0    FL_GPIO_GetExtiLine0
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine0(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI0_Msk));
}

/**
  * @brief    Set EXTI1 interrupt input
  * @rmtoll   EXTISEL    EXTI1    FL_GPIO_SetExtiLine1
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_1_PA4
  *           @arg @ref FL_GPIO_EXTI_LINE_1_PA5
  *           @arg @ref FL_GPIO_EXTI_LINE_1_PA6
  *           @arg @ref FL_GPIO_EXTI_LINE_1_PA7
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine1(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI1_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI1 interrupt input
  * @rmtoll   EXTISEL    EXTI1    FL_GPIO_GetExtiLine1
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine1(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI1_Msk));
}

/**
  * @brief    Set EXTI2 interrupt input
  * @rmtoll   EXTISEL    EXTI2    FL_GPIO_SetExtiLine2
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_2_PA8
  *           @arg @ref FL_GPIO_EXTI_LINE_2_PA9
  *           @arg @ref FL_GPIO_EXTI_LINE_2_PA10
  *           @arg @ref FL_GPIO_EXTI_LINE_2_PA11
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine2(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI2_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI2 interrupt input
  * @rmtoll   EXTISEL    EXTI2    FL_GPIO_GetExtiLine2
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine2(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI2_Msk));
}

/**
  * @brief    Set EXTI3 interrupt input
  * @rmtoll   EXTISEL    EXTI3    FL_GPIO_SetExtiLine3
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_3_PA12
  *           @arg @ref FL_GPIO_EXTI_LINE_3_PA13
  *           @arg @ref FL_GPIO_EXTI_LINE_3_PA14
  *           @arg @ref FL_GPIO_EXTI_LINE_3_PA15
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine3(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI3_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI3 interrupt input
  * @rmtoll   EXTISEL    EXTI3    FL_GPIO_GetExtiLine3
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine3(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI3_Msk));
}

/**
  * @brief    Set EXTI4 interrupt input
  * @rmtoll   EXTISEL    EXTI4    FL_GPIO_SetExtiLine4
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_4_PB0
  *           @arg @ref FL_GPIO_EXTI_LINE_4_PB1
  *           @arg @ref FL_GPIO_EXTI_LINE_4_PB2
  *           @arg @ref FL_GPIO_EXTI_LINE_4_PB3
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine4(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI4_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI4 interrupt input
  * @rmtoll   EXTISEL    EXTI4    FL_GPIO_GetExtiLine4
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine4(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI4_Msk));
}

/**
  * @brief    Set EXTI5 interrupt input
  * @rmtoll   EXTISEL    EXTI5    FL_GPIO_SetExtiLine5
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_5_PB4
  *           @arg @ref FL_GPIO_EXTI_LINE_5_PB5
  *           @arg @ref FL_GPIO_EXTI_LINE_5_PB6
  *           @arg @ref FL_GPIO_EXTI_LINE_5_PB7
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine5(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI5_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI5 interrupt input
  * @rmtoll   EXTISEL    EXTI5    FL_GPIO_GetExtiLine5
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine5(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI5_Msk));
}

/**
  * @brief    Set EXTI6 interrupt input
  * @rmtoll   EXTISEL    EXTI6    FL_GPIO_SetExtiLine6
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_6_PB8
  *           @arg @ref FL_GPIO_EXTI_LINE_6_PB9
  *           @arg @ref FL_GPIO_EXTI_LINE_6_PB10
  *           @arg @ref FL_GPIO_EXTI_LINE_6_PB11
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine6(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI6_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI6 interrupt input
  * @rmtoll   EXTISEL    EXTI6    FL_GPIO_GetExtiLine6
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine6(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI6_Msk));
}

/**
  * @brief    Set EXTI7 interrupt input
  * @rmtoll   EXTISEL    EXTI7    FL_GPIO_SetExtiLine7
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_7_PB12
  *           @arg @ref FL_GPIO_EXTI_LINE_7_PB13
  *           @arg @ref FL_GPIO_EXTI_LINE_7_PB14
  *           @arg @ref FL_GPIO_EXTI_LINE_7_PB15
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine7(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI7_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI7 interrupt input
  * @rmtoll   EXTISEL    EXTI7    FL_GPIO_GetExtiLine7
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine7(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI7_Msk));
}

/**
  * @brief    Set EXTI8 interrupt input
  * @rmtoll   EXTISEL    EXTI8    FL_GPIO_SetExtiLine8
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_8_PC0
  *           @arg @ref FL_GPIO_EXTI_LINE_8_PC1
  *           @arg @ref FL_GPIO_EXTI_LINE_8_PC2
  *           @arg @ref FL_GPIO_EXTI_LINE_8_PC3
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine8(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI8_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI8 interrupt input
  * @rmtoll   EXTISEL    EXTI8    FL_GPIO_GetExtiLine8
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine8(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI8_Msk));
}

/**
  * @brief    Set EXTI9 interrupt input
  * @rmtoll   EXTISEL    EXTI9    FL_GPIO_SetExtiLine9
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_9_PC4
  *           @arg @ref FL_GPIO_EXTI_LINE_9_PC5
  *           @arg @ref FL_GPIO_EXTI_LINE_9_PC6
  *           @arg @ref FL_GPIO_EXTI_LINE_9_PC7
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine9(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI9_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI9 interrupt input
  * @rmtoll   EXTISEL    EXTI9    FL_GPIO_GetExtiLine9
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine9(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI9_Msk));
}

/**
  * @brief    Set EXTI10 interrupt input
  * @rmtoll   EXTISEL    EXTI10    FL_GPIO_SetExtiLine10
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_10_PC8
  *           @arg @ref FL_GPIO_EXTI_LINE_10_PC9
  *           @arg @ref FL_GPIO_EXTI_LINE_10_PC10
  *           @arg @ref FL_GPIO_EXTI_LINE_10_PC11
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine10(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI10_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI10 interrupt input
  * @rmtoll   EXTISEL    EXTI10    FL_GPIO_GetExtiLine10
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine10(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI10_Msk));
}

/**
  * @brief    Set EXTI11 interrupt input
  * @rmtoll   EXTISEL    EXTI11    FL_GPIO_SetExtiLine11
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_PIN_0
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine11(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI11_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI11 interrupt input
  * @rmtoll   EXTISEL    EXTI11    FL_GPIO_GetExtiLine11
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine11(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI11_Msk));
}

/**
  * @brief    Set EXTI12 interrupt input
  * @rmtoll   EXTISEL    EXTI12    FL_GPIO_SetExtiLine12
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_12_PD0
  *           @arg @ref FL_GPIO_EXTI_LINE_12_PD1
  *           @arg @ref FL_GPIO_EXTI_LINE_12_PD2
  *           @arg @ref FL_GPIO_EXTI_LINE_12_PD3
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine12(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI12_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI12 interrupt input
  * @rmtoll   EXTISEL    EXTI12    FL_GPIO_GetExtiLine12
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine12(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI12_Msk));
}

/**
  * @brief    Set EXTI13 interrupt input
  * @rmtoll   EXTISEL    EXTI13    FL_GPIO_SetExtiLine13
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_13_PD4
  *           @arg @ref FL_GPIO_EXTI_LINE_13_PD5
  *           @arg @ref FL_GPIO_EXTI_LINE_13_PD6
  *           @arg @ref FL_GPIO_EXTI_LINE_13_PD7
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine13(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI13_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI13 interrupt input
  * @rmtoll   EXTISEL    EXTI13    FL_GPIO_GetExtiLine13
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine13(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI13_Msk));
}

/**
  * @brief    Set EXTI14 interrupt input
  * @rmtoll   EXTISEL    EXTI14    FL_GPIO_SetExtiLine14
  * @param    GPIOx GPIO Port
  * @param    EXTIPin This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_EXTI_LINE_14_PD8
  *           @arg @ref FL_GPIO_EXTI_LINE_14_PD9
  *           @arg @ref FL_GPIO_EXTI_LINE_14_PD10
  *           @arg @ref FL_GPIO_EXTI_LINE_14_PD11
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetExtiLine14(GPIO_COMMON_Type *GPIOx, uint32_t EXTIPin)
{
    MODIFY_REG(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI14_Msk, EXTIPin);
}

/**
  * @brief    Get EXTI14 interrupt input
  * @rmtoll   EXTISEL    EXTI14    FL_GPIO_GetExtiLine14
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_GPIO_GetExtiLine14(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->EXTISEL, GPIO_EXTISEL_EXTI14_Msk));
}

/**
  * @brief    Get WKUP enable status
  * @rmtoll   PINWKEN    EN    FL_GPIO_IsEnabledWakeup
  * @param    GPIOx GPIO Port
  * @param    wakeup This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_WAKEUP_0
  *           @arg @ref FL_GPIO_WAKEUP_1
  *           @arg @ref FL_GPIO_WAKEUP_2
  *           @arg @ref FL_GPIO_WAKEUP_3
  *           @arg @ref FL_GPIO_WAKEUP_4
  *           @arg @ref FL_GPIO_WAKEUP_5
  *           @arg @ref FL_GPIO_WAKEUP_6
  *           @arg @ref FL_GPIO_WAKEUP_7
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_GPIO_IsEnabledWakeup(GPIO_COMMON_Type *GPIOx, uint32_t wakeup)
{
    return (uint32_t)(READ_BIT(GPIOx->PINWKEN, ((wakeup & 0xff) << 0x0U)) == ((wakeup & 0xff) << 0x0U));
}

/**
  * @brief    WKUP enable
  * @rmtoll   PINWKEN    EN    FL_GPIO_EnableWakeup
  * @param    GPIOx GPIO Port
  * @param    wakeup This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_WAKEUP_0
  *           @arg @ref FL_GPIO_WAKEUP_1
  *           @arg @ref FL_GPIO_WAKEUP_2
  *           @arg @ref FL_GPIO_WAKEUP_3
  *           @arg @ref FL_GPIO_WAKEUP_4
  *           @arg @ref FL_GPIO_WAKEUP_5
  *           @arg @ref FL_GPIO_WAKEUP_6
  *           @arg @ref FL_GPIO_WAKEUP_7
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_EnableWakeup(GPIO_COMMON_Type *GPIOx, uint32_t wakeup)
{
    SET_BIT(GPIOx->PINWKEN, ((wakeup & 0xff) << 0x0U));
}

/**
  * @brief    WKUP disable
  * @rmtoll   PINWKEN    EN    FL_GPIO_DisableWakeup
  * @param    GPIOx GPIO Port
  * @param    wakeup This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_WAKEUP_0
  *           @arg @ref FL_GPIO_WAKEUP_1
  *           @arg @ref FL_GPIO_WAKEUP_2
  *           @arg @ref FL_GPIO_WAKEUP_3
  *           @arg @ref FL_GPIO_WAKEUP_4
  *           @arg @ref FL_GPIO_WAKEUP_5
  *           @arg @ref FL_GPIO_WAKEUP_6
  *           @arg @ref FL_GPIO_WAKEUP_7
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_DisableWakeup(GPIO_COMMON_Type *GPIOx, uint32_t wakeup)
{
    CLEAR_BIT(GPIOx->PINWKEN, ((wakeup & 0xff) << 0x0U));
}

/**
  * @brief    Get WKUP interrupt entry
  * @rmtoll   PINWKEN    WKISEL    FL_GPIO_GetWakeupInterruptEntry
  * @param    GPIOx GPIO Port
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPIO_WAKEUP_INT_ENTRY_NMI
  *           @arg @ref FL_GPIO_WAKEUP_INT_ENTRY_38
  */
__STATIC_INLINE uint32_t FL_GPIO_GetWakeupInterruptEntry(GPIO_COMMON_Type *GPIOx)
{
    return (uint32_t)(READ_BIT(GPIOx->PINWKEN, GPIO_PINWKEN_WKISEL_Msk));
}

/**
  * @brief    Set wkup interrupt entry
  * @rmtoll   PINWKEN    WKISEL    FL_GPIO_SetWakeupInterruptEntry
  * @param    GPIOx GPIO Port
  * @param    wakeup This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_WAKEUP_INT_ENTRY_NMI
  *           @arg @ref FL_GPIO_WAKEUP_INT_ENTRY_38
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetWakeupInterruptEntry(GPIO_COMMON_Type *GPIOx, uint32_t wakeup)
{
    MODIFY_REG(GPIOx->PINWKEN, GPIO_PINWKEN_WKISEL_Msk, wakeup);
}

/**
  * @brief    Set WKUP edge polarity
  * @rmtoll   PINWKEN    SEL    FL_GPIO_SetWakeupEdge
  * @param    GPIOx GPIO Port
  * @param    wakeup This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_WAKEUP_0
  *           @arg @ref FL_GPIO_WAKEUP_1
  *           @arg @ref FL_GPIO_WAKEUP_2
  *           @arg @ref FL_GPIO_WAKEUP_3
  *           @arg @ref FL_GPIO_WAKEUP_4
  *           @arg @ref FL_GPIO_WAKEUP_5
  *           @arg @ref FL_GPIO_WAKEUP_6
  *           @arg @ref FL_GPIO_WAKEUP_7
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_WAKEUP_TRIGGER_RISING
  *           @arg @ref FL_GPIO_WAKEUP_TRIGGER_FALLING
  * @retval   None
  */
__STATIC_INLINE void FL_GPIO_SetWakeupEdge(GPIO_COMMON_Type *GPIOx, uint32_t wakeup, uint32_t mode)
{
    MODIFY_REG(GPIOx->PINWKEN, (wakeup << GPIO_PINWKEN_SEL_Pos), (wakeup * mode));
}

/**
  * @brief    Get WKUP edge polarity
  * @rmtoll   PINWKEN    SEL    FL_GPIO_GetWakeupEdge
  * @param    GPIOx GPIO Port
  * @param    wakeup This parameter can be one of the following values:
  *           @arg @ref FL_GPIO_WAKEUP_0
  *           @arg @ref FL_GPIO_WAKEUP_1
  *           @arg @ref FL_GPIO_WAKEUP_2
  *           @arg @ref FL_GPIO_WAKEUP_3
  *           @arg @ref FL_GPIO_WAKEUP_4
  *           @arg @ref FL_GPIO_WAKEUP_5
  *           @arg @ref FL_GPIO_WAKEUP_6
  *           @arg @ref FL_GPIO_WAKEUP_7
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_GPIO_WAKEUP_TRIGGER_RISING
  *           @arg @ref FL_GPIO_WAKEUP_TRIGGER_FALLING
  */
__STATIC_INLINE uint32_t FL_GPIO_GetWakeupEdge(GPIO_COMMON_Type *GPIOx, uint32_t wakeup)
{
    return (uint32_t)(READ_BIT(GPIOx->PINWKEN, (wakeup << GPIO_PINWKEN_SEL_Pos)) / wakeup);
}

/**
  * @}
  */

/** @defgroup GPIO_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus FL_GPIO_Init(GPIO_Type *GPIOx, FL_GPIO_InitTypeDef *initStruct);
FL_ErrorStatus FL_GPIO_DeInit(GPIO_Type *GPIOx, uint32_t pin);
void FL_GPIO_StructInit(FL_GPIO_InitTypeDef *initStruct);
FL_ErrorStatus FL_WKUP_Init(FL_WKUP_InitTypeDef *initStruct, uint32_t wakeup);
FL_ErrorStatus FL_WKUP_DeInit(uint32_t wakeup);
void FL_WKUP_StructInit(FL_WKUP_InitTypeDef *initStruct);

/**
  * @}
  */

/** @defgroup RNG_FL_EF_Operation Opeartion functions
  * @{
  */

void FL_GPIO_ALLPIN_LPM_MODE(void);

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

#endif /* __FM33LC0XX_FL_GPIO_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.2 @ 2021-08-19*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
