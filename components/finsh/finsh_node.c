/*
 *  node routines for finsh shell.
 *
 * COPYRIGHT (C) 2006 - 2013, RT-Thread Development Team
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-22     Bernard      first version
 */
#include <finsh.h>

#include "finsh_node.h"
#include "finsh_error.h"
#include "finsh_var.h"
#include "finsh_heap.h"

struct finsh_node global_node_table[FINSH_NODE_MAX];

int finsh_node_init()
{
    memset(global_node_table, 0, sizeof(global_node_table));

    return 0;
}

struct finsh_node* finsh_node_allocate(uint8_t type)
{
    int i;

    /* find an empty entry */
    for (i = 0; i < FINSH_NODE_MAX; i ++)
    {
        if (global_node_table[i].node_type == FINSH_NODE_UNKNOWN) break;
    }

    if (i == FINSH_NODE_MAX) return NULL;

    /* fill type field */
    global_node_table[i].node_type = type;

    /* return this allocated node */
    return &global_node_table[i];
}

struct finsh_node* finsh_node_new_id(char* id)
{
    struct finsh_node* node;
    void*  symbol;
    unsigned char type;

    symbol  = NULL;
    type    = 0;
    node    = NULL;

    /* lookup variable firstly */
    symbol = (void*)finsh_var_lookup(id);
    if (symbol == NULL)
    {
        /* then lookup system variable */
        symbol = (void*)finsh_sysvar_lookup(id);
        if (symbol == NULL)
        {
            /* then lookup system call */
            symbol = (void*)finsh_syscall_lookup(id);
            if (symbol != NULL) type = FINSH_IDTYPE_SYSCALL;
        }
        else type = FINSH_IDTYPE_SYSVAR;
    }
    else type = FINSH_IDTYPE_VAR;

    if (symbol != NULL)
    {
        /* allocate a new node */
        node = finsh_node_allocate(FINSH_NODE_ID);

        /* allocate node error */
        if (node == NULL)
        {
            finsh_error_set(FINSH_ERROR_MEMORY_FULL);
            return NULL;
        }

        /* fill node value according type */
        switch (type)
        {
        case FINSH_IDTYPE_VAR:
            node->id.var = (struct finsh_var*)symbol;
            break;

        case FINSH_IDTYPE_SYSVAR:
            node->id.sysvar = (struct finsh_sysvar*)symbol;
            break;

        case FINSH_IDTYPE_SYSCALL:
            node->id.syscall = (struct finsh_syscall*)symbol;
            break;
        }
        /* fill identifier type */
        node->idtype = type;
    }
    else finsh_error_set(FINSH_ERROR_UNKNOWN_SYMBOL);

    return node;
}

struct finsh_node* finsh_node_new_char(char c)
{
    struct finsh_node* node;

    node = finsh_node_allocate(FINSH_NODE_VALUE_CHAR);
    if (node == NULL)
    {
        finsh_error_set(FINSH_ERROR_MEMORY_FULL);
        return NULL;
    }

    node->value.char_value = c;
    return node;
}

struct finsh_node* finsh_node_new_int(int i)
{
    struct finsh_node* node;

    node = finsh_node_allocate(FINSH_NODE_VALUE_INT);
    if (node == NULL)
    {
        finsh_error_set(FINSH_ERROR_MEMORY_FULL);
        return NULL;
    }

    node->value.int_value = i;
    return node;
}

struct finsh_node* finsh_node_new_long(long l)
{
    struct finsh_node* node;

    node = finsh_node_allocate(FINSH_NODE_VALUE_LONG);
    if (node == NULL)
    {
        finsh_error_set(FINSH_ERROR_MEMORY_FULL);
        return NULL;
    }

    node->value.long_value = l;
    return node;
}

struct finsh_node* finsh_node_new_string(char* s)
{
    struct finsh_node* node;

    node = finsh_node_allocate(FINSH_NODE_VALUE_STRING);
    if (node == NULL)
    {
        finsh_error_set(FINSH_ERROR_MEMORY_FULL);
        return NULL;
    }

    /* make string */
    node->value.ptr = finsh_heap_allocate(strlen(s) + 1);
    strncpy(node->value.ptr, s, strlen(s));
    ((uint8_t*)node->value.ptr)[strlen(s)] = '\0';

    return node;
}

struct finsh_node* finsh_node_new_ptr(void* ptr)
{
    struct finsh_node* node;

    node = finsh_node_allocate(FINSH_NODE_VALUE_NULL);
    if (node == NULL)
    {
        finsh_error_set(FINSH_ERROR_MEMORY_FULL);
        return NULL;
    }

    node->value.ptr = ptr;
    return node;
}
