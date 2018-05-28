/*
 * File      : drv_led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-28     wlhe         Initial version
 */
#include <rtthread.h>
#include <rtdef.h>

#include "drv_led.h"
#include "stm32f7xx_hal.h"

#define LED_NUM 3

#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOJ
#define LED2_Pin  GPIO_PIN_5
#define LED2_GPIO_Port GPIOJ
#define LED3_Pin GPIO_PIN_12
#define LED3_GPIO_Port GPIOA

struct led_ctrl {
    GPIO_TypeDef *port;
    uint16_t pin;
};

static struct led_ctrl leds_ctrl[LED_NUM] =
{
    {
        LED1_GPIO_Port,
        LED1_Pin
    },
    {
        LED2_GPIO_Port,
        LED2_Pin
    },
    {
        LED3_GPIO_Port,
        LED3_Pin
    }
};
struct led_device {
    struct rt_device parent;
    int led_num;
    struct led_ctrl *leds;
};
static struct led_device led_dev;

static void led_bsp_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOJ, LED1_Pin | LED2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);

    GPIO_InitStruct.Pin = LED1_Pin | LED2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = LED3_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED3_GPIO_Port, &GPIO_InitStruct);
}

static inline uint16_t led_read(struct led_ctrl *led)
{
    return HAL_GPIO_ReadPin(led->port, led->pin);
}
static inline void led_write(struct led_ctrl *led, int value)
{
    HAL_GPIO_WritePin(led->port, led->pin, value ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static rt_err_t rt_led_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t rt_led_open(rt_device_t dev, rt_uint16_t oflag)
{
    led_bsp_init();
    return RT_EOK;
}

static rt_err_t rt_led_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_led_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    RT_ASSERT(dev == &led_dev.parent);

    struct led_device *d = (struct led_device *)dev->user_data;
    RT_ASSERT(pos < d->led_num);

    rt_uint8_t *buf = buffer;
    rt_size_t len = (pos + size <= d->led_num) ? size : (d->led_num - pos);

    for (uint8_t i = 0; i < len; i++)
    {
        buf[i] = led_read(&(d->leds[pos + i]));
    }
    return len;
}

static rt_size_t rt_led_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{

    RT_ASSERT(dev == &led_dev.parent);

    struct led_device *d = (struct led_device *)dev->user_data;
    RT_ASSERT(pos <= d->led_num);

    const rt_uint8_t *buf = buffer;
    rt_size_t len = (pos + size <= d->led_num) ? size : (d->led_num - pos);

    for (uint8_t i = 0; i < len; i++)
    {
        led_write(&(d->leds[pos + i]), buf[i]);
    }
    return len;
}

static rt_err_t rt_led_control(rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev == &led_dev.parent);

    struct led_device *d = (struct led_device *)dev->user_data;

    if (cmd == DEV_CTRL_GET_LED_NUM) {
        rt_uint32_t *num = (rt_uint32_t *)args;
        *num = d->led_num;
    }

    return RT_EOK;
}


int rt_led_hw_init(void)
{
    int ret = 0;
#ifdef BSP_USING_LED
    led_dev.parent.type         = RT_Device_Class_Char;
    led_dev.parent.rx_indicate  = RT_NULL;
    led_dev.parent.tx_complete  = RT_NULL;
    led_dev.parent.init         = rt_led_init;
    led_dev.parent.open         = rt_led_open;
    led_dev.parent.close        = rt_led_close;
    led_dev.parent.read         = rt_led_read;
    led_dev.parent.write        = rt_led_write;
    led_dev.parent.control      = rt_led_control;
    led_dev.parent.user_data    = &led_dev;

    led_dev.led_num = LED_NUM;
    led_dev.leds = leds_ctrl;

    ret =  rt_device_register(&led_dev.parent, "led", RT_DEVICE_FLAG_RDWR);
#endif // BSP_USING_LED
    return ret;
}

#ifdef BSP_USING_LED
INIT_DEVICE_EXPORT(rt_led_hw_init);
#endif // BSP_USING_LED

// led test entry
void led_test_entry(void *arg)
{
    rt_uint8_t buf[6] = {1, 0, 1, 0, 1, 0};
    rt_device_t led = rt_device_find("led");

    if (led == NULL) {
        rt_kprintf("can't find led device\n");
        return;
    }
    rt_device_open(led, RT_DEVICE_OFLAG_RDWR);

    rt_uint32_t num = 0;
    rt_device_control(led, DEV_CTRL_GET_LED_NUM, &num);
    rt_kprintf("led num [%d]\n", num);

    while (1)
    {
        rt_device_write(led, 0, &buf[0], 3);
        rt_thread_delay(50);
        rt_device_write(led, 0, &buf[3], 3);
        rt_thread_delay(50);
    }
}