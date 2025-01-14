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
#define XTAL_PORT                       (GPIO_PORT_F)
#define XTAL_IN_PIN                     (GPIO_PIN_00)
#define XTAL_OUT_PIN                    (GPIO_PIN_01)

/************************ USART port **********************/
#if defined(BSP_USING_UART1)
    #define USART1_RX_PORT                  (GPIO_PORT_E)
    #define USART1_RX_PIN                   (GPIO_PIN_03)
    #define USART1_RX_FUNC                  (GPIO_FUNC_33)

    #define USART1_TX_PORT                  (GPIO_PORT_E)
    #define USART1_TX_PIN                   (GPIO_PIN_04)
    #define USART1_TX_FUNC                  (GPIO_FUNC_32)
#endif

#if defined(BSP_USING_UART2)
    #define USART2_RX_PORT                  (GPIO_PORT_F)
    #define USART2_RX_PIN                   (GPIO_PIN_02)
    #define USART2_RX_FUNC                  (GPIO_FUNC_35)

    #define USART2_TX_PORT                  (GPIO_PORT_C)
    #define USART2_TX_PIN                   (GPIO_PIN_13)
    #define USART2_TX_FUNC                  (GPIO_FUNC_34)
#endif

#if defined(BSP_USING_UART5)
    #define USART5_RX_PORT                  (GPIO_PORT_E)
    #define USART5_RX_PIN                   (GPIO_PIN_05)
    #define USART5_RX_FUNC                  (GPIO_FUNC_41)

    #define USART5_TX_PORT                  (GPIO_PORT_E)
    #define USART5_TX_PIN                   (GPIO_PIN_06)
    #define USART5_TX_FUNC                  (GPIO_FUNC_40)
#endif

/************************ I2C port **********************/
#if defined(BSP_USING_I2C1)
    #define I2C1_SDA_PORT                   (GPIO_PORT_B)
    #define I2C1_SDA_PIN                    (GPIO_PIN_09)
    #define I2C1_SDA_FUNC                   (GPIO_FUNC_54)

    #define I2C1_SCL_PORT                   (GPIO_PORT_B)
    #define I2C1_SCL_PIN                    (GPIO_PIN_06)
    #define I2C1_SCL_FUNC                   (GPIO_FUNC_55)
#endif
// TODO, ch2/3 for test only
#if defined(BSP_USING_I2C2)
    #define I2C2_SDA_PORT                   (GPIO_PORT_A)
    #define I2C2_SDA_PIN                    (GPIO_PIN_09)
    #define I2C2_SDA_FUNC                   (GPIO_FUNC_56)

    #define I2C2_SCL_PORT                   (GPIO_PORT_A)
    #define I2C2_SCL_PIN                    (GPIO_PIN_10)
    #define I2C2_SCL_FUNC                   (GPIO_FUNC_57)
#endif

#if defined(BSP_USING_I2C3)
    #define I2C3_SDA_PORT                   (GPIO_PORT_A)
    #define I2C3_SDA_PIN                    (GPIO_PIN_09)
    #define I2C3_SDA_FUNC                   (GPIO_FUNC_58)

    #define I2C3_SCL_PORT                   (GPIO_PORT_A)
    #define I2C3_SCL_PIN                    (GPIO_PIN_10)
    #define I2C3_SCL_FUNC                   (GPIO_FUNC_59)
#endif

/***********  ADC configure *********/
#if defined(BSP_USING_ADC1)
    #define ADC1_CH_PORT                    (GPIO_PORT_C)   /* Default ADC123_IN10 */
    #define ADC1_CH_PIN                     (GPIO_PIN_00)
#endif

#if defined(BSP_USING_ADC2)
    #define ADC2_CH_PORT                    (GPIO_PORT_C)   /* Default ADC123_IN11 */
    #define ADC2_CH_PIN                     (GPIO_PIN_01)
#endif

#if defined(BSP_USING_ADC3)
    #define ADC3_CH_PORT                    (GPIO_PORT_C)   /* Default ADC123_IN12 */
    #define ADC3_CH_PIN                     (GPIO_PIN_02)
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
    #define CAN1_TX_PORT                    (GPIO_PORT_D)
    #define CAN1_TX_PIN                     (GPIO_PIN_12)
    #define CAN1_TX_PIN_FUNC                (GPIO_FUNC_60)

    #define CAN1_RX_PORT                    (GPIO_PORT_D)
    #define CAN1_RX_PIN                     (GPIO_PIN_13)
    #define CAN1_RX_PIN_FUNC                (GPIO_FUNC_61)
#endif

#if defined(BSP_USING_CAN2)
    #define CAN2_TX_PORT                    (GPIO_PORT_C)
    #define CAN2_TX_PIN                     (GPIO_PIN_07)
    #define CAN2_TX_PIN_FUNC                (GPIO_FUNC_60)

    #define CAN2_RX_PORT                    (GPIO_PORT_D)
    #define CAN2_RX_PIN                     (GPIO_PIN_11)
    #define CAN2_RX_PIN_FUNC                (GPIO_FUNC_63)
#endif

#if defined(BSP_USING_CAN3)
    #define CAN3_TX_PORT                    (GPIO_PORT_C)
    #define CAN3_TX_PIN                     (GPIO_PIN_06)
    #define CAN3_TX_PIN_FUNC                (GPIO_FUNC_62)

    #define CAN3_RX_PORT                    (GPIO_PORT_A)
    #define CAN3_RX_PIN                     (GPIO_PIN_05)
    #define CAN3_RX_PIN_FUNC                (GPIO_FUNC_63)
#endif

/************************* SPI port ***********************/
#if defined(BSP_USING_SPI1)
    #define SPI1_CS_PORT                (GPIO_PORT_B)
    #define SPI1_CS_PIN                 (GPIO_PIN_12)

    #define SPI1_SCK_PORT               (GPIO_PORT_B)
    #define SPI1_SCK_PIN                (GPIO_PIN_13)
    #define SPI1_SCK_FUNC               (GPIO_FUNC_6)

    #define SPI1_MOSI_PORT              (GPIO_PORT_A)
    #define SPI1_MOSI_PIN               (GPIO_PIN_07)
    #define SPI1_MOSI_FUNC              (GPIO_FUNC_6)

    #define SPI1_MISO_PORT              (GPIO_PORT_B)
    #define SPI1_MISO_PIN               (GPIO_PIN_14)
    #define SPI1_MISO_FUNC              (GPIO_FUNC_6)

    #define SPI1_WP_PORT                (GPIO_PORT_B)
    #define SPI1_WP_PIN                 (GPIO_PIN_10)

    #define SPI1_HOLD_PORT              (GPIO_PORT_B)
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

    #if defined(BSP_USING_PWM_TMRA_2)
        #if defined(BSP_USING_PWM_TMRA_2_CH1)
            #define PWM_TMRA_2_CH1_PORT             (GPIO_PORT_C)
            #define PWM_TMRA_2_CH1_PIN              (GPIO_PIN_06)
            #define PWM_TMRA_2_CH1_PIN_FUNC         (GPIO_FUNC_16)
        #endif
        #if defined(BSP_USING_PWM_TMRA_2_CH2)
            #define PWM_TMRA_2_CH2_PORT             (GPIO_PORT_C)
            #define PWM_TMRA_2_CH2_PIN              (GPIO_PIN_07)
            #define PWM_TMRA_2_CH2_PIN_FUNC         (GPIO_FUNC_16)
        #endif
        #if defined(BSP_USING_PWM_TMRA_2_CH3)
            #define PWM_TMRA_2_CH3_PORT             (GPIO_PORT_C)
            #define PWM_TMRA_2_CH3_PIN              (GPIO_PIN_08)
            #define PWM_TMRA_2_CH3_PIN_FUNC         (GPIO_FUNC_16)
        #endif
        #if defined(BSP_USING_PWM_TMRA_2_CH4)
            #define PWM_TMRA_2_CH4_PORT             (GPIO_PORT_C)
            #define PWM_TMRA_2_CH4_PIN              (GPIO_PIN_09)
            #define PWM_TMRA_2_CH4_PIN_FUNC         (GPIO_FUNC_16)
        #endif
    #endif

    /***********  PWM_TMR4 configure *********/
    #if defined(BSP_USING_PWM_TMR4_1)
        #if defined(BSP_USING_PWM_TMR4_1_OUH)
            #define PWM_TMR4_1_OUH_PORT             (GPIO_PORT_B)
            #define PWM_TMR4_1_OUH_PIN              (GPIO_PIN_14)
            #define PWM_TMR4_1_OUH_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OUL)
            #define PWM_TMR4_1_OUL_PORT             (GPIO_PORT_B)
            #define PWM_TMR4_1_OUL_PIN              (GPIO_PIN_15)
            #define PWM_TMR4_1_OUL_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVH)
            #define PWM_TMR4_1_OVH_PORT             (GPIO_PORT_D)
            #define PWM_TMR4_1_OVH_PIN              (GPIO_PIN_08)
            #define PWM_TMR4_1_OVH_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVL)
            #define PWM_TMR4_1_OVL_PORT             (GPIO_PORT_D)
            #define PWM_TMR4_1_OVL_PIN              (GPIO_PIN_09)
            #define PWM_TMR4_1_OVL_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWH)
            #define PWM_TMR4_1_OWH_PORT             (GPIO_PORT_D)
            #define PWM_TMR4_1_OWH_PIN              (GPIO_PIN_10)
            #define PWM_TMR4_1_OWH_PIN_FUNC         (GPIO_FUNC_20)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWL)
            #define PWM_TMR4_1_OWL_PORT             (GPIO_PORT_D)
            #define PWM_TMR4_1_OWL_PIN              (GPIO_PIN_11)
            #define PWM_TMR4_1_OWL_PIN_FUNC         (GPIO_FUNC_20)
        #endif
    #endif

    /***********  PWM_TMR6 configure *********/
    #if defined(BSP_USING_PWM_TMR6_1)
        #if defined(BSP_USING_PWM_TMR6_1_A)
            #define PWM_TMR6_1_A_PORT               (GPIO_PORT_A)
            #define PWM_TMR6_1_A_PIN                (GPIO_PIN_08)
            #define PWM_TMR6_1_A_PIN_FUNC           (GPIO_FUNC_13)
        #endif
        #if defined(BSP_USING_PWM_TMR6_1_B)
            #define PWM_TMR6_1_B_PORT               (GPIO_PORT_C)
            #define PWM_TMR6_1_B_PIN                (GPIO_PIN_10)
            #define PWM_TMR6_1_B_PIN_FUNC           (GPIO_FUNC_12)
        #endif
    #endif

#endif

#if defined(BSP_USING_QSPI)
    #ifndef BSP_QSPI_USING_SOFT_CS
        /* QSSN */
        #define QSPI_FLASH_CS_PORT              (GPIO_PORT_B)
        #define QSPI_FLASH_CS_PIN               (GPIO_PIN_12)
        #define QSPI_FLASH_CS_FUNC              (GPIO_FUNC_5)
    #endif
    /* QSCK */
    #define QSPI_FLASH_SCK_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_SCK_PIN              (GPIO_PIN_13)
    #define QSPI_FLASH_SCK_FUNC             (GPIO_FUNC_5)
    /* QSIO0 */
    #define QSPI_FLASH_IO0_PORT             (GPIO_PORT_A)
    #define QSPI_FLASH_IO0_PIN              (GPIO_PIN_07)
    #define QSPI_FLASH_IO0_FUNC             (GPIO_FUNC_5)
    /* QSIO1 */
    #define QSPI_FLASH_IO1_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_IO1_PIN              (GPIO_PIN_14)
    #define QSPI_FLASH_IO1_FUNC             (GPIO_FUNC_5)
    /* QSIO2 */
    #define QSPI_FLASH_IO2_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_IO2_PIN              (GPIO_PIN_10)
    #define QSPI_FLASH_IO2_FUNC             (GPIO_FUNC_4)
    /* QSIO3 */
    #define QSPI_FLASH_IO3_PORT             (GPIO_PORT_B)
    #define QSPI_FLASH_IO3_PIN              (GPIO_PIN_11)
    #define QSPI_FLASH_IO3_FUNC             (GPIO_FUNC_4)
#endif

/*********** TMRA_PULSE_ENCODER configure *********/
#if defined(RT_USING_PULSE_ENCODER)
    #if defined(BSP_USING_TMRA_PULSE_ENCODER)
        #if defined(BSP_USING_PULSE_ENCODER_TMRA_1)
            #define PULSE_ENCODER_TMRA_1_A_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMRA_1_A_PIN       (GPIO_PIN_00)
            #define PULSE_ENCODER_TMRA_1_A_PIN_FUNC  (GPIO_FUNC_15)
            #define PULSE_ENCODER_TMRA_1_B_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMRA_1_B_PIN       (GPIO_PIN_01)
            #define PULSE_ENCODER_TMRA_1_B_PIN_FUNC  (GPIO_FUNC_15)
        #endif /* BSP_USING_PULSE_ENCODER_TMRA_1 */
    #endif /* BSP_USING_TMRA_PULSE_ENCODER */

    #if defined(BSP_USING_TMR6_PULSE_ENCODER)
        #if defined(BSP_USING_PULSE_ENCODER_TMR6_1)
            #define PULSE_ENCODER_TMR6_1_A_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMR6_1_A_PIN       (GPIO_PIN_03)
            #define PULSE_ENCODER_TMR6_1_A_PIN_FUNC  (GPIO_FUNC_11)
            #define PULSE_ENCODER_TMR6_1_B_PORT      (GPIO_PORT_A)
            #define PULSE_ENCODER_TMR6_1_B_PIN       (GPIO_PIN_07)
            #define PULSE_ENCODER_TMR6_1_B_PIN_FUNC  (GPIO_FUNC_14)
        #endif /* BSP_USING_PULSE_ENCODER_TMR6_1 */
    #endif /* BSP_USING_TMR6_PULSE_ENCODER */
#endif /* RT_USING_PULSE_ENCODER */

#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    #if defined(BSP_USING_USBFS)
        /* USBFS Core*/
        #define USBF_DP_PORT                    (GPIO_PORT_A)
        #define USBF_DP_PIN                     (GPIO_PIN_12)
        #define USBF_DM_PORT                    (GPIO_PORT_A)
        #define USBF_DM_PIN                     (GPIO_PIN_11)
        #define USBF_VBUS_PORT                  (GPIO_PORT_A)
        #define USBF_VBUS_PIN                   (GPIO_PIN_09)
        #define USBF_DRVVBUS_PORT               (GPIO_PORT_C)
        #define USBF_DRVVBUS_PIN                (GPIO_PIN_09)
    #endif
#endif

#endif

