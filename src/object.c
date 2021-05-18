/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-14     Bernard      the first version
 * 2006-04-21     Bernard      change the scheduler lock to interrupt lock
 * 2006-05-18     Bernard      fix the object init bug
 * 2006-08-03     Bernard      add hook support
 * 2007-01-28     Bernard      rename RT_OBJECT_Class_Static to RT_Object_Class_Static
 * 2010-10-26     yi.qiu       add module support in rt_object_allocate and rt_object_free
 * 2017-12-10     Bernard      Add object_info enum.
 * 2018-01-25     Bernard      Fix the object find issue when enable MODULE.
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif

/*
 * define object_info for the number of rt_object_container items.
 */
enum rt_object_info_type
{
    RT_Object_Info_Thread = 0,                         /**< The object is a thread. */
#ifdef RT_USING_SEMAPHORE
    RT_Object_Info_Semaphore,                          /**< The object is a semaphore. */
#endif
#ifdef RT_USING_MUTEX
    RT_Object_Info_Mutex,                              /**< The object is a mutex. */
#endif
#ifdef RT_USING_EVENT
    RT_Object_Info_Event,                              /**< The object is a event. */
#endif
#ifdef RT_USING_MAILBOX
    RT_Object_Info_MailBox,                            /**< The object is a mail box. */
#endif
#ifdef RT_USING_MESSAGEQUEUE
    RT_Object_Info_MessageQueue,                       /**< The object is a message queue. */
#endif
#ifdef RT_USING_MEMHEAP
    RT_Object_Info_MemHeap,                            /**< The object is a memory heap */
#endif
#ifdef RT_USING_MEMPOOL
    RT_Object_Info_MemPool,                            /**< The object is a memory pool. */
#endif
#ifdef RT_USING_DEVICE
    RT_Object_Info_Device,                             /**< The object is a device */
#endif
    RT_Object_Info_Timer,                              /**< The object is a timer. */
#ifdef RT_USING_MODULE
    RT_Object_Info_Module,                             /**< The object is a module. */
#endif
    RT_Object_Info_Unknown,                            /**< The object is unknown. */
};

#define _OBJ_CONTAINER_LIST_INIT(c)     \
    {&(rt_object_container[c].object_list), &(rt_object_container[c].object_list)}
static struct rt_object_information rt_object_container[RT_Object_Info_Unknown] =
{
    /* initialize object container - thread */
    {RT_Object_Class_Thread, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Thread), sizeof(struct rt_thread)},
#ifdef RT_USING_SEMAPHORE
    /* initialize object container - semaphore */
    {RT_Object_Class_Semaphore, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Semaphore), sizeof(struct rt_semaphore)},
#endif
#ifdef RT_USING_MUTEX
    /* initialize object container - mutex */
    {RT_Object_Class_Mutex, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Mutex), sizeof(struct rt_mutex)},
#endif
#ifdef RT_USING_EVENT
    /* initialize object container - event */
    {RT_Object_Class_Event, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Event), sizeof(struct rt_event)},
#endif
#ifdef RT_USING_MAILBOX
    /* initialize object container - mailbox */
    {RT_Object_Class_MailBox, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MailBox), sizeof(struct rt_mailbox)},
#endif
#ifdef RT_USING_MESSAGEQUEUE
    /* initialize object container - message queue */
    {RT_Object_Class_MessageQueue, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MessageQueue), sizeof(struct rt_messagequeue)},
#endif
#ifdef RT_USING_MEMHEAP
    /* initialize object container - memory heap */
    {RT_Object_Class_MemHeap, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemHeap), sizeof(struct rt_memheap)},
#endif
#ifdef RT_USING_MEMPOOL
    /* initialize object container - memory pool */
    {RT_Object_Class_MemPool, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemPool), sizeof(struct rt_mempool)},
#endif
#ifdef RT_USING_DEVICE
    /* initialize object container - device */
    {RT_Object_Class_Device, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Device), sizeof(struct rt_device)},
#endif
    /* initialize object container - timer */
    {RT_Object_Class_Timer, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Timer), sizeof(struct rt_timer)},
#ifdef RT_USING_MODULE
    /* initialize object container - module */
    {RT_Object_Class_Module, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Module), sizeof(struct rt_dlmodule)},
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

/**@{*/

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

/**@}*/
#endif

/**
 * @addtogroup KernelObject
 */

/**@{*/

/**
 * This function will return the specified type of object information.
 *
 * @param type the type of object, which can be
 *             RT_Object_Class_Thread/Semaphore/Mutex... etc
 *
 * @return the object type information or RT_NULL
 */
struct rt_object_information *
rt_object_get_information(enum rt_object_class_type type)
{
    int index;

    for (index = 0; index < RT_Object_Info_Unknown; index ++)
        if (rt_object_container[index].type == type) return &rt_object_container[index];

    return RT_NULL;
}
RTM_EXPORT(rt_object_get_information);

/**
 * This function will return the length of object list in object container.
 *
 * @param type the type of object, which can be
 *             RT_Object_Class_Thread/Semaphore/Mutex... etc
 * @return the length of object list
 */
int rt_object_get_length(enum rt_object_class_type type)
{
    int count = 0;
    rt_ubase_t level;
    struct rt_list_node *node = RT_NULL;
    struct rt_object_information *information = RT_NULL;

    information = rt_object_get_information((enum rt_object_class_type)type);
    if (information == RT_NULL) return 0;

    level = rt_hw_interrupt_disable();
    /* get the count of objects */
    rt_list_for_each(node, &(information->object_list))
    {
        count ++;
    }
    rt_hw_interrupt_enable(level);

    return count;
}
RTM_EXPORT(rt_object_get_length);

/**
 * This function will copy the object pointer of the specified type,
 * with the maximum size specified by maxlen.
 *
 * @param type the type of object, which can be
 *             RT_Object_Class_Thread/Semaphore/Mutex... etc
 * @param pointers the pointers will be saved to
 * @param maxlen the maximum number of pointers can be saved
 *
 * @return the copied number of object pointers
 */
int rt_object_get_pointers(enum rt_object_class_type type, rt_object_t *pointers, int maxlen)
{
    int index = 0;
    rt_ubase_t level;

    struct rt_object *object;
    struct rt_list_node *node = RT_NULL;
    struct rt_object_information *information = RT_NULL;

    if (maxlen <= 0) return 0;

    information = rt_object_get_information((enum rt_object_class_type)type);
    if (information == RT_NULL) return 0;

    level = rt_hw_interrupt_disable();
    /* retrieve pointer of object */
    rt_list_for_each(node, &(information->object_list))
    {
        object = rt_list_entry(node, struct rt_object, list);

        pointers[index] = object;
        index ++;

        if (index >= maxlen) break;
    }
    rt_hw_interrupt_enable(level);

    return index;
}
RTM_EXPORT(rt_object_get_pointers);

/**
 * This function will initialize an object and add it to object system
 * management.
 *
 * @param object the specified object to be initialized.
 * @param type the object type.
 * @param name the object name. In system, the object's name must be unique.
 */
void rt_object_init(struct rt_object         *object,
                    enum rt_object_class_type type,
                    const char               *name)
{
    register rt_base_t temp;
    struct rt_list_node *node = RT_NULL;
    struct rt_object_information *information;
#ifdef RT_USING_MODULE
    struct rt_dlmodule *module = dlmodule_self();
#endif

    /* get object information */
    information = rt_object_get_information(type);
    RT_ASSERT(information != RT_NULL);

    /* check object type to avoid re-initialization */

    /* enter critical */
    rt_enter_critical();
    /* try to find object */
    for (node  = information->object_list.next;
            node != &(information->object_list);
            node  = node->next)
    {
        struct rt_object *obj;

        obj = rt_list_entry(node, struct rt_object, list);
        if (obj) /* skip warning when disable debug */
        {
            RT_ASSERT(obj != object);
        }
    }
    /* leave critical */
    rt_exit_critical();

    /* initialize object's parameters */
    /* set object type to static */
    object->type = type | RT_Object_Class_Static;
    /* copy name */
    rt_strncpy(object->name, name, RT_NAME_MAX);

    RT_OBJECT_HOOK_CALL(rt_object_attach_hook, (object));

    /* lock interrupt */
    temp = rt_hw_interrupt_disable();

#ifdef RT_USING_MODULE
    if (module)
    {
        rt_list_insert_after(&(module->object_list), &(object->list));
        object->module_id = (void *)module;
    }
    else
#endif
    {
        /* insert object into information object list */
        rt_list_insert_after(&(information->object_list), &(object->list));
    }

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

    /* reset object type */
    object->type = 0;

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
#ifdef RT_USING_MODULE
    struct rt_dlmodule *module = dlmodule_self();
#endif

    RT_DEBUG_NOT_IN_INTERRUPT;

    /* get object information */
    information = rt_object_get_information(type);
    RT_ASSERT(information != RT_NULL);

    object = (struct rt_object *)RT_KERNEL_MALLOC(information->object_size);
    if (object == RT_NULL)
    {
        /* no memory can be allocated */
        return RT_NULL;
    }

    /* clean memory data of object */
    rt_memset(object, 0x0, information->object_size);

    /* initialize object's parameters */

    /* set object type */
    object->type = type;

    /* set object flag */
    object->flag = 0;

    /* copy name */
    rt_strncpy(object->name, name, RT_NAME_MAX);

    RT_OBJECT_HOOK_CALL(rt_object_attach_hook, (object));

    /* lock interrupt */
    temp = rt_hw_interrupt_disable();

#ifdef RT_USING_MODULE
    if (module)
    {
        rt_list_insert_after(&(module->object_list), &(object->list));
        object->module_id = (void *)module;
    }
    else
#endif
    {
        /* insert object into information object list */
        rt_list_insert_after(&(information->object_list), &(object->list));
    }

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

    /* reset object type */
    object->type = RT_Object_Class_Null;

    /* lock interrupt */
    temp = rt_hw_interrupt_disable();

    /* remove from old list */
    rt_list_remove(&(object->list));

    /* unlock interrupt */
    rt_hw_interrupt_enable(temp);

    /* free the memory of object */
    RT_KERNEL_FREE(object);
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
 * This function will return the type of object without
 * RT_Object_Class_Static flag.
 *
 * @param object the specified object to be get type.
 *
 * @return the type of object.
 */
rt_uint8_t rt_object_get_type(rt_object_t object)
{
    /* object check */
    RT_ASSERT(object != RT_NULL);

    return object->type & ~RT_Object_Class_Static;
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
    struct rt_object *object = RT_NULL;
    struct rt_list_node *node = RT_NULL;
    struct rt_object_information *information = RT_NULL;

    information = rt_object_get_information((enum rt_object_class_type)type);

    /* parameter check */
    if ((name == RT_NULL) || (information == RT_NULL)) return RT_NULL;

    /* which is invoke in interrupt status */
    RT_DEBUG_NOT_IN_INTERRUPT;

    /* enter critical */
    rt_enter_critical();

    /* try to find object */
    rt_list_for_each(node, &(information->object_list))
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

/**@}*/
