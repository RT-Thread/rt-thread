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

#include <rtdef.h>

#ifdef _MSC_VER
#pragma section("FSymTab$f",read)
#endif /* _MSC_VER */

typedef long (*syscall_func)(void);
#ifdef FINSH_USING_SYMTAB
#ifdef __TI_COMPILER_VERSION__
#define __TI_FINSH_EXPORT_FUNCTION(f)  PRAGMA(DATA_SECTION(f,"FSymTab"))
#endif /* __TI_COMPILER_VERSION__ */
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
#ifdef __TMS320C28XX__
#define RT_NOBLOCKED __attribute__((noblocked))
#else
#define RT_NOBLOCKED
#endif
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                __TI_FINSH_EXPORT_FUNCTION(__fsym_##cmd);           \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const char __fsym_##cmd##_desc[] = #desc;           \
                rt_used RT_NOBLOCKED const struct finsh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    __fsym_##cmd##_desc,    \
                    (syscall_func)&name     \
                };
#else
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc)                      \
                const char __fsym_##cmd##_name[] rt_section(".rodata.name") = #cmd;    \
                const char __fsym_##cmd##_desc[] rt_section(".rodata.name") = #desc;   \
                rt_used const struct finsh_syscall __fsym_##cmd rt_section("FSymTab")= \
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
                rt_used const struct finsh_syscall __fsym_##cmd rt_section("FSymTab")= \
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
#endif

/* find out system call, which should be implemented in user program */
struct finsh_syscall *finsh_syscall_lookup(const char *name);

#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
void finsh_set_device(const char *device_name);
#endif

#endif
