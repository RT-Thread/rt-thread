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
#define BOARD_NAME                      "MRB-KW01"

#define CLOCK_VLPR 1U
#define CLOCK_RUN  2U
#define CLOCK_XTAL 3U
#define CLOCK_NUMBER_OF_CONFIGURATIONS 3U

#ifndef CLOCK_INIT_CONFIG
#if defined(RTC_DEMO) || defined(POWER_DEMO)
  #define CLOCK_INIT_CONFIG CLOCK_XTAL
#else
  #define CLOCK_INIT_CONFIG CLOCK_RUN
#endif
#endif

#if (CLOCK_INIT_CONFIG == CLOCK_RUN)
#define CORE_CLOCK_FREQ 48000000U
#elif (CLOCK_INIT_CONFIG == CLOCK_XTAL)
#define CORE_CLOCK_FREQ 47972352U
#else
#define CORE_CLOCK_FREQ 4000000U
#endif

/* OSC0 configuration. */
#if (CLOCK_INIT_CONFIG == CLOCK_XTAL)
  #define OSC0_XTAL_FREQ 32768U
#else
#ifdef MRB_KW01_9030JA    /* Define this symbol for MRB-KW01-9030JA version of the board, which have 30MHz oscillator */
  #define OSC0_XTAL_FREQ 30000000U
#else
  #define OSC0_XTAL_FREQ 32000000U
#endif
#endif
#define OSC0_SC2P_ENABLE_CONFIG  false
#define OSC0_SC4P_ENABLE_CONFIG  false
#define OSC0_SC8P_ENABLE_CONFIG  false
#define OSC0_SC16P_ENABLE_CONFIG false
#define MCG_HGO0   kOscGainLow
#if (CLOCK_INIT_CONFIG == CLOCK_XTAL)
  #define MCG_RANGE0 kOscRangeLow
#else
  #define MCG_RANGE0 kOscRangeVeryHigh
#endif
#define MCG_EREFS0 kOscSrcOsc

/* Wireless modem configuration */
#define MODEM_CLK_OUT_CTRL_ADDRESS   0xA6U
#define MODEM_CLK_OUT_CTRL_VALUE     0x00U

/* EXTAL0 PTA18 */
#define EXTAL0_PORT   PORTA
#define EXTAL0_PIN    18
#define EXTAL0_PINMUX kPortPinDisabled

/* XTAL0 PTA19 */
#define XTAL0_PORT   PORTA
#define XTAL0_PIN    19
#define XTAL0_PINMUX kPortPinDisabled

/* The UART to use for debug messages. */
#ifndef BOARD_DEBUG_UART_INSTANCE
    #define BOARD_DEBUG_UART_INSTANCE   0
    #define BOARD_DEBUG_UART_BASEADDR   UART0
#endif
#ifndef BOARD_DEBUG_UART_BAUD
    #define BOARD_DEBUG_UART_BAUD       115200
#endif

#define BOARD_LOW_POWER_UART_BAUD       9600

#define BOARD_USE_LPSCI

/* Define the port interrupt number for the board switches */
#define BOARD_SW_GPIO               kGpioSW1
#define BOARD_SW_IRQ_NUM            PORTC_PORTD_IRQn
#define BOARD_SW_IRQ_HANDLER        PORTC_PORTD_IRQHandler
#define BOARD_SW_NAME               "SW1"
/* Define print statement to inform user which switch to press for
 * low_power_demo
 */
#define PRINT_INT_SW_NUM \
  PRINTF("SW2")

#define PRINT_LLWU_SW_NUM \
  PRINTF("SW1")

 /* Defines the llwu pin number for board switch which is used in power_manager_demo. */
#define BOARD_SW_HAS_LLWU_PIN        1
#define BOARD_SW_LLWU_EXT_PIN        7
/* Switch port base address and IRQ handler name. Used by power_manager_demo */
#define BOARD_SW_LLWU_PIN            3
#define BOARD_SW_LLWU_BASE           PORTC
#define BOARD_SW_LLWU_IRQ_HANDLER    PORTC_PORTD_IRQHandler
#define BOARD_SW_LLWU_IRQ_NUM        PORTC_PORTD_IRQn

#define BOARD_I2C_GPIO_SCL              GPIO_MAKE_PIN(GPIOE_IDX, 24)
#define BOARD_I2C_GPIO_SDA              GPIO_MAKE_PIN(GPIOE_IDX, 25)

/* The instances of peripherals used for dac_adc_demo */
#define BOARD_DAC_DEMO_DAC_INSTANCE     0U
#define BOARD_DAC_DEMO_ADC_INSTANCE     0U
#define BOARD_DAC_DEMO_ADC_CHANNEL      23U

#define HWADC_INSTANCE                  0

/* The i2c instance used for i2c DAC demo */
#define BOARD_DAC_I2C_INSTANCE          1

/* The i2c instance used for i2c connection by default */
#define BOARD_I2C_INSTANCE              1

/* The spi instance used for spi example */
#define BOARD_SPI_INSTANCE              1

/* The TPM instance/channel used for board */
#define BOARD_TPM_INSTANCE              0
#define BOARD_TPM_CHANNEL               5

/* TSI electrodes mapping */
#define BOARD_TSI_ELECTRODE_CNT         2
#define BOARD_TSI_ELECTRODE_1           9
#define BOARD_TSI_ELECTRODE_2           10

/* board led color mapping */
#define BOARD_GPIO_LED_RED              kGpioLED2
#define BOARD_GPIO_LED_GREEN            kGpioLED1
#define BOARD_GPIO_LED_BLUE             kGpioLED3
#define BOARD_GPIO_LED_YELLOW           kGpioLED4

#define LED1_EN (GPIO_DRV_OutputPinInit(&ledPins[0]))  /*!< Enable target LED1 */
#define LED2_EN (GPIO_DRV_OutputPinInit(&ledPins[1]))  /*!< Enable target LED2 */
#define LED3_EN (GPIO_DRV_OutputPinInit(&ledPins[2]))  /*!< Enable target LED3 */
#define LED4_EN (GPIO_DRV_OutputPinInit(&ledPins[3]))  /*!< Enable target LED4 */

#define LED1_DIS (PORT_HAL_SetMuxMode(PORTA, 19, kPortMuxAsGpio))    /*!< Enable target LED1 */
#define LED2_DIS (PORT_HAL_SetMuxMode(PORTE, 16, kPortMuxAsGpio))    /*!< Enable target LED2 */
#define LED3_DIS (PORT_HAL_SetMuxMode(PORTB, 0, kPortMuxAsGpio))     /*!< Enable target LED3 */
#define LED4_DIS (PORT_HAL_SetMuxMode(PORTE, 17, kPortMuxAsGpio))    /*!< Enable target LED4 */

#define LED1_OFF (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 1))         /*!< Turn off target LED1 */
#define LED2_OFF (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 1))         /*!< Turn off target LED2 */
#define LED3_OFF (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 1))         /*!< Turn off target LED3 */
#define LED4_OFF (GPIO_DRV_WritePinOutput(ledPins[3].pinName, 1))         /*!< Turn off target LED4 */

#define LED1_ON (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 0))          /*!< Turn on target LED1 */
#define LED2_ON (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 0))          /*!< Turn on target LED2 */
#define LED3_ON (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 0))          /*!< Turn on target LED3 */
#define LED4_ON (GPIO_DRV_WritePinOutput(ledPins[3].pinName, 0))          /*!< Turn on target LED4 */

#define LED1_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[0].pinName))           /*!< Toggle on target LED1 */
#define LED2_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[1].pinName))           /*!< Toggle on target LED2 */
#define LED3_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[2].pinName))           /*!< Toggle on target LED3 */
#define LED4_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[3].pinName))           /*!< Toggle on target LED4 */

#define LED_RTOS_EN        LED1_EN
#define LED_RTOS_TOGGLE    LED1_TOGGLE
#define LED_CLOCK_EN       LED2_EN
#define LED_CLOCK_TOGGLE   LED2_TOGGLE

#define OFF_ALL_LEDS  \
                           LED1_OFF;\
                           LED2_OFF;\
                           LED3_OFF;\
                           LED4_OFF;

/* The CMP instance used for board. */
#define BOARD_CMP_INSTANCE              0
/* The CMP channel used for board. */
#define BOARD_CMP_CHANNEL               0

/* The rtc instance used for rtc_func */
#define BOARD_RTC_FUNC_INSTANCE         0

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

/* Function to initialize RTC external clock base on board configuration. */
void BOARD_InitRtcOsc(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __BOARD_H__ */
