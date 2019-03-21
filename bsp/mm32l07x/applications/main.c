/*
 * Copyright (c) 2017-2019, MindMotion AE Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-13     henryhuang   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "HAL_device.h"
/********************************************************************************************************
* led_init(void)
********************************************************************************************************/
void led_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

int main(void)
{
    int count = 1;
    led_init();
    while (count++)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_15);
        rt_thread_mdelay(500);
        GPIO_ResetBits(GPIOA, GPIO_Pin_15);
        rt_thread_mdelay(500);
    }
    return RT_EOK;
}
