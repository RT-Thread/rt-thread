#include <rtgui/rtgui.h>
#include <rtgui/image.h>
#include <rtgui/rtgui_system.h>

#include <rtgui/widgets/view.h>
#include <rtgui/widgets/workbench.h>
#include <string.h>

#include <dfs_posix.h>

#include "player_ui.h"
#include "player_bg.h"
#include "play_list.h"

#include "listview.h"
#include "filelist.h"

#include "play.hdh"
#include "stop.hdh"

static rtgui_image_t *background = RT_NULL;

static struct rtgui_view* function_view;
static struct rtgui_view* home_view;
static struct rtgui_workbench* workbench;
static rtgui_timer_t* info_timer;
static rt_thread_t player_ui_tid = RT_NULL;
static enum PLAYER_MODE player_mode = PLAYER_STOP;
static enum PLAYER_STEP next_step = PLAYER_STEP_STOP;
static struct tag_info tinfo;

void player_set_position(rt_uint32_t position)
{
    tinfo.position = position / (tinfo.bit_rate / 8);
}

void info_timer_timeout(rtgui_timer_t* timer, void* parameter)
{
	struct rtgui_dc* dc;
	rtgui_color_t saved;

	dc = rtgui_dc_begin_drawing(RTGUI_WIDGET(home_view));
	if (dc == RT_NULL) return ;

	saved = RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view));

	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view)) = RTGUI_RGB(206, 231, 255);
	rtgui_dc_draw_hline(dc, 14, 14  + (tinfo.position * 212) / tinfo.duration, 75);

	RTGUI_WIDGET_FOREGROUND(RTGUI_WIDGET(home_view)) = saved;
	rtgui_dc_end_drawing(dc);
}

rt_uint32_t read_line(int fd, char* line, rt_uint32_t line_size)
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

	rt_kprintf("line %s\n", line);
    return length;
}

static void player_update_tag_info(struct rtgui_dc* dc)
{
	rtgui_rect_t rect;
    char line[32];
	rtgui_color_t saved;

	saved = rtgui_dc_get_color(dc);
	rtgui_dc_set_color(dc, black);

	rect.x1 = 0; rect.y1 = 0;
	rect.x2 = 240; rect.y2 = 65;
	/* draw background */
    background = rtgui_image_create_from_file("hdc",
        "/resource/bg.hdc", RT_FALSE);
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
		rt_snprintf(line, sizeof(line),
			"网络收音机");
	    rtgui_dc_draw_text(dc, line, &rect);
	}
	else
	    rtgui_dc_draw_text(dc, tinfo.title, &rect);

    rect.x1 = 28; rect.y1 = 39;
    rect.x2 = 220; rect.y2 = 59;
	if (player_mode == PLAYER_STOP)
	{
		rt_snprintf(line, sizeof(line),
			"radio.rt-thread.org");
	    rtgui_dc_draw_text(dc, line, &rect);
	}
	else
	    rtgui_dc_draw_text(dc, tinfo.artist, &rect);

	if ((tinfo.duration != 0) && player_mode != PLAYER_STOP)
	{
        rect.x1 = rect.x2 - 64;
		rt_snprintf(line, sizeof(line), "%02d:%02d:%02d",
			tinfo.duration / 3600, tinfo.duration / 60, tinfo.duration % 60);
        rtgui_dc_draw_text(dc, line, &rect);
	}

	rtgui_dc_set_color(dc, saved);
}

void play_mp3_file(const char* fn)
{
	struct rtgui_dc* dc;
	rtgui_color_t saved;

    /* get music tag information */
    mp3_get_info(fn, &tinfo);
    if (tinfo.title[0] == '\0')
        rt_snprintf(tinfo.title, sizeof(tinfo.title), "<未知名音乐>");
	
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

	rt_kprintf("play file: %s\n", fn);
    player_play_file(fn);
}

void function_filelist(void* parameter)
{
	rtgui_rect_t rect;
	filelist_view_t *view;

	rtgui_widget_get_rect(RTGUI_WIDGET(workbench), &rect);
	view = filelist_view_create(workbench, "/", "*.*", &rect);
	if (view != RT_NULL)
	{
	    if (rtgui_view_show(RTGUI_VIEW(view), RT_TRUE) == RTGUI_MODAL_OK)
	    {
			char fn[64];

            /* get open file */
            rt_snprintf(fn, 64, "%s/%s", view->current_directory,
                view->items[view->current_item].name);

            if (strstr(view->items[view->current_item].name , ".mp3") != RT_NULL ||
                strstr(view->items[view->current_item].name , ".MP3") != RT_NULL)
            {
				/* clear old play list */
				play_list_clear();
				play_list_append(fn);

			    player_mode = PLAYER_PLAY_FILE;
				next_step = PLAYER_STEP_STOP;
				play_mp3_file(play_list_start());
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
                            if (line[0] != '/')
                            {
                                rt_snprintf(fn, sizeof(fn),
                                    "%s/%s", view->current_directory, line);
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
		                play_mp3_file(play_list_start());
					}
                }
            }
            else if (strstr(view->items[view->current_item].name , ".wav") != RT_NULL ||
                strstr(view->items[view->current_item].name , ".WAV") != RT_NULL)
            {
            }
	    }

		/* destroy view */
		filelist_view_destroy(view);
	}

	return;
}

void function_device(void* parameter)
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

void function_player(void* parameter)
{
    rtgui_view_show(home_view, RT_FALSE);
	return;
}

void function_action(void* parameter)
{
	rt_kprintf("item action!\n");
	return;
}

struct list_item function_list[] =
{
	{"选择电台", RT_NULL, function_action, RT_NULL},
	{"更新电台", RT_NULL, function_action, RT_NULL},
	{"播放文件", RT_NULL, function_filelist, RT_NULL},
	{"设备信息", RT_NULL, function_device, RT_NULL},
	{"选项设置", RT_NULL, function_action, RT_NULL},
	{"返回播放器", RT_NULL, function_player, RT_NULL},
};

static rt_bool_t home_view_event_handler(struct rtgui_widget* widget, struct rtgui_event* event)
{
	if (event->type == RTGUI_EVENT_PAINT)
	{
		struct rtgui_dc* dc;
		struct rtgui_rect rect;
		rtgui_color_t saved;

		dc = rtgui_dc_begin_drawing(widget);
		if (dc == RT_NULL) return RT_FALSE;
		rtgui_widget_get_rect(widget, &rect);
		saved = RTGUI_WIDGET_FOREGROUND(widget);

		/* draw background */
	    background = rtgui_image_create_from_file("hdc",
	        "/resource/bg.hdc", RT_FALSE);
		if (background != RT_NULL)
		{
            rtgui_image_t *play;
            rtgui_rect_t  play_rect;

            rtgui_image_blit(background, dc, &rect);
			rtgui_image_destroy(background);

			background = RT_NULL;

			if (player_mode == PLAYER_STOP)
				play = rtgui_image_create_from_mem("hdc",
	                stop_hdh, sizeof(stop_hdh), RT_FALSE);
			else
				play = rtgui_image_create_from_mem("hdc",
	                play_hdh, sizeof(play_hdh), RT_FALSE);
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
				rt_snprintf(line, sizeof(line),
					"网络收音机");
			    rtgui_dc_draw_text(dc, line, &rect);
			}
			else
			    rtgui_dc_draw_text(dc, tinfo.title, &rect);

            rect.x1 = 28; rect.y1 = 39;
            rect.x2 = 220; rect.y2 = 59;
			if (player_mode == PLAYER_STOP)
			{
				rt_snprintf(line, sizeof(line),
					"radio.rt-thread.org");
			    rtgui_dc_draw_text(dc, line, &rect);
			}
			else
			    rtgui_dc_draw_text(dc, tinfo.artist, &rect);

			if (tinfo.duration != 0)
			{
	            rect.x1 = rect.x2 - 64;
				rt_snprintf(line, sizeof(line), "%02d:%02d:%02d",
					tinfo.duration / 3600, tinfo.duration / 60, tinfo.duration % 60);
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
			rect.x2 = 220; rect.y2 = 168;
			for (index = 0; index < play_list_items() && index < 8; index ++)
			{
				item = play_list_item(index);
				rtgui_dc_draw_text(dc, item->title, &rect);

	            rect.x1 = rect.x2 - 64;
				rt_snprintf(line, sizeof(line), "%02d:%02d:%02d",
					item->duration / 3600,
					item->duration / 60,
					item->duration % 60);
	            rtgui_dc_draw_text(dc, line, &rect);

				/* move to next item */
				rect.x1 = 20;
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
					player_stop();
					next_step = PLAYER_STEP_NEXT;
                }
                break;
			case RTGUIK_LEFT:
                if (player_mode == PLAYER_PLAY_FILE && play_list_items() > 0)
                {
					player_stop();
					next_step = PLAYER_STEP_PREV;
                }
				break;

			case RTGUIK_RETURN:
				if (player_is_playing() == RT_TRUE)
				{
					player_stop();
					next_step = PLAYER_STEP_STOP;
				}
				else
				{
					if ((player_mode == PLAYER_STOP) && (play_list_items() > 0))
					{
						next_step = PLAYER_STEP_NEXT;
						play_mp3_file(play_list_current_item());
					}
				}
				break;

			case RTGUIK_DOWN:
                rtgui_view_show(function_view, RT_FALSE);
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
				button = rtgui_image_create_from_mem("hdc",
	                stop_hdh, sizeof(stop_hdh), RT_FALSE);
	            play_rect.x1 = 32; play_rect.y1 = 92;
	            play_rect.x2 = 61; play_rect.y2 = 114;
	            rtgui_image_blit(button, dc, &play_rect);
	            rtgui_image_destroy(button);
	
				RTGUI_WIDGET_FOREGROUND(widget) = saved;
				rtgui_dc_end_drawing(dc);
			}
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
	                play_mp3_file(play_list_next());
					next_step = PLAYER_STEP_NEXT;
				}
				break;

			case PLAYER_STEP_PREV:
				play_mp3_file(play_list_prev());
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
	info_timer = rtgui_timer_create(RT_TICK_PER_SECOND,
		RT_TIMER_FLAG_PERIODIC,
		info_timer_timeout, RT_NULL);

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
	function_view = (struct rtgui_view*)list_view_create(function_list,
		sizeof(function_list)/sizeof(struct list_item),
		&rect);
	rtgui_workbench_add_view(workbench, function_view);

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
		4096, 25, 5);
	if (player_ui_tid != RT_NULL)
		rt_thread_startup(player_ui_tid);
}
