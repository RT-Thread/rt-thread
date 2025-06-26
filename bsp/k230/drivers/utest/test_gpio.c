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
  * 本测试用例演示基于 01Studio Canmv-K230 开发板测试 gpio 的基本输入和输出功能。其中
  * gpio_led_flashing 演示 LED 的跑马灯功能。LED 采用开发板上的 LED2（连接 LED_GPIO52）。
  * gpio_io 演示用杜邦线将 40Pin GPIO 中的 GPIO33 和 GPIO32 连接起来，GPIO33 配
  * 置为输出，GPIO32 配置为输入。分别用 GPIO33 产生输出给 GPIO32 读取并检查是否
  * 和预期的输出一致。
  */
#include <unistd.h>
#include <stdio.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <ioremap.h>
#include "board.h"
#include "drv_pinctrl.h"
#include "drv_gpio.h"
#include "utest.h"

#define LED_PIN_NUM 52

#define OUT_PIN_NUM 33
#define IN_PIN_NUM  32

static void gpio_led_flashing(void)
{
    int cnt = 5;

    /* Use default pinmux function */
    kd_pin_mode(LED_PIN_NUM, GPIO_DM_OUTPUT);

    while(cnt--)
    {
        LOG_I("led ON");
        kd_pin_write(LED_PIN_NUM, GPIO_PV_HIGH);
        rt_thread_mdelay(1000);

        LOG_I("led OFF");
        kd_pin_write(LED_PIN_NUM, GPIO_PV_LOW);
        rt_thread_mdelay(1000);
    }
}

static void gpio_io(void)
{
    int cnt = 5;
    int level = 0xff;

    rt_uint32_t val;

    /* Set pinmux function */
    k230_pinctrl_set_function(IN_PIN_NUM, IOMUX_FUNC1);
    k230_pinctrl_set_ie(IN_PIN_NUM, 1);
    k230_pinctrl_set_oe(IN_PIN_NUM, 0);

    k230_pinctrl_set_function(OUT_PIN_NUM, IOMUX_FUNC1);
    k230_pinctrl_set_ie(OUT_PIN_NUM, 0);
    k230_pinctrl_set_oe(OUT_PIN_NUM, 1);

    /* Set GPIO mode */
    kd_pin_mode(OUT_PIN_NUM, GPIO_DM_OUTPUT);
    kd_pin_mode(IN_PIN_NUM, GPIO_DM_INPUT);

    while(cnt--)
    {
        kd_pin_write(OUT_PIN_NUM, GPIO_PV_LOW);
        level = kd_pin_read(IN_PIN_NUM);
        LOG_I("--> %d", level);
        uassert_int_equal(level, GPIO_PV_LOW);

        kd_pin_write(OUT_PIN_NUM, GPIO_PV_HIGH);
        level = kd_pin_read(IN_PIN_NUM);
        LOG_I("--> %d", level);
        uassert_int_equal(level, GPIO_PV_HIGH);

        rt_thread_mdelay(500);
    }
}

static void testcase(void)
{
    UTEST_UNIT_RUN(gpio_led_flashing);
    UTEST_UNIT_RUN(gpio_io);
}

static rt_err_t utest_tc_init(void)
{
    return RT_EOK;
}
static rt_err_t utest_tc_cleanup(void)
{
    return RT_EOK;
}

UTEST_TC_EXPORT(testcase, "gpio", utest_tc_init, utest_tc_cleanup, 100);