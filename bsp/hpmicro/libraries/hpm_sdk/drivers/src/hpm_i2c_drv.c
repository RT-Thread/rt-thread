/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_i2c_drv.h"

#ifndef HPM_I2C_DRV_DEFAULT_TPM
#define HPM_I2C_DRV_DEFAULT_TPM (0U)
#endif

#ifndef HPM_I2C_DRV_DEFAULT_RETRY_COUNT
#define HPM_I2C_DRV_DEFAULT_RETRY_COUNT (5000U)
#endif

#define period_in_100ps(freq) (10000000000UL / (freq))

typedef struct {
    uint32_t t_high;
    uint32_t t_low;
    uint16_t t_sp;
    uint16_t t_sudat;
    uint16_t t_hddat;
    uint16_t t_sclhi;
    uint16_t t_sclratio;
} i2c_timing_t;

static hpm_stat_t i2c_configure_timing(uint32_t src_clk_in_hz,
                                       i2c_mode_t i2c_mode,
                                       i2c_timing_t *timing)
{
    int32_t setup_time, hold_time, period;
    int32_t temp1, temp2, temp3;
    int32_t tpclk = period_in_100ps(src_clk_in_hz);

    switch (i2c_mode) {
    /*
     *          |Standard mode | Fast mode | Fast mode plus | Uint
     * ---------+--------------+-----------+----------------+-------
     *  t_high  |     4.0      |    0.6    |     0.26       |   us
     *  t_low   |     4.7      |    1.3    |     0.5        |   us
     *
     */
    /* time uint: 100ps */
    case i2c_mode_fast:
        timing->t_high = 6000;
        timing->t_low = 13000;
        timing->t_sclratio = 2;
        setup_time = 1000;
        hold_time = 3000;
        period = period_in_100ps(400000); /**< baudrate 400KHz */
        break;
    case i2c_mode_fast_plus:
        timing->t_high = 2600;
        timing->t_low = 5000;
        timing->t_sclratio = 2;
        setup_time = 500;
        hold_time = 0;
        period = period_in_100ps(1000000); /**< baudrate 1MHz */
        break;
    case i2c_mode_normal:
        timing->t_high = 40000;
        timing->t_low = 47000;
        timing->t_sclratio = 1;
        setup_time = 2500;
        hold_time = 3000;
        period = period_in_100ps(100000); /**< baudrate 100KHz */
        break;
    default:
        return status_i2c_not_supported;
    }

    /*
     * Spike Suppression | Standard | Fast mode | Fast mode plus | Uint
     *                   | mode     |           |                |
     * ------------------+----------+-----------+----------------+-------
     *    t_sp (min)     |    -     |  0 - 50   |    0 - 50      |   ns
     *
     * T_SP = 50ns / (tpclk * (TPM + 1))
     */
    timing->t_sp = 500 / period_in_100ps(src_clk_in_hz) / (HPM_I2C_DRV_DEFAULT_TPM + 1);

    /*
     * Setup time       |Standard mode | Fast mode | Fast mode plus | Uint
     * -----------------+--------------+-----------+----------------+-------
     *  t_sudat (min)   |     250      |    100    |     50         |   ns
     *
     * Setup time = (2 * tpclk) + (2 + T_SP + T_SUDAT) * tpclk * (TPM + 1)
     */
    temp1 = (setup_time - 2 * tpclk) / tpclk / (HPM_I2C_DRV_DEFAULT_TPM + 1) - 2 - timing->t_sp;
    timing->t_sudat = MAX(temp1, 0);
    /*
     * Hold time       |Standard mode | Fast mode | Fast mode plus | Uint
     * ----------------+--------------+-----------+----------------+-------
     *  t_hddata (min) |     300      |    300    |     0          |   ns
     *
     * Hold time = (2 * tpclk) + (2 + T_SP + T_HDDAT) * tpclk * (TPM + 1)
     */
    temp1 = (hold_time - 2 * tpclk) / tpclk / (HPM_I2C_DRV_DEFAULT_TPM + 1) - 2 - timing->t_sp;
    timing->t_hddat = MAX(temp1, 0);

    /*
     * SCLK High period = (2 * tpclk) + (2 + T_SP + T_SCLHi) * tpclk * (TPM + 1) > t_high;
     */
    temp1 = (timing->t_high - 2 * tpclk) / tpclk / (HPM_I2C_DRV_DEFAULT_TPM + 1) - 2 - timing->t_sp;

    /*
     * SCLK High period = (2 * tpclk) + (2 + T_SP + T_SCLHi) * tpclk * (TPM + 1) > period / (1 + ratio);
     */
    temp2 = (period / (1 + timing->t_sclratio) - 2 * tpclk) / tpclk / (HPM_I2C_DRV_DEFAULT_TPM + 1) - 2 - timing->t_sp;

    /*
     * SCLK Low period = (2 * tpclk) + (2 + T_SP + T_SCLHi * ratio) * tpclk * (TPM + 1) > t_low;
     */
    temp3 = ((timing->t_low - 2 * tpclk) / tpclk / (HPM_I2C_DRV_DEFAULT_TPM + 1) - 2 - timing->t_sp) / (timing->t_sclratio);

    timing->t_sclhi = MAX(MAX(temp1, temp2), temp3);

    /* update high_period and low_period to calculated value */
    timing->t_high = 2 * tpclk + (2 + timing->t_sp + timing->t_sclhi) * tpclk;
    timing->t_low = timing->t_high * timing->t_sclratio;

    return status_success;
}

void i2c_reset(I2C_Type *ptr)
{
    ptr->CTRL = 0;
    ptr->CMD = I2C_CMD_RESET;
    ptr->SETUP &= ~I2C_SETUP_IICEN_MASK;
}

hpm_stat_t i2c_init_master(I2C_Type *ptr, uint32_t src_clk_in_hz, i2c_config_t *config)
{
    hpm_stat_t stat = status_success;
    i2c_timing_t timing = {0};

    i2c_reset(ptr);

    stat = i2c_configure_timing(src_clk_in_hz, config->i2c_mode, &timing);
    if (status_success != stat) {
        return stat;
    }

    ptr->TPM = I2C_TPM_TPM_SET(HPM_I2C_DRV_DEFAULT_TPM);

    ptr->SETUP = I2C_SETUP_T_SP_SET(timing.t_sp)
        | I2C_SETUP_T_SUDAT_SET(timing.t_sudat)
        | I2C_SETUP_T_HDDAT_SET(timing.t_hddat)
        | I2C_SETUP_T_SCLRADIO_SET(timing.t_sclratio - 1)
        | I2C_SETUP_T_SCLHI_SET(timing.t_sclhi)
        | I2C_SETUP_ADDRESSING_SET(config->is_10bit_addressing)
        | I2C_SETUP_IICEN_MASK
        | I2C_SETUP_MASTER_MASK;

    return status_success;
}

hpm_stat_t i2c_master_address_read(I2C_Type *ptr, const uint16_t device_address,
                                   uint8_t *addr, uint32_t addr_size_in_byte,
                                   uint8_t *buf, const uint32_t size_in_byte)
{
    hpm_stat_t stat = status_success;
    uint32_t left;
    uint32_t retry;

    assert(addr_size_in_byte > 0 && addr_size_in_byte <= I2C_SOC_TRANSFER_COUNT_MAX);
    assert(size_in_byte > 0 && size_in_byte <= I2C_SOC_TRANSFER_COUNT_MAX);

    retry = 0;
    while (ptr->STATUS & I2C_STATUS_BUSBUSY_MASK) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    /* W1C, clear CMPL bit to avoid blocking the transmission */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;

    ptr->CMD = I2C_CMD_CLEAR_FIFO;
    ptr->CTRL = I2C_CTRL_PHASE_START_MASK
        | I2C_CTRL_PHASE_ADDR_MASK
        | I2C_CTRL_PHASE_DATA_MASK
        | I2C_CTRL_DIR_SET(I2C_DIR_MASTER_WRITE)
        | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(addr_size_in_byte));

    ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);

    left = addr_size_in_byte;
    while (left) {
        ptr->DATA = *(addr++);
        left--;
    }
    ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;

    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_CMPL_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }
    /* W1C, clear CMPL bit to avoid blocking the transmission */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;

    ptr->CMD = I2C_CMD_CLEAR_FIFO;
    ptr->CTRL = I2C_CTRL_PHASE_START_MASK
        | I2C_CTRL_PHASE_STOP_MASK
        | I2C_CTRL_PHASE_ADDR_MASK
        | I2C_CTRL_PHASE_DATA_MASK
        | I2C_CTRL_DIR_SET(I2C_DIR_MASTER_READ)
        | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size_in_byte));
    ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;

    retry = 0;
    left = size_in_byte;
    while (left) {
        if (!(ptr->STATUS & I2C_STATUS_FIFOEMPTY_MASK)) {
            *(buf++) = ptr->DATA;
            left--;
            retry = 0;
        } else {
            if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }

    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_CMPL_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }
    return stat;
}

hpm_stat_t i2c_master_address_write(I2C_Type *ptr, const uint16_t device_address,
                                    uint8_t *addr, uint32_t addr_size_in_byte,
                                    uint8_t *buf, const uint32_t size_in_byte)
{
    hpm_stat_t stat = status_success;
    uint32_t left;
    uint32_t retry;

    assert(addr_size_in_byte > 0 && addr_size_in_byte <= I2C_SOC_TRANSFER_COUNT_MAX);
    assert(size_in_byte > 0 && size_in_byte <= I2C_SOC_TRANSFER_COUNT_MAX);
    assert(addr_size_in_byte + size_in_byte <= I2C_SOC_TRANSFER_COUNT_MAX);

    retry = 0;
    while (ptr->STATUS & I2C_STATUS_BUSBUSY_MASK) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    /* W1C, clear CMPL bit to avoid blocking the transmission */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;

    ptr->CMD = I2C_CMD_CLEAR_FIFO;
    ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);
    ptr->CTRL = I2C_CTRL_PHASE_START_MASK
        | I2C_CTRL_PHASE_STOP_MASK
        | I2C_CTRL_PHASE_ADDR_MASK
        | I2C_CTRL_PHASE_DATA_MASK
        | I2C_CTRL_DIR_SET(I2C_DIR_MASTER_WRITE)
        | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size_in_byte + addr_size_in_byte));

    left = addr_size_in_byte;
    while (left) {
        ptr->DATA = *(addr++);
        left--;
    }
    ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;

    retry = 0;
    left = size_in_byte;
    while (left) {
        if (!(ptr->STATUS & I2C_STATUS_FIFOFULL_MASK)) {
            ptr->DATA = *(buf++);
            left--;
            retry = 0;
        } else {
            if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_CMPL_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        } else {
            retry++;
        }
    }

    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    return stat;
}

hpm_stat_t i2c_master_read(I2C_Type *ptr, const uint16_t device_address,
                           uint8_t *buf, const uint32_t size)
{
    hpm_stat_t stat = status_success;
    uint32_t left;
    uint32_t retry;

    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    retry = 0;
    while (ptr->STATUS & I2C_STATUS_BUSBUSY_MASK) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    /* W1C, clear CMPL bit to avoid blocking the transmission */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;

    ptr->CMD = I2C_CMD_CLEAR_FIFO;
    ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);
    ptr->CTRL = I2C_CTRL_PHASE_START_MASK
        | I2C_CTRL_PHASE_STOP_MASK
        | I2C_CTRL_PHASE_ADDR_MASK
        | I2C_CTRL_PHASE_DATA_MASK
        | I2C_CTRL_DIR_SET(I2C_DIR_MASTER_READ)
        | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size));
    ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;

    retry = 0;
    left = size;
    while (left) {
        if (!(ptr->STATUS & I2C_STATUS_FIFOEMPTY_MASK)) {
            *(buf++) = ptr->DATA;
            left--;
            retry = 0;
        } else {
            if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_CMPL_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    };
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    if (!(ptr->STATUS & I2C_STATUS_ADDRHIT_MASK)) {
        /* I2C slave did not receive this transaction correctly. */
        return status_fail;
    }

    if (i2c_get_data_count(ptr)) {
        return status_i2c_transmit_not_completed;
    }

    return stat;
}

hpm_stat_t i2c_master_write(I2C_Type *ptr, const uint16_t device_address,
                            uint8_t *buf, const uint32_t size)
{
    hpm_stat_t stat = status_success;
    uint32_t retry;
    uint32_t left;

    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    retry = 0;
    while (ptr->STATUS & I2C_STATUS_BUSBUSY_MASK) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    /* W1C, clear CMPL bit to avoid blocking the transmission */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;

    ptr->CMD = I2C_CMD_CLEAR_FIFO;
    ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);
    ptr->CTRL = I2C_CTRL_PHASE_START_MASK
        | I2C_CTRL_PHASE_STOP_MASK
        | I2C_CTRL_PHASE_ADDR_MASK
        | I2C_CTRL_PHASE_DATA_MASK
        | I2C_CTRL_DIR_SET(I2C_DIR_MASTER_WRITE)
        | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size));

    retry = 0;
    left = size;
    while (left) {
        if (!(ptr->STATUS & I2C_STATUS_FIFOFULL_MASK)) {
            ptr->DATA = *(buf++);
            left--;
            ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;
            retry = 0;
        } else {
            if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_CMPL_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    if (i2c_get_data_count(ptr)) {
        return status_i2c_transmit_not_completed;
    }

    return stat;
}

hpm_stat_t i2c_init_slave(I2C_Type *ptr, uint32_t src_clk_in_hz,
                          i2c_config_t *config, const uint16_t slave_address)
{
    hpm_stat_t stat = status_success;
    i2c_timing_t timing = {0};

    i2c_reset(ptr);

    ptr->ADDR = I2C_ADDR_ADDR_SET(slave_address);

    stat = i2c_configure_timing(src_clk_in_hz, config->i2c_mode, &timing);
    if (status_success != stat) {
        return stat;
    }

    ptr->TPM = I2C_TPM_TPM_SET(HPM_I2C_DRV_DEFAULT_TPM);

    ptr->SETUP = I2C_SETUP_T_SP_SET(timing.t_sp)
        | I2C_SETUP_T_SUDAT_SET(timing.t_sudat)
        | I2C_SETUP_T_HDDAT_SET(timing.t_hddat)
        | I2C_SETUP_T_SCLRADIO_SET(timing.t_sclratio - 1)
        | I2C_SETUP_T_SCLHI_SET(timing.t_sclhi)
        | I2C_SETUP_ADDRESSING_SET(config->is_10bit_addressing)
        | I2C_SETUP_IICEN_MASK;

    return stat;
}

hpm_stat_t i2c_slave_write(I2C_Type *ptr, uint8_t *buf, const uint32_t size)
{
    volatile uint32_t status;
    uint32_t retry;
    uint32_t left;

    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    /* wait for address hit */
    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_ADDRHIT_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_fail;
    }

    /* W1C, clear CMPL bit and clear ADDRHIT bit to avoid blocking the transmission */
    ptr->STATUS = I2C_STATUS_CMPL_MASK | I2C_STATUS_ADDRHIT_MASK;
    ptr->CMD = I2C_CMD_CLEAR_FIFO;

    retry = 0;
    left = size;
    while (left) {
        status = ptr->STATUS;
        if (!(status & I2C_STATUS_FIFOFULL_MASK)) {
            ptr->DATA = *(buf++);
            left--;
            retry = 0;
        } else {
            if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_CMPL_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }
    /* clear status, CMPL must to be cleared at slave mode before next transaction */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;

    if (i2c_get_data_count(ptr) != size) {
        return status_i2c_transmit_not_completed;
    }

    return status_success;
}

hpm_stat_t i2c_slave_read(I2C_Type *ptr,
                          uint8_t *buf,
                          const uint32_t size)
{
    volatile uint32_t status;
    uint32_t retry;
    uint32_t left;

    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    /* wait for address hit */
    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_ADDRHIT_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_fail;
    }

    /* W1C, clear CMPL bit and clear ADDRHIT bit to avoid blocking the transmission */
    ptr->STATUS = I2C_STATUS_CMPL_MASK | I2C_STATUS_ADDRHIT_MASK;
    ptr->CMD = I2C_CMD_CLEAR_FIFO;

    retry = 0;
    left = size;
    while (left) {
        status = ptr->STATUS;
        if (!(status & I2C_STATUS_FIFOEMPTY_MASK)) {
            *(buf++) = ptr->DATA;
            left--;
            retry = 0;
        } else {
            if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_CMPL_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }
    /* clear status, CMPL must to be cleared at slave mode before next transaction */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;

    if (i2c_get_data_count(ptr) != size) {
        return status_i2c_transmit_not_completed;
    }

    return status_success;
}

hpm_stat_t i2c_master_start_dma_write(I2C_Type *i2c_ptr, const uint16_t device_address, uint32_t size)
{
    uint32_t retry = 0;
    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    while (i2c_ptr->STATUS & I2C_STATUS_BUSBUSY_MASK) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    /* W1C, clear CMPL bit to avoid blocking the transmission */
    i2c_ptr->STATUS = I2C_STATUS_CMPL_MASK;

    i2c_ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);
    i2c_ptr->CTRL = I2C_CTRL_PHASE_START_MASK
        | I2C_CTRL_PHASE_STOP_MASK
        | I2C_CTRL_PHASE_ADDR_MASK
        | I2C_CTRL_PHASE_DATA_MASK
        | I2C_CTRL_DIR_SET(I2C_DIR_MASTER_WRITE)
        | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size));

    i2c_ptr->SETUP |= I2C_SETUP_DMAEN_MASK;

    i2c_ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;

    return status_success;
}

hpm_stat_t i2c_master_start_dma_read(I2C_Type *i2c_ptr, const uint16_t device_address, uint32_t size)
{
    uint32_t retry = 0;
    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    while (i2c_ptr->STATUS & I2C_STATUS_BUSBUSY_MASK) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }
    /* W1C, clear CMPL bit to avoid blocking the transmission */
    i2c_ptr->STATUS = I2C_STATUS_CMPL_MASK;

    i2c_ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);
    i2c_ptr->CTRL = I2C_CTRL_PHASE_START_MASK
        | I2C_CTRL_PHASE_STOP_MASK
        | I2C_CTRL_PHASE_ADDR_MASK
        | I2C_CTRL_PHASE_DATA_MASK
        | I2C_CTRL_DIR_SET(I2C_DIR_MASTER_READ)
        | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size));

    i2c_ptr->SETUP |= I2C_SETUP_DMAEN_MASK;

    i2c_ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;

    return status_success;
}

hpm_stat_t i2c_slave_dma_transfer(I2C_Type *i2c_ptr, uint32_t size)
{
    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    /* W1C, clear CMPL bit to avoid blocking the transmission */
    i2c_ptr->STATUS = I2C_STATUS_CMPL_MASK;

    i2c_ptr->CTRL |= I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size));

    i2c_ptr->SETUP |= I2C_SETUP_DMAEN_MASK;

    return status_success;
}

hpm_stat_t i2c_master_configure_transfer(I2C_Type *i2c_ptr, const uint16_t device_address, uint32_t size, bool read)
{
    uint32_t retry = 0;
    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    while (i2c_ptr->STATUS & I2C_STATUS_BUSBUSY_MASK) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }
    /* W1C, clear CMPL bit to avoid blocking the transmission */
    i2c_ptr->STATUS = I2C_STATUS_CMPL_MASK;
    i2c_ptr->CMD = I2C_CMD_CLEAR_FIFO;
    i2c_ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);
    i2c_ptr->CTRL = I2C_CTRL_PHASE_START_MASK
                | I2C_CTRL_PHASE_STOP_MASK
                | I2C_CTRL_PHASE_ADDR_MASK
                | I2C_CTRL_PHASE_DATA_MASK
                | I2C_CTRL_DIR_SET(read)
                | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size));

    i2c_ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;

    return status_success;
}

hpm_stat_t i2c_master_seq_transmit(I2C_Type *ptr, const uint16_t device_address,
                                    uint8_t *buf, const uint32_t size, i2c_seq_transfer_opt_t opt)
{
    uint32_t ctrl;
    uint32_t retry = 0;
    uint32_t left = 0;

    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    /* W1C, clear CMPL bit to avoid blocking the transmission */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;
    ptr->CMD = I2C_CMD_CLEAR_FIFO;
    ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);

    switch (opt) {
    case i2c_frist_frame:
        ctrl = I2C_CTRL_PHASE_START_SET(true) | I2C_CTRL_PHASE_STOP_SET(false) \
               | I2C_CTRL_PHASE_ADDR_SET(true);
        break;
    case i2c_next_frame:
        ctrl = I2C_CTRL_PHASE_START_SET(false) | I2C_CTRL_PHASE_STOP_SET(false) \
               | I2C_CTRL_PHASE_ADDR_SET(false);
        break;
    case i2c_last_frame:
        ctrl = I2C_CTRL_PHASE_START_SET(false) | I2C_CTRL_PHASE_STOP_SET(true) \
               | I2C_CTRL_PHASE_ADDR_SET(false);
        break;
    default:
        return status_invalid_argument;
    }

    ptr->CTRL = ctrl | I2C_CTRL_PHASE_DATA_SET(true) \
                | I2C_CTRL_DIR_SET(I2C_DIR_MASTER_WRITE) \
                | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size));
    /* enable auto ack */
    ptr->INTEN &= ~I2C_EVENT_BYTE_RECEIVED;

    retry = 0;
    left = size;
    while (left) {
        if (!(ptr->STATUS & I2C_STATUS_FIFOFULL_MASK)) {
            ptr->DATA = *(buf++);
            left--;
            ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;
            retry = 0;
        } else {
            if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }
    retry = 0;
    while (!(ptr->STATUS & I2C_STATUS_CMPL_MASK)) {
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            break;
        }
        retry++;
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }
    /* clear status, CMPL must to be cleared at slave mode before next transaction */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;
    return status_success;
}

hpm_stat_t i2c_master_seq_receive(I2C_Type *ptr, const uint16_t device_address,
                                    uint8_t *buf, const uint32_t size, i2c_seq_transfer_opt_t opt)
{
   uint32_t ctrl;
    uint32_t retry = 0;
    uint32_t left = 0;

    assert(size > 0 && size <= I2C_SOC_TRANSFER_COUNT_MAX);

    /* W1C, clear CMPL bit to avoid blocking the transmission */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;
    ptr->CMD = I2C_CMD_CLEAR_FIFO;
    ptr->ADDR = I2C_ADDR_ADDR_SET(device_address);

    switch (opt) {
    case i2c_frist_frame:
        ctrl = I2C_CTRL_PHASE_START_SET(true) | I2C_CTRL_PHASE_STOP_SET(false) \
               | I2C_CTRL_PHASE_ADDR_SET(true);
        break;
    case i2c_next_frame:
        ctrl = I2C_CTRL_PHASE_START_SET(false) | I2C_CTRL_PHASE_STOP_SET(false) \
               | I2C_CTRL_PHASE_ADDR_SET(false);
        break;
    case i2c_last_frame:
        ctrl = I2C_CTRL_PHASE_START_SET(false) | I2C_CTRL_PHASE_STOP_SET(true) \
               | I2C_CTRL_PHASE_ADDR_SET(false);
        break;
    default:
        return status_invalid_argument;
    }

    ptr->CTRL = ctrl | I2C_CTRL_PHASE_DATA_SET(true) \
                | I2C_CTRL_DIR_SET(I2C_DIR_MASTER_READ) \
                | I2C_CTRL_DATACNT_SET(I2C_DATACNT_MAP(size));

    /* disable auto ack */
    ptr->INTEN |= I2C_EVENT_BYTE_RECEIVED;
    ptr->CMD = I2C_CMD_ISSUE_DATA_TRANSMISSION;

    retry = 0;
    left = size;
    while (left) {
        if (!(ptr->STATUS & I2C_STATUS_FIFOEMPTY_MASK)) {
            *(buf++) = ptr->DATA;
            left--;
            if ((left == 0) && (opt == i2c_last_frame)) {
                ptr->CMD = I2C_CMD_NACK;
            } else {
                ptr->CMD = I2C_CMD_ACK;
            }
            retry = 0;
        } else {
            if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
    }
    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }

    if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
        return status_timeout;
    }
    if (opt  == i2c_last_frame) {
        retry = 0;
        while (!(ptr->STATUS & I2C_STATUS_CMPL_MASK)) {
            if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
                break;
            }
            retry++;
        }
        if (retry > HPM_I2C_DRV_DEFAULT_RETRY_COUNT) {
            return status_timeout;
        }
    }
    /* clear status, CMPL must to be cleared at slave mode before next transaction */
    ptr->STATUS = I2C_STATUS_CMPL_MASK;
    /* default auto ack */
    ptr->INTEN &= ~I2C_EVENT_BYTE_RECEIVED;

    return status_success;
}

