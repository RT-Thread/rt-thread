/*******************************************************************************
 * File Name: cycfg_pins.h
 *
 * Description:
 * Pin configuration
 * This file was automatically generated and should not be modified.
 * Configurator Backend 3.20.0
 * device-db 4.15.0.5746
 * mtb-pdl-cat1 3.10.0.32115
 *
 *******************************************************************************
 * Copyright 2024 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"
#include "cycfg_routing.h"

#if defined (CY_USING_HAL)
#include "cyhal_hwmgr.h"
#endif /* defined (CY_USING_HAL) */

#if defined (CY_USING_HAL_LITE)
#include "cyhal_hw_types.h"
#endif /* defined (CY_USING_HAL_LITE) */

#if defined(__cplusplus)
extern "C" {
#endif /* defined(__cplusplus) */

#if defined (CY_USING_HAL)
#define CYBSP_CAN_TX (P0_2)
#define CYBSP_CAN_RX (P0_3)
#define CYBSP_SPI_MISO (P10_0)
#define CYBSP_D12 CYBSP_SPI_MISO
#define CYBSP_SPI_MOSI (P10_1)
#define CYBSP_D11 CYBSP_SPI_MOSI
#define CYBSP_SPI_CLK (P10_2)
#define CYBSP_D13 CYBSP_SPI_CLK
#define CYBSP_SPI_CS (P10_3)
#define CYBSP_D10 CYBSP_SPI_CS
#define CYBSP_D9 (P10_4)
#define CYBSP_D8 (P10_5)
#define CYBSP_A8 (P12_0)
#define CYBSP_A9 (P12_1)
#define CYBSP_A10 (P12_2)
#define CYBSP_A11 (P12_3)
#define CYBSP_A12 (P12_4)
#define CYBSP_A13 (P12_5)
#define CYBSP_A14 (P12_6)
#define CYBSP_A15 (P12_7)
#define CYBSP_DEBUG_UART_RX (P13_0)
#define CYBSP_D0 CYBSP_DEBUG_UART_RX
#define CYBSP_DEBUG_UART_TX (P13_1)
#define CYBSP_D1 CYBSP_DEBUG_UART_TX
#define CYBSP_DEBUG_UART_RTS (P13_2)
#define CYBSP_D2 CYBSP_DEBUG_UART_RTS
#define CYBSP_DEBUG_UART_CTS (P13_3)
#define CYBSP_D3 CYBSP_DEBUG_UART_CTS
#define CYBSP_D4 (P13_4)
#define CYBSP_D5 (P13_5)
#define CYBSP_D6 (P13_6)
#define CYBSP_D7 (P13_7)
#define CYBSP_A0 (P14_0)
#define CYBSP_A1 (P14_1)
#define CYBSP_A2 (P14_2)
#define CYBSP_A3 (P14_3)
#define CYBSP_A4 (P14_4)
#define CYBSP_A5 (P14_5)
#define CYBSP_A6 (P14_6)
#define CYBSP_A7 (P14_7)
#define CYBSP_I2C_SDA (P15_1)
#define CYBSP_I2C_SCL (P15_2)
#define CYBSP_USER_LED (P16_1)
#define CYBSP_USER_LED1 CYBSP_USER_LED
#define LED1 CYBSP_USER_LED
#define CYBSP_USER_LED2 (P16_2)
#define LED2 CYBSP_USER_LED2
#define CYBSP_USER_LED3 (P16_3)
#define LED3 CYBSP_USER_LED3
#define CYBSP_USER_BTN2 (P17_3)
#endif /* defined (CY_USING_HAL) */

#define CYBSP_WCO_IN_ENABLED 1U
#define CYBSP_WCO_IN_PORT GPIO_PRT21
#define CYBSP_WCO_IN_PORT_NUM 21U
#define CYBSP_WCO_IN_PIN 0U
#define CYBSP_WCO_IN_NUM 0U
#define CYBSP_WCO_IN_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_WCO_IN_INIT_DRIVESTATE 1
#ifndef ioss_0_port_21_pin_0_HSIOM
    #define ioss_0_port_21_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_WCO_IN_HSIOM ioss_0_port_21_pin_0_HSIOM
#define CYBSP_WCO_IN_IRQ ioss_interrupts_gpio_21_IRQn

#if defined (CY_USING_HAL)
#define CYBSP_WCO_IN_HAL_PORT_PIN P21_0
#define CYBSP_WCO_IN P21_0
#define CYBSP_WCO_IN_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_WCO_IN_HAL_DIR CYHAL_GPIO_DIR_INPUT
#define CYBSP_WCO_IN_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) */

#define CYBSP_WCO_OUT_ENABLED 1U
#define CYBSP_WCO_OUT_PORT GPIO_PRT21
#define CYBSP_WCO_OUT_PORT_NUM 21U
#define CYBSP_WCO_OUT_PIN 1U
#define CYBSP_WCO_OUT_NUM 1U
#define CYBSP_WCO_OUT_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_WCO_OUT_INIT_DRIVESTATE 1
#ifndef ioss_0_port_21_pin_1_HSIOM
    #define ioss_0_port_21_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_WCO_OUT_HSIOM ioss_0_port_21_pin_1_HSIOM
#define CYBSP_WCO_OUT_IRQ ioss_interrupts_gpio_21_IRQn

#if defined (CY_USING_HAL)
#define CYBSP_WCO_OUT_HAL_PORT_PIN P21_1
#define CYBSP_WCO_OUT P21_1
#define CYBSP_WCO_OUT_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_WCO_OUT_HAL_DIR CYHAL_GPIO_DIR_INPUT
#define CYBSP_WCO_OUT_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) */

#define CYBSP_ECO_IN_ENABLED 1U
#define CYBSP_ECO_IN_PORT GPIO_PRT21
#define CYBSP_ECO_IN_PORT_NUM 21U
#define CYBSP_ECO_IN_PIN 2U
#define CYBSP_ECO_IN_NUM 2U
#define CYBSP_ECO_IN_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_ECO_IN_INIT_DRIVESTATE 1
#ifndef ioss_0_port_21_pin_2_HSIOM
    #define ioss_0_port_21_pin_2_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ECO_IN_HSIOM ioss_0_port_21_pin_2_HSIOM
#define CYBSP_ECO_IN_IRQ ioss_interrupts_gpio_21_IRQn

#if defined (CY_USING_HAL)
#define CYBSP_ECO_IN_HAL_PORT_PIN P21_2
#define CYBSP_ECO_IN P21_2
#define CYBSP_ECO_IN_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ECO_IN_HAL_DIR CYHAL_GPIO_DIR_INPUT
#define CYBSP_ECO_IN_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) */

#define CYBSP_ECO_OUT_ENABLED 1U
#define CYBSP_ECO_OUT_PORT GPIO_PRT21
#define CYBSP_ECO_OUT_PORT_NUM 21U
#define CYBSP_ECO_OUT_PIN 3U
#define CYBSP_ECO_OUT_NUM 3U
#define CYBSP_ECO_OUT_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_ECO_OUT_INIT_DRIVESTATE 1
#ifndef ioss_0_port_21_pin_3_HSIOM
    #define ioss_0_port_21_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_ECO_OUT_HSIOM ioss_0_port_21_pin_3_HSIOM
#define CYBSP_ECO_OUT_IRQ ioss_interrupts_gpio_21_IRQn

#if defined (CY_USING_HAL)
#define CYBSP_ECO_OUT_HAL_PORT_PIN P21_3
#define CYBSP_ECO_OUT P21_3
#define CYBSP_ECO_OUT_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ECO_OUT_HAL_DIR CYHAL_GPIO_DIR_INPUT
#define CYBSP_ECO_OUT_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#define CYBSP_USER_BTN1 (P21_4)
#define CYBSP_USER_BTN CYBSP_USER_BTN1
#define CYBSP_TRACE_DATA0 (P21_5)
#define CYBSP_TRACE_DATA1 (P22_1)
#define CYBSP_TRACE_DATA2 (P22_2)
#define CYBSP_TRACE_DATA3 (P22_3)
#define CYBSP_TRACE_CLK (P22_4)
#endif /* defined (CY_USING_HAL) */

#define CYBSP_SWO_ENABLED 1U
#define CYBSP_SWO_PORT GPIO_PRT23
#define CYBSP_SWO_PORT_NUM 23U
#define CYBSP_SWO_PIN 4U
#define CYBSP_SWO_NUM 4U
#define CYBSP_SWO_DRIVEMODE CY_GPIO_DM_STRONG_IN_OFF
#define CYBSP_SWO_INIT_DRIVESTATE 1
#ifndef ioss_0_port_23_pin_4_HSIOM
    #define ioss_0_port_23_pin_4_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_SWO_HSIOM ioss_0_port_23_pin_4_HSIOM
#define CYBSP_SWO_IRQ ioss_interrupts_gpio_23_IRQn

#if defined (CY_USING_HAL)
#define CYBSP_SWO_HAL_PORT_PIN P23_4
#define CYBSP_SWO P23_4
#define CYBSP_SWO_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_SWO_HAL_DIR CYHAL_GPIO_DIR_OUTPUT
#define CYBSP_SWO_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#endif /* defined (CY_USING_HAL) */

#define CYBSP_SWDCK_ENABLED 1U
#define CYBSP_SWDCK_PORT GPIO_PRT23
#define CYBSP_SWDCK_PORT_NUM 23U
#define CYBSP_SWDCK_PIN 5U
#define CYBSP_SWDCK_NUM 5U
#define CYBSP_SWDCK_DRIVEMODE CY_GPIO_DM_PULLDOWN
#define CYBSP_SWDCK_INIT_DRIVESTATE 1
#ifndef ioss_0_port_23_pin_5_HSIOM
    #define ioss_0_port_23_pin_5_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_SWDCK_HSIOM ioss_0_port_23_pin_5_HSIOM
#define CYBSP_SWDCK_IRQ ioss_interrupts_gpio_23_IRQn

#if defined (CY_USING_HAL)
#define CYBSP_SWDCK_HAL_PORT_PIN P23_5
#define CYBSP_SWDCK P23_5
#define CYBSP_SWDCK_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_SWDCK_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL
#define CYBSP_SWDCK_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLDOWN
#endif /* defined (CY_USING_HAL) */

#define CYBSP_SWDIO_ENABLED 1U
#define CYBSP_SWDIO_PORT GPIO_PRT23
#define CYBSP_SWDIO_PORT_NUM 23U
#define CYBSP_SWDIO_PIN 6U
#define CYBSP_SWDIO_NUM 6U
#define CYBSP_SWDIO_DRIVEMODE CY_GPIO_DM_PULLUP
#define CYBSP_SWDIO_INIT_DRIVESTATE 1
#ifndef ioss_0_port_23_pin_6_HSIOM
    #define ioss_0_port_23_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_SWDIO_HSIOM ioss_0_port_23_pin_6_HSIOM
#define CYBSP_SWDIO_IRQ ioss_interrupts_gpio_23_IRQn

#if defined (CY_USING_HAL)
#define CYBSP_SWDIO_HAL_PORT_PIN P23_6
#define CYBSP_SWDIO P23_6
#define CYBSP_SWDIO_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_SWDIO_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL
#define CYBSP_SWDIO_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLUP
#define CYBSP_WIFI_SDIO_CLK (P24_2)
#define CYBSP_WIFI_SDIO_CMD (P24_3)
#define CYBSP_WIFI_SDIO_D0 (P25_0)
#define CYBSP_WIFI_SDIO_D1 (P25_1)
#define CYBSP_WIFI_SDIO_D2 (P25_2)
#define CYBSP_WIFI_SDIO_D3 (P25_3)
#define CYBSP_WIFI_HOST_WAKE (P25_4)
#define CYBSP_WIFI_WL_REG_ON (P25_6)
#define CYBSP_BT_UART_RX (P32_0)
#define CYBSP_BT_UART_TX (P32_1)
#define CYBSP_BT_UART_RTS (P32_2)
#define CYBSP_BT_UART_CTS (P32_3)
#define CYBSP_BT_HOST_WAKE (P32_4)
#define CYBSP_BT_DEVICE_WAKE (P32_5)
#define CYBSP_BT_POWER (P32_6)
#define CYBSP_QSPI_SCK (P6_3)
#define CYBSP_QSPI_SS (P6_5)
#define CYBSP_QSPI_FLASH_SSEL CYBSP_QSPI_SS
#define CYBSP_POT (P6_6)
#define CYBSP_QSPI_D0 (P7_1)
#define CYBSP_QSPI_D1 (P7_2)
#define CYBSP_QSPI_D2 (P7_3)
#define CYBSP_QSPI_D3 (P7_4)
#endif /* defined (CY_USING_HAL) */

extern const cy_stc_gpio_pin_config_t CYBSP_WCO_IN_config;

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t CYBSP_WCO_IN_obj;
#endif /* defined (CY_USING_HAL) */

extern const cy_stc_gpio_pin_config_t CYBSP_WCO_OUT_config;

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t CYBSP_WCO_OUT_obj;
#endif /* defined (CY_USING_HAL) */

extern const cy_stc_gpio_pin_config_t CYBSP_ECO_IN_config;

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t CYBSP_ECO_IN_obj;
#endif /* defined (CY_USING_HAL) */

extern const cy_stc_gpio_pin_config_t CYBSP_ECO_OUT_config;

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t CYBSP_ECO_OUT_obj;
#endif /* defined (CY_USING_HAL) */

extern const cy_stc_gpio_pin_config_t CYBSP_SWO_config;

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t CYBSP_SWO_obj;
#endif /* defined (CY_USING_HAL) */

extern const cy_stc_gpio_pin_config_t CYBSP_SWDCK_config;

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t CYBSP_SWDCK_obj;
#endif /* defined (CY_USING_HAL) */

extern const cy_stc_gpio_pin_config_t CYBSP_SWDIO_config;

#if defined (CY_USING_HAL)
extern const cyhal_resource_inst_t CYBSP_SWDIO_obj;
#endif /* defined (CY_USING_HAL) */

void init_cycfg_pins(void);
void reserve_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_PINS_H */
