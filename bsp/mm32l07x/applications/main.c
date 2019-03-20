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
** led_init(void)
********************************************************************************************************/
void led_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE); //Enable GPIOA,GPIOB clock
    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

int main(void)
{
    int count = 1;
    led_init();
    while (count++)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_15);
        GPIO_SetBits(GPIOB, GPIO_Pin_3);
        GPIO_SetBits(GPIOB, GPIO_Pin_4);
        GPIO_SetBits(GPIOB, GPIO_Pin_5);
        rt_thread_mdelay(500);
        GPIO_ResetBits(GPIOA, GPIO_Pin_15);
        GPIO_ResetBits(GPIOB, GPIO_Pin_3);
        GPIO_ResetBits(GPIOB, GPIO_Pin_4);
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        rt_thread_mdelay(500);
    }
    return RT_EOK;
}
