#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>

/*
 * a single panel for 240x320
 */
void panel_init(void)
{
    rtgui_rect_t rect;

    /* register main panel */
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 240;
    rect.y2 = 320;
    rtgui_panel_register("main", &rect);
    rtgui_panel_set_default_focused("main");
}
