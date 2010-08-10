#include <rtgui/rtgui.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui_server.h>

/*
 * a single panel
 */
void panel_init(void)
{
    rtgui_rect_t rect;

    /* register main panel */
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = rtgui_graphic_driver_get_default()->width;
    rect.y2 = rtgui_graphic_driver_get_default()->height;
    rtgui_panel_register("main", &rect);
    rtgui_panel_set_default_focused("main");
}
