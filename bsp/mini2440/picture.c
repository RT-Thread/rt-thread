#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>
#include <dfs_posix.h>
#include <string.h>

enum picture_view_mode
{
	VIEW_SINGLE_MODE,
	VIEW_DIR_MODE,
	VIEW_FN_LIST_MODE
};

static rtgui_view_t* picture_view = RT_NULL;
static enum picture_view_mode view_mode = VIEW_SINGLE_MODE;

/* current picture file name */
static char current_fn[32] = {0};
static const char** picture_fn_list;
static rt_uint8_t picture_fn_list_size, picture_fn_list_current;

static void picture_show_prev()
{
	DIR* dir;
	struct dirent* entry;
	rt_bool_t is_last;
	char fn[32];

	fn[0] = '\0';
	is_last = RT_FALSE;

	dir = opendir("/");
	if (dir == RT_NULL)
	{
		rt_kprintf("open directory failed\n");
		return;
	}

	do
	{
		entry = readdir(dir);
		if (entry != RT_NULL)
		{
			if (strstr(entry->d_name, ".hdc") != RT_NULL ||
				strstr(entry->d_name, ".HDC") != RT_NULL)
			{
				/* it's a HDC image */
				if ((strcmp(entry->d_name, current_fn) == 0) &&
					is_last != RT_TRUE)
				{
					if (fn[0] == '\0')
					{
						/* it should be the last image */
						is_last = RT_TRUE;
					}
					else
					{
						/* display image */
						strcpy(current_fn, fn);
						rtgui_widget_update(RTGUI_WIDGET(picture_view));
						closedir(dir);
						return;
					}
				}
				strcpy(fn, entry->d_name);
			}
		}
	} while(entry != RT_NULL);

	/* close directory */
	closedir(dir);

	if ((is_last == RT_TRUE) && fn[0] != '\0')
	{
		strcpy(current_fn, fn);
		rtgui_widget_update(RTGUI_WIDGET(picture_view));
	}
}

static void picture_show_next()
{
	DIR* dir;
	struct dirent* entry;
	rt_bool_t found, has_image;

	found = RT_FALSE; has_image = RT_FALSE;

__restart:
	dir = opendir("/");
	if (dir == RT_NULL)
	{
		rt_kprintf("open directory failed\n");
		return;
	}

	do
	{
		entry = readdir(dir);
		if (entry != RT_NULL)
		{
			if (strstr(entry->d_name, ".hdc") != RT_NULL ||
				strstr(entry->d_name, ".HDC") != RT_NULL)
			{
				/* this directory includes image */
				has_image = RT_TRUE;

				if (found == RT_TRUE || current_fn[0] == '\0')
				{
					strcpy(current_fn, entry->d_name);
					rtgui_widget_update(RTGUI_WIDGET(picture_view));

					closedir(dir);
					return;
				}

				/* it's a HDC image */
				if (strcmp(entry->d_name, current_fn) == 0)
					found = RT_TRUE;
			}
		}
	} while(entry != RT_NULL);

	/* close directory */
	closedir(dir);

	if (has_image != RT_TRUE) return;
	current_fn[0] = '\0';
	goto __restart;
}

static rt_bool_t picture_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;
		struct rtgui_image* image;
		char fn[32];

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return RT_FALSE;
		rtgui_widget_get_rect(widget, &rect);

		/* open image */
		rt_sprintf(fn, "/%s", current_fn);
		image = rtgui_image_create_from_file("hdc",
			fn, RT_FALSE);
		if (image != RT_NULL)
		{
			/* blit image */
			rtgui_image_blit(image, dc, &rect);
			/* destroy image */
			rtgui_image_destroy(image);
		}
		else
		{
			rtgui_dc_fill_rect(dc, &rect);
			rtgui_dc_draw_text(dc, "没有文件被打开", &rect);
		}
		rtgui_dc_end_drawing(dc);

		return RT_FALSE;
	}
	else if (event->type == RTGUI_EVENT_KBD)
	{
		struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
		if (ekbd->type == RTGUI_KEYDOWN)
		{
			switch (ekbd->key)
			{
			case RTGUIK_UP:
				if (view_mode == VIEW_DIR_MODE) picture_show_next();
				else if (view_mode == VIEW_FN_LIST_MODE)
				{
					picture_fn_list_current ++;
					if (picture_fn_list_current == picture_fn_list_size)
					{
						picture_fn_list_current = 0;
					}
					strcpy(current_fn, picture_fn_list[picture_fn_list_current]);
					rtgui_widget_update(RTGUI_WIDGET(picture_view));
				}
				break;
			case RTGUIK_DOWN:
				if (view_mode == VIEW_DIR_MODE) picture_show_prev();
				else if (view_mode == VIEW_FN_LIST_MODE)
				{
					if (picture_fn_list_current == 0)
					{
						picture_fn_list_current = picture_fn_list_size - 1;
					}
					else picture_fn_list_current --;

					strcpy(current_fn, picture_fn_list[picture_fn_list_current]);
					rtgui_widget_update(RTGUI_WIDGET(picture_view));
				}
				break;
			case RTGUIK_RETURN:
			{
				rtgui_view_t* view;
				rtgui_workbench_t* workbench;
				
				/* close this view */
				current_fn[0] = '\0';
				
				/* remove view in workbench */
				view = RTGUI_VIEW(widget);
				workbench = RTGUI_WORKBENCH(RTGUI_WIDGET(view)->parent);
				rtgui_workbench_remove_view(workbench, view);
				rtgui_view_destroy(view);
				
				picture_view = RT_NULL;
			}
				break;
			}
		}
		return RT_FALSE;
	}

	return rtgui_view_event_handler(widget, event);
}

rtgui_view_t *picture_view_create(struct rtgui_workbench* workbench)
{
    if (picture_view != RT_NULL)
    {
        rtgui_view_show(picture_view, RT_FALSE);
    }
	else
	{
	    /* create picture view */
	    picture_view = rtgui_view_create("Picture Presentation");
		rtgui_widget_set_event_handler(RTGUI_WIDGET(picture_view),
	        picture_view_event_handler);
	
		rtgui_workbench_add_view(workbench, picture_view);
		/* this view can be focused */
		RTGUI_WIDGET(picture_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	}

	return picture_view;
}

rtgui_view_t *picture_view_create_view_file(struct rtgui_workbench* workbench,
	const char* filename)
{
    if (picture_view != RT_NULL)
    {
        rtgui_view_show(picture_view, RT_FALSE);
    }
	else
	{
		strcpy(current_fn, filename);

	    /* create picture view */
	    picture_view = rtgui_view_create("Picture Presentation");
		rtgui_widget_set_event_handler(RTGUI_WIDGET(picture_view),
	        picture_view_event_handler);
	
		rtgui_workbench_add_view(workbench, picture_view);
		/* this view can be focused */
		RTGUI_WIDGET(picture_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
		
		view_mode = VIEW_SINGLE_MODE;
	}

	return picture_view;
}

rtgui_view_t *picture_view_create_view_list(struct rtgui_workbench* workbench,
	const char* list[], rt_uint8_t size)
{
    if (picture_view != RT_NULL)
    {
        rtgui_view_show(picture_view, RT_FALSE);
    }
	else
	{
		picture_fn_list = list;
		picture_fn_list_size = size; 
		picture_fn_list_current = 0;
		strcpy(current_fn, picture_fn_list[picture_fn_list_current]);

	    /* create picture view */
	    picture_view = rtgui_view_create("Picture Presentation");
		rtgui_widget_set_event_handler(RTGUI_WIDGET(picture_view),
	        picture_view_event_handler);

		rtgui_workbench_add_view(workbench, picture_view);
		/* this view can be focused */
		RTGUI_WIDGET(picture_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;

		view_mode = VIEW_FN_LIST_MODE;
	}

	return picture_view;
}
