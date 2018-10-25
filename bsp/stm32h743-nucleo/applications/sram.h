/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-08-03     xiaonong      The first version for STM32F7
 * 2017-08-25     LongfeiMa    transplantation for stm32h7xx
 */

#ifndef __SRAM_H__
#define __SRAM_H__

void sram_init(void);
void *sram_malloc(unsigned long nbytes);
void sram_free(void *ptr);
void *sram_realloc(void *ptr, unsigned long nbytes);

#endif
