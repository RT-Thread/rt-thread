#ifndef __STATION_LIST_H__
#define __STATION_LIST_H__

#include <rtthread.h>
#include <rtgui/rtgui.h>
#include <rtgui/widgets/list_view.h>
#include <rtgui/widgets/workbench.h>

struct station_item
{
	char title[40];
	char url[128];
};

struct station_list
{
	rt_uint32_t count;
	struct station_item* items;
};

struct station_list* station_list_create(const char* fn);
void station_list_destroy(struct station_list* list);

/* update station list file from network */
void station_list_update(struct rtgui_workbench* workbench);

/* select a station from list */
struct station_item* station_list_select(struct station_list* list, struct rtgui_workbench* workbench);

#endif

