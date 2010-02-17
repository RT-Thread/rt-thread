#include "play_list.h"
#include "player_ui.h"
#include "mp3.h"

#include <string.h>

static struct play_item **play_list = RT_NULL;
static rt_uint16_t play_list_size = 0;
static rt_int16_t  play_list_current = 0;

void play_list_clear()
{
    rt_uint32_t index;

    for (index = 0; index < play_list_size; index ++)
    {
        rt_free(play_list[index]->fn);
        rt_free(play_list[index]);

		play_list[index] = RT_NULL;
    }

    rt_free(play_list);
    play_list = RT_NULL;
    play_list_size = 0;
}

char* play_list_start()
{
    play_list_current = 0;
    return play_list[play_list_current]->fn;
}

rt_bool_t play_list_is_end()
{
    if ((play_list_current == play_list_size - 1) ||
        play_list_size == 0)
        return RT_TRUE;

    return RT_FALSE;
}

rt_uint32_t play_list_items(void)
{
    return play_list_size;
}

struct play_item* play_list_item(rt_uint32_t n)
{
    if (n > play_list_size) return RT_NULL;
    return play_list[n];
}

void play_list_append(char* fn)
{
    play_list_size ++;
	if (play_list == RT_NULL)
		play_list = (struct play_item**) rt_malloc (play_list_size * sizeof(struct play_item*));
	else
    	play_list = (struct play_item**) rt_realloc(play_list, play_list_size * sizeof(struct play_item*));

    play_list[play_list_size - 1] = (struct play_item*)rt_malloc(sizeof(struct play_item));
	if (strstr(fn, ".mp3") != RT_NULL ||
		strstr(fn, ".MP3") != RT_NULL)
	{
		struct tag_info info;

		memset(&info, 0, sizeof(info));
		mp3_get_info(fn, &info);
		if (info.title[0] == '\0')
			rt_snprintf(play_list[play_list_size - 1]->title, sizeof(play_list[play_list_size - 1]->title),
				"<未知名音乐>");
		else
			strcpy(play_list[play_list_size - 1]->title, info.title);

		play_list[play_list_size - 1]->fn = rt_strdup(fn);
		play_list[play_list_size - 1]->duration = info.duration;
	}
	else
	{
		rt_snprintf(play_list[play_list_size - 1]->title, sizeof(play_list[play_list_size - 1]->title),
			"<未知名音乐>");
		play_list[play_list_size - 1]->fn = rt_strdup(fn);
		play_list[play_list_size - 1]->duration = 0;
	}
}

char* play_list_next()
{
    if (play_list_current < play_list_size - 1) play_list_current ++;
    return play_list[play_list_current]->fn;
}

char* play_list_prev()
{
    if (play_list_current > 0) play_list_current --;
    return play_list[play_list_current]->fn;
}

char* play_list_current_item()
{
    return play_list[play_list_current]->fn;
}
