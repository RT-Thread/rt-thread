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
#include <arch.h>

int msleep(unsigned int msecs);

static u32 g_screen_index;

static int show_layer(struct test_layer_cfg *cfg, u32 width, u32 height,
              u32 channel, u32 format, char *filename)
{
    if (!cfg || !filename)
        return -1;

    printf("show %s format:0x%x\n", filename, format);
    disp_mem(0, width, height, 0, filename);
    awos_arch_clean_flush_dcache(); /* flush cache */

    cfg->mem_id = 0;
    cfg->screen_id = g_screen_index;
    cfg->layer_cfg.channel = channel;
    cfg->layer_id = 0;
    cfg->layer_cfg.layer_id = 0;

    cfg->layer_cfg.info.fb.format = format;
    cfg->layer_cfg.info.fb.size[0].width = width;
    cfg->layer_cfg.info.fb.size[0].height = height;
    cfg->layer_cfg.info.fb.crop.x = 0;
    cfg->layer_cfg.info.fb.crop.y = 0;
    cfg->layer_cfg.info.fb.crop.width = width;
    cfg->layer_cfg.info.fb.crop.height = height;
    cfg->layer_cfg.info.fb.align[0] = 4;
    cfg->layer_cfg.info.mode = 0;
    cfg->layer_cfg.info.alpha_mode = 1;
    cfg->layer_cfg.info.alpha_value = 255;
    cfg->layer_cfg.info.zorder = 0;
    cfg->layer_cfg.info.screen_win.x = 0;
    cfg->layer_cfg.info.screen_win.y = 0;

    disp_layer_cfg(cfg);

    msleep(5000);
    disp_layer_clear(g_screen_index, channel, 0);
    disp_mem_clear(0);
    return 0;
}

int disp_layer_rgb_test(int argc, char **argv)
{
    struct test_layer_cfg test_cfg;
    int i, sw, sh;
    /*main test start*/

    if (argc == 2) {
        g_screen_index = atoi(argv[1]);
    } else
        g_screen_index = 0;

    disp_layer_clear_all(g_screen_index);

    printf("request mem_id 0\n");

    printf("Start show layer\n");

    memset(&test_cfg, 0, sizeof(struct test_layer_cfg));
    show_layer(&test_cfg, 480, 272, 0, DISP_FORMAT_ARGB_8888, "rgb");

    disp_layer_clear_all(g_screen_index);
    msleep(100);

    return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(disp_layer_rgb_test, __cmd_disp_layer_rgb_test, disp_layer_rgb_test);
