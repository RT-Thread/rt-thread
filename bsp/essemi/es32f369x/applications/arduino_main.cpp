/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 * 2022-07-07     shiwa        Adapt ES32F369x
 */
#include <Arduino.h>

void setup(void)
{
    /* put your setup code here, to run once: */
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop(void)
{
    /* put your main code here, to run repeatedly: */
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(250);
}
