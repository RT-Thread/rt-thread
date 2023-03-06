/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 */

#include <Arduino.h>

void setup(void)
{
    /* put your setup code here, to run once: */
    Serial.begin();
    Serial.println("Hello RTduino!");
}

void loop(void)
{
    /* put your main code here, to run repeatedly: */
    delay(1000);
}
