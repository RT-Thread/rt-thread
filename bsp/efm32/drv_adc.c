/******************************************************************//**
 * @file 		drv_adc.c
 * @brief 	ADC driver of RT-Thread RTOS for EFM32
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
 * 2011-02-21	onelife		Initial creation for EFM32
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
/* Private variables ------------------------------------------------------------*/
#ifdef RT_USING_ADC0
	static struct rt_device adc0_device;
#endif

/* Private function prototypes ---------------------------------------------------*/
rt_uint32_t efm32_adc_calibration(
	ADC_TypeDef 			*adc, 
	ADC_Ref_TypeDef			ref,
	ADC_SingleInput_TypeDef	input);

/* Private functions ------------------------------------------------------------*/
/******************************************************************//**
 * @brief
 *   Initialize ADC device
 *
 * @details
 *
 * @note
 *
 * @param[in] dev
 *   Pointer to device descriptor
 *
 * @return
 *   Error code
 *********************************************************************/
 static rt_err_t rt_adc_init(rt_device_t dev)
{
	RT_ASSERT(dev != RT_NULL);

	rt_uint32_t temp;
	
	struct efm32_adc_device_t *adc;

	adc = (struct efm32_adc_device_t *)(dev->user_data);

	temp = efm32_adc_calibration(adc->adc_device, ADC_INIT_REF, ADC_INIT_CH);

#ifdef RT_ADC_DEBUG
	rt_kprintf("adc->CAL = %x\n", temp);
#endif

	return RT_EOK;
}

/******************************************************************//**
* @brief
*	Configure ADC device
*
* @details
*
* @note
*
* @param[in] dev
*	Pointer to device descriptor
*
* @param[in] cmd
*	ADC control command
*
* @param[in] args
*	Arguments
*
* @return
*	Error code
*********************************************************************/
static rt_err_t rt_adc_control(
	rt_device_t 	dev, 
	rt_uint8_t 		cmd, 
	void 			*args)
{
	RT_ASSERT(dev != RT_NULL);

	struct efm32_adc_device_t *adc;

	adc = (struct efm32_adc_device_t *)(dev->user_data);

	switch (cmd)
	{
	case RT_DEVICE_CTRL_SUSPEND:
		/* Suspend device */
		dev->flag |= RT_DEVICE_FLAG_SUSPENDED;
		adc->adc_device->CMD = ADC_CMD_SINGLESTOP | ADC_CMD_SCANSTOP;
		break;

	case RT_DEVICE_CTRL_RESUME:
		/* Resume device */
		dev->flag &= ~RT_DEVICE_FLAG_SUSPENDED;
		
		switch (adc->mode)
		{
		case ADC_MODE_SINGLE:
			ADC_Start(adc->adc_device, adcStartSingle);
			break;
		
		case ADC_MODE_SCAN:
			ADC_Start(adc->adc_device, adcStartScan);
			break;
		
		case ADC_MODE_TAILGATE:
			ADC_Start(adc->adc_device, adcStartScanAndSingle);
			break;
		
		default:
			return -RT_ERROR;
		}
		break;

	case RT_DEVICE_CTRL_ADC_MODE:
		{
			/* change device setting */
			struct efm32_adc_control_t *control;

			control = (struct efm32_adc_control_t *)args;

			switch (control->mode)
			{
			case ADC_MODE_SINGLE:
				ADC_InitSingle(adc->adc_device, control->singleInit);
				break;

			case ADC_MODE_SCAN:
				ADC_InitScan(adc->adc_device, control->scanInit);
				break;

			case ADC_MODE_TAILGATE:
				ADC_InitSingle(adc->adc_device, control->singleInit);
				ADC_InitScan(adc->adc_device, control->scanInit);
				break;

			default:
				return -RT_ERROR;
			}

			adc->mode = control->mode;
		}
		break;
		
	case RT_DEVICE_CTRL_ADC_RESULT:
		switch (adc->mode)
		{
		case ADC_MODE_SINGLE:
			while (adc->adc_device->STATUS & ADC_STATUS_SINGLEACT);
			*((rt_uint32_t *)args) = ADC_DataSingleGet(adc->adc_device);
			break;

		case ADC_MODE_SCAN:
			while (adc->adc_device->STATUS & ADC_STATUS_SCANACT);
			*((rt_uint32_t *)args) = ADC_DataScanGet(adc->adc_device);
			break;

		case ADC_MODE_TAILGATE:
			while (adc->adc_device->STATUS & ADC_STATUS_SCANACT);
			*((rt_uint32_t *)args) = ADC_DataScanGet(adc->adc_device);
			
			while (adc->adc_device->STATUS & ADC_STATUS_SINGLEACT);
			*((rt_uint32_t *)args + 1) = ADC_DataSingleGet(adc->adc_device);
			break;

		default:
			return -RT_ERROR;
		}
		break;
	}

	return RT_EOK;
}

/******************************************************************//**
* @brief
*	Register ADC device
*
* @details
*
* @note
*
* @param[in] device
*	Pointer to device descriptor
*
* @param[in] name
*	Device name
*
* @param[in] flag
*	Configuration flags
*
* @param[in] adc
*	Pointer to ADC device descriptor 
*
* @return
*	Error code
*********************************************************************/
rt_err_t rt_hw_adc_register(
	rt_device_t		device, 
	const char		*name, 
	rt_uint32_t		flag, 
	struct efm32_adc_device_t *adc)
{
	RT_ASSERT(device != RT_NULL);

	device->type 		= RT_Device_Class_Char; /* fixme: should be adc type */
	device->rx_indicate = RT_NULL;
	device->tx_complete = RT_NULL;
	device->init 		= rt_adc_init;
	device->open		= RT_NULL;
	device->close		= RT_NULL;
	device->read 		= RT_NULL;
	device->write 		= RT_NULL;
	device->control 	= rt_adc_control;
	device->user_data	= adc;

	/* register a character device */
	return rt_device_register(device, name, flag);
}

/******************************************************************//**
* @brief
*	Initialize all ADC module related hardware and register ADC device to kernel
*
* @details
*
* @note
*
*********************************************************************/
void rt_hw_adc_init(void)
{
	struct efm32_adc_device_t 	*adc;
	ADC_Init_TypeDef 			init = ADC_INIT_DEFAULT;

	// TODO: Fixed oversampling rate?
	init.ovsRateSel	= adcOvsRateSel4096;
	init.timebase 	= ADC_TimebaseCalc(0);
	init.prescale 	= ADC_PrescaleCalc(ADC_CONVERT_FREQUENCY, 0);

	
#ifdef RT_USING_ADC0
	adc = rt_malloc(sizeof(struct efm32_adc_device_t));
	if (adc == RT_NULL)
	{
#ifdef RT_ADC_DEBUG
		rt_kprintf("no memory for ADC driver\n");
#endif
		return;
	}
	adc->adc_device	= ADC0;
	adc->mode 		= ADC_MODE_SINGLE;

	/* Enable clock for ADCn module */
	CMU_ClockEnable(cmuClock_ADC0, true);

	/* Reset */
	 ADC_Reset(ADC0);

	/* Configure ADC */
	ADC_Init(adc->adc_device, &init);

	rt_hw_adc_register(&adc0_device, RT_ADC0_NAME, EFM32_NO_DATA, adc);	
#endif
}


/***************************************************************************//**
 * @brief
 *   Calibrate offset and gain for the specified reference.
 *   Supports currently only single ended gain calibration.
 *   Could easily be expanded to support differential gain calibration.
 *
 * @details
 *   The offset calibration routine measures 0 V with the ADC, and adjust
 *   the calibration register until the converted value equals 0.
 *   The gain calibration routine needs an external reference voltage equal
 *   to the top value for the selected reference. For example if the 2.5 V
 *   reference is to be calibrated, the external supply must also equal 2.5V.
 *
 * @param[in] adc
 *   Pointer to ADC peripheral register block.
 *
 * @param[in] ref
 *   Reference used during calibration. Can be both external and internal
 *   references.
 *
 * @param[in] input
 *   Input channel used during calibration.
 *
 * @return
 *   The final value of the calibration register, note that the calibration
 *   register gets updated with this value during the calibration.
 *   No need to load the calibration values after the function returns.
 ******************************************************************************/
rt_uint32_t efm32_adc_calibration(
	ADC_TypeDef 			*adc, 
	ADC_Ref_TypeDef			ref,
	ADC_SingleInput_TypeDef	input)
{
	rt_uint32_t 	cal;
	rt_int32_t 		sample;
	rt_int8_t 		high, mid, low, tmp;
	ADC_InitSingle_TypeDef singleInit 	= ADC_INITSINGLE_DEFAULT;

	/* Init for single conversion use, measure diff 0 with selected reference. */
	singleInit.reference 	= ref;
	singleInit.input 		= adcSingleInpDiff0;
	singleInit.acqTime 		= adcAcqTime32;
	singleInit.diff 		= true;
	/* Enable oversampling rate */
	singleInit.resolution	= adcResOVS;
	ADC_InitSingle(adc, &singleInit);

	/* ADC is now set up for offset calibration */
	/* Offset calibration register is a 7 bit signed 2's complement value. */
	/* Use unsigned indexes for binary search, and convert when calibration */
	/* register is written to. */
	high = 63;
	low = -64;

	/* Do binary search for offset calibration*/
	while (low < high)
	{
		/* Calculate midpoint */
		mid = low + (high - low) / 2;

		/* Midpoint is converted to 2's complement and written to both scan and */
		/* single calibration registers */
		cal = adc->CAL & ~(_ADC_CAL_SINGLEOFFSET_MASK | _ADC_CAL_SCANOFFSET_MASK);
		tmp = mid < 0 ? (mid & 0x3F ^ 0x3F | 0x40) + 1 : mid;
		cal |= tmp << _ADC_CAL_SINGLEOFFSET_SHIFT;
		cal |= tmp << _ADC_CAL_SCANOFFSET_SHIFT;
#ifdef RT_ADC_DEBUG
		rt_kprintf("adc->CAL = %x, cal = %x, tmp = %x\n", adc->CAL, cal, tmp);
#endif			
		adc->CAL = cal;

		/* Do a conversion */
		ADC_Start(adc, adcStartSingle);

		/* Wait while conversion is active */
		while (adc->STATUS & ADC_STATUS_SINGLEACT) ;

		/* Get ADC result */
		sample = ADC_DataSingleGet(adc);

		/* Check result and decide in which part of to repeat search */
		/* Calibration register has negative effect on result */
		if (sample < 0)
		{
			/* Repeat search in bottom half. */
			high = mid;
		}
		else if (sample > 0)
		{
			/* Repeat search in top half. */
			low = mid + 1;
		}
		else
		{
			/* Found it, exit while loop */
			break;
		}
	}
#ifdef RT_ADC_DEBUG
	rt_kprintf("adc->CAL = %x\n", adc->CAL);
#endif

	/* Now do gain calibration, only input and diff settings needs to be changed */
	adc->SINGLECTRL &= ~(_ADC_SINGLECTRL_INPUTSEL_MASK | _ADC_SINGLECTRL_DIFF_MASK);
	adc->SINGLECTRL |= (input << _ADC_SINGLECTRL_INPUTSEL_SHIFT);
	adc->SINGLECTRL |= (false << _ADC_SINGLECTRL_DIFF_SHIFT);

	/* ADC is now set up for gain calibration */
	/* Gain calibration register is a 7 bit unsigned value. */
	high = 127;
	low = 0;

	/* Do binary search for gain calibration */
	while (low < high)
	{
		/* Calculate midpoint and write to calibration register */
		mid = low + (high - low) / 2;

		/* Midpoint is converted to 2's complement */
		cal      = adc->CAL & ~(_ADC_CAL_SINGLEGAIN_MASK | _ADC_CAL_SCANGAIN_MASK);
		cal     |= mid << _ADC_CAL_SINGLEGAIN_SHIFT;
		cal     |= mid << _ADC_CAL_SCANGAIN_SHIFT;
#ifdef RT_ADC_DEBUG
		rt_kprintf("adc->CAL = %x, cal = %x, mid = %x\n", adc->CAL, cal, mid);
#endif		
		adc->CAL = cal;

		/* Do a conversion */
		ADC_Start(adc, adcStartSingle);

		/* Wait while conversion is active */
		while (adc->STATUS & ADC_STATUS_SINGLEACT) ;

		/* Get ADC result */
		sample = ADC_DataSingleGet(adc);

		/* Check result and decide in which part to repeat search */
		/* Compare with a value atleast one LSB's less than top to avoid overshooting */
		/* Since oversampling is used, the result is 16 bits, but a couple of lsb's */
		/* applies to the 12 bit result value, if 0xffe is the top value in 12 bit, this */
		/* is in turn 0xffe0 in the 16 bit result. */
		/* Calibration register has positive effect on result */
		if (sample > 0xffd0)
		{
		  /* Repeat search in bottom half. */
		  high = mid;
		}
		else if (sample < 0xffd0)
		{
		  /* Repeat search in top half. */
		  low = mid + 1;
		}
		else
		{
		  /* Found it, exit while loop */
		  break;
		}
	}
#ifdef RT_ADC_DEBUG
	rt_kprintf("adc->CAL = %x\n", adc->CAL);
#endif

	return adc->CAL;
}

/******************************************************************//**
 * @}
*********************************************************************/
