/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2021-07-28     songchao           first version
 */

#include <rtconfig.h>

#ifdef RT_USING_WDT
#include <rtthread.h>
#include <rtdbg.h>
#include "drv_wdt.h"
#include "fsl_wdog.h"
#include "imx6ull.h"

enum
{
#ifdef RT_USING_WDT1
    DEV_WDT1,
#endif

#ifdef RT_USING_WDT2
    DEV_WDT2,
#endif

#ifdef RT_USING_WDT3
    DEV_WDT3,
#endif

    DEV_MAX,
};

#ifdef RT_USING_WDT1
static wdog_config_t WDOG_1_config =
{
    .timeoutValue = 0xffu,
    .enablePowerDown = false,
    .softwareResetExtension = false,
    .softwareAssertion = true,
    .softwareResetSignal = true,
    .enableWdog = true,
    .workMode =
    {
        .enableWait = false,
        .enableStop = false,
        .enableDebug = false,
    },
    .enableInterrupt = false,
    .interruptTimeValue = 0x04u,
};
#endif

#ifdef RT_USING_WDT2
static wdog_config_t WDOG_2_config =
{
    .timeoutValue = 0xffu,
    .enablePowerDown = false,
    .softwareResetExtension = false,
    .softwareAssertion = true,
    .softwareResetSignal = true,
    .enableWdog = true,
    .workMode =
    {
        .enableWait = false,
        .enableStop = false,
        .enableDebug = false,
    },
    .enableInterrupt = false,
    .interruptTimeValue = 0x04u,
};
#endif

#ifdef RT_USING_WDT3
static wdog_config_t WDOG_3_config =
{
    .timeoutValue = 0xffu,
    .enablePowerDown = false,
    .softwareResetExtension = false,
    .softwareAssertion = true,
    .softwareResetSignal = true,
    .enableWdog = true,
    .workMode =
    {
        .enableWait = false,
        .enableStop = false,
        .enableDebug = false,
    },
    .enableInterrupt = false,
    .interruptTimeValue = 0x04u,
};
#endif

static rt_watchdog_t imx6ull_watchdog[DEV_MAX] =
{
#ifdef RT_USING_WDT1
    {
        .name = "wdt1",
        .paddr = IMX6ULL_WATCHDOG1_BASE,
        .config = &WDOG_1_config,
    },
#endif

#ifdef RT_USING_WDT2
    {
        .name = "wdt2",
        .paddr = IMX6ULL_WATCHDOG2_BASE,
        .config = &WDOG_2_config,
    },
#endif

#ifdef RT_USING_WDT3
    {
        .name = "wdt3",
        .paddr = IMX6ULL_WATCHDOG3_BASE,
        .config = &WDOG_3_config,
    },
#endif

};

static rt_err_t imx6ull_wdog_init(rt_watchdog_t *wdt)
{
    WDOG_Type *base = RT_NULL;
    base = (WDOG_Type *)wdt->vaddr;
    WDOG_Init(base, wdt->config);
    WDOG_Disable(base);
    return RT_EOK;
}

static rt_err_t imx6ull_wdog_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    RT_ASSERT(wdt != NULL);

    WDOG_Type *base = RT_NULL;
    base = (WDOG_Type *)wdt->vaddr;

    switch(cmd)
    {
        case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        {
            *(uint16_t *)args = (base->WCR >> 8)  / 2;
        }
        break;
        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        {
            RT_ASSERT(*(uint16_t *)args != 0);
            WDOG_SetTimeoutValue(base, (*(uint16_t *)args) * 2);
            WDOG_Disable(base);
        }
        break;
        case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        {
            WDOG_Refresh(base);
        }
        break;
        case RT_DEVICE_CTRL_WDT_START:
        {
            WDOG_Enable(base);
        }
        break;
        case RT_DEVICE_CTRL_WDT_STOP:
        {
            WDOG_Disable(base);
        }
        break;
        default:
            return RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops imx6ull_wdog_ops =
{
    .init = imx6ull_wdog_init,
    .control = imx6ull_wdog_control,
};

int rt_hw_wdt_init(void)
{
    rt_err_t ret = RT_EOK;
    for(int idx = 0; idx < GET_ARRAY_NUM(imx6ull_watchdog); idx++)
    {
        imx6ull_watchdog[idx].ops = &imx6ull_wdog_ops;
        imx6ull_watchdog[idx].vaddr = platform_get_periph_vaddr(imx6ull_watchdog[idx].paddr);
        ret = rt_hw_watchdog_register(&imx6ull_watchdog[idx], imx6ull_watchdog[idx].name,
                                         RT_DEVICE_FLAG_DEACTIVATE, RT_NULL);
        if (ret != RT_EOK)
        {
            LOG_E("rt device register failed %d\n", ret);
        }
    }

    return ret;
}

INIT_DEVICE_EXPORT(rt_hw_wdt_init);

#endif
