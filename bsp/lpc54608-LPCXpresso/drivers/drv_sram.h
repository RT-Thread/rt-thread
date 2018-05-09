/*
 * File      : sram.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009-2013 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-05-19     Bernard      The first version for LPC40xx
 */

#ifndef __DRV_SRAM_H__
#define __DRV_SRAM_H__

void sram_init(void);

void *sram_malloc(unsigned long nbytes);
void sram_free(void *ptr);
void *sram_realloc(void *ptr, unsigned long nbytes);

#endif
