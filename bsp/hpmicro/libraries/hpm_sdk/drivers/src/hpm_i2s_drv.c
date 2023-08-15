/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_i2s_drv.h"

#define HPM_I2S_DRV_DEFAULT_RETRY_COUNT 5000U

#ifndef HPM_I2S_BCLK_TOLERANCE
#define HPM_I2S_BCLK_TOLERANCE (4U)
#endif

static bool i2s_audio_depth_is_valid(uint8_t bits)
{
    /* i2s audio depth only support 16bits, 24bits, 32bits */
    if (bits == i2s_audio_depth_16_bits || bits == i2s_audio_depth_24_bits || bits == i2s_audio_depth_32_bits) {
        return true;
    }
    return false;
}

static bool i2s_channel_length_is_valid(uint8_t bits)
{
    /* i2s channel length only support 16bits or 32bits */
    if (bits == i2s_channel_length_16_bits || bits == i2s_channel_length_32_bits) {
        return true;
    }
    return false;
}

void i2s_reset_all(I2S_Type *ptr)
{
    /* gate off bclk */
    ptr->CFGR |= I2S_CFGR_BCLK_GATEOFF_MASK;
    /* gate off mclk */
    ptr->MISC_CFGR |= I2S_MISC_CFGR_MCLK_GATEOFF_MASK;
    /*
     * clear fifos
     */
    ptr->CTRL |= I2S_CTRL_TXFIFOCLR_MASK | I2S_CTRL_RXFIFOCLR_MASK;
    ptr->CTRL &= ~(I2S_CTRL_TXFIFOCLR_MASK | I2S_CTRL_RXFIFOCLR_MASK);

    /*
     * software reset all blocks
     */
    ptr->CTRL |= I2S_CTRL_SFTRST_CLKGEN_MASK | I2S_CTRL_SFTRST_TX_MASK | I2S_CTRL_SFTRST_RX_MASK;
    ptr->CTRL &= ~(I2S_CTRL_SFTRST_CLKGEN_MASK | I2S_CTRL_SFTRST_TX_MASK | I2S_CTRL_SFTRST_RX_MASK);
    /*
     * disable i2s
     */
    ptr->CTRL &= ~I2S_CTRL_I2S_EN_MASK;
}

void i2s_get_default_config(I2S_Type *ptr, i2s_config_t *config)
{
    config->invert_mclk_out = false;
    config->invert_mclk_in = false;
    config->use_external_mclk = false;
    config->invert_bclk_out = false;
    config->invert_bclk_in = false;
    config->use_external_bclk = false;
    config->invert_fclk_out = false;
    config->invert_fclk_in = false;
    config->use_external_fclk = false;
    config->enable_mclk_out = false;
    config->frame_start_at_rising_edge = false;
    config->fifo_threshold = 4;
}

void i2s_init(I2S_Type *ptr, i2s_config_t *config)
{
    i2s_reset_all(ptr);

    ptr->CFGR = I2S_CFGR_INV_MCLK_OUT_SET(config->invert_mclk_out)
        | I2S_CFGR_INV_MCLK_IN_SET(config->invert_mclk_in)
        | I2S_CFGR_MCK_SEL_OP_SET(config->use_external_mclk)
        | I2S_CFGR_INV_BCLK_OUT_SET(config->invert_bclk_out)
        | I2S_CFGR_INV_BCLK_IN_SET(config->invert_bclk_in)
        | I2S_CFGR_BCLK_SEL_OP_SET(config->use_external_bclk)
        | I2S_CFGR_INV_FCLK_OUT_SET(config->invert_fclk_out)
        | I2S_CFGR_INV_FCLK_IN_SET(config->invert_fclk_in)
        | I2S_CFGR_FCLK_SEL_OP_SET(config->use_external_fclk)
        | I2S_CFGR_FRAME_EDGE_SET(config->frame_start_at_rising_edge);
    ptr->MISC_CFGR = (ptr->MISC_CFGR
            & ~(I2S_MISC_CFGR_MCLKOE_MASK
                | I2S_MISC_CFGR_MCLK_GATEOFF_MASK))
        | I2S_MISC_CFGR_MCLKOE_SET(config->enable_mclk_out);
    ptr->FIFO_THRESH = I2S_FIFO_THRESH_TX_SET(config->fifo_threshold)
        | I2S_FIFO_THRESH_RX_SET(config->fifo_threshold);
    /**
     * @brief i2s interrupt work_around
     *
     */
    for (uint32_t i = 0; i <= I2S_DATA_LINE_MAX; i++) {
        ptr->TXDSLOT[i] = 0;
        for (uint32_t j = 0; j <= I2S_SOC_MAX_TX_CHANNEL_NUM; j++) {
            ptr->TXD[i] = 0x01;
        }
    }
}

static void i2s_config_cfgr(I2S_Type *ptr,
                            uint32_t bclk_div,
                            i2s_transfer_config_t *config)
{
    i2s_gate_bclk(ptr);
    ptr->CFGR = (ptr->CFGR & ~(I2S_CFGR_BCLK_DIV_MASK | I2S_CFGR_TDM_EN_MASK | I2S_CFGR_CH_MAX_MASK | I2S_CFGR_STD_MASK | I2S_CFGR_DATSIZ_MASK | I2S_CFGR_CHSIZ_MASK))
                | I2S_CFGR_BCLK_DIV_SET(bclk_div)
                | I2S_CFGR_TDM_EN_SET(config->enable_tdm_mode)
                | I2S_CFGR_CH_MAX_SET(config->channel_num_per_frame)
                | I2S_CFGR_STD_SET(config->protocol)
                | I2S_CFGR_DATSIZ_SET(I2S_CFGR_DATASIZ(config->audio_depth))
                | I2S_CFGR_CHSIZ_SET(I2S_CFGR_CHSIZ(config->channel_length));
    i2s_ungate_bclk(ptr);
}

static void i2s_config_cfgr_slave(I2S_Type *ptr,
                            i2s_transfer_config_t *config)
{
    ptr->CFGR = (ptr->CFGR & ~(I2S_CFGR_TDM_EN_MASK | I2S_CFGR_CH_MAX_MASK | I2S_CFGR_STD_MASK | I2S_CFGR_DATSIZ_MASK | I2S_CFGR_CHSIZ_MASK))
              | I2S_CFGR_TDM_EN_SET(config->enable_tdm_mode)
              | I2S_CFGR_CH_MAX_SET(config->channel_num_per_frame)
              | I2S_CFGR_STD_SET(config->protocol)
              | I2S_CFGR_DATSIZ_SET(I2S_CFGR_DATASIZ(config->audio_depth))
              | I2S_CFGR_CHSIZ_SET(I2S_CFGR_CHSIZ(config->channel_length));
}

static bool i2s_calculate_bclk_divider(uint32_t mclk_in_hz, uint32_t bclk_in_hz, uint32_t *div_out)
{
    uint32_t bclk_div;
    uint32_t delta1, delta2;

    bclk_div = mclk_in_hz / bclk_in_hz;

    if ((bclk_div > (I2S_CFGR_BCLK_DIV_MASK >> I2S_CFGR_BCLK_DIV_SHIFT))) {
        return false;
    }

    delta1 = mclk_in_hz - bclk_in_hz * bclk_div;
    delta2 = bclk_in_hz * (bclk_div + 1) - mclk_in_hz;
    if (delta2 < delta1) {
        bclk_div++;
        if ((bclk_div > (I2S_CFGR_BCLK_DIV_MASK >> I2S_CFGR_BCLK_DIV_SHIFT))) {
            return false;
        }
    }

    if (MIN(delta1, delta2) && ((MIN(delta1, delta2) * 100 / bclk_in_hz) > HPM_I2S_BCLK_TOLERANCE)) {
        return false;
    }

    *div_out = bclk_div;
    return true;
}

static hpm_stat_t _i2s_config_tx(I2S_Type *ptr, i2s_transfer_config_t *config)
{
    /* channel_num_per_frame has to even. non TDM mode, it has be 2 */
    if (!i2s_audio_depth_is_valid(config->audio_depth)
        || !i2s_channel_length_is_valid(config->channel_length)
        || !config->sample_rate
        || !config->channel_num_per_frame
        || (config->channel_num_per_frame > I2S_SOC_MAX_CHANNEL_NUM)
        || (config->channel_num_per_frame & 1U)
        || ((!config->enable_tdm_mode) && (config->channel_num_per_frame > 2))) {
        return status_invalid_argument;
    }

    if (config->channel_slot_mask) {
        ptr->TXDSLOT[config->data_line] = config->channel_slot_mask;
    }
    ptr->CTRL = (ptr->CTRL & ~(I2S_CTRL_TX_EN_MASK))
        | I2S_CTRL_TX_EN_SET(1 << config->data_line)
        | I2S_CTRL_I2S_EN_MASK;

    return status_success;
}

static hpm_stat_t _i2s_config_rx(I2S_Type *ptr, i2s_transfer_config_t *config)
{
    /* channel_num_per_frame has to even. non TDM mode, it has be 2 */
    if (!i2s_audio_depth_is_valid(config->audio_depth)
        || !i2s_channel_length_is_valid(config->channel_length)
        || !config->sample_rate
        || !config->channel_num_per_frame
        || (config->channel_num_per_frame > I2S_SOC_MAX_CHANNEL_NUM)
        || (config->channel_num_per_frame & 1U)
        || ((!config->enable_tdm_mode) && (config->channel_num_per_frame > 2))) {
        return status_invalid_argument;
    }

    if (config->channel_slot_mask) {
        ptr->RXDSLOT[config->data_line] = config->channel_slot_mask;
    }
    ptr->CTRL = (ptr->CTRL & ~(I2S_CTRL_RX_EN_MASK))
            | I2S_CTRL_RX_EN_SET(1 << config->data_line)
            | I2S_CTRL_I2S_EN_MASK;

    return status_success;
}

static hpm_stat_t _i2s_config_transfer(I2S_Type *ptr, i2s_transfer_config_t *config)
{
    /* channel_num_per_frame has to even. non TDM mode, it has be 2 */
    if (!i2s_audio_depth_is_valid(config->audio_depth)
        || !i2s_channel_length_is_valid(config->channel_length)
        || !config->sample_rate
        || !config->channel_num_per_frame
        || (config->channel_num_per_frame > I2S_SOC_MAX_CHANNEL_NUM)
        || (config->channel_num_per_frame & 1U)
        || ((!config->enable_tdm_mode) && (config->channel_num_per_frame > 2))) {
        return status_invalid_argument;
    }

    if (config->channel_slot_mask) {
        /* Suppose RX and TX use same channel */
        ptr->RXDSLOT[config->data_line] = config->channel_slot_mask;
        ptr->TXDSLOT[config->data_line] = config->channel_slot_mask;
    } else {
        /**
         * @brief i2s interrupt work_around
         *
         */
        ptr->TXDSLOT[config->data_line] = 0x0000ffff;
    }
    ptr->CTRL = (ptr->CTRL & ~(I2S_CTRL_RX_EN_MASK | I2S_CTRL_TX_EN_MASK))
            | I2S_CTRL_RX_EN_SET(1 << config->data_line)
            | I2S_CTRL_TX_EN_SET(1 << config->data_line)
            | I2S_CTRL_I2S_EN_MASK;

    return status_success;
}

hpm_stat_t i2s_config_tx(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config)
{
    uint32_t bclk_in_hz;
    uint32_t bclk_div;

    bclk_in_hz = config->sample_rate * config->channel_length * config->channel_num_per_frame;
    if (!i2s_calculate_bclk_divider(mclk_in_hz, bclk_in_hz, &bclk_div)) {
        return status_invalid_argument;
    }

    i2s_disable(ptr);
    i2s_config_cfgr(ptr, bclk_div, config);

    return _i2s_config_tx(ptr, config);
}

hpm_stat_t i2s_config_tx_slave(I2S_Type *ptr, i2s_transfer_config_t *config)
{
    i2s_disable(ptr);
    i2s_config_cfgr_slave(ptr, config);

    return _i2s_config_tx(ptr, config);
}

hpm_stat_t i2s_config_rx(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config)
{
    uint32_t bclk_in_hz;
    uint32_t bclk_div;

    bclk_in_hz = config->sample_rate * config->channel_length * config->channel_num_per_frame;
    if (!i2s_calculate_bclk_divider(mclk_in_hz, bclk_in_hz, &bclk_div)) {
        return status_invalid_argument;
    }

    i2s_disable(ptr);
    i2s_config_cfgr(ptr, bclk_div, config);

    return _i2s_config_rx(ptr, config);
}

hpm_stat_t i2s_config_rx_slave(I2S_Type *ptr, i2s_transfer_config_t *config)
{
    i2s_disable(ptr);
    i2s_config_cfgr_slave(ptr, config);

    return _i2s_config_rx(ptr, config);
}

hpm_stat_t i2s_config_transfer(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config)
{
    uint32_t bclk_in_hz;
    uint32_t bclk_div;

    bclk_in_hz = config->sample_rate * config->channel_length * config->channel_num_per_frame;
    if (!i2s_calculate_bclk_divider(mclk_in_hz, bclk_in_hz, &bclk_div)) {
        return status_invalid_argument;
    }

    i2s_disable(ptr);
    i2s_config_cfgr(ptr, bclk_div, config);

    return _i2s_config_transfer(ptr, config);
}

hpm_stat_t i2s_config_transfer_slave(I2S_Type *ptr, i2s_transfer_config_t *config)
{
    i2s_disable(ptr);
    i2s_config_cfgr_slave(ptr, config);

    return _i2s_config_transfer(ptr, config);
}

uint32_t i2s_send_buff(I2S_Type *ptr, uint8_t tx_line_index, uint8_t samplebits, uint8_t *src, uint32_t size)
{
    uint32_t data;
    uint32_t retry = 0;
    uint8_t bytes = samplebits / 8U;
    uint32_t left;

    if (!i2s_audio_depth_is_valid(samplebits)) {
        return 0;
    }

    if ((size % bytes) != 0) {
        return 0;
    }

    left = size;
    while (left) {
        /* check fifo status */
        if (i2s_get_tx_line_fifo_level(ptr, tx_line_index) < I2S_FIFO_THRESH_TX_GET(ptr->FIFO_THRESH)) {
            /* Move valid data to high position */
            data = *((uint32_t *)(src)) << (32 - samplebits);
            ptr->TXD[tx_line_index] = data;
            src += bytes;
            left -= bytes;
            retry = 0;
        } else {
            if (retry > HPM_I2S_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }

    return size - left;
}

uint32_t i2s_receive_buff(I2S_Type *ptr, uint8_t rx_line_index, uint8_t samplebits, uint8_t *dst, uint32_t size)
{
    uint32_t data;
    uint32_t left;
    uint32_t retry = 0;
    uint8_t bytes = samplebits / 8U;

    if (!i2s_audio_depth_is_valid(samplebits)) {
        return 0;
    }

    if ((size % bytes) != 0) {
        return 0;
    }

    left = size;
    while (left) {
        /* check fifo status */
        if (i2s_get_rx_line_fifo_level(ptr, rx_line_index) < I2S_FIFO_THRESH_RX_GET(ptr->FIFO_THRESH)) {
            /* valid data on high position */
            data = ptr->RXD[rx_line_index] >> (32 - samplebits);
            for (uint8_t n = 0; n < bytes; n++) {
                *dst = (uint8_t)(data >> (8U * n)) & 0xFFU;
                dst++;
                left--;
                retry = 0;
            }
        } else {
            if (retry > HPM_I2S_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }

    return size - left;
}

void i2s_get_default_transfer_config_for_pdm(i2s_transfer_config_t *transfer)
{
    transfer->sample_rate = PDM_SOC_SAMPLE_RATE_IN_HZ;
    transfer->channel_num_per_frame = 8;
    transfer->channel_length = i2s_channel_length_32_bits;
    transfer->audio_depth = i2s_audio_depth_32_bits;
    transfer->enable_tdm_mode = true;
    transfer->protocol = I2S_PROTOCOL_MSB_JUSTIFIED;
}

void i2s_get_default_transfer_config_for_dao(i2s_transfer_config_t *transfer)
{
    transfer->sample_rate = DAO_SOC_SAMPLE_RATE_IN_HZ;
    transfer->channel_num_per_frame = 2;
    transfer->channel_length = i2s_channel_length_32_bits;
    transfer->audio_depth = i2s_audio_depth_32_bits;
    transfer->enable_tdm_mode = false;
    transfer->protocol = I2S_PROTOCOL_MSB_JUSTIFIED;
    transfer->data_line = I2S_DATA_LINE_0;
    transfer->channel_slot_mask = 0xFFFF;
}

void i2s_get_default_transfer_config(i2s_transfer_config_t *transfer)
{
    transfer->sample_rate = 48000U;
    transfer->channel_num_per_frame = 2;
    transfer->channel_length = i2s_channel_length_32_bits;
    transfer->audio_depth = i2s_audio_depth_32_bits;
    transfer->enable_tdm_mode = false;
    transfer->protocol = I2S_PROTOCOL_MSB_JUSTIFIED;
    transfer->data_line = I2S_DATA_LINE_0;
    transfer->channel_slot_mask = 0xFFFF;
}
