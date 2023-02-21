/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_spi.h"

static hpm_stat_t hpm_spi_tx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr, uint32_t src, uint32_t size)
{
    dma_handshake_config_t config;
    config.ch_index = ch_num;
    config.dst = (uint32_t)&spi_ptr->DATA;
    config.dst_fixed = true;
    config.src = src;
    config.src_fixed = false;
    config.size_in_byte = size;

    return dma_setup_handshake(dma_ptr, &config);
}

static hpm_stat_t hpm_spi_rx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr, uint32_t dst, uint32_t size)
{
    dma_handshake_config_t config;
    config.ch_index = ch_num;
    config.dst = dst;
    config.dst_fixed = false;
    config.src = (uint32_t)&spi_ptr->DATA;
    config.src_fixed = true;
    config.size_in_byte = size;

    return dma_setup_handshake(dma_ptr, &config);
}


void hpm_spi_prepare_dma_tx_descriptors(spi_context_t *context, spi_control_config_t *config, uint32_t trans_count,
                                    uint32_t *spi_transctrl, dma_linked_descriptor_t *tx_dma_descriptors)
{
    SPI_Type *ptr = context->ptr;
    uint32_t dma_transfer_size[trans_count];
    uint32_t tx_size = context->tx_size;
    uint32_t per_trans_size = context->per_trans_max;
    uint32_t dmamux_ch = context->dma_context.tx_dmamux_ch;
    uint8_t *tx_buff = context->tx_buff;

    static uint8_t dummy_cmd = 0xff;

    uint32_t temp32;
    uint32_t tx_buff_index = 0;
    for (uint32_t i = 0; i < trans_count; i++) {
        if (tx_size > per_trans_size) {
            temp32 = per_trans_size;
            tx_size -= per_trans_size;
        } else {
            temp32 = tx_size;
        }

        *(spi_transctrl + i) = SPI_TRANSCTRL_TRANSMODE_SET(config->common_config.trans_mode == spi_trans_write_read_together ?
                                                           spi_trans_write_read_together : spi_trans_write_only)
                                | SPI_TRANSCTRL_DUALQUAD_SET(config->common_config.data_phase_fmt)
                                | SPI_TRANSCTRL_WRTRANCNT_SET(temp32 - 1)
                                | SPI_TRANSCTRL_RDTRANCNT_SET(temp32 - 1);

        if (i == 0) {
            temp32 = temp32 + 1; /* DMA transmits one byte more than SPI at the first transmission */
        }
        if (i == trans_count - 1) {
            temp32 = temp32 - 1;
        }
        dma_transfer_size[i] = temp32;

        /* SPI CTRL */
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->trans_size = 1;
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(spi_transctrl + i));
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->TRANSCTRL);
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->ctrl = DMA_CHCTRL_CTRL_SRCWIDTH_SET(DMA_TRANSFER_WIDTH_WORD)
                                                                        | DMA_CHCTRL_CTRL_DSTWIDTH_SET(DMA_TRANSFER_WIDTH_WORD)
                                                                        | DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(DMA_NUM_TRANSFER_PER_BURST_1T)
                                                                        | DMA_CHCTRL_CTRL_SRCREQSEL_SET(dmamux_ch)
                                                                        | DMA_CHCTRL_CTRL_DSTREQSEL_SET(dmamux_ch);
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->linked_ptr =
                                    core_local_mem_to_sys_address(context->running_core, (uint32_t)(tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1));

        /* SPI CMD */
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->trans_size = 1;
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&dummy_cmd);
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->CMD);
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->ctrl = DMA_CHCTRL_CTRL_SRCWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                                                                        | DMA_CHCTRL_CTRL_DSTWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                                                                        | DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(DMA_NUM_TRANSFER_PER_BURST_1T)
                                                                        | DMA_CHCTRL_CTRL_SRCREQSEL_SET(dmamux_ch)
                                                                        | DMA_CHCTRL_CTRL_DSTREQSEL_SET(dmamux_ch);
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->linked_ptr =
                                core_local_mem_to_sys_address(context->running_core, (uint32_t)(tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2));

        /* SPI DATA */
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->trans_size = dma_transfer_size[i];
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->src_addr =
                                                                    core_local_mem_to_sys_address(context->running_core, (uint32_t)(tx_buff + tx_buff_index));
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->DATA);
        (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->ctrl = DMA_CHCTRL_CTRL_SRCWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                                                                        | DMA_CHCTRL_CTRL_DSTWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                                                                        | DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(DMA_NUM_TRANSFER_PER_BURST_1T)
                                                                        | DMA_CHCTRL_CTRL_DSTMODE_SET(DMA_HANDSHAKE_MODE_HANDSHAKE)
                                                                        | DMA_CHCTRL_CTRL_DSTADDRCTRL_SET(DMA_ADDRESS_CONTROL_FIXED)
                                                                        | DMA_CHCTRL_CTRL_SRCREQSEL_SET(dmamux_ch)
                                                                        | DMA_CHCTRL_CTRL_DSTREQSEL_SET(dmamux_ch);
        if (i == trans_count - 1) {
            (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->linked_ptr = 0;
        } else {
            (tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->linked_ptr =
                                core_local_mem_to_sys_address(context->running_core, (uint32_t)(tx_dma_descriptors + (i + 1) * SPI_DMA_DESC_COUNT_PER_TRANS));
        }

        tx_buff_index += temp32;
    }
}

void hpm_prepare_dma_rx_descriptors(spi_context_t *context, spi_control_config_t *config, uint32_t trans_count,
                                    uint32_t *spi_transctrl, dma_linked_descriptor_t *rx_dma_descriptors)
{
    SPI_Type *ptr = context->ptr;
    uint32_t dma_transfer_size[trans_count];
    uint32_t rx_size = context->rx_size;
    uint32_t per_trans_size = context->per_trans_max;
    uint32_t dmamux_ch = context->dma_context.rx_dmamux_ch;
    uint8_t *rx_buff = context->rx_buff;

    static uint8_t dummy_cmd = 0xff;

    uint32_t temp32;
    uint32_t rx_buff_index = 0;
    for (uint32_t i = 0; i < trans_count; i++) {
        if (rx_size > per_trans_size) {
            temp32 = per_trans_size;
            rx_size -= per_trans_size;
        } else {
            temp32 = rx_size;
        }

        *(spi_transctrl + i) = SPI_TRANSCTRL_TRANSMODE_SET(spi_trans_read_only) |
                                SPI_TRANSCTRL_DUALQUAD_SET(config->common_config.data_phase_fmt) |
                                SPI_TRANSCTRL_WRTRANCNT_SET(temp32 - 1) |
                                SPI_TRANSCTRL_RDTRANCNT_SET(temp32 - 1);
        dma_transfer_size[i] = temp32;

        /* SPI CTRL */
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->trans_size = 1;
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(spi_transctrl + i));
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->TRANSCTRL);
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->ctrl = DMA_CHCTRL_CTRL_SRCWIDTH_SET(DMA_TRANSFER_WIDTH_WORD)
                                                                    | DMA_CHCTRL_CTRL_DSTWIDTH_SET(DMA_TRANSFER_WIDTH_WORD)
                                                                    | DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(DMA_NUM_TRANSFER_PER_BURST_1T)
                                                                    | DMA_CHCTRL_CTRL_SRCREQSEL_SET(dmamux_ch)
                                                                    | DMA_CHCTRL_CTRL_DSTREQSEL_SET(dmamux_ch);
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS)->linked_ptr =
                                    core_local_mem_to_sys_address(context->running_core, (uint32_t)(rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1));

        /* SPI CMD */
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->trans_size = 1;
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&dummy_cmd);
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->CMD);
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->ctrl = DMA_CHCTRL_CTRL_SRCWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                                                                        | DMA_CHCTRL_CTRL_DSTWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                                                                        | DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(DMA_NUM_TRANSFER_PER_BURST_1T)
                                                                        | DMA_CHCTRL_CTRL_SRCREQSEL_SET(dmamux_ch)
                                                                        | DMA_CHCTRL_CTRL_DSTREQSEL_SET(dmamux_ch);
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1)->linked_ptr =
                                    core_local_mem_to_sys_address(context->running_core, (uint32_t)(rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2));

        /* SPI DATA */
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->trans_size = dma_transfer_size[i];
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->DATA);
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->dst_addr =
                                                                    core_local_mem_to_sys_address(context->running_core, (uint32_t)(rx_buff + rx_buff_index));
        (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->ctrl = DMA_CHCTRL_CTRL_SRCWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                                                                        | DMA_CHCTRL_CTRL_DSTWIDTH_SET(DMA_TRANSFER_WIDTH_BYTE)
                                                                        | DMA_CHCTRL_CTRL_SRCBURSTSIZE_SET(DMA_NUM_TRANSFER_PER_BURST_1T)
                                                                        | DMA_CHCTRL_CTRL_SRCMODE_SET(DMA_HANDSHAKE_MODE_HANDSHAKE)
                                                                        | DMA_CHCTRL_CTRL_SRCADDRCTRL_SET(DMA_ADDRESS_CONTROL_FIXED)
                                                                        | DMA_CHCTRL_CTRL_SRCREQSEL_SET(dmamux_ch)
                                                                        | DMA_CHCTRL_CTRL_DSTREQSEL_SET(dmamux_ch);
        if (i == trans_count - 1) {
            (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->linked_ptr = 0;
        } else {
            (rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2)->linked_ptr =
                                core_local_mem_to_sys_address(context->running_core, (uint32_t)(rx_dma_descriptors + (i + 1) * SPI_DMA_DESC_COUNT_PER_TRANS));
        }
        rx_buff_index += temp32;
    }
}

static uint32_t hpm_spi_get_trans_count(spi_context_t *context, spi_control_config_t *config)
{
    uint32_t total_trans_size, per_trans_size, trans_count;

    per_trans_size = context->per_trans_max;
    if (config->common_config.trans_mode == spi_trans_write_only || config->common_config.trans_mode == spi_trans_dummy_write) {
        total_trans_size = context->tx_size;
    } else if (config->common_config.trans_mode == spi_trans_read_only || config->common_config.trans_mode == spi_trans_dummy_read) {
        total_trans_size = context->rx_size;
    } else {
        /* write read together */
        assert(context->tx_size == context->rx_size);
        total_trans_size = context->tx_size;
    }
    trans_count = (total_trans_size + per_trans_size - 1) / per_trans_size;

    return trans_count;
}

static hpm_stat_t spi_setup_trans_with_dma_chain(spi_context_t *context, spi_control_config_t *config)
{
    hpm_stat_t stat = status_success;
    SPI_Type *spi_ptr = context->ptr;
    DMA_Type *dma_ptr = context->dma_context.dma_ptr;
    DMAMUX_Type *dmamux_ptr = context->dma_context.dmamux_ptr;
    dma_linked_descriptor_t *dma_linked_descriptor = context->dma_linked_descriptor;
    uint32_t *spi_transctrl = context->spi_transctrl;
    uint32_t dma_channel;
    uint32_t trans_count;
    dma_channel_config_t dma_ch_config = {0};

    trans_count = hpm_spi_get_trans_count(context, config);

    /* active spi cs pin */
    context->write_cs(context->cs_pin, SPI_CS_ACTIVE);

    stat = spi_setup_dma_transfer(spi_ptr,
                                config,
                                &context->cmd,
                                &context->addr,
                                MIN(context->tx_size, context->per_trans_max),
                                MIN(context->rx_size, context->per_trans_max));
    if (stat != status_success) {
        return stat;
    }

    if (config->common_config.trans_mode == spi_trans_write_only || config->common_config.trans_mode == spi_trans_dummy_write) {
        /* write only */
        hpm_spi_prepare_dma_tx_descriptors(context, config, trans_count, spi_transctrl, dma_linked_descriptor);
        dma_channel = context->dma_context.tx_dma_ch;
        dmamux_config(dmamux_ptr, context->dma_context.tx_dmamux_ch, context->dma_context.tx_req, true);
    } else if (config->common_config.trans_mode == spi_trans_read_only || config->common_config.trans_mode == spi_trans_dummy_read) {
        /* read only */
        hpm_prepare_dma_rx_descriptors(context, config, trans_count, spi_transctrl, dma_linked_descriptor);
        dma_channel = context->dma_context.rx_dma_ch;
        dmamux_config(dmamux_ptr, context->dma_context.rx_dmamux_ch, context->dma_context.rx_req, true);
    } else if (config->common_config.trans_mode == spi_trans_write_read_together) {
        /* write and read together */
        hpm_spi_prepare_dma_tx_descriptors(context, config, trans_count, spi_transctrl, dma_linked_descriptor);
        dma_channel = context->dma_context.tx_dma_ch;
        dmamux_config(dmamux_ptr, context->dma_context.tx_dmamux_ch, context->dma_context.tx_req, true);
        dmamux_config(dmamux_ptr, context->dma_context.rx_dmamux_ch, context->dma_context.rx_req, true);
        /* spi tx use chained dma descriptor, spi rx use unchained dma */
        stat = hpm_spi_rx_trigger_dma(dma_ptr,
                            context->dma_context.rx_dmamux_ch,
                            spi_ptr,
                            core_local_mem_to_sys_address(context->running_core, (uint32_t)context->rx_buff),
                            context->rx_size);
        if (stat != status_success) {
            return stat;
        }
    }

    /* use a dummy dma transfer to start SPI trans dma chain */
    static uint32_t dummy_data1 = 0xff, dummy_data2 = 0xff;
    dma_ch_config.src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&dummy_data1);
    dma_ch_config.dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&dummy_data2);
    dma_ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
    dma_ch_config.src_width = DMA_TRANSFER_WIDTH_WORD;
    dma_ch_config.dst_width = DMA_TRANSFER_WIDTH_WORD;
    dma_ch_config.size_in_byte = 4;
    dma_ch_config.linked_ptr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(dma_linked_descriptor + SPI_DMA_DESC_COUNT_PER_TRANS - 1));

    stat = dma_setup_channel(dma_ptr, dma_channel, &dma_ch_config);
    if (stat != status_success) {
        return stat;
    }

    return stat;
}

static hpm_stat_t spi_setup_trans_with_dma(spi_context_t *context, spi_control_config_t *config)
{
    hpm_stat_t stat = status_success;
    SPI_Type *spi_ptr = context->ptr;
    DMA_Type *dma_ptr = context->dma_context.dma_ptr;
    DMAMUX_Type *dmamux_ptr = context->dma_context.dmamux_ptr;
    uint32_t trans_mode = config->common_config.trans_mode;

    if (context->write_cs != NULL) {
        context->write_cs(context->cs_pin, SPI_CS_ACTIVE);
    }
    stat = spi_setup_dma_transfer(spi_ptr, config,
                                &context->cmd, &context->addr,
                                context->tx_size, context->rx_size);
    if (stat != status_success) {
        return stat;
    }

    if (trans_mode != spi_trans_write_only && trans_mode != spi_trans_dummy_write && trans_mode != spi_trans_no_data) {
        dmamux_config(dmamux_ptr, context->dma_context.rx_dmamux_ch, context->dma_context.rx_req, true);
        stat = hpm_spi_rx_trigger_dma(dma_ptr,
                                context->dma_context.rx_dmamux_ch,
                                spi_ptr,
                                core_local_mem_to_sys_address(context->running_core, (uint32_t)context->rx_buff),
                                context->rx_size);
        if (stat != status_success) {
            return stat;
        }
        /* cache invalidate for receive buff */
        if (l1c_dc_is_enabled()) {
            l1c_dc_invalidate((uint32_t)context->rx_buff, context->rx_size);
        }
    }
    if (trans_mode != spi_trans_read_only && trans_mode != spi_trans_dummy_read && trans_mode != spi_trans_no_data) {
        dmamux_config(dmamux_ptr, context->dma_context.tx_dmamux_ch, context->dma_context.tx_req, true);
        /* cache writeback for tx buff */
        if (l1c_dc_is_enabled()) {
            l1c_dc_writeback((uint32_t)context->tx_buff, context->tx_size);
        }

        stat = hpm_spi_tx_trigger_dma(dma_ptr,
                                context->dma_context.tx_dmamux_ch,
                                spi_ptr,
                                core_local_mem_to_sys_address(context->running_core, (uint32_t)context->tx_buff),
                                context->tx_size);
        if (stat != status_success) {
            return stat;
        }
    }

    return stat;
}

hpm_stat_t hpm_spi_setup_dma_transfer(spi_context_t *context, spi_control_config_t *config)
{
    assert(context != NULL || config != NULL);
    /* use dma */
    assert(&context->dma_context != NULL);
    /* spi per trans data size not zero */
    assert(context->per_trans_max);

    hpm_stat_t stat = status_success;
    uint32_t trans_mode = config->common_config.trans_mode;

    if ((context->rx_size > context->per_trans_max) || (context->tx_size > context->per_trans_max)) {
        /* multiple SPI transmissions with chained DMA */
        assert(trans_mode == spi_trans_read_only || trans_mode == spi_trans_dummy_read
                || trans_mode == spi_trans_write_only || trans_mode == spi_trans_dummy_write
                || trans_mode == spi_trans_write_read_together);
        /* master mode */
        assert((context->ptr->TRANSFMT & SPI_TRANSFMT_SLVMODE_MASK) != SPI_TRANSFMT_SLVMODE_MASK);
        /* GPIO should be used to replace SPI CS pin for SPI chained DMA transmissions */
        assert(context->write_cs != NULL);

        stat = spi_setup_trans_with_dma_chain(context, config);
    } else {
        /* one SPI transmissions with chained DMA */
        stat = spi_setup_trans_with_dma(context, config);
    }

    return stat;
}

/* Using GPIO as SPI CS pin */
/* When SPI trans completed, GPIO cs pin should be released manually */
hpm_stat_t hpm_spi_release_gpio_cs(spi_context_t *context)
{
    hpm_stat_t stat;
    SPI_Type *ptr = context->ptr;
    assert(context->write_cs != NULL);

    stat = spi_wait_for_idle_status(ptr);
    if (stat != status_success) {
        return stat;
    }

    context->write_cs(context->cs_pin, !SPI_CS_ACTIVE);
    return status_success;
}

