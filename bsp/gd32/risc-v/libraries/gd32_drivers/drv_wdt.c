/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-02-04     Yixizhang         first version
 */

#include <board.h>
#include <rtthread.h>




#ifdef RT_USING_WDT

#if defined(BSP_USING_FWDT)     
    #define   HW_WDGT_DEV_NAME  "fwdgt"
#elif defined(BSP_USING_WWDT)
    #define   HW_WDGT_DEV_NAME  "wwdgt"
#endif

#define DBG_TAG "wdt"
#define DBG_LVL DBG_LOG

#include <rtdbg.h>
struct gd32_wdt_obj
{
    rt_watchdog_t watchdog;
    rt_uint16_t is_start;
};
static struct gd32_wdt_obj gd32_wdt;
static struct rt_watchdog_ops ops;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    LOG_D("wdt init success.");
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    
    rt_uint32_t time_sec;
    rt_uint32_t time_msec;
    rt_uint32_t wdgt_count;
    rt_uint32_t window_value;
    switch (cmd)
    {
        /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
#if defined(BSP_USING_FWDT)     
        fwdgt_counter_reload();
#elif defined(BSP_USING_WWDT)
        wwdgt_counter_update(0x70);
        LOG_D("wdt update success.");
#endif
    break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
   
#if defined(BSP_USING_FWDT) 
     /* set timeout sec*/
     time_sec = *(rt_uint32_t*)arg;
     wdgt_count = 32*1000/32*time_sec;
     ErrStatus res = fwdgt_prescaler_value_config(FWDGT_PSC_DIV32);
     res = fwdgt_reload_value_config(wdgt_count);
     LOG_D("timeout=%d sec,count=%d res=%d ", time_sec, wdgt_count, res);
#elif defined(BSP_USING_WWDT)
     /* set timeout ms */
     window_value = 0x7F;
     time_msec = *(rt_uint32_t*)arg;
     wdgt_count =  (rt_uint32_t)((float)((float)1/0.78)*time_msec) + 0x3F;
     wwdgt_config(wdgt_count, window_value, WWDGT_CFG_PSC_DIV8);
     LOG_D("timeout=%d msec,count=%d ", time_msec, wdgt_count);
#endif
    
    break;
    case RT_DEVICE_CTRL_WDT_START:
#if defined(BSP_USING_FWDT)  
        fwdgt_enable();
#elif defined(BSP_USING_WWDT)
        wwdgt_enable();
#endif
    LOG_D("wdt control enable success.");
    break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
    rcu_periph_clock_enable(RCU_WWDGT);
    gd32_wdt.is_start = 0;
    ops.init = &wdt_init;
    ops.control = &wdt_control;
    gd32_wdt.watchdog.ops = &ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&gd32_wdt.watchdog, HW_WDGT_DEV_NAME, RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D(" wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#if defined(BSP_USING_FWDT)  
int fwdt_test_sample()
{
    rt_err_t ret = RT_EOK;
    rt_device_t hw_dev = RT_NULL;
    rt_ubase_t time_out_sec = 4;
    hw_dev = rt_device_find(HW_WDGT_DEV_NAME);
    
    LOG_D("find fwdt device success,device=%x",hw_dev);
    if (hw_dev == RT_NULL)
    {
        LOG_D("hwtimer sample run failed! can't find %s device!", HW_WDGT_DEV_NAME);
        return -RT_ERROR;
    }
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    LOG_D("open fwdt device success");
    if (ret != RT_EOK)
    {
        LOG_D("open %s device failed!", HW_WDGT_DEV_NAME);
        return ret;
    }

    ret = rt_device_control(hw_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &time_out_sec);
    if (ret != RT_EOK)
    {
        LOG_D("control %s device failed!", HW_WDGT_DEV_NAME);
        return ret;
    }
    rt_device_control(hw_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    rt_device_control(hw_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
}

MSH_CMD_EXPORT(fwdt_test_sample, fwdt timeout 4 sec reset)

#elif defined(BSP_USING_WWDT)
int wwdt_test_sample()
{
    rt_err_t ret = RT_EOK;
    rt_device_t hw_dev = RT_NULL;
    rt_ubase_t time_out_msec = 40;
    hw_dev = rt_device_find(HW_WDGT_DEV_NAME);
    
    LOG_D("find wwdt device success,device=%x",hw_dev);
    if (hw_dev == RT_NULL)
    {
        LOG_D("hwtimer sample run failed! can't find %s device!", HW_WDGT_DEV_NAME);
        return -RT_ERROR;
    }
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    LOG_D("open wwdt device success");
    if (ret != RT_EOK)
    {
        LOG_D("open %s device failed!", HW_WDGT_DEV_NAME);
        return ret;
    }

    ret = rt_device_control(hw_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &time_out_msec);
    if (ret != RT_EOK)
    {
        LOG_D("control %s device failed!", HW_WDGT_DEV_NAME);
        return ret;
    }
    rt_device_control(hw_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    rt_device_control(hw_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, RT_NULL);
}
MSH_CMD_EXPORT(wwdt_test_sample, wwdt timeout 40 msec reset)
#endif

#endif /* RT_USING_WDT */
