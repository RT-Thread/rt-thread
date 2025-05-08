/*******************************************************************************
 * File Name: cycfg_pins.h
 *
 * Description:
 * Pin configuration
 * This file was automatically generated and should not be modified.
 * Configurator Backend 3.50.0
 * device-db 4.22.0.7873
 * mtb-pdl-cat1 3.15.0.40227
 *
 *******************************************************************************
 * Copyright 2025 Cypress Semiconductor Corporation (an Infineon company) or
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
#include "cy_smartio.h"
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

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_D2 (P0_0)
#define CYBSP_S2G1_INT CYBSP_D2
#define CYBSP_S2G2_INT CYBSP_D2
#define CYBSP_D3 (P0_1)
#define CYBSP_I2C_SCL (P0_2)
#define CYBSP_S2G1_I2C_SCL CYBSP_I2C_SCL
#define CYBSP_MIKROBUS_I2C_SCL CYBSP_I2C_SCL
#define CYBSP_S2G2_I2C_SCL CYBSP_I2C_SCL
#define CYBSP_I2C_SDA (P0_3)
#define CYBSP_S2G1_I2C_SDA CYBSP_I2C_SDA
#define CYBSP_MIKROBUS_I2C_SDA CYBSP_I2C_SDA
#define CYBSP_S2G2_I2C_SDA CYBSP_I2C_SDA
#define CYBSP_DEBUG_UART_RX (P10_0)
#define CYBSP_DEBUG_UART_TX (P10_1)
#define CYBSP_A1 (P11_0)
#define CYBSP_S2G1_GPIO1 CYBSP_A1
#define CYBSP_S2G2_GPIO1 CYBSP_A1
#define CYBSP_A2 (P11_1)
#define CYBSP_MIKROBUS_INT CYBSP_A2
#define CYBSP_A3 (P11_2)
#define CYBSP_MIKROBUS_UART_RX (P12_0)
#define CYBSP_MIKROBUS_UART_TX (P12_1)
#define CYBSP_D9 (P12_2)
#define CYBSP_D8 (P12_3)
#define CYBSP_SPI_MISO (P13_0)
#define CYBSP_S2G1_SPI_MISO CYBSP_SPI_MISO
#define CYBSP_MIKROBUS_SPI_MISO CYBSP_SPI_MISO
#define CYBSP_S2G2_SPI_MISO CYBSP_SPI_MISO
#define CYBSP_SPI_MOSI (P13_1)
#define CYBSP_S2G1_SPI_MOSI CYBSP_SPI_MOSI
#define CYBSP_MIKROBUS_SPI_MOSI CYBSP_SPI_MOSI
#define CYBSP_S2G2_SPI_MOSI CYBSP_SPI_MOSI
#define CYBSP_SPI_CLK (P13_2)
#define CYBSP_S2G1_SPI_SCK CYBSP_SPI_CLK
#define CYBSP_MIKROBUS_SPI_SCK CYBSP_SPI_CLK
#define CYBSP_S2G2_SPI_SCK CYBSP_SPI_CLK
#define CYBSP_SPI_CS (P13_3)
#define CYBSP_MIKROBUS_SPI_CS (P13_4)
#define CYBSP_S2G2_SPI_CS (P13_5)
#define CYBSP_S2G1_SPI_CS (P13_6)
#define CYBSP_A4 (P13_7)
#define CYBSP_S2G1_UART_RX (P14_0)
#define CYBSP_S2G2_UART_RX CYBSP_S2G1_UART_RX
#define CYBSP_S2G1_UART_TX (P14_1)
#define CYBSP_S2G2_UART_TX CYBSP_S2G1_UART_TX
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

#define ioss_0_port_14_smartio_0_ENABLED 1U
#define ioss_0_port_14_smartio_0_HW SMARTIO_PRT14

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ETH_REF_CLK (P18_0)
#define CYBSP_ETH_TX_CTL (P18_1)
#define CYBSP_MIKROBUS_AN (P18_2)
#define CYBSP_ETH_TXD_0 (P18_4)
#define CYBSP_ETH_TXD_1 (P18_5)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */
#define M2B_ENABLED 1U
#define M2B_PORT GPIO_PRT18
#define M2B_PORT_NUM 18U
#define M2B_PIN 6U
#define M2B_NUM 6U
#define M2B_DRIVEMODE CY_GPIO_DM_HIGHZ
#define M2B_INIT_DRIVESTATE 1
#ifndef ioss_0_port_18_pin_6_HSIOM
    #define ioss_0_port_18_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define M2B_HSIOM ioss_0_port_18_pin_6_HSIOM
#define M2B_IRQ ioss_interrupts_gpio_dpslp_18_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define M2B_HAL_PORT_PIN P18_6
#define M2B P18_6
#define M2B_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define M2B_HAL_DIR CYHAL_GPIO_DIR_INPUT
#define M2B_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_NONE
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */
#define M2A_ENABLED 1U
#define M2A_PORT GPIO_PRT18
#define M2A_PORT_NUM 18U
#define M2A_PIN 7U
#define M2A_NUM 7U
#define M2A_DRIVEMODE CY_GPIO_DM_HIGHZ
#define M2A_INIT_DRIVESTATE 1
#ifndef ioss_0_port_18_pin_7_HSIOM
    #define ioss_0_port_18_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define M2A_HSIOM ioss_0_port_18_pin_7_HSIOM
#define M2A_IRQ ioss_interrupts_gpio_dpslp_18_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define M2A_HAL_PORT_PIN P18_7
#define M2A P18_7
#define M2A_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define M2A_HAL_DIR CYHAL_GPIO_DIR_INPUT
#define M2A_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_NONE
#define UART_RX (P19_0)
#define UART_TX (P19_1)
#define CYBSP_MIKROBUS_PWM (P19_3)
#define CYBSP_WCO_IN (P21_0)
#define CYBSP_WCO_OUT (P21_1)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */
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
#define CYBSP_ECO_IN_IRQ ioss_interrupts_gpio_dpslp_21_IRQn

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ECO_IN_HAL_PORT_PIN P21_2
#define CYBSP_ECO_IN P21_2
#define CYBSP_ECO_IN_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ECO_IN_HAL_DIR CYHAL_GPIO_DIR_INPUT
#define CYBSP_ECO_IN_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */
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
#define CYBSP_ECO_OUT_IRQ ioss_interrupts_gpio_dpslp_21_IRQn
#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_ECO_OUT_HAL_PORT_PIN P21_3
#define CYBSP_ECO_OUT P21_3
#define CYBSP_ECO_OUT_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_ECO_OUT_HAL_DIR CYHAL_GPIO_DIR_INPUT
#define CYBSP_ECO_OUT_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#define CYBSP_ETH_RX_CTL (P21_5)
#define CYBSP_S2G1_PWM (P23_3)
#define CYBSP_S2G2_PWM CYBSP_S2G1_PWM
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */
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
#define CYBSP_SWO_IRQ ioss_interrupts_gpio_dpslp_23_IRQn
#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_SWO_HAL_PORT_PIN P23_4
#define CYBSP_SWO P23_4
#define CYBSP_SWO_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_SWO_HAL_DIR CYHAL_GPIO_DIR_OUTPUT
#define CYBSP_SWO_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_STRONG
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */
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
#define CYBSP_SWDCK_IRQ ioss_interrupts_gpio_dpslp_23_IRQn
#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_SWDCK_HAL_PORT_PIN P23_5
#define CYBSP_SWDCK P23_5
#define CYBSP_SWDCK_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_SWDCK_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL
#define CYBSP_SWDCK_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLDOWN
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */
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
#define CYBSP_SWDIO_IRQ ioss_interrupts_gpio_dpslp_23_IRQn
#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
#define CYBSP_SWDIO_HAL_PORT_PIN P23_6
#define CYBSP_SWDIO P23_6
#define CYBSP_SWDIO_HAL_IRQ CYHAL_GPIO_IRQ_NONE
#define CYBSP_SWDIO_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL
#define CYBSP_SWDIO_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLUP
#define CYBSP_ETH_RX_ERR (P2_2)
#define CYBSP_ETH_MDIO (P3_0)
#define CYBSP_ETH_MDC (P3_1)
#define CYBSP_USER_LED2 (P5_1)
#define LED2 CYBSP_USER_LED2
#define CYBSP_CANFD_STB (P5_2)
#define CYBSP_USER_BTN1 (P5_3)
#define CYBSP_USER_BTN CYBSP_USER_BTN1
#define CYBSP_POT (P6_0)
#define CYBSP_D4 (P6_1)
#define CYBSP_QSPI_SCK (P6_3)
#define CYBSP_FLASH_RST (P6_4)
#define CYBSP_QSPI_SS (P7_0)
#define CYBSP_QSPI_D0 (P7_1)
#define CYBSP_QSPI_D1 (P7_2)
#define CYBSP_QSPI_D2 (P7_3)
#define CYBSP_QSPI_D3 (P7_4)
#define CYBSP_USER_BUZZER (P7_5)
#define CYBSP_CAN_TX (P8_0)
#define CYBSP_CAN_RX (P8_1)
#define M1B (P8_2)
#define M1A (P8_3)
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_smartio_config_t ioss_0_port_14_smartio_0_config;
extern const cy_stc_gpio_pin_config_t M2B_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t M2B_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t M2A_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t M2A_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ECO_IN_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ECO_IN_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_ECO_OUT_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_ECO_OUT_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_SWO_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_SWO_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_SWDCK_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_SWDCK_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

extern const cy_stc_gpio_pin_config_t CYBSP_SWDIO_config;

#if defined (CY_USING_HAL) || (CY_USING_HAL_LITE)
extern const cyhal_resource_inst_t CYBSP_SWDIO_obj;
#endif /* defined (CY_USING_HAL) || (CY_USING_HAL_LITE) */

void init_cycfg_pins(void);
void reserve_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* CYCFG_PINS_H */