/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#ifndef __FINSH_PARSER_H__
#define __FINSH_PARSER_H__

#include <finsh.h>

int finsh_parser_init(struct finsh_parser* self);
void finsh_parser_run(struct finsh_parser* self, const uint8_t* string);

#endif
