/*
 * Copyright (c) 2006-2018, Synwit Technology Co.,Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Zohar_Lee    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "HAL_device.h"
/* defined the LED pin: PA12 */
#define LED_PIN    100



/********************************************************************************************************
** LED_Init(void)                        
********************************************************************************************************/
void LED_Init(void)
{
    
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB, ENABLE);  //Enable GPIOA,GPIOB clock
    
    GPIO_InitStructure.GPIO_Pin  =  GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    

}


int main(void)
{
    int count = 1;
    /* set LED4 pin mode to output */
    LED_Init();

    while (count++)
    {

        GPIO_SetBits(GPIOB, GPIO_Pin_5);
        rt_thread_mdelay(500);
        GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        rt_thread_mdelay(500);
    }

    return RT_EOK;
}
