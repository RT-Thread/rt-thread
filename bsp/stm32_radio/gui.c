#include <rtgui/rtgui.h>
#include <rtgui/widgets/window.h>
#include <rtgui/widgets/label.h>

#include <finsh.h>

void msg()
{
	struct rtgui_win* msgbox;
	struct rtgui_rect rect = {50, 50, 200, 200};

	msgbox = rtgui_win_create("Information", &rect, RTGUI_WIN_STYLE_DEFAULT);
	if (msgbox != RT_NULL)
	{
		struct rtgui_box* box = rtgui_box_create(RTGUI_VERTICAL, RT_NULL);
		struct rtgui_label* label = rtgui_label_create("Hello World");

		rtgui_win_set_box(msgbox, box);
		RTGUI_WIDGET(label)->align = RTGUI_ALIGN_CENTER_HORIZONTAL |
			RTGUI_ALIGN_CENTER_VERTICAL;
		rtgui_box_append(box, RTGUI_WIDGET(label));

		rtgui_win_show(msgbox);
	}
}
FINSH_FUNCTION_EXPORT(msg, msg on gui)
