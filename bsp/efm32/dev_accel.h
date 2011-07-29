/***************************************************************************//**
 * @file 	dev_accel.h
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
#ifndef __DEV_ACCEL_H__
#define __DEV_ACCEL_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct efm32_accel_result_t
{
	rt_uint32_t 			x;
	rt_uint32_t 			y;
	rt_uint32_t 			z;
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define ACCEL_X_ADC_CH 		ADC_SCANCTRL_INPUTMASK_CH2
#define ACCEL_Y_ADC_CH 		ADC_SCANCTRL_INPUTMASK_CH3
#define ACCEL_Z_ADC_CH 		ADC_SCANCTRL_INPUTMASK_CH4

/* Exported functions ------------------------------------------------------- */
rt_err_t efm_accel_get_data(struct efm32_accel_result_t *data);
rt_err_t efm_accel_auto_zero(rt_tick_t period);
rt_err_t efm_accel_init(void);

#endif /*__DEV_ACCEL_H__ */
