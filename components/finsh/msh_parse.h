/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-25     WangQiang    the first verion for msh parse
 */

#ifndef MSH_PARSE_H
#define MSH_PARSE_H

#include <rtthread.h>
#include <stdlib.h>
#include <ctype.h>

rt_bool_t msh_isint(char *strvalue);
#define msh_strtoint    atoi
rt_bool_t msh_ishex(char *strvalue);
int msh_strtohex(char *strvalue);

#endif /* MSH_PARSE_H */
