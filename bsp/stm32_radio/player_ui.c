#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/list_view.h>
#include <rtgui/widgets/workbench.h>
#include <rtgui/widgets/filelist_view.h>

#include <string.h>
#include <dfs_posix.h>

#include "mp3.h"
#include "picture.h"
#include "player_ui.h"
#include "player_bg.h"
#include "play_list.h"
#include "station_list.h"

#include "play.hdh"
#include "stop.hdh"

#define RADIO_FN    "/radio.pls"

const static char *time_bg_xpm[] = {
"48 20 7 1",
".	c #007DC6",
"+	c #0079C6",
"@	c #0079BD",
"#	c #0075BD",
"$	c #0071BD",
"%	c #0071B5",
"&	c #006DB5",
"................................................",
"................................................",
"................................................",
"................................................",
"................................................",
"++++++++++++++++++++++++++++++++++++++++++++++++",
"++++++++++++++++++++++++++++++++++++++++++++++++",
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
"################################################",
"################################################",
"################################################",
"################################################",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%",
"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&",
"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&",
"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&",
"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"};

static struct rtgui_view* home_view;
static struct rtgui_list_view* function_view;
static struct rtgui_workbench* workbench;
static rtgui_timer_t* info_timer;
static rt_thread_t player_ui_tid = RT_NULL;
static enum PLAYER_MODE player_mode = PLAYER_STOP;
static enum PLAYER_STEP next_step = PLAYER_STEP_STOP;
static struct tag_info tinfo;
static rt_uint32_t play_time;
static rtgui_image_t *time_bg_image;

void player_play_file(const char* fn);
void player_play_url(const char* url);

static void info_timer_timeout(rtgui_timer_t* timer, void* parameter)
{
	struct rtgui_dc* dc;
	rtgui_color_t saved;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(home_view));
	if (dc == RT_NULL) return ;

	saved = RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view));

	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view)) = RTGUI_RGB(206, 231, 255);
	rtgui_dc_draw_hline(dc, 14, 14	+ (tinfo.position * 212) / tinfo.duration, 75);

	if ((player_mode == PLAYER_PLAY_RADIO) && ((tinfo.position * 212 + 14)/tinfo.duration) < 226)
	{
		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view)) = RTGUI_RGB(82, 199, 16);
		rtgui_dc_draw_hline(dc, 14  + (tinfo.position * 212) / tinfo.duration, 226, 75);
	}
    RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view)) = saved;

	if (player_mode == PLAYER_PLAY_FILE)
	{
		rtgui_rect_t rect;
	    char line[32];

	    play_time++;
		rt_snprintf(line, sizeof(line), "%3d:%02d", play_time / 60, play_time % 60);

		rect.x1 = 172; rect.y1 = 39;
	    rect.x2 = 220; rect.y2 = 59;
	    rtgui_image_blit(time_bg_image, dc, &rect);
	    rtgui_dc_draw_text(dc, line, &rect);
	}

	rtgui_dc_end_drawing(dc);
}

static void player_update_tag_info(struct rtgui_dc* dc)
{
	rtgui_rect_t rect;
    char line[32];
	rtgui_color_t saved;
	rtgui_image_t *background;

	saved = rtgui_dc_get_color(dc);
	rtgui_dc_set_color(dc, black);

	rect.x1 = 0; rect.y1 = 0;
	rect.x2 = 240; rect.y2 = 65;
	/* draw background */
    background = rtgui_image_create_from_file("hdc", "/resource/bg.hdc", RT_FALSE);
	if (background != RT_NULL)
	{
        rtgui_image_blit(background, dc, &rect);
		rtgui_image_destroy(background);

		background = RT_NULL;
	}
	else
	{
		rtgui_dc_fill_rect(dc, &rect);
	}

	/* draw playing information */
    rect.x1 = 28; rect.y1 = 12;
    rect.x2 = 220; rect.y2 = rect.y1 + 16;
	if (player_mode == PLAYER_STOP)
	{
		rt_snprintf(line, sizeof(line), "网络收音机");
	    rtgui_dc_draw_text(dc, line, &rect);
	}
	else
	    rtgui_dc_draw_text(dc, tinfo.title, &rect);

    rect.x1 = 28; rect.y1 = 39;
    rect.x2 = 220; rect.y2 = 59;
	if (player_mode == PLAYER_STOP)
	{
		rt_snprintf(line, sizeof(line), "radio.rt-thread.org");
	    rtgui_dc_draw_text(dc, line, &rect);
	}
	else
	    rtgui_dc_draw_text(dc, tinfo.artist, &rect);

	if ((tinfo.duration != 0) && player_mode == PLAYER_PLAY_FILE)
	{
		play_time = 0;

        rect.x1 = 172;
		rt_snprintf(line, sizeof(line), "  0:00");
        rtgui_dc_draw_text(dc, line, &rect);
	}

	rtgui_dc_set_color(dc, saved);
}

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

static void function_play_radio(void* parameter)
{
	struct station_list* list;
	struct station_item* item;

	list = station_list_create(RADIO_FN);
	if (list != RT_NULL)
	{
		item = station_list_select(list, workbench);
		if (item != RT_NULL)
		{
			player_play_url(item->url);
		}

		station_list_destroy(list);
	}
}

static void function_filelist(void* parameter)
{
	rtgui_rect_t rect;
	rtgui_filelist_view_t *view;

	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);
	view = rtgui_filelist_view_create(workbench, "/", "*.*", &rect);
	if (view != RT_NULL)
	{
	    if (rtgui_view_show(RTGUI_VIEW(view), RT_TRUE) == RTGUI_MODAL_OK)
	    {
			char fn[64];

            /* get open file */
            rt_snprintf(fn, 64, "%s/%s", view->current_directory,
                view->items[view->current_item].name);

            if (strstr(view->items[view->current_item].name , ".mp3") != RT_NULL ||
                strstr(view->items[view->current_item].name , ".MP3") != RT_NULL ||
                strstr(view->items[view->current_item].name , ".wav") != RT_NULL ||
                strstr(view->items[view->current_item].name , ".WAV") != RT_NULL)
            {
				/* clear old play list */
				play_list_clear();
				play_list_append(fn);

			    player_mode = PLAYER_PLAY_FILE;
				next_step = PLAYER_STEP_STOP;
				player_play_file(play_list_start());
            }
            else if (strstr(view->items[view->current_item].name , ".m3u") != RT_NULL ||
                strstr(view->items[view->current_item].name , ".M3U") != RT_NULL)
            {
                /* read all of music filename to a list */
                int fd;
                char line[64];

                fd = open(fn, O_RDONLY, 0);
                if (fd >= 0)
                {
                    rt_uint32_t length;

                    length = read_line(fd, line, sizeof(line));
					/* clear old play list */
					play_list_clear();

                    do
                    {
                        length = read_line(fd, line, sizeof(line));
                        if (length > 0)
                        {
                        	if (strstr(line, "http:") != RT_NULL)
                        	{
                        		play_list_append(line);
                        	}
							else if (line[0] != '/')
                            {
                                rt_snprintf(fn, sizeof(fn), "%s/%s", view->current_directory, line);
                                play_list_append(fn);
                            }
                            else play_list_append(line);
                        }
                    } while (length > 0);

                    close(fd);

					if (play_list_items() > 0)
					{
					    player_mode = PLAYER_PLAY_FILE;
						next_step = PLAYER_STEP_NEXT;
		                player_play_file(play_list_start());
					}
                }
            }
	    }

		/* destroy view */
		rtgui_filelist_view_destroy(view);
	}

	return;
}

static void function_device(void* parameter)
{
	rtgui_view_t *view;
	extern rtgui_view_t* device_view_create(rtgui_workbench_t* workbench);

	view = device_view_create(workbench);
	if (view != RT_NULL)
	{
	    rtgui_view_show(view, RT_FALSE);
	}

	return;
}

static void function_player(void* parameter)
{
    rtgui_view_show(home_view, RT_FALSE);
	return;
}

static void function_show_picure(void* parameter)
{
	rtgui_view_t *view;

	view = picture_view_create(workbench);
	if (view != RT_NULL)
	{
		rtgui_view_show(view, RT_TRUE);
		rtgui_view_destroy(view);
	}

	return;
}

void function_action(void* parameter)
{
	rt_kprintf("item action!\n");
	return;
}

void function_cable(void* parameter)
{
	extern void USB_cable(void);
    USB_cable();
}

const struct rtgui_list_item function_list[] =
{
	{"选择电台", RT_NULL, function_play_radio, RT_NULL},
	{"更新电台", RT_NULL, function_action, RT_NULL},
	{"播放文件", RT_NULL, function_filelist, RT_NULL},
	{"浏览图片", RT_NULL, function_show_picure, RT_NULL},
	{"设备信息", RT_NULL, function_device, RT_NULL},
	{"选项设置", RT_NULL, function_action, RT_NULL},
	{"USB 联机", RT_NULL, function_cable, RT_NULL},
	{"返回播放器", RT_NULL, function_player, RT_NULL},
};

void player_set_position(rt_uint32_t position)
{
	if (player_mode != PLAYER_PLAY_RADIO)
	{
	    tinfo.position = position / (tinfo.bit_rate / 8);
	}
	else
	{
		tinfo.position = position;
	}
}

void player_set_title(const char* title)
{
	strncpy(tinfo.title, title, 40);
}

void player_set_buffer_status(rt_bool_t buffering)
{
	if (buffering == RT_TRUE)
		strncpy(tinfo.artist, "缓冲中...", 40);
	else
		strncpy(tinfo.artist, "播放中...", 40);
}

enum PLAYER_MODE player_get_mode()
{
	return player_mode;
}

void player_play_file(const char* fn)
{
	struct rtgui_dc* dc;
	rtgui_color_t saved;
	rt_bool_t is_mp3;

	is_mp3 = RT_FALSE;

	if (strstr(fn, ".mp3") != RT_NULL ||
		strstr(fn, ".MP3") != RT_NULL)
		is_mp3 = RT_TRUE;
	else if (strstr(fn, ".wav") != RT_NULL ||
		strstr(fn, ".wav") != RT_NULL)
		is_mp3 = RT_FALSE;
	else return; /* not supported audio format */

	if (is_mp3 == RT_TRUE)
	{
		/* get music tag information */
		mp3_get_info(fn, &tinfo);
		if (tinfo.title[0] == '\0')
			rt_snprintf(tinfo.title, sizeof(tinfo.title), "<未知名音乐>");
	}
	else
	{
		/* wav file */
		rt_snprintf(tinfo.title, sizeof(tinfo.title), "<未知名音乐>");
		rt_snprintf(tinfo.artist, sizeof(tinfo.title), "<wav音乐>");

		tinfo.duration = 0;
	}

	/* set player mode */
	player_mode = PLAYER_PLAY_FILE;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(home_view));
	if (dc != RT_NULL)
	{
		rtgui_rect_t play_rect;
		rtgui_image_t *button;

		/* update tag information */
		player_update_tag_info(dc);

		/* reset progress bar */
		saved = RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view));
		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view)) = RTGUI_RGB(82, 199, 16);
		rtgui_dc_draw_hline(dc, 14, 226, 75);
		RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view)) = saved;

		/* update play button */
		button = rtgui_image_create_from_mem("hdc",
            play_hdh, sizeof(play_hdh), RT_FALSE);
        play_rect.x1 = 32; play_rect.y1 = 92;
        play_rect.x2 = 61; play_rect.y2 = 114;
        rtgui_image_blit(button, dc, &play_rect);
        rtgui_image_destroy(button);

		rtgui_dc_end_drawing(dc);
	}

    rtgui_view_show(home_view, RT_FALSE);

    player_play_req(fn);
}

void player_play_url(const char* url)
{
	struct rtgui_dc* dc;

    /* set music tag information */
	strncpy(tinfo.title, "网络电台", 40);
	player_set_buffer_status(RT_TRUE);
	tinfo.duration = 320 * 1024; /* 320 k */

	/* set player mode */
	player_mode = PLAYER_PLAY_RADIO;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(home_view));
	if (dc != RT_NULL)
	{
		rtgui_rect_t play_rect;
		rtgui_image_t *button;

		/* update tag information */
		player_update_tag_info(dc);

		/* update play button */
		button = rtgui_image_create_from_mem("hdc",
            play_hdh, sizeof(play_hdh), RT_FALSE);
        play_rect.x1 = 32; play_rect.y1 = 92;
        play_rect.x2 = 61; play_rect.y2 = 114;
        rtgui_image_blit(button, dc, &play_rect);
        rtgui_image_destroy(button);

		rtgui_dc_end_drawing(dc);
	}

    rtgui_view_show(home_view, RT_FALSE);

    player_play_req(url);
}

static rt_bool_t home_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;
		rtgui_color_t saved;
		rtgui_image_t *background;

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return RT_FALSE;
		rtgui_widget_get_rect(widget, &rect);
		saved = RTGUI_WIDGET_FOREGROUND(widget);

		/* draw background */
	    background = rtgui_image_create_from_file("hdc", "/resource/bg.hdc", RT_FALSE);
		if (background != RT_NULL)
		{
            rtgui_image_t *play;
            rtgui_rect_t  play_rect;

            rtgui_image_blit(background, dc, &rect);
			rtgui_image_destroy(background);

			background = RT_NULL;

			if (player_mode == PLAYER_STOP)
				play = rtgui_image_create_from_mem("hdc", stop_hdh, sizeof(stop_hdh), RT_FALSE);
			else
				play = rtgui_image_create_from_mem("hdc", play_hdh, sizeof(play_hdh), RT_FALSE);
            play_rect.x1 = 32; play_rect.y1 = 92;
            play_rect.x2 = 61; play_rect.y2 = 114;
            rtgui_image_blit(play, dc, &play_rect);
            rtgui_image_destroy(play);
		}
		else
		{
			rtgui_dc_fill_rect(dc, &rect);
		}

		/* draw playing information */
		rtgui_dc_set_color(dc, black);
        {
            char line[32];

            rect.x1 = 28; rect.y1 = 12;
            rect.x2 = 220; rect.y2 = rect.y1 + 16;
			if (player_mode == PLAYER_STOP)
			{
				rt_snprintf(line, sizeof(line), "网络收音机");
			    rtgui_dc_draw_text(dc, line, &rect);
			}
			else
			    rtgui_dc_draw_text(dc, tinfo.title, &rect);

            rect.x1 = 28; rect.y1 = 39;
            rect.x2 = 170; rect.y2 = 59;
			if (player_mode == PLAYER_STOP)
			{
				rect.x2 = 220;
				rt_snprintf(line, sizeof(line), "radio.rt-thread.org");
			    rtgui_dc_draw_text(dc, line, &rect);
			}
			else
			    rtgui_dc_draw_text(dc, tinfo.artist, &rect);

			if ((tinfo.duration != 0) && (player_mode == PLAYER_PLAY_FILE))
			{
	            rt_uint32_t t = player_mode == PLAYER_STOP ? tinfo.duration : play_time;

	            rect.x1 = 172; rect.x2 = 220;
				rt_snprintf(line, sizeof(line), "%3d:%02d", t / 60, t % 60);
	            rtgui_dc_draw_text(dc, line, &rect);
			}
        }

		RTGUI_WIDGET_FOREGROUND(widget) = RTGUI_RGB(82, 199, 16);
		rtgui_dc_draw_hline(dc, 14, 226, 75);

		RTGUI_WIDGET_FOREGROUND(widget) = saved;

		if (player_mode == PLAYER_PLAY_FILE)
		{
			char line[32];
			rt_uint32_t index;
			struct play_item* item;

			rect.x1 = 20; rect.y1 = 150;
			rect.x2 = 170; rect.y2 = 168;
			for (index = 0; index < play_list_items() && index < 8; index ++)
			{
				item = play_list_item(index);
				rtgui_dc_draw_text(dc, item->title, &rect);

	            rect.x1 = 172; rect.x2 = 220;
				rt_snprintf(line, sizeof(line), "%3d:%02d", item->duration / 60, item->duration % 60);
	            rtgui_dc_draw_text(dc, line, &rect);

				/* move to next item */
				rect.x1 = 20; rect.x2 = 170;
				rect.y1 += 18; rect.y2 += 18;
			}
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
			case RTGUIK_RIGHT:
                if (player_mode == PLAYER_PLAY_FILE && play_list_items() > 0)
                {
					player_stop_req();
					next_step = PLAYER_STEP_NEXT;
                }
                break;

			case RTGUIK_LEFT:
                if (player_mode == PLAYER_PLAY_FILE && play_list_items() > 0)
                {
					player_stop_req();
					next_step = PLAYER_STEP_PREV;
                }
				break;

			case RTGUIK_RETURN:
				if (player_is_playing() == RT_TRUE)
				{
					player_stop_req();
					next_step = PLAYER_STEP_STOP;
				}
				else
				{
					if ((player_mode == PLAYER_STOP) && (play_list_items() > 0))
					{
						next_step = PLAYER_STEP_NEXT;
						player_play_file(play_list_current_item());
					}
				}
				break;

			case RTGUIK_DOWN:
                rtgui_view_show(RTGUI_VIEW(function_view), RT_FALSE);
				break;
			}
		}
		return RT_FALSE;
	}
	else if (event->type == RTGUI_EVENT_COMMAND)
	{
		struct rtgui_event_command* ecmd = (struct rtgui_event_command*)event;

		switch (ecmd->command_id)
		{
		case PLAYER_REQUEST_PLAY_SINGLE_FILE:
		case PLAYER_REQUEST_PLAY_LIST:
			rtgui_timer_start(info_timer);
			break;

		case PLAYER_REQUEST_STOP:
		{
			rtgui_timer_stop(info_timer);

			switch (next_step)
			{
			case PLAYER_STEP_STOP:
// #define TEST_MODE
#ifdef TEST_MODE
				player_play_file(play_list_start());
				next_step = PLAYER_STEP_STOP;
#else
			{
				struct rtgui_dc* dc;
				rtgui_color_t saved;
	            rtgui_image_t *button;
	            rtgui_rect_t  play_rect;

				player_mode = PLAYER_STOP;

				dc = rtgui_dc_begin_drawing(widget);
				if (dc == RT_NULL) return RT_FALSE;

				player_update_tag_info(dc);

				saved = RTGUI_WIDGET_FOREGROUND(widget);

				RTGUI_WIDGET_FOREGROUND(widget) = RTGUI_RGB(82, 199, 16);
				rtgui_dc_draw_hline(dc, 14, 226, 75);

				/* update play button */
				button = rtgui_image_create_from_mem("hdc", stop_hdh, sizeof(stop_hdh), RT_FALSE);
	            play_rect.x1 = 32; play_rect.y1 = 92;
	            play_rect.x2 = 61; play_rect.y2 = 114;
	            rtgui_image_blit(button, dc, &play_rect);
	            rtgui_image_destroy(button);

				RTGUI_WIDGET_FOREGROUND(widget) = saved;
				rtgui_dc_end_drawing(dc);
			}
#endif
				break;

			case PLAYER_STEP_NEXT:
				if (play_list_is_end() == RT_TRUE)
				{
					struct rtgui_dc* dc;
					rtgui_color_t saved;
		            rtgui_image_t *button;
		            rtgui_rect_t  play_rect;

					/* set stat */
					next_step = PLAYER_STEP_STOP;
					player_mode = PLAYER_STOP;

					/* update UI */
					dc = rtgui_dc_begin_drawing(widget);
					if (dc == RT_NULL) return RT_FALSE;

					player_update_tag_info(dc);

					saved = RTGUI_WIDGET_FOREGROUND(widget);

					RTGUI_WIDGET_FOREGROUND(widget) = RTGUI_RGB(82, 199, 16);
					rtgui_dc_draw_hline(dc, 14, 226, 75);

					/* update play button */
					button = rtgui_image_create_from_mem("hdc",
		                stop_hdh, sizeof(stop_hdh), RT_FALSE);
		            play_rect.x1 = 32; play_rect.y1 = 92;
		            play_rect.x2 = 61; play_rect.y2 = 114;
		            rtgui_image_blit(button, dc, &play_rect);
		            rtgui_image_destroy(button);

					RTGUI_WIDGET_FOREGROUND(widget) = saved;
					rtgui_dc_end_drawing(dc);
				}
				else
				{
	                player_play_file(play_list_next());
					next_step = PLAYER_STEP_NEXT;
				}
				break;

			case PLAYER_STEP_PREV:
				player_play_file(play_list_prev());
				next_step = PLAYER_STEP_NEXT;
				break;
			};
		}
			break;

		default:
			break;
		}

		return RT_FALSE;
	}

	return rtgui_view_event_handler(widget, event);
}

rt_bool_t player_workbench_event_handler(rtgui_widget_t *widget, rtgui_event_t *event)
{
    if (event->type == RTGUI_EVENT_KBD)
    {
        struct rtgui_event_kbd* ekbd = (struct rtgui_event_kbd*)event;
        if ((ekbd->type == RTGUI_KEYUP) && ekbd->key == RTGUIK_HOME)
        {
            /* active home view */
            if (workbench->current_view != home_view)
            {
                rtgui_view_show(home_view, RT_FALSE);
                return RT_FALSE;
            }
        }
    }

    return rtgui_workbench_event_handler(widget, event);
}

static void player_entry(void* parameter)
{
	rt_mq_t mq;
	rtgui_rect_t rect;

	mq = rt_mq_create("ply_ui", 256, 4, RT_IPC_FLAG_FIFO);
	rtgui_thread_register(rt_thread_self(), mq);

	/* create information timer */
	info_timer = rtgui_timer_create(RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC, info_timer_timeout, RT_NULL);

	time_bg_image = rtgui_image_create_from_mem("xpm", (rt_uint8_t *) time_bg_xpm, sizeof(time_bg_xpm), RT_TRUE);

	workbench = rtgui_workbench_create("main", "workbench");
	if (workbench == RT_NULL) return;
	rtgui_widget_set_event_handler(RTGUI_WIDGET(workbench), player_workbench_event_handler);

    /* add home view */
	home_view = rtgui_view_create("Home");
	rtgui_widget_set_event_handler(RTGUI_WIDGET(home_view), home_view_event_handler);

	rtgui_workbench_add_view(workbench, home_view);
	/* this view can be focused */
	RTGUI_WIDGET(home_view)->flag |= RTGUI_WIDGET_FLAG_FOCUSABLE;
	/* set widget focus */
	rtgui_widget_focus(RTGUI_WIDGET(home_view));

	rtgui_view_show(home_view, RT_FALSE);

    /* add function view */
	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);
	function_view = rtgui_list_view_create(function_list,
		sizeof(function_list)/sizeof(struct rtgui_list_item),
		&rect);
	rtgui_workbench_add_view(workbench, RTGUI_VIEW(function_view));

	rtgui_workbench_event_loop(workbench);

	rtgui_thread_deregister(rt_thread_self());
	rt_mq_delete(mq);
}

void player_notify_play(void)
{
    struct rtgui_event_command ecmd;
    RTGUI_EVENT_COMMAND_INIT(&ecmd);
    ecmd.type = RTGUI_CMD_USER_INT;
    ecmd.command_id = PLAYER_REQUEST_PLAY_SINGLE_FILE;

    rtgui_thread_send(player_ui_tid, &ecmd.parent, sizeof(ecmd));
}

void player_notify_stop()
{
    struct rtgui_event_command ecmd;
    RTGUI_EVENT_COMMAND_INIT(&ecmd);
    ecmd.type = RTGUI_CMD_USER_INT;
    ecmd.command_id = PLAYER_REQUEST_STOP;

    rtgui_thread_send(player_ui_tid, &ecmd.parent, sizeof(ecmd));
}

void player_ui_init()
{
	player_ui_tid = rt_thread_create("ply_ui", player_entry, RT_NULL,
		0x800, 25, 5);
	if (player_ui_tid != RT_NULL)
		rt_thread_startup(player_ui_tid);
}

