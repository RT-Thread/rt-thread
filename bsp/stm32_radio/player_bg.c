#include "player_bg.h"
#include "player_ui.h"

#include <string.h>

static rt_mq_t player_thread_mq;
rt_bool_t is_playing = RT_FALSE;

rt_bool_t player_is_playing()
{
	return is_playing;
}

void player_play_file(const char* fn)
{
    struct player_request request;
    request.type = PLAYER_REQUEST_PLAY_SINGLE_FILE;
    strncpy(request.fn, fn, sizeof(request.fn));

    /* send to message queue */
    rt_mq_send(player_thread_mq, (void*)&request, sizeof(struct player_request));
}

void player_stop()
{
	is_playing = RT_FALSE;
}

void player_thread(void* parameter)
{
	rt_err_t result;
	struct player_request request;

	while(1)
	{
		/* get request from message queue */
		result = rt_mq_recv(player_thread_mq, (void*)&request,
			sizeof(struct player_request), RT_WAITING_FOREVER);
		if (result == RT_EOK)
		{
			switch (request.type)
			{
			case PLAYER_REQUEST_PLAY_SINGLE_FILE:
				if ((strstr(request.fn, ".mp3") != RT_NULL) ||
					(strstr(request.fn, ".MP3") != RT_NULL))
				{
					is_playing = RT_TRUE;
					player_notify_play();

				    /* get music tag information */
					mp3(request.fn);
					
					player_notify_stop();
					is_playing = RT_FALSE;
				}
				else if ((strstr(request.fn, ".wav") != RT_NULL) ||
					(strstr(request.fn, ".WAV") != RT_NULL))
				{
					is_playing = RT_TRUE;
					wav(request.fn);
					is_playing = RT_FALSE;
				}
				break;
			}
		}
	}
}

void player_init()
{
    rt_thread_t tid;

	/* create player thread */
	player_thread_mq = rt_mq_create("player", sizeof(struct player_request),
		8, RT_IPC_FLAG_FIFO);
	RT_ASSERT(player_thread_mq != RT_NULL);

	tid = rt_thread_create("ply_bg", player_thread, RT_NULL,
		2048, 20, 5);
	if (tid != RT_NULL) rt_thread_startup(tid);
	
	player_ui_init();
}
