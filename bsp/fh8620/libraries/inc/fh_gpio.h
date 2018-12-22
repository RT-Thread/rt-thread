/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef FH_GPIO_H_
#define FH_GPIO_H_


#define     REG_GPIO_SWPORTA_DR         (0x0000)
#define     REG_GPIO_SWPORTA_DDR        (0x0004)
#define     REG_GPIO_PORTA_CTL          (0x0008)
#define     REG_GPIO_INTEN              (0x0030)
#define     REG_GPIO_INTMASK            (0x0034)
#define     REG_GPIO_INTTYPE_LEVEL      (0x0038)
#define     REG_GPIO_INT_POLARITY       (0x003C)
#define     REG_GPIO_INTSTATUS          (0x0040)
#define     REG_GPIO_RAWINTSTATUS       (0x0044)
#define     REG_GPIO_DEBOUNCE           (0x0048)
#define     REG_GPIO_PORTA_EOI          (0x004C)
#define     REG_GPIO_EXT_PORTA          (0x0050)

#define NUM_OF_GPIO         (64)

struct fh_gpio_obj
{
    unsigned int              id;
    unsigned int              irq;
};



#endif /* FH_GPIO_H_ */
