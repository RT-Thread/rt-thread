/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-04     default      first version
 */

#include <Arduino.h>

#define LED_BUILTIN D2
void setup(void)
{
    /* put your setup code here, to run once: */
    Serial.begin();
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop(void)
{
    /* put your main code here, to run repeatedly: */
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    Serial.println("Hello Arduino!");
    delay(2000);
    
}
