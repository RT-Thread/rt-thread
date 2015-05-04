/*
 * File      : rt_low_level_gcc.inc
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
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
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-14     ArdaFu      first version
 */

/*--------- Stack size of CPU modes ------------------------------------------*/
.equ UND_STK_SIZE,    2048
.equ SVC_STK_SIZE,    4096
.equ ABT_STK_SIZE,    2048
.equ IRQ_STK_SIZE,    4096
.equ FIQ_STK_SIZE,    4096
.equ SYS_STK_SIZE,    2048
