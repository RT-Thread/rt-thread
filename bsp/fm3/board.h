/*
 * File      : board.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-09-22     Bernard      add board.h to this bsp
 * 2010-02-04     Magicoe      add board.h to LPC176x bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include "mb9bf506r.h"

/*LEDs*/
#define LED1        (1UL<<10)
#define LED2        (1UL<<11)
#define LED3        (1UL<<12)
#define LED_MASK    (LED1 | LED2 | LED3)

#define LED_PFR     (FM3_GPIO->PFR3)
#define LED_DDR     (FM3_GPIO->DDR3)
#define LED_PDOR    (FM3_GPIO->PDOR3)

//Internal SRAM memory size[Kbytes] <8-64>
//MB9BF500 : 32
//MB9BF504 : 32
//MB9BF505 : 48
//MB9BF506 : 64
#define FM3_SRAM_SIZE         32
#define FM3_SRAM_END          (0x20000000 + FM3_SRAM_SIZE * 1024)

void rt_hw_led_on(int n);
void rt_hw_led_off(int n);
void rt_hw_board_init(void);

#endif
