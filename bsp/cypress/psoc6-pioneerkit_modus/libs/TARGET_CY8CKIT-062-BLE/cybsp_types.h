/***************************************************************************//**
* \file CY8CKIT-062-BLE/cybsp_types.h
*
* Description:
* Provides APIs for interacting with the hardware contained on the Cypress
* CY8CKIT-062-BLE pioneer kit.
*
********************************************************************************
* \copyright
* Copyright 2018-2019 Cypress Semiconductor Corporation
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
*******************************************************************************/

#pragma once

#if defined(CY_USING_HAL)
#include "cyhal_pin_package.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_bsp_settings BSP Settings
* \{
*
* <div class="category">Peripheral Default HAL Settings:</div>
* | Resource | Parameter | Value | Remarks |
* | :------: | :-------: | :---: | :------ |
* | ADC      | VREF      | 1.2 V | |
* | ^        | Measurement type | Single Ended | |
* | ^        | Input voltage range | 0 to 2.4 V (0 to 2*VREF) | |
* | ^        | Output range | 0x000 to 0x7FF | |
* | DAC      | Reference source | VDDA | |
* | ^        | Input range | 0x000 to 0xFFF | |
* | ^        | Output range | 0 to VDDA | |
* | ^        | Output type | Unbuffered output | |
* | I2C      | Role | Master | Configurable to slave mode through HAL function |
* | ^        | Data rate | 100 kbps | Configurable through HAL function |
* | ^        | Drive mode of SCL & SDA pins | Open Drain (drives low) | External pull-up resistors are required |
* | LpTimer  | Uses WCO (32.768 kHz) as clock source & MCWDT as counter. 1 count = 1/32768 second or 32768 counts = 1 second. |||
* | SPI      | Data rate | 100 kpbs | Configurable through HAL function |
* | ^        | Slave select polarity | Active low | |
* | UART     | Flow control | No flow control | Configurable through HAL function |
* | ^        | Data format | 8N1 | Configurable through HAL function |
* | ^        | Baud rate | 115200 | Configurable through HAL function |
*/
/** \} group_bsp_settings */

/**
* \addtogroup group_bsp_pin_state Pin States
* \{
*/

/** Pin state for the LED on. */
#define CYBSP_LED_STATE_ON          (0U)
/** Pin state for the LED off. */
#define CYBSP_LED_STATE_OFF         (1U)

/** Pin state for when a button is pressed. */
#define CYBSP_BTN_PRESSED           (0U)
/** Pin state for when a button is released. */
#define CYBSP_BTN_OFF               (1U)

/** \} group_bsp_pin_state */

#if defined(CY_USING_HAL)

/**
* \addtogroup group_bsp_pins Pin Mappings
* \{
*/

/**
* \addtogroup group_bsp_pins_led LED Pins
* \{
*/

/** LED 8; User LED1 */
#define CYBSP_LED8                  (P1_5)
/** LED 9; User LED2 */
#define CYBSP_LED9                  (P13_7)
/** LED 5: RGB LED - Red; User LED3 */
#define CYBSP_LED_RGB_RED           (P0_3)
/** LED 5: RGB LED - Green; User LED4 */
#define CYBSP_LED_RGB_GREEN         (P1_1)
/** LED 5: RGB LED - Blue; User LED5 */
#define CYBSP_LED_RGB_BLUE          (P11_1)

/** LED 8; User LED1 */
#define CYBSP_USER_LED1             (CYBSP_LED8)
/** LED 9; User LED2 */
#define CYBSP_USER_LED2             (CYBSP_LED9)
/** LED 5: RGB LED - Red; User LED3 */
#define CYBSP_USER_LED3             (CYBSP_LED_RGB_RED)
/** LED 5: RGB LED - Green; User LED4 */
#define CYBSP_USER_LED4             (CYBSP_LED_RGB_GREEN)
/** LED 5: RGB LED - Blue; User LED5 */
#define CYBSP_USER_LED5             (CYBSP_LED_RGB_BLUE)
/** LED 8; User LED1 */
#define CYBSP_USER_LED              (CYBSP_USER_LED1)

/** \} group_bsp_pins_led */

/**
* \addtogroup group_bsp_pins_btn Button Pins
* \{
*/

/** Switch 2; User Button 1 */
#define CYBSP_SW2                   (P0_4)

/** Switch 2; User Button 1 */
#define CYBSP_USER_BTN1             (CYBSP_SW2)
/** Switch 2; User Button 1 */
#define CYBSP_USER_BTN              (CYBSP_USER_BTN1)

/** \} group_bsp_pins_btn */


/**
* \addtogroup group_bsp_pins_comm Communication Pins
* \{
*/

/** Pin: UART RX */
#define CYBSP_DEBUG_UART_RX         (P5_0)
/** Pin: UART TX */
#define CYBSP_DEBUG_UART_TX         (P5_1)

/** Pin: I2C SCL */
#define CYBSP_I2C_SCL               (P6_0)
/** Pin: I2C SDA */
#define CYBSP_I2C_SDA               (P6_1)

/** Pin: SWO */
#define CYBSP_SWO                   (P6_4)
/** Pin: SWDIO */
#define CYBSP_SWDIO                 (P6_6)
/** Pin: SWDCK */
#define CYBSP_SWDCK                 (P6_7)

/** Pin: QUAD SPI SS */
#define CYBSP_QSPI_SS               (P11_2)
/** Pin: QUAD SPI D3 */
#define CYBSP_QSPI_D3               (P11_3)
/** Pin: QUAD SPI D2 */
#define CYBSP_QSPI_D2               (P11_4)
/** Pin: QUAD SPI D1 */
#define CYBSP_QSPI_D1               (P11_5)
/** Pin: QUAD SPI D0 */
#define CYBSP_QSPI_D0               (P11_6)
/** Pin: QUAD SPI SCK */
#define CYBSP_QSPI_SCK              (P11_7)

/** \} group_bsp_pins_comm */


/**
* \addtogroup group_bsp_pins_arduino Arduino Header Pins
* \{
*/

/** Arduino A0 */
#define CYBSP_A0                    (P10_0)
/** Arduino A1 */
#define CYBSP_A1                    (P10_1)
/** Arduino A2 */
#define CYBSP_A2                    (P10_2)
/** Arduino A3 */
#define CYBSP_A3                    (P10_3)
/** Arduino A4 */
#define CYBSP_A4                    (P10_4)
/** Arduino A5 */
#define CYBSP_A5                    (P10_5)
/** Arduino D0 */
#define CYBSP_D0                    (P5_0)
/** Arduino D1 */
#define CYBSP_D1                    (P5_1)
/** Arduino D2 */
#define CYBSP_D2                    (P5_2)
/** Arduino D3 */
#define CYBSP_D3                    (P5_3)
/** Arduino D4 */
#define CYBSP_D4                    (P5_4)
/** Arduino D5 */
#define CYBSP_D5                    (P5_5)
/** Arduino D6 */
#define CYBSP_D6                    (P5_6)
/** Arduino D7 */
#define CYBSP_D7                    (P0_2)
/** Arduino D8 */
#define CYBSP_D8                    (P13_0)
/** Arduino D9 */
#define CYBSP_D9                    (P13_1)
/** Arduino D10 */
#define CYBSP_D10                   (P12_3)
/** Arduino D11 */
#define CYBSP_D11                   (P12_0)
/** Arduino D12 */
#define CYBSP_D12                   (P12_1)
/** Arduino D13 */
#define CYBSP_D13                   (P12_2)
/** Arduino D14 */
#define CYBSP_D14                   (P6_1)
/** Arduino D15 */
#define CYBSP_D15                   (P6_0)

/** \} group_bsp_pins_arduino */


/**
* \addtogroup group_bsp_pins_j2 J2 Header Pins
* \{
*/

/** Cypress J2 Header pin 1 */
#define CYBSP_J2_1                  (CYBSP_A0)
/** Cypress J2 Header pin 2 */
#define CYBSP_J2_2                  (P9_0)
/** Cypress J2 Header pin 3 */
#define CYBSP_J2_3                  (CYBSP_A1)
/** Cypress J2 Header pin 4 */
#define CYBSP_J2_4                  (P9_1)
/** Cypress J2 Header pin 5 */
#define CYBSP_J2_5                  (CYBSP_A2)
/** Cypress J2 Header pin 6 */
#define CYBSP_J2_6                  (P9_2)
/** Cypress J2 Header pin 7 */
#define CYBSP_J2_7                  (CYBSP_A3)
/** Cypress J2 Header pin 8 */
#define CYBSP_J2_8                  (P9_3)
/** Cypress J2 Header pin 9 */
#define CYBSP_J2_9                  (CYBSP_A4)
/** Cypress J2 Header pin 10 */
#define CYBSP_J2_10                 (P9_4)
/** Cypress J2 Header pin 11 */
#define CYBSP_J2_11                 (CYBSP_A5)
/** Cypress J2 Header pin 12 */
#define CYBSP_J2_12                 (P9_5)
/** Cypress J2 Header pin 13 */
#define CYBSP_J2_13                 (P10_6)
/** Cypress J2 Header pin 14 */
#define CYBSP_J2_14                 (NC)
/** Cypress J2 Header pin 15 */
#define CYBSP_J2_15                 (P6_2)
/** Cypress J2 Header pin 16 */
#define CYBSP_J2_16                 (P9_6)
/** Cypress J2 Header pin 17 */
#define CYBSP_J2_17                 (P6_3)
/** Cypress J2 Header pin 18 */
#define CYBSP_J2_18                 (P9_7)
/** Cypress J2 Header pin 19 */
#define CYBSP_J2_19                 (P13_6)
/** Cypress J2 Header pin 20 */
#define CYBSP_J2_20                 (P13_7)

/** \} group_bsp_pins_j2 */

/** \} group_bsp_pins */

#endif /* defined(CY_USING_HAL) */

#if defined(__cplusplus)
}
#endif
