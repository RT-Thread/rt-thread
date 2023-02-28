/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "de_hal.h"

#define EINK_DEBUG 0
static unsigned int g_device_fps[DE_NUM] = { 60 };
static bool g_de_blank[DE_NUM] = { false };
static unsigned int g_de_freq;

int de_update_device_fps(unsigned int sel, u32 fps)
{
    g_device_fps[sel] = fps;

    return 0;
}

/**
 * Update clk rate of de, unit hz.
 */
int de_update_clk_rate(u32 rate)
{
    g_de_freq = rate / 1000000;

    return 0;
}

/**
 * Get clk rate of de, unit hz.
 */
int de_get_clk_rate(void)
{
    return g_de_freq * 1000000;
}

static int de_set_coarse(unsigned int sel, unsigned char chno, unsigned int fmt,
             unsigned int lcd_fps, unsigned int lcd_height,
             unsigned int de_freq_mhz, unsigned int ovl_w,
             unsigned int ovl_h, unsigned int vsu_outw,
             unsigned int vsu_outh, unsigned int *midyw,
             unsigned int *midyh, struct scaler_para *fix_ypara,
             struct scaler_para *fix_cpara)
{
    int coarse_status;
    unsigned int midcw, midch;

    coarse_status =
        de_rtmx_set_coarse_fac(sel, chno, fmt, lcd_fps, lcd_height,
                   de_freq_mhz, ovl_w, ovl_h, vsu_outw,
                   vsu_outh, midyw, midyh, &midcw, &midch);
    de_vsu_recalc_scale_para(coarse_status, vsu_outw, vsu_outh, *midyw,
                 *midyh, midcw, midch, fix_ypara, fix_cpara);

    return 0;
}

static int
de_calc_overlay_scaler_para(unsigned int screen_id,
        unsigned char chn, unsigned char layno,
        unsigned char *fmt,
        struct disp_layer_config_data *data,
        unsigned char (*premul)[LAYER_MAX_NUM_PER_CHN],
        unsigned char *premode,
        struct de_rect(*crop)[LAYER_MAX_NUM_PER_CHN],
        struct de_rect(*layer)[LAYER_MAX_NUM_PER_CHN],
        struct de_rect *bld_rect, unsigned int *ovlw,
        unsigned int *ovlh, unsigned char *pen,
        struct scaler_para *ovl_para,
        struct scaler_para *ovl_cpara)
{
    bool scaler_en;
    unsigned char i, j, k, lay_en[CHN_NUM][LAYER_MAX_NUM_PER_CHN];
    unsigned int midyw, midyh;
    unsigned int lcd_fps = g_device_fps[screen_id];
    unsigned int lcd_width = 1280, lcd_height = 720;
    unsigned int de_freq_mhz = g_de_freq;
    struct de_rect64 crop64[CHN_NUM][LAYER_MAX_NUM_PER_CHN];
    struct de_rect frame[CHN_NUM][LAYER_MAX_NUM_PER_CHN];
    static struct scaler_para para[CHN_NUM][LAYER_MAX_NUM_PER_CHN];
    static struct scaler_para cpara[VI_CHN_NUM][LAYER_MAX_NUM_PER_CHN];
    unsigned int vi_chn = de_feat_get_num_vi_chns(screen_id);
    unsigned int scaler_num = de_feat_is_support_scale(screen_id);

    de_rtmx_get_display_size(screen_id, &lcd_width, &lcd_height);
    /* init para */
    for (j = 0; j < vi_chn; j++)
        memset((void *)cpara[j], 0x0,
            layno * sizeof(struct scaler_para));
    for (j = 0; j < chn; j++)
        memset((void *)para[j], 0x0,
            layno * sizeof(struct scaler_para));

    /* get the original crop frame data */
    for (j = 0, k = 0; j < chn; j++) {
        for (i = 0; i < layno;) {
            memcpy(&crop64[j][i], &data[k].config.info.fb.crop,
                   sizeof(struct disp_rect64));
            memcpy(&frame[j][i], &data[k].config.info.screen_win,
                   sizeof(struct disp_rect));
            lay_en[j][i] = data[k].config.enable;
            premul[j][i] = data[k].config.info.fb.pre_multiply;

            /* 3d mode */
            if (data[k].config.info.fb.flags) {
                memcpy(&crop64[j][i + 1],
                       &data[k].config.info.fb.crop,
                       sizeof(struct disp_rect64));
                de_rtmx_get_3d_in_single_size(
                    (enum de_3d_in_mode)
                    data[k].config.info.fb.flags,
                    &crop64[j][i]);
                if (data[k].config.info.b_trd_out) {
                    de_rtmx_get_3d_in_single_size(
                    (enum de_3d_in_mode) data[k].config.
                    info.fb.flags, &crop64[j][i + 1]);
                    de_rtmx_get_3d_out(frame[j][i],
                               lcd_width,
                               lcd_height,
                               (enum de_3d_out_mode)
                               data[k].config.info.
                               out_trd_mode,
                               &frame[j][i + 1]);
                    lay_en[j][i + 1] =
                        data[k].config.enable;
                } else {
                    lay_en[j][i + 1] = 0;
                }
                premul[j][i + 1] =
                    data[k].config.info.fb.pre_multiply;
                k += 2;
                i += 2;
            } else {
                i++;
                k++;
            }
        }
    }

    for (j = 0; j < vi_chn; j++) {
        for (i = 0; i < layno; i++) {
            if (lay_en[j][i])
                de_vsu_calc_scaler_para(fmt[j], crop64[j][i],
                            frame[j][i],
                            &crop[j][i],
                            &para[j][i],
                            &cpara[j][i]);
        }
    }

    for (j = vi_chn; j < chn; j++) {
        for (i = 0; i < layno; i++) {
            if (lay_en[j][i])
                de_gsu_calc_scaler_para(crop64[j][i],
                            frame[j][i],
                            &crop[j][i],
                            &para[j][i]);
        }
    }

    /* calculate the layer coordinate,
     * overlay size & blending input coordinate
     */
    for (j = 0; j < chn; j++) {
        int gsu_sel = (j < vi_chn) ? 0 : 1;

        pen[j] =
            de_rtmx_calc_chnrect(lay_en[j], layno, frame[j], crop[j],
                gsu_sel, para[j], layer[j],
                &bld_rect[j], &ovlw[j], &ovlh[j]);
        premode[j] = de_rtmx_get_premul_ctl(layno, premul[j]);
        DE_INF("ovl_rect[%d]=<%d,%d>\n", j, ovlw[j], ovlh[j]);
        DE_INF("bld_rect[%d]=<%d,%d,%d,%d>\n", j, bld_rect[j].x,
              bld_rect[j].y, bld_rect[j].w, bld_rect[j].h);
    }

    /* get video overlay parameter for scaler */
    for (j = 0; j < vi_chn; j++) {
        DE_INF("fmt[%d]=%d, ovlw[%d]=%d,ovlh[%d]=%d, bld_rect[%d].w=%d, bld_rect[%d].h=%d\n",
            j, fmt[j], j, ovlw[j], j, ovlh[j], j, bld_rect[j].w,
            j, bld_rect[j].h);
        scaler_en = 0x1;
        if ((fmt[j] == 0) && (ovlw[j] == bld_rect[j].w)
            && (ovlh[j] == bld_rect[j].h)) {
            scaler_en = 0x0;
        }
        if (scaler_en)
            de_vsu_sel_ovl_scaler_para(lay_en[j], para[j], cpara[j],
                &ovl_para[j], &ovl_cpara[j]);

        /* recalculate overlay size, blending coordinate,
         * blending size, layer coordinate
         */
        de_recalc_ovl_bld_for_scale(scaler_en, lay_en[j], layno,
                        &ovl_para[j], layer[j],
                        &bld_rect[j], &ovlw[j], &ovlh[j], 0,
                        lcd_width, lcd_height);

        de_set_coarse(screen_id, j, fmt[j], lcd_fps, lcd_height,
                  de_freq_mhz, ovlw[j], ovlh[j], bld_rect[j].w,
                  bld_rect[j].h, &midyw, &midyh, &ovl_para[j],
                  &ovl_cpara[j]);
        de_vsu_set_para(screen_id, j, scaler_en, fmt[j], midyw, midyh,
                bld_rect[j].w, bld_rect[j].h, &ovl_para[j],
                &ovl_cpara[j]);
    }

    /* get ui overlay parameter for scaler */
    for (j = vi_chn; j < scaler_num; j++) {
        scaler_en = 0x1;
        if ((ovlw[j] == bld_rect[j].w) && (ovlh[j] == bld_rect[j].h))
            scaler_en = 0x0;
        if (scaler_en)
            de_gsu_sel_ovl_scaler_para(lay_en[j], para[j],
                           &ovl_para[j]);

        /* recalculate overlay size, blending coordinate,
         * blending size, layer coordinate
         */
        de_recalc_ovl_bld_for_scale(scaler_en, lay_en[j], layno,
                        &ovl_para[j], layer[j],
                        &bld_rect[j], &ovlw[j], &ovlh[j], 1,
                        lcd_width, lcd_height);

        de_gsu_set_para(screen_id, j, scaler_en, ovlw[j], ovlh[j],
                bld_rect[j].w, bld_rect[j].h, &ovl_para[j]);
    }

    return 0;
}

int de_al_lyr_apply_direct_show(unsigned int screen_id,
            struct disp_layer_config_data *data,
            unsigned int layer_num, bool direct_show)
{
    unsigned int display_width, display_height;
    unsigned int i;

    if (!direct_show)
        return 0;

    de_rtmx_get_display_size(screen_id, &display_width, &display_height);

    for (i = 0; i < layer_num; i++, data++) {
        struct disp_rect64 *crop64;
        struct disp_rect crop;
        struct disp_rect frame;
        struct disp_rect *screen_win;

        if (!data->config.enable)
            continue;

        crop64 = &data->config.info.fb.crop;
        screen_win = &data->config.info.screen_win;
        crop.x = crop64->x >> VSU_FB_FRAC_BITWIDTH;
        crop.y = crop64->y >> VSU_FB_FRAC_BITWIDTH;
        crop.width = crop64->width >> VSU_FB_FRAC_BITWIDTH;
        crop.height = crop64->height >> VSU_FB_FRAC_BITWIDTH;

        frame.x = 0;
        frame.y = 0;
        /*
         * If source is larger than screen, crop the source.
         * And if source is smaller than screen,
         * make frame para center in the screen
         */
        if (crop.width > display_width) {
            crop.x = (crop.width - display_width) >> 1;
            crop.width = display_width;
            frame.x = 0;
        } else {
            crop.x = 0;
            frame.x = (display_width - crop.width) >> 1;
        }

        if (crop.height > display_height) {
            crop.y = (crop.height - display_height) >> 1;
            crop.height = display_height;
            frame.y = 0;
        } else {
            crop.y = 0;
            crop.height = (crop.height >> 2) << 2;
            frame.y = (display_height - crop.height) >> 1;
        }

        frame.width = crop.width;
        frame.height = crop.height;

        crop64->x = (long long)crop.x << VSU_FB_FRAC_BITWIDTH;
        crop64->y = (long long)crop.y << VSU_FB_FRAC_BITWIDTH;
        crop64->width = (unsigned long long)crop.width
            << VSU_FB_FRAC_BITWIDTH;
        crop64->height = (unsigned long long)crop.height
            << VSU_FB_FRAC_BITWIDTH;
        screen_win->x = frame.x;
        screen_win->y = frame.y;
        screen_win->width = frame.width;
        screen_win->height = frame.height;
    }

    return 0;
}

static enum de_color_space __cs_transform(enum disp_color_space cs)
{
    enum de_color_space cs_inner;

    switch (cs) {
    case DISP_BT709:
    case DISP_BT709_F:
        cs_inner = DE_BT709;
        break;
    case DISP_BT601:
    case DISP_BT601_F:
        cs_inner = DE_BT601;
        break;
    default:
        cs_inner = DE_BT601;
        break;
    }

    return cs_inner;
}

int de_al_lyr_apply(unsigned int screen_id, struct disp_layer_config_data *data,
            unsigned int layer_num, bool direct_show)
{
    unsigned char i, j, k, chn, vi_chn, layno;
    unsigned char haddr[LAYER_MAX_NUM_PER_CHN][3];
    unsigned char premul[CHN_NUM][LAYER_MAX_NUM_PER_CHN], format[CHN_NUM],
        premode[CHN_NUM], zoder[CHN_NUM] = { 0, 1}, pen[CHN_NUM];
    unsigned int ovlw[CHN_NUM], ovlh[CHN_NUM];
    static struct __lay_para_t lay_cfg[CHN_NUM * LAYER_MAX_NUM_PER_CHN];
    struct de_rect layer[CHN_NUM][LAYER_MAX_NUM_PER_CHN], bld_rect[CHN_NUM];
    struct de_rect crop[CHN_NUM][LAYER_MAX_NUM_PER_CHN];
    static struct scaler_para ovl_para[CHN_NUM], ovl_cpara[VI_CHN_NUM];
    bool chn_used[CHN_NUM] = { false }, chn_zorder_cfg[CHN_NUM] = {
    false}, chn_dirty[CHN_NUM] = {
    false};
    bool chn_is_yuv[CHN_NUM] = { false };
    enum de_color_space cs[CHN_NUM];
    unsigned char layer_zorder[CHN_NUM] = { 0 }, chn_index;
    unsigned char pipe_used[4] = { 0 };
    unsigned int pipe_sel[CHN_NUM] = { 0 };
    struct de_rect pipe_rect[CHN_NUM] = { {0} };
    struct disp_rect dispsize[CHN_NUM] = { {0} };
    struct disp_layer_config_data *data1;
    unsigned int color = 0xff000000;
    struct de_rect input_layer;
 #if EINK_DEBUG
    u32 count = 0;
    u32 kcon = 0;
    char buf[256] = {0};
    struct disp_layer_config_data data_print;
#endif

    data1 = data;

    chn = de_feat_get_num_chns(screen_id);
    vi_chn = de_feat_get_num_vi_chns(screen_id);
    layno = LAYER_MAX_NUM_PER_CHN;

#if EINK_DEBUG
    for (kcon = 0; kcon < layer_num; kcon++) {
        if (data[kcon].config.enable == false)
            continue;
        memcpy(&data_print, &data[kcon],
            sizeof(struct disp_layer_config_data));
        memset(buf, 0, sizeof(buf));
        count = 0;
        count += sprintf(buf + count, " %5s ",
            (data_print.config.info.mode == LAYER_MODE_BUFFER) ?
            "BUF" : "COLOR");
        count += sprintf(buf + count, " %8s ",
            (data_print.config.enable == 1) ? "enable" : "disable");
        count += sprintf(buf + count, "ch[%1u] ",
                        data_print.config.channel);
        count += sprintf(buf + count, "lyr[%1u] ",
                        data_print.config.layer_id);
        count += sprintf(buf + count, "z[%1u] ",
                        data_print.config.info.zorder);
        count += sprintf(buf + count, "prem[%1s] ",
            (data_print.config.info.fb.pre_multiply) ? "Y" : "N");
        count += sprintf(buf + count, "a[%5s %3u] ",
            (data_print.config.info.alpha_mode) ? "globl" : "pixel",
            data_print.config.info.alpha_value);
        count += sprintf(buf + count,
                "fmt[%3d] ",
                data_print.config.info.fb.format);
        count += sprintf(buf + count, "fb[%4u,%4u;%4u,%4u;%4u,%4u] ",
                data_print.config.info.fb.size[0].width,
                data_print.config.info.fb.size[0].height,
                data_print.config.info.fb.size[1].width,
                data_print.config.info.fb.size[1].height,
                data_print.config.info.fb.size[2].width,
                data_print.config.info.fb.size[2].height);
        count += sprintf(buf + count, "crop[%4u,%4u,%4u,%4u] ",
            (unsigned int)(data_print.config.info.fb.crop.x>>32),
            (unsigned int)(data_print.config.info.fb.crop.y>>32),
            (unsigned int)(data_print.config.info.fb.crop.width>>32),
            (unsigned int)(data_print.config.info.fb.crop.height>>32));

        count += sprintf(buf + count, "frame[%4d,%4d,%4u,%4u] ",
                data_print.config.info.screen_win.x,
                data_print.config.info.screen_win.y,
                data_print.config.info.screen_win.width,
                data_print.config.info.screen_win.height);
        count += sprintf(buf + count, "addr[%8llx,%8llx,%8llx] ",
                    data_print.config.info.fb.addr[0],
                    data_print.config.info.fb.addr[1],
                    data_print.config.info.fb.addr[2]);
        count += sprintf(buf + count, "flags[0x%8x] trd[%1d,%1d]\n",
                    data_print.config.info.fb.flags,
                    data_print.config.info.b_trd_out,
                    data_print.config.info.out_trd_mode);
        pr_info("%s\n", buf);
    }
#endif

    de_al_lyr_apply_direct_show(screen_id, data, layer_num, direct_show);
    /* parse zorder of channel */
    data1 = data;
    for (i = 0; i < layer_num; i++) {
        if (data1->config.enable) {
            chn_used[data1->config.channel] = true;
            if (data1->config.info.fb.format >=
                DISP_FORMAT_YUV444_I_AYUV) {
                chn_is_yuv[data1->config.channel] = true;
                cs[data1->config.channel] = __cs_transform(
                    data1->config.info.fb.color_space);
            }
            if (data1->flag)
                chn_dirty[data1->config.channel] = true;

            layer_zorder[data1->config.channel] =
                data1->config.info.zorder;
        }
        data1++;
    }

    data1 = data;
    for (i = 0; i < layer_num; i++) {
        if (data1->config.enable && chn_dirty[data1->config.channel])
            data1->flag = LAYER_ALL_DIRTY;
        data1++;
    }

    chn_index = 0;
    for (i = 0; i < chn; i++) {
        u32 min_zorder = 255, min_zorder_chn = 0;
        bool find = false;

        for (j = 0; j < chn; j++) {
            if ((true == chn_used[j]) && (true != chn_zorder_cfg[j]
                && (min_zorder > layer_zorder[j]))) {
                min_zorder = layer_zorder[j];
                min_zorder_chn = j;
                find = true;
            }
        }
        if (find) {
            chn_zorder_cfg[min_zorder_chn] = true;
            zoder[min_zorder_chn] = chn_index++;
        }
    }

    /* parse zorder of pipe */
    for (i = 0; i < chn; i++) {
        if (chn_used[i]) {
            u32 pipe_index = zoder[i];

            pipe_used[pipe_index] = (g_de_blank[screen_id]) ?
                false : true;
            pipe_sel[pipe_index] = i;
        }
    }
    for (i = 0; i < chn; i++)
        DE_INF("ch%d z %d %s\n", i, zoder[i],
              chn_used[i] ? "en" : "dis");
    for (i = 0; i < chn; i++)
        DE_INF("pipe%d z %d %s\n", i, pipe_sel[i],
              pipe_used[i] ? "en" : "dis");

    /* init para */
    for (j = 0; j < chn; j++)
        memset((void *)crop[j], 0x0, layno * sizeof(struct de_rect));

/* check the video format for fill color, because of the hardware limit */
    for (j = 0, k = 0; j < vi_chn; j++) {
        format[j] = 0;
        for (i = 0; i < layno; i++) {
            if (data[k].config.info.fb.format >=
                DISP_FORMAT_YUV422_I_YVYU)
                format[j] = data[k].config.info.fb.format;
            k++;
        }
        DE_INF("format[%d]=%d\n", j, format[j]);
    }

    de_calc_overlay_scaler_para(screen_id, chn, layno, format, data, premul,
                    premode, crop, layer, bld_rect, ovlw, ovlh,
                    pen, ovl_para, ovl_cpara);

    for (j = 0; j < vi_chn; j++) {
        if (chn_used[j]) {
            struct disp_csc_config csc_cfg;

            /*
             * We need to disable csc function when on direct show,
             * And  to enable csc function if needed otherwise.
             * When the input format of csc module is the same width
             * the output, the csc function will be disable.
             */
            if (direct_show) {
                csc_cfg.in_fmt = DE_YUV;
                csc_cfg.in_mode = DE_BT601;
                csc_cfg.out_fmt = DE_YUV;
                csc_cfg.out_mode = DE_BT601;

                color = (16 << 16) | (128 << 8) | (128 << 0);
            } else {
                csc_cfg.in_fmt = (chn_is_yuv[j]) ?
                    DE_YUV : DE_RGB;
                csc_cfg.in_mode = cs[j];
                csc_cfg.out_fmt = DE_RGB;
                csc_cfg.out_mode = DE_BT601;

                color = 0;
            }
            csc_cfg.out_color_range = DISP_COLOR_RANGE_0_255;
            csc_cfg.brightness = 50;
            csc_cfg.contrast = 50;
            csc_cfg.saturation = 50;
            csc_cfg.hue = 50;
            de_ccsc_apply(screen_id, j, &csc_cfg);
            de_rtmx_set_blend_color(screen_id, j, color);
        }
    }

    /* init lay_cfg from layer config */
    for (j = 0, k = 0; j < chn; j++) {
        for (i = 0; i < layno;) {
            lay_cfg[k].en = data[k].config.enable;
            lay_cfg[k].alpha_mode = data[k].config.info.alpha_mode;
            lay_cfg[k].alpha = data[k].config.info.alpha_value;
            lay_cfg[k].fcolor_en = data[k].config.info.mode;
            lay_cfg[k].fmt = data[k].config.info.fb.format;
            lay_cfg[k].premul_ctl = premul[j][i];
            lay_cfg[k].lbc_en = data[k].config.info.fb.lbc_en;
            lay_cfg[k].lbc_info = data[k].config.info.fb.lbc_info;

            if(!lay_cfg[k].lbc_en) {
                lay_cfg[k].pitch[0] =
                    data[k].config.info.fb.size[0].width;
                lay_cfg[k].pitch[1] =
                    data[k].config.info.fb.size[1].width;
                lay_cfg[k].pitch[2] =
                    data[k].config.info.fb.size[2].width;
                lay_cfg[k].layer = layer[j][i];
                lay_cfg[k].laddr_t[0] =
                    (data[k].config.info.fb.addr[0] & 0xFFFFFFFF);
                lay_cfg[k].laddr_t[1] =
                    (data[k].config.info.fb.addr[1] & 0xFFFFFFFF);
                lay_cfg[k].laddr_t[2] =
                    (data[k].config.info.fb.addr[2] & 0xFFFFFFFF);

                lay_cfg[k].top_bot_en = 0x0;
                lay_cfg[k].laddr_b[0] = 0x0;
                lay_cfg[k].laddr_b[1] = 0x0;
                lay_cfg[k].laddr_b[2] = 0x0;
            } else {
                input_layer.x = data[k].config.info.screen_win.x;
                input_layer.y = data[k].config.info.screen_win.y;
                input_layer.w = data[k].config.info.fb.size[0].width;
                input_layer.h = data[k].config.info.fb.size[0].height;
                lay_cfg[k].layer = input_layer;
                lay_cfg[k].lbc_haddr = ((data[k].config.info.fb.addr[0] >> 32) & 0xFF);
                lay_cfg[k].lbc_laddr = (data[k].config.info.fb.addr[0] & 0xFFFFFFFF);
                lay_cfg[k].lbc_crop.x = data[k].config.info.fb.crop.x >> 32;
                lay_cfg[k].lbc_crop.y = data[k].config.info.fb.crop.y >> 32;
                lay_cfg[k].lbc_crop.w = data[k].config.info.fb.crop.width >> 32;
                lay_cfg[k].lbc_crop.h = data[k].config.info.fb.crop.height >> 32;
            }
            /* 3d mode */
            if (data[k].config.info.fb.flags) {
                if (data[k].config.info.b_trd_out)
                    lay_cfg[k + 1].en =
                        data[k].config.enable;
                else
                    lay_cfg[k + 1].en = 0;

                lay_cfg[k + 1].alpha_mode =
                    data[k].config.info.alpha_mode;
                lay_cfg[k + 1].alpha =
                    data[k].config.info.alpha_value;
                lay_cfg[k + 1].fcolor_en =
                    data[k].config.info.mode;
                lay_cfg[k + 1].fmt =
                    data[k].config.info.fb.format;
                lay_cfg[k + 1].premul_ctl = premul[j][i];

                lay_cfg[k + 1].layer = layer[j][i + 1];
                de_rtmx_get_3d_in(data[k].config.info.fb.format,
                    crop[j][i + 1],
                    (struct de_fb *) data[k].config.info.
                    fb.size,
                    data[k].config.info.fb.align,
                    (enum de_3d_in_mode) data[k].
                    config.info.fb.flags,
                    lay_cfg[k].laddr_t,
                    data[k].config.info.fb.
                    trd_right_addr,
                    lay_cfg[k].pitch,
                    lay_cfg[k + 1].pitch,
                    lay_cfg[k + 1].laddr_t);

                lay_cfg[k + 1].top_bot_en =
                    lay_cfg[k].top_bot_en;
                lay_cfg[k + 1].laddr_b[0] =
                    lay_cfg[k].laddr_b[0];
                lay_cfg[k + 1].laddr_b[1] =
                    lay_cfg[k].laddr_b[1];
                lay_cfg[k + 1].laddr_b[2] =
                    lay_cfg[k].laddr_b[2];
                data[k + 1].flag = data[k].flag;
                k += 2;
                i += 2;
            } else {
                i++;
                k++;
            }
        }
    }

    for (j = 0, k = 0; j < chn; j++) {
        for (i = 0; i < layno; i++) {
            if (LAYER_SIZE_DIRTY & data[k + i].flag) {
                de_rtmx_set_overlay_size(screen_id, j, ovlw[j],
                             ovlh[j], data[k + i].config.info.fb.lbc_en);
                break;
            }
        }

        for (i = 0; i < layno; i++) {
            if (LAYER_ATTR_DIRTY & data[k].flag) {
                de_rtmx_set_lay_cfg(screen_id, j, i,
                            &lay_cfg[k]);
                de_rtmx_set_lay_laddr(screen_id, j, i,
                              lay_cfg[k].fmt,
                              crop[j][i],
                              lay_cfg[k].pitch,
                              data[k].config.info.fb.
                              align,
            (enum de_3d_in_mode)data[k].config.info.fb.flags,
                              lay_cfg[k].laddr_t,
                              haddr[i],
                              lay_cfg[k].lbc_en);
            }
            if (LAYER_VI_FC_DIRTY & data[k].flag) {
                de_rtmx_set_lay_fcolor(screen_id, j, i,
                               data[k].config.info.mode,
                               format[j],
                               data[k].config.info.color,
                               data[k].config.info.fb.lbc_en);
            }
            if (LAYER_HADDR_DIRTY & data[k].flag) {
                lay_cfg[k].haddr_t[0] =
                    ((data[k].config.info.fb.
                      addr[0] >> 32) & 0xFF) + haddr[i][0];
                lay_cfg[k].haddr_t[1] =
                    ((data[k].config.info.fb.
                      addr[1] >> 32) & 0xFF) + haddr[i][1];
                lay_cfg[k].haddr_t[2] =
                    ((data[k].config.info.fb.
                      addr[2] >> 32) & 0xFF) + haddr[i][2];

                lay_cfg[k].haddr_b[0] = 0x0;
                lay_cfg[k].haddr_b[1] = 0x0;
                lay_cfg[k].haddr_b[2] = 0x0;
                de_rtmx_set_lay_haddr(screen_id, j, i,
                              lay_cfg[k].top_bot_en,
                              lay_cfg[k].haddr_t,
                              lay_cfg[k].haddr_b,
                              lay_cfg[k].lbc_en);
            }
            k++;
        }
    }

    /* parse pipe rect */
    for (i = 0; i < chn; i++) {
        if (pipe_used[i]) {
            u32 chn_index = pipe_sel[i];

            memcpy(&pipe_rect[i], &bld_rect[chn_index],
                   sizeof(struct disp_rect));
            dispsize[i].width = bld_rect[i].w;
            dispsize[i].height = bld_rect[i].h;
        }
    }
    /* need route information to calculate pipe enable and input size */
    de_rtmx_set_pf_en(screen_id, pipe_used);
    for (i = 0; i < chn; i++) {
        DE_INF("sel=%d, pipe_rect[%d]=<%d,%d,%d,%d>\n", screen_id, i,
              pipe_rect[i].x, pipe_rect[i].y, pipe_rect[i].w,
              pipe_rect[i].h);
        de_rtmx_set_pipe_cfg(screen_id, i, color, pipe_rect[i]);
        de_rtmx_set_route(screen_id, i, pipe_sel[i]);
        de_rtmx_set_premul(screen_id, i, premode[i]);
    }

    for (i = 0; i < chn - 1; i++)
        de_rtmx_set_blend_mode(screen_id, i, DE_BLD_SRCOVER);
    /* de_rtmx_set_colorkey(screen_id,); */

    /* set enhance size */
    de_enhance_set_size(screen_id, dispsize);
    de_enhance_set_format(screen_id, (chn_is_yuv[0]) ? DE_YUV : DE_RGB);

    return 0;
}

int de_al_mgr_apply_color(unsigned int screen_id, struct disp_csc_config *cfg)
{
    struct disp_csc_config csc_cfg;

    de_rtmx_set_background_color(screen_id, cfg->color);

    de_dcsc_get_config(screen_id, &csc_cfg);
    csc_cfg.in_fmt = DISP_CSC_TYPE_RGB;
    csc_cfg.in_mode = DE_BT601;

    csc_cfg.out_fmt = cfg->out_fmt;
    csc_cfg.out_mode = cfg->out_mode;
    csc_cfg.out_color_range = cfg->out_color_range;
    csc_cfg.brightness = 50;
    csc_cfg.contrast = 50;
    csc_cfg.saturation = 50;
    csc_cfg.hue = 50;
    de_dcsc_apply(screen_id, &csc_cfg);

    return 0;
}

int de_al_mgr_apply(unsigned int screen_id, struct disp_manager_data *data)
{
    struct disp_csc_config csc_cfg;
    int color =
        (data->config.back_color.alpha << 24) | (data->config.back_color.
                             red << 16)
        | (data->config.back_color.green << 8) | (data->config.back_color.
                              blue << 0);

    g_de_blank[screen_id] = data->config.blank;

    if ((data->flag & MANAGER_ENABLE_DIRTY)
        || (data->flag & MANAGER_COLOR_SPACE_DIRTY)) {
        csc_cfg.color = color;
        csc_cfg.out_fmt =
            (data->config.cs == DISP_CSC_TYPE_RGB) ? DE_RGB : DE_YUV;
        if ((data->config.size.width < 1280)
            && (data->config.size.height < 720))
            csc_cfg.out_mode = DE_BT601;
        else
            csc_cfg.out_mode = DE_BT709;
        csc_cfg.out_color_range = data->config.color_range;
        de_al_mgr_apply_color(screen_id, &csc_cfg);
    }

    if (data->flag & MANAGER_SIZE_DIRTY) {
        de_rtmx_set_blend_size(screen_id, data->config.size.width,
                       data->config.size.height);
        de_rtmx_set_display_size(screen_id, data->config.size.width,
                     data->config.size.height);
    }
    if (data->flag & MANAGER_ENABLE_DIRTY) {
        de_rtmx_set_enable(screen_id, data->config.enable);
#if !defined(HAVE_DEVICE_COMMON_MODULE)
        de_rtmx_mux(screen_id, data->config.hwdev_index);
#endif
        de_rtmx_set_outitl(screen_id, data->config.interlace);
    }

    if (data->flag & MANAGER_PALETTE_DIRTY) {
        de_rtmx_set_palette(screen_id, data->config.palette.channel,
                    data->config.palette.data,
                    data->config.palette.num);
    }
    return 0;
}

int de_al_mgr_sync(unsigned int screen_id)
{
    /* double register switch */
    return de_rtmx_set_dbuff_rdy(screen_id);
}

int de_al_mgr_update_regs(unsigned int screen_id)
{
    int ret = 0;

    de_rtmx_update_regs(screen_id);
    de_vsu_update_regs(screen_id);
    de_gsu_update_regs(screen_id);
    de_ccsc_update_regs(screen_id);
    de_dcsc_update_regs(screen_id);

    return ret;
}

/* query irq, if irq coming, return 1, and clear irq flga */
int de_al_query_irq(unsigned int screen_id)
{
    return de_rtmx_query_irq(screen_id);
}

int de_al_enable_irq(unsigned int screen_id, unsigned int en)
{
    return de_rtmx_enable_irq(screen_id, en);
}

int de_al_init(struct disp_bsp_init_para *para)
{
    int i;
    int num_screens = de_feat_get_num_screens();

#if defined(CONFIG_ARCH_SUN50IW10)
    for (i = 0; i < num_screens; i++) {
        de_rtmx_init(i, para->reg_base[DISP_MOD_DE + i]);
        de_vsu_init(i, para->reg_base[DISP_MOD_DE + i]);
        de_gsu_init(i, para->reg_base[DISP_MOD_DE + i]);
    }
#else
    for (i = 0; i < num_screens; i++) {
        de_rtmx_init(i, para->reg_base[DISP_MOD_DE]);
        de_vsu_init(i, para->reg_base[DISP_MOD_DE]);
        de_gsu_init(i, para->reg_base[DISP_MOD_DE]);
    }
#endif
    return 0;
}

int de_al_exit(void)
{
    int i;
    int num_screens = de_feat_get_num_screens();

    for (i = 0; i < num_screens; i++) {
        de_gsu_exit(i);
        de_vsu_exit(i);
        de_rtmx_exit(i);
    }

    return 0;
}

