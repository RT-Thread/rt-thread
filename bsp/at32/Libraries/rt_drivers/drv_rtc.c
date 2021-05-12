/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author        Notes
 * 2020-05-19   shelton       first version
 */

#include "board.h"
#include <rtthread.h>
#include <sys/time.h>

#ifdef BSP_USING_RTC

#ifndef BKP_DR1
#define BKP_DR1 RT_NULL
#endif

//#define DRV_DEBUG
#define LOG_TAG             "drv.rtc"
#include <drv_log.h>

#define BKUP_REG_DATA 0xA5A5

static struct rt_device rtc;

static time_t get_rtc_timestamp(void)
{
#ifdef SOC_SERIES_AT32F415
    struct tm tm_new;
    ERTC_TimeType ERTC_TimeStruct;
    ERTC_DateType ERTC_DateStruct;

    ERTC_GetTimeValue(ERTC_Format_BIN, &ERTC_TimeStruct);
    ERTC_GetDateValue(ERTC_Format_BIN, &ERTC_DateStruct);
    tm_new.tm_sec  = ERTC_TimeStruct.ERTC_Seconds;
    tm_new.tm_min  = ERTC_TimeStruct.ERTC_Minutes;
    tm_new.tm_hour = ERTC_TimeStruct.ERTC_Hours;
    tm_new.tm_mday = ERTC_DateStruct.ERTC_Date;
    tm_new.tm_mon  = ERTC_DateStruct.ERTC_Month - 1;
    tm_new.tm_year = ERTC_DateStruct.ERTC_Year + 100;

    LOG_D("get rtc time.");
    return timegm(&tm_new);
#else
    return RTC_GetCounter();
#endif
}

static rt_err_t set_rtc_time_stamp(time_t time_stamp)
{
#ifdef SOC_SERIES_AT32F415
    ERTC_TimeType  ERTC_TimeStructure;
    ERTC_DateType  ERTC_DateStructure;

    struct tm *p_tm;

    p_tm = gmtime(&time_stamp);
    if (p_tm->tm_year < 100)
    {
        return -RT_ERROR;
    }
    ERTC_TimeStructure.ERTC_Seconds = p_tm->tm_sec ;
    ERTC_TimeStructure.ERTC_Minutes = p_tm->tm_min ;
    ERTC_TimeStructure.ERTC_Hours   = p_tm->tm_hour;
    ERTC_DateStructure.ERTC_Date    = p_tm->tm_mday;
    ERTC_DateStructure.ERTC_Month   = p_tm->tm_mon + 1 ;
    ERTC_DateStructure.ERTC_Year    = p_tm->tm_year - 100;
    ERTC_DateStructure.ERTC_WeekDay = p_tm->tm_wday + 1;

    if (ERTC_SetTimeValue(ERTC_Format_BIN, &ERTC_TimeStructure) != SUCCESS)
    {
        return -RT_ERROR;
    }
    if (ERTC_SetDateValue(ERTC_Format_BIN, &ERTC_DateStructure) != SUCCESS)
    {
        return -RT_ERROR;
    }
#else
    /* Set the RTC counter value */
    RTC_SetCounter(time_stamp);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
#endif /* SOC_SERIES_AT32F415 */
    LOG_D("set rtc time.");
#ifdef SOC_SERIES_AT32F415
    ERTC_WriteBackupRegister(ERTC_BKP_DT0, BKUP_REG_DATA);
#else
    BKP_WriteBackupReg(BKP_DT1, BKUP_REG_DATA);
#endif
    return RT_EOK;
}

static void rt_rtc_init(void)
{
#if defined (SOC_SERIES_AT32F415)
    RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR, ENABLE);
#else
    RCC_APB1PeriphClockCmd(RCC_APB1PERIPH_PWR | RCC_APB1PERIPH_BKP, ENABLE);
#endif

#ifdef BSP_RTC_USING_LSI
    RCC_LSICmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_LSISTBL) == RESET);
#else
    PWR_BackupAccessCtrl(ENABLE);
    RCC_LSEConfig(RCC_LSE_ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_LSESTBL) == RESET);
#endif /* BSP_RTC_USING_LSI */
}

static rt_err_t rt_rtc_config(struct rt_device *dev)
{
#if defined (SOC_SERIES_AT32F415)
    ERTC_InitType ERTC_InitStructure;
#endif
    /* Allow access to BKP Domain */
    PWR_BackupAccessCtrl(ENABLE);

#ifdef SOC_SERIES_AT32F415
  #ifdef BSP_RTC_USING_LSI
    RCC_ERTCCLKConfig(RCC_ERTCCLKSelection_LSI);
    RCC_ERTCCLKCmd(ENABLE);
  #else
    RCC_ERTCCLKConfig(RCC_ERTCCLKSelection_LSE);
    RCC_ERTCCLKCmd(ENABLE);
  #endif /* BSP_RTC_USING_LSI */
    /* Wait for ERTC APB registers synchronisation */
    ERTC_WaitForSynchro();
#else
  #ifdef BSP_RTC_USING_LSI
    RCC_RTCCLKConfig(RCC_RTCCLKSelection_LSI);
    RCC_RTCCLKCmd(ENABLE);
  #else
    RCC_RTCCLKConfig(RCC_RTCCLKSelection_LSE);
    RCC_RTCCLKCmd(ENABLE);
  #endif /* BSP_RTC_USING_LSI */
    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
#endif /* SOC_SERIES_AT32F415 */

#ifdef SOC_SERIES_AT32F415
    if (ERTC_ReadBackupRegister(BKP_DT1)!= BKUP_REG_DATA)
#else
    if (BKP_ReadBackupReg(BKP_DT1) != BKUP_REG_DATA)
#endif
    {
        LOG_I("RTC hasn't been configured, please use <date> command to config.");
#ifdef SOC_SERIES_AT32F415
        /* Configure the ERTC data register and ERTC prescaler */
        ERTC_InitStructure.ERTC_AsynchPrediv = 0x7F;
        ERTC_InitStructure.ERTC_SynchPrediv = 0xFF;
        ERTC_InitStructure.ERTC_HourFormat = ERTC_HourFormat_24;
        ERTC_Init(&ERTC_InitStructure);
#else
        /* Set RTC prescaler: set RTC period to 1sec */
        RTC_SetDIV(32767);
        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();
#endif
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

#endif /* BSP_USING_RTC */
