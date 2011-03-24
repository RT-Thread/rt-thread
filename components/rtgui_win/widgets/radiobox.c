#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/widgets/radiobox.h>

#define RTGUI_RADIOBOX_DEFAULT_WIDTH	100
#define RTGUI_RADIOBOX_DEFAULT_HEIGHT	20

static void _rtgui_radiobox_constructor(rtgui_radiobox_t *rbox)
{
	rtgui_rect_t rect = {0, 0, RTGUI_RADIOBOX_DEFAULT_WIDTH, RTGUI_RADIOBOX_DEFAULT_HEIGHT};

	/* init widget and set event handler */
	RTGUI_WIDGET_FLAG(rbox) |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	RTGUI_WIDGET_TEXTALIGN(rbox) = RTGUI_ALIGN_LEFT | RTGUI_ALIGN_CENTER_VERTICAL;
	rtgui_widget_set_rect(rbox, &rect);
	rtgui_widget_set_event_handler(rbox, rtgui_radiobox_event_handler);

	/* set proper of control */
	rbox->items = RT_NULL;
	rbox->item_count = 0;
	rbox->item_sel = -1;
	rbox->orient = RTGUI_HORIZONTAL;
}

static void _rtgui_radiobox_destructor(rtgui_radiobox_t *rbox)
{
	if(rbox->name != RT_NULL)
	{
		rt_free(rbox->name);
		rbox->name = RT_NULL;
	}
}
rtgui_type_t *rtgui_radiobox_type_get(void)
{
	static rtgui_type_t *radiobox_type = RT_NULL;

	if(!radiobox_type)
	{
		radiobox_type = rtgui_type_create("radiobox", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_radiobox_t), 
			RTGUI_CONSTRUCTOR(_rtgui_radiobox_constructor), 
			RTGUI_DESTRUCTOR(_rtgui_radiobox_destructor));
	}

	return radiobox_type;
}

rtgui_radiobox_t* rtgui_radiobox_create(PVOID parent, const char* name, int orient, char** items, int count,
						int left, int top, int w, int h)
{
    rtgui_radiobox_t* rbox;

	RT_ASSERT(parent != RT_NULL);

    rbox = rtgui_widget_create(RTGUI_RADIOBOX_TYPE);
    if(rbox != RT_NULL)
    {
		rtgui_rect_t rect;

		rtgui_widget_get_rect(parent,&rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(rbox,&rect);
		rtgui_container_add_child(parent, rbox);

		rbox->name = rt_strdup(name);
        rbox->item_count = count;
		if(count > 0)
		{
			rbox->items = (char**)rt_malloc(sizeof(char**)*count);
			if(rbox->items == RT_NULL) return RT_NULL;
		}

        rbox->item_sel = -1;
		rbox->orient = orient;
	}

	return rbox;
}

void rtgui_radiobox_destroy(rtgui_radiobox_t* rbox)
{
	rtgui_widget_destroy(rbox);
}

static void rtgui_radiobox_onmouse(rtgui_radiobox_t* rbox, rtgui_event_mouse_t* event)
{
	RT_ASSERT(rbox != RT_NULL);
	RT_ASSERT(event  != RT_NULL);

	if(event->button & RTGUI_MOUSE_BUTTON_DOWN && event->button & RTGUI_MOUSE_BUTTON_LEFT)
	{

		rtgui_rect_t rect;

		/* focus widgets */
		rtgui_widget_focus(rbox);

		/* get widget physical rect */
		rtgui_widget_get_rect(rbox, &rect);

		/* get board size */
		if(rbox->orient == RTGUI_HORIZONTAL)
		{//Ë®Æ½
		}
		else if(rbox->orient == RTGUI_VERTICAL)
		{//´¹Ö±

		}
		
	}
}

rt_bool_t rtgui_radiobox_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_radiobox_t* rbox = (rtgui_radiobox_t*)widget;

	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		if(widget->on_draw != RT_NULL) 
			widget->on_draw(widget, event);
		else
		{	
			rtgui_theme_draw_radiobox(rbox);
		}

		break;

	case RTGUI_EVENT_KBD:
		if(widget->on_key != RT_NULL) widget->on_key(widget, event);
		else
		{
            rtgui_event_kbd_t *e = (rtgui_event_kbd_t*)event;

            /* set focused */
            rtgui_widget_focus(rbox);
            if(!(RTGUI_KBD_IS_UP(e))) return RT_FALSE;

			if(rbox->orient == RTGUI_VERTICAL)
			{
	            if(e->key == RTGUIK_UP)
	            {
	                if(rbox->item_sel > 0)
	                    rtgui_radiobox_set_selection(rbox, rbox->item_sel - 1);
	            }
	            else if(e->key == RTGUIK_DOWN)
	            {
	                if(rbox->item_sel < rbox->item_count - 1)
	                    rtgui_radiobox_set_selection(rbox, rbox->item_sel + 1);
	            }
			}
			else
			{
	            if(e->key == RTGUIK_LEFT)
	            {
	                if(rbox->item_sel > 0)
	                    rtgui_radiobox_set_selection(rbox, rbox->item_sel - 1);
	            }
	            else if(e->key == RTGUIK_RIGHT)
	            {
	                if(rbox->item_sel < rbox->item_count - 1)
	                    rtgui_radiobox_set_selection(rbox, rbox->item_sel + 1);
	            }
			}
        }
		break;

	case RTGUI_EVENT_MOUSE_BUTTON:
		if(widget->on_mouseclick != RT_NULL) 
			widget->on_mouseclick(widget, event);
		else
		{
			rtgui_radiobox_onmouse(rbox, (rtgui_event_mouse_t*)event);
		}
		break;
	}

	return RT_FALSE;
}

void rtgui_radiobox_set_selection(rtgui_radiobox_t* rbox, int selection)
{
	rt_uint16_t old_item;

	if(selection == rbox->item_sel) return;

	old_item = rbox->item_sel;
    if(selection >= 0 && selection < rbox->item_count)
    {
    	rbox->item_sel = selection;
    }

    /* update rbox widget */
	rtgui_theme_draw_radiobutton(rbox, old_item);
	rtgui_theme_draw_radiobutton(rbox, rbox->item_sel);
}

int rtgui_radiobox_get_selection(rtgui_radiobox_t* rbox)
{
    return rbox->item_sel;
}
