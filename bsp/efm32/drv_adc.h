/******************************************************************//**
 * @file 		drv_adc.h
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
#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

/* Includes -------------------------------------------------------------------*/
/* Exported types -------------------------------------------------------------*/
struct efm32_adc_device_t
{
	ADC_TypeDef 			*adc_device;
	rt_uint32_t 			mode;
};

struct efm32_adc_control_t
{
	rt_uint32_t 			mode;
	ADC_InitSingle_TypeDef	*singleInit;
	ADC_InitScan_TypeDef 	*scanInit;
};

/* Exported constants ---------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
#define ADC_MODE_SINGLE 	0x00UL
#define ADC_MODE_SCAN 		0x01UL
#define ADC_MODE_TAILGATE	0x02UL

/* Exported functions --------------------------------------------------------- */
void rt_hw_adc_init(void);

#endif /*__DRV_ADC_H__ */
