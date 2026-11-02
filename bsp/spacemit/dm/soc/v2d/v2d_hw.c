/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "v2d_internal.h"
#include "v2d_reg.h"

static const int cscmatrix[V2D_CSC_MODE_BUTT][3][4] =
{
    /* RGB2BT601Wide */
    {{  306,  601, 117,   0 },
     { -173, -339, 512, 128 },
     {  512, -429, -83, 128 }},

    /* BT601Wide2RGB */
    {{ 1024,    0, 1436, -179 },
     { 1024, -352, -731,  135 },
     { 1024, 1815,    0, -227 }},

    /* RGB2BT601Narrow */
    {{  263,  516, 100,  16 },
     { -152, -298, 450, 128 },
     {  450, -377, -73, 128 }},

    /* BT601Narrow2RGB */
    {{ 1192,    0, 1634, -223 },
     { 1192, -401, -832,  136 },
     { 1192, 2066,    0, -277 }},

    /* RGB2BT709Wide */
    {{  218,  732,   74,   0 },
     { -117, -395,  512, 128 },
     {  512, -465,  -47, 128 }},

    /* BT709Wide2RGB */
    {{ 1024,    0, 1613, -202 },
     { 1024, -192, -479,   84 },
     { 1024, 1900,    0, -238 }},

    /* RGB2BT709Narrow */
    {{  187,  629,  63, 16 },
     { -103, -347, 450, 128},
     {  450, -409, -41, 128}},

    /* BT709Narrow2RGB */
    {{ 1192,    0, 1836, -248 },
     { 1192, -218, -546,   77 },
     { 1192, 2163,    0, -289 }},

    /* BT601Wide2BT709Wide */
    {{ 1024, -121, -218,  42 },
     {    0, 1043,  117, -17 },
     {    0,   77, 1050, -13 }},

    /* BT601Wide2BT709Narrow */
    {{ 879, -104, -187, 52 },
     {   0,  916,  103,  1 },
     {   0,   68,  922,  4 }},

    /* BT601Wide2BT601Narrow */
    {{ 879,   0,   0,  16 },
     {   0, 900,   0,  16 },
     {   0,   0, 900,  16 }},

    /* BT601Narrow2BT709Wide */
    {{ 1192, -138, -248,   30 },
     {   0,  1187,  134,  -37 },
     {   0,    88, 1195,  -32 }},

    /* BT601Narrow2BT709Narrow */
    {{ 1024, -118, -213,  41 },
     {    0, 1043,  117, -17 },
     {    0,   77, 1050, -13 }},

    /* BT601Narrow2BT601Wide */
    {{ 1192,    0,    0, -19 },
     {    0, 1166,    0, -18 },
     {    0,    0, 1166, -18 }},

    /* BT709Wide2BT601Wide */
    {{ 1024,  104,  201,  -38 },
     {   0,  1014, -113,   15 },
     {   0,   -74, 1007,   11 }},

    /* BT709Wide2BT601Narrow */
    {{ 879,  89,  172, -17 },
     {   0, 890, -100,  29 },
     {   0, -65,  885,  26 }},

    /* BT709Wide2BT709Narrow */
    {{ 879,   0,   0,  16 },
     {   0, 900,   0,  16 },
     {   0,   0, 900,  16 }},

    /* BT709Narrow2BT601Wide */
    {{ 1192,  118,  229,  -62 },
     {    0, 1154, -129,    0 },
     {    0,  -85, 1146,   -5 }},

    /* BT709Narrow2BT601Narrow */
    {{ 1024,  102,  196,  -37 },
     {    0, 1014, -113,   15 },
     {    0,  -74, 1007,   11 }},

    /* BT709Narrow2BT709Wide */
    {{ 1192,    0,    0, -19 },
     {    0, 1166,    0, -18 },
     {    0,    0, 1166, -18 }},

    /* RGB2Grey */
    {{  218,  732,  74,   0  },
     { -117, -395, 512,  128 },
     {  512, -465, -47,  128 }},

    /* RGB2RGB */
    {{ 1024,    0,    0, 0 },
     {    0, 1024,    0, 0 },
     {    0,    0, 1024, 0 }}
};

enum
{
    R = 0,
    G,
    B,
    A
};

static const int32_t bicubic_coef[16][3] =
{
    { 246, 507, 246 },
    { 222, 505, 270 },
    { 199, 501, 294 },
    { 177, 494, 318 },
    { 155, 486, 342 },
    { 136, 474, 365 },
    { 117, 461, 387 },
    { 100, 445, 408 },
    { 85, 427, 427 },
    { 71, 408, 445 },
    { 59, 387, 461 },
    { 49, 365, 474 },
    { 41, 343, 485 },
    { 35, 318, 494 },
    { 30, 294, 501 },
    { 27, 270, 505 }
};

static void *v2d_reg_base;

void v2d_hw_set_base(void *base)
{
    v2d_reg_base = base;
}

rt_inline void v2d_write(uint32_t reg, uint32_t val)
{
    HWREG32((rt_uint8_t *)v2d_reg_base + reg) = val;
}

rt_inline uint32_t v2d_read(uint32_t reg)
{
    return HWREG32((rt_uint8_t *)v2d_reg_base + reg);
}

rt_inline void v2d_set_bits(uint32_t reg, uint32_t bits)
{
    v2d_write(reg, v2d_read(reg) | bits);
}

rt_inline void v2d_clear_bits(uint32_t reg, uint32_t bits)
{
    v2d_write(reg, v2d_read(reg) & ~bits);
}

static void v2d_write_bits(uint32_t reg, uint32_t value, uint32_t mask, uint32_t shifts)
{
    uint32_t reg_val;

    reg_val = v2d_read(reg);
    reg_val &= ~(mask << shifts);
    reg_val |= (value << shifts);
    v2d_write(reg, reg_val);
}

int v2d_global_reset(void)
{
    int timeout = 10000;

    v2d_set_bits(V2D_AUTO_CLK_REG, V2D_GLOBAL_RESET);
    while ((v2d_read(V2D_AUTO_CLK_REG) & V2D_GLOBAL_RESET) && --timeout)
    {
        rt_hw_us_delay(1);
    }

    if (!timeout)
    {
        LOG_E("global reset timeout");
        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}

uint32_t v2d_irq_status(void)
{
    return v2d_read(V2D_IRQ_STATUS);
}

void v2d_dump_irqraw_status(void)
{
    uint32_t irqerr_raw, encirq, dec0_irqraw, dec1_irqraw;
    irqerr_raw  = v2d_read(V2D_ERR_IRQ_RAW);
    dec0_irqraw = v2d_read(V2D_L0_DEC_REG8);
    dec1_irqraw = v2d_read(V2D_L1_DEC_REG8);
    encirq      = v2d_read(V2D_ENC_REG18);
    LOG_E("raw status: core=%08x dec0=%08x dec1=%08x enc=%08x",
            irqerr_raw, dec0_irqraw, dec1_irqraw, encirq);
}

uint32_t v2d_irqerr_status(void)
{
    return v2d_read(V2D_ERR_IRQ_STATUS);
}

void v2d_irqerr_clear(uint32_t irqerr)
{
    v2d_write(V2D_ERR_IRQ_STATUS, irqerr);
}

void v2d_irq_clear(uint32_t irqstaus)
{
    v2d_write(V2D_ENC_REG18, 0x3ffff);
    v2d_write(V2D_IRQ_STATUS, irqstaus);
}

void v2d_irq_enable(void)
{
    v2d_write(V2D_IRQ_MASK, V2D_EOF_IRQ_MASK|V2D_FBCENC_IRQ_MASK);
    v2d_write(V2D_ERR_IRQ_MASK, 0xE07);
    v2d_write_bits(V2D_DEBUG_REG0, 0x1, 0x1, 0);
}

void v2d_irq_disable(void)
{
    v2d_write(V2D_IRQ_MASK, 0x00);
    v2d_write(V2D_ERR_IRQ_MASK, 0x00);
}

static void ConfigAxiBus(void)
{
    v2d_axi_bus_ctrl_reg_t ctrl;

    ctrl.overlay = 0;
    ctrl.field.arqos_m = 2;
    ctrl.field.awqos_m = 2;
    ctrl.field.shadow_mode = 1;
    v2d_write(V2D_AXI_BUS_CTRL, ctrl.overlay);
}

int getBytePerPixel(V2D_COLOR_FORMAT_E enFormat)
{
    int Bpp=0;

    switch (enFormat)
    {
    case V2D_COLOR_FORMAT_NV12:
    case V2D_COLOR_FORMAT_NV21:
        Bpp = 1;
        break;
    case V2D_COLOR_FORMAT_RGB888:
    case V2D_COLOR_FORMAT_BGR888:
        Bpp = 3;
        break;
    case V2D_COLOR_FORMAT_RGBX8888:
    case V2D_COLOR_FORMAT_RGBA8888:
    case V2D_COLOR_FORMAT_ARGB8888:
    case V2D_COLOR_FORMAT_BGRX8888:
    case V2D_COLOR_FORMAT_BGRA8888:
    case V2D_COLOR_FORMAT_ABGR8888:
        Bpp = 4;
        break;
    case V2D_COLOR_FORMAT_RGB565:
    case V2D_COLOR_FORMAT_BGR565:
        Bpp = 2;
        break;
    case V2D_COLOR_FORMAT_RGBA5658:
    case V2D_COLOR_FORMAT_ARGB8565:
    case V2D_COLOR_FORMAT_BGRA5658:
    case V2D_COLOR_FORMAT_ABGR8565:
        Bpp = 3;
        break;
    case V2D_COLOR_FORMAT_A8:
    case V2D_COLOR_FORMAT_Y8:
        Bpp = 1;
        break;
    default:
        LOG_E("err format: %d not supported",enFormat);
    }
    return Bpp;
}

static void v2d_scaler_coef_init(void)
{
    const int32_t *pCoef;
    v2d_scaler_coef_reg_t scaler_coef;

    scaler_coef.overlay = 0;
    pCoef = &bicubic_coef[0][0];
    for (int i=0; i<SCALER_COEF_REG_NUM; ++i)
    {
        scaler_coef.field.scaler_coef0 = *(pCoef + 2*i);
        scaler_coef.field.scaler_coef1 = *(pCoef + 2*i+1);
        v2d_write(V2D_SCALER_COEF_REG(i), scaler_coef.overlay);
    }
}

static void split_fillcolor(uint32_t fillcolor, V2D_COLOR_FORMAT_E enFormatIn, uint8_t *pChl)
{
    uint8_t r, g, b, a;

    switch (enFormatIn)
    {
    case V2D_COLOR_FORMAT_NV12:
        r = fillcolor & 0xFF;
        g = (fillcolor >> 8) & 0xFF;
        b = (fillcolor >> 16) & 0xFF;
        a = 0xFF;
        break;
    case V2D_COLOR_FORMAT_NV21:
        r = fillcolor & 0xFF;
        b = (fillcolor >> 8) & 0xFF;
        g = (fillcolor >> 16) & 0xFF;
        a = 0xFF;
        break;
    case V2D_COLOR_FORMAT_RGB888:
    case V2D_COLOR_FORMAT_RGBX8888:
        r = fillcolor & 0xFF;
        g = (fillcolor >> 8) & 0xFF;
        b = (fillcolor >> 16) & 0xFF;
        a = 0xFF;
        break;
    case V2D_COLOR_FORMAT_RGBA8888:
        r = fillcolor & 0xFF;
        g = (fillcolor >> 8) & 0xFF;
        b = (fillcolor >> 16) & 0xFF;
        a = (fillcolor >> 24) & 0xFF;
        break;
    case V2D_COLOR_FORMAT_ARGB8888:
        a = fillcolor & 0xFF;
        r = (fillcolor >> 8) & 0xFF;
        g = (fillcolor >> 16) & 0xFF;
        b = (fillcolor >> 24) & 0xFF;
        break;
    case V2D_COLOR_FORMAT_RGB565:
        a = 0xFF;
        r = fillcolor & 0x1F;
        g = (fillcolor >> 5) & 0x3F;
        b = (fillcolor >> 11) & 0x1F;
        break;
    case V2D_COLOR_FORMAT_RGBA5658:
        r = fillcolor & 0x1F;
        g = (fillcolor >> 5) & 0x3F;
        b = (fillcolor >> 11) & 0x1F;
        a = (fillcolor >> 16) & 0xFF;
        break;
    case V2D_COLOR_FORMAT_ARGB8565:
        a = fillcolor & 0xFF;
        r = (fillcolor >> 8) & 0x1F;
        g = (fillcolor >> 13) & 0x3F;
        b = (fillcolor >> 19) & 0x1F;
        break;
    case V2D_COLOR_FORMAT_BGR888:
    case V2D_COLOR_FORMAT_BGRX8888:
        b = fillcolor & 0xFF;
        g = (fillcolor >> 8) & 0xFF;
        r = (fillcolor >> 16) & 0xFF;
        a = 0xFF;
        break;
    case V2D_COLOR_FORMAT_BGRA8888:
        b = fillcolor & 0xFF;
        g = (fillcolor >> 8) & 0xFF;
        r = (fillcolor >> 16) & 0xFF;
        a = (fillcolor >> 24) & 0xFF;
        break;
    case V2D_COLOR_FORMAT_ABGR8888:
        a = fillcolor & 0xFF;
        b = (fillcolor >> 8) & 0xFF;
        g = (fillcolor >> 16) & 0xFF;
        r = (fillcolor >> 24) & 0xFF;
        break;
    case V2D_COLOR_FORMAT_BGR565:
        a = 0xFF;
        b = fillcolor & 0x1F;
        g = (fillcolor >> 5) & 0x3F;
        r = (fillcolor >> 11) & 0x1F;
        break;
    case V2D_COLOR_FORMAT_BGRA5658:
        b = fillcolor & 0x1F;
        g = (fillcolor >> 5) & 0x3F;
        r = (fillcolor >> 11) & 0x1F;
        a = (fillcolor >> 16) & 0xFF;
        break;
    case V2D_COLOR_FORMAT_ABGR8565:
        a = fillcolor & 0xFF;
        b = (fillcolor >> 8) & 0x1F;
        g = (fillcolor >> 13) & 0x3F;
        r = (fillcolor >> 19) & 0x1F;
        break;
    default:
        r = 0xFF;
        g = 0xFF;
        b = 0xFF;
        a = 0xFF;
        break;
    }
    pChl[R] = r;
    pChl[G] = g;
    pChl[B] = b;
    pChl[A] = a;
}

static bool do_swap(V2D_COLOR_FORMAT_E enFormatIn)
{
    switch (enFormatIn)
    {
    case V2D_COLOR_FORMAT_BGR888:
    case V2D_COLOR_FORMAT_BGRX8888:
    case V2D_COLOR_FORMAT_BGRA8888:
    case V2D_COLOR_FORMAT_ABGR8888:
    case V2D_COLOR_FORMAT_BGR565:
    case V2D_COLOR_FORMAT_BGRA5658:
    case V2D_COLOR_FORMAT_ABGR8565:
    case V2D_COLOR_FORMAT_NV21:
    case V2D_COLOR_FORMAT_L8_BGR565:
    case V2D_COLOR_FORMAT_L8_BGR888:
    case V2D_COLOR_FORMAT_L8_BGRA8888:
        return RT_TRUE;
    default:
        return RT_FALSE;
    }
}

static bool do_narrow(V2D_CSC_MODE_E enForeCSCMode, V2D_CSC_MODE_E enBackCSCMode)
{
    int ret = RT_FALSE;

    switch (enForeCSCMode)
    {
    case V2D_CSC_MODE_RGB_2_BT601NARROW:
    case V2D_CSC_MODE_RGB_2_BT709NARROW:
    case V2D_CSC_MODE_BT601WIDE_2_BT709NARROW:
    case V2D_CSC_MODE_BT601WIDE_2_BT601NARROW:
    case V2D_CSC_MODE_BT601NARROW_2_BT709NARROW:
    case V2D_CSC_MODE_BT709WIDE_2_BT601NARROW:
    case V2D_CSC_MODE_BT709WIDE_2_BT709NARROW:
    case V2D_CSC_MODE_BT709NARROW_2_BT601NARROW:
        ret = RT_TRUE;
        break;
    default:
        break;
    }
    switch (enBackCSCMode)
    {
    case V2D_CSC_MODE_RGB_2_BT601NARROW:
    case V2D_CSC_MODE_RGB_2_BT709NARROW:
    case V2D_CSC_MODE_BT601WIDE_2_BT709NARROW:
    case V2D_CSC_MODE_BT601WIDE_2_BT601NARROW:
    case V2D_CSC_MODE_BT601NARROW_2_BT709NARROW:
    case V2D_CSC_MODE_BT709WIDE_2_BT601NARROW:
    case V2D_CSC_MODE_BT709WIDE_2_BT709NARROW:
    case V2D_CSC_MODE_BT709NARROW_2_BT601NARROW:
        ret = RT_TRUE;
        break;
    default:
        break;
    }
    return ret;
}

static V2D_COLOR_FORMAT_E fmt_convert(V2D_COLOR_FORMAT_E enFormatIn)
{
    V2D_COLOR_FORMAT_E enFormatOut = 0;

    switch (enFormatIn)
    {
    case V2D_COLOR_FORMAT_RGB888:
    case V2D_COLOR_FORMAT_RGBX8888:
    case V2D_COLOR_FORMAT_RGBA8888:
    case V2D_COLOR_FORMAT_ARGB8888:
    case V2D_COLOR_FORMAT_RGB565:
    case V2D_COLOR_FORMAT_NV12:
    case V2D_COLOR_FORMAT_RGBA5658:
    case V2D_COLOR_FORMAT_ARGB8565:
    case V2D_COLOR_FORMAT_A8:
    case V2D_COLOR_FORMAT_Y8:
        enFormatOut = enFormatIn;
        break;
    case V2D_COLOR_FORMAT_BGR888:
    case V2D_COLOR_FORMAT_BGRX8888:
    case V2D_COLOR_FORMAT_BGRA8888:
    case V2D_COLOR_FORMAT_ABGR8888:
    case V2D_COLOR_FORMAT_BGR565:
    case V2D_COLOR_FORMAT_NV21:
    case V2D_COLOR_FORMAT_BGRA5658:
    case V2D_COLOR_FORMAT_ABGR8565:
        enFormatOut = enFormatIn - V2D_COLOR_FORMAT_BGR888;
        break;
    case V2D_COLOR_FORMAT_L8_RGBA8888:
    case V2D_COLOR_FORMAT_L8_RGB888:
    case V2D_COLOR_FORMAT_L8_RGB565:
    case V2D_COLOR_FORMAT_L8_BGRA8888:
    case V2D_COLOR_FORMAT_L8_BGR888:
    case V2D_COLOR_FORMAT_L8_BGR565:
        enFormatOut = V2D_COLOR_FORMAT_L8_RGBA8888;
        break;
    default:
        break;
    }
    return enFormatOut;
}

static int Get_L8_Palette_bytePerPixel(V2D_SURFACE_S *pstBackGround, V2D_SURFACE_S *pstForeGround)
{
    int bpp = 4;

    if (pstBackGround)
    {
        if (pstBackGround->format == V2D_COLOR_FORMAT_L8_RGBA8888 || pstBackGround->format == V2D_COLOR_FORMAT_L8_BGRA8888)
        {
            bpp = 4;
        }
        else if (pstBackGround->format == V2D_COLOR_FORMAT_L8_RGB888 || pstBackGround->format == V2D_COLOR_FORMAT_L8_BGR888)
        {
            bpp = 3;
        }
        else if (pstBackGround->format == V2D_COLOR_FORMAT_L8_RGB565 || pstBackGround->format == V2D_COLOR_FORMAT_L8_BGR565)
        {
            bpp = 2;
        }
    }
    if (pstForeGround)
    {
        if (pstForeGround->format == V2D_COLOR_FORMAT_L8_RGBA8888 || pstForeGround->format == V2D_COLOR_FORMAT_L8_BGRA8888)
        {
            bpp = 4;
        }
        else if (pstForeGround->format == V2D_COLOR_FORMAT_L8_RGB888 || pstForeGround->format == V2D_COLOR_FORMAT_L8_BGR888)
        {
            bpp = 3;
        }
        else if (pstForeGround->format == V2D_COLOR_FORMAT_L8_RGB565 || pstForeGround->format == V2D_COLOR_FORMAT_L8_BGR565)
        {
            bpp = 2;
        }
    }
    return bpp;
}

static void ConfigV2dFbcDecoder(V2D_SURFACE_S *pstV2DSurface, V2D_INPUT_LAYER_E enInputLayer)
{
    v2d_fbc_decoder_bbox_reg_t bbox_x = { 0 }, bbox_y = { 0 };
    v2d_fbc_decoder_imgae_size_reg_t img_size = { 0 };
    v2d_fbc_decoder_mode_reg_t dec_mode = { 0 };
    v2d_fbc_decoder_dma_ctrl_reg_t dmac = { 0 };
    v2d_fbc_decoder_irq_ctrl_reg_t irqmask = { 0 };
    FBC_DECODER_S *pDecInfo = &pstV2DSurface->fbcDecInfo;

    LOG_D("config %s fbc decoder", (enInputLayer > 0 ? "layer1" : "layer0"));
    bbox_x.field.bbox_start = pDecInfo->bboxLeft;
    bbox_x.field.bbox_end   = pDecInfo->bboxRight;
    bbox_y.field.bbox_start = pDecInfo->bboxTop;
    bbox_y.field.bbox_end   = pDecInfo->bboxBottom;
    img_size.field.width    = pstV2DSurface->w;
    img_size.field.height   = pstV2DSurface->h;
    dec_mode.field.mode        = pDecInfo->enFbcdecMode;
    dec_mode.field.format   = pDecInfo->enFbcdecFmt;
    dec_mode.field.is_split = pDecInfo->is_split;
    dec_mode.field.rgb_pack_en = pDecInfo->rgb_pack_en;
    dmac.overlay = 0xffff1a02;
    irqmask.overlay = 0x00000017;

    v2d_write(V2D_LAYER_DEC_REG0_L(enInputLayer), pDecInfo->headerAddr_l);
    v2d_write(V2D_LAYER_DEC_REG1_L(enInputLayer), pDecInfo->headerAddr_h);
    v2d_write(V2D_LAYER_DEC_REG2_L(enInputLayer), bbox_x.overlay);
    v2d_write(V2D_LAYER_DEC_REG3_L(enInputLayer), bbox_y.overlay);
    v2d_write(V2D_LAYER_DEC_REG4_L(enInputLayer), img_size.overlay);
    v2d_write(V2D_LAYER_DEC_REG5_L(enInputLayer), dec_mode.overlay);
    v2d_write(V2D_LAYER_DEC_REG6_L(enInputLayer), dmac.overlay);
    v2d_write(V2D_LAYER_DEC_REG7_L(enInputLayer), irqmask.overlay);
}

static void ConfigV2dFbcEncoder(V2D_SURFACE_S *pstV2DSurface)
{
    v2d_fbc_encoder_bbox_reg_t bbox_x = { 0 }, bbox_y = { 0 };
    v2d_fbc_encoder_buf_size_reg_t y_buf_size = { 0 }, uv_buf_size = { 0 };
    v2d_fbc_encoder_irq_reg_t irqmask = { 0 };
    v2d_fbc_encoder_mode_reg_t enc_mode = { 0 };
    v2d_fbc_encoder_dmac_burst_reg_t dmac_burst = { 0 };
    FBC_ENCODER_S *pEncInfo = &pstV2DSurface->fbcEncInfo;

    LOG_D("config fbc encoder");
    bbox_x.field.bbox_start = pEncInfo->bboxLeft;
    bbox_x.field.bbox_end   = pEncInfo->bboxRight;
    bbox_y.field.bbox_start = pEncInfo->bboxTop;
    bbox_y.field.bbox_end   = pEncInfo->bboxBottom;
    y_buf_size.field.x_size = pstV2DSurface->w;
    y_buf_size.field.y_size = pstV2DSurface->h;
    uv_buf_size.field.x_size = pstV2DSurface->w >> 1;
    uv_buf_size.field.y_size = pstV2DSurface->w >> 1;
    irqmask.overlay = 0x0001ffff;
    enc_mode.field.encode_enable = 1;
    enc_mode.field.split_mode_en = pEncInfo->is_split;
    enc_mode.field.img_pix_format = pEncInfo->enFbcencFmt;
    dmac_burst.field.burst_length = 0x10;

    v2d_write(V2D_ENC_REG0, pEncInfo->headerAddr_l);
    v2d_write(V2D_ENC_REG1, pEncInfo->headerAddr_h);
    v2d_write(V2D_ENC_REG2, pEncInfo->payloadAddr_l);
    v2d_write(V2D_ENC_REG3, pEncInfo->payloadAddr_h);
    v2d_write(V2D_ENC_REG4, bbox_x.overlay);
    v2d_write(V2D_ENC_REG5, bbox_y.overlay);
    v2d_write(V2D_ENC_REG10, y_buf_size.overlay);
    v2d_write(V2D_ENC_REG11, uv_buf_size.overlay);
    v2d_write(V2D_ENC_REG13, irqmask.overlay);
    v2d_write(V2D_ENC_REG15, 0x9e00ffff);
    v2d_write(V2D_ENC_REG16, enc_mode.overlay);
    v2d_write(V2D_ENC_REG17, dmac_burst.overlay);
}

static void ConfigV2dInputLayer(V2D_SURFACE_S *pstV2DSurface,
                                V2D_AREA_S *pstV2DArea,
                                V2D_BLEND_CONF_S *pstBlendConf,
                                V2D_ROTATE_ANGLE_E enRotateAngle,
                                V2D_CSC_MODE_E enCSCMode,
                                V2D_INPUT_LAYER_E enInputLayer)
{
    const int *pCscMatrix;
    V2D_SCALER_MODE_E enScaleMode = V2D_NO_SCALE;
    uint32_t width = 0, height = 0;
    V2D_FILLCOLOR_S *pFillColor; uint8_t chl[4];
    V2D_BLEND_LAYER_CONF_S *pBlendLayerConf;
    v2d_blend_layer_ctrl0_reg_t bld_layer_ctrl0 = { 0 };
    v2d_blend_layer_ctrl1_reg_t bld_layer_ctrl1 = { 0 };
    v2d_blend_layer_ctrl2_reg_t bld_layer_ctrl2 = { 0 };
    v2d_blend_layer_ctrl3_reg_t bld_layer_ctrl3 = { 0 };
    v2d_blend_layer_factor_reg_t bld_layer_factor = { 0 };
    v2d_solid_color_ctrl0_reg_t solidcolor_ctrl0 = { 0 };
    v2d_solid_color_ctrl1_reg_t solidcolor_ctrl1 = { 0 };
    v2d_input_layer_width_height_reg_t layer_in_ori_w_h = { 0 };
    v2d_input_layer_ctrl_reg_t layer_in_ctrl = { 0 };
    v2d_input_layer_crop0_reg_t layer_in_crop0 = { 0 };
    v2d_input_layer_crop1_reg_t layer_in_crop1 = { 0 };
    v2d_input_layer_csc_ctrl0_reg_t layer_in_csc_ctrl0 = { 0 };
    v2d_input_layer_csc_ctrl1_reg_t layer_in_csc_ctrl1 = { 0 };
    v2d_input_layer_csc_ctrl2_reg_t layer_in_csc_ctrl2 = { 0 };
    v2d_input_layer_scale_mode_reg_t layer_scale_mode = { 0 };
    v2d_input_layer_scale_delta_x_reg_t layer_scale_delta_x = { 0 };
    v2d_input_layer_scale_delta_y_reg_t layer_scale_delta_y = { 0 };

    bld_layer_ctrl1.overlay = 0;
    bld_layer_ctrl3.overlay = 0;
    bld_layer_factor.overlay = 0;
    solidcolor_ctrl0.overlay = 0;
    solidcolor_ctrl1.overlay = 0;
    layer_in_ctrl.overlay = 0;
    layer_in_csc_ctrl0.overlay = 0;
    layer_in_csc_ctrl1.overlay = 0;
    layer_in_csc_ctrl2.overlay = 0;
    layer_scale_mode.overlay = 0;
    layer_scale_delta_x.overlay = 0;
    layer_scale_delta_y.overlay = 0;

    if ((!pstV2DSurface->solidcolor.enable) &&
        (pstV2DSurface->phyaddr_y_l == 0) &&
        (pstV2DSurface->phyaddr_y_h == 0) &&
        (!pstV2DSurface->fbc_enable))
    {
            LOG_D("%s disable", (enInputLayer > 0 ? "layer1" : "layer0"));
            bld_layer_ctrl1.field.blend_en = V2D_FUNC_DISABLE;
            v2d_write(V2D_LAYER_BLD_CTRL1_LAYER(enInputLayer), bld_layer_ctrl1.overlay);
    }
    else
    {
        LOG_D("config %s rot: %d, csc: %d", (enInputLayer > 0 ? "layer1" : "layer0"), enRotateAngle, enCSCMode);
        /* blendlayer */
        pBlendLayerConf = &pstBlendConf->blendlayer[enInputLayer];
        bld_layer_ctrl0.field.bld_alpha_source = pBlendLayerConf->blend_alpha_source;
        bld_layer_ctrl0.field.bld_pre_alp_func = pBlendLayerConf->blend_pre_alpha_func;
        bld_layer_ctrl0.field.bld_glb_alp = pBlendLayerConf->global_alpha;
        bld_layer_ctrl0.field.scl_delta_y = 0;
        bld_layer_ctrl1.field.blend_en = V2D_FUNC_ENABLE;
        bld_layer_ctrl1.field.bld_rect_ltop_x = pBlendLayerConf->blend_area.x;
        bld_layer_ctrl2.field.bld_rect_ltop_y = pBlendLayerConf->blend_area.y;
        bld_layer_ctrl2.field.bld_rect_width = pBlendLayerConf->blend_area.w;
        bld_layer_ctrl3.field.bld_rect_height = pBlendLayerConf->blend_area.h;
        LOG_D("bld alpha_src: %d,pre_func: %d,glb_alpha: %d", pBlendLayerConf->blend_alpha_source, pBlendLayerConf->blend_pre_alpha_func, pBlendLayerConf->global_alpha);
        LOG_D("bld_rect:(%d,%d,%d,%d)", pBlendLayerConf->blend_area.x, pBlendLayerConf->blend_area.y, pBlendLayerConf->blend_area.w, pBlendLayerConf->blend_area.h);
        v2d_write(V2D_LAYER_BLD_CTRL0_LAYER(enInputLayer), bld_layer_ctrl0.overlay);
        v2d_write(V2D_LAYER_BLD_CTRL1_LAYER(enInputLayer), bld_layer_ctrl1.overlay);
        v2d_write(V2D_LAYER_BLD_CTRL2_LAYER(enInputLayer), bld_layer_ctrl2.overlay);
        v2d_write(V2D_LAYER_BLD_CTRL3_LAYER(enInputLayer), bld_layer_ctrl3.overlay);

        bld_layer_factor.field.in_addr_uv_33_32 = pstV2DSurface->phyaddr_uv_h & V2D_H_ADDR_MASK;
        if (pstBlendConf->blend_cmd)
        {
            bld_layer_factor.field.bld_color_rop2_code = pBlendLayerConf->stRop2Code.colorRop2Code;
            bld_layer_factor.field.bld_alpha_rop2_code = pBlendLayerConf->stRop2Code.alphaRop2Code;
        }
        else
        {
            bld_layer_factor.field.bld_src_color_factor = pBlendLayerConf->stBlendFactor.srcColorFactor;
            bld_layer_factor.field.bld_src_alpha_factor = pBlendLayerConf->stBlendFactor.srcAlphaFactor;
            bld_layer_factor.field.bld_dst_color_factor = pBlendLayerConf->stBlendFactor.dstColorFactor;
            bld_layer_factor.field.bld_dst_alpha_factor = pBlendLayerConf->stBlendFactor.dstAlphaFactor;
        }
        LOG_D("bld factor:src_c=%d,src_a=%d,dst_c=%d,dst_a=%d", pBlendLayerConf->stBlendFactor.srcColorFactor, pBlendLayerConf->stBlendFactor.srcAlphaFactor,
                pBlendLayerConf->stBlendFactor.dstColorFactor, pBlendLayerConf->stBlendFactor.dstAlphaFactor);
        v2d_write(V2D_LAYER_BLD_FACTOR_LAYER(enInputLayer), bld_layer_factor.overlay);

        if (pstV2DSurface->solidcolor.enable)
        {
            /* solid color */
            pFillColor = &pstV2DSurface->solidcolor.fillcolor;
            split_fillcolor(pFillColor->colorvalue, pFillColor->format, chl);
            solidcolor_ctrl0.field.solid_en = V2D_FUNC_ENABLE;
            solidcolor_ctrl0.field.solid_R = chl[R];
            solidcolor_ctrl0.field.solid_G = chl[G];
            solidcolor_ctrl0.field.solid_B = chl[B];
            solidcolor_ctrl1.field.solid_A = chl[A];
            solidcolor_ctrl1.field.csc_en = V2D_FUNC_DISABLE;
            v2d_write(V2D_LAYER_SOLIDCOLOR_CTRL0_LAYER(enInputLayer), solidcolor_ctrl0.overlay);
            v2d_write(V2D_LAYER_SOLIDCOLOR_CTRL1_LAYER(enInputLayer), solidcolor_ctrl1.overlay);
        }
        else
        {
            /* input layer */
            solidcolor_ctrl0.field.solid_en = V2D_FUNC_DISABLE;
            v2d_write(V2D_LAYER_SOLIDCOLOR_CTRL0_LAYER(enInputLayer), solidcolor_ctrl0.overlay);
            if (pstV2DSurface->fbc_enable)
            {
                ConfigV2dFbcDecoder(pstV2DSurface, enInputLayer);
            }
            else
            {
                v2d_write(V2D_LAYER_Y_ADDR_L_LAYER(enInputLayer),  pstV2DSurface->phyaddr_y_l);
                v2d_write(V2D_LAYER_Y_ADDR_H_LAYER(enInputLayer),  pstV2DSurface->phyaddr_y_h);
                v2d_write(V2D_LAYER_UV_ADDR_L_LAYER(enInputLayer), pstV2DSurface->phyaddr_uv_l);
            }
            layer_in_ori_w_h.field.layer_in_ori_width = pstV2DSurface->w;
            layer_in_ori_w_h.field.layer_in_ori_height = pstV2DSurface->h;
            v2d_write(V2D_LAYER_WIDTH_HEIGHT_LAYER(enInputLayer), layer_in_ori_w_h.overlay);

            layer_in_ctrl.field.stride = pstV2DSurface->stride;
            layer_in_ctrl.field.swap = do_swap(pstV2DSurface->format);
            layer_in_ctrl.field.format = fmt_convert(pstV2DSurface->format);
            layer_in_ctrl.field.rotation = enRotateAngle;
            layer_in_ctrl.field.fbc_en = pstV2DSurface->fbc_enable;
            v2d_write(V2D_LAYER_CTRL_LAYER(enInputLayer), layer_in_ctrl.overlay);
            /* crop */
            layer_in_crop0.field.layer_in_crop_ltop_x = pstV2DArea->x;
            layer_in_crop0.field.layer_in_crop_ltop_y = pstV2DArea->y;
            layer_in_crop1.field.layer_in_crop_width = pstV2DArea->w;
            layer_in_crop1.field.layer_in_crop_height = pstV2DArea->h;
            LOG_D("crop:(%d,%d,%d,%d)", pstV2DArea->x, pstV2DArea->y, pstV2DArea->w, pstV2DArea->h);
            v2d_write(V2D_LAYER_CROP_REG0_LAYER(enInputLayer), layer_in_crop0.overlay);
            v2d_write(V2D_LAYER_CROP_REG1_LAYER(enInputLayer), layer_in_crop1.overlay);
            /* csc */
            if (enCSCMode < V2D_CSC_MODE_BUTT)
            {
                layer_in_csc_ctrl0.field.csc_en = V2D_FUNC_ENABLE;
                pCscMatrix = &cscmatrix[enCSCMode][0][0];
                layer_in_csc_ctrl0.field.csc_matrix0 = pCscMatrix[0];
                for (int i = 0; i < 5; i++)
                {
                    layer_in_csc_ctrl1.field.csc_matrix1 = pCscMatrix[2 * i + 1];
                    layer_in_csc_ctrl1.field.csc_matrix2 = pCscMatrix[2 * i + 2];
                    v2d_write(V2D_LAYER_CSC_CRTL1_LAYER(enInputLayer) + 0x4 * i, layer_in_csc_ctrl1.overlay);
                }
                layer_in_csc_ctrl2.field.csc_matrix11 = pCscMatrix[11];
                v2d_write(V2D_LAYER_CSC_CRTL6_LAYER(enInputLayer), layer_in_csc_ctrl2.overlay);
            }
            else
            {
                layer_in_csc_ctrl0.field.csc_en = V2D_FUNC_DISABLE;
            }
            v2d_write(V2D_LAYER_CSC_CRTL0_LAYER(enInputLayer), layer_in_csc_ctrl0.overlay);
            /* scale */
            if (enRotateAngle == V2D_ROT_90 || enRotateAngle == V2D_ROT_270)
            {
                width = pstV2DArea->h; height = pstV2DArea->w;
            }
            else
            {
                width = pstV2DArea->w; height = pstV2DArea->h;
            }
            if (width == pBlendLayerConf->blend_area.w && height == pBlendLayerConf->blend_area.h)
            {
                enScaleMode = V2D_NO_SCALE;
            }
            else if (width > pBlendLayerConf->blend_area.w || height > pBlendLayerConf->blend_area.h)
            {
                enScaleMode = V2D_SCALE_DOWN;
            }
            else if (width < pBlendLayerConf->blend_area.w || height < pBlendLayerConf->blend_area.h)
            {
                enScaleMode = V2D_SCALE_UP;
            }
            LOG_D("scale: %d", enScaleMode);
            layer_scale_mode.overlay = layer_in_csc_ctrl2.overlay;
            layer_scale_mode.field.scl_mode = enScaleMode;
            v2d_write(V2D_LAYER_SCALE_MODE_LAYER(enInputLayer), layer_scale_mode.overlay);
            if (enScaleMode)
            {
                layer_scale_delta_x.field.scl_delta_x = (width << 16) / pBlendLayerConf->blend_area.w;
                layer_scale_delta_y.overlay = bld_layer_ctrl0.overlay;
                layer_scale_delta_y.field.scl_delta_y = (height << 16) / pBlendLayerConf->blend_area.h;
                v2d_write(V2D_LAYER_SCALE_DELTA_X_LAYER(enInputLayer), layer_scale_delta_x.overlay);
                v2d_write(V2D_LAYER_SCALE_DELTA_Y_LAYER(enInputLayer), layer_scale_delta_y.overlay);
            }
            else
            {
                layer_scale_delta_x.field.scl_delta_x = (1 << 16);
                layer_scale_delta_y.overlay = bld_layer_ctrl0.overlay;
                layer_scale_delta_y.field.scl_delta_y = (1 << 16);
                v2d_write(V2D_LAYER_SCALE_DELTA_X_LAYER(enInputLayer), layer_scale_delta_x.overlay);
                v2d_write(V2D_LAYER_SCALE_DELTA_Y_LAYER(enInputLayer), layer_scale_delta_y.overlay);
            }
        }
    }
}

static void ConfigV2dMaskLayer(V2D_SURFACE_S *pstMask, V2D_AREA_S *pstMaskRect, V2D_BLEND_CONF_S *pstBlendConf)
{
    v2d_mask_width_reg_t mask_in_width = { 0 };
    v2d_mask_height_reg_t mask_in_height = { 0 };
    v2d_mask_crop0_reg_t mask_in_crop0 = { 0 };
    v2d_mask_crop1_reg_t mask_in_crop1 = { 0 };
    v2d_blend_mask_ctrl0_reg_t bld_mask_ctrl0 = { 0 };
    v2d_blend_mask_ctrl1_reg_t bld_mask_ctrl1 = { 0 };
    v2d_blend_mask_ctrl2_reg_t bld_mask_ctrl2 = { 0 };

    bld_mask_ctrl0.overlay = 0;
    mask_in_width.overlay = 0;
    bld_mask_ctrl2.overlay = 0;

    if (pstMask->phyaddr_y_l != 0 || pstMask->phyaddr_y_h != 0)
    {
        LOG_D("ConfigV2dMaskLayer");
        mask_in_width.field.mask_addr_33_32 = (pstMask->phyaddr_y_h & V2D_H_ADDR_MASK);
        mask_in_width.field.mask_ori_width = pstMask->w;
        mask_in_height.field.mask_ori_height = pstMask->h;
        mask_in_height.field.mask_ori_stride = pstMask->stride;
        mask_in_crop0.field.mask_crop_ltop_x = pstMaskRect->x;
        mask_in_crop0.field.mask_crop_ltop_y = pstMaskRect->y;
        mask_in_crop1.field.mask_crop_width = pstMaskRect->w;
        mask_in_crop1.field.mask_crop_height = pstMaskRect->h;
        bld_mask_ctrl0.field.bld_mask_enable = pstBlendConf->mask_cmd;
        bld_mask_ctrl0.field.bld_mask_rect_ltop_x = pstBlendConf->blend_mask_area.x;
        bld_mask_ctrl1.field.bld_mask_rect_ltop_y = pstBlendConf->blend_mask_area.y;
        bld_mask_ctrl1.field.bld_mask_rect_width = pstBlendConf->blend_mask_area.w;
        bld_mask_ctrl2.field.bld_mask_rect_height = pstBlendConf->blend_mask_area.h;
        v2d_write(V2D_MASK_ADDR_L, pstMask->phyaddr_y_l);
        v2d_write(V2D_MASK_WIDTH,  mask_in_width.overlay);
        v2d_write(V2D_MASK_HEIGHT, mask_in_height.overlay);
        v2d_write(V2D_MASK_CROP_REG0, mask_in_crop0.overlay);
        v2d_write(V2D_MASK_CROP_REG1, mask_in_crop1.overlay);
        v2d_write(V2D_BLD_MASK_REG0,  bld_mask_ctrl0.overlay);
        v2d_write(V2D_BLD_MASK_REG1,  bld_mask_ctrl1.overlay);
        v2d_write(V2D_BLD_MASK_REG2,  bld_mask_ctrl2.overlay);
    }
    else
    {
        LOG_D("mask layer disable");
        bld_mask_ctrl0.field.bld_mask_enable = V2D_FUNC_DISABLE;
        v2d_write(V2D_BLD_MASK_REG0,  bld_mask_ctrl0.overlay);
    }
}

static void ConfigPaletteTable(V2D_SURFACE_S *pstBackGround, V2D_SURFACE_S *pstForeGround, V2D_PALETTE_S *pstPalette)
{
    int bpp;
    uint32_t val;
    uint8_t *pTmp, r, g, b, a;

    if (pstPalette->len != 0)
    {
        LOG_D("ConfigPaletteTable");
        pTmp = pstPalette->palVal;
        bpp = Get_L8_Palette_bytePerPixel(pstBackGround, pstForeGround);
        LOG_D("bpp: %d, palette len: %d", bpp, pstPalette->len);
        for (int i = 0; i < (pstPalette->len / bpp); i++)
        {
            if (bpp == 4)
            {
                r = *(pTmp + 4 * i);  g = *(pTmp + 4 * i + 1);
                b = *(pTmp + 4 * i + 2); a = *(pTmp + 4 * i + 3);
            }
            else if (bpp == 3)
            {
                r = *(pTmp + 3 * i);   g = *(pTmp + 3 * i + 1);
                b = *(pTmp + 3 * i + 2); a = 0xFF;
            }
            else if (bpp == 2)
            {
                r = *(pTmp + 2 * i) & 0x1F;
                g = ((*(pTmp + 2 * i) >> 5) & 0x7) | ((*(pTmp + 2 * i + 1) & 0x7) << 3);
                b = (*(pTmp + 2 * i + 1) >> 3) & 0x1F;
                a = 0xFF;
            }
            val = r | (g << 8) | (b << 16) | (a << 24);
            v2d_write(V2D_PALETTE_TABLE(i), val);
        }
    }
}

static void ConfigV2dBlendMode_And_BgColor(V2D_BLEND_CONF_S *pstBlendConf)
{
    V2D_FILLCOLOR_S *pFillColor;
    uint8_t chl[4];
    v2d_blend_ctrl0_reg_t blend_ctrl0 = { 0 };
    v2d_blend_ctrl1_reg_t blend_ctrl1 = { 0 };

    LOG_D("ConfigV2dBlendMode_And_BgColor");
    blend_ctrl0.overlay = 0;
    blend_ctrl1.overlay = 0;
    blend_ctrl0.field.bld_mode = pstBlendConf->blend_cmd;
    blend_ctrl0.field.bld_bg_enable = pstBlendConf->bgcolor.enable;
    pFillColor = &pstBlendConf->bgcolor.fillcolor;
    split_fillcolor(pFillColor->colorvalue, V2D_COLOR_FORMAT_RGBA8888, chl);
    LOG_D("bgcolor_en: %d,r: %d,g: %d,b: %d,alpha: %d",  pstBlendConf->bgcolor.enable, chl[R], chl[G], chl[B], chl[A]);
    blend_ctrl0.field.bld_bg_r = chl[R];
    blend_ctrl0.field.bld_bg_g = chl[G];
    blend_ctrl0.field.bld_bg_b = chl[B];
    blend_ctrl1.field.bld_bg_a = chl[A];
    v2d_write(V2D_BLEND_REG0, blend_ctrl0.overlay);
    v2d_write(V2D_BLEND_REG1, blend_ctrl1.overlay);
}

static void ConfigV2dOutput(V2D_SURFACE_S *pstDst,
                            V2D_AREA_S *pstDstRect,
                            V2D_CSC_MODE_E enForeCSCMode,
                            V2D_CSC_MODE_E enBackCSCMode,
                            V2D_DITHER_E dither)
{
    v2d_output_width_reg_t output_width = { 0 };
    v2d_output_height_reg_t output_height = { 0 };
    v2d_output_ctrl0_reg_t output_ctrl0 = { 0 };
    v2d_output_ctrl1_reg_t output_ctrl1 = { 0 };
    v2d_output_ctrl2_reg_t output_ctrl2 = { 0 };

    LOG_D("config output");
    output_width.overlay = 0;
    output_ctrl0.overlay = 0;
    output_ctrl2.overlay = 0;
    output_width.field.out_ori_width = pstDst->w;
    output_width.field.out_addr_uv_33_32 = (pstDst->phyaddr_uv_h & V2D_H_ADDR_MASK);
    output_height.field.out_ori_height = pstDst->h;
    output_height.field.out_ori_stride = pstDst->stride;
    output_ctrl0.field.format = fmt_convert(pstDst->format);
    output_ctrl0.field.range = do_narrow(enForeCSCMode, enBackCSCMode);
    output_ctrl0.field.dither = dither;
    output_ctrl0.field.swap = do_swap(pstDst->format);
    output_ctrl0.field.fbc_en = pstDst->fbc_enable;
    output_ctrl0.field.crop_ltop_x = pstDstRect->x;
    output_ctrl1.field.crop_ltop_y = pstDstRect->y;
    output_ctrl1.field.crop_width = pstDstRect->w;
    output_ctrl2.field.crop_height = pstDstRect->h;
    LOG_D("dst:w=%d,h=%d", pstDst->w, pstDst->h);
    LOG_D("crop=(%d,%d,%d,%d)", pstDstRect->x, pstDstRect->y, pstDstRect->w, pstDstRect->h);
    LOG_D("dst:fmt=%d, dither: %d,narrow=%d, swap=%d, stride=%d",
            output_ctrl0.field.format, output_ctrl0.field.dither, output_ctrl0.field.range, output_ctrl0.field.swap, pstDst->stride);

    v2d_write(V2D_OUTPUT_WIDTH,  output_width.overlay);
    v2d_write(V2D_OUTPUT_HEIGHT, output_height.overlay);
    v2d_write(V2D_OUTPUT_CRTL0,  output_ctrl0.overlay);
    v2d_write(V2D_OUTPUT_CRTL1,  output_ctrl1.overlay);
    v2d_write(V2D_OUTPUT_CRTL2,  output_ctrl2.overlay);
    if (pstDst->fbc_enable)
    {
        ConfigV2dFbcEncoder(pstDst);
    }
    else
    {
        v2d_write(V2D_OUTPUT_Y_ADDR_L, pstDst->phyaddr_y_l);
        v2d_write(V2D_OUTPUT_Y_ADDR_H, pstDst->phyaddr_y_h);
        v2d_write(V2D_OUTPUT_UV_ADDR_L, pstDst->phyaddr_uv_l);
    }
}

static void ConfigV2dDmac(void)
{
    v2d_dma_ctrl_reg_t dma_ctrl;

    dma_ctrl.overlay = 0;
    dma_ctrl.field.dmac_arb_mode = 2;
    dma_ctrl.field.dmac_max_req_num = 7;
    dma_ctrl.field.dmac_postwr_en = 255;
    dma_ctrl.field.dmac_rst_n_pwr = 1;
    dma_ctrl.field.dmac_arqos = 2;
    dma_ctrl.field.dmac_awqos = 2;
    v2d_write(V2D_DMA_CTRL, dma_ctrl.overlay);
}

static void TriggerV2dRun(V2D_PARAM_S *pParam)
{
    v2d_ctrl_reg_t ctrl = { 0 };
    v2d_fbc_decoder_trigger_reg_t decTrigger = { 0 };
    v2d_fbc_encoder_trigger_reg_t encTrigger = { 0 };

    if (pParam->layer0.fbc_enable)
    {
        decTrigger.overlay = 0;
        decTrigger.field.direct_swap = 1;
        v2d_write(V2D_L0_DEC_REG10, decTrigger.overlay);
    }
    if (pParam->layer1.fbc_enable)
    {
        decTrigger.overlay = 0;
        decTrigger.field.direct_swap = 1;
        v2d_write(V2D_L1_DEC_REG10, decTrigger.overlay);
    }
    if (pParam->dst.fbc_enable)
    {
        encTrigger.overlay = 0;
        encTrigger.field.direct_swap = 1;
        v2d_write(V2D_ENC_REG12, encTrigger.overlay);
    }
    ctrl.overlay = 0;
    ctrl.field.rdma_burst_len = 4;
    ctrl.field.wdma_burst_len = 16;
    ctrl.field.trigger        = 1;
    rt_hw_dsb();
    v2d_write(V2D_CTRL_REG, ctrl.overlay);
}

void config_v2d_hw(V2D_SUBMIT_TASK_S *pTask)
{
    V2D_SURFACE_S *pstBackGround, *pstForeGround, *pstMask, *pstDst;
    V2D_AREA_S *pstBackGroundRect, *pstForeGroundRect, *pstMaskRect, *pstDstRect;
    V2D_BLEND_CONF_S *pstBlendConf;
    V2D_ROTATE_ANGLE_E enForeRoate, enBackRotate;
    V2D_CSC_MODE_E enForeCscMode, enBackCscMode;
    V2D_PALETTE_S *pstPalette;
    V2D_DITHER_E enDither;
    V2D_PARAM_S *pV2dParam;

    pV2dParam = &pTask->param;
    pstBackGround = &pV2dParam->layer0;
    pstBackGroundRect = &pV2dParam->l0_rect;
    pstForeGround = &pV2dParam->layer1;
    pstForeGroundRect = &pV2dParam->l1_rect;
    pstMask = &pV2dParam->mask;
    pstMaskRect = &pV2dParam->mask_rect;
    pstDst = &pV2dParam->dst;
    pstDstRect = &pV2dParam->dst_rect;
    pstBlendConf = &pV2dParam->blendconf;
    enBackRotate = pV2dParam->l0_rt;
    enForeRoate = pV2dParam->l1_rt;
    enBackCscMode = pV2dParam->l0_csc;
    enForeCscMode = pV2dParam->l1_csc;
    enDither = pV2dParam->dither;
    pstPalette = &pV2dParam->palette;

    /* init scaler coef */
    v2d_scaler_coef_init();
    /* config layer0 */
    ConfigV2dInputLayer(pstBackGround, pstBackGroundRect, pstBlendConf, enBackRotate, enBackCscMode, V2D_INPUT_LAYER0);
    /* config layer1 */
    ConfigV2dInputLayer(pstForeGround, pstForeGroundRect, pstBlendConf, enForeRoate, enForeCscMode, V2D_INPUT_LAYER1);
    /* set palette */
    ConfigPaletteTable(pstBackGround, pstForeGround, pstPalette);
    /* config mask */
    ConfigV2dMaskLayer(pstMask, pstMaskRect, pstBlendConf);
    /* blend */
    ConfigV2dBlendMode_And_BgColor(pstBlendConf);
    /* output */
    ConfigV2dOutput(pstDst, pstDstRect, enForeCscMode, enBackCscMode, enDither);
    /* DMA control */
    ConfigV2dDmac();
    /* set v2d qos */
    ConfigAxiBus();
    /* trigger */
    TriggerV2dRun(pV2dParam);
    LOG_D("v2d config done");
}
