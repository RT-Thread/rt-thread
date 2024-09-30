/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_smix_drv.h"

static uint8_t smix_get_fir_shift(smix_mixer_rate_convert_t rate)
{
    uint8_t shift = 0;

    switch (rate) {
    case smix_mixer_no_rate_convert:
    case smix_mixer_upper_2x_sample:
    case smix_mixer_upper_3x_sample:
        shift = 0;
        break;
    case smix_mixer_upper_4x_sample:
    case smix_mixer_upper_6x_sample:
        shift = 1;
        break;
    case smix_mixer_upper_8x_sample:
    case smix_mixer_upper_12x_sample:
        shift = 2;
        break;
    case smix_mixer_lower_2x_sample:
        shift = 7;
        break;
    default:
        shift = 0;
        break;
    }

    return shift;
}

void smix_get_dma_default_ch_config(SMIX_Type *ptr, smix_dma_ch_config_t *config)
{
    (void) ptr;
    config->priority = 0;
    config->src_mode = smix_dma_mode_normal;
    config->dst_mode = smix_dma_mode_normal;
    config->src_width = smix_dma_transfer_half_word;
    config->dst_width = smix_dma_transfer_half_word;
    config->src_addr_ctrl = smix_dma_address_increment;
    config->dst_addr_ctrl = smix_dma_address_increment;
    config->src_burst_size = smix_dma_transfer_burst_1t;
    config->trans_bytes = 0;
    config->linked_ptr = 0;
    config->src_req_sel = 0;
    config->dst_req_sel = 0;

    config->abort_int_en = false;
    config->error_int_en = false;
    config->complete_int_en = false;
}


void smix_get_mixer_dst_ch_default_config(SMIX_Type *ptr, smix_mixer_dst_config_t *config)
{
    (void) ptr;
    config->underflow_int_en = false;
    config->fifo_thr = 8; /* Must be greater than or equal to 8 */
    config->calsat_int_en = false;
    config->da_int_en = false;
    config->auto_deactivate_en = false;
    config->fadeout_done_int_en = false;
    config->deactivate_en = false;
    config->active_en = true;
    config->fadeout_now_en = false;
    config->fadeout_auto_en = false;
    config->fadein_en = false;
    config->channel_en = true;
    config->mixer_en = true;

    config->gain = smix_mixer_gain_0db;
    config->length = 0; /* 0 = infinite length */
    config->fadein_delta = 6; /* 48K sample rate, need 3s */
    config->fadeout_delta = 14; /* 48K sample rate, need 1/3s */
    config->src_ch_mask = 0x1;
}

void smix_get_mixer_source_ch_default_config(SMIX_Type *ptr, smix_mixer_source_config_t *config)
{
    (void) ptr;
    config->fifo_thr = 4; /* Must be greater than or equal to 4 */
    config->calsat_int_en = false;
    config->dn_int_en = false;
    config->auto_deactivate_en = true;
    config->fadeout_int_en = false;

    config->convert_rate = smix_mixer_no_rate_convert;
    config->gain = smix_mixer_gain_0db;
    config->fadein_delta = 6; /* 48K sample rate, need 3s */
    config->fadeout_delta = 14; /* 48K sample rate, need 1/3s */
    config->length = 0; /* 0 = infinite length */
}

hpm_stat_t smix_config_dma_channel(SMIX_Type *ptr, uint8_t ch, smix_dma_ch_config_t *config, bool start)
{
    uint32_t tmp;

    if ((config->trans_bytes & ((1 << config->dst_width) - 1))
     || (config->src_addr & ((1 << config->src_width) - 1))
     || (config->dst_addr & ((1 << config->dst_width) - 1))
     || (config->linked_ptr & 0x7)) {
        return status_invalid_argument;
    }

    ptr->DMA_CH[ch].SRCADDR = SMIX_DMA_CH_SRCADDR_PTR_SET(config->src_addr);
    ptr->DMA_CH[ch].DSTADDR = SMIX_DMA_CH_DSTADDR_PTR_SET(config->dst_addr);
    ptr->DMA_CH[ch].BURST_COUNT = SMIX_DMA_CH_BURST_COUNT_NUM_SET(config->trans_bytes >> config->src_width);
    ptr->DMA_CH[ch].LLP = SMIX_DMA_CH_LLP_PTR_SET(config->linked_ptr);

    /* clear status bit, W1C */
    ptr->DMAC_ERR_ST = 1 << ch;
    ptr->DMAC_ABRT_ST = 1 << ch;
    ptr->DMAC_TC_ST = 1 << ch;

    tmp = SMIX_DMA_CH_CTL_SRCREQSEL_SET(config->src_req_sel)
        | SMIX_DMA_CH_CTL_DSTREQSEL_SET(config->dst_req_sel)
        | SMIX_DMA_CH_CTL_PRIORITY_SET(config->priority)
        | SMIX_DMA_CH_CTL_SRCBURSTSIZE_SET(config->src_burst_size)
        | SMIX_DMA_CH_CTL_SRCWIDTH_SET(config->src_width)
        | SMIX_DMA_CH_CTL_DSTWIDTH_SET(config->dst_width)
        | SMIX_DMA_CH_CTL_SRCMODE_SET(config->src_mode)
        | SMIX_DMA_CH_CTL_DSTMODE_SET(config->dst_mode)
        | SMIX_DMA_CH_CTL_SRCADDRCTRL_SET(config->src_addr_ctrl)
        | SMIX_DMA_CH_CTL_DSTADDRCTRL_SET(config->dst_addr_ctrl)
        | SMIX_DMA_CH_CTL_ABRT_INT_EN_SET(config->abort_int_en)
        | SMIX_DMA_CH_CTL_ERR_INT_EN_SET(config->error_int_en)
        | SMIX_DMA_CH_CTL_TC_INT_EN_SET(config->complete_int_en);

    if (start) {
        tmp |= SMIX_DMA_CH_CTL_EN_MASK;
    }
    ptr->DMA_CH[ch].CTL = tmp;

    return status_success;
}

hpm_stat_t smix_mixer_config_source_ch(SMIX_Type *ptr, uint8_t ch, smix_mixer_source_config_t *src)
{
    /* reset fifo */
    ptr->SOURCE_CH[ch].CTRL |= SMIX_SOURCE_CH_CTRL_FIFO_RESET_MASK;
    ptr->SOURCE_CH[ch].CTRL &= ~SMIX_SOURCE_CH_CTRL_FIFO_RESET_MASK;

    ptr->SOURCE_CH[ch].CTRL = SMIX_SOURCE_CH_CTRL_THRSH_SET(src->fifo_thr)
                        | SMIX_SOURCE_CH_CTRL_CALSAT_INT_EN_SET(src->calsat_int_en)
                        | SMIX_SOURCE_CH_CTRL_DN_INT_EN_SET(src->dn_int_en)
                        | SMIX_SOURCE_CH_CTRL_SHFT_CTRL_SET(smix_get_fir_shift(src->convert_rate))
                        | SMIX_SOURCE_CH_CTRL_AUTODEACTAFTERFADEOUT_EN_SET(src->auto_deactivate_en)
                        | SMIX_SOURCE_CH_CTRL_FADEOUT_DONE_IE_SET(src->fadeout_int_en)
                        | SMIX_SOURCE_CH_CTRL_RATECONV_SET(src->convert_rate);

    ptr->SOURCE_CH[ch].GAIN = SMIX_SOURCE_CH_GAIN_VAL_SET(src->gain);

    ptr->SOURCE_CH[ch].FADEIN = SMIX_SOURCE_CH_FADEIN_DELTA_SET(src->fadein_delta);

    ptr->SOURCE_CH[ch].FADEOUT = SMIX_SOURCE_CH_FADEOUT_DELTA_SET(src->fadeout_delta);

    if (src->length == 0) {
        ptr->SOURCE_CH[ch].BUFSIZE = SMIX_SOURCE_CH_BUFSIZE_MAXIDX_SET(0);
    } else {
        ptr->SOURCE_CH[ch].BUFSIZE = SMIX_SOURCE_CH_BUFSIZE_MAXIDX_SET(src->length - 1);
    }

    return status_success;
}


hpm_stat_t smix_mixer_config_dst_ch(SMIX_Type *ptr, uint8_t ch, smix_mixer_dst_config_t *dst)
{
    /* Reset */
    ptr->DST_CH[ch].CTRL |= SMIX_DST_CH_CTRL_SOFTRST_MASK;
    ptr->DST_CH[ch].CTRL &= ~SMIX_DST_CH_CTRL_SOFTRST_MASK;

    ptr->DST_CH[ch].GAIN = SMIX_DST_CH_GAIN_VAL_SET(dst->gain);

    if (dst->length == 0) {
        ptr->DST_CH[ch].BUFSIZE = SMIX_DST_CH_BUFSIZE_MAX_IDX_SET(0);
    } else {
        ptr->DST_CH[ch].BUFSIZE = SMIX_DST_CH_BUFSIZE_MAX_IDX_SET(dst->length - 1);
    }

    ptr->DST_CH[ch].FADEIN = SMIX_DST_CH_FADEIN_DELTA_SET(dst->fadein_delta);

    ptr->DST_CH[ch].FADEOUT = SMIX_DST_CH_FADEOUT_DELTA_SET(dst->fadeout_delta);

    ptr->DST_CH[ch].SOURCE_EN = dst->src_ch_mask;
    ptr->DST_CH[ch].SOURCE_ACT = dst->src_ch_mask;

    ptr->DST_CH[ch].CTRL = SMIX_DST_CH_CTRL_DATA_UNFL_IE_SET(dst->underflow_int_en)
                        | SMIX_DST_CH_CTRL_THRSH_SET(dst->fifo_thr)
                        | SMIX_DST_CH_CTRL_CALSAT_INT_EN_SET(dst->calsat_int_en)
                        | SMIX_DST_CH_CTRL_DA_INT_EN_SET(dst->da_int_en)
                        | SMIX_DST_CH_CTRL_ADEACTFADEOUT_EN_SET(dst->auto_deactivate_en)
                        | SMIX_DST_CH_CTRL_FADEOUT_DONE_IE_SET(dst->fadeout_done_int_en)
                        | SMIX_DST_CH_CTRL_DST_DEACT_SET(dst->deactivate_en)
                        | SMIX_DST_CH_CTRL_DST_ACT_SET(dst->active_en)
                        | SMIX_DST_CH_CTRL_DSTFADOUT_MEN_SET(dst->fadeout_now_en)
                        | SMIX_DST_CH_CTRL_DSTFADOUT_AEN_SET(dst->fadeout_auto_en)
                        | SMIX_DST_CH_CTRL_DSTFADIN_EN_SET(dst->fadein_en)
                        | SMIX_DST_CH_CTRL_DST_EN_SET(dst->channel_en);

    /* Workaround: DST_CH[0].CTRL.MIXER_EN bit controls mixer module enable or disable, DST_CH[1].CTRL.MIXER_EN should not be set */
    if (dst->mixer_en) {
        ptr->DST_CH[0].CTRL |= SMIX_DST_CH_CTRL_MIXER_EN_MASK;
        ptr->DST_CH[1].CTRL &= ~SMIX_DST_CH_CTRL_MIXER_EN_MASK;
    }

    return status_success;
}

hpm_stat_t smix_mixer_config_dst_fadein_delta(SMIX_Type *ptr, uint8_t ch, uint32_t target_sample_rate, uint32_t ms)
{
    uint32_t delta = SMIX_DST_CH_FADEIN_DELTA_MASK * 1000 / target_sample_rate / ms;

    if (delta == 0) {
        return status_invalid_argument;
    }
    ptr->DST_CH[ch].FADEIN = SMIX_DST_CH_FADEIN_DELTA_SET(delta);
    return status_success;
}

hpm_stat_t smix_mixer_config_dst_fadeout_delta(SMIX_Type *ptr, uint8_t ch, uint32_t target_sample_rate, uint32_t ms)
{
    uint32_t delta = (uint32_t)log2(target_sample_rate * ms / 1000);

    /* fadeout delta valid bit: 14 */
    if (delta > 0x3fff) {
        return status_invalid_argument;
    }
    ptr->DST_CH[ch].FADEOUT = SMIX_DST_CH_FADEOUT_DELTA_SET(delta);
    return status_success;
}

hpm_stat_t smix_mixer_config_source_fadein_delta(SMIX_Type *ptr, uint8_t ch, uint32_t target_sample_rate, uint32_t ms)
{
    uint32_t delta = SMIX_DST_CH_FADEIN_DELTA_MASK * 1000 / target_sample_rate / ms;

    if (delta == 0) {
        return status_invalid_argument;
    }
    ptr->SOURCE_CH[ch].FADEIN = SMIX_SOURCE_CH_FADEIN_DELTA_SET(delta);
    return status_success;
}

hpm_stat_t smix_mixer_config_source_fadeout_delta(SMIX_Type *ptr, uint8_t ch, uint32_t target_sample_rate, uint32_t ms)
{
    uint32_t delta = (uint32_t)log2(target_sample_rate * ms / 1000);

    /* fadeout delta valid bit: 14 */
    if (delta > 0x3fff) {
        return status_invalid_argument;
    }
    ptr->SOURCE_CH[ch].FADEOUT = SMIX_SOURCE_CH_FADEOUT_DELTA_SET(delta);
    return status_success;
}