/***************************************************************************//**
 * @file 	dev_accel.c
 * @brief 	Accelerometer driver of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	onelife
 * @version 0.4 beta
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file 
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2011-07-13	onelife		Initial creation for using EFM32 ADC module to 
 *  interface the Freescale MMA7361L
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup efm32
 * @{
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "drv_adc.h"
#include "dev_accel.h"

#if defined(EFM32_USING_ACCEL)
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#ifdef RT_ACCEL_DEBUG
#define accel_debug(format,args...) 		rt_kprintf(format, ##args)
#else
#define accel_debug(format,args...)
#endif

/* Private constants ---------------------------------------------------------*/
static rt_device_t 					accel;
static struct efm32_adc_control_t 	control = \
	{ADC_MODE_SCAN, {3, ACCEL_USING_DMA}, {}};
static struct efm32_accel_result_t 	accelOffset = {0};
static rt_bool_t 					accelInTime = true;

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/***************************************************************************//**
 * @brief
 *   Get accelerometer output
 *
 * @details
 *
 * @note
 *
 * @param[out] data
 *	Pointer to output buffer
 *
 * @return
 *	 Error code
 ******************************************************************************/
rt_err_t efm_accel_get_data(struct efm32_accel_result_t *data)
{
	RT_ASSERT(accel != RT_NULL);

	struct efm32_adc_result_t result;

	if (data == RT_NULL)
	{
		return -RT_ERROR;
	}

	result.mode = control.mode;
	result.buffer = (void *)data;
	accel->control(accel, RT_DEVICE_CTRL_RESUME, &result);
	accel->control(accel, RT_DEVICE_CTRL_ADC_RESULT, &result);

	return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Accelerometer timeout interrupt handler
 *
 * @details
 *
 * @note
 *
 * @param[in] parameter
 *	Parameter
 ******************************************************************************/
static void efm_accel_timer(void* parameter)
{
	accelInTime = false;
}

/***************************************************************************//**
 * @brief
 *   Accelerometer auto-zero calibration function
 *
 * @details
 *
 * @note
 *
 * @param[in] period
 *	Time period to perform auto-zero calibration
 *
 * @return
 *	 Error code
 ******************************************************************************/
rt_err_t efm_accel_auto_zero(rt_tick_t period)
{
	RT_ASSERT(accel != RT_NULL);

	rt_timer_t calTimer;
	struct efm32_accel_result_t min = {0x7ff, 0x7ff, 0x7ff};
	struct efm32_accel_result_t max = {0x7ff, 0x7ff, 0x7ff};
	struct efm32_accel_result_t temp;
	struct efm32_adc_result_t result;

	if ((calTimer = rt_timer_create(
		"cal_tmr",
		efm_accel_timer,
		RT_NULL,
		period, 
		RT_TIMER_FLAG_ONE_SHOT)) == RT_NULL)
	{
		accel_debug("Accel err: Create timer failed!\n");
		return -RT_ERROR;
	}

	result.mode = control.mode;
	result.buffer = (void *)&temp;
	accelInTime = true;
	rt_timer_start(calTimer);
	do
	{
		accel->control(accel, RT_DEVICE_CTRL_RESUME, &result);
		accel->control(accel, RT_DEVICE_CTRL_ADC_RESULT, &result);
		if (temp.x < min.x)
		{
			min.x = temp.x;
		}
		if (temp.y < min.y)
		{
			min.y = temp.y;
		}
		if (temp.z < min.z)
		{
			min.z = temp.z;
		}
		if (temp.x > max.x)
		{
			max.x = temp.x;
		}
		if (temp.y > max.y)
		{
			max.y = temp.y;
		}
		if (temp.z > max.z)
		{
			max.z = temp.z;
		}
		rt_thread_sleep(1);
	} while (accelInTime);

	accelOffset.x = (min.x + max.x) >> 1;
	accelOffset.y = (min.y + max.y) >> 1;
	accelOffset.z = (min.z + max.z) >> 1;
	accel_debug("Accel: Min %x %x %x, max %x %x %x, Offset %x %x %x\n", 
		min.x, min.y, min.z, max.x,	max.y, max.z, 
		accelOffset.x, accelOffset.y, accelOffset.z);

	rt_timer_delete(calTimer);
	return RT_EOK;
}

/***************************************************************************//**
 * @brief
 *   Initialize the accelerometer
 *
 * @details
 *
 * @note
 *
 * @return
 *	 Error code
 ******************************************************************************/
rt_err_t efm_accel_init(void)
{
	ADC_InitScan_TypeDef scanInit = ADC_INITSCAN_DEFAULT;

#if defined(EFM32_G290_DK)
	/* Enable accelerometer */
	DVK_enablePeripheral(DVK_ACCEL);
	/* Select low g-range */
	DVK_disablePeripheral(DVK_ACCEL_GSEL);
#endif

	do
	{
		/* Find ADC device */
		accel = rt_device_find(ACCEL_USING_DEVICE_NAME);
		if (accel == RT_NULL)
		{
			accel_debug("Accel err: Can't find device: %s!\n", ACCEL_USING_DEVICE_NAME);
			break;
		}
		accel_debug("Accel: Find device %s\n", ACCEL_USING_DEVICE_NAME);

		/* Init ADC for scan mode */
		scanInit.reference = adcRefVDD;
		scanInit.input = ACCEL_X_ADC_CH | ACCEL_Y_ADC_CH | ACCEL_Z_ADC_CH;

		control.scan.init = &scanInit;
		accel->control(accel, RT_DEVICE_CTRL_ADC_MODE, &control);

		accel_debug("Accel: Init OK\n");
		return RT_EOK;
	} while (0);

	accel_debug("Accel err: Init failed!\n");
	return -RT_ERROR;
}

/*******************************************************************************
 * 	Export to FINSH
 ******************************************************************************/
#ifdef RT_USING_FINSH
#include <finsh.h>

void accel_cal(rt_uint32_t second)
{
	efm_accel_auto_zero(RT_TICK_PER_SECOND * second);

	rt_kprintf("Calibration done. Offset: 0x%03x, 0x%03x, 0x%03x\n", 
		accelOffset.x, accelOffset.y, accelOffset.z);
}
FINSH_FUNCTION_EXPORT(accel_cal, auto-zero calibration.)

void list_accel(void)
{
	struct efm32_accel_result_t temp;
	rt_int32_t x, y, z;

	if ((accelOffset.x == 0) && \
		(accelOffset.y == 0) && \
		(accelOffset.z == 0))
	{
		rt_kprintf("Please calibrate the device first!\n");
		return;
	}
	efm_accel_get_data(&temp);
	x = temp.x - accelOffset.x;
	y = temp.y - accelOffset.y;
	z = temp.z - accelOffset.z;
	
	rt_kprintf("X: %d, Y: %d, Z: %d\n", x, y, z);
}
FINSH_FUNCTION_EXPORT(list_accel, list accelerometer info.)
#endif

#endif
/***************************************************************************//**
 * @}
 ******************************************************************************/
