/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-30     greedyhao         first version
 */

#include <board.h>

#ifdef RT_USING_WDT

#include <drv_wdt.h>

// #define DRV_DEBUG
#define LOG_TAG             "drv.wdt"
#include <drv_log.h>

struct ab32_wdt_obj
{
    rt_watchdog_t watchdog;
};
static struct ab32_wdt_obj ab32_wdt;
static struct rt_watchdog_ops ops;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    rt_uint32_t tmp = 0;

    switch (cmd)
    {
        /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        WDTCON = 0xa;
        break;
        /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        if (arg == RT_NULL) {
            LOG_E("The watchdog timeout argument cannot be NULL!");
            break;
        }

        tmp = WDTCON & ~(0x7 << 20);

        switch (*((rt_uint32_t *)arg))
        {
        case AB32_WDT_TIMEOUT_1MS:
            LOG_I("The watchdog timeout is set to 1ms");
            tmp |= (0xa << 24) | (0x00 << 20);
            break;
        case AB32_WDT_TIMEOUT_256MS:
            LOG_I("The watchdog timeout is set to 256ms");
            tmp |= (0xa << 24) | (0x01 << 20);
            break;
        case AB32_WDT_TIMEOUT_512MS:
            LOG_I("The watchdog timeout is set to 512ms");
            tmp |= (0xa << 24) | (0x02 << 20);
            break;
        case AB32_WDT_TIMEOUT_1024MS:
            LOG_I("The watchdog timeout is set to 1024ms");
            tmp |= (0xa << 24) | (0x03 << 20);
            break;
        case AB32_WDT_TIMEOUT_2048MS:
            LOG_I("The watchdog timeout is set to 2048ms");
            tmp |= (0xa << 24) | (0x04 << 20);
            break;
        case AB32_WDT_TIMEOUT_4096MS:
            LOG_I("The watchdog timeout is set to 4096ms");
            tmp |= (0xa << 24) | (0x05 << 20);
            break;
        case AB32_WDT_TIMEOUT_8192MS:
            LOG_I("The watchdog timeout is set to 8192ms");
            tmp |= (0xa << 24) | (0x06 << 20);
            break;
        case AB32_WDT_TIMEOUT_16384MS:
            LOG_I("The watchdog timeout is set to 16384ms");
            tmp |= (0xa << 24) | (0x07 << 20);
            break;
        default:
            LOG_W("The watchdog timeout argument range from 0 to 7!");
            tmp = WDTCON;
            break;
        }
        WDTCON = tmp;
        LOG_D("WDTCON=%X", WDTCON);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        switch ((WDTCON >> 20) & 0x7)
        {
        case AB32_WDT_TIMEOUT_1MS:
            LOG_D("The watchdog timeout is set to 1ms");
            break;
        case AB32_WDT_TIMEOUT_256MS:
            LOG_D("The watchdog timeout is set to 256ms");
            break;
        case AB32_WDT_TIMEOUT_512MS:
            LOG_D("The watchdog timeout is set to 512ms");
            break;
        case AB32_WDT_TIMEOUT_1024MS:
            LOG_D("The watchdog timeout is set to 1024ms");
            break;
        case AB32_WDT_TIMEOUT_2048MS:
            LOG_D("The watchdog timeout is set to 2048ms");
            break;
        case AB32_WDT_TIMEOUT_4096MS:
            LOG_D("The watchdog timeout is set to 4096ms");
            break;
        case AB32_WDT_TIMEOUT_8192MS:
            LOG_D("The watchdog timeout is set to 8192ms");
            break;
        case AB32_WDT_TIMEOUT_16384MS:
            LOG_D("The watchdog timeout is set to 16384ms");
            break;
        default:
            break;
        }
        break;
    case RT_DEVICE_CTRL_WDT_START:
        WDTCON = 0x110;
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
    ops.init = &wdt_init;
    ops.control = &wdt_control;
    ab32_wdt.watchdog.ops = &ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&ab32_wdt.watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#endif /* RT_USING_WDT */
