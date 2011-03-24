/*
 * File      : textbox.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-16     Bernard      first version
 */
#include <rtgui/rtgui.h>
#include <rtgui/dc.h>
#include <rtgui/rtgui_theme.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/widgets/textbox.h>
#include <rtgui/widgets/widget.h>

#include <ctype.h>

static void rtgui_textbox_timeout(rtgui_timer_t* timer, void* parameter);
static rt_bool_t rtgui_textbox_onkey(PVOID wdt, rtgui_event_t* event);
static rt_bool_t rtgui_textbox_onfocus(PVOID wdt, rtgui_event_t* event);
static rt_bool_t rtgui_textbox_onunfocus(PVOID wdt, rtgui_event_t* event);


void _rtgui_textbox_constructor(rtgui_textbox_t *box)
{
	rtgui_rect_t rect;

	RTGUI_WIDGET_FLAG(box) |= RTGUI_WIDGET_FLAG_FOCUSABLE;

	rtgui_widget_set_event_handler(box, rtgui_textbox_event_handler);
	rtgui_widget_set_onfocus(box, rtgui_textbox_onfocus);
	rtgui_widget_set_onunfocus(box, rtgui_textbox_onunfocus);
	rtgui_widget_set_onkey(box,rtgui_textbox_onkey);

	RTGUI_WIDGET_BACKGROUND(box) = white;
	/* set default text align */
	RTGUI_WIDGET_TEXTALIGN(box) = RTGUI_ALIGN_CENTER_VERTICAL;
	rtgui_widget_set_style(box, RTGUI_BORDER_SUNKEN);
	/* set proper of control 创建一个周期型的控制定时器*/
	box->caret_timer = rtgui_timer_create(100, RT_TIMER_FLAG_PERIODIC,rtgui_textbox_timeout, box);
	
	//初始化...当前行,开始行,在当前行中的位置
	box->line = box->line_begin = box->position = 0;
	box->flag = RTGUI_TEXTBOX_NONE; //单行(默认)
	box->isedit = RT_TRUE;//默认是可以编辑的
	/* allocate default line buffer 分配默认的行缓存 */
	box->text = RT_NULL;

	rtgui_font_get_string_rect(RTGUI_WIDGET_FONT(box), "h", &rect);
	box->font_width = rtgui_rect_width(rect);
	box->on_change = RT_NULL;
	box->on_enter = RT_NULL;
}

void _rtgui_textbox_deconstructor(rtgui_textbox_t *textbox)
{
	if(textbox->text != RT_NULL)
	{
		rt_free(textbox->text);
		textbox->text = RT_NULL;
	}
	if(textbox->caret_timer != RT_NULL)
		rtgui_timer_destory(textbox->caret_timer);
	textbox->caret_timer = RT_NULL;

}

rtgui_type_t *rtgui_textbox_type_get(void)
{
	static rtgui_type_t *textbox_type = RT_NULL;

	if(!textbox_type)
	{
		textbox_type = rtgui_type_create("textbox", RTGUI_WIDGET_TYPE,
			sizeof(rtgui_textbox_t),
			RTGUI_CONSTRUCTOR(_rtgui_textbox_constructor),
			RTGUI_DESTRUCTOR(_rtgui_textbox_deconstructor));
	}

	return textbox_type;
}

//#include <rthw.h>
//绘制编辑块光标
void rtgui_textbox_draw_caret(rtgui_textbox_t* box, rt_uint16_t position)
{
	int x,y;
//	rtgui_color_t color;
	rtgui_rect_t rect;
	int font_h,box_h;
	rtgui_dc_t *dc;

	RT_ASSERT(box != RT_NULL);

	dc = rtgui_dc_begin_drawing(box);
	if(dc == RT_NULL)return;

	rtgui_widget_get_rect(box, &rect);

	font_h = rtgui_font_get_font_height(RTGUI_WIDGET_FONT(box));
	box_h = rtgui_rect_height(rect);

	rect.x1 += position * box->font_width+2;
	rect.x2 = rect.x1+2;
	rect.y1 += (box_h-font_h)/2;
	rect.y2 = rect.y1 + font_h;

	for(x=rect.x1;x<rect.x2;x++)
	{
		for(y=rect.y1;y<rect.y2;y++)
		{
//			rt_hw_lcd_get_pixel(color,x,y);
//			color ^= white;
//			rtgui_dc_draw_point(box, color,x,y);

			if(box->flag & RTGUI_TEXTBOX_CARET_SHOW)
			{
				RTGUI_DC_FC(dc) = black;
				rtgui_dc_draw_point(dc, x,y);
			}
			else
			{
				RTGUI_DC_FC(dc) = white;
				rtgui_dc_draw_point(dc, x,y);
			}
		}
	}
	
	rtgui_dc_end_drawing(dc);		
}

static void rtgui_textbox_timeout(rtgui_timer_t* timer, void* parameter)
{
	rtgui_textbox_t* box;
	
	box = (rtgui_textbox_t*)parameter;
	/* set caret flag */
	if(box->flag & RTGUI_TEXTBOX_CARET_SHOW)
		box->flag &= ~RTGUI_TEXTBOX_CARET_SHOW;
	else
		box->flag |= RTGUI_TEXTBOX_CARET_SHOW;

	rtgui_textbox_draw_caret(box,box->position);

	return ;
}

static void rtgui_textbox_onmouse(rtgui_textbox_t* box, rtgui_event_mouse_t* event)
{
	rt_size_t length;
	rt_uint16_t posbak = box->position;

	RT_ASSERT(box != RT_NULL);
	RT_ASSERT(event != RT_NULL);

	if(box->isedit == RT_FALSE)return;

	length = rt_strlen(box->text);

	if(event->button & RTGUI_MOUSE_BUTTON_LEFT && event->button & RTGUI_MOUSE_BUTTON_DOWN)
	{
		rt_int32_t x;
		if(!box->isedit)return;
		if(box->flag & RTGUI_TEXTBOX_MULTI)
		{//多行文本
			/* set widget focus */
			rtgui_widget_focus(box);

			//add codes at here.
			//...
						
			box->position = 0;
			box->flag |= RTGUI_TEXTBOX_CARET_SHOW;
			rtgui_textbox_draw_caret(box,box->position);
		}
		else
		{//单行文本
			/* set caret position */
			x = event->x - RTGUI_WIDGET(box)->extent.x1;
			if(x < 0)
			{
				box->position = 0;
			}
			else if(x > length * box->font_width)
			{
				box->position = length;
			}
			else
			{
				box->position = x / box->font_width;
			}

			//改变了位置,如果上一个位置显示了编辑框光标,则清除之.
			if(box->flag & RTGUI_TEXTBOX_CARET_SHOW)
			{
				rtgui_timer_stop(box->caret_timer);
		
				box->flag &= ~RTGUI_TEXTBOX_CARET_SHOW;
				rtgui_textbox_draw_caret(box, posbak);//先刷新以下编辑块光标,如果是显示状态
		
				rtgui_timer_start(box->caret_timer);
			}

			/* set widget focus */
			rtgui_widget_focus(box);
	
			/* draw caret 绘制编辑块光标 */
			rtgui_textbox_draw_caret(box,box->position);
		}
	}
}

static rt_bool_t rtgui_textbox_onkey(PVOID wdt, rtgui_event_t* event)
{
	rtgui_textbox_t* box = (rtgui_textbox_t*)wdt;
	rtgui_event_kbd_t* ekbd = (rtgui_event_kbd_t*)event;
	rt_size_t length;
	rt_uint16_t posbak = box->position;

	RT_ASSERT(box != RT_NULL);
	RT_ASSERT(ekbd != RT_NULL);

	length = rt_strlen(box->text);
	if(ekbd->key == RTGUIK_DELETE)
	{//删除光标后面的字符
		if(box->position == length - 1)
		{
			box->text[box->position] = '\0';
		}
		else
		{
			char *c;

			/* remove character */
			for(c = &box->text[box->position]; c[1] != '\0'; c++)
				*c = c[1];
			*c = '\0';
		}

		if(box->on_change)box->on_change(box,RT_NULL);
	}
	else if(ekbd->key == RTGUIK_BACKSPACE)
	{//删除光标前面的字符
		
		if(box->position == length - 1)
		{
			box->text[box->position] = '\0';
			box->position --;
		}
		else if(box->position != 0)
		{
			/* remove current character */
			if(box->position != 0)
			{
				char *c;

				/* remove character */
				for(c = &box->text[box->position - 1]; c[1] != '\0'; c++)
					*c = c[1];
				*c = '\0';
			}
			box->position --;
		}

		if(box->on_change)box->on_change(box,RT_NULL);
	}
	else if(ekbd->key == RTGUIK_LEFT)
	{//光标向左移动一个字符位
		if(box->position > 0) 
		{
			box->position --;
		}
	}
	else if(ekbd->key == RTGUIK_RIGHT)
	{//光标向右移动一个字符位
		if(box->position < length) 
		{
			box->position ++;
		}
	}
	else if(ekbd->key == RTGUIK_HOME)
	{//光标移动到串首
		box->position = 0;
	}
	else if(ekbd->key == RTGUIK_END)
	{//光标移动到串尾
		box->position = length;
	}
	else if(ekbd->key == RTGUIK_RETURN)
	{
		if(box->on_enter != RT_NULL)
		{
			box->on_enter(box, RT_NULL);
		}
	}
	else if(ekbd->key == RTGUIK_NUMLOCK)//数字键有效
	{
		/* change numlock state */
	}
	else
	{
		if(isprint(ekbd->key))
		{//是可打印字符或数字
			/* no buffer on this line */
			if(box->flag & RTGUI_TEXTBOX_DIGIT)
			{//输入限制为数字
				if(!isdigit(ekbd->key))
				{//允许'.'和'-'
					if(ekbd->key != '.' && ekbd->key !='-')return RT_FALSE;
					if(ekbd->key == '.' && strchr(box->text,'.'))return RT_FALSE;
					
					if(ekbd->key == '-')
					{//在数字模式下,单独处理符号
						if(length+1 > box->line_length) return RT_FALSE;
						if(length+1 > box->dis_length) return RT_FALSE;
						
						if(strchr(box->text,'-'))
						{//当前已经置为负号
							char* c;
							for(c = &box->text[0]; c != &box->text[length]; c++)
								*c = *(c+1);
							box->text[length] = '\0';
							box->position --;
							goto _exit;
						}
						else
						{
							char* c;
							for(c = &box->text[length]; c != &box->text[0]; c--)
								*c = *(c-1);
							box->text[0] = '-';
							box->text[length+1] = '\0';
							box->position ++;
							goto _exit;
						}	
					}
				}
				//rt_kprintf("%c ",ekbd->key);//debug printf
			}
			if(length+1 > box->line_length) return RT_FALSE;
			if(length+1 > box->dis_length) return RT_FALSE;

			if(box->position <= length-1)
			{
				char* c;

				for(c = &box->text[length]; c != &box->text[box->position]; c--)
					*c = *(c-1);
				box->text[length+1] = '\0';
			}

			box->text[box->position] = ekbd->key;
			box->position ++;

			if(box->on_change)box->on_change(box,RT_NULL);
		}
	}

_exit:
	//改变了位置,如果上一个位置显示了编辑框光标,则清除之.
	if(box->flag & RTGUI_TEXTBOX_CARET_SHOW)
	{
		rtgui_timer_stop(box->caret_timer);

		box->flag &= ~RTGUI_TEXTBOX_CARET_SHOW;
		rtgui_textbox_draw_caret(box, posbak);//先刷新一下编辑块光标,如果是显示状态

		rtgui_timer_start(box->caret_timer);
	}
	/* set widget focus */
	rtgui_widget_focus(box);
	/* set caret to show */
	box->flag |= RTGUI_TEXTBOX_CARET_SHOW;
	/* re-draw text box */
	rtgui_theme_draw_textbox(box);
	/* draw caret 绘制编辑块光标 */
	rtgui_textbox_draw_caret(box,box->position);

	return RT_TRUE;
}

static rt_bool_t rtgui_textbox_onfocus(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_textbox_t* box = (rtgui_textbox_t*)widget;

	/* set caret to show */
	box->flag |= RTGUI_TEXTBOX_CARET_SHOW;//编辑块光标
	/* start caret timer */
	rtgui_timer_start(box->caret_timer);

	return RT_TRUE;
}

static rt_bool_t rtgui_textbox_onunfocus(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_textbox_t* box = (rtgui_textbox_t*)widget;

	/* stop caret timer */
	rtgui_timer_stop(box->caret_timer);

	/* set caret to hide */
	box->flag &= ~RTGUI_TEXTBOX_CARET_SHOW;
	rtgui_textbox_draw_caret(box,box->position);

	if(box->on_enter)box->on_enter(box,event);

	rtgui_theme_draw_textbox(box);

	return RT_TRUE;
}

rt_bool_t rtgui_textbox_event_handler(PVOID wdt, rtgui_event_t* event)
{
	rtgui_widget_t *widget = (rtgui_widget_t*)wdt;
	rtgui_textbox_t* box = (rtgui_textbox_t*)widget;
	
	switch (event->type)
	{
		case RTGUI_EVENT_PAINT:
			if(widget->on_draw != RT_NULL) widget->on_draw(widget, event);
			else 
				rtgui_theme_draw_textbox(box);
			break;
	
		case RTGUI_EVENT_MOUSE_BUTTON:
			if(widget->on_mouseclick != RT_NULL) widget->on_mouseclick(widget, event);
			else 
				rtgui_textbox_onmouse(box, (rtgui_event_mouse_t*)event);
			return RT_TRUE;
	
		case RTGUI_EVENT_KBD:
			if(widget->on_key != RT_NULL) 
				widget->on_key(widget, event);

			return RT_TRUE;
		default:
			return rtgui_widget_event_handler(widget,event);
			
	}

	return RT_FALSE;
}

rtgui_textbox_t* rtgui_textbox_create(PVOID parent,const char* text,int left,int top,int w,int h, rt_uint32_t flag)
{
    rtgui_textbox_t* box;
	
	RT_ASSERT(parent != RT_NULL);

    box = rtgui_widget_create(RTGUI_TEXTBOX_TYPE);
    if(box != RT_NULL)
    {
		rtgui_rect_t rect;
		rtgui_widget_get_rect(parent, &rect);
		rtgui_widget_rect_to_device(parent,&rect);
		rect.x1 += left;
		rect.y1 += top;
		rect.x2 = rect.x1+w;
		rect.y2 = rect.y1+h;
		rtgui_widget_set_rect(box,&rect);

		/* allocate default line buffer */
		rtgui_textbox_set_value(box, text);

		box->flag = flag;
		//设定可显示字符数量
		box->dis_length = (w-5)/rtgui_font_get_font_width(RTGUI_WIDGET_FONT(box));

		rtgui_container_add_child(parent, box);
	}

	return box;
}

void rtgui_textbox_destroy(rtgui_textbox_t* box)
{
	rtgui_widget_destroy(box);
}

//将一个文本串关联到一个textbox控件
void rtgui_textbox_set_value(rtgui_textbox_t* box, const char* text)
{
	if(box->text != RT_NULL)
	{//已经有内容
		/* free the old text */
		rt_free(box->text);
		box->text = RT_NULL;
	}

	//原先没有内容
	box->line_length = ((rt_strlen(text)+1)/RTGUI_TEXTBOX_LINE_MAX+1)*RTGUI_TEXTBOX_LINE_MAX;

	/* allocate line buffer */
	box->text = rt_malloc(box->line_length);  
	rt_memset(box->text, 0, box->line_length);

	/* copy text */
	rt_memcpy(box->text, text, rt_strlen(text) + 1);

	/* set current position */
	box->position = rt_strlen(text);
}

const char* rtgui_textbox_get_value(rtgui_textbox_t* box)
{
	return (const char*)box->text;
}

void rtgui_textbox_set_line_length(rtgui_textbox_t* box, rt_size_t length)
{
	rt_uint8_t* new_line;

	RT_ASSERT(box != RT_NULL);

	/* invalid length */
	if(length <= 0) return;

	new_line = rt_malloc(length);
	if(length < box->line_length)
	{
		rt_memcpy(new_line, box->text, length - 1);
		new_line[length] = '\0';
	}
	else
	{
		rt_memcpy(new_line, (const char*)box->text, rt_strlen((const char*)box->text));
	}

	/* set line length */
	box->line_length = length;
}

//取得textbox控件的文本显示区域
void rtgui_textbox_get_edit_rect(rtgui_textbox_t *box,rtgui_rect_t *rect)
{
	rtgui_widget_get_rect(box, rect);
	rtgui_rect_inflate(rect,-1);
}


