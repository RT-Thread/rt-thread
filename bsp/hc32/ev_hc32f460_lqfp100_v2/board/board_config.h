/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */


#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include <rtconfig.h>
#include "hc32_ll.h"
#include "drv_config.h"


/************************* XTAL port **********************/
#define XTAL_PORT                       (GPIO_PORT_H)
#define XTAL_IN_PIN                     (GPIO_PIN_01)
#define XTAL_OUT_PIN                    (GPIO_PIN_00)

/************************ USART port **********************/
#if defined(BSP_USING_UART2)
    #define USART2_RX_PORT                  (GPIO_PORT_A)
    #define USART2_RX_PIN                   (GPIO_PIN_03)
    #define USART2_RX_FUNC                  (GPIO_FUNC_37)

    #define USART2_TX_PORT                  (GPIO_PORT_A)
    #define USART2_TX_PIN                   (GPIO_PIN_02)
    #define USART2_TX_FUNC                  (GPIO_FUNC_36)
#endif

#if defined(BSP_USING_UART4)
    #define USART4_RX_PORT                  (GPIO_PORT_B)
    #define USART4_RX_PIN                   (GPIO_PIN_09)
    #define USART4_RX_FUNC                  (GPIO_FUNC_37)

    #define USART4_TX_PORT                  (GPIO_PORT_E)
    #define USART4_TX_PIN                   (GPIO_PIN_06)
    #define USART4_TX_FUNC                  (GPIO_FUNC_36)
#endif

/************************ I2C port **********************/
#if defined(BSP_USING_I2C3)
    #define I2C3_SDA_PORT                   (GPIO_PORT_B)
    #define I2C3_SDA_PIN                    (GPIO_PIN_05)
    #define I2C3_SDA_FUNC                   (GPIO_FUNC_48)

    #define I2C3_SCL_PORT                   (GPIO_PORT_E)
    #define I2C3_SCL_PIN                    (GPIO_PIN_15)
    #define I2C3_SCL_FUNC                   (GPIO_FUNC_49)
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

/***********  CAN configure *********/
#if defined(BSP_USING_CAN1)
    #define CAN1_TX_PORT                    (GPIO_PORT_B)
    #define CAN1_TX_PIN                     (GPIO_PIN_07)
    #define CAN1_TX_PIN_FUNC                (GPIO_FUNC_50)

    #define CAN1_RX_PORT                    (GPIO_PORT_B)
    #define CAN1_RX_PIN                     (GPIO_PIN_06)
    #define CAN1_RX_PIN_FUNC                (GPIO_FUNC_51)

    #define CAN1_STB_PORT                   (GPIO_PORT_D)
    #define CAN1_STB_PIN                    (GPIO_PIN_15)
#endif

/************************* SPI port ***********************/
#if defined(BSP_USING_SPI3)
    #define SPI3_CS_PORT                (GPIO_PORT_C)
    #define SPI3_CS_PIN                 (GPIO_PIN_07)

    #define SPI3_SCK_PORT               (GPIO_PORT_C)
    #define SPI3_SCK_PIN                (GPIO_PIN_06)
    #define SPI3_SCK_FUNC               (GPIO_FUNC_43)

    #define SPI3_MOSI_PORT              (GPIO_PORT_D)
    #define SPI3_MOSI_PIN               (GPIO_PIN_08)
    #define SPI3_MOSI_FUNC              (GPIO_FUNC_40)

    #define SPI3_MISO_PORT              (GPIO_PORT_D)
    #define SPI3_MISO_PIN               (GPIO_PIN_09)
    #define SPI3_MISO_FUNC              (GPIO_FUNC_41)

    #define SPI3_WP_PORT                (GPIO_PORT_D)
    #define SPI3_WP_PIN                 (GPIO_PIN_10)

    #define SPI3_HOLD_PORT              (GPIO_PORT_D)
    #define SPI3_HOLD_PIN               (GPIO_PIN_11)
#endif

/************************ SDIOC port **********************/
#if defined(BSP_USING_SDIO1)
    #define SDIOC1_CK_PORT                  (GPIO_PORT_C)
    #define SDIOC1_CK_PIN                   (GPIO_PIN_12)
    #define SDIOC1_CK_FUNC                  (GPIO_FUNC_9)

    #define SDIOC1_CMD_PORT                 (GPIO_PORT_D)
    #define SDIOC1_CMD_PIN                  (GPIO_PIN_02)
    #define SDIOC1_CMD_FUNC                 (GPIO_FUNC_9)

    #define SDIOC1_D0_PORT                  (GPIO_PORT_C)
    #define SDIOC1_D0_PIN                   (GPIO_PIN_08)
    #define SDIOC1_D0_FUNC                  (GPIO_FUNC_9)

    #define SDIOC1_D1_PORT                  (GPIO_PORT_C)
    #define SDIOC1_D1_PIN                   (GPIO_PIN_09)
    #define SDIOC1_D1_FUNC                  (GPIO_FUNC_9)

    #define SDIOC1_D2_PORT                  (GPIO_PORT_C)
    #define SDIOC1_D2_PIN                   (GPIO_PIN_10)
    #define SDIOC1_D2_FUNC                  (GPIO_FUNC_9)

    #define SDIOC1_D3_PORT                  (GPIO_PORT_C)
    #define SDIOC1_D3_PIN                   (GPIO_PIN_11)
    #define SDIOC1_D3_FUNC                  (GPIO_FUNC_9)
#endif

/************************ RTC/PM *****************************/
#if defined(BSP_USING_RTC) || defined(RT_USING_PM)
    #if defined(BSP_RTC_USING_XTAL32) || defined(RT_USING_PM)
        #define XTAL32_PORT                     (GPIO_PORT_C)
        #define XTAL32_IN_PIN                   (GPIO_PIN_15)
        #define XTAL32_OUT_PIN                  (GPIO_PIN_14)
    #endif
#endif

#if defined(RT_USING_PWM)
    /***********  PWM_TMRA configure *********/
    #if defined(BSP_USING_PWM_TMRA_4)
        #if defined(BSP_USING_PWM_TMRA_4_CH1)
            #define PWM_TMRA_4_CH1_PORT             (GPIO_PORT_D)
            #define PWM_TMRA_4_CH1_PIN              (GPIO_PIN_12)
            #define PWM_TMRA_4_CH1_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_4_CH2)
            #define PWM_TMRA_4_CH2_PORT             (GPIO_PORT_D)
            #define PWM_TMRA_4_CH2_PIN              (GPIO_PIN_13)
            #define PWM_TMRA_4_CH2_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_4_CH3)
            #define PWM_TMRA_4_CH3_PORT             (GPIO_PORT_D)
            #define PWM_TMRA_4_CH3_PIN              (GPIO_PIN_14)
            #define PWM_TMRA_4_CH3_PIN_FUNC         (GPIO_FUNC_4)
        #endif
        #if defined(BSP_USING_PWM_TMRA_4_CH4)
            #define PWM_TMRA_4_CH4_PORT             (GPIO_PORT_D)
            #define PWM_TMRA_4_CH4_PIN              (GPIO_PIN_15)
            #define PWM_TMRA_4_CH4_PIN_FUNC         (GPIO_FUNC_4)
        #endif
    #endif

    #if defined(BSP_USING_PWM_TMRA_5)
        #if defined(BSP_USING_PWM_TMRA_5_CH1)
            #define PWM_TMRA_5_CH1_PORT             (GPIO_PORT_C)
            #define PWM_TMRA_5_CH1_PIN              (GPIO_PIN_10)
            #define PWM_TMRA_5_CH1_PIN_FUNC         (GPIO_FUNC_5)
        #endif
        #if defined(BSP_USING_PWM_TMRA_5_CH2)
            #define PWM_TMRA_5_CH2_PORT             (GPIO_PORT_C)
            #define PWM_TMRA_5_CH2_PIN              (GPIO_PIN_11)
            #define PWM_TMRA_5_CH2_PIN_FUNC         (GPIO_FUNC_5)
        #endif
        #if defined(BSP_USING_PWM_TMRA_5_CH3)
            #define PWM_TMRA_5_CH3_PORT             (GPIO_PORT_C)
            #define PWM_TMRA_5_CH3_PIN              (GPIO_PIN_12)
            #define PWM_TMRA_5_CH3_PIN_FUNC         (GPIO_FUNC_5)
        #endif
        #if defined(BSP_USING_PWM_TMRA_5_CH4)
            #define PWM_TMRA_5_CH4_PORT             (GPIO_PORT_D)
            #define PWM_TMRA_5_CH4_PIN              (GPIO_PIN_00)
            #define PWM_TMRA_5_CH4_PIN_FUNC         (GPIO_FUNC_5)
        #endif
    #endif

    /***********  PWM_TMR4 configure *********/
    #if defined(BSP_USING_PWM_TMR4_1)
        #if defined(BSP_USING_PWM_TMR4_1_OUH)
            #define PWM_TMR4_1_OUH_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OUH_PIN              (GPIO_PIN_09)
            #define PWM_TMR4_1_OUH_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OUL)
            #define PWM_TMR4_1_OUL_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OUL_PIN              (GPIO_PIN_08)
            #define PWM_TMR4_1_OUL_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVH)
            #define PWM_TMR4_1_OVH_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OVH_PIN              (GPIO_PIN_11)
            #define PWM_TMR4_1_OVH_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OVL)
            #define PWM_TMR4_1_OVL_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OVL_PIN              (GPIO_PIN_10)
            #define PWM_TMR4_1_OVL_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWH)
            #define PWM_TMR4_1_OWH_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OWH_PIN              (GPIO_PIN_13)
            #define PWM_TMR4_1_OWH_PIN_FUNC         (GPIO_FUNC_2)
        #endif
        #if defined(BSP_USING_PWM_TMR4_1_OWL)
            #define PWM_TMR4_1_OWL_PORT             (GPIO_PORT_E)
            #define PWM_TMR4_1_OWL_PIN              (GPIO_PIN_12)
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

#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
    #if defined(BSP_USING_USBFS)
        /* USBFS Core*/
        #define USBF_DP_PORT                    (GPIO_PORT_A)
        #define USBF_DP_PIN                     (GPIO_PIN_12)
        #define USBF_DP_FUNC                    (GPIO_FUNC_10)
        #define USBF_DM_PORT                    (GPIO_PORT_A)
        #define USBF_DM_PIN                     (GPIO_PIN_11)
        #define USBF_DM_FUNC                    (GPIO_FUNC_10)
        #define USBF_VBUS_PORT                  (GPIO_PORT_A)
        #define USBF_VBUS_PIN                   (GPIO_PIN_09)
        #define USBF_VBUS_FUNC                  (GPIO_FUNC_10)
        #define USBF_DRVVBUS_PORT               (GPIO_PORT_B)
        #define USBF_DRVVBUS_PIN                (GPIO_PIN_08)
        #define USBF_DRVVBUS_FUNC               (GPIO_FUNC_10)
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
    #define QSPI_FLASH_SCK_PORT             (GPIO_PORT_C)
    #define QSPI_FLASH_SCK_PIN              (GPIO_PIN_06)
    #define QSPI_FLASH_SCK_FUNC             (GPIO_FUNC_7)
    /* QSIO0 */
    #define QSPI_FLASH_IO0_PORT             (GPIO_PORT_D)
    #define QSPI_FLASH_IO0_PIN              (GPIO_PIN_08)
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
            #define PULSE_ENCODER_TMR6_1_A_PORT      (GPIO_PORT_E)
            #define PULSE_ENCODER_TMR6_1_A_PIN       (GPIO_PIN_09)
            #define PULSE_ENCODER_TMR6_1_A_PIN_FUNC  (GPIO_FUNC_3)
            #define PULSE_ENCODER_TMR6_1_B_PORT      (GPIO_PORT_E)
            #define PULSE_ENCODER_TMR6_1_B_PIN       (GPIO_PIN_08)
            #define PULSE_ENCODER_TMR6_1_B_PIN_FUNC  (GPIO_FUNC_3)
        #endif /* BSP_USING_PULSE_ENCODER_TMR6_1 */
    #endif /* BSP_USING_TMR6_PULSE_ENCODER */
#endif /* RT_USING_PULSE_ENCODER */

#endif

