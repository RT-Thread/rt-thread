/*
 * Copyright (c) 2013-2014, Freescale Semiconductor, Inc.
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

#include "gpio_pins.h"
#include "pin_mux.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

/* The board name */
#define BOARD_NAME                      "FRDM-KL03Z"

#define CLOCK_VLPR 1U
#define CLOCK_RUN  2U
#define CLOCK_NUMBER_OF_CONFIGURATIONS 3U

#ifndef CLOCK_INIT_CONFIG
#define CLOCK_INIT_CONFIG CLOCK_RUN
#endif

#if (CLOCK_INIT_CONFIG == CLOCK_RUN)
#define CORE_CLOCK_FREQ 48000000U
#else
#define CORE_CLOCK_FREQ 2000000U
#endif

/* OSC0 configuration. */
#define OSC0_XTAL_FREQ 32768U
#define OSC0_SC2P_ENABLE_CONFIG  false
#define OSC0_SC4P_ENABLE_CONFIG  false
#define OSC0_SC8P_ENABLE_CONFIG  false
#define OSC0_SC16P_ENABLE_CONFIG false
#define MCG_EREFS0 kOscSrcOsc

/* EXTAL0 PTA18 */
#define EXTAL0_PORT   PORTA
#define EXTAL0_PIN    18
#define EXTAL0_PINMUX kPortPinDisabled

/* XTAL0 PTA19 */
#define XTAL0_PORT   PORTA
#define XTAL0_PIN    19
#define XTAL0_PINMUX kPortPinDisabled

/*! The LPUART to use for debug messages. */
#define BOARD_DEBUG_UART_INSTANCE (0)
#define BOARD_DEBUG_UART_BAUD      9600
#define BOARD_DEBUG_UART_BASEADDR  LPUART0

/* This define to use for power manager demo */
#define BOARD_LOW_POWER_UART_BAUD       9600
#ifndef BOARD_LPUART_CLOCK_SOURCE
  #define BOARD_LPUART_CLOCK_SOURCE   kClockLpuartSrcIrc48M
#endif

#ifndef USB_UART_CLOCK_SOURCE
    #define USB_UART_CLOCK_SOURCE   BOARD_LPUART_CLOCK_SOURCE
#endif

/* Define the port interrupt number for the board switches */
#define BOARD_SW_GPIO               kGpioSW2
#define BOARD_SW_IRQ_NUM            PORTB_IRQn
#define BOARD_SW_IRQ_HANDLER        PORTB_IRQHandler
#define BOARD_SW_NAME               "SW2"
/* Define print statement to inform user which switch to press for
 * power_manager_hal_demo and power_manager_rtos_demo
 */
#define PRINT_LLWU_SW_NUM \
  PRINTF("SW2")

 /* Defines the llwu pin number for board switch which is used in power_manager_demo. */
#define BOARD_SW_HAS_LLWU_PIN        1
#define BOARD_SW_LLWU_EXT_PIN        4
/* Switch port base address and IRQ handler name. Used by power_manager_demo */
#define BOARD_SW_LLWU_PIN            0
#define BOARD_SW_LLWU_BASE           PORTB
#define BOARD_SW_LLWU_IRQ_HANDLER    PORTB_IRQHandler
#define BOARD_SW_LLWU_IRQ_NUM        PORTB_IRQn

#define BOARD_USE_LPUART

#define HWADC_INSTANCE              0

#define BOARD_DAC_I2C_INSTANCE      1

#define BOARD_I2C_GPIO_SCL          GPIO_MAKE_PIN(GPIOB_IDX, 3)
#define BOARD_I2C_GPIO_SDA          GPIO_MAKE_PIN(GPIOB_IDX, 4)

/* The i2c instance used for i2c connection by default */
#define BOARD_I2C_INSTANCE          0

/* ADC channels definition for thermistors using differential input */
#define BOARD_ADC_INSTANCE              0         /*!< ADC instance number*/
#define ADC0_CHANNEL0                   3         /*!< PTA8 - ADC0_SE3 */
#define ADC0_CHANNEL1                   2         /*!< PTA9 - ADC0_SE2 */

/* The spi instance used for spi example */
#define BOARD_SPI_INSTANCE              0

/* The TPM instance/channel used for board */
#define BOARD_TPM_INSTANCE              0
#define BOARD_TPM_CHANNEL               0

/* The bubble level demo information */
#define BOARD_BUBBLE_TPM_INSTANCE       0
#define BOARD_TPM_X_CHANNEL             0
#define BOARD_TPM_Y_CHANNEL             1
#define BOARD_MMA8451_ADDR              0x1D
#define BOARD_ACCEL_ADDR                BOARD_MMA8451_ADDR
#define BOARD_ACCEL_BAUDRATE            100
#define BOARD_ACCEL_I2C_INSTANCE        0

/* board led color mapping */
#define BOARD_GPIO_LED_RED              kGpioLED1
#define BOARD_GPIO_LED_GREEN            kGpioLED2
#define BOARD_GPIO_LED_BLUE             kGpioLED3

#define LED1_EN  (GPIO_DRV_OutputPinInit(&ledPins[0]))  /*!< Enable target LED1 */
#define LED2_EN  (GPIO_DRV_OutputPinInit(&ledPins[1]))  /*!< Enable target LED2 */
#define LED3_EN  (GPIO_DRV_OutputPinInit(&ledPins[2]))  /*!< Enable target LED3 */

#define LED1_DIS (PORT_HAL_SetMuxMode(PORTB, 10, kPortPinDisabled))  /*!< Disable target LED1 */
#define LED2_DIS (PORT_HAL_SetMuxMode(PORTB, 11, kPortPinDisabled))  /*!< Disable target LED2 */
#define LED3_DIS (PORT_HAL_SetMuxMode(PORTB, 13, kPortPinDisabled))  /*!< Disable target LED3 */

#define LED1_OFF (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 1))         /*!< Turn off target LED1 */
#define LED2_OFF (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 1))         /*!< Turn off target LED2 */
#define LED3_OFF (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 1))         /*!< Turn off target LED3 */

#define LED1_ON (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 0))          /*!< Turn on target LED1 */
#define LED2_ON (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 0))          /*!< Turn on target LED2 */
#define LED3_ON (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 0))          /*!< Turn on target LED3 */

#define LED1_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[0].pinName))        /*!< Toggle on target LED1 */
#define LED2_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[1].pinName))        /*!< Toggle on target LED2 */
#define LED3_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[2].pinName))        /*!< Toggle on target LED3 */

#define OFF_ALL_LEDS  \
                           LED1_OFF;\
                           LED2_OFF;\
                           LED3_OFF;

/* deafult ADC channel for hw trigger demo */
#define BOARD_ADC_HW_TRIGGER_CHAN 3

/* The rtc instance used for rtc_func */
#define BOARD_RTC_FUNC_INSTANCE         0

/* The CMP instance used for board. */
#define BOARD_CMP_INSTANCE              0
/* The CMP channel used for board. */
#define BOARD_CMP_CHANNEL               1
/* The SW name for CMP example */
#define BOARD_CMP_SW_NAME               "SW3"

/******************************************************************************
 * Externs
 ******************************************************************************/

/******************************************************************************
 * Prototypes
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void hardware_init(void);
void dbg_uart_init(void);
/*This function to used for power manager demo*/
void disable_unused_pins(void);
void enable_unused_pins(void);

/* Function to initialize clock base on board configuration. */
void BOARD_ClockInit(void);

/* Function to initialize OSC0 base on board configuration. */
void BOARD_InitOsc0(void);

/* Function to initialize OSC0 using the RTC override feature */
void BOARD_InitRtcOsc(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __BOARD_H__ */
/******************************************************************************
 * EOF
 ******************************************************************************/
