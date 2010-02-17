/*
 * File      : rtc.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

#include <rtthread.h>
#include <stm32f10x.h>

static struct rt_device rtc;
static rt_err_t rt_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    if (dev->rx_indicate != RT_NULL)
    {
        /* Open Interrupt */
    }

    return RT_EOK;
}

static rt_size_t rt_rtc_read(rt_device_t dev, rt_off_t pos, void* buffer, rt_size_t size)
{
    return 0;
}

static rt_err_t rt_rtc_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    rt_time_t *time;
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        time = (rt_time_t *)args;
        /* read device */
        *time = RTC_GetCounter();
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        time = (rt_time_t *)args;

        /* Enable PWR and BKP clocks */
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

        /* Allow access to BKP Domain */
        PWR_BackupAccessCmd(ENABLE);

        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();

        /* Change the current time */
        RTC_SetCounter(*time);

        /* Wait until last write operation on RTC registers has finished */
        RTC_WaitForLastTask();

        BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
    }
    break;
    }

    return RT_EOK;
}

/*******************************************************************************
* Function Name  : RTC_Configuration
* Description    : Configures the RTC.
* Input          : None
* Output         : None
* Return         : 0 reday,-1 error.
*******************************************************************************/
int RTC_Configuration(void)
{
    u32 count=0x200000;

    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset Backup Domain */
    BKP_DeInit();

    /* Enable LSE */
    RCC_LSEConfig(RCC_LSE_ON);
    /* Wait till LSE is ready */
    while ( (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET) && (--count) );
    if ( count == 0 )
    {
        return -1;
    }

    /* Select LSE as RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    /* Enable RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    return 0;
}

void rt_hw_rtc_init(void)
{
    rtc.type	= RT_Device_Class_RTC;

    if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
    {
        rt_kprintf("rtc is not configured\n");
        rt_kprintf("please configure with set_date and set_time\n");
        if ( RTC_Configuration() != 0)
        {
            rt_kprintf("rtc configure fail...\r\n");
            return ;
        }
    }
    else
    {
        /* Wait for RTC registers synchronization */
        RTC_WaitForSynchro();
    }

    /* register rtc device */
    rtc.init 	= RT_NULL;
    rtc.open 	= rt_rtc_open;
    rtc.close	= RT_NULL;
    rtc.read 	= rt_rtc_read;
    rtc.write	= RT_NULL;
    rtc.control = rt_rtc_control;

    /* no private */
    rtc.private = RT_NULL;

    rt_device_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);

    return;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <time.h>
time_t time(time_t* t)
{
    rt_device_t device;
    time_t time;

    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
        rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time);
        if (t != RT_NULL) *t = time;
    }

    return time;
}

void set_date(rt_uint32_t year, rt_uint32_t month, rt_uint32_t day)
{
    time_t now;
    struct tm* ti;
    rt_device_t device;

    ti = RT_NULL;
    /* get current time */
    time(&now);

    ti = localtime(&now);
    if (ti != RT_NULL)
    {
        ti->tm_year = year - 1900;
        ti->tm_mon 	= month - 1; /* ti->tm_mon 	= month; */
        ti->tm_mday = day;
    }

    now = mktime(ti);

    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
        rt_rtc_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &now);
    }
}
FINSH_FUNCTION_EXPORT(set_date, set date. e.g: set_date(2010,2,28))

void set_time(rt_uint32_t hour, rt_uint32_t minute, rt_uint32_t second)
{
    time_t now;
    struct tm* ti;
    rt_device_t device;

    ti = RT_NULL;
    /* get current time */
    time(&now);

    ti = localtime(&now);
    if (ti != RT_NULL)
    {
        ti->tm_hour = hour;
        ti->tm_min 	= minute;
        ti->tm_sec 	= second;
    }

    now = mktime(ti);
    device = rt_device_find("rtc");
    if (device != RT_NULL)
    {
        rt_rtc_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &now);
    }
}
FINSH_FUNCTION_EXPORT(set_time, set time. e.g: set_time(23,59,59))

void list_date()
{
    time_t now;

    time(&now);
    rt_kprintf("%s\n", ctime(&now));
}
FINSH_FUNCTION_EXPORT(list_date, show date and time.)
#endif
