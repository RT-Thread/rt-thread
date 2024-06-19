/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-05-24     QT-one       first version
 */

#include <rtdbg.h>
#include "drv_wdt.h"

#ifdef BSP_USING_WDT

struct ht32_wdt
{
    struct rt_watchdog_device ht32_wdt_device;
    rt_uint8_t ht32_wdt_start_flag;
};

static struct ht32_wdt ht32_wdt_obj;

/* Initialization functions for wdt */
static rt_err_t ht32_wdt_init(rt_watchdog_t *wdt)
{
    return -RT_ERROR;
}
/* Control function for wdt */
static rt_err_t ht32_wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    rt_uint16_t wdt_time_val = (*((rt_uint16_t*)arg));
    switch(cmd)
    {
        /* get timeout(in seconds) */
        case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
            (*((rt_uint16_t*)arg)) = (WDT_GetReloadValue())/250;
            break;
        /* set timeout(in seconds) */
        case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
            if(ht32_wdt_obj.ht32_wdt_start_flag)
            {
                LOG_W("Please stop the WDT device first.");
            }
            else
            {
                if(wdt_time_val > 16)
                {
                    LOG_W("Parameter out of settable range.");
                }
                else
                {
                    /* Disable WDT Protection */
                    WDT_ProtectCmd(DISABLE);
                    /* Reset WDT */
                    WDT_DeInit();
                    /* Set Prescaler Value, 32K/128 = 250Hz 4ms */
                    WDT_SetPrescaler(WDT_PRESCALER_128);
                    /* Set Prescaler Value, 250Hz*wdt_time_val*250 = nms */
                    WDT_SetReloadValue((wdt_time_val*250));
                    /* Set Delta Value, 250Hz*wdt_time_val*250 = nms */
                    WDT_SetDeltaValue((wdt_time_val*250));
                    /* Enable the WDT Reset when WDT meets underflow or error */
                    WDT_ResetCmd(ENABLE);
                    /* Reload Counter as WDTV Value */
                    WDT_Restart();
                }
            }
            break;
        /* get the left time before reboot(in seconds) */
        case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
            return -RT_ERROR;
        /* refresh watchdog */
        case RT_DEVICE_CTRL_WDT_KEEPALIVE:
            if(ht32_wdt_obj.ht32_wdt_start_flag)
            {
                /* Enable WDT Restart (Reload WDT Counter) */
                WDT_Restart();
            }
            else
            {
                LOG_W("WDT device not activated.");
            }
            break;
        /* start watchdog */
        case RT_DEVICE_CTRL_WDT_START:
            if(ht32_wdt_obj.ht32_wdt_start_flag)
            {
                LOG_W("The WDT device has been activated.");
            }
            else
            {
                /* Enable WDT */
                WDT_Cmd(ENABLE);
                /* Enable WDT Protection */
                WDT_ProtectCmd(ENABLE);
                ht32_wdt_obj.ht32_wdt_start_flag = 1;
            }
            break;
        /* stop watchdog */
        case RT_DEVICE_CTRL_WDT_STOP:
            if(ht32_wdt_obj.ht32_wdt_start_flag)
            {
                /* Disable WDT Protection */
                WDT_ProtectCmd(DISABLE);
                /* Disable WDT */
                WDT_Cmd(DISABLE);
                ht32_wdt_obj.ht32_wdt_start_flag = 0;
            }
            else
            {
                LOG_W("WDT is not activated and does not need to be shut down.");
            }
            break;
        default:
            LOG_W("This command is not supported.");
            return -RT_ERROR;
    }
    return RT_EOK;
}

static struct rt_watchdog_ops ht32_wdt_ops =
{
    .init       = ht32_wdt_init,
    .control    = ht32_wdt_control,
};

static int rt_hw_wdt_init(void)
{
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.WDT = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* wdt operator function */
    ht32_wdt_obj.ht32_wdt_device.ops = &ht32_wdt_ops;
    /* wdt activation flag bit */
    ht32_wdt_obj.ht32_wdt_start_flag = 0;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&ht32_wdt_obj.ht32_wdt_device, BSP_USING_WDT_NAME, RT_DEVICE_FLAG_DEACTIVATE, &ht32_wdt_obj) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif
