/*
 * Initialization procedure for finsh shell.
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
#include "finsh_vm.h"
#include "finsh_parser.h"
#include "finsh_var.h"
#include "finsh_error.h"
#include "finsh_heap.h"

int finsh_init(struct finsh_parser* parser)
{
    finsh_parser_init(parser);

    /* finsh init */
    finsh_node_init();
    finsh_var_init();
    finsh_error_init();
    finsh_heap_init();

    return 0;
}

long finsh_stack_bottom()
{
    return finsh_vm_stack[0].long_value;
}

int finsh_flush(struct finsh_parser* parser)
{
    finsh_parser_init(parser);

    /* finsh init */
    finsh_node_init();
    finsh_error_init();

    return 0;
}

int finsh_reset(struct finsh_parser* parser)
{
    /* finsh init */
    finsh_node_init();
    finsh_var_init();
    finsh_error_init();
    finsh_heap_init();

    return 0;
}
