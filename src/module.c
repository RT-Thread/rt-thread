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
 * 2010-10-23      yi.qiu	implement module memory allocator
 */

#include <rtthread.h>
#include <rtm.h>

#include "string.h"
#include "kservice.h"

/* #define RT_MODULE_DEBUG */
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

/* module memory allocator */
struct rt_module_page
{
	rt_uint8_t *ptr;				/* address of memory block  */
	rt_size_t npage;					/* number of pages  */
	rt_list_t list;
};
static struct rt_module_page *rt_module_page_list;

/* module memory allocator */
struct rt_mem_head
{
	rt_size_t size;				/* size of memory block  */
	struct rt_mem_head *next;		/* next valid memory block */
};

static rt_module_t rt_current_module = RT_NULL;
rt_list_t rt_module_symbol_list;
struct rt_module_symtab *_rt_module_symtab_begin = RT_NULL, *_rt_module_symtab_end = RT_NULL;

/**
 * @ingroup SystemInit
 *
 * This function will initialize system module
 *
 */
void rt_system_module_init(void)
{
	extern int __rtmsymtab_start;
	extern int __rtmsymtab_end;

#ifdef __GNUC__
	_rt_module_symtab_begin = (struct rt_module_symtab *)&__rtmsymtab_start;
	_rt_module_symtab_end   = (struct rt_module_symtab *)&__rtmsymtab_end;
#endif

	rt_list_init(&rt_module_symbol_list);

	/* init current module */
	rt_current_module = RT_NULL;
}

static rt_uint32_t rt_module_symbol_find(const rt_uint8_t* sym_str)
{
	/* find in kernel symbol table */
	struct rt_module_symtab* index;
	for (index = _rt_module_symtab_begin; index != _rt_module_symtab_end; index ++)
	{
		if (rt_strcmp(index->name, (const char*)sym_str) == 0)
			return index->addr;
	}

	return 0;
}

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
	case R_ARM_JUMP_SLOT:
		*where = (Elf32_Addr)sym_val;
#ifdef RT_MODULE_DEBUG
		rt_kprintf("R_ARM_JUMP_SLOT: 0x%x -> 0x%x 0x%x\n", where, *where, sym_val);
#endif		
	break;
	default:
		return -1;
	}

	return 0;
}

static void rt_module_init_object_container(struct rt_module* module)
{
	RT_ASSERT(module != RT_NULL);

	/* initialize object container - thread */
	rt_list_init(&(module->module_object[RT_Object_Class_Thread].object_list));
	module->module_object[RT_Object_Class_Thread].object_size = sizeof(struct rt_thread);
	module->module_object[RT_Object_Class_Thread].type = RT_Object_Class_Thread;

#ifdef RT_USING_SEMAPHORE
	/* initialize object container - semaphore */
	rt_list_init(&(module->module_object[RT_Object_Class_Semaphore].object_list));
	module->module_object[RT_Object_Class_Semaphore].object_size = sizeof(struct rt_semaphore);
	module->module_object[RT_Object_Class_Semaphore].type = RT_Object_Class_Semaphore;
#endif

#ifdef RT_USING_MUTEX
	/* initialize object container - mutex */
	rt_list_init(&(module->module_object[RT_Object_Class_Mutex].object_list));
	module->module_object[RT_Object_Class_Mutex].object_size = sizeof(struct rt_mutex);
	module->module_object[RT_Object_Class_Mutex].type = RT_Object_Class_Mutex;
#endif

#ifdef RT_USING_EVENT
	/* initialize object container - event */
	rt_list_init(&(module->module_object[RT_Object_Class_Event].object_list));
	module->module_object[RT_Object_Class_Event].object_size = sizeof(struct rt_event);
	module->module_object[RT_Object_Class_Event].type = RT_Object_Class_Event;
#endif

#ifdef RT_USING_MAILBOX
	/* initialize object container - mailbox */
	rt_list_init(&(module->module_object[RT_Object_Class_MailBox].object_list));
	module->module_object[RT_Object_Class_MailBox].object_size = sizeof(struct rt_mailbox);
	module->module_object[RT_Object_Class_MailBox].type = RT_Object_Class_MailBox;
#endif

#ifdef RT_USING_MESSAGEQUEUE
	/* initialize object container - message queue */
	rt_list_init(&(module->module_object[RT_Object_Class_MessageQueue].object_list));
	module->module_object[RT_Object_Class_MessageQueue].object_size = sizeof(struct rt_messagequeue);
	module->module_object[RT_Object_Class_MessageQueue].type = RT_Object_Class_MessageQueue;
#endif

#ifdef RT_USING_MEMPOOL
	/* initialize object container - memory pool */
	rt_list_init(&(module->module_object[RT_Object_Class_MemPool].object_list));
	module->module_object[RT_Object_Class_MemPool].object_size = sizeof(struct rt_mempool);
	module->module_object[RT_Object_Class_MemPool].type = RT_Object_Class_MemPool;
#endif

#ifdef RT_USING_DEVICE
	/* initialize object container - device */
	rt_list_init(&(module->module_object[RT_Object_Class_Device].object_list));
	module->module_object[RT_Object_Class_Device].object_size = sizeof(struct rt_device);
	module->module_object[RT_Object_Class_Device].type = RT_Object_Class_Device;
#endif

	/* initialize object container - timer */
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
	rt_module_t module = RT_NULL;
	rt_uint8_t *ptr, *strtab;
	rt_bool_t linked = RT_FALSE;

	rt_kprintf("rt_module_load: %s\n", name);

	/* check ELF header */
	if (rt_memcmp(elf_module->e_ident, RTMMAG, SELFMAG) == 0)
	{
		/* rtmlinke finished */
		linked = RT_TRUE;
	}
	else	 if (rt_memcmp(elf_module->e_ident, ELFMAG, SELFMAG) != 0)
	{
		rt_kprintf(" module magic error\n");
		return RT_NULL;
	}

	/* check ELF class */
	if(elf_module->e_ident[EI_CLASS] != ELFCLASS32)
	{
		rt_kprintf(" module class error\n");
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
	if (!module) return RT_NULL;

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
	module->module_entry = module->module_space + elf_module->e_entry;
	
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
				Elf32_Sym *sym = &symtab[ELF32_R_SYM(rel->r_info)];
#ifdef RT_MODULE_DEBUG
				rt_kprintf("relocate symbol %s shndx %d\n", strtab + sym->st_name, sym->st_shndx);
#endif
				if(sym->st_shndx != 0)
				{	
					rt_module_arm_relocate(
						module, 
						rel, 
						(Elf32_Addr)(module->module_space + sym->st_value));
				}
				else if(linked == RT_FALSE)
				{
					Elf32_Addr addr;
#ifdef RT_MODULE_DEBUG
					rt_kprintf("unresolved relocate symbol: %s\n", strtab + sym->st_name);
#endif
					/* need to resolve symbol in kernel symbol table */
					addr = rt_module_symbol_find(strtab + sym->st_name);
					if (addr == 0)
					{
						rt_kprintf("can't find %s in kernel symbol table\n", strtab + sym->st_name);
						rt_object_delete(&(module->parent));
						rt_free(module);
						return RT_NULL;
					}	
					rt_module_arm_relocate(module, rel, addr);
				}
				rel ++;
			}
		}
	}

	/* construct module symbol table */
	for (index = 0; index < elf_module->e_shnum; index ++)
	{	
		rt_uint8_t* shstrab = (rt_uint8_t*) module_ptr + shdr[elf_module->e_shstrndx].sh_offset;
		if (rt_strcmp(shstrab + shdr[index].sh_name, ELF_RTMSYMTAB) == 0)
		{
			module->symtab = (struct rt_module_symtab *)(module->module_space + shdr[index].sh_addr);
			module->nsym = shdr[index].sh_size / sizeof(struct rt_module_symtab);
		}	
	}

	/* init module object container */
	rt_module_init_object_container(module);
		
	/* increase module reference count  */
	module->nref++;

	if(elf_module->e_entry != 0)
	{	
		/* init module page list */
		rt_list_init(&module->page_list);	

		/* init module memory allocator */
		module->mem_list = RT_NULL;
		
		/* create mpool for page node */
		module->mpool = rt_mp_create(name, 1024, sizeof(struct rt_module_page));
		
		/* create module thread */
		module->stack_size = 2048;
		module->thread_priority = 90;
		module->module_thread = rt_thread_create(name,
			module->module_entry, RT_NULL,
			module->stack_size,
			module->thread_priority, 10);
		
		module->module_thread->module_id = (void*)module;
		
		/* startup module thread */
		rt_thread_startup(module->module_thread);
	}	
	else
	{
		/* without entry point */
		module->parent.flag |= RT_MODULE_FLAG_WITHOUTENTRY;
	}	

	return module;
}	

#ifdef RT_USING_DFS
#include <dfs_posix.h>
/**
 * This function will load a module from a file
 *
 * @param filename the file name of application module
 *
 * @return the module object
 *
 */
rt_module_t rt_module_open(const char* filename)
{
	int fd, length;
	struct rt_module* module;
	struct stat s;
	char *buffer, *offset_ptr;;
	
	if (stat(filename, &s) !=0)
	{
		rt_kprintf("access file failed\n");
		return RT_NULL;
	}
	buffer = (char *)rt_malloc(s.st_size);
	if (buffer == RT_NULL)
	{
		rt_kprintf("out of memory\n");
		return RT_NULL;
	}

	offset_ptr = buffer;
	fd = open(filename, O_RDONLY, 0);
	if (fd < 0)
	{
		rt_kprintf("open file failed\n");
		rt_free(buffer);
		return RT_NULL;
	}

	do
	{
		length = read(fd, offset_ptr, 4096);
		if (length > 0)
		{
			offset_ptr += length;
		}
	}while (length > 0);

	/* close fd */
	close(fd);

	if ((rt_uint32_t)offset_ptr - (rt_uint32_t)buffer != s.st_size)
	{
		rt_kprintf("check: read file failed\n");
		rt_free(buffer);
		return RT_NULL;
	}
	
	module = rt_module_load(filename, (void *)buffer);
	rt_free(buffer);

	return module;
}

#if defined(RT_USING_FINSH)
#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(rt_module_open, exec, exec module from file);
#endif
#endif

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
	struct rt_object* object;
	struct rt_list_node *list;

	rt_kprintf("rt_module_unload: %s\n", module->parent.name);

	/* check parameter */
	RT_ASSERT(module != RT_NULL);

	/* module has entry point */
	if(!(module->parent.flag & RT_MODULE_FLAG_WITHOUTENTRY))
	{	
		/* suspend module main thread */
		if(module->module_thread != RT_NULL)
		{	
			if (module->module_thread->stat == RT_THREAD_READY)
				rt_thread_suspend(module->module_thread);
		}
		
		/* delete threads */
		list = &module->module_object[RT_Object_Class_Thread].object_list;	
		while(list->next != list)
		{
			object = rt_list_entry(list->next, struct rt_object, list);
			if (rt_object_is_systemobject(object) == RT_EOK)
			{
				/* detach static object */
				rt_thread_detach((rt_thread_t)object);
			}
			else
			{	
				/* delete dynamic object */
				rt_thread_delete((rt_thread_t)object);
			}	
		}
		
#ifdef RT_USING_SEMAPHORE
		/* delete semaphores */
		list = &module->module_object[RT_Object_Class_Thread].object_list;	
		while(list->next != list)
		{
			object = rt_list_entry(list->next, struct rt_object, list);
			if (rt_object_is_systemobject(object) == RT_EOK)
			{
				/* detach static object */
				rt_sem_detach((rt_sem_t)object);
			}
			else
			{	
				/* delete dynamic object */
				rt_sem_delete((rt_sem_t)object);
			}	
		}
#endif

#ifdef RT_USING_MUTEX
		/* delete mutexs*/
		list = &module->module_object[RT_Object_Class_Mutex].object_list;	
		while(list->next != list)
		{
			object = rt_list_entry(list->next, struct rt_object, list);
			if (rt_object_is_systemobject(object) == RT_EOK)
			{
				/* detach static object */
				rt_mutex_detach((rt_mutex_t)object);
			}
			else
			{	
				/* delete dynamic object */
				rt_mutex_delete((rt_mutex_t)object);
			}	
		}
#endif

#ifdef RT_USING_EVENT
		/* delete mailboxs */
		list = &module->module_object[RT_Object_Class_Event].object_list;	
		while(list->next != list)
		{
			object = rt_list_entry(list->next, struct rt_object, list);
			if (rt_object_is_systemobject(object) == RT_EOK)
			{
				/* detach static object */
				rt_event_detach((rt_event_t)object);
			}
			else
			{	
				/* delete dynamic object */
				rt_event_delete((rt_event_t)object);
			}	
		}
#endif

#ifdef RT_USING_MAILBOX
		/* delete mailboxs */
		list = &module->module_object[RT_Object_Class_MailBox].object_list;	
		while(list->next != list)
		{
			object = rt_list_entry(list->next, struct rt_object, list);
			if (rt_object_is_systemobject(object) == RT_EOK)
			{
				/* detach static object */
				rt_mb_detach((rt_mailbox_t)object);
			}
			else
			{	
				/* delete dynamic object */
				rt_mb_delete((rt_mailbox_t)object);
			}	
		}
#endif

#ifdef RT_USING_MESSAGEQUEUE
		/* delete msgqueues */
		list = &module->module_object[RT_Object_Class_MessageQueue].object_list;	
		while(list->next != list)
		{
			object = rt_list_entry(list->next, struct rt_object, list);
			if (rt_object_is_systemobject(object) == RT_EOK)
			{
				/* detach static object */
				rt_mq_detach((rt_mq_t)object);
			}
			else
			{	
				/* delete dynamic object */
				rt_mq_delete((rt_mq_t)object);
			}	
		}
#endif

#ifdef RT_USING_MEMPOOL
		/* delete mempools */
		list = &module->module_object[RT_Object_Class_MemPool].object_list;	
		while(list->next != list)
		{
			object = rt_list_entry(list->next, struct rt_object, list);
			if (rt_object_is_systemobject(object) == RT_EOK)
			{
				/* detach static object */
				rt_mp_detach((rt_mp_t)object);
			}
			else
			{	
				/* delete dynamic object */
				rt_mp_delete((rt_mp_t)object);
			}	
		}
#endif

#ifdef RT_USING_DEVICE
		/* delete devices */
		list = &module->module_object[RT_Object_Class_Device].object_list;	
		while(list->next != list)
		{
			object = rt_list_entry(list->next, struct rt_object, list);
			rt_device_unregister((rt_device_t)object);
		}	
#endif

		/* delete timers */
		list = &module->module_object[RT_Object_Class_Timer].object_list;
		while(list->next != list)
		{
			object = rt_list_entry(list->next, struct rt_object, list);
			if (rt_object_is_systemobject(object) == RT_EOK)
			{
				/* detach static object */
				rt_timer_detach((rt_timer_t)object);
			}
			else
			{	
				/* delete dynamic object */
				rt_timer_delete((rt_timer_t)object);
			}	
		}

		/* free module pages */
		list = &module->page_list;
		while(list->next != list)
		{
			struct rt_module_page* page;

			/* free page */
			page = rt_list_entry(list->next, struct rt_module_page, list);
			rt_page_free(page->ptr, page->npage);
			rt_list_remove(list->next);
		}	

		/* delete mpool */
		if(module->mpool) rt_mp_delete(module->mpool);
	}
	
	/* release module space memory */
	rt_free(module->module_space);

	/* delete module object */
	rt_object_delete((rt_object_t)module);

	return RT_EOK;
}

/**
 * This function will find the specified module.
 *
 * @param name the name of module finding
 *
 * @return the module
 */
rt_module_t rt_module_find(const char* name)
{
	struct rt_object_information *information;
	struct rt_object* object;
	struct rt_list_node* node;

	extern struct rt_object_information rt_object_container[];

	/* enter critical */
	rt_enter_critical();

	/* try to find device object */
	information = &rt_object_container[RT_Object_Class_Module];
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

static struct rt_mem_head *morepage(rt_size_t nu)
{
	rt_uint8_t *cp;
	rt_uint32_t npage;
	struct rt_mem_head *up;
	struct rt_module_page *node;

	RT_ASSERT (nu != 0);

	/* allocate pages from system heap */
	npage = (nu * sizeof(struct rt_mem_head) + RT_MM_PAGE_SIZE - 1)/RT_MM_PAGE_SIZE;
	cp = rt_page_alloc(npage);
	if(!cp) return RT_NULL;
	
	/* allocate page list node from mpool */
	node = rt_mp_alloc(rt_current_module->mpool, RT_WAITING_FOREVER);
	node->ptr = cp;
	node->npage = npage;

	/* insert page list node to moudle's page list */
	rt_list_insert_after (&rt_current_module->page_list, &node->list);

	up = (struct rt_mem_head *) cp;
	up->size = npage * RT_MM_PAGE_SIZE / sizeof(struct rt_mem_head);
	rt_module_free(rt_current_module, (void *)(up+1));
	
	return up;
}

/*
  rt_module_malloc - allocate memory block in free list
*/
void *rt_module_malloc(rt_size_t size)
{
	struct rt_mem_head *b, *n;
	struct rt_mem_head **prev;
	rt_size_t nunits;
	
	nunits = (size + sizeof(struct rt_mem_head) -1)/sizeof(struct rt_mem_head) + 1; 

	RT_ASSERT(size != 0);
	RT_ASSERT(nunits != 0);

	prev = (struct rt_mem_head **)&rt_current_module->mem_list;

	/* if size can be divided by page, allocate page directly */
	if(size % RT_MM_PAGE_SIZE == 0)
	{
		rt_uint8_t *cp;
		struct rt_module_page *node;
		rt_uint32_t npage = size / RT_MM_PAGE_SIZE;

		/* allocate pages from system heap */
		cp = rt_page_alloc(npage);
		if(!cp) return RT_NULL;

		/* allocate page list node from mpool */
		node = rt_mp_alloc(rt_current_module->mpool, RT_WAITING_FOREVER);
		node->ptr = cp;
		node->npage = npage;

		/* insert page list node to moudle's page list */
		rt_list_insert_after (&rt_current_module->page_list, &node->list);
	}	
		
	while(RT_TRUE)
	{
		b = *prev;
		if(!b)
		{
			if ((b = morepage(nunits)) == RT_NULL) return RT_NULL;
			else return rt_module_malloc(size); /* To be improved */
		}	
		
		if (b->size > nunits)
		{
			/* split memory */
			n = b + nunits;
			n->next = b->next;
			n->size = b->size - nunits;
			b->size = nunits;
			*prev = n;
			break;
		}

		if (b->size == nunits)
		{
			/* this node fit, remove this node */
			*prev = b->next;
			break;
		}

		prev = &(b->next);
	}

	return (void *)(b + 1);
}

/*
  rt_module_free - insert memory block in free list
*/
void rt_module_free(rt_module_t module, void *addr)
{
	struct rt_mem_head *b, *n;
	struct rt_mem_head **prev;
	
	RT_ASSERT(addr);
	RT_ASSERT((((rt_uint32_t)addr) & (sizeof(struct rt_mem_head) -1)) == 0);

	n = (struct rt_mem_head *)addr - 1;
	prev = (struct rt_mem_head **)&module->mem_list;

	while ((b = *prev) != RT_NULL)
	{		
		RT_ASSERT(b->size > 0);
		RT_ASSERT(b > n || b + b->size <= n);

		if (b + b->size == n)
		{
			if (b + (b->size += n->size) == b->next)
			{
				b->size += b->next->size;
				b->next  = b->next->next;
			}

			return;
		}

		if (b == n + n->size)
		{
			n->size = b->size + n->size;
			n->next = b->next;
			*prev = n;

			return;
		}
		if (b > n + n->size) break;

		prev = &(b->next);
	}

	n->next = b;
	*prev = n;

	/* free page, TODO */
}

/*
  rt_module_realloc - realloc memory block in free list
*/
void *rt_module_realloc(void *ptr, rt_size_t size)
{
	struct rt_mem_head *b, *p, *prev, *tmpp;
	rt_size_t nunits;

	if (!ptr) return rt_module_malloc(size);
	if (size == 0)
	{
		rt_module_free(rt_current_module, ptr);
		return RT_NULL;
	}

	nunits = (size + sizeof(struct rt_mem_head) - 1) / sizeof(struct rt_mem_head) + 1;
	b = (struct rt_mem_head *)ptr - 1;

	if (nunits <= b->size) 
	{   
		/* new size is smaller or equal then before */    
		if (nunits == b->size) return ptr;
		else 
		{
			p = b + nunits;
			p->size = b->size - nunits;
			b->size = nunits;
			rt_module_free(rt_current_module, (void *)(p + 1));
			return (void *)(b + 1);
		}
	}
	else 
	{      
		/* more space then required */
		prev = (struct rt_mem_head *)rt_current_module->mem_list;
		for (p = prev->next; p != (b->size + b) && p != RT_NULL; prev = p, p = p->next) break;

		/* available block after ap in freelist */ 
		if (p != RT_NULL && (p->size >= (nunits - (b->size))) &&  p == (b + b->size))  
		{
			/* perfect match */
			if (p->size == (nunits - (b->size)))  
			{
				b->size = nunits;
				prev->next = p->next;
			}
			else  /* more space then required, split block*/
			{
				/* pointer to old header */
				tmpp = p;  
				p = b + nunits;

				/* restoring old pointer */
				p->next = tmpp->next;
				
				/* new size for p */
				p->size = tmpp->size + b->size - nunits; 
				b->size = nunits;
				prev->next = p;
			}
			rt_current_module->mem_list = (void *)prev;
			return (void *) (b + 1);
		}
		else /* allocate new memory and copy old data */
		{
			if ((p = rt_module_malloc(size)) == RT_NULL) return RT_NULL;
			rt_memmove(p, (b+1), ((b->size) * sizeof(struct rt_mem_head)));
			rt_module_free(rt_current_module, (void *)(b + 1));
			return (void *) (p);
		}
	}
}

#endif
