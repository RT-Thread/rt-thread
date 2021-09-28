/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 */
#ifndef __BOARD_H__
#define __BOARD_H__
int rt_hw_board_init(void);
rt_uint8_t *rt_hw_sram_init(void);

/* SD Card init function */
void rt_hw_sdcard_init(void);

int rt_hw_mtd_nand_init(void);
int sst25vfxx_mtd_init(const char *, unsigned int , unsigned int);
void pcap_netif_hw_init(void);
void rt_platform_init(void);
void rt_hw_usart_init(void);
void rt_hw_serial_init(void);
void rt_hw_sdl_start(void);
void rt_hw_win32_low_cpu(void);

void rt_hw_exit(void);
#endif
