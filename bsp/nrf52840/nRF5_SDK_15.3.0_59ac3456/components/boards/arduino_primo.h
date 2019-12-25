/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef ARDUINO_PRIMO_H
#define ARDUINO_PRIMO_H

#ifdef __cplusplus
extern "C" {
#endif

// LEDs definitions
#define LEDS_NUMBER    1

#define LED_1          20

#define LEDS_ACTIVE_STATE 0

#define LEDS_LIST { LED_1}

#define BSP_LED_0      LED_1

#define LEDS_INV_MASK  0

#define BUTTONS_NUMBER 1

#define BUTTON_START   7
#define BUTTON_1       7
#define BUTTON_STOP    7
#define BUTTON_PULL    NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BUTTONS_LIST { BUTTON_1 }

#define BSP_BUTTON_0   BUTTON_1

#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  12
#define CTS_PIN_NUMBER UART_PIN_DISCONNECTED
#define RTS_PIN_NUMBER UART_PIN_DISCONNECTED
#define HWFC           false

#define BUZZER_PIN_NUMBER  8

// Arduino board mappings
#define ARDUINO_SCL_PIN             27    // SCL signal pin
#define ARDUINO_SDA_PIN             26    // SDA signal pin
#define ARDUINO_AREF_PIN            2     // Aref pin
#define ARDUINO_13_PIN              25    // Digital pin 13
#define ARDUINO_12_PIN              24    // Digital pin 12
#define ARDUINO_11_PIN              23    // Digital pin 11
#define ARDUINO_10_PIN              22    // Digital pin 10
#define ARDUINO_9_PIN               20    // Digital pin 9
#define ARDUINO_8_PIN               19    // Digital pin 8

#define ARDUINO_7_PIN               18    // Digital pin 7
#define ARDUINO_6_PIN               17    // Digital pin 6
#define ARDUINO_5_PIN               16    // Digital pin 5
#define ARDUINO_4_PIN               15    // Digital pin 4
#define ARDUINO_3_PIN               14    // Digital pin 3
#define ARDUINO_2_PIN               13    // Digital pin 2
#define ARDUINO_1_PIN               12    // Digital pin 1
#define ARDUINO_0_PIN               11    // Digital pin 0

#define ARDUINO_A0_PIN              3     // Analog channel 0
#define ARDUINO_A1_PIN              4     // Analog channel 1
#define ARDUINO_A2_PIN              28    // Analog channel 2
#define ARDUINO_A3_PIN              29    // Analog channel 3
#define ARDUINO_A4_PIN              30    // Analog channel 4
#define ARDUINO_A5_PIN              31    // Analog channel 5


#ifdef __cplusplus
}
#endif

#endif // ARDUINO_PRIMO_H
