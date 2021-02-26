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

#if defined(BSP_USING_TIM14) && defined(BSP_USING_ADC2)

#include <rtthread.h>
#include <rtdevice.h>

#define HWTIMER_DEV_NAME   "timer14"
#define HWADC_DEV_NAME     "adc2"
#define REFER_VOLTAGE       330         /* voltage reference */
#define CONVERT_BITS        (1 << 12)   /* Conversion digit */
#define ADC_DEV_CHANNEL     6

static rt_adc_device_t adc_dev = RT_NULL;

static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_uint32_t value = 0 , vol = 0;
    
    /* read adc value */
    value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
    rt_kprintf("the value is :%d \n", value);
    
    vol = value * REFER_VOLTAGE / CONVERT_BITS;
    rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);

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
    
    /* close adc channel */
    ret = rt_adc_disable(adc_dev, ADC_DEV_CHANNEL);
    
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

    /* find adc dev */
    adc_dev = (rt_adc_device_t)rt_device_find(HWADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("hwtimer sample run failed! can't find %s device!\n", HWADC_DEV_NAME);
        return RT_ERROR;
    }
    
    /* Open the device in read/write mode */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", HWTIMER_DEV_NAME);
        return ret;
    }

    /* Set the timeout callback function */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* Set the mode to periodic timer */
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
    
    /* enable adc channel */
    ret = rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);
    
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

#endif
