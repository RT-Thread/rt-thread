/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include "board.h"

#define RT_DEVICE_CTRL_RTC_GET_COUNT        0x81        /**< get count                                   */

#define LED_NUM                             4
struct fm3_gpio_ctrl
{
    uint32_t led_num;
    volatile uint32_t * PDOR;
    volatile uint32_t * PDIR;
};

struct fm3_led
{
    /* inherit from rt_device */
    struct rt_device parent;

    struct fm3_gpio_ctrl fm3_gpio_ctrl[LED_NUM];
};

static struct fm3_led fm3_led;

static rt_err_t rt_led_init (rt_device_t dev)
{
    uint32_t i;

    /* led0 : P54 */
    FM3_GPIO->PFR5 &= ~((1<<7) | (1<<6) | (1<<5) |(1<<4));  /* set P54 fuction is GPIO. */
    FM3_GPIO->DDR5 |=  (1<<7) | (1<<6) | (1<<5) |(1<<4);    /* set P54 output. */

    /* LED0 */
    i = 0;
    fm3_led.fm3_gpio_ctrl[i].led_num = 4;
    fm3_led.fm3_gpio_ctrl[i].PDOR = &FM3_GPIO->PDOR5;
    fm3_led.fm3_gpio_ctrl[i].PDIR = &FM3_GPIO->PDIR5;

    /* LED1 */
    i++;
    fm3_led.fm3_gpio_ctrl[i].led_num = 5;
    fm3_led.fm3_gpio_ctrl[i].PDOR = &FM3_GPIO->PDOR5;
    fm3_led.fm3_gpio_ctrl[i].PDIR = &FM3_GPIO->PDIR5;

    /* LED2 */
    i++;
    fm3_led.fm3_gpio_ctrl[i].led_num = 6;
    fm3_led.fm3_gpio_ctrl[i].PDOR = &FM3_GPIO->PDOR5;
    fm3_led.fm3_gpio_ctrl[i].PDIR = &FM3_GPIO->PDIR5;

    /* LED3 */
    i++;
    fm3_led.fm3_gpio_ctrl[i].led_num = 7;
    fm3_led.fm3_gpio_ctrl[i].PDOR = &FM3_GPIO->PDOR5;
    fm3_led.fm3_gpio_ctrl[i].PDIR = &FM3_GPIO->PDIR5;

    return RT_EOK;
}

static rt_err_t rt_led_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_led_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_led_read (rt_device_t dev, rt_off_t pos, void* buffer,
                              rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nr = size;
    rt_uint8_t * value = buffer;

    RT_ASSERT(dev == &fm3_led.parent);
    RT_ASSERT((pos+size) <= LED_NUM );

    for(index=0; index<nr; index++)
    {
        if(*fm3_led.fm3_gpio_ctrl[pos+index].PDIR & 1<<fm3_led.fm3_gpio_ctrl[pos+index].led_num)
        {
            *value = 0;
        }
        else
        {
            *value = 1;
        }
        value++;
    }
    return index;
}

static rt_size_t rt_led_write (rt_device_t dev, rt_off_t pos,
                               const void* buffer, rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nw = size;
    const rt_uint8_t * value = buffer;

    RT_ASSERT(dev == &fm3_led.parent);
    RT_ASSERT((pos+size) <= LED_NUM );

    for(index=0; index<nw; index++)
    {
        if(*value++)
        {
            *fm3_led.fm3_gpio_ctrl[pos+index].PDOR &= ~(1<<fm3_led.fm3_gpio_ctrl[pos+index].led_num);
        }
        else
        {
            *fm3_led.fm3_gpio_ctrl[pos+index].PDOR |= (1<<fm3_led.fm3_gpio_ctrl[pos+index].led_num);
        }
    }
    return index;
}

static rt_err_t rt_led_control (rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev == &fm3_led.parent);

    if(cmd == RT_DEVICE_CTRL_RTC_GET_COUNT)
    {
        rt_uint32_t * led_num = args;
        *led_num = LED_NUM;
    }
    return RT_EOK;
}

void rt_led_hw_init(void)
{
    fm3_led.parent.type         = RT_Device_Class_Char;
    fm3_led.parent.rx_indicate  = RT_NULL;
    fm3_led.parent.tx_complete  = RT_NULL;
    fm3_led.parent.init         = rt_led_init;
    fm3_led.parent.open         = rt_led_open;
    fm3_led.parent.close        = rt_led_close;
    fm3_led.parent.read         = rt_led_read;
    fm3_led.parent.write        = rt_led_write;
    fm3_led.parent.control      = rt_led_control;
    fm3_led.parent.user_data    = RT_NULL;

    /* register a character device */
    rt_device_register(&fm3_led.parent, "led", RT_DEVICE_FLAG_RDWR);
    /* init led device */
    rt_led_init(&fm3_led.parent);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void led(rt_uint32_t led, rt_uint32_t value)
{
    rt_uint8_t led_value = value;
    rt_led_write(&fm3_led.parent, led, &led_value, 1);
}
FINSH_FUNCTION_EXPORT(led, e.g:led(0,100).)
#endif
