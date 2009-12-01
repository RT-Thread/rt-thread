#ifndef __PLAY_LIST_H__
#define __PLAY_LIST_H__

#include <rtthread.h>

struct play_item
{
	char title[40];
	char *fn;
	rt_uint32_t duration;
};

void play_list_clear(void);

char* play_list_start(void);
rt_bool_t play_list_is_end(void);
rt_uint32_t play_list_items(void);
struct play_item* play_list_item(rt_uint32_t n);

void play_list_append(char* fn);
char* play_list_next(void);
char* play_list_prev(void);
char* play_list_current_item(void);

#endif
