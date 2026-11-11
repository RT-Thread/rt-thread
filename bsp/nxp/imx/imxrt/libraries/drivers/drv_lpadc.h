/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     Lee          the first version.
 */

#ifndef DRV_ADC_H__
#define DRV_ADC_H__
#include <rtdevice.h>


/* drv adc channel definition */
/*
#define RT_DRV_ADC_CH_A_0     0x01
#define RT_DRV_ADC_CH_A_1     0x02
#define RT_DRV_ADC_CH_A_2     0x04
#define RT_DRV_ADC_CH_A_3     0x08
#define RT_DRV_ADC_CH_A_4     0x10
#define RT_DRV_ADC_CH_A_5     0x20
#define RT_DRV_ADC_CH_A_6     0x40
#define RT_DRV_ADC_CH_A_7     0x80

#define RT_DRV_ADC_CH_B_0     0x01
#define RT_DRV_ADC_CH_B_1     0x02
#define RT_DRV_ADC_CH_B_2     0x04
#define RT_DRV_ADC_CH_B_3     0x08
#define RT_DRV_ADC_CH_B_4     0x10
#define RT_DRV_ADC_CH_B_5     0x20
#define RT_DRV_ADC_CH_B_6     0x40
#define RT_DRV_ADC_CH_B_7     0x80
*/

/*
imxrt1180-nxp-evk arduino interface ADC channel configuration:
ADC1:
RT_DRV_ADC1_CH_A_4, RT_DRV_ADC1_CH_A_6, RT_DRV_ADC1_CH_A_7
RT_DRV_ADC1_CH_B_5, RT_DRV_ADC1_CH_B_6, RT_DRV_ADC1_CH_B_7

ADC2:
RT_DRV_ADC1_CH_A_0, RT_DRV_ADC1_CH_B_0

IMPORTANT!!
Propose to change rt_adc_ops structure from rt_int8_t to rt_int16_t to enable side A and side B simultineously in same ADC !!!
*/


int rt_hw_adc_init(void);

#endif /* DRV_ADC_H__ */

