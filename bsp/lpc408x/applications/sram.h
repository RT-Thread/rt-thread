/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-19     Bernard      The first version for LPC40xx
 */

#ifndef __SRAM_H__
#define __SRAM_H__

void *sram_malloc(unsigned long nbytes);
void sram_free(void *ptr);
void *sram_realloc(void *ptr, unsigned long nbytes);

#endif
