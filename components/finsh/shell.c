/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-04-30     Bernard      the first version for FinSH
 * 2006-05-08     Bernard      change finsh thread stack to 2048
 * 2006-06-03     Bernard      add support for skyeye
 * 2006-09-24     Bernard      remove the code related with hardware
 * 2010-01-18     Bernard      fix down then up key bug.
 * 2010-03-19     Bernard      fix backspace issue and fix device read in shell.
 * 2010-04-01     Bernard      add prompt output when start and remove the empty history
 * 2011-02-23     Bernard      fix variable section end issue of finsh shell
 *                             initialization when use GNU GCC compiler.
 * 2016-11-26     armink       add password authentication
 * 2018-07-02     aozima       add custom prompt support.
 * 2025-09-22     yiyi         reconstruct the shell, and the functions after reconstruction are as follows:
 *                             #ifdef FINSH_USING_HISTORY
 *                             1. 'Up/Down' to history command.
 *                             #endif
 *                             2. 'Left/Right' to move cursor.
 *                             #ifdef FINSH_USING_WORD_OPERATION
 *                             3. 'Ctrl+Left/Right' to jump word by word.
 *                             4. 'Ctrl+W/Backspace' to delete word.
 *                             #endif
 *                             #ifdef FINSH_USING_SNAPSHOT
 *                             5. 'Ctrl+Z' to pop snapshot.
 *                             6. 'Ctrl+Y' to rollback snapshot.
 *                             #endif
 *                             #ifdef FINSH_USING_EXTEND_FEATURE
 *                             7. 'Home/End' to move cursor to the beginning/end of the command.
 *                             8. 'Delete' to delete character backward.
 *                             9. 'Insert' to toggle insert mode.
 *                             #endif
 *                             10. 'Tab' to auto complete.
 *                             11. 'Backspace' to delete character forward
 *                             12. 'Enter' to execute command.
 */

#include <rthw.h>
#include <string.h>
#include <stdio.h>

#ifdef RT_USING_FINSH

#include "shell.h"
#include "msh.h"

#ifdef DFS_USING_POSIX
#include <unistd.h>
#include <fcntl.h>
#endif /* DFS_USING_POSIX */

#ifdef RT_USING_POSIX_STDIO
#include <unistd.h>
#include <posix/stdio.h>
#endif /* RT_USING_POSIX_STDIO */

/* finsh thread */
#ifndef RT_USING_HEAP
static struct rt_thread finsh_thread = { 0 };
rt_align(RT_ALIGN_SIZE) static char finsh_thread_stack[FINSH_THREAD_STACK_SIZE] = { 0 };
static struct finsh_shell _shell = { 0 };
#endif /* !RT_USING_HEAP */

/* finsh symtab */
#ifdef FINSH_USING_SYMTAB
struct finsh_syscall *_syscall_table_begin = RT_NULL;
struct finsh_syscall *_syscall_table_end = RT_NULL;
#endif /* FINSH_USING_SYMTAB */

static struct finsh_shell *shell = RT_NULL;
static char finsh_prompt[RT_CONSOLEBUF_SIZE + 1] = { 0 };
static rt_size_t finsh_prompt_length = 0;

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__))
struct finsh_syscall *finsh_syscall_next(struct finsh_syscall *call)
{
    rt_ubase_t *ptr;
    ptr = (rt_ubase_t *)(call + 1);
    while ((!(*ptr)) && ((rt_ubase_t *)ptr < (rt_ubase_t *)_syscall_table_end))
        ptr++;

    return (struct finsh_syscall *)ptr;
}
#endif /* defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__)) */

#ifdef RT_USING_HOOK
static void (*_finsh_thread_entry_hook)(void);

/**
  * @brief Set the hook function to be called at the entry of the finsh thread.
  *
  * This function assigns a user-defined hook function that will be executed
  * when the finsh thread starts. It allows users to perform custom initialization
  * or actions at the beginning of the finsh thread execution.
  *
  * @param hook Pointer to the hook function to be set.
  */
void finsh_thread_entry_sethook(void (*hook)(void))
{
    _finsh_thread_entry_hook = hook;
}
#endif /* RT_USING_HOOK */

/**
  * @brief Set the shell prompt string.
  *
  * This function sets the prompt string for the FinSH shell. It copies the given prompt
  * to the internal prompt buffer, ensuring it does not exceed the maximum buffer size.
  * If the input prompt is RT_NULL, it prints an error message and returns an error code.
  *
  * @param prompt The new prompt string to set.
  *
  * @return 0 on success, -RT_EINVAL if the prompt is RT_NULL.
  */
int finsh_set_prompt_word(const char *prompt)
{
    if (!prompt)
    {
        rt_kprintf("Invalid prompt!\n");
        return -RT_EINVAL;
    }

    rt_memset(finsh_prompt, 0, sizeof(finsh_prompt));
    rt_strncpy(finsh_prompt, prompt, RT_CONSOLEBUF_SIZE);
    finsh_prompt_length = rt_strlen(finsh_prompt);

    return 0;
}

/**
  * @brief Get the current shell prompt string.
  *
  * This function returns the current prompt string for the FinSH shell.
  * If the prompt mode is disabled, it returns an empty string.
  * If the prompt string is not set, it sets the default prompt ("msh ").
  * When POSIX and workdir support are enabled, it appends the current working directory to the prompt.
  * Finally, it appends a '>' character to the prompt if there is enough space.
  *
  * @return Pointer to the prompt string.
  */
const char *finsh_get_prompt_word(void)
{
    rt_size_t len;

    RT_ASSERT(shell != RT_NULL);

    /* check prompt mode */
    if (!shell->is_prompt)
    {
        finsh_prompt[RT_CONSOLEBUF_SIZE] = 0;
        return &finsh_prompt[RT_CONSOLEBUF_SIZE];
    }

    if (!finsh_prompt[0])
        finsh_set_prompt_word(FINSH_PROMPT_WORD_DEFAULT);

    len = finsh_prompt_length;
#if defined(DFS_USING_POSIX) && defined(DFS_USING_WORKDIR)
    /* get current working directory */
    getcwd(&finsh_prompt[len], RT_CONSOLEBUF_SIZE - len);
#endif
    len = rt_strlen(finsh_prompt);
    if ((len + 2) < RT_CONSOLEBUF_SIZE)
    {
        finsh_prompt[len++] = '>';
        finsh_prompt[len++] = 0;
    }

    return finsh_prompt;
}

/**
  * @brief Set the prompt mode of the FinSH shell.
  *
  * This function enables or disables the prompt mode for the FinSH shell.
  * If the parameter is 0, the prompt mode is disabled; any other value enables the prompt mode.
  *
  * @param prompt The prompt mode flag (0 to disable, non-zero to enable).
  */
void finsh_set_prompt(rt_bool_t prompt)
{
    RT_ASSERT(shell != RT_NULL);
    shell->is_prompt = prompt;
}

/**
  * @brief Get the prompt mode of the FinSH shell.
  *
  * This function returns the current prompt mode of the FinSH shell.
  * If the prompt mode is enabled, it returns a non-zero value; if disabled, it returns 0.
  *
  * @return The prompt mode status: 0 means prompt mode is disabled, non-zero means enabled.
  */
rt_bool_t finsh_get_prompt(void)
{
    RT_ASSERT(shell != RT_NULL);
    return shell->is_prompt;
}

#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
static rt_err_t finsh_rx_ind(rt_device_t dev, rt_size_t size)
{
    RT_ASSERT(shell != RT_NULL);

    if (size)
        rt_sem_release(&shell->rx_notice);

    return 0;
}

/**
  * @brief Set the input device for the FinSH shell.
  *
  * This function changes the input device used by the FinSH shell to the device specified by device_name.
  * It first finds the device by name, then opens it with the appropriate flags. If the device is already
  * the current input device, the function returns immediately. If a previous device was set, it will be closed
  * and its receive indication callback cleared. The new device will have its receive indication callback set
  * to finsh_rx_ind, and the shell's device pointer will be updated.
  *
  * @param device_name The name of the new input device to be used by the shell.
  */
void finsh_set_device(const char *device_name)
{
    struct rt_device *device;
    rt_uint16_t oflag;
    int ret;
#ifdef RT_USING_SERIAL_V2
    int rxto;
#endif /* RT_USING_SERIAL_V2 */

    RT_ASSERT(shell != RT_NULL);
    RT_ASSERT(device_name != RT_NULL);

    device = rt_device_find(device_name);
    if (!device)
    {
        rt_kprintf("Finsh: can not find device: %s!\n", device_name);
        return;
    }

    if (device == shell->device)
        return;

#ifdef RT_USING_SERIAL_V2
    oflag = RT_DEVICE_FLAG_RX_BLOCKING | RT_DEVICE_FLAG_TX_BLOCKING;
#else
    oflag = RT_DEVICE_FLAG_INT_RX;
#endif /* RT_USING_SERIAL_V2 */
    oflag |= RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_STREAM;
    ret = rt_device_open(device, oflag);
    if (ret)
    {
        rt_kprintf("Finsh: open device: %s failed!\n", device_name);
        return;
    }

#ifdef RT_USING_SERIAL_V2
    rxto = RT_WAITING_NO;
    rt_device_control(device, RT_SERIAL_CTRL_SET_RX_TIMEOUT, (void *)&rxto);
#endif /* RT_USING_SERIAL_V2 */

    if (shell->device)
    {
        rt_device_close(shell->device);
        rt_device_set_rx_indicate(shell->device, RT_NULL);
    }

    rt_device_set_rx_indicate(device, finsh_rx_ind);
    shell->device = device;
}

/**
  * Get the name of the current input device used by the finsh shell.
  *
  * @return The name of the device as a string.
  */
const char *finsh_get_device(void)
{
    RT_ASSERT(shell != RT_NULL);
    return shell->device->parent.name;
}
#endif /* !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE) */

/**
  * Set the echo mode of the finsh shell.
  *
  * When echo mode is enabled, the shell will display user input characters.
  * When disabled, user input will not be echoed to the terminal.
  *
  * @param echo RT_TRUE to enable echo, RT_FALSE to disable echo.
  */
void finsh_set_echo(rt_bool_t echo)
{
    RT_ASSERT(shell != RT_NULL);
    shell->is_echo = echo;
}

/**
  * @brief Get the current echo mode status of the finsh shell.
  *
  * This function returns whether the shell is currently in echo mode.
  * When echo mode is enabled, user input will be displayed on the terminal.
  *
  * @return RT_TRUE if echo mode is enabled, RT_FALSE otherwise.
  */
rt_bool_t finsh_get_echo(void)
{
    RT_ASSERT(shell != RT_NULL);
    return shell->is_echo;
}

#ifdef FINSH_USING_AUTH
/**
  * @brief Set a new password for the finsh shell.
  *
  * This function sets a new password for the finsh shell. It first checks whether the input password
  * is valid (not RT_NULL and its length is within the allowed range). If the password is valid, it copies
  * the new password into the shell's password buffer in a critical section to ensure thread safety.
  *
  * @param password The new password string to set.
  *
  * @return 0 on success, -RT_EINVAL if the password is RT_NULL or its length is invalid.
  */
int finsh_set_password(const char *password)
{
    rt_size_t len;
    rt_base_t level;

    RT_ASSERT(shell != RT_NULL);

    if (!password)
    {
        rt_kprintf("Password is RT_NULL!\n");
        return -RT_EINVAL;
    }

    len = rt_strlen(password);
    if (len > FINSH_PASSWORD_MAX || len < FINSH_PASSWORD_MIN)
    {
        rt_kprintf("Password length is less than FINSH_PASSWORD_MIN(%d) or greater than FINSH_PASSWORD_MAX(%d)!\n", FINSH_PASSWORD_MIN, FINSH_PASSWORD_MAX);
        return -RT_EINVAL;
    }

    level = rt_hw_interrupt_disable();
    rt_strncpy(shell->password, password, len);
    shell->password[len] = 0;
    rt_hw_interrupt_enable(level);

    return 0;
}

/**
  * @brief Get the current password of the finsh shell.
  *
  * This function returns a pointer to the password string currently used by the finsh shell
  * for authentication purposes.
  *
  * @return Pointer to the password string.
  */
const char *finsh_get_password(void)
{
    RT_ASSERT(shell != RT_NULL);
    return shell->password;
}

static void finsh_wait_input_password(char *password)
{
    char ch;
    rt_size_t cursor = 0;

    while (1)
    {
        /* read one character from device */
        ch = finsh_getchar();
        if (ch < 0)
            continue;

        if (ch >= ' ' && ch <= '~' && cursor < FINSH_PASSWORD_MAX)
        {
            rt_kprintf("*");
            password[cursor++] = ch;
        }
        else if (ch == '\b' && cursor > 0)
        {
            password[--cursor] = 0;
            rt_kprintf("\b \b");
        }
        else if (ch == '\r' || ch == '\n')
            break;
    }

    rt_kprintf("\n");
}

static void finsh_password_auth(void)
{
    char password[FINSH_PASSWORD_MAX] = { 0 };

    /* password not set */
    if (!rt_strlen(finsh_get_password()))
        return;

    while (1)
    {
        rt_kprintf("Password for login: ");
        finsh_wait_input_password(password);

        if (!rt_strncmp(shell->password, password, FINSH_PASSWORD_MAX))
            break;

        /* authentication failed, delay 2S for retry */
        rt_thread_delay(2 * RT_TICK_PER_SECOND);
        rt_kprintf("Sorry, password is incorrect, try again.\n");
        rt_memset(password, 0, FINSH_PASSWORD_MAX);
    }
}
#endif /* FINSH_USING_AUTH */

#ifdef FINSH_USING_HISTORY
static struct finsh_history *finsh_history_alloc(char *cmd, rt_size_t cmd_length)
{
    struct finsh_history *history;

#ifndef RT_USING_HEAP
    int i;
    for (i = 0; i < FINSH_HISTORY_LINES; i++)
    {
        /* Use list.next and list.prev to check if the current historical record is being used */
        if (shell->history[i].list.next && shell->history[i].list.prev)
            continue;
        history = &shell->history[i];
        break;
    }
    if (i >= FINSH_HISTORY_LINES)
    {
        rt_kprintf("No available historical record buffer zone!\n");
        return RT_NULL;
    }
#else
    history = (struct finsh_history *)rt_malloc(sizeof(*history));
    if (!history)
    {
        rt_kprintf("Failed to allocate memory for history!\n");
        return RT_NULL;
    }

    history->cmd = (char *)rt_calloc(1, cmd_length + 1);
    if (!history->cmd)
    {
        rt_free(history);
        rt_kprintf("Failed to allocate memory for history command!\n");
        return RT_NULL;
    }
#endif /* !RT_USING_HEAP */

    if (cmd)
        rt_strncpy(history->cmd, cmd, cmd_length);
    history->cmd[cmd_length] = 0; /* add null terminator */

    return history;
}

static void finsh_history_free(struct finsh_history *history)
{
#ifdef RT_USING_HEAP
    if (!history || !history->cmd)
#else
    if (!history)
#endif /* RT_USING_HEAP */
        return;

#ifdef RT_USING_HEAP
    rt_memset(history->cmd, 0, rt_strlen(history->cmd));
    rt_free(history->cmd);
#endif /* RT_USING_HEAP */
    rt_memset(history, 0, sizeof(*history));
#ifdef RT_USING_HEAP
    rt_free(history);
#endif /* RT_USING_HEAP */
}

static struct finsh_history *finsh_history_realloc(struct finsh_history *history, char *cmd, rt_size_t cmd_length)
{
    if (!history)
        return finsh_history_alloc(cmd, cmd_length);

#ifdef RT_USING_HEAP
    if (cmd_length > rt_strlen(history->cmd))
        history->cmd = (char *)rt_realloc(history->cmd, cmd_length + 1);
    if (!history->cmd)
    {
        rt_free(history);
        rt_kprintf("Failed to allocate memory for history command!\n");
        return RT_NULL;
    }
#endif /* RT_USING_HEAP */

    if (cmd)
        rt_strncpy(history->cmd, cmd, cmd_length);
    history->cmd[cmd_length] = 0; /* add null terminator */

    return history;
}
#endif /* FINSH_USING_HISTORY */

#ifdef FINSH_USING_SNAPSHOT
static struct finsh_snapshot *finsh_snapshot_alloc(char *cmd, rt_size_t cmd_length, rt_size_t cmd_cursor)
{
    struct finsh_snapshot *snap;

#ifndef RT_USING_HEAP
    int i;
    for (i = 0; i < FINSH_SNAPSHOT_DEPTH; i++)
    {
        if (shell->snapshot[i].list.next && shell->snapshot[i].list.prev)
            continue;
        snap = &shell->snapshot[i];
        break;
    }
    if (i >= FINSH_SNAPSHOT_DEPTH)
    {
        rt_kprintf("No available snapshot buffer!\n");
        return RT_NULL;
    }
#else
    snap = (struct finsh_snapshot *)rt_malloc(sizeof(*snap));
    if (!snap)
    {
        rt_kprintf("Failed to allocate memory for snapshot!\n");
        return RT_NULL;
    }

    snap->cmd = (char *)rt_calloc(1, cmd_length + 1);
    if (!snap->cmd)
    {
        rt_free(snap);
        rt_kprintf("Failed to allocate memory for snapshot command!\n");
        return RT_NULL;
    }
#endif /* !RT_USING_HEAP */

    if (cmd)
        rt_strncpy(snap->cmd, cmd, cmd_length);
    snap->cmd_cursor = cmd_cursor;
    snap->cmd_length = cmd_length;
    snap->cmd[cmd_length] = 0; /* add null terminator */

    return snap;
}

static void finsh_snapshot_free(struct finsh_snapshot *snap)
{
#ifdef RT_USING_HEAP
    if (!snap || !snap->cmd)
#else
    if (!snap)
#endif /* RT_USING_HEAP */
        return;

#ifdef RT_USING_HEAP
    rt_memset(snap->cmd, 0, snap->cmd_length);
    rt_free(snap->cmd);
#endif /* RT_USING_HEAP */
    rt_memset(snap, 0, sizeof(*snap));
#ifdef RT_USING_HEAP
    rt_free(snap);
#endif /* RT_USING_HEAP */
}

static struct finsh_snapshot *finsh_snapshot_realloc(struct finsh_snapshot *snap, char *cmd, rt_size_t cmd_length, rt_size_t cmd_cursor)
{
    if (!snap)
        return finsh_snapshot_alloc(cmd, cmd_length, cmd_cursor);

#ifdef RT_USING_HEAP
    if (cmd_length > rt_strlen(snap->cmd))
        snap->cmd = (char *)rt_realloc(snap->cmd, cmd_length + 1);
    if (!snap->cmd)
    {
        rt_free(snap);
        rt_kprintf("Failed to allocate memory for snapshot command!\n");
        return RT_NULL;
    }
#endif /* RT_USING_HEAP */

    if (cmd)
        rt_strncpy(snap->cmd, cmd, cmd_length);
    snap->cmd_cursor = cmd_cursor;
    snap->cmd_length = cmd_length;
    snap->cmd[cmd_length] = 0; /* add null terminator */

    return snap;
}
#endif /* FINSH_USING_SNAPSHOT */

static int finsh_shell_init(void)
{
#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    struct rt_device *console;
#endif /* !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE) */
    int ret;

    RT_ASSERT(shell != RT_NULL);

    ret = rt_sem_init(&shell->rx_notice, "shrx", 0, RT_IPC_FLAG_FIFO);
    if (ret)
    {
        rt_kprintf("Failed to initialize shell_rx_notice semaphore!\n");
        return -RT_EIO;
    }

    shell->input_state = FINSH_INPUT_STATE_NORMAL;

#ifdef FINSH_USING_HISTORY
    rt_list_init(&shell->history_list);
    shell->cur_history = &shell->history_list;
    shell->is_push_last_history = RT_FALSE;
#ifndef RT_USING_HEAP
    rt_memset(shell->history, 0, sizeof(shell->history));
#endif /* !RT_USING_HEAP */
#endif /* FINSH_USING_HISTORY */

    rt_memset(shell->cmd, 0, sizeof(shell->cmd));
    shell->cmd_length = 0;
    shell->cmd_cursor = 0;

    shell->extend_key = 0;
    shell->is_insert = RT_FALSE;
    shell->is_ctrl = RT_FALSE;

#ifndef FINSH_ECHO_DISABLE_DEFAULT
    shell->is_echo = RT_TRUE;
#else
    shell->is_echo = RT_FALSE;
#endif /* !FINSH_ECHO_DISABLE_DEFAULT */

#ifdef FINSH_PROMPT_ENABLE_DEFAULT
    shell->is_prompt = RT_TRUE;
#else
    shell->is_prompt = RT_FALSE;
#endif /* FINSH_PROMPT_ENABLE_DEFAULT */

#ifdef FINSH_USING_SNAPSHOT
    rt_list_init(&shell->snapshot_list);
    shell->cur_snapshot = &shell->snapshot_list;
    shell->is_push_last_snapshot = RT_FALSE;
    shell->snapshot_state = FINSH_SNAPSHOT_STATE_NONE;
#ifndef RT_USING_HEAP
    rt_memset(shell->snapshot, 0, sizeof(shell->snapshot));
#endif /* !RT_USING_HEAP */
#endif /* FINSH_USING_SNAPSHOT */

#ifdef FINSH_USING_AUTH
    rt_memset(shell->password, 0, sizeof(shell->password));
#endif /* FINSH_USING_AUTH */

#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    if (!shell->device)
    {
        console = rt_console_get_device();
        if (console)
            finsh_set_device(console->parent.name);
    }
    if (!shell->device)
    {
        rt_sem_detach(&shell->rx_notice);
        rt_kprintf("Finsh: can not find device!\n");
        return -RT_ENOENT;
    }
#endif /* !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE) */

    return 0;
}

static void finsh_shell_deinit(void)
{
#ifdef FINSH_USING_HISTORY
    struct finsh_history *history, *n;
#endif /* AT_BYPASS_USING_HISTORY */
#ifdef FINSH_USING_SNAPSHOT
    struct finsh_snapshot *snap, *s;
#endif /* AT_BYPASS_USING_SNAPSHOT */

    RT_ASSERT(shell != RT_NULL);

#ifdef FINSH_USING_HISTORY
    rt_list_for_each_entry_safe(history, n, &shell->history_list, list)
    {
        rt_list_remove(&history->list);
        finsh_history_free(history);
    }
#endif /* FINSH_USING_HISTORY */

#ifdef FINSH_USING_SNAPSHOT
    rt_list_for_each_entry_safe(snap, s, &shell->snapshot_list, list)
    {
        rt_list_remove(&snap->list);
        finsh_snapshot_free(snap);
    }
#endif /* FINSH_USING_SNAPSHOT */

#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
    if (shell->device)
    {
        rt_device_close(shell->device);
        rt_device_set_rx_indicate(shell->device, RT_NULL);
    }
    shell->device = RT_NULL;
#endif /* !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE) */

    rt_sem_detach(&shell->rx_notice);
}

/**
  * @brief Get a character from the shell input.
  *
  * This function reads a single character from the shell input source.
  * - If RT_USING_DEVICE is defined, it reads from the configured device.
  *   - If RT_USING_POSIX_STDIO is defined, it reads from the POSIX console file descriptor.
  *   - Otherwise, it reads from the shell's device using rt_device_read. If no data is available,
  *     it waits on the rx_notice semaphore until data arrives. If the device is unavailable, it returns -1 (EOF).
  * - If RT_USING_DEVICE is not defined, it reads from the hardware console using rt_hw_console_getchar.
  *
  * @return The character read on success, or -1 on failure or EOF.
  */
char finsh_getchar(void)
{
#ifdef RT_USING_DEVICE
    char ch;
#ifdef RT_USING_POSIX_STDIO
    return (read(rt_posix_stdio_get_console(), &ch, 1) > 0) ? ch : -1;
#else
    int ret;

    RT_ASSERT(shell != RT_NULL);

    if (!shell->device)
        return -1; /* EOF */

    ch = 0;
    while (rt_device_read(shell->device, -1, &ch, 1) != 1)
    {
        ret = rt_sem_take(&shell->rx_notice, RT_WAITING_FOREVER);
        if (ret || !shell->device)
            return -1;
    }

    return ch;
#endif /* RT_USING_POSIX_STDIO */
#else
    extern signed char rt_hw_console_getchar(void);
    return rt_hw_console_getchar();
#endif /* RT_USING_DEVICE */
}

/* clang-format off */
 #define finsh_printf(fmt, ...) do { if (shell->is_echo) rt_kprintf(fmt, ##__VA_ARGS__); } while (0)
 #define finsh_puts(str) do { if (shell->is_echo) rt_kputs(str); } while (0)
 #define finsh_putc(ch) do { if (shell->is_echo) rt_kprintf("%c", ch); } while (0)
/* clang-format on */

#ifdef FINSH_USING_SNAPSHOT
rt_inline int _is_snapshot_last(rt_list_t *node)
{
    return node == shell->snapshot_list.next;
}

static void finsh_push_snapshot(void)
{
    struct finsh_snapshot *snap, *pos, *n;
    rt_list_t *node;
    rt_uint32_t len;

    /* if current snapshot is not the last of the snapshot list, use the current snapshot */
    node = !_is_snapshot_last(shell->cur_snapshot) ? shell->cur_snapshot : RT_NULL;
    if (node)
        snap = rt_list_entry(node, struct finsh_snapshot, list);
    else
    {
        len = rt_list_len(&shell->snapshot_list);
        if (len > 0)
        {
            node = shell->cur_snapshot;
            snap = rt_list_entry(node, struct finsh_snapshot, list);
            if (snap->cmd_length == shell->cmd_length && !rt_strncmp(snap->cmd, shell->cmd, snap->cmd_length))
            {
                shell->is_push_last_snapshot = RT_FALSE;
                return;
            }
        }

        if (len < FINSH_SNAPSHOT_DEPTH)
            snap = RT_NULL;
        else
        {
            node = shell->snapshot_list.prev;
            snap = rt_list_entry(node, struct finsh_snapshot, list);
            rt_list_remove(&snap->list);
        }
    }

    snap = finsh_snapshot_realloc(snap, shell->cmd, shell->cmd_length, shell->cmd_cursor);
    if (!snap)
    {
        rt_kprintf("Failed to allocate memory for snapshot!\n");
        return;
    }

    /* if current snapshot is not the top of the snapshot list, remove the snapshot list */
    if (!_is_snapshot_last(shell->cur_snapshot))
    {
        rt_list_for_each_entry_safe(pos, n, &shell->snapshot_list, list)
        {
            rt_list_remove(&pos->list);
            if (&pos->list == shell->cur_snapshot)
                break;
            finsh_snapshot_free(pos);
        }
    }

    rt_list_insert_after(&shell->snapshot_list, &snap->list);
    /* Update cur_snapshot to point to the newly inserted snapshot (most recent). */
    shell->cur_snapshot = &snap->list;
    shell->is_push_last_snapshot = RT_FALSE;
}
#endif /* FINSH_USING_SNAPSHOT */

static void finsh_handle_backspace_key(void)
{
    rt_size_t cursor;
    int i;

#ifdef FINSH_USING_SNAPSHOT
    if (shell->cmd_length > 0 && shell->snapshot_state != FINSH_SNAPSHOT_STATE_BACKSPACE)
    {
        finsh_push_snapshot();
        shell->snapshot_state = FINSH_SNAPSHOT_STATE_BACKSPACE;
    }
#endif /* FINSH_USING_SNAPSHOT */

    /* if cursor is at the beginning of the command, do nothing */
    if (shell->cmd_cursor == 0)
        return;

    /* move index to the previous position */
    shell->cmd_length--;
    shell->cmd_cursor--;

    if (shell->cmd_cursor >= shell->cmd_length)
    {
        finsh_puts("\b \b");
        shell->cmd[shell->cmd_length] = 0;
        return;
    }

    cursor = shell->cmd_cursor;
    rt_memmove(&shell->cmd[cursor], &shell->cmd[cursor + 1], shell->cmd_length - cursor);
    shell->cmd[shell->cmd_length] = 0;

    finsh_printf("\b%s \b", &shell->cmd[cursor]);

    /* move the cursor to the origin position */
    for (i = cursor; i < shell->cmd_length; i++)
        finsh_putc('\b');
}

static void finsh_auto_complete(void)
{
    finsh_putc('\n');
    msh_auto_complete(shell->cmd);
#ifdef FINSH_USING_OPTION_COMPLETION
    msh_opt_auto_complete(shell->cmd);
#endif /* FINSH_USING_OPTION_COMPLETION */
    finsh_printf("%s%s", FINSH_PROMPT, shell->cmd);

    /* re-calculate position */
    shell->cmd_cursor = rt_strlen(shell->cmd);
    shell->cmd_length = shell->cmd_cursor;
}

#if defined(FINSH_USING_WORD_OPERATION) || defined(FINSH_USING_SNAPSHOT) || defined(FINSH_USING_HISTORY)
static void finsh_render_line(void)
{
#ifdef _WIN32
    int i;

    finsh_putc('\r');
    for (i = 0; i <= 60; i++)
        finsh_putc(' ');
    finsh_putc('\r');
#else /* _WIN32 */
    finsh_puts("\033[2K\r"); /* 2K: clear the line, \r: return to the beginning of the line */
#endif /* _WIN32 */
    finsh_printf("%s%s", FINSH_PROMPT, shell->cmd);

    if (shell->cmd_cursor < shell->cmd_length)
        finsh_printf("\033[%dD", (int)(shell->cmd_length - shell->cmd_cursor));
}
#endif /* FINSH_USING_WORD_OPERATION || FINSH_USING_SNAPSHOT || FINSH_USING_HISTORY */

#ifdef FINSH_USING_WORD_OPERATION // 123 456 789
rt_inline int _is_word_char(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_';
}

static void finsh_handle_ctrl_backspace_key(void)
{
    rt_size_t cursor, start_cursor, delete_count;
    rt_bool_t is_word_char;

    /* if cursor is at the beginning, do nothing */
    if (shell->cmd_cursor == 0)
        return;

    start_cursor = shell->cmd_cursor;
    cursor = shell->cmd_cursor;
    while (cursor > 0 && shell->cmd[cursor - 1] == ' ')
        cursor--;
    is_word_char = cursor > 0 && _is_word_char(shell->cmd[cursor - 1]);

    /* find the start of the word to delete */
    while (cursor > 0 && is_word_char && _is_word_char(shell->cmd[cursor - 1]))
        cursor--;
    while (cursor > 0 && !is_word_char && !_is_word_char(shell->cmd[cursor - 1]))
        cursor--;

    /* calculate how many characters to delete */
    delete_count = start_cursor - cursor;
    if (delete_count == 0)
        return;

#ifdef FINSH_USING_SNAPSHOT
    finsh_push_snapshot();
#endif /* FINSH_USING_SNAPSHOT */

    /* move the remaining characters to fill the gap */
    rt_memmove(&shell->cmd[cursor], &shell->cmd[start_cursor], shell->cmd_length - start_cursor);
    shell->cmd_length -= delete_count;
    rt_memset(&shell->cmd[shell->cmd_length], 0, delete_count);
    shell->cmd_cursor = cursor;

    finsh_render_line();
}
#endif /* FINSH_USING_WORD_OPERATION */

#ifdef FINSH_USING_SNAPSHOT
rt_inline int _is_snapshot_tail(rt_list_t *node)
{
    return node == shell->snapshot_list.prev;
}

static void finsh_pop_snapshot(void)
{
    struct finsh_snapshot *snap;
    rt_list_t *node;

    if (rt_list_isempty(&shell->snapshot_list))
        return;

    if (!shell->is_push_last_snapshot)
    {
        finsh_push_snapshot();
        shell->is_push_last_snapshot = RT_TRUE;
    }

    if (_is_snapshot_tail(shell->cur_snapshot))
        return;

    node = shell->cur_snapshot->next;
    snap = rt_list_entry(node, struct finsh_snapshot, list);
    rt_memset(shell->cmd, 0, sizeof(shell->cmd));
    rt_strncpy(shell->cmd, snap->cmd, snap->cmd_length);
    shell->cmd_length = snap->cmd_length;
    shell->cmd_cursor = snap->cmd_cursor;

    finsh_render_line();
    shell->cur_snapshot = node;
}

rt_inline int _is_snapshot_head(rt_list_t *node)
{
    return node == &shell->snapshot_list;
}

static void finsh_rollback_snapshot(void)
{
    struct finsh_snapshot *snap;
    rt_list_t *node;

    if (rt_list_isempty(&shell->snapshot_list))
        return;

    node = shell->cur_snapshot->prev;
    if (_is_snapshot_head(node))
        return;

    snap = rt_list_entry(node, struct finsh_snapshot, list);
    rt_memset(shell->cmd, 0, sizeof(shell->cmd));
    rt_strncpy(shell->cmd, snap->cmd, snap->cmd_length);
    shell->cmd_length = snap->cmd_length;
    shell->cmd_cursor = snap->cmd_cursor;

    finsh_render_line();
    shell->cur_snapshot = node;
}
#endif /* FINSH_USING_SNAPSHOT */

#ifdef FINSH_USING_HISTORY
rt_inline int _is_history_head(rt_list_t *node)
{
    return node == &shell->history_list;
}

rt_inline int _is_history_last(rt_list_t *node)
{
    return node == shell->history_list.next;
}

static void finsh_push_history(void)
{
    struct finsh_history *history;
    rt_list_t *node;
    rt_uint32_t len;

    /* if command is empty, do nothing */
    if (shell->cmd_length == 0)
        return;

    /* if current history is not the head of the history list, check if the command is the same as the current history */
    if (!_is_history_head(shell->cur_history))
    {
        node = shell->cur_history;
        history = rt_list_entry(node, struct finsh_history, list);
        len = rt_strlen(history->cmd);
        if (len == shell->cmd_length && !rt_strncmp(history->cmd, shell->cmd, len))
        {
            if (!_is_history_last(node))
            {
                rt_list_remove(&history->list);
                rt_list_insert_after(&shell->history_list, &history->list);
                shell->cur_history = &history->list;
            }
            shell->is_push_last_history = RT_TRUE;
            return;
        }
    }

    /* if the history list is not full, allocate a new history */
    len = rt_list_len(&shell->history_list);
    if (len < FINSH_HISTORY_LINES)
        history = RT_NULL;
    else
    {
        /* if the history list is full, remove the last history */
        node = shell->history_list.prev;
        history = rt_list_entry(node, struct finsh_history, list);
        rt_list_remove(&history->list);
    }

    history = finsh_history_realloc(history, shell->cmd, shell->cmd_length);
    if (!history)
    {
        rt_kprintf("Failed to allocate memory for new history!\n");
        return;
    }

    /* insert the new history to the head of the history list */
    rt_list_insert_after(&shell->history_list, &history->list);

    shell->cur_history = &history->list;
    shell->is_push_last_history = RT_TRUE;
}
#endif /* FINSH_USING_HISTORY */

static void finsh_handle_enter_key(void)
{
#ifdef FINSH_USING_SNAPSHOT
    struct finsh_snapshot *snap, *n;
#endif /* FINSH_USING_SNAPSHOT */

#ifdef FINSH_USING_HISTORY
    finsh_push_history();
#endif /* FINSH_USING_HISTORY */

    rt_kprintf("\n");
    msh_exec(shell->cmd, shell->cmd_length);
    rt_kprintf(FINSH_PROMPT);
    rt_memset(shell->cmd, 0, sizeof(shell->cmd));
    shell->cmd_cursor = 0;
    shell->cmd_length = 0;

#ifdef FINSH_USING_SNAPSHOT
    rt_list_for_each_entry_safe(snap, n, &shell->snapshot_list, list)
    {
        rt_list_remove(&snap->list);
        finsh_snapshot_free(snap);
    }
    rt_list_init(&shell->snapshot_list);
    shell->cur_snapshot = &shell->snapshot_list;
    shell->snapshot_state = FINSH_SNAPSHOT_STATE_NONE;
#endif /* FINSH_USING_SNAPSHOT */
}

rt_inline void _finsh_add_key_by_insert(char ch)
{
    rt_size_t cursor;

    cursor = shell->cmd_cursor;
    shell->cmd[cursor] = ch;
    finsh_putc(ch);

    shell->cmd_cursor++;
}

rt_inline void _finsh_add_key_by_normal(char ch)
{
    rt_size_t cursor;
    int i;

    cursor = shell->cmd_cursor;
    rt_memmove(&shell->cmd[cursor + 1], &shell->cmd[cursor], shell->cmd_length - cursor);
    shell->cmd[cursor] = ch;

    finsh_puts(&shell->cmd[cursor]);
    for (i = cursor; i < shell->cmd_length; i++)
        finsh_putc('\b');

    shell->cmd_cursor++;
    shell->cmd_length++;
}

static void finsh_handle_normal_key(char ch)
{
    switch (ch)
    {
    case 0x1B: /* ESC key */
        shell->input_state = FINSH_INPUT_STATE_SPECIFIED_KEY;
        return;
    case 0x08: /* backspace key */
    case 0x7F:
        finsh_handle_backspace_key();
        return;
    case 0x09: /* tab key */
        finsh_auto_complete();
        return;
    case 0x17: /* Ctrl+W/Backspace delete word */
#ifdef FINSH_USING_WORD_OPERATION
        finsh_handle_ctrl_backspace_key();
#endif /* FINSH_USING_WORD_OPERATION */
        return;
    case 0x1A: /* Ctrl+Z pop snapshot */
#ifdef FINSH_USING_SNAPSHOT
        finsh_pop_snapshot();
#endif /* FINSH_USING_SNAPSHOT */
        return;
    case 0x19: /* Ctrl+Y rollback snapshot */
#ifdef FINSH_USING_SNAPSHOT
        finsh_rollback_snapshot();
#endif /* FINSH_USING_SNAPSHOT */
        return;
    case '\r': /* enter key */
    case '\n': /* newline key */
        finsh_handle_enter_key();
        return;
    case ' ': /* space key */
#ifdef FINSH_USING_SNAPSHOT
        if (!shell->is_space_snapshot)
        {
            shell->snapshot_state = FINSH_SNAPSHOT_STATE_SPACE;
            shell->is_space_snapshot = RT_TRUE;
        }
#endif /* FINSH_USING_SNAPSHOT */
        break;
    default:
        if (ch > 0x7E || ch < 0x21)
        {
            rt_kprintf("Invalid character: %d!\n", ch);
            return;
        }
#ifdef FINSH_USING_SNAPSHOT
        shell->is_space_snapshot = RT_FALSE;
#endif /* FINSH_USING_SNAPSHOT */
        break;
    }

#ifdef FINSH_USING_SNAPSHOT
    if (shell->snapshot_state != FINSH_SNAPSHOT_STATE_NORMAL)
    {
        finsh_push_snapshot();
        shell->snapshot_state = FINSH_SNAPSHOT_STATE_NORMAL;
    }
#endif /* FINSH_USING_SNAPSHOT */

    if (shell->cmd_length >= FINSH_CMD_SIZE)
    {
        shell->cmd_length = 0;
        shell->cmd_cursor = 0;
    }

    if (shell->cmd_cursor >= shell->cmd_length)
    {
        shell->cmd[shell->cmd_length] = ch;
        finsh_putc(ch);
        shell->cmd_length++;
        shell->cmd_cursor++;
    }
    else
        shell->is_insert ? _finsh_add_key_by_insert(ch) : _finsh_add_key_by_normal(ch);
}

rt_inline void _finsh_handle_specified_key(char ch)
{
#ifdef FINSH_USING_SNAPSHOT
    if (shell->cmd_length > 0 && shell->snapshot_state != FINSH_SNAPSHOT_STATE_ESC)
    {
        finsh_push_snapshot();
        shell->snapshot_state = FINSH_SNAPSHOT_STATE_ESC;
    }
#endif /* FINSH_USING_SNAPSHOT */
    shell->input_state = ch == 0x5B ? FINSH_INPUT_STATE_FUNCTION_KEY : FINSH_INPUT_STATE_NORMAL;
}

#ifdef FINSH_USING_HISTORY
static void finsh_pop_history(int ch)
{
    struct finsh_history *history;
    rt_list_t *node;

    if (rt_list_isempty(&shell->history_list))
        return;

    node = shell->cur_history;
    if (!shell->is_push_last_history)
        node = ch == 0x41 ? node->next : node->prev;
    else
        shell->is_push_last_history = RT_FALSE;

    if (_is_history_head(node))
        node = shell->cur_history;
    else
        shell->cur_history = node;

    history = rt_list_entry(node, struct finsh_history, list);
    shell->cmd_length = rt_strlen(history->cmd);
    shell->cmd_cursor = shell->cmd_length;
    rt_memset(shell->cmd, 0, sizeof(shell->cmd));
    rt_memcpy(shell->cmd, history->cmd, shell->cmd_length);

    finsh_render_line();
}
#endif /* FINSH_USING_HISTORY */

rt_inline void _finsh_handle_left_key(void)
{
    if (shell->cmd_cursor > 0)
    {
        finsh_putc('\b');
        shell->cmd_cursor--;
    }
}

rt_inline void _finsh_handle_right_key(void)
{
    if (shell->cmd_cursor < shell->cmd_length)
    {
        finsh_putc(shell->cmd[shell->cmd_cursor]);
        shell->cmd_cursor++;
    }
}

#ifdef FINSH_USING_EXTEND_FEATURE
rt_inline void _finsh_handle_home_key(void)
{
    int i;

    for (i = 0; i < shell->cmd_cursor; i++)
        finsh_putc('\b');
    shell->cmd_cursor = 0;
}

rt_inline void _finsh_handle_end_key(void)
{
    int i;

    for (i = shell->cmd_cursor; i < shell->cmd_length; i++)
        finsh_putc(shell->cmd[i]);
    shell->cmd_cursor = shell->cmd_length;
}
#endif /* FINSH_USING_EXTEND_FEATURE */

static void finsh_handle_function_key(char ch)
{
    /* if the key is the extend key, set the input state to extend key */
    if (ch >= 0x31 && ch <= 0x34)
    {
        shell->extend_key = ch;
        shell->input_state = FINSH_INPUT_STATE_EXTEND_KEY;
        return;
    }

    switch (ch)
    {
    case 0x41: /* up key */
    case 0x42: /* down key */
#ifdef FINSH_USING_HISTORY
        finsh_pop_history(ch);
#endif /* FINSH_USING_HISTORY */
        break;
    case 0x44: /* left key */
        _finsh_handle_left_key();
        break;
    case 0x43: /* right key */
        _finsh_handle_right_key();
        break;
    case 0x46: /* end key */
#ifdef FINSH_USING_EXTEND_FEATURE
        _finsh_handle_end_key();
#endif /* FINSH_USING_EXTEND_FEATURE */
        break;
    case 0x48: /* home key */
#ifdef FINSH_USING_EXTEND_FEATURE
        _finsh_handle_home_key();
#endif /* FINSH_USING_EXTEND_FEATURE */
        break;
    default:
        rt_kprintf("Invalid function key: %d!\n", ch);
        break;
    }

    shell->input_state = FINSH_INPUT_STATE_NORMAL;
}

#ifdef FINSH_USING_EXTEND_FEATURE
static void finsh_handle_delete_key(void)
{
    rt_size_t cursor;
    int i;

    /* if cursor is at the end of the command, do nothing */
    if (shell->cmd_cursor >= shell->cmd_length)
        return;

    /* move index to the previous position */
    shell->cmd_length--;

    cursor = shell->cmd_cursor;
    rt_memmove(&shell->cmd[cursor], &shell->cmd[cursor + 1], shell->cmd_length - cursor);
    shell->cmd[shell->cmd_length] = 0;

    finsh_printf("%s \b", &shell->cmd[cursor]);

    /* move the cursor to the origin position */
    for (i = cursor; i < shell->cmd_length; i++)
        finsh_putc('\b');
}
#endif /* FINSH_USING_EXTEND_FEATURE */

static void finsh_handle_extend_key(char ch)
{
    /* if not the end of the key, do nothing */
    if (ch != 0x7E)
    {
        shell->extend_key = 0;
        shell->input_state = ch == 0x3B ? FINSH_INPUT_STATE_CTRL_SEQUENCE : FINSH_INPUT_STATE_NORMAL;
        return;
    }

#ifdef FINSH_USING_EXTEND_FEATURE
    switch (shell->extend_key)
    {
    case 0x32: /* insert key */
        shell->is_insert = !shell->is_insert;
        break;
    case 0x33: /* delete key */
        finsh_handle_delete_key();
        break;
    case 0x31: /* home key */
        _finsh_handle_home_key();
        break;
    case 0x34: /* end key */
        _finsh_handle_end_key();
        break;
    default:
        rt_kprintf("Invalid extend key: %d!\n", shell->extend_key);
        break;
    }
#endif /* FINSH_USING_EXTEND_FEATURE */

    /* reset extend key */
    shell->extend_key = 0;
    shell->input_state = FINSH_INPUT_STATE_NORMAL;
}

#ifdef FINSH_USING_WORD_OPERATION
static void finsh_handle_ctrl_left_key(void)
{
    rt_size_t cursor;
    rt_bool_t is_word_char;

    /* if already at the beginning, do nothing */
    if (shell->cmd_cursor == 0)
        return;

    cursor = shell->cmd_cursor;
    while (cursor > 0 && shell->cmd[cursor - 1] == ' ')
        cursor--;
    is_word_char = cursor > 0 && _is_word_char(shell->cmd[cursor - 1]);

    while (cursor > 0 && is_word_char && _is_word_char(shell->cmd[cursor - 1]))
        cursor--;
    while (cursor > 0 && !is_word_char && !_is_word_char(shell->cmd[cursor - 1]))
        cursor--;

    /* calculate steps to move and move cursor */
    finsh_printf("\033[%dD", shell->cmd_cursor - cursor);

    shell->cmd_cursor = cursor;
}

static void finsh_handle_ctrl_right_key(void)
{
    rt_size_t cursor;
    rt_bool_t is_word_char;

    /* if already at the end, do nothing */
    if (shell->cmd_cursor >= shell->cmd_length)
        return;

    cursor = shell->cmd_cursor;
    while (cursor < shell->cmd_length && shell->cmd[cursor] == ' ')
        cursor++;
    is_word_char = cursor < shell->cmd_length && _is_word_char(shell->cmd[cursor]);

    while (cursor < shell->cmd_length && is_word_char && _is_word_char(shell->cmd[cursor]))
        cursor++;
    while (cursor < shell->cmd_length && !is_word_char && !_is_word_char(shell->cmd[cursor]))
        cursor++;

    /* display moved characters */
    finsh_printf("\033[%dC", cursor - shell->cmd_cursor);

    shell->cmd_cursor = cursor;
}
#endif /* FINSH_USING_WORD_OPERATION */

static void finsh_handle_ctrl_sequence(char ch)
{
    if (!shell->is_ctrl)
    {
        /* if the key is the ctrl key, set the input state to ctrl sequence */
        if (ch == 0x35)
            shell->is_ctrl = RT_TRUE;
        else
            shell->input_state = FINSH_INPUT_STATE_NORMAL;
        return;
    }

#ifdef FINSH_USING_WORD_OPERATION
    switch (ch)
    {
    case 0x44: /* Ctrl+left key */
        finsh_handle_ctrl_left_key();
        break;
    case 0x43: /* Ctrl+right key */
        finsh_handle_ctrl_right_key();
        break;
    case 0x7F: /* Ctrl+W/Backspace delete word */
        finsh_handle_ctrl_backspace_key();
        break;
    default:
        rt_kprintf("Invalid Ctrl sequence: %d!\n", ch);
        break;
    }
#endif /* FINSH_USING_WORD_OPERATION */

    shell->is_ctrl = RT_FALSE;
    shell->input_state = FINSH_INPUT_STATE_NORMAL;
}

static void finsh_thread_entry(void *parameter)
{
    char ch;

    RT_OBJECT_HOOK_CALL(_finsh_thread_entry_hook, ());

    if (finsh_shell_init())
        return;

#ifdef FINSH_USING_AUTH
    /* set the default password when the password isn't setting */
    if (!rt_strlen(finsh_get_password()))
        finsh_set_password(FINSH_DEFAULT_PASSWORD);
    /* waiting authenticate success */
    finsh_password_auth();
#endif /* FINSH_USING_AUTH */

    rt_kprintf(FINSH_PROMPT);
    while (1)
    {
        ch = finsh_getchar();
        if (ch <= 0)
            continue;

        /*
          * handle control key
          * up key:          0x1B 0x5B 0x41
          * down key:        0x1B 0x5B 0x42
          * right key:       0x1B 0x5B 0x43
          * left key:        0x1B 0x5B 0x44
          * end key:         0x1B 0x5B 0x46
          * home key:        0x1B 0x5B 0x48
          *
          * handle extend key
          * home key:        0x1B 0x5B 0x31 0x7E
          * insert key:      0x1B 0x5B 0x32 0x7E
          * delete key:      0x1B 0x5B 0x33 0x7E
          * end key:         0x1B 0x5B 0x34 0x7E
          *
          * handle Ctrl sequence
          * Ctrl+left:       0x1B 0x5B 0x31 0x3B 0x35 0x44 (jump to previous word)
          * Ctrl+right:      0x1B 0x5B 0x31 0x3B 0x35 0x43 (jump to next word)
          * Ctrl+backspace/w:0x1B 0x5B 0x31 0x3B 0x35 0x7F (delete word)
          */

        switch (shell->input_state)
        {
        case FINSH_INPUT_STATE_NORMAL:
            finsh_handle_normal_key(ch);
            break;
        case FINSH_INPUT_STATE_SPECIFIED_KEY:
            _finsh_handle_specified_key(ch);
            break;
        case FINSH_INPUT_STATE_FUNCTION_KEY:
            finsh_handle_function_key(ch);
            break;
        case FINSH_INPUT_STATE_EXTEND_KEY:
            finsh_handle_extend_key(ch);
            break;
        case FINSH_INPUT_STATE_CTRL_SEQUENCE:
            finsh_handle_ctrl_sequence(ch);
            break;
        default:
            rt_kprintf("Invalid input state: %d", shell->input_state);
            break;
        }
    }
}

static void finsh_system_function_init(const void *begin, const void *end)
{
    _syscall_table_begin = (struct finsh_syscall *)begin;
    _syscall_table_end = (struct finsh_syscall *)end;
}

#if defined(__ICCARM__) || defined(__ICCRX__) /* for IAR compiler */
#ifdef FINSH_USING_SYMTAB
#pragma section = "FSymTab"
#endif /* FINSH_USING_SYMTAB */
#elif defined(__ADSPBLACKFIN__) /* for VisaulDSP++ Compiler*/
#ifdef FINSH_USING_SYMTAB
extern "asm" int __fsymtab_start;
extern "asm" int __fsymtab_end;
#endif /* FINSH_USING_SYMTAB */
#elif defined(_MSC_VER)
#pragma section("FSymTab$a", read)
const char __fsym_begin_name[] = "__start";
const char __fsym_begin_desc[] = "begin of finsh";
__declspec(allocate("FSymTab$a")) const struct finsh_syscall __fsym_begin = {
    __fsym_begin_name,
    __fsym_begin_desc,
    RT_NULL,
};

#pragma section("FSymTab$z", read)
const char __fsym_end_name[] = "__end";
const char __fsym_end_desc[] = "end of finsh";
__declspec(allocate("FSymTab$z")) const struct finsh_syscall __fsym_end = {
    __fsym_end_name,
    __fsym_end_desc,
    RT_NULL,
};
#endif /* _MSC_VER */

/**
  * @brief Initialize the finsh shell system.
  *
  * This function initializes the finsh shell, including allocating memory for the shell structure,
  * setting up the system call table if symbol table support is enabled, and creating or initializing
  * the shell thread. It supports different compilers and memory allocation strategies (heap or static).
  * If the shell is already initialized, it will not re-initialize.
  *
  * @return 0 on success, negative error code on failure.
  */
int finsh_system_init(void)
{
    rt_thread_t tid;

    if (shell)
    {
        rt_kprintf("Finsh shell already initialized.\n");
        return 0;
    }

#ifdef FINSH_USING_SYMTAB
#ifdef __ARMCC_VERSION /* ARM C Compiler */
    extern const int FSymTab$$Base;
    extern const int FSymTab$$Limit;
    finsh_system_function_init(&FSymTab$$Base, &FSymTab$$Limit);
#elif defined(__ICCARM__) || defined(__ICCRX__) /* for IAR Compiler */
    finsh_system_function_init(__section_begin("FSymTab"), __section_end("FSymTab"));
#elif defined(__GNUC__) || defined(__TI_COMPILER_VERSION__) || defined(__TASKING__)
    /* GNU GCC Compiler and TI CCS */
    extern const int __fsymtab_start;
    extern const int __fsymtab_end;
    finsh_system_function_init(&__fsymtab_start, &__fsymtab_end);
#elif defined(__ADSPBLACKFIN__) /* for VisualDSP++ Compiler */
    finsh_system_function_init(&__fsymtab_start, &__fsymtab_end);
#elif defined(_MSC_VER)
    rt_ubase_t *ptr_begin, *ptr_end;

    ptr_begin = (rt_ubase_t *)&__fsym_begin;
    ptr_begin += (sizeof(struct finsh_syscall) / sizeof(rt_ubase_t));
    while (*ptr_begin == 0)
        ptr_begin++;

    ptr_end = (rt_ubase_t *)&__fsym_end;
    ptr_end--;
    while (*ptr_end == 0)
        ptr_end--;

    finsh_system_function_init(ptr_begin, ptr_end);
#endif /* _MSC_VER */
#endif /* FINSH_USING_SYMTAB */

#ifdef RT_USING_HEAP
    shell = (struct finsh_shell *)rt_calloc(1, sizeof(*shell));
    if (!shell)
    {
        rt_kprintf("No memory for shell!\n");
        return -RT_ENOMEM;
    }
    tid = rt_thread_create(FINSH_THREAD_NAME, finsh_thread_entry, RT_NULL, FINSH_THREAD_STACK_SIZE, FINSH_THREAD_PRIORITY, 10);
    if (!tid)
    {
        rt_free(shell);
        rt_kprintf("Create finsh thread failed!\n");
        return -RT_ENOMEM;
    }
#else
    int ret;
    ret = rt_thread_init(&finsh_thread, FINSH_THREAD_NAME, finsh_thread_entry, RT_NULL, &finsh_thread_stack[0], sizeof(finsh_thread_stack), FINSH_THREAD_PRIORITY, 10);
    if (ret)
    {
        rt_kprintf("Init finsh thread failed!\n");
        return ret;
    }
    shell = &_shell;
    tid = &finsh_thread;
#endif /* RT_USING_HEAP */

    return rt_thread_startup(tid);
}
INIT_APP_EXPORT(finsh_system_init);

/**
  * @brief Deinitialize the FinSH shell system.
  *
  * This function performs a complete deinitialization of the FinSH shell system.
  * It first deinitializes the shell's internal state and resources, then closes
  * and detaches the associated device if it exists. The function also finds and
  * deletes the shell thread, and finally clears the shell structure memory.
  *
  * @return 0 on success.
  */
int finsh_system_deinit(void)
{
    rt_thread_t tid;

    RT_ASSERT(shell != RT_NULL);

    finsh_shell_deinit();

    tid = rt_thread_find(FINSH_THREAD_NAME);
    if (tid)
    {
#ifdef RT_USING_HEAP
        rt_thread_delete(tid);
#else
        rt_thread_detach(tid);
#endif /* RT_USING_HEAP */
    }

    rt_memset(shell, 0, sizeof(*shell));

    return 0;
}

#endif /* RT_USING_FINSH */
