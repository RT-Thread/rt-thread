/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifdef HPMSOC_HAS_HPMSDK_DMAV2
#include "hpm_dmav2_drv.h"
#else
#include "hpm_dma_drv.h"
#endif
#include "hpm_dmamux_drv.h"
#include "hpm_spi_drv.h"
#include "hpm_l1c_drv.h"
#include "board.h"
#include "hpm_serial_nor_host.h"

static hpm_stat_t spi_nor_rx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr,
                                        uint32_t dst, uint8_t data_width, uint32_t size, uint8_t burst_size);

static hpm_stat_t spi_nor_rx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr, uint32_t dst,
                                            uint8_t data_width, uint32_t size, uint8_t burst_size);

static void hpm_config_cmd_addr_format(void *ops, hpm_serial_nor_transfer_seq_t *cmd_seq, spi_control_config_t *control_config);

static hpm_stat_t hpm_spi_transfer_via_dma(hpm_serial_nor_host_t *host, spi_control_config_t *control_config,
                                            uint8_t cmd, uint32_t addr,
                                            uint8_t *buf, uint32_t len, bool is_read);

static hpm_stat_t transfer(void *host, hpm_serial_nor_transfer_seq_t *command_seq);

static hpm_stat_t init(void *ops);

static hpm_stat_t write(void *ops, hpm_serial_nor_transfer_seq_t *cmd_seq);

static hpm_stat_t read(void *ops, hpm_serial_nor_transfer_seq_t *cmd_seq);

ATTR_WEAK hpm_stat_t serial_nor_host_ops_use_spi(hpm_serial_nor_t *dev)
{
    if (dev == NULL) {
        return status_invalid_argument;
    }
    dev->host.host_ops.init  = init;
    dev->host.host_ops.transfer = transfer;
    dev->host.host_ops.set_cs = dev->host.host_param.param.set_cs;
    dev->host.host_ops.set_frequency = dev->host.host_param.param.set_frequency;
    return status_success;
}

static hpm_stat_t transfer(void *host, hpm_serial_nor_transfer_seq_t *command_seq)
{
    hpm_stat_t stat = status_success;
    if (command_seq->data_phase.direction == read_direction) {
        stat = read(host, command_seq);
    } else {
        stat = write(host, command_seq);
    }
    return stat;
}

static hpm_stat_t spi_nor_tx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr,
                                            uint32_t src, uint8_t data_width, uint32_t size, uint8_t burst_size)
{
    hpm_stat_t stat;
    dma_channel_config_t config;
    if (ch_num >= DMA_SOC_CHANNEL_NUM) {
        return status_invalid_argument;
    }
    dma_default_channel_config(dma_ptr, &config);
    config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
    config.dst_mode      = DMA_HANDSHAKE_MODE_HANDSHAKE;
    config.src_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
    config.src_mode      = DMA_HANDSHAKE_MODE_NORMAL;
    config.src_width     = data_width;
    config.dst_width     = data_width;
    config.src_addr      = src;
    config.dst_addr      = (uint32_t)&spi_ptr->DATA;
    config.size_in_byte  = size;
    config.src_burst_size = burst_size;
    stat = dma_setup_channel(dma_ptr, ch_num, &config, true);
    if (stat != status_success) {
        return stat;
    }
    return stat;
}

static hpm_stat_t spi_nor_rx_trigger_dma(DMA_Type *dma_ptr, uint8_t ch_num, SPI_Type *spi_ptr, uint32_t dst,
                                            uint8_t data_width, uint32_t size, uint8_t burst_size)
{
    hpm_stat_t stat;
    dma_channel_config_t config;
    if (ch_num >= DMA_SOC_CHANNEL_NUM) {
        return status_invalid_argument;
    }
    dma_default_channel_config(dma_ptr, &config);
    config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
    config.dst_mode      = DMA_HANDSHAKE_MODE_HANDSHAKE;
    config.src_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
    config.src_mode      = DMA_HANDSHAKE_MODE_NORMAL;
    config.src_width     = data_width;
    config.dst_width     = data_width;
    config.src_addr      = (uint32_t)&spi_ptr->DATA;
    config.dst_addr      = dst;
    config.size_in_byte  = size;
    config.src_burst_size = burst_size;
    stat = dma_setup_channel(dma_ptr, ch_num, &config, true);
    if (stat != status_success) {
        return stat;
    }
    return stat;
}

static void hpm_config_cmd_addr_format(void *ops, hpm_serial_nor_transfer_seq_t *cmd_seq, spi_control_config_t *control_config)
{
    spi_trans_mode_t _trans_mode;
    hpm_serial_nor_host_t *host = (hpm_serial_nor_host_t *)ops;
    control_config->master_config.cmd_enable  = true;

    /* judge the valid of addr */
    if (cmd_seq->addr_phase.enable == true) {
        control_config->master_config.addr_enable = true;
        if (cmd_seq->addr_phase.addr_io_mode == single_io_mode) {
            control_config->master_config.addr_phase_fmt = spi_address_phase_format_single_io_mode;
        } else {
            control_config->master_config.addr_phase_fmt = spi_address_phase_format_dualquad_io_mode;
        }
        if (cmd_seq->addr_phase.addr_bit == flash_addrlen_24bit) {
            spi_set_address_len((SPI_Type *)host->host_param.param.host_base, addrlen_24bit);
        } else {
            spi_set_address_len((SPI_Type *)host->host_param.param.host_base, addrlen_32bit);
        }
    } else {
        control_config->master_config.addr_enable = false;
    }

    /* judge the valid of buf */
    if ((cmd_seq->data_phase.buf != NULL) || (cmd_seq->data_phase.len != 0)) {
        if (cmd_seq->dummy_phase.dummy_count == 0) {
            _trans_mode = (cmd_seq->data_phase.direction == read_direction) ? spi_trans_read_only : spi_trans_write_only;
        } else {
            control_config->common_config.dummy_cnt = cmd_seq->dummy_phase.dummy_count - 1;
            _trans_mode = (cmd_seq->data_phase.direction == read_direction) ? spi_trans_dummy_read : spi_trans_dummy_write;
        }
        control_config->common_config.trans_mode = _trans_mode;

        if ((cmd_seq->data_phase.data_io_mode == single_io_mode)
                || (host->host_param.flags & SERIAL_NOR_HOST_SUPPORT_SINGLE_IO_MODE)) {
            control_config->common_config.data_phase_fmt = spi_single_io_mode;
        } else if (cmd_seq->data_phase.data_io_mode == dual_io_mode) {
            control_config->common_config.data_phase_fmt = spi_dual_io_mode;
        } else {
            control_config->common_config.data_phase_fmt = spi_quad_io_mode;
        }
    } else {
        control_config->common_config.trans_mode = spi_trans_no_data;
    }
}

static hpm_stat_t init(void *ops)
{
    spi_format_config_t format_config = {0};
    hpm_serial_nor_host_t *host = (hpm_serial_nor_host_t *)ops;
    if ((host == NULL) || (host->host_param.param.host_base == NULL)) {
        return status_invalid_argument;
    }
    spi_master_get_default_format_config(&format_config);
    format_config.common_config.data_len_in_bits = 8;
    format_config.common_config.mode = spi_master_mode;
    format_config.common_config.cpol = spi_sclk_low_idle;
    format_config.common_config.cpha = spi_sclk_sampling_odd_clk_edges;
    format_config.common_config.data_merge = false;
    spi_format_init(host->host_param.param.host_base, &format_config);
    if (host->host_param.flags & SERIAL_NOR_HOST_SUPPORT_DMA) {
        if ((host->host_param.param.dma_control.dma_base == NULL) || (host->host_param.param.dma_control.dmamux_base == NULL)) {
            return status_invalid_argument;
        }
        dmamux_config(host->host_param.param.dma_control.dmamux_base,
                        DMA_SOC_CHN_TO_DMAMUX_CHN(host->host_param.param.dma_control.dma_base,
                        host->host_param.param.dma_control.rx_dma_ch),
                        host->host_param.param.dma_control.rx_dma_req, true);

        dmamux_config(host->host_param.param.dma_control.dmamux_base,
                        DMA_SOC_CHN_TO_DMAMUX_CHN(host->host_param.param.dma_control.dma_base,
                        host->host_param.param.dma_control.tx_dma_ch),
                        host->host_param.param.dma_control.tx_dma_req, true);
    }
    return status_success;
}

static hpm_stat_t hpm_spi_transfer_via_dma(hpm_serial_nor_host_t *host, spi_control_config_t *control_config,
                                            uint8_t cmd, uint32_t addr,
                                            uint8_t *buf, uint32_t len, bool is_read)
{
    hpm_stat_t stat;
    uint32_t data_width = 0;
    uint8_t burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
    uint32_t timeout_count = 0;
    uint16_t dma_send_size;
    if (is_read) {
    /*The supplement of the byte less than the integer multiple of four bytes is an integer multiple of four bytes to DMA*/
        data_width = DMA_TRANSFER_WIDTH_WORD;
        if ((len % 4) == 0) {
            dma_send_size = len;
        } else {
            dma_send_size = ((len >> 2) + 1) << 2;
        }
        stat = spi_setup_dma_transfer((SPI_Type *)host->host_param.param.host_base, control_config, &cmd, &addr, 0, len);
        stat = spi_nor_rx_trigger_dma((DMA_Type *)host->host_param.param.dma_control.dma_base,
                                host->host_param.param.dma_control.rx_dma_ch,
                                (SPI_Type *)host->host_param.param.host_base,
                                core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)buf),
                                data_width,
                                dma_send_size, burst_size);
        while (spi_is_active((SPI_Type *)host->host_param.param.host_base)) {
            timeout_count++;
            if (timeout_count >= 0xFFFFFF) {
                stat = status_timeout;
                break;
            }
        }
        timeout_count = 0;
        if ((dma_check_transfer_status(
                    (DMA_Type *)host->host_param.param.dma_control.dma_base,
                    host->host_param.param.dma_control.rx_dma_ch) &&
                DMA_CHANNEL_STATUS_TC) == 0) {
            dma_disable_channel((DMA_Type *)host->host_param.param.dma_control.dma_base, host->host_param.param.dma_control.rx_dma_ch);
            dma_reset((DMA_Type *)host->host_param.param.dma_control.dma_base);
        }
    } else {
        if ((len % 4) == 0) {
            spi_enable_data_merge((SPI_Type *)host->host_param.param.host_base);
            data_width = DMA_TRANSFER_WIDTH_WORD;
        } else {
            data_width = DMA_TRANSFER_WIDTH_BYTE;
        }
        spi_set_tx_fifo_threshold((SPI_Type *)host->host_param.param.host_base, 3);
        burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;
        stat = spi_setup_dma_transfer((SPI_Type *)host->host_param.param.host_base, control_config, &cmd, &addr, len, 0);

        stat = spi_nor_tx_trigger_dma((DMA_Type *)host->host_param.param.dma_control.dma_base,
                                        host->host_param.param.dma_control.tx_dma_ch,
                                       (SPI_Type *)host->host_param.param.host_base,
                                        core_local_mem_to_sys_address(BOARD_RUNNING_CORE, (uint32_t)buf),
                                        data_width, len, burst_size);

        while (spi_is_active((SPI_Type *)host->host_param.param.host_base)) {
            timeout_count++;
            if (timeout_count >= 0xFFFFFF) {
                stat = status_timeout;
                break;
            }
        }
        timeout_count = 0;
        spi_disable_data_merge((SPI_Type *)host->host_param.param.host_base);
    }
    return stat;
}
static hpm_stat_t write(void *ops, hpm_serial_nor_transfer_seq_t *cmd_seq)
{
    hpm_stat_t stat = status_success;
    spi_control_config_t control_config = {0};
    hpm_serial_nor_host_t *host = (hpm_serial_nor_host_t *)ops;
    uint32_t aligned_start;
    uint32_t aligned_end;
    uint32_t aligned_size;
    if ((cmd_seq->data_phase.len > host->host_param.param.transfer_max_size) || (host == NULL)
        || (host->host_param.param.host_base == NULL)) {
        return status_invalid_argument;
    }

    if (!(host->host_param.flags & SERIAL_NOR_HOST_CS_CONTROL_AUTO)) {
        if (host->host_param.param.set_cs == NULL) {
            return status_fail;
        }
        host->host_param.param.set_cs(host->host_param.param.pin_or_cs_index, false);
    }

    spi_master_get_default_control_config(&control_config);
    hpm_config_cmd_addr_format(ops, cmd_seq, &control_config);

    if ((host->host_param.flags & SERIAL_NOR_HOST_SUPPORT_DMA) && (cmd_seq->use_dma == 1)) {
        control_config.common_config.tx_dma_enable = true;
        control_config.common_config.rx_dma_enable = false;
        if (l1c_dc_is_enabled()) {
            /* cache writeback for sent buff */
            aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)cmd_seq->data_phase.buf);
            aligned_end = HPM_L1C_CACHELINE_ALIGN_UP((uint32_t)cmd_seq->data_phase.buf + cmd_seq->data_phase.len);
            aligned_size = aligned_end - aligned_start;
            l1c_dc_writeback(aligned_start, aligned_size);
        }
        stat = hpm_spi_transfer_via_dma(host, &control_config, cmd_seq->cmd_phase.cmd, cmd_seq->addr_phase.addr,
                                         (uint8_t *)cmd_seq->data_phase.buf, cmd_seq->data_phase.len, false);
    } else {
        stat = spi_transfer((SPI_Type *)host->host_param.param.host_base, &control_config,
                        &cmd_seq->cmd_phase.cmd, &cmd_seq->addr_phase.addr,
                        cmd_seq->data_phase.buf, cmd_seq->data_phase.len, NULL, 0);
    }
    if (!(host->host_param.flags & SERIAL_NOR_HOST_CS_CONTROL_AUTO)) {
        host->host_param.param.set_cs(host->host_param.param.pin_or_cs_index, true);
    }
    return stat;
}

static hpm_stat_t read(void *ops, hpm_serial_nor_transfer_seq_t *cmd_seq)
{
    hpm_stat_t stat = status_success;
    uint32_t aligned_start;
    uint32_t aligned_end;
    uint32_t aligned_size;
    spi_control_config_t control_config = {0};
    hpm_serial_nor_host_t *host = (hpm_serial_nor_host_t *)ops;
    uint32_t read_size = 0;
    uint32_t read_start = cmd_seq->addr_phase.addr;
    uint8_t *dst_8 = (uint8_t *) cmd_seq->data_phase.buf;
    uint32_t remaining_len = cmd_seq->data_phase.len;

    if ((host == NULL) || (host->host_param.param.host_base == NULL)) {
        return status_invalid_argument;
    }
    if (!(host->host_param.flags & SERIAL_NOR_HOST_CS_CONTROL_AUTO)) {
        if (host->host_param.param.set_cs == NULL) {
            return status_fail;
        }
    }

    spi_master_get_default_control_config(&control_config);
    hpm_config_cmd_addr_format(ops, cmd_seq, &control_config);

    if ((host->host_param.flags & SERIAL_NOR_HOST_SUPPORT_DMA) && (cmd_seq->use_dma == 1)) {
        if (host->host_param.param.dma_control.dma_base == NULL) {
            return status_fail;
        }
        if (((uint32_t)dst_8 % HPM_L1C_CACHELINE_SIZE) != 0) {
            return status_invalid_argument;
        }
        control_config.common_config.tx_dma_enable = false;
        control_config.common_config.rx_dma_enable = true;
    }
    while (remaining_len > 0U) {
        if (!(host->host_param.flags & SERIAL_NOR_HOST_CS_CONTROL_AUTO)) {
            host->host_param.param.set_cs(host->host_param.param.pin_or_cs_index, false);
        }
        read_size = MIN(remaining_len, host->host_param.param.transfer_max_size);
        if ((host->host_param.flags & SERIAL_NOR_HOST_SUPPORT_DMA) && (cmd_seq->use_dma == 1)) {
            spi_enable_data_merge((SPI_Type *)host->host_param.param.host_base);
            stat = hpm_spi_transfer_via_dma(host, &control_config, cmd_seq->cmd_phase.cmd, read_start, dst_8, read_size, true);
        } else {
            stat = spi_transfer((SPI_Type *)host->host_param.param.host_base, &control_config, &cmd_seq->cmd_phase.cmd,
                                    &read_start, NULL, 0, dst_8, read_size);
        }
        HPM_BREAK_IF(stat != status_success);
        if (l1c_dc_is_enabled()) {
            /* cache invalidate for receive buff */
            aligned_start = HPM_L1C_CACHELINE_ALIGN_DOWN((uint32_t)dst_8);
            aligned_end = HPM_L1C_CACHELINE_ALIGN_UP(read_size);
            aligned_size = aligned_end - aligned_start;
            l1c_dc_invalidate(aligned_start, aligned_size);
        }
        read_start += read_size;
        remaining_len -= read_size;
        dst_8 += read_size;
        if (!(host->host_param.flags & SERIAL_NOR_HOST_CS_CONTROL_AUTO)) {
            host->host_param.param.set_cs(host->host_param.param.pin_or_cs_index, true);
        }
    }
    spi_disable_data_merge((SPI_Type *)host->host_param.param.host_base);
    return stat;
}
