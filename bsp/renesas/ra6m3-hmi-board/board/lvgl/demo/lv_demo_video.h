
#ifndef _LV_DEMO_VIDEO_H
#define _LV_DEMO_VIDEO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "lv_file_explorer.h"

typedef enum {
    LV_MEDIA_STATE_NORMAL,
    LV_MEDIA_STATE_PAUSE,
    LV_MEDIA_STATE_PLAY,
    LV_MEDIA_STATE_NEXT,
    LV_MEDIA_STATE_PREV,
} lv_mdeia_state_t;

typedef enum {
    LV_FILE_EXPLORER_OPEN,
    LV_FILE_EXPLORER_CLOSE,
} lv_file_btn_starte_t;

typedef enum {
    LV_MUSIC_PLAY,
    LV_MUSIC_STOP,
} play_btn_starte_t;

typedef struct
{
    lv_obj_t obj;
    char *cur_fn;
    lv_mdeia_state_t state;
} lv_media_obj_t;

LV_IMG_DECLARE(ui_img_prev_png);
LV_IMG_DECLARE(ui_img_next_png);
LV_IMG_DECLARE(ui_img_pause_png);
LV_IMG_DECLARE(ui_img_run_png);
LV_IMG_DECLARE(ui_img_indicator_ver_png);
LV_IMG_DECLARE(ui_img_audio_wave_1_png);

void set_audio_wave_value(int32_t value);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
