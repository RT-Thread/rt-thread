/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2023-12-30     ChuShicheng    first version
 */

#include <Arduino.h>

void setup(void)
{
    /* put your setup code here, to run once: */
    Serial2.begin();
}

void loop(void)
{
    /* put your main code here, to run repeatedly: */
    Serial2.println("Hello Arduino!");
    delay(800);
}
