#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>

extern void workbench_init(void);
extern void panel_init(void);

/* GUI相关演示入口，需放在线程中进行初始化 */
void rtgui_startup()
{
	/* GUI系统初始化 */
    rtgui_system_server_init();

	/* 各个面板初始化 */
	panel_init();

	/* 启动workbench */
	workbench_init();
}
