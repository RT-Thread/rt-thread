#include "apps_list.h"
#include <rtgui/rtgui_app.h>
#include <rtgui/widgets/listctrl.h>

#include "xpm/exec.xpm"
#include "xpm/close.xpm"

/* application manager */
struct rtgui_application_item
{
	struct rtgui_app* app;
};
static struct rtgui_application_item *app_items = RT_NULL;
static rt_uint16_t app_count = 0;
static struct rtgui_listctrl* app_list;
static struct rtgui_image* app_default_icon = RT_NULL;
static struct rtgui_image* app_close = RT_NULL;

static void _handle_app_create(struct rtgui_event_application* event)
{
	rt_uint32_t index;
	rt_int32_t status;
	struct rtgui_app* app;

	status = RTGUI_STATUS_OK;
	for (index = 0; index < app_count; index ++)
	{
		app = (struct rtgui_app*)app_items[index].app;
		if (app == event->app)
		{
			/* application is created already */
			status = RTGUI_STATUS_ERROR;
			goto __exit;
		}
	}

	app_count += 1;
	if (app_items == RT_NULL)
		app_items = (struct rtgui_application_item*) rtgui_malloc(sizeof(struct rtgui_application_item));
	else
		app_items = (struct rtgui_application_item*) rtgui_realloc(app_items, sizeof(struct rtgui_application_item) * app_count);

	if (app_items == RT_NULL) 
	{
		status = RTGUI_STATUS_ERROR;
		goto __exit;
	}

	app = event->app;

	app_items[app_count - 1].app = app;
	rtgui_listctrl_set_items(app_list, (rt_uint32_t)app_items, app_count);

__exit:
	/* send ack to the application */
	rtgui_ack(RTGUI_EVENT(event), status);
	return;
}

static void _handle_app_destroy(struct rtgui_event_application* event)
{
	rt_uint32_t index;
	struct rtgui_app* app;

	for (index = 0; index < app_count; index ++)
	{
		app = (struct rtgui_app*)app_items[index].app;
		if (app == event->app)
		{
			/* remove this application */
			app_count --;
			if (app_count == 0) 
			{
				rtgui_free(app_items);
				app_items = RT_NULL;
			}
			else if (index == app_count)
			{
				app_items = rtgui_realloc(app_items, app_count * sizeof(struct rtgui_application_item));
			}
			else
			{
				rt_uint32_t j;
				for (j = index; j < app_count; j ++)
				{
					app_items[j] = app_items[j + 1];
				}
				app_items = rtgui_realloc(app_items, app_count * sizeof(struct rtgui_application_item));
			}
			rtgui_listctrl_set_items(app_list, (rt_uint32_t)app_items, app_count);
			rtgui_ack(RTGUI_EVENT(event), RTGUI_STATUS_OK);
			return ;
		}
	}

	/* send ack to the application */
	rtgui_ack(RTGUI_EVENT(event), RTGUI_STATUS_ERROR);
	return;
}

static rt_bool_t _handle_app_activate(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_application_item *item;

	if (app_list->current_item == -1) return RT_TRUE;
	item = &app_items[app_list->current_item];

	rtgui_app_activate(item->app);

	return RT_TRUE;
}

rt_bool_t apps_list_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	RT_ASSERT(object != RT_NULL);
	RT_ASSERT(event  != RT_NULL);

	switch (event->type)
	{
	case RTGUI_EVENT_APP_CREATE:
		_handle_app_create((struct rtgui_event_application*) event);
		break;

	case RTGUI_EVENT_APP_DESTROY:
		_handle_app_destroy((struct rtgui_event_application*) event);
		break;
	}

	return RT_TRUE;
}

static rt_bool_t apps_listctrl_event_handler(struct rtgui_object* object, struct rtgui_event* event)
{
	struct rtgui_listctrl* ctrl;

	ctrl = RTGUI_LISTCTRL(object);
	if (event->type == RTGUI_EVENT_MOUSE_BUTTON)
	{
		struct rtgui_rect rect, close_rect;
		struct rtgui_event_mouse* emouse;

		emouse = (struct rtgui_event_mouse*)event;
		if (emouse->button & RTGUI_MOUSE_BUTTON_UP)
		{
			/* get physical extent information */
			rtgui_widget_get_extent(RTGUI_WIDGET(ctrl), &rect);
			close_rect = rect;
			close_rect.x1 = close_rect.x2 - 50;

			if ((rtgui_rect_contains_point(&close_rect, emouse->x, emouse->y) == RT_EOK) &&
					(ctrl->items_count > 0))
			{
				rt_uint16_t index;
				index = (emouse->y - rect.y1) / (2 + ctrl->item_height);

				if ((index < ctrl->page_items) &&
					(ctrl->current_item/ctrl->page_items)* ctrl->page_items + index < ctrl->items_count)
				{
					rt_uint16_t cur_item;

					/* get current item */
					cur_item = (ctrl->current_item/ctrl->page_items) * ctrl->page_items + index;
					if (cur_item == ctrl->current_item)
					{
						rt_kprintf("close app\n");
						rtgui_app_close(app_items[ctrl->current_item].app);
						return RT_TRUE;
					}
				}
			}
		}
	}

	return rtgui_listctrl_event_handler(object, event);
}

static void _app_info_draw(struct rtgui_listctrl *list, struct rtgui_dc* dc, rtgui_rect_t* rect, rt_uint16_t index)
{
	struct rtgui_image *image;
	rtgui_rect_t item_rect, image_rect;
	struct rtgui_application_item *item, *items;

	item_rect = *rect;
	item_rect.x1 += 5;

	/* draw item */
	items = (struct rtgui_application_item*)list->items;
	item = &items[index];

	/* draw image */
	if (item->app->icon != RT_NULL) image = item->app->icon;
	else image = app_default_icon;

	if (image != RT_NULL)
	{
		image_rect.x1 = image_rect.y1 = 0;
		image_rect.x2 = app_default_icon->w;
		image_rect.y2 = app_default_icon->h;

		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_image_blit(image, dc, &image_rect);
	}
	item_rect.x1 += app_default_icon->w + RTGUI_WIDGET_DEFAULT_MARGIN;

	/* draw text */
	rtgui_dc_draw_text(dc, (const char*)item->app->name, &item_rect); item_rect.x1 += 60;

	if (list->current_item == index)
	{
		/* draw close button */
		image_rect.x1 = image_rect.y1 = 0;
		image_rect.x2 = app_close->w;
		image_rect.y2 = app_close->h;

		item_rect.x1 = item_rect.x2 - 50;
		rtgui_rect_moveto_align(&item_rect, &image_rect, RTGUI_ALIGN_CENTER_VERTICAL);
		rtgui_image_blit(app_close, dc, &image_rect);
	}
}

struct rtgui_panel* apps_list_create(struct rtgui_panel* panel)
{
	struct rtgui_rect rect;

	RT_ASSERT(panel != RT_NULL);

	if (app_default_icon == RT_NULL)
	{
		app_default_icon = rtgui_image_create_from_mem("xpm", (const rt_uint8_t*)exec_xpm, sizeof(exec_xpm), RT_FALSE);
	}
	if (app_close == RT_NULL)
	{
		app_close = rtgui_image_create_from_mem("xpm", (const rt_uint8_t *)close_xpm, sizeof(close_xpm), RT_FALSE);
	}

	rtgui_widget_get_extent(RTGUI_WIDGET(panel), &rect);

	/* create application list */
	rtgui_rect_inflate(&rect, -15);

	app_list = rtgui_listctrl_create((rt_uint32_t)app_items, app_count, &rect, _app_info_draw);
	rtgui_listctrl_set_itemheight(app_list, app_default_icon->h + 2);
	rtgui_listctrl_set_onitem(app_list, _handle_app_activate);
	rtgui_object_set_event_handler(RTGUI_OBJECT(app_list), apps_listctrl_event_handler);

	rtgui_container_add_child(RTGUI_CONTAINER(panel), RTGUI_WIDGET(app_list));

	return RTGUI_PANEL(panel);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void list_apps(void)
{
	rt_uint32_t index;
	struct rtgui_app* app;

	rt_kprintf("GUI Applications:\n");
	rt_kprintf("=================\n");

	for (index = 0; index < app_count; index ++)
	{
		app = (struct rtgui_app*) app_items[index].app;
		rt_kprintf("%s\n", app->name);
	}
}
FINSH_FUNCTION_EXPORT(list_apps,show the application list);
#endif
