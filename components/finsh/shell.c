/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
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
 */

#include <rthw.h>
#include <string.h>
#include <stdio.h>

#ifdef RT_USING_MSH

#include "shell.h"
#include "msh.h"

#ifdef RT_USING_POSIX
#include <dfs_posix.h>
#endif /* RT_USING_POSIX */

/* msh thread */
#ifndef RT_USING_HEAP
    static struct rt_thread msh_thread;
    ALIGN(RT_ALIGN_SIZE)
    static char msh_thread_stack[MSH_THREAD_STACK_SIZE];
    struct msh_shell _shell;
#endif

/* msh symtab */
#ifdef MSH_USING_SYMTAB
    struct msh_syscall *_syscall_table_begin  = NULL;
    struct msh_syscall *_syscall_table_end    = NULL;
#endif

struct msh_shell *shell;
static char *msh_prompt_custom = RT_NULL;

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__))
struct msh_syscall *msh_syscall_next(struct msh_syscall *call)
{
    unsigned int *ptr;
    ptr = (unsigned int *)(call + 1);
    while ((*ptr == 0) && ((unsigned int *)ptr < (unsigned int *) _syscall_table_end))
        ptr ++;

    return (struct msh_syscall *)ptr;
}

#endif /* defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__)) */

#ifdef RT_USING_HEAP
int msh_set_prompt(const char *prompt)
{
    if (msh_prompt_custom)
    {
        rt_free(msh_prompt_custom);
        msh_prompt_custom = RT_NULL;
    }

    /* strdup */
    if (prompt)
    {
        msh_prompt_custom = (char *)rt_malloc(strlen(prompt) + 1);
        if (msh_prompt_custom)
        {
            strcpy(msh_prompt_custom, prompt);
        }
    }

    return 0;
}
#endif /* RT_USING_HEAP */

#define _MSH_PROMPT "msh "

const char *msh_get_prompt(void)
{
    static char msh_prompt[RT_CONSOLEBUF_SIZE + 1] = {0};

    /* check prompt mode */
    if (!shell->prompt_mode)
    {
        msh_prompt[0] = '\0';
        return msh_prompt;
    }

    if (msh_prompt_custom)
    {
        strncpy(msh_prompt, msh_prompt_custom, sizeof(msh_prompt) - 1);
        return msh_prompt;
    }
    strcpy(msh_prompt, _MSH_PROMPT);

#if defined(RT_USING_POSIX) && defined(DFS_USING_WORKDIR)
    /* get current working directory */
    getcwd(&msh_prompt[rt_strlen(msh_prompt)], RT_CONSOLEBUF_SIZE - rt_strlen(msh_prompt));
#endif

    strcat(msh_prompt, ">");

    return msh_prompt;
}

/**
 * @ingroup msh
 *
 * This function get the prompt mode of msh shell.
 *
 * @return prompt the prompt mode, 0 disable prompt mode, other values enable prompt mode.
 */
rt_uint32_t msh_get_prompt_mode(void)
{
    RT_ASSERT(shell != RT_NULL);
    return shell->prompt_mode;
}

/**
 * @ingroup msh
 *
 * This function set the prompt mode of msh shell.
 *
 * The parameter 0 disable prompt mode, other values enable prompt mode.
 *
 * @param prompt the prompt mode
 */
void msh_set_prompt_mode(rt_uint32_t prompt_mode)
{
    RT_ASSERT(shell != RT_NULL);
    shell->prompt_mode = prompt_mode;
}

int msh_getchar(void)
{
#ifdef RT_USING_DEVICE
    char ch = 0;
#ifdef RT_USING_POSIX
    if(read(STDIN_FILENO, &ch, 1) > 0)
    {
        return ch;
    }
    else
    {
        return -1; /* EOF */
    }
#else
    rt_device_t device;

    RT_ASSERT(shell != RT_NULL);

    device = shell->device;
    if (device == RT_NULL)
    {
        return -1; /* EOF */
    }

    while (rt_device_read(device, -1, &ch, 1) != 1)
        rt_sem_take(&shell->rx_sem, RT_WAITING_FOREVER);

    return ch;
#endif /* RT_USING_POSIX */
#else
    extern char rt_hw_console_getchar(void);
    return rt_hw_console_getchar();
#endif /* RT_USING_DEVICE */
}

#if !defined(RT_USING_POSIX) && defined(RT_USING_DEVICE)
static rt_err_t msh_rx_ind(rt_device_t dev, rt_size_t size)
{
    RT_ASSERT(shell != RT_NULL);

    /* release semaphore to let msh thread rx data */
    rt_sem_release(&shell->rx_sem);

    return RT_EOK;
}

/**
 * @ingroup msh
 *
 * This function sets the input device of msh shell.
 *
 * @param device_name the name of new input device.
 */
void msh_set_device(const char *device_name)
{
    rt_device_t dev = RT_NULL;

    RT_ASSERT(shell != RT_NULL);
    dev = rt_device_find(device_name);
    if (dev == RT_NULL)
    {
        rt_kprintf("msh: can not find device: %s\n", device_name);
        return;
    }

    /* check whether it's a same device */
    if (dev == shell->device) return;
    /* open this device and set the new device in msh shell */
    if (rt_device_open(dev, RT_DEVICE_OFLAG_RDWR | RT_DEVICE_FLAG_INT_RX | \
                       RT_DEVICE_FLAG_STREAM) == RT_EOK)
    {
        if (shell->device != RT_NULL)
        {
            /* close old msh device */
            rt_device_close(shell->device);
            rt_device_set_rx_indicate(shell->device, RT_NULL);
        }

        /* clear line buffer before switch to new device */
        memset(shell->line, 0, sizeof(shell->line));
        shell->line_curpos = shell->line_position = 0;

        shell->device = dev;
        rt_device_set_rx_indicate(dev, msh_rx_ind);
    }
}

/**
 * @ingroup msh
 *
 * This function returns current msh shell input device.
 *
 * @return the msh shell input device name is returned.
 */
const char *msh_get_device()
{
    RT_ASSERT(shell != RT_NULL);
    return shell->device->parent.name;
}
#endif

/**
 * @ingroup msh
 *
 * This function set the echo mode of msh shell.
 *
 * MSH_OPTION_ECHO=0x01 is echo mode, other values are none-echo mode.
 *
 * @param echo the echo mode
 */
void msh_set_echo(rt_uint32_t echo)
{
    RT_ASSERT(shell != RT_NULL);
    shell->echo_mode = (rt_uint8_t)echo;
}

/**
 * @ingroup msh
 *
 * This function gets the echo mode of msh shell.
 *
 * @return the echo mode
 */
rt_uint32_t msh_get_echo()
{
    RT_ASSERT(shell != RT_NULL);

    return shell->echo_mode;
}

#ifdef MSH_USING_AUTH
/**
 * set a new password for msh
 *
 * @param password new password
 *
 * @return result, RT_EOK on OK, -RT_ERROR on the new password length is less than
 *  MSH_PASSWORD_MIN or greater than MSH_PASSWORD_MAX
 */
rt_err_t msh_set_password(const char *password)
{
    rt_ubase_t level;
    rt_size_t pw_len = rt_strlen(password);

    if (pw_len < MSH_PASSWORD_MIN || pw_len > MSH_PASSWORD_MAX)
        return -RT_ERROR;

    level = rt_hw_interrupt_disable();
    rt_strncpy(shell->password, password, MSH_PASSWORD_MAX);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * get the msh password
 *
 * @return password
 */
const char *msh_get_password(void)
{
    return shell->password;
}

static void msh_wait_auth(void)
{
    int ch;
    rt_bool_t input_finish = RT_FALSE;
    char password[MSH_PASSWORD_MAX] = { 0 };
    rt_size_t cur_pos = 0;
    /* password not set */
    if (rt_strlen(msh_get_password()) == 0) return;

    while (1)
    {
        rt_kprintf("Password for login: ");
        while (!input_finish)
        {
            while (1)
            {
                /* read one character from device */
                ch = (int)msh_getchar();
                if (ch < 0)
                {
                    continue;
                }

                if (ch >= ' ' && ch <= '~' && cur_pos < MSH_PASSWORD_MAX)
                {
                    /* change the printable characters to '*' */
                    rt_kprintf("*");
                    password[cur_pos++] = ch;
                }
                else if (ch == '\b' && cur_pos > 0)
                {
                    /* backspace */
                    cur_pos--;
                    password[cur_pos] = '\0';
                    rt_kprintf("\b \b");
                }
                else if (ch == '\r' || ch == '\n')
                {
                    rt_kprintf("\n");
                    input_finish = RT_TRUE;
                    break;
                }
            }
        }
        if (!rt_strncmp(shell->password, password, MSH_PASSWORD_MAX)) return;
        else
        {
            /* authentication failed, delay 2S for retry */
            rt_thread_delay(2 * RT_TICK_PER_SECOND);
            rt_kprintf("Sorry, try again.\n");
            cur_pos = 0;
            input_finish = RT_FALSE;
            rt_memset(password, '\0', MSH_PASSWORD_MAX);
        }
    }
}
#endif /* MSH_USING_AUTH */

static void shell_auto_complete(char *prefix)
{
    rt_kprintf("\n");
    msh_auto_complete(prefix);

    rt_kprintf("%s%s", MSH_PROMPT, prefix);
}

#ifdef MSH_USING_HISTORY
static rt_bool_t shell_handle_history(struct msh_shell *shell)
{
#if defined(_WIN32)
    int i;
    rt_kprintf("\r");

    for (i = 0; i <= 60; i++)
        putchar(' ');
    rt_kprintf("\r");

#else
    rt_kprintf("\033[2K\r");
#endif
    rt_kprintf("%s%s", MSH_PROMPT, shell->line);
    return RT_FALSE;
}

static void shell_push_history(struct msh_shell *shell)
{
    if (shell->line_position != 0)
    {
        /* push history */
        if (shell->history_count >= MSH_HISTORY_LINES)
        {
            /* if current cmd is same as last cmd, don't push */
            if (memcmp(&shell->cmd_history[MSH_HISTORY_LINES - 1], shell->line, MSH_CMD_SIZE))
            {
                /* move history */
                int index;
                for (index = 0; index < MSH_HISTORY_LINES - 1; index ++)
                {
                    memcpy(&shell->cmd_history[index][0],
                           &shell->cmd_history[index + 1][0], MSH_CMD_SIZE);
                }
                memset(&shell->cmd_history[index][0], 0, MSH_CMD_SIZE);
                memcpy(&shell->cmd_history[index][0], shell->line, shell->line_position);

                /* it's the maximum history */
                shell->history_count = MSH_HISTORY_LINES;
            }
        }
        else
        {
            /* if current cmd is same as last cmd, don't push */
            if (shell->history_count == 0 || memcmp(&shell->cmd_history[shell->history_count - 1], shell->line, MSH_CMD_SIZE))
            {
                shell->current_history = shell->history_count;
                memset(&shell->cmd_history[shell->history_count][0], 0, MSH_CMD_SIZE);
                memcpy(&shell->cmd_history[shell->history_count][0], shell->line, shell->line_position);

                /* increase count and set current history position */
                shell->history_count ++;
            }
        }
    }
    shell->current_history = shell->history_count;
}
#endif

void msh_thread_entry(void *parameter)
{
    int ch;

    /* normal is echo mode */
#ifndef MSH_ECHO_DISABLE_DEFAULT
    shell->echo_mode = 1;
#else
    shell->echo_mode = 0;
#endif

#if !defined(RT_USING_POSIX) && defined(RT_USING_DEVICE)
    /* set console device as shell device */
    if (shell->device == RT_NULL)
    {
        rt_device_t console = rt_console_get_device();
        if (console)
        {
            msh_set_device(console->parent.name);
        }
    }
#endif

#ifdef MSH_USING_AUTH
    /* set the default password when the password isn't setting */
    if (rt_strlen(msh_get_password()) == 0)
    {
        if (msh_set_password(MSH_DEFAULT_PASSWORD) != RT_EOK)
        {
            rt_kprintf("MSH password set failed.\n");
        }
    }
    /* waiting authenticate success */
    msh_wait_auth();
#endif

    rt_kprintf(MSH_PROMPT);

    while (1)
    {
        ch = (int)msh_getchar();
        if (ch < 0)
        {
            continue;
        }

        /*
         * handle control key
         * up key  : 0x1b 0x5b 0x41
         * down key: 0x1b 0x5b 0x42
         * right key:0x1b 0x5b 0x43
         * left key: 0x1b 0x5b 0x44
         */
        if (ch == 0x1b)
        {
            shell->stat = WAIT_SPEC_KEY;
            continue;
        }
        else if (shell->stat == WAIT_SPEC_KEY)
        {
            if (ch == 0x5b)
            {
                shell->stat = WAIT_FUNC_KEY;
                continue;
            }

            shell->stat = WAIT_NORMAL;
        }
        else if (shell->stat == WAIT_FUNC_KEY)
        {
            shell->stat = WAIT_NORMAL;

            if (ch == 0x41) /* up key */
            {
#ifdef MSH_USING_HISTORY
                /* prev history */
                if (shell->current_history > 0)
                    shell->current_history --;
                else
                {
                    shell->current_history = 0;
                    continue;
                }

                /* copy the history command */
                memcpy(shell->line, &shell->cmd_history[shell->current_history][0],
                       MSH_CMD_SIZE);
                shell->line_curpos = shell->line_position = strlen(shell->line);
                shell_handle_history(shell);
#endif
                continue;
            }
            else if (ch == 0x42) /* down key */
            {
#ifdef MSH_USING_HISTORY
                /* next history */
                if (shell->current_history < shell->history_count - 1)
                    shell->current_history ++;
                else
                {
                    /* set to the end of history */
                    if (shell->history_count != 0)
                        shell->current_history = shell->history_count - 1;
                    else
                        continue;
                }

                memcpy(shell->line, &shell->cmd_history[shell->current_history][0],
                       MSH_CMD_SIZE);
                shell->line_curpos = shell->line_position = strlen(shell->line);
                shell_handle_history(shell);
#endif
                continue;
            }
            else if (ch == 0x44) /* left key */
            {
                if (shell->line_curpos)
                {
                    rt_kprintf("\b");
                    shell->line_curpos --;
                }

                continue;
            }
            else if (ch == 0x43) /* right key */
            {
                if (shell->line_curpos < shell->line_position)
                {
                    rt_kprintf("%c", shell->line[shell->line_curpos]);
                    shell->line_curpos ++;
                }

                continue;
            }
        }

        /* received null or error */
        if (ch == '\0' || ch == 0xFF) continue;
        /* handle tab key */
        else if (ch == '\t')
        {
            int i;
            /* move the cursor to the beginning of line */
            for (i = 0; i < shell->line_curpos; i++)
                rt_kprintf("\b");

            /* auto complete */
            shell_auto_complete(&shell->line[0]);
            /* re-calculate position */
            shell->line_curpos = shell->line_position = strlen(shell->line);

            continue;
        }
        /* handle backspace key */
        else if (ch == 0x7f || ch == 0x08)
        {
            /* note that shell->line_curpos >= 0 */
            if (shell->line_curpos == 0)
                continue;

            shell->line_position--;
            shell->line_curpos--;

            if (shell->line_position > shell->line_curpos)
            {
                int i;

                rt_memmove(&shell->line[shell->line_curpos],
                           &shell->line[shell->line_curpos + 1],
                           shell->line_position - shell->line_curpos);
                shell->line[shell->line_position] = 0;

                rt_kprintf("\b%s  \b", &shell->line[shell->line_curpos]);

                /* move the cursor to the origin position */
                for (i = shell->line_curpos; i <= shell->line_position; i++)
                    rt_kprintf("\b");
            }
            else
            {
                rt_kprintf("\b \b");
                shell->line[shell->line_position] = 0;
            }

            continue;
        }

        /* handle end of line, break */
        if (ch == '\r' || ch == '\n')
        {
#ifdef MSH_USING_HISTORY
            shell_push_history(shell);
#endif
            if (shell->echo_mode)
                rt_kprintf("\n");
            msh_exec(shell->line, shell->line_position);

            rt_kprintf(MSH_PROMPT);
            memset(shell->line, 0, sizeof(shell->line));
            shell->line_curpos = shell->line_position = 0;
            continue;
        }

        /* it's a large line, discard it */
        if (shell->line_position >= MSH_CMD_SIZE)
            shell->line_position = 0;

        /* normal character */
        if (shell->line_curpos < shell->line_position)
        {
            int i;

            rt_memmove(&shell->line[shell->line_curpos + 1],
                       &shell->line[shell->line_curpos],
                       shell->line_position - shell->line_curpos);
            shell->line[shell->line_curpos] = ch;
            if (shell->echo_mode)
                rt_kprintf("%s", &shell->line[shell->line_curpos]);

            /* move the cursor to new position */
            for (i = shell->line_curpos; i < shell->line_position; i++)
                rt_kprintf("\b");
        }
        else
        {
            shell->line[shell->line_position] = ch;
            if (shell->echo_mode)
                rt_kprintf("%c", ch);
        }

        ch = 0;
        shell->line_position ++;
        shell->line_curpos++;
        if (shell->line_position >= MSH_CMD_SIZE)
        {
            /* clear command line */
            shell->line_position = 0;
            shell->line_curpos = 0;
        }
    } /* end of device read */
}

void msh_system_function_init(const void *begin, const void *end)
{
    _syscall_table_begin = (struct msh_syscall *) begin;
    _syscall_table_end = (struct msh_syscall *) end;
}

#if defined(__ICCARM__) || defined(__ICCRX__)               /* for IAR compiler */
#ifdef MSH_USING_SYMTAB
    #pragma section="FSymTab"
#endif
#elif defined(__ADSPBLACKFIN__) /* for VisaulDSP++ Compiler*/
#ifdef MSH_USING_SYMTAB
    extern "asm" int __fsymtab_start;
    extern "asm" int __fsymtab_end;
#endif
#elif defined(_MSC_VER)
#pragma section("FSymTab$a", read)
const char __fsym_begin_name[] = "__start";
const char __fsym_begin_desc[] = "begin of msh";
__declspec(allocate("FSymTab$a")) const struct msh_syscall __fsym_begin =
{
    __fsym_begin_name,
    __fsym_begin_desc,
    NULL
};

#pragma section("FSymTab$z", read)
const char __fsym_end_name[] = "__end";
const char __fsym_end_desc[] = "end of msh";
__declspec(allocate("FSymTab$z")) const struct msh_syscall __fsym_end =
{
    __fsym_end_name,
    __fsym_end_desc,
    NULL
};
#endif

/*
 * @ingroup msh
 *
 * This function will initialize msh shell
 */
int msh_system_init(void)
{
    rt_err_t result = RT_EOK;
    rt_thread_t tid;

#ifdef MSH_USING_SYMTAB
#ifdef __ARMCC_VERSION  /* ARM C Compiler */
    extern const int FSymTab$$Base;
    extern const int FSymTab$$Limit;
    msh_system_function_init(&FSymTab$$Base, &FSymTab$$Limit);
#elif defined (__ICCARM__) || defined(__ICCRX__)      /* for IAR Compiler */
    msh_system_function_init(__section_begin("FSymTab"),
                               __section_end("FSymTab"));
#elif defined (__GNUC__) || defined(__TI_COMPILER_VERSION__) || defined(__TASKING__)
    /* GNU GCC Compiler and TI CCS */
    extern const int __fsymtab_start;
    extern const int __fsymtab_end;
    msh_system_function_init(&__fsymtab_start, &__fsymtab_end);
#elif defined(__ADSPBLACKFIN__) /* for VisualDSP++ Compiler */
    msh_system_function_init(&__fsymtab_start, &__fsymtab_end);
#elif defined(_MSC_VER)
    unsigned int *ptr_begin, *ptr_end;

    if (shell)
    {
        rt_kprintf("msh shell already init.\n");
        return RT_EOK;
    }

    ptr_begin = (unsigned int *)&__fsym_begin;
    ptr_begin += (sizeof(struct msh_syscall) / sizeof(unsigned int));
    while (*ptr_begin == 0) ptr_begin ++;

    ptr_end = (unsigned int *) &__fsym_end;
    ptr_end --;
    while (*ptr_end == 0) ptr_end --;

    msh_system_function_init(ptr_begin, ptr_end);
#endif
#endif

#ifdef RT_USING_HEAP
    /* create or set shell structure */
    shell = (struct msh_shell *)rt_calloc(1, sizeof(struct msh_shell));
    if (shell == RT_NULL)
    {
        rt_kprintf("no memory for shell\n");
        return -1;
    }
    tid = rt_thread_create(MSH_THREAD_NAME,
                           msh_thread_entry, RT_NULL,
                           MSH_THREAD_STACK_SIZE, MSH_THREAD_PRIORITY, 10);
#else
    shell = &_shell;
    tid = &msh_thread;
    result = rt_thread_init(&msh_thread,
                            MSH_THREAD_NAME,
                            msh_thread_entry, RT_NULL,
                            &msh_thread_stack[0], sizeof(msh_thread_stack),
                            MSH_THREAD_PRIORITY, 10);
#endif /* RT_USING_HEAP */

    rt_sem_init(&(shell->rx_sem), "shrx", 0, 0);
    msh_set_prompt_mode(1);

    if (tid != NULL && result == RT_EOK)
        rt_thread_startup(tid);
    return 0;
}
INIT_APP_EXPORT(msh_system_init);

#endif /* RT_USING_MSH */

