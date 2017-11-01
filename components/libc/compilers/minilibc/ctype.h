/*
 * File      : ctype.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-08-14     Bernard      the first version
 */
#ifndef __CTYPE_H__
#define __CTYPE_H__

int isprint(int c) __attribute__ ((__const__));
int isalpha (int c) __attribute__ ((__const__));
int isdigit (int ch) __attribute__ ((__const__));
int isspace(int ch) __attribute__ ((__const__));

#endif
