/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-07-27     thread-liu        first version
 */

#include <board.h>
#include <rtthread.h>
#include <rtdevice.h>

#define HWTIMER_DEV_NAME   "timer14"

static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is hwtimer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int hwtimer_stop(void)
{
    rt_err_t ret = RT_EOK;
    rt_device_t hw_dev = RT_NULL;

    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return RT_ERROR;
    }

    ret = rt_device_close(hw_dev);
    if (ret != RT_EOK)
    {
        rt_kprintf("close %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }
    
    return ret;
}

static int hwtimer_start(void)
{
    rt_err_t ret = RT_EOK;
    rt_hwtimerval_t timeout_s;     
    rt_device_t hw_dev = RT_NULL;
    rt_hwtimer_mode_t mode;

    hw_dev = rt_device_find(HWTIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWTIMER_DEV_NAME);
        return RT_ERROR;
    }

    /* 以读写方式打开设备 */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    /* 设置超时回调函数 */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* 设置模式为周期性定时器 */
    mode = HWTIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, HWTIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    timeout_s.sec = 5;
    timeout_s.usec = 0;

    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return RT_ERROR;
    }

    rt_thread_mdelay(3500);

    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}

static int tim_sample(int argc, char *argv[])
{
    if (argc > 1)
    {
        if (!rt_strcmp(argv[1], "start"))
        { 
           rt_kprintf("tim14 will start\n"); 
           hwtimer_start();
           return RT_EOK;
        }
        else if (!rt_strcmp(argv[1], "stop"))
        {
            hwtimer_stop();
            rt_kprintf("stop tim14 success!\n");
            return RT_EOK;
        }
        else
        {
            goto _exit;
        }
    }
_exit:
    {
        rt_kprintf("Usage:\n");
        rt_kprintf("tim_sample start         - start TIM14 \n");
        rt_kprintf("tim_sample stop          - stop TIM14 \n");
    }
    
    return RT_ERROR;
}

MSH_CMD_EXPORT(tim_sample, tim sample);
