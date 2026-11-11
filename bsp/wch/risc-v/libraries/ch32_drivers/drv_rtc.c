/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2021-08-10   charlown      first version
 * 2022-09-22   hg0720        the first version which add from wch
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

#define BKUP_REG_DATA 0xA1A1

static struct rt_rtc_device rtc;

static void rt_rtc_config(void)
{
    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);

#if defined(BSP_USING_RTC_LSI) && defined(LSI_VALUE)
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#else /* BSP_USING_RTC_LSE */
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

static rt_err_t ch32_rtc_init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

#if defined(BSP_USING_RTC_LSI) && defined(LSI_VALUE)
    RCC_LSICmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
#else /* BSP_USING_RTC_LSE */
    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
#endif

    rt_rtc_config();

    return RT_EOK;
}

static rt_err_t ch32_get_secs(time_t *sec)
{
    *(rt_uint32_t *)sec = RTC_GetCounter();
    LOG_D("RTC: get rtc_time %x\n", *(rt_uint32_t *)sec);

    return RT_EOK;
}

static rt_err_t ch32_set_secs(time_t *sec)
{
    /* Set the RTC counter value */
    RTC_SetCounter(*(rt_uint32_t *)sec);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
    LOG_D("set rtc time.");
    BKP_WriteBackupRegister(BKP_DR1, BKUP_REG_DATA);
    LOG_D("RTC: set rtc_time %x\n", *(rt_uint32_t *)sec);

    return RT_EOK;
}

const static struct rt_rtc_ops rtc_ops =
{
    ch32_rtc_init,
    ch32_get_secs,
    ch32_set_secs,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL
};

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
