#ifndef __DEMO_VIEW_H__
#define __DEMO_VIEW_H__

#include <rtgui/rtgui.h>
#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

#ifndef RTGUI_USING_SMALL_SIZE
#include <rtgui/widgets/box.h>
#endif

rtgui_view_t* demo_view(rtgui_workbench_t* workbench, const char* title);
void demo_view_get_rect(rtgui_view_t* view, rtgui_rect_t *rect);
void demo_view_show(void);

#ifndef RTGUI_USING_SMALL_SIZE
rtgui_box_t* demo_view_create_box(rtgui_view_t* view, int orient);
#endif

#endif

