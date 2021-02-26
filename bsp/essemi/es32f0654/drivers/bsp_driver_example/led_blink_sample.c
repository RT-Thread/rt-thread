/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-25     misonyo      first edition.
 */
/*
 * 程序清单：这是一个通过PIN脚控制LED亮灭的使用例程
 * 例程导出了 led_sample 命令到控制终端
 * 命令调用格式：led_sample 41
 * 命令解释：命令第二个参数是要使用的PIN脚编号，为空则使用例程默认的引脚编号。
 * 程序功能：程序创建一个led线程，线程每隔1000ms改变PIN脚状态，达到控制led灯
 *            亮灭的效果。
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>

/* PIN脚编号，查看驱动文件drv_gpio.c确定 */
#define LED_PIN_NUM    40   /*PB9*/
static int pin_num;

static void led_entry(void *parameter)
{
    int count = 0;
    /* 设置PIN脚模式为输出 */
    rt_pin_mode(pin_num, PIN_MODE_OUTPUT);

    while (1)
    {
        count++;
        rt_kprintf("thread run count : %d\r\n", count);
        /* 拉低PIN脚 */
        rt_pin_write(pin_num, PIN_LOW);
        rt_kprintf("led on!\r\n");
        /* 延时1000ms */
        rt_thread_mdelay(1000);

        /* 拉高PIN脚 */
        rt_pin_write(pin_num, PIN_HIGH);
        rt_kprintf("led off!\r\n");
        rt_thread_mdelay(1000);
    }
}

static int led_sample(int argc, char *argv[])
{
    rt_thread_t tid;
    rt_err_t ret = RT_EOK;

    /* 判断命令行参数是否给定了PIN脚编号 */
    if (argc == 2)
    {
        pin_num = atoi(argv[1]);
    }
    else
    {
        pin_num = LED_PIN_NUM;
    }

    tid = rt_thread_create("led",
                           led_entry,
                           RT_NULL,
                           512,
                           RT_THREAD_PRIORITY_MAX / 3,
                           20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        ret = RT_ERROR;
    }

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(led_sample, led sample);
