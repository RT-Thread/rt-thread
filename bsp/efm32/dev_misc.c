/******************************************************************//**
 * @file 		dev_misc.c
 * @brief 	Miscellaneous drivers of RT-Thread RTOS for EFM32
 * 	COPYRIGHT (C) 2011, RT-Thread Development Team
 * @author 	onelife
 * @version 	0.4 beta
 **********************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file LICENSE in this 
 * distribution or at http://www.rt-thread.org/license/LICENSE
 **********************************************************************
 * @section Change Logs
 * Date			Author		Notes
 * 2011-02-22	onelife		Initial creation for EFM32
 *********************************************************************/

/******************************************************************//**
 * @addtogroup efm32
 * @{
*********************************************************************/

/* Includes -------------------------------------------------------------------*/
#include "board.h"
#include "drv_adc.h"

/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
#ifdef RT_MISC_DEBUG
#define misc_debug(format,args...) 			rt_kprintf(format, ##args)
#else
#define misc_debug(format,args...)
#endif

/* Private constants -----------------------------------------------------------*/
static rt_device_t adc0;
static struct efm32_adc_control_t control = {ADC_MODE_SINGLE};

/* Private variables ------------------------------------------------------------*/
/* Private function prototypes ---------------------------------------------------*/
rt_int32_t efm32_misc_getCelsius(rt_uint32_t adcSample);

/* Private functions ------------------------------------------------------------*/
/******************************************************************//**
 * @brief
 *   Get current temperature value in degree celsius
 *
 * @details
 *
 * @note
 *
 * @return
 *   Temperature value (signed integer) in degree celsius times 100
 *
 *********************************************************************/
rt_int32_t rt_hw_get_temp(void)
{
	ADC_InitSingle_TypeDef 	singleInit = ADC_INITSINGLE_DEFAULT;
	rt_uint32_t 			temp;

	/* Set input to temperature sensor. Acquisition time must be 256 cycles. Reference must 
	    be 1.25V */
	singleInit.acqTime 		= adcAcqTime32;
	singleInit.reference 	= adcRef1V25;
	singleInit.input 		= adcSingleInpTemp;

	control.singleInit 		= &singleInit;
	adc0->control(adc0, RT_DEVICE_CTRL_ADC_MODE, &control);
	adc0->control(adc0, RT_DEVICE_CTRL_RESUME, EFM32_NO_POINTER);
	adc0->control(adc0, RT_DEVICE_CTRL_ADC_RESULT, &temp);

	return efm32_misc_getCelsius(temp);
}

/******************************************************************//**
 * @brief
 *   Get current VDD value in volt
 *
 * @details
 *
 * @note
 *
 * @return
 *   VDD value (unsigned integer) in volt times 100
 *
 *********************************************************************/
rt_uint32_t rt_hw_get_vdd(void)
{
	ADC_InitSingle_TypeDef 	singleInit = ADC_INITSINGLE_DEFAULT;
	rt_uint32_t 			vdd;

	/* Set input to temperature sensor. Reference must be 1.25V */
	singleInit.acqTime 		= adcAcqTime32;
	singleInit.reference 	= adcRef1V25;
	singleInit.input 		= adcSingleInpVDDDiv3;

	control.singleInit 		= &singleInit;
	adc0->control(adc0, RT_DEVICE_CTRL_ADC_MODE, &control);
	adc0->control(adc0, RT_DEVICE_CTRL_RESUME, EFM32_NO_POINTER);
	adc0->control(adc0, RT_DEVICE_CTRL_ADC_RESULT, &vdd);

	return (vdd * 125 * 3) / 4096;
}

/******************************************************************//**
 * @brief
 *   Initialize all the miscellaneous drivers
 *
 * @details
 *
 * @note
 *
 * @return
 *	 Error code
 *********************************************************************/
rt_err_t rt_hw_misc_init(void)
{
	adc0 = rt_device_find(RT_ADC0_NAME);
	if (adc0 == RT_NULL)
	{
		misc_debug("Batt err: Can't find device: %s!\n", RT_ADC0_NAME);
		goto MISC_INIT_ERROR;
	}
	return RT_EOK;

MISC_INIT_ERROR:
	misc_debug("Misc err: Init failed!\n");
	return -RT_ERROR;

}

/**************************************************************************//**
 * @brief 
 *   Convert ADC result to degree celsius.
 *
 * @details
 *
 * @note 
 *   See section 2.3.4 in the reference manual for details on this calculatoin
 *
 * @param adcResult 
 *   Raw value from ADC to be converted to celsius
 *
 * @return 
 *   The temperature value (signed integer) in degrees celsius times 100
 *
 *****************************************************************************/
rt_int32_t efm32_misc_getCelsius(rt_uint32_t adcResult)
{
	/* Factory calibration temperature from device information page. */
	rt_int32_t cal_temp 	= ((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK) \
								>> _DEVINFO_CAL_TEMP_SHIFT) * 100;

	/* Factory calibration value from device information page. */
	rt_int32_t cal_value	= ((DEVINFO->ADC0CAL2 & _DEVINFO_ADC0CAL2_TEMP1V25_MASK) \
								>> _DEVINFO_ADC0CAL2_TEMP1V25_SHIFT) * 10000;

	/* Temperature gradient (from datasheet) in (ADC unit / degree celsius * 100) */
	rt_int32_t t_grad 		= -385;

	return (cal_temp - (cal_value - (rt_int32_t)adcResult * 10000) / t_grad);
}

/*********************************************************************
* 	Export to FINSH
*********************************************************************/
#ifdef RT_USING_FINSH
#include <finsh.h>

void list_temp(void)
{
	rt_int32_t temp = rt_hw_get_temp();

	rt_kprintf("Temperature is %2d.%02d C\n", temp / 100, temp % 100);
}
FINSH_FUNCTION_EXPORT(list_temp, list current temperature value.)

void list_vdd(void)
{
	rt_uint32_t vdd = rt_hw_get_vdd();
	
	rt_kprintf("VDD is %1d.%02d V\n", vdd / 100, vdd % 100);
}
FINSH_FUNCTION_EXPORT(list_vdd, list current VDD value.)

#endif

/******************************************************************//**
 * @}
*********************************************************************/
