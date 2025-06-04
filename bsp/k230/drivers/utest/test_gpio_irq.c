/*
 * Copyright (C) 2022, Canaan Bright Sight Co., Ltd
 *
 * All enquiries to https://www.canaan-creative.com/
 */

/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

 /*
  * 本测试用例演示基于 01Studio Canmv-K230 开发板测试 gpio 的中断检测功能。其中
  * 采用开发板上的按键 S3 以及其连接的 KEY_GPIO21 作为中断输入
  * 在中断处理函数中控制 LED 的状态。LED2 采用开发板上的 LED2（连接 LED_GPIO52）。
  * gpio_falling_edge_trigger_irq 将按键 S3 的中断触发方式设置为下降沿触发，测试
  * 时应该会观察到在每次按下 S3 时收到中断。
  * gpio_rising_edge_trigger_irq 将按键 S3 的中断触发方式设置为上升沿触发，测试
  * 时应该会观察到在每次松开 S3 时收到中断。
  * gpio_both_edge_trigger_irq 将按键 S3 的中断触发方式设置为双边沿触发。测试时
  * 应该会观察到在每次按下或松开 S3 时都会收到中断。
  */
#include <unistd.h>
#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_gpio.h"
#include "utest.h"

#define LED_PIN_NUM            52
#define KEY_PIN_NUM            21

/* It is best to use an even number, especially for testing both edges triggering. */
#define MAX_LOOP_COUNT  6
static volatile int cnt;

#define LED_ON  1
#define LED_OFF 0
static volatile int led_status;

static void led_on(void)
{
    LOG_W("led ON\n");
    kd_pin_write(LED_PIN_NUM, GPIO_PV_HIGH);
    led_status = LED_ON;
}

static void led_off(void)
{
    LOG_W("led OFF\n");
    kd_pin_write(LED_PIN_NUM, GPIO_PV_LOW);
    led_status = LED_OFF;
}

void key_irq(void *args)
{
    LOG_I("---> IRQ: %d\n", ++cnt);
    if(LED_OFF == led_status)
        led_on();
    else
        led_off();
}

static void gpio_falling_edge_trigger_irq(void)
{
    cnt = 0;

    /* Use default pinmux function */
    kd_pin_mode(LED_PIN_NUM, GPIO_DM_OUTPUT);
    led_off();

    /* Use default pinmux function */
    kd_pin_mode(KEY_PIN_NUM, GPIO_DM_INPUT);
    kd_pin_attach_irq(KEY_PIN_NUM, GPIO_PE_FALLING, key_irq, RT_NULL);
    kd_pin_irq_enable(KEY_PIN_NUM, KD_GPIO_IRQ_ENABLE);

    while (cnt < MAX_LOOP_COUNT);
    kd_pin_detach_irq(KEY_PIN_NUM);
}

static void gpio_rising_edge_trigger_irq(void)
{
    cnt = 0;

    /* Use default pinmux function */
    kd_pin_mode(LED_PIN_NUM, GPIO_DM_OUTPUT);
    led_off();

    /* Use default pinmux function */
    kd_pin_mode(KEY_PIN_NUM, GPIO_DM_INPUT);
    kd_pin_attach_irq(KEY_PIN_NUM, GPIO_PE_RISING, key_irq, RT_NULL);
    kd_pin_irq_enable(KEY_PIN_NUM, KD_GPIO_IRQ_ENABLE);

    while (cnt < MAX_LOOP_COUNT);
    kd_pin_detach_irq(KEY_PIN_NUM);
}

static void gpio_both_edge_trigger_irq(void)
{
    cnt = 0;

    /* Use default pinmux function */
    kd_pin_mode(LED_PIN_NUM, GPIO_DM_OUTPUT);
    led_off();

    /* Use default pinmux function */
    kd_pin_mode(KEY_PIN_NUM, GPIO_DM_INPUT);
    kd_pin_attach_irq(KEY_PIN_NUM, GPIO_PE_BOTH, key_irq, RT_NULL);
    kd_pin_irq_enable(KEY_PIN_NUM, KD_GPIO_IRQ_ENABLE);

    while (cnt < MAX_LOOP_COUNT);
    kd_pin_detach_irq(KEY_PIN_NUM);
}

static void testcase(void)
{
    UTEST_UNIT_RUN(gpio_falling_edge_trigger_irq);
    UTEST_UNIT_RUN(gpio_rising_edge_trigger_irq);
    UTEST_UNIT_RUN(gpio_both_edge_trigger_irq);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(testcase, "gpio_irq", utest_tc_init, utest_tc_cleanup, 100);