/***************************************************************************//**
 * @file    drv_rtc.c
 * @brief   RTC driver of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author  Bernard, onelife
 * @version 0.4 beta
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 *  LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2009-01-05   Bernard     the first version
 * 2010-12-27   onelife     Modify for EFM32
 * 2011-06-16   onelife     Modify init function for efm32lib v2 upgrading
 * 2011-12-14   onelife     Move LFXO enabling routine to driver initialization
 *  function (board.c)
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "hdl_interrupt.h"
#include "drv_rtc.h"

#if defined(RT_USING_RTC)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef RT_RTC_DEBUG
#define rtc_debug(format,args...) 			rt_kprintf(format, ##args)
#else
#define rtc_debug(format,args...)
#endif

/* Private variables ---------------------------------------------------------*/
static struct rt_device rtc;
static rt_uint32_t rtc_time;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static rt_err_t rt_rtc_open(rt_device_t dev, rt_uint16_t oflag)
{
    if (dev->rx_indicate != RT_NULL)
    {
        /* Open Interrupt */
    }

    return RT_EOK;
}

static rt_size_t rt_rtc_read(
	rt_device_t 	dev,
	rt_off_t 		pos,
	void* 			buffer,
	rt_size_t 		size)
{
    return 0;
}

/***************************************************************************//**
 * @brief
 *  Configure RTC device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *  Pointer to device descriptor
 *
 * @param[in] cmd
 *  RTC control command
 *
 * @param[in] args
 *  Arguments
 *
 * @return
 *  Error code
 ******************************************************************************/
static rt_err_t rt_rtc_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_RTC_GET_TIME:
        *(rt_uint32_t *)args = rtc_time + RTC_CounterGet();
		rtc_debug("RTC: get rtc_time %x + %x\n", rtc_time, RTC_CounterGet());
        break;

    case RT_DEVICE_CTRL_RTC_SET_TIME:
    {
        rtc_time = *(rt_uint32_t *)args;
		rtc_debug("RTC: set rtc_time %x\n", rtc_time);

		/* Reset counter */
		RTC_CounterReset();
    }
    break;
    }

    return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *  RTC counter overflow interrupt handler
 *
 * @details
 *
 * @note
 ******************************************************************************/
void rt_hw_rtc_isr(rt_device_t device)
{
	if (RTC->IF & RTC_IFC_OF)
	{
		rtc_time += _RTC_CNT_MASK;
	}

	RTC->IFC = _RTC_IFC_MASK;
}

/***************************************************************************//**
 * @brief
 *  Register RTC device
 *
 * @details
 *
 * @note
 *
 * @param[in] device
 *  Pointer to device descriptor
 *
 * @param[in] name
 *  Device name
 *
 * @param[in] flag
 *  Configuration flags
 *
 * @return
 *  Error code
 ******************************************************************************/
rt_err_t rt_hw_rtc_register(
	rt_device_t		device,
	const char		*name,
	rt_uint32_t		flag)
{
	RT_ASSERT(device != RT_NULL);

	device->type 		= RT_Device_Class_RTC;
	device->rx_indicate = RT_NULL;
	device->tx_complete = RT_NULL;
	device->init 		= RT_NULL;
	device->open		= rt_rtc_open;
	device->close		= RT_NULL;
	device->read 		= rt_rtc_read;
	device->write 		= RT_NULL;
	device->control 	= rt_rtc_control;
	device->user_data	= RT_NULL; /* no private */

	/* register a character device */
	return rt_device_register(device, name, RT_DEVICE_FLAG_RDWR | flag);
}


/***************************************************************************//**
 * @brief
 *  Initialize all RTC module related hardware and register RTC device to kernel
 *
 * @details
 *
 * @note
 ******************************************************************************/
void rt_hw_rtc_init(void)
{
	rt_uint32_t reset;

	reset = RMU_ResetCauseGet();

	// TODO: What is the current reset mode?
	if (reset & RMU_RSTCAUSE_PORST || reset & RMU_RSTCAUSE_EXTRST)
    {
    	RTC_Init_TypeDef rtcInit;
		efm32_irq_hook_init_t hook;

		rtcInit.enable = true;
		rtcInit.debugRun = false;
		rtcInit.comp0Top = false;

		rtc_time = 0UL;

        rt_kprintf("rtc is not configured\n");
        rt_kprintf("please configure with set_date and set_time\n");

		/* Configuring clock */
        CMU_ClockDivSet(cmuClock_RTC,cmuClkDiv_32768);
        CMU_ClockEnable(cmuClock_RTC, true);

		/* Initialize and enable RTC */
		RTC_Reset();
		RTC_Init(&rtcInit);

		hook.type		= efm32_irq_type_rtc;
		hook.unit		= 0;
		hook.cbFunc 	= rt_hw_rtc_isr;
		hook.userPtr	= RT_NULL;
		efm32_irq_hook_register(&hook);

		/* Enabling Interrupt from RTC */
		RTC_IntEnable(RTC_IFC_OF);
		RTC_IntClear(RTC_IFC_OF);

		NVIC_ClearPendingIRQ(RTC_IRQn);
		NVIC_SetPriority(RTC_IRQn, EFM32_IRQ_PRI_DEFAULT);
		NVIC_EnableIRQ(RTC_IRQn);
    }

    /* register rtc device */
	rt_hw_rtc_register(&rtc, RT_RTC_NAME, EFM32_NO_DATA);
}

/***************************************************************************//**
 *  Export to FINSH
 ******************************************************************************/
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
	rtc_debug("RTC: Now %x\n", now);

    ti = localtime(&now);
    if (ti != RT_NULL)
    {
        ti->tm_hour = hour;
        ti->tm_min 	= minute;
        ti->tm_sec 	= second;
    }
	rtc_debug("RTC: DST %d\n", ti->tm_isdst);
	rtc_debug("RTC: Days in year %d\n", ti->tm_yday);
	rtc_debug("RTC: Day of week %d\n", ti->tm_wday);
	rtc_debug("RTC: Year %d\n", ti->tm_year);
	rtc_debug("RTC: Month %d\n", ti->tm_mon);
	rtc_debug("RTC: Day %d\n", ti->tm_mday);
	rtc_debug("RTC: Hour %d\n", ti->tm_hour);
	rtc_debug("RTC: Min %d\n", ti->tm_min);
	rtc_debug("RTC: Sec %d\n", ti->tm_sec);

    now = mktime(ti);
	rtc_debug("RTC: Now %x\n", now);
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

#endif

/***************************************************************************//**
 * @}
 ******************************************************************************/
