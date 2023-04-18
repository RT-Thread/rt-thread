/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-03-30     Bernard      the first verion for FinSH
 */

#ifndef __M_SHELL__
#define __M_SHELL__

#include <rtthread.h>

int msh_exec(char *cmd, rt_size_t length);
void msh_auto_complete(char *prefix);
void msh_opt_auto_complete(char *prefix);

int msh_exec_module(const char *cmd_line, int size);
int msh_exec_script(const char *cmd_line, int size);

void msh_opt_list_dump(void *options);
int msh_cmd_opt_id_get(int argc, char *argv[], void *options);

#define MSH_OPT_ID_GET(fun) msh_cmd_opt_id_get(argc, argv, (void*) fun##_msh_options)
#define MSH_OPT_DUMP(fun)   msh_opt_list_dump((void*) fun##_msh_options)
#endif
