/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-22     ChuShicheng  first version
 */

#include <Arduino.h>

int led = 37; /* LED pin */
int brightness = 0;
int fadeAmount = 5;

void setup()
{
    /* Do not invoke pinMode for the PWM IO! */
}

void loop()
{
    analogWrite(led, brightness);
    brightness = brightness + fadeAmount;
    if (brightness <= 0 || brightness >= 255)
    {
        fadeAmount = -fadeAmount;
    }

    delay(100);
}
