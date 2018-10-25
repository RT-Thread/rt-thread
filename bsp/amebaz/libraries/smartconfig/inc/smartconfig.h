/*
 * File      : smartconfig.h
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
 * 2018-09-13     Bernard      the first version
 */
#ifndef __SMARTCONFIG_H__
#define __SMARTCONFIG_H__

#define SMARTCONFIG_EVENT_CHANGE_CHANNEL    (1 << 0)
#define SMARTCONFIG_EVENT_LOCKED_CHANNEL    (1 << 1)
#define SMARTCONFIG_EVENT_COMPLETE          (1 << 2)
#define SMARTCONFIG_EVENT_RESTART           (1 << 3)
#define SMARTCONFIG_EVENT_STOP              (1 << 4)

typedef enum
{
    SMARTCONFIG_TYPE_AIRKISS = 0,
    SMARTCONFIG_TYPE_JDSMART = 1,
    SMARTCONFIG_TYPE_ESPTOUCH,
    SMARTCONFIG_TYPE_REALTOUCH,
    SMARTCONFIG_TYPE_ALL,
    SMARTCONFIG_TYPE_MAX,
} rt_smartconfig_type;

typedef enum
{
    SMARTCONFIG_ENCRYPT_NONE,
    SMARTCONFIG_ENCRYPT_AES,
} rt_smartconfig_encrypt_type;

typedef int (*rt_smartconfig_result_cb)(rt_smartconfig_type result_type, char *ssid, char *passwd, \
                                        void *userdata, rt_uint8_t userdata_len);
typedef void (*rt_smartconfig_event_handle)(rt_uint32_t event, void *userdata);

int rt_smartconfig_start(rt_smartconfig_type config_type, rt_smartconfig_encrypt_type encrypt_type, char *encrypt, \
                         rt_smartconfig_result_cb result_cb);

int rt_smartconfig_stop(void);

void rt_smartconfig_set_event_handle(rt_smartconfig_event_handle handle, void *userdata);

char *rt_smartconfig_version(void);

#endif
