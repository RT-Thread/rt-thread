/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */


#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include <rtconfig.h>
#include "hc32_ll.h"
#include "drv_config.h"


/************************* XTAL port **********************/
#define XTAL_PORT                       (GPIO_PORT_F)
#define XTAL_IN_PIN                     (GPIO_PIN_00)
#define XTAL_OUT_PIN                    (GPIO_PIN_01)

/************************ USART port **********************/
#if defined(BSP_USING_UART1)
    #define USART1_RX_PORT                  (GPIO_PORT_B)
    #define USART1_RX_PIN                   (GPIO_PIN_06)
    #define USART1_RX_FUNC                  (GPIO_FUNC_33)

    #define USART1_TX_PORT                  (GPIO_PORT_B)
    #define USART1_TX_PIN                   (GPIO_PIN_07)
    #define USART1_TX_FUNC                  (GPIO_FUNC_32)
#endif

#if defined(BSP_USING_UART2)
    #define USART2_RX_PORT                  (GPIO_PORT_C)
    #define USART2_RX_PIN                   (GPIO_PIN_04)
    #define USART2_RX_FUNC                  (GPIO_FUNC_37)

    #define USART2_TX_PORT                  (GPIO_PORT_C)
    #define USART2_TX_PIN                   (GPIO_PIN_10)
    #define USART2_TX_FUNC                  (GPIO_FUNC_36)
#endif

/************************ I2C port **********************/
#if defined(BSP_USING_I2C1)
    #define I2C1_SDA_PORT                   (GPIO_PORT_B)
    #define I2C1_SDA_PIN                    (GPIO_PIN_06)
    #define I2C1_SDA_FUNC                   (GPIO_FUNC_52)

    #define I2C1_SCL_PORT                   (GPIO_PORT_B)
    #define I2C1_SCL_PIN                    (GPIO_PIN_07)
    #define I2C1_SCL_FUNC                   (GPIO_FUNC_53)
#endif

/***********  ADC configure *********/
#if defined(BSP_USING_ADC1)
    #define ADC1_CH_PORT                    (GPIO_PORT_C)   /* Default ADC12_IN10 */
    #define ADC1_CH_PIN                     (GPIO_PIN_00)
#endif

#if defined(BSP_USING_ADC2)
    #define ADC2_CH_PORT                    (GPIO_PORT_A)   /* Default ADC12_IN4 */
    #define ADC2_CH_PIN                     (GPIO_PIN_04)
#endif

#if defined(BSP_USING_ADC3)
    #define ADC3_CH_PORT                    (GPIO_PORT_B)   /* Default ADC3_IN1 */
    #define ADC3_CH_PIN                     (GPIO_PIN_13)
#endif

/***********  DAC configure *********/
#if defined(BSP_USING_DAC1)
    #define DAC1_CH1_PORT                   (GPIO_PORT_A)
    #define DAC1_CH1_PIN                    (GPIO_PIN_04)
    #define DAC1_CH2_PORT                   (GPIO_PORT_A)
    #define DAC1_CH2_PIN                    (GPIO_PIN_05)
#endif
#if defined(BSP_USING_DAC2)
    #define DAC2_CH1_PORT                   (GPIO_PORT_A)
    #define DAC2_CH1_PIN                    (GPIO_PIN_06)
#endif

/***********  CAN configure *********/
#if defined(BSP_USING_MCAN1)
    #define MCAN1_TX_PORT                   (GPIO_PORT_A)
    #define MCAN1_TX_PIN                    (GPIO_PIN_02)
    #define MCAN1_TX_PIN_FUNC               (GPIO_FUNC_54)

    #define MCAN1_RX_PORT                   (GPIO_PORT_C)
    #define MCAN1_RX_PIN                    (GPIO_PIN_05)
    #define MCAN1_RX_PIN_FUNC               (GPIO_FUNC_55)

    #define MCAN1_PHY_STBY_PORT             (GPIO_PORT_B)
    #define MCAN1_PHY_STBY_PIN              (GPIO_PIN_01)
#endif

#if defined(BSP_USING_MCAN2)
    #define MCAN2_TX_PORT                   (GPIO_PORT_B)
    #define MCAN2_TX_PIN                    (GPIO_PIN_11)
    #define MCAN2_TX_PIN_FUNC               (GPIO_FUNC_56)

    #define MCAN2_RX_PORT                   (GPIO_PORT_B)
    #define MCAN2_RX_PIN                    (GPIO_PIN_10)
    #define MCAN2_RX_PIN_FUNC               (GPIO_FUNC_57)

    #define MCAN2_PHY_STBY_PORT             (GPIO_PORT_B)
    #define MCAN2_PHY_STBY_PIN              (GPIO_PIN_02)
#endif

/************************* SPI port ***********************/
#if defined(BSP_USING_SPI1)
    #define SPI1_CS_PORT                (GPIO_PORT_C)
    #define SPI1_CS_PIN                 (GPIO_PIN_01)

    #define SPI1_SCK_PORT               (GPIO_PORT_B)
    #define SPI1_SCK_PIN                (GPIO_PIN_05)
    #define SPI1_SCK_FUNC               (GPIO_FUNC_49)

    #define SPI1_MOSI_PORT              (GPIO_PORT_A)
    #define SPI1_MOSI_PIN               (GPIO_PIN_00)
    #define SPI1_MOSI_FUNC              (GPIO_FUNC_50)

    #define SPI1_MISO_PORT              (GPIO_PORT_A)
    #define SPI1_MISO_PIN               (GPIO_PIN_01)
    #define SPI1_MISO_FUNC              (GPIO_FUNC_51)
#endif

/************************ RTC/PM *****************************/
#if defined(BSP_USING_RTC) || defined(RT_USING_PM)
    #if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)
        #define XTAL32_PORT                     (GPIO_PORT_C)
        #define XTAL32_PIN                      (GPIO_PIN_14 | GPIO_PIN_15)
    #endif
#endif

#if defined(RT_USING_PWM)
    /***********  PWM_TMRA configure *********/
    #if defined(BSP_USING_PWM_TMRA_1)
        #if defined(BSP_USING_PWM_TMRA_1_CH1)
            #define PWM_TMRA_1_CH1_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH1_PIN              (GPIO_PIN_00)
            #define PWM_TMRA_1_CH1_PIN_FUNC         (GPIO_FUNC_15)
        #endif
        #if defined(BSP_USING_PWM_TMRA_1_CH2)
            #define PWM_TMRA_1_CH2_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH2_PIN              (GPIO_PIN_01)
            #define PWM_TMRA_1_CH2_PIN_FUNC         (GPIO_FUNC_15)
        #endif
        #if defined(BSP_USING_PWM_TMRA_1_CH3)
            #define PWM_TMRA_1_CH3_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH3_PIN              (GPIO_PIN_02)
            #define PWM_TMRA_1_CH3_PIN_FUNC         (GPIO_FUNC_15)
        #endif
        #if defined(BSP_USING_PWM_TMRA_1_CH4)
            #define PWM_TMRA_1_CH4_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH4_PIN              (GPIO_PIN_03)
            #define PWM_TMRA_1_CH4_PIN_FUNC         (GPIO_FUNC_15)
        #endif
    #endif

    /***********  PWM_TMR4 configure *********/
    #if defined(BSP_USING_PWM_TMR4_1)
        #if defined(BSP_USING_PWM_TMR4_1_OUH)
            #define PWM_TMR4_1_OUH_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OUH_PIN              (GPIO_PIN_02)
            #define PWM_TMR4_1_OUH_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OUL)
            #define PWM_TMR4_1_OUL_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OUL_PIN              (GPIO_PIN_01)
            #define PWM_TMR4_1_OUL_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVH)
            #define PWM_TMR4_1_OVH_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OVH_PIN              (GPIO_PIN_06)
            #define PWM_TMR4_1_OVH_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVL)
            #define PWM_TMR4_1_OVL_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OVL_PIN              (GPIO_PIN_04)
            #define PWM_TMR4_1_OVL_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWH)
            #define PWM_TMR4_1_OWH_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OWH_PIN              (GPIO_PIN_07)
            #define PWM_TMR4_1_OWH_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWL)
            #define PWM_TMR4_1_OWL_PORT             (GPIO_PORT_B)
            #define PWM_TMR4_1_OWL_PIN              (GPIO_PIN_02)
            #define PWM_TMR4_1_OWL_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OXH)
            #define PWM_TMR4_1_OXH_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OXH_PIN              (GPIO_PIN_01)
            #define PWM_TMR4_1_OXH_PIN_FUNC         (GPIO_FUNC_23)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OXL)
            #define PWM_TMR4_1_OXL_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OXL_PIN              (GPIO_PIN_00)
            #define PWM_TMR4_1_OXL_PIN_FUNC         (GPIO_FUNC_23)
        #endif
    #endif

    /***********  PWM_TMR6 configure *********/
    #if defined(BSP_USING_PWM_TMR6_1)
        #if defined(BSP_USING_PWM_TMR6_1_A)
            #define PWM_TMR6_1_A_PORT               (GPIO_PORT_C)
            #define PWM_TMR6_1_A_PIN                (GPIO_PIN_00)
            #define PWM_TMR6_1_A_PIN_FUNC           (GPIO_FUNC_12)
        #endif
        #if defined(BSP_USING_PWM_TMR6_1_B)
            #define PWM_TMR6_1_B_PORT               (GPIO_PORT_A)
            #define PWM_TMR6_1_B_PIN                (GPIO_PIN_00)
            #define PWM_TMR6_1_B_PIN_FUNC           (GPIO_FUNC_12)
        #endif
    #endif

#endif

#if defined(BSP_USING_INPUT_CAPTURE)
    #define INPUT_CAPTURE_TMR6_FUNC                 (GPIO_FUNC_14)
    #if defined(BSP_USING_INPUT_CAPTURE_TMR6_1)
        #define INPUT_CAPTURE_TMR6_1_PORT           (GPIO_PORT_C)
        #define INPUT_CAPTURE_TMR6_1_PIN            (GPIO_PIN_06)
    #endif
    #if defined(BSP_USING_INPUT_CAPTURE_TMR6_2)
        #define INPUT_CAPTURE_TMR6_2_PORT           (GPIO_PORT_C)
        #define INPUT_CAPTURE_TMR6_2_PIN            (GPIO_PIN_07)
    #endif
    #if defined(BSP_USING_INPUT_CAPTURE_TMR6_3)
        #define INPUT_CAPTURE_TMR6_3_PORT           (GPIO_PORT_B)
        #define INPUT_CAPTURE_TMR6_3_PIN            (GPIO_PIN_02)
    #endif
#endif


/*********** TMRA_PULSE_ENCODER configure *********/
#if defined(RT_USING_PULSE_ENCODER)
    #if defined(BSP_USING_TMRA_PULSE_ENCODER)
        #if defined(BSP_USING_PULSE_ENCODER_TMRA_1)
            #define PULSE_ENCODER_TMRA_1_A_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMRA_1_A_PIN       (GPIO_PIN_08)
            #define PULSE_ENCODER_TMRA_1_A_PIN_FUNC  (GPIO_FUNC_4)
            #define PULSE_ENCODER_TMRA_1_B_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMRA_1_B_PIN       (GPIO_PIN_09)
            #define PULSE_ENCODER_TMRA_1_B_PIN_FUNC  (GPIO_FUNC_4)
        #endif /* BSP_USING_PULSE_ENCODER_TMRA_1 */
    #endif /* BSP_USING_TMRA_PULSE_ENCODER */

    #if defined(BSP_USING_TMR6_PULSE_ENCODER)
        #if defined(BSP_USING_PULSE_ENCODER_TMR6_1)
            #define PULSE_ENCODER_TMR6_1_A_PORT      (GPIO_PORT_B)
            #define PULSE_ENCODER_TMR6_1_A_PIN       (GPIO_PIN_05)
            #define PULSE_ENCODER_TMR6_1_A_PIN_FUNC  (GPIO_FUNC_3)
            #define PULSE_ENCODER_TMR6_1_B_PORT      (GPIO_PORT_B)
            #define PULSE_ENCODER_TMR6_1_B_PIN       (GPIO_PIN_13)
            #define PULSE_ENCODER_TMR6_1_B_PIN_FUNC  (GPIO_FUNC_3)
        #endif /* BSP_USING_PULSE_ENCODER_TMR6_1 */
    #endif /* BSP_USING_TMR6_PULSE_ENCODER */
#endif /* RT_USING_PULSE_ENCODER */

#endif

