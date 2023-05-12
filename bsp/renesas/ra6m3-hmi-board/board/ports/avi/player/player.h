/*
* Copyright (c) 2006-2023, RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date           Author       Notes
* 2023-03-29     Rbb666       the first version
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <rtthread.h>
#include <rthw.h>

#include "drv_jpeg.h"

#define PLAYER_SOUND_SIZE_DEFAULT     0
#define PLAYER_SONG_NUM_MAX          20
#define PLAYER_SONG_NAME_LEN_MAX     32

enum PLAYER_STATUS
{
    PLAYER_IDLE,
    PLAYER_READY,
    PLAYER_RUNNING,
    PLAYER_STOP,
    PLAYER_DELETE,
    PLAYER_LAST,
    PLAYER_NEXT,
};
enum PLAYER_CMD
{
    PLAYER_CMD_INIT,
    PLAYER_CMD_PLAY,
    PLAYER_CMD_STOP,
    PLAYER_CMD_LAST,
    PLAYER_CMD_NEXT,
    PLAYER_CMD_SET_VOL,
    PLAYER_CMD_GET_VOL,
    PLAYER_CMD_GET_STATUS
};
enum AUDIO_OPS_CMD
{
    AUDIO_OPS_CMD_SET_VOL
};
enum DECODE_OPS_CMD
{
    DECODE_OPS_CMD_GET_NAME,
    DECODE_OPS_CMD_GET_LEN
};

struct audio_ops
{
    int (*init)(void);
    int (*open)(void);
    int (*close)(void);
    int (*control)(int cmd, void *arg);
    int (*write)(void *buffer, int size);
};

struct player
{
    enum PLAYER_STATUS  status;             /*state*/
    int16_t             volume;             /*Sound Size*/
    uint8_t             song_current;       /*Playing video*/
    uint8_t             video_num;          /*Total number of videos*/
    uint16_t            song_time_pass;     /*Played time*/
    uint16_t            song_time_all;      /*Played all time*/
    char  *             video_list[PLAYER_SONG_NUM_MAX];
    char                video_name[PLAYER_SONG_NAME_LEN_MAX];

    rt_sem_t            sem_play;
    rt_thread_t         play_thread;

    struct audio_ops    *audio;
    decode_drv_t        *decode;
};
typedef struct player *player_t;

int player_add_song(player_t player, void *song);
int player_start(player_t player);
int player_control(player_t player, int cmd, void *arg);
int player_show(player_t player);
int player_delete(player_t player);

#endif
