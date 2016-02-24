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
#include <rtgui/rtgui.h>

#ifdef __cplusplus
extern "C" {
#endif

/* rtgui object type */
#define RTGUI_CONTAINER_OF(obj, type, member)   \
	((type *)((char *)(obj) - (unsigned long)(&((type *)0)->member)))

/** Casts the function pointer to an rtgui_constructor */
#define RTGUI_CONSTRUCTOR(constructor)                ((rtgui_constructor_t)(constructor))
/** Casts the function pointer to an rtgui_constructor */
#define RTGUI_DESTRUCTOR(destructor)                  ((rtgui_destructor_t)(destructor))

/* pre-definition */
struct rtgui_object;
struct rtgui_app;

typedef struct rtgui_object rtgui_object_t;
typedef void (*rtgui_constructor_t)(rtgui_object_t *object);
typedef void (*rtgui_destructor_t)(rtgui_object_t *object);

/* rtgui type structure */
struct rtgui_type
{
    /* type name */
    char *name;

    /* parent type link */
    const struct rtgui_type *parent;

    /* constructor and destructor */
    rtgui_constructor_t constructor;
    rtgui_destructor_t destructor;

    /* size of type */
    int size;
};
typedef struct rtgui_type rtgui_type_t;
#define RTGUI_TYPE(type)            (_rtgui_##type##_get_type())
#define RTGUI_PARENT_TYPE(type)		(const struct rtgui_type*)(&_rtgui_##type)

#define DECLARE_CLASS_TYPE(type)    \
	const rtgui_type_t *_rtgui_##type##_get_type(void); \
	extern const struct rtgui_type _rtgui_##type

#define DEFINE_CLASS_TYPE(type, name, parent, constructor, destructor, size) \
	const struct rtgui_type _rtgui_##type = { \
	name, \
	parent, \
	RTGUI_CONSTRUCTOR(constructor), \
	RTGUI_DESTRUCTOR(destructor), \
	size }; \
	const rtgui_type_t *_rtgui_##type##_get_type(void) { return &_rtgui_##type; } \
	RTM_EXPORT(_rtgui_##type##_get_type)

void          rtgui_type_object_construct(const rtgui_type_t *type, rtgui_object_t *object);
void          rtgui_type_destructors_call(const rtgui_type_t *type, rtgui_object_t *object);
rt_bool_t     rtgui_type_inherits_from(const rtgui_type_t *type, const rtgui_type_t *parent);
const rtgui_type_t  *rtgui_type_parent_type_get(const rtgui_type_t *type);
const char    *rtgui_type_name_get(const rtgui_type_t *type);
const rtgui_type_t *rtgui_object_object_type_get(rtgui_object_t *object);

#ifdef RTGUI_USING_CAST_CHECK
	#define RTGUI_OBJECT_CAST(obj, obj_type, c_type) \
	 	((c_type *)rtgui_object_check_cast((rtgui_object_t *)(obj), (obj_type), __FUNCTION__, __LINE__))
#else
	#define RTGUI_OBJECT_CAST(obj, obj_type, c_type)     ((c_type *)(obj))
#endif

#define RTGUI_OBJECT_CHECK_TYPE(_obj, _type) \
	(rtgui_type_inherits_from(((rtgui_object_t *)(_obj))->type, (_type)))

DECLARE_CLASS_TYPE(object);
/** Gets the type of an object */
#define RTGUI_OBJECT_TYPE       RTGUI_TYPE(object)
/** Casts the object to an rtgui_object_t */
#define RTGUI_OBJECT(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_OBJECT_TYPE, struct rtgui_object))
/** Checks if the object is an rtgui_Object */
#define RTGUI_IS_OBJECT(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_OBJECT_TYPE))

enum rtgui_object_flag
{
    RTGUI_OBJECT_FLAG_NONE     = 0x0000,
    RTGUI_OBJECT_FLAG_STATIC   = 0x0001,
    RTGUI_OBJECT_FLAG_DISABLED = 0x0002,
    /* When an object is created, it's flag is set to valid. When an object is
     * deleted, the valid bits will be cleared. */
    RTGUI_OBJECT_FLAG_VALID    = 0xAB00,
};

/* rtgui base object */
struct rtgui_object
{
    /* object type */
    const rtgui_type_t *type;

    /* the event handler */
    rtgui_event_handler_ptr event_handler;

    enum rtgui_object_flag flag;

    rt_uint32_t id;
};

rtgui_object_t *rtgui_object_create(const rtgui_type_t *object_type);
void rtgui_object_destroy(rtgui_object_t *object);

/* set the event handler of object */
void rtgui_object_set_event_handler(struct rtgui_object *object, rtgui_event_handler_ptr handler);
/* object default event handler */
rt_bool_t rtgui_object_event_handler(struct rtgui_object *object, struct rtgui_event *event);
/* helper micro. widget event handlers could use this. */
#define RTGUI_WIDGET_EVENT_HANDLER_PREPARE \
	struct rtgui_widget *widget;  \
	RT_ASSERT(object != RT_NULL); \
	RT_ASSERT(event != RT_NULL);  \
	widget = RTGUI_WIDGET(object); \
	/* supress compiler warning */ \
	widget = widget;

/** handle @param event on @param object's own event handler
 *
 * If the @param object does not have an event handler, which means the object
 * does not interested in any event, it will return RT_FALSE. Otherwise, the
 * return code of that handler is returned.
 */
rt_inline rt_bool_t rtgui_object_handle(struct rtgui_object *object, struct rtgui_event *event)
{
    if (object->event_handler)
        return object->event_handler(object, event);
    return RT_FALSE;
}

rtgui_object_t *rtgui_object_check_cast(rtgui_object_t *object, const rtgui_type_t *type, const char *func, int line);
const rtgui_type_t *rtgui_object_object_type_get(rtgui_object_t *object);

void rtgui_object_set_id(struct rtgui_object *obj, rt_uint32_t id);
rt_uint32_t rtgui_object_get_id(struct rtgui_object *obj);
struct rtgui_object* rtgui_get_object(struct rtgui_app *app, rt_uint32_t id);
struct rtgui_object* rtgui_get_self_object(rt_uint32_t id);

#ifdef __cplusplus
}
#endif

#endif

