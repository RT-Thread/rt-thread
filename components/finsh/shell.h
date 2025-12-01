/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-06-02     Bernard      Add finsh_get_prompt function declaration.
 * 2025-09-22     yiyi         reconstruct the shell.
 */

#ifndef __SHELL_H__
#define __SHELL_H__

#include <rtdevice.h>
#include "finsh.h"

#ifndef FINSH_THREAD_NAME
#define FINSH_THREAD_NAME "tshell"
#endif /* !FINSH_THREAD_NAME */

#ifndef FINSH_THREAD_PRIORITY
#define FINSH_THREAD_PRIORITY 20
#endif /* !FINSH_THREAD_PRIORITY */

#ifndef FINSH_THREAD_STACK_SIZE
#define FINSH_THREAD_STACK_SIZE 2048
#endif /* !FINSH_THREAD_STACK_SIZE */

#ifndef FINSH_CMD_SIZE
#define FINSH_CMD_SIZE 80
#endif /* !FINSH_CMD_SIZE */

#ifdef FINSH_USING_HISTORY
#ifndef FINSH_HISTORY_LINES
#define FINSH_HISTORY_LINES 5
#endif /* !FINSH_HISTORY_LINES */
#endif /* FINSH_USING_HISTORY */

#ifdef FINSH_USING_AUTH
#ifndef FINSH_PASSWORD_MAX
#define FINSH_PASSWORD_MAX RT_NAME_MAX
#endif /* !FINSH_PASSWORD_MAX */
#ifndef FINSH_PASSWORD_MIN
#define FINSH_PASSWORD_MIN 6
#endif /* !FINSH_PASSWORD_MIN */
#ifndef FINSH_DEFAULT_PASSWORD
#define FINSH_DEFAULT_PASSWORD "rtthread"
#endif /* !FINSH_DEFAULT_PASSWORD */
#endif /* FINSH_USING_AUTH */

#ifdef FINSH_USING_SNAPSHOT
#ifndef FINSH_SNAPSHOT_DEPTH
#define FINSH_SNAPSHOT_DEPTH 32
#endif /* !FINSH_SNAPSHOT_DEPTH */
#endif /* FINSH_USING_SNAPSHOT */

#ifndef FINSH_PROMPT_WORD_DEFAULT
#define FINSH_PROMPT_WORD_DEFAULT "msh "
#endif /* !FINSH_PROMPT_WORD_DEFAULT */

enum finsh_input_state
{
    FINSH_INPUT_STATE_NORMAL,
    FINSH_INPUT_STATE_SPECIFIED_KEY,
    FINSH_INPUT_STATE_FUNCTION_KEY,
    FINSH_INPUT_STATE_EXTEND_KEY,
    FINSH_INPUT_STATE_CTRL_SEQUENCE,
};

#ifdef FINSH_USING_HISTORY
struct finsh_history
{
#ifndef RT_USING_HEAP
    char cmd[FINSH_CMD_SIZE + 1];
#else
    char *cmd; /* cmd is the command string */
#endif /* !RT_USING_HEAP */
    rt_list_t list;
};
#endif /* FINSH_USING_HISTORY */

#ifdef FINSH_USING_SNAPSHOT
enum finsh_snapshot_state
{
    FINSH_SNAPSHOT_STATE_NONE,
    FINSH_SNAPSHOT_STATE_NORMAL,
    FINSH_SNAPSHOT_STATE_ESC,
    FINSH_SNAPSHOT_STATE_BACKSPACE,
    FINSH_SNAPSHOT_STATE_SPACE,
};

struct finsh_snapshot
{
#ifndef RT_USING_HEAP
    char cmd[FINSH_CMD_SIZE + 1];
#else
    char *cmd; /* cmd is the command string */
#endif /* !RT_USING_HEAP */
    rt_size_t cmd_length;
    rt_size_t cmd_cursor;
    rt_list_t list;
};
#endif /* FINSH_USING_SNAPSHOT */

struct finsh_shell
{
    struct rt_semaphore rx_notice;
    enum finsh_input_state input_state;

#ifdef FINSH_USING_HISTORY
    rt_list_t history_list;
    rt_list_t *cur_history;
    rt_bool_t is_push_last_history;
#ifndef RT_USING_HEAP
    struct finsh_history history[FINSH_HISTORY_LINES];
#endif /* !RT_USING_HEAP */
#endif /* FINSH_USING_HISTORY */

    char cmd[FINSH_CMD_SIZE + 1];
    rt_size_t cmd_length;
    rt_size_t cmd_cursor;

    char extend_key; /* extend key is the key after the function key */
    rt_bool_t is_insert; /* insert mode is the mode to insert character at the cursor position */
    rt_bool_t is_ctrl; /* ctrl mode is the mode to handle ctrl sequence */

    rt_bool_t is_echo; /* echo mode is the mode to echo the command */
    rt_bool_t is_prompt; /* prompt mode is the mode to prompt the command */

#ifdef FINSH_USING_SNAPSHOT
    rt_list_t snapshot_list;
    rt_list_t *cur_snapshot;
    rt_bool_t is_push_last_snapshot;
    enum finsh_snapshot_state snapshot_state;
    rt_bool_t is_space_snapshot;
#ifndef RT_USING_HEAP
    struct finsh_snapshot snapshot[FINSH_SNAPSHOT_DEPTH];
#endif /* !RT_USING_HEAP */
#endif /* FINSH_USING_SNAPSHOT */

#ifdef FINSH_USING_AUTH
    char password[FINSH_PASSWORD_MAX];
#endif /* FINSH_USING_AUTH */

#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    struct rt_device *device;
#endif /* !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE) */
};

int finsh_system_init(void);
int finsh_system_deinit(void);

char finsh_getchar(void);

#ifdef RT_USING_HOOK
void finsh_thread_entry_sethook(void (*hook)(void));
#endif /* RT_USING_HOOK */

int finsh_set_prompt_word(const char *prompt);
const char *finsh_get_prompt_word(void);
#define FINSH_PROMPT finsh_get_prompt_word()

void finsh_set_prompt(rt_bool_t prompt);
rt_bool_t finsh_get_prompt(void);

#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
void finsh_set_device(const char *device_name);
const char *finsh_get_device(void);
#endif /* !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE) */

void finsh_set_echo(rt_bool_t echo);
rt_bool_t finsh_get_echo(void);

#ifdef FINSH_USING_AUTH
int finsh_set_password(const char *password);
const char *finsh_get_password(void);
#endif /* FINSH_USING_AUTH */

#endif /* __SHELL_H__ */
