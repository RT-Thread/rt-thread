#include "rtthread.h"
#include <rtgui/rtgui.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

extern void info_init(void);


void radio_rtgui_init(void)
{
    rtgui_rect_t rect;

    rtgui_system_server_init();

    /* register dock panel */
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 240;
    rect.y2 = 25;
    rtgui_panel_register("info", &rect);

    /* register main panel */
    rect.x1 = 0;
    rect.y1 = 25;
    rect.x2 = 320;
    rect.y2 = 320;
    rtgui_panel_register("main", &rect);
    rtgui_panel_set_default_focused("main");

    info_init();
    /* player_init(); */
}
