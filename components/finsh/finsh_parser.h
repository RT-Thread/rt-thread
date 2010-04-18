/*
 * File      : finsh_parser.h
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
#ifndef __FINSH_PARSER_H__
#define __FINSH_PARSER_H__

#include <finsh.h>

int finsh_parser_init(struct finsh_parser* self);
void finsh_parser_run(struct finsh_parser* self, const u_char* string);

#endif
