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

   object->flag = RTGUI_OBJECT_FLAG_NONE;
}

/* Destroys the object */
static void _rtgui_object_destructor(rtgui_object_t *object)
{
	/* nothing */
}

DEFINE_CLASS_TYPE(object, "object",
	RT_NULL,
	_rtgui_object_constructor,
	_rtgui_object_destructor,
	sizeof(struct rtgui_object));
RTM_EXPORT(_rtgui_object);

void rtgui_type_object_construct(const rtgui_type_t *type, rtgui_object_t *object)
{
	/* first call parent's type */
	if (type->parent != RT_NULL)
		rtgui_type_object_construct(type->parent, object);

	if (type->constructor) type->constructor(object);
}

void rtgui_type_destructors_call(const rtgui_type_t *type, rtgui_object_t *object)
{
	const rtgui_type_t *t;
	
	t = type;
	while (t)
	{
		if (t->destructor) t->destructor(object);
		t = t->parent;
	}
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
 * @brief Creates a new object: it calls the corresponding constructors (from the constructor of the base class to the
 * constructor of the more derived class) and then sets the values of the given properties
 * @param object_type the type of object to create
 * @return Returns the new Etk_Object of type @a object_type
 */
rtgui_object_t *rtgui_object_create(rtgui_type_t *object_type)
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
 * @brief Destroys the object: it first sets the weak-pointers to RT_NULL, emits the "destroyed" signal, and then
 * queues the object in the list of objects to free. Thus, the destructors will only be called at the beginning of the
 * next main loop iteration (from the destructor of the more derived class to the destructor of the ultimate base class).
 * @param object the object to destroy
 * @warning You should not assume that this function will call directly the destructors of the object!
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
 * @brief Checks if @a object can be cast to @a type.
 * If @a object doesn't inherit from @a type, a warning is displayed in the console but the object is returned anyway.
 * @param object the object to cast
 * @param type the type to which we cast the object
 * @return Returns the object
 * @note You usually do not need to call this function, use specific macros instead (ETK_IS_WIDGET() for example)
 */
rtgui_object_t *rtgui_object_check_cast(rtgui_object_t *obj, rtgui_type_t *obj_type, const char* func, int line)
{
	if (!obj) return RT_NULL;

	if (!rtgui_type_inherits_from(obj->type, obj_type))
	{
		rt_kprintf("%s[%d]: Invalid cast from \"%s\" to \"%s\"\n", func, line, rtgui_type_name_get(obj->type), rtgui_type_name_get(obj_type));
	}

	return obj;
}
RTM_EXPORT(rtgui_object_check_cast);


/**
 * @brief Gets the type of the object
 * @param object an object
 * @return Returns the type of @a object (RT_NULL on failure)
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

rt_bool_t rtgui_object_event_handler(struct rtgui_object *object, struct rtgui_event* event)
{
	return RT_FALSE;
}
RTM_EXPORT(rtgui_object_event_handler);

