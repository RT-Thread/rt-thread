/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_jpeg_drv.h"

#define HPM_JPEG_DEFAULT_MAX_OT (2)

const jpeg_sampling_t jpeg_supported_sampling[5] = {
    {2, 2, 1, 1}, /* 420 */
    {2, 1, 1, 1}, /* 422H */
    {1, 2, 1, 1}, /* 422V */
    {1, 1, 1, 1}, /* 444 */
    {1, 1, 0, 0}, /* 400 */
};

const jpeg_pixel_t jpeg_supported_pixel_format[6] = {
    {4, 1, 1, true}, /* JPEG_PIXEL_FORMAT_ARGB8888 */
    {2, 2, 2, true}, /* JPEG_PIXEL_FORMAT_RGB565 */
    {2, 3, 0, false}, /* JPEG_PIXEL_FORMAT_YUV422H1P */
    {1, 0, 0, false}, /* JPEG_PIXEL_FORMAT_YUV422H2P */
    {1, 0, 0, false}, /* JPEG_PIXEL_FORMAT_YUV420 */
    {1, 0, 0, false}, /* JPEG_PIXEL_FORMAT_Y8 */
};

void jpeg_disable_irq(JPEG_Type *ptr, uint32_t mask)
{
    if (mask & JPEG_EVENT_IN_DMA_FINISH) {
        ptr->INDMA_MISC &= ~(JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_MASK
            | JPEG_INDMA_MISC_IRQ_EN_MASK);
    }
    if (mask & JPEG_EVENT_OUT_DMA_FINISH) {
        ptr->OUTDMA_MISC &= ~(JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_MASK
            | JPEG_OUTDMA_MISC_IRQ_EN_MASK);
    }
    if (mask & JPEG_EVENT_ERROR) {
        ptr->CFG &= ~(JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_MASK);
    }
}

void jpeg_enable_irq(JPEG_Type *ptr, uint32_t mask)
{
    if (mask & JPEG_EVENT_IN_DMA_FINISH) {
        ptr->INDMA_MISC |= JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_MASK
            | JPEG_INDMA_MISC_IRQ_EN_MASK;
    }
    if (mask & JPEG_EVENT_OUT_DMA_FINISH) {
        ptr->OUTDMA_MISC |= JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_MASK
            | JPEG_OUTDMA_MISC_IRQ_EN_MASK;
    }
    if (mask & JPEG_EVENT_ERROR) {
        ptr->CFG |= JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_MASK;
    }
}

void jpeg_reset(JPEG_Type *ptr)
{
    jpeg_stop(ptr);
    jpeg_software_reset(ptr);
    ptr->STAT = 0xFFFFFFFFUL;

}

void jpeg_init(JPEG_Type *ptr)
{
    jpeg_clear_cfg(ptr);
    jpeg_reset(ptr);
}

static bool jpeg_need_csc(jpeg_pixel_format_t in, jpeg_pixel_format_t out)
{
    return (jpeg_supported_pixel_format[in].is_rgb != jpeg_supported_pixel_format[out].is_rgb);
}

static bool jpeg_is_valid_size(uint8_t format, uint32_t width, uint32_t height)
{
    uint32_t align;
    if (format > ARRAY_SIZE(jpeg_supported_sampling)) {
        return false;
    }
    align = jpeg_supported_sampling[format].hy * 8;
    if (width % align) {
        return false;
    }
    align = jpeg_supported_sampling[format].vy * 8;
    if (height % align) {
        return false;
    }
    return true;
}

#define JPEG_HY(x) ((x)->hy)
#define JPEG_VY(x) ((x)->vy)
#define JPEG_HC(x) ((x)->hc)
#define JPEG_VC(x) ((x)->vc)

static uint32_t jpeg_calculate_macro_block_count(uint32_t width, uint32_t height, jpeg_sampling_t *sampling)
{
    return (width / (JPEG_HY(sampling) << 3)) * (height / (JPEG_VY(sampling) << 3));
}

static void jpeg_config_interal_regs(JPEG_Type *ptr,
                                bool decoding,
                                uint32_t macro_block_count,
                                uint8_t format)
{
    uint8_t hy, vy, hc, vc;
    hy = JPEG_HY(&jpeg_supported_sampling[format]);
    vy = JPEG_VY(&jpeg_supported_sampling[format]);
    hc = JPEG_HC(&jpeg_supported_sampling[format]);
    vc = JPEG_VC(&jpeg_supported_sampling[format]);

    if (format != JPEG_SUPPORTED_FORMAT_400) {
        ptr->IMGREG1 =  JPEG_IMGREG1_NCOL_SET(2);
    } else {
        ptr->IMGREG1 = 8;
    }
    ptr->IMGREG2 = JPEG_IMGREG2_NMCU_SET(macro_block_count - 1);
    ptr->IMGREG3 = 0;
    ptr->IMGREG[0] = JPEG_IMGREG_NBLOCK_SET(hy * vy - 1);
    if (format == JPEG_SUPPORTED_FORMAT_400) {
        ptr->IMGREG[1] = 0;
        ptr->IMGREG[2] = 0;
    } else {
        ptr->IMGREG[1] = JPEG_IMGREG_NBLOCK_SET(hc * vc - 1)
            | JPEG_IMGREG_QT_SET(1)
            | JPEG_IMGREG_HA_SET(1)
            | JPEG_IMGREG_HD_SET(1);
        ptr->IMGREG[2] = JPEG_IMGREG_NBLOCK_SET(hc * vc - 1)
            | JPEG_IMGREG_QT_SET(1)
            | JPEG_IMGREG_HA_SET(1)
            | JPEG_IMGREG_HD_SET(1);
    }
    ptr->IMGREG[3] = 0;
}

hpm_stat_t jpeg_start_encode(JPEG_Type *ptr, jpeg_job_config_t *config)
{
    uint32_t macro_block_count;
    uint32_t macro_block_bytes;
    uint32_t total_bytes;
    jpeg_sampling_t *sampling;

    if (!jpeg_is_valid_size(config->jpeg_format, config->width_in_pixel, config->height_in_pixel)) {
        return status_invalid_argument;
    }

    jpeg_disable(ptr);
    jpeg_software_reset(ptr);

    sampling = (jpeg_sampling_t *)&jpeg_supported_sampling[config->jpeg_format];
    macro_block_count = jpeg_calculate_macro_block_count(config->width_in_pixel, config->height_in_pixel, sampling);
    macro_block_bytes = (JPEG_HY(sampling) * JPEG_VY(sampling)
            + 2 * JPEG_HC(sampling) * JPEG_VC(sampling)) << 6;
    total_bytes = macro_block_count * macro_block_bytes;

    /* input DMA setting */
    ptr->INDMA_MISC = JPEG_INDMA_MISC_IN_DMA_ID_SET(0)
        | JPEG_INDMA_MISC_MAX_OT_SET(HPM_JPEG_DEFAULT_MAX_OT)
        | JPEG_INDMA_MISC_INDMA2D_MASK
        | JPEG_INDMA_MISC_IN_DMA_REQ_MASK
        | JPEG_INDMA_MISC_PACK_DIR_SET(config->in_byte_order);
    ptr->INDMABASE = JPEG_INDMABASE_ADDR_SET(config->in_buffer);
    ptr->INDMA_CTRL0 = JPEG_INDMA_CTRL0_TTLEN_SET(total_bytes)
        | JPEG_INDMA_CTRL0_PITCH_SET(config->width_in_pixel * jpeg_supported_pixel_format[config->in_pixel_format].pixel_width);
    ptr->INDMA_CTRL1 = JPEG_INDMA_CTRL1_ROWLEN_SET(total_bytes >> 16);

    ptr->INXT_CMD = JPEG_INXT_CMD_ADDR_SET(5) | JPEG_INXT_CMD_OP_VALID_MASK;

    /* output DMA setting */
    ptr->OUTDMA_MISC = JPEG_OUTDMA_MISC_EN_OUTCNT_MASK
        | JPEG_OUTDMA_MISC_INI_OUTCNT_MASK
        | JPEG_OUTDMA_MISC_OUT_DMA_ID_SET(1)
        | JPEG_OUTDMA_MISC_OUT_DMA_REQ_MASK
        | JPEG_OUTDMA_MISC_ADD_ODMA_ENDINGS_MASK
        | JPEG_OUTDMA_MISC_PACK_DIR_SET(config->out_byte_order);
    ptr->OUTDMABASE = JPEG_OUTDMABASE_ADDR_SET(config->out_buffer);
    ptr->OUTDMA_CTRL0 = JPEG_OUTDMA_CTRL0_TTLEN_SET(total_bytes);
    ptr->OUTDMA_CTRL1 = JPEG_OUTDMA_CTRL1_ROWLEN_SET(total_bytes >> 16);

    ptr->ONXT_CMD = JPEG_ONXT_CMD_ADDR_SET(5) | JPEG_ONXT_CMD_OP_VALID_MASK;

    jpeg_config_interal_regs(ptr, false, macro_block_count, config->jpeg_format);

    ptr->WIDTH = config->width_in_pixel - 1;
    ptr->HEIGHT = config->height_in_pixel - 1;

    if (jpeg_need_csc(config->in_pixel_format, config->out_pixel_format)) {
        if (config->enable_ycbcr) {
            ptr->RGB2YUV_COEF0 = JPEG_RGB2YUV_COEF0_C0_SET(0x42)
                | JPEG_RGB2YUV_COEF0_UV_OFFSET_SET(0x80)
                | JPEG_RGB2YUV_COEF0_Y_OFFSET_SET(0x10)
                | JPEG_RGB2YUV_COEF0_ENABLE_MASK
                | JPEG_RGB2YUV_COEF0_YCBCR_MODE_MASK;
            ptr->RGB2YUV_COEF1 = JPEG_RGB2YUV_COEF1_C1_SET(0x81)
                | JPEG_RGB2YUV_COEF1_C4_SET(0x7B5);
            ptr->RGB2YUV_COEF2 = JPEG_RGB2YUV_COEF2_C2_SET(0x19)
                | JPEG_RGB2YUV_COEF2_C3_SET(0x7DA);
            ptr->RGB2YUV_COEF3 = JPEG_RGB2YUV_COEF3_C6_SET(0x70)
                | JPEG_RGB2YUV_COEF3_C5_SET(0x70);
            ptr->RGB2YUV_COEF4 = JPEG_RGB2YUV_COEF4_C8_SET(0x7EE)
                | JPEG_RGB2YUV_COEF4_C7_SET(0x7A2);
        } else {
            ptr->RGB2YUV_COEF0 = JPEG_RGB2YUV_COEF0_C0_SET(0x4D)
                | JPEG_RGB2YUV_COEF0_UV_OFFSET_SET(0)
                | JPEG_RGB2YUV_COEF0_Y_OFFSET_SET(0x0)
                | JPEG_RGB2YUV_COEF0_ENABLE_MASK;
            ptr->RGB2YUV_COEF1 = JPEG_RGB2YUV_COEF1_C1_SET(0x96)
                | JPEG_RGB2YUV_COEF1_C4_SET(0x7B6);
            ptr->RGB2YUV_COEF2 = JPEG_RGB2YUV_COEF2_C2_SET(0x1D)
                | JPEG_RGB2YUV_COEF2_C3_SET(0x7DA);
            ptr->RGB2YUV_COEF3 = JPEG_RGB2YUV_COEF3_C6_SET(0x9D)
                | JPEG_RGB2YUV_COEF3_C5_SET(0x70);
            ptr->RGB2YUV_COEF4 = JPEG_RGB2YUV_COEF4_C8_SET(0x7E6)
                | JPEG_RGB2YUV_COEF4_C7_SET(0x77C);
        }
    } else {
        ptr->RGB2YUV_COEF0 = 0x04030000;
    }

    ptr->CFG = JPEG_CFG_CFG_IPATH_SEL_SET(jpeg_supported_pixel_format[config->in_pixel_format].ipath)
        |  JPEG_CFG_CFG_OPATH_SEL_SET(jpeg_supported_pixel_format[config->out_pixel_format].opath)
        | JPEG_CFG_CLKGATE_MASK
        | JPEG_CFG_JDATA_FORMAT_SET(config->jpeg_format)
        | JPEG_CFG_JPEG_EN_MASK
        | JPEG_CFG_START_MASK;

    return status_success;
}


hpm_stat_t jpeg_start_decode(JPEG_Type *ptr,
                             jpeg_job_config_t *config,
                             uint32_t length)
{
    uint32_t macro_block_count;
    uint32_t macro_block_bytes;
    uint32_t total_bytes;
    jpeg_sampling_t *sampling;

    if (!jpeg_is_valid_size(config->jpeg_format, config->width_in_pixel, config->height_in_pixel)) {
        return status_invalid_argument;
    }

    jpeg_disable(ptr);
    jpeg_software_reset(ptr);

    sampling = (jpeg_sampling_t *)&jpeg_supported_sampling[config->jpeg_format];
    macro_block_count = jpeg_calculate_macro_block_count(config->width_in_pixel, config->height_in_pixel, sampling);
    macro_block_bytes = (JPEG_HY(sampling) * JPEG_VY(sampling)
            + 2 * JPEG_HC(sampling) * JPEG_VC(sampling)) << 6;
    total_bytes = macro_block_count * macro_block_bytes;

    /* input DMA setting */
    ptr->INDMA_MISC = JPEG_INDMA_MISC_IN_DMA_ID_SET(1)
        | JPEG_INDMA_MISC_IN_DMA_REQ_MASK
        | JPEG_INDMA_MISC_MAX_OT_SET(2)
        | JPEG_INDMA_MISC_PACK_DIR_SET(config->in_byte_order);
    ptr->INDMABASE = JPEG_INDMABASE_ADDR_SET(config->in_buffer);
    /* TODO: check if it has to use the compressed length */
    ptr->INDMA_CTRL0 = JPEG_INDMA_CTRL0_TTLEN_SET(length);
    ptr->INDMA_CTRL1 = JPEG_INDMA_CTRL1_ROWLEN_SET(length >> 16);
    ptr->INXT_CMD = JPEG_INXT_CMD_ADDR_SET(5) | JPEG_INXT_CMD_OP_VALID_MASK;

    /* output DMA setting */
    ptr->OUTDMA_MISC = JPEG_OUTDMA_MISC_EN_OUTCNT_MASK
        | JPEG_OUTDMA_MISC_OUT_DMA_ID_SET(0)
        | JPEG_OUTDMA_MISC_INI_OUTCNT_MASK
        | JPEG_OUTDMA_MISC_OUT_DMA_REQ_MASK
        | JPEG_OUTDMA_MISC_OUTDMA2D_MASK
        | JPEG_OUTDMA_MISC_PACK_DIR_SET(config->out_byte_order);
    ptr->OUTDMABASE = JPEG_OUTDMABASE_ADDR_SET(config->out_buffer);
    ptr->OUTDMA_CTRL0 = JPEG_OUTDMA_CTRL0_TTLEN_SET(total_bytes)
        | JPEG_OUTDMA_CTRL0_PITCH_SET(config->width_in_pixel * jpeg_supported_pixel_format[config->in_pixel_format].pixel_width);
    ptr->OUTDMA_CTRL1 = JPEG_OUTDMA_CTRL1_ROWLEN_SET(total_bytes >> 16);
    ptr->ONXT_CMD = JPEG_ONXT_CMD_ADDR_SET(5) | JPEG_ONXT_CMD_OP_VALID_MASK;

    jpeg_config_interal_regs(ptr, true, macro_block_count, config->jpeg_format);

    ptr->WIDTH = config->width_in_pixel - 1;
    ptr->HEIGHT = config->height_in_pixel - 1;

    ptr->CSC_COEF0 = 0x4ab01f0
        | JPEG_CSC_COEF0_YCBCR_MODE_SET(config->enable_ycbcr)
        | JPEG_CSC_COEF0_ENABLE_SET(jpeg_need_csc(config->in_pixel_format, config->out_pixel_format));
    ptr->CSC_COEF1 = 0x01980204;
    ptr->CSC_COEF2 = 0x0730079C;

    ptr->CFG = JPEG_CFG_CFG_OPATH_SEL_SET(jpeg_supported_pixel_format[config->out_pixel_format].opath)
        | JPEG_CFG_JDATA_FORMAT_SET(config->jpeg_format)
        | JPEG_CFG_JPEG_EN_MASK
        | JPEG_CFG_START_MASK
        | JPEG_CFG_CLKGATE_MASK
        | JPEG_CFG_MODE_MASK;
    return status_success;
}

#define JPEG_TABLE_WIDTH(x)  (((x) & 0xF00000UL) >> 20)
#define JPEG_TABLE_LENGTH(x) (((x) & 0xFFFF0UL) >> 4)
#define JPEG_TABLE_TYPE(x)   (((x) & 0xFUL))
#define JPEG_TABLE_VALUE_MASK(x) (((x) == 4) ? (0xFFFFFFFFUL) : ((1 << ((x) << 3)) - 1))

hpm_stat_t jpeg_fill_table(JPEG_Type *ptr, jpeg_table_t table, uint8_t *data, uint32_t count)
{
    uint32_t i = 0;
    uint32_t width = JPEG_TABLE_WIDTH(table);
    uint32_t length = JPEG_TABLE_LENGTH(table);
    uint32_t type = JPEG_TABLE_TYPE(table);
    uint32_t *p;

    if (length != count) {
        return status_invalid_argument;
    }

    ptr->BUFADDR = type << 28;
    for (i = 0; i < count; i++) {
        p = (uint32_t *) &data[i * width];
        ptr->BUFDATA = JPEG_BUFADDR_ADDR_SET(*p & JPEG_TABLE_VALUE_MASK(width));
    }
    return status_success;
}

