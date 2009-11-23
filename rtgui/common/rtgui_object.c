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
   if (!object) return;

   object->is_static = RT_FALSE;
}

/* Destroys the object */
static void _rtgui_object_destructor(rtgui_object_t *object)
{
	/* nothing */
}

rtgui_type_t *rtgui_type_create(const char *type_name, rtgui_type_t *parent_type,
						 int type_size, rtgui_constructor_t constructor,
						 rtgui_destructor_t destructor)
{
	rtgui_type_t *new_type;

	if (!type_name)
		return RT_NULL;

	new_type = rtgui_malloc(sizeof(rtgui_type_t));
	new_type->name = rt_strdup(type_name);
	new_type->size = type_size;
	new_type->constructor = constructor;
	new_type->destructor = destructor;

	if (!parent_type)
	{
		new_type->hierarchy_depth = 0;
		new_type->hierarchy = RT_NULL;
	}
	else
	{
		/* Build the type hierarchy */
		new_type->hierarchy_depth = parent_type->hierarchy_depth + 1;
		new_type->hierarchy = rtgui_malloc(sizeof(rtgui_type_t *) * new_type->hierarchy_depth);

		new_type->hierarchy[0] = parent_type;
		rt_memcpy(new_type->hierarchy + 1, parent_type->hierarchy,
				  parent_type->hierarchy_depth * sizeof(rtgui_type_t *));
	}

	return new_type;
}

void rtgui_type_destroy(rtgui_type_t *type)
{
	if (!type) return;

	if (type->hierarchy) rtgui_free(type->hierarchy);

	rtgui_free(type->name);
	rtgui_free(type);
}

void rtgui_type_object_construct(rtgui_type_t *type, rtgui_object_t *object)
{
	int i;

	if (!type || !object) return;

	/* Call the constructors */
	for (i = type->hierarchy_depth - 1; i >= 0; i--)
	{
		if (type->hierarchy[i]->constructor)
			type->hierarchy[i]->constructor(object);
	}
	if (type->constructor) type->constructor(object);
}

void rtgui_type_destructors_call(rtgui_type_t *type, rtgui_object_t *object)
{
	int i;

	if (!type || !object) return;

	if (type->destructor) type->destructor(object);
	for (i = 0; i < type->hierarchy_depth; i++)
	{
		if (type->hierarchy[i]->destructor)
			type->hierarchy[i]->destructor(object);
	}
}

rt_bool_t rtgui_type_inherits_from(rtgui_type_t *type, rtgui_type_t *parent)
{
	int i;

	if (!type || !parent) return RT_FALSE;

	if (type == parent) return RT_TRUE;

	for (i = 0; i < type->hierarchy_depth; i++)
	{
		if (type->hierarchy[i] == parent) return RT_TRUE;
	}

	return RT_FALSE;
}

rtgui_type_t *rtgui_type_parent_type_get(rtgui_type_t *type)
{
	if (!type || !type->hierarchy) return RT_NULL;

	return type->hierarchy[0];
}

const char *rtgui_type_name_get(rtgui_type_t *type)
{
	if (!type) return RT_NULL;

	return type->name;
}

struct rtgui_object_information
{
	rt_uint32_t objs_number;
	rt_uint32_t allocated_size;
	rt_uint32_t max_allocated;
};
struct rtgui_object_information obj_info = {0, 0, 0};

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

	obj_info.objs_number ++;
	obj_info.allocated_size += object_type->size;
	if (obj_info.allocated_size > obj_info.max_allocated)
		obj_info.max_allocated = obj_info.allocated_size;

	new_object->type = object_type;
	new_object->is_static = RT_FALSE;

	rtgui_type_object_construct(object_type, new_object);

	return new_object;
}

/**
 * @brief Destroys the object: it first sets the weak-pointers to RT_NULL, emits the "destroyed" signal, and then
 * queues the object in the list of objects to free. Thus, the destructors will only be called at the beginning of the
 * next main loop iteration (from the destructor of the more derived class to the destructor of the ultimate base class).
 * @param object the object to destroy
 * @warning You should not assume that this function will call directly the destructors of the object!
 */
void rtgui_object_destroy(rtgui_object_t *object)
{
	if (!object || object->is_static == RT_TRUE) return;

	obj_info.objs_number --;
	obj_info.allocated_size -= object->type->size;

	/* call destructor */
	RT_ASSERT(object->type != RT_NULL);
	rtgui_type_destructors_call(object->type, object);

	/* release object */
	rtgui_free(object);
}

/**
 * @internal
 * @brief Gets the type of a rtgui_object
 * @return Returns the type of a rtgui_object
 */
rtgui_type_t *rtgui_object_type_get(void)
{
	static rtgui_type_t *object_type = RT_NULL;

	if (!object_type)
	{
		object_type = rtgui_type_create("object", RT_NULL,
			sizeof(rtgui_object_t), RTGUI_CONSTRUCTOR(_rtgui_object_constructor),
			RTGUI_DESTRUCTOR(_rtgui_object_destructor));
	}

	return object_type;
}

/**
 * @brief Checks if @a object can be cast to @a type.
 * If @a object doesn't inherit from @a type, a warning is displayed in the console but the object is returned anyway.
 * @param object the object to cast
 * @param type the type to which we cast the object
 * @return Returns the object
 * @note You usually do not need to call this function, use specific macros instead (ETK_IS_WIDGET() for example)
 */
rtgui_object_t *rtgui_object_check_cast(rtgui_object_t *object, rtgui_type_t *type)
{
	if (!object) return RT_NULL;

	if (!rtgui_type_inherits_from(object->type, type))
	{
		rt_kprintf("Invalid cast from \"%s\" to \"%s\"\n", rtgui_type_name_get(object->type), rtgui_type_name_get(type));
	}

	return object;
}

/**
 * @brief Gets the type of the object
 * @param object an object
 * @return Returns the type of @a object (RT_NULL on failure)
 */
rtgui_type_t *rtgui_object_object_type_get(rtgui_object_t *object)
{
	if (!object) return RT_NULL;

	return object->type;
}
