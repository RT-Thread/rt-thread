#include "demo_view.h"
#include <rtgui/widgets/digtube.h>

/* digit tube codes: "ERROR" */
static char digitbuf[5] = {0x79, 0x77, 0x77, 0x3F, 0x77};

rtgui_container_t * demo_view_digtube(void)
{
    struct rtgui_rect rect;
	rtgui_container_t *container;
	struct rtgui_digtube * digtube;
	struct rtgui_digitfont digitfont;

	container = demo_view("Digit Tube View");
	/* add digtube 1: use the default digit font */
	digtube = rtgui_digtube_create(RT_NULL, 5, (void *)4213, 0);
	rtgui_container_add_child(container, RTGUI_WIDGET(digtube));

    demo_view_get_rect(container, &rect);
	rect.y2 = rect.y1 + 80;
	rtgui_widget_set_rect(RTGUI_WIDGET(digtube), &rect);

	/* add digtube 2: show hex */
	digitfont.seg1_len = 20;
	digitfont.seg1_hspace = 4;
	digitfont.seg1_nr = 3;
	digitfont.seg2_len = 20;
	digitfont.seg3_len = 20;
	digitfont.seg1_vspace = 1;
	digitfont.data = RT_NULL;

	digtube = rtgui_digtube_create(&digitfont, 5, (void *)0xABC, RTGUI_DIGTUBE_STYLE_NOBACKFONT | RTGUI_DIGTUBE_STYLE_DISHEXNUM);
	rtgui_container_add_child(container, RTGUI_WIDGET(digtube));
	rect.y1 = rect.y2 + 10;;
	rect.y2 = rect.y1 + 60;
	rtgui_widget_set_rect(RTGUI_WIDGET(digtube), &rect);

	/* add digtube 3: show custom codes table */
	digitfont.seg1_len = 25;
	digitfont.seg1_hspace = 5;
	digitfont.seg1_nr = 5;
	digitfont.seg2_len = 25;
	digitfont.seg3_len = 25;
	digitfont.seg1_vspace = 1;
	digitfont.data = RT_NULL;
	digtube = rtgui_digtube_create(&digitfont, 5, (void *)digitbuf, RTGUI_DIGTUBE_STYLE_DISCODES);
	rtgui_container_add_child(container, RTGUI_WIDGET(digtube));
	rect.y1 = rect.y2 + 5;
	rect.y2 = rect.y1 + 80;
	rtgui_widget_set_rect(RTGUI_WIDGET(digtube), &rect);
	RTGUI_WIDGET_BACKGROUND(digtube) = RTGUI_RGB(0x00, 0x00, 0x00);
	RTGUI_WIDGET_FOREGROUND(digtube) = RTGUI_RGB(0x00, 0xFF, 0x00);
	digtube->digit_bc = RTGUI_RGB(0x00, 0xFF, 0xFF);

	return container;
}