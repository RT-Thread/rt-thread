#ifndef __FILE_LIST_VIEW_H__
#define __FILE_LIST_VIEW_H__

#define FITEM_FILE      0x0
#define FITEM_DIR       0x1
struct file_item
{
	char* name;

	rt_uint32_t type;
	rt_uint32_t size;

    /* files under same directory */
	rtgui_list_t list;
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

	/* total number of items */
	rt_uint32_t count;

	/* the selected item */
	struct file_item* selected;

    /* current directory */
    rt_uint8_t* current_directory;
    rt_uint8_t* pattern;

    /* the number of item in a page */
    rt_uint16_t page_items;

    /* item_list */
	rtgui_list_t item_list;
};
typedef struct filelist_view filelist_view_t;

#endif