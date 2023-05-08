/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2023-03-09     Rbb666        First version
 */
#include <rtthread.h>
#include <lcd_port.h>
#include "lvgl.h"
#include "drv_jpeg.h"
#include "lv_demo_video.h"

#include "ui_helpers.h"
#include "ui_anim.h"
#include "player.h"

#define JPEG_WIDTH  400
#define JPEG_HEIGHT 240
#define DCODE_BUFFER_SIZE   (35 * 1024)

#define MY_CLASS &lv_media_class

lv_obj_t *win_obj;
lv_obj_t *avi_obj;
lv_obj_t *file_explorer_panel;
lv_obj_t *file_ImgButton;

lv_obj_t *ui_ImgButton1;
lv_obj_t *ui_ImgButton2;
lv_obj_t *ui_ImgButton3;
lv_obj_t *ui_Indicator_Left;
lv_obj_t *ui_Audio_Wave;

const lv_obj_class_t lv_media_class =
{
    .width_def = LV_SIZE_CONTENT,
    .height_def = LV_SIZE_CONTENT,
    .instance_size = sizeof(lv_media_obj_t),
    .base_class = &lv_obj_class
};

static rt_bool_t btn_state_change = RT_FALSE;
static rt_bool_t play_state_change = RT_FALSE;
static uint16_t lv_show_buffer[JPEG_WIDTH * JPEG_HEIGHT] BSP_ALIGN_VARIABLE(16);
struct player v_player;

static void func_button_create(lv_obj_t *parent);

void lv_media_set_state(lv_obj_t *obj, lv_mdeia_state_t state)
{
    lv_media_obj_t *media = (lv_media_obj_t *)obj;
    media->state = state;
}

lv_mdeia_state_t lv_media_get_state(lv_obj_t *obj, lv_mdeia_state_t state)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_media_obj_t *media = (lv_media_obj_t *)obj;

    return media->state;
}

void lv_media_set_fn(lv_obj_t *obj, char *fn)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_media_obj_t *fd = (lv_media_obj_t *)obj;

    uint16_t fn_len = strlen(fn);

    if ((!fn) || (fn_len == 0)) return;

    if (fd->cur_fn)
    {
        lv_mem_free(fd->cur_fn);
        fd->cur_fn = NULL;
    }

    fd->cur_fn = lv_mem_alloc(fn_len + 1);
    LV_ASSERT_MALLOC(fd->cur_fn);

    if (fd->cur_fn == NULL) return;
    strcpy(fd->cur_fn, fn);
}

char *lv_media_get_fn(lv_obj_t *obj)
{
    LV_ASSERT_OBJ(obj, MY_CLASS);

    lv_media_obj_t *media = (lv_media_obj_t *)obj;

    return media->cur_fn;
}

static void file_explorer_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *file_explorer = lv_event_get_target(e);
    lv_obj_t *file = lv_event_get_user_data(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        const char *path = lv_file_explorer_get_current_path(file_explorer);
        const char *fn = lv_file_explorer_get_selected_file_name(file_explorer);

        uint16_t path_len = strlen(path);
        uint16_t fn_len = strlen(fn);

        if ((path_len + fn_len) <= LV_FILE_EXPLORER_PATH_MAX_LEN)
        {
            char sel_fn[LV_FILE_EXPLORER_PATH_MAX_LEN];

            strcpy(sel_fn, path);
            strcat(sel_fn, fn);

            if (strstr(sel_fn, ".avi") == NULL)
                return;

            lv_media_set_fn(file, sel_fn);
            /* send event to take back file panel */
            lv_event_send(file_ImgButton, LV_EVENT_RELEASED, NULL);

            player_control(&v_player, PLAYER_CMD_INIT, sel_fn);

            /* delete button */
            lv_obj_del(file_ImgButton);
            lv_obj_del_delayed(file_explorer_panel, 1000);

            func_button_create(win_obj);
        }
    }
}

#define set_pause_picture lv_imgbtn_set_src(ui_ImgButton2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_pause_png, NULL)
#define set_play_picture lv_imgbtn_set_src(ui_ImgButton2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_run_png, NULL)

void Button_event(lv_event_t *e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    if (target == file_ImgButton)
    {
        if (event_code == LV_EVENT_RELEASED)
        {
            btn_state_change = !btn_state_change;

            btn_state_change == LV_FILE_EXPLORER_OPEN ?         \
            roll_out_Animation(file_explorer_panel, 0) :    \
            take_back_Animation(file_explorer_panel, 0);
            \
        }
    }
    // pause
    if (target == ui_ImgButton2)
    {
        if (event_code == LV_EVENT_RELEASED)
        {
            play_state_change = !play_state_change;
            play_state_change == LV_MUSIC_PLAY ?                                        \
            player_control(&v_player, PLAYER_CMD_PLAY, RT_NULL), set_play_picture :  \
            player_control(&v_player, PLAYER_CMD_STOP, RT_NULL), set_pause_picture;
            \
        }
    }
    // next
    if (target == ui_ImgButton1)
    {
        if (event_code == LV_EVENT_RELEASED)
        {
            if (v_player.status == PLAYER_STOP)
                player_control(&v_player, PLAYER_CMD_PLAY, RT_NULL);
            player_control(&v_player, PLAYER_CMD_NEXT, RT_NULL);
        }
    }
    // prev
    if (target == ui_ImgButton3)
    {
        if (event_code == LV_EVENT_RELEASED)
        {
            if (v_player.status == PLAYER_STOP)
                player_control(&v_player, PLAYER_CMD_PLAY, RT_NULL);
            player_control(&v_player, PLAYER_CMD_LAST, RT_NULL);
        }
    }
}

static void slider_event_cb(lv_event_t *event)
{
    int16_t volume;
    lv_obj_t *slider = lv_event_get_target(event);
    volume = lv_slider_get_value(slider);
    player_control(&v_player, PLAYER_CMD_SET_VOL, &volume);
}

static lv_obj_t *lv_media_page_create(lv_obj_t *parent)
{
    LV_LOG_INFO("begin");
    lv_obj_t *obj = lv_obj_class_create_obj(MY_CLASS, parent);
    lv_obj_class_init_obj(obj);
    return obj;
}

void file_explorer_create(lv_obj_t *parent)
{
    lv_obj_set_style_border_width(lv_scr_act(), 0, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_size(parent, LCD_WIDTH, LCD_HEIGHT);
    lv_obj_center(parent);

    file_explorer_panel = lv_file_explorer_create(parent);
    lv_obj_set_size(file_explorer_panel, 370, 200);
    lv_obj_center(file_explorer_panel);

    lv_file_explorer_set_sort(file_explorer_panel, LV_EXPLORER_SORT_NONE);
    lv_file_explorer_open_dir(file_explorer_panel, "/");

    lv_obj_add_event_cb(file_explorer_panel, file_explorer_event_cb, LV_EVENT_VALUE_CHANGED, parent);
}

static void file_ImgButton_create(lv_obj_t *parent)
{
    LV_IMG_DECLARE(file_icon);

    file_ImgButton = lv_imgbtn_create(parent);
    lv_imgbtn_set_src(file_ImgButton, LV_IMGBTN_STATE_RELEASED, NULL, &file_icon, NULL);
    lv_obj_set_size(file_ImgButton, 62, 62);
    lv_obj_align(file_ImgButton, LV_ALIGN_TOP_RIGHT, 0, 0);

    lv_obj_add_event_cb(file_ImgButton, Button_event, LV_EVENT_ALL, NULL);
}

static void func_button_create(lv_obj_t *parent)
{
    ui_ImgButton3 = lv_imgbtn_create(parent);
    lv_imgbtn_set_src(ui_ImgButton3, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_prev_png, NULL);
    lv_obj_set_width(ui_ImgButton3, 35);
    lv_obj_set_height(ui_ImgButton3, 35);
    lv_obj_set_x(ui_ImgButton3, 220);
    lv_obj_set_y(ui_ImgButton3, -69);
    lv_obj_set_align(ui_ImgButton3, LV_ALIGN_CENTER);

    ui_ImgButton1 = lv_imgbtn_create(parent);
    lv_imgbtn_set_src(ui_ImgButton1, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_next_png, NULL);
    lv_obj_set_width(ui_ImgButton1, 35);
    lv_obj_set_height(ui_ImgButton1, 35);
    lv_obj_set_x(ui_ImgButton1, 220);
    lv_obj_set_y(ui_ImgButton1, 56);
    lv_obj_set_align(ui_ImgButton1, LV_ALIGN_CENTER);

    ui_ImgButton2 = lv_imgbtn_create(parent);
    lv_imgbtn_set_src(ui_ImgButton2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_pause_png, NULL);
    lv_obj_set_width(ui_ImgButton2, 35);
    lv_obj_set_height(ui_ImgButton2, 35);
    lv_obj_set_x(ui_ImgButton2, 220);
    lv_obj_set_y(ui_ImgButton2, -7);
    lv_obj_set_align(ui_ImgButton2, LV_ALIGN_CENTER);

    btn1_comein_Animation(ui_ImgButton1, 0);
    btn2_comein_Animation(ui_ImgButton2, 0);
    btn3_comein_Animation(ui_ImgButton3, 0);

    lv_obj_add_event_cb(ui_ImgButton1, Button_event, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImgButton2, Button_event, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ImgButton3, Button_event, LV_EVENT_ALL, NULL);
}

static void sound_slider_create(lv_obj_t *parent)
{
    ui_Indicator_Left = lv_slider_create(parent);
    lv_slider_set_range(ui_Indicator_Left, -16, 16);
    lv_slider_set_mode(ui_Indicator_Left, LV_SLIDER_MODE_SYMMETRICAL);
    lv_obj_set_width(ui_Indicator_Left, 20);
    lv_obj_set_height(ui_Indicator_Left, 200);
    lv_obj_set_align(ui_Indicator_Left, LV_ALIGN_LEFT_MID);
    lv_obj_set_style_radius(ui_Indicator_Left, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Indicator_Left, lv_color_hex(0x272A33), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Indicator_Left, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Indicator_Left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Indicator_Left, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Indicator_Left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Indicator_Left, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Indicator_Left, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Indicator_Left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Indicator_Left, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Indicator_Left, 4, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Indicator_Left, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Indicator_Left, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Indicator_Left, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Indicator_Left, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Indicator_Left, &ui_img_indicator_ver_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Indicator_Left, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Indicator_Left, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Indicator_Left, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
}

static void lv_audio_wave_create(lv_obj_t *parent)
{
    ui_Audio_Wave = lv_slider_create(parent);
    lv_slider_set_value(ui_Audio_Wave, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(ui_Audio_Wave) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_Audio_Wave, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_Audio_Wave, 310);
    lv_obj_set_height(ui_Audio_Wave, 10);
    lv_obj_set_align(ui_Audio_Wave, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_style_bg_color(ui_Audio_Wave, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Audio_Wave, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Audio_Wave, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Audio_Wave, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Audio_Wave, &ui_img_audio_wave_1_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui_Audio_Wave, 50, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Audio_Wave, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Audio_Wave, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_Audio_Wave, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_Audio_Wave, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Audio_Wave, &ui_img_audio_wave_1_png, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Audio_Wave, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Audio_Wave, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
}

void set_audio_wave_value(int32_t value)
{
    lv_slider_set_value(ui_Audio_Wave, value, LV_ANIM_OFF);
}

static void lv_avi_window_create(lv_obj_t *parent)
{
    avi_obj = lv_img_create(parent);
    lv_obj_set_size(avi_obj, JPEG_WIDTH, JPEG_HEIGHT);
    lv_obj_align(avi_obj, LV_ALIGN_CENTER, 0, 0);
}

void lv_avi_player_draw(int32_t x, int32_t y, const void *pInBuffer, int32_t xSize, int32_t ySize)
{
    static lv_img_dsc_t img_dsc =
    {
        .header.always_zero = 0,
        .header.w = JPEG_WIDTH,
        .header.h = JPEG_HEIGHT,
        .header.cf = LV_IMG_CF_TRUE_COLOR,
        .data_size = JPEG_WIDTH * JPEG_HEIGHT * sizeof(lv_color16_t),
        .data = NULL,
    };

    uint16_t *fbp16 = (uint16_t *)lv_show_buffer;
    long int location = 0;

    location = x + y * JPEG_WIDTH;
    rt_memcpy(&fbp16[location], pInBuffer, (ySize * JPEG_WIDTH * sizeof(lv_color16_t)));

    if (y == JPEG_HEIGHT - 16)
    {
        img_dsc.data_size = ySize * xSize * sizeof(lv_color16_t);
        img_dsc.data = (const uint8_t *)fbp16;
        lv_img_set_src(avi_obj, &img_dsc);
    }
}

static void auto_run_video_timer_cb(lv_timer_t *timer)
{
    /* send event to take back file panel */
    lv_event_send(file_ImgButton, LV_EVENT_RELEASED, NULL);

    player_control(&v_player, PLAYER_CMD_INIT, v_player.video_list[0]);

    /* delete button */
    lv_obj_del(file_ImgButton);
    lv_obj_del_delayed(file_explorer_panel, 1000);
    func_button_create(win_obj);

    lv_timer_del(timer);
}

void lv_video_gui_init(void)
{
    win_obj = lv_media_page_create(lv_scr_act());
    lv_avi_window_create(win_obj);
    file_explorer_create(win_obj);
    file_ImgButton_create(win_obj);
    sound_slider_create(win_obj);
    lv_audio_wave_create(win_obj);

    lv_timer_t *t = lv_timer_create(auto_run_video_timer_cb, 2000, NULL);
    lv_timer_ready(t);
}

static uint8_t jpeg_outbuffer[DCODE_BUFFER_SIZE] BSP_ALIGN_VARIABLE(8);
static decode_drv_t decode;

int player_init(void)
{
    v_player.decode = &decode;
    v_player.decode->jpeg_out_buf = &jpeg_outbuffer;
    v_player.decode->decode_read = lv_avi_player_draw;

    player_start(&v_player);

    return 0;
}
INIT_APP_EXPORT(player_init);
