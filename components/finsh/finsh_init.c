/*
 * File      : finsh_init.c
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
