/*
 * Copyright (c) 2021 HPMicro
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
    } while (status & SPI_STATUS_SPIACTIVE_MASK);

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
    } while (!(status & SPI_STATUS_SPIACTIVE_MASK));

    if (retry > HPM_SPI_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    return status_success;
}

hpm_stat_t spi_write_command(SPI_Type *ptr, spi_mode_selection_t mode, spi_control_config_t *config, uint8_t *cmd)
{
    if (mode == spi_master_mode) {
        if (config->master_config.cmd_enable == true) {
            if (cmd == NULL) {
                return status_invalid_argument;
            }
            ptr->CMD = SPI_CMD_CMD_SET(*cmd);
        } else {
            ptr->CMD = SPI_CMD_CMD_SET(0xff); /* Write a dummy byte */
        }
    }

    return status_success;
}

hpm_stat_t spi_read_command(SPI_Type *ptr, spi_mode_selection_t mode, spi_control_config_t *config, uint8_t *cmd)
{
    if (mode == spi_slave_mode) {
        if (config->slave_config.slave_data_only == false) {
            if (cmd == NULL) {
                return status_invalid_argument;
            }
            *cmd = (uint8_t)(ptr->CMD & SPI_CMD_CMD_MASK) >> SPI_CMD_CMD_SHIFT;
        }
    }

    return status_success;
}

hpm_stat_t spi_write_address(SPI_Type *ptr, spi_mode_selection_t mode, spi_control_config_t *config, uint32_t *addr)
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

hpm_stat_t spi_write_data(SPI_Type *ptr, uint8_t data_len_in_bytes, uint8_t *buff, uint32_t count)
{
    uint32_t status;
    uint32_t transferred = 0;
    uint32_t retry = 0;
    uint32_t temp;

    /* check parameter validity */
    if (buff == NULL || count == 0) {
        return status_invalid_argument;
    }

    if (data_len_in_bytes > 4 || data_len_in_bytes < 1) {
        return status_invalid_argument;
    }

    /* data transfer */
    while (transferred < count) {
        status = ptr->STATUS;
        if (!(status & SPI_STATUS_TXFULL_MASK)) {
            /* write data into the txfifo */
            temp = 0;
            for (uint8_t i = 0; i < data_len_in_bytes; i++) {
                temp += *(buff++) << i * 8;
            }
            ptr->DATA = temp;
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

hpm_stat_t spi_read_data(SPI_Type *ptr, uint8_t data_len_in_bytes, uint8_t *buff, uint32_t count)
{
    uint32_t transferred = 0;
    uint32_t retry = 0;
    uint32_t temp;
    uint8_t rx_valid_size = 0;
    uint8_t j = 0;
    /* check parameter validity */
    if (buff == NULL || count == 0) {
        return status_invalid_argument;
    }

    if (data_len_in_bytes > 4 || data_len_in_bytes < 1) {
        return status_invalid_argument;
    }

    /* data transfer */
    while (transferred < count) {
        rx_valid_size = spi_get_rx_fifo_valid_data_size(ptr);
        if (rx_valid_size > 0) {
            for (j = 0; j < rx_valid_size; j++) {
                temp = ptr->DATA;
                for (uint8_t i = 0; i < data_len_in_bytes; i++) {
                    *(buff++) = (uint8_t)(temp >> (i * 8));
                }
            }
            /* transfer count increment */
            transferred += rx_valid_size;
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

hpm_stat_t spi_write_read_data(SPI_Type *ptr, uint8_t data_len_in_bytes, uint8_t *wbuff, uint32_t wcount, uint8_t *rbuff, uint32_t rcount)
{
    uint32_t status;
    uint32_t wtransferred = 0;
    uint32_t rtransferred = 0;
    uint32_t retry = 0;
    uint32_t temp;

    /* check parameter validity */
    if (wbuff == NULL || wcount == 0 || rbuff == NULL || rcount == 0) {
        return status_invalid_argument;
    }

    if (data_len_in_bytes > 4 || data_len_in_bytes < 1) {
        return status_invalid_argument;
    }

    /* data transfer */
    while (wtransferred < wcount || rtransferred < rcount) {
        status = ptr->STATUS;

        if (wtransferred < wcount) {
            /* write data into the txfifo */
            if (!(status & SPI_STATUS_TXFULL_MASK)) {
                temp = 0;
                for (uint8_t i = 0; i < data_len_in_bytes; i++) {
                    temp += *(wbuff++) << i * 8;
                }
                ptr->DATA = temp;
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

        if (rtransferred < rcount) {
            /* read data from the txfifo */
            if (!(status & SPI_STATUS_RXEMPTY_MASK)) {
                temp = ptr->DATA;
                for (uint8_t i = 0; i < data_len_in_bytes; i++) {
                    *(rbuff++) = (uint8_t)(temp >> (i * 8));
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
    (void) ptr;
    if (mode == spi_master_mode) {
        if (config->master_config.cmd_enable == false && config->master_config.addr_enable == false) {
            return status_invalid_argument;
        }
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
#if defined(HPM_IP_FEATURE_SPI_CS_SELECT) && (HPM_IP_FEATURE_SPI_CS_SELECT == 1)
    config->common_config.cs_index = spi_cs_0;
#endif
}

void spi_slave_get_default_control_config(spi_control_config_t *config)
{
    config->slave_config.slave_data_only = false;
    config->common_config.tx_dma_enable = false;
    config->common_config.rx_dma_enable = false;
    config->common_config.trans_mode = spi_trans_read_only;
    config->common_config.data_phase_fmt = spi_single_io_mode;
    config->common_config.dummy_cnt = spi_dummy_count_2;
#if defined(HPM_IP_FEATURE_SPI_CS_SELECT) && (HPM_IP_FEATURE_SPI_CS_SELECT == 1)
    config->common_config.cs_index = spi_cs_0;
#endif
}

hpm_stat_t spi_master_timing_init(SPI_Type *ptr, spi_timing_config_t *config)
{
    uint8_t sclk_div;
    uint8_t div_remainder;
    uint8_t div_integer;
    if (config->master_config.sclk_freq_in_hz == 0) {
        return status_invalid_argument;
    }

    if (config->master_config.clk_src_freq_in_hz > config->master_config.sclk_freq_in_hz) {
        div_remainder = (config->master_config.clk_src_freq_in_hz % config->master_config.sclk_freq_in_hz);
        div_integer  = (config->master_config.clk_src_freq_in_hz / config->master_config.sclk_freq_in_hz);
        if ((div_remainder != 0) || ((div_integer % 2) != 0)) {
            return status_invalid_argument;
        }
        sclk_div = (div_integer / 2) - 1;
    } else {
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

hpm_stat_t spi_control_init(SPI_Type *ptr, spi_control_config_t *config, uint32_t wcount, uint32_t rcount)
{
#if defined (SPI_SOC_TRANSFER_COUNT_MAX) && (SPI_SOC_TRANSFER_COUNT_MAX == 512)
    if ((wcount > SPI_SOC_TRANSFER_COUNT_MAX) || (rcount > SPI_SOC_TRANSFER_COUNT_MAX)) {
        return status_invalid_argument;
    }
#endif
    /* slave data only mode only works on write read together transfer mode */
    if (config->slave_config.slave_data_only == true && config->common_config.trans_mode != spi_trans_write_read_together) {
        return status_invalid_argument;
    }

    ptr->TRANSCTRL = SPI_TRANSCTRL_SLVDATAONLY_SET(config->slave_config.slave_data_only) |
                     SPI_TRANSCTRL_CMDEN_SET(config->master_config.cmd_enable) |
                     SPI_TRANSCTRL_ADDREN_SET(config->master_config.addr_enable) |
                     SPI_TRANSCTRL_ADDRFMT_SET(config->master_config.addr_phase_fmt) |
                     SPI_TRANSCTRL_TRANSMODE_SET(config->common_config.trans_mode) |
                     SPI_TRANSCTRL_DUALQUAD_SET(config->common_config.data_phase_fmt) |
                     SPI_TRANSCTRL_TOKENEN_SET(config->master_config.token_enable) |
                     SPI_TRANSCTRL_WRTRANCNT_SET(wcount - 1) |
                     SPI_TRANSCTRL_TOKENVALUE_SET(config->master_config.token_value) |
                     SPI_TRANSCTRL_DUMMYCNT_SET(config->common_config.dummy_cnt) |
                     SPI_TRANSCTRL_RDTRANCNT_SET(rcount - 1);

#if defined(HPM_IP_FEATURE_SPI_CS_SELECT) && (HPM_IP_FEATURE_SPI_CS_SELECT == 1)
    ptr->CTRL = (ptr->CTRL & ~SPI_CTRL_CS_EN_MASK) | SPI_CTRL_CS_EN_SET(config->common_config.cs_index);
#endif

#if defined(HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT) && (HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT == 1)
    ptr->WR_TRANS_CNT = wcount - 1;
    ptr->RD_TRANS_CNT = rcount - 1;
#endif

    /* reset txfifo, rxfifo and control */
    ptr->CTRL |= SPI_CTRL_TXFIFORST_MASK | SPI_CTRL_RXFIFORST_MASK | SPI_CTRL_SPIRST_MASK;

    return status_success;
}

hpm_stat_t spi_transfer(SPI_Type *ptr,
                        spi_control_config_t *config,
                        uint8_t *cmd, uint32_t *addr,
                        uint8_t *wbuff, uint32_t wcount, uint8_t *rbuff, uint32_t rcount)
{
    hpm_stat_t stat = status_fail;
    uint8_t mode, data_len_in_bytes, trans_mode;

    stat = spi_control_init(ptr, config, wcount, rcount);
    if (stat != status_success) {
        return stat;
    }

    /* read data length */
    data_len_in_bytes = spi_get_data_length_in_bytes(ptr);

    /* read spi control mode */
    mode = (ptr->TRANSFMT & SPI_TRANSFMT_SLVMODE_MASK) >> SPI_TRANSFMT_SLVMODE_SHIFT;

    /* read spi transfer mode */
    trans_mode = config->common_config.trans_mode;

    /* write address on master mode */
    stat = spi_write_address(ptr, mode, config, addr);
    if (stat != status_success) {
        return stat;
    }

    /* write command on master mode */
    stat = spi_write_command(ptr, mode, config, cmd);
    if (stat != status_success) {
        return stat;
    }

    /* data phase */
    if (trans_mode == spi_trans_write_read_together) {
        stat = spi_write_read_data(ptr, data_len_in_bytes, wbuff, wcount, rbuff, rcount);
    } else if (trans_mode == spi_trans_write_only || trans_mode == spi_trans_dummy_write) {
        stat = spi_write_data(ptr, data_len_in_bytes, wbuff, wcount);
    } else if (trans_mode == spi_trans_read_only || trans_mode == spi_trans_dummy_read) {
        stat = spi_read_data(ptr, data_len_in_bytes, rbuff, rcount);
    } else if (trans_mode == spi_trans_write_read || trans_mode == spi_trans_write_dummy_read) {
        stat = spi_write_read_data(ptr, data_len_in_bytes, wbuff, wcount, rbuff, rcount);
    } else if (trans_mode == spi_trans_read_write || trans_mode == spi_trans_read_dummy_write) {
        stat = spi_write_read_data(ptr, data_len_in_bytes, wbuff, wcount, rbuff, rcount);
    } else if (trans_mode == spi_trans_no_data) {
        stat = spi_no_data(ptr, mode, config);
    } else {
        stat = status_invalid_argument;
    }

    if (stat != status_success) {
        return stat;
    }

    /* read command on slave mode */
    stat = spi_read_command(ptr, mode, config, cmd);
    if (stat != status_success) {
        return stat;
    }
    /* on the slave mode, if master keeps asserting the cs signal, it's maybe timeout */
    stat = spi_wait_for_idle_status(ptr);
    return stat;
}

hpm_stat_t spi_setup_dma_transfer(SPI_Type *ptr,
                        spi_control_config_t *config,
                        uint8_t *cmd, uint32_t *addr,
                        uint32_t wcount, uint32_t rcount)
{
    hpm_stat_t stat = status_fail;
    uint8_t mode;

    stat = spi_control_init(ptr, config, wcount, rcount);
    if (stat != status_success) {
        return stat;
    }

    if (config->common_config.tx_dma_enable) {
        ptr->CTRL |= SPI_CTRL_TXDMAEN_MASK;
    }
    if (config->common_config.rx_dma_enable) {
        ptr->CTRL |= SPI_CTRL_RXDMAEN_MASK;
    }

    /* read spi control mode */
    mode = (ptr->TRANSFMT & SPI_TRANSFMT_SLVMODE_MASK) >> SPI_TRANSFMT_SLVMODE_SHIFT;

    /* address phase */
    stat = spi_write_address(ptr, mode, config, addr);
    if (stat != status_success) {
        return stat;
    }

    /* command phase */
    stat = spi_write_command(ptr, mode, config, cmd);
    if (stat != status_success) {
        return stat;
    }

    return stat;
}


#if defined(HPM_IP_FEATURE_SPI_SUPPORT_DIRECTIO) && (HPM_IP_FEATURE_SPI_SUPPORT_DIRECTIO == 1)
hpm_stat_t spi_directio_enable_output(SPI_Type *ptr, spi_directio_pin_t pin)
{
    hpm_stat_t stat = status_success;
    switch (pin) {
    case hold_pin:
        ptr->DIRECTIO |= SPI_DIRECTIO_HOLD_OE_MASK;
        break;
    case wp_pin:
        ptr->DIRECTIO |= SPI_DIRECTIO_WP_OE_MASK;
        break;
    case miso_pin:
        ptr->DIRECTIO |= SPI_DIRECTIO_MISO_OE_MASK;
        break;
    case mosi_pin:
        ptr->DIRECTIO |= SPI_DIRECTIO_MOSI_OE_MASK;
        break;
    case sclk_pin:
        ptr->DIRECTIO |= SPI_DIRECTIO_SCLK_OE_MASK;
        break;
    case cs_pin:
        ptr->DIRECTIO |= SPI_DIRECTIO_CS_OE_MASK;
        break;
    default:
        stat = status_invalid_argument;
        break;
    }
    return stat;
}

hpm_stat_t spi_directio_disable_output(SPI_Type *ptr, spi_directio_pin_t pin)
{
    hpm_stat_t stat = status_success;
    switch (pin) {
    case hold_pin:
        ptr->DIRECTIO &= ~SPI_DIRECTIO_HOLD_OE_MASK;
        break;
    case wp_pin:
        ptr->DIRECTIO &= ~SPI_DIRECTIO_WP_OE_MASK;
        break;
    case miso_pin:
        ptr->DIRECTIO &= ~SPI_DIRECTIO_MISO_OE_MASK;
        break;
    case mosi_pin:
        ptr->DIRECTIO &= ~SPI_DIRECTIO_MOSI_OE_MASK;
        break;
    case sclk_pin:
        ptr->DIRECTIO &= ~SPI_DIRECTIO_SCLK_OE_MASK;
        break;
    case cs_pin:
        ptr->DIRECTIO &= ~SPI_DIRECTIO_CS_OE_MASK;
        break;
    default:
        stat = status_invalid_argument;
        break;
    }
    return stat;
}

hpm_stat_t spi_directio_write(SPI_Type *ptr, spi_directio_pin_t pin, bool high)
{
    hpm_stat_t stat = status_success;
    switch (pin) {
    case hold_pin:
        (high == true) ? (ptr->DIRECTIO |= SPI_DIRECTIO_HOLD_O_MASK) : (ptr->DIRECTIO &= ~SPI_DIRECTIO_HOLD_O_MASK);
        break;
    case wp_pin:
        (high == true) ? (ptr->DIRECTIO |= SPI_DIRECTIO_WP_O_MASK) : (ptr->DIRECTIO &= ~SPI_DIRECTIO_WP_O_MASK);
        break;
    case miso_pin:
        (high == true) ? (ptr->DIRECTIO |= SPI_DIRECTIO_MISO_O_MASK) : (ptr->DIRECTIO &= ~SPI_DIRECTIO_MISO_O_MASK);
        break;
    case mosi_pin:
        (high == true) ? (ptr->DIRECTIO |= SPI_DIRECTIO_MOSI_O_MASK) : (ptr->DIRECTIO &= ~SPI_DIRECTIO_MOSI_O_MASK);
        break;
    case sclk_pin:
        (high == true) ? (ptr->DIRECTIO |= SPI_DIRECTIO_SCLK_O_MASK) : (ptr->DIRECTIO &= ~SPI_DIRECTIO_SCLK_O_MASK);
        break;
    case cs_pin:
        (high == true) ? (ptr->DIRECTIO |= SPI_DIRECTIO_CS_O_MASK) : (ptr->DIRECTIO &= ~SPI_DIRECTIO_CS_O_MASK);
        break;
    default:
        stat = status_invalid_argument;
        break;
    }
    return stat;
}

uint8_t spi_directio_read(SPI_Type *ptr, spi_directio_pin_t pin)
{
    uint8_t io_sta = 0;
    switch (pin) {
    case hold_pin:
        io_sta = SPI_DIRECTIO_HOLD_I_GET(ptr->DIRECTIO);
        break;
    case wp_pin:
        io_sta = SPI_DIRECTIO_WP_I_GET(ptr->DIRECTIO);
        break;
    case miso_pin:
        io_sta = SPI_DIRECTIO_MISO_I_GET(ptr->DIRECTIO);
        break;
    case mosi_pin:
        io_sta = SPI_DIRECTIO_MOSI_I_GET(ptr->DIRECTIO);
        break;
    case sclk_pin:
        io_sta = SPI_DIRECTIO_SCLK_I_GET(ptr->DIRECTIO);
        break;
    case cs_pin:
        io_sta = SPI_DIRECTIO_CS_I_GET(ptr->DIRECTIO);
        break;
    default:
        break;
    }
    return io_sta;
}
#endif

