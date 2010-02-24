#ifndef __PLAYER_BG_H__
#define __PLAYER_BG_H__

#include <rtthread.h>

enum PLAYER_REQUEST_TYPE
{
	PLAYER_REQUEST_PLAY_SINGLE_FILE,
	PLAYER_REQUEST_PLAY_LIST,
	PLAYER_REQUEST_STOP,
	PLAYER_REQUEST_FREEZE,
};

struct player_request
{
	enum PLAYER_REQUEST_TYPE type;
	char fn[64];
};

/* get player background status */
rt_bool_t player_is_playing(void);
/* player background thread init */
void player_init(void);

/* send a stop request to player background thread */
void player_stop_req(void);
/* send a play request to player background thread */
void player_play_req(const char* fn);

#endif

