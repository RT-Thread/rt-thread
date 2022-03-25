/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 */

#include "board.h"
#include <sys/time.h>

#ifdef BSP_USING_ONCHIP_RTC

#define LOG_TAG               "drv.rtc"
#define DBG_LVL               DBG_INFO
#include <rtdbg.h>

#ifndef LSI_VALUE
    #define  LSI_VALUE            ((uint32_t)40000)
#endif
#ifndef LSE_VALUE
    #define  LSE_VALUE            ((uint32_t)32768)
#endif

#define DRV_RTC_TIME_OUT      0xFFF

static rt_rtc_dev_t apm32_rtc_dev;

/**
 * @brief    This function will initialize the rtc on chip.
 *
 * @return   RT_EOK indicates successful initialize, other value indicates failed;
 */
static rt_err_t _rtc_init(void)
{
    volatile rt_uint32_t counter = 0;

    /* Enable RTC Clock */
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_PMU | RCM_APB1_PERIPH_BAKR);
    PMU_EnableBackupAccess();

    /* Config RTC clock */
#ifdef BSP_RTC_USING_LSI
    RCM_EnableLSI();
    while (!RCM_ReadStatusFlag(RCM_FLAG_LSIRDY))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return RT_ETIMEOUT;
        }
    }
    RCM_ConfigRTCCLK(RCM_RTCCLK_LSI);
#else
    RCM_ConfigLSE(RCM_LSE_OPEN);
    while (!RCM_ReadStatusFlag(RCM_FLAG_LSERDY))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return RT_ETIMEOUT;
        }
    }
    RCM_ConfigRTCCLK(RCM_RTCCLK_LSE);
#endif

    RCM_EnableRTCCLK();

    RTC_WaitForSynchor();

    counter = 0;
    while (!RTC_ReadStatusFlag(RTC_FLAG_OC))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return RT_ETIMEOUT;
        }
    }

    RTC_EnableConfigMode();

    RTC_ClearStatusFlag(RTC_FLAG_OVR | RTC_FLAG_ALR | RTC_FLAG_SEC);

#ifdef BSP_RTC_USING_LSI
    RTC_ConfigPrescaler(LSI_VALUE - 1);
#else
    RTC_ConfigPrescaler(LSE_VALUE - 1);
#endif

    return RT_EOK;
}

/**
 * @brief    This function will initialize the rtc on chip.
 *
 * @return   RT_EOK indicates successful initialize, other value indicates failed;
 */
static rt_err_t _rtc_get_secs(void *args)
{
    volatile rt_uint32_t counter = 0;

    while (!RTC_ReadStatusFlag(RTC_FLAG_OC))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return RT_ETIMEOUT;
        }
    }

    *(rt_uint32_t *) args = RTC_ReadCounter();

    return RT_EOK;
}

static rt_err_t _rtc_set_secs(void *args)
{
    volatile rt_uint32_t counter = 0;

    while (!RTC_ReadStatusFlag(RTC_FLAG_OC))
    {
        if (++counter > DRV_RTC_TIME_OUT)
        {
            return RT_ETIMEOUT;
        }
    }

    RTC_ConfigCounter(*(rt_uint32_t *)args);

    return RT_EOK;
}


static const struct rt_rtc_ops _rtc_ops =
{
    _rtc_init,
    _rtc_get_secs,
    _rtc_set_secs,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
};

/**
 * @brief    RTC initialization function.
 *
 * @return   RT_EOK indicates successful initialization, other value indicates failed;
 */
static int rt_hw_rtc_init(void)
{
    rt_err_t result = RT_EOK;

    apm32_rtc_dev.ops = &_rtc_ops;

    if (rt_hw_rtc_register(&apm32_rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL) != RT_EOK)
    {
        LOG_E("rtc init failed");
        result = RT_ERROR;
    }
    else
    {
        LOG_D("rtc init success");
    }

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_ONCHIP_RTC */
