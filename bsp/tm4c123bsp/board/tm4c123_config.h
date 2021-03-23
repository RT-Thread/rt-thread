/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#ifndef __TM4C123GH6PZ_CONFIG_H__
#define __TM4C123GH6PZ_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_SERIAL
void uart_hw_config(void);
#endif /* RT_USING_SERIAL */
#ifdef RT_USING_ADC
void adc_hw_config(void);
#endif /* RT_USING_ADC */
#ifdef RT_USING_PWM
void pwm_hw_config(void);
#endif /* RT_USING_PWM */
#ifdef RT_USING_SPI
void spi_hw_config(void);
#endif /* RT_USING_SPI */

#ifdef __cplusplus
}
#endif

#endif /*__TM4C123GH6PZ_CONFIG_H__*/

/************************** end of file ******************/

