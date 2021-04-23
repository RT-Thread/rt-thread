/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-12-12      Wayne        First version
*
******************************************************************************/
#include <rtconfig.h>

#if defined (BSP_USING_RTC)

#include <rtdevice.h>
#include <sys/time.h>
#include "NuMicro.h"
#include <drv_sys.h>

/* Private define ---------------------------------------------------------------*/

/* convert the real year and month value to the format of struct tm. */
#define CONV_TO_TM_YEAR(year)           ((year) - 1900)
#define CONV_TO_TM_MON(mon)             ((mon) - 1)

/* convert the tm_year and tm_mon from struct tm to the real value. */
#define CONV_FROM_TM_YEAR(tm_year)      ((tm_year) + 1900)
#define CONV_FROM_TM_MON(tm_mon)        ((tm_mon) + 1)

/* rtc date upper bound reaches the year of 2099. */
#define RTC_TM_UPPER_BOUND                                              \
{   .tm_year = CONV_TO_TM_YEAR(2099),                                   \
    .tm_mon  = CONV_TO_TM_MON(12),                                      \
    .tm_mday  = 31,                                                     \
    .tm_hour  = 23,                                                     \
    .tm_min = 59,                                                       \
    .tm_sec  = 59,                                                      \
}

/* rtc date lower bound reaches the year of 2000. */
#define RTC_TM_LOWER_BOUND                                              \
{   .tm_year = CONV_TO_TM_YEAR(2000),                                   \
    .tm_mon  = CONV_TO_TM_MON(1),                                       \
    .tm_mday  = 1,                                                      \
    .tm_hour  = 0,                                                      \
    .tm_min = 0,                                                        \
    .tm_sec  = 0,                                                       \
}

/* Private typedef --------------------------------------------------------------*/

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_rtc_control(rt_device_t dev, int cmd, void *args);

#if defined (NU_RTC_SUPPORT_IO_RW)
    static rt_size_t nu_rtc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
    static rt_size_t nu_rtc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
#endif

static rt_err_t nu_rtc_is_date_valid(const time_t *const t);
static void nu_rtc_init(void);

#if defined(RT_USING_ALARM)
    static void nu_rtc_alarm_reset(void);
    static void nu_rtc_isr(int vector, void *param);
#endif

/* Public functions -------------------------------------------------------------*/
#if defined (NU_RTC_SUPPORT_MSH_CMD)
    extern rt_err_t set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day);
    extern rt_err_t set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second);
#endif

/* Private variables ------------------------------------------------------------*/
static struct rt_device device_rtc;


static void nu_rtc_init(void)
{
    nu_sys_ipclk_enable(RTCCKEN);

    /* hw rtc initialise */
    RTC_Open(NULL);
    RTC_DisableInt(RTC_INTEN_ALMIEN_Msk | RTC_INTEN_TICKIEN_Msk);

#if defined(RT_USING_ALARM)

    nu_rtc_alarm_reset();
    RTC_EnableInt(RTC_INTEN_ALMIEN_Msk);

    rt_hw_interrupt_install(IRQ_RTC, nu_rtc_isr, &device_rtc, "rtc");
    rt_hw_interrupt_umask(IRQ_RTC);

#endif
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

#if defined (NU_RTC_SUPPORT_IO_RW)
    device_rtc.read = nu_rtc_read;
    device_rtc.write = nu_rtc_write;
#else
    device_rtc.read = NULL;
    device_rtc.write = NULL;
#endif

    device_rtc.user_data = RT_NULL;
    device_rtc.rx_indicate = RT_NULL;
    device_rtc.tx_complete = RT_NULL;

    ret = rt_device_register(&device_rtc, "rtc", RT_DEVICE_FLAG_RDWR);

    return (int)ret;
}
INIT_BOARD_EXPORT(rt_hw_rtc_init);


#if defined (NU_RTC_SUPPORT_IO_RW)
/* Register rt-thread device.read() entry. */
static rt_size_t nu_rtc_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    (void) pos;
    nu_rtc_control(dev, RT_DEVICE_CTRL_RTC_GET_TIME, buffer);

    return size;
}
#endif


#if defined (NU_RTC_SUPPORT_IO_RW)
/* Register rt-thread device.write() entry. */
static rt_size_t nu_rtc_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    (void) pos;
    nu_rtc_control(dev, RT_DEVICE_CTRL_RTC_SET_TIME, (void *)buffer);

    return size;
}
#endif


static rt_err_t nu_rtc_is_date_valid(const time_t *const t)
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

    /* check the date is supported by rtc. */
    if ((*t > t_upper) || (*t < t_lower))
        return -(RT_EINVAL);

    return RT_EOK;
}


/* Register rt-thread device.control() entry. */
static rt_err_t nu_rtc_control(rt_device_t dev, int cmd, void *args)
{
    struct tm tm_out, *tm_in;
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
        tm_in = gmtime(time);

        if (nu_rtc_is_date_valid(time) != RT_EOK)
            return -(RT_ERROR);

        hw_time.u32Year = CONV_FROM_TM_YEAR(tm_in->tm_year);
        hw_time.u32Month = CONV_FROM_TM_MON(tm_in->tm_mon);
        hw_time.u32Day = tm_in->tm_mday;
        hw_time.u32Hour = tm_in->tm_hour;
        hw_time.u32Minute = tm_in->tm_min;
        hw_time.u32Second = tm_in->tm_sec;
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

        RTC_SetAlarmDateAndTime(&hw_alarm);
        break;

    default:
        return -(RT_EINVAL);
#endif
    }

    return RT_EOK;
}


#if defined (NU_RTC_SUPPORT_MSH_CMD)

/* Support "rtc_det_date" command line in msh mode */
static rt_err_t msh_rtc_set_date(int argc, char **argv)
{
    rt_uint32_t index, len, arg[3];

    rt_memset(arg, 0, sizeof(arg));
    len = (argc >= 4) ? 4 : argc;

    /* The date information stored in argv is represented by the following order :
       argv[0,1,2,3] = [cmd, year, month, day] */
    for (index = 0; index < (len - 1); index ++)
    {
        arg[index] = atol(argv[index + 1]);
    }

    return set_date(arg[0], arg[1], arg[2]);
}
MSH_CMD_EXPORT_ALIAS(msh_rtc_set_date, rtc_set_date, e.g: rtc_set_date 2020 1 20);
#endif


#if defined (NU_RTC_SUPPORT_MSH_CMD)

/* Support "rtc_det_time" command line in msh mode */
static rt_err_t msh_rtc_set_time(int argc, char **argv)
{
    rt_uint32_t index, len, arg[3];

    rt_memset(arg, 0, sizeof(arg));
    len = (argc >= 4) ? 4 : argc;

    /* The time information stored in argv is represented by the following order :
       argv[0,1,2,3] = [cmd, hour, minute, second] */
    for (index = 0; index < (len - 1); index ++)
    {
        arg[index] = atol(argv[index + 1]);
    }

    return set_time(arg[0], arg[1], arg[2]);
}
MSH_CMD_EXPORT_ALIAS(msh_rtc_set_time, rtc_set_time, e.g: rtc_set_time 18 30 00);
#endif

#if defined(RT_USING_ALARM)
/* rtc interrupt entry */
static void nu_rtc_isr(int vector, void *param)
{
    if (RTC_GET_TICK_INT_FLAG())
    {
        RTC_CLEAR_TICK_INT_FLAG();
    }

    if (RTC_GET_ALARM_INT_FLAG())
    {
        RTC_CLEAR_ALARM_INT_FLAG();

        /* Send an alarm event to notify rt-thread alarm service. */
        rt_alarm_update(&device_rtc, (rt_uint32_t)NULL);
    }

}
#endif

#endif /* BSP_USING_RTC */

