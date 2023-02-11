/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-08     WangShun     first version
 */

#include <Arduino.h>

void setup(void)
 {
     /* put your setup code here, to run once: */
    pinMode(8, OUTPUT);
    Serial.begin();
    Serial.println("Hello Arduino!");
 }

void loop(void)
{
    /* put your main code here, to run repeatedly: */
    digitalWrite(8, HIGH);
    delay(500);
    digitalWrite(8, LOW);
    delay(500);
}
