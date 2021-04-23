/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-13     shelton      first version
 */

#ifndef __AT32_MSP_H__
#define __AT32_MSP_H__

void at32_msp_usart_init(void *Instance);
void at32_msp_spi_init(void *Instance);
void at32_msp_tmr_init(void *Instance);
void at32_msp_i2c_init(void *Instance);
void at32_msp_sdio_init(void *Instance);
void at32_msp_adc_init(void *Instance);
void at32_msp_hwtmr_init(void *Instance);
void at32_msp_can_init(void *Instance);

#endif /* __AT32_MSP_H__ */
