/*
 * File      : rtgui_object.c
 * This file is part of RTGUI in RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-04     Bernard      first version
 */

#include <rtgui/rtgui_object.h>
#include <rtgui/rtgui_system.h>

static void _rtgui_object_constructor(rtgui_object_t *object)
{
    if (!object)
        return;

    object->flag = RTGUI_OBJECT_FLAG_VALID;
    object->id   = (rt_uint32_t)object;
}

/* Destroys the object */
static void _rtgui_object_destructor(rtgui_object_t *object)
{
    /* Any valid objest should both have valid flag _and_ valid type. Only use
     * flag is not enough because the chunk of memory may be reallocted to other
     * object and thus the flag will become valid. */
    object->flag = RTGUI_OBJECT_FLAG_NONE;
    object->type = RT_NULL;
}

DEFINE_CLASS_TYPE(object, "object",
                  RT_NULL,
                  _rtgui_object_constructor,
                  _rtgui_object_destructor,
                  sizeof(struct rtgui_object));
RTM_EXPORT(_rtgui_object);

void rtgui_type_object_construct(const rtgui_type_t *type, rtgui_object_t *object)
{
    /* construct from parent to children */
    if (type->parent != RT_NULL)
        rtgui_type_object_construct(type->parent, object);

    if (type->constructor)
        type->constructor(object);
}

void rtgui_type_destructors_call(const rtgui_type_t *type, rtgui_object_t *object)
{
    /* destruct from children to parent */
    if (type->destructor)
        type->destructor(object);

    if (type->parent)
        rtgui_type_destructors_call(type->parent, object);
}

rt_bool_t rtgui_type_inherits_from(const rtgui_type_t *type, const rtgui_type_t *parent)
{
    const rtgui_type_t *t;

    t = type;
    while (t)
    {
        if (t == parent) return RT_TRUE;
        t = t->parent;
    }

    return RT_FALSE;
}

const rtgui_type_t *rtgui_type_parent_type_get(const rtgui_type_t *type)
{
    return type->parent;
}

const char *rtgui_type_name_get(const rtgui_type_t *type)
{
    if (!type) return RT_NULL;

    return type->name;
}

#ifdef RTGUI_OBJECT_TRACE
struct rtgui_object_information
{
    rt_uint32_t objs_number;
    rt_uint32_t allocated_size;
    rt_uint32_t max_allocated;
};
struct rtgui_object_information obj_info = {0, 0, 0};
#endif

/**
 * @brief Creates a new object: it calls the corresponding constructors
 * (from the constructor of the base class to the constructor of the more
 * derived class) and then sets the values of the given properties
 *
 * @param object_type the type of object to create
 * @return the created object
 */
rtgui_object_t *rtgui_object_create(const rtgui_type_t *object_type)
{
    rtgui_object_t *new_object;

    if (!object_type)
        return RT_NULL;

    new_object = rtgui_malloc(object_type->size);
    if (new_object == RT_NULL) return RT_NULL;

#ifdef RTGUI_OBJECT_TRACE
    obj_info.objs_number ++;
    obj_info.allocated_size += object_type->size;
    if (obj_info.allocated_size > obj_info.max_allocated)
        obj_info.max_allocated = obj_info.allocated_size;
#endif

    new_object->type = object_type;

    rtgui_type_object_construct(object_type, new_object);

    return new_object;
}
RTM_EXPORT(rtgui_object_create);

/**
 * @brief Destroys the object.
 *
 * The object destructors will be called in inherited type order.
 *
 * @param object the object to destroy
 */
void rtgui_object_destroy(rtgui_object_t *object)
{
    if (!object || object->flag & RTGUI_OBJECT_FLAG_STATIC)
        return;

#ifdef RTGUI_OBJECT_TRACE
    obj_info.objs_number --;
    obj_info.allocated_size -= object->type->size;
#endif

    /* call destructor */
    RT_ASSERT(object->type != RT_NULL);
    rtgui_type_destructors_call(object->type, object);

    /* release object */
    rtgui_free(object);
}
RTM_EXPORT(rtgui_object_destroy);

/**
 * @brief Checks if the object can be cast to the specified type.
 *
 * If the object doesn't inherit from the specified type, a warning
 * is displayed in the console but the object is returned anyway.
 *
 * @param object the object to cast
 * @param type the type to which we cast the object
 * @return Returns the object
 */
rtgui_object_t *rtgui_object_check_cast(rtgui_object_t *obj, const rtgui_type_t *obj_type, const char *func, int line)
{
    if (!obj) return RT_NULL;

	if (!rtgui_type_inherits_from(obj->type, obj_type))
	{
		rt_kprintf("%s[%d]: Invalid cast from \"%s\" to \"%s\"\n", func, line,
            rtgui_type_name_get(obj->type), rtgui_type_name_get(obj_type));
	}

    return obj;
}
RTM_EXPORT(rtgui_object_check_cast);


/**
 * @brief Gets the type of the object
 *
 * @param object an object
 * @return the type of the object (RT_NULL on failure)
 */
const rtgui_type_t *rtgui_object_object_type_get(rtgui_object_t *object)
{
    if (!object) return RT_NULL;

    return object->type;
}
RTM_EXPORT(rtgui_object_object_type_get);

void rtgui_object_set_event_handler(struct rtgui_object *object, rtgui_event_handler_ptr handler)
{
    RT_ASSERT(object != RT_NULL);

    object->event_handler = handler;
}
RTM_EXPORT(rtgui_object_set_event_handler);

rt_bool_t rtgui_object_event_handler(struct rtgui_object *object, struct rtgui_event *event)
{
    return RT_FALSE;
}
RTM_EXPORT(rtgui_object_event_handler);

void rtgui_object_set_id(struct rtgui_object *object, rt_uint32_t id)
{
#ifdef RTGUI_USING_ID_CHECK
    struct rtgui_object *obj = rtgui_get_self_object(id);
    RT_ASSERT(!obj);
#endif

    object->id = id;
}
RTM_EXPORT(rtgui_object_set_id);

rt_uint32_t rtgui_object_get_id(struct rtgui_object *object)
{
    return object->id;
}
RTM_EXPORT(rtgui_object_get_id);
