/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-27     Jiao         first version
 */

#include <rtthread.h>
#include "board.h"

int main(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    FL_GPIO_SetOutputPin(GPIOD, FL_GPIO_PIN_4);
    GPIO_InitStruct.pin = FL_GPIO_PIN_4;
    GPIO_InitStruct.mode = FL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    FL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    while (1)
    {
        FL_GPIO_SetOutputPin(GPIOD, FL_GPIO_PIN_4);
        rt_thread_mdelay(500);
        FL_GPIO_ResetOutputPin(GPIOD, FL_GPIO_PIN_4);
        rt_thread_mdelay(500);
    }

}
