/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include "disp_al.h"
#include "de_hal.h"
#include "../disp_features.h"

#if defined(CONFIG_ARCH_SUN8IW12)
#define DISP2_TCON_TV_SYNC_POL_ISSUE
#endif /*endif CONFIG_ARCH_SUN8IW12P1 */

/*
 * disp_al_private_data - abstract layer private data
 * @output_type: current output type of specified device(eg. LCD/HDMI/TV)
 * @output_mode: current output mode of specified device(eg. 720P,1080P)
 * @output_cs: current output color space of specified device
 * @tcon_id: the id of device connect to the specified de
 * @de_id: the id of de connect to the specified tcon
 * @disp_size: the output size of specified de
 * @output_fps: the output fps of specified device
 * @tcon_type: tcon type, 0: tcon0(drive panel), 1: tcon1(general drive HDMI/TV)
 * @direct_show: indicate if enable direct show function(bypass all CSCs)
 * @direct_show_toggle: indicate if direct show state change
 */
struct disp_al_private_data {
    u32 output_type[DEVICE_NUM];
    u32 output_mode[DEVICE_NUM];
    u32 output_cs[DEVICE_NUM];
    u32 output_color_range[DEVICE_NUM];
    u32 tcon_id[DE_NUM];
    u32 de_id[DEVICE_NUM];
    struct disp_rect disp_size[DE_NUM];
    u32 output_fps[DEVICE_NUM];
    u32 tcon_type[DEVICE_NUM];
    u32 de_backcolor[DE_NUM];
    bool direct_show[DE_NUM];
    bool direct_show_toggle[DE_NUM];
};

static struct disp_al_private_data al_priv;

#ifdef SUPPORT_WB   /*DE write back function, just for eink 32bpp to 8bpp*/
int disp_al_set_rtmx_base(u32 disp, unsigned int base)
{
    return rtmx_set_base(base);
}

int disp_al_rtmx_init(u32 disp, unsigned int addr0, unsigned int addr1,
            unsigned int addr2, unsigned int w, unsigned int h,
            unsigned int outw, unsigned int outh, unsigned int fmt)
{
    rt_mixer_init(disp, addr0, addr1, addr2, w, h, outw, outh, fmt);
    return 0;
}

int disp_al_rtmx_set_addr(u32 disp, unsigned int addr0)
{
    rt_mixer_set_addr(disp, addr0);
    return 0;
}

int disp_al_set_eink_wb_base(u32 disp, unsigned int base)
{
    return wb_eink_set_reg_base(disp, base);
}

int disp_al_set_eink_wb_param(u32 disp, unsigned int w,
                unsigned int h, unsigned int addr)
{
    __einkwb_config_t wbcfg;

    wbcfg.width = w;
    wbcfg.height = h;
    wbcfg.addr[0] = addr;
    wbcfg.addr[1] = 0;
    wbcfg.addr[2] = 0;
    wbcfg.csc_std = 2;
    return wb_eink_set_para(0, &wbcfg);
}

int disp_al_enable_eink_wb_interrupt(u32 disp)
{
    return wb_eink_enableint(disp);
}

int disp_al_disable_eink_wb_interrupt(u32 disp)
{

    return wb_eink_disableint(disp);
}

int disp_al_clear_eink_wb_interrupt(u32 disp)
{
    return wb_eink_clearint(disp);
}

int disp_al_enable_eink_wb(u32 disp)
{
    return wb_eink_writeback_enable(disp);
}

int disp_al_disable_eink_wb(u32 disp)
{
    return wb_eink_close(disp);
}

int disp_al_eink_wb_reset(u32 disp)
{
    return wb_eink_reset(disp);
}

int disp_al_eink_wb_dereset(u32 disp)
{
    return wb_eink_dereset(disp);
}


int disp_al_get_eink_wb_status(u32 disp)
{
    return wb_eink_get_status(disp);
}
#endif

#if defined(CONFIG_EINK_PANEL_USED)
int disp_al_set_eink_base(u32 disp, unsigned long base)
{
    return eink_set_base(base);
}

int disp_al_eink_irq_enable(u32 disp)
{
    return eink_irq_enable();
}

int disp_al_eink_irq_disable(u32 disp)
{
    return eink_irq_disable();
}

/*return: 0,decode int; 1:index_calc int; -1 error*/
int disp_al_eink_irq_query(u32 disp)
{
    /*clear interrupt*/
    return eink_irq_query();
}


int disp_al_eink_config(u32 disp, struct eink_init_param *param)
{

    eink_config(param->eink_bits, param->eink_mode);
    return 0;
}


int disp_al_eink_disable(u32 disp)
{
    return 0;

}


s32 disp_al_eink_start_calculate_index(u32 disp,
                    unsigned long old_index_data_paddr,
                    unsigned long new_index_data_paddr,
                    struct eink_8bpp_image *last_image,
                    struct eink_8bpp_image *current_image)
{
    struct ee_img tcurrent_img, tlast_img;
    struct area_info update_area;

    unsigned char  flash_mode, win_en;

    tcurrent_img.addr = (unsigned long)current_image->paddr;/*image_addr*/
    tcurrent_img.w = current_image->size.width;
    tcurrent_img.h = current_image->size.height;
    tcurrent_img.pitch = DISPALIGN(current_image->size.width,
                    current_image->size.align);

    tlast_img.addr = (unsigned long)last_image->paddr;
    tlast_img.w = last_image->size.width;
    tlast_img.h = last_image->size.height;
    tlast_img.pitch = DISPALIGN(last_image->size.width,
                    last_image->size.align);

    flash_mode = current_image->flash_mode;
    win_en = current_image->window_calc_enable;

    memcpy((void *)&update_area, (void *)&current_image->update_area,
                    sizeof(struct area_info));

    eink_start_idx(&tlast_img, &tcurrent_img, flash_mode, win_en,
                    old_index_data_paddr,
                    new_index_data_paddr, &update_area);

    return 0;
}

int disp_al_is_calculate_index_finish(unsigned int disp)
{
#if 1
    return eink_index_finish();
#else
    int ret = eink_irq_query();

    return ((ret == 1)?1:0);
#endif
}

int disp_al_get_update_area(unsigned int disp, struct area_info *area)
{
    return eink_get_updata_area(area);
}


int disp_al_eink_pipe_enable(u32 disp, unsigned int pipe_no)
{
    return eink_pipe_enable(pipe_no);
}

int disp_al_eink_pipe_disable(u32 disp, unsigned int pipe_no)
{

    return eink_pipe_disable(pipe_no);
}

int disp_al_eink_pipe_config(u32 disp,  unsigned int pipe_no,
                    struct area_info area)
{
    return eink_pipe_config(&area, pipe_no);

}

int disp_al_eink_pipe_config_wavefile(u32 disp, unsigned int wav_file_addr,
                        unsigned int pipe_no)
{

    return eink_pipe_config_wavefile(wav_file_addr, pipe_no);
}

int disp_al_eink_start_decode(unsigned int disp, unsigned long new_idx_addr,
                        unsigned long wav_data_addr,
                        struct eink_init_param *param)
{
    return eink_decoder_start(new_idx_addr, wav_data_addr, param);
}

int disp_al_edma_init(unsigned int disp, struct eink_init_param *param)
{

    return eink_edma_init(param->eink_mode);
}

int disp_al_eink_edma_cfg_addr(unsigned int disp, unsigned long wav_addr)
{
    return  eink_edma_cfg_addr(wav_addr);
}


int disp_al_edma_config(unsigned int disp, unsigned long wave_data_addr,
                        struct eink_init_param *param)
{

    return eink_edma_cfg(wave_data_addr, param);
}

int disp_al_edma_write(unsigned int disp, unsigned char en)
{

    return eink_edma_en(en);
}

int disp_al_dbuf_rdy(void)
{
    return eink_dbuf_rdy();
}

int disp_al_eink_set_wb(unsigned char wb_en, unsigned int wb_addr)
{
    /* edma write back */
    return eink_set_wb(wb_en, wb_addr);
}

int disp_al_init_waveform(const char *path)
{
    return init_waveform(path);
}

void disp_al_free_waveform(void)
{
    free_waveform();
}


int disp_al_get_waveform_data(unsigned int disp, enum eink_update_mode mode,
                unsigned int temp, unsigned int *total_frames,
                            unsigned int *wf_buf)
{
    return get_waveform_data(mode, temp, total_frames, wf_buf);
}

int disp_al_get_eink_panel_bit_num(unsigned int disp,
                    enum eink_bit_num *bit_num)
{
    return get_eink_panel_bit_num(bit_num);
}

int disp_al_init_eink_ctrl_data_8(unsigned int disp, unsigned long wavedata_buf,
                struct eink_timing_param *eink_timing_info,
                unsigned int i)
{
    return init_eink_ctrl_data_8(wavedata_buf, eink_timing_info, i);

}

int disp_al_init_eink_ctrl_data_16(unsigned int disp, unsigned int wavedata_buf,
                struct eink_timing_param *eink_timing_info)
{
    return init_eink_ctrl_data_16(wavedata_buf, eink_timing_info);

}
#endif

static int disp_al_validate_direct_show(unsigned int disp,
            struct disp_layer_config_data *data,
            unsigned int layer_num)
{
    int tcon_id = al_priv.tcon_id[disp];
    bool direct_show = true;
    unsigned char i, vi_chn;

    /*
     * We need to check several conditions:
     * 1, the output must be TV(PAL/NTSC) type
     * 2, the output must be in yuv color space,
     * 3, only video channels are used,
     * 4, input format must be yuv format.
     * 5, input layer size must be in the p2p limit range
     * 6, the layer must be display on the fullscreen or non-scalely
     */
    if (al_priv.output_type[tcon_id] != DISP_OUTPUT_TYPE_TV) {
        direct_show = false;
        goto exit;
    }

    if ((al_priv.disp_size[disp].width != CVBS_PAL_WIDTH)
        && (al_priv.disp_size[disp].width != CVBS_NTSC_WIDTH)) {
        direct_show = false;
        goto exit;
    }

    if ((al_priv.disp_size[disp].height != CVBS_PAL_HEIGHT)
        && (al_priv.disp_size[disp].height != CVBS_NTSC_HEIGHT)) {
        direct_show = false;
        goto exit;
    }

    if (al_priv.output_cs[tcon_id] != 1) {
        direct_show = false;
        goto exit;
    }

    vi_chn = de_feat_get_num_vi_chns(disp);
    for (i = 0; i < layer_num; i++, data++) {
        struct disp_rect64 *crop64;
        struct disp_rect crop;
        struct disp_rect *screen_win;

        if (!data->config.enable)
            continue;

        if (data->config.channel >= vi_chn) {
            direct_show = false;
            goto exit;
        }

        if (data->config.info.fb.format < DISP_FORMAT_YUV444_I_AYUV) {
            direct_show = false;
            goto exit;
        }

        crop64 = &data->config.info.fb.crop;
        crop.x = crop64->x >> VSU_FB_FRAC_BITWIDTH;
        crop.y = crop64->y >> VSU_FB_FRAC_BITWIDTH;
        crop.width = crop64->width >> VSU_FB_FRAC_BITWIDTH;
        crop.height = crop64->height >> VSU_FB_FRAC_BITWIDTH;
        if ((crop.width < P2P_FB_MIN_WIDTH)
            || (crop.width > P2P_FB_MAX_WIDTH)) {
            direct_show = false;
            goto exit;
        }

        if (crop.height != al_priv.disp_size[disp].height) {
            direct_show = false;
            goto exit;
        }

        screen_win = &data->config.info.screen_win;
        if ((screen_win->width != al_priv.disp_size[disp].width)
            && (screen_win->width != crop.width)) {
            direct_show = false;
            goto exit;
        }

        if ((screen_win->height != al_priv.disp_size[disp].height)
            && (screen_win->height != crop.height)) {
            direct_show = false;
            goto exit;
        }
    }

exit:
    if (al_priv.direct_show[disp] != direct_show)
        al_priv.direct_show_toggle[disp] = true;
    else
        al_priv.direct_show_toggle[disp] = false;
    al_priv.direct_show[disp] = direct_show;

    return 0;
}

bool disp_al_get_direct_show_state(unsigned int disp)
{
    return al_priv.direct_show[disp];
}

int disp_al_layer_apply(unsigned int disp, struct disp_layer_config_data *data,
            unsigned int layer_num)
{
    bool direct_show;

    disp_al_validate_direct_show(disp, data, layer_num);
    direct_show = al_priv.direct_show[disp];

    /*
     * If direct_show_toggle, we need to update the output cs of de .
     * When direct_show enable, we need to disable csc function,
     * And when direct show disable, we need to enable csc function as usual
     */
    if (al_priv.direct_show_toggle[disp]) {
        struct disp_csc_config csc_cfg;

        memset(&csc_cfg, 0, sizeof(struct disp_csc_config));
        if (direct_show) {
            csc_cfg.out_fmt = DE_RGB;
            csc_cfg.out_color_range = DISP_COLOR_RANGE_0_255;
            csc_cfg.color = (16 << 16) | (128 << 8) | (128);
        } else {
            int tcon_id = al_priv.tcon_id[disp];

            csc_cfg.out_fmt = al_priv.output_cs[tcon_id];
            if ((al_priv.disp_size[disp].width < 1280)
                && (al_priv.disp_size[disp].height < 720))
                csc_cfg.out_mode = DE_BT601;
            else
                csc_cfg.out_mode = DE_BT709;
            csc_cfg.out_color_range =
                al_priv.output_color_range[tcon_id];
            csc_cfg.color = al_priv.de_backcolor[disp];
        }
        de_al_mgr_apply_color(disp, &csc_cfg);
    }
    return de_al_lyr_apply(disp, data, layer_num, direct_show);
}

int disp_al_manager_init(unsigned int disp)
{
    return de_clk_enable(DE_CLK_CORE0 + disp);
}

int disp_al_manager_exit(unsigned int disp)
{
    return de_clk_disable(DE_CLK_CORE0 + disp);
}

int disp_al_de_clk_enable(unsigned int disp)
{
    return de_clk_enable(DE_CLK_CORE0 + disp);
}

int disp_al_de_clk_disable(unsigned int disp)
{
    return de_clk_disable(DE_CLK_CORE0 + disp);
}
int disp_al_manager_apply(unsigned int disp, struct disp_manager_data *data)
{
    if (data->flag & MANAGER_ENABLE_DIRTY) {
        struct disp_color *back_color = &data->config.back_color;

        al_priv.disp_size[disp].width = data->config.size.width;
        al_priv.disp_size[disp].height = data->config.size.height;
        al_priv.tcon_id[disp] = data->config.hwdev_index;
        al_priv.de_id[al_priv.tcon_id[disp]] = disp;
        al_priv.output_cs[al_priv.tcon_id[disp]] = data->config.cs;
        al_priv.output_color_range[al_priv.tcon_id[disp]] =
            data->config.color_range;
        al_priv.de_backcolor[disp] =
            (back_color->alpha << 24) | (back_color->red << 16)
            | (back_color->green << 8) | (back_color->blue << 0);
    }

    if (al_priv.output_type[al_priv.tcon_id[disp]] ==
        (u32) DISP_OUTPUT_TYPE_HDMI) {
#ifdef BYPASS_TCON_CEU
        tcon1_hdmi_color_remap(al_priv.tcon_id[disp], 0,
                           data->config.cs);

#else
        /*
         * If yuv output(cs != 0), remap yuv plane to (v y u) sequency
         * else disable color remap function
         */
        if (data->config.cs != 0)
            tcon1_hdmi_color_remap(al_priv.tcon_id[disp], 1,
                           data->config.cs);
        else
            tcon1_hdmi_color_remap(al_priv.tcon_id[disp], 0,
                           data->config.cs);
#endif
    }
    de_update_clk_rate(data->config.de_freq);

    return de_al_mgr_apply(disp, data);
}

int disp_al_manager_sync(unsigned int disp)
{
    return de_al_mgr_sync(disp);
}

int disp_al_manager_update_regs(unsigned int disp)
{
    return de_al_mgr_update_regs(disp);
}

int disp_al_manager_query_irq(unsigned int disp)
{
    return de_al_query_irq(disp);
}

int disp_al_manager_enable_irq(unsigned int disp)
{
    return de_al_enable_irq(disp, 1);
}

int disp_al_manager_disable_irq(unsigned int disp)
{
    return de_al_enable_irq(disp, 0);
}

int disp_al_enhance_apply(unsigned int disp, struct disp_enhance_config *config)
{
    if (config->flags & ENH_MODE_DIRTY) {
        struct disp_csc_config csc_config;

        de_dcsc_get_config(disp, &csc_config);
        csc_config.enhance_mode = (config->info.mode >> 16);
        de_dcsc_apply(disp, &csc_config);
    }

    return de_enhance_apply(disp, config);
}

int disp_al_enhance_update_regs(unsigned int disp)
{
    return de_enhance_update_regs(disp);
}

int disp_al_enhance_sync(unsigned int disp)
{
    return de_enhance_sync(disp);
}

int disp_al_enhance_tasklet(unsigned int disp)
{
    return de_enhance_tasklet(disp);
}

#ifndef CONFIG_EINK200_SUNXI
int disp_al_capture_init(unsigned int disp)
{
    int ret = -1;

    ret = de_clk_enable(DE_CLK_WB);
    ret = wb_input_select(disp);
    return ret;
}

int disp_al_capture_exit(unsigned int disp)
{
    return de_clk_disable(DE_CLK_WB);
}

int disp_al_capture_sync(u32 disp)
{
    wb_ebios_update_regs(disp);
    wb_ebios_enableint(disp);
    wb_ebios_writeback_enable(disp, 1);

    return 0;
}

int disp_al_capture_apply(unsigned int disp, struct disp_capture_config *cfg)
{
    return wb_ebios_apply(disp, cfg);
}

int disp_al_capture_get_status(unsigned int disp)
{
    return wb_ebios_get_status(disp);
}

int disp_al_write_back_clk_init(unsigned int disp)
{
    return de_clk_enable(DE_CLK_WB);
}

int disp_al_write_back_clk_exit(unsigned int disp)
{
    return de_clk_disable(DE_CLK_WB);
}
#else
int disp_al_capture_init(unsigned int disp)
{
    return 0;
}

int disp_al_capture_exit(unsigned int disp)
{
    return 0;
}

int disp_al_capture_sync(u32 disp)
{
    return 0;
}

int disp_al_capture_apply(unsigned int disp, struct disp_capture_config *cfg)
{
    return 0;
}

int disp_al_capture_get_status(unsigned int disp)
{
    return 0;
}

int disp_al_write_back_clk_init(unsigned int disp)
{
    return 0;
}

int disp_al_write_back_clk_exit(unsigned int disp)
{
    return 0;
}
#endif

int disp_al_smbl_apply(unsigned int disp, struct disp_smbl_info *info)
{
    return de_smbl_apply(disp, info);
}

int disp_al_smbl_update_regs(unsigned int disp)
{
    return de_smbl_update_regs(disp);
}

int disp_al_smbl_sync(unsigned int disp)
{
    return 0;
}

int disp_al_smbl_tasklet(unsigned int disp)
{
    return de_smbl_tasklet(disp);
}

int disp_al_smbl_get_status(unsigned int disp)
{
    return de_smbl_get_status(disp);
}

#ifdef CONFIG_FPGA_V4_PLATFORM
static struct lcd_clk_info clk_tbl[] = {
    {LCD_IF_HV,    0x12, 1, 1, 0},
    {LCD_IF_CPU,   12, 1, 1, 0},
    {LCD_IF_LVDS,   7, 1, 1, 0},
    {LCD_IF_DSI,    4, 1, 4, 0},
};
#else
static struct lcd_clk_info clk_tbl[] = {
    {LCD_IF_HV, 0x12, 1, 1, 0},
    {LCD_IF_CPU, 12, 1, 1, 0},
    {LCD_IF_LVDS, 7, 1, 1, 0},
#if defined(DSI_VERSION_40)
    {LCD_IF_DSI, 4, 1, 4, 148500000},
#else
    {LCD_IF_DSI, 4, 1, 4, 0},
#endif /*endif DSI_VERSION_40*/
    {LCD_IF_VDPO, 4, 1, 1, 0},
};
#endif
/* lcd */
/* lcd_dclk_freq * div -> lcd_clk_freq * div2 -> pll_freq */
/* lcd_dclk_freq * dsi_div -> lcd_dsi_freq */
int disp_al_lcd_get_clk_info(u32 screen_id, struct lcd_clk_info *info,
                 struct disp_panel_para *panel)
{
    int tcon_div = 6;
    int lcd_div = 1;
    int dsi_div = 4;
    int dsi_rate = 0;
    int i;
    int find = 0;

    if (panel == NULL) {
        DE_WRN("panel is NULL\n");
        return 0;
    }

    for (i = 0; i < sizeof(clk_tbl) / sizeof(struct lcd_clk_info); i++) {
        if (clk_tbl[i].lcd_if == panel->lcd_if) {
            tcon_div = clk_tbl[i].tcon_div;
            lcd_div = clk_tbl[i].lcd_div;
            dsi_div = clk_tbl[i].dsi_div;
            dsi_rate = clk_tbl[i].dsi_rate;
            find = 1;
            break;
        }
    }

#if defined(DSI_VERSION_40)
    if (panel->lcd_if == LCD_IF_DSI) {
        u32 lane = panel->lcd_dsi_lane;
        u32 bitwidth = 0;

        switch (panel->lcd_dsi_format) {
        case LCD_DSI_FORMAT_RGB888:
            bitwidth = 24;
            break;
        case LCD_DSI_FORMAT_RGB666:
            bitwidth = 24;
            break;
        case LCD_DSI_FORMAT_RGB565:
            bitwidth = 16;
            break;
        case LCD_DSI_FORMAT_RGB666P:
            bitwidth = 18;
            break;
        }

        dsi_div = bitwidth / lane;
        if (panel->lcd_dsi_if == LCD_DSI_IF_COMMAND_MODE) {
            tcon_div = dsi_div;
        }
    }
#endif

    if (find == 0)
        DE_WRN("cant find clk info for lcd_if %d\n", panel->lcd_if);

#if defined(CONFIG_FPGA_V4_PLATFORM) && defined(CONFIG_EINK_PANEL_USED)
    if (panel->lcd_dclk_freq < 10) {
        tcon_div = 30;
        lcd_div = 1;
    } else if (panel->lcd_dclk_freq < 40 && panel->lcd_dclk_freq >= 10) {
        tcon_div = 10;
        lcd_div = 1;
    } else {
        tcon_div = 6;
        lcd_div = 1;
    }
#endif
    if (panel->lcd_if == LCD_IF_HV &&
        panel->lcd_hv_if == LCD_HV_IF_CCIR656_2CYC &&
        panel->ccir_clk_div > 0)
        tcon_div = panel->ccir_clk_div;
    else if (panel->lcd_tcon_mode == DISP_TCON_DUAL_DSI &&
         panel->lcd_if == LCD_IF_DSI) {
        tcon_div = tcon_div / 2;
        dsi_div /= 2;
    }

#if defined(DSI_VERSION_28)
    if (panel->lcd_if == LCD_IF_DSI &&
        panel->lcd_dsi_if == LCD_DSI_IF_COMMAND_MODE) {
        tcon_div = 6;
        dsi_div = 6;
    }
#endif

    info->tcon_div = tcon_div;
    info->lcd_div = lcd_div;
    info->dsi_div = dsi_div;
    info->dsi_rate = dsi_rate;

    return 0;
}

int disp_al_lcd_cfg(u32 screen_id, struct disp_panel_para *panel,
            struct panel_extend_para *extend_panel)
{
    struct lcd_clk_info info;

    al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_LCD;
    al_priv.output_mode[screen_id] = (u32) panel->lcd_if;
    al_priv.output_fps[screen_id] =
        panel->lcd_dclk_freq * 1000000 / panel->lcd_ht / panel->lcd_vt;

#if defined(CONFIG_EINK_PANEL_USED)
        if (al_priv.output_fps[screen_id] > 30)
            al_priv.output_fps[screen_id] = 30;
#endif

    de_update_device_fps(al_priv.de_id[screen_id],
                 al_priv.output_fps[screen_id]);

    tcon_init(screen_id);
    disp_al_lcd_get_clk_info(screen_id, &info, panel);
    tcon0_set_dclk_div(screen_id, info.tcon_div);

#if !defined(TCON1_DRIVE_PANEL)
    al_priv.tcon_type[screen_id] = 0;
    if (tcon0_cfg(screen_id, panel) != 0)
        DE_WRN("lcd cfg fail!\n");
    else
        DE_INF("lcd cfg ok!\n");

    tcon0_cfg_ext(screen_id, extend_panel);
    tcon0_src_select(screen_id, LCD_SRC_DE, al_priv.de_id[screen_id]);

    if (panel->lcd_if == LCD_IF_DSI)    {
#if defined(SUPPORT_DSI)
        if (panel->lcd_if == LCD_IF_DSI) {
            if (dsi_cfg(screen_id, panel) != 0)
                DE_WRN("dsi %d cfg fail!\n", screen_id);
            if (panel->lcd_tcon_mode == DISP_TCON_DUAL_DSI &&
                screen_id + 1 < DEVICE_DSI_NUM) {
                if (dsi_cfg(screen_id + 1, panel) != 0)
                    DE_WRN("dsi %d cfg fail!\n",
                           screen_id + 1);
            }
        }
#endif
    }
#else

    /* There is no tcon0 on this platform,
     * At fpga period, we can use tcon1 to driver lcd pnael,
     * so, here we need to config tcon1 here.
     */
    al_priv.tcon_type[screen_id] = 1;
    if (tcon1_cfg_ex(screen_id, panel) != 0)
        DE_WRN("lcd cfg fail!\n");
    else
        DE_INF("lcd cfg ok!\n");
#endif
    return 0;
}

int disp_al_lcd_cfg_ext(u32 screen_id, struct panel_extend_para *extend_panel)
{
    tcon0_cfg_ext(screen_id, extend_panel);

    return 0;
}

int disp_al_lcd_enable(u32 screen_id, struct disp_panel_para *panel)
{
#if !defined(TCON1_DRIVE_PANEL)

    tcon0_open(screen_id, panel);
    if (panel->lcd_if == LCD_IF_LVDS) {
        lvds_open(screen_id, panel);
    } else if (panel->lcd_if == LCD_IF_DSI) {
#if defined(SUPPORT_DSI)
        dsi_open(screen_id, panel);
        if (panel->lcd_tcon_mode == DISP_TCON_DUAL_DSI &&
            screen_id + 1 < DEVICE_DSI_NUM)
            dsi_open(screen_id + 1, panel);
#endif
    }

#else
    /* There is no tcon0 on this platform,
     * At fpga period, we can use tcon1 to driver lcd pnael,
     * so, here we need to open tcon1 here.
     */
    tcon1_open(screen_id);
#endif

    return 0;
}

int disp_al_lcd_disable(u32 screen_id, struct disp_panel_para *panel)
{
    al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_NONE;

#if !defined(TCON1_DRIVE_PANEL)

    if (panel->lcd_if == LCD_IF_LVDS) {
        lvds_close(screen_id);
    } else if (panel->lcd_if == LCD_IF_DSI) {
#if defined(SUPPORT_DSI)
        dsi_close(screen_id);
        if (panel->lcd_tcon_mode == DISP_TCON_DUAL_DSI &&
            screen_id + 1 < DEVICE_DSI_NUM)
            dsi_close(screen_id + 1);

#endif
    }
    tcon0_close(screen_id);
#else
    /* There is no tcon0 on platform sun50iw2,
     * on fpga period, we can use tcon1 to driver lcd pnael,
     * so, here we need to close tcon1.
     */
    tcon1_close(screen_id);
#endif
    tcon_exit(screen_id);

    return 0;
}

/* query lcd irq, clear it when the irq queried exist
 */
int disp_al_lcd_query_irq(u32 screen_id, enum __lcd_irq_id_t irq_id,
              struct disp_panel_para *panel)
{
    int ret = 0;

#if defined(SUPPORT_DSI) && defined(DSI_VERSION_40)
    if (panel->lcd_if == LCD_IF_DSI &&
        panel->lcd_dsi_if != LCD_DSI_IF_COMMAND_MODE) {
        enum __dsi_irq_id_t dsi_irq =
            (irq_id == LCD_IRQ_TCON0_VBLK) ?
            DSI_IRQ_VIDEO_VBLK : DSI_IRQ_VIDEO_LINE;

        ret = dsi_irq_query(screen_id, dsi_irq);
    } else
#endif
        ret = tcon_irq_query(screen_id,
                (al_priv.tcon_type[screen_id] == 0) ?
                irq_id : LCD_IRQ_TCON1_VBLK);

    return ret;
}

int disp_al_lcd_enable_irq(u32 screen_id, enum __lcd_irq_id_t irq_id,
               struct disp_panel_para *panel)
{
    int ret = 0;

#if defined(SUPPORT_DSI) && defined(DSI_VERSION_40)
    if (panel->lcd_if == LCD_IF_DSI) {
        enum __dsi_irq_id_t dsi_irq =
            (irq_id == LCD_IRQ_TCON0_VBLK) ?
            DSI_IRQ_VIDEO_VBLK : DSI_IRQ_VIDEO_LINE;

        ret = dsi_irq_enable(screen_id, dsi_irq);
    } else
#endif
        ret =
            tcon_irq_enable(screen_id,
                    (al_priv.tcon_type[screen_id] ==
                     0) ? irq_id : LCD_IRQ_TCON1_VBLK);

    return ret;
}

int disp_al_lcd_disable_irq(u32 screen_id, enum __lcd_irq_id_t irq_id,
                struct disp_panel_para *panel)
{
    int ret = 0;

#if defined(SUPPORT_DSI) && defined(DSI_VERSION_40)
    if (panel->lcd_if == LCD_IF_DSI) {
        enum __dsi_irq_id_t dsi_irq =
            (irq_id == LCD_IRQ_TCON0_VBLK) ?
            DSI_IRQ_VIDEO_VBLK : DSI_IRQ_VIDEO_LINE;

        ret = dsi_irq_disable(screen_id, dsi_irq);
    } else
#endif
        ret =
            tcon_irq_disable(screen_id,
                     (al_priv.tcon_type[screen_id] ==
                      0) ? irq_id : LCD_IRQ_TCON1_VBLK);

    return ret;
}

int disp_al_lcd_tri_busy(u32 screen_id, struct disp_panel_para *panel)
{
    int busy = 0;
    int ret = 0;

    busy |= tcon0_tri_busy(screen_id);
#if defined(SUPPORT_DSI)
    if (panel->lcd_if == LCD_IF_DSI)
        busy |= dsi_inst_busy(screen_id);
#endif
    ret = (busy == 0) ? 0 : 1;

    return ret;
}

/* take dsi irq s32o account, todo? */
int disp_al_lcd_tri_start(u32 screen_id, struct disp_panel_para *panel)
{
#if defined(SUPPORT_DSI) && defined(DSI_VERSION_40)
    if (panel->lcd_if == LCD_IF_DSI)
        dsi_tri_start(screen_id);
#endif
    return tcon0_tri_start(screen_id);
}

int disp_al_lcd_io_cfg(u32 screen_id, u32 enable, struct disp_panel_para *panel)
{
#if defined(SUPPORT_DSI)
    if (panel->lcd_if == LCD_IF_DSI) {
        if (enable == 1) {
            dsi_io_open(screen_id, panel);
            if (panel->lcd_tcon_mode == DISP_TCON_DUAL_DSI &&
                screen_id + 1 < DEVICE_DSI_NUM)
                dsi_io_open(screen_id + 1, panel);
        } else {
            dsi_io_close(screen_id);
            if (panel->lcd_tcon_mode == DISP_TCON_DUAL_DSI &&
                screen_id + 1 < DEVICE_DSI_NUM)
                dsi_io_close(screen_id + 1);
        }
    }
#endif

    return 0;
}

int disp_al_lcd_get_cur_line(u32 screen_id, struct disp_panel_para *panel)
{
#if defined(SUPPORT_DSI) && defined(DSI_VERSION_40)
    if (panel->lcd_if == LCD_IF_DSI)
        return dsi_get_cur_line(screen_id);
#endif

    return tcon_get_cur_line(screen_id,
                 al_priv.tcon_type[screen_id]);
}

int disp_al_lcd_get_start_delay(u32 screen_id, struct disp_panel_para *panel)
{
#if defined(SUPPORT_DSI) && defined(DSI_VERSION_40)
    u32 lcd_start_delay = 0;
    u32 de_clk_rate = de_get_clk_rate() / 1000000;

    if (panel && panel->lcd_if == LCD_IF_DSI) {
        lcd_start_delay =
            ((tcon0_get_cpu_tri2_start_delay(screen_id) + 1) << 3) *
            (panel->lcd_dclk_freq) / (panel->lcd_ht * de_clk_rate);
        return lcd_start_delay;
    } else
#endif
    return tcon_get_start_delay(screen_id,
                    al_priv.tcon_type[screen_id]);
}

/* hdmi */
int disp_al_hdmi_enable(u32 screen_id)
{
    tcon1_hdmi_clk_enable(screen_id, 1);

    tcon1_open(screen_id);
    return 0;
}

int disp_al_hdmi_disable(u32 screen_id)
{
    al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_NONE;

    tcon1_close(screen_id);
    tcon_exit(screen_id);
    tcon1_hdmi_clk_enable(screen_id, 0);

    return 0;
}

int disp_al_hdmi_cfg(u32 screen_id, struct disp_video_timings *video_info)
{
    al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_HDMI;
    al_priv.output_mode[screen_id] = (u32) video_info->vic;
    al_priv.output_fps[screen_id] =
        video_info->pixel_clk / video_info->hor_total_time /
        video_info->ver_total_time * (video_info->b_interlace +
                      1) / (video_info->trd_mode + 1);
    al_priv.tcon_type[screen_id] = 1;

    de_update_device_fps(al_priv.de_id[screen_id],
                 al_priv.output_fps[screen_id]);

    tcon_init(screen_id);
    tcon1_set_timming(screen_id, video_info);
#if defined(DISP2_TCON_TV_SYNC_POL_ISSUE)
    tcon_set_sync_pol(screen_id, !video_info->ver_sync_polarity,
              !video_info->hor_sync_polarity);
#endif /*endif DISP2_TCON_TV_SYNC_POL_ISSUE */

#ifdef TCON_POL_CORRECT
    tcon1_cfg_correct(screen_id, video_info);
#endif

#ifdef BYPASS_TCON_CEU
    tcon1_hdmi_color_remap(screen_id, 0,
               al_priv.output_cs[screen_id]);
#else
    /*
     * If yuv output(cs != 0), remap yuv plane to (v y u) sequency
     * else disable color remap function
     */
    if (al_priv.output_cs[screen_id] != 0)
        tcon1_hdmi_color_remap(screen_id, 1,
                       al_priv.output_cs[screen_id]);
    else
        tcon1_hdmi_color_remap(screen_id, 0,
                       al_priv.output_cs[screen_id]);
#endif
    tcon1_src_select(screen_id, LCD_SRC_DE, al_priv.de_id[screen_id]);

    return 0;
}

int disp_al_hdmi_irq_enable(u32 screen_id)
{
    tcon_irq_enable(screen_id, LCD_IRQ_TCON1_VBLK);

    return 0;
}

int disp_al_hdmi_irq_disable(u32 screen_id)
{
    tcon_irq_disable(screen_id, LCD_IRQ_TCON1_VBLK);

    return 0;
}

int disp_al_hdmi_pad_sel(u32 screen_id, u32 pad)
{
    tcon_pan_sel(screen_id, pad);

    return 0;
}

/* tv */
int disp_al_tv_enable(u32 screen_id)
{
    tcon1_tv_clk_enable(screen_id, 1);
    tcon1_open(screen_id);

    return 0;
}

int disp_al_tv_disable(u32 screen_id)
{
    al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_NONE;

    tcon1_close(screen_id);
    tcon_exit(screen_id);
    tcon1_tv_clk_enable(screen_id, 0);

    return 0;
}

int disp_al_tv_cfg(u32 screen_id, struct disp_video_timings *video_info)
{
    unsigned int pixel_clk;

    pixel_clk = video_info->pixel_clk;
#if defined(TV_UGLY_CLK_RATE)
    pixel_clk = (pixel_clk == TV_UGLY_CLK_RATE) ?
        TV_COMPOSITE_CLK_RATE : pixel_clk;
#endif
    al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_TV;
    al_priv.output_mode[screen_id] = (u32) video_info->tv_mode;
    al_priv.output_fps[screen_id] =
        pixel_clk / video_info->hor_total_time
        / video_info->ver_total_time;
    al_priv.tcon_type[screen_id] = 1;

    de_update_device_fps(al_priv.de_id[screen_id],
                 al_priv.output_fps[screen_id]);

    tcon_init(screen_id);
    tcon1_set_timming(screen_id, video_info);
    tcon1_yuv_range(screen_id, 1);
    tcon1_src_select(screen_id, LCD_SRC_DE, al_priv.de_id[screen_id]);

    return 0;
}

int disp_al_tv_irq_enable(u32 screen_id)
{
    tcon_irq_enable(screen_id, LCD_IRQ_TCON1_VBLK);

    return 0;
}

int disp_al_tv_irq_disable(u32 screen_id)
{
    tcon_irq_disable(screen_id, LCD_IRQ_TCON1_VBLK);

    return 0;
}

#if defined(SUPPORT_VGA)
/* vga interface
 */
int disp_al_vga_enable(u32 screen_id)
{
    tcon1_tv_clk_enable(screen_id, 1);
    tcon1_open(screen_id);
    tcon1_out_to_gpio(screen_id);
    return 0;
}

int disp_al_vga_disable(u32 screen_id)
{
    al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_NONE;

    tcon1_close(screen_id);
    tcon_exit(screen_id);
    tcon1_tv_clk_enable(screen_id, 0);
    return 0;
}

int disp_al_vga_cfg(u32 screen_id, struct disp_video_timings *video_info)
{
    al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_VGA;
    al_priv.output_mode[screen_id] = (u32) video_info->tv_mode;
    al_priv.output_fps[screen_id] =
        video_info->pixel_clk / video_info->hor_total_time
        / video_info->ver_total_time;
    al_priv.tcon_type[screen_id] = 1;

    de_update_device_fps(al_priv.de_id[screen_id],
                 al_priv.output_fps[screen_id]);

    tcon_init(screen_id);
    tcon1_set_timming(screen_id, video_info);
    tcon1_src_select(screen_id, LCD_SRC_DE, al_priv.de_id[screen_id]);

    return 0;
}

int disp_al_vga_irq_enable(u32 screen_id)
{
    tcon_irq_enable(screen_id, LCD_IRQ_TCON1_VBLK);

    return 0;
}

int disp_al_vga_irq_disable(u32 screen_id)
{
    tcon_irq_disable(screen_id, LCD_IRQ_TCON1_VBLK);

    return 0;
}

#endif

int disp_al_vdevice_cfg(u32 screen_id, struct disp_video_timings *video_info,
            struct disp_vdevice_interface_para *para,
            u8 config_tcon_only)
{
    struct lcd_clk_info clk_info;
    struct disp_panel_para info;

    if (para->sub_intf == LCD_HV_IF_CCIR656_2CYC)
        al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_TV;
    else
        al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_LCD;
    al_priv.output_mode[screen_id] = (u32) para->intf;
    al_priv.output_fps[screen_id] =
        video_info->pixel_clk / video_info->hor_total_time
        / video_info->ver_total_time;
    al_priv.tcon_type[screen_id] = 0;

    de_update_device_fps(al_priv.de_id[screen_id],
                 al_priv.output_fps[screen_id]);

    memset(&info, 0, sizeof(struct disp_panel_para));
    info.lcd_if = para->intf;
    info.lcd_x = video_info->x_res;
    info.lcd_y = video_info->y_res;
    info.lcd_hv_if = (enum disp_lcd_hv_if) para->sub_intf;
    info.lcd_dclk_freq = video_info->pixel_clk;
    info.lcd_ht = video_info->hor_total_time;
    info.lcd_hbp = video_info->hor_back_porch + video_info->hor_sync_time;
    info.lcd_hspw = video_info->hor_sync_time;
    info.lcd_vt = video_info->ver_total_time;
    info.lcd_vbp = video_info->ver_back_porch + video_info->ver_sync_time;
    info.lcd_vspw = video_info->ver_sync_time;
    info.lcd_interlace = video_info->b_interlace;
    info.lcd_hv_syuv_fdly = para->fdelay;
    info.lcd_hv_clk_phase = para->clk_phase;
    info.lcd_hv_sync_polarity = para->sync_polarity;
    info.ccir_clk_div = para->ccir_clk_div;
    info.input_csc = para->input_csc;

    if (info.lcd_hv_if == LCD_HV_IF_CCIR656_2CYC)
        info.lcd_hv_syuv_seq = para->sequence;
    else
        info.lcd_hv_srgb_seq = para->sequence;
    tcon_init(screen_id);
    disp_al_lcd_get_clk_info(screen_id, &clk_info, &info);
    tcon0_set_dclk_div(screen_id, clk_info.tcon_div);

    if (para->sub_intf == LCD_HV_IF_CCIR656_2CYC)
        tcon1_yuv_range(screen_id, 1);
    if (tcon0_cfg(screen_id, &info) != 0)
        DE_WRN("lcd cfg fail!\n");
    else
        DE_INF("lcd cfg ok!\n");

    if (!config_tcon_only)
        tcon0_src_select(screen_id, LCD_SRC_DE,
                 al_priv.de_id[screen_id]);
    else
        DE_INF("%s:config_tcon_only is %d\n", __func__,
               config_tcon_only);

    return 0;
}

int disp_al_vdevice_enable(u32 screen_id)
{
    struct disp_panel_para panel;

    memset(&panel, 0, sizeof(struct disp_panel_para));
    panel.lcd_if = LCD_IF_HV;
    tcon0_open(screen_id, &panel);

    return 0;
}

int disp_al_vdevice_disable(u32 screen_id)
{
    al_priv.output_type[screen_id] = (u32) DISP_OUTPUT_TYPE_NONE;

    tcon0_close(screen_id);
    tcon_exit(screen_id);

    return 0;
}

/* screen_id: used for index of manager */
int disp_al_device_get_cur_line(u32 screen_id)
{
    u32 tcon_type = al_priv.tcon_type[screen_id];

    return tcon_get_cur_line(screen_id, tcon_type);
}

int disp_al_device_get_start_delay(u32 screen_id)
{
    u32 tcon_type = al_priv.tcon_type[screen_id];

    tcon_type = (al_priv.tcon_type[screen_id] == 0) ? 0 : 1;
    return tcon_get_start_delay(screen_id, tcon_type);
}

int disp_al_device_query_irq(u32 screen_id)
{
    int ret = 0;
    int irq_id = 0;

    irq_id = (al_priv.tcon_type[screen_id] == 0) ?
        LCD_IRQ_TCON0_VBLK : LCD_IRQ_TCON1_VBLK;
    ret = tcon_irq_query(screen_id, irq_id);

    return ret;
}

int disp_al_device_enable_irq(u32 screen_id)
{
    int ret = 0;
    int irq_id = 0;

    irq_id = (al_priv.tcon_type[screen_id] == 0) ?
        LCD_IRQ_TCON0_VBLK : LCD_IRQ_TCON1_VBLK;
    ret = tcon_irq_enable(screen_id, irq_id);

    return ret;
}

int disp_al_device_disable_irq(u32 screen_id)
{
    int ret = 0;
    int irq_id = 0;

    irq_id = (al_priv.tcon_type[screen_id] == 0) ?
        LCD_IRQ_TCON0_VBLK : LCD_IRQ_TCON1_VBLK;
    ret = tcon_irq_disable(screen_id, irq_id);

    return ret;
}

int disp_al_device_get_status(u32 screen_id)
{
    int ret = 0;

    ret = tcon_get_status(screen_id, al_priv.tcon_type[screen_id]);

    return ret;
}

int disp_al_device_src_select(u32 screen_id, u32 src)
{
    int ret = 0;

    return ret;
}

int disp_init_al(struct disp_bsp_init_para *para)
{
    int i;
    u32 hwdev_index = 0;

    memset(&al_priv, 0, sizeof(struct disp_al_private_data));
    de_al_init(para);
    de_enhance_init(para);
    de_ccsc_init(para);
    de_dcsc_init(para);
#if defined(CONFIG_EINK_PANEL_USED) || defined(CONFIG_EINK200_SUNXI)
#else
    wb_ebios_init(para);
#endif
    de_clk_set_reg_base(para->reg_base[DISP_MOD_DE]);
#if defined(CONFIG_ARCH_SUN50IW10)
    de1_clk_set_reg_base(para->reg_base[DISP_MOD_DE1]);
#endif


    for (i = 0; i < DEVICE_NUM; i++)
        tcon_set_reg_base(i, para->reg_base[DISP_MOD_LCD0 + i]);

    for (i = 0; i < DE_NUM; i++) {
        if (de_feat_is_support_smbl(i))
#if defined(CONFIG_ARCH_SUN50IW10)
            de_smbl_init(i, para->reg_base[DISP_MOD_DE + i]);
#else
            de_smbl_init(i, para->reg_base[DISP_MOD_DE]);
#endif
    }

#if defined(HAVE_DEVICE_COMMON_MODULE)
#if defined(CONFIG_ARCH_SUN50IW10)
    for (i = 0; i < DE_NUM; i++) {
        tcon_top_set_reg_base(i, para->reg_base[DISP_MOD_DEVICE + i]);
    }
#else
    tcon_top_set_reg_base(0, para->reg_base[DISP_MOD_DEVICE]);
#endif
#endif
#if defined(SUPPORT_DSI)
    for (i = 0; i < DEVICE_DSI_NUM; ++i)
        dsi_set_reg_base(i, para->reg_base[DISP_MOD_DSI0 + i]);
#endif

    if (para->boot_info.sync == 1) {
        u32 disp = para->boot_info.disp;
        u32 tcon_id;
        struct disp_video_timings tt;

        memset(&tt, 0, sizeof(struct disp_video_timings));
        i = 0;
        for (hwdev_index = 0; hwdev_index < DEVICE_NUM; ++hwdev_index) {
            if (!bsp_disp_feat_is_supported_output_types(
                hwdev_index, para->boot_info.type)) {
                continue;
            }
            if (disp != i) {
                ++i;
                continue;
            } else
                break;
        }
        if (hwdev_index == DEVICE_NUM) {
            DE_WRN("Can not find tcon index for smooth display\n");
            hwdev_index = 0;
        }
#if defined(HAVE_DEVICE_COMMON_MODULE)
        al_priv.tcon_id[disp] = hwdev_index;
#else
        al_priv.tcon_id[disp] = de_rtmx_get_mux(disp);
#endif
        tcon_id = al_priv.tcon_id[disp];

        /*
         * should take care about this,
         * extend display treated as a LCD OUTPUT
         */
        al_priv.output_type[tcon_id] = para->boot_info.type;
        al_priv.output_mode[tcon_id] = para->boot_info.mode;
        al_priv.tcon_type[tcon_id] = get_tcon_type_by_de_index(disp);

        de_rtmx_sync_hw(disp);
        de_rtmx_get_display_size(disp, &al_priv.disp_size[disp].width,
                     &al_priv.disp_size[disp].height);

        al_priv.output_fps[tcon_id] = 60;
        de_update_device_fps(disp, al_priv.output_fps[tcon_id]);
    }

    return 0;
}

int disp_exit_al(void)
{

#if defined(SUPPORT_SMBL)
    int i;
#endif /*endif SUPPORT_SMBL */

    de_al_exit();
    de_enhance_exit();
    de_ccsc_exit();
    de_dcsc_exit();
#if defined(CONFIG_EINK_PANEL_USED) || defined(CONFIG_EINK200_SUNXI)
#else
    wb_ebios_exit();
#endif

#if defined(SUPPORT_SMBL)
    for (i = 0; i < DE_NUM; i++) {
        if (de_feat_is_support_smbl(i))
            de_smbl_exit(i);
    }
#endif /*endif SUPPORT_SMBL */

    return 0;
}

int disp_al_get_display_size(unsigned int screen_id, unsigned int *width,
                 unsigned int *height)
{
    *width = al_priv.disp_size[screen_id].width;
    *height = al_priv.disp_size[screen_id].height;

    return 0;
}

/**
 * @name       :disp_al_vdpo_cfg
 * @brief      :config tcon(tcon_lcd or tcon_tv) and other data structure
 * @param[IN]  :screen_id:tcon index
 * @param[IN]  :video_info:timing info
 * @return     :0 if success else fail
 */
int disp_al_vdpo_cfg(u32 screen_id, u32 vdpo_index,
             struct disp_video_timings *video_info)
{
    struct lcd_clk_info clk_info;
    struct disp_panel_para panel;

    al_priv.output_type[screen_id] = (u32)DISP_OUTPUT_TYPE_VDPO;
    al_priv.output_mode[screen_id] = LCD_IF_HV;
    al_priv.output_fps[screen_id] =
        video_info->pixel_clk / video_info->hor_total_time /
        video_info->ver_total_time * (video_info->b_interlace + 1) /
        (video_info->trd_mode + 1);

    de_update_device_fps(al_priv.de_id[screen_id],
                 al_priv.output_fps[screen_id]);
    /*judge output type:tcon_lcd or tcon_tv*/
    if (de_feat_is_supported_output_types(screen_id,
                            DISP_OUTPUT_TYPE_LCD)) {
        al_priv.tcon_type[screen_id] = 0;
        memset(&panel, 0, sizeof(struct disp_panel_para));

        panel.lcd_if = LCD_IF_VDPO;
        panel.lcd_x = video_info->x_res;
        panel.lcd_y = video_info->y_res;
        panel.lcd_hv_if = LCD_HV_IF_PRGB_1CYC;
        panel.lcd_dclk_freq = video_info->pixel_clk;
        panel.lcd_ht = video_info->hor_total_time;
        panel.lcd_hbp =
            video_info->hor_back_porch + video_info->hor_sync_time;
        panel.lcd_hspw = video_info->hor_sync_time;
        panel.lcd_vt = video_info->ver_total_time;
        panel.lcd_vbp =
            video_info->ver_back_porch + video_info->ver_sync_time;
        panel.lcd_vspw = video_info->ver_sync_time;
        panel.lcd_interlace = video_info->b_interlace;
        panel.lcd_hv_syuv_fdly = 1; /*TODO*/
        panel.lcd_hv_clk_phase = 0;
        panel.lcd_hv_sync_polarity = 0;
        panel.lcd_hv_srgb_seq = 0;

        tcon_init(screen_id);
        disp_al_lcd_get_clk_info(screen_id, &clk_info, &panel);
        tcon0_set_dclk_div(screen_id, clk_info.tcon_div);
        if (tcon0_cfg(screen_id, &panel) != 0)
            DE_WRN("lcd cfg fail!\n");
        else
            DE_INF("lcd cfg ok!\n");

        tcon0_src_select(screen_id, LCD_SRC_DE,
                 al_priv.de_id[screen_id]);
    } else {
        tcon_init(screen_id);
        al_priv.tcon_type[screen_id] = 1;
        tcon1_set_timming(screen_id, video_info);
        vdpo_src_sel(vdpo_index, 1); /*use tcon_tv*/
        tcon1_src_select(screen_id, LCD_SRC_DE,
                 al_priv.de_id[screen_id]);
    }
    return 0;
}

/**
 * @name       :disp_al_vdpo_enable
 * @brief      :start tcon
 * @param[IN]  :screen_id:de index
 * @param[OUT] :
 * @return     :0
 */
int disp_al_vdpo_enable(u32 screen_id, u32 vdpo_index)
{
    struct disp_panel_para panel;

    if (de_feat_is_supported_output_types(screen_id,
                            DISP_OUTPUT_TYPE_LCD)) {
        memset(&panel, 0, sizeof(struct disp_panel_para));
        panel.lcd_if = LCD_IF_HV;
        tcon_vdpo_clk_enable(vdpo_index, 1);
        tcon0_open(screen_id, &panel);
    } else {
        tcon_vdpo_clk_enable(vdpo_index, 1);
        tcon1_open(screen_id);
    }

    return 0;
}

int disp_al_vdpo_disable(u32 screen_id)
{
    al_priv.output_type[screen_id] = (u32)DISP_OUTPUT_TYPE_NONE;
    if (de_feat_is_supported_output_types(screen_id,
                            DISP_OUTPUT_TYPE_LCD)) {
        tcon0_close(screen_id);
        tcon_exit(screen_id);
    } else {
        tcon1_close(screen_id);
        tcon_exit(screen_id);
        tcon1_tv_clk_enable(screen_id, 0);
    }
    return 0;
}

void disp_al_show_builtin_patten(u32 hwdev_index, u32 patten)
{
    tcon_show_builtin_patten(hwdev_index, patten);
}
