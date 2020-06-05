/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.c
 * @author Nations Solution Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
 
#include <rtthread.h>
#include <rtdevice.h>
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include "drv_gpio.h"

/**
 * @brief  Main program.
 */
 
 /* defined the LED2 pin: PA8 */
#define LED2_PIN    GET_PIN(A, 8)

int main(void)
{
    uint32_t Speed = 200;
    /* set PA8 pin mode to output */
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    while (1)
    {
        rt_pin_write(LED2_PIN, PIN_LOW);
        rt_thread_mdelay(Speed);
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_mdelay(Speed);
    }
}

