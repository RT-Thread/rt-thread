/*
 * Copyright (c) 2011-2013, Freescale Semiconductor, Inc.
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
#include <cassert>
#include "gpio/gpio_pin.h"
#include "timer/timer.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

// Make it use C linkage so we can call it from sdk_unit_test.
extern "C" void gpio_led_test(void);

// Definition for the debug LED on various boards.
#if CHIP_MX6DQ || CHIP_MX6SDL
#   if BOARD_EVB
#       define LED_PIN GPIO_MAKE_PIN(3, 25)
#   elif BOARD_SMART_DEVICE
#       define LED_PIN GPIO_MAKE_PIN(1, 2) // green is 1,2; red is 1,1
#   elif BOARD_SABRE_AI
#       define LED_PIN GPIO_MAKE_PIN(5, 15)
#   endif
#elif CHIP_MX6SL
#   if BOARD_EVK
#       define LED_PIN GPIO_MAKE_PIN(3, 20)
#   endif
#endif

///////////////////////////////////////////////////////////////////////////////
// Code
///////////////////////////////////////////////////////////////////////////////

//! This test simply blinks the debug LED at a 1 Hz rate.
void gpio_led_test(void)
{
    GpioOutput led(LED_PIN);

    while (true)
    {
        led = !led;
        
        hal_delay_us(500000);
    }
}

///////////////////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////////////////

