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
 *   other materials provided witwh the distribution.
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
#define BOARD_NAME                      "TWR-KM34Z75M"

#define CLOCK_VLPR 1U
#define CLOCK_RUN  2U
#define CLOCK_NUMBER_OF_CONFIGURATIONS 3U

#ifndef CLOCK_INIT_CONFIG
#define CLOCK_INIT_CONFIG CLOCK_RUN
#endif

#if (CLOCK_INIT_CONFIG == CLOCK_RUN)
#define CORE_CLOCK_FREQ 72000000U
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

/* EXTAL0 PTE2 */
#define EXTAL0_PORT   PORTE
#define EXTAL0_PIN    2
#define EXTAL0_PINMUX kPortPinDisabled

/* XTAL0 PTE3 */
#define XTAL0_PORT   PORTE
#define XTAL0_PIN    3
#define XTAL0_PINMUX kPortPinDisabled

/* RTC external clock configuration. */
#define RTC_XTAL_FREQ   32768U
#define RTC_SC2P_ENABLE_CONFIG       false
#define RTC_SC4P_ENABLE_CONFIG       false
#define RTC_SC8P_ENABLE_CONFIG       false
#define RTC_SC16P_ENABLE_CONFIG      false
#define RTC_OSC_ENABLE_CONFIG        true

/* The UART to use for debug messages. */
#ifndef BOARD_DEBUG_UART_INSTANCE
    #define BOARD_DEBUG_UART_INSTANCE   2
    #define BOARD_DEBUG_UART_BASEADDR   UART2
#endif
#ifndef BOARD_DEBUG_UART_BAUD
    #define BOARD_DEBUG_UART_BAUD       115200
#endif

#ifndef BOARD_LPUART_CLOCK_SOURCE
    #define BOARD_LPUART_CLOCK_SOURCE   kClockLpuartSrcOsc0erClk
#endif

/* The spi instance used for spi example */
#define BOARD_SPI_INSTANCE              0

/* This define to use for power manager demo */
#define BOARD_LOW_POWER_UART_BAUD       9600
#define BOARD_USE_UART

/* Define feature for the low_power_demo */
#define FSL_FEATURE_HAS_VLLS2 (1)

/* Define the port interrupt number for the board switches */
#define BOARD_SW_GPIO           kGpioSW1
#define BOARD_SW_IRQ_NUM        PTx_IRQn
#define BOARD_SW_IRQ_HANDLER    PTx_IRQHandler
#define BOARD_SW_NAME           "SW1"
/* Define print statement to inform user which switch to press for
 * low_power_demo
 */
#define PRINT_INT_SW_NUM \
  PRINTF("SW2")

#define PRINT_LLWU_SW_NUM \
  PRINTF("SW1")

/* Defines the llwu pin number for board switch which is used in power_manager_demo. */
#define BOARD_SW_HAS_LLWU_PIN        1
#define BOARD_SW_LLWU_EXT_PIN        kLlwuWakeupPin15
/* Switch port base address and IRQ handler name. Used by power_manager_demo */
#define BOARD_SW_LLWU_PIN            4
#define BOARD_SW_LLWU_BASE           PORTA
#define BOARD_SW_LLWU_IRQ_HANDLER    PTx_IRQHandler
#define BOARD_SW_LLWU_IRQ_NUM        PTx_IRQn

/* The MMA8451 i2c instance and slave address */
#define BOARD_MMA8451_I2C_INSTANCE      0
#define BOARD_ACCEL_ADDR_ACTUAL         (0x1D)
#define BOARD_ACCEL_I2C_ADDR            (BOARD_ACCEL_ADDR_ACTUAL << 1)

#define BOARD_I2C_GPIO_SCL              GPIO_MAKE_PIN(GPIOD_IDX, 7)
#define BOARD_I2C_GPIO_SDA              GPIO_MAKE_PIN(GPIOE_IDX, 0)
#define BOARD_I2C_DELAY \
    do \
    { \
        int32_t i; \
        for (i = 0; i < 500; i++) \
        { \
            __asm("nop"); \
        } \
    } while (0)


/* The i2c instance used for i2c communication demo */
#define BOARD_I2C_INSTANCE         0

/* ADC0 input channel */
#define BOARD_ADC0_INPUT_CHAN           0

/* board led color mapping */
#define BOARD_GPIO_LED_GREEN          kGpioLED1
#define BOARD_GPIO_LED_RED            kGpioLED2
/* In TWR_KM34Z75M the three LEDs colors are green, red and orange, but to ensure
      the code consistency, we use blue instead of orange*/
#define BOARD_GPIO_LED_ORANGE         kGpioLED3
#define BOARD_GPIO_LED_BLUE           kGpioLED3

#define DISABLE_DEBUG_CONSOLE_TX PORT_HAL_SetMuxMode(PORTI, 7, kPortPinDisabled)
#define DISABLE_DEBUG_CONSOLE_RX PORT_HAL_SetMuxMode(PORTI, 6, kPortPinDisabled)

//#define DISABLE_SW_INTERRUPT PORT_HAL_SetPinIntMode(PORTA, 19, kPortIntDisabled)
//#define DISABLE_SW_PIN PORT_HAL_SetMuxMode(PORTA, 19, kPortPinDisabled)

#define LED1_EN {PORT_HAL_SetMuxMode(PORTJ, 3, kPortMuxAsGpio);GPIO_DRV_OutputPinInit(&ledPins[0]);}   /*!< Enable target LED1 */
#define LED2_EN {PORT_HAL_SetMuxMode(PORTJ, 4, kPortMuxAsGpio);GPIO_DRV_OutputPinInit(&ledPins[1]);}   /*!< Enable target LED2 */
#define LED3_EN {PORT_HAL_SetMuxMode(PORTD, 0, kPortMuxAsGpio);GPIO_DRV_OutputPinInit(&ledPins[2]);}   /*!< Enable target LED3 */

#define LED1_DIS (PORT_HAL_SetMuxMode(PORTJ, 3, kPortPinDisabled))  /*!< Disable target LED1 */
#define LED2_DIS (PORT_HAL_SetMuxMode(PORTJ, 4, kPortPinDisabled))  /*!< Disable target LED2 */
#define LED3_DIS (PORT_HAL_SetMuxMode(PORTD, 0, kPortPinDisabled))  /*!< Disable target LED3 */

#define LED1_OFF (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 1))       /*!< Turn off target LED1 */
#define LED2_OFF (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 1))       /*!< Turn off target LED2 */
#define LED3_OFF (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 1))       /*!< Turn off target LED3 */

#define LED1_ON (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 0))        /*!< Turn on target LED1 */
#define LED2_ON (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 0))        /*!< Turn on target LED2 */
#define LED3_ON (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 0))        /*!< Turn on target LED3 */

#define LED1_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[0].pinName))        /*!< Toggle on target LED1 */
#define LED2_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[1].pinName))        /*!< Toggle on target LED2 */
#define LED3_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[2].pinName))        /*!< Toggle on target LED3 */
#define OFF_ALL_LEDS  \
                           LED1_OFF;\
                           LED2_OFF;\
                           LED3_OFF;

/* The CMP instance used for board. */
#define BOARD_CMP_INSTANCE              2
/* The CMP channel used for board. */
#define BOARD_CMP_CHANNEL               4

/* The rtc instance used for rtc_func */
#define BOARD_RTC_FUNC_INSTANCE         0

/* The UART Smartcard interface. */
#define BOARD_SMARTCARD_MODULE_INSTANCE           (1)
#define HW_SMARTCARD_CLOCK_MODULE_INSTANCE        (1)
#define HW_SMARTCARD_CLOCK_MODULE_CHANNEL         (0)
#define HW_SMARTCARD_CLOCK_VALUE                  (2000000)
#define HW_SMARTCARD_CONTROL_PORT_INSTANCE        (PORTH_IDX)
#define HW_SMARTCARD_CONTROL_PIN                  (7)
#define HW_SMARTCARD_RST_PORT_INSTANCE            (PORTK_IDX)
#define HW_SMARTCARD_RST_PIN                      (5)
#define HW_SMARTCARD_IRQ_PORT_INSTANCE            (PORTH_IDX)
#define HW_SMARTCARD_IRQ_PIN                      (2)
#define HW_SMARTCARD_VSEL0_PORT_INSTANCE          (PORTI_IDX)
#define HW_SMARTCARD_VSEL0_PIN                    (2)
#define HW_SMARTCARD_VSEL1_PORT_INSTANCE          (PORTH_IDX)
#define HW_SMARTCARD_VSEL1_PIN                    (6)

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
