#ifndef __RTGUI_LIST_VIEW_H__
#define __RTGUI_LIST_VIEW_H__

#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>

typedef void (*item_action)(void* parameter);
struct list_item
{
    char* name;
	rtgui_image_t *image;

    item_action action;
    void *parameter;
};

/** Gets the type of a list view */
#define LIST_VIEW_TYPE       (list_view_type_get())
/** Casts the object to a filelist */
#define LIST_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), LIST_VIEW_TYPE, list_view_t))
/** Checks if the object is a filelist view */
#define IS_LIST_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), LIST_VIEW_TYPE))

struct list_view
{
	struct rtgui_view parent;

	/* widget private data */
	/* list item */
    struct list_item* items;

	/* total number of items */
	rt_uint16_t items_count;
    /* the number of item in a page */
    rt_uint16_t page_items;
    /* current item */
    rt_uint16_t current_item;
};
typedef struct list_view list_view_t;

rtgui_type_t *list_view_type_get(void);

list_view_t* list_view_create(struct list_item* items, rt_uint16_t count,
    rtgui_rect_t *rect);
void list_view_clear(list_view_t* view);

rt_bool_t list_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);

#endif

