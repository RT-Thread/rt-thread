/*
 * File      : adc.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-03     lgnq
 */
 
#ifndef __ADC_H__
#define __ADC_H__

/* Exported constants ---------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
#define ADC_MODE_SINGLE 	0x00UL
#define ADC_MODE_SCAN 		0x01UL
#define ADC_MODE_TAILGATE	0x02UL

#define RT_DEVICE_CTRL_ADC_START        0xF1       /* start ADC conversion */
#define RT_DEVICE_CTRL_ADC_RESULT		0xF2		/* get ADC result */

#define ADC_UPDATE 0

/* Exported functions --------------------------------------------------------- */
void rt_hw_adc_init(void);

#endif /*__ADC_H__ */
