/*
 * File      : object.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
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
 * 2010-10-26     yi.qiu       add module support in rt_object_allocate and rt_object_free
 */

#include <rtthread.h>
#include <rthw.h>

#define _OBJ_CONTAINER_LIST_INIT(c) 	\
	{&(rt_object_container[c].object_list), &(rt_object_container[c].object_list)}
struct rt_object_information rt_object_container[RT_Object_Class_Unknown] =
{
	/* initialize object container - thread */
	{RT_Object_Class_Thread, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Thread), sizeof(struct rt_thread)},
#ifdef RT_USING_SEMAPHORE
	/* initialize object container - semaphore */
	{RT_Object_Class_Semaphore, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Semaphore), sizeof(struct rt_semaphore)},
#endif
#ifdef RT_USING_MUTEX
	/* initialize object container - mutex */
	{RT_Object_Class_Mutex, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Mutex), sizeof(struct rt_mutex)},
#endif
#ifdef RT_USING_EVENT
	/* initialize object container - event */
	{RT_Object_Class_Event, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Event), sizeof(struct rt_event)},
#endif
#ifdef RT_USING_MAILBOX
	/* initialize object container - mailbox */
	{RT_Object_Class_MailBox, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_MailBox), sizeof(struct rt_mailbox)},
#endif
#ifdef RT_USING_MESSAGEQUEUE
	/* initialize object container - message queue */
	{RT_Object_Class_MessageQueue, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_MessageQueue), sizeof(struct rt_messagequeue)},
#endif
#ifdef RT_USING_MEMHEAP
	/* initialize object container - memory heap */
	{RT_Object_Class_MemHeap, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_MemHeap), sizeof(struct rt_memheap)},
#endif
#ifdef RT_USING_MEMPOOL
	/* initialize object container - memory pool */
	{RT_Object_Class_MemPool, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_MemPool), sizeof(struct rt_mempool)},
#endif
#ifdef RT_USING_DEVICE
	/* initialize object container - device */
	{RT_Object_Class_Device, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Device), sizeof(struct rt_device)},
#endif
	/* initialize object container - timer */
	{RT_Object_Class_Timer, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Timer), sizeof(struct rt_timer)},
#ifdef RT_USING_MODULE
	/* initialize object container - module */
	{RT_Object_Class_Module, _OBJ_CONTAINER_LIST_INIT(RT_Object_Class_Module), sizeof(struct rt_module)},
#endif
};

#ifdef RT_USING_HOOK
static void (*rt_object_attach_hook)(struct rt_object *object);
static void (*rt_object_detach_hook)(struct rt_object *object);
void (*rt_object_trytake_hook)(struct rt_object *object);
void (*rt_object_take_hook)(struct rt_object *object);
void (*rt_object_put_hook)(struct rt_object *object);

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
void rt_object_attach_sethook(void (*hook)(struct rt_object *object))
{
	rt_object_attach_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when object
 * detaches from kernel object system.
 *
 * @param hook the hook function
 */
void rt_object_detach_sethook(void (*hook)(struct rt_object *object))
{
	rt_object_detach_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when object
 * is taken from kernel object system.
 *
 * The object is taken means:
 * semaphore - semaphore is taken by thread
 * mutex - mutex is taken by thread
 * event - event is received by thread
 * mailbox - mail is received by thread
 * message queue - message is received by thread
 *
 * @param hook the hook function
 */
void rt_object_trytake_sethook(void (*hook)(struct rt_object *object))
{
	rt_object_trytake_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when object
 * have been taken from kernel object system.
 *
 * The object have been taken means:
 * semaphore - semaphore have been taken by thread
 * mutex - mutex have been taken by thread
 * event - event have been received by thread
 * mailbox - mail have been received by thread
 * message queue - message have been received by thread
 * timer - timer is started
 *
 * @param hook the hook function
 */
void rt_object_take_sethook(void (*hook)(struct rt_object *object))
{
	rt_object_take_hook = hook;
}

/**
 * This function will set a hook function, which will be invoked when object
 * is put to kernel object system.
 *
 * @param hook the hook function
 */
void rt_object_put_sethook(void (*hook)(struct rt_object *object))
{
	rt_object_put_hook = hook;
}

/*@}*/
#endif

/**
 * @ingroup SystemInit
 *
 * This function will initialize system object management.
 *
 * @deprecated since 0.3.0, this function does not need to be invoked
 * in the system initialization.
 */
void rt_system_object_init(void)
{
}

/**
 * @addtogroup KernelObject
 */

/*@{*/

/**
 * This function will return the specified type of object information.
 * 
 * @param type the type of object
 * @return the object type information or RT_NULL
 */
struct rt_object_information *rt_object_get_information(enum rt_object_class_type type)
{
	return &rt_object_container[type];
}

/**
 * This function will initialize an object and add it to object system management.
 *
 * @param object the specified object to be initialized.
 * @param type the object type.
 * @param name the object name. In system, the object's name must be unique.
 */
void rt_object_init(struct rt_object *object, enum rt_object_class_type type, const char *name)
{
	register rt_base_t temp;
	struct rt_object_information *information;

#ifdef RT_USING_MODULE
	/* get module object information */
	information = (rt_module_self() != RT_NULL) ? 
		&rt_module_self()->module_object[type] : &rt_object_container[type];
#else
	/* get object information */
	information = &rt_object_container[type];
#endif

	/* initialize object's parameters */

	/* set object type to static */
	object->type = type | RT_Object_Class_Static;

	/* copy name */
	rt_strncpy(object->name, name, RT_NAME_MAX);

	RT_OBJECT_HOOK_CALL(rt_object_attach_hook, (object));

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

	RT_OBJECT_HOOK_CALL(rt_object_detach_hook, (object));

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
rt_object_t rt_object_allocate(enum rt_object_class_type type, const char *name)
{
	struct rt_object *object;
	register rt_base_t temp;
	struct rt_object_information *information;

	RT_DEBUG_NOT_IN_INTERRUPT;

#ifdef RT_USING_MODULE
	/* get module object information, module object should be managed by kernel object container */
	information = (rt_module_self() != RT_NULL && (type != RT_Object_Class_Module)) ? 
		&rt_module_self()->module_object[type] : &rt_object_container[type];
#else
	/* get object information */
	information = &rt_object_container[type];
#endif

	object = (struct rt_object *)rt_malloc(information->object_size);
	if (object == RT_NULL)
	{
		/* no memory can be allocated */
		return RT_NULL;
	}
	
	/* initialize object's parameters */

	/* set object type */
	object->type = type;

	/* set object flag */
	object->flag = 0;

#ifdef RT_USING_MODULE
	if (rt_module_self() != RT_NULL)
	{
		object->flag |= RT_OBJECT_FLAG_MODULE;
	}
	object->module_id = (void *)rt_module_self();
#endif

	/* copy name */
	rt_strncpy(object->name, name, RT_NAME_MAX);

	RT_OBJECT_HOOK_CALL(rt_object_attach_hook, (object));

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

	RT_OBJECT_HOOK_CALL(rt_object_detach_hook, (object));

	/* lock interrupt */
	temp = rt_hw_interrupt_disable();

	/* remove from old list */
	rt_list_remove(&(object->list));

	/* unlock interrupt */
	rt_hw_interrupt_enable(temp);

#if defined(RT_USING_MODULE) && defined(RT_USING_SLAB)
	if (object->flag & RT_OBJECT_FLAG_MODULE) 
		rt_module_free((rt_module_t)object->module_id, object);
	else
#endif

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
 * @return RT_TRUE if a system object, RT_FALSE for others.
 */
rt_bool_t rt_object_is_systemobject(rt_object_t object)
{
	/* object check */
	RT_ASSERT(object != RT_NULL);

	if (object->type & RT_Object_Class_Static)
		return RT_TRUE;

	return RT_FALSE;
}

/**
 * This function will find specified name object from object
 * container.
 *
 * @param name the specified name of object.
 * @param type the type of object
 *
 * @return the found object or RT_NULL if there is no this object
 * in object container.
 *
 * @note this function shall not be invoked in interrupt status.
 */
rt_object_t rt_object_find(const char *name, rt_uint8_t type)
{
	struct rt_object *object;
	struct rt_list_node *node;
	struct rt_object_information *information;
	extern volatile rt_uint8_t rt_interrupt_nest;

	/* parameter check */
	if ((name == RT_NULL) || (type > RT_Object_Class_Unknown))
		return RT_NULL;

	/* which is invoke in interrupt status */
	if (rt_interrupt_nest != 0)
		RT_ASSERT(0);

	/* enter critical */
	rt_enter_critical();

	/* try to find object */
	information = &rt_object_container[type];
	for (node = information->object_list.next; node != &(information->object_list); node = node->next)
	{
		object = rt_list_entry(node, struct rt_object, list);
		if (rt_strncmp(object->name, name, RT_NAME_MAX) == 0)
		{
			/* leave critical */
			rt_exit_critical();

			return object;
		}
	}

	/* leave critical */
	rt_exit_critical();

	return RT_NULL;
}

/*@}*/
