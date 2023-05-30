/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-01-29     XiaojieFan   add port file
 */

#include "board.h"
#include "drv_gpio.h"

#define ESP8266_CH_PD_Pin GET_PIN(G,1)
#define ESP8266_RST       GET_PIN(G,0)

int esp_02_device_init()
{
    rt_pin_mode(ESP8266_CH_PD_Pin,PIN_MODE_OUTPUT) ;
    rt_pin_mode(ESP8266_RST,PIN_MODE_OUTPUT) ;
    rt_pin_write(ESP8266_CH_PD_Pin,PIN_HIGH) ;
    rt_pin_write(ESP8266_RST,PIN_HIGH) ;

    return RT_EOK ;
}
INIT_DEVICE_EXPORT(esp_02_device_init);
