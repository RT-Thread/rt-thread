/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
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
#include "finsh_api.h"

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

/* std header file */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define FINSH_VERSION_MAJOR         1
#define FINSH_VERSION_MINOR         0

/**
 * @addtogroup finsh
 */
/*@{*/
#define FINSH_ERROR_OK              0   /**< No error           */
#define FINSH_ERROR_INVALID_TOKEN   1   /**< Invalid token      */
#define FINSH_ERROR_EXPECT_TYPE     2   /**< Expect a type      */
#define FINSH_ERROR_UNKNOWN_TYPE    3   /**< Unknown type       */
#define FINSH_ERROR_VARIABLE_EXIST  4   /**< Variable exist     */
#define FINSH_ERROR_EXPECT_OPERATOR 5   /**< Expect a operator  */
#define FINSH_ERROR_MEMORY_FULL     6   /**< Memory full        */
#define FINSH_ERROR_UNKNOWN_OP      7   /**< Unknown operator   */
#define FINSH_ERROR_UNKNOWN_NODE    8   /**< Unknown node       */
#define FINSH_ERROR_EXPECT_CHAR     9   /**< Expect a character */
#define FINSH_ERROR_UNEXPECT_END    10  /**< Unexpect end       */
#define FINSH_ERROR_UNKNOWN_TOKEN   11  /**< Unknown token      */
#define FINSH_ERROR_NO_FLOAT        12  /**< Float not supported */
#define FINSH_ERROR_UNKNOWN_SYMBOL  13  /**< Unknown symbol     */
#define FINSH_ERROR_NULL_NODE       14  /**< Null node          */
/*@}*/

/* system call item */
struct finsh_syscall_item
{
    struct finsh_syscall_item* next;    /* next item */
    struct finsh_syscall syscall;       /* syscall */
};
extern struct finsh_syscall_item *global_syscall_list;

/* system variable table */
struct finsh_sysvar
{
    const char*     name;       /* the name of variable */
#if defined(FINSH_USING_DESCRIPTION) && defined(FINSH_USING_SYMTAB)
    const char*     desc;       /* description of system variable */
#endif
    uint8_t      type;      /* the type of variable */
    void*        var ;      /* the address of variable */
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
    struct finsh_sysvar_item *next;     /* next item */
    struct finsh_sysvar sysvar;         /* system variable */
};
extern struct finsh_sysvar *_sysvar_table_begin, *_sysvar_table_end;
extern struct finsh_sysvar_item* global_sysvar_list;

/* find out system variable, which should be implemented in user program */
struct finsh_sysvar* finsh_sysvar_lookup(const char* name);


struct finsh_token
{
    char eof;
    char replay;

    int  position;
    uint8_t current_token;

    union {
        char char_value;
        int int_value;
        long long_value;
    } value;
    uint8_t string[FINSH_STRING_MAX];

    uint8_t* line;
};

#define FINSH_IDTYPE_VAR        0x01
#define FINSH_IDTYPE_SYSVAR     0x02
#define FINSH_IDTYPE_SYSCALL    0x04
#define FINSH_IDTYPE_ADDRESS    0x08
struct finsh_node
{
    uint8_t node_type;  /* node node_type */
    uint8_t data_type;  /* node data node_type */
    uint8_t idtype;     /* id node information */

    union {         /* value node */
        char    char_value;
        short   short_value;
        int     int_value;
        long    long_value;
        void*   ptr;
    } value;
    union
    {
        /* point to variable identifier or function identifier */
        struct finsh_var    *var;
        struct finsh_sysvar *sysvar;
        struct finsh_syscall*syscall;
    }id;

    /* sibling and child node */
    struct finsh_node *sibling, *child;
};

struct finsh_parser
{
    uint8_t* parser_string;

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
    finsh_type_void,        /**< void           */
    finsh_type_voidp,       /**< void pointer   */
    finsh_type_char,        /**< char           */
    finsh_type_uchar,       /**< unsigned char  */
    finsh_type_charp,       /**< char pointer   */
    finsh_type_short,       /**< short          */
    finsh_type_ushort,      /**< unsigned short */
    finsh_type_shortp,      /**< short pointer  */
    finsh_type_int,         /**< int            */
    finsh_type_uint,        /**< unsigned int   */
    finsh_type_intp,        /**< int pointer    */
    finsh_type_long,        /**< long           */
    finsh_type_ulong,       /**< unsigned long  */
    finsh_type_longp        /**< long pointer   */
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
uint8_t finsh_errno(void);
/* get error string */
const char* finsh_error_string(uint8_t type);

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
void finsh_sysvar_append(const char* name, uint8_t type, void* addr);
#endif
#endif
