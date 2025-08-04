/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-25     ShichengChu  first version
 */

#include <Arduino.h>

void setup(void)
{
    /* put your setup code here, to run once: */
    Serial2.begin();
    Serial2.println("Hello RTduino!");
}

void loop(void)
{
    /* put your main code here, to run repeatedly: */
    delay(1000);
}
