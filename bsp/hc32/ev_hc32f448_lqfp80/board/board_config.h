/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
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
#define XTAL_PORT                       (GPIO_PORT_H)
#define XTAL_IN_PIN                     (GPIO_PIN_00)
#define XTAL_OUT_PIN                    (GPIO_PIN_01)

/************************ USART port **********************/
#if defined(BSP_USING_UART1)
    #define USART1_RX_PORT                  (GPIO_PORT_A)
    #define USART1_RX_PIN                   (GPIO_PIN_10)
    #define USART1_RX_FUNC                  (GPIO_FUNC_33)

    #define USART1_TX_PORT                  (GPIO_PORT_A)
    #define USART1_TX_PIN                   (GPIO_PIN_09)
    #define USART1_TX_FUNC                  (GPIO_FUNC_32)
#endif

#if defined(BSP_USING_UART2)
    #define USART2_RX_PORT                  (GPIO_PORT_C)
    #define USART2_RX_PIN                   (GPIO_PIN_11)
    #define USART2_RX_FUNC                  (GPIO_FUNC_37)

    #define USART2_TX_PORT                  (GPIO_PORT_C)
    #define USART2_TX_PIN                   (GPIO_PIN_10)
    #define USART2_TX_FUNC                  (GPIO_FUNC_36)
#endif

#if defined(BSP_USING_UART6)
    #define USART6_RX_PORT                  (GPIO_PORT_D)
    #define USART6_RX_PIN                   (GPIO_PIN_01)
    #define USART6_RX_FUNC                  (GPIO_FUNC_55)

    #define USART6_TX_PORT                  (GPIO_PORT_D)
    #define USART6_TX_PIN                   (GPIO_PIN_02)
    #define USART6_TX_FUNC                  (GPIO_FUNC_54)
#endif

/************************ I2C port **********************/
#if defined(BSP_USING_I2C1)
    #define I2C1_SDA_PORT                   (GPIO_PORT_E)
    #define I2C1_SDA_PIN                    (GPIO_PIN_00)
    #define I2C1_SDA_FUNC                   (GPIO_FUNC_48)

    #define I2C1_SCL_PORT                   (GPIO_PORT_E)
    #define I2C1_SCL_PIN                    (GPIO_PIN_01)
    #define I2C1_SCL_FUNC                   (GPIO_FUNC_49)
#endif

#if defined(BSP_USING_I2C2) // TODO, ch2 for test only
    #define I2C2_SDA_PORT                   (GPIO_PORT_A)
    #define I2C2_SDA_PIN                    (GPIO_PIN_09)
    #define I2C2_SDA_FUNC                   (GPIO_FUNC_50)

    #define I2C2_SCL_PORT                   (GPIO_PORT_A)
    #define I2C2_SCL_PIN                    (GPIO_PIN_10)
    #define I2C2_SCL_FUNC                   (GPIO_FUNC_51)
#endif


/***********  ADC configure *********/
#if defined(BSP_USING_ADC1)
    #define ADC1_CH_PORT                    (GPIO_PORT_C)
    #define ADC1_CH_PIN                     (GPIO_PIN_00)
#endif

#if defined(BSP_USING_ADC2)
    #define ADC2_CH_PORT                    (GPIO_PORT_C)
    #define ADC2_CH_PIN                     (GPIO_PIN_01)
#endif

#if defined(BSP_USING_ADC3)
    #define ADC3_CH_PORT                    (GPIO_PORT_E)
    #define ADC3_CH_PIN                     (GPIO_PIN_03)
#endif

/***********  DAC configure *********/
#if defined(BSP_USING_DAC1)
    #define DAC1_CH1_PORT                   (GPIO_PORT_A)
    #define DAC1_CH1_PIN                    (GPIO_PIN_04)
    #define DAC1_CH2_PORT                   (GPIO_PORT_A)
    #define DAC1_CH2_PIN                    (GPIO_PIN_05)
#endif

/***********  CAN configure *********/
#if defined(BSP_USING_CAN1)
    #define CAN1_TX_PORT                    (GPIO_PORT_C)
    #define CAN1_TX_PIN                     (GPIO_PIN_12)
    #define CAN1_TX_PIN_FUNC                (GPIO_FUNC_56)

    #define CAN1_RX_PORT                    (GPIO_PORT_D)
    #define CAN1_RX_PIN                     (GPIO_PIN_00)
    #define CAN1_RX_PIN_FUNC                (GPIO_FUNC_57)
#endif

#if defined(BSP_USING_CAN2)
    #define CAN2_TX_PORT                    (GPIO_PORT_H)
    #define CAN2_TX_PIN                     (GPIO_PIN_02)
    #define CAN2_TX_PIN_FUNC                (GPIO_FUNC_56)

    #define CAN2_RX_PORT                    (GPIO_PORT_E)
    #define CAN2_RX_PIN                     (GPIO_PIN_04)
    #define CAN2_RX_PIN_FUNC                (GPIO_FUNC_57)
#endif

/************************* SPI port ***********************/
#if defined(BSP_USING_SPI1)
    #define SPI1_CS_PORT                (GPIO_PORT_C)
    #define SPI1_CS_PIN                 (GPIO_PIN_07)

    #define SPI1_SCK_PORT               (GPIO_PORT_B)
    #define SPI1_SCK_PIN                (GPIO_PIN_14)
    #define SPI1_SCK_FUNC               (GPIO_FUNC_47)

    #define SPI1_MOSI_PORT              (GPIO_PORT_B)
    #define SPI1_MOSI_PIN               (GPIO_PIN_13)
    #define SPI1_MOSI_FUNC              (GPIO_FUNC_44)

    #define SPI1_MISO_PORT              (GPIO_PORT_D)
    #define SPI1_MISO_PIN               (GPIO_PIN_09)
    #define SPI1_MISO_FUNC              (GPIO_FUNC_45)

    #define SPI1_WP_PORT                (GPIO_PORT_D)
    #define SPI1_WP_PIN                 (GPIO_PIN_10)

    #define SPI1_HOLD_PORT              (GPIO_PORT_D)
    #define SPI1_HOLD_PIN               (GPIO_PIN_11)
#endif

/************************ RTC/PM *****************************/
#if defined(BSP_USING_RTC) || defined(RT_USING_PM)
    #if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)
        #define XTAL32_PORT                     (GPIO_PORT_C)
        #define XTAL32_IN_PIN                   (GPIO_PIN_14)
        #define XTAL32_OUT_PIN                  (GPIO_PIN_15)
    #endif
#endif

#if defined(RT_USING_PWM)
    /***********  PWM_TMRA configure *********/
    #if defined(BSP_USING_PWM_TMRA_1)
        #if defined(BSP_USING_PWM_TMRA_1_CH1)
            #define PWM_TMRA_1_CH1_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH1_PIN              (GPIO_PIN_08)
            #define PWM_TMRA_1_CH1_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_1_CH2)
            #define PWM_TMRA_1_CH2_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH2_PIN              (GPIO_PIN_09)
            #define PWM_TMRA_1_CH2_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_1_CH3)
            #define PWM_TMRA_1_CH3_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH3_PIN              (GPIO_PIN_10)
            #define PWM_TMRA_1_CH3_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_1_CH4)
            #define PWM_TMRA_1_CH4_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_1_CH4_PIN              (GPIO_PIN_11)
            #define PWM_TMRA_1_CH4_PIN_FUNC         (GPIO_FUNC_4)
        #endif
    #endif

    #if defined(BSP_USING_PWM_TMRA_2)
        #if defined(BSP_USING_PWM_TMRA_2_CH1)
            #define PWM_TMRA_2_CH1_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_2_CH1_PIN              (GPIO_PIN_00)
            #define PWM_TMRA_2_CH1_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_2_CH2)
            #define PWM_TMRA_2_CH2_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_2_CH2_PIN              (GPIO_PIN_01)
            #define PWM_TMRA_2_CH2_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_2_CH3)
            #define PWM_TMRA_2_CH3_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_2_CH3_PIN              (GPIO_PIN_02)
            #define PWM_TMRA_2_CH3_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_2_CH4)
            #define PWM_TMRA_2_CH4_PORT             (GPIO_PORT_A)
            #define PWM_TMRA_2_CH4_PIN              (GPIO_PIN_03)
            #define PWM_TMRA_2_CH4_PIN_FUNC         (GPIO_FUNC_4)
        #endif
    #endif

    /***********  PWM_TMR4 configure *********/
    #if defined(BSP_USING_PWM_TMR4_1)
        #if defined(BSP_USING_PWM_TMR4_1_OUH)
            #define PWM_TMR4_1_OUH_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OUH_PIN              (GPIO_PIN_08)
            #define PWM_TMR4_1_OUH_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OUL)
            #define PWM_TMR4_1_OUL_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OUL_PIN              (GPIO_PIN_07)
            #define PWM_TMR4_1_OUL_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVH)
            #define PWM_TMR4_1_OVH_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OVH_PIN              (GPIO_PIN_09)
            #define PWM_TMR4_1_OVH_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVL)
            #define PWM_TMR4_1_OVL_PORT             (GPIO_PORT_B)
            #define PWM_TMR4_1_OVL_PIN              (GPIO_PIN_00)
            #define PWM_TMR4_1_OVL_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWH)
            #define PWM_TMR4_1_OWH_PORT             (GPIO_PORT_A)
            #define PWM_TMR4_1_OWH_PIN              (GPIO_PIN_10)
            #define PWM_TMR4_1_OWH_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWL)
            #define PWM_TMR4_1_OWL_PORT             (GPIO_PORT_B)
            #define PWM_TMR4_1_OWL_PIN              (GPIO_PIN_01)
            #define PWM_TMR4_1_OWL_PIN_FUNC         (GPIO_FUNC_2)
        #endif
    #endif

    /***********  PWM_TMR6 configure *********/
    #if defined(BSP_USING_PWM_TMR6_1)
        #if defined(BSP_USING_PWM_TMR6_1_A)
            #define PWM_TMR6_1_A_PORT               (GPIO_PORT_A)
            #define PWM_TMR6_1_A_PIN                (GPIO_PIN_08)
            #define PWM_TMR6_1_A_PIN_FUNC           (GPIO_FUNC_3)
        #endif
        #if defined(BSP_USING_PWM_TMR6_1_B)
            #define PWM_TMR6_1_B_PORT               (GPIO_PORT_A)
            #define PWM_TMR6_1_B_PIN                (GPIO_PIN_07)
            #define PWM_TMR6_1_B_PIN_FUNC           (GPIO_FUNC_3)
        #endif
    #endif

#endif

#if defined(BSP_USING_QSPI)
    #ifndef BSP_QSPI_USING_SOFT_CS
        /* QSSN */
        #define QSPI_FLASH_CS_PORT              (GPIO_PORT_C)
        #define QSPI_FLASH_CS_PIN               (GPIO_PIN_07)
        #define QSPI_FLASH_CS_FUNC              (GPIO_FUNC_7)
    #endif
    /* QSCK */
    #define QSPI_FLASH_SCK_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_SCK_PIN              (GPIO_PIN_14)
    #define QSPI_FLASH_SCK_FUNC             (GPIO_FUNC_7)
    /* QSIO0 */
    #define QSPI_FLASH_IO0_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_IO0_PIN              (GPIO_PIN_13)
    #define QSPI_FLASH_IO0_FUNC             (GPIO_FUNC_7)
    /* QSIO1 */
    #define QSPI_FLASH_IO1_PORT             (GPIO_PORT_D)
    #define QSPI_FLASH_IO1_PIN              (GPIO_PIN_09)
    #define QSPI_FLASH_IO1_FUNC             (GPIO_FUNC_7)
    /* QSIO2 */
    #define QSPI_FLASH_IO2_PORT             (GPIO_PORT_D)
    #define QSPI_FLASH_IO2_PIN              (GPIO_PIN_10)
    #define QSPI_FLASH_IO2_FUNC             (GPIO_FUNC_7)
    /* QSIO3 */
    #define QSPI_FLASH_IO3_PORT             (GPIO_PORT_D)
    #define QSPI_FLASH_IO3_PIN              (GPIO_PIN_11)
    #define QSPI_FLASH_IO3_FUNC             (GPIO_FUNC_7)
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
            #define PULSE_ENCODER_TMR6_1_A_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMR6_1_A_PIN       (GPIO_PIN_08)
            #define PULSE_ENCODER_TMR6_1_A_PIN_FUNC  (GPIO_FUNC_3)
            #define PULSE_ENCODER_TMR6_1_B_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMR6_1_B_PIN       (GPIO_PIN_07)
            #define PULSE_ENCODER_TMR6_1_B_PIN_FUNC  (GPIO_FUNC_3)
        #endif /* BSP_USING_PULSE_ENCODER_TMR6_1 */
    #endif /* BSP_USING_TMR6_PULSE_ENCODER */
#endif /* RT_USING_PULSE_ENCODER */

#endif

