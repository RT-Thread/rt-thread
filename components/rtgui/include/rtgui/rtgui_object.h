/*
 * File      : rtgui_object.h
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
#ifndef __RTGUI_OBJECT_H__
#define __RTGUI_OBJECT_H__


#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

/* rtgui object type */
#define RTGUI_CONTAINER_OF(obj, type, member)	\
	((type *)((char *)(obj) - (unsigned long)(&((type *)0)->member)))

/** Casts the function pointer to an rtgui_constructor */
#define RTGUI_CONSTRUCTOR(constructor)                ((rtgui_constructor_t)(constructor))
/** Casts the function pointer to an rtgui_constructor */
#define RTGUI_DESTRUCTOR(destructor)                  ((rtgui_destructor_t)(destructor))

/* pre-definetion */
struct rtgui_object;
typedef struct rtgui_object rtgui_object_t;
typedef void (*rtgui_constructor_t)(rtgui_object_t *object);
typedef void (*rtgui_destructor_t)(rtgui_object_t *object);

/* rtgui type structure */
struct rtgui_type
{
	/* type name */
	char* name;

	/* hierarchy and depth */
	struct rtgui_type **hierarchy;
	int hierarchy_depth;

	/* constructor and destructor */
	rtgui_constructor_t constructor;
	rtgui_destructor_t destructor;

	/* size of type */
	int size;
};
typedef struct rtgui_type rtgui_type_t;

rtgui_type_t	*rtgui_type_create(const char *type_name, rtgui_type_t *parent_type,
                           int type_size, rtgui_constructor_t constructor,
                           rtgui_destructor_t destructor);
void          rtgui_type_destroy(rtgui_type_t *type);

void          rtgui_type_object_construct(rtgui_type_t *type, rtgui_object_t *object);
void          rtgui_type_destructors_call(rtgui_type_t *type, rtgui_object_t *object);
rt_bool_t     rtgui_type_inherits_from(rtgui_type_t *type, rtgui_type_t *parent);
rtgui_type_t  *rtgui_type_parent_type_get(rtgui_type_t *type);
const char	  *rtgui_type_name_get(rtgui_type_t *type);
rtgui_type_t  *rtgui_type_get_from_name(const char *name);

#ifdef RTGUI_USING_CAST_CHECK
	#define RTGUI_OBJECT_CAST(obj, rtgui_type_t, c_type) \
		((c_type *)rtgui_object_check_cast((rtgui_object_t *)(obj), (rtgui_type_t)))
#else
	#define RTGUI_OBJECT_CAST(obj, rtgui_type_t, c_type)     ((c_type *)(obj))
#endif

#define RTGUI_OBJECT_CHECK_TYPE(_obj, _type) \
	(rtgui_type_inherits_from(((rtgui_object_t *)(_obj))->type, (_type)))

/** Gets the type of an object */
#define RTGUI_OBJECT_TYPE       (rtgui_object_type_get())
/** Casts the object to an rtgui_object_t */
#define RTGUI_OBJECT(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_OBJECT_TYPE, rtgui_object_t))
/** Checks if the object is an rtgui_Object */
#define RTGUI_IS_OBJECT(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_OBJECT_TYPE))

/* rtgui base object */
struct rtgui_object
{
	/* object type */
	rtgui_type_t* type;

	rt_bool_t is_static;
};
rtgui_type_t *rtgui_object_type_get(void);

rtgui_object_t *rtgui_object_create(rtgui_type_t *object_type);
void         rtgui_object_destroy(rtgui_object_t *object);

void         rtgui_object_name_set(rtgui_object_t *object, const char *name);
const char   *rtgui_object_name_get(rtgui_object_t *object);

rtgui_object_t *rtgui_object_check_cast(rtgui_object_t *object, rtgui_type_t *type);
rtgui_type_t   *rtk_object_object_type_get(rtgui_object_t *object);

#ifdef __cplusplus
}
#endif

#endif
