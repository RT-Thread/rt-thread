/*
 * Allwinner SoCs display driver.
 *
 * Copyright (C) 2016 Allwinner.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

/**
 *  All Winner Tech, All Right Reserved. 2014-2015 Copyright (c)
 *
 *  File name   :       de2_wb_ebios.c
 *
 *  Description :       display engine 2.0 WBC basic function definition
 *
 *  History     :       2014/03/03   wangxuan   initial version
 *                      2014/04/02   wangxuan   change the register
 *                                              operation from bits to word
 */
#include "de_wb_type.h"
#include "de_wb.h"
#define WB_MODULE_NUMBER DE_NUM
#define WB_OFFSET 0x010000

static volatile struct __wb_reg_t *wb_dev[WB_MODULE_NUMBER] = { NULL };
static struct disp_capture_config wb_config;

unsigned int wb_lan2coefftab16[16] = {
    0x00004000, 0x00033ffe, 0x00063efc, 0x000a3bfb,
    0xff0f37fb, 0xfe1433fb, 0xfd192ffb, 0xfd1f29fb,
    0xfc2424fc, 0xfb291ffd, 0xfb2f19fd, 0xfb3314fe,
    0xfb370fff, 0xfb3b0a00, 0xfc3e0600, 0xfe3f0300
};

unsigned int wb_lan2coefftab16_down[16] = {
    0x000e240e, 0x0010240c, 0x0013230a, 0x00142309,
    0x00162208, 0x01182106, 0x011a2005, 0x021b1f04,
    0x031d1d03, 0x041e1c02, 0x05201a01, 0x06211801,
    0x07221601, 0x09231400, 0x0a231300, 0x0c231100
};

int rgb2yuv601[3][4] = {
    {0x00bb, 0x0274, 0x003f, 0x04200},
    {0x1f98, 0x1ea5, 0x01c1, 0x20200},
    {0x01c1, 0x1e67, 0x1fd7, 0x20200} };/* rgb2yuv */
int rgb2yuv709[3][4] = {
    {0x00da, 0x02dc, 0x0049, 0x00200},
    {0xff8b, 0xfe76, 0x0200, 0x20200},
    {0x0200, 0xfe30, 0xffd1, 0x20200} };/* rgb2yuv */
int r2gray[3][4] = {
    {0x0155, 0x0155, 0x0156, 0x0200},
    {0x0000, 0x0000, 0x0000, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000} };/* rgb2gray */


/**
 *  function       : wb_ebios_set_reg_base(u32 sel, u32 base)
 *  description    : setup write-back controller register base
 *  parameters     :
 *                       sel <controller select>
 *                       base <register base>
 *  return         :
 *                   success
 */
s32 wb_ebios_set_reg_base(u32 sel, uintptr_t base)
{
    int i = 0;

    DE_INF("sel=%d, base=0x%p\n", sel, (void *)(base + WB_OFFSET));

    for (i = 0; i < DE_NUM; ++i)
        wb_dev[i] = (struct __wb_reg_t *) (base + WB_OFFSET);

    return 0;
}

/**
 *  function       : wb_ebios_get_reg_base(u32 sel)
 *  description    : get write-back controller register base
 *  parameters     :
 *                       sel <controller select>
 *  return         :
 *                   registers base
 */
uintptr_t wb_ebios_get_reg_base(u32 sel)
{
    uintptr_t ret = 0;

    ret = (uintptr_t) wb_dev[sel];

    return ret;
}

/**
 *  function       : wb_ebios_init(struct disp_bsp_init_para *para)
 *  description    : initial write-back controller registers
 *  parameters     :
 *                       para <>
 *  return         :
 *                   success
 */
s32 wb_ebios_init(struct disp_bsp_init_para *para)
{
    wb_ebios_set_reg_base(0, para->reg_base[DISP_MOD_DE]);
#if defined(CONFIG_ARCH_SUN50IW10)
    wb_ebios_set_reg_base(1, para->reg_base[DISP_MOD_DE1]);
#endif
    /* FIXME, need */
    /* memset((void*)wb_dev[0], 0, sizeof(struct __wb_reg_t)); */
    return 0;
}

/**
 *  function       : wb_ebios_exit
 *  description    : de-initial write-back controller registers
 *  parameters     :
 *                       para <>
 *  return         :
 *                   success
 */
s32 wb_ebios_exit(void)
{
    return 0;
}

/**
 *  function       : wb_ebios_writeback_enable(u32 sel, bool en)
 *  description    : enable write-back once
 *  parameters     :
 *                       sel <controller select>
 *                       en <0:disable; 1:enable>
 *  return         :
 *                   success
 */
s32 wb_ebios_writeback_enable(u32 sel, bool en)
{
    wb_dev[sel]->gctrl.dwval |= ((en == 0) ? 0x0 : 0x00000001);

    return 0;
}

/**
 *  function       : wb_ebios_apply(u32 sel,
 *                  struct disp_capture_config *cfg)
 *  description    : save user config
 *  parameters     :
 *                       sel <controller select>
 *                       cfg <write-back information,include input_fb and
 *                            output_fb information>
 *  return         :
 *                   0   success
 *                   -1  fail
 *  note           : Don't support YUV input yet 14-02-28
 *                   when write-back format is yuv, default 16-235 output
 */
s32 wb_ebios_apply(u32 sel, struct disp_capture_config *cfg)
{
    memcpy(&wb_config, cfg, sizeof(struct disp_capture_config));
    return 0;
}

/**
 *  function       : wb_ebios_update_regs(u32 sel)
 *  description    : transform user config into hw config
 *  parameters     :
 *                       sel <controller select>
 *  return         :
 *                   0   success
 *                   -1  fail
 */
s32 wb_ebios_update_regs(u32 sel)
{
    wb_ebios_set_para(sel, &wb_config);
    return 0;
}

/**
 *  function       : wb_ebios_set_para(u32 sel,disp_capture_config *cfg)
 *  description    : setup write-back controller parameters
 *  parameters     :
 *                       sel <controller select>
 *                       cfg <write-back information,include input_fb and
 *                            output_fb information>
 *  return         :
 *                   0   success
 *                   -1  fail
 *  note           : Don't support YUV input yet 14-02-28
 *                   when write-back format is yuv, default 16-235 output
 */
s32 wb_ebios_set_para(u32 sel, struct disp_capture_config *cfg)
{
    u32 in_port;
    u32 in_w, in_h;
    u32 crop_x, crop_y, crop_w, crop_h;
    u32 out_addr[3];
    u32 out_buf_w, out_buf_h;
    u32 out_fmt;
    u32 out_window_w, out_window_h, out_window_x, out_window_y;
    u32 cs_out_w0 = 0, cs_out_h0 = 0, cs_out_w1 = 0, cs_out_h1 = 0;
    u32 fs_out_w0, fs_out_h0, fs_out_w1, fs_out_h1;
    u32 step_h, step_v;
    u32 v_intg, v_frac, h_intg, h_frac;
    u32 down_scale_y, down_scale_c;
    u32 i;
    /* get para */
    in_port = cfg->disp;
    in_w = cfg->in_frame.size[0].width;
    in_h = cfg->in_frame.size[0].height;
    crop_x = (u32) cfg->in_frame.crop.x;
    crop_y = (u32) cfg->in_frame.crop.y;
    crop_w = cfg->in_frame.crop.width;
    crop_h = cfg->in_frame.crop.height;
    out_addr[0] = cfg->out_frame.addr[0];
    out_addr[1] = cfg->out_frame.addr[1];
    out_addr[2] = cfg->out_frame.addr[2];
    out_buf_w = cfg->out_frame.size[0].width;
    out_buf_h = cfg->out_frame.size[0].height;
    out_fmt = cfg->out_frame.format;
    out_window_x = cfg->out_frame.crop.x;
    out_window_y = cfg->out_frame.crop.y;
    out_window_w = cfg->out_frame.crop.width;
    out_window_h = cfg->out_frame.crop.height;
    if (in_port >= DE_NUM)
        return -1;
    if ((in_w < MININWIDTH) || (in_w > MAXINWIDTH) || (in_h < MININHEIGHT)
        || (in_h > MAXINHEIGHT))
        return -1;
    if ((crop_w < MININWIDTH) || (crop_w > MAXINWIDTH)
        || (crop_h < MININHEIGHT) || (crop_h > MAXINHEIGHT))
        return -1;
    if ((crop_x + crop_w > in_w) || (crop_y + crop_h > in_h))
        return -1;
    if ((out_buf_w < out_window_w) || (out_buf_h < out_window_h))
        return -1;
    if ((out_window_w < MININWIDTH) || (out_window_w > MAXINWIDTH)
        || (out_window_h < MININHEIGHT) || (out_window_h > MAXINHEIGHT))
        return -1;
    if ((out_window_w > crop_w) || (out_window_h > crop_h))
        return -1;
    if (((out_fmt == DISP_FORMAT_YUV420_P)
         || (out_fmt == DISP_FORMAT_YUV420_SP_VUVU)
         || (out_fmt == DISP_FORMAT_YUV420_SP_UVUV))
        && (out_window_w > LINE_BUF_LEN))
        return -1;
    /* gctrl */
    wb_dev[sel]->gctrl.dwval |= (0x10000000 | (in_port << 16));
    /* input size */
    wb_dev[sel]->size.dwval = (in_w - 1) | ((in_h - 1) << 16);
    /* input crop window */
    wb_dev[sel]->crop_coord.dwval = crop_x | ((crop_y) << 16);
    wb_dev[sel]->crop_size.dwval = (crop_w - 1) | ((crop_h - 1) << 16);
    /* output fmt */
    if (out_fmt == DISP_FORMAT_ARGB_8888)
        wb_dev[sel]->fmt.dwval = WB_FORMAT_ARGB_8888;
    else if (out_fmt == DISP_FORMAT_ABGR_8888)
        wb_dev[sel]->fmt.dwval = WB_FORMAT_ABGR_8888;
    else if (out_fmt == DISP_FORMAT_RGBA_8888)
        wb_dev[sel]->fmt.dwval = WB_FORMAT_RGBA_8888;
    else if (out_fmt == DISP_FORMAT_BGRA_8888)
        wb_dev[sel]->fmt.dwval = WB_FORMAT_BGRA_8888;
    else if (out_fmt == DISP_FORMAT_RGB_888)
        wb_dev[sel]->fmt.dwval = WB_FORMAT_RGB_888;
    else if (out_fmt == DISP_FORMAT_BGR_888)
        wb_dev[sel]->fmt.dwval = WB_FORMAT_BGR_888;
    else if (out_fmt == DISP_FORMAT_YUV420_P)
        wb_dev[sel]->fmt.dwval = WB_FORMAT_YUV420_P;
    else if (out_fmt == DISP_FORMAT_YUV420_SP_VUVU)
        wb_dev[sel]->fmt.dwval = WB_FORMAT_YUV420_SP_UVUV;
    else if (out_fmt == DISP_FORMAT_YUV420_SP_UVUV)
        wb_dev[sel]->fmt.dwval = WB_FORMAT_YUV420_SP_VUVU;
    else
        return -1;

    /* output addr and pitch for different fmt */
    if ((out_fmt == DISP_FORMAT_ARGB_8888)
        || (out_fmt == DISP_FORMAT_ABGR_8888)
        || (out_fmt == DISP_FORMAT_RGBA_8888)
        || (out_fmt == DISP_FORMAT_BGRA_8888)) {
        out_addr[0] += (out_window_y * out_buf_w + out_window_x) << 2;
        wb_dev[sel]->wb_addr_a0.dwval = out_addr[0];
        wb_dev[sel]->wb_pitch0.dwval = out_buf_w << 2;
    }
    if ((out_fmt == DISP_FORMAT_RGB_888)
        || (out_fmt == DISP_FORMAT_BGR_888)) {
        out_addr[0] += (out_window_y * out_buf_w + out_window_x) * 3;
        wb_dev[sel]->wb_addr_a0.dwval = out_addr[0];
        wb_dev[sel]->wb_pitch0.dwval = 3 * out_buf_w;
    }
    if ((out_fmt == DISP_FORMAT_YUV420_SP_VUVU)
        || (out_fmt == DISP_FORMAT_YUV420_SP_UVUV)) {
        out_addr[0] += (out_window_y * out_buf_w + out_window_x);
        out_addr[1] +=
            (((out_window_y * out_buf_w) >> 1) + out_window_x);
        wb_dev[sel]->wb_addr_a0.dwval = out_addr[0];
        wb_dev[sel]->wb_addr_a1.dwval = out_addr[1];
        wb_dev[sel]->wb_pitch0.dwval = out_buf_w;
        wb_dev[sel]->wb_pitch1.dwval = out_buf_w;
    }
    if (out_fmt == DISP_FORMAT_YUV420_P) {
        out_addr[0] += (out_window_y * out_buf_w + out_window_x);
        out_addr[1] += (out_window_y * out_buf_w + out_window_x) >> 1;
        out_addr[2] += (out_window_y * out_buf_w + out_window_x) >> 1;
        wb_dev[sel]->wb_addr_a0.dwval = out_addr[0];
        wb_dev[sel]->wb_addr_a1.dwval = out_addr[1];
        wb_dev[sel]->wb_addr_a2.dwval = out_addr[2];
        wb_dev[sel]->wb_pitch0.dwval = out_buf_w;
        wb_dev[sel]->wb_pitch1.dwval = out_buf_w >> 1;
    }
    /* CSC */
    if ((out_fmt == DISP_FORMAT_ARGB_8888)
        || (out_fmt == DISP_FORMAT_ABGR_8888)
        || (out_fmt == DISP_FORMAT_RGBA_8888)
        || (out_fmt == DISP_FORMAT_BGRA_8888)
        || (out_fmt == DISP_FORMAT_RGB_888)
        || (out_fmt == DISP_FORMAT_BGR_888))
        wb_dev[sel]->bypass.dwval &= 0xfffffffe;
    else {
        wb_dev[sel]->bypass.dwval |= 0x00000001;
    }
    /* Coarse scaling */
    if ((crop_w > (out_window_w << 1)) && (crop_h > (out_window_h << 1))) {
        wb_dev[sel]->bypass.dwval |= 0x00000002;
        wb_dev[sel]->cs_horz.dwval = crop_w | (out_window_w << 17);
        wb_dev[sel]->cs_vert.dwval = crop_h | (out_window_h << 17);
        cs_out_w0 = out_window_w << 1;
        cs_out_h0 = out_window_h << 1;
    }
    if ((crop_w > (out_window_w << 1)) && (crop_h <= (out_window_h << 1))) {
        wb_dev[sel]->bypass.dwval |= 0x00000002;
        wb_dev[sel]->cs_horz.dwval = crop_w | (out_window_w << 17);
        wb_dev[sel]->cs_vert.dwval = 0;
        cs_out_w0 = out_window_w << 1;
        cs_out_h0 = crop_h;
    }
    if ((crop_w <= (out_window_w << 1)) && (crop_h > (out_window_h << 1))) {
        wb_dev[sel]->bypass.dwval |= 0x00000002;
        wb_dev[sel]->cs_horz.dwval = 0;
        wb_dev[sel]->cs_vert.dwval = crop_h | (out_window_h << 17);
        cs_out_w0 = crop_w;
        cs_out_h0 = out_window_h << 1;
    }
    if ((crop_w <= (out_window_w << 1))
        && (crop_h <= (out_window_h << 1))) {
        wb_dev[sel]->bypass.dwval &= 0xfffffffd;
        wb_dev[sel]->cs_horz.dwval = 0;
        wb_dev[sel]->cs_vert.dwval = 0;
        cs_out_w0 = crop_w;
        cs_out_h0 = crop_h;
    }
    /* Fine scaling */
    cs_out_w1 = cs_out_w0;
    cs_out_h1 = cs_out_h0;
    fs_out_w0 = out_window_w;
    fs_out_w1 =
        ((out_fmt == DISP_FORMAT_YUV420_P)
        | (out_fmt == DISP_FORMAT_YUV420_SP_VUVU)
        | (out_fmt == DISP_FORMAT_YUV420_SP_UVUV)) ?
        (out_window_w >> 1) : out_window_w;
    fs_out_h0 = out_window_h;
    fs_out_h1 =
        ((out_fmt == DISP_FORMAT_YUV420_P)
        | (out_fmt == DISP_FORMAT_YUV420_SP_VUVU)
        | (out_fmt == DISP_FORMAT_YUV420_SP_UVUV)) ?
        (out_window_h >> 1) : out_window_h;
    if ((cs_out_w0 == fs_out_w0) && (cs_out_h0 == fs_out_h0)
        && (cs_out_w1 == fs_out_w1) && (cs_out_h1 == fs_out_h1)) {
        wb_dev[sel]->bypass.dwval &= 0xfffffffb;
        wb_dev[sel]->fs_hstep.dwval = 1 << 20;
        wb_dev[sel]->fs_vstep.dwval = 1 << 20;
    } else {
        unsigned long long tmp;

        wb_dev[sel]->bypass.dwval |= 0x00000004;
        tmp = ((long long)cs_out_w0 << LOCFRACBIT);
        tmp /= (long long)out_window_w;
        step_h = (int)tmp;
        tmp = ((long long)cs_out_h0 << LOCFRACBIT);
        tmp /= (long long)out_window_h;
        step_v = (int)tmp;
        h_intg = (step_h & (~((1 << LOCFRACBIT) - 1))) >> LOCFRACBIT;
        h_frac = step_h & ((1 << LOCFRACBIT) - 1);
        v_intg = (step_v & (~((1 << LOCFRACBIT) - 1))) >> LOCFRACBIT;
        v_frac = step_v & ((1 << LOCFRACBIT) - 1);
        wb_dev[sel]->fs_hstep.dwval = (h_frac << 2) | (h_intg << 20);
        wb_dev[sel]->fs_vstep.dwval = (v_frac << 2) | (v_intg << 20);
        if (cs_out_w0 <= fs_out_w0)
            down_scale_y = 0;
        else
            down_scale_y = 1;
        if (cs_out_w1 <= fs_out_w1)
            down_scale_c = 0;
        else
            down_scale_c = 1;
        for (i = 0; i < SCALERPHASE; i++) {
            wb_dev[sel]->yhcoeff[i].dwval =
                down_scale_y ? wb_lan2coefftab16_down[i] :
                wb_lan2coefftab16[i];
            wb_dev[sel]->chcoeff[i].dwval =
                down_scale_c ? wb_lan2coefftab16_down[i] :
                wb_lan2coefftab16[i];
        }
    }
    wb_dev[sel]->fs_insize.dwval =
        (cs_out_w0 - 1) | ((cs_out_h0 - 1) << 16);
    wb_dev[sel]->fs_outsize.dwval =
        (out_window_w - 1) | ((out_window_h - 1) << 16);
    return 0;
}

/**
 *  function       : wb_ebios_get_status(u32 sel)
 *  description    : get last frame write back status
 *  parameters     :
 *                       sel <controller select>
 *  return         :
 *                   0    writeback finish
 *                   1    overflow
 *                   2    timeout
 *                   3    not start
 */
u32 wb_ebios_get_status(u32 sel)
{
    u32 status;

    status = wb_dev[sel]->status.dwval & 0x71;
    wb_dev[sel]->status.dwval = 0x71;

    if (status & 0x10)
        return 0;
    else if (status & 0x20)
        return 1;
    else if (status & 0x40)
        return 2;
    else
        return 3;
}

/* INTERRUPT */
s32 wb_ebios_enableint(u32 sel)
{
    wb_dev[sel]->intr.dwval |= 0x00000001;
    return 0;
}

s32 wb_ebios_disableint(u32 sel)
{
    wb_dev[sel]->intr.dwval &= 0xfffffffe;
    return 0;
}

u32 wb_ebios_queryint(u32 sel)
{
    return wb_dev[sel]->status.dwval;
}

u32 wb_ebios_clearint(u32 sel)
{
    /* write 1 to clear */
    wb_dev[sel]->status.dwval |=
        (WB_END_IE | WB_FINISH_IE | WB_FIFO_OVERFLOW_ERROR_IE |
         WB_TIMEOUT_ERROR_IE);
    return 0;
}

/**
 * @name       :wb_input_select
 * @brief      :rt-wb input port select
 * @param[IN]  :sel:port index(0~3)
 * @return     :0 if success, -1 else
 */
s32 wb_input_select(u32 sel)
{
    if (sel >= DE_NUM)
        return -1;

    wb_dev[sel]->gctrl.bits.in_port_sel = sel;
    return 0;
}

#if defined(CONFIG_EINK_PANEL_USED)
/* ************************************************************************* */
/* function       : WB_eink_Set_Reg_Base(unsigned int sel, unsigned int base) */
/* description    : setup write-back controller register base */
/* parameters     : */
/* sel <controller select> */
/* base <register base> */
/* return         : */
/* success */
/* ************************************************************************* */
int wb_eink_set_reg_base(unsigned int sel, unsigned int base)
{
    DE_INF("sel=%d, base=0x%x\n", sel, base + WB_OFFSET);
    wb_dev[sel] = (struct __wb_reg_t *)(base + WB_OFFSET);

    return 0;
}

/* ************************************************************************* */
/* function       : WB_eink_Get_Reg_Base(unsigned int sel) */
/* description    : get write-back controller register base */
/* parameters     : */
/* sel <controller select> */
/*  */
/* return         : */
/* registers base */
/* ************************************************************************* */
unsigned int wb_eink_get_reg_base(unsigned int sel)
{
    unsigned int ret = 0;

    ret = (unsigned int)wb_dev[sel];

    return ret;
}

/* ************************************************************************* */
/* function       : WB_eink_Init(unsigned int sel) */
/* description    : initial write-back controller registers */
/* parameters     : */
/* sel <controller select> */
/*  */
/* return         : */
/* success */
/* ************************************************************************* */
int wb_eink_init(unsigned int sel, unsigned int base_addr)
{
    wb_eink_set_reg_base(sel, base_addr); /* 0x01000000 */
    return 0;
}

int wb_eink_close(unsigned int sel)
{
    wb_dev[sel]->gctrl.dwval = 0;
    return 0;
}

/* ************************************************************************* */
/* function       : WB_eink_Writeback_Enable(unsigned int sel) */
/* description    : enable write-back once */
/* parameters     : */
/* sel <controller select>, en<0:disable; 1:enable> */
/* return         : */
/* success */
/* ************************************************************************* */
int wb_eink_writeback_enable(unsigned int sel)
{
    wb_dev[sel]->gctrl.dwval |= 1;

    return 0;
}

int wb_eink_reset(unsigned int sel)
{
    wb_dev[sel]->gctrl.dwval = 0x20000010;

    return 0;
}

int wb_eink_dereset(unsigned int sel)
{
    wb_dev[sel]->gctrl.dwval = 0x00000000;

    return 0;
}
/* ************************************************************************* */
/* function: WB_eink_Set_Para(unsigned int sel,disp_capture_config *cfg) */
/* description: setup write-back controller parameters */
/* parameters : */
/* sel <controller select> */
/* wb_config <write-back information,*/
/*include input_fb and output_fb information> */
/* return: */
/* 0    --  success */
/* -1   --  fail */
/* note       : Don't support YUV input yet 14-02-28 */
/* when write-back format is yuv, default 16-235 output */
/* ************************************************************************* */
int wb_eink_set_para(unsigned int sel, __einkwb_config_t *cfg)
{
    unsigned int in_port;
    unsigned int in_w, in_h;
    unsigned int crop_x, crop_y, crop_w, crop_h;
    unsigned int out_addr[3];
    unsigned int out_buf_w, out_buf_h;
    unsigned int out_fmt;
    unsigned int out_window_w, out_window_h, out_window_x, out_window_y;
    unsigned int csc_std;
    unsigned int self_sync;
    /* get para */
    in_port      = 0;/* cfg->disp; */
    in_w         = cfg->width;
    in_h         = cfg->height;
    crop_x       = 0;
    crop_y       = 0;
    crop_w       = cfg->width;
    crop_h       = cfg->height;
    out_addr[0]  = cfg->addr[0];
    out_addr[1]  = cfg->addr[1];
    out_addr[2]  = cfg->addr[2];
    out_buf_w    = cfg->width;
    out_buf_h    = cfg->height;
    out_fmt      = 9;/* DISP_FORMAT_Y;//cfg->format; fixed format */
    out_window_x = 0;
    out_window_y = 0;
    out_window_w = cfg->width;
    out_window_h = cfg->height;

    csc_std = cfg->csc_std;
    self_sync = (out_fmt == 9)?1:0;


    /* (0x30000000|(in_port<<16)|(self_sync == 1)?0x20:0x0); */
    wb_dev[sel]->gctrl.dwval |= 0x20000020;

    wb_dev[sel]->size.dwval = (in_w-1)|((in_h-1)<<16);
    /* input crop window */
    wb_dev[sel]->crop_coord.dwval = crop_x|((crop_y)<<16);
    wb_dev[sel]->crop_size.dwval = (crop_w - 1)|((crop_h - 1)<<16);
    /* output fmt */
    wb_dev[sel]->fmt.dwval = 9;

    if (out_fmt == 9/*DISP_FORMAT_Y*/) {
        out_addr[0] += (out_window_y * out_buf_w + out_window_x);
        out_addr[1] = 0;
        out_addr[2] = 0;
        wb_dev[sel]->wb_addr_a0.dwval = out_addr[0];
        wb_dev[sel]->wb_addr_a1.dwval = 0;
        wb_dev[sel]->wb_addr_a2.dwval = 0;
        wb_dev[sel]->wb_pitch0.dwval = out_buf_w;
        wb_dev[sel]->wb_pitch1.dwval = 0;

      /* CSC */
        wb_dev[sel]->bypass.dwval |= 0x00000001;
        if (csc_std == 0 || csc_std > 2) {
            wb_dev[sel]->c00.bits.coff = rgb2yuv601[0][0];
            wb_dev[sel]->c01.bits.coff = rgb2yuv601[0][1];
            wb_dev[sel]->c02.bits.coff = rgb2yuv601[0][2];
            wb_dev[sel]->c03.bits.cont = rgb2yuv601[0][3];

            wb_dev[sel]->c10.bits.coff = rgb2yuv601[1][0];
            wb_dev[sel]->c11.bits.coff = rgb2yuv601[1][1];
            wb_dev[sel]->c12.bits.coff = rgb2yuv601[1][2];
            wb_dev[sel]->c13.bits.cont = rgb2yuv601[1][3];

            wb_dev[sel]->c20.bits.coff = rgb2yuv601[2][0];
            wb_dev[sel]->c21.bits.coff = rgb2yuv601[2][1];
            wb_dev[sel]->c22.bits.coff = rgb2yuv601[2][2];
            wb_dev[sel]->c23.bits.cont = rgb2yuv601[2][3];
        } else if (csc_std == 1) {
            wb_dev[sel]->c00.bits.coff = rgb2yuv709[0][0];
            wb_dev[sel]->c01.bits.coff = rgb2yuv709[0][1];
            wb_dev[sel]->c02.bits.coff = rgb2yuv709[0][2];
            wb_dev[sel]->c03.bits.cont = rgb2yuv709[0][3];

            wb_dev[sel]->c10.bits.coff = rgb2yuv709[1][0];
            wb_dev[sel]->c11.bits.coff = rgb2yuv709[1][1];
            wb_dev[sel]->c12.bits.coff = rgb2yuv709[1][2];
            wb_dev[sel]->c13.bits.cont = rgb2yuv709[1][3];

            wb_dev[sel]->c20.bits.coff = rgb2yuv709[2][0];
            wb_dev[sel]->c21.bits.coff = rgb2yuv709[2][1];
            wb_dev[sel]->c22.bits.coff = rgb2yuv709[2][2];
            wb_dev[sel]->c23.bits.cont = rgb2yuv709[2][3];
        } else if (csc_std == 2) {
            wb_dev[sel]->c00.bits.coff = r2gray[0][0];
            wb_dev[sel]->c01.bits.coff = r2gray[0][1];
            wb_dev[sel]->c02.bits.coff = r2gray[0][2];
            wb_dev[sel]->c03.bits.cont = r2gray[0][3];

            wb_dev[sel]->c10.bits.coff = r2gray[1][0];
            wb_dev[sel]->c11.bits.coff = r2gray[1][1];
            wb_dev[sel]->c12.bits.coff = r2gray[1][2];
            wb_dev[sel]->c13.bits.cont = r2gray[1][3];

            wb_dev[sel]->c20.bits.coff = r2gray[2][0];
            wb_dev[sel]->c21.bits.coff = r2gray[2][1];
            wb_dev[sel]->c22.bits.coff = r2gray[2][2];
            wb_dev[sel]->c23.bits.cont = r2gray[2][3];
        }

        /*fine scal*/
        wb_dev[sel]->bypass.dwval &= 0xfffffffb;
        wb_dev[sel]->fs_hstep.dwval = 1 << 20;
        wb_dev[sel]->fs_vstep.dwval = 1 << 20;
        wb_dev[sel]->fs_insize.dwval =
                (out_window_w - 1) | ((out_window_h - 1) << 16);
        wb_dev[sel]->fs_outsize.dwval =
                (out_window_w - 1) | ((out_window_h - 1) << 16);
    }
    return 0;
}


int wb_eink_get_status(unsigned int sel)
{
    unsigned int status;

    status = wb_dev[sel]->status.dwval & 0x71;

    if (status == 0x11)
        return EWB_OK;
    else if (status & 0x20)
        return EWB_OVFL;
    else if (status & 0x40)
        return EWB_TIMEOUT;
    else if (status & 0x100)
        return EWB_BUSY;
    else
        return EWB_ERR;
}

/* /INTERRUPT */
int wb_eink_enableint(unsigned int sel)
{
    /* register irq routine */
    /* os_request_irq(); */

    wb_dev[sel]->intr.dwval |= 0x00000001;
    return 0;
}

int wb_eink_disableint(unsigned int sel)
{
    /* unregister irq routine */

    wb_dev[sel]->intr.dwval &= 0xfffffffe;
    return 0;
}

/* write 1 to clear */
int wb_eink_clearint(unsigned int sel)
{
    wb_dev[sel]->status.dwval |= (WB_END_IE | WB_FINISH_IE |
                    WB_FIFO_OVERFLOW_ERROR_IE |
                    WB_TIMEOUT_ERROR_IE);
    return 0;
}
#endif
