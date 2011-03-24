#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/slider.h>

#define RTGUI_SLIDER_DEFAULT_WIDTH	100
#define RTGUI_SLIDER_DEFAULT_HEIGHT	20
#define RTGUI_SLIDER_DEFAULT_MIN	0
#define RTGUI_SLIDER_DEFAULT_MAX	100

static void _rtgui_slider_constructor(rtgui_slider_t *slider)
{
	rtgui_rect_t rect = {0, 0, RTGUI_SLIDER_DEFAULT_WIDTH, RTGUI_SLIDER_DEFAULT_HEIGHT};

	/* init widget and set event handler */
	RTGUI_WIDGET_FLAG(slider) |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	rtgui_widget_set_rect(slider, &rect);
	rtgui_widget_set_event_handler(slider, rtgui_slider_event_handler);

	/* set proper of control */
	slider->min = RTGUI_SLIDER_DEFAULT_MIN;
	slider->max = RTGUI_SLIDER_DEFAULT_MAX;
	slider->value = RTGUI_SLIDER_DEFAULT_MIN;
	slider->orient = RTGUI_HORIZONTAL;

	slider->ticks = 10;
	slider->thumb_width = 6;
}

static void _rtgui_slider_destructor(rtgui_slider_t *slider)
{

}

rtgui_type_t *rtgui_slider_type_get(void)
{
	static rtgui_type_t *slider_type = RT_NULL;

	if(!slider_type)
	{
		slider_type = rtgui_type_create("slider", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_slider_t), 
			RTGUI_CONSTRUCTOR(_rtgui_slider_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_slider_destructor));
	}

	return slider_type;
}

static void rtgui_slider_onmouse(rtgui_slider_t* slider, rtgui_event_mouse_t* event)
{
	RT_ASSERT(slider != RT_NULL);
	RT_ASSERT(event  != RT_NULL);

	if(event->button & RTGUI_MOUSE_BUTTON_DOWN &&
		event->button & RTGUI_MOUSE_BUTTON_LEFT)
	{
		int sel;
		int range = slider->max - slider->min;
		int x0, xsize;
		int x;
		x0 = 1 + slider->thumb_width/2;

		if(slider->orient == RTGUI_VERTICAL)
		{
			x = event->y - RTGUI_WIDGET(slider)->extent.y1;
			x -= x0;
			xsize = rtgui_rect_height(RTGUI_WIDGET(slider)->extent) - 2 * x0;
		}
		else
		{
			x = event->x - RTGUI_WIDGET(slider)->extent.x1;
			x -= x0;
			xsize = rtgui_rect_width(RTGUI_WIDGET(slider)->extent) - 2 * x0;
		}

		if(x <= 0)
		{
			sel = slider->min;
		}
		else if(x >= xsize)
		{
			sel = slider->max;
		}
		else
		{
			sel = ((range * x) + xsize/2) / xsize;
			sel += slider->min;
		}

		rtgui_widget_focus(slider);
		rtgui_slider_set_value(slider, sel);
	}
}

static void rtgui_slider_onkey(rtgui_slider_t* slider, rtgui_event_kbd_t *event)
{
	RT_ASSERT(slider != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	if(!(RTGUI_KBD_IS_UP(event))) return;

	if(event->key == RTGUIK_LEFT)
	{
		if(slider->value > slider->min)
			slider->value ++;
	}

	if(event->key == RTGUIK_RIGHT)
	{
		if(slider->value < slider->max)
			slider->value --;
	}

	/* update widget */
	rtgui_widget_update(slider);
}

rt_bool_t rtgui_slider_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_slider_t* slider = (rtgui_slider_t*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		if(widget->on_draw != RT_NULL) widget->on_draw(widget, event);
		else
		{
			rtgui_theme_draw_slider(slider);
		}

		break;

	case RTGUI_EVENT_KBD:
		if(widget->on_key != RT_NULL) widget->on_key(widget, event);
		else
		{
			rtgui_slider_onkey(slider, (rtgui_event_kbd_t *)event);
		}
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		if(widget->on_mouseclick != RT_NULL) widget->on_mouseclick(widget, event);
		else
		{
			rtgui_slider_onmouse(slider, (rtgui_event_mouse_t*)event);
		}
		break;
	}

	return RT_FALSE;
}

//创建一个滑动块控件
rtgui_slider_t* rtgui_slider_create(PVOID parent, rt_size_t min, rt_size_t max, int left, int top, int w, int h, int orient)
{
    rtgui_slider_t* slider;

	RT_ASSERT(parent != RT_NULL);

    slider = rtgui_widget_create (RTGUI_SLIDER_TYPE);
    if(slider != RT_NULL)
    {
		rtgui_rect_t rect;

		/* set proper of control */
		slider->min = min;
		slider->max = max;
		slider->value = min;

		slider->ticks = 10;
		slider->thumb_width = 6;//滑动尺宽度

		rtgui_slider_set_orientation(slider, orient);

		rtgui_widget_get_rect(parent, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(slider, &rect);
	}

	return slider;
}

void rtgui_slider_destroy(rtgui_slider_t* slider)
{
	rtgui_widget_destroy(slider);
}

void rtgui_slider_set_range(rtgui_slider_t* slider, rt_size_t min, rt_size_t max)
{
	RT_ASSERT(slider != RT_NULL);

	slider->max = max;
	slider->min = min;
}

void rtgui_slider_set_value(rtgui_slider_t* slider, rt_size_t value)
{
	RT_ASSERT(slider != RT_NULL);

	if(value < slider->min) value = slider->min;
	if(value > slider->max) value = slider->max;

	if(slider->value != value)
	{
		slider->value = value;
		rtgui_theme_draw_slider(slider);
	}
}

//设置目标方向
void rtgui_slider_set_orientation(rtgui_slider_t* slider, int orient)
{
	RT_ASSERT(slider != RT_NULL);

	/* set orient */
	slider->orient = orient;
}

rt_size_t rtgui_slider_get_value(rtgui_slider_t* slider)
{
	RT_ASSERT(slider != RT_NULL);

	return slider->value;
}
