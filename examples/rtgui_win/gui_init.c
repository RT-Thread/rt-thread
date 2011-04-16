#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/rtgui_server.h>
#include "touch.h"

void rt_hw_lcd_init(void);
void rt_hw_key_init(void);
void rtgui_panel_init(void);


/* GUI相关演示入口，需放在线程中进行初始化 */
void rtgui_startup()
{
	/* GUI系统初始化 */
    rtgui_system_server_init();

	/* 按键初始化 */
	rt_hw_key_init();
	/* LCD驱动初始化 */
	rt_hw_lcd_init();
	rtgui_touch_hw_init();
	rtgui_panel_init();
}
