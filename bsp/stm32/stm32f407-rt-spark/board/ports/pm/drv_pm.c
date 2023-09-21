/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-07-31     tanek        first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
/**
 * This function will put STM32F4xx into sleep mode.
 *
 * @param pm pointer to power manage structure
 */
static void sleep(struct rt_pm *pm, uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
        break;

    case PM_SLEEP_MODE_LIGHT:
        HAL_SuspendTick();  /* 关闭系统时钟中断 */
        HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); /* 进入 F407 sleep 模式，这个模式会停掉所有时钟，可被任意中断唤醒 */
        break;

    case PM_SLEEP_MODE_DEEP:
        HAL_SuspendTick();  /* 关闭系统时钟中断 */
        HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI); /* 进入 F407 stop 模式，这个模式会停掉所有时钟，可被任意中断唤醒  */
        break;

    case PM_SLEEP_MODE_STANDBY:
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        break;

    default:
        RT_ASSERT(0);
        break;
    }
}

/**
 * This function will be Called in Wake up interrupt callback
 *
 * @param pm pointer to power manage structure
 */

static struct rt_device *device = RT_NULL;
static struct rt_pm *pm = RT_NULL;

void pm_wk_up()
{

    switch (pm->sleep_mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
        break;

    case PM_SLEEP_MODE_LIGHT:
        HAL_ResumeTick();   /* 启动系统时钟中断 */
        break;

    case PM_SLEEP_MODE_DEEP:
        SystemClock_Config(); /* 重新配置系统时钟 */
        HAL_ResumeTick();   /* 启动系统时钟中断 */
        break;

    case PM_SLEEP_MODE_STANDBY:
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        break;

    default:
        RT_ASSERT(0);
        break;
    }

}

/**
 * This function initialize the power manager
 */
static int drv_pm_hw_init(void)
{
    static const struct rt_pm_ops _ops =
    {
        sleep,
        RT_NULL,
        RT_NULL,
        RT_NULL,
        RT_NULL
    };

    /* initialize system pm module */
    rt_system_pm_init(&_ops, 0, RT_NULL);

    /* get pm device */
    device = rt_device_find("pm");
    if(device == RT_NULL)
    {
        rt_kprintf("rt_pm find error");
        return 0;
    }
    pm = rt_container_of(device,struct rt_pm,parent);
    return 1;
}
INIT_DEVICE_EXPORT(drv_pm_hw_init);
