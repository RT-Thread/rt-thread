/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_i2s_drv.h"

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
    for (uint32_t i = 0; i < I2S_DATA_LINE_MAX; i++) {
        ptr->TXDSLOT[i] = 0;
        for (uint32_t j = 0; j < I2S_SOC_MAX_TX_CHANNEL_NUM; j++) {
            ptr->TXD[i] = 0x01;
        }
    }
}

static void i2s_config_cfgr(I2S_Type *ptr,
                            uint32_t bclk_div,
                            i2s_transfer_config_t *config)
{
    i2s_gate_bclk(ptr);
    ptr->CFGR = I2S_CFGR_BCLK_DIV_SET(bclk_div)
        | I2S_CFGR_TDM_EN_SET(config->enable_tdm_mode)
        | I2S_CFGR_CH_MAX_SET(config->channel_num_per_frame)
        | I2S_CFGR_STD_SET(config->protocol)
        | I2S_CFGR_DATSIZ_SET(config->audio_depth)
        | I2S_CFGR_CHSIZ_SET(config->channel_length);
    i2s_ungate_bclk(ptr);
}

hpm_stat_t i2s_config_tx(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config)
{
    uint32_t bclk_freq_in_hz;
    uint32_t bclk_div;
    if (I2S_AUDIO_DEPTH_IS_NOT_VALID(config->audio_depth)
            || !config->sample_rate
            || !config->channel_num_per_frame
            || (config->channel_num_per_frame > I2S_SOC_MAX_CHANNEL_NUM)
            || !(config->channel_slot_mask & ((1U << config->channel_num_per_frame) - 1U))) {
        return status_invalid_argument;
    }

    bclk_freq_in_hz = config->sample_rate * ((config->channel_length << 4) + 16) * config->channel_num_per_frame;
    bclk_div = mclk_in_hz / bclk_freq_in_hz;
    if ((bclk_div > (I2S_CFGR_BCLK_DIV_MASK >> I2S_CFGR_BCLK_DIV_SHIFT))) {
        return status_invalid_argument;
    }
    if ((bclk_div * bclk_freq_in_hz) < mclk_in_hz) {
        bclk_div++;
    }

    i2s_disable(ptr);
    i2s_config_cfgr(ptr, bclk_div, config);

    if (config->channel_slot_mask) {
        ptr->TXDSLOT[config->data_line] = config->channel_slot_mask;
    }
    ptr->CTRL = (ptr->CTRL & ~(I2S_CTRL_TX_EN_MASK))
        | I2S_CTRL_TX_EN_SET(1 << config->data_line)
        | I2S_CTRL_I2S_EN_MASK;
    return status_success;
}

hpm_stat_t i2s_config_rx(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config)
{
    uint32_t bclk_freq_in_hz;
    uint32_t bclk_div;
    if (I2S_AUDIO_DEPTH_IS_NOT_VALID(config->audio_depth)
            || !config->sample_rate
            || !config->channel_num_per_frame
            || (config->channel_num_per_frame > I2S_SOC_MAX_CHANNEL_NUM)
            || !(config->channel_slot_mask & ((1U << config->channel_num_per_frame) - 1U))) {
        return status_invalid_argument;
    }

    bclk_freq_in_hz = config->sample_rate * ((config->channel_length << 4) + 16) * config->channel_num_per_frame;
    bclk_div = mclk_in_hz / bclk_freq_in_hz;
    if (!bclk_div || (bclk_div > (I2S_CFGR_BCLK_DIV_MASK >> I2S_CFGR_BCLK_DIV_SHIFT))) {
        return status_invalid_argument;
    }
    if ((bclk_div * bclk_freq_in_hz) < mclk_in_hz) {
        bclk_div++;
    }

    i2s_disable(ptr);
    i2s_config_cfgr(ptr, bclk_div, config);

    if (config->channel_slot_mask) {
        ptr->RXDSLOT[config->data_line] = config->channel_slot_mask;
    }
    ptr->CTRL = (ptr->CTRL & ~(I2S_CTRL_RX_EN_MASK))
            | I2S_CTRL_RX_EN_SET(1 << config->data_line)
            | I2S_CTRL_I2S_EN_MASK;
    return status_success;
}

hpm_stat_t i2s_config_transfer(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config)
{
    uint32_t bclk_freq_in_hz;
    uint32_t bclk_div;
    if (I2S_AUDIO_DEPTH_IS_NOT_VALID(config->audio_depth)
            || !config->sample_rate
            || !config->channel_num_per_frame
            || (config->channel_num_per_frame > I2S_SOC_MAX_CHANNEL_NUM)
            || !(config->channel_slot_mask & ((1U << config->channel_num_per_frame) - 1U))) {
        return status_invalid_argument;
    }

    bclk_freq_in_hz = config->sample_rate * ((config->channel_length << 4) + 16) * config->channel_num_per_frame;
    bclk_div = mclk_in_hz / bclk_freq_in_hz;
    if (!bclk_div || (bclk_div > (I2S_CFGR_BCLK_DIV_MASK >> I2S_CFGR_BCLK_DIV_SHIFT))) {
        return status_invalid_argument;
    }
    if ((bclk_div * bclk_freq_in_hz) < mclk_in_hz) {
        bclk_div++;
    }

    i2s_disable(ptr);
    i2s_config_cfgr(ptr, bclk_div, config);

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

uint32_t i2s_send_data(I2S_Type *ptr, uint8_t tx_line_index, uint32_t *src, uint32_t size)
{
    register uint32_t count;
    for (count = 0; count < size; count ++) {
        ptr->TXD[tx_line_index] = *(src + count);
    }
    return count;
}

uint32_t i2s_receive_data(I2S_Type *ptr, uint8_t rx_line_index, uint32_t *dst, uint32_t size)
{
    register uint32_t count;
    for (count = 0; count < size; count++) {
        *(dst + count) = ptr->RXD[rx_line_index];
    }
    return count;
}

void i2s_get_default_transfer_config_for_pdm(i2s_transfer_config_t *transfer)
{
    transfer->sample_rate = PDM_SOC_SAMPLE_RATE_IN_HZ;
    transfer->channel_num_per_frame = 16;
    transfer->channel_length = I2S_CHANNEL_LENGTH_32_BITS;
    transfer->audio_depth = I2S_AUDIO_DEPTH_32_BITS;
    transfer->enable_tdm_mode = true;
    transfer->protocol = I2S_PROTOCOL_MSB_JUSTIFIED;
}

void i2s_get_default_transfer_config_for_dao(i2s_transfer_config_t *transfer)
{
    transfer->sample_rate = DAO_SOC_SAMPLE_RATE_IN_HZ;
    transfer->channel_num_per_frame = 2;
    transfer->channel_length = I2S_CHANNEL_LENGTH_32_BITS;
    transfer->audio_depth = I2S_AUDIO_DEPTH_32_BITS;
    transfer->enable_tdm_mode = false;
    transfer->protocol = I2S_PROTOCOL_MSB_JUSTIFIED;
    transfer->data_line = I2S_DATA_LINE_0;
    transfer->channel_slot_mask = 0xFFFF;
}

void i2s_get_default_transfer_config(i2s_transfer_config_t *transfer)
{
    transfer->sample_rate = 48000U;
    transfer->channel_num_per_frame = 2;
    transfer->channel_length = I2S_CHANNEL_LENGTH_32_BITS;
    transfer->audio_depth = I2S_AUDIO_DEPTH_32_BITS;
    transfer->enable_tdm_mode = false;
    transfer->protocol = I2S_PROTOCOL_MSB_JUSTIFIED;
    transfer->data_line = I2S_DATA_LINE_0;
    transfer->channel_slot_mask = 0xFFFF;
}
