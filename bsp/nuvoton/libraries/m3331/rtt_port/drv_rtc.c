/*
 * @copyright (C) 2026 Nuvoton Technology Corp. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Includes ------------------------------------------------------------------*/
#include "rtconfig.h"
#if defined(BSP_USING_RTC)

#include "NuMicro.h"
#include "sys/time.h"
#include "rtdevice.h"

/* Defines / Macros ----------------------------------------------------------*/
#undef LOG_TAG
#define LOG_TAG "drv.rtc"
#define DBG_TAG LOG_TAG
#include "drv_log.h"

#define CONV_TO_TM_YEAR(year)           ((year) - 1900)
#define CONV_TO_TM_MON(mon)             ((mon) - 1)

#define CONV_FROM_TM_YEAR(tm_year)      ((tm_year) + 1900)
#define CONV_FROM_TM_MON(tm_mon)        ((tm_mon) + 1)

#define RTC_TM_UPPER_BOUND                                              \
{   .tm_year = CONV_TO_TM_YEAR(2038),                                   \
    .tm_mon  = CONV_TO_TM_MON(1),                                       \
    .tm_mday  = 19,                                                     \
    .tm_hour  = 3,                                                      \
    .tm_min = 14,                                                       \
    .tm_sec  = 07,                                                      \
}
#define RTC_TM_LOWER_BOUND                                              \
{   .tm_year = CONV_TO_TM_YEAR(2000),                                   \
    .tm_mon  = CONV_TO_TM_MON(1),                                       \
    .tm_mday  = 1,                                                      \
    .tm_hour  = 0,                                                      \
    .tm_min = 0,                                                        \
    .tm_sec  = 0,                                                       \
}

/* Types / Structures ---------------------------------------------------------*/

/* Static Function Prototypes ------------------------------------------------*/
static rt_err_t nu_rtc_control(rt_device_t dev, int cmd, void *args);
static rt_err_t nu_rtc_is_date_valid(const time_t t);
static rt_err_t nu_rtc_init(void);
#if defined(RT_USING_ALARM)
static void nu_rtc_alarm_reset(void);
#endif

/* Static Variables ----------------------------------------------------------*/
static struct rt_device device_rtc;

/* Functions Implementation --------------------------------------------------*/
static rt_err_t nu_rtc_init(void)
{
    /* hw rtc initialise */
    RTC_Open(NULL);
    RTC_DisableInt(RTC_INTEN_ALMIEN_Msk | RTC_INTEN_TICKIEN_Msk);
#if defined(RT_USING_ALARM)
    nu_rtc_alarm_reset();
    RTC_EnableInt(RTC_INTEN_ALMIEN_Msk);
    NVIC_EnableIRQ(RTC_IRQn);
#endif

    return RT_EOK;
}
#if defined(RT_USING_ALARM)
/* Reset alarm settings to avoid the unwanted values remain in rtc registers. */
static void nu_rtc_alarm_reset(void)
{
    S_RTC_TIME_DATA_T alarm;

    /* Reset alarm time and calendar. */
    alarm.u32Year       = RTC_YEAR2000;
    alarm.u32Month      = 0;
    alarm.u32Day        = 0;
    alarm.u32Hour       = 0;
    alarm.u32Minute     = 0;
    alarm.u32Second     = 0;
    alarm.u32TimeScale  = RTC_CLOCK_24;

    RTC_SetAlarmDateAndTime(&alarm);

    /* Reset alarm time mask and calendar mask. */
    RTC_SetAlarmDateMask(0, 0, 0, 0, 0, 0);
    RTC_SetAlarmTimeMask(0, 0, 0, 0, 0, 0);

    /* Clear alarm flag for safe */
    RTC_CLEAR_ALARM_INT_FLAG();
}
#endif

/* rtc device driver initialise. */
int rt_hw_rtc_init(void)
{
    rt_err_t ret;

    nu_rtc_init();

    /* register rtc device IO operations */
    device_rtc.type = RT_Device_Class_RTC;
    device_rtc.init = NULL;
    device_rtc.open = NULL;
    device_rtc.close = NULL;
    device_rtc.control = nu_rtc_control;
    device_rtc.read = NULL;
    device_rtc.write = NULL;

    device_rtc.user_data = RT_NULL;
    device_rtc.rx_indicate = RT_NULL;
    device_rtc.tx_complete = RT_NULL;

    ret = rt_device_register(&device_rtc, "rtc", RT_DEVICE_FLAG_RDWR);

    return (int)ret;
}
INIT_BOARD_EXPORT(rt_hw_rtc_init);

static rt_err_t nu_rtc_is_date_valid(const time_t t)
{
    static struct tm tm_upper = RTC_TM_UPPER_BOUND;
    static struct tm tm_lower = RTC_TM_LOWER_BOUND;
    static time_t t_upper, t_lower;
    static rt_bool_t initialised = RT_FALSE;

    if (!initialised)
    {
        t_upper = timegm((struct tm *)&tm_upper);
        t_lower = timegm((struct tm *)&tm_lower);
        initialised = RT_TRUE;
    }
    if ((t > t_upper) || (t < t_lower))
        return -(RT_EINVAL);

    return RT_EOK;
}

static rt_err_t nu_rtc_control(rt_device_t dev, int cmd, void *args)
{
    struct tm tm_out, tm_in;
    time_t *time;
    S_RTC_TIME_DATA_T hw_time;
#if defined(RT_USING_ALARM)

    struct rt_rtc_wkalarm *wkalarm;
    S_RTC_TIME_DATA_T hw_alarm;
#endif

    if ((dev == NULL) || (args == NULL))
        return -(RT_EINVAL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:

        time = (time_t *)args;
        RTC_GetDateAndTime(&hw_time);

        tm_out.tm_year = CONV_TO_TM_YEAR(hw_time.u32Year);
        tm_out.tm_mon = CONV_TO_TM_MON(hw_time.u32Month);
        tm_out.tm_mday = hw_time.u32Day;
        tm_out.tm_hour = hw_time.u32Hour;
        tm_out.tm_min = hw_time.u32Minute;
        tm_out.tm_sec = hw_time.u32Second;
        *time = timegm(&tm_out);
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:

        time = (time_t *) args;

        if (nu_rtc_is_date_valid(*time) != RT_EOK)
            return -(RT_ERROR);

        gmtime_r(time, &tm_in);
        hw_time.u32Year = CONV_FROM_TM_YEAR(tm_in.tm_year);
        hw_time.u32Month = CONV_FROM_TM_MON(tm_in.tm_mon);
        hw_time.u32Day = tm_in.tm_mday;
        hw_time.u32Hour = tm_in.tm_hour;
        hw_time.u32Minute = tm_in.tm_min;
        hw_time.u32Second = tm_in.tm_sec;
        hw_time.u32TimeScale = RTC_CLOCK_24;
        hw_time.u32AmPm = 0;

        RTC_SetDateAndTime(&hw_time);
        break;
#if defined(RT_USING_ALARM)
    case RT_DEVICE_CTRL_RTC_GET_ALARM:

        wkalarm = (struct rt_rtc_wkalarm *) args;
        RTC_GetAlarmDateAndTime(&hw_alarm);

        wkalarm->tm_hour = hw_alarm.u32Hour;
        wkalarm->tm_min = hw_alarm.u32Minute;
        wkalarm->tm_sec = hw_alarm.u32Second;
        break;

    case RT_DEVICE_CTRL_RTC_SET_ALARM:

        wkalarm = (struct rt_rtc_wkalarm *) args;
        hw_alarm.u32Hour = wkalarm->tm_hour;
        hw_alarm.u32Minute = wkalarm->tm_min;
        hw_alarm.u32Second = wkalarm->tm_sec;

        RTC_SetAlarmDateMask(1, 1, 1, 1, 1, 1);
        RTC_SetAlarmDateAndTime(&hw_alarm);
        break;

    default:
        return -(RT_EINVAL);
#endif
    }

    return RT_EOK;
}
/* rtc interrupt entry */
void RTC_IRQHandler(void)
{
    rt_interrupt_enter();

    if (RTC_GET_TICK_INT_FLAG())
    {
        RTC_CLEAR_TICK_INT_FLAG();
    }
#if defined(RT_USING_ALARM)

    if (RTC_GET_ALARM_INT_FLAG())
    {
        RTC_CLEAR_ALARM_INT_FLAG();

        /* Send an alarm event to notify rt-thread alarm service. */
        rt_alarm_update(&device_rtc, 0);
    }
#endif

    rt_interrupt_leave();
}
#endif //#if defined(BSP_USING_RTC)
