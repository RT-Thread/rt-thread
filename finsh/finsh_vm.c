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

// #define VM_DISASSEMBLE
void finsh_vm_run()
{
	u_char op;

	/* if want to disassemble the bytecode, please define VM_DISASSEMBLE */
#ifdef VM_DISASSEMBLE
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
extern char *strdup(const char *s);
void finsh_syscall_append(const char* name, syscall_func func)
{
	/* create the syscall */
	struct finsh_syscall_item* item;

	item = (struct finsh_syscall_item*)rt_malloc(sizeof(struct finsh_syscall_item));
	if (item != RT_NULL)
	{
		item->next = NULL;
		item->syscall.name = strdup(name);
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

struct finsh_syscall* finsh_syscall_lookup(const char* name)
{
	struct finsh_syscall* index;
	struct finsh_syscall_item* item;

	for (index = _syscall_table_begin; index < _syscall_table_end; index ++)
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

#ifdef VM_DISASSEMBLE
#include <stdio.h>
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
			printf("addb\n");
			break;

		case FINSH_OP_SUB_BYTE:
			pc ++;
			printf("subb\n");
			break;

		case FINSH_OP_DIV_BYTE:
			pc ++;
			printf("divb\n");
			break;

		case FINSH_OP_MOD_BYTE:
			pc ++;
			printf("modb\n");
			break;

		case FINSH_OP_MUL_BYTE:
			pc ++;
			printf("mulb\n");
			break;

		case FINSH_OP_AND_BYTE:
			pc ++;
			printf("andb\n");
			break;

		case FINSH_OP_OR_BYTE:
			pc ++;
			printf("orb\n");
			break;

		case FINSH_OP_XOR_BYTE:
			pc ++;
			printf("xorb\n");
			break;

		case FINSH_OP_BITWISE_BYTE:
			pc ++;
			printf("bwb\n");
			break;

		case FINSH_OP_SHL_BYTE:
			pc ++;
			printf("shlb\n");
			break;

		case FINSH_OP_SHR_BYTE:
			pc ++;
			printf("shrb\n");
			break;

		case FINSH_OP_LD_BYTE:
			pc ++;
			printf("ldb %d\n", *pc++);
			break;

		case FINSH_OP_LD_VALUE_BYTE:
			pc ++;
			printf("ldb [0x%x]\n", FINSH_GET32(pc));
			pc += 4;
			break;

		case FINSH_OP_ST_BYTE:
			pc ++;
			printf("stb\n");
			break;

		case FINSH_OP_ADD_WORD:
			pc ++;
			printf("addw\n");
			break;

		case FINSH_OP_SUB_WORD:
			pc ++;
			printf("subw\n");
			break;

		case FINSH_OP_DIV_WORD:
			pc ++;
			printf("divw\n");
			break;

		case FINSH_OP_MOD_WORD:
			pc ++;
			printf("modw\n");
			break;

		case FINSH_OP_MUL_WORD:
			pc ++;
			printf("mulw\n");
			break;

		case FINSH_OP_AND_WORD:
			pc ++;
			printf("andw\n");
			break;

		case FINSH_OP_OR_WORD:
			pc ++;
			printf("orw\n");
			break;

		case FINSH_OP_XOR_WORD:
			pc ++;
			printf("xorw\n");
			break;

		case FINSH_OP_BITWISE_WORD:
			pc ++;
			printf("bww\n");
			break;

		case FINSH_OP_SHL_WORD:
			pc ++;
			printf("shlw\n");
			break;

		case FINSH_OP_SHR_WORD:
			pc ++;
			printf("shrw\n");
			break;

		case FINSH_OP_LD_WORD:
			pc ++;
			printf("ldw %d\n", FINSH_GET16(pc));
			pc += 2;
			break;

		case FINSH_OP_LD_VALUE_WORD:
			pc ++;
			printf("ldw [0x%x]\n", FINSH_GET32(pc));
			pc += 4;
			break;

		case FINSH_OP_ST_WORD:
			pc ++;
			printf("stw\n");
			break;

		case FINSH_OP_ADD_DWORD:
			pc ++;
			printf("addd\n");
			break;

		case FINSH_OP_SUB_DWORD:
			pc ++;
			printf("subd\n");
			break;

		case FINSH_OP_DIV_DWORD:
			pc ++;
			printf("divd\n");
			break;

		case FINSH_OP_MOD_DWORD:
			pc ++;
			printf("modd\n");
			break;

		case FINSH_OP_MUL_DWORD:
			pc ++;
			printf("muld\n");
			break;

		case FINSH_OP_AND_DWORD:
			pc ++;
			printf("andd\n");
			break;

		case FINSH_OP_OR_DWORD:
			pc ++;
			printf("ord\n");
			break;

		case FINSH_OP_XOR_DWORD:
			pc ++;
			printf("xord\n");
			break;

		case FINSH_OP_BITWISE_DWORD:
			pc ++;
			printf("bwd\n");
			break;

		case FINSH_OP_SHL_DWORD:
			pc ++;
			printf("shld\n");
			break;

		case FINSH_OP_SHR_DWORD:
			pc ++;
			printf("shrd\n");
			break;

		case FINSH_OP_LD_DWORD:
			pc ++;
			printf("ldd 0x%x\n", FINSH_GET32(pc));
			pc += 4;
			break;

		case FINSH_OP_LD_VALUE_DWORD:
			pc ++;
			printf("ldd [0x%x]\n", FINSH_GET32(pc));
			pc += 4;
			break;

		case FINSH_OP_ST_DWORD:
			pc ++;
			printf("std\n");
			break;

		case FINSH_OP_POP:
			printf("pop\n");
			pc ++;
			break;

		case FINSH_OP_SYSCALL:
			pc ++;
			printf("syscall %d\n", *pc++);
			break;

		case FINSH_OP_LD_VALUE_BYTE_STACK:
			pc ++;
			printf("ldb [sp]\n");
			break;

		case FINSH_OP_LD_VALUE_WORD_STACK:
			pc ++;
			printf("ldw [sp]\n");
			break;

		case FINSH_OP_LD_VALUE_DWORD_STACK:
			pc ++;
			printf("ldd [sp]\n");
			break;

		default:
			return;
		}
	}
}
#endif
