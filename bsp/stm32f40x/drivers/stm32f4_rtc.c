/*
 * File      : stm32f4_rtc.c
 * This file is stm32f4 rtc driver part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-09-29     FlyM	       the first version.
 */
#include <time.h>
#include <rtthread.h>
#include <stm32f4xx.h>
#include "stm32f4_rtc.h"

static int get_week(int year, int month, int day)
{
	if (month==1||month==2)
	{
		year -=1;
		month +=12;
	}
	return (day+1+2*month+3*(month+1)/5+year+(year/4)-year/100+year/400)%7;
}

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
		{
			struct tm ct;
			RTC_TimeTypeDef	t;
			RTC_DateTypeDef	d;

			rt_memset(&ct,0,sizeof(struct tm));
			time = (rt_time_t *)args;
			/* read device */
			RTC_GetDate(RTC_Format_BIN,&d);
			RTC_GetTime(RTC_Format_BIN,&t);

			ct.tm_year = d.RTC_Year + 100;
			ct.tm_mon = d.RTC_Month - 1;
			ct.tm_mday = d.RTC_Date;
			ct.tm_wday = d.RTC_WeekDay;

			ct.tm_hour = t.RTC_Hours;
			ct.tm_min = t.RTC_Minutes;
			ct.tm_sec = t.RTC_Seconds;

			*time = mktime(&ct);
		}
		break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
		struct tm *ct;
		struct tm tm_new;
		time_t *time;
		RTC_TimeTypeDef  RTC_TimeStructure;
		RTC_InitTypeDef  RTC_InitStructure;
		RTC_DateTypeDef  RTC_DateStructure;

        time = (time_t *)args;
		/* lock scheduler. */
		rt_enter_critical();
		/* converts calendar time time into local time. */
		ct = localtime(time);
		/* copy the statically located variable */
		rt_memcpy(&tm_new, ct, sizeof(struct tm));
		/* unlock scheduler. */
		rt_exit_critical();		
		/* Enable the PWR clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
		/* Allow access to RTC */
		PWR_BackupAccessCmd(ENABLE);
		/* ck_spre(1Hz) = RTCCLK(LSI) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
		//uwSynchPrediv = 0xFF;
		//uwAsynchPrediv = 0x7F;
		/* Configure the RTC data register and RTC prescaler */
		RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
		RTC_InitStructure.RTC_SynchPrediv = 0xFF;
		RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
		RTC_Init(&RTC_InitStructure);
		/* Set the date */
		RTC_DateStructure.RTC_Year = tm_new.tm_year - 100;
		RTC_DateStructure.RTC_Month = tm_new.tm_mon + 1;
		RTC_DateStructure.RTC_Date = tm_new.tm_mday;
		RTC_DateStructure.RTC_WeekDay = get_week(tm_new.tm_year+1900,tm_new.tm_mon+1,tm_new.tm_mday);
		RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
		/* Set the time*/
		if (tm_new.tm_hour > 11)
		{
			RTC_TimeStructure.RTC_H12 = RTC_H12_PM;
		}
		else
		{
			RTC_TimeStructure.RTC_H12 = RTC_H12_AM;
		}		
		RTC_TimeStructure.RTC_Hours   = tm_new.tm_hour;
		RTC_TimeStructure.RTC_Minutes = tm_new.tm_min;
		RTC_TimeStructure.RTC_Seconds = tm_new.tm_sec; 

		RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure); 		

		/* Indicator for the RTC configuration */
		RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);        
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
	/* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

	/* Allow access to RTC */
	PWR_BackupAccessCmd(ENABLE);

#if defined (RTC_CLOCK_SOURCE_LSI)  /* LSI used as RTC source clock*/
	/* The RTC Clock may varies due to LSI frequency dispersion */   
	/* Enable the LSI OSC */ 
	RCC_LSICmd(ENABLE);

	/* Wait till LSI is ready */  
	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{
	}

	/* Select the RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

	/* ck_spre(1Hz) = RTCCLK(LSI) /(uwAsynchPrediv + 1)*(uwSynchPrediv + 1)*/
	//uwSynchPrediv = 0xFF;
	//uwAsynchPrediv = 0x7F;

#elif defined (RTC_CLOCK_SOURCE_LSE) /* LSE used as RTC source clock */
	/* Enable the LSE OSC */
	RCC_LSEConfig(RCC_LSE_ON);

	/* Wait till LSE is ready */  
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{
	}
	/* Select the RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

#else
#error Please select the RTC Clock source inside the main.c file
#endif /* RTC_CLOCK_SOURCE_LSI */

	/* Enable the RTC Clock */
	RCC_RTCCLKCmd(ENABLE);

	/* Wait for RTC APB registers synchronisation */
	RTC_WaitForSynchro();

	return 0;
}

void rt_hw_rtc_init(void)
{
    rtc.type	= RT_Device_Class_RTC;

    if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x32F2)
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
    rtc.user_data = RT_NULL;

    rt_device_register(&rtc, "rtc", RT_DEVICE_FLAG_RDWR);

    return;
}

#ifdef RT_USING_FINSH
#include "finsh.h"
void show_time(void)
{
	RTC_TimeTypeDef	t;
	RTC_DateTypeDef	d;
	/* Get the current Date */
	RTC_GetDate(RTC_Format_BIN,&d);
	/* Get the current Time */
	RTC_GetTime(RTC_Format_BIN, &t);
	/* Display time Format : hh:mm:ss */
	rt_kprintf("Now Time = 20%02d %02d %02d[%02d]-%0.2d:%0.2d:%0.2d \r\n", \
		d.RTC_Year,d.RTC_Month,d.RTC_Date,d.RTC_WeekDay,t.RTC_Hours, t.RTC_Minutes, t.RTC_Seconds);
}

FINSH_FUNCTION_EXPORT(show_time, show current time.)
#endif


