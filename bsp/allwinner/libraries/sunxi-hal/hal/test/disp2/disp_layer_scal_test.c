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

static int show_vi_layer(struct test_layer_cfg *cfg, u32 screen_width, u32 screen_height)
{
    if (!cfg)
        return -1;

    cfg->mem_id = 0;
    cfg->screen_id = g_screen_index;
    cfg->layer_cfg.channel = 0;
    cfg->layer_id = 0;
    cfg->layer_cfg.layer_id = 0;

    cfg->layer_cfg.info.fb.format = 3;
    cfg->layer_cfg.info.fb.size[0].width = 1280;
    cfg->layer_cfg.info.fb.size[0].height = 720;
    cfg->layer_cfg.info.fb.crop.x = 0;
    cfg->layer_cfg.info.fb.crop.y = 0;
    cfg->layer_cfg.info.fb.crop.width = 1280;
    cfg->layer_cfg.info.fb.crop.height = 720;
    cfg->layer_cfg.info.fb.align[0] = 4;
    cfg->layer_cfg.info.mode = 0;
    cfg->layer_cfg.info.alpha_mode = 1;
    cfg->layer_cfg.info.alpha_value = 255;
    cfg->layer_cfg.info.zorder = 0;
    cfg->layer_cfg.info.screen_win.x = 0;
    cfg->layer_cfg.info.screen_win.y = 0;
    cfg->layer_cfg.info.screen_win.width = screen_width;
    cfg->layer_cfg.info.screen_win.height = screen_height;

    return disp_layer_cfg(cfg);
}

static int show_vi_layer2(struct test_layer_cfg *cfg, u32 screen_width, u32 screen_height)
{
    if (!cfg)
        return -1;

    cfg->mem_id = 0;
    cfg->screen_id = g_screen_index;
    cfg->layer_cfg.channel = 0;
    cfg->layer_id = 0;
    cfg->layer_cfg.layer_id = 0;

    cfg->layer_cfg.info.fb.format = 0;
    cfg->layer_cfg.info.fb.size[0].width = 241;
    cfg->layer_cfg.info.fb.size[0].height = 161;
    cfg->layer_cfg.info.fb.crop.x = 0;
    cfg->layer_cfg.info.fb.crop.y = 0;
    cfg->layer_cfg.info.fb.crop.width = 241;
    cfg->layer_cfg.info.fb.crop.height = 161;
    cfg->layer_cfg.info.fb.align[0] = 4;
    cfg->layer_cfg.info.mode = 0;
    cfg->layer_cfg.info.alpha_mode = 1;
    cfg->layer_cfg.info.alpha_value = 255;
    cfg->layer_cfg.info.zorder = 0;
    cfg->layer_cfg.info.screen_win.x = 0;
    cfg->layer_cfg.info.screen_win.y = 0;
    cfg->layer_cfg.info.screen_win.width = screen_width;
    cfg->layer_cfg.info.screen_win.height = screen_height;

    return disp_layer_cfg(cfg);
}

int disp_layer_scal_test(int argc, char **argv)
{
    struct test_layer_cfg test_cfg;
    int i, sw, sh;
    u32 cap_x = 0, cap_y = 0;
    /*main test start*/

    if (argc == 2) {
        g_screen_index = atoi(argv[1]);
    } else
        g_screen_index = 0;

    disp_layer_clear_all(g_screen_index);

    printf("request mem_id 0\n");
    disp_mem(0, 1280, 720, 0, "./pic/bike_1280x720_150.bin");

    printf("Start show layer\n");

    memset(&test_cfg, 0, sizeof(struct test_layer_cfg));
    show_vi_layer(&test_cfg, 480, 640);

    disp_layer_get_resolution(g_screen_index, &cap_x, &cap_y);

    printf("Scal up\n");
    for (i = 0, sw = 0, sh = 0; sw < cap_x; ++i) {
        sw += 32;
        sh += 20;
        show_vi_layer(&test_cfg, sw, sh);
        msleep(100);
    }

    printf("Scal down\n");
    for (; sw > 0 && sh > 0  ;) {
        show_vi_layer(&test_cfg,  sw, sh);
        msleep(100);
        sw -= 32;
        sh -= 20;
    }



    disp_mem_clear(0);
    disp_layer_clear_all(g_screen_index);

    printf("Scal test 2\n");
    disp_mem(0, 241, 161, 0, "./pic/leopard_241x161_151_Deu.bin");

    printf("Scal up\n");
    for (i = 0, sw = 0, sh = 0; sw < cap_x; ++i) {
        sw += 32;
        sh += 20;
        show_vi_layer2(&test_cfg, sw, sh);
        msleep(100);
    }

    printf("Scal down\n");
    for (; sw > 0 && sh > 0  ;) {
        show_vi_layer2(&test_cfg,  sw, sh);
        msleep(100);
        sw -= 32;
        sh -= 20;
    }

    disp_layer_clear_all(g_screen_index);
    msleep(100);
    disp_mem_clear(0);

    return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(disp_layer_scal_test, __cmd_disp_layer_scal_test, disp_layer_scal_test);
