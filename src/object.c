/*
 * File      : object.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-14     Bernard      the first version
 * 2006-04-21     Bernard      change the scheduler lock to interrupt lock
 * 2006-05-18     Bernard      fix the object init bug
 * 2006-08-03     Bernard      add hook support
 * 2007-01-28     Bernard      rename RT_OBJECT_Class_Static to RT_Object_Class_Static
 */

#include <rtthread.h>
#include <rthw.h>

#include "kservice.h"

#ifdef RT_USING_MODULE
extern struct rt_module* rt_current_module;
#endif

#define _OBJ_CONTAINER_LIST_INIT(c) 	\
	{&(rt_object_container[c].object_list), &(rt_object_container[c].object_list)}
struct rt_object_information rt_object_container[RT_Object_Class_Unknown] =
{
	/* init object container - thread */
	{RT_Object_Class_Thread, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Thread), sizeof(struct rt_thread)},
#ifdef RT_USING_SEMAPHORE
	/* init object container - semaphore */
	{RT_Object_Class_Semaphore, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Semaphore), sizeof(struct rt_semaphore)},
#endif
#ifdef RT_USING_MUTEX
	/* init object container - mutex */
	{RT_Object_Class_Mutex, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Mutex), sizeof(struct rt_mutex)},
#endif
#ifdef RT_USING_EVENT
	/* init object container - event */
	{RT_Object_Class_Event, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Event), sizeof(struct rt_event)},
#endif
#ifdef RT_USING_MAILBOX
	/* init object container - mailbox */
	{RT_Object_Class_MailBox, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_MailBox), sizeof(struct rt_mailbox)},
#endif
#ifdef RT_USING_MESSAGEQUEUE
	/* init object container - message queue */
	{RT_Object_Class_MessageQueue, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_MessageQueue), sizeof(struct rt_messagequeue)},
#endif
#ifdef RT_USING_MEMPOOL
	/* init object container - memory pool */
	{RT_Object_Class_MemPool, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_MemPool), sizeof(struct rt_mempool)},
#endif
#ifdef RT_USING_DEVICE
	/* init object container - device */
	{RT_Object_Class_Device, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Device), sizeof(struct rt_device)},
#endif
	/* init object container - timer */
	{RT_Object_Class_Timer, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Timer), sizeof(struct rt_timer)},
#ifdef RT_USING_MODULE
	/* init object container - module */
	{RT_Object_Class_Module, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Module), sizeof(struct rt_module)},
#endif
};

#ifdef RT_USING_HOOK
static void (*rt_object_attach_hook)(struct rt_object* object);
static void (*rt_object_detach_hook)(struct rt_object* object);
void (*rt_object_trytake_hook)(struct rt_object* object);
void (*rt_object_take_hook)(struct rt_object* object);
void (*rt_object_put_hook)(struct rt_object* object);

/**
 * @addtogroup Hook
 */
/*@{*/

/**
 * This function will set a hook function, which will be invoked when object
 * attaches to kernel object system.
 *
 * @param hook the hook function
 */
void rt_object_attach_sethook(void (*hook)(struct rt_object* object))
{
	rt_object_attach_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when object
 * detaches from kernel object system.
 *
 * @param hook the hook function
 */
void rt_object_detach_sethook(void (*hook)(struct rt_object* object))
{
	rt_object_detach_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when object
 * is taken from kernel object system.
 *
 * The object is taken means that
 * semaphore - semaphore is taken by thread
 * mutex - mutex is taken by thread
 * event - event is received by thread
 * mailbox - mail is received by thread
 * message queue - message is received by thread
 *
 * @param hook the hook function
 */
void rt_object_trytake_sethook(void (*hook)(struct rt_object* object))
{
	rt_object_trytake_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when object
 * have been taken from kernel object system.
 *
 * The object have been taken means that
 * semaphore - semaphore have been taken by thread
 * mutex - mutex have been taken by thread
 * event - event have been received by thread
 * mailbox - mail have been received by thread
 * message queue - message have been received by thread
 * timer - timer is started
 *
 * @param hook the hook function
 */
void rt_object_take_sethook(void (*hook)(struct rt_object* object))
{
	rt_object_take_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when object
 * is put to kernel object system.
 *
 * @param hook the hook function
 */
void rt_object_put_sethook(void (*hook)(struct rt_object* object))
{
	rt_object_put_hook = hook;
}

/*@}*/
#endif

/**
 * @ingroup SystemInit
 *
 * This function will initialize system object management
 *
 */
void rt_system_object_init(void)
{
}

/**
 * @addtogroup KernelObject
 */
/*@{*/

/**
 * This function will init an object and add it to object system management.
 *
 * @param object the specified object to be initialized.
 * @param type the object type.
 * @param name the object name. In system, the object's name must
 * be unique.
 */
void rt_object_init(struct rt_object* object, enum rt_object_class_type type, const char* name)
{
	register rt_base_t temp;
	struct rt_object_information* information;

#ifdef RT_USING_MODULE
	/* get module object information */
	information = (rt_current_module != RT_NULL) ? 
		&rt_current_module->module_object[type] : &rt_object_container[type];
#else
	/* get object information */
	information = &rt_object_container[type];
#endif

	/* init object's parameters */

	/* set object type to static */
	object->type = type | RT_Object_Class_Static;

	/* copy name */
	for (temp = 0; temp < RT_NAME_MAX; temp ++)
	{
		object->name[temp] = name[temp];
	}

#ifdef RT_USING_HOOK
	if (rt_object_attach_hook != RT_NULL)
	{
		rt_object_attach_hook(object);
	}
#endif

	/* lock interrupt */
	temp = rt_hw_interrupt_disable();

	/* insert object into information object list */
	rt_list_insert_after(&(information->object_list), &(object->list));

	/* unlock interrupt */
	rt_hw_interrupt_enable(temp);
}

/**
 * This function will detach a static object from object system,
 * and the memory of static object is not freed.
 *
 * @param object the specified object to be detached.
 */
void rt_object_detach(rt_object_t object)
{
	register rt_base_t temp;

	/* object check */
	RT_ASSERT(object != RT_NULL);

#ifdef RT_USING_HOOK
	if (rt_object_detach_hook != RT_NULL) rt_object_detach_hook(object);
#endif

	/* lock interrupt */
	temp = rt_hw_interrupt_disable();

	/* remove from old list */
	rt_list_remove(&(object->list));

	/* unlock interrupt */
	rt_hw_interrupt_enable(temp);
}

#ifdef RT_USING_HEAP
/**
 * This function will allocate an object from object system
 *
 * @param type the type of object
 * @param name the object name. In system, the object's name must be unique.
 *
 * @return object
 */
rt_object_t rt_object_allocate(enum rt_object_class_type type, const char* name)
{
	struct rt_object* object;
	register rt_base_t temp;
	struct rt_object_information* information;

#ifdef RT_USING_MODULE
	/* get module object information */
	information = (rt_current_module != RT_NULL) ? 
		&rt_current_module->module_object[type] : &rt_object_container[type];
#else
	/* get object information */
	information = &rt_object_container[type];
#endif

	object = (struct rt_object*)rt_malloc(information->object_size);
	if (object == RT_NULL)
	{
		/* no memory can be allocated */
		return RT_NULL;
	}

	/* init object's parameters */

	/* set object type */
	object->type = type;

	/* copy name */
	for (temp = 0; temp < RT_NAME_MAX; temp ++)
	{
		object->name[temp] = name[temp];
	}

#ifdef RT_USING_HOOK
	if (rt_object_attach_hook != RT_NULL) rt_object_attach_hook(object);
#endif

	/* lock interrupt */
	temp = rt_hw_interrupt_disable();

	/* insert object into information object list */
	rt_list_insert_after(&(information->object_list), &(object->list));

	/* unlock interrupt */
	rt_hw_interrupt_enable(temp);

	/* return object */
	return object;
}

/**
 * This function will delete an object and release object memory.
 *
 * @param object the specified object to be deleted.
 */
void rt_object_delete(rt_object_t object)
{
	register rt_base_t temp;

	/* object check */
	RT_ASSERT(object != RT_NULL);
	RT_ASSERT(!(object->type & RT_Object_Class_Static));

#ifdef RT_USING_HOOK
	if (rt_object_detach_hook != RT_NULL) rt_object_detach_hook(object);
#endif

	/* lock interrupt */
	temp = rt_hw_interrupt_disable();

	/* remove from old list */
	rt_list_remove(&(object->list));

	/* unlock interrupt */
	rt_hw_interrupt_enable(temp);

	/* free the memory of object */
	rt_free(object);
}
#endif

/**
 * This function will judge the object is system object or not.
 * Normally, the system object is a static object and the type
 * of object set to RT_Object_Class_Static.
 *
 * @param object the specified object to be judged.
 *
 * @return RT_EOK if a system object, RT_ERROR for others.
 */
rt_err_t rt_object_is_systemobject(rt_object_t object)
{
	/* object check */
	RT_ASSERT(object != RT_NULL);

	if (object->type & RT_Object_Class_Static) return RT_EOK;

	return -RT_ERROR;
}

/*@}*/
