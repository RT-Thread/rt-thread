#ifndef __PLAYER_BG_H__
#define __PLAYER_BG_H__

#include <rtthread.h>

enum PLAYER_REQUEST_TYPE
{
	PLAYER_REQUEST_PLAY_SINGLE_FILE,
	PLAYER_REQUEST_PLAY_LIST,
	PLAYER_REQUEST_STOP,
	PLAYER_REQUEST_NEXT,
	PLAYER_REQUEST_PREV,
};

struct player_request
{
	enum PLAYER_REQUEST_TYPE type;

	char fn[64];
};

rt_bool_t player_is_playing(void);
void player_stop(void);

void player_play_list(const char** list);
void player_play_file(const char* fn);

#endif
