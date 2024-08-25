/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2017-10-20     ZYH          emmm...setup for HAL Libraries
 */

/* <<< Use Configuration Wizard in Context Menu >>> */
#ifndef __BOARD_H__
#define __BOARD_H__

#include "ch32v10x.h"
#include <rthw.h>
#include "drivers/dev_pin.h"
#define CH32V10X_PIN_NUMBERS   64

/* board configuration */
#define SRAM_SIZE  20
#define SRAM_END (0x20000000 + SRAM_SIZE * 1024)

extern int _ebss;
#define HEAP_BEGIN  ((void *)&_ebss)
#define HEAP_END    (SRAM_END-_stack_size)


/* extern volatile unsigned long  interrupter_sp_saver */
void rt_hw_board_init(void);

#endif /* __BOARD_H__ */
