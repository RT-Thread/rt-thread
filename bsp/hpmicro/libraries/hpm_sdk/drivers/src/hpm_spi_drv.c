/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_common.h"
#include "hpm_spi_drv.h"

#ifndef HPM_SPI_DRV_DEFAULT_RETRY_COUNT
/* the waiting time of timeout status is related to retry count and CPU frequency */
#define HPM_SPI_DRV_DEFAULT_RETRY_COUNT (5000U)
#endif

typedef enum {
    spi_data_length_8_bits = 7,
    spi_data_length_16_bits = 15,
    spi_data_length_31_bits = 30
} spi_data_length_in_bits_t;

hpm_stat_t spi_wait_for_idle_status(SPI_Type *ptr)
{
    uint32_t status;
    uint32_t retry = 0;

    do {
        status = ptr->STATUS;
        if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    } while(status & SPI_STATUS_SPIACTIVE_MASK);

    if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    return status_success;
}

hpm_stat_t spi_wait_for_busy_status(SPI_Type *ptr)
{
    uint32_t status;
    uint32_t retry = 0;

    do {
        status = ptr->STATUS;
        if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    } while(!(status & SPI_STATUS_SPIACTIVE_MASK));

    if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    return status_success;
}

static hpm_stat_t spi_write_command(SPI_Type *ptr, spi_mode_selection_t mode, spi_control_config_t *config, uint8_t *cmd)
{
    if (mode == spi_master_mode) {
        if (config->master_config.cmd_enable == true) {
            if (cmd == NULL) {
                return status_invalid_argument;
            }
            ptr->CMD = SPI_CMD_CMD_SET(*cmd);
        }
        else {
            ptr->CMD = SPI_CMD_CMD_SET(0xff); /* Write a dummy byte */
        }
    }

    return status_success;
}

static void spi_read_command(SPI_Type *ptr, spi_mode_selection_t mode, uint8_t *cmd)
{
    if (mode == spi_slave_mode) {
      *cmd = (uint8_t)(ptr->CMD & SPI_CMD_CMD_MASK) >> SPI_CMD_CMD_SHIFT;
    }
}

static hpm_stat_t spi_write_address(SPI_Type *ptr, spi_mode_selection_t mode, spi_control_config_t *config, uint32_t *addr)
{
    if (mode == spi_master_mode) {
        if (config->master_config.addr_enable == true) {
            if (addr == NULL) {
                return status_invalid_argument;
            }
            ptr->ADDR = SPI_ADDR_ADDR_SET(*addr);
        }
    }

    return status_success;
}

static hpm_stat_t spi_write_data(SPI_Type *ptr, uint8_t datalen, uint8_t *buff, uint32_t size)
{
    uint32_t status;
    uint32_t transferred = 0;
    uint32_t retry = 0;

    /* check parameter validity */
    if (buff == NULL || size == 0) {
        return status_invalid_argument;
    }

    /* data transfer */
    while (transferred < size)
    {
        status = ptr->STATUS;
        if (!(status & SPI_STATUS_TXFULL_MASK)) {
            /* write data into the txfifo */
            if (datalen <= spi_data_length_8_bits) {
                ptr->DATA = *(uint8_t *)buff & ((1UL << (datalen + 1)) - 1);
                buff += sizeof(uint8_t);
            }
            else if (datalen <= spi_data_length_16_bits) {
                ptr->DATA = *(uint16_t *)buff & ((1UL << (datalen + 1)) - 1);
                buff += sizeof(uint16_t);
            }
            else if (datalen <= spi_data_length_31_bits) {
                ptr->DATA = *(uint32_t *)buff & ((1UL << (datalen + 1)) - 1);
                buff += sizeof(uint32_t);
            }
            else {
                ptr->DATA = *(uint32_t *)buff & 0xffffffff;
                buff += sizeof(uint32_t);
            }
            /* transfer count increment */
            transferred++;
            retry = 0;
        } else {
            if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }

    if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
        /* dummy state may triggers timeout if dummy count, retry count, spi rate and cpu frequency are inappropriate */
        return status_timeout;
    }

    return status_success;
}

static hpm_stat_t spi_read_data(SPI_Type *ptr, uint8_t datalen, uint8_t *buff, uint32_t size)
{
    uint32_t status;
    uint32_t transferred = 0;
    uint32_t retry = 0;

    /* check parameter validity */
    if (buff == NULL || size == 0) {
        return status_invalid_argument;
    }

    /* data transfer */
    while (transferred < size)
    {
        status = ptr->STATUS;
        if (!(status & SPI_STATUS_RXEMPTY_MASK)) {
            /* read data from the txfifo */
            if (datalen <= spi_data_length_8_bits) {
                *(uint8_t *)buff = (uint8_t)(ptr->DATA & ((1UL << (datalen + 1)) - 1));
                buff += sizeof(uint8_t);
            }
            else if (datalen <= spi_data_length_16_bits) {
                *(uint16_t *)buff = (uint16_t)(ptr->DATA & ((1UL << (datalen + 1)) - 1));
                buff += sizeof(uint16_t);
            }
            else if (datalen <= spi_data_length_31_bits) {
                *(uint32_t *)buff = (uint32_t)(ptr->DATA & ((1UL << (datalen + 1)) - 1));
                buff += sizeof(uint32_t);
            }
            else {
                *(uint32_t *)buff = (uint32_t)(ptr->DATA & 0xffffffff);
                buff += sizeof(uint32_t);
            }
            /* transfer count increment */
            transferred++;
            retry = 0;
        } else {
            if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }

    if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
        /* dummy state may triggers timeout if dummy count, retry count, spi rate and cpu frequency are inappropriate */
        return status_timeout;
    }

    return status_success;
}

static hpm_stat_t spi_write_read_data(SPI_Type *ptr, uint8_t datalen, uint8_t *wbuff, uint32_t wsize, uint8_t *rbuff, uint32_t rsize)
{
    uint32_t status;
    uint32_t wtransferred = 0;
    uint32_t rtransferred = 0;
    uint32_t retry = 0;

    /* check parameter validity */
    if (wbuff == NULL || wsize == 0 || rbuff == NULL || rsize == 0) {
        return status_invalid_argument;
    }

    /* data transfer */
    while (wtransferred < wsize || rtransferred < rsize) {
        status = ptr->STATUS;

        if (wtransferred < wsize) {
            /* write data into the txfifo */
            if (!(status & SPI_STATUS_TXFULL_MASK)) {
                if (datalen <= spi_data_length_8_bits) {
                    ptr->DATA = *(uint8_t *)wbuff & ((1UL << (datalen + 1)) - 1);
                    wbuff += sizeof(uint8_t);
                }
                else if (datalen <= spi_data_length_16_bits) {
                    ptr->DATA = *(uint16_t *)wbuff & ((1UL << (datalen + 1)) - 1);
                    wbuff += sizeof(uint16_t);
                }
                else if (datalen <= spi_data_length_31_bits) {
                    ptr->DATA = *(uint32_t *)wbuff & ((1UL << (datalen + 1)) - 1);
                    wbuff += sizeof(uint32_t);
                }
                else {
                    ptr->DATA = *(uint32_t *)wbuff & 0xffffffff;
                    wbuff += sizeof(uint32_t);
                }
                /* transfer count increment */
                wtransferred++;
                retry = 0;
            } else {
                if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
                    break;
                }
                retry++;
            }
        }

        if (rtransferred < rsize) {
            /* read data from the txfifo */
            if (!(status & SPI_STATUS_RXEMPTY_MASK)) {

                if (datalen <= spi_data_length_8_bits) {
                    *(uint8_t *)rbuff = (uint8_t)(ptr->DATA & ((1UL << (datalen + 1)) - 1));
                    rbuff += sizeof(uint8_t);
                }
                else if (datalen <= spi_data_length_16_bits) {
                    *(uint16_t *)rbuff = (uint16_t)(ptr->DATA & ((1UL << (datalen + 1)) - 1));
                    rbuff += sizeof(uint16_t);
                }
                else if (datalen <= spi_data_length_31_bits) {
                    *(uint32_t *)rbuff = (uint32_t)(ptr->DATA & ((1UL << (datalen + 1)) - 1));
                    rbuff += sizeof(uint32_t);
                }
                else {
                    *(uint32_t *)rbuff = (uint32_t)(ptr->DATA & 0xffffffff);
                    rbuff += sizeof(uint32_t);
                }
                /* transfer count increment */
                rtransferred++;
                retry = 0;
            } else {
                if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
                    break;
                }
                retry++;
            }
        }
    }

    if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
        /* dummy state may triggers timeout if dummy count, retry count, spi rate and cpu frequency are inappropriate */
        return status_timeout;
    }

    return status_success;
}

static hpm_stat_t spi_no_data(SPI_Type *ptr, spi_mode_selection_t mode, spi_control_config_t *config)
{
    hpm_stat_t stat;
    if (mode == spi_master_mode) {
        if (config->master_config.cmd_enable == false && config->master_config.addr_enable == false) {
            return status_invalid_argument;
        }
    }
    else {
        HPM_CHECK_RET(spi_wait_for_busy_status(ptr));
        HPM_CHECK_RET(spi_wait_for_idle_status(ptr));
    }

    return status_success;
}

void spi_master_get_default_timing_config(spi_timing_config_t *config)
{
    config->master_config.cs2sclk = spi_cs2sclk_half_sclk_4;
    config->master_config.csht = spi_csht_half_sclk_12;
}

void spi_master_get_default_format_config(spi_format_config_t *config)
{
    config->master_config.addr_len_in_bytes = 1;
    config->common_config.data_len_in_bits = 32;
    config->common_config.data_merge = false;
    config->common_config.mosi_bidir = false;
    config->common_config.lsb = false;
    config->common_config.mode = spi_master_mode;
    config->common_config.cpol = spi_sclk_high_idle;
    config->common_config.cpha = spi_sclk_sampling_even_clk_edges;
}

void spi_slave_get_default_format_config(spi_format_config_t *config)
{
    config->common_config.data_len_in_bits = 32;
    config->common_config.data_merge = false;
    config->common_config.mosi_bidir = false;
    config->common_config.lsb = false;
    config->common_config.mode = spi_master_mode;
    config->common_config.cpol = spi_sclk_high_idle;
    config->common_config.cpha = spi_sclk_sampling_even_clk_edges;
}

void spi_master_get_default_control_config(spi_control_config_t *config)
{
    config->master_config.cmd_enable = false;
    config->master_config.addr_enable = false;
    config->master_config.token_enable = false;
    config->master_config.token_value = spi_token_value_0x00;
    config->master_config.addr_phase_fmt = spi_address_phase_format_single_io_mode;
    config->common_config.tx_dma_enable = false;
    config->common_config.rx_dma_enable = false;
    config->common_config.trans_mode = spi_trans_write_only;
    config->common_config.data_phase_fmt = spi_single_io_mode;
    config->common_config.dummy_cnt = spi_dummy_count_2;
}

void spi_slave_get_default_control_config(spi_control_config_t *config)
{
    config->slave_config.slave_data_only = false;
    config->common_config.tx_dma_enable = false;
    config->common_config.rx_dma_enable = false;
    config->common_config.trans_mode = spi_trans_read_only;
    config->common_config.data_phase_fmt = spi_single_io_mode;
    config->common_config.dummy_cnt = spi_dummy_count_2;
}

hpm_stat_t spi_master_timing_init(SPI_Type *ptr, spi_timing_config_t *config)
{
    uint8_t sclk_div;

    if (config->master_config.sclk_freq_in_hz == 0) {
        return status_invalid_argument;
    }

    if (config->master_config.clk_src_freq_in_hz > config->master_config.sclk_freq_in_hz) {
        sclk_div = (config->master_config.clk_src_freq_in_hz / config->master_config.sclk_freq_in_hz) / 2 - 1;
    }
    else {
        sclk_div = 0xff;
    }

     ptr->TIMING = SPI_TIMING_CS2SCLK_SET(config->master_config.cs2sclk) |
                   SPI_TIMING_CSHT_SET(config->master_config.csht) |
                   SPI_TIMING_SCLK_DIV_SET(sclk_div);

    return status_success;
}

void spi_format_init(SPI_Type *ptr, spi_format_config_t *config)
{
    ptr->TRANSFMT = SPI_TRANSFMT_ADDRLEN_SET(config->master_config.addr_len_in_bytes - 1) |
                    SPI_TRANSFMT_DATALEN_SET(config->common_config.data_len_in_bits - 1) |
                    SPI_TRANSFMT_DATAMERGE_SET(config->common_config.data_merge) |
                    SPI_TRANSFMT_MOSIBIDIR_SET(config->common_config.mosi_bidir) |
                    SPI_TRANSFMT_LSB_SET(config->common_config.lsb) |
                    SPI_TRANSFMT_SLVMODE_SET(config->common_config.mode) |
                    SPI_TRANSFMT_CPOL_SET(config->common_config.cpol) |
                    SPI_TRANSFMT_CPHA_SET(config->common_config.cpha);
}

hpm_stat_t spi_transfer(SPI_Type *ptr,
                        spi_control_config_t *config,
                        uint8_t *cmd, uint32_t *addr,
                        uint8_t *wbuff, uint32_t wsize, uint8_t *rbuff, uint32_t rsize)
{
    hpm_stat_t stat = status_fail;
    uint8_t mode ,data_len, trans_mode;

    ptr->TRANSCTRL = SPI_TRANSCTRL_SLVDATAONLY_SET(config->slave_config.slave_data_only) |
                     SPI_TRANSCTRL_CMDEN_SET(config->master_config.cmd_enable) |
                     SPI_TRANSCTRL_ADDREN_SET(config->master_config.addr_enable) |
                     SPI_TRANSCTRL_ADDRFMT_SET(config->master_config.addr_phase_fmt) |
                     SPI_TRANSCTRL_TRANSMODE_SET(config->common_config.trans_mode) |
                     SPI_TRANSCTRL_DUALQUAD_SET(config->common_config.data_phase_fmt) |
                     SPI_TRANSCTRL_TOKENEN_SET(config->master_config.token_enable) |
                     SPI_TRANSCTRL_WRTRANCNT_SET(wsize - 1) |
                     SPI_TRANSCTRL_TOKENVALUE_SET(config->master_config.token_value) |
                     SPI_TRANSCTRL_DUMMYCNT_SET(config->common_config.dummy_cnt) |
                     SPI_TRANSCTRL_RDTRANCNT_SET(rsize - 1);

    /* reset txfifo, rxfifo and control */
    ptr->CTRL |= SPI_CTRL_TXFIFORST_MASK | SPI_CTRL_RXFIFORST_MASK | SPI_CTRL_SPIRST_MASK;

    /* read data length */
    data_len = (ptr->TRANSFMT & SPI_TRANSFMT_DATALEN_MASK) >> SPI_TRANSFMT_DATALEN_SHIFT;

    /* read spi control mode */
    mode = (ptr->TRANSFMT & SPI_TRANSFMT_SLVMODE_MASK) >> SPI_TRANSFMT_SLVMODE_SHIFT;

    /* read spi transfer mode */
    trans_mode = config->common_config.trans_mode;

    /* command phase */
    stat = spi_write_command(ptr, mode, config, cmd);
    if (stat != status_success) {
        return stat;
    }

    /* address phase */
    stat = spi_write_address(ptr, mode, config, addr);
    if (stat != status_success) {
        return stat;
    }

    /* data phase */
    if (trans_mode == spi_trans_write_read_together) {
        stat = spi_write_read_data(ptr, data_len, wbuff, wsize, rbuff, rsize);
    }
    else if (trans_mode == spi_trans_write_only || trans_mode == spi_trans_dummy_write) {
        stat = spi_write_data(ptr, data_len, wbuff, wsize);
    }
    else if (trans_mode == spi_trans_read_only || trans_mode == spi_trans_dummy_read) {
        stat = spi_read_data(ptr, data_len, rbuff, rsize);
    }
    else if (trans_mode == spi_trans_write_read || trans_mode == spi_trans_write_dummy_read) {
        stat = spi_write_read_data(ptr, data_len, wbuff, wsize, rbuff, rsize);
    }
    else if (trans_mode == spi_trans_read_write || trans_mode == spi_trans_read_dummy_write) {
        stat = spi_write_read_data(ptr, data_len, wbuff, wsize, rbuff, rsize);
    }
    else if (trans_mode == spi_trans_no_data) {
        stat = spi_no_data(ptr, mode, config);
    }
    else {
        stat = status_invalid_argument;
    }

    /* read command and address */
    if (stat == status_success) {
        spi_read_command(ptr, mode, cmd);
    }

    if (stat != status_success) {
        return stat;
    }

    stat = spi_wait_for_idle_status(ptr);

    return stat;
}

hpm_stat_t spi_setup_dma_transfer(SPI_Type *ptr,
                        spi_control_config_t *config,
                        uint8_t *cmd, uint32_t *addr,
                        uint32_t wsize, uint32_t rsize)
{
    hpm_stat_t stat = status_fail;
    uint8_t mode;

    stat = spi_wait_for_idle_status(ptr);
    if (stat != status_success) {
        return stat;
    }

    ptr->TRANSCTRL = SPI_TRANSCTRL_SLVDATAONLY_SET(config->slave_config.slave_data_only) |
                     SPI_TRANSCTRL_CMDEN_SET(config->master_config.cmd_enable) |
                     SPI_TRANSCTRL_ADDREN_SET(config->master_config.addr_enable) |
                     SPI_TRANSCTRL_ADDRFMT_SET(config->master_config.addr_phase_fmt) |
                     SPI_TRANSCTRL_TRANSMODE_SET(config->common_config.trans_mode) |
                     SPI_TRANSCTRL_DUALQUAD_SET(config->common_config.data_phase_fmt) |
                     SPI_TRANSCTRL_TOKENEN_SET(config->master_config.token_enable) |
                     SPI_TRANSCTRL_WRTRANCNT_SET(wsize - 1) |
                     SPI_TRANSCTRL_TOKENVALUE_SET(config->master_config.token_value) |
                     SPI_TRANSCTRL_DUMMYCNT_SET(config->common_config.dummy_cnt) |
                     SPI_TRANSCTRL_RDTRANCNT_SET(rsize - 1);

    /* reset txfifo, rxfifo and control */
    ptr->CTRL |= SPI_CTRL_TXFIFORST_MASK | SPI_CTRL_RXFIFORST_MASK | SPI_CTRL_SPIRST_MASK;

    if (config->common_config.tx_dma_enable) {
        ptr->CTRL |= SPI_CTRL_TXDMAEN_MASK;
    }
    if (config->common_config.rx_dma_enable) {
        ptr->CTRL |= SPI_CTRL_RXDMAEN_MASK;
    }

    /* read spi control mode */
    mode = (ptr->TRANSFMT & SPI_TRANSFMT_SLVMODE_MASK) >> SPI_TRANSFMT_SLVMODE_SHIFT;

    /* command phase */
    stat = spi_write_command(ptr, mode, config, cmd);
    if (stat != status_success) {
        return stat;
    }

    /* address phase */
    stat = spi_write_address(ptr, mode, config, addr);
    if (stat != status_success) {
        return stat;
    }

    /* read command and address */
    if (stat == status_success) {
        spi_read_command(ptr, mode, cmd);
    }

    return stat;
}

