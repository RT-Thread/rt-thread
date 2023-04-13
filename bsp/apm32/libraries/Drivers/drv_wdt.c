/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-03-04     stevetong459      first version
 * 2022-12-26     luobeihai         add APM32F0 series MCU support
 * 2023-03-28     luobeihai         add APM32E1/S1 series MCU support
 */

#include <board.h>
#include <sys/time.h>

#ifdef RT_USING_WDT

#define DBG_TAG             "drv.wdt"
#define DBG_LVL             DBG_INFO
#include <rtdbg.h>

#ifndef LSI_VALUE
    #define LSI_VALUE            ((uint32_t)40000)
#endif

#define DRV_WDT_TIME_OUT      0xFFFF

typedef struct
{
    struct rt_watchdog_device wdt;
    rt_uint32_t min_threshold;
    rt_uint32_t max_threshold;
    rt_uint32_t current_threshold;
} apm32_wdt_t;

static apm32_wdt_t wdt_config;

static rt_err_t apm32_iwdt_init(rt_watchdog_t *wdt)
{
    rt_uint32_t counter = 0;

    RCM_EnableLSI();

    while (!RCM_ReadStatusFlag(RCM_FLAG_LSIRDY))
    {
        if (++counter > DRV_WDT_TIME_OUT)
        {
            LOG_E("LSI clock open failed.");
            return -RT_ERROR;
        }
    }

    wdt_config.min_threshold = 1;
    wdt_config.max_threshold = (0xfff << 8) / LSI_VALUE;
    LOG_I("threshold section [%u, %d]", \
          wdt_config.min_threshold,
          wdt_config.max_threshold);

#if defined(SOC_SERIES_APM32F0)
    while (IWDT_ReadStatusFlag(IWDT_FLAG_DIVU))
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    while (IWDT_ReadStatusFlag(IWDT_FLAG_PSCU))
#endif
    {
        if (++counter > DRV_WDT_TIME_OUT)
        {
            LOG_E("watchdog prescaler init failed.");
            return -RT_ERROR;
        }
    }

    IWDT_EnableWriteAccess();

#if defined(SOC_SERIES_APM32F0)
    IWDT_ConfigDivider(IWDT_DIV_256);
#elif defined(SOC_SERIES_APM32F1) || defined(SOC_SERIES_APM32E1) || defined(SOC_SERIES_APM32S1) \
    || defined(SOC_SERIES_APM32F4)
    IWDT_ConfigDivider(IWDT_DIVIDER_256);
#endif

    IWDT_DisableWriteAccess();

    return RT_EOK;
}

/**
 * @brief    This function will control watchdog device.
 *
 * @param    wdt is a pointer to i2c config class.
 *
 * @return   RT_EOK indicates successful , other value indicates failed.
 */
static rt_err_t apm32_iwdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    volatile rt_uint32_t param, counter = 0;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        IWDT_Refresh();
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        param = *(rt_uint32_t *) arg;
        if ((param > wdt_config.max_threshold) || \
                (param < wdt_config.min_threshold))
        {
            LOG_E("invalid param@%u.", param);
            return -RT_ERROR;
        }
        else
        {
            wdt_config.current_threshold = param;
        }
        while (IWDT_ReadStatusFlag(IWDT_FLAG_CNTU))
        {
            if (++counter > DRV_WDT_TIME_OUT)
            {
                LOG_E("Update watchdog reload value complete.");
                return -RT_ERROR;
            }
        }
        IWDT_Refresh();
        IWDT_EnableWriteAccess();
        IWDT_ConfigReload(param * LSI_VALUE >> 8);
        IWDT_DisableWriteAccess();
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)arg = wdt_config.current_threshold;
        break;
    case RT_DEVICE_CTRL_WDT_START:
        IWDT_Enable();
        IWDT_Refresh();
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops apm32_wdt_ops =
{
    apm32_iwdt_init,
    apm32_iwdt_control,
};

static int rt_hw_wdt_init(void)
{
    wdt_config.wdt.ops = &apm32_wdt_ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&wdt_config.wdt, "wdt", \
                                RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif
