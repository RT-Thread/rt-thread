#include "demo_view.h"
#ifndef RTGUI_USING_SMALL_SIZE
#include <rtgui/widgets/box.h>

rtgui_container_t* demo_view_box(rtgui_workbench_t* workbench)
{
    rtgui_rect_t  rect;
    rtgui_container_t* view;

    view = demo_view(workbench, "Box View");
    demo_view_get_rect(view, &rect);

    return view;
}
#endif
