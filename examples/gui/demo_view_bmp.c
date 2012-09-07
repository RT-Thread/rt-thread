/*
* 程序清单：bmp_zoom演示
*/
#include "demo_view.h"
#include <rtgui/dc.h>
#include <rtgui/image.h>
#include <rtgui/image_bmp.h>
#include <rtgui/widgets/label.h>
#include <rtgui/widgets/button.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/container.h>

#if defined(RTGUI_USING_DFS_FILERW)
struct demo_bmp_dt
{
	float scale, angle;
	char *filename;
	struct rtgui_image *image;
	struct rtgui_image *showimg;
	rtgui_container_t *showbox;
	rtgui_textbox_t *box;
	rtgui_rect_t lastrect;
}bmpdt;

rt_bool_t demo_bitmap_showbox(struct rtgui_object* object, struct rtgui_event* event)
{
	rtgui_container_t *container;
	rtgui_widget_t *widget;
	
	RT_ASSERT(object != RT_NULL);

	container = RTGUI_CONTAINER(object);
	widget = RTGUI_WIDGET(object);

	if(event->type == RTGUI_EVENT_PAINT)
	{
		int w, h;
		rtgui_rect_t rect;
		struct rtgui_dc *dc;
		struct rtgui_image *image = bmpdt.showimg;
		/* 如果从其他标签切换到当前标签, image应该是RT_NULL, 重置它 */
		if(image == RT_NULL && bmpdt.image != RT_NULL)
		{
			image = bmpdt.image;
			bmpdt.scale = 1.0f;
			bmpdt.angle = 0.0f;
			rtgui_widget_get_rect(RTGUI_WIDGET(bmpdt.showbox), &bmpdt.lastrect);
			rtgui_rect_inflate(&bmpdt.lastrect, -RTGUI_WIDGET_BORDER(bmpdt.showbox));
		}

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL)
			return RT_FALSE;
		
		rtgui_widget_get_rect(widget, &rect);
		/* 在绘制边框后, 再将rect缩小填充背景, 可以降低闪烁现象 */
		rtgui_dc_draw_border(dc, &rect, RTGUI_WIDGET_BORDER_STYLE(widget));
		rtgui_rect_inflate(&rect, -RTGUI_WIDGET_BORDER(widget));
		w = rtgui_rect_width(bmpdt.lastrect);
		h = rtgui_rect_height(bmpdt.lastrect);
		if(w > rtgui_rect_width(rect)) w = rtgui_rect_width(rect);
		if(h > rtgui_rect_height(rect)) h = rtgui_rect_height(rect);
		
		/* fill container with background */
		/*
		* 参数lastrect会记录上一次绘图所用区域
		* 每次重绘时,只需与lastrect比较,即可得知那些背景区域需要刷新
		* 例如当放大图片时,lastrect比当前绘图区小,所有无需更新背景区,
		* 当缩小图片时, 也仅需要更新绘图区比lastrect大的区域.
		*/
		if(image != RT_NULL)
		{	/* 减少不必要的绘图 */
			rtgui_rect_t rc;
			if(w > image->w)
			{
				rc.x1 = image->w;
				rc.y1 = bmpdt.lastrect.y1;
				rc.x2 = bmpdt.lastrect.x2;
				rc.y2 = (h > image->h) ? image->h : bmpdt.lastrect.y2;
				rtgui_dc_fill_rect(dc, &rc);
			}
			if(h > image->h)
			{
				rc.x1 = bmpdt.lastrect.x1;
				rc.y1 = image->h;
				rc.x2 = bmpdt.lastrect.x2;
				rc.y2 = bmpdt.lastrect.y2;
				rtgui_dc_fill_rect(dc, &rc);
			}
		}
		else
			rtgui_dc_fill_rect(dc, &bmpdt.lastrect);

		/* 将图像数据blit到画布上 */
		if (image != RT_NULL)
		{
			int value;
			rtgui_image_blit(image, dc, &rect);
			bmpdt.lastrect.x1 = bmpdt.lastrect.y1 = RTGUI_WIDGET_BORDER(bmpdt.showbox);

			if(image->w > rtgui_rect_width(rect))
				value = rtgui_rect_width(rect);
			else
				value = image->w;
			bmpdt.lastrect.x2 = bmpdt.lastrect.x1 + value;

			if(image->h > rtgui_rect_height(rect))
				value = rtgui_rect_height(rect);
			else
				value = image->h;
			bmpdt.lastrect.y2 = bmpdt.lastrect.y1 + value;
		}

		rtgui_dc_end_drawing(dc);
		return RT_FALSE;
	}
	return rtgui_container_event_handler(object, event);
}

void demo_bitmap_open(struct rtgui_object* object, struct rtgui_event* event)
{
	char *str;
	rtgui_button_t *button = RTGUI_BUTTON(object);
	/* 从textbox控件中取得文件名 */
	str = (char*)rtgui_textbox_get_value(bmpdt.box);
	if(str == RT_NULL) return;
	if(*str == '/' && (rt_strstr(str, ".bmp")!=RT_NULL || rt_strstr(str, ".BMP")!=RT_NULL))
	{	/* 如果是bmp文件, 且文件名有效, 则读入图像数据 */
		if(bmpdt.filename != RT_NULL) 
			rt_free(bmpdt.filename);
		bmpdt.filename = rt_strdup(str);

		if(bmpdt.image != RT_NULL)
			rtgui_image_destroy(bmpdt.image);

		bmpdt.image = rtgui_image_create_from_file("bmp", bmpdt.filename, RT_TRUE);
		
		if(bmpdt.image != RT_NULL)
		{
			bmpdt.showimg = bmpdt.image;
			bmpdt.scale = 1.0;
			bmpdt.angle = 0.0;
			rtgui_widget_update(RTGUI_WIDGET(bmpdt.showbox));
		}
	}
	else
		rt_kprintf("Bad filename!");
}

void demo_image_zoom_in(struct rtgui_object* object, struct rtgui_event* event)
{
	rtgui_button_t *button = RTGUI_BUTTON(object);

	if (bmpdt.image == RT_NULL) return;

	if (bmpdt.scale > 0.45)
	{	/* 更新缩放倍率 */
		if (bmpdt.scale > 1.0) bmpdt.scale -= (float)0.5;
		else bmpdt.scale -= (float)0.1;
	}
	/* 根据缩放倍率, 缩放原始图形, 并得到新图形的指针 */
	bmpdt.showimg = rtgui_image_zoom(bmpdt.image, bmpdt.scale, bmpdt.scale, RTGUI_IMG_ZOOM_BILINEAR);
	if (bmpdt.showimg != RT_NULL)
		rtgui_widget_update(RTGUI_WIDGET(bmpdt.showbox));
	else
		return;
	if(bmpdt.showimg != bmpdt.image)
	{	/* 释放掉新图形所用的资源 */
		rtgui_image_destroy(bmpdt.showimg);
		bmpdt.showimg = RT_NULL;
	}
}

void demo_image_zoom_out(struct rtgui_object* object, struct rtgui_event* event)
{
	rtgui_button_t *button = RTGUI_BUTTON(object);

	if (bmpdt.image == RT_NULL) return;

	if (bmpdt.scale < 4.95)
	{	/* 更新缩放倍率 */
		if (bmpdt.scale > 0.95) bmpdt.scale += (float)0.5;
		else bmpdt.scale += (float)0.1;
	}

	bmpdt.showimg = rtgui_image_zoom(bmpdt.image, bmpdt.scale, bmpdt.scale, RTGUI_IMG_ZOOM_BILINEAR);
	if (bmpdt.showimg != RT_NULL)
		rtgui_widget_update(RTGUI_WIDGET(bmpdt.showbox));
	else
		return;
	if(bmpdt.showimg != bmpdt.image)
	{
		rtgui_image_destroy(bmpdt.showimg);
		bmpdt.showimg = RT_NULL;
	}
}

void demo_image_rotate(struct rtgui_object* object, struct rtgui_event* event)
{
	rtgui_button_t *button = RTGUI_BUTTON(object);

	if (bmpdt.image == RT_NULL) return;
	/* 更新图像旋转角度 */
	if (bmpdt.angle < 360.0)
		bmpdt.angle += (float)1.0;
	else
		bmpdt.angle = 0.0;
	/* 调用旋转函数执行旋转, 并取得一个新的图像指针 */
	bmpdt.showimg = rtgui_image_rotate(bmpdt.image, bmpdt.angle);
	if (bmpdt.showimg != RT_NULL)
		rtgui_widget_update(RTGUI_WIDGET(bmpdt.showbox));
	else
		return;
	if(bmpdt.showimg != bmpdt.image)
	{
		rtgui_image_destroy(bmpdt.showimg);
		bmpdt.showimg = RT_NULL;
	}
}

rtgui_container_t *demo_view_bmp(void)
{
	rtgui_rect_t rect;
	rtgui_container_t *container, *showbox;
	rtgui_button_t *button;
	rtgui_textbox_t *box;
	/* 用bmpdt结构体记录一些参数 */
	rt_memset(&bmpdt, 0, sizeof(struct demo_bmp_dt));
	bmpdt.scale = 1.0;
	bmpdt.angle = 0.0;
	/* 创建用于演示本代码的容器控件 */
	container = demo_view("Bmp File:");

	demo_view_get_rect(container, &rect);
	rect.x1 += 85;
	rect.x2 -= 5;
	rect.y1 -= 42;
	rect.y2 = rect.y1 + 20;
	box = rtgui_textbox_create("", RTGUI_TEXTBOX_SINGLE);
	rtgui_widget_set_rect(RTGUI_WIDGET(box), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(box));
	bmpdt.box = box;
	/* create a button "open" */
	demo_view_get_rect(container, &rect);
	rect.x1 += 5;
	rect.x2 = rect.x1 + 60;
	rect.y1 -= 10;
	rect.y2 = rect.y1 + 24;
	button = rtgui_button_create("open");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(button));
	rtgui_button_set_onbutton(button, demo_bitmap_open);

	/* create a button "zoom in" */
	demo_view_get_rect(container, &rect);
	rect.x1 += 85;
	rect.x2 = rect.x1 + 70;
	rect.y1 -= 10;
	rect.y2 = rect.y1 + 24;
	button = rtgui_button_create("zoom in");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(button));
	rtgui_button_set_onbutton(button, demo_image_zoom_in);

	/* create a button "zoom out" */
	demo_view_get_rect(container, &rect);
	rect.x1 += 165;
	rect.x2 = rect.x1 + 70;
	rect.y1 -= 10;
	rect.y2 = rect.y1 + 24;
	button = rtgui_button_create("zoom out");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(button));
	rtgui_button_set_onbutton(button, demo_image_zoom_out);

	/* create a button "rotate" */
	demo_view_get_rect(container, &rect);
	rect.x1 += 245;
	rect.x2 = rect.x1 + 70;
	rect.y1 -= 10;
	rect.y2 = rect.y1 + 24;
	button = rtgui_button_create("rotate");
	rtgui_widget_set_rect(RTGUI_WIDGET(button), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(button));
	rtgui_button_set_onbutton(button, demo_image_rotate);

	/* create a container "showbox" */
	demo_view_get_rect(container, &rect);
	rect.x1 += 5;
	rect.x2 -= 5;
	rect.y1 += 20;
	rect.y2 -= 0;
	showbox = rtgui_container_create();
	rtgui_widget_set_rect(RTGUI_WIDGET(showbox), &rect);
	rtgui_container_add_child(container, RTGUI_WIDGET(showbox));
	rtgui_widget_set_border(RTGUI_WIDGET(showbox), RTGUI_BORDER_SIMPLE);
	bmpdt.showbox = showbox;
	rtgui_object_set_event_handler(RTGUI_OBJECT(showbox), demo_bitmap_showbox);
	rtgui_widget_get_rect(RTGUI_WIDGET(showbox), &bmpdt.lastrect);
	rtgui_rect_inflate(&bmpdt.lastrect, -RTGUI_WIDGET_BORDER(showbox));
	
	return container;
}
#endif
