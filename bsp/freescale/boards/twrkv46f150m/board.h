/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if !defined(__BOARD_H__)
#define __BOARD_H__

#include <stdint.h>
#include "pin_mux.h"
#include "gpio_pins.h"

/* The board name */
#define BOARD_NAME                      "TWR-KV46F150M"

#define CLOCK_VLPR   1U
#define CLOCK_RUN    2U
#define CLOCK_HSRUN  3U
#define CLOCK_NUMBER_OF_CONFIGURATIONS 4U

#ifndef CLOCK_INIT_CONFIG
#define CLOCK_INIT_CONFIG CLOCK_RUN
#endif

#if (CLOCK_INIT_CONFIG == CLOCK_RUN)
#define CORE_CLOCK_FREQ 100000000U
#elif (CLOCK_INIT_CONFIG == CLOCK_HSRUN)
#define CORE_CLOCK_FREQ 148000000U
#else
#define CORE_CLOCK_FREQ 4000000U
#endif

/* OSC0 configuration. */
#define OSC0_XTAL_FREQ 8000000U
#define OSC0_SC2P_ENABLE_CONFIG  false
#define OSC0_SC4P_ENABLE_CONFIG  false
#define OSC0_SC8P_ENABLE_CONFIG  false
#define OSC0_SC16P_ENABLE_CONFIG false
#define MCG_HGO0   kOscGainLow
#define MCG_RANGE0 kOscRangeVeryHigh
#define MCG_EREFS0 kOscSrcOsc

/* EXTAL0 PTA18 */
#define EXTAL0_PORT   PORTA
#define EXTAL0_PIN    18
#define EXTAL0_PINMUX kPortPinDisabled

/* XTAL0 PTA19 */
#define XTAL0_PORT   PORTA
#define XTAL0_PIN    19
#define XTAL0_PINMUX kPortPinDisabled

/* Defined clock for board */
#define BOARD_XTAL0_CLK_FREQUENCY   8000000U;
/* The UART to use for debug messages. */
#ifndef BOARD_DEBUG_UART_INSTANCE
    #define BOARD_DEBUG_UART_INSTANCE   1
    #define BOARD_DEBUG_UART_BASEADDR   UART1_BASE_PTR
#endif
#ifndef BOARD_DEBUG_UART_BAUD
    #define BOARD_DEBUG_UART_BAUD       115200
#endif

/* This define to use for power manager demo */
#define BOARD_LOW_POWER_UART_BAUD       9600

#define BOARD_USE_UART
#define PM_DBG_UART_IRQ_HANDLER         UART1_RX_TX_IRQHandler
#define PM_DBG_UART_IRQn                UART1_RX_TX_IRQn

/* Define feature for the low_power_demo */
#define FSL_FEATURE_HAS_VLLS2 (1)

/* Define the port interrupt number for the board switches */
#define BOARD_SW_GPIO               kGpioSW2
#define BOARD_SW_IRQ_NUM            PORTE_IRQn
#define BOARD_SW_IRQ_HANDLER        PORTE_IRQHandler
#define BOARD_SW_NAME               "SW2"
/* Define print statement to inform user which switch to press for
 * power_manager_hal_demo and power_manager_rtos_demo
 */
#define PRINT_LLWU_SW_NUM \
  PRINTF("SW2")

/* Defines the llwu pin number for board switch which is used in power_manager_demo. */
#define BOARD_SW_HAS_LLWU_PIN        1
#define BOARD_SW_LLWU_EXT_PIN        kLlwuWakeupPin16
/* Switch port base address and IRQ handler name. Used by power_manager_demo */
#define BOARD_SW_LLWU_PIN            6
#define BOARD_SW_LLWU_BASE           PORTE
#define BOARD_SW_LLWU_IRQ_HANDLER    PORTE_IRQHandler
#define BOARD_SW_LLWU_IRQ_NUM        PORTE_IRQn

#define HWADC_INSTANCE               1
#define ADC_IRQ_N                    ADC1_IRQn

#define BOARD_DAC_DEMO_DAC_INSTANCE     0U
#define BOARD_DAC_DEMO_ADC_INSTANCE     0U

/* The i2c instance used for i2c connection by default */
#define BOARD_I2C_INSTANCE              0

/* The dspi instance used for dspi example */
#define BOARD_DSPI_INSTANCE             0

/* The Flextimer instance/channel used for board */
#define BOARD_FTM_INSTANCE              0
#define BOARD_FTM_CHANNEL               0

#define BOARD_CMP_INSTANCE              0
#define BOARD_CMP_CHANNEL               1       /* PTC7 - CMP0_IN1. */
/* The SW name for CMP example */
#define BOARD_CMP_SW_NAME               "SW1"

#define BOARD_CAN_INSTANCE              0

/* The SPI instance/channel used for board */
#define SPI0_BASE       SPI_BASE
#define SPI0            SPI

/* board led color mapping */
#define LED1_EN (GPIO_DRV_OutputPinInit(&ledPins[0]))                   /*!< Enable target LED1 */
#define LED2_EN (GPIO_DRV_OutputPinInit(&ledPins[1]))                   /*!< Enable target LED2 */
#define LED3_EN (GPIO_DRV_OutputPinInit(&ledPins[2]))                   /*!< Enable target LED3 */
#define LED4_EN (GPIO_DRV_OutputPinInit(&ledPins[3]))                   /*!< Enable target LED4 */
#define LED5_EN (GPIO_DRV_OutputPinInit(&ledPins[4]))                   /*!< Enable target LED5 */
#define LED6_EN (GPIO_DRV_OutputPinInit(&ledPins[5]))                   /*!< Enable target LED6 */
#define LED7_EN (GPIO_DRV_OutputPinInit(&ledPins[6]))                   /*!< Enable target LED7 */
#define LED8_EN (GPIO_DRV_OutputPinInit(&ledPins[7]))                   /*!< Enable target LED8 */
#define LED9_EN (GPIO_DRV_OutputPinInit(&ledPins[8]))                   /*!< Enable target LED9 */

#define LED1_DIS (PORT_HAL_SetMuxMode(PORTD, 0, kPortPinDisabled))      /*!< Disable target LED1 */
#define LED2_DIS (PORT_HAL_SetMuxMode(PORTD, 1, kPortPinDisabled))      /*!< Disable target LED2 */
#define LED3_DIS (PORT_HAL_SetMuxMode(PORTD, 2, kPortPinDisabled))      /*!< Disable target LED3 */
#define LED4_DIS (PORT_HAL_SetMuxMode(PORTD, 3, kPortPinDisabled))      /*!< Disable target LED4 */
#define LED5_DIS (PORT_HAL_SetMuxMode(PORTD, 4, kPortPinDisabled))      /*!< Disable target LED5 */
#define LED6_DIS (PORT_HAL_SetMuxMode(PORTD, 5, kPortPinDisabled))      /*!< Disable target LED6 */
#define LED7_DIS (PORT_HAL_SetMuxMode(PORTC, 1, kPortPinDisabled))      /*!< Disable target LED7 */
#define LED8_DIS (PORT_HAL_SetMuxMode(PORTC, 2, kPortPinDisabled))      /*!< Disable target LED8 */
#define LED9_DIS (PORT_HAL_SetMuxMode(PORTB, 23, kPortPinDisabled))     /*!< Disable target LED9 */

#define LED1_ON (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 1))        /*!< Turn off target LED1 */
#define LED2_ON (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 1))        /*!< Turn off target LED2 */
#define LED3_ON (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 1))        /*!< Turn off target LED3 */
#define LED4_ON (GPIO_DRV_WritePinOutput(ledPins[3].pinName, 1))        /*!< Turn off target LED4 */
#define LED5_ON (GPIO_DRV_WritePinOutput(ledPins[4].pinName, 1))        /*!< Turn off target LED5 */
#define LED6_ON (GPIO_DRV_WritePinOutput(ledPins[5].pinName, 1))        /*!< Turn off target LED6 */
#define LED7_ON (GPIO_DRV_WritePinOutput(ledPins[6].pinName, 1))        /*!< Turn off target LED7 */
#define LED8_ON (GPIO_DRV_WritePinOutput(ledPins[7].pinName, 1))        /*!< Turn off target LED8 */
#define LED9_ON (GPIO_DRV_WritePinOutput(ledPins[8].pinName, 1))        /*!< Turn off target LED9 */

#define LED1_OFF (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 0))       /*!< Turn on target LED1 */
#define LED2_OFF (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 0))       /*!< Turn on target LED2 */
#define LED3_OFF (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 0))       /*!< Turn on target LED3 */
#define LED4_OFF (GPIO_DRV_WritePinOutput(ledPins[3].pinName, 0))       /*!< Turn on target LED4 */
#define LED5_OFF (GPIO_DRV_WritePinOutput(ledPins[4].pinName, 0))       /*!< Turn on target LED5 */
#define LED6_OFF (GPIO_DRV_WritePinOutput(ledPins[5].pinName, 0))       /*!< Turn on target LED6 */
#define LED7_OFF (GPIO_DRV_WritePinOutput(ledPins[6].pinName, 0))       /*!< Turn on target LED7 */
#define LED8_OFF (GPIO_DRV_WritePinOutput(ledPins[7].pinName, 0))       /*!< Turn on target LED8 */
#define LED9_OFF (GPIO_DRV_WritePinOutput(ledPins[8].pinName, 0))       /*!< Turn on target LED9 */

#define LED1_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[0].pinName))      /*!< Toggle on target LED1 */
#define LED2_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[1].pinName))      /*!< Toggle on target LED2 */
#define LED3_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[2].pinName))      /*!< Toggle on target LED3 */
#define LED4_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[3].pinName))      /*!< Toggle on target LED4 */
#define LED5_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[4].pinName))      /*!< Toggle on target LED5 */
#define LED6_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[5].pinName))      /*!< Toggle on target LED6 */
#define LED7_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[6].pinName))      /*!< Toggle on target LED7 */
#define LED8_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[7].pinName))      /*!< Toggle on target LED8 */
#define LED9_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[8].pinName))      /*!< Toggle on target LED9 */

#define LED_RTOS_EN        LED1_EN
#define LED_RTOS_TOGGLE    LED1_TOGGLE
#define LED_CLOCK_EN       LED2_EN
#define LED_CLOCK_TOGGLE   LED2_TOGGLE

#define EN_ALL_LEDS  \
                           LED1_EN;\
                           LED2_EN;\
                           LED3_EN;\
                           LED4_EN;\
                           LED5_EN;\
                           LED6_EN;\
                           LED7_EN;\
                           LED8_EN;\
                           LED9_EN;

#define OFF_ALL_LEDS  \
                           LED1_OFF;\
                           LED2_OFF;\
                           LED3_OFF;\
                           LED4_OFF;\
                           LED5_OFF;\
                           LED6_OFF;\
                           LED7_OFF;\
                           LED8_OFF;\
                           LED9_OFF;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void hardware_init(void);
void dbg_uart_init(void);
void disable_unused_pins(void);
void enable_unused_pins(void);
/*This function to used for power manager demo*/
/* Function to initialize clock base on board configuration. */
void BOARD_ClockInit(void);

/* Function to initialize OSC0 base on board configuration. */
void BOARD_InitOsc0(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __BOARD_H__ */

