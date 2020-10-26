/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-10-23     yuzrain       the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <string.h>
#include "board.h"
#include "drv_rtc.h"

#ifdef RT_USING_RTC

/**
  * @brief Time structure
  */
typedef struct
{
    uint8_t hour;       /**< Hours */
    uint8_t minute;     /**< Minutes */
    uint8_t second;     /**< Seconds */
    uint16_t sub_sec;   /**< Sub-seconds */
} rtc_time_t;

/**
  * @brief Date structure
  */
typedef struct
{
    uint8_t week;   /**< Weeks */
    uint8_t day;    /**< days */
    uint8_t month;  /**< months */
    uint8_t year;   /**< years */
} rtc_date_t;

static rt_uint32_t bcd_to_dec(rt_uint32_t bcd)
{
    return ((bcd & 0xF) + ((bcd >> 4) & 0xF) * 10);
}

static void rtc_get_time(rtc_time_t *time)
{
    rt_uint32_t tmp = RTC->TIME;

    time->second = bcd_to_dec(tmp & 0x7F);
    time->minute = bcd_to_dec((tmp >> 8) & 0x7F);
    time->hour   = bcd_to_dec((tmp >> 16) & 0x7F);

    return;
}

static void rtc_get_date(rtc_date_t *date)
{
    uint32_t tmp = RTC->CAL;

    date->day   = bcd_to_dec(tmp & 0x3F);
    date->month = bcd_to_dec((tmp >> 8) & 0x1F);
    date->year  = bcd_to_dec((tmp >> 16) & 0xFF);
    date->week  = bcd_to_dec((RTC->TIME >> 24) & 0x7);

    return;
}

static rt_err_t es32f0_rtc_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    struct tm time_temp;
    struct tm *pNow;
    rt_uint16_t timout = 0xFFF;
    rtc_time_t *time = rt_malloc(sizeof(rtc_time_t));
    rtc_date_t *date = rt_malloc(sizeof(rtc_date_t));

    switch (cmd)
    {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
        {
            /* Wait RTC data ready then read */
            while ((--timout)&&((RTC->STAT & RTC_STAT_SYNDONE_MSK) != RTC_STAT_SYNDONE_MSK));
            if (timout == 0)
                result = RT_ERROR;
            /* Read */
            rtc_get_time(time);
            rtc_get_date(date);

            time_temp.tm_sec    = time->second;
            time_temp.tm_min    = time->minute;
            time_temp.tm_hour   = time->hour;
            time_temp.tm_wday   = date->week - 1;
            time_temp.tm_mday   = date->day;
            time_temp.tm_mon    = date->month - 1;
            time_temp.tm_year   = date->year - 1900 + 2000;
            *((time_t *)args) = mktime(&time_temp);
            break;
        }
        case RT_DEVICE_CTRL_RTC_SET_TIME:
        {
            rt_enter_critical();
            /* converts calendar time time into local time. */
            pNow = localtime((const time_t *)args);
            /* copy the statically located variable */
            memcpy(&time_temp, pNow, sizeof(struct tm));
            /* unlock scheduler. */
            rt_exit_critical();

            time->hour   = time_temp.tm_hour;
            time->minute = time_temp.tm_min;
            time->second = time_temp.tm_sec;
            date->year   = time_temp.tm_year + 1900 - 2000;
            date->month  = time_temp.tm_mon + 1;
            date->day    = time_temp.tm_mday;
            /* Stop RTC */
            CLEAR_BIT(RTC->CON, RTC_CON_RTCEN_MSK);
            WRITE_REG(RTC->TIME, ((time->hour/10)<<RTC_TIME_HOUR_T_POSS)  /* hour */
                                |((time->hour%10)<<RTC_TIME_HOUR_U_POSS)
                                |((time->minute/10)<<RTC_TIME_MIN_T_POSS)   /* minute */
                                |((time->minute%10)<<RTC_TIME_MIN_U_POSS)
                                |((time->second/10)<<RTC_TIME_SEC_T_POSS)   /* second */
                                |((time->second%10)<<RTC_TIME_SEC_U_POSS));
            WRITE_REG(RTC->CAL,  ((date->year/10)<<RTC_CAL_YEAR_T_POSS)   /* year */
                                |((date->year%10)<<RTC_CAL_YEAR_U_POSS)
                                |((date->month/10)<<RTC_CAL_MON_T_POS)     /* month */
                                |((date->month%10)<<RTC_CAL_MON_U_POSS)
                                |((date->day/10)<<RTC_CAL_DATE_T_POSS)   /* date */
                                |((date->day%10)<<RTC_CAL_DATE_U_POSS));
            /* start RTC */
            SET_BIT(RTC->CON, RTC_CON_RTCEN_MSK);
            break;
        }
        case RT_DEVICE_CTRL_RTC_GET_ALARM:
            break;

        case RT_DEVICE_CTRL_RTC_SET_ALARM:
            break;

        default:
            break;
    }

    rt_free(time);
    rt_free(date);

    return result;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops es32f0_rtc_ops =
{
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    RT_NULL,
    es32f0_rtc_control
};
#endif

static struct rt_device rtc_dev;
#define RTC_SOURCE_LOSC  0x1
#define RTC_SOURCE_LRC   0x2
int rt_hw_rtc_init(void)
{
    rt_err_t ret        = RT_EOK;
    rt_uint16_t timout   = 0xFFFF;
    rt_uint32_t rtc_clk = 32768-1;
    rt_uint8_t  rtc_src = RTC_SOURCE_LOSC;

    /*
     * Config RTC clock
     * We config the external 32.768K crystal as RTC clock source for the first
     * choice. If external 32.768K crystal is not ready, we will choose LRC.
     */
    /* Enable LOSC then wait it ready */
    if ((RCU->CON & RCU_CON_LOSCON_MSK) != RCU_CON_LOSCON_MSK)
        SET_BIT(RCU->CON, RCU_CON_LOSCON_MSK);

    /* Wait external 32.768K crystal ready */
    while (((RCU->CON & RCU_CON_LOSCRDY_MSK) != RCU_CON_LOSCRDY_MSK)&&(--timout));
    if (timout == 0)
    {
        /* We use LRC if external 32.768K crystal is not ready */
        if ((RCU->CON & RCU_CON_LRCON_MSK) != RCU_CON_LRCON_MSK)
            SET_BIT(RCU->CON, RCU_CON_LRCON_MSK);
        /* Wait LRC ready */
        timout = 0xFF;
        while (((RCU->CON & RCU_CON_LRCRDY_MSK) != RCU_CON_LRCRDY_MSK)&&(--timout));
        rtc_clk = 32000-1;
        rtc_src = RTC_SOURCE_LRC;
    }

    /* Open RTC clock */
    SET_BIT(RCU->AHBEN, RCU_AHBEN_RTCEN_MSK);

    /* Reset RTC */
    SET_BIT(RCU->AHBRST, RCU_AHBRST_RTCEN_MSK);
    CLEAR_BIT(RCU->AHBRST, RCU_AHBRST_RTCEN_MSK);
    CLEAR_BIT(RTC->CON, RTC_CON_RTCEN_MSK);

    /* Config RTC clock source */
    MODIFY_REG(RTC->CON, RTC_CON_CKSEL_MSK, rtc_src<<RTC_CON_CKSEL_POSS);
    MODIFY_REG(RTC->CON, RTC_CON_PSCALE_MSK|RTC_CON_SCALE_MSK,
                  ((rtc_clk&0x7F)<<RTC_CON_PSCALE_POSS)|
                  (((rtc_clk>>7)&0xFF)<<RTC_CON_SCALE_POSS));

    /* Set default time - Wed Oct 30 08:00:00 2019 */
    WRITE_REG(RTC->TIME, (0x3<<RTC_TIME_WEEK_POSS)    /* week */
                        |(0x0<<RTC_TIME_HOUR_T_POSS)  /* hour */
                        |(0x8<<RTC_TIME_HOUR_U_POSS)
                        |(0x0<<RTC_TIME_MIN_T_POSS)   /* minute */
                        |(0x0<<RTC_TIME_MIN_U_POSS)
                        |(0x0<<RTC_TIME_SEC_T_POSS)   /* second */
                        |(0x0<<RTC_TIME_SEC_U_POSS));
    WRITE_REG(RTC->CAL,  (0x1<<RTC_CAL_YEAR_T_POSS)   /* year */
                        |(0x9<<RTC_CAL_YEAR_U_POSS)
                        |(0x1<<RTC_CAL_MON_T_POS)     /* month */
                        |(0x0<<RTC_CAL_MON_U_POSS)
                        |(0x3<<RTC_CAL_DATE_T_POSS)   /* date */
                        |(0x0<<RTC_CAL_DATE_U_POSS));

    /* RTC start */
    SET_BIT(RTC->CON, RTC_CON_RTCEN_MSK);

    rtc_dev.type = RT_Device_Class_RTC;
    rtc_dev.rx_indicate = RT_NULL;
    rtc_dev.tx_complete = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    rtc_dev.ops = &es32f0_rtc_ops;
#else
    rtc_dev.init = RT_NULL;
    rtc_dev.open = RT_NULL;
    rtc_dev.close = RT_NULL;
    rtc_dev.read = RT_NULL;
    rtc_dev.write = RT_NULL;
    rtc_dev.control = es32f0_rtc_control;
#endif

    rtc_dev.user_data = RTC;

    ret = rt_device_register(&rtc_dev, "rtc", RT_DEVICE_FLAG_RDWR);

    return ret;
}
INIT_DEVICE_EXPORT(rt_hw_rtc_init);

#endif
