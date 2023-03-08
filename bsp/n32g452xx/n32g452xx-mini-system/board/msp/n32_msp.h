/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-13     shelton      first version
 */

#ifndef __N32_MSP_H__
#define __N32_MSP_H__

void n32_msp_usart_init(void *Instance);
void n32_msp_spi_init(void *Instance);
void n32_msp_tim_init(void *Instance);
void n32_msp_sdio_init(void *Instance);
void n32_msp_adc_init(void *Instance);
void n32_msp_hwtim_init(void *Instance);
void n32_msp_can_init(void *Instance);
void n32_msp_jtag_init(void *Instance);

#endif /* __N32_MSP_H__ */

