/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_lin_drv.h"

#define HPM_LIN_DRV_RETRY_COUNT (50000U)

hpm_stat_t lin_master_configure_timing(LIN_Type *ptr, lin_timing_t *timing)
{
    assert(timing->src_freq_in_hz >= 8000000U);
    assert((timing->baudrate >= 1000U) && (timing->baudrate <= 20000U));

    uint8_t prescaler, bt_mul;
    uint16_t bt_div;

    /** set master mode */
    ptr->TV |= LIN_TV_MASTER_MODE_MASK;
    ptr->TV |= LIN_TV_INITIAL_MODE_MASK;
    ptr->TV &= ~LIN_TV_INITIAL_MODE_MASK;

    bt_mul = 20000U / timing->baudrate - 1U;
    prescaler = log((timing->src_freq_in_hz / ((bt_mul + 1U) * timing->baudrate * 200U))) / log(2U) - 1U;
    bt_div = timing->src_freq_in_hz / ((1U << (prescaler + 1U)) * (bt_mul + 1U) * timing->baudrate);

    if ((bt_div < 200) || (bt_div > 512)) {
        return status_invalid_argument;
    }

    /** src =20MHz baudrate = 19.2KHz */
    /** bt_div = 260, scaler = 1, bt_mul = 0 */
    ptr->BAUDRATE_CTL_LOW = bt_div & 0xFF;
    ptr->BARDRATE_CTL_HIGH = LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_SET(bt_div >> 8U)
                             | LIN_BARDRATE_CTL_HIGH_BT_MUL_SET(bt_mul)
                             | LIN_BARDRATE_CTL_HIGH_PRESCL_SET(prescaler);

    return status_success;
}

hpm_stat_t lin_slave_configure_timing(LIN_Type *ptr, uint32_t src_freq_in_hz)
{
    assert(src_freq_in_hz >= 8000000U);

    uint8_t prescaler;
    uint16_t bt_div;

    /** set slave mode */
    ptr->TV &= ~LIN_TV_MASTER_MODE_MASK;
    ptr->TV |= LIN_TV_INITIAL_MODE_MASK;
    ptr->TV &= ~LIN_TV_INITIAL_MODE_MASK;

    prescaler = log((src_freq_in_hz / (20000U * 200U))) / log(2U) - 1U;
    bt_div = src_freq_in_hz / ((1U << (prescaler + 1U)) * 20000U);

    if ((bt_div < 200) || (bt_div > 512)) {
        return status_invalid_argument;
    }

    /** src = 20MHz, prescaler = 1, bt_div = 250 */
    ptr->BAUDRATE_CTL_LOW = bt_div & 0xFF;
    ptr->BARDRATE_CTL_HIGH = LIN_BARDRATE_CTL_HIGH_BT_DIV_HIGH_SET(bt_div >> 8U)
                             | LIN_BARDRATE_CTL_HIGH_PRESCL_SET(prescaler);

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

uint8_t lin_get_data_length(LIN_Type *ptr)
{
    uint8_t data_length = 0;
    if (((ptr->DATA_LEN) & LIN_DATA_LEN_DATA_LENGTH_MASK) == LIN_DATA_LEN_DATA_LENGTH_MASK) {
        data_length = lin_get_data_length_from_id(ptr->ID);
    } else {
        data_length = LIN_DATA_LEN_DATA_LENGTH_GET(ptr->DATA_LEN);
    }
    return data_length;
}

void lin_master_transfer(LIN_Type *ptr, lin_trans_config_t *config)
{
    uint8_t data_length;

    ptr->ID = config->id;

    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(ptr->ID);
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_MASK;
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_SET(data_length);
    }

    /** sent or receive */
    ptr->CONTROL = 0U;
    if (config->transmit) {
        ptr->CONTROL = LIN_CONTROL_TRANSMIT_MASK;
    }

    if (config->transmit) {
        for (uint8_t i = 0; i < data_length; i++) {
            ptr->DATABYTE[i] = *((config->data_buff)++);
        }
    }

    /** start */
    ptr->CONTROL |= LIN_CONTROL_START_REQ_MASK;
}

hpm_stat_t lin_master_sent(LIN_Type *ptr, lin_trans_config_t *config)
{
    uint32_t retry = 0;
    uint8_t data_length = 0;

    /** lin active */
    while (((ptr->STATE & LIN_STATE_LIN_ACTIVE_MASK) == LIN_STATE_LIN_ACTIVE_MASK)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    ptr->ID = config->id;

    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(ptr->ID);
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_MASK;
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_SET(data_length);
    }

    ptr->CONTROL = LIN_CONTROL_TRANSMIT_MASK;

    /** load data into registers */
    for (uint8_t i = 0; i < data_length; i++) {
        ptr->DATABYTE[i] = *((config->data_buff)++);
    }

    /** start */
    ptr->CONTROL |= LIN_CONTROL_START_REQ_MASK;

    /**  lin complete */
    retry = 0;
    while (!((ptr->STATE & LIN_STATE_COMPLETE_MASK) == LIN_STATE_COMPLETE_MASK)) {
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

hpm_stat_t lin_master_receive(LIN_Type *ptr, lin_trans_config_t *config)
{
    uint32_t retry = 0;
    uint8_t data_length;

    /** lin active */
    while (((ptr->STATE & LIN_STATE_LIN_ACTIVE_MASK) == LIN_STATE_LIN_ACTIVE_MASK)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    ptr->ID = config->id;

    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(ptr->ID);
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_MASK;
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_SET(data_length);
    }

    /** receive */
    ptr->CONTROL = 0U;
    /** start */
    ptr->CONTROL |= LIN_CONTROL_START_REQ_MASK;

    /** waiting for receive complete */
    retry = 0;
    while (!((ptr->STATE & LIN_STATE_COMPLETE_MASK) == LIN_STATE_COMPLETE_MASK)) {
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
        *((config->data_buff)++) = ptr->DATABYTE[i];
    }

    return status_success;
}

void lin_slave_transfer(LIN_Type *ptr, lin_trans_config_t *config)
{
    uint8_t data_length;

    /** transmit or receive */
    ptr->CONTROL = LIN_CONTROL_TRANSMIT_SET(config->transmit);

    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(ptr->ID);
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_MASK;
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_SET(data_length);
    }

    if (config->transmit) {
        for (uint8_t i = 0; i < data_length; i++) {
            ptr->DATABYTE[i] = *((config->data_buff)++);
        }
    }

    /** data ack */
    ptr->CONTROL |= LIN_CONTROL_DATA_ACK_MASK;
}

hpm_stat_t lin_slave_sent(LIN_Type *ptr, lin_trans_config_t *config)
{
    uint32_t retry = 0;
    uint8_t data_length;

    /** lin data_req */
    /** lin active? */
    while (((ptr->STATE & LIN_STATE_DATA_REQ_MASK) == LIN_STATE_DATA_REQ_MASK)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    /** transmit */
    ptr->CONTROL = LIN_CONTROL_TRANSMIT_MASK;

    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(ptr->ID);
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_MASK;
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_SET(data_length);
    }

    for (uint8_t i = 0; i < data_length; i++) {
        ptr->DATABYTE[i] = *((config->data_buff)++);
    }

    /** data ack */
    ptr->CONTROL |= LIN_CONTROL_DATA_ACK_MASK;

    /** lin complete */
    retry = 0;
    while (!((ptr->STATE & LIN_STATE_COMPLETE_MASK) == LIN_STATE_COMPLETE_MASK)) {
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

hpm_stat_t lin_slave_receive(LIN_Type *ptr, lin_trans_config_t *config)
{
    uint32_t retry = 0;
    uint8_t data_length;

    /** lin data_req */
    while (((ptr->STATE & LIN_STATE_DATA_REQ_MASK) == LIN_STATE_DATA_REQ_MASK)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT) {
        return status_timeout;
    }

    /** receive */
    ptr->CONTROL = 0U;

    if (config->data_length_from_id) {
        data_length = lin_get_data_length_from_id(ptr->ID);
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_MASK;
    } else {
        data_length = config->data_length;
        ptr->DATA_LEN = LIN_DATA_LEN_ENH_CHECK_SET(config->enhanced_checksum) | LIN_DATA_LEN_DATA_LENGTH_SET(data_length);
    }

    /** data ack */
    ptr->CONTROL |= LIN_CONTROL_DATA_ACK_MASK;

    /** lin complete */
    retry = 0;
    while (!((ptr->STATE & LIN_STATE_COMPLETE_MASK) == LIN_STATE_COMPLETE_MASK)) {
        if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
            break;
        }
        retry++;
    }

    if (retry > HPM_LIN_DRV_RETRY_COUNT * 8) {
        return status_timeout;
    }

    for (uint8_t i = 0; i < data_length; i++) {
        *((config->data_buff)++) = ptr->DATABYTE[i];
    }

    return status_success;
}
