#ifndef __RTGUI_FILELIST_VIEW_H__
#define __RTGUI_FILELIST_VIEW_H__

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/scrollbar.h>
#include <rtgui/kbddef.h>
#include <rtgui/color.h>

#define RTGUI_FITEM_FILE      0x0
#define RTGUI_FITEM_DIR       0x1


typedef struct rtgui_fileview rtgui_filelist_view_t;

/** Gets the type of a filelist view */
#define RTGUI_FILELIST_VIEW_TYPE       (rtgui_filelist_view_type_get())
/** Casts the object to a filelist */
#define RTGUI_FILELIST_VIEW(obj)       (RTGUI_OBJECT_CAST((obj), RTGUI_FILELIST_VIEW_TYPE, rtgui_filelist_view_t))
/** Checks if the object is a filelist view */
#define RTGUI_IS_FILELIST_VIEW(obj)    (RTGUI_OBJECT_CHECK_TYPE((obj), RTGUI_FILELIST_VIEW_TYPE))


typedef struct rtgui_file_item
{
	char* name;
	rt_uint32_t type;
	rt_uint32_t size;
}rtgui_filelist_view_item_t;

struct rtgui_fileview
{
	rtgui_container_t parent;

	/* widget private data */
    char* current_dir;	   //当前文件夹current_dir
    char* pattern;         //文件查找类型

    rt_int16_t item_per_page; //每页可显示条数
	rt_int16_t item_count;	   //总条数

	rt_int16_t frist_aloc;/* frist item */
	rt_int16_t now_aloc;  /* now item */
	rt_int16_t old_aloc;  /* old item */

	rtgui_scrollbar_t *sbar;     //卷标  
	
	rtgui_filelist_view_item_t *items; /* items array */
};

rtgui_type_t *rtgui_filelist_view_type_get(void);

rtgui_filelist_view_t* rtgui_filelist_view_create(PVOID parent, const char* directory, const char* pattern,  int left, int top, int w, int h);
void rtgui_filelist_view_destroy(rtgui_filelist_view_t* view);

rt_bool_t rtgui_filelist_view_event_handler(PVOID wdt, rtgui_event_t* event);
void rtgui_filelist_view_set_directory(rtgui_filelist_view_t* view, const char* directory);
void rtgui_filelist_view_on_enter(rtgui_filelist_view_t* fview);
void rtgui_filelist_view_get_fullpath(rtgui_filelist_view_t* view, char* path, rt_size_t len);

#endif
