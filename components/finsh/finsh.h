/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#ifndef __FINSH_H__
#define __FINSH_H__

#warning "<finsh.h> and macros like FINSH_xxx will be obsolete in the next version. Please use <msh.h> and MSH_xxx to instead."

#include <msh.h>

#ifdef RT_USING_MSH
#define FINSH_USING_MSH
#define FINSH_THREAD_NAME MSH_THREAD_NAME
#define FINSH_THREAD_PRIORITY MSH_THREAD_PRIORITY
#define FINSH_THREAD_STACK_SIZE MSH_THREAD_STACK_SIZE
#ifdef MSH_USING_HISTORY
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES MSH_HISTORY_LINES
#endif
#ifdef MSH_USING_SYMTAB
#define FINSH_USING_SYMTAB
#endif
#define FINSH_CMD_SIZE MSH_CMD_SIZE
#ifdef MSH_USING_DESCRIPTION
#define FINSH_USING_DESCRIPTION
#endif
#ifdef MSH_ECHO_DISABLE_DEFAULT
#define FINSH_ECHO_DISABLE_DEFAULT
#endif
#ifdef MSH_USING_AUTH
#define FINSH_USING_AUTH
#define FINSH_DEFAULT_PASSWORD MSH_DEFAULT_PASSWORD
#define FINSH_PASSWORD_MIN MSH_PASSWORD_MIN
#define FINSH_PASSWORD_MAX MSH_PASSWORD_MAX
#endif
#define FINSH_ARG_MAX MSH_ARG_MAX
#endif

#define FINSH_PROMPT MSH_PROMPT

#define finsh_get_prompt msh_get_prompt
#define finsh_set_prompt msh_set_prompt
#define finsh_shell msh_shell

#define finsh_set_echo msh_set_echo
#define finsh_get_echo msh_get_echo 
#define finsh_system_init msh_system_init
#define finsh_set_device msh_set_device
#define finsh_get_device msh_get_device
#define finsh_getchar msh_getchar
#define finsh_get_prompt_mode msh_get_prompt_mode
#define finsh_set_prompt_mode msh_set_prompt_mode
#ifdef MSH_USING_AUTH
#define finsh_set_password msh_set_password
#define finsh_get_password msh_get_password
#endif

/**
 * @ingroup finsh
 *
 * This macro exports a system function to finsh shell.
 *
 * @param name the name of function.
 * @param desc the description of function, which will show in help.
 */
#define FINSH_FUNCTION_EXPORT(name, desc)

/**
 * @ingroup finsh
 *
 * This macro exports a system function with an alias name to finsh shell.
 *
 * @param name the name of function.
 * @param alias the alias name of function.
 * @param desc the description of function, which will show in help.
 */
#define FINSH_FUNCTION_EXPORT_ALIAS(name, alias, desc)


#endif
