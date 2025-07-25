/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单：这是一个 hwtimer 设备使用例程
 * 例程导出了 hwtimer_sample 命令到控制终端
 * 命令调用格式：hwtimer_sample  hwtimer_sample [option1] [option2] [option3]
 *                                            option1: [tmra_1/2/3..] 定时器单元
 *                                            option2: [oneshot/period] 定时模式
 *                                            option3: 超时时间，单位毫秒
 * eg:hwtimer_sample tmra_1 period 1000
 * 程序功能：每隔一秒打印一次定时器运行时间值，在定时器超时回调函数中打印总tick值
 * 可以使用逻辑分析进一步查看测试管脚PA0定时时间是否准确
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>
#include <board.h>

#ifdef BSP_USING_HWTIMER

/* IO用于定时时间测试 */
#define TIMEOUT_TEST_PIN GET_PIN(A, 0)

static rt_uint32_t tick;
static rt_bool_t cb_run = RT_FALSE;

static void _hwtimer_cmd_print_usage(void)
{
    rt_kprintf("hwtimer_sample [option1] [option2] [option3]\n");
    rt_kprintf("  option1: [tmra_1/2/3..] tmra uint\n");
    rt_kprintf("  option2: [oneshot/period] timing mode set\n");
    rt_kprintf("  option3: timeout unit:ms\n");
    rt_kprintf("    e.g. MSH >hwtimer_sample tmra_1 period 1000\n");
}

/* 定时器超时回调函数 */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    static rt_uint8_t pin_cnt = 0;
    rt_pin_write(TIMEOUT_TEST_PIN, ++pin_cnt % 2);   /* 电平取反 */
    /* 打印出的tick值由于printf原因可能有误差，可以查看测试IO来精确确认时间 */
    rt_kprintf("callback successful! ticks = %d \n", rt_tick_get() - tick);
    tick = rt_tick_get();
    cb_run = RT_TRUE;

    return 0;
}

static int hwtimer_sample(int argc, char *argv[])
{
    rt_uint8_t i;
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;                              /* 定时器超时值 */
    rt_hwtimer_mode_t mode = HWTIMER_MODE_ONESHOT;          /* 定时器模式 */
    rt_device_t hw_dev = RT_NULL;                           /* 定时器设备句柄 */
    rt_hwtimer_t *hwtimer;
    float t;
    rt_uint8_t loop_cnt;                                    /* 循环打印次数 */
    rt_hwtimerval_t overflow_tv;                            /* 定时器超时值 */
    rt_uint32_t timer_out_s;

    if ((argc != 4) || (rt_strcmp("oneshot", argv[2]) && rt_strcmp("period", argv[2])))
    {
        _hwtimer_cmd_print_usage();
        return -RT_ERROR;
    }

    /* 查找定时器设备 */
    hw_dev = rt_device_find(argv[1]);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", argv[1]);
        return -RT_ERROR;
    }
    else
    {
        hwtimer = (rt_hwtimer_t *)hw_dev;
    }

    /* 以读写方式打开设备 */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", argv[1]);
        return ret;
    }

    /* 设置模式 */
    if (0 == rt_strcmp(argv[2], "oneshot"))
    {
        mode = HWTIMER_MODE_ONESHOT;
        loop_cnt = 1;
    }
    else if (0 == rt_strcmp(argv[2], "period"))
    {
        mode = HWTIMER_MODE_PERIOD;
        loop_cnt = 5;
    }
    rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);

    /* 设置超时回调函数 */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* 设置定时器超时并启动定时器 */
    timeout_s.sec = atoi(argv[3]) / 1000U;            /* 秒 */
    timeout_s.usec = (atoi(argv[3]) % 1000U) * 1000U; /* 微秒 */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return -RT_ERROR;
    }
    tick = rt_tick_get();
    rt_kprintf("set timeout (%d) ms successful\n", atoi(argv[3]));

    /* 设置测试管脚为输出模式 */
    rt_pin_mode(TIMEOUT_TEST_PIN, PIN_MODE_OUTPUT);

    /* oneshot模式cb函数执行一次，period模式cb函数执行5次,且每秒打印一次运行时间 */
    timer_out_s = (atoi(argv[3]) / 1000U) > 1 ? (atoi(argv[3]) / 1000U) : 1;
    for (i = 0; i < (timer_out_s * loop_cnt); i++)
    {
        /* 延时1000ms */
        rt_thread_mdelay(1000);

        /* 读取定时器当前值 */
        if (mode == HWTIMER_MODE_PERIOD)
        {
            rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
        }
        else if (mode == HWTIMER_MODE_ONESHOT)
        {
            rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));

            t = hwtimer->overflow * hwtimer->period_sec;
            overflow_tv.sec = (rt_int32_t)t;
            overflow_tv.usec = (rt_int32_t)((t - overflow_tv.sec) * 1000000);

            timeout_s.sec = overflow_tv.sec + (timeout_s.usec + overflow_tv.usec) / 1000000;
            timeout_s.usec = (timeout_s.usec + overflow_tv.usec) % 1000000;
        }
        rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);
    }

    /* 确保oneshot模式cb函数执行一次后才关闭定时器 */
    while (cb_run == RT_FALSE);
    cb_run = RT_FALSE;

    /* close */
    rt_device_close(hw_dev);

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(hwtimer_sample, hwtimer sample: devname [oneshot | period] timeout);
#endif
