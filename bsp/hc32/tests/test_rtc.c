/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单：这是 RTC 设备使用例程和 Alarm 使用示例。
 * 例程导出了 rtc_sample 命令到控制终端。
 * 命令调用格式：rtc_sample x
 * 命令解释：命令第二个参数是要使用的功能对应的编号，
 *           RTC 基本功能对应的编号为 0~3，Alarm 功能对应的编号为 4~9
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include "rtconfig.h"
#include "rtdef.h"
// #include "alarm.h"

#if defined(BSP_USING_RTC)

/* macros define */
#define SAMPLE_RTC_NAME         "rtc"

/* variables define */
static rt_device_t rtc_dev;
#if defined(RT_USING_ALARM)
    extern void rt_alarm_dump(void);

    static rt_uint16_t callback_counter, alarm_idx = 0;
    static struct rt_alarm *ptr_alarm = RT_NULL;
    static struct rt_alarm_setup alarm_setup;
#endif /* RT_USING_ALARM */

/* command type */
enum RTC_CMD
{
    CMD_OPEN_RTC        = 0x00,
    CMD_SET_TIME        = 0x01,
    CMD_SET_DATE        = 0x02,
    CMD_GET_DATE_TIME,
#if defined(RT_USING_ALARM)
    CMD_SET_ALARM,
    CMD_SET_START_ALARM,
    CMD_STOP_ALARM,
    CMD_CTRL_ALARM,
    CMD_DUMP_ALARM,
    CMD_DEL_ALARM,
};

void alarm_callback_fun(rt_alarm_t alarm, time_t timestamp)
{
    rt_kprintf("\nuser alarm %d callback function.\n", alarm_idx);
    if ((0 == (--callback_counter)) && (alarm_idx))
    {
        rt_kprintf("stop alarm %d \n", alarm_idx);
        if (RT_EOK != rt_alarm_stop(alarm))
        {
            rt_kprintf("failed to stop alarm\n");
        }
        /* enter callback 2 times */
        callback_counter = 2;
        --alarm_idx;
    }
}
#else
};
#endif /* RT_USING_ALARM */

static int rtc_sample(int argc, char *argv[])
{
    rt_uint8_t idx;
    rt_uint16_t temp1, temp2, temp3;
    time_t now;
#if defined(RT_USING_ALARM)
    struct tm p_tm;
#endif

    if (argc < 2)
    {
        rt_kprintf("unkown rtc command, rtc [usage] as the following: \n");
        rt_kprintf("\'0\': find and open rtc \n");
        rt_kprintf("\'1 xx:xx:xx\': set time with \n");
        rt_kprintf("\'2 xxxx-xx-xx\': set date with \n");
        rt_kprintf("\'3\': get time and date \n");
#if defined(RT_USING_ALARM)
        rt_kprintf("\'4\': set current time + 10s as alarm \n");
        rt_kprintf("\'5\': start alarm \n");
        rt_kprintf("\'6\': stop alarm \n");
        rt_kprintf("cmd-7 based on cmd-4\n");
        rt_kprintf("\'7\' o: oneshot,\n\'7\' s: second,\n\'7\' m: minute \n");
        rt_kprintf("\'8\': dump all alarm \n");
        rt_kprintf("\'9\': delete all alarm \n");
#endif /* RT_USING_ALARM */
        return -RT_ERROR;
    }

    idx = *(argv[1]) - '0';
    switch (idx)
    {
    case CMD_OPEN_RTC:
        /* find and open device with standard interface */
        rtc_dev = rt_device_find(SAMPLE_RTC_NAME);
        if (!rtc_dev)
        {
            rt_kprintf("find %s failed\n", SAMPLE_RTC_NAME);
            return -RT_ERROR;
        }
        if (RT_EOK != rt_device_open(rtc_dev, RT_NULL))
        {
            rt_kprintf("failed to open %s\n", SAMPLE_RTC_NAME);
            return -RT_ERROR;
        }
        rt_kprintf("rtc opened\n");
        break;
    case CMD_SET_TIME:
        /* set time with xx:xx:xx format characters */
        if (argc < 3)
        {
            rt_kprintf("unsurpported command\n");
            return -RT_ERROR;
        }
        temp1 = ((argv[2][0] - '0') * 10) + \
                (argv[2][1] - '0');
        temp2 = ((argv[2][3] - '0') * 10) + \
                (argv[2][4] - '0');
        temp3 = ((argv[2][6] - '0') * 10) + \
                (argv[2][7] - '0');
        if (RT_EOK != set_time(temp1, temp2, temp3))
        {
            rt_kprintf("set RTC time failed\n");
            return -RT_ERROR;
        }
        rt_kprintf("\nset RTC time as %2d:%2d:%2d\n", temp1, temp2, temp3);
        break;
    case CMD_SET_DATE:
        /* set data xxxx-xx-xx format characters */
        temp1 = ((argv[2][0] - '0') * 1000) + \
                ((argv[2][1] - '0') * 100) + \
                ((argv[2][2] - '0') * 10) + \
                (argv[2][3] - '0');
        temp2 = ((argv[2][5] - '0') * 10) + \
                (argv[2][6] - '0');
        temp3 = ((argv[2][8] - '0') * 10) + \
                (argv[2][9] - '0');
        if (RT_EOK != set_date(temp1, temp2, temp3))
        {
            rt_kprintf("failed to set date for %s\n", SAMPLE_RTC_NAME);
            return -RT_ERROR;
        }
        rt_kprintf("\nset RTC date as %4d-%2d-%2d\n", temp1, temp2, temp3);
        break;
    case CMD_GET_DATE_TIME:
        /* get current time and print it */
        now = time(NULL);
        rt_kprintf("GMT  time is: %s\n", ctime(&now));
        break;
#if defined(RT_USING_ALARM)
    case CMD_SET_ALARM:
        /* get current time (uint: second) from 1970-01-01 */
        now = time(NULL);
        rt_kprintf("GMT  time is: \n%s\n", ctime(&now));
        now += 60;
        gmtime_r(&now, &p_tm);
        // localtime_r(&now, &p_tm);
        alarm_setup.flag = RT_ALARM_MINUTE;
        alarm_setup.wktime.tm_year = p_tm.tm_year;
        alarm_setup.wktime.tm_mon = p_tm.tm_mon;
        alarm_setup.wktime.tm_mday = p_tm.tm_mday;
        alarm_setup.wktime.tm_yday = p_tm.tm_yday;
        alarm_setup.wktime.tm_wday = p_tm.tm_wday;
        alarm_setup.wktime.tm_hour = p_tm.tm_hour;
        alarm_setup.wktime.tm_min = p_tm.tm_min;
        alarm_setup.wktime.tm_sec = p_tm.tm_sec;
        alarm_setup.wktime.tm_isdst = -1;
        rt_kprintf("UTC alarm Time: \n%d-%02d-%02d %02d:%02d:%02d\n\n",
                   p_tm.tm_year + 1900,
                   p_tm.tm_mon + 1,
                   p_tm.tm_mday,
                   p_tm.tm_hour,
                   p_tm.tm_min,
                   p_tm.tm_sec);
        ptr_alarm = rt_alarm_create(alarm_callback_fun, &alarm_setup);
        if (RT_NULL == ptr_alarm)
        {
            rt_kprintf("failed to create rtc alarm\n");
            return -RT_ERROR;
        }
        callback_counter = 2;
        ++alarm_idx;
        rt_alarm_dump();
        break;
    case CMD_SET_START_ALARM:
        if (RT_EOK != rt_alarm_start(ptr_alarm))
        {
            rt_kprintf("failed to start rtc alarm\n");
            return -RT_ERROR;
        }
        rt_kprintf("rtc alarm started\n");
        break;
    case CMD_STOP_ALARM:
        if (RT_EOK != rt_alarm_stop(ptr_alarm))
        {
            rt_kprintf("failed to stop rtc alarm\n");
            return -RT_ERROR;
        }
        rt_kprintf("rtc alarm stopped\n");
        break;
    case CMD_CTRL_ALARM:
        if (argc < 3)
        {
            rt_kprintf("unkown para to control rtc alarm\n");
            return -RT_ERROR;
        }
        switch (argv[2][0])
        {
        case 's':
            alarm_setup.flag = RT_ALARM_SECOND;
            break;
        case 'm':
            alarm_setup.flag = RT_ALARM_MINUTE;
            break;
        case 'o':
        default:
            alarm_setup.flag = RT_ALARM_ONESHOT;
            break;
        }
        if (RT_EOK != rt_alarm_control(ptr_alarm, RT_ALARM_CTRL_MODIFY, &alarm_setup))
        {
            rt_kprintf("failed to control rtc alarm\n");
        }
        rt_alarm_dump();
        break;
    case CMD_DUMP_ALARM:
        rt_alarm_dump();
        break;
    case CMD_DEL_ALARM:
        if (RT_EOK != rt_alarm_delete(ptr_alarm))
        {
            rt_kprintf("failed to delete alarm\n");
        }
        alarm_idx = 0;
        rt_kprintf("alarm deleted\n");
        break;
#endif /* RT_USING_ALARM */
    default:
        if (RT_EOK != rt_device_close(rtc_dev))
        {
            rt_kprintf("failed to close RTC\n");
            return -RT_ERROR;
        }
        rt_kprintf("unkown rtc command, rtc closed \n");
        break;
    }
    /* fetch and print current time and date each second until next year */
    return RT_EOK;
}

MSH_CMD_EXPORT(rtc_sample, rtc option);

#endif /* BSP_USING_RTC */

/*
 EOF
*/
