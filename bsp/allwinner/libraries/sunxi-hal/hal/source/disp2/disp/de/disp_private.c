/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "../dev_disp.h"
#include "disp_private.h"

extern struct disp_drv_info g_disp_drv;


u32 dump_layer_config(struct disp_layer_config_data *data)
{
    u32 count = 0;
    char buf[512];

    count +=
        sprintf(buf + count, " %6s ",
            (data->config.info.mode == LAYER_MODE_BUFFER) ?
            "buffer" : "color");
    count +=
        sprintf(buf + count, " %8s ",
            (data->config.enable == 1) ? "enable" : "disable");
    count += sprintf(buf + count, "ch[%1d] ", data->config.channel);
    count += sprintf(buf + count, "lyr[%1d] ", data->config.layer_id);
    count += sprintf(buf + count, "z[%1d] ", data->config.info.zorder);
    count +=
        sprintf(buf + count, "pre_m[%1s] ",
            (data->config.info.fb.pre_multiply) ? "Y" : "N");
    count +=
        sprintf(buf + count, "alpha[%5s %3d] ",
            (data->config.info.alpha_mode) ? "globl" : "pixel",
            data->config.info.alpha_value);
    count += sprintf(buf + count, "fmt[%3d] ", data->config.info.fb.format);
    count +=
        sprintf(buf + count, "size[%4d,%4d;%4d,%4d;%4d,%4d] ",
            data->config.info.fb.size[0].width,
            data->config.info.fb.size[0].height,
            data->config.info.fb.size[0].width,
            data->config.info.fb.size[0].height,
            data->config.info.fb.size[0].width,
            data->config.info.fb.size[0].height);
    count +=
        sprintf(buf + count, "crop[%4d,%4d,%4d,%4d] ",
            (int) (data->config.info.fb.crop.x >> 32),
            (int) (data->config.info.fb.crop.y >> 32),
            (int) (data->config.info.fb.crop.width >> 32),
            (int) (data->config.info.fb.crop.height >> 32));
    count +=
        sprintf(buf + count, "frame[%4d,%4d,%4d,%4d] ",
            data->config.info.screen_win.x,
            data->config.info.screen_win.y,
            data->config.info.screen_win.width,
            data->config.info.screen_win.height);
    count +=
        sprintf(buf + count, "addr[%8llx,%8llx,%8llx] ",
            data->config.info.fb.addr[0], data->config.info.fb.addr[1],
            data->config.info.fb.addr[2]);
    count += sprintf(buf + count, "flag[0x%8x] ", data->flag);
    count += sprintf(buf + count, "\n");

    DE_WRN("%s", buf);
    return count;
}




