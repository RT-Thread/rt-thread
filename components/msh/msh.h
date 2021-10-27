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

#if defined(_MSC_VER)
    #pragma section("FSymTab$f",read)
#endif

typedef long (*syscall_func)(void);
#ifdef MSH_USING_SYMTAB
#ifdef __TI_COMPILER_VERSION__
    #define __TI_MSH_EXPORT_FUNCTION(f)  PRAGMA(DATA_SECTION(f,"FSymTab"))
#endif
#ifdef MSH_USING_DESCRIPTION
#ifdef _MSC_VER
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const char __fsym_##cmd##_desc[] = #desc;           \
                __declspec(allocate("FSymTab$f"))                   \
                const struct msh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    __fsym_##cmd##_desc,    \
                    (syscall_func)&name     \
                };
#pragma comment(linker, "/merge:FSymTab=mytext")

#elif defined(__TI_COMPILER_VERSION__)
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                __TI_MSH_EXPORT_FUNCTION(__fsym_##cmd);           \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const char __fsym_##cmd##_desc[] = #desc;           \
                const struct msh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    __fsym_##cmd##_desc,    \
                    (syscall_func)&name     \
                };

#else
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)                      \
                const char __fsym_##cmd##_name[] RT_SECTION(".rodata.name") = #cmd;    \
                const char __fsym_##cmd##_desc[] RT_SECTION(".rodata.name") = #desc;   \
                RT_USED const struct msh_syscall __fsym_##cmd RT_SECTION("FSymTab")= \
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
                const struct msh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    (syscall_func)&name     \
                };
#pragma comment(linker, "/merge:FSymTab=mytext")

#elif defined(__TI_COMPILER_VERSION__)
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                __TI_MSH_EXPORT_FUNCTION(__fsym_##cmd);           \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const struct msh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    (syscall_func)&name     \
                };

#else
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)                      \
                const char __fsym_##cmd##_name[] = #cmd;                            \
                RT_USED const struct msh_syscall __fsym_##cmd RT_SECTION("FSymTab")= \
                {                                                                   \
                    __fsym_##cmd##_name,                                            \
                    (syscall_func)&name                                             \
                };

#endif
#endif /* end of MSH_USING_DESCRIPTION */
#endif /* end of MSH_USING_SYMTAB */

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

/**
 * @ingroup msh
 *
 * This macro exports a command to module shell.
 *
 * @param command is the name of the command.
 * @param desc is the description of the command, which will show in help list.
 */
#define MSH_CMD_EXPORT(command, desc)   \
    MSH_FUNCTION_EXPORT_CMD(command, command, desc)

/**
 * @ingroup msh
 *
 * This macro exports a command with alias to module shell.
 *
 * @param command is the name of the command.
 * @param alias is the alias of the command.
 * @param desc is the description of the command, which will show in help list.
 */
#define MSH_CMD_EXPORT_ALIAS(command, alias, desc)  \
    MSH_FUNCTION_EXPORT_CMD(command, alias, desc)

/* system call table */
struct msh_syscall
{
    const char     *name;       /* the name of system call */
#if defined(MSH_USING_DESCRIPTION) && defined(MSH_USING_SYMTAB)
    const char     *desc;       /* description of system call */
#endif
    syscall_func func;      /* the function address of system call */
};

/* system call item */
struct msh_syscall_item
{
    struct msh_syscall_item *next;    /* next item */
    struct msh_syscall syscall;       /* syscall */
};

extern struct msh_syscall_item *global_syscall_list;
extern struct msh_syscall *_syscall_table_begin, *_syscall_table_end;

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__))
    struct msh_syscall *msh_syscall_next(struct msh_syscall *call);
    #define MSH_NEXT_SYSCALL(index)  index=msh_syscall_next(index)
#else
    #define MSH_NEXT_SYSCALL(index)  index++
#endif

#ifdef RT_USING_DEVICE
    void msh_set_device(const char *device_name);
#endif













int msh_exec(char *cmd, rt_size_t length);
void msh_auto_complete(char *prefix);

int msh_exec_module(const char *cmd_line, int size);
int msh_exec_script(const char *cmd_line, int size);

#endif
