/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_linv2_drv.h"

#define HPM_LIN_DRV_RETRY_COUNT (50000U)

hpm_stat_t lin_master_configure_timing(LINV2_Type *ptr, lin_timing_t *timing)
{
    assert(timing->src_freq_in_hz >= 8000000U);
    assert((timing->baudrate >= 1000U) && (timing->baudrate <= 20000U));

    uint8_t prescaler, bt_mul;
    uint16_t bt_div;

    /** set master mode */
    ptr->TIMING_CONTROL = LINV2_TIMING_CONTROL_MASTER_MODE_MASK;
    ptr->TIMING_CONTROL |= LINV2_TIMING_CONTROL_LIN_INITIAL_MASK;
    ptr->TIMING_CONTROL &= ~LINV2_TIMING_CONTROL_LIN_INITIAL_MASK;

    bt_mul = 20000U / timing->baudrate - 1U;
    prescaler = (uint8_t)(log((timing->src_freq_in_hz / ((bt_mul + 1U) * timing->baudrate * 200U))) / log(2U) - 1U);
    bt_div = timing->src_freq_in_hz / ((1U << (prescaler + 1U)) * (bt_mul + 1U) * timing->baudrate);

    if ((bt_div < 200) || (bt_div > 512)) {
        return status_invalid_argument;
    }

    /** src =20MHz baudrate = 19.2KHz */
    /** bt_div = 260, scaler = 1, bt_mul = 0 */
    ptr->TIMING_CONTROL |= LINV2_TIMING_CONTROL_BT_DIV_SET(bt_div)
                        | LINV2_TIMING_CONTROL_BT_MUL_SET(bt_mul)
                        | LINV2_TIMING_CONTROL_PRESCL_SET(prescaler);

    return status_success;
}

hpm_stat_t lin_slave_configure_timing(LINV2_Type *ptr, uint32_t src_freq_in_hz)
{
    assert(src_freq_in_hz >= 8000000U);

    uint8_t prescaler;
    uint16_t bt_div;

    /** set slave mode, clean bt_div, bit_mul, prescl */
    ptr->TIMING_CONTROL = 0;
    ptr->TIMING_CONTROL |= LINV2_TIMING_CONTROL_LIN_INITIAL_MASK;
    ptr->TIMING_CONTROL &= ~LINV2_TIMING_CONTROL_LIN_INITIAL_MASK;

    prescaler = (uint8_t)(log((src_freq_in_hz / (20000U * 200U))) / log(2U) - 1U);
    bt_div = src_freq_in_hz / ((1U << (prescaler + 1U)) * 20000U);

    if ((bt_div < 200) || (bt_div >= 512)) {
        return status_invalid_argument;
    }

    /** src = 20MHz, prescaler = 1, bt_div = 250 */
    /* TODO: set wakeup_len */
    ptr->TIMING_CONTROL = LINV2_TIMING_CONTROL_BT_DIV_SET(bt_div)
                        | LINV2_TIMING_CONTROL_PRESCL_SET(prescaler);

    /* disable break_err detect */
    ptr->CONTROL_STATUS = LINV2_CONTROL_STATUS_BREAK_ERR_DIS_MASK;

    return status_success;
}

uint8_t lin_get_data_length_from_id(uint8_t id)
{
    switch (LIN_ID_DATA_LEN_GET(id)) {
    case id_data_length_2bytes:
        return 2;
    case id_data_length_2bytes_2:
        return 2;
    case id_data_length_4bytes:
        return 4;
    case id_data_length_8bytes:
        return 8;
    default:
        return 8;
    }
}

uint8_t lin_get_data_length(LINV2_Type *ptr)
{
    uint8_t data_length = 0;
    if (((ptr->DATA_LEN_ID) & LINV2_DATA_LEN_ID_DATA_LEN_MASK) == LINV2_DATA_LEN_ID_DATA_LEN_MASK) {
        data_length = lin_get_data_length_from_id(lin_get_id(ptr));
    } else {
        data_length = LINV2_DATA_LEN_ID_DATA_LEN_GET(ptr->DATA_LEN_ID);
    }
    return data_length;
}

void lin_master_transfer(LINV2_Type *ptr, lin_trans_config_t *config)
{
    uint8_t data_length;

    /** config id */
    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(lin_get_id(ptr));
        ptr->DATA_LEN_ID = LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_MASK | LINV2_DATA_LEN_ID_ID_SET(config->id);
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN_ID = LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_SET(data_length) | LINV2_DATA_LEN_ID_ID_SET(config->id);
    }

    /** sent or receive */
    ptr->CONTROL_STATUS = 0U;
    if (config->transmit) {
        ptr->CONTROL_STATUS |= LINV2_CONTROL_STATUS_TRANSMIT_MASK;
    }

    if (config->transmit) {
        for (uint8_t i = 0; i < data_length; i++) {
            ptr->DATA_BYTE[i] = *((config->data_buff)++);
        }
    }

    /** start */
    ptr->CONTROL_STATUS |= LINV2_CONTROL_STATUS_START_REQ_MASK;
}

hpm_stat_t lin_master_sent(LINV2_Type *ptr, lin_trans_config_t *config)
{
    uint32_t retry = 0;
    uint8_t data_length = 0;

    /** wait for lin inactive */
    while (lin_is_active(ptr)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    /** config id */
    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(lin_get_id(ptr));
        ptr->DATA_LEN_ID = LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_MASK | LINV2_DATA_LEN_ID_ID_SET(config->id);
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN_ID = LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_SET(data_length) | LINV2_DATA_LEN_ID_ID_SET(config->id);
    }

    ptr->CONTROL_STATUS = LINV2_CONTROL_STATUS_TRANSMIT_MASK;

    /** load data into registers */
    for (uint8_t i = 0; i < data_length; i++) {
        ptr->DATA_BYTE[i] = *((config->data_buff)++);
    }

    /** start */
    ptr->CONTROL_STATUS |=  LINV2_CONTROL_STATUS_START_REQ_MASK;

    /** waiting for lin complete */
    retry = 0;
    while (!lin_is_complete(ptr)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
        return status_timeout;
    }
    return status_success;
}

hpm_stat_t lin_master_receive(LINV2_Type *ptr, lin_trans_config_t *config)
{
    uint32_t retry = 0;
    uint8_t data_length;

    /** waiting for lin inactive */
    while (lin_is_active(ptr)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    /** config id */
    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(lin_get_id(ptr));
        ptr->DATA_LEN_ID = LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_MASK | LINV2_DATA_LEN_ID_ID_SET(config->id);
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN_ID = LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_SET(data_length) | LINV2_DATA_LEN_ID_ID_SET(config->id);
    }

    /** receive */
    ptr->CONTROL_STATUS = 0U;
    /** start */
    ptr->CONTROL_STATUS |= LINV2_CONTROL_STATUS_START_REQ_MASK;

    /** waiting for receive complete */
    retry = 0;
    while (!lin_is_complete(ptr)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
        return status_fail;
    }

    /** load register data into buffer */
    for (uint8_t i = 0; i < data_length; i++) {
        *((config->data_buff)++) = ptr->DATA_BYTE[i];
    }

    return status_success;
}

void lin_slave_transfer(LINV2_Type *ptr, lin_trans_config_t *config)
{
    uint8_t data_length;

    /** transmit or receive */
    ptr->CONTROL_STATUS &= ~LINV2_CONTROL_STATUS_TRANSMIT_MASK;
    if (config->transmit) {
        ptr->CONTROL_STATUS |= LINV2_CONTROL_STATUS_TRANSMIT_MASK;
    }

    /* clean enh_check and data_len */
    ptr->DATA_LEN_ID &= ~(LINV2_DATA_LEN_ID_ENH_CHECK_MASK | LINV2_DATA_LEN_ID_DATA_LEN_MASK);
    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(lin_get_id(ptr));
        ptr->DATA_LEN_ID |= LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_MASK;
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN_ID |= LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_SET(data_length);
    }

    if (config->transmit) {
        for (uint8_t i = 0; i < data_length; i++) {
            ptr->DATA_BYTE[i] = *((config->data_buff)++);
        }
    }

    /** data ack */
    ptr->CONTROL_STATUS |= LINV2_CONTROL_STATUS_DATA_ACK_MASK;
}

hpm_stat_t lin_slave_sent(LINV2_Type *ptr, lin_trans_config_t *config)
{
    uint32_t retry = 0;
    uint8_t data_length;

    /** waiting for lin data_req */
    while (!((ptr->CONTROL_STATUS & LINV2_CONTROL_STATUS_DATA_REQ_MASK) == LINV2_CONTROL_STATUS_DATA_REQ_MASK)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    /** transmit */
    ptr->CONTROL_STATUS = LINV2_CONTROL_STATUS_TRANSMIT_MASK;

    /* clean enh_check and data_len */
    ptr->DATA_LEN_ID &= ~(LINV2_DATA_LEN_ID_ENH_CHECK_MASK | LINV2_DATA_LEN_ID_DATA_LEN_MASK);
    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(lin_get_id(ptr));
        ptr->DATA_LEN_ID |= LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_MASK;
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN_ID |= LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_SET(data_length);
    }

    for (uint8_t i = 0; i < data_length; i++) {
        ptr->DATA_BYTE[i] = *((config->data_buff)++);
    }

    /** data ack */
    ptr->CONTROL_STATUS |= LINV2_CONTROL_STATUS_DATA_ACK_MASK;

    /** waiting for lin complete */
    retry = 0;
    while (!lin_is_complete(ptr)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
        return status_timeout;
    }
    return status_success;
}

hpm_stat_t lin_slave_receive(LINV2_Type *ptr, lin_trans_config_t *config)
{
    uint32_t retry = 0;
    uint8_t data_length;

    /** waiting for lin data_req */
    while (!((ptr->CONTROL_STATUS & LINV2_CONTROL_STATUS_DATA_REQ_MASK) == LINV2_CONTROL_STATUS_DATA_REQ_MASK)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    /** receive */
    ptr->CONTROL_STATUS = 0U;

    /* clean enh_check and data_len */
    ptr->DATA_LEN_ID &= ~(LINV2_DATA_LEN_ID_ENH_CHECK_MASK | LINV2_DATA_LEN_ID_DATA_LEN_MASK);
    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(lin_get_id(ptr));
        ptr->DATA_LEN_ID |= LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_MASK;
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN_ID |= LINV2_DATA_LEN_ID_ENH_CHECK_SET(config->enhanced_checksum) | LINV2_DATA_LEN_ID_DATA_LEN_SET(data_length);
    }

    /** data ack */
    ptr->CONTROL_STATUS |= LINV2_CONTROL_STATUS_DATA_ACK_MASK;

    /** waiting for lin complete */
    retry = 0;
    while (!lin_is_complete(ptr)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
        return status_timeout;
    }

    for (uint8_t i = 0; i < data_length; i++) {
        *((config->data_buff)++) = ptr->DATA_BYTE[i];
    }

    return status_success;
}

void lin_slave_dma_transfer(LINV2_Type *ptr, lin_trans_config_t *config)
{
    ptr->DMA_CONTROL = LINV2_DMA_CONTROL_DMA_REQ_ENABLE_MASK
                    | LINV2_DMA_CONTROL_DMA_REQ_ID_SET(config->id)
                    | LINV2_DMA_CONTROL_DMA_REQ_ID_TYPE_SET(config->transmit)
                    | LINV2_DMA_CONTROL_DMA_REQ_LEN_SET(config->data_length)
                    | LINV2_DMA_CONTROL_DMA_REQ_ENH_CHK_SET(config->enhanced_checksum);
}