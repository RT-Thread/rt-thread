/*
 * Copyright 2017-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_common.h"
#include "fsl_reset.h"
#include "fsl_gpio.h"
#include "fsl_iocon.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define BOARD_NAME "LPCXpresso55S06"

/*! @brief The UART to use for debug messages. */
/* TODO: rename UART to USART */
#define BOARD_DEBUG_UART_TYPE       kSerialPort_Uart
#define BOARD_DEBUG_UART_BASEADDR   (uint32_t) USART0
#define BOARD_DEBUG_UART_INSTANCE   0U
#define BOARD_DEBUG_UART_CLK_FREQ   12000000U
#define BOARD_DEBUG_UART_CLK_ATTACH kFRO12M_to_FLEXCOMM0
#define BOARD_DEBUG_UART_RST        kFC0_RST_SHIFT_RSTn
#define BOARD_DEBUG_UART_CLKSRC     kCLOCK_Flexcomm0
#define BOARD_UART_IRQ_HANDLER      FLEXCOMM0_IRQHandler
#define BOARD_UART_IRQ              FLEXCOMM0_IRQn

#define BOARD_ACCEL_I2C_BASEADDR   I2C0
#define BOARD_ACCEL_I2C_CLOCK_FREQ 12000000

#ifndef BOARD_DEBUG_UART_BAUDRATE
#define BOARD_DEBUG_UART_BAUDRATE 115200U
#endif /* BOARD_DEBUG_UART_BAUDRATE */

#define BOARD_CODEC_I2C_BASEADDR   I2C4
#define BOARD_CODEC_I2C_CLOCK_FREQ 12000000
#define BOARD_CODEC_I2C_INSTANCE   4
#ifndef BOARD_LED_RED_GPIO
#define BOARD_LED_RED_GPIO GPIO
#endif
#define BOARD_LED_RED_GPIO_PORT 0U
#ifndef BOARD_LED_RED_GPIO_PIN
#define BOARD_LED_RED_GPIO_PIN 21U
#endif

#ifndef BOARD_LED_BLUE_GPIO
#define BOARD_LED_BLUE_GPIO GPIO
#endif
#define BOARD_LED_BLUE_GPIO_PORT 0U
#ifndef BOARD_LED_BLUE_GPIO_PIN
#define BOARD_LED_BLUE_GPIO_PIN 22U
#endif

#ifndef BOARD_LED_GREEN_GPIO
#define BOARD_LED_GREEN_GPIO GPIO
#endif
#define BOARD_LED_GREEN_GPIO_PORT 0U
#ifndef BOARD_LED_GREEN_GPIO_PIN
#define BOARD_LED_GREEN_GPIO_PIN 18U
#endif

#ifndef BOARD_SW1_GPIO
#define BOARD_SW1_GPIO GPIO
#endif
#define BOARD_SW1_GPIO_PORT 0U
#ifndef BOARD_SW1_GPIO_PIN
#define BOARD_SW1_GPIO_PIN 28U
#endif
#define BOARD_SW1_NAME        "SW1"
#define BOARD_SW1_IRQ         PIN_INT0_IRQn
#define BOARD_SW1_IRQ_HANDLER PIN_INT0_IRQHandler

#ifndef BOARD_SW3_GPIO
#define BOARD_SW3_GPIO GPIO
#endif
#define BOARD_SW3_GPIO_PORT 1U
#ifndef BOARD_SW3_GPIO_PIN
#define BOARD_SW3_GPIO_PIN 9U
#endif
#define BOARD_SW3_NAME              "SW3"
#define BOARD_SW3_IRQ               PIN_INT1_IRQn
#define BOARD_SW3_IRQ_HANDLER       PIN_INT1_IRQHandler
#define BOARD_SW3_GPIO_PININT_INDEX 1

#ifndef BOARD_SW4_GPIO
#define BOARD_SW4_GPIO GPIO
#endif
#define BOARD_SW4_GPIO_PORT 0U
#ifndef BOARD_SW4_GPIO_PIN
#define BOARD_SW4_GPIO_PIN 5U
#endif
#define BOARD_SW4_NAME              "SW4"
#define BOARD_SW4_IRQ               PIN_INT0_IRQn
#define BOARD_SW4_IRQ_HANDLER       PIN_INT0_IRQHandler
#define BOARD_SW4_GPIO_PININT_INDEX 1

/* Board led color mapping */
#define LOGIC_LED_ON  1U
#define LOGIC_LED_OFF 0U

#define BOARD_SDIF_CLK_ATTACH kMAIN_CLK_to_SDIO_CLK

#define LED_RED_INIT(output)                                                                          \
    {                                                                                                 \
        IOCON_PinMuxSet(IOCON, BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN, IOCON_DIGITAL_EN);    \
        GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT, BOARD_LED_RED_GPIO_PIN,             \
                     &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}); /*!< Enable target LED1 */ \
    }
#define LED_RED_OFF()                                           \
    GPIO_PortClear(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT, \
                   1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn off target LED1 */
#define LED_RED_ON()                                                                        \
    GPIO_PortSet(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT,                               \
                 1U << BOARD_LED_RED_GPIO_PIN) /*!< Turn on target LED1 \ \ \ \ \ \ \ \ \ \ \
                                                */
#define LED_RED_TOGGLE()                                         \
    GPIO_PortToggle(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PORT, \
                    1U << BOARD_LED_RED_GPIO_PIN) /*!< Toggle on target LED1 */

#define LED_BLUE_INIT(output)                                                                         \
    {                                                                                                 \
        IOCON_PinMuxSet(IOCON, BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_GPIO_PIN, IOCON_DIGITAL_EN);  \
        GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, BOARD_LED_BLUE_GPIO_PIN,          \
                     &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}); /*!< Enable target LED1 */ \
    }
#define LED_BLUE_OFF()                                            \
    GPIO_PortClear(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, \
                   1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn off target LED1 */
#define LED_BLUE_ON()                                           \
    GPIO_PortSet(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, \
                 1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Turn on target LED1 */
#define LED_BLUE_TOGGLE()                                          \
    GPIO_PortToggle(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, \
                    1U << BOARD_LED_BLUE_GPIO_PIN) /*!< Toggle on target LED1 */

#define LED_GREEN_INIT(output)                                                              \
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, BOARD_LED_GREEN_GPIO_PIN, \
                 &(gpio_pin_config_t){kGPIO_DigitalOutput, (output)}) /*!< Enable target LED1 */
#define LED_GREEN_OFF()                                             \
    GPIO_PortClear(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, \
                   1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn off target LED1 */
#define LED_GREEN_ON()                                            \
    GPIO_PortSet(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, \
                 1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Turn on target LED1 */
#define LED_GREEN_TOGGLE()                                           \
    GPIO_PortToggle(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PORT, \
                    1U << BOARD_LED_GREEN_GPIO_PIN) /*!< Toggle on target LED1 */

/* Display. */
#define BOARD_LCD_DC_GPIO      GPIO
#define BOARD_LCD_DC_GPIO_PORT 0U
#define BOARD_LCD_DC_GPIO_PIN  24U

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*******************************************************************************
 * API
 ******************************************************************************/

void BOARD_InitDebugConsole(void);
#if defined(SDK_I2C_BASED_COMPONENT_USED) && SDK_I2C_BASED_COMPONENT_USED
void BOARD_I2C_Init(I2C_Type *base, uint32_t clkSrc_Hz);
status_t BOARD_I2C_Send(I2C_Type *base,
                        uint8_t deviceAddress,
                        uint32_t subAddress,
                        uint8_t subaddressSize,
                        uint8_t *txBuff,
                        uint8_t txBuffSize);
status_t BOARD_I2C_Receive(I2C_Type *base,
                           uint8_t deviceAddress,
                           uint32_t subAddress,
                           uint8_t subaddressSize,
                           uint8_t *rxBuff,
                           uint8_t rxBuffSize);
void BOARD_Accel_I2C_Init(void);
status_t BOARD_Accel_I2C_Send(uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint32_t txBuff);
status_t BOARD_Accel_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subaddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
void BOARD_Codec_I2C_Init(void);
status_t BOARD_Codec_I2C_Send(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, const uint8_t *txBuff, uint8_t txBuffSize);
status_t BOARD_Codec_I2C_Receive(
    uint8_t deviceAddress, uint32_t subAddress, uint8_t subAddressSize, uint8_t *rxBuff, uint8_t rxBuffSize);
#endif /* SDK_I2C_BASED_COMPONENT_USED */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */
