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
 * 2022-01-07     Gabriel      Moving __on_rt_xxxxx_hook to object.c
 * 2023-09-15     xqyjlj       perf rt_hw_interrupt_disable/enable
 * 2023-11-17     xqyjlj       add process group and session support
 */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_MODULE
#include <dlmodule.h>
#endif /* RT_USING_MODULE */

#ifdef RT_USING_SMART
#include <lwp.h>
#endif

struct rt_custom_object
{
    struct rt_object parent;
    rt_err_t (*destroy)(void *);
    void *data;
};

/*
 * define object_info for the number of _object_container items.
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
#ifdef RT_USING_HEAP
    RT_Object_Info_Memory,                             /**< The object is a memory. */
#endif
#ifdef RT_USING_SMART
    RT_Object_Info_Channel,                            /**< The object is a IPC channel */
    RT_Object_Info_ProcessGroup,                       /**< The object is a process group */
    RT_Object_Info_Session,                            /**< The object is a session */
#endif
#ifdef RT_USING_HEAP
    RT_Object_Info_Custom,                             /**< The object is a custom object */
#endif
    RT_Object_Info_Unknown,                            /**< The object is unknown. */
};

#define _OBJ_CONTAINER_LIST_INIT(c)     \
    {&(_object_container[c].object_list), &(_object_container[c].object_list)}

static struct rt_object_information _object_container[RT_Object_Info_Unknown] =
{
    /* initialize object container - thread */
    {RT_Object_Class_Thread, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Thread), sizeof(struct rt_thread), RT_SPINLOCK_INIT},
#ifdef RT_USING_SEMAPHORE
    /* initialize object container - semaphore */
    {RT_Object_Class_Semaphore, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Semaphore), sizeof(struct rt_semaphore), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_MUTEX
    /* initialize object container - mutex */
    {RT_Object_Class_Mutex, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Mutex), sizeof(struct rt_mutex), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_EVENT
    /* initialize object container - event */
    {RT_Object_Class_Event, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Event), sizeof(struct rt_event), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_MAILBOX
    /* initialize object container - mailbox */
    {RT_Object_Class_MailBox, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MailBox), sizeof(struct rt_mailbox), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_MESSAGEQUEUE
    /* initialize object container - message queue */
    {RT_Object_Class_MessageQueue, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MessageQueue), sizeof(struct rt_messagequeue), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_MEMHEAP
    /* initialize object container - memory heap */
    {RT_Object_Class_MemHeap, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemHeap), sizeof(struct rt_memheap), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_MEMPOOL
    /* initialize object container - memory pool */
    {RT_Object_Class_MemPool, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemPool), sizeof(struct rt_mempool), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_DEVICE
    /* initialize object container - device */
    {RT_Object_Class_Device, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Device), sizeof(struct rt_device), RT_SPINLOCK_INIT},
#endif
    /* initialize object container - timer */
    {RT_Object_Class_Timer, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Timer), sizeof(struct rt_timer), RT_SPINLOCK_INIT},
#ifdef RT_USING_MODULE
    /* initialize object container - module */
    {RT_Object_Class_Module, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Module), sizeof(struct rt_dlmodule), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_HEAP
    /* initialize object container - small memory */
    {RT_Object_Class_Memory, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Memory), sizeof(struct rt_memory), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_SMART
    /* initialize object container - module */
    {RT_Object_Class_Channel, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Channel), sizeof(struct rt_channel), RT_SPINLOCK_INIT},
    {RT_Object_Class_ProcessGroup, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_ProcessGroup), sizeof(struct rt_processgroup), RT_SPINLOCK_INIT},
    {RT_Object_Class_Session, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Session), sizeof(struct rt_session), RT_SPINLOCK_INIT},
#endif
#ifdef RT_USING_HEAP
    {RT_Object_Class_Custom, _OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Custom), sizeof(struct rt_custom_object), RT_SPINLOCK_INIT},
#endif
};

#if defined(RT_USING_HOOK) && defined(RT_HOOK_USING_FUNC_PTR)
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
 * @brief This function will set a hook function, which will be invoked when object
 *        attaches to kernel object system.
 *
 * @param hook is the hook function.
 */
void rt_object_attach_sethook(void (*hook)(struct rt_object *object))
{
    rt_object_attach_hook = hook;
}

/**
 * @brief This function will set a hook function, which will be invoked when object
 *        detaches from kernel object system.
 *
 * @param hook is the hook function
 */
void rt_object_detach_sethook(void (*hook)(struct rt_object *object))
{
    rt_object_detach_hook = hook;
}

/**
 * @brief This function will set a hook function, which will be invoked when object
 *        is taken from kernel object system.
 *
 *        The object is taken means:
 *            semaphore - semaphore is taken by thread
 *            mutex - mutex is taken by thread
 *            event - event is received by thread
 *            mailbox - mail is received by thread
 *            message queue - message is received by thread
 *
 * @param hook is the hook function.
 */
void rt_object_trytake_sethook(void (*hook)(struct rt_object *object))
{
    rt_object_trytake_hook = hook;
}

/**
 * @brief This function will set a hook function, which will be invoked when object
 *        have been taken from kernel object system.
 *
 *        The object have been taken means:
 *            semaphore - semaphore have been taken by thread
 *            mutex - mutex have been taken by thread
 *            event - event have been received by thread
 *            mailbox - mail have been received by thread
 *            message queue - message have been received by thread
 *            timer - timer is started
 *
 * @param hook the hook function.
 */
void rt_object_take_sethook(void (*hook)(struct rt_object *object))
{
    rt_object_take_hook = hook;
}

/**
 * @brief This function will set a hook function, which will be invoked when object
 *        is put to kernel object system.
 *
 * @param hook is the hook function
 */
void rt_object_put_sethook(void (*hook)(struct rt_object *object))
{
    rt_object_put_hook = hook;
}

/**@}*/
#endif /* RT_USING_HOOK */

/**
 * @addtogroup KernelObject
 */

/**@{*/

/**
 * @brief This function will return the specified type of object information.
 *
 * @param type is the type of object, which can be
 *             RT_Object_Class_Thread/Semaphore/Mutex... etc
 *
 * @return the object type information or RT_NULL
 */
struct rt_object_information *
rt_object_get_information(enum rt_object_class_type type)
{
    int index;

    type = (enum rt_object_class_type)(type & ~RT_Object_Class_Static);

    for (index = 0; index < RT_Object_Info_Unknown; index ++)
        if (_object_container[index].type == type) return &_object_container[index];

    return RT_NULL;
}
RTM_EXPORT(rt_object_get_information);

/**
 * @brief This function will return the length of object list in object container.
 *
 * @param type is the type of object, which can be
 *             RT_Object_Class_Thread/Semaphore/Mutex... etc
 *
 * @return the length of object list
 */
int rt_object_get_length(enum rt_object_class_type type)
{
    int count = 0;
    rt_base_t level;
    struct rt_list_node *node = RT_NULL;
    struct rt_object_information *information = RT_NULL;

    information = rt_object_get_information((enum rt_object_class_type)type);
    if (information == RT_NULL) return 0;

    level = rt_spin_lock_irqsave(&(information->spinlock));
    rt_list_for_each(node, &(information->object_list))
    {
        count ++;
    }
    rt_spin_unlock_irqrestore(&(information->spinlock), level);

    return count;
}
RTM_EXPORT(rt_object_get_length);

/**
 * @brief This function will copy the object pointer of the specified type,
 *        with the maximum size specified by maxlen.
 *
 * @param type is the type of object, which can be
 *             RT_Object_Class_Thread/Semaphore/Mutex... etc
 *
 * @param pointers is the pointer will be saved to.
 *
 * @param maxlen is the maximum number of pointers can be saved.
 *
 * @return the copied number of object pointers.
 */
int rt_object_get_pointers(enum rt_object_class_type type, rt_object_t *pointers, int maxlen)
{
    int index = 0;
    rt_base_t level;

    struct rt_object *object;
    struct rt_list_node *node = RT_NULL;
    struct rt_object_information *information = RT_NULL;

    if (maxlen <= 0) return 0;

    information = rt_object_get_information(type);
    if (information == RT_NULL) return 0;

    level = rt_spin_lock_irqsave(&(information->spinlock));
    /* retrieve pointer of object */
    rt_list_for_each(node, &(information->object_list))
    {
        object = rt_list_entry(node, struct rt_object, list);

        pointers[index] = object;
        index ++;

        if (index >= maxlen) break;
    }
    rt_spin_unlock_irqrestore(&(information->spinlock), level);

    return index;
}
RTM_EXPORT(rt_object_get_pointers);

/**
 * @brief This function will initialize an object and add it to object system
 *        management.
 *
 * @param object is the specified object to be initialized.
 *
 * @param type is the object type.
 *
 * @param name is the object name. In system, the object's name must be unique.
 */
void rt_object_init(struct rt_object         *object,
                    enum rt_object_class_type type,
                    const char               *name)
{
    rt_base_t level;
#ifdef RT_DEBUGING_ASSERT
    struct rt_list_node *node = RT_NULL;
#endif /* RT_DEBUGING_ASSERT */
    struct rt_object_information *information;
#ifdef RT_USING_MODULE
    struct rt_dlmodule *module = dlmodule_self();
#endif /* RT_USING_MODULE */

    /* get object information */
    information = rt_object_get_information(type);
    RT_ASSERT(information != RT_NULL);

#ifdef RT_DEBUGING_ASSERT
    /* check object type to avoid re-initialization */

    /* enter critical */
    level = rt_spin_lock_irqsave(&(information->spinlock));
    /* try to find object */
    for (node  = information->object_list.next;
            node != &(information->object_list);
            node  = node->next)
    {
        struct rt_object *obj;

        obj = rt_list_entry(node, struct rt_object, list);
        RT_ASSERT(obj != object);
    }
    /* leave critical */
    rt_spin_unlock_irqrestore(&(information->spinlock), level);
#endif /* RT_DEBUGING_ASSERT */

    /* initialize object's parameters */
    /* set object type to static */
    object->type = type | RT_Object_Class_Static;
#if RT_NAME_MAX > 0
    rt_strncpy(object->name, name, RT_NAME_MAX);  /* copy name */
#else
    object->name = name;
#endif /* RT_NAME_MAX > 0 */

    RT_OBJECT_HOOK_CALL(rt_object_attach_hook, (object));

    level = rt_spin_lock_irqsave(&(information->spinlock));

#ifdef RT_USING_MODULE
    if (module)
    {
        rt_list_insert_after(&(module->object_list), &(object->list));
        object->module_id = (void *)module;
    }
    else
#endif /* RT_USING_MODULE */
    {
        /* insert object into information object list */
        rt_list_insert_after(&(information->object_list), &(object->list));
    }
    rt_spin_unlock_irqrestore(&(information->spinlock), level);
}

/**
 * @brief This function will detach a static object from object system,
 *        and the memory of static object is not freed.
 *
 * @param object the specified object to be detached.
 */
void rt_object_detach(rt_object_t object)
{
    rt_base_t level;
    struct rt_object_information *information;

    /* object check */
    RT_ASSERT(object != RT_NULL);

    RT_OBJECT_HOOK_CALL(rt_object_detach_hook, (object));

    information = rt_object_get_information((enum rt_object_class_type)object->type);
    RT_ASSERT(information != RT_NULL);

    level = rt_spin_lock_irqsave(&(information->spinlock));
    /* remove from old list */
    rt_list_remove(&(object->list));
    rt_spin_unlock_irqrestore(&(information->spinlock), level);

    object->type = RT_Object_Class_Null;
}

#ifdef RT_USING_HEAP
/**
 * @brief This function will allocate an object from object system.
 *
 * @param type is the type of object.
 *
 * @param name is the object name. In system, the object's name must be unique.
 *
 * @return object
 */
rt_object_t rt_object_allocate(enum rt_object_class_type type, const char *name)
{
    struct rt_object *object;
    rt_base_t level;
    struct rt_object_information *information;
#ifdef RT_USING_MODULE
    struct rt_dlmodule *module = dlmodule_self();
#endif /* RT_USING_MODULE */

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

#if RT_NAME_MAX > 0
    rt_strncpy(object->name, name, RT_NAME_MAX - 1); /* copy name */
#else
    object->name = name;
#endif /* RT_NAME_MAX > 0 */

    RT_OBJECT_HOOK_CALL(rt_object_attach_hook, (object));

    level = rt_spin_lock_irqsave(&(information->spinlock));

#ifdef RT_USING_MODULE
    if (module)
    {
        rt_list_insert_after(&(module->object_list), &(object->list));
        object->module_id = (void *)module;
    }
    else
#endif /* RT_USING_MODULE */
    {
        /* insert object into information object list */
        rt_list_insert_after(&(information->object_list), &(object->list));
    }
    rt_spin_unlock_irqrestore(&(information->spinlock), level);

    return object;
}

/**
 * @brief This function will delete an object and release object memory.
 *
 * @param object is the specified object to be deleted.
 */
void rt_object_delete(rt_object_t object)
{
    rt_base_t level;
    struct rt_object_information *information;

    /* object check */
    RT_ASSERT(object != RT_NULL);
    RT_ASSERT(!(object->type & RT_Object_Class_Static));

    RT_OBJECT_HOOK_CALL(rt_object_detach_hook, (object));


    information = rt_object_get_information((enum rt_object_class_type)object->type);
    RT_ASSERT(information != RT_NULL);

    level = rt_spin_lock_irqsave(&(information->spinlock));

    /* remove from old list */
    rt_list_remove(&(object->list));

    rt_spin_unlock_irqrestore(&(information->spinlock), level);

    /* reset object type */
    object->type = RT_Object_Class_Null;

    /* free the memory of object */
    RT_KERNEL_FREE(object);
}
#endif /* RT_USING_HEAP */

/**
 * @brief This function will judge the object is system object or not.
 *
 * @note  Normally, the system object is a static object and the type
 *        of object set to RT_Object_Class_Static.
 *
 * @param object is the specified object to be judged.
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
 * @brief This function will return the type of object without
 *        RT_Object_Class_Static flag.
 *
 * @param object is the specified object to be get type.
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
 * @brief This function will iterate through each object from object
 *        container.
 *
 * @param type is the type of object
 * @param iter is the iterator
 * @param data is the specified data passed to iterator
 *
 * @return RT_EOK on succeed, otherwise the error from `iter`
 *
 * @note this function shall not be invoked in interrupt status.
 */
rt_err_t rt_object_for_each(rt_uint8_t type, rt_object_iter_t iter, void *data)
{
    struct rt_object *object = RT_NULL;
    struct rt_list_node *node = RT_NULL;
    struct rt_object_information *information = RT_NULL;
    rt_base_t level;
    rt_err_t error;

    information = rt_object_get_information((enum rt_object_class_type)type);

    /* parameter check */
    if (information == RT_NULL)
    {
        return -RT_EINVAL;
    }

    /* which is invoke in interrupt status */
    RT_DEBUG_NOT_IN_INTERRUPT;

    /* enter critical */
    level = rt_spin_lock_irqsave(&(information->spinlock));

    /* try to find object */
    rt_list_for_each(node, &(information->object_list))
    {
        object = rt_list_entry(node, struct rt_object, list);
        if ((error = iter(object, data)) != RT_EOK)
        {
            rt_spin_unlock_irqrestore(&(information->spinlock), level);

            return error >= 0 ? RT_EOK : error;
        }
    }

    rt_spin_unlock_irqrestore(&(information->spinlock), level);

    return RT_EOK;
}

struct _obj_find_param
{
    const char *match_name;
    rt_object_t matched_obj;
};

static rt_err_t _match_name(struct rt_object *obj, void *data)
{
    struct _obj_find_param *param = data;
    const char *name = param->match_name;
    if (rt_strncmp(obj->name, name, RT_NAME_MAX) == 0)
    {
        param->matched_obj = obj;

        /* notify an early break of loop, but not on error */
        return 1;
    }

    return RT_EOK;
}

/**
 * @brief This function will find specified name object from object
 *        container.
 *
 * @param name is the specified name of object.
 *
 * @param type is the type of object
 *
 * @return the found object or RT_NULL if there is no this object
 * in object container.
 *
 * @note this function shall not be invoked in interrupt status.
 */
rt_object_t rt_object_find(const char *name, rt_uint8_t type)
{
    struct _obj_find_param param =
    {
        .match_name = name,
        .matched_obj = RT_NULL,
    };

    /* parameter check */
    if (name == RT_NULL) return RT_NULL;

    /* which is invoke in interrupt status */
    RT_DEBUG_NOT_IN_INTERRUPT;

    rt_object_for_each(type, _match_name, &param);
    return param.matched_obj;
}

/**
 * @brief This function will return the name of the specified object container
 *
 * @param object    the specified object to be get name
 * @param name      buffer to store the object name string
 * @param name_size  maximum size of the buffer to store object name
 *
 * @return -RT_EINVAL if any parameter is invalid or RT_EOK if the operation is successfully executed
 *
 * @note this function shall not be invoked in interrupt status
 */
rt_err_t rt_object_get_name(rt_object_t object, char *name, rt_uint8_t name_size)
{
    rt_err_t result = -RT_EINVAL;
    if ((object != RT_NULL) && (name != RT_NULL) && (name_size != 0U))
    {
        const char *obj_name = object->name;
        (void) rt_strncpy(name, obj_name, (rt_size_t)name_size);
        result = RT_EOK;
    }

    return result;
}

#ifdef RT_USING_HEAP
/**
 * This function will create a custom object
 * container.
 *
 * @param name the specified name of object.
 * @param data the custom data
 * @param data_destroy the custom object destroy callback
 *
 * @return the found object or RT_NULL if there is no this object
 * in object container.
 *
 * @note this function shall not be invoked in interrupt status.
 */

rt_object_t rt_custom_object_create(const char *name, void *data, rt_err_t (*data_destroy)(void *))
{
    struct rt_custom_object *cobj = RT_NULL;

    cobj = (struct rt_custom_object *)rt_object_allocate(RT_Object_Class_Custom, name);
    if (!cobj)
    {
        return RT_NULL;
    }
    cobj->destroy = data_destroy;
    cobj->data = data;
    return (struct rt_object *)cobj;
}

/**
 * This function will destroy a custom object
 * container.
 *
 * @param obj the specified name of object.
 *
 * @note this function shall not be invoked in interrupt status.
 */
rt_err_t rt_custom_object_destroy(rt_object_t obj)
{
    rt_err_t ret = -1;

    struct rt_custom_object *cobj = (struct rt_custom_object *)obj;

    if (obj && obj->type == RT_Object_Class_Custom)
    {
        if (cobj->destroy)
        {
            ret = cobj->destroy(cobj->data);
        }
        rt_object_delete(obj);
    }
    return ret;
}
#endif

/**@}*/
