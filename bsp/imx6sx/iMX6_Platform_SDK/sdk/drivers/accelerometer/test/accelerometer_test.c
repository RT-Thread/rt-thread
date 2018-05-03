/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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

#include <string.h>
#include <math.h>
#include "accelerometer/mma8451.h"
#include "board_i2c.h"
#include "gpio/gpio.h"
#include "timer/timer.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void accelerometer_test(void)
{
    mma8451_device_t dev;
    
    printf("\n== Accelerometer Test ==\n\n");

#if BOARD_SMART_DEVICE || BOARD_SABRE_AI

#if defined(BOARD_SMART_DEVICE)
    // Make sure Audio codec, also on I2C1, is powered up to
    // allow I2C1 bus to work properly.
    //
    //CODEC PWR_EN, key_col12
    gpio_set_gpio(GPIO_PORT4, 10);
    gpio_set_direction(GPIO_PORT4, 10, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT4, 10, GPIO_HIGH_LEVEL);

    //  SENSOR_PWR_EN
    gpio_set_gpio(GPIO_PORT2, 31);
    gpio_set_direction(GPIO_PORT2, 31, GPIO_GDIR_OUTPUT);
    gpio_set_level(GPIO_PORT2, 31, GPIO_LOW_LEVEL);
    hal_delay_us(1000);
    gpio_set_level(GPIO_PORT2, 31, GPIO_HIGH_LEVEL);
#endif    
    
    int err = mma8451_init(&dev, &g_mma8451_i2c_device);
    if (err)
    {
        printf("Failed to initialize the MMA8451 (err=%d)!\n", err);
        return;
    }
    
    printf("Reading acceleration data... Press any key to stop.\n");
    
    while (true)
    {
        // Read acceleration data.
        acceleration_t accel;
        err = mma8451_get_acceleration(&dev, &accel);
        if (err)
        {
            printf("Failed to read acceleration data (err=%d)!\n", err);
            return;
        }
        
        // Having problems with float format specifiers, so we're just converting to
        // decimal before printing.
        char buf[128];
        float integralPart;
        sprintf(buf, "x=%+d.%03d, y=%+d.%03d, z=%+d.%03d",
            (int)accel.x, (int)(fabsf(modff(accel.x, &integralPart)) * 1000.0),
            (int)accel.y, (int)(fabsf(modff(accel.y, &integralPart)) * 1000.0),
            (int)accel.z, (int)(fabsf(modff(accel.z, &integralPart)) * 1000.0));
        printf("%s", buf);
        fflush(stdout);
        
        // Check if we should exit.
        if (getchar() != NONE_CHAR)
        {
            break;
        }
        
        // Delay 50 ms.
        hal_delay_us(50000);
        
        // Back up to start of the line by outputting a bunch of backspace chars.
        int len = strlen(buf);
        memset(buf, 0x08, sizeof(buf));
        buf[len] = 0;
        fputs(buf, stdout);
        fflush(stdout);
    }
    
    printf("\n\n");

#else // BOARD_SMART_DEVICE || BOARD_SABRE_AI
    printf("Sorry, no accelerometer available on this board.\n");
#endif
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
