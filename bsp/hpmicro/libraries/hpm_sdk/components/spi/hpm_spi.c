/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_spi.h"

static hpm_stat_t hpm_spi_tx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr, uint32_t src, uint8_t data_width, uint32_t size)
{
    dma_handshake_config_t config;

    dma_default_handshake_config(dma_ptr, &config);
    config.ch_index = ch_num;
    config.dst = (uint32_t)&spi_ptr->DATA;
    config.dst_fixed = true;
    config.src = src;
    config.src_fixed = false;
    config.data_width = data_width;
    config.size_in_byte = size;

    return dma_setup_handshake(dma_ptr, &config, true);
}

static hpm_stat_t hpm_spi_rx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr, uint32_t dst, uint8_t data_width, uint32_t size)
{
    dma_handshake_config_t config;

    dma_default_handshake_config(dma_ptr, &config);
    config.ch_index = ch_num;
    config.dst = dst;
    config.dst_fixed = false;
    config.src = (uint32_t)&spi_ptr->DATA;
    config.src_fixed = true;
    config.data_width = data_width;
    config.size_in_byte = size;

    return dma_setup_handshake(dma_ptr, &config, true);
}


void hpm_spi_prepare_dma_tx_descriptors(spi_context_t *context, spi_control_config_t *config, uint32_t trans_count,
                                    uint32_t *spi_transctrl, dma_linked_descriptor_t *tx_dma_descriptors)
{
    SPI_Type *ptr = context->ptr;
    uint32_t dma_transfer_size[trans_count];
    uint32_t tx_count = context->tx_count;
    uint32_t per_trans_size = context->per_trans_max;
    uint32_t dma_ch = context->dma_context.tx_dma_ch;
    uint8_t *tx_buff = context->tx_buff;
    dma_channel_config_t dma_ch_config;

    static uint8_t dummy_cmd = 0xff;

    uint32_t temp32;
    uint32_t tx_buff_index = 0;

    dma_default_channel_config(context->dma_context.dma_ptr, &dma_ch_config);
    for (uint32_t i = 0; i < trans_count; i++) {
        if (tx_count > per_trans_size) {
            temp32 = per_trans_size;
            tx_count -= per_trans_size;
        } else {
            temp32 = tx_count;
        }

        *(spi_transctrl + i) = SPI_TRANSCTRL_TRANSMODE_SET(config->common_config.trans_mode == spi_trans_write_read_together ?
                                                           spi_trans_write_read_together : spi_trans_write_only)
                                | SPI_TRANSCTRL_DUALQUAD_SET(config->common_config.data_phase_fmt)
                                | SPI_TRANSCTRL_WRTRANCNT_SET(temp32 - 1)
                                | SPI_TRANSCTRL_RDTRANCNT_SET(temp32 - 1);

        if (i == 0) {
            /* Set the count of data transferred by dma to be one more than that of spi */
            /* when dma transfer finished, there are data in SPI fifo, dma should not execute the dma descriptor which changes SPI CTRL register */
            temp32 = temp32 + 1;
        }
        if (i == trans_count - 1) {
            temp32 = temp32 - 1;
        }
        dma_transfer_size[i] = temp32;

        /* SPI CTRL */
        dma_ch_config.size_in_byte = 4;
        dma_ch_config.src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(spi_transctrl + i));
        dma_ch_config.dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->TRANSCTRL);
        dma_ch_config.src_width = DMA_TRANSFER_WIDTH_WORD;
        dma_ch_config.dst_width = DMA_TRANSFER_WIDTH_WORD;
        dma_ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
        dma_ch_config.src_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.dst_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        dma_ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        dma_ch_config.linked_ptr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1));
        dma_config_linked_descriptor(context->dma_context.dma_ptr, tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS, dma_ch, &dma_ch_config);

        /* SPI CMD */
        dma_ch_config.size_in_byte = 1;
        dma_ch_config.src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&dummy_cmd);
        dma_ch_config.dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->CMD);
        dma_ch_config.src_width = DMA_TRANSFER_WIDTH_BYTE;
        dma_ch_config.dst_width = DMA_TRANSFER_WIDTH_BYTE;
        dma_ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
        dma_ch_config.src_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.dst_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        dma_ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        dma_ch_config.linked_ptr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2));
        dma_config_linked_descriptor(context->dma_context.dma_ptr, tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1, dma_ch, &dma_ch_config);

        /* SPI DATA */
        dma_ch_config.size_in_byte = dma_transfer_size[i] << context->dma_context.data_width;
        dma_ch_config.src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(tx_buff + tx_buff_index));
        dma_ch_config.dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->DATA);
        dma_ch_config.src_width = context->dma_context.data_width;
        dma_ch_config.dst_width = context->dma_context.data_width;
        dma_ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
        dma_ch_config.src_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.dst_mode = DMA_HANDSHAKE_MODE_HANDSHAKE;
        dma_ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
        dma_ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        if (i == trans_count - 1) {
            dma_ch_config.linked_ptr = 0;
        } else {
            dma_ch_config.linked_ptr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(tx_dma_descriptors + (i + 1) * SPI_DMA_DESC_COUNT_PER_TRANS));
        }
        dma_config_linked_descriptor(context->dma_context.dma_ptr, tx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2, dma_ch, &dma_ch_config);

        tx_buff_index += temp32 * context->data_len_in_byte;
    }
}

void hpm_prepare_dma_rx_descriptors(spi_context_t *context, spi_control_config_t *config, uint32_t trans_count,
                                    uint32_t *spi_transctrl, dma_linked_descriptor_t *rx_dma_descriptors)
{
    SPI_Type *ptr = context->ptr;
    uint32_t dma_transfer_size[trans_count];
    uint32_t rx_count = context->rx_count;
    uint32_t per_trans_size = context->per_trans_max;
    uint32_t dma_ch = context->dma_context.rx_dma_ch;
    uint8_t *rx_buff = context->rx_buff;
    dma_channel_config_t dma_ch_config;

    static uint8_t dummy_cmd = 0xff;

    uint32_t temp32;
    uint32_t rx_buff_index = 0;

    dma_default_channel_config(context->dma_context.dma_ptr, &dma_ch_config);
    for (uint32_t i = 0; i < trans_count; i++) {
        if (rx_count > per_trans_size) {
            temp32 = per_trans_size;
            rx_count -= per_trans_size;
        } else {
            temp32 = rx_count;
        }

        *(spi_transctrl + i) = SPI_TRANSCTRL_TRANSMODE_SET(spi_trans_read_only) |
                                SPI_TRANSCTRL_DUALQUAD_SET(config->common_config.data_phase_fmt) |
                                SPI_TRANSCTRL_WRTRANCNT_SET(temp32 - 1) |
                                SPI_TRANSCTRL_RDTRANCNT_SET(temp32 - 1);
        dma_transfer_size[i] = temp32;

        /* SPI CTRL */
        dma_ch_config.size_in_byte = 4;
        dma_ch_config.src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(spi_transctrl + i));
        dma_ch_config.dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->TRANSCTRL);
        dma_ch_config.src_width = DMA_TRANSFER_WIDTH_WORD;
        dma_ch_config.dst_width = DMA_TRANSFER_WIDTH_WORD;
        dma_ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
        dma_ch_config.src_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.dst_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        dma_ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        dma_ch_config.linked_ptr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1));
        dma_config_linked_descriptor(context->dma_context.dma_ptr, rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS, dma_ch, &dma_ch_config);

        /* SPI CMD */
        dma_ch_config.size_in_byte = 1;
        dma_ch_config.src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&dummy_cmd);
        dma_ch_config.dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->CMD);
        dma_ch_config.src_width = DMA_TRANSFER_WIDTH_BYTE;
        dma_ch_config.dst_width = DMA_TRANSFER_WIDTH_BYTE;
        dma_ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
        dma_ch_config.src_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.dst_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        dma_ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        dma_ch_config.linked_ptr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2));
        dma_config_linked_descriptor(context->dma_context.dma_ptr, rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 1, dma_ch, &dma_ch_config);

        /* SPI DATA */
        dma_ch_config.size_in_byte = dma_transfer_size[i] << context->dma_context.data_width;
        dma_ch_config.src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&ptr->DATA);
        dma_ch_config.dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(rx_buff + rx_buff_index));
        dma_ch_config.src_width = context->dma_context.data_width;
        dma_ch_config.dst_width = context->dma_context.data_width;
        dma_ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
        dma_ch_config.src_mode = DMA_HANDSHAKE_MODE_HANDSHAKE;
        dma_ch_config.dst_mode = DMA_HANDSHAKE_MODE_NORMAL;
        dma_ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        dma_ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
        if (i == trans_count - 1) {
            dma_ch_config.linked_ptr = 0;
        } else {
            dma_ch_config.linked_ptr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(rx_dma_descriptors + (i + 1) * SPI_DMA_DESC_COUNT_PER_TRANS));
        }
        dma_config_linked_descriptor(context->dma_context.dma_ptr, rx_dma_descriptors + i * SPI_DMA_DESC_COUNT_PER_TRANS + 2, dma_ch, &dma_ch_config);

        rx_buff_index += temp32 * context->data_len_in_byte;
    }
}

static uint32_t hpm_spi_get_trans_count(spi_context_t *context, spi_control_config_t *config)
{
    uint32_t total_trans_count, per_trans_count, trans_count;

    per_trans_count = context->per_trans_max;
    if (config->common_config.trans_mode == spi_trans_write_only || config->common_config.trans_mode == spi_trans_dummy_write) {
        total_trans_count = context->tx_count;
    } else if (config->common_config.trans_mode == spi_trans_read_only || config->common_config.trans_mode == spi_trans_dummy_read) {
        total_trans_count = context->rx_count;
    } else {
        /* write read together */
        assert(context->tx_count == context->rx_count);
        total_trans_count = context->tx_count;
    }
    trans_count = (total_trans_count + per_trans_count - 1) / per_trans_count;

    return trans_count;
}

/**
 * spi with dma chain workflow
 *
 * 1. call spi_setup_dma_transfer to config SPI for first transmission
 * 2. execute data transmission phase in dma chain descriptor
 * 3. execute setting SPI CTRL register phase in dma chain descriptor
 * 4. execute writing SPI CMD register phase in dma chain descriptor
 * 5. Repeat steps 2-4 until finish the transmission
 */
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

    /* config SPI for first dma transmission */
    stat = spi_setup_dma_transfer(spi_ptr,
                                config,
                                &context->cmd,
                                &context->addr,
                                MIN(context->tx_count, context->per_trans_max),
                                MIN(context->rx_count, context->per_trans_max));
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
                            context->dma_context.rx_dma_ch,
                            spi_ptr,
                            core_local_mem_to_sys_address(context->running_core, (uint32_t)context->rx_buff),
                            context->dma_context.data_width,
                            context->rx_size);
        if (stat != status_success) {
            return stat;
        }
    }

    /* use a dummy dma transfer to start SPI trans dma chain */
    static uint32_t dummy_data1 = 0xff, dummy_data2 = 0xff;

    dma_default_channel_config(context->dma_context.dma_ptr, &dma_ch_config);
    dma_ch_config.src_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&dummy_data1);
    dma_ch_config.dst_addr = core_local_mem_to_sys_address(context->running_core, (uint32_t)&dummy_data2);
    dma_ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
    dma_ch_config.src_width = DMA_TRANSFER_WIDTH_WORD;
    dma_ch_config.dst_width = DMA_TRANSFER_WIDTH_WORD;
    dma_ch_config.size_in_byte = 4;
    /* start data transmission phase in dma chain */
    dma_ch_config.linked_ptr = core_local_mem_to_sys_address(context->running_core, (uint32_t)(dma_linked_descriptor + SPI_DMA_DESC_COUNT_PER_TRANS - 1));

    stat = dma_setup_channel(dma_ptr, dma_channel, &dma_ch_config, true);
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
                                context->tx_count, context->rx_count);
    if (stat != status_success) {
        return stat;
    }

    if (trans_mode != spi_trans_write_only && trans_mode != spi_trans_dummy_write && trans_mode != spi_trans_no_data) {
        dmamux_config(dmamux_ptr, context->dma_context.rx_dmamux_ch, context->dma_context.rx_req, true);
        stat = hpm_spi_rx_trigger_dma(dma_ptr,
                                context->dma_context.rx_dma_ch,
                                spi_ptr,
                                core_local_mem_to_sys_address(context->running_core, (uint32_t)context->rx_buff),
                                context->dma_context.data_width,
                                context->rx_size);
        if (stat != status_success) {
            return stat;
        }
    }
    if (trans_mode != spi_trans_read_only && trans_mode != spi_trans_dummy_read && trans_mode != spi_trans_no_data) {
        dmamux_config(dmamux_ptr, context->dma_context.tx_dmamux_ch, context->dma_context.tx_req, true);
        stat = hpm_spi_tx_trigger_dma(dma_ptr,
                                context->dma_context.tx_dma_ch,
                                spi_ptr,
                                core_local_mem_to_sys_address(context->running_core, (uint32_t)context->tx_buff),
                                context->dma_context.data_width,
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

    if (l1c_dc_is_enabled()) {
        /* cache writeback for tx buff */
        if (context->tx_buff != NULL && context->tx_size != 0) {
            uint32_t aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)context->tx_buff);
            uint32_t aligned_end = HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)context->tx_buff + context->tx_size);
            uint32_t aligned_size = aligned_end - aligned_start;
            l1c_dc_writeback(aligned_start, aligned_size);
        }
        /* cache invalidate for receive buff */
        if (context->rx_buff != NULL && context->rx_size != 0) {
            uint32_t aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)context->rx_buff);
            uint32_t aligned_end = HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)context->rx_buff + context->rx_size);
            uint32_t aligned_size = aligned_end - aligned_start;
            l1c_dc_invalidate(aligned_start, aligned_size);
        }
    }

    if ((context->rx_count > context->per_trans_max) || (context->tx_count > context->per_trans_max)) {
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

