/**
 * Copyright (c) 2012 - 2019, Nordic Semiconductor ASA
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
#ifndef PCA10000_H
#define PCA10000_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

// Definitions for PCA10000 v2.0.0 or higher
#if 1

#define LEDS_NUMBER    3

// there is RGB LED on this board
#define LED_RGB_RED    21
#define LED_RGB_GREEN  22
#define LED_RGB_BLUE   23

#define LED_START  LED_RGB_RED
#define BSP_LED_0  LED_RGB_RED
#define BSP_LED_1  LED_RGB_GREEN
#define BSP_LED_2  LED_RGB_BLUE
#define LED_STOP   LED_RGB_BLUE

#define LEDS_ACTIVE_STATE 0

#define BUTTONS_LIST {}
#define LEDS_LIST { LED_RGB_RED, LED_RGB_GREEN, LED_RGB_BLUE }

#define LEDS_INV_MASK  LEDS_MASK

// there are no buttons on this board
#define BUTTONS_NUMBER 0

// UART pins connected to J-Link
#define RX_PIN_NUMBER  11
#define TX_PIN_NUMBER  9
#define CTS_PIN_NUMBER 10
#define RTS_PIN_NUMBER 8
#define HWFC           true

// Definitions for PCA10000 v1.0
#else

#define RX_PIN_NUMBER  3
#define TX_PIN_NUMBER  1
#define CTS_PIN_NUMBER 2
#define RTS_PIN_NUMBER 0
#define HWFC           true

#endif


#ifdef __cplusplus
}
#endif

#endif
