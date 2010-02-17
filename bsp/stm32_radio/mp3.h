#ifndef __MP3_H__
#define __MP3_H__

#include "player_ui.h"

void mp3_get_info(const char* filename, struct tag_info* info);

void mp3(char* filename);
void http_mp3(char* url);
void ice_mp3(char* url);

#endif
