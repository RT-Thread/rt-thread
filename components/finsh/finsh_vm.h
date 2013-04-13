/*
 *  Virtual machine finsh shell.
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
