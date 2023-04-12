/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-08     shelton      first version
 */

#ifndef __AT32_MSP_H__
#define __AT32_MSP_H__

void at32_msp_usart_init(void *instance);
void at32_msp_spi_init(void *instance);
void at32_msp_tmr_init(void *instance);
void at32_msp_adc_init(void *instance);
void at32_msp_hwtmr_init(void *instance);
void at32_msp_can_init(void *instance);
void at32_msp_usb_init(void *instance);

#endif /* __AT32_MSP_H__ */
