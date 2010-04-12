#ifndef __PICTURE_H__
#define __PICTURE_H__

rtgui_view_t *picture_view_create(struct rtgui_workbench* workbench);
rtgui_view_t *picture_view_create_view_file(struct rtgui_workbench* workbench, const char* fn);
rtgui_view_t *picture_view_create_view_list(struct rtgui_workbench* workbench, const char* list[], rt_uint8_t size);

#endif
