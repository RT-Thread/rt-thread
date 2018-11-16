/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-10-25     ZYH               first implementation
 * 2018-10-23     XXXXzzzz000       first implementation,referance:stm32f4xx-HAL/drv_rtc.c
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include <string.h>
#include <time.h>
RTC_HandleTypeDef hrtc;
/* RTC init function */
void MX_RTC_Init(void)
{
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
    /* Initialize RTC Only */
    hrtc.Instance = RTC;
    hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
    hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
    RT_ASSERT(HAL_RTC_Init(&hrtc) == HAL_OK);
    /* Initialize RTC and set the Time and Date */
    if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) != 0x32F1)
    {
        sTime.Hours = 0x0;
        sTime.Minutes = 0x0;
        sTime.Seconds = 0x0;
        RT_ASSERT(HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK);
        sDate.WeekDay = RTC_WEEKDAY_MONDAY;
        sDate.Month = RTC_MONTH_JANUARY;
        sDate.Date = 1;
        sDate.Year = 0;
        RT_ASSERT(HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) == HAL_OK);
    }
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F1);
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *rtcHandle)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    if (rtcHandle->Instance == RTC)
    {

        __HAL_RCC_PWR_CLK_ENABLE();
        HAL_PWR_EnableBkUpAccess();

        __HAL_RCC_BKP_CLK_ENABLE();

        RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
        RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
        RCC_OscInitStruct.LSEState = RCC_LSE_ON;
        HAL_RCC_OscConfig(&RCC_OscInitStruct);

        PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
        PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
        HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

        __HAL_RCC_RTC_ENABLE();
    }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef *rtcHandle)
{
    if (rtcHandle->Instance == RTC)
    {
        /* 禁用RTC时钟 */
        __HAL_RCC_RTC_DISABLE();

        /* 禁用PWR时钟和读取备份域 */
        HAL_PWR_DisableBkUpAccess();
        __HAL_RCC_PWR_CLK_DISABLE();

        /* 禁用备份时钟：备份寄存器 */
        __HAL_RCC_BKP_CLK_DISABLE();
    }
}

static rt_err_t stm32_rtc_control(struct rt_device *dev,
                                  int cmd,
                                  void *args)
{
    struct tm *tm_now;
    struct tm now;
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
        now.tm_hour = sTime.Hours;
        now.tm_min = sTime.Minutes;
        now.tm_sec = sTime.Seconds;
        now.tm_year = sDate.Year + 100;
        now.tm_mon = sDate.Month - 1;
        now.tm_mday = sDate.Date;
        *((time_t *)args) = mktime(&now);
        break;
    case RT_DEVICE_CTRL_RTC_SET_TIME:
        rt_enter_critical();
        /* converts calendar time time into local time. */
        tm_now = localtime((const time_t *)args);
        /* copy the statically located variable */
        memcpy(&now, tm_now, sizeof(struct tm));
        /* unlock scheduler. */
        rt_exit_critical();
        sTime.Hours = now.tm_hour;
        sTime.Minutes = now.tm_min;
        sTime.Seconds = now.tm_sec;
        sDate.Year = now.tm_year - 100;
        sDate.Month = now.tm_mon + 1;
        sDate.Date = now.tm_mday;
        HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
        HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
        break;
    }
    return RT_EOK;
}

static rt_err_t stm32_rtc_init(struct rt_device *dev)
{
    return RT_EOK;
}

static rt_err_t stm32_rtc_open(struct rt_device *dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t stm32_rtc_close(struct rt_device *dev)
{
    return RT_EOK;
}

static rt_size_t stm32_rtc_read(struct rt_device *dev,
                                rt_off_t pos,
                                void *buffer,
                                rt_size_t size)
{
    stm32_rtc_control(dev, RT_DEVICE_CTRL_RTC_GET_TIME, buffer);
    return size;
}

static rt_size_t stm32_rtc_write(struct rt_device *dev,
                                 rt_off_t pos,
                                 const void *buffer,
                                 rt_size_t size)
{
    stm32_rtc_control(dev, RT_DEVICE_CTRL_RTC_SET_TIME, (void *)buffer);
    return size;
}

struct rt_device rtc_device;
int rt_hw_rtc_init(void)
{
    MX_RTC_Init();
    rtc_device.type = RT_Device_Class_RTC;
    rtc_device.rx_indicate = RT_NULL;
    rtc_device.tx_complete = RT_NULL;
    rtc_device.init = stm32_rtc_init;
    rtc_device.open = stm32_rtc_open;
    rtc_device.close = stm32_rtc_close;
    rtc_device.read = stm32_rtc_read;
    rtc_device.write = stm32_rtc_write;
    rtc_device.control = stm32_rtc_control;
    rtc_device.user_data = RT_NULL;
    /* register a character device */
    return rt_device_register(&rtc_device, "rtc", RT_DEVICE_FLAG_RDWR);
}
INIT_BOARD_EXPORT(rt_hw_rtc_init);

static void rtc_set(uint8_t argc, char **argv)
{
    rt_device_t rtc = rt_device_find("rtc");
    RT_ASSERT(rtc != NULL);
    struct tm now = {
        .tm_hour = 10,
        .tm_min = 35,
        .tm_sec = 0,
        .tm_year = 2018 - 1900,
        .tm_mon = 10 - 1,
        .tm_mday = 23,
    };
    time_t tim = mktime(&now);
    rt_device_control(rtc, RT_DEVICE_CTRL_RTC_SET_TIME, &tim);
    int ret = rt_device_write(rtc, 0, &tim, 0);
}
MSH_CMD_EXPORT(rtc_set, rtc_set yyyy mm dd hh mm ss);

static void rtc_get(uint8_t argc, char **argv)
{
    rt_device_t rtc = rt_device_find("rtc");
    RT_ASSERT(rtc != NULL);
    struct tm *tm_now;
    time_t tim;
    struct tm now;
    rt_device_control(rtc, RT_DEVICE_CTRL_RTC_GET_TIME, &tim);

    rt_enter_critical();
    tm_now = localtime(&tim);
    memcpy(&now, tm_now, sizeof(struct tm));
    rt_exit_critical();
    rt_kprintf("%d/%d/%d %d:%d:%d\n", now.tm_year + 1900, now.tm_mon + 1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
}
MSH_CMD_EXPORT(rtc_get, rtc_get);