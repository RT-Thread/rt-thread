#include "demo_view.h"
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/slider.h>

static const rt_uint8_t boxChecked[7] = {0x02, 0x06, 0x8E, 0xDC, 0xF8, 0x70, 0x20};

static const rt_uint8_t  sysMin[2] = {0x7E, 0x7E};
static const rt_uint8_t  sysMax[18] = {0x0F, 0xF8, 0x0F, 0xF8, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x08, 0x08, 0x08, 0x08, 0x0F, 0xF8
};
static const rt_uint8_t  sysNormal[18] = {0x03, 0xF0, 0x03, 0xF0, 0x02, 0x10,
	0x0F, 0xD0, 0x0F, 0xD0, 0x08, 0x70,
	0x08, 0x40, 0x08, 0x40, 0x0F, 0xC0
};

static const rt_uint8_t  sysClose[14] = {0x06, 0x18, 0x03, 0x30, 0x01, 0xE0, 0x00,
	0xC0, 0x01, 0xE0, 0x03, 0x30, 0x06, 0x18
};

static const rt_uint8_t  viewSYS[28] = {0xFF, 0x1F, 0x3C, 0x06, 0x1C, 0x04, 0x1C,
	0x0C, 0x0E, 0x08, 0x0E, 0x18, 0x07, 0x10,
	0x07, 0x30, 0x03, 0xA0, 0x03, 0xE0, 0x01,
	0xC0, 0x01, 0xC0, 0x00, 0x80, 0x00, 0x80
};

rt_bool_t dc_event_handler(rtgui_widget_t* widget, rtgui_event_t *event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		rtgui_rect_t rect;
		rt_uint32_t vx[] = {20, 50, 60, 45, 60, 20};
		rt_uint32_t vy[] = {150, 50, 90, 60, 45, 50};

		/* 因为用的是demo view，上面本身有一部分控件，所以在绘图时先要让demo view先绘图 */
		rtgui_view_event_handler(widget, event);

		/************************************************************************/
		/* 下面的是DC的处理                                             */
		/************************************************************************/

		/* 获得控件所属的DC */
		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) /* 如果不能正常获得DC，返回（如果控件或父控件是隐藏状态，DC是获取不成功的） */
			return RT_FALSE;

		/* 获得demo view允许绘图的区域 */
		demo_view_get_rect(RTGUI_VIEW(widget), &rect);

		rtgui_dc_set_textalign(dc, RTGUI_ALIGN_BOTTOM | RTGUI_ALIGN_CENTER_HORIZONTAL);
#ifdef RTGUI_USING_SMALL_SIZE
		rtgui_dc_draw_text(dc, "RT-Thread/GUI小型版本", &rect);
#else
		rtgui_dc_draw_text(dc, "RT-Thread/GUI标准版本", &rect);
#endif

		/* 绘制一个圆形 */
		rtgui_dc_set_color(dc, red);
		rtgui_dc_draw_circle(dc, rect.x1 + 10, rect.y1 + 10, 10);

		/* 填充一个圆形 */
		rtgui_dc_set_color(dc, green);
		rtgui_dc_fill_circle(dc, rect.x1 + 30, rect.y1 + 10, 10);

		/* 画一个圆弧 */
		rtgui_dc_set_color(dc, RTGUI_RGB(250, 120, 120));
		rtgui_dc_draw_arc(dc, rect.x1 + 120, rect.y1 + 60, 30, 0, 120);

		/* 多边形 */
		rtgui_dc_set_color(dc, blue);
		rtgui_dc_draw_polygon(dc, vx, vy, 6);

		{
			rtgui_rect_t item_rect = {0, 0, 14, 14};
			rt_uint16_t item_size = 14;

			rtgui_rect_moveto(&item_rect, 100, 100);

			rtgui_dc_set_color(dc, RTGUI_RGB(0x66, 0x66, 0x66));
			rtgui_dc_draw_circle(dc, item_rect.x1 + item_size/2, item_rect.y1 + item_size/2, item_size/2);
			rtgui_dc_set_color(dc, RTGUI_RGB(0xff, 0xFF, 0xFF));
			rtgui_dc_draw_circle(dc, item_rect.x1 + item_size/2, item_rect.y1 + item_size/2, item_size/2 - 1);

			rtgui_dc_set_color(dc, RTGUI_RGB(0x00, 0x00, 0x00));
			rtgui_dc_fill_circle(dc, item_rect.x1 + item_size/2, item_rect.y1 + item_size/2, item_size/2 - 3);
		}

		{
			rtgui_rect_t item_rect = {0, 0, 14, 14};
			rt_uint16_t item_size = 14;
			rtgui_rect_moveto(&item_rect, 120, 120);

			rtgui_dc_set_color(dc, RTGUI_RGB(0x66, 0x66, 0x66));
			rtgui_dc_draw_circle(dc, item_rect.x1 + item_size/2, item_rect.y1 + item_size/2, item_size/2);
			rtgui_dc_set_color(dc, RTGUI_RGB(0xff, 0xFF, 0xFF));
			rtgui_dc_draw_circle(dc, item_rect.x1 + item_size/2, item_rect.y1 + item_size/2, item_size/2 - 1);
			rtgui_dc_set_color(dc, RTGUI_RGB(0x00, 0x00, 0x00));
		}
		{
			int x, y;

			x = 150; y = 150;
			rtgui_dc_set_color(dc, black);

			rtgui_dc_draw_byte(dc, x, y, 7, boxChecked);
			y += 7 + 2;

			rtgui_dc_draw_byte(dc, x, y, 2, sysMin);
			y += 2 + 2;

			rtgui_dc_draw_word(dc, x, y, 9, sysMax);
			y += 9 + 2;

			rtgui_dc_draw_word(dc, x, y, 9, sysNormal);
			y += 9 + 2;

			rtgui_dc_draw_word(dc, x, y, 7, sysClose);
			y += 7 + 2;

			rtgui_dc_draw_word(dc, x, y, 14, viewSYS);
			y += 14 + 2;
		}

		{
			rtgui_rect_t rect = {0, 0, 16, 16};
			rtgui_rect_moveto(&rect, 30, 120);

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_RAISE); 
			rect.x1 += 20; rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "raise", &rect);
			rect.x1 -= 20; rect.x2 -= 20 + 50;
			rect.y1 += 20; rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SIMPLE);
			rect.x1 += 20; rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "simple", &rect);
			rect.x1 -= 20; rect.x2 -= 20 + 50;
			rect.y1 += 20; rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_SUNKEN);
			rect.x1 += 20; rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "sunken", &rect);
			rect.x1 -= 20; rect.x2 -= 20 + 50;
			rect.y1 += 20; rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_BOX);
			rect.x1 += 20; rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "box", &rect);
			rect.x1 -= 20; rect.x2 -= 20 + 50;
			rect.y1 += 20; rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_STATIC);
			rect.x1 += 20; rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "static", &rect);
			rect.x1 -= 20; rect.x2 -= 20 + 50;
			rect.y1 += 20; rect.y2 += 20;

			rtgui_dc_draw_border(dc, &rect, RTGUI_BORDER_EXTRA);
			rect.x1 += 20; rect.x2 += 20 + 50;
			rtgui_dc_draw_text(dc, "extra", &rect);
			rect.x1 -= 20; rect.x2 -= 20 + 50;
			rect.y1 += 20; rect.y2 += 20;
		}
		/* 绘图完成 */
		rtgui_dc_end_drawing(dc);
	}
	else
	{
		/* 调用默认的事件处理函数 */
		return rtgui_view_event_handler(widget, event);
	}

	return RT_FALSE;
}

rtgui_view_t *demo_view_dc(rtgui_workbench_t* workbench)
{
	rtgui_view_t *view;

	view = demo_view(workbench, "DC Demo");
	if (view != RT_NULL)
		rtgui_widget_set_event_handler(RTGUI_WIDGET(view), dc_event_handler);

	return view;
}
