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

#define HPM_I2S_SLOT_MASK I2S_TXDSLOT_EN_MASK /* TX/RX has same SLOT MASK */


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

/* work around: fill dummy data into TX fifo to avoid TX underflow during tx start */
hpm_stat_t i2s_fill_tx_dummy_data(I2S_Type *ptr, uint8_t data_line, uint8_t data_count)
{
    uint32_t retry = 0;

    if (data_count > I2S_SOC_MAX_TX_FIFO_DEPTH) {
        return status_invalid_argument;
    }

    /* check dummy data count in TX FIFO */
    while (i2s_get_tx_line_fifo_level(ptr, data_line) < data_count) {
        ptr->TXD[data_line] = 0;
        if (retry > HPM_I2S_DRV_DEFAULT_RETRY_COUNT * data_count) {
            return status_timeout;
        }
        retry++;
    }

    return status_success;
}

/* The I2S software reset function relies on a working BCLK */
void i2s_reset_all(I2S_Type *ptr)
{
    uint32_t cfgr_temp, misc_cfgr_temp;

    /* disable I2S */
    ptr->CTRL &= ~I2S_CTRL_I2S_EN_MASK;

    /* enable internal clock for software reset function */
    cfgr_temp = ptr->CFGR;
    ptr->CFGR |= I2S_CFGR_BCLK_DIV_SET(1);
    ptr->CFGR &= ~(I2S_CFGR_MCK_SEL_OP_MASK | I2S_CFGR_BCLK_SEL_OP_MASK | I2S_CFGR_FCLK_SEL_OP_MASK | I2S_CFGR_BCLK_GATEOFF_MASK);
    misc_cfgr_temp = ptr->MISC_CFGR;
    ptr->MISC_CFGR &= ~I2S_MISC_CFGR_MCLK_GATEOFF_MASK;

    /* reset function block and clear fifo */
    ptr->CTRL |= (I2S_CTRL_TXFIFOCLR_MASK | I2S_CTRL_RXFIFOCLR_MASK | I2S_CTRL_SFTRST_CLKGEN_MASK | I2S_CTRL_SFTRST_TX_MASK | I2S_CTRL_SFTRST_RX_MASK);
    ptr->CTRL &= ~(I2S_CTRL_TXFIFOCLR_MASK | I2S_CTRL_RXFIFOCLR_MASK | I2S_CTRL_SFTRST_CLKGEN_MASK | I2S_CTRL_SFTRST_TX_MASK | I2S_CTRL_SFTRST_RX_MASK);

    /* Restore the value of the register */
    ptr->CFGR = cfgr_temp;
    ptr->MISC_CFGR = misc_cfgr_temp;
}

void i2s_get_default_config(I2S_Type *ptr, i2s_config_t *config)
{
    (void) ptr;
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
    config->tx_fifo_threshold = 4;
    config->rx_fifo_threshold = 4;
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
    ptr->FIFO_THRESH = I2S_FIFO_THRESH_TX_SET(config->tx_fifo_threshold)
        | I2S_FIFO_THRESH_RX_SET(config->rx_fifo_threshold);
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
    uint8_t channel_num_per_frame = HPM_NUM_TO_EVEN_CEILING(config->channel_num_per_frame);
    if (!i2s_audio_depth_is_valid(config->audio_depth)
        || !i2s_channel_length_is_valid(config->channel_length)
        || !config->sample_rate
        || !channel_num_per_frame
        || (channel_num_per_frame > I2S_SOC_MAX_CHANNEL_NUM)
        || ((!config->enable_tdm_mode) && (channel_num_per_frame > 2))
        || ((config->channel_slot_mask & HPM_I2S_SLOT_MASK) == 0)) {
        return status_invalid_argument;
    }

    ptr->TXDSLOT[config->data_line] = config->channel_slot_mask;

    /* work around: fill dummy data into TX fifo to avoid TX underflow during tx start */
    if (i2s_fill_tx_dummy_data(ptr, config->data_line, config->channel_num_per_frame) != status_success) {
        return status_invalid_argument;
    }

    ptr->CTRL = (ptr->CTRL & ~(I2S_CTRL_TX_EN_MASK))
        | I2S_CTRL_TX_EN_SET(1 << config->data_line);

    return status_success;
}

static hpm_stat_t _i2s_config_rx(I2S_Type *ptr, i2s_transfer_config_t *config)
{
    /* channel_num_per_frame has to even. non TDM mode, it has be 2 */
    uint8_t channel_num_per_frame = HPM_NUM_TO_EVEN_CEILING(config->channel_num_per_frame);
    if (!i2s_audio_depth_is_valid(config->audio_depth)
        || !i2s_channel_length_is_valid(config->channel_length)
        || !config->sample_rate
        || !channel_num_per_frame
        || (channel_num_per_frame > I2S_SOC_MAX_CHANNEL_NUM)
        || ((!config->enable_tdm_mode) && (channel_num_per_frame > 2))
        || ((config->channel_slot_mask & HPM_I2S_SLOT_MASK) == 0)) {
        return status_invalid_argument;
    }

    ptr->RXDSLOT[config->data_line] = config->channel_slot_mask;
    ptr->CTRL = (ptr->CTRL & ~(I2S_CTRL_RX_EN_MASK))
            | I2S_CTRL_RX_EN_SET(1 << config->data_line);

    return status_success;
}

static hpm_stat_t _i2s_config_transfer(I2S_Type *ptr, i2s_transfer_config_t *config)
{
    /* channel_num_per_frame has to even. non TDM mode, it has be 2 */
    uint8_t channel_num_per_frame = HPM_NUM_TO_EVEN_CEILING(config->channel_num_per_frame);
    if (!i2s_audio_depth_is_valid(config->audio_depth)
        || !i2s_channel_length_is_valid(config->channel_length)
        || !config->sample_rate
        || !channel_num_per_frame
        || (channel_num_per_frame > I2S_SOC_MAX_CHANNEL_NUM)
        || ((!config->enable_tdm_mode) && (channel_num_per_frame > 2))
        || ((config->channel_slot_mask & HPM_I2S_SLOT_MASK) == 0)) {
        return status_invalid_argument;
    }

    /* Suppose RX and TX use same channel */
    ptr->RXDSLOT[config->data_line] = config->channel_slot_mask;
    ptr->TXDSLOT[config->data_line] = config->channel_slot_mask;

    /* work around: fill dummy data into TX fifo to avoid TX underflow during tx start */
    if (i2s_fill_tx_dummy_data(ptr, config->data_line, config->channel_num_per_frame) != status_success) {
        return status_invalid_argument;
    }

    ptr->CTRL = (ptr->CTRL & ~(I2S_CTRL_RX_EN_MASK | I2S_CTRL_TX_EN_MASK))
            | I2S_CTRL_RX_EN_SET(1 << config->data_line)
            | I2S_CTRL_TX_EN_SET(1 << config->data_line);

    return status_success;
}

hpm_stat_t i2s_config_tx(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config)
{
    uint32_t bclk_in_hz;
    uint32_t bclk_div;
    uint8_t channel_num_per_frame = HPM_NUM_TO_EVEN_CEILING(config->channel_num_per_frame);

    bclk_in_hz = config->sample_rate * config->channel_length * channel_num_per_frame;
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

    uint8_t channel_num_per_frame = HPM_NUM_TO_EVEN_CEILING(config->channel_num_per_frame);
    bclk_in_hz = config->sample_rate * config->channel_length * channel_num_per_frame;
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

    uint8_t channel_num_per_frame = HPM_NUM_TO_EVEN_CEILING(config->channel_num_per_frame);
    bclk_in_hz = config->sample_rate * config->channel_length * channel_num_per_frame;
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
    transfer->channel_slot_mask = 0x3;
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
    transfer->channel_slot_mask = 0x3;
}
