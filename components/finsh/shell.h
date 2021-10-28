/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-06-02     Bernard      Add finsh_get_prompt function declaration
 */

#ifndef __SHELL_H__
#define __SHELL_H__

#include <rtthread.h>
#include "msh.h"

#ifndef MSH_THREAD_PRIORITY
    #define MSH_THREAD_PRIORITY 20
#endif
#ifndef MSH_THREAD_STACK_SIZE
    #define MSH_THREAD_STACK_SIZE 2048
#endif
#ifndef MSH_CMD_SIZE
    #define MSH_CMD_SIZE      80
#endif

#define MSH_OPTION_ECHO   0x01

#define MSH_PROMPT        msh_get_prompt()
const char *msh_get_prompt(void);
int msh_set_prompt(const char *prompt);

#ifdef MSH_USING_HISTORY
    #ifndef MSH_HISTORY_LINES
        #define MSH_HISTORY_LINES 5
    #endif
#endif

#ifdef MSH_USING_AUTH
    #ifndef MSH_PASSWORD_MAX
        #define MSH_PASSWORD_MAX RT_NAME_MAX
    #endif
    #ifndef MSH_PASSWORD_MIN
        #define MSH_PASSWORD_MIN 6
    #endif
    #ifndef MSH_DEFAULT_PASSWORD
        #define MSH_DEFAULT_PASSWORD "rtthread"
    #endif
#endif /* MSH_USING_AUTH */

#ifndef MSH_THREAD_NAME
    #define MSH_THREAD_NAME   "tshell"
#endif

enum input_stat
{
    WAIT_NORMAL,
    WAIT_SPEC_KEY,
    WAIT_FUNC_KEY,
};
struct msh_shell
{
    struct rt_semaphore rx_sem;

    enum input_stat stat;

    rt_uint8_t echo_mode: 1;
    rt_uint8_t prompt_mode: 1;

#ifdef MSH_USING_HISTORY
    rt_uint16_t current_history;
    rt_uint16_t history_count;

    char cmd_history[MSH_HISTORY_LINES][MSH_CMD_SIZE];
#endif

    char line[MSH_CMD_SIZE + 1];
    rt_uint16_t line_position;
    rt_uint16_t line_curpos;

#if !defined(RT_USING_POSIX) && defined(RT_USING_DEVICE)
    rt_device_t device;
#endif

#ifdef MSH_USING_AUTH
    char password[MSH_PASSWORD_MAX];
#endif
};

void msh_set_echo(rt_uint32_t echo);
rt_uint32_t msh_get_echo(void);

int msh_system_init(void);
void msh_set_device(const char *device_name);
const char *msh_get_device(void);
int msh_getchar(void);

rt_uint32_t msh_get_prompt_mode(void);
void msh_set_prompt_mode(rt_uint32_t prompt_mode);

#ifdef MSH_USING_AUTH
    rt_err_t msh_set_password(const char *password);
    const char *msh_get_password(void);
#endif

#endif
