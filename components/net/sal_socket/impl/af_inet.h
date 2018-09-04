/*
 * File      : af_inet.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
 * 2018-08-25     ChenYong     First version
 */

#ifndef __AF_INET_H__
#define __AF_INET_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SAL_USING_LWIP
/* lwIP protocol family register */
int lwip_inet_init(void);
#endif

#ifdef SAL_USING_AT
/* AT protocol family register */
int at_inet_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AF_INET_H__ */
