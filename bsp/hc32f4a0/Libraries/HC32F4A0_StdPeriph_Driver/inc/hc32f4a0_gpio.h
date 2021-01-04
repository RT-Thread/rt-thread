/**
 *******************************************************************************
 * @file  hc32f4a0_gpio.h
 * @brief This file contains all the functions prototypes of the GPIO driver
 *        library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Zhangxl         First version
   2020-09-21       Zhangxl         Typo, missing FUNC_I2C3 defintion
   2020-10-27       Zhangxl         Revise debug port definition
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_GPIO_H__
#define __HC32F4A0_GPIO_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_GPIO
 * @{
 */

#if (DDL_GPIO_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Types GPIO Global Types
 * @{
 */

/**
 * @brief  GPIO Pin Set and Reset enumeration
 */
typedef enum
{
    Pin_Reset = 0U,           /*!< Pin reset    */
    Pin_Set   = 1U            /*!< Pin set      */
} en_pin_state_t;

/**
 * @brief  GPIO Init structure definition
 */
typedef struct
{
    uint16_t u16PinState;     /*!< Set pin state to High or Low, @ref GPIO_PinState_Sel for details       */
    uint16_t u16PinDir;       /*!< Pin mode setting, @ref GPIO_PinDirection_Sel for details               */
    uint16_t u16PinOType;     /*!< Output type setting, @ref GPIO_PinOutType_Sel for details              */
    uint16_t u16PinDrv;       /*!< Pin drive capacity setting, @ref GPIO_PinDrv_Sel for details           */
    uint16_t u16Latch;        /*!< Pin latch setting, @ref GPIO_PinLatch_Sel for details                  */
    uint16_t u16PullUp;       /*!< Internal pull-up resistor setting, @ref GPIO_PinPU_Sel for details     */
    uint16_t u16Invert;       /*!< Pin input/output invert setting, @ref GPIO_PinInvert_Sel               */
    uint16_t u16PinIType;     /*!< Input type setting, @ref GPIO_PinInType_Sel                            */
    uint16_t u16ExInt;        /*!< External interrupt pin setting, @ref GPIO_PinExInt_Sel for details     */
    uint16_t u16PinAttr;      /*!< Digital or analog attribute setting, @ref GPIO_PinMode_Sel for details */
} stc_gpio_init_t;
/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup GPIO_Global_Macros GPIO Global Macros
 * @{
 */

/** @defgroup GPIO_pins_define GPIO pin source
 * @{
 */
#define GPIO_PIN_00                 (0x0001U)  /*!< Pin 00 selected   */
#define GPIO_PIN_01                 (0x0002U)  /*!< Pin 01 selected   */
#define GPIO_PIN_02                 (0x0004U)  /*!< Pin 02 selected   */
#define GPIO_PIN_03                 (0x0008U)  /*!< Pin 03 selected   */
#define GPIO_PIN_04                 (0x0010U)  /*!< Pin 04 selected   */
#define GPIO_PIN_05                 (0x0020U)  /*!< Pin 05 selected   */
#define GPIO_PIN_06                 (0x0040U)  /*!< Pin 06 selected   */
#define GPIO_PIN_07                 (0x0080U)  /*!< Pin 07 selected   */
#define GPIO_PIN_08                 (0x0100U)  /*!< Pin 08 selected   */
#define GPIO_PIN_09                 (0x0200U)  /*!< Pin 09 selected   */
#define GPIO_PIN_10                 (0x0400U)  /*!< Pin 10 selected   */
#define GPIO_PIN_11                 (0x0800U)  /*!< Pin 11 selected   */
#define GPIO_PIN_12                 (0x1000U)  /*!< Pin 12 selected   */
#define GPIO_PIN_13                 (0x2000U)  /*!< Pin 13 selected   */
#define GPIO_PIN_14                 (0x4000U)  /*!< Pin 14 selected   */
#define GPIO_PIN_15                 (0x8000U)  /*!< Pin 15 selected   */
#define GPIO_PIN_ALL                (0xFFFFU)  /*!< All pins selected */

#define GPIO_PIN_MASK               (0xFFFFU)  /*!< PIN mask for assert test */

/**
 * @}
 */

/** @defgroup GPIO_Port_source GPIO port source
  * @{
  */
#define GPIO_PORT_A                 (0x00U)  /*!< Port A selected  */
#define GPIO_PORT_B                 (0x01U)  /*!< Port B selected  */
#define GPIO_PORT_C                 (0x02U)  /*!< Port C selected  */
#define GPIO_PORT_D                 (0x03U)  /*!< Port D selected  */
#define GPIO_PORT_E                 (0x04U)  /*!< Port E selected  */
#define GPIO_PORT_F                 (0x05U)  /*!< Port F selected  */
#define GPIO_PORT_G                 (0x06U)  /*!< Port G selected  */
#define GPIO_PORT_H                 (0x07U)  /*!< Port H selected  */
#define GPIO_PORT_I                 (0x08U)  /*!< Port I selected  */
/**
 * @}
 */

/** @defgroup GPIO_Port_index GPIO port index
 * @{
 */
#define GPIO_PORTA_IDX              (0x0001U)
#define GPIO_PORTB_IDX              (0x0002U)
#define GPIO_PORTC_IDX              (0x0004U)
#define GPIO_PORTD_IDX              (0x0008U)
#define GPIO_PORTE_IDX              (0x0010U)
#define GPIO_PORTF_IDX              (0x0020U)
#define GPIO_PORTG_IDX              (0x0040U)
#define GPIO_PORTH_IDX              (0x0080U)
#define GPIO_PORTI_IDX              (0x0100U)
#define GPIO_PORT_ALL               (0x01FFU)

#define GPIO_PORT_MASK              (0x01FFU)
/**
 * @}
 */

/**
 * @}
 */

/** @defgroup GPIO_function_selection_define GPIO function selection
 * @{
 */
/** @defgroup GPIO_PinFunction0 GPIO Function 0 selection
 * @{
 */
#define GPIO_FUNC_0                 (0x00U)
#define GPIO_FUNC_0_GPO             (GPIO_FUNC_0)     /* GPO function */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction1 GPIO Function 1 selection
 * @{
 */
#define GPIO_FUNC_1                 (0x01U)
#define GPIO_FUNC_1_FCMREF          (GPIO_FUNC_1)   /*!< Reference clock input for FCM */
#define GPIO_FUNC_1_CTCREF          (GPIO_FUNC_1)   /*!< Reference clock input for internal CTC */
#define GPIO_FUNC_1_RTCOUT          (GPIO_FUNC_1)   /*!< RTC 1Hz output */
#define GPIO_FUNC_1_VCOUT           (GPIO_FUNC_1)   /*!< Voltage comparator output */
#define GPIO_FUNC_1_ADTRG           (GPIO_FUNC_1)   /*!< ADC external trigger */
#define GPIO_FUNC_1_MCO             (GPIO_FUNC_1)   /*!< Clock output */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction2 GPIO Function 2 selection
 * @{
 */
#define GPIO_FUNC_2                 (0x02U)
#define GPIO_FUNC_2_TIM41           (GPIO_FUNC_2)   /*!< TMR4 unit */
#define GPIO_FUNC_2_TIM41_PCT       (GPIO_FUNC_2)   /*!< TMR4 unit 1 basetimer count direction indicator */
#define GPIO_FUNC_2_TIM41_ADSM      (GPIO_FUNC_2)   /*!< TMR4 unit 1 special event */
#define GPIO_FUNC_2_TIM41_CLK       (GPIO_FUNC_2)   /*!< TMR4 unit 1 clock input */
#define GPIO_FUNC_2_TIM41_OUH       (GPIO_FUNC_2)   /*!< TMR4 unit 1 U-phase output high */
#define GPIO_FUNC_2_TIM41_OUL       (GPIO_FUNC_2)   /*!< TMR4 unit 1 U-phase output low */
#define GPIO_FUNC_2_TIM41_OVH       (GPIO_FUNC_2)   /*!< TMR4 unit 1 V-phase output high */
#define GPIO_FUNC_2_TIM41_OVL       (GPIO_FUNC_2)   /*!< TMR4 unit 1 V-phase output low */
#define GPIO_FUNC_2_TIM41_OWH       (GPIO_FUNC_2)   /*!< TMR4 unit 1 W-phase output high */
#define GPIO_FUNC_2_TIM41_OWL       (GPIO_FUNC_2)   /*!< TMR4 unit 1 W-phase output low */

#define GPIO_FUNC_2_TIM42           (GPIO_FUNC_2)   /*!< TMR4 unit */
#define GPIO_FUNC_2_TIM42_PCT       (GPIO_FUNC_2)   /*!< TMR4 unit 2 basetimer count direction indicator */
#define GPIO_FUNC_2_TIM42_ADSM      (GPIO_FUNC_2)   /*!< TMR4 unit 2 special event */
#define GPIO_FUNC_2_TIM42_CLK       (GPIO_FUNC_2)   /*!< TMR4 unit 2 clock input */
#define GPIO_FUNC_2_TIM42_OUH       (GPIO_FUNC_2)   /*!< TMR4 unit 2 U-phase output high */
#define GPIO_FUNC_2_TIM42_OUL       (GPIO_FUNC_2)   /*!< TMR4 unit 2 U-phase output low */
#define GPIO_FUNC_2_TIM42_OVH       (GPIO_FUNC_2)   /*!< TMR4 unit 2 V-phase output high */
#define GPIO_FUNC_2_TIM42_OVL       (GPIO_FUNC_2)   /*!< TMR4 unit 2 V-phase output low */
#define GPIO_FUNC_2_TIM42_OWH       (GPIO_FUNC_2)   /*!< TMR4 unit 2 W-phase output high */
#define GPIO_FUNC_2_TIM42_OWL       (GPIO_FUNC_2)   /*!< TMR4 unit 2 W-phase output low */

#define GPIO_FUNC_2_TIM43           (GPIO_FUNC_2)   /*!< TMR4 unit */
#define GPIO_FUNC_2_TIM43_PCT       (GPIO_FUNC_2)   /*!< TMR4 unit 3 basetimer count direction indicator */
#define GPIO_FUNC_2_TIM43_ADSM      (GPIO_FUNC_2)   /*!< TMR4 unit 3 special event */
#define GPIO_FUNC_2_TIM43_CLK       (GPIO_FUNC_2)   /*!< TMR4 unit 3 clock input */
#define GPIO_FUNC_2_TIM43_OUH       (GPIO_FUNC_2)   /*!< TMR4 unit 3 U-phase output high */
#define GPIO_FUNC_2_TIM43_OUL       (GPIO_FUNC_2)   /*!< TMR4 unit 3 U-phase output low */
#define GPIO_FUNC_2_TIM43_OVH       (GPIO_FUNC_2)   /*!< TMR4 unit 3 V-phase output high */
#define GPIO_FUNC_2_TIM43_OVL       (GPIO_FUNC_2)   /*!< TMR4 unit 3 V-phase output low */
#define GPIO_FUNC_2_TIM43_OWH       (GPIO_FUNC_2)   /*!< TMR4 unit 3 W-phase output high */
#define GPIO_FUNC_2_TIM43_OWL       (GPIO_FUNC_2)   /*!< TMR4 unit 3 W-phase output low */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction3 GPIO Function 3 selection
 * @{
 */
#define GPIO_FUNC_3                 (0x03U)
#define GPIO_FUNC_3_TIM6_TRIG       (GPIO_FUNC_3)   /*!< TMR6 trigger */
#define GPIO_FUNC_3_TIM6_TRIGA      (GPIO_FUNC_3)   /*!< TMR6 trigger A */
#define GPIO_FUNC_3_TIM6_TRIGB      (GPIO_FUNC_3)   /*!< TMR6 trigger B */
#define GPIO_FUNC_3_TIM6_TRIGC      (GPIO_FUNC_3)   /*!< TMR6 trigger C */
#define GPIO_FUNC_3_TIM6_TRIGD      (GPIO_FUNC_3)   /*!< TMR6 trigger D */

#define GPIO_FUNC_3_TIM61           (GPIO_FUNC_3)   /*!< TMR6 unit 1 */
#define GPIO_FUNC_3_TIM61_PWMA      (GPIO_FUNC_3)   /*!< TMR6 unit 1 channel A PWM output */
#define GPIO_FUNC_3_TIM61_PWMB      (GPIO_FUNC_3)   /*!< TMR6 unit 1 channel B PWM output */

#define GPIO_FUNC_3_TIM62           (GPIO_FUNC_3)   /*!< TMR6 unit 2 */
#define GPIO_FUNC_3_TIM62_PWMA      (GPIO_FUNC_3)   /*!< TMR6 unit 2 channel A PWM output */
#define GPIO_FUNC_3_TIM62_PWMB      (GPIO_FUNC_3)   /*!< TMR6 unit 2 channel B PWM output */

#define GPIO_FUNC_3_TIM63           (GPIO_FUNC_3)   /*!< TMR6 unit 3 */
#define GPIO_FUNC_3_TIM63_PWMA      (GPIO_FUNC_3)   /*!< TMR6 unit 3 channel A PWM output */
#define GPIO_FUNC_3_TIM63_PWMB      (GPIO_FUNC_3)   /*!< TMR6 unit 3 channel B PWM output */

#define GPIO_FUNC_3_TIM64           (GPIO_FUNC_3)   /*!< TMR6 unit 4 */
#define GPIO_FUNC_3_TIM64_PWMA      (GPIO_FUNC_3)   /*!< TMR6 unit 4 channel A PWM output */
#define GPIO_FUNC_3_TIM64_PWMB      (GPIO_FUNC_3)   /*!< TMR6 unit 4 channel B PWM output */

#define GPIO_FUNC_3_TIM65           (GPIO_FUNC_3)   /*!< TMR6 unit 5 */
#define GPIO_FUNC_3_TIM65_PWMA      (GPIO_FUNC_3)   /*!< TMR6 unit 5 channel A PWM output */
#define GPIO_FUNC_3_TIM65_PWMB      (GPIO_FUNC_3)   /*!< TMR6 unit 5 channel B PWM output */

#define GPIO_FUNC_3_TIM66           (GPIO_FUNC_3)   /*!< TMR6 unit 6 */
#define GPIO_FUNC_3_TIM66_PWMA      (GPIO_FUNC_3)   /*!< TMR6 unit 6 channel A PWM output */
#define GPIO_FUNC_3_TIM66_PWMB      (GPIO_FUNC_3)   /*!< TMR6 unit 6 channel B PWM output */

#define GPIO_FUNC_3_TIM67           (GPIO_FUNC_3)   /*!< TMR6 unit 7 */
#define GPIO_FUNC_3_TIM67_PWMA      (GPIO_FUNC_3)   /*!< TMR6 unit 7 channel A PWM output */
#define GPIO_FUNC_3_TIM67_PWMB      (GPIO_FUNC_3)   /*!< TMR6 unit 7 channel B PWM output */

#define GPIO_FUNC_3_TIM68           (GPIO_FUNC_3)   /*!< TMR6 unit 8 */
#define GPIO_FUNC_3_TIM68_PWMA      (GPIO_FUNC_3)   /*!< TMR6 unit 8 channel A PWM output */
#define GPIO_FUNC_3_TIM68_PWMB      (GPIO_FUNC_3)   /*!< TMR6 unit 8 channel B PWM output */

/**
 * @}
 */

/** @defgroup GPIO_PinFunction4     GPIO Function 4 selection
 * @{
 */
#define GPIO_FUNC_4                 (0x04U)
#define GPIO_FUNC_4_TIMA1           (GPIO_FUNC_4)   /*!< TMRA unit 1 */
#define GPIO_FUNC_4_TIMA1_TRIG      (GPIO_FUNC_4)   /*!< TMRA unit 1 trigger */
#define GPIO_FUNC_4_TIMA1_PWM1      (GPIO_FUNC_4)   /*!< TMRA unit 1 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA1_PWM2      (GPIO_FUNC_4)   /*!< TMRA unit 1 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA1_PWM3      (GPIO_FUNC_4)   /*!< TMRA unit 1 channel 3 PWM output */
#define GPIO_FUNC_4_TIMA1_PWM4      (GPIO_FUNC_4)   /*!< TMRA unit 1 channel 4 PWM output */

#define GPIO_FUNC_4_TIMA2_PWM       (GPIO_FUNC_4)   /*!< TMRA unit 2 PWM */
#define GPIO_FUNC_4_TIMA2_PWM1      (GPIO_FUNC_4)   /*!< TMRA unit 2 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA2_PWM2      (GPIO_FUNC_4)   /*!< TMRA unit 2 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA2_PWM3      (GPIO_FUNC_4)   /*!< TMRA unit 2 channel 3 PWM output */
#define GPIO_FUNC_4_TIMA2_PWM4      (GPIO_FUNC_4)   /*!< TMRA unit 2 channel 4 PWM output */

#define GPIO_FUNC_4_TIMA3           (GPIO_FUNC_4)   /*!< TMRA unit 3 */
#define GPIO_FUNC_4_TIMA3_TRIG      (GPIO_FUNC_4)   /*!< TMRA unit 3 trigger */
#define GPIO_FUNC_4_TIMA3_PWM1      (GPIO_FUNC_4)   /*!< TMRA unit 3 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA3_PWM2      (GPIO_FUNC_4)   /*!< TMRA unit 3 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA3_PWM3      (GPIO_FUNC_4)   /*!< TMRA unit 3 channel 3 PWM output */
#define GPIO_FUNC_4_TIMA3_PWM4      (GPIO_FUNC_4)   /*!< TMRA unit 3 channel 4 PWM output */

#define GPIO_FUNC_4_TIMA4           (GPIO_FUNC_4)   /*!< TMRA unit 4 */
#define GPIO_FUNC_4_TIMA4_TRIG      (GPIO_FUNC_4)   /*!< TMRA unit 4 trigger */
#define GPIO_FUNC_4_TIMA4_PWM1      (GPIO_FUNC_4)   /*!< TMRA unit 4 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA4_PWM2      (GPIO_FUNC_4)   /*!< TMRA unit 4 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA4_PWM3      (GPIO_FUNC_4)   /*!< TMRA unit 4 channel 3 PWM output */
#define GPIO_FUNC_4_TIMA4_PWM4      (GPIO_FUNC_4)   /*!< TMRA unit 4 channel 4 PWM output */

#define GPIO_FUNC_4_TIMA6           (GPIO_FUNC_4)   /*!< TMRA unit 6 */
#define GPIO_FUNC_4_TIMA6_PWM1      (GPIO_FUNC_4)   /*!< TMRA unit 6 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA6_PWM2      (GPIO_FUNC_4)   /*!< TMRA unit 6 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA6_PWM3      (GPIO_FUNC_4)   /*!< TMRA unit 6 channel 3 PWM output */
#define GPIO_FUNC_4_TIMA6_PWM4      (GPIO_FUNC_4)   /*!< TMRA unit 6 channel 4 PWM output */

#define GPIO_FUNC_4_TIMA7           (GPIO_FUNC_4)   /*!< TMRA unit 7 */
#define GPIO_FUNC_4_TIMA7_PWM1      (GPIO_FUNC_4)   /*!< TMRA unit 7 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA7_PWM2      (GPIO_FUNC_4)   /*!< TMRA unit 7 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA7_PWM3      (GPIO_FUNC_4)   /*!< TMRA unit 7 channel 3 PWM output */
#define GPIO_FUNC_4_TIMA7_PWM4      (GPIO_FUNC_4)   /*!< TMRA unit 7 channel 4 PWM output */

#define GPIO_FUNC_4_TIMA8           (GPIO_FUNC_4)   /*!< TMRA unit 8 */
#define GPIO_FUNC_4_TIMA8_PWM1      (GPIO_FUNC_4)   /*!< TMRA unit 8 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA8_PWM2      (GPIO_FUNC_4)   /*!< TMRA unit 8 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA8_PWM3      (GPIO_FUNC_4)   /*!< TMRA unit 8 channel 3 PWM output */
#define GPIO_FUNC_4_TIMA8_PWM4      (GPIO_FUNC_4)   /*!< TMRA unit 8 channel 4 PWM output */

#define GPIO_FUNC_4_TIMA9           (GPIO_FUNC_4)   /*!< TMRA unit 9 */
#define GPIO_FUNC_4_TIMA9_PWM1      (GPIO_FUNC_4)   /*!< TMRA unit 9 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA9_PWM2      (GPIO_FUNC_4)   /*!< TMRA unit 9 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA9_PWM3      (GPIO_FUNC_4)   /*!< TMRA unit 9 channel 3 PWM output */
#define GPIO_FUNC_4_TIMA9_PWM4      (GPIO_FUNC_4)   /*!< TMRA unit 9 channel 4 PWM output */

#define GPIO_FUNC_4_TIMA10          (GPIO_FUNC_4)   /*!< TMRA unit 10 */
#define GPIO_FUNC_4_TIMA10_PWM1     (GPIO_FUNC_4)   /*!< TMRA unit 10 channel 1 PWM output */
#define GPIO_FUNC_4_TIMA10_PWM2     (GPIO_FUNC_4)   /*!< TMRA unit 10 channel 2 PWM output */
#define GPIO_FUNC_4_TIMA10_PWM3     (GPIO_FUNC_4)   /*!< TMRA unit 10 channel 3 PWM output */
#define GPIO_FUNC_4_TIMA10_PWM4     (GPIO_FUNC_4)   /*!< TMRA unit 10 channel 4 PWM output */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction5 GPIO Function 5 selection
 * @{
 */
#define GPIO_FUNC_5                 (0x05U)
#define GPIO_FUNC_5_TIMA2_TRIG      (GPIO_FUNC_5)   /*!< TMRA unit 2 trigger */

#define GPIO_FUNC_5_TIMA3           (GPIO_FUNC_5)   /*!< TMRA unit 3 */
#define GPIO_FUNC_5_TIMA3_TRIG      (GPIO_FUNC_5)   /*!< TMRA unit 3 trigger */
#define GPIO_FUNC_5_TIMA3_PWM1      (GPIO_FUNC_5)   /*!< TMRA unit 3 channel 1 PWM output */
#define GPIO_FUNC_5_TIMA3_PWM2      (GPIO_FUNC_5)   /*!< TMRA unit 3 channel 2 PWM output */
#define GPIO_FUNC_5_TIMA3_PWM3      (GPIO_FUNC_5)   /*!< TMRA unit 3 channel 3 PWM output */
#define GPIO_FUNC_5_TIMA3_PWM4      (GPIO_FUNC_5)   /*!< TMRA unit 3 channel 4 PWM output */

#define GPIO_FUNC_5_TIMA4           (GPIO_FUNC_5)   /*!< TMRA unit 4 */
#define GPIO_FUNC_5_TIMA4_PWM1      (GPIO_FUNC_5)   /*!< TMRA unit 4 channel 1 PWM output */
#define GPIO_FUNC_5_TIMA4_PWM2      (GPIO_FUNC_5)   /*!< TMRA unit 4 channel 2 PWM output */
#define GPIO_FUNC_5_TIMA4_PWM3      (GPIO_FUNC_5)   /*!< TMRA unit 4 channel 3 PWM output */
#define GPIO_FUNC_5_TIMA4_PWM4      (GPIO_FUNC_5)   /*!< TMRA unit 4 channel 4 PWM output */

#define GPIO_FUNC_5_TIMA5           (GPIO_FUNC_5)   /*!< TMRA unit 5 */
#define GPIO_FUNC_5_TIMA5_TRIG      (GPIO_FUNC_5)   /*!< TMRA unit 5 trigger */
#define GPIO_FUNC_5_TIMA5_PWM1      (GPIO_FUNC_5)   /*!< TMRA unit 5 channel 1 PWM output */
#define GPIO_FUNC_5_TIMA5_PWM2      (GPIO_FUNC_5)   /*!< TMRA unit 5 channel 2 PWM output */
#define GPIO_FUNC_5_TIMA5_PWM3      (GPIO_FUNC_5)   /*!< TMRA unit 5 channel 3 PWM output */
#define GPIO_FUNC_5_TIMA5_PWM4      (GPIO_FUNC_5)   /*!< TMRA unit 5 channel 4 PWM output */

#define GPIO_FUNC_5_TIMA6           (GPIO_FUNC_5)   /*!< TMRA unit 6 */
#define GPIO_FUNC_5_TIMA6_TRIG      (GPIO_FUNC_5)   /*!< TMRA unit 6 trigger */
#define GPIO_FUNC_5_TIMA6_PWM1      (GPIO_FUNC_5)   /*!< TMRA unit 6 channel 1 PWM output */
#define GPIO_FUNC_5_TIMA6_PWM2      (GPIO_FUNC_5)   /*!< TMRA unit 6 channel 2 PWM output */
#define GPIO_FUNC_5_TIMA6_PWM3      (GPIO_FUNC_5)   /*!< TMRA unit 6 channel 3 PWM output */
#define GPIO_FUNC_5_TIMA6_PWM4      (GPIO_FUNC_5)   /*!< TMRA unit 6 channel 4 PWM output */

#define GPIO_FUNC_5_TIMA9           (GPIO_FUNC_5)   /*!< TMRA unit 9 */
#define GPIO_FUNC_5_TIMA9_TRIG      (GPIO_FUNC_5)   /*!< TMRA unit 9 trigger */
#define GPIO_FUNC_5_TIMA9_PWM1      (GPIO_FUNC_5)   /*!< TMRA unit 9 channel 1 PWM output */
#define GPIO_FUNC_5_TIMA9_PWM2      (GPIO_FUNC_5)   /*!< TMRA unit 9 channel 2 PWM output */
#define GPIO_FUNC_5_TIMA9_PWM3      (GPIO_FUNC_5)   /*!< TMRA unit 9 channel 3 PWM output */
#define GPIO_FUNC_5_TIMA9_PWM4      (GPIO_FUNC_5)   /*!< TMRA unit 9 channel 4 PWM output */

#define GPIO_FUNC_5_TIMA11_PWM      (GPIO_FUNC_5)   /*!< TMRA unit 11 PWM */
#define GPIO_FUNC_5_TIMA11_PWM1     (GPIO_FUNC_5)   /*!< TMRA unit 11 channel 1 PWM output */
#define GPIO_FUNC_5_TIMA11_PWM2     (GPIO_FUNC_5)   /*!< TMRA unit 11 channel 2 PWM output */
#define GPIO_FUNC_5_TIMA11_PWM3     (GPIO_FUNC_5)   /*!< TMRA unit 11 channel 3 PWM output */
#define GPIO_FUNC_5_TIMA11_PWM4     (GPIO_FUNC_5)   /*!< TMRA unit 11 channel 4 PWM output */

#define GPIO_FUNC_5_TIMA12_PWM      (GPIO_FUNC_5)   /*!< TMRA unit 12 PWM */
#define GPIO_FUNC_5_TIMA12_PWM1     (GPIO_FUNC_5)   /*!< TMRA unit 12 channel 1 PWM output */
#define GPIO_FUNC_5_TIMA12_PWM2     (GPIO_FUNC_5)   /*!< TMRA unit 12 channel 2 PWM output */
#define GPIO_FUNC_5_TIMA12_PWM3     (GPIO_FUNC_5)   /*!< TMRA unit 12 channel 3 PWM output */
#define GPIO_FUNC_5_TIMA12_PWM4     (GPIO_FUNC_5)   /*!< TMRA unit 12 channel 4 PWM output */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction6 GPIO Function 6 selection
 * @{
 */
#define GPIO_FUNC_6                 (0x06U)
#define GPIO_FUNC_6_TIMA1_TRIG      (GPIO_FUNC_6)   /*!< TMRA unit 1 trigger */
#define GPIO_FUNC_6_TIMA2_TRIG      (GPIO_FUNC_6)   /*!< TMRA unit 2 trigger */
#define GPIO_FUNC_6_TIMA3_TRIG      (GPIO_FUNC_6)   /*!< TMRA unit 3 trigger */
#define GPIO_FUNC_6_TIMA4_TRIG      (GPIO_FUNC_6)   /*!< TMRA unit 4 trigger */
#define GPIO_FUNC_6_TIMA6_TRIG      (GPIO_FUNC_6)   /*!< TMRA unit 6 trigger */
#define GPIO_FUNC_6_TIMA7_TRIG      (GPIO_FUNC_6)   /*!< TMRA unit 7 trigger */
#define GPIO_FUNC_6_TIMA8_TRIG      (GPIO_FUNC_6)   /*!< TMRA unit 8 trigger */
#define GPIO_FUNC_6_TIMA11_TRIG     (GPIO_FUNC_6)   /*!< TMRA unit 11 trigger */
#define GPIO_FUNC_6_TIMA12_TRIG     (GPIO_FUNC_6)   /*!< TMRA unit 12 trigger */

#define GPIO_FUNC_6_TIMA5           (GPIO_FUNC_6)   /*!< TMRA unit 5 */
#define GPIO_FUNC_6_TIMA5_TRIG      (GPIO_FUNC_6)   /*!< TMRA unit 5 trigger */
#define GPIO_FUNC_6_TIMA5_PWM1      (GPIO_FUNC_6)   /*!< TMRA unit 5 channel 1 PWM output */
#define GPIO_FUNC_6_TIMA5_PWM2      (GPIO_FUNC_6)   /*!< TMRA unit 5 channel 2 PWM output */
#define GPIO_FUNC_6_TIMA5_PWM3      (GPIO_FUNC_6)   /*!< TMRA unit 5 channel 3 PWM output */
#define GPIO_FUNC_6_TIMA5_PWM4      (GPIO_FUNC_6)   /*!< TMRA unit 5 channel 4 PWM output */

#define GPIO_FUNC_6_TIMA9           (GPIO_FUNC_6)   /*!< TMRA unit 9 */
#define GPIO_FUNC_6_TIMA9_TRIG      (GPIO_FUNC_6)   /*!< TMRA unit 9 trigger */
#define GPIO_FUNC_6_TIMA9_PWM1      (GPIO_FUNC_6)   /*!< TMRA unit 9 channel 1 PWM output */
#define GPIO_FUNC_6_TIMA9_PWM2      (GPIO_FUNC_6)   /*!< TMRA unit 9 channel 2 PWM output */
#define GPIO_FUNC_6_TIMA9_PWM3      (GPIO_FUNC_6)   /*!< TMRA unit 9 channel 3 PWM output */
#define GPIO_FUNC_6_TIMA9_PWM4      (GPIO_FUNC_6)   /*!< TMRA unit 9 channel 4 PWM output */

#define GPIO_FUNC_6_TIMA10          (GPIO_FUNC_6)   /*!< TMRA unit 10 */
#define GPIO_FUNC_6_TIMA10_TRIG     (GPIO_FUNC_6)   /*!< TMRA unit 10 trigger */
#define GPIO_FUNC_6_TIMA10_PWM1     (GPIO_FUNC_6)   /*!< TMRA unit 10 channel 1 PWM output */
#define GPIO_FUNC_6_TIMA10_PWM2     (GPIO_FUNC_6)   /*!< TMRA unit 10 channel 2 PWM output */
#define GPIO_FUNC_6_TIMA10_PWM3     (GPIO_FUNC_6)   /*!< TMRA unit 10 channel 3 PWM output */
#define GPIO_FUNC_6_TIMA10_PWM4     (GPIO_FUNC_6)   /*!< TMRA unit 10 channel 4 PWM output */

#define GPIO_FUNC_6_TIM65_PWMA      (GPIO_FUNC_6)   /*!< TMR6 unit 5 channel A PWM output */
#define GPIO_FUNC_6_TIM66_PWMA      (GPIO_FUNC_6)   /*!< TMR6 unit 6 channel A PWM output */
#define GPIO_FUNC_6_TIM67_PWMA      (GPIO_FUNC_6)   /*!< TMR6 unit 7 channel A PWM output */
#define GPIO_FUNC_6_TIM68_PWMA      (GPIO_FUNC_6)   /*!< TMR6 unit 8 channel A PWM output */

#define GPIO_FUNC_6_EMB_PORT        (GPIO_FUNC_6)   /*!< EMB port */
#define GPIO_FUNC_6_EMB_PORT0       (GPIO_FUNC_6)   /*!< EMB port 0 */
#define GPIO_FUNC_6_EMB_PORT1       (GPIO_FUNC_6)   /*!< EMB port 1 */
#define GPIO_FUNC_6_EMB_PORT2       (GPIO_FUNC_6)   /*!< EMB port 2 */
#define GPIO_FUNC_6_EMB_PORT3       (GPIO_FUNC_6)   /*!< EMB port 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction7 GPIO Function 7 selection
 * @{
 */
#define GPIO_FUNC_7                 (0x07U)
#define GPIO_FUNC_7_USART1          (GPIO_FUNC_7)     /*!< USART1 */
#define GPIO_FUNC_7_USART1_CK       (GPIO_FUNC_7)     /*!< USART1 CK */
#define GPIO_FUNC_7_USART1_CTS      (GPIO_FUNC_7)     /*!< USART1 CTS */
#define GPIO_FUNC_7_USART1_RTS      (GPIO_FUNC_7)     /*!< USART1 RTS */

#define GPIO_FUNC_7_USART2          (GPIO_FUNC_7)     /*!< USART2 */
#define GPIO_FUNC_7_USART2_CK       (GPIO_FUNC_7)     /*!< USART2 CK */
#define GPIO_FUNC_7_USART2_CTS      (GPIO_FUNC_7)     /*!< USART2 CTS */
#define GPIO_FUNC_7_USART2_RTS      (GPIO_FUNC_7)     /*!< USART2 RTS */

#define GPIO_FUNC_7_USART3          (GPIO_FUNC_7)     /*!< USART3 */
#define GPIO_FUNC_7_USART3_CK       (GPIO_FUNC_7)     /*!< USART3 CK */
#define GPIO_FUNC_7_USART3_CTS      (GPIO_FUNC_7)     /*!< USART3 CTS */
#define GPIO_FUNC_7_USART3_RTS      (GPIO_FUNC_7)     /*!< USART3 RTS */

#define GPIO_FUNC_7_USART4          (GPIO_FUNC_7)     /*!< USART4 */
#define GPIO_FUNC_7_USART4_CK       (GPIO_FUNC_7)     /*!< USART4 CK */
#define GPIO_FUNC_7_USART4_CTS      (GPIO_FUNC_7)     /*!< USART4 CTS */
#define GPIO_FUNC_7_USART4_RTS      (GPIO_FUNC_7)     /*!< USART4 RTS */

#define GPIO_FUNC_7_USART5          (GPIO_FUNC_7)     /*!< USART5 */
#define GPIO_FUNC_7_USART5_CK       (GPIO_FUNC_7)     /*!< USART5 CK */
#define GPIO_FUNC_7_USART5_CTS      (GPIO_FUNC_7)     /*!< USART5 CTS */
#define GPIO_FUNC_7_USART5_RTS      (GPIO_FUNC_7)     /*!< USART5 RTS */

#define GPIO_FUNC_7_USART6          (GPIO_FUNC_7)     /*!< USART6 */
#define GPIO_FUNC_7_USART6_CK       (GPIO_FUNC_7)     /*!< USART6 CK */
#define GPIO_FUNC_7_USART6_CTS      (GPIO_FUNC_7)     /*!< USART6 CTS */
#define GPIO_FUNC_7_USART6_RTS      (GPIO_FUNC_7)     /*!< USART6 RTS */

#define GPIO_FUNC_7_USART7          (GPIO_FUNC_7)     /*!< USART7 */
#define GPIO_FUNC_7_USART7_CK       (GPIO_FUNC_7)     /*!< USART7 CK */
#define GPIO_FUNC_7_USART7_CTS      (GPIO_FUNC_7)     /*!< USART7 CTS */
#define GPIO_FUNC_7_USART7_RTS      (GPIO_FUNC_7)     /*!< USART7 RTS */

#define GPIO_FUNC_7_USART8          (GPIO_FUNC_7)     /*!< USART8 */
#define GPIO_FUNC_7_USART8_CK       (GPIO_FUNC_7)     /*!< USART8 CK */
#define GPIO_FUNC_7_USART8_CTS      (GPIO_FUNC_7)     /*!< USART8 CTS */
#define GPIO_FUNC_7_USART8_RTS      (GPIO_FUNC_7)     /*!< USART8 RTS */

#define GPIO_FUNC_7_USART9          (GPIO_FUNC_7)     /*!< USART9 */
#define GPIO_FUNC_7_USART9_CK       (GPIO_FUNC_7)     /*!< USART9 CK */
#define GPIO_FUNC_7_USART9_CTS      (GPIO_FUNC_7)     /*!< USART9 CTS */
#define GPIO_FUNC_7_USART9_RTS      (GPIO_FUNC_7)     /*!< USART9 RTS */

#define GPIO_FUNC_7_USART10         (GPIO_FUNC_7)     /*!< USART10 */
#define GPIO_FUNC_7_USART10_CK      (GPIO_FUNC_7)     /*!< USART10 CK */
#define GPIO_FUNC_7_USART10_CTS     (GPIO_FUNC_7)     /*!< USART10 CTS */
#define GPIO_FUNC_7_USART10_RTS     (GPIO_FUNC_7)     /*!< USART10 RTS */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction8 GPIO Function 8 selection
 * @{
 */
#define GPIO_FUNC_8                 (0x08U)
#define GPIO_FUNC_8_KEYSCAN         (GPIO_FUNC_8)     /*!< KEYSCAN */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction9 GPIO Function 9 selection
 * @{
 */
#define GPIO_FUNC_9                 (0x09U)
#define GPIO_FUNC_9_SDIO            (GPIO_FUNC_9)     /*!< SDIO */
#define GPIO_FUNC_9_SDIO1           (GPIO_FUNC_9)     /*!< SDIO1 */
#define GPIO_FUNC_9_SDIO1_WP        (GPIO_FUNC_9)     /*!< SDIO1 WP */
#define GPIO_FUNC_9_SDIO1_CD        (GPIO_FUNC_9)     /*!< SDIO1 CD */
#define GPIO_FUNC_9_SDIO1_CMD       (GPIO_FUNC_9)     /*!< SDIO1 CMD */
#define GPIO_FUNC_9_SDIO1_CK        (GPIO_FUNC_9)     /*!< SDIO1 CK */
#define GPIO_FUNC_9_SDIO1_DATA      (GPIO_FUNC_9)     /*!< SDIO1 data bus */

#define GPIO_FUNC_9_SDIO2           (GPIO_FUNC_9)     /*!< SDIO2 */
#define GPIO_FUNC_9_SDIO2_WP        (GPIO_FUNC_9)     /*!< SDIO2 WP */
#define GPIO_FUNC_9_SDIO2_CD        (GPIO_FUNC_9)     /*!< SDIO2 CD */
#define GPIO_FUNC_9_SDIO2_CMD       (GPIO_FUNC_9)     /*!< SDIO2 CMD */
#define GPIO_FUNC_9_SDIO2_CK        (GPIO_FUNC_9)     /*!< SDIO2 CK */
#define GPIO_FUNC_9_SDIO2_DATA      (GPIO_FUNC_9)     /*!< SDIO2 data bus */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction10 GPIO Function 10 selection
 * @{
 */
#define GPIO_FUNC_10                    (0x0AU)
#define GPIO_FUNC_10_USBF               (GPIO_FUNC_10)    /*!< USB Full-speed */
#define GPIO_FUNC_10_USBF_DRVVBUS       (GPIO_FUNC_10)    /*!< USB Full-speed host VBUS ctrl */
#define GPIO_FUNC_10_USBF_SOF           (GPIO_FUNC_10)    /*!< USB Full-speed SOF */
#define GPIO_FUNC_10_USBF_VBUS          (GPIO_FUNC_10)    /*!< USB Full-speed slave VBUS */
#define GPIO_FUNC_10_USBF_ID            (GPIO_FUNC_10)    /*!< USB Full-speed */

#define GPIO_FUNC_10_USBH               (GPIO_FUNC_10)    /*!< USB High-speed */
#define GPIO_FUNC_10_USBH_ULPI_DIR      (GPIO_FUNC_10)    /*!< USB High-speed ULPI DIR */
#define GPIO_FUNC_10_USBH_ULPI_STP      (GPIO_FUNC_10)    /*!< USB High-speed ULPI STP */
#define GPIO_FUNC_10_USBH_ULPI_NXT      (GPIO_FUNC_10)    /*!< USB High-speed ULPI NXT */
#define GPIO_FUNC_10_USBH_ULPI_CK       (GPIO_FUNC_10)    /*!< USB High-speed ULPI CK */
#define GPIO_FUNC_10_USBH_ULPI_DRVVBUS  (GPIO_FUNC_10)    /*!< USB High-speed host VBUS ctrl */
#define GPIO_FUNC_10_USBH_ULPI_DATA     (GPIO_FUNC_10)    /*!< USB High-speed ULPI data bus */

#define GPIO_FUNC_10_TIM22_PWM          (GPIO_FUNC_10)    /*!< TMR2 unit 2 PWM */
#define GPIO_FUNC_10_TIM22_PWMA         (GPIO_FUNC_10)    /*!< TMR2 unit 2 channel A PWM */
#define GPIO_FUNC_10_TIM22_PWMB         (GPIO_FUNC_10)    /*!< TMR2 unit 2 channel B PWM */

#define GPIO_FUNC_10_TIM24_PWM          (GPIO_FUNC_10)    /*!< TMR2 unit 4 PWM */
#define GPIO_FUNC_10_TIM24_PWMA         (GPIO_FUNC_10)    /*!< TMR2 unit 4 channel A PWM */
#define GPIO_FUNC_10_TIM24_PWMB         (GPIO_FUNC_10)    /*!< TMR2 unit 4 channel B PWM */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction11 GPIO Function 11 selection
 * @{
 */
#define GPIO_FUNC_11                (0x0BU)
#define GPIO_FUNC_11_ETH            (GPIO_FUNC_11)      /*!< Ethernet */
#define GPIO_FUNC_11_ETH_TXD        (GPIO_FUNC_11)      /*!< ETH TXD */
#define GPIO_FUNC_11_ETH_TXEN       (GPIO_FUNC_11)      /*!< ETH TX enable */
#define GPIO_FUNC_11_ETH_TXCLK      (GPIO_FUNC_11)      /*!< ETH TX clock */
#define GPIO_FUNC_11_ETH_RXD        (GPIO_FUNC_11)      /*!< ETH RXD */
#define GPIO_FUNC_11_ETH_RXER       (GPIO_FUNC_11)      /*!< ETH RX error */
#define GPIO_FUNC_11_ETH_RXCLK      (GPIO_FUNC_11)      /*!< ETH RX clock */
#define GPIO_FUNC_11_ETH_RXDV       (GPIO_FUNC_11)      /*!< ETH RX data valid */
#define GPIO_FUNC_11_ETH_SMI_MDIO   (GPIO_FUNC_11)      /*!< SMI data */
#define GPIO_FUNC_11_ETH_SMI_MDC    (GPIO_FUNC_11)      /*!< SMI clock */
#define GPIO_FUNC_11_ETH_CRS        (GPIO_FUNC_11)      /*!< ETH MII carrier sense */
#define GPIO_FUNC_11_ETH_COL        (GPIO_FUNC_11)      /*!< ETH MII collisioin detected */
#define GPIO_FUNC_11_ETH_PPS_OUT    (GPIO_FUNC_11)      /*!< ETH PPS out */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction12 GPIO Function 12 selection
 * @{
 */
#define GPIO_FUNC_12                (0x0CU)
#define GPIO_FUNC_12_EXMC           (GPIO_FUNC_12)      /*!< Ext. Bus */
#define GPIO_FUNC_12_EXMC_CLE       (GPIO_FUNC_12)      /*!< Ext. Bus NAND CMD latch */
#define GPIO_FUNC_12_EXMC_ALE       (GPIO_FUNC_12)      /*!< Ext. Bus NAND ADDR latch */
#define GPIO_FUNC_12_EXMC_RB        (GPIO_FUNC_12)      /*!< Ext. Bus NAND busy or SRAM wait(RB0) input */
#define GPIO_FUNC_12_EXMC_CE        (GPIO_FUNC_12)      /*!< Ext. Bus chip enable */
#define GPIO_FUNC_12_EXMC_WE        (GPIO_FUNC_12)      /*!< Ext. Bus write enable */
#define GPIO_FUNC_12_EXMC_OE        (GPIO_FUNC_12)      /*!< Ext. Bus output enable */
#define GPIO_FUNC_12_EXMC_BAA       (GPIO_FUNC_12)      /*!< Ext. Bus SRAM BAA */
#define GPIO_FUNC_12_EXMC_ADV       (GPIO_FUNC_12)      /*!< Ext. Bus SRAM ADDR latch */
#define GPIO_FUNC_12_EXMC_CLK       (GPIO_FUNC_12)      /*!< Ext. Bus clock output */
#define GPIO_FUNC_12_EXMC_ADDR      (GPIO_FUNC_12)      /*!< Ext. Bus Addr. Bus */
#define GPIO_FUNC_12_EXMC_DATA      (GPIO_FUNC_12)      /*!< Ext. Bus data Bus */

#define GPIO_FUNC_12_USBH           (GPIO_FUNC_12)      /*!< USB High-speed */
#define GPIO_FUNC_12_USBH_SOF       (GPIO_FUNC_12)      /*!< USB High-speed SOF */
#define GPIO_FUNC_12_USBH_VBUS      (GPIO_FUNC_12)      /*!< USB High-speed slave VBUS */
#define GPIO_FUNC_12_USBH_ID        (GPIO_FUNC_12)      /*!< USB High-speed ID */

#define GPIO_FUNC_12_I2S2_EXCK      (GPIO_FUNC_12)      /*!< I2S2 EXCK */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction13 GPIO Function 13 selection
 * @{
 */
#define GPIO_FUNC_13                (0x0DU)
#define GPIO_FUNC_13_DVP            (GPIO_FUNC_13)      /*!< DVP */
#define GPIO_FUNC_13_DVP_DATA       (GPIO_FUNC_13)      /*!< DVP data bus */
#define GPIO_FUNC_13_DVP_PIXCLK     (GPIO_FUNC_13)      /*!< DVP pix clock */
#define GPIO_FUNC_13_DVP_HSYNC      (GPIO_FUNC_13)      /*!< DVP line sync */
#define GPIO_FUNC_13_DVP_VSYNC      (GPIO_FUNC_13)      /*!< DVP frame sync */

#define GPIO_FUNC_13_EXMC           (GPIO_FUNC_13)      /*!< Ext. Bus */
#define GPIO_FUNC_13_EXMC_A16       (GPIO_FUNC_13)      /*!< Ext. Bus address 16 */
#define GPIO_FUNC_13_EXMC_A17       (GPIO_FUNC_13)      /*!< Ext. Bus address 17 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction14 GPIO Function 14 selection
 * @{
 */
#define GPIO_FUNC_14                (0x0EU)
#define GPIO_FUNC_14_EP             (GPIO_FUNC_14)      /*!< Event Port */
#define GPIO_FUNC_14_EP1            (GPIO_FUNC_14)      /*!< Event Port Group 1 */
#define GPIO_FUNC_14_EP2            (GPIO_FUNC_14)      /*!< Event Port Group 2 */
#define GPIO_FUNC_14_EP3            (GPIO_FUNC_14)      /*!< Event Port Group 3 */
#define GPIO_FUNC_14_EP4            (GPIO_FUNC_14)      /*!< Event Port Group 4 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction15 GPIO Function 15 selection
 * @{
 */
#define GPIO_FUNC_15                (0x0FU)
#define GPIO_FUNC_15_EVENTOUT       (GPIO_FUNC_15)      /*!< Event Out */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction16 GPIO Function 16 selection
 * @{
 */
#define GPIO_FUNC_16                (0x10U)
#define GPIO_FUNC_16_TIM21          (GPIO_FUNC_16)      /*!< TMR2 unit 1 */
#define GPIO_FUNC_16_TIM21_CLKA     (GPIO_FUNC_16)      /*!< TMR2 unit 1 channel A CLK input */
#define GPIO_FUNC_16_TIM21_CLKB     (GPIO_FUNC_16)      /*!< TMR2 unit 1 channel B CLK input */
#define GPIO_FUNC_16_TIM21_PWMA     (GPIO_FUNC_16)      /*!< TMR2 unit 1 channel A PWM output */
#define GPIO_FUNC_16_TIM21_PWMB     (GPIO_FUNC_16)      /*!< TMR2 unit 1 channel B PWM output */

#define GPIO_FUNC_16_TIM22          (GPIO_FUNC_16)      /*!< TMR2 unit 2 */
#define GPIO_FUNC_16_TIM22_CLKA     (GPIO_FUNC_16)      /*!< TMR2 unit 2 channel A CLK input */
#define GPIO_FUNC_16_TIM22_CLKB     (GPIO_FUNC_16)      /*!< TMR2 unit 2 channel B CLK input */
#define GPIO_FUNC_16_TIM22_PWMA     (GPIO_FUNC_16)      /*!< TMR2 unit 2 channel A PWM output */
#define GPIO_FUNC_16_TIM22_PWMB     (GPIO_FUNC_16)      /*!< TMR2 unit 2 channel B PWM output */

#define GPIO_FUNC_16_TIM23          (GPIO_FUNC_16)      /*!< TMR2 unit 3 */
#define GPIO_FUNC_16_TIM23_CLKA     (GPIO_FUNC_16)      /*!< TMR2 unit 3 channel A CLK input */
#define GPIO_FUNC_16_TIM23_CLKB     (GPIO_FUNC_16)      /*!< TMR2 unit 3 channel B CLK input */
#define GPIO_FUNC_16_TIM23_PWMA     (GPIO_FUNC_16)      /*!< TMR2 unit 3 channel A PWM output */
#define GPIO_FUNC_16_TIM23_PWMB     (GPIO_FUNC_16)      /*!< TMR2 unit 3 channel B PWM output */

#define GPIO_FUNC_16_TIM24          (GPIO_FUNC_16)      /*!< TMR2 unit 4 */
#define GPIO_FUNC_16_TIM24_CLKA     (GPIO_FUNC_16)      /*!< TMR2 unit 4 channel A CLK input */
#define GPIO_FUNC_16_TIM24_CLKB     (GPIO_FUNC_16)      /*!< TMR2 unit 4 channel B CLK input */
#define GPIO_FUNC_16_TIM24_PWMA     (GPIO_FUNC_16)      /*!< TMR2 unit 4 channel A PWM output */
#define GPIO_FUNC_16_TIM24_PWMB     (GPIO_FUNC_16)      /*!< TMR2 unit 4 channel B PWM output */

#define GPIO_FUNC_16_TIM41_CLK      (GPIO_FUNC_16)      /*!< TMR4 unit 1 CLK input */

#define GPIO_FUNC_16_TIM42_CLK      (GPIO_FUNC_16)      /*!< TMR4 unit 2 CLK input */
#define GPIO_FUNC_16_TIM42_OUL      (GPIO_FUNC_16)      /*!< TMR4 unit 2 U-phase low output */
#define GPIO_FUNC_16_TIM42_OVL      (GPIO_FUNC_16)      /*!< TMR4 unit 2 V-phase low output */
#define GPIO_FUNC_16_TIM42_OWL      (GPIO_FUNC_16)      /*!< TMR4 unit 2 W-phase low output */

#define GPIO_FUNC_16_TIM43_ADSM     (GPIO_FUNC_16)      /*!< TMR4 unit 3 special event */

/**
 * @}
 */

/** @defgroup GPIO_PinFunction17 GPIO Function 17 selection
 * @{
 */
#define GPIO_FUNC_17                (0x11U)
#define GPIO_FUNC_17_I2S1           (GPIO_FUNC_17)      /*!< I2S1 */
#define GPIO_FUNC_17_I2S1_MCK       (GPIO_FUNC_17)      /*!< I2S1 MCK */
#define GPIO_FUNC_17_I2S1_EXCK      (GPIO_FUNC_17)      /*!< I2S1 EXCK */
#define GPIO_FUNC_17_I2S1_SDIN      (GPIO_FUNC_17)      /*!< I2S1 SDIN */

#define GPIO_FUNC_17_I2S2           (GPIO_FUNC_17)      /*!< I2S2 */
#define GPIO_FUNC_17_I2S2_CK        (GPIO_FUNC_17)      /*!< I2S2 CK */
#define GPIO_FUNC_17_I2S2_MCK       (GPIO_FUNC_17)      /*!< I2S2 MCK */
#define GPIO_FUNC_17_I2S2_EXCK      (GPIO_FUNC_17)      /*!< I2S2 EXCK */
#define GPIO_FUNC_17_I2S2_SD        (GPIO_FUNC_17)      /*!< I2S2 SD */
#define GPIO_FUNC_17_I2S2_SDIN      (GPIO_FUNC_17)      /*!< I2S2 SDIN */

#define GPIO_FUNC_17_I2S3           (GPIO_FUNC_17)      /*!< I2S3 */
#define GPIO_FUNC_17_I2S3_MCK       (GPIO_FUNC_17)      /*!< I2S3 MCK */
#define GPIO_FUNC_17_I2S3_EXCK      (GPIO_FUNC_17)      /*!< I2S3 EXCK */
#define GPIO_FUNC_17_I2S3_SDIN      (GPIO_FUNC_17)      /*!< I2S3 SDIN */

#define GPIO_FUNC_17_I2S4           (GPIO_FUNC_17)      /*!< I2S4 */
#define GPIO_FUNC_17_I2S4_MCK       (GPIO_FUNC_17)      /*!< I2S4 MCK */
#define GPIO_FUNC_17_I2S4_EXCK      (GPIO_FUNC_17)      /*!< I2S4 EXCK */
#define GPIO_FUNC_17_I2S4_SDIN      (GPIO_FUNC_17)      /*!< I2S4 SDIN */
#define GPIO_FUNC_17_I2S4_SD        (GPIO_FUNC_17)      /*!< I2S4 SD */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction18 GPIO Function 18 selection
 * @{
 */
#define GPIO_FUNC_18                (0x12U)
#define GPIO_FUNC_18_SPI1           (GPIO_FUNC_18)      /*!< SPI1 */
#define GPIO_FUNC_18_SPI1_NSS1      (GPIO_FUNC_18)      /*!< SPI1 NSS1 */
#define GPIO_FUNC_18_SPI1_NSS2      (GPIO_FUNC_18)      /*!< SPI1 NSS2 */
#define GPIO_FUNC_18_SPI1_NSS3      (GPIO_FUNC_18)      /*!< SPI1 NSS3 */

#define GPIO_FUNC_18_SPI2           (GPIO_FUNC_18)      /*!< SPI2 */
#define GPIO_FUNC_18_SPI2_NSS0      (GPIO_FUNC_18)      /*!< SPI2 NSS0 */
#define GPIO_FUNC_18_SPI2_NSS1      (GPIO_FUNC_18)      /*!< SPI2 NSS1 */
#define GPIO_FUNC_18_SPI2_NSS2      (GPIO_FUNC_18)      /*!< SPI2 NSS2 */
#define GPIO_FUNC_18_SPI2_NSS3      (GPIO_FUNC_18)      /*!< SPI2 NSS3 */

#define GPIO_FUNC_18_SPI3           (GPIO_FUNC_18)      /*!< SPI3 */
#define GPIO_FUNC_18_SPI3_NSS1      (GPIO_FUNC_18)      /*!< SPI3 NSS1 */
#define GPIO_FUNC_18_SPI3_NSS2      (GPIO_FUNC_18)      /*!< SPI3 NSS2 */
#define GPIO_FUNC_18_SPI3_NSS3      (GPIO_FUNC_18)      /*!< SPI3 NSS3 */

#define GPIO_FUNC_18_SPI4           (GPIO_FUNC_18)      /*!< SPI4 */
#define GPIO_FUNC_18_SPI4_NSS1      (GPIO_FUNC_18)      /*!< SPI4 NSS1 */
#define GPIO_FUNC_18_SPI4_NSS2      (GPIO_FUNC_18)      /*!< SPI4 NSS2 */
#define GPIO_FUNC_18_SPI4_NSS3      (GPIO_FUNC_18)      /*!< SPI4 NSS3 */

#define GPIO_FUNC_18_SPI5           (GPIO_FUNC_18)      /*!< SPI5 */
#define GPIO_FUNC_18_SPI5_NSS0      (GPIO_FUNC_18)      /*!< SPI5 NSS0 */
#define GPIO_FUNC_18_SPI5_NSS1      (GPIO_FUNC_18)      /*!< SPI5 NSS1 */
#define GPIO_FUNC_18_SPI5_NSS2      (GPIO_FUNC_18)      /*!< SPI5 NSS2 */
#define GPIO_FUNC_18_SPI5_NSS3      (GPIO_FUNC_18)      /*!< SPI5 NSS3 */

#define GPIO_FUNC_18_SPI6           (GPIO_FUNC_18)      /*!< SPI6 */
#define GPIO_FUNC_18_SPI6_NSS1      (GPIO_FUNC_18)      /*!< SPI6 NSS1 */
#define GPIO_FUNC_18_SPI6_NSS2      (GPIO_FUNC_18)      /*!< SPI6 NSS2 */
#define GPIO_FUNC_18_SPI6_NSS3      (GPIO_FUNC_18)      /*!< SPI6 NSS3 */

#define GPIO_FUNC_18_QSPI           (GPIO_FUNC_18)      /*!< QSPI */
#define GPIO_FUNC_18_QSPI_NSS       (GPIO_FUNC_18)      /*!< QSPI NSS */
#define GPIO_FUNC_18_QSPI_SCK       (GPIO_FUNC_18)      /*!< QSPI SCK */
#define GPIO_FUNC_18_QSPI_IO0       (GPIO_FUNC_18)      /*!< QSPI IO0 */
#define GPIO_FUNC_18_QSPI_IO1       (GPIO_FUNC_18)      /*!< QSPI IO1 */
#define GPIO_FUNC_18_QSPI_IO2       (GPIO_FUNC_18)      /*!< QSPI IO2 */
#define GPIO_FUNC_18_QSPI_IO3       (GPIO_FUNC_18)      /*!< QSPI IO3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction19 GPIO Function 19 selection
 * @{
 */
#define GPIO_FUNC_19                (0x13U)
#define GPIO_FUNC_19_SPI1           (GPIO_FUNC_19)      /*!< SPI1 */
#define GPIO_FUNC_19_SPI1_NSS0      (GPIO_FUNC_19)      /*!< SPI1 NSS0 */

#define GPIO_FUNC_19_SPI2           (GPIO_FUNC_19)      /*!< SPI2 */
#define GPIO_FUNC_19_SPI2_NSS0      (GPIO_FUNC_19)      /*!< SPI2 NSS0 */
#define GPIO_FUNC_19_SPI2_MOSI      (GPIO_FUNC_19)      /*!< SPI2 MOSI */
#define GPIO_FUNC_19_SPI2_MISO      (GPIO_FUNC_19)      /*!< SPI2 MISO */
#define GPIO_FUNC_19_SPI2_SCK       (GPIO_FUNC_19)      /*!< SPI2 SCK */

#define GPIO_FUNC_19_SPI3           (GPIO_FUNC_19)      /*!< SPI3 */
#define GPIO_FUNC_19_SPI3_NSS0      (GPIO_FUNC_19)      /*!< SPI3 NSS0 */
#define GPIO_FUNC_19_SPI3_MOSI      (GPIO_FUNC_19)      /*!< SPI3 MOSI */
#define GPIO_FUNC_19_SPI3_MISO      (GPIO_FUNC_19)      /*!< SPI3 MISO */
#define GPIO_FUNC_19_SPI3_SCK       (GPIO_FUNC_19)      /*!< SPI3 SCK */

#define GPIO_FUNC_19_SPI            (GPIO_FUNC_19)      /*!< SPI4 */
#define GPIO_FUNC_19_SPI4_NSS0      (GPIO_FUNC_19)      /*!< SPI4 NSS0 */

#define GPIO_FUNC_19_SPI5           (GPIO_FUNC_19)      /*!< SPI5 */
#define GPIO_FUNC_19_SPI5_NSS0      (GPIO_FUNC_19)      /*!< SPI5 NSS0 */
#define GPIO_FUNC_19_SPI5_MOSI      (GPIO_FUNC_19)      /*!< SPI5 MOSI */
#define GPIO_FUNC_19_SPI5_MISO      (GPIO_FUNC_19)      /*!< SPI5 MISO */
#define GPIO_FUNC_19_SPI5_SCK       (GPIO_FUNC_19)      /*!< SPI5 SCK */

#define GPIO_FUNC_19_SPI6           (GPIO_FUNC_19)      /*!< SPI6 */
#define GPIO_FUNC_19_SPI6_NSS0      (GPIO_FUNC_19)      /*!< SPI6 NSS0 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction20 GPIO Function 20 selection
 * @{
 */
#define GPIO_FUNC_20                (0x14U)
#define GPIO_FUNC_20_USART1         (GPIO_FUNC_20)      /*!< USART1 */
#define GPIO_FUNC_20_USART1_TX      (GPIO_FUNC_20)      /*!< USART1 TX */
#define GPIO_FUNC_20_USART1_RX      (GPIO_FUNC_20)      /*!< USART1 RX */
#define GPIO_FUNC_20_USART1_CTS     (GPIO_FUNC_20)      /*!< USART1 CTS */
#define GPIO_FUNC_20_USART1_RTS     (GPIO_FUNC_20)      /*!< USART1 RTS */
#define GPIO_FUNC_20_USART1_CK      (GPIO_FUNC_20)      /*!< USART1 CK */

#define GPIO_FUNC_20_USART2         (GPIO_FUNC_20)      /*!< USART2 */
#define GPIO_FUNC_20_USART2_TX      (GPIO_FUNC_20)      /*!< USART2 TX */
#define GPIO_FUNC_20_USART2_RX      (GPIO_FUNC_20)      /*!< USART2 RX */
#define GPIO_FUNC_20_USART2_CTS     (GPIO_FUNC_20)      /*!< USART2 CTS */
#define GPIO_FUNC_20_USART2_RTS     (GPIO_FUNC_20)      /*!< USART2 RTS */
#define GPIO_FUNC_20_USART2_CK      (GPIO_FUNC_20)      /*!< USART2 CK */

#define GPIO_FUNC_20_USART4         (GPIO_FUNC_20)      /*!< USART4 */
#define GPIO_FUNC_20_USART4_TX      (GPIO_FUNC_20)      /*!< USART4 TX */
#define GPIO_FUNC_20_USART4_RX      (GPIO_FUNC_20)      /*!< USART4 RX */

#define GPIO_FUNC_20_USART5         (GPIO_FUNC_20)      /*!< USART5 */
#define GPIO_FUNC_20_USART5_TX      (GPIO_FUNC_20)      /*!< USART5 TX */
#define GPIO_FUNC_20_USART5_RX      (GPIO_FUNC_20)      /*!< USART5 RX */

#define GPIO_FUNC_20_USART6         (GPIO_FUNC_20)      /*!< USART6 */
#define GPIO_FUNC_20_USART6_TX      (GPIO_FUNC_20)      /*!< USART6 TX */
#define GPIO_FUNC_20_USART6_RX      (GPIO_FUNC_20)      /*!< USART6 RX */
#define GPIO_FUNC_20_USART6_CTS     (GPIO_FUNC_20)      /*!< USART6 CTS */
#define GPIO_FUNC_20_USART6_RTS     (GPIO_FUNC_20)      /*!< USART6 RTS */
#define GPIO_FUNC_20_USART6_CK      (GPIO_FUNC_20)      /*!< USART6 CK */

#define GPIO_FUNC_20_USART7         (GPIO_FUNC_20)      /*!< USART7 */
#define GPIO_FUNC_20_USART7_TX      (GPIO_FUNC_20)      /*!< USART7 TX */
#define GPIO_FUNC_20_USART7_RX      (GPIO_FUNC_20)      /*!< USART7 RX */

#define GPIO_FUNC_20_USART8         (GPIO_FUNC_20)      /*!< USART8 */
#define GPIO_FUNC_20_USART8_TX      (GPIO_FUNC_20)      /*!< USART8 TX */
#define GPIO_FUNC_20_USART8_RX      (GPIO_FUNC_20)      /*!< USART8 RX */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction32 GPIO Function 32 selection
 * @{
 */
#define GPIO_FUNC_32                (0x20U)
#define GPIO_FUNC_32_USART1_TX      (GPIO_FUNC_32)      /*!< USART1 TX in Function Group 1 */
#define GPIO_FUNC_32_USART4_TX      (GPIO_FUNC_32)      /*!< USART4 TX in Function Group 2 */
#define GPIO_FUNC_32_USART3_TX      (GPIO_FUNC_32)      /*!< USART3 TX in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction33 GPIO Function 33 selection
 * @{
 */
#define GPIO_FUNC_33                (0x21U)
#define GPIO_FUNC_33_USART1_RX      (GPIO_FUNC_33)      /*!< USART1 RX in Function Group 1 */
#define GPIO_FUNC_33_USART4_RX      (GPIO_FUNC_33)      /*!< USART4 RX in Function Group 2 */
#define GPIO_FUNC_33_USART3_RX      (GPIO_FUNC_33)      /*!< USART3 RX in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction34 GPIO Function 34 selection
 * @{
 */
#define GPIO_FUNC_34                (0x22U)
#define GPIO_FUNC_34_USART2_TX      (GPIO_FUNC_34)      /*!< USART2 TX in Function Group 1 */
#define GPIO_FUNC_34_USART5_TX      (GPIO_FUNC_34)      /*!< USART5 TX in Function Group 2 */
#define GPIO_FUNC_34_USART8_TX      (GPIO_FUNC_34)      /*!< USART8 TX in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction35 GPIO Function 35 selection
 * @{
 */
#define GPIO_FUNC_35                (0x23U)
#define GPIO_FUNC_35_USART2_RX      (GPIO_FUNC_35)      /*!< USART2 RX in Function Group 1 */
#define GPIO_FUNC_35_USART5_RX      (GPIO_FUNC_35)      /*!< USART5 RX in Function Group 2 */
#define GPIO_FUNC_35_USART8_RX      (GPIO_FUNC_35)      /*!< USART8 RX in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction36 GPIO Function 36 selection
 * @{
 */
#define GPIO_FUNC_36                (0x24U)
#define GPIO_FUNC_36_USART3_TX      (GPIO_FUNC_36)      /*!< USART3 TX in Function Group 1 */
#define GPIO_FUNC_36_USART6_TX      (GPIO_FUNC_36)      /*!< USART6 TX in Function Group 2 */
#define GPIO_FUNC_36_USART9_TX      (GPIO_FUNC_36)      /*!< USART9 TX in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction37 GPIO Function 37 selection
 * @{
 */
#define GPIO_FUNC_37                (0x25U)
#define GPIO_FUNC_37_USART3_RX      (GPIO_FUNC_37)      /*!< USART3 RX in Function Group 1 */
#define GPIO_FUNC_37_USART6_RX      (GPIO_FUNC_37)      /*!< USART6 RX in Function Group 2 */
#define GPIO_FUNC_37_USART9_RX      (GPIO_FUNC_37)      /*!< USART9 RX in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction38 GPIO Function 38 selection
 * @{
 */
#define GPIO_FUNC_38                (0x26U)
#define GPIO_FUNC_38_USART4_TX      (GPIO_FUNC_38)      /*!< USART4 TX in Function Group 1 */
#define GPIO_FUNC_38_USART7_TX      (GPIO_FUNC_38)      /*!< USART7 TX in Function Group 2 */
#define GPIO_FUNC_38_USART10_TX     (GPIO_FUNC_38)      /*!< USART10 TX in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction39 GPIO Function 39 selection
 * @{
 */
#define GPIO_FUNC_39                (0x27U)
#define GPIO_FUNC_39_USART4_RX      (GPIO_FUNC_39)      /*!< USART4 RX in Function Group 1 */
#define GPIO_FUNC_39_USART7_RX      (GPIO_FUNC_39)      /*!< USART7 RX in Function Group 2 */
#define GPIO_FUNC_39_USART10_RX     (GPIO_FUNC_39)      /*!< USART10 RX in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction40 GPIO Function 40 selection
 * @{
 */
#define GPIO_FUNC_40                (0x28U)
#define GPIO_FUNC_40_SPI1_SCK       (GPIO_FUNC_40)      /*!< SPI1 SCK in Function Group 1 & 3 */
#define GPIO_FUNC_40_SPI4_SCK       (GPIO_FUNC_40)      /*!< SPI4 SCK in Function Group 2 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction41 GPIO Function 41 selection
 * @{
 */
#define GPIO_FUNC_41                (0x29U)
#define GPIO_FUNC_41_SPI1_MOSI      (GPIO_FUNC_41)      /*!< SPI1 MOSI in Function Group 1 & 3 */
#define GPIO_FUNC_41_SPI4_MOSI      (GPIO_FUNC_41)      /*!< SPI4 MOSI in Function Group 2 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction42 GPIO Function 42 selection
 * @{
 */
#define GPIO_FUNC_42                (0x2AU)
#define GPIO_FUNC_42_SPI1_MISO      (GPIO_FUNC_42)      /*!< SPI1 MISO in Function Group 1 & 3 */
#define GPIO_FUNC_42_SPI4_MISO      (GPIO_FUNC_42)      /*!< SPI4 MISO in Function Group 2 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction43 GPIO Function 43 selection
 * @{
 */
#define GPIO_FUNC_43                (0x2BU)
#define GPIO_FUNC_43_SPI2_SCK       (GPIO_FUNC_43)      /*!< SPI2 SCK in Function Group 1 */
#define GPIO_FUNC_43_SPI5_SCK       (GPIO_FUNC_43)      /*!< SPI5 SCK in Function Group 2 */
#define GPIO_FUNC_43_SPI4_SCK       (GPIO_FUNC_43)      /*!< SPI4 SCK in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction44 GPIO Function 44 selection
 * @{
 */
#define GPIO_FUNC_44                (0x2CU)
#define GPIO_FUNC_44_SPI2_MOSI      (GPIO_FUNC_44)      /*!< SPI2 MOSI in Function Group 1 */
#define GPIO_FUNC_44_SPI5_MOSI      (GPIO_FUNC_44)      /*!< SPI5 MOSI in Function Group 2 */
#define GPIO_FUNC_44_SPI4_MOSI      (GPIO_FUNC_44)      /*!< SPI4 MOSI in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction45 GPIO Function 45 selection
 * @{
 */
#define GPIO_FUNC_45                (0x2DU)
#define GPIO_FUNC_45_SPI2_MISO      (GPIO_FUNC_45)      /*!< SPI2 MISO in Function Group 1 */
#define GPIO_FUNC_45_SPI5_MISO      (GPIO_FUNC_45)      /*!< SPI5 MISO in Function Group 2 */
#define GPIO_FUNC_45_SPI4_MISO      (GPIO_FUNC_45)      /*!< SPI4 MISO in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction46 GPIO Function 46 selection
 * @{
 */
#define GPIO_FUNC_46                (0x2EU)
#define GPIO_FUNC_46_SPI3_SCK       (GPIO_FUNC_46)      /*!< SPI3 SCK in Function Group 1 */
#define GPIO_FUNC_46_SPI6_SCK       (GPIO_FUNC_46)      /*!< SPI6 SCK in Function Group 2 */
#define GPIO_FUNC_46_SPI4_NSS0      (GPIO_FUNC_46)      /*!< SPI4 NSS0 in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction47 GPIO Function 47 selection
 * @{
 */
#define GPIO_FUNC_47                (0x2FU)
#define GPIO_FUNC_47_SPI3_MOSI      (GPIO_FUNC_47)      /*!< SPI3 MOSI in Function Group 1 */
#define GPIO_FUNC_47_SPI6_MOSI      (GPIO_FUNC_47)      /*!< SPI6 MOSI in Function Group 2 */
#define GPIO_FUNC_47_SPI1_NSS0      (GPIO_FUNC_47)      /*!< SPI4 NSS0 in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction48 GPIO Function 48 selection
 * @{
 */
#define GPIO_FUNC_48                (0x30U)
#define GPIO_FUNC_48_SPI3_MISO      (GPIO_FUNC_48)      /*!< SPI3 MISO in Function Group 1 */
#define GPIO_FUNC_48_SPI6_MISO      (GPIO_FUNC_48)      /*!< SPI6 MISO in Function Group 2 */
#define GPIO_FUNC_48_I2C1_SDA       (GPIO_FUNC_48)      /*!< I2C1 SDA in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction49 GPIO Function 49 selection
 * @{
 */
#define GPIO_FUNC_49                (0x31U)
#define GPIO_FUNC_49_SPI3_NSS0      (GPIO_FUNC_49)      /*!< SPI3 NSS0 in Function Group 1 */
#define GPIO_FUNC_49_SPI6_NSS0      (GPIO_FUNC_49)      /*!< SPI6 NSS0 in Function Group 2 */
#define GPIO_FUNC_49_I2C1_SCL       (GPIO_FUNC_49)      /*!< I2C1 SCL in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction50 GPIO Function 50 selection
 * @{
 */
#define GPIO_FUNC_50                (0x32U)
#define GPIO_FUNC_50_I2C1_SDA       (GPIO_FUNC_50)      /*!< I2C1 SDA in Function Group 1 */
#define GPIO_FUNC_50_I2C2_SDA       (GPIO_FUNC_50)      /*!< I2C2 SDA in Function Group 2 & 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction51 GPIO Function 51 selection
 * @{
 */
#define GPIO_FUNC_51                (0x33U)
#define GPIO_FUNC_51_I2C1_SCL       (GPIO_FUNC_51)      /*!< I2C1 SCL in Function Group 1 */
#define GPIO_FUNC_51_I2C2_SCL       (GPIO_FUNC_51)      /*!< I2C2 SCL in Function Group 2 & 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction52 GPIO Function 52 selection
 * @{
 */
#define GPIO_FUNC_52                (0x34U)
#define GPIO_FUNC_52_I2C3_SDA       (GPIO_FUNC_52)      /*!< I2C3 SDA in Function Group 1 */
#define GPIO_FUNC_52_I2C4_SDA       (GPIO_FUNC_52)      /*!< I2C4 SDA in Function Group 2 */
#define GPIO_FUNC_52_I2C6_SDA       (GPIO_FUNC_52)      /*!< I2C6 SDA in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction53 GPIO Function 53 selection
 * @{
 */
#define GPIO_FUNC_53                (0x35U)
#define GPIO_FUNC_53_I2C3_SCL       (GPIO_FUNC_53)      /*!< I2C3 SCL in Function Group 1 */
#define GPIO_FUNC_53_I2C4_SCL       (GPIO_FUNC_53)      /*!< I2C4 SCL in Function Group 2 */
#define GPIO_FUNC_53_I2C6_SCL       (GPIO_FUNC_53)      /*!< I2C6 SCL in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction54 GPIO Function 54 selection
 * @{
 */
#define GPIO_FUNC_54                (0x36U)
#define GPIO_FUNC_54_I2S1_CK        (GPIO_FUNC_54)      /*!< I2S1 CK in Function Group 1&3 */
#define GPIO_FUNC_54_I2C5_SDA       (GPIO_FUNC_54)      /*!< I2C5 SDA in Function Group 2 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction55 GPIO Function 55 selection
 * @{
 */
#define GPIO_FUNC_55                (0x37U)
#define GPIO_FUNC_55_I2S1_WS        (GPIO_FUNC_55)      /*!< I2S1_WS in Function Group 1&3 */
#define GPIO_FUNC_55_I2C5_SCL       (GPIO_FUNC_55)      /*!< I2C5_SCL in Function Group 2 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction56 GPIO Function 56 selection
 * @{
 */
#define GPIO_FUNC_56                (0x38U)
#define GPIO_FUNC_56_I2S1_SD        (GPIO_FUNC_56)      /*!< I2S1 SD in Function Group 1&3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction57 GPIO Function 57 selection
 * @{
 */
#define GPIO_FUNC_57                (0x39U)
#define GPIO_FUNC_57_I2S2_CK        (GPIO_FUNC_57)      /*!< I2S2 CK in Function Group 1 */
#define GPIO_FUNC_57_I2S3_CK        (GPIO_FUNC_57)      /*!< I2S3 CK in Function Group 2 */
#define GPIO_FUNC_57_I2S4_CK        (GPIO_FUNC_57)      /*!< I2S4 CK in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction58 GPIO Function 58 selection
 * @{
 */
#define GPIO_FUNC_58                (0x3AU)
#define GPIO_FUNC_58_I2S2_WS        (GPIO_FUNC_58)      /*!< I2S2 WS in Function Group 1 */
#define GPIO_FUNC_58_I2S3_WS        (GPIO_FUNC_58)      /*!< I2S3 WS in Function Group 2 */
#define GPIO_FUNC_58_I2S4_WS        (GPIO_FUNC_58)      /*!< I2S4 WS in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction59 GPIO Function 59 selection
 * @{
 */
#define GPIO_FUNC_59                (0x3BU)
#define GPIO_FUNC_59_I2S2_SD        (GPIO_FUNC_59)      /*!< I2S2 SD in Function Group 1 */
#define GPIO_FUNC_59_I2S3_SD        (GPIO_FUNC_59)      /*!< I2S3 SD in Function Group 2 */
#define GPIO_FUNC_59_I2S4_SD        (GPIO_FUNC_59)      /*!< I2S4 SD in Function Group 3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction60 GPIO Function 60 selection
 * @{
 */
#define GPIO_FUNC_60                (0x3CU)
#define GPIO_FUNC_60_CAN1_TX        (GPIO_FUNC_60)      /*!< CAN1 TX in Function Group 1~3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction61 GPIO Function 61 selection
 * @{
 */
#define GPIO_FUNC_61                (0x3DU)
#define GPIO_FUNC_61_CAN1_RX        (GPIO_FUNC_61)      /*!< CAN1 RX in Function Group 1~3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction62 GPIO Function 62 selection
 * @{
 */
#define GPIO_FUNC_62                (0x3EU)
#define GPIO_FUNC_62_CAN2_TX        (GPIO_FUNC_62)      /*!< CAN2 TX in Function Group 1~3 */
/**
 * @}
 */

/** @defgroup GPIO_PinFunction63 GPIO Function 63 selection
 * @{
 */
#define GPIO_FUNC_63                (0x3FU)
#define GPIO_FUNC_63_CAN2_RX        (GPIO_FUNC_63)      /*!< CAN2 RX in Function Group 1~3 */
/**
 * @}
 */

/** @defgroup GPIO_DebugPin_Sel GPIO Debug pin selection
 * @{
 */
#define GPIO_PIN_SWCLK              (0x01U)
#define GPIO_PIN_SWDIO              (0x02U)
#define GPIO_PIN_SWO                (0x04U)
#define GPIO_PIN_DEBUG_SWD          (0x07U)

#define GPIO_PIN_TCK                (0x01U)
#define GPIO_PIN_TMS                (0x02U)
#define GPIO_PIN_TDO                (0x04U)
#define GPIO_PIN_TDI                (0x08U)
#define GPIO_PIN_TRST               (0x10U)
#define GPIO_PIN_DEBUG_JTAG         (0x1FU)
/**
 * @}
 */

/** @defgroup GPIO_ReadCycle_Sel GPIO pin read wait cycle selection
 * @{
 */
#define GPIO_READ_WAIT_0            ((uint16_t)(0x00UL << GPIO_PCCR_RDWT_POS))
#define GPIO_READ_WAIT_1            ((uint16_t)(0x01UL << GPIO_PCCR_RDWT_POS))
#define GPIO_READ_WAIT_2            ((uint16_t)(0x02UL << GPIO_PCCR_RDWT_POS))
#define GPIO_READ_WAIT_3            ((uint16_t)(0x03UL << GPIO_PCCR_RDWT_POS))
#define GPIO_READ_WAIT_4            ((uint16_t)(0x04UL << GPIO_PCCR_RDWT_POS))
#define GPIO_READ_WAIT_5            ((uint16_t)(0x05UL << GPIO_PCCR_RDWT_POS))
#define GPIO_READ_WAIT_6            ((uint16_t)(0x06UL << GPIO_PCCR_RDWT_POS))
#define GPIO_READ_WAIT_7            ((uint16_t)(0x07UL << GPIO_PCCR_RDWT_POS))
/**
 * @}
 */

/**
 * @defgroup GPIO_PinState_Sel GPIO pin output state selection
 * @{
 */
#define PIN_STATE_RESET             (0U)
#define PIN_STATE_SET               (GPIO_PCR_POUT)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinDirection_Sel GPIO pin input/output direction selection
 * @{
 */
#define PIN_DIR_IN                  (0U)
#define PIN_DIR_OUT                 (GPIO_PCR_POUTE)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinOutType_Sel GPIO pin output type selection
 * @{
 */
#define PIN_OTYPE_CMOS              (0U)
#define PIN_OTYPE_NMOS              (GPIO_PCR_NOD)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinDrv_Sel GPIO Pin drive capacity selection
 * @{
 */
#define PIN_DRV_LOW                 (0U)
#define PIN_DRV_MID                 (GPIO_PCR_DRV_0)
#define PIN_DRV_HIGH                (GPIO_PCR_DRV_1)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinLatch_Sel GPIO Pin output latch selection
 * @{
 */
#define PIN_LATCH_OFF               (0U)
#define PIN_LATCH_ON                (GPIO_PCR_LTE)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinPU_Sel GPIO Pin internal pull-up resistor selection
 * @{
 */
#define PIN_PU_OFF                  (0U)
#define PIN_PU_ON                   (GPIO_PCR_PUU)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinInvert_Sel GPIO Pin I/O invert selection
 * @{
 */
#define PIN_INVERT_OFF              (0U)
#define PIN_INVERT_ON               (GPIO_PCR_INVE)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinInType_Sel GPIO Pin input type selection
 * @{
 */
#define PIN_ITYPE_SMT               (0U)
#define PIN_ITYPE_CMOS              (GPIO_PCR_CINSEL)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinExInt_Sel GPIO Pin external interrupt selection
 * @{
 */
#define PIN_EXINT_OFF               (0U)
#define PIN_EXINT_ON                (GPIO_PCR_INTE)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinMode_Sel GPIO Pin mode selection
 * @{
 */
#define PIN_ATTR_DIGITAL            (0U)
#define PIN_ATTR_ANALOG             (GPIO_PCR_DDIS)
/**
 * @}
 */

/**
 * @defgroup GPIO_PinSubFuncSet_Sel GPIO Pin sub-function enable or disable
 * @{
 */
#define PIN_SUBFUNC_DISABLE         (0U)
#define PIN_SUBFUNC_ENABLE          (GPIO_PFSR_BFE)
/**
 * @}
 */

/**
 * @defgroup GPIO_Register_Protect GPIO Registers Protect Code
 * @{
 */
#define GPIO_REG_UNPROTECT          (0xA501U)
#define GPIO_REG_PROTECT            (0xA500U)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup GPIO_Global_Functions
 * @{
 */
/**
 * @brief  GPIO lock. PSPCR, PCCR, PINAER, PCRxy, PFSRxy write disable
 * @param  None
 * @retval None
 */
__STATIC_INLINE void GPIO_Lock(void)
{
    WRITE_REG16(M4_GPIO->PWPR, GPIO_REG_PROTECT);
}

/**
 * @brief  GPIO unlock. PSPCR, PCCR, PINAER, PCRxy, PFSRxy write enable
 * @param  None
 * @retval None
 */
__STATIC_INLINE void GPIO_Unlock(void)
{
    WRITE_REG16(M4_GPIO->PWPR, GPIO_REG_UNPROTECT);
}

en_result_t GPIO_Init(uint8_t u8Port, uint16_t u16Pin, const stc_gpio_init_t *pstcGpioInit);
void GPIO_DeInit(void);
void GPIO_Unlock(void);
void GPIO_Lock(void);
en_result_t GPIO_StructInit(stc_gpio_init_t *pstcGpioInit);
void GPIO_SetDebugPort(uint8_t u8DebugPort, en_functional_state_t enNewState);
void GPIO_SetFunc(uint8_t u8Port, uint16_t u16Pin, uint8_t u8Func, uint16_t u16BFE);
void GPIO_SetSubFunc(uint8_t u8Func);
void GPIO_SetReadWaitCycle(uint16_t u16ReadWait);
void GPIO_InMOSCmd(uint16_t u16PortIdx, en_functional_state_t enNewState);
void GPIO_OE(uint8_t u8Port, uint16_t u16Pin, en_functional_state_t enNewState);
//port pin
en_pin_state_t GPIO_ReadInputPins(uint8_t u8Port, uint16_t u16Pin);
uint16_t GPIO_ReadInputPort(uint8_t u8Port);
en_pin_state_t GPIO_ReadOutputPins(uint8_t u8Port, uint16_t u16Pin);
uint16_t GPIO_ReadOutputPort(uint8_t u8Port);
void GPIO_SetPins(uint8_t u8Port, uint16_t u16Pin);
void GPIO_ResetPins(uint8_t u8Port, uint16_t u16Pin);
void GPIO_TogglePins(uint8_t u8Port, uint16_t u16Pin);
void GPIO_WritePort(uint8_t u8Port, uint16_t u16PortVal);

/**
 * @}
 */

#endif /* DDL_GPIO_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_GPIO_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
