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

#define LED_NUM                             3
struct fm4_gpio_ctrl
{
    uint32_t led_num;
    volatile uint32_t * PDOR;
    volatile uint32_t * PDIR;
};

struct fm4_led
{
    /* inherit from rt_device */
    struct rt_device parent;

    struct fm4_gpio_ctrl fm4_gpio_ctrl[LED_NUM];
};

static struct fm4_led fm4_led;

static rt_err_t rt_led_init (rt_device_t dev)
{
    uint32_t i;

    /* led0-1-2 : P27-P38-PE0 */
    FM4_GPIO->PFR2 &= ~((1<<7) );  /* set P27 fuction is GPIO. */
    FM4_GPIO->DDR2 |=  (1<<7) ;    /* set P27 output. */
        FM4_GPIO->PFR3 &= ~((1<<8) );  /* set P38 fuction is GPIO. */
    FM4_GPIO->DDR3 |=  (1<<8) ;    /* set P38 output. */
        FM4_GPIO->PFRE &= ~((1<<0) );  /* set PE0 fuction is GPIO. */
    FM4_GPIO->DDRE |=  (1<<0) ;    /* set PE0 output. */

    /* LED0 */
    i = 0;
    fm4_led.fm4_gpio_ctrl[i].led_num = 7;
    fm4_led.fm4_gpio_ctrl[i].PDOR = &FM4_GPIO->PDOR2;
    fm4_led.fm4_gpio_ctrl[i].PDIR = &FM4_GPIO->PDIR2;

    /* LED1 */
    i++;
    fm4_led.fm4_gpio_ctrl[i].led_num = 8;
    fm4_led.fm4_gpio_ctrl[i].PDOR = &FM4_GPIO->PDOR3;
    fm4_led.fm4_gpio_ctrl[i].PDIR = &FM4_GPIO->PDIR3;

    /* LED2 */
    i++;
    fm4_led.fm4_gpio_ctrl[i].led_num = 0;
    fm4_led.fm4_gpio_ctrl[i].PDOR = &FM4_GPIO->PDORE;
    fm4_led.fm4_gpio_ctrl[i].PDIR = &FM4_GPIO->PDIRE;

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

    RT_ASSERT(dev == &fm4_led.parent);
    RT_ASSERT((pos+size) <= LED_NUM );

    for(index=0; index<nr; index++)
    {
        if(*fm4_led.fm4_gpio_ctrl[pos+index].PDIR & 1<<fm4_led.fm4_gpio_ctrl[pos+index].led_num)
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

    RT_ASSERT(dev == &fm4_led.parent);
    RT_ASSERT((pos+size) <= LED_NUM );

    for(index=0; index<nw; index++)
    {
        if(*value++)
        {
            *fm4_led.fm4_gpio_ctrl[pos+index].PDOR &= ~(1<<fm4_led.fm4_gpio_ctrl[pos+index].led_num);
        }
        else
        {
            *fm4_led.fm4_gpio_ctrl[pos+index].PDOR |= (1<<fm4_led.fm4_gpio_ctrl[pos+index].led_num);
        }
    }
    return index;
}

static rt_err_t rt_led_control (rt_device_t dev, int cmd, void *args)
{
    RT_ASSERT(dev == &fm4_led.parent);

    if(cmd == RT_DEVICE_CTRL_RTC_GET_COUNT)
    {
        rt_uint32_t * led_num = args;
        *led_num = LED_NUM;
    }
    return RT_EOK;
}

void rt_led_hw_init(void)
{
    fm4_led.parent.type         = RT_Device_Class_Char;
    fm4_led.parent.rx_indicate  = RT_NULL;
    fm4_led.parent.tx_complete  = RT_NULL;
    fm4_led.parent.init         = rt_led_init;
    fm4_led.parent.open         = rt_led_open;
    fm4_led.parent.close        = rt_led_close;
    fm4_led.parent.read         = rt_led_read;
    fm4_led.parent.write        = rt_led_write;
    fm4_led.parent.control      = rt_led_control;
    fm4_led.parent.user_data    = RT_NULL;

    /* register a character device */
    rt_device_register(&fm4_led.parent, "led", RT_DEVICE_FLAG_RDWR);
    /* init led device */
    rt_led_init(&fm4_led.parent);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void led(rt_uint32_t led, rt_uint32_t value)
{
    rt_uint8_t led_value = value;
    rt_led_write(&fm4_led.parent, led, &led_value, 1);
}
FINSH_FUNCTION_EXPORT(led, e.g:led(0,0)/led(0,1).)
#endif
