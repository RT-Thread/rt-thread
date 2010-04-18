/*
 * File      : finsh_error.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#ifndef __FINSH_ERROR_H__
#define __FINSH_ERROR_H__

#include <finsh.h>

int finsh_error_init(void);

/* get error number */
u_char finsh_errno(void);

int finsh_error_set(u_char type);
const char* finsh_error_string(u_char type);

#endif
