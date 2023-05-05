#include "player.h"
#include "avifile.h"
#include "pwm_audio.h"

#include <dfs_file.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include "lv_demo_video.h"
#include "drv_jpeg.h"

#define DBG_TAG    "player"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define T_vids  _REV(0x30306463)
#define T_auds  _REV(0x30317762)

#define __Map(x, in_min, in_max, out_min, out_max) \
    (((x) - (in_min)) * ((out_max) - (out_min)) / ((in_max) - (in_min)) + (out_min))

struct avi_file_info
{
    uint32_t Strsize;
    uint32_t Strtype;
    size_t BytesRD;
    uint32_t cur_time;
    uint32_t alltime;
} avi_file;

extern AVI_TypeDef AVI_file;
static uint8_t *v_pbuffer;

static uint32_t _REV(uint32_t value)
{
    return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) << 8 |
           (value & 0x00FF0000U) >> 8 | (value & 0xFF000000U) >> 24;
}

static void audio_init(player_t player)
{
    pwm_audio_config_t pac;
    pac.duty_resolution    = 10;
    pac.gpio_num_left      = 1;
    pac.gpio_num_right     = -1;
    pac.ringbuf_len        = 1024 * 8;

    pwm_audio_init(&pac);

    /* set default volume:-16 -- +16*/
    pwm_audio_set_volume(player->volume);
}

static uint32_t read_video_frame(int fd, uint8_t *buffer, uint32_t length, uint32_t *fourcc)
{
    AVI_CHUNK_HEAD head;
    read(fd, &head, sizeof(AVI_CHUNK_HEAD));
    if (head.FourCC)
    {
        /* code */
    }
    *fourcc = head.FourCC;
    if (head.size % 2)
    {
        head.size++;
    }
    if (length < head.size)
    {
        rt_kprintf("frame size too large\n");
        return 0;
    }

    read(fd, buffer, head.size);
    return head.size;
}

static int video_start_parser(player_t player, int fd, char *filename)
{
    int ret;
    uint32_t alltime;

    fd = open(filename, O_WRONLY);

    avi_file.BytesRD = read(fd, v_pbuffer, 20480);
    ret = AVI_Parser(v_pbuffer, avi_file.BytesRD);
    if (0 > ret)
    {
        LOG_E("parse failed (%d)\n", ret);
        return RT_ERROR;
    }

    /* Audio Init */
    audio_init(player);
    pwm_audio_set_param(AVI_file.auds_sample_rate, AVI_file.auds_bits, AVI_file.auds_channels);

    alltime = (AVI_file.avi_hd.avih.us_per_frame / 1000) * AVI_file.avi_hd.avih.total_frames;
    alltime /= 1000; /* s */
    player->song_time_all = alltime;
    LOG_I("video total time:%02d:%02d:%02d\n", alltime / 3600, (alltime % 3600) / 60, alltime % 60);

    lseek(fd, AVI_file.movi_start, SEEK_SET);
    avi_file.Strsize = read_video_frame(fd, v_pbuffer, DCODE_BUFFER_SIZE, &avi_file.Strtype);
    avi_file.BytesRD = avi_file.Strsize + 8;

    return fd;
}

static void search_files(player_t player, const char *dir_path, const char *ext)
{
    struct dirent *dirp;

    DIR *dir = opendir(dir_path);
    if (dir == NULL)
    {
        LOG_E("open directory error!");
        return;
    }
    while ((dirp = readdir(dir)))
    {
        if (dirp->d_type == DT_DIR)
        {
            if (rt_strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            {
                continue;
            }
            char subdir_path[64];
            rt_snprintf(subdir_path, sizeof(subdir_path), "%s/%s", dir_path, dirp->d_name);
            search_files(player, subdir_path, ext);
        }
        else
        {
            char *file_ext = strrchr(dirp->d_name, '.');
            if (file_ext != NULL && strcmp(file_ext, ext) == 0)
            {
                char file_path[64];
                rt_snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, dirp->d_name);
                LOG_I("%s\n", file_path);

                player->video_list[player->video_num] = rt_strdup(file_path);
                LOG_E("video_list[%d]:%s", player->video_num, player->video_list[player->video_num]);
                player->video_num ++;
            }
        }
    }
    closedir(dir);
}

static uint8_t add_video_player(player_t player)
{
    uint8_t video_index = 0;

    if (player->video_num == 0)
    {
        player->video_list[player->song_current] = rt_strdup(player->video_name);
        LOG_I("Add first res to player list:%s", player->video_list[player->song_current]);
        player->song_current ++;
        player->video_num++;
    }
    else
    {
        rt_bool_t flag = RT_FALSE;
        /* find in list*/
        for (int index = 0; index < player->video_num; index++)
        {
            char *video_name = player->video_list[index];
            if (rt_strcmp(player->video_name, video_name))
            {
                flag = RT_TRUE;
            }
            else
            {
                flag = RT_FALSE;
                video_index = index;
                LOG_I("Find name to the list,index:%d", video_index);
                break;
            }
        }
        if (flag)
        {
            player->video_list[player->song_current] = rt_strdup(player->video_name);
            LOG_I("Add [%s] to player list", player->video_list[player->song_current]);
            player->song_current ++;
            player->video_num ++;
            /* free currnet player,to play next video */
            player_delete(player);
        }
    }
    /* show player */
    player_show(player);

    return video_index;
}

int player_show(player_t player)
{
    uint8_t i;
    uint16_t percent;

    rt_kprintf("*********** video Player ***********\n");

    /* print now video */
    for (i = 0; i < player->video_num; i++)
    {
        rt_kprintf("%02d. %s\n", i + 1, (char *)player->video_list[i]);
    }

    /* print now player status */
    if (PLAYER_RUNNING == player->status)
    {
        rt_kprintf("<---  current player:");
    }
    else
    {
        rt_kprintf("<---  stop player:");
    }

    /* print current player */
    rt_kprintf("%s", (char *)player->video_list[player->song_current]);
    rt_kprintf("--->\n");

    /*  print player process */
    percent = player->song_time_pass * 100 / player->song_time_all;
    rt_kprintf("Player Progress:%02d%%  Volume level:%02d%%\n", percent, player->volume);
    rt_kprintf("***********************************\n");

    return 0;
}

static int player_init(player_t player)
{
    rt_uint32_t level;

    if (player->status != PLAYER_RUNNING)
    {
        level = rt_hw_interrupt_disable();

        player->status = PLAYER_READY;

        player->song_current = add_video_player(player) + 1;

        rt_hw_interrupt_enable(level);

        rt_sem_release(player->sem_play);
    }

    return 0;
}

static int player_play(player_t player)
{
    rt_uint32_t level;

    if (player->status != PLAYER_RUNNING)
    {
        level = rt_hw_interrupt_disable();

        player->status = PLAYER_RUNNING;

        rt_hw_interrupt_enable(level);

        rt_sem_release(player->sem_play);
    }

    return 0;
}

static int player_stop(player_t player)
{
    rt_uint32_t level;

    if (player->status == PLAYER_RUNNING)
    {
        level = rt_hw_interrupt_disable();

        player->status = PLAYER_STOP;

        rt_hw_interrupt_enable(level);
    }

    return 0;
}

int player_delete(player_t player)
{
    rt_uint32_t level;

    if (player->status == PLAYER_RUNNING)
    {
        level = rt_hw_interrupt_disable();

        player->status = PLAYER_DELETE;

        rt_hw_interrupt_enable(level);
    }

    return 0;
}

static int player_last(player_t player)
{
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();

    if (player->song_current > 1)
    {
        player->song_current --;
    }
    else
    {
        player->song_current = player->video_num;
    }

    rt_hw_interrupt_enable(level);

    player->status = PLAYER_LAST;

    level = rt_hw_interrupt_disable();

    rt_hw_interrupt_enable(level);

    return 0;
}

static int player_next(player_t player)
{
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();

    if (player->song_current < player->video_num)
    {
        player->song_current ++;
    }
    else
    {
        player->song_current = 1;
    }

    rt_hw_interrupt_enable(level);

    player->status = PLAYER_NEXT;

    level = rt_hw_interrupt_disable();

    rt_hw_interrupt_enable(level);

    return 0;
}

int player_control(player_t player, int cmd, void *arg)
{
    rt_uint32_t level;

    switch (cmd)
    {
    case PLAYER_CMD_INIT:
        LOG_I("Rec res name:%s len:%d", (char *)arg, rt_strlen(arg));
        rt_memset(player->video_name, 0x00, rt_strlen(arg));
        rt_strcpy(player->video_name, arg);
        player_init(player);
        break;
    case PLAYER_CMD_PLAY:
        player_play(player);
        break;
    case PLAYER_CMD_STOP:
        player_stop(player);
        break;
    case PLAYER_CMD_LAST:
        player_last(player);
        break;
    case PLAYER_CMD_NEXT:
        player_next(player);
        break;
    case PLAYER_CMD_SET_VOL:
        level = rt_hw_interrupt_disable();
        player->volume = *(int16_t *)arg;
        rt_hw_interrupt_enable(level);
        pwm_audio_set_volume(player->volume);
        break;
    case PLAYER_CMD_GET_VOL:
        *(uint8_t *)arg = player->volume;
        break;
    case PLAYER_CMD_GET_STATUS:
        *(uint8_t *)arg = player->status;
        break;
    }
    return 0;
}

static void player_entry(void *parameter)
{
    int fd = -1;
    int32_t process;
    player_t player = (player_t)parameter;

    while (1)
    {
        if (player->status == PLAYER_READY)
        {
            fd = video_start_parser(player, fd, player->video_list[player->song_current - 1]);
            LOG_I("Player:%s ready decode\n", player->video_list[player->song_current - 1]);

            player->status = PLAYER_RUNNING;
        }
        if (player->status == PLAYER_RUNNING)
        {
            avi_file.cur_time = ((float)avi_file.BytesRD / AVI_file.movi_size) * avi_file.alltime;

            if (avi_file.Strtype == T_vids)
            {
                JPEG_Draw_frame(player->decode, v_pbuffer, 0x00, 0x00);
            }
            /* audio output */
            else if (avi_file.Strtype == T_auds)
            {
                size_t cnt;
                pwm_audio_write((uint8_t *)v_pbuffer, avi_file.Strsize, &cnt, 500);
            }
            else
            {
                LOG_E("Unknow frame\n");
                break;
            }

            /* read frame */
            avi_file.Strsize = read_video_frame(fd, v_pbuffer, DCODE_BUFFER_SIZE, &avi_file.Strtype);
            avi_file.BytesRD += avi_file.Strsize + 8;
            player->song_time_pass = ((double)avi_file.BytesRD / AVI_file.movi_size) * player->song_time_all;

            process = __Map((int32_t)player->song_time_pass, 0, player->song_time_all, 0, 100);
            set_audio_wave_value(process);

            /* if video was play over,play next video */
            if (avi_file.BytesRD >= AVI_file.movi_size)
            {
                set_audio_wave_value(0);
                player_show(player);
                player_next(player);
            }
        }
        if (player->status == PLAYER_STOP)
        {
            LOG_I("Stop player");

            pwm_audio_stop();

            rt_sem_take(player->sem_play, RT_WAITING_FOREVER);

            pwm_audio_start();
        }
        if (player->status == PLAYER_DELETE)
        {
            close(fd);
            pwm_audio_deinit();
            player->status = PLAYER_IDLE;
            LOG_I("Free %s resources", player->video_list[player->song_current - 1]);
        }
        if (player->status == PLAYER_LAST)
        {
            close(fd);
            pwm_audio_deinit();
            player->status = PLAYER_READY;
            LOG_I("Free %s resources", player->video_list[player->song_current - 1]);
        }
        if (player->status == PLAYER_NEXT)
        {
            close(fd);
            pwm_audio_deinit();
            player->status = PLAYER_READY;
            LOG_I("Free %s resources", player->video_list[player->song_current - 1]);
        }
        if (player->status == PLAYER_IDLE)
        {
            rt_sem_take(player->sem_play, RT_WAITING_FOREVER);
        }
    }
}

int player_start(player_t player)
{
    static rt_uint8_t inited = 0;

    if (inited == 1)
    {
        return -RT_ERROR;
    }

    v_pbuffer = rt_malloc(DCODE_BUFFER_SIZE);
    RT_ASSERT(v_pbuffer != NULL)
    rt_memset(v_pbuffer, 0x00, DCODE_BUFFER_SIZE);

    /* read filesystem */
    search_files(player, "/", ".avi");

    player->status = PLAYER_IDLE;
    player->volume = PLAYER_SOUND_SIZE_DEFAULT;
    player->song_current = 0;
    player->song_time_pass = 0;

    player->sem_play = rt_sem_create("sem_play", 0, RT_IPC_FLAG_FIFO);
    if (player->sem_play == RT_NULL)
    {
        return -RT_ERROR;
    }

    player->play_thread = rt_thread_create("player",
                                           player_entry, player,
                                           2 * 1024, 18, 20);
    if (player->play_thread != RT_NULL)
    {
        rt_thread_startup(player->play_thread);
    }
    else
    {
        rt_sem_delete(player->sem_play);
        return -RT_ERROR;
    }

    inited = 1;

    return 0;
}
