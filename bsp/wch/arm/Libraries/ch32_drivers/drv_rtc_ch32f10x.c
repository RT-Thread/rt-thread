/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2021-08-10   charlown       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>
#include "board.h"

#ifdef BSP_USING_RTC

#define LOG_TAG "drv.rtc"
#include "drv_log.h"

#ifndef BKP_DR1
#define BKP_DR1 RT_NULL
#endif

#define BKUP_REG_DATA 0xA5A5

static struct rt_rtc_device rtc;

static void rt_rtc_config(void)
{
    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);

#if defined(BSP_USING_RTC_LSI) && defined(LSI_VALUE)
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#else
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#endif

    RCC_RTCCLKCmd(ENABLE);

    RTC_WaitForLastTask();

    RTC_WaitForSynchro();

    if (BKP_ReadBackupRegister(BKP_DR1) != BKUP_REG_DATA)
    {
        LOG_I("RTC hasn't been configured, please use <date> command to config.");
        /* Set RTC prescaler: set RTC period to 1sec */
        RTC_SetPrescaler(32767);
        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();
    }
}

static rt_err_t ch32f1_rt_rtc_init(void)
{

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

#if defined(BSP_USING_RTC_LSI) && defined(LSI_VALUE)
    RCC_LSICmd(ENABLE);

    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
        ;
#else

    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
        ;
#endif

    rt_rtc_config();

    return RT_EOK;
}

static rt_err_t ch32f1_get_secs(time_t *args)
{
    *(rt_uint32_t *)args = RTC_GetCounter();
    LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)args);

    return RT_EOK;
}

static rt_err_t ch32f1_set_secs(time_t *args)
{
    /* Set the RTC counter value */
    RTC_SetCounter(*(rt_uint32_t *)args);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    LOG_D("set rtc time.");
    BKP_WriteBackupRegister(BKP_DR1, BKUP_REG_DATA);

    LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)args);

    return RT_EOK;
}

const static struct rt_rtc_ops rtc_ops =
    {
        .init = ch32f1_rt_rtc_init,
        .get_secs = ch32f1_get_secs,
        .set_secs = ch32f1_set_secs,
        .get_alarm = RT_NULL,
        .set_alarm = RT_NULL,
        .get_timeval = RT_NULL,
        .set_timeval = RT_NULL};

int rt_hw_rtc_init(void)
{
    rt_err_t result;

    rtc.ops = &rtc_ops;

    result = rt_hw_rtc_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR, RT_NULL);
    if (result != RT_EOK)
    {
        LOG_E("rtc register err code: %d", result);
        return result;
    }
    LOG_D("rtc init success");

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif /* BSP_USING_RTC */
