#include <rtgui/rtgui.h>
#include <rtgui/rtgui_system.h>
#include <stdio.h>
#include <stdlib.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>

#include <stm32f10x_dbgmcu.h>

#ifdef RT_USING_LWIP
#include <lwip/err.h>
#include <lwip/dns.h>
#include <lwip/netif.h>
#endif

static struct rtgui_view* device_view = RT_NULL;

int get_thread_cnt()
{
	int cnt = 0;
	struct rt_list_node *list, *node;
	extern struct rt_object_information rt_object_container[];

	list = &rt_object_container[RT_Object_Class_Thread].object_list;

	for (node = list->next; node != list; node = node->next)
	{
		cnt ++;
	}

	return cnt;
}

const static char *stm32_devname[] = 
{
	"STM32 MD",	/* 0x410 */
	"STM32 LD", /* 0x412 */
	"STM32 HD", /* 0x414 */
	"Unknown" , /* 0x416 */ 
	"STM32 CL", /* 0x418 */
};

const static char *stm32_revname[] = 
{
	"Rev A", 
	"Rev B",
	"Rev Z",
	"Rev Y",
	"Rev Unknown"
};

/*
 * Device Information View
 * Device: Win32 or Cortex-M3 etc
 * Memory:
 * Thread:
 * IP Address:
 * Gateway:
 * DNS:
 */
static rt_bool_t view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	switch (event->type)
	{
	case RTGUI_EVENT_PAINT:
		{
			struct rtgui_dc* dc;
			struct rtgui_rect rect;
			char* line;
			rt_uint32_t total, used, max_used;

			line = rtgui_malloc(256);
			if (line == RT_NULL) return RT_FALSE;

			dc = rtgui_dc_begin_drawing(widget);
			if (dc == RT_NULL)
			{
				rtgui_free(line);
				return RT_FALSE;
			}
			rtgui_widget_get_rect(widget, &rect);

			/* fill background */
			rtgui_dc_fill_rect(dc, &rect);

			rect.y2 = rect.y1 + 18;

			{
				rt_uint32_t dev_index, rev_index;
				
				dev_index = DBGMCU_GetDEVID();
				dev_index = (dev_index - 0x410)/2;
				rev_index = DBGMCU_GetREVID();
				switch (rev_index)
				{
				case 0x1000:
				case 0x0000:
					rev_index = 0; 	/* Revision A */
					break;
					
				case 0x1001:
				case 0x2001:
					rev_index = 3;	/* Revision Z */
					break;
				
				case 0x2000:
					rev_index = 1;	/* Revision B */
					break;
				case 0x2002:
					rev_index = 2;	/* Revision Y */
					break;
					
				default:
					rev_index = 4;	/* Unknown */
					break;
				};

				/* check device index */
				if (dev_index > 4) dev_index = 3;

				/* draw each information */
				sprintf(line, "设备: %s %s", 
					stm32_devname[dev_index], 
					stm32_revname[rev_index]);
				rtgui_dc_draw_text(dc, line, &rect); rect.y1 += 16; rect.y2 += 16;
			}

			rt_memory_info(&total, &used, &max_used);
			sprintf(line, "内存: 当前使用 %d 字节", used);
			rtgui_dc_draw_text(dc, line, &rect); rect.y1 += 16; rect.y2 += 16;
			{
				rt_uint16_t rect_width;
				rtgui_color_t saved;
				
				rtgui_rect_t mem_rect = rect;
				rtgui_rect_inflate(&mem_rect, -2);
				rtgui_dc_draw_rect(dc, &mem_rect);

				rtgui_rect_inflate(&mem_rect, -1);
				rect_width = rtgui_rect_width(mem_rect);

				saved = RTGUI_WIDGET_BACKGROUND(widget);

				RTGUI_WIDGET_BACKGROUND(widget) = light_grey;
				mem_rect.x2 = mem_rect.x1 + (max_used * rect_width / total);
				rtgui_dc_fill_rect(dc, &mem_rect);
				
				RTGUI_WIDGET_BACKGROUND(widget) = blue;
				mem_rect.x2 = mem_rect.x1 + (used * rect_width / total);
				rtgui_dc_fill_rect(dc, &mem_rect);

				/* restore color */
				RTGUI_WIDGET_BACKGROUND(widget) = saved;
			}
			rect.y1 += 18; rect.y2 += 18;

			sprintf(line, "线程数: %d", get_thread_cnt());
			rtgui_dc_draw_text(dc, line, &rect); rect.y1 += 16; rect.y2 += 16;

#ifdef RT_USING_LWIP
			{
				struct ip_addr ip_addr;
				struct _ip_addr
				{
					rt_uint8_t addr0, addr1, addr2, addr3;
				} *addr;
			
				addr = (struct _ip_addr*)&netif_default->ip_addr.addr;

				sprintf(line, "IP地址  : %d.%d.%d.%d", addr->addr0, addr->addr1, addr->addr2, addr->addr3);
				rtgui_dc_draw_text(dc, line, &rect); rect.y1 += 16; rect.y2 += 16;

				addr = (struct _ip_addr*)&netif_default->gw.addr;
				sprintf(line, "网关地址: %d.%d.%d.%d", addr->addr0, addr->addr1, addr->addr2, addr->addr3);
				rtgui_dc_draw_text(dc, line, &rect); rect.y1 += 16; rect.y2 += 16;

				addr = (struct _ip_addr*)&netif_default->netmask.addr;
				sprintf(line, "网络掩码: %d.%d.%d.%d", addr->addr0, addr->addr1, addr->addr2, addr->addr3);
				rtgui_dc_draw_text(dc, line, &rect); rect.y1 += 16; rect.y2 += 16;

#if LWIP_DNS
				ip_addr = dns_getserver(0);
				addr = (struct _ip_addr*)&ip_addr;
				sprintf(line, "DNS地址 : %d.%d.%d.%d", addr->addr0, addr->addr1, addr->addr2, addr->addr3);
				rtgui_dc_draw_text(dc, line, &rect); rect.y1 += 16; rect.y2 += 16;
#endif
			}
#endif

			rtgui_dc_end_drawing(dc);
			rtgui_free(line);
			return RT_FALSE;
		}

	case RTGUI_EVENT_KBD:
		{
            struct rtgui_event_kbd* ekbd;
			
			ekbd = (struct rtgui_event_kbd*)event;
            if (ekbd->type == RTGUI_KEYDOWN && ekbd->key == RTGUIK_RETURN)
            {
				rtgui_workbench_t* workbench;

				workbench = RTGUI_WORKBENCH(RTGUI_WIDGET(device_view)->parent);
				rtgui_workbench_remove_view(workbench, device_view);

				rtgui_view_destroy(device_view);
				device_view = RT_NULL;
            }
		}
		return RT_FALSE;
	}

	/* use parent event handler */
	return rtgui_view_event_handler(widget, event);
}

rtgui_view_t *device_view_create(rtgui_workbench_t* workbench)
{
	if (device_view != RT_NULL)
	{
		rtgui_view_show(device_view, RT_FALSE);
	}
	else
	{
		/* create a view */
		device_view = rtgui_view_create("Device Info");
		/* set view event handler */
		rtgui_widget_set_event_handler(RTGUI_WIDGET(device_view), view_event_handler);
		/* this view can be focused */
		RTGUI_WIDGET(device_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	
		/* add view to workbench */
		rtgui_workbench_add_view(workbench, device_view);
	}
	
	return device_view;
}
