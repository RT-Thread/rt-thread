#include "demo_view.h"
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/filelist_view.h>

static rtgui_label_t* label;
static void open_btn_onbutton(rtgui_widget_t* widget, struct rtgui_event* event)
{
	/* create a file list view */
	rtgui_filelist_view_t *view;
	rtgui_workbench_t *workbench;
	rtgui_rect_t rect;

	workbench = RTGUI_WORKBENCH(rtgui_widget_get_toplevel(widget));
	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);

#ifdef _WIN32
	view = rtgui_filelist_view_create(workbench, "d:\\", "*.*", &rect);
#else
	view = rtgui_filelist_view_create(workbench, "/", "*.*", &rect);
#endif
	if (rtgui_view_show(RTGUI_VIEW(view), RT_TRUE) == RTGUI_MODAL_OK)
	{
		char path[32];

		/* set label */
		rtgui_filelist_get_fullpath(view, path, sizeof(path));

		rtgui_label_set_text(label, path);
	}

	/* 删除 文件列表 视图 */
	rtgui_view_destroy(RTGUI_VIEW(view));
}

rtgui_view_t* demo_fn_view(rtgui_workbench_t* workbench)
{
	rtgui_rect_t rect;
	rtgui_view_t* view;
	rtgui_button_t* open_btn;
	rtgui_font_t* font;

	font = rtgui_font_refer("asc", 12);

	view = demo_view(workbench, "FileList View");
	demo_view_get_rect(view, &rect);

	rect.x1 += 5;
	rect.x2 -= 5;
	rect.y1 += 5;
	rect.y2 = rect.y1 + 20;
	label = rtgui_label_create("fn: ");
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(label));
	rtgui_widget_set_rect(RTGUI_WIDGET(label), &rect);
	RTGUI_WIDGET_FONT(RTGUI_WIDGET(label)) = font;

	demo_view_get_rect(view, &rect);
	rect.x1 += 5;
	rect.x2 = rect.x1 + 80;
	rect.y1 += 30;
	rect.y2 = rect.y1 + 20;
	open_btn = rtgui_button_create("Open File");
	rtgui_container_add_child(RTGUI_CONTAINER(view), RTGUI_WIDGET(open_btn));
	rtgui_widget_set_rect(RTGUI_WIDGET(open_btn), &rect);
	RTGUI_WIDGET_FONT(RTGUI_WIDGET(open_btn)) = font;
	rtgui_button_set_onbutton(open_btn, open_btn_onbutton);

	return view;
}
