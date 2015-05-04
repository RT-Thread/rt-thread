/*
 * File      : interrupt.h
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
 
#include "asm9260t.h"
#include "rtthread.h"

void HW_SetPinMux(rt_uint8_t port, rt_uint8_t pin, rt_uint8_t mux_type)
{
    rt_uint32_t addr = HW_IOCON(port, pin);
    rt_uint32_t val = inl(addr);   // read origin value

    val &= ~7UL;     // clear MUX field
    val |= mux_type; // set MUX field with new value

    outl(val ,addr);   // Set new value
}

void HW_GpioSetDir(rt_uint8_t port, rt_uint8_t pin, rt_uint8_t isOut)
{
    rt_uint32_t addr = HW_GPIO_DATA_BASE | ((port>>2)<<16) | 0x8000;
    rt_uint32_t val;
    addr = isOut? REG_SET(addr) : REG_CLR(addr);
    val = (1 << ((port%4)*8+pin));
    outl(val, addr);
}

void HW_GpioSetVal(rt_uint8_t port, rt_uint8_t pin)
{
    rt_uint32_t addr, val;
    addr = REG_SET(HW_GPIO_DATA_BASE | ((port>>2)<<16));
    val  = (1 << ((port%4)*8+pin));
    outl(val, addr);
}

void HW_GpioClrVal(rt_uint8_t port, rt_uint8_t pin)
{
    rt_uint32_t addr, val;
    addr = REG_CLR(HW_GPIO_DATA_BASE | ((port>>2)<<16));
    val  = (1 << ((port%4)*8+pin));
    outl(val, addr);
}
