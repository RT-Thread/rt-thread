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
#include "drv_jpeg.h"

#define PLAYER_SOUND_SIZE_DEFAULT     0
#define PLAYER_SONG_NUM_MAX          20
#define PLAYER_SONG_NAME_LEN_MAX     32

enum PLAYER_STATUS
{
    PLAYER_IDLE,
    PLAYER_READY,   //准备播放
    PLAYER_RUNNING, //正在播放
    PLAYER_STOP,    //播放停止
    PLAYER_DELETE,  //删除资源
    PLAYER_LAST,    //播放上一首
    PLAYER_NEXT,    //播放下一首
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
    enum PLAYER_STATUS  status;             //当前播放状态
    int16_t             volume;             //声音大小
    uint8_t             song_current;       //正在播放的视频
    uint8_t             video_num;          //视频总数
    uint16_t            song_time_pass;     //已经播放的时间
    uint16_t            song_time_all;      //总播放时间
    char  *             video_list[PLAYER_SONG_NUM_MAX];    //列表
    char                video_name[PLAYER_SONG_NAME_LEN_MAX];

    rt_sem_t            sem_play;           //用于播放状态控制的信号量
    rt_thread_t         play_thread;        //播放的线程

    struct audio_ops    *audio;
    decode_drv_t        *decode;
};
typedef struct player *player_t;

int player_add_song(player_t player, void *song);   //添加歌曲到歌曲列表
int player_start(player_t player);                  //初始化
int player_control(player_t player, int cmd, void *arg);
int player_show(player_t player);                   //打印歌单和当前进度
int player_delete(player_t player);

#endif
