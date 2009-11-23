#ifndef __FILE_LIST_VIEW_H__
#define __FILE_LIST_VIEW_H__

#include <rtgui/widgets/view.h>

#define FITEM_FILE      0x0
#define FITEM_DIR       0x1
struct file_item
{
	rt_uint8_t* name;

	rt_uint32_t type;
	rt_uint32_t size;
};

/** Gets the type of a filelist view */
#define FILELIST_VIEW_TYPE       (filelist_view_type_get())
/** Casts the object to a filelist */
#define FILELIST_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), FILELIST_VIEW_TYPE, filelist_view_t))
/** Checks if the object is a filelist view */
#define IS_FILELIST_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), FILELIST_VIEW_TYPE))

struct filelist_view
{
	struct rtgui_view parent;

	/* widget private data */

    /* current directory */
    rt_uint8_t* current_directory;
    rt_uint8_t* pattern;

    /* the number of item in a page */
    rt_uint16_t page_items;
	rt_uint16_t items_count;

	/* the selected item */
	rt_uint16_t current_item;

	/* items array */
	struct file_item *items;
};
typedef struct filelist_view filelist_view_t;

rtgui_type_t *filelist_view_type_get(void);

filelist_view_t* filelist_view_create(rtgui_workbench_t* workbench, const char* directory, const char* pattern, const rtgui_rect_t* rect);
void filelist_view_destroy(filelist_view_t* view);

void filelist_view_clear(filelist_view_t* view);

rt_bool_t filelist_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event);
void filelist_view_set_directory(filelist_view_t* view, const char* directory);

#endif
