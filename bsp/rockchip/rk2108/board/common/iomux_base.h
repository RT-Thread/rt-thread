/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-12     Steven Liu   first implementation
 */

#ifndef __IOMUX_BASE_H__
#define __IOMUX_BASE_H__

void m4_jtag_iomux_config(void);
void uart0_iomux_config(void);
void uart1_m0_iomux_config(void);
void uart1_m1_iomux_config(void);
void uart1_m2_iomux_config(void);
void uart1_m3_iomux_config(void);
void uart2_iomux_config(void);
void rt_hw_iomux_config(void);

#endif
