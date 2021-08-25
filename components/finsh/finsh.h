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

#include <rtthread.h>

#if defined(_MSC_VER)
    #pragma section("FSymTab$f",read)
#endif

typedef long (*syscall_func)(void);
#ifdef FINSH_USING_SYMTAB
#ifdef __TI_COMPILER_VERSION__
    #define __TI_FINSH_EXPORT_FUNCTION(f)  PRAGMA(DATA_SECTION(f,"FSymTab"))
#endif
#ifdef FINSH_USING_DESCRIPTION
#ifdef _MSC_VER
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const char __fsym_##cmd##_desc[] = #desc;           \
                __declspec(allocate("FSymTab$f"))                   \
                const struct finsh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    __fsym_##cmd##_desc,    \
                    (syscall_func)&name     \
                };
#pragma comment(linker, "/merge:FSymTab=mytext")

#elif defined(__TI_COMPILER_VERSION__)
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                __TI_FINSH_EXPORT_FUNCTION(__fsym_##cmd);           \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const char __fsym_##cmd##_desc[] = #desc;           \
                const struct finsh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    __fsym_##cmd##_desc,    \
                    (syscall_func)&name     \
                };

#else
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)                      \
                const char __fsym_##cmd##_name[] RT_SECTION(".rodata.name") = #cmd;    \
                const char __fsym_##cmd##_desc[] RT_SECTION(".rodata.name") = #desc;   \
                RT_USED const struct finsh_syscall __fsym_##cmd RT_SECTION("FSymTab")= \
                {                           \
                    __fsym_##cmd##_name,    \
                    __fsym_##cmd##_desc,    \
                    (syscall_func)&name     \
                };

#endif
#else
#ifdef _MSC_VER
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                const char __fsym_##cmd##_name[] = #cmd;            \
                __declspec(allocate("FSymTab$f"))                   \
                const struct finsh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    (syscall_func)&name     \
                };
#pragma comment(linker, "/merge:FSymTab=mytext")

#elif defined(__TI_COMPILER_VERSION__)
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                __TI_FINSH_EXPORT_FUNCTION(__fsym_##cmd);           \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const struct finsh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    (syscall_func)&name     \
                };

#else
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)                      \
                const char __fsym_##cmd##_name[] = #cmd;                            \
                RT_USED const struct finsh_syscall __fsym_##cmd RT_SECTION("FSymTab")= \
                {                                                                   \
                    __fsym_##cmd##_name,                                            \
                    (syscall_func)&name                                             \
                };

#endif
#endif /* end of FINSH_USING_DESCRIPTION */
#endif /* end of FINSH_USING_SYMTAB */

/**
 * @ingroup finsh
 *
 * This macro exports a system function to finsh shell (discarded).
 *
 * @param name the name of function.
 * @param desc the description of function, which will show in help.
 */
#define FINSH_FUNCTION_EXPORT(name, desc)

/**
 * @ingroup finsh
 *
 * This macro exports a system function with an alias name to finsh shell (discarded).
 *
 * @param name the name of function.
 * @param alias the alias name of function.
 * @param desc the description of function, which will show in help.
 */
#define FINSH_FUNCTION_EXPORT_ALIAS(name, alias, desc)

/**
 * @ingroup finsh
 *
 * This macro exports a command to module shell.
 *
 * @param command the name of command.
 * @param desc the description of command, which will show in help.
 */
#define MSH_CMD_EXPORT(command, desc)   \
    MSH_FUNCTION_EXPORT_CMD(command, command, desc)

/**
 * @ingroup finsh
 *
 * This macro exports a command with an alias name to module shell.
 *
 * @param name the name of command.
 * @param alias the alias name of command.
 * @param desc the description of command, which will show in help.
 */
#define MSH_CMD_EXPORT_ALIAS(command, alias, desc)  \
    MSH_FUNCTION_EXPORT_CMD(command, alias, desc)

/* system call table */
struct finsh_syscall
{
    const char     *name;       /* the name of system call */
#if defined(FINSH_USING_DESCRIPTION) && defined(FINSH_USING_SYMTAB)
    const char     *desc;       /* description of system call */
#endif
    syscall_func func;      /* the function address of system call */
};

/* system call item */
struct finsh_syscall_item
{
    struct finsh_syscall_item *next;    /* next item */
    struct finsh_syscall syscall;       /* syscall */
};

extern struct finsh_syscall_item *global_syscall_list;
extern struct finsh_syscall *_syscall_table_begin, *_syscall_table_end;

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__))
    struct finsh_syscall *finsh_syscall_next(struct finsh_syscall *call);
    #define FINSH_NEXT_SYSCALL(index)  index=finsh_syscall_next(index)
#else
    #define FINSH_NEXT_SYSCALL(index)  index++
#endif /* defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__)) */

/* find out system call, which should be implemented in user program */
struct finsh_syscall *finsh_syscall_lookup(const char *name);

int finsh_system_init(void);
#ifdef RT_USING_DEVICE
void finsh_set_device(const char *device_name);
const char *finsh_get_device(void);
#endif

char finsh_getchar(void);

#define FINSH_OPTION_ECHO   0x01
void finsh_set_echo(rt_uint32_t echo);
rt_uint32_t finsh_get_echo(void);

#define FINSH_PROMPT        finsh_get_prompt()
rt_uint32_t finsh_get_prompt_mode(void);
void finsh_set_prompt_mode(rt_uint32_t prompt_mode);

#ifdef FINSH_USING_AUTH
rt_err_t finsh_set_password(const char *password);
const char *finsh_get_password(void);
#endif

int msh_exec(char *cmd, rt_size_t length);
void msh_auto_complete(char *prefix);
int msh_exec_module(const char *cmd_line, int size);
int msh_exec_script(const char *cmd_line, int size);

#endif
