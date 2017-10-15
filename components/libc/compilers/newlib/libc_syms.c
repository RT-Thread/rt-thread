/*
 * File     : libc_syms.c
 * Brief    : exported symbols for libc.
 *
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
 * 2017/10/15     bernard      the first version
 */
#include <rtthread.h>
#include <rtm.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

RTM_EXPORT(strcpy);
RTM_EXPORT(strncpy);
RTM_EXPORT(strlen);
RTM_EXPORT(strcat);
RTM_EXPORT(strstr);
RTM_EXPORT(strchr);
RTM_EXPORT(strcmp);
RTM_EXPORT(strtol);
RTM_EXPORT(strtoul);
RTM_EXPORT(strncmp);

RTM_EXPORT(memcpy);
RTM_EXPORT(memcmp);
RTM_EXPORT(memmove);
RTM_EXPORT(memset);
RTM_EXPORT(memchr);

RTM_EXPORT(putchar);
RTM_EXPORT(puts);
RTM_EXPORT(printf);
RTM_EXPORT(sprintf);
RTM_EXPORT(snprintf);

RTM_EXPORT(fwrite);

#include <time.h>
RTM_EXPORT(localtime);
RTM_EXPORT(time);

#include <setjmp.h>
RTM_EXPORT(longjmp);
RTM_EXPORT(setjmp);

RTM_EXPORT(exit);
RTM_EXPORT(abort);

RTM_EXPORT(rand);

#include <assert.h>
RTM_EXPORT(__assert_func);
