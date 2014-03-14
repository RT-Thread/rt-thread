/*
 *  Virtual machine of finsh shell.
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

#include "finsh_vm.h"
#include "finsh_ops.h"
#include "finsh_var.h"

/* stack */
union finsh_value	finsh_vm_stack[FINSH_STACK_MAX];
/* text segment */
u_char				text_segment[FINSH_TEXT_MAX];

union finsh_value*	finsh_sp;		/* stack pointer */
u_char*				finsh_pc;		/* PC */

/* syscall list, for dynamic system call register */
struct finsh_syscall_item* global_syscall_list = NULL;

// #define FINSH_VM_DISASSEMBLE
void finsh_vm_run()
{
	u_char op;

	/* if you want to disassemble the byte code, please define FINSH_VM_DISASSEMBLE */
#ifdef FINSH_VM_DISASSEMBLE
	void finsh_disassemble();
	finsh_disassemble();
#endif

	/* set sp(stack pointer) to the beginning of stack */
	finsh_sp = &finsh_vm_stack[0];

	/* set pc to the beginning of text segment */
	finsh_pc = &text_segment[0];

	while ((finsh_pc - &text_segment[0] >= 0) &&
		(finsh_pc - &text_segment[0] < FINSH_TEXT_MAX))
	{
		/* get op */
		op = *finsh_pc++;

		/* call op function */
		op_table[op]();
	}
}

#ifdef RT_USING_HEAP
void finsh_syscall_append(const char* name, syscall_func func)
{
	/* create the syscall */
	struct finsh_syscall_item* item;

	item = (struct finsh_syscall_item*)rt_malloc(sizeof(struct finsh_syscall_item));
	if (item != RT_NULL)
	{
		item->next = NULL;
		item->syscall.name = rt_strdup(name);
		item->syscall.func = func;

		if (global_syscall_list == NULL)
		{
			global_syscall_list = item;
		}
		else
		{
			item->next = global_syscall_list;
			global_syscall_list = item;
		}
	}
}
#endif

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(__x86_64__))
struct finsh_syscall* finsh_syscall_next(struct finsh_syscall* call)
{
	unsigned int *ptr;
	ptr = (unsigned int*) (call + 1);
	while ((*ptr == 0) && ((unsigned int*)ptr < (unsigned int*) _syscall_table_end))
		ptr ++;

	return (struct finsh_syscall*)ptr;
}

struct finsh_sysvar* finsh_sysvar_next(struct finsh_sysvar* call)
{
	unsigned int *ptr;
	ptr = (unsigned int*) (call + 1);
	while ((*ptr == 0) && ((unsigned int*)ptr < (unsigned int*) _sysvar_table_end))
		ptr ++;

	return (struct finsh_sysvar*)ptr;
}
#endif

struct finsh_syscall* finsh_syscall_lookup(const char* name)
{
	struct finsh_syscall* index;
	struct finsh_syscall_item* item;

	for (index = _syscall_table_begin; index < _syscall_table_end; FINSH_NEXT_SYSCALL(index))
	{
		if (strcmp(index->name, name) == 0)
			return index;
	}

	/* find on syscall list */
	item = global_syscall_list;
	while (item != NULL)
	{
		if (strncmp(item->syscall.name, name, strlen(name)) == 0)
		{
			return &(item->syscall);
		}

		item = item->next;
	}

	return NULL;
}

#ifdef FINSH_VM_DISASSEMBLE
void finsh_disassemble()
{
	u_char *pc, op;

	pc = &text_segment[0];
	while (*pc != 0)
	{
		op = *pc;
		switch (op)
		{
		case FINSH_OP_ADD_BYTE:
			pc ++;
			rt_kprintf("addb\n");
			break;

		case FINSH_OP_SUB_BYTE:
			pc ++;
			rt_kprintf("subb\n");
			break;

		case FINSH_OP_DIV_BYTE:
			pc ++;
			rt_kprintf("divb\n");
			break;

		case FINSH_OP_MOD_BYTE:
			pc ++;
			rt_kprintf("modb\n");
			break;

		case FINSH_OP_MUL_BYTE:
			pc ++;
			rt_kprintf("mulb\n");
			break;

		case FINSH_OP_AND_BYTE:
			pc ++;
			rt_kprintf("andb\n");
			break;

		case FINSH_OP_OR_BYTE:
			pc ++;
			rt_kprintf("orb\n");
			break;

		case FINSH_OP_XOR_BYTE:
			pc ++;
			rt_kprintf("xorb\n");
			break;

		case FINSH_OP_BITWISE_BYTE:
			pc ++;
			rt_kprintf("bwb\n");
			break;

		case FINSH_OP_SHL_BYTE:
			pc ++;
			rt_kprintf("shlb\n");
			break;

		case FINSH_OP_SHR_BYTE:
			pc ++;
			rt_kprintf("shrb\n");
			break;

		case FINSH_OP_LD_BYTE:
			pc ++;
			rt_kprintf("ldb %d\n", *pc++);
			break;

		case FINSH_OP_LD_VALUE_BYTE:
			pc ++;
			rt_kprintf("ldb [0x%x]\n", FINSH_GET32(pc));
			pc += 4;
			break;

		case FINSH_OP_ST_BYTE:
			pc ++;
			rt_kprintf("stb\n");
			break;

		case FINSH_OP_ADD_WORD:
			pc ++;
			rt_kprintf("addw\n");
			break;

		case FINSH_OP_SUB_WORD:
			pc ++;
			rt_kprintf("subw\n");
			break;

		case FINSH_OP_DIV_WORD:
			pc ++;
			rt_kprintf("divw\n");
			break;

		case FINSH_OP_MOD_WORD:
			pc ++;
			rt_kprintf("modw\n");
			break;

		case FINSH_OP_MUL_WORD:
			pc ++;
			rt_kprintf("mulw\n");
			break;

		case FINSH_OP_AND_WORD:
			pc ++;
			rt_kprintf("andw\n");
			break;

		case FINSH_OP_OR_WORD:
			pc ++;
			rt_kprintf("orw\n");
			break;

		case FINSH_OP_XOR_WORD:
			pc ++;
			rt_kprintf("xorw\n");
			break;

		case FINSH_OP_BITWISE_WORD:
			pc ++;
			rt_kprintf("bww\n");
			break;

		case FINSH_OP_SHL_WORD:
			pc ++;
			rt_kprintf("shlw\n");
			break;

		case FINSH_OP_SHR_WORD:
			pc ++;
			rt_kprintf("shrw\n");
			break;

		case FINSH_OP_LD_WORD:
			pc ++;
			rt_kprintf("ldw %d\n", FINSH_GET16(pc));
			pc += 2;
			break;

		case FINSH_OP_LD_VALUE_WORD:
			pc ++;
			rt_kprintf("ldw [0x%x]\n", FINSH_GET32(pc));
			pc += 4;
			break;

		case FINSH_OP_ST_WORD:
			pc ++;
			rt_kprintf("stw\n");
			break;

		case FINSH_OP_ADD_DWORD:
			pc ++;
			rt_kprintf("addd\n");
			break;

		case FINSH_OP_SUB_DWORD:
			pc ++;
			rt_kprintf("subd\n");
			break;

		case FINSH_OP_DIV_DWORD:
			pc ++;
			rt_kprintf("divd\n");
			break;

		case FINSH_OP_MOD_DWORD:
			pc ++;
			rt_kprintf("modd\n");
			break;

		case FINSH_OP_MUL_DWORD:
			pc ++;
			rt_kprintf("muld\n");
			break;

		case FINSH_OP_AND_DWORD:
			pc ++;
			rt_kprintf("andd\n");
			break;

		case FINSH_OP_OR_DWORD:
			pc ++;
			rt_kprintf("ord\n");
			break;

		case FINSH_OP_XOR_DWORD:
			pc ++;
			rt_kprintf("xord\n");
			break;

		case FINSH_OP_BITWISE_DWORD:
			pc ++;
			rt_kprintf("bwd\n");
			break;

		case FINSH_OP_SHL_DWORD:
			pc ++;
			rt_kprintf("shld\n");
			break;

		case FINSH_OP_SHR_DWORD:
			pc ++;
			rt_kprintf("shrd\n");
			break;

		case FINSH_OP_LD_DWORD:
			pc ++;
			rt_kprintf("ldd 0x%x\n", FINSH_GET32(pc));
			pc += 4;
			break;

		case FINSH_OP_LD_VALUE_DWORD:
			pc ++;
			rt_kprintf("ldd [0x%x]\n", FINSH_GET32(pc));
			pc += 4;
			break;

		case FINSH_OP_ST_DWORD:
			pc ++;
			rt_kprintf("std\n");
			break;

		case FINSH_OP_POP:
			rt_kprintf("pop\n");
			pc ++;
			break;

		case FINSH_OP_SYSCALL:
			pc ++;
			rt_kprintf("syscall %d\n", *pc++);
			break;

		case FINSH_OP_LD_VALUE_BYTE_STACK:
			pc ++;
			rt_kprintf("ldb [sp]\n");
			break;

		case FINSH_OP_LD_VALUE_WORD_STACK:
			pc ++;
			rt_kprintf("ldw [sp]\n");
			break;

		case FINSH_OP_LD_VALUE_DWORD_STACK:
			pc ++;
			rt_kprintf("ldd [sp]\n");
			break;

		default:
			return;
		}
	}
}
#endif
