/*******************************************************************************
* File Name: cycfg_pins.h
*
* Description:
* Pin configuration
* This file was automatically generated and should not be modified.
* Configurator Backend 3.0.0
* device-db 4.3.0.3855
* mtb-pdl-cat1 3.4.0.24948
*
********************************************************************************
* Copyright 2023 Cypress Semiconductor Corporation (an Infineon company) or
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
********************************************************************************/

#if !defined(CYCFG_PINS_H)
#define CYCFG_PINS_H

#include "cycfg_notices.h"
#include "cy_gpio.h"
#include "cycfg_routing.h"
#if defined (CY_USING_HAL)
    #include "cyhal_hwmgr.h"
#endif //defined (CY_USING_HAL)

#if defined(__cplusplus)
extern "C" {
#endif

#if defined (CY_USING_HAL)
    #define CYBSP_USER_LED1 (P0_0)
    #define CYBSP_USER_LED2 (P0_1)
    #define CYBSP_SW2 (P0_4)
    #define CYBSP_USER_BTN1 CYBSP_SW2
    #define CYBSP_LED_RGB_GREEN (P0_5)
    #define CYBSP_A0 (P10_0)
    #define CYBSP_J2_1 CYBSP_A0
    #define CYBSP_A1 (P10_1)
    #define CYBSP_J2_3 CYBSP_A1
    #define CYBSP_A2 (P10_2)
    #define CYBSP_J2_5 CYBSP_A2
    #define CYBSP_A3 (P10_3)
    #define CYBSP_J2_7 CYBSP_A3
    #define CYBSP_A4 (P10_4)
    #define CYBSP_J2_9 CYBSP_A4
    #define CYBSP_A5 (P10_5)
    #define CYBSP_J2_11 CYBSP_A5
    #define CYBSP_BT_UART_RX (P11_0)
    #define CYBSP_BT_UART_TX (P11_1)
    #define CYBSP_BT_UART_RTS (P11_2)
    #define CYBSP_BT_UART_CTS (P11_3)
    #define CYBSP_BT_DEVICE_WAKE (P11_6)
    #define CYBSP_BT_POWER (P11_7)
    #define CYBSP_WIFI_HOST_WAKE (P12_6)
    #define CYBSP_BT_HOST_WAKE (P12_7)
    #define CYBSP_WIFI_SDIO_D0 (P2_0)
    #define CYBSP_WIFI_SDIO_D1 (P2_1)
    #define CYBSP_WIFI_SDIO_D2 (P2_2)
    #define CYBSP_WIFI_SDIO_D3 (P2_3)
    #define CYBSP_WIFI_SDIO_CMD (P2_4)
    #define CYBSP_WIFI_SDIO_CLK (P2_5)
    #define CYBSP_WIFI_WL_REG_ON (P2_7)
    #define CYBSP_D0 (P5_0)
    #define CYBSP_D1 (P5_1)
    #define CYBSP_D6 (P5_6)
    #define CYBSP_D7 (P5_7)
    #define CYBSP_USER_BTN (P6_2)
    #define CYBSP_DEBUG_UART_RX (P6_4)
    #define CYBSP_DEBUG_UART_TX (P6_5)
#endif //defined (CY_USING_HAL)
#define CYBSP_SWDIO_ENABLED 1U
#define CYBSP_SWDIO_PORT GPIO_PRT6
#define CYBSP_SWDIO_PORT_NUM 6U
#define CYBSP_SWDIO_PIN 6U
#define CYBSP_SWDIO_NUM 6U
#define CYBSP_SWDIO_DRIVEMODE CY_GPIO_DM_PULLUP
#define CYBSP_SWDIO_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_6_HSIOM
    #define ioss_0_port_6_pin_6_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_SWDIO_HSIOM ioss_0_port_6_pin_6_HSIOM
#define CYBSP_SWDIO_IRQ ioss_interrupts_gpio_6_IRQn
#if defined (CY_USING_HAL)
    #define CYBSP_SWDIO_HAL_PORT_PIN P6_6
    #define CYBSP_SWDIO P6_6
    #define CYBSP_SWDIO_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_SWDIO_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL 
    #define CYBSP_SWDIO_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLUP
#endif //defined (CY_USING_HAL)
#define CYBSP_SWDCK_ENABLED 1U
#define CYBSP_SWDCK_PORT GPIO_PRT6
#define CYBSP_SWDCK_PORT_NUM 6U
#define CYBSP_SWDCK_PIN 7U
#define CYBSP_SWDCK_NUM 7U
#define CYBSP_SWDCK_DRIVEMODE CY_GPIO_DM_PULLDOWN
#define CYBSP_SWDCK_INIT_DRIVESTATE 1
#ifndef ioss_0_port_6_pin_7_HSIOM
    #define ioss_0_port_6_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_SWDCK_HSIOM ioss_0_port_6_pin_7_HSIOM
#define CYBSP_SWDCK_IRQ ioss_interrupts_gpio_6_IRQn
#if defined (CY_USING_HAL)
    #define CYBSP_SWDCK_HAL_PORT_PIN P6_7
    #define CYBSP_SWDCK P6_7
    #define CYBSP_SWDCK_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_SWDCK_HAL_DIR CYHAL_GPIO_DIR_BIDIRECTIONAL 
    #define CYBSP_SWDCK_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_PULLDOWN
    #define CYBSP_TRACE_CLK (P7_0)
#endif //defined (CY_USING_HAL)
#define CYBSP_CINA_ENABLED 1U
#define CYBSP_CINA_PORT GPIO_PRT7
#define CYBSP_CINA_PORT_NUM 7U
#define CYBSP_CINA_PIN 1U
#define CYBSP_CINA_NUM 1U
#define CYBSP_CINA_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_CINA_INIT_DRIVESTATE 1
#ifndef ioss_0_port_7_pin_1_HSIOM
    #define ioss_0_port_7_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_CINA_HSIOM ioss_0_port_7_pin_1_HSIOM
#define CYBSP_CINA_IRQ ioss_interrupts_gpio_7_IRQn
#if defined (CY_USING_HAL)
    #define CYBSP_CINA_HAL_PORT_PIN P7_1
    #define CYBSP_CINA P7_1
    #define CYBSP_CINA_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_CINA_HAL_DIR CYHAL_GPIO_DIR_INPUT 
    #define CYBSP_CINA_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif //defined (CY_USING_HAL)
#define CYBSP_CINB_ENABLED 1U
#define CYBSP_CINB_PORT GPIO_PRT7
#define CYBSP_CINB_PORT_NUM 7U
#define CYBSP_CINB_PIN 2U
#define CYBSP_CINB_NUM 2U
#define CYBSP_CINB_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_CINB_INIT_DRIVESTATE 1
#ifndef ioss_0_port_7_pin_2_HSIOM
    #define ioss_0_port_7_pin_2_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_CINB_HSIOM ioss_0_port_7_pin_2_HSIOM
#define CYBSP_CINB_IRQ ioss_interrupts_gpio_7_IRQn
#if defined (CY_USING_HAL)
    #define CYBSP_CINB_HAL_PORT_PIN P7_2
    #define CYBSP_CINB P7_2
    #define CYBSP_CINB_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_CINB_HAL_DIR CYHAL_GPIO_DIR_INPUT 
    #define CYBSP_CINB_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif //defined (CY_USING_HAL)
#define CYBSP_LED_RGB_BLUE_ENABLED 1U
#define CYBSP_USER_LED5_ENABLED CYBSP_LED_RGB_BLUE_ENABLED
#define CYBSP_LED_RGB_BLUE_PORT GPIO_PRT7
#define CYBSP_USER_LED5_PORT CYBSP_LED_RGB_BLUE_PORT
#define CYBSP_LED_RGB_BLUE_PORT_NUM 7U
#define CYBSP_USER_LED5_PORT_NUM CYBSP_LED_RGB_BLUE_PORT_NUM
#define CYBSP_LED_RGB_BLUE_PIN 3U
#define CYBSP_USER_LED5_PIN CYBSP_LED_RGB_BLUE_PIN
#define CYBSP_LED_RGB_BLUE_NUM 3U
#define CYBSP_USER_LED5_NUM CYBSP_LED_RGB_BLUE_NUM
#define CYBSP_LED_RGB_BLUE_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_USER_LED5_DRIVEMODE CYBSP_LED_RGB_BLUE_DRIVEMODE
#define CYBSP_LED_RGB_BLUE_INIT_DRIVESTATE 1
#define CYBSP_USER_LED5_INIT_DRIVESTATE CYBSP_LED_RGB_BLUE_INIT_DRIVESTATE
#ifndef ioss_0_port_7_pin_3_HSIOM
    #define ioss_0_port_7_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_LED_RGB_BLUE_HSIOM ioss_0_port_7_pin_3_HSIOM
#define CYBSP_USER_LED5_HSIOM CYBSP_LED_RGB_BLUE_HSIOM
#define CYBSP_LED_RGB_BLUE_IRQ ioss_interrupts_gpio_7_IRQn
#define CYBSP_USER_LED5_IRQ CYBSP_LED_RGB_BLUE_IRQ
#if defined (CY_USING_HAL)
    #define CYBSP_LED_RGB_BLUE_HAL_PORT_PIN P7_3
    #define CYBSP_USER_LED5_HAL_PORT_PIN CYBSP_LED_RGB_BLUE_HAL_PORT_PIN
    #define CYBSP_LED_RGB_BLUE P7_3
    #define CYBSP_USER_LED5 CYBSP_LED_RGB_BLUE
    #define CYBSP_LED_RGB_BLUE_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_USER_LED5_HAL_IRQ CYBSP_LED_RGB_BLUE_HAL_IRQ
    #define CYBSP_LED_RGB_BLUE_HAL_DIR CYHAL_GPIO_DIR_INPUT 
    #define CYBSP_USER_LED5_HAL_DIR CYBSP_LED_RGB_BLUE_HAL_DIR
    #define CYBSP_LED_RGB_BLUE_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
    #define CYBSP_USER_LED5_HAL_DRIVEMODE CYBSP_LED_RGB_BLUE_HAL_DRIVEMODE
#endif //defined (CY_USING_HAL)
#define CYBSP_CMOD_ENABLED 1U
#define CYBSP_CMOD_PORT GPIO_PRT7
#define CYBSP_CMOD_PORT_NUM 7U
#define CYBSP_CMOD_PIN 7U
#define CYBSP_CMOD_NUM 7U
#define CYBSP_CMOD_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_CMOD_INIT_DRIVESTATE 1
#ifndef ioss_0_port_7_pin_7_HSIOM
    #define ioss_0_port_7_pin_7_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_CMOD_HSIOM ioss_0_port_7_pin_7_HSIOM
#define CYBSP_CMOD_IRQ ioss_interrupts_gpio_7_IRQn
#if defined (CY_USING_HAL)
    #define CYBSP_CMOD_HAL_PORT_PIN P7_7
    #define CYBSP_CMOD P7_7
    #define CYBSP_CMOD_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_CMOD_HAL_DIR CYHAL_GPIO_DIR_INPUT 
    #define CYBSP_CMOD_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
#endif //defined (CY_USING_HAL)
#define CYBSP_CSD_BTN0_ENABLED 1U
#define CYBSP_CS_BTN0_ENABLED CYBSP_CSD_BTN0_ENABLED
#define CYBSP_CSD_BTN0_PORT GPIO_PRT8
#define CYBSP_CS_BTN0_PORT CYBSP_CSD_BTN0_PORT
#define CYBSP_CSD_BTN0_PORT_NUM 8U
#define CYBSP_CS_BTN0_PORT_NUM CYBSP_CSD_BTN0_PORT_NUM
#define CYBSP_CSD_BTN0_PIN 1U
#define CYBSP_CS_BTN0_PIN CYBSP_CSD_BTN0_PIN
#define CYBSP_CSD_BTN0_NUM 1U
#define CYBSP_CS_BTN0_NUM CYBSP_CSD_BTN0_NUM
#define CYBSP_CSD_BTN0_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_CS_BTN0_DRIVEMODE CYBSP_CSD_BTN0_DRIVEMODE
#define CYBSP_CSD_BTN0_INIT_DRIVESTATE 1
#define CYBSP_CS_BTN0_INIT_DRIVESTATE CYBSP_CSD_BTN0_INIT_DRIVESTATE
#ifndef ioss_0_port_8_pin_1_HSIOM
    #define ioss_0_port_8_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_CSD_BTN0_HSIOM ioss_0_port_8_pin_1_HSIOM
#define CYBSP_CS_BTN0_HSIOM CYBSP_CSD_BTN0_HSIOM
#define CYBSP_CSD_BTN0_IRQ ioss_interrupts_gpio_8_IRQn
#define CYBSP_CS_BTN0_IRQ CYBSP_CSD_BTN0_IRQ
#if defined (CY_USING_HAL)
    #define CYBSP_CSD_BTN0_HAL_PORT_PIN P8_1
    #define CYBSP_CS_BTN0_HAL_PORT_PIN CYBSP_CSD_BTN0_HAL_PORT_PIN
    #define CYBSP_CSD_BTN0 P8_1
    #define CYBSP_CS_BTN0 CYBSP_CSD_BTN0
    #define CYBSP_CSD_BTN0_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_CS_BTN0_HAL_IRQ CYBSP_CSD_BTN0_HAL_IRQ
    #define CYBSP_CSD_BTN0_HAL_DIR CYHAL_GPIO_DIR_INPUT 
    #define CYBSP_CS_BTN0_HAL_DIR CYBSP_CSD_BTN0_HAL_DIR
    #define CYBSP_CSD_BTN0_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
    #define CYBSP_CS_BTN0_HAL_DRIVEMODE CYBSP_CSD_BTN0_HAL_DRIVEMODE
#endif //defined (CY_USING_HAL)
#define CYBSP_A8_ENABLED 1U
#define CYBSP_J2_2_ENABLED CYBSP_A8_ENABLED
#define CYBSP_A8_PORT GPIO_PRT9
#define CYBSP_J2_2_PORT CYBSP_A8_PORT
#define CYBSP_A8_PORT_NUM 9U
#define CYBSP_J2_2_PORT_NUM CYBSP_A8_PORT_NUM
#define CYBSP_A8_PIN 0U
#define CYBSP_J2_2_PIN CYBSP_A8_PIN
#define CYBSP_A8_NUM 0U
#define CYBSP_J2_2_NUM CYBSP_A8_NUM
#define CYBSP_A8_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_J2_2_DRIVEMODE CYBSP_A8_DRIVEMODE
#define CYBSP_A8_INIT_DRIVESTATE 1
#define CYBSP_J2_2_INIT_DRIVESTATE CYBSP_A8_INIT_DRIVESTATE
#ifndef ioss_0_port_9_pin_0_HSIOM
    #define ioss_0_port_9_pin_0_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_A8_HSIOM ioss_0_port_9_pin_0_HSIOM
#define CYBSP_J2_2_HSIOM CYBSP_A8_HSIOM
#define CYBSP_A8_IRQ ioss_interrupts_gpio_9_IRQn
#define CYBSP_J2_2_IRQ CYBSP_A8_IRQ
#if defined (CY_USING_HAL)
    #define CYBSP_A8_HAL_PORT_PIN P9_0
    #define CYBSP_J2_2_HAL_PORT_PIN CYBSP_A8_HAL_PORT_PIN
    #define CYBSP_A8 P9_0
    #define CYBSP_J2_2 CYBSP_A8
    #define CYBSP_A8_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_J2_2_HAL_IRQ CYBSP_A8_HAL_IRQ
    #define CYBSP_A8_HAL_DIR CYHAL_GPIO_DIR_INPUT 
    #define CYBSP_J2_2_HAL_DIR CYBSP_A8_HAL_DIR
    #define CYBSP_A8_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
    #define CYBSP_J2_2_HAL_DRIVEMODE CYBSP_A8_HAL_DRIVEMODE
#endif //defined (CY_USING_HAL)
#define CYBSP_A9_ENABLED 1U
#define CYBSP_J2_4_ENABLED CYBSP_A9_ENABLED
#define CYBSP_A9_PORT GPIO_PRT9
#define CYBSP_J2_4_PORT CYBSP_A9_PORT
#define CYBSP_A9_PORT_NUM 9U
#define CYBSP_J2_4_PORT_NUM CYBSP_A9_PORT_NUM
#define CYBSP_A9_PIN 1U
#define CYBSP_J2_4_PIN CYBSP_A9_PIN
#define CYBSP_A9_NUM 1U
#define CYBSP_J2_4_NUM CYBSP_A9_NUM
#define CYBSP_A9_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_J2_4_DRIVEMODE CYBSP_A9_DRIVEMODE
#define CYBSP_A9_INIT_DRIVESTATE 1
#define CYBSP_J2_4_INIT_DRIVESTATE CYBSP_A9_INIT_DRIVESTATE
#ifndef ioss_0_port_9_pin_1_HSIOM
    #define ioss_0_port_9_pin_1_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_A9_HSIOM ioss_0_port_9_pin_1_HSIOM
#define CYBSP_J2_4_HSIOM CYBSP_A9_HSIOM
#define CYBSP_A9_IRQ ioss_interrupts_gpio_9_IRQn
#define CYBSP_J2_4_IRQ CYBSP_A9_IRQ
#if defined (CY_USING_HAL)
    #define CYBSP_A9_HAL_PORT_PIN P9_1
    #define CYBSP_J2_4_HAL_PORT_PIN CYBSP_A9_HAL_PORT_PIN
    #define CYBSP_A9 P9_1
    #define CYBSP_J2_4 CYBSP_A9
    #define CYBSP_A9_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_J2_4_HAL_IRQ CYBSP_A9_HAL_IRQ
    #define CYBSP_A9_HAL_DIR CYHAL_GPIO_DIR_INPUT 
    #define CYBSP_J2_4_HAL_DIR CYBSP_A9_HAL_DIR
    #define CYBSP_A9_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
    #define CYBSP_J2_4_HAL_DRIVEMODE CYBSP_A9_HAL_DRIVEMODE
#endif //defined (CY_USING_HAL)
#define CYBSP_A10_ENABLED 1U
#define CYBSP_J2_6_ENABLED CYBSP_A10_ENABLED
#define CYBSP_A10_PORT GPIO_PRT9
#define CYBSP_J2_6_PORT CYBSP_A10_PORT
#define CYBSP_A10_PORT_NUM 9U
#define CYBSP_J2_6_PORT_NUM CYBSP_A10_PORT_NUM
#define CYBSP_A10_PIN 2U
#define CYBSP_J2_6_PIN CYBSP_A10_PIN
#define CYBSP_A10_NUM 2U
#define CYBSP_J2_6_NUM CYBSP_A10_NUM
#define CYBSP_A10_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_J2_6_DRIVEMODE CYBSP_A10_DRIVEMODE
#define CYBSP_A10_INIT_DRIVESTATE 1
#define CYBSP_J2_6_INIT_DRIVESTATE CYBSP_A10_INIT_DRIVESTATE
#ifndef ioss_0_port_9_pin_2_HSIOM
    #define ioss_0_port_9_pin_2_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_A10_HSIOM ioss_0_port_9_pin_2_HSIOM
#define CYBSP_J2_6_HSIOM CYBSP_A10_HSIOM
#define CYBSP_A10_IRQ ioss_interrupts_gpio_9_IRQn
#define CYBSP_J2_6_IRQ CYBSP_A10_IRQ
#if defined (CY_USING_HAL)
    #define CYBSP_A10_HAL_PORT_PIN P9_2
    #define CYBSP_J2_6_HAL_PORT_PIN CYBSP_A10_HAL_PORT_PIN
    #define CYBSP_A10 P9_2
    #define CYBSP_J2_6 CYBSP_A10
    #define CYBSP_A10_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_J2_6_HAL_IRQ CYBSP_A10_HAL_IRQ
    #define CYBSP_A10_HAL_DIR CYHAL_GPIO_DIR_INPUT 
    #define CYBSP_J2_6_HAL_DIR CYBSP_A10_HAL_DIR
    #define CYBSP_A10_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
    #define CYBSP_J2_6_HAL_DRIVEMODE CYBSP_A10_HAL_DRIVEMODE
#endif //defined (CY_USING_HAL)
#define CYBSP_A11_ENABLED 1U
#define CYBSP_J2_8_ENABLED CYBSP_A11_ENABLED
#define CYBSP_TRACE_DATA0_ENABLED CYBSP_A11_ENABLED
#define CYBSP_A11_PORT GPIO_PRT9
#define CYBSP_J2_8_PORT CYBSP_A11_PORT
#define CYBSP_TRACE_DATA0_PORT CYBSP_A11_PORT
#define CYBSP_A11_PORT_NUM 9U
#define CYBSP_J2_8_PORT_NUM CYBSP_A11_PORT_NUM
#define CYBSP_TRACE_DATA0_PORT_NUM CYBSP_A11_PORT_NUM
#define CYBSP_A11_PIN 3U
#define CYBSP_J2_8_PIN CYBSP_A11_PIN
#define CYBSP_TRACE_DATA0_PIN CYBSP_A11_PIN
#define CYBSP_A11_NUM 3U
#define CYBSP_J2_8_NUM CYBSP_A11_NUM
#define CYBSP_TRACE_DATA0_NUM CYBSP_A11_NUM
#define CYBSP_A11_DRIVEMODE CY_GPIO_DM_ANALOG
#define CYBSP_J2_8_DRIVEMODE CYBSP_A11_DRIVEMODE
#define CYBSP_TRACE_DATA0_DRIVEMODE CYBSP_A11_DRIVEMODE
#define CYBSP_A11_INIT_DRIVESTATE 1
#define CYBSP_J2_8_INIT_DRIVESTATE CYBSP_A11_INIT_DRIVESTATE
#define CYBSP_TRACE_DATA0_INIT_DRIVESTATE CYBSP_A11_INIT_DRIVESTATE
#ifndef ioss_0_port_9_pin_3_HSIOM
    #define ioss_0_port_9_pin_3_HSIOM HSIOM_SEL_GPIO
#endif
#define CYBSP_A11_HSIOM ioss_0_port_9_pin_3_HSIOM
#define CYBSP_J2_8_HSIOM CYBSP_A11_HSIOM
#define CYBSP_TRACE_DATA0_HSIOM CYBSP_A11_HSIOM
#define CYBSP_A11_IRQ ioss_interrupts_gpio_9_IRQn
#define CYBSP_J2_8_IRQ CYBSP_A11_IRQ
#define CYBSP_TRACE_DATA0_IRQ CYBSP_A11_IRQ
#if defined (CY_USING_HAL)
    #define CYBSP_A11_HAL_PORT_PIN P9_3
    #define CYBSP_J2_8_HAL_PORT_PIN CYBSP_A11_HAL_PORT_PIN
    #define CYBSP_TRACE_DATA0_HAL_PORT_PIN CYBSP_A11_HAL_PORT_PIN
    #define CYBSP_A11 P9_3
    #define CYBSP_J2_8 CYBSP_A11
    #define CYBSP_TRACE_DATA0 CYBSP_A11
    #define CYBSP_A11_HAL_IRQ CYHAL_GPIO_IRQ_NONE
    #define CYBSP_J2_8_HAL_IRQ CYBSP_A11_HAL_IRQ
    #define CYBSP_TRACE_DATA0_HAL_IRQ CYBSP_A11_HAL_IRQ
    #define CYBSP_A11_HAL_DIR CYHAL_GPIO_DIR_INPUT 
    #define CYBSP_J2_8_HAL_DIR CYBSP_A11_HAL_DIR
    #define CYBSP_TRACE_DATA0_HAL_DIR CYBSP_A11_HAL_DIR
    #define CYBSP_A11_HAL_DRIVEMODE CYHAL_GPIO_DRIVE_ANALOG
    #define CYBSP_J2_8_HAL_DRIVEMODE CYBSP_A11_HAL_DRIVEMODE
    #define CYBSP_TRACE_DATA0_HAL_DRIVEMODE CYBSP_A11_HAL_DRIVEMODE
#endif //defined (CY_USING_HAL)

extern const cy_stc_gpio_pin_config_t CYBSP_SWDIO_config;
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_SWDIO_obj;
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_SWDCK_config;
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_SWDCK_obj;
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_CINA_config;
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_CINA_obj;
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_CINB_config;
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_CINB_obj;
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_LED_RGB_BLUE_config;
#define CYBSP_USER_LED5_config CYBSP_LED_RGB_BLUE_config
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_LED_RGB_BLUE_obj;
    #define CYBSP_USER_LED5_obj CYBSP_LED_RGB_BLUE_obj
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_CMOD_config;
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_CMOD_obj;
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_CSD_BTN0_config;
#define CYBSP_CS_BTN0_config CYBSP_CSD_BTN0_config
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_CSD_BTN0_obj;
    #define CYBSP_CS_BTN0_obj CYBSP_CSD_BTN0_obj
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_A8_config;
#define CYBSP_J2_2_config CYBSP_A8_config
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_A8_obj;
    #define CYBSP_J2_2_obj CYBSP_A8_obj
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_A9_config;
#define CYBSP_J2_4_config CYBSP_A9_config
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_A9_obj;
    #define CYBSP_J2_4_obj CYBSP_A9_obj
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_A10_config;
#define CYBSP_J2_6_config CYBSP_A10_config
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_A10_obj;
    #define CYBSP_J2_6_obj CYBSP_A10_obj
#endif //defined (CY_USING_HAL)
extern const cy_stc_gpio_pin_config_t CYBSP_A11_config;
#define CYBSP_J2_8_config CYBSP_A11_config
#define CYBSP_TRACE_DATA0_config CYBSP_A11_config
#if defined (CY_USING_HAL)
    extern const cyhal_resource_inst_t CYBSP_A11_obj;
    #define CYBSP_J2_8_obj CYBSP_A11_obj
    #define CYBSP_TRACE_DATA0_obj CYBSP_A11_obj
#endif //defined (CY_USING_HAL)

void init_cycfg_pins(void);
void reserve_cycfg_pins(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PINS_H */
