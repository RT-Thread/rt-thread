/*
 * File      : fm24clxx.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2017-07-14     aubr.cool    1st version
 */

#ifndef __FM24CLXX_H__
#define __FM24CLXX_H__

#include <rtthread.h>

struct fm24clxx_config
{
    rt_uint32_t              size;
    rt_uint16_t              addr;
    rt_uint16_t              flags;
};

extern rt_err_t fm24clxx_register(const char *e2m_device_name,
                                  const char *i2c_bus, void *user_data);

#endif /*__FM24CLXX_H__*/