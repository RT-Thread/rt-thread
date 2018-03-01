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
#ifndef __FINSH_NODE_H__
#define __FINSH_NODE_H__

#include <finsh.h>

#define FINSH_NODE_UNKNOWN          0
#define FINSH_NODE_ID               1

#define FINSH_NODE_VALUE_CHAR       2
#define FINSH_NODE_VALUE_INT        3
#define FINSH_NODE_VALUE_LONG       4
#define FINSH_NODE_VALUE_STRING     5
#define FINSH_NODE_VALUE_NULL       6

#define FINSH_NODE_SYS_ADD          7
#define FINSH_NODE_SYS_SUB          8
#define FINSH_NODE_SYS_MUL          9
#define FINSH_NODE_SYS_DIV          10
#define FINSH_NODE_SYS_MOD          11
#define FINSH_NODE_SYS_AND          12
#define FINSH_NODE_SYS_OR           13
#define FINSH_NODE_SYS_XOR          14
#define FINSH_NODE_SYS_BITWISE      15
#define FINSH_NODE_SYS_SHL          16
#define FINSH_NODE_SYS_SHR          17
#define FINSH_NODE_SYS_FUNC         18
#define FINSH_NODE_SYS_ASSIGN       19
#define FINSH_NODE_SYS_CAST         20
#define FINSH_NODE_SYS_PREINC       21
#define FINSH_NODE_SYS_PREDEC       22
#define FINSH_NODE_SYS_INC          23
#define FINSH_NODE_SYS_DEC          24
#define FINSH_NODE_SYS_GETVALUE    25
#define FINSH_NODE_SYS_GETADDR     26
#define FINSH_NODE_SYS_NULL         27

#define FINSH_DATA_TYPE_VOID        0x00
#define FINSH_DATA_TYPE_BYTE        0x01
#define FINSH_DATA_TYPE_WORD        0x02
#define FINSH_DATA_TYPE_DWORD       0x03
#define FINSH_DATA_TYPE_PTR         0x10

#define FINSH_NODE_VALUE            0
#define FINSH_NODE_ADDRESS          1
#define FINSH_NODE_FUNCTION         2

int finsh_node_init(void);

struct finsh_node* finsh_node_allocate(uint8_t type);
struct finsh_node* finsh_node_new_id(char* id);
struct finsh_node* finsh_node_new_char(char c);
struct finsh_node* finsh_node_new_int(int i);
struct finsh_node* finsh_node_new_long(long l);
struct finsh_node* finsh_node_new_string(char* s);
struct finsh_node* finsh_node_new_ptr(void* ptr);

#define finsh_node_sibling(node)    ((node)->sibling)
#define finsh_node_child(node)      ((node)->child)

#endif
