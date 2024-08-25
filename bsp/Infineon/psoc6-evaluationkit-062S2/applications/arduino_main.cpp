/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-08-16     LZerro         first version
 */

#include <Arduino.h>

void setup(void)
{
    /* put your setup code here, to run once: */
    Serial.begin();
}

void loop(void)
{
    /* put your main code here, to run repeatedly: */
    Serial.println("Hello Arduino!");
    delay(800);
}
