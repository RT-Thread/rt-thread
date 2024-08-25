/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2021-03-15   picospuch     Porting for maxiam32660
 */

#include "drivers/dev_rtc.h"
#include "board.h"
#include <sys/time.h>

#ifdef BSP_USING_ONCHIP_RTC

#define DBG_LEVEL   DBG_INFO
#include <rtdbg.h>
#define LOG_TAG                "drv.rtc"

static struct rt_device rtc;

static sys_cfg_rtc_t sys_cfg;

static time_t get_rtc_timestamp(void)
{
    LOG_D("get rtc time.");
    return RTC_GetSecond();
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
  LOG_D("set rtc time.");

  if (RTC_Init(MXC_RTC, time_stamp, 0, &sys_cfg) != E_SUCCESS) {
    return -RT_ERROR;
  }

  if (RTC_EnableRTCE(MXC_RTC) != E_SUCCESS) {
    return -RT_ERROR;
  }

  return RT_EOK;
}

static void rt_rtc_init(void)
{
  sys_cfg.tmr = MXC_TMR0;
  RTC_Init(MXC_RTC, 0, 0, &sys_cfg);
}

static rt_err_t rt_rtc_config(struct rt_device *dev)
{
  if (RTC_EnableRTCE(MXC_RTC) != E_SUCCESS) {
    return -RT_ERROR;
  }
  return RT_EOK;
}

static rt_err_t rt_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(dev != RT_NULL);
    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = get_rtc_timestamp();
        LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
        if (set_rtc_time_stamp(*(rt_uint32_t *)args))
        {
            result = -RT_ERROR;
        }
        LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)args);
        break;
    }

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops rtc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    rt_rtc_control
};
#endif

static rt_err_t rt_hw_rtc_register(rt_device_t device, const char *name, rt_uint32_t flag)
{
    RT_ASSERT(device != RT_NULL);

    rt_rtc_init();
    if (rt_rtc_config(device) != RT_EOK)
    {
        return -RT_ERROR;
    }
#ifdef RT_USING_DEVICE_OPS
    device->ops         = &rtc_ops;
#else
    device->init        = RT_NULL;
    device->open        = RT_NULL;
    device->close       = RT_NULL;
    device->read        = RT_NULL;
    device->write       = RT_NULL;
    device->control     = rt_rtc_control;
#endif
    device->type        = RT_Device_Class_RTC;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;
    device->user_data   = RT_NULL;

    /* register a character device */
    return rt_device_register(device, name, flag);
}

int rt_hw_rtc_init(void)
{
    rt_err_t result;
    result = rt_hw_rtc_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_ONCHIP_RTC */
