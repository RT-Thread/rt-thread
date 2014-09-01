/*
 * File      : finsh.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
#pragma section("VSymTab",read)
#endif

/* -- the beginning of option -- */
#define FINSH_NAME_MAX          16      /* max length of identifier */
#define FINSH_NODE_MAX          16      /* max number of node */

#define FINSH_HEAP_MAX          128     /* max length of heap */
#define FINSH_STRING_MAX        128     /* max length of string */
#define FINSH_VARIABLE_MAX      8       /* max number of variable */

#define FINSH_STACK_MAX         64      /* max stack size */
#define FINSH_TEXT_MAX          128     /* max text segment size */

#define HEAP_ALIGNMENT          4       /* heap alignment */

#define FINSH_GET16(x)    (*(x)) | (*((x)+1) << 8)
#define FINSH_GET32(x)    (rt_uint32_t)(*(x)) | ((rt_uint32_t)*((x)+1) << 8) | \
    ((rt_uint32_t)*((x)+2) << 16) | ((rt_uint32_t)*((x)+3) << 24)

#define FINSH_SET16(x, v)           \
    do                              \
    {                               \
        *(x)     = (v) & 0x00ff;    \
        (*((x)+1)) = (v) >> 8;      \
    } while ( 0 )

#define FINSH_SET32(x, v)                                       \
    do                                                          \
    {                                                           \
        *(x)     = (rt_uint32_t)(v)  & 0x000000ff;              \
        (*((x)+1)) = ((rt_uint32_t)(v) >> 8) & 0x000000ff;      \
        (*((x)+2)) = ((rt_uint32_t)(v) >> 16) & 0x000000ff;     \
        (*((x)+3)) = ((rt_uint32_t)(v) >> 24);                  \
    } while ( 0 )

/* -- the end of option -- */

#if defined(RT_USING_NEWLIB) || defined (RT_USING_MINILIBC)
#include <sys/types.h>
#include <string.h>
#else
typedef unsigned char  u_char;
typedef unsigned short u_short;
typedef unsigned long  u_long;

#if !defined(__CC_ARM)             && \
    !defined(__IAR_SYSTEMS_ICC__)  && \
    !defined(__ADSPBLACKFIN__)     && \
    !defined(_MSC_VER)

/* only for GNU GCC */

#if !(defined(__GNUC__) && defined(__x86_64__))
typedef unsigned int size_t;
#else
#include <stdio.h>
#endif

#ifndef NULL
#define NULL RT_NULL
#endif

#else
/* use libc of armcc */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#endif
#endif

#define FINSH_VERSION_MAJOR			1
#define FINSH_VERSION_MINOR			0

/**
 * @addtogroup finsh
 */
/*@{*/
#define FINSH_ERROR_OK              0   /**< No error 			*/
#define FINSH_ERROR_INVALID_TOKEN	1	/**< Invalid token 		*/
#define FINSH_ERROR_EXPECT_TYPE		2	/**< Expect a type 		*/
#define FINSH_ERROR_UNKNOWN_TYPE	3	/**< Unknown type 		*/
#define FINSH_ERROR_VARIABLE_EXIST	4	/**< Variable exist 	*/
#define FINSH_ERROR_EXPECT_OPERATOR	5	/**< Expect a operator 	*/
#define FINSH_ERROR_MEMORY_FULL		6	/**< Memory full 		*/
#define FINSH_ERROR_UNKNOWN_OP		7 	/**< Unknown operator 	*/
#define FINSH_ERROR_UNKNOWN_NODE	8	/**< Unknown node 		*/
#define FINSH_ERROR_EXPECT_CHAR		9	/**< Expect a character */
#define FINSH_ERROR_UNEXPECT_END	10	/**< Unexpect end 		*/
#define FINSH_ERROR_UNKNOWN_TOKEN	11	/**< Unknown token 		*/
#define FINSH_ERROR_NO_FLOAT		12	/**< Float not supported */
#define FINSH_ERROR_UNKNOWN_SYMBOL	13	/**< Unknown symbol 	*/
#define FINSH_ERROR_NULL_NODE		14	/**< Null node 			*/
/*@}*/

typedef long (*syscall_func)();

/* system call table */
struct finsh_syscall
{
	const char*		name;		/* the name of system call */
#if defined(FINSH_USING_DESCRIPTION) && defined(FINSH_USING_SYMTAB)
	const char*		desc;		/* description of system call */
#endif
	syscall_func func;		/* the function address of system call */
};

/* system call item */
struct finsh_syscall_item
{
	struct finsh_syscall_item* next;	/* next item */
	struct finsh_syscall syscall;		/* syscall */
};
extern struct finsh_syscall *_syscall_table_begin, *_syscall_table_end;
extern struct finsh_syscall_item *global_syscall_list;

/* find out system call, which should be implemented in user program */
struct finsh_syscall* finsh_syscall_lookup(const char* name);

/* system variable table */
struct finsh_sysvar
{
	const char*		name;		/* the name of variable */
#if defined(FINSH_USING_DESCRIPTION) && defined(FINSH_USING_SYMTAB)
	const char* 	desc;		/* description of system variable */
#endif
	u_char		 type;		/* the type of variable */
	void*		 var ;		/* the address of variable */
};

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__))
struct finsh_syscall* finsh_syscall_next(struct finsh_syscall* call);
struct finsh_sysvar* finsh_sysvar_next(struct finsh_sysvar* call);
#define FINSH_NEXT_SYSCALL(index)  index=finsh_syscall_next(index)
#define FINSH_NEXT_SYSVAR(index)   index=finsh_sysvar_next(index)
#else
#define FINSH_NEXT_SYSCALL(index)  index++
#define FINSH_NEXT_SYSVAR(index)   index++
#endif

/* system variable item */
struct finsh_sysvar_item
{
	struct finsh_sysvar_item *next;		/* next item */
	struct finsh_sysvar sysvar;			/* system variable */
};
extern struct finsh_sysvar *_sysvar_table_begin, *_sysvar_table_end;
extern struct finsh_sysvar_item* global_sysvar_list;

/* find out system variable, which should be implemented in user program */
struct finsh_sysvar* finsh_sysvar_lookup(const char* name);

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
            #define FINSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const char __fsym_##cmd##_desc[] = #desc;           \
                const struct finsh_syscall __fsym_##cmd SECTION("FSymTab")= \
                {                           \
                    __fsym_##cmd##_name,    \
                    __fsym_##cmd##_desc,    \
                    (syscall_func)&name     \
                };

            #define FINSH_VAR_EXPORT(name, type, desc)              \
                const char __vsym_##name##_name[] = #name;          \
                const char __vsym_##name##_desc[] = #desc;          \
                const struct finsh_sysvar __vsym_##name SECTION("VSymTab")= \
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
                {                           \
                    __vsym_##name##_name,   \
                    type,                   \
                    (void*)&name            \
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
                {                           \
                    __vsym_##name##_name,   \
                    type,                   \
                    (void*)&name            \
                };
            
        #else
            #define FINSH_FUNCTION_EXPORT_CMD(name, cmd, desc)      \
                const char __fsym_##cmd##_name[] = #cmd;            \
                const struct finsh_syscall __fsym_##cmd SECTION("FSymTab")= \
                {                           \
                    __fsym_##cmd##_name,    \
                    (syscall_func)&name     \
                };

            #define FINSH_VAR_EXPORT(name, type, desc)              \
                const char __vsym_##name##_name[] = #name;          \
                const struct finsh_sysvar __vsym_##name SECTION("VSymTab")= \
                {                           \
                    __vsym_##name##_name,   \
                    type,                   \
                    (void*)&name            \
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
#else
#define MSH_CMD_EXPORT(command, desc)
#endif

struct finsh_token
{
	char eof;
	char replay;

	int  position;
	u_char current_token;

	union {
		char char_value;
		int int_value;
		long long_value;
	} value;
	u_char string[128];

	u_char* line;
};

#define FINSH_IDTYPE_VAR		0x01
#define FINSH_IDTYPE_SYSVAR		0x02
#define FINSH_IDTYPE_SYSCALL	0x04
#define FINSH_IDTYPE_ADDRESS	0x08
struct finsh_node
{
	u_char node_type;	/* node node_type */
	u_char data_type;	/* node data node_type */
	u_char idtype;		/* id node information */

	union {			/* value node */
		char 	char_value;
		short 	short_value;
		int 	int_value;
		long 	long_value;
		void* 	ptr;
	} value;
	union
	{
		/* point to variable identifier or function identifier */
		struct finsh_var	*var;
		struct finsh_sysvar	*sysvar;
		struct finsh_syscall*syscall;
	}id;

	/* sibling and child node */
	struct finsh_node *sibling, *child;
};

struct finsh_parser
{
	u_char* parser_string;

    struct finsh_token token;
	struct finsh_node* root;
};

/**
 * @ingroup finsh
 *
 * The basic data type in finsh shell
 */
enum finsh_type {
	finsh_type_unknown = 0, /**< unknown data type */
	finsh_type_void,		/**< void  			*/
	finsh_type_voidp,		/**< void pointer  	*/
	finsh_type_char,		/**< char  			*/
	finsh_type_uchar,		/**< unsigned char  */
	finsh_type_charp,		/**< char pointer  	*/
	finsh_type_short,		/**< short  		*/
	finsh_type_ushort,		/**< unsigned short */
	finsh_type_shortp,		/**< short pointer  */
	finsh_type_int,			/**< int 			*/
	finsh_type_uint,		/**< unsigned int 	*/
	finsh_type_intp,		/**< int pointer 	*/
	finsh_type_long,		/**< long 			*/
	finsh_type_ulong,		/**< unsigned long 	*/
	finsh_type_longp		/**< long pointer 	*/
};

/* init finsh environment */
int finsh_init(struct finsh_parser* parser);
/* flush finsh node, text segment */
int finsh_flush(struct finsh_parser* parser);
/* reset all of finsh */
int finsh_reset(struct finsh_parser* parser);
#ifdef RT_USING_DEVICE
void finsh_set_device(const char* device_name);
#endif

/* run finsh parser to generate abstract synatx tree */
void finsh_parser_run (struct finsh_parser* parser, const unsigned char* string);
/* run compiler to compile abstract syntax tree */
int finsh_compiler_run(struct finsh_node* node);
/* run finsh virtual machine */
void finsh_vm_run(void);

/* get variable value */
struct finsh_var* finsh_var_lookup(const char* name);
/* get bottom value of stack */
long finsh_stack_bottom(void);

/* get error number of finsh */
u_char finsh_errno(void);
/* get error string */
const char* finsh_error_string(u_char type);

#ifdef RT_USING_HEAP
/**
 * @ingroup finsh
 *
 * This function appends a system call to finsh runtime environment
 * @param name the name of system call
 * @param func the function pointer of system call
 */
void finsh_syscall_append(const char* name, syscall_func func);

/**
 * @ingroup finsh
 *
 * This function appends a system variable to finsh runtime environment
 * @param name the name of system variable
 * @param type the data type of system variable
 * @param addr the address of system variable
 */
void finsh_sysvar_append(const char* name, u_char type, void* addr);
#endif
#endif
