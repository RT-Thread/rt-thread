/**
 * This software is subject to the ANT+ Shared Source License
 * www.thisisant.com/swlicenses
 * Copyright (c) Dynastream Innovations, Inc. 2016
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 * 1) Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer.
 * 
 * 2) Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 * 
 * 3) Neither the name of Dynastream nor the names of its
 *    contributors may be used to endorse or promote products
 *    derived from this software without specific prior
 *    written permission.
 * 
 * The following actions are prohibited:
 * 1) Redistribution of source code containing the ANT+ Network
 *    Key. The ANT+ Network Key is available to ANT+ Adopters.
 *    Please refer to http://thisisant.com to become an ANT+
 *    Adopter and access the key.
 * 
 * 2) Reverse engineering, decompilation, and/or disassembly of
 *    software provided in binary form under this license.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE HEREBY
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; DAMAGE TO ANY DEVICE, LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE. SOME STATES DO NOT ALLOW
 * THE EXCLUSION OF INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO THE
 * ABOVE LIMITATIONS MAY NOT APPLY TO YOU.
 * 
 */
#ifndef D52STARTERKIT_H
#define D52STARTERKIT_H

#include "nrf_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

// LEDs definitions for D52DK1
#define LEDS_NUMBER    4

// IO board active low leds
// D52DK1 does not define LED_START or LED_STOP since the LEDS are not on sequential pins
#define LED_A        24 //LED A on D52 Starter Kit IO Board
#define LED_B        31 //LED B on D52 Starter Kit IO Board
#define LED_C        17 //LED C on D52 Starter Kit IO Board
#define LED_D        20 //LED D on D52 Starter Kit IO Board

#define LEDS_ACTIVE_STATE 0

#define LEDS_LIST { LED_A, LED_B, LED_C, LED_D }

#define BSP_LED_0      LED_A
#define BSP_LED_1      LED_B
#define BSP_LED_2      LED_C
#define BSP_LED_3      LED_D

#define LEDS_INV_MASK  LEDS_MASK

#define BUTTONS_NUMBER 4

// IO board pull-up buttons
#define BUTTON_A     6  //BUTTON A on D52 Starter Kit IO Board
#define BUTTON_B     7  //BUTTON B on D52 Starter Kit IO Board
#define BUTTON_C     16 //BUTTON C on D52 Starter Kit IO Board
#define BUTTON_D     19 //BUTTON D on D52 Starter Kit IO Board
#define BUTTON_PULL  NRF_GPIO_PIN_PULLUP

#define BUTTONS_ACTIVE_STATE 0

#define BSP_BUTTON_0   BUTTON_A
#define BSP_BUTTON_1   BUTTON_B
#define BSP_BUTTON_2   BUTTON_C
#define BSP_BUTTON_3   BUTTON_D

#define BUTTONS_LIST { BUTTON_A, BUTTON_B, BUTTON_C, BUTTON_D }

// Battery board pull-up switches
#define SWITCH_1     12 // Switch 1 on D52 Starter Kit Battery Board
#define SWITCH_2     8  // Switch 2 on D52 Starter Kit Battery Board
#define SWITCH_3     15 // Switch 3 on D52 Starter Kit Battery Board
#define SWITCH_4     11 // Switch 4 on D52 Starter Kit Battery Board
#define SWITCH_5     14 // Switch 5 on D52 Starter Kit Battery Board
#define SWITCH_PULL  NRF_GPIO_PIN_PULLUP

#define SWITCHES_NUMBER 5

#define BSP_SWITCH_0 SWITCH_1
#define BSP_SWITCH_1 SWITCH_2
#define BSP_SWITCH_2 SWITCH_3
#define BSP_SWITCH_3 SWITCH_4
#define BSP_SWITCH_4 SWITCH_5

#define BSP_SWITCH_0_MASK   (1<<BSP_SWITCH_0)
#define BSP_SWITCH_1_MASK   (1<<BSP_SWITCH_1)
#define BSP_SWITCH_2_MASK   (1<<BSP_SWITCH_2)
#define BSP_SWITCH_3_MASK   (1<<BSP_SWITCH_3)
#define BSP_SWITCH_4_MASK   (1<<BSP_SWITCH_4)

#define SWITCHES_MASK (BSP_SWITCH_0_MASK | BSP_SWITCH_1_MASK | BSP_SWITCH_2_MASK | BSP_SWITCH_3_MASK | BSP_SWITCH_4_MASK)

// D52DK1 does not have UART peripheral. Dummy defines for compilation.
#define RX_PIN_NUMBER  UART_PIN_DISCONNECTED
#define TX_PIN_NUMBER  UART_PIN_DISCONNECTED
#define CTS_PIN_NUMBER UART_PIN_DISCONNECTED
#define RTS_PIN_NUMBER UART_PIN_DISCONNECTED

// serialization CONNECTIVITY board
#define SER_CON_RX_PIN              22    // UART RX pin number.
#define SER_CON_TX_PIN              23    // UART TX pin number.
#define SER_CON_CTS_PIN             25    // UART Clear To Send pin number. Not used if HWFC is set to false.
#define SER_CON_RTS_PIN             2     // UART Request To Send pin number. Not used if HWFC is set to false.

// serialization APPLICATION board - temp. setup for running serialized MEMU tests
#define SER_APP_RX_PIN              23    // UART RX pin number.
#define SER_APP_TX_PIN              22    // UART TX pin number.
#define SER_APP_CTS_PIN             2     // UART Clear To Send pin number.
#define SER_APP_RTS_PIN             25    // UART Request To Send pin number.


#define SER_CONN_CHIP_RESET_PIN     11    // Pin used to reset connectivity chip

#ifdef __cplusplus
}
#endif

#endif
