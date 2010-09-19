/*
 * File      : module.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2010-01-09      Bernard	first version
 * 2010-04-09      yi.qiu	implement based on first version
 */

#include <rtthread.h>
#include <rtm.h>

#include "string.h"
#include "kservice.h"

#define RT_MODULE_DEBUG
#ifdef RT_USING_MODULE
#include "module.h"

#define elf_module 		((Elf32_Ehdr *)module_ptr)
#define shdr				((Elf32_Shdr *)((rt_uint8_t *)module_ptr + elf_module->e_shoff))
#define phdr				((Elf32_Phdr *)((rt_uint8_t *)module_ptr + elf_module->e_phoff))

#define IS_PROG(s)		(s.sh_type == SHT_PROGBITS)
#define IS_NOPROG(s)		(s.sh_type == SHT_NOBITS)
#define IS_REL(s)			(s.sh_type == SHT_REL)
#define IS_RELA(s)		(s.sh_type == SHT_RELA)
#define IS_ALLOC(s)		(s.sh_flags == SHF_ALLOC)
#define IS_AX(s)			((s.sh_flags & SHF_ALLOC) && (s.sh_flags & SHF_EXECINSTR))
#define IS_AW(s)			((s.sh_flags & SHF_ALLOC) && (s.sh_flags & SHF_WRITE))

static struct rt_module* rt_current_module;

/**
 * This function will return self module object
 *
 * @return the self module object
 *
 */
rt_module_t rt_module_self (void)
{
	/* return current module */
	return rt_current_module;
}

/**
 * This function will set current module object
 *
 * @return RT_EOK
 */
rt_err_t rt_module_set (rt_module_t module)
{
	/* set current module */
	rt_current_module = module;

	return RT_EOK;
}

static int rt_module_arm_relocate(struct rt_module* module, Elf32_Rel *rel, Elf32_Addr sym_val)
{
	Elf32_Addr *where, tmp;
	Elf32_Sword addend;

	where = (Elf32_Addr *)((rt_uint8_t*)module->module_space + rel->r_offset);
	switch (ELF32_R_TYPE(rel->r_info))
	{
	case R_ARM_NONE:
		break;

	case R_ARM_ABS32:
		*where += (Elf32_Addr)sym_val;
#ifdef RT_MODULE_DEBUG
		rt_kprintf("R_ARM_ABS32: %x -> %x\n", where, *where);
#endif
		break;

	case R_ARM_PC24:
	case R_ARM_PLT32:
	case R_ARM_CALL:
	case R_ARM_JUMP24:
		addend = *where & 0x00ffffff;
		if (addend & 0x00800000)
			addend |= 0xff000000;
		tmp = sym_val - (Elf32_Addr)where + (addend << 2);
		tmp >>= 2;
		*where = (*where & 0xff000000) | (tmp & 0x00ffffff);
#ifdef RT_MODULE_DEBUG
		rt_kprintf("R_ARM_PC24: %x -> %x\n", where, *where);
#endif
		break;

	case R_ARM_V4BX:
		*where &= 0xf000000f;
		*where |= 0x01a0f000;
		break;
	case R_ARM_GLOB_DAT:
		*where += (Elf32_Addr)sym_val;
		break;
	case R_ARM_JUMP_SLOT:
		break;
	default:
		return -1;
	}

	return 0;
}

static void rt_module_init_object_container(struct rt_module* module)
{
	RT_ASSERT(module != RT_NULL);

	/* init object container - thread */
	rt_list_init(&(module->module_object[RT_Object_Class_Thread].object_list));
	module->module_object[RT_Object_Class_Thread].object_size = sizeof(struct rt_thread);
	module->module_object[RT_Object_Class_Thread].type = RT_Object_Class_Thread;

#ifdef RT_USING_SEMAPHORE
	/* init object container - semaphore */
	rt_list_init(&(module->module_object[RT_Object_Class_Semaphore].object_list));
	module->module_object[RT_Object_Class_Semaphore].object_size = sizeof(struct rt_semaphore);
	module->module_object[RT_Object_Class_Semaphore].type = RT_Object_Class_Semaphore;
#endif

#ifdef RT_USING_MUTEX
	/* init object container - mutex */
	rt_list_init(&(module->module_object[RT_Object_Class_Mutex].object_list));
	module->module_object[RT_Object_Class_Mutex].object_size = sizeof(struct rt_mutex);
	module->module_object[RT_Object_Class_Mutex].type = RT_Object_Class_Mutex;
#endif

#ifdef RT_USING_EVENT
	/* init object container - event */
	rt_list_init(&(module->module_object[RT_Object_Class_Event].object_list));
	module->module_object[RT_Object_Class_Event].object_size = sizeof(struct rt_event);
	module->module_object[RT_Object_Class_Event].type = RT_Object_Class_Event;
#endif

#ifdef RT_USING_MAILBOX
	/* init object container - mailbox */
	rt_list_init(&(module->module_object[RT_Object_Class_MailBox].object_list));
	module->module_object[RT_Object_Class_MailBox].object_size = sizeof(struct rt_mailbox);
	module->module_object[RT_Object_Class_MailBox].type = RT_Object_Class_MailBox;
#endif

#ifdef RT_USING_MESSAGEQUEUE
	/* init object container - message queue */
	rt_list_init(&(module->module_object[RT_Object_Class_MessageQueue].object_list));
	module->module_object[RT_Object_Class_MessageQueue].object_size = sizeof(struct rt_messagequeue);
	module->module_object[RT_Object_Class_MessageQueue].type = RT_Object_Class_MessageQueue;
#endif

#ifdef RT_USING_MEMPOOL
	/* init object container - memory pool */
	rt_list_init(&(module->module_object[RT_Object_Class_MemPool].object_list));
	module->module_object[RT_Object_Class_MemPool].object_size = sizeof(struct rt_mempool);
	module->module_object[RT_Object_Class_MemPool].type = RT_Object_Class_MemPool;
#endif

#ifdef RT_USING_DEVICE
	/* init object container - device */
	rt_list_init(&(module->module_object[RT_Object_Class_Device].object_list));
	module->module_object[RT_Object_Class_Device].object_size = sizeof(struct rt_device);
	module->module_object[RT_Object_Class_Device].type = RT_Object_Class_Device;
#endif

	/* init object container - timer */
	rt_list_init(&(module->module_object[RT_Object_Class_Timer].object_list));
	module->module_object[RT_Object_Class_Timer].object_size = sizeof(struct rt_timer);
	module->module_object[RT_Object_Class_Timer].type = RT_Object_Class_Timer;
}

/**
 * This function will load a module from memory and create a thread for it
 *
 * @param name the name of module, which shall be unique
 * @param module_ptr the memory address of module image
 *
 * @return the module object
 *
 */
rt_module_t rt_module_load(const rt_uint8_t* name, void* module_ptr)
{
	rt_uint32_t index;
	rt_uint32_t module_size = 0;
	struct rt_module* module = RT_NULL;
	rt_uint8_t *ptr, *strtab, *shstrab;

#ifdef RT_MODULE_DEBUG
	rt_kprintf("rt_module_load: %s\n", name);
#endif
	/* check ELF header */
	if (rt_memcmp(elf_module->e_ident, RTMMAG, SELFMAG) != 0 ||
		elf_module->e_ident[EI_CLASS] != ELFCLASS32)
	{
		rt_kprintf(" module magic error\n");
		return RT_NULL;
	}
	
	/* get the ELF image size */
	for (index = 0; index < elf_module->e_phnum; index++)
	{
		if(phdr[index].p_type == PT_LOAD)
			module_size += phdr[index].p_memsz;
	}	
	
	if (module_size == 0) 
	{
		rt_kprintf(" module size error\n");
		return module;
	}	

	/* allocate module */
	module = (struct rt_module *)rt_object_allocate(RT_Object_Class_Module, (const char*)name);
	if (module == RT_NULL) return RT_NULL;

	/* allocate module space */
	module->module_space = rt_malloc(module_size);
	if (module->module_space == RT_NULL)
	{
		rt_object_delete(&(module->parent));
		return RT_NULL;
	}

	/* zero all space */
	ptr = module->module_space;
	rt_memset(ptr, 0, module_size);

	for (index = 0; index < elf_module->e_phnum; index++)
	{
		if(phdr[index].p_type == PT_LOAD)
		{
			rt_memcpy(ptr, (rt_uint8_t*)elf_module + phdr[index].p_offset, phdr[index].p_filesz);
			ptr += phdr[index].p_memsz;
		}		
	}	

	/* set module entry */
	module->module_entry = (rt_uint8_t*)module->module_space + elf_module->e_entry;
	
	/* handle relocation section */
	for (index = 0; index < elf_module->e_shnum; index ++)
	{
		if (IS_REL(shdr[index]))
		{
			rt_uint32_t i, nr_reloc;
			Elf32_Sym *symtab;
			Elf32_Rel *rel;

			/* get relocate item */
			rel = (Elf32_Rel *) ((rt_uint8_t*)module_ptr + shdr[index].sh_offset);

			/* locate .rel.plt and .rel.dyn */
			symtab =(Elf32_Sym *) ((rt_uint8_t*)module_ptr + shdr[shdr[index].sh_link].sh_offset);
			strtab = (rt_uint8_t*) module_ptr + shdr[shdr[shdr[index].sh_link].sh_link].sh_offset;
 			nr_reloc = (rt_uint32_t) (shdr[index].sh_size / sizeof(Elf32_Rel));

			/* relocate every items */
			for (i = 0; i < nr_reloc; i ++)
			{
				Elf32_Addr addr = 0;
				Elf32_Sym *sym = &symtab[ELF32_R_SYM(rel->r_info)];
#ifdef RT_MODULE_DEBUG
				rt_kprintf("relocate symbol %s\n", strtab + sym->st_name);
#endif
				rt_module_arm_relocate(module, rel, (Elf32_Addr)((rt_uint8_t*)module->module_space + sym->st_value));
				rel ++;
			}
		}
	}

	/* init module object container */
	rt_module_init_object_container(module);

	module->stack_size = 512;
	module->thread_priority = 90;
	module->module_thread = rt_thread_create(name,
		module->module_entry, RT_NULL,
		module->stack_size,
		module->thread_priority, 10);
	module->module_thread->module_parent = module;
	rt_thread_startup(module->module_thread);
		
	return module;
}	

/**
 * This function will unload a module from memory and release resources 
 *
 * @param module the module to be unloaded
 *
 * @return the operation status, RT_EOK on OK; -RT_ERROR on error
 *
 */
rt_err_t rt_module_unload(rt_module_t module)
{
	int i;
	struct rt_object* object;
	struct rt_list_node *list, *node;

#ifdef RT_MODULE_DEBUG
	rt_kprintf("rt_module_unload %s\n", module->parent.name);
#endif

	/* check parameter */
	RT_ASSERT(module != RT_NULL);

	/* suspend module main thread */
	if (module->module_thread->stat == RT_THREAD_READY)
		rt_thread_suspend(module->module_thread);

	/* delete all module object */
	for(i = RT_Object_Class_Thread; i < RT_Object_Class_Module; i++)
	{	
		list = &module->module_object[i].object_list;	
		for (node = list->next; node != list; node = node->next)
		{
			object = rt_list_entry(node, struct rt_object, list);
			if (rt_object_is_systemobject(object) == RT_EOK)
			{
				/* detach static objcet */
				rt_object_detach(object);
			}
			else
			{	
				/* delete dynamic object */
				rt_object_delete(object);
			}	
		}
	}	
	
	/* release module memory */
	rt_free(module->module_space);
	rt_object_delete((struct rt_object *)module);

	return RT_EOK;
}

/**
 * This function will find the specified module.
 *
 * @param name the name of module finding
 *
 * @return the module
 */
rt_module_t rt_module_find(char* name)
{
	struct rt_object_information *information;
	struct rt_object* object;
	struct rt_list_node* node;

	extern struct rt_object_information rt_object_container[];

	/* enter critical */
	rt_enter_critical();

	/* try to find device object */
	information = &rt_object_container[RT_Object_Class_Thread];
	for (node = information->object_list.next; node != &(information->object_list); node = node->next)
	{
		object = rt_list_entry(node, struct rt_object, list);
		if (rt_strncmp(object->name, name, RT_NAME_MAX) == 0)
		{
			/* leave critical */
			rt_exit_critical();

			return (rt_module_t)object;
		}
	}

	/* leave critical */
	rt_exit_critical();

	/* not found */
	return RT_NULL;
}

#endif
