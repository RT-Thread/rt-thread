#include <string.h>
#include <dfs_posix.h>
#include "station_list.h"

static rt_uint32_t read_line(int fd, char* line, rt_uint32_t line_size)
{
    char *pos, *next;
    rt_uint32_t length;

    length = read(fd, line, line_size);
    if (length > 0)
    {
        pos = strstr(line, "\r\n");
		if (pos == RT_NULL)
		{
			pos = strstr(line, "\n");
			next = pos ++;
		}
		else next = pos + 2;

        if (pos != RT_NULL)
        {
            *pos = '\0';

            /* move back */
            lseek(fd, -(length - (next - line)), SEEK_CUR);

            length = pos - line;
        }
        else length = 0;
    }

    return length;
}

static char *strncasestr(const char *haystack, const char *needle)
{
  size_t nl=strlen(needle);
  size_t hl=strlen(haystack);
  size_t i;

  if (!nl) goto found;
  if (nl>hl) return 0;
  for (i=hl-nl+1; i; --i)
  {
    if (*haystack==*needle && !strncasecmp(haystack,needle,nl))
found:
      return (char*)haystack;
    ++haystack;
  }
  return 0;
}

/*
 station list file format:

 [playlist]
 numberofentries=1
 File1=http://67.159.5.47:8110
 Title1=(#1 - 7/500) The Dominican.net Radio
 */
struct station_list* station_list_create(const char* fn)
{
	int fd;
	rt_uint32_t length, index;
	struct station_list* list;
	char  *line, *pos, prefix[8];

	list = (struct station_list*)rt_malloc(sizeof(struct station_list));
	if (list == RT_NULL) goto _return0; /* no memory */
	list->count = 0; list->items = RT_NULL;
	
#define LINE_BUFFER_SIZE	128
	line = rt_malloc(LINE_BUFFER_SIZE);
	if (line == RT_NULL)
		goto _return1; /* no memory */

	fd = open(fn, O_RDONLY, 0); 
	if (fd < 0) goto _return2; /* open file failed */

	length = read_line(fd, line, LINE_BUFFER_SIZE);
	pos = strncasestr(line, "[playlist]");
	if (pos == RT_NULL) 
	{
		station_list_destroy(list);
		list = RT_NULL;
		goto _return2;
	}

	length = read_line(fd, line, LINE_BUFFER_SIZE);
	pos = strncasestr(line, "numberofentries=");
	if (pos != RT_NULL)
	{
		list->count = (int)strtol(pos + strlen("numberofentries="), RT_NULL, 10);
		if (list->count > 0)
		{
			list->items = (struct station_item*) rt_malloc (sizeof(struct station_item) * list->count);
			rt_memset(list->items, 0, sizeof(struct station_item) * list->count);
		}
	}
	else
	{
		station_list_destroy(list);
		list = RT_NULL;
		goto _return2;
	}

	if (list->items == RT_NULL)
	{
		station_list_destroy(list);
		list = RT_NULL;
		goto _return2;
	}

	index = 0;
	while (index < list->count)
	{
		length = read_line(fd, line, LINE_BUFFER_SIZE);
		if (length > 0)
		{
			rt_snprintf(prefix, sizeof(prefix), "File%d", index + 1);
			pos = strncasestr(line, prefix);
			if (pos != RT_NULL)
				strncpy(list->items[index].url, pos + strlen(prefix) + 1, 128);

			rt_snprintf(prefix, sizeof(prefix), "Title%d", index + 1);
			pos = strncasestr(line, prefix);
			if (pos != RT_NULL)
			{
				strncpy(list->items[index].title, pos + strlen(prefix) + 1, 40);
				index ++;
			}
		}
		else break;
	}

_return2:
	close(fd);
_return1:
	rt_free(line);

_return0:
	return list;
}

void station_list_destroy(struct station_list* list)
{
	/* release memory */
	rt_free(list->items);
	rt_free(list);
}

/* update station list file from network */
void station_list_update(struct rtgui_workbench* workbench)
{
}

static void station_list_selected(void* parameter)
{
	rtgui_list_view_t *view;

	view = RTGUI_LIST_VIEW(parameter);

	if (view->current_item != 0)
		rtgui_view_end_modal(RTGUI_VIEW(view), RTGUI_MODAL_OK);
	else
		rtgui_view_end_modal(RTGUI_VIEW(view), RTGUI_MODAL_CANCEL);
}

/* select a station from list */
struct station_item* station_list_select(struct station_list* list, struct rtgui_workbench* workbench)
{
	rt_size_t index;
	rtgui_rect_t rect;
	rtgui_list_view_t *view;
	struct rtgui_list_item* items;
	struct station_item* station;
	char exit_str[] = "·µ»Ø..";

	RT_ASSERT(list != RT_NULL);
	RT_ASSERT(workbench != RT_NULL);

	station = RT_NULL;

	items = (struct rtgui_list_item*) rt_malloc (sizeof(struct rtgui_list_item) * (list->count + 1));
	if (items == RT_NULL) return RT_NULL; /* no memory */

	/* create view */
	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);
	view = rtgui_list_view_create(items, list->count + 1, &rect);

	items[0].image = RT_NULL;
	items[0].action = station_list_selected;
	items[0].name = exit_str;
	items[0].parameter = view;

	for (index = 1; index < list->count + 1; index ++)
	{
		items[index].image = RT_NULL;
		items[index].action = station_list_selected;
		items[index].name = list->items[index - 1].title;
		items[index].parameter = view;
	}

	/* add view to workbench */
	rtgui_workbench_add_view(workbench, RTGUI_VIEW(view));

	/* show view as modal */
	if (rtgui_view_show(RTGUI_VIEW(view), RT_TRUE) == RTGUI_MODAL_OK)
	{
		station = &list->items[view->current_item - 1];
	}

	/* destroy view */
	rtgui_list_view_destroy(view);

	return station;
}

