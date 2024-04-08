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

#ifdef FINSH_USING_OPTION_COMPLETION
#define FINSH_COND(opt) opt,
#else
#define FINSH_COND(opt)
#endif

#ifdef FINSH_USING_DESCRIPTION
#define FINSH_DESC(cmd, desc) __fsym_##cmd##_desc,
#else
#define FINSH_DESC(cmd, desc)
#endif

typedef long (*syscall_func)(void);
#ifdef FINSH_USING_SYMTAB

#ifdef __TI_COMPILER_VERSION__
#define __TI_FINSH_EXPORT_FUNCTION(f)  PRAGMA(DATA_SECTION(f,"FSymTab"))
#endif /* __TI_COMPILER_VERSION__ */

/**
 * Macro to export a command along with its name, description, and options to the symbol table in MSVC.
 * @param name The function name associated with the command.
 * @param cmd The command name.
 * @param desc The description of the command.
 * @param opt The options associated with the command, used for option completion.
 */
#ifdef _MSC_VER
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc, opt)               \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const char __fsym_##cmd##_desc[] = #desc;           \
                __declspec(allocate("FSymTab$f"))                   \
                const struct finsh_syscall __fsym_##cmd =           \
                {                           \
                    __fsym_##cmd##_name,    \
                    FINSH_DESC(cmd, desc)   \
                    FINSH_COND(opt)         \
                    (syscall_func)&name     \
                };
#pragma comment(linker, "/merge:FSymTab=mytext")

#elif defined(__TI_COMPILER_VERSION__)
#ifdef __TMS320C28XX__
#define RT_NOBLOCKED __attribute__((noblocked))
#else
#define RT_NOBLOCKED
#endif
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc, opt)                           \
                __TI_FINSH_EXPORT_FUNCTION(__fsym_##cmd);                       \
                const char __fsym_##cmd##_name[] = #cmd;                        \
                const char __fsym_##cmd##_desc[] = #desc;                       \
                rt_used RT_NOBLOCKED const struct finsh_syscall __fsym_##cmd =  \
                {                           \
                    __fsym_##cmd##_name,    \
                    FINSH_DESC(cmd, desc)   \
                    FINSH_COND(opt)         \
                    (syscall_func)&name     \
                };

#else
#define MSH_FUNCTION_EXPORT_CMD(name, cmd, desc, opt)                                  \
                const char __fsym_##cmd##_name[] rt_section(".rodata.name") = #cmd;    \
                const char __fsym_##cmd##_desc[] rt_section(".rodata.name") = #desc;   \
                rt_used const struct finsh_syscall __fsym_##cmd rt_section("FSymTab")= \
                {                           \
                    __fsym_##cmd##_name,    \
                    FINSH_DESC(cmd, desc)   \
                    FINSH_COND(opt)         \
                    (syscall_func)&name     \
                };

#endif  /* _MSC_VER */
#endif /* FINSH_USING_SYMTAB */

/**
 * Macro definitions to simplify the declaration of exported functions or commands.
 */
#define __MSH_GET_MACRO(_1, _2, _3, _FUN, ...)  _FUN
#define __MSH_GET_EXPORT_MACRO(_1, _2, _3, _4, _FUN, ...) _FUN

#define _MSH_FUNCTION_CMD2(a0, a1)       \
        MSH_FUNCTION_EXPORT_CMD(a0, a0, a1, 0)

#define _MSH_FUNCTION_CMD2_OPT(a0, a1, a2)       \
        MSH_FUNCTION_EXPORT_CMD(a0, a0, a1, a0##_msh_options)

#define _MSH_FUNCTION_EXPORT_CMD3(a0, a1, a2)       \
        MSH_FUNCTION_EXPORT_CMD(a0, a1, a2, 0)

#define _MSH_FUNCTION_EXPORT_CMD3_OPT(a0, a1, a2, a3)   \
        MSH_FUNCTION_EXPORT_CMD(a0, a1, a2, a0##_msh_options)


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
 * @param opt This is an option, enter any content to enable option completion
 */
/* MSH_CMD_EXPORT(command, desc) or MSH_CMD_EXPORT(command, desc, opt) */
#define MSH_CMD_EXPORT(...)                                 \
    __MSH_GET_MACRO(__VA_ARGS__, _MSH_FUNCTION_CMD2_OPT,    \
        _MSH_FUNCTION_CMD2)(__VA_ARGS__)

/**
 * @ingroup msh
 *
 * This macro exports a command with alias to module shell.
 *
 * @param command is the name of the command.
 * @param alias is the alias of the command.
 * @param desc is the description of the command, which will show in help list.
 * @param opt This is an option, enter any content to enable option completion
 * @note
 *      #define MSH_CMD_EXPORT_ALIAS(command, alias, desc) or
 *      #define MSH_CMD_EXPORT_ALIAS(command, alias, desc, opt)
 */
#define MSH_CMD_EXPORT_ALIAS(...)                                           \
    __MSH_GET_EXPORT_MACRO(__VA_ARGS__, _MSH_FUNCTION_EXPORT_CMD3_OPT,      \
            _MSH_FUNCTION_EXPORT_CMD3)(__VA_ARGS__)

/* system call table */
struct finsh_syscall
{
    const char     *name;       /* the name of system call */
#if defined(FINSH_USING_DESCRIPTION) && defined(FINSH_USING_SYMTAB)
    const char     *desc;       /* description of system call */
#endif

#ifdef FINSH_USING_OPTION_COMPLETION
    struct msh_cmd_opt *opt;
#endif
    syscall_func func;      /* the function address of system call */
};

/* system call item */
struct finsh_syscall_item
{
    struct finsh_syscall_item *next;    /* next item */
    struct finsh_syscall syscall;       /* syscall */
};

#ifdef FINSH_USING_OPTION_COMPLETION
typedef struct msh_cmd_opt
{
    rt_uint32_t     id;
    const char      *name;
    const char      *des;
} msh_cmd_opt_t;

/* Command options declaration and definition macros */

/**
 * Declares a static array of command options for a specific command.
 * @param command The command associated with these options.
 */
#define CMD_OPTIONS_STATEMENT(command) static struct msh_cmd_opt command##_msh_options[];

/**
 * Starts the definition of command options for a specific command.
 * @param command The command these options are associated with.
 */
#define CMD_OPTIONS_NODE_START(command) static struct msh_cmd_opt command##_msh_options[] = {

/**
 * Defines a single command option.
 * @param _id Unique identifier for the option.
 * @param _name The name of the option.
 * @param _des Description of the option.
 */
#define CMD_OPTIONS_NODE(_id, _name, _des) {.id = _id, .name = #_name, .des = #_des},

/**
 * Marks the end of command options definition.
 */
#define CMD_OPTIONS_NODE_END    {0},};

void msh_opt_list_dump(void *options);
int msh_cmd_opt_id_get(int argc, char *argv[], void *options);
#define MSH_OPT_ID_GET(fun) msh_cmd_opt_id_get(argc, argv, (void*) fun##_msh_options)
#define MSH_OPT_DUMP(fun)   msh_opt_list_dump((void*) fun##_msh_options)

#else
#define CMD_OPTIONS_STATEMENT(command)
#define CMD_OPTIONS_NODE_START(command)
#define CMD_OPTIONS_NODE(_id, _name, _des)
#define CMD_OPTIONS_NODE_END
#define MSH_OPT_ID_GET(fun) ((int)(-1UL))
#define MSH_OPT_DUMP(fun)   do{}while(0)
#endif

extern struct finsh_syscall_item *global_syscall_list;
extern struct finsh_syscall *_syscall_table_begin, *_syscall_table_end;

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__))
    struct finsh_syscall *finsh_syscall_next(struct finsh_syscall *call);
    #define FINSH_NEXT_SYSCALL(index)  index=finsh_syscall_next(index)
#else
    #define FINSH_NEXT_SYSCALL(index)  index++
#endif

#if !defined(RT_USING_POSIX_STDIO) && defined(RT_USING_DEVICE)
void finsh_set_device(const char *device_name);
#endif

#endif
