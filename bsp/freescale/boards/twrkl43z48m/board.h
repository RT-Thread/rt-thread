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
#define BOARD_NAME                  "TWR-KL43Z48M"

#define CLOCK_VLPR                       1U
#define CLOCK_RUN                        2U
#define CLOCK_NUMBER_OF_CONFIGURATIONS   3U

#ifndef CLOCK_INIT_CONFIG
#define CLOCK_INIT_CONFIG CLOCK_RUN
#endif

/* NMI pin */
#define NMI_PORT   PORTA
#define NMI_PIN    4


#if (CLOCK_INIT_CONFIG == CLOCK_RUN)
#define CORE_CLOCK_FREQ 48000000U
#else
#define CORE_CLOCK_FREQ 2000000U
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

/* RTC external clock configuration. */
#define RTC_XTAL_FREQ   32768u

/* RTC_CLKIN PTC1 */
#define RTC_CLKIN_PORT   PORTC
#define RTC_CLKIN_PIN    1
#define RTC_CLKIN_PINMUX kPortMuxAsGpio

/*! The UART to use for debug messages. */
#ifndef BOARD_DEBUG_UART_INSTANCE
    #define BOARD_DEBUG_UART_INSTANCE   2
    #define BOARD_DEBUG_UART_BASEADDR   UART2
#endif

#ifndef BOARD_LPUART_CLOCK_SOURCE
#define BOARD_LPUART_CLOCK_SOURCE   kClockLpuartSrcIrc48M
#endif

#ifndef USB_UART_CLOCK_SOURCE
    #define USB_UART_CLOCK_SOURCE   BOARD_LPUART_CLOCK_SOURCE
#endif

#ifndef BOARD_DEBUG_UART_BAUD
#define BOARD_DEBUG_UART_BAUD       115200
#endif

/* This define to use for power manager demo */
#define BOARD_LOW_POWER_UART_BAUD       9600

#define BOARD_USE_UART
#define PM_DBG_UART_IRQ_HANDLER         UART2_FLEXIO_IRQHandler
#define PM_DBG_UART_IRQn                UART2_FLEXIO_IRQn
#define BOARD_DAC_DEMO_DAC_INSTANCE     0U
#define BOARD_DAC_DEMO_ADC_INSTANCE     0U
#define BOARD_DAC_DEMO_ADC_CHANNEL      23U
#define BOARD_ADC_USE_ALT_VREF          1

/* Define print statement to inform user which switch to press for
 * power_manager_hal_demo and power_manager_rtos_demo
 */
#define PRINT_LLWU_SW_NUM \
  PRINTF("SW2")

/* Defines the llwu pin number for board switch which is used in power_manager_demo. */
#define BOARD_SW_HAS_LLWU_PIN        0
#define BOARD_SW_LLWU_EXT_PIN        7
/* Switch port base address and IRQ handler name. Used by power_manager_demo */
#define BOARD_SW_LLWU_PIN            4
#define BOARD_SW_LLWU_BASE           PORTA
#define BOARD_SW_LLWU_IRQ_HANDLER    PORTA_IRQHandler
#define BOARD_SW_LLWU_IRQ_NUM        PORTA_IRQn

#define HWADC_INSTANCE               0
#define ADC_IRQ_N                    ADC0_IRQn

#define BOARD_TPM_INSTANCE 1
#define BOARD_TPM_CHANNEL  1

/* Isn't supported now to use DAC as sine generator in adc_hw_trigger demo */
//#define USE_DAC_OUT_AS_SOURCE

#define BOARD_CMP_INSTANCE          0
#define BOARD_CMP_CHANNEL           0

/* The i2c instance used for i2c connection by default */
#define BOARD_I2C_INSTANCE          1

/* The spi instance used for spi example */
#define BOARD_SPI_INSTANCE              0

/* The rtc instance used for rtc_func */
#define BOARD_RTC_FUNC_INSTANCE         0

/* The i2c instance used for sai demo or flexio i2s example */
#define BOARD_SAI_DEMO_I2C_INSTANCE     1

/*! Tower I2C instance connected to Accelerometer */
#define BOARD_I2C_GPIO_SCL          GPIO_MAKE_PIN(GPIOE_IDX, 1) // PTE1
#define BOARD_I2C_GPIO_SDA          GPIO_MAKE_PIN(GPIOE_IDX, 0) // PTE0

/* board led color mapping */
#define BOARD_GPIO_LED_GREEN           kGpioLED1
#define BOARD_GPIO_LED_RED             kGpioLED2
#define BOARD_GPIO_LED_BLUE            kGpioLED3
#define BOARD_GPIO_LED2_RED            kGpioLED4

/* board button mapping */
#define BOARD_GPIO_BUTTON              kGpioSW3
#define BOARD_GPIO_BUTTON_IRQ          PORTA_IRQn /*!< PTA5 */

#define BOARD_SW_GPIO                  kGpioSW2
#define BOARD_SW_IRQ_HANDLER           PORTA_IRQHandler
#define BOARD_SW_NAME                  "SW2"

#define BOARD_GPIO_BUTTON2             kGpioSW2
#define BOARD_GPIO_BUTTON2_IRQ         PORTA_IRQn /*!< PTA4 */

#define LED1_EN (GPIO_DRV_OutputPinInit(&ledPins[0])) /*!< Enable target LED1 */
#define LED2_EN (GPIO_DRV_OutputPinInit(&ledPins[1])) /*!< Enable target LED2 */
#define LED3_EN (GPIO_DRV_OutputPinInit(&ledPins[2])) /*!< Enable target LED3 */
#define LED4_EN (GPIO_DRV_OutputPinInit(&ledPins[3])) /*!< Enable target LED4 */

#define LED1_DIS (PORT_HAL_SetMuxMode(PORTA, 12, kPortPinDisabled)) /*!< Enable target LED1 */
#define LED2_DIS (PORT_HAL_SetMuxMode(PORTA, 13, kPortPinDisabled)) /*!< Enable target LED2 */
#define LED3_DIS (PORT_HAL_SetMuxMode(PORTB,  0, kPortPinDisabled)) /*!< Enable target LED3 */
#define LED4_DIS (PORT_HAL_SetMuxMode(PORTB, 19, kPortPinDisabled)) /*!< Enable target LED4 */

#define LED1_OFF (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 1)) /*!< Turn off target LED1 */
#define LED2_OFF (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 1)) /*!< Turn off target LED2 */
#define LED3_OFF (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 1)) /*!< Turn off target LED3 */
#define LED4_OFF (GPIO_DRV_WritePinOutput(ledPins[3].pinName, 1)) /*!< Turn off target LED4 */

#define LED1_ON (GPIO_DRV_WritePinOutput(ledPins[0].pinName, 0))  /*!< Turn on target LED1 */
#define LED2_ON (GPIO_DRV_WritePinOutput(ledPins[1].pinName, 0))  /*!< Turn on target LED2 */
#define LED3_ON (GPIO_DRV_WritePinOutput(ledPins[2].pinName, 0))  /*!< Turn on target LED3 */
#define LED4_ON (GPIO_DRV_WritePinOutput(ledPins[3].pinName, 0))  /*!< Turn on target LED4 */

#define LED1_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[0].pinName)) /*!< Toggle on target LED1 */
#define LED2_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[1].pinName)) /*!< Toggle on target LED2 */
#define LED3_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[2].pinName)) /*!< Toggle on target LED3 */
#define LED4_TOGGLE (GPIO_DRV_TogglePinOutput(ledPins[3].pinName)) /*!< Toggle on target LED4 */

#define LED_RTOS_EN        LED1_EN
#define LED_RTOS_TOGGLE    LED1_TOGGLE
#define LED_CLOCK_EN       LED2_EN
#define LED_CLOCK_TOGGLE   LED2_TOGGLE

/* The UART Smartcard interface. */
#define BOARD_SMARTCARD_UART_INSTANCE             (0)
#define HW_SMARTCARD_CLOCK_MODULE_INSTANCE        (0)
#define HW_SMARTCARD_CLOCK_MODULE_CHANNEL         (0)
#define HW_SMARTCARD_CLOCK_VALUE                  (4000000)
#define HW_SMARTCARD_PRESENSE_GPIO_BASE           (PTE)
#define HW_SMARTCARD_PRESENSE_GPIO_PIN            (30)
#define HW_SMARTCARD_CONTROL_PORT_INSTANCE        (PORTB_IDX)
#define HW_SMARTCARD_CONTROL_PIN                  (0)
#define HW_SMARTCARD_RST_PORT_INSTANCE            (PORTE_IDX)
#define HW_SMARTCARD_RST_PIN                      (29)
#define HW_SMARTCARD_IRQ_PORT_INSTANCE            (PORTC_IDX)
#define HW_SMARTCARD_IRQ_PIN                      (1)
#define HW_SMARTCARD_VSEL0_PORT_INSTANCE          (PORTB_IDX)
#define HW_SMARTCARD_VSEL0_PIN                    (2)
#define HW_SMARTCARD_VSEL1_PORT_INSTANCE          (PORTB_IDX)
#define HW_SMARTCARD_VSEL1_PIN                    (19)
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

/* Function to initialize RTC external clock base on board configuration. */
void BOARD_InitRtcOsc(void);

/*Function to handle board-specified initialization*/
uint8_t usb_device_board_init(uint8_t controller_id);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* __BOARD_H__ */
/******************************************************************************
 * EOF
 ******************************************************************************/
