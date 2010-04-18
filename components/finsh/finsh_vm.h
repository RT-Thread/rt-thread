/*
 * File      : finsh_vm.h
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
#ifndef __FINSH_VM_H__
#define __FINSH_VM_H__

#include <finsh.h>

#include "finsh_var.h"

union finsh_value {
	char	char_value;
	short	short_value;
	long	long_value;
	void*	ptr;
};

extern union finsh_value*	finsh_sp;		/* stack pointer */
extern u_char*				finsh_pc;		/* PC */

/* stack */
extern union finsh_value	finsh_vm_stack[FINSH_STACK_MAX];
/* text segment */
extern u_char				text_segment[FINSH_TEXT_MAX];

void finsh_vm_run(void);
//void finsh_disassemble(void);

#endif
