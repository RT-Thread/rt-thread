/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-01     liYony       first version
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
int val = 0;
static int rtduino(int argc, char **argv)
{   
    if (!strcmp(argv[1], "pwm"))
    {
        for(val=0;val<255;val++)
        {
            analogWrite(atoi(argv[2]), val); // 设置PWM输出，val越大，PWM占空比越大，led越亮
            delay(10);//延迟
        }
        for(val=255;val>=0;val--)
        {
            analogWrite(atoi(argv[2]), val); // 设置PWM输出，val越大，PWM占空比越大，led越亮
            delay(10);//延迟
        }

    }
    if (!strcmp(argv[1], "adc"))
    {
        rt_kprintf("%d %d\n",atoi(argv[2]),analogRead(atoi(argv[2])));
    }
    return 0;
}
MSH_CMD_EXPORT(rtduino, rtduino [option]);