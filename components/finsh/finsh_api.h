/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#ifndef FINSH_API_H__
#define FINSH_API_H__

#if defined(_MSC_VER)
#pragma section("FSymTab$f",read)
#pragma section("VSymTab",read)
#endif

typedef long (*syscall_func)(void);

/* system call table */
struct finsh_syscall
{
    const char*     name;       /* the name of system call */
#if defined(FINSH_USING_DESCRIPTION) && defined(FINSH_USING_SYMTAB)
    const char*     desc;       /* description of system call */
#endif
    syscall_func func;      /* the function address of system call */
};
extern struct finsh_syscall *_syscall_table_begin, *_syscall_table_end;

/* find out system call, which should be implemented in user program */
struct finsh_syscall* finsh_syscall_lookup(const char* name);

#ifdef FINSH_USING_SYMTAB

#ifdef __TI_COMPILER_VERSION__
#define __TI_FINSH_EXPORT_FUNCTION(f)  PRAGMA(DATA_SECTION(f,"FSymTab"))
#define __TI_FINSH_EXPORT_VAR(v)       PRAGMA(DATA_SECTION(v,"VSymTab"))
#endif

    #ifdef FINSH_USING_DESCRIPTION
        #ifdef _MSC_VER
            #define FINSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
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

            #define FINSH_VAR_EXPORT(name, type, desc)              \
                const char __vsym_##name##_name[] = #name;          \
                const char __vsym_##name##_desc[] = #desc;          \
                __declspec(allocate("VSymTab"))                     \
                const struct finsh_sysvar __vsym_##name =           \
                {                           \
                    __vsym_##name##_name,   \
                    __vsym_##name##_desc,   \
                    type,                   \
                    (void*)&name            \
                };

        #elif defined(__TI_COMPILER_VERSION__)
            #define FINSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                __TI_FINSH_EXPORT_FUNCTION(__fsym_##cmd);           \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const char __fsym_##cmd##_desc[] = #desc;           \
                const struct finsh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    __fsym_##cmd##_desc,    \
                    (syscall_func)&name     \
                };

            #define FINSH_VAR_EXPORT(name, type, desc)              \
                __TI_FINSH_EXPORT_VAR(__vsym_##name);               \
                const char __vsym_##name##_name[] = #name;          \
                const char __vsym_##name##_desc[] = #desc;          \
                const struct finsh_sysvar __vsym_##name =           \
                {                           \
                    __vsym_##name##_name,   \
                    __vsym_##name##_desc,   \
                    type,                   \
                    (void*)&name            \
                };

        #else
            #define FINSH_FUNCTION_EXPORT_CMD(name, cmd, desc)                      \
                const char __fsym_##cmd##_name[] SECTION(".rodata.name") = #cmd;    \
                const char __fsym_##cmd##_desc[] SECTION(".rodata.name") = #desc;   \
                RT_USED const struct finsh_syscall __fsym_##cmd SECTION("FSymTab")= \
                {                           \
                    __fsym_##cmd##_name,    \
                    __fsym_##cmd##_desc,    \
                    (syscall_func)&name     \
                };

            #define FINSH_VAR_EXPORT(name, type, desc)                              \
                const char __vsym_##name##_name[] SECTION(".rodata.name") = #name;  \
                const char __vsym_##name##_desc[] SECTION(".rodata.name") = #desc;  \
                RT_USED const struct finsh_sysvar __vsym_##name SECTION("VSymTab")= \
                {                           \
                    __vsym_##name##_name,   \
                    __vsym_##name##_desc,   \
                    type,                   \
                    (void*)&name            \
                };

        #endif
    #else
        #ifdef _MSC_VER
            #define FINSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                const char __fsym_##cmd##_name[] = #cmd;            \
                __declspec(allocate("FSymTab$f"))                   \
                const struct finsh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    (syscall_func)&name     \
                };
            #pragma comment(linker, "/merge:FSymTab=mytext")

            #define FINSH_VAR_EXPORT(name, type, desc)              \
                const char __vsym_##name##_name[] = #name;          \
                __declspec(allocate("VSymTab")) const struct finsh_sysvar __vsym_##name = \
                {                                                                         \
                    __vsym_##name##_name,                                                 \
                    type,                                                                 \
                    (void*)&name                                                          \
                };

        #elif defined(__TI_COMPILER_VERSION__)
            #define FINSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                __TI_FINSH_EXPORT_FUNCTION(__fsym_##cmd);           \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const struct finsh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    (syscall_func)&name     \
                };

            #define FINSH_VAR_EXPORT(name, type, desc)              \
                __TI_FINSH_EXPORT_VAR(__vsym_##name);               \
                const char __vsym_##name##_name[] = #name;          \
                const struct finsh_sysvar __vsym_##name =           \
                {                                                   \
                    __vsym_##name##_name,                           \
                    type,                                           \
                    (void*)&name                                    \
                };

        #else
            #define FINSH_FUNCTION_EXPORT_CMD(name, cmd, desc)                      \
                const char __fsym_##cmd##_name[] = #cmd;                            \
                RT_USED const struct finsh_syscall __fsym_##cmd SECTION("FSymTab")= \
                {                                                                   \
                    __fsym_##cmd##_name,                                            \
                    (syscall_func)&name                                             \
                };

            #define FINSH_VAR_EXPORT(name, type, desc)                              \
                const char __vsym_##name##_name[] = #name;                          \
                RT_USED const struct finsh_sysvar __vsym_##name SECTION("VSymTab")= \
                {                                                                   \
                    __vsym_##name##_name,                                           \
                    type,                                                           \
                    (void*)&name                                                    \
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
#define FINSH_FUNCTION_EXPORT(name, desc)   \
    FINSH_FUNCTION_EXPORT_CMD(name, name, desc)

/**
 * @ingroup finsh
 *
 * This macro exports a system function with an alias name to finsh shell.
 *
 * @param name the name of function.
 * @param alias the alias name of function.
 * @param desc the description of function, which will show in help.
 */
#define FINSH_FUNCTION_EXPORT_ALIAS(name, alias, desc)  \
        FINSH_FUNCTION_EXPORT_CMD(name, alias, desc)

/**
 * @ingroup finsh
 *
 * This macro exports a command to module shell.
 *
 * @param command the name of command.
 * @param desc the description of command, which will show in help.
 */
#ifdef FINSH_USING_MSH
#define MSH_CMD_EXPORT(command, desc)   \
    FINSH_FUNCTION_EXPORT_CMD(command, __cmd_##command, desc)
#define MSH_CMD_EXPORT_ALIAS(command, alias, desc)  \
    FINSH_FUNCTION_EXPORT_ALIAS(command, __cmd_##alias, desc)
#else
#define MSH_CMD_EXPORT(command, desc)
#define MSH_CMD_EXPORT_ALIAS(command, alias, desc)
#endif

#endif
