#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <rtthread.h>
#include <hal_mem.h>
#include <log.h>
#include <video/sunxi_display2.h>
#include "disp_layer_cfg.h"
#include "disp_mem.h"

int msleep(unsigned int msecs);

static u32 g_screen_index;
#define DELAY_MS 100

static int show_vi_layer(struct test_layer_cfg *cfg, u32 alpha_mode, u32 alpha_value)
{
    if (!cfg)
        return -1;

    cfg->mem_id = 1;
    cfg->screen_id = g_screen_index;
    cfg->layer_cfg.channel = 0;
    cfg->layer_id = 0;
    cfg->layer_cfg.layer_id = 0;

    cfg->layer_cfg.info.fb.format = 72;
    cfg->layer_cfg.info.fb.size[0].width = 1280;
    cfg->layer_cfg.info.fb.size[0].height = 720;
    cfg->layer_cfg.info.fb.crop.x = 0;
    cfg->layer_cfg.info.fb.crop.y = 0;
    cfg->layer_cfg.info.fb.crop.width = 1280;
    cfg->layer_cfg.info.fb.crop.height = 720;
    cfg->layer_cfg.info.fb.align[0] = 4;
    cfg->layer_cfg.info.mode = 0;
    cfg->layer_cfg.info.alpha_mode = alpha_mode;
    cfg->layer_cfg.info.alpha_value = alpha_value;
    cfg->layer_cfg.info.zorder = 0;
    cfg->layer_cfg.info.screen_win.x = 0;
    cfg->layer_cfg.info.screen_win.y = 0;

    return disp_layer_cfg(cfg);
}

static int show_ui_layer(struct test_layer_cfg *cfg,u32 ch,  u32 alpha_mode, u32 alpha_value)
{
    if (!cfg)
        return -1;

    cfg->mem_id = 0;
    cfg->screen_id = g_screen_index;
    cfg->layer_cfg.channel = ch;
    cfg->layer_id = 0;
    cfg->layer_cfg.layer_id = 0;

    cfg->layer_cfg.info.fb.format = 0;
    cfg->layer_cfg.info.fb.size[0].width = 800;
    cfg->layer_cfg.info.fb.size[0].height = 480;
    cfg->layer_cfg.info.fb.crop.x = 0;
    cfg->layer_cfg.info.fb.crop.y = 0;
    cfg->layer_cfg.info.fb.crop.width = 800;
    cfg->layer_cfg.info.fb.crop.height = 480;
    cfg->layer_cfg.info.fb.align[0] = 4;
    cfg->layer_cfg.info.mode = 0;
    cfg->layer_cfg.info.alpha_mode = alpha_mode;
    cfg->layer_cfg.info.alpha_value = alpha_value;
    cfg->layer_cfg.info.zorder = 1;
    cfg->layer_cfg.info.screen_win.x = 0;
    cfg->layer_cfg.info.screen_win.y = 0;

    return disp_layer_cfg(cfg);
}

int disp_layer_alpha_test(int argc, char **argv)
{
    struct test_layer_cfg test_cfg;
    int ch_index = 0, i , j;
    int ch_num = 3, vi_chn_num = 1;
    /*main test start*/

    if (argc == 2) {
        g_screen_index = atoi(argv[1]);
    } else
        g_screen_index = 0;

    disp_layer_clear_all(g_screen_index);

    printf("request mem_id 0\n");
    disp_mem(0, 800, 480, 0, "./pic/ui_800x480_double_151.bin");

    disp_mem(1, 1280, 800, 0, "./pic/bike_1280x720_020.bin");

    printf("Start show layer\n");
    memset(&test_cfg, 0, sizeof(struct test_layer_cfg));
    show_vi_layer(&test_cfg, 0, 255);

    memset(&test_cfg, 0, sizeof(struct test_layer_cfg));
    msleep(DELAY_MS);
    ch_index = vi_chn_num;
    while(ch_index < ch_num) {
        show_ui_layer(&test_cfg, ch_index, 1, 255);
        msleep(DELAY_MS);
        /*pixel mode*/
        for (i = 0; i < 255; i+=25) {
            show_ui_layer(&test_cfg, ch_index, 1, i);
            msleep(DELAY_MS);
        }
        msleep(DELAY_MS);
        show_ui_layer(&test_cfg, ch_index, 1, 255);
        msleep(DELAY_MS);
        /*pixel mode*/
        for (i = 0; i < 255; i+=25) {
            show_ui_layer(&test_cfg, ch_index, 0, i);
            msleep(DELAY_MS);
        }
        /*global pixel mode*/
        for (i = 0; i < 255; i+=25) {
            show_ui_layer(&test_cfg, ch_index, 2, i);
            msleep(DELAY_MS);
        }
        ++ch_index;
    }



    disp_layer_clear_all(g_screen_index);
    msleep(100);
    disp_mem_clear(0);
    disp_mem_clear(1);
    return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(disp_layer_alpha_test, __cmd_disp_layer_alpha_test, disp_layer_alpha_test);
