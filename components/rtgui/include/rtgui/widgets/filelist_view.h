#ifndef __RTGUI_FILELIST_VIEW_H__
#define __RTGUI_FILELIST_VIEW_H__

#include <rtgui/widgets/container.h>

#if defined(RTGUI_USING_DFS_FILERW)
#define RTGUI_FITEM_FILE      0x0
#define RTGUI_FITEM_DIR       0x1
struct rtgui_file_item
{
	char* name;

	rt_uint32_t type;
	rt_uint32_t size;
};

DECLARE_CLASS_TYPE(filelist);
/** Gets the type of a filelist view */
#define RTGUI_FILELIST_VIEW_TYPE       (RTGUI_TYPE(filelist))
/** Casts the object to a filelist */
#define RTGUI_FILELIST_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_FILELIST_VIEW_TYPE, rtgui_filelist_view_t))
/** Checks if the object is a filelist view */
#define RTGUI_IS_FILELIST_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_FILELIST_VIEW_TYPE))

struct rtgui_filelist_view
{
	struct rtgui_container parent;

	/* widget private data */

    /* current directory */
    char* current_directory;
    char* pattern;

    /* the number of item in a page */
    rt_uint16_t page_items;
	rt_uint16_t items_count;

	/* the selected item */
	rt_uint16_t current_item;

	/* items array */
	struct rtgui_file_item *items;
};
typedef struct rtgui_filelist_view rtgui_filelist_view_t;

rtgui_filelist_view_t* rtgui_filelist_view_create(const char* directory,
												  const char* pattern,
												  const rtgui_rect_t* rect);
void rtgui_filelist_view_destroy(rtgui_filelist_view_t* view);

rt_bool_t rtgui_filelist_view_event_handler(struct rtgui_object* object, struct rtgui_event* event);
void rtgui_filelist_view_set_directory(rtgui_filelist_view_t* view, const char* directory);

void rtgui_filelist_view_get_fullpath(rtgui_filelist_view_t* view, char* path, rt_size_t len);
#endif

#endif
