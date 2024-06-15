/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_uart_lin.h"

#ifndef HPM_UART_LIN_RETRY_COUNT
#define HPM_UART_LIN_RETRY_COUNT (50000U)
#endif

#ifndef HPM_UART_LIN_BREAK_LENGTH
#define HPM_UART_LIN_BREAK_LENGTH (13U)  /* bits */
#endif

#ifndef HPM_UART_LIN_WAKEUP_LENGTH
#define HPM_UART_LIN_WAKEUP_LENGTH (400U) /* us */
#endif


uint8_t hpm_uart_lin_calculate_protected_id(uint8_t id)
{
    uint8_t id0, id1, id2, id3, id4, id5, p0, p1, pid;

    /* P0 = ID0 @ ID1 @ ID2 @ ID3 @ ID4 */
    /* P1 = !(ID1 @ ID2 @ ID3 @ ID4 @ ID5) */
    id0 = (id >> 0U) & 0x1U;
    id1 = (id >> 1U) & 0x1U;
    id2 = (id >> 2U) & 0x1U;
    id3 = (id >> 3U) & 0x1U;
    id4 = (id >> 4U) & 0x1U;
    id5 = (id >> 5U) & 0x1U;

    p0 = id0 ^ id1 ^ id2 ^ id4;
    p1 = !(id1 ^ id3 ^ id4 ^ id5);
    pid  = (p1 << 7) | (p0 << 6) | id;
    return pid;
}

static uint8_t hpm_uart_lin_calculate_checksum(uint8_t id, uint8_t *data, uint8_t length, bool enhanced_checksum)
{
    assert(length <= 8U);
    uint8_t checksum = 0;
    uint16_t temp;
    for (uint8_t i = 0; i < length; i++) {
        temp = checksum + data[i];
        checksum += data[i] + (temp >> 8U);
    }

    if (enhanced_checksum) {
        temp = checksum + id;
        checksum += id + (temp >> 8U);
    }

    checksum = ~checksum;
    return checksum;
}

static bool hpm_uart_lin_check_checksum(uint8_t id, uint8_t *data, uint8_t length, bool enhanced_checksum, uint8_t checksum)
{
    uint8_t cal_checksum;
    cal_checksum = hpm_uart_lin_calculate_checksum(id, data, length, enhanced_checksum);

    if (cal_checksum != checksum) {
        return false;
    }
    return true;
}


static void hpm_uart_lin_send_break(UART_Type *ptr, uart_lin_master_pin_ctrl_t *pin_ctrl)
{
    assert(pin_ctrl->baudrate <= 20000);

    uint32_t bit_period_us = 1000000 / pin_ctrl->baudrate;
    uint32_t break_period_us = bit_period_us * HPM_UART_LIN_BREAK_LENGTH;
    pin_ctrl->config_uart_pin_as_gpio(ptr);
    gpio_set_pin_output(pin_ctrl->ptr, pin_ctrl->tx_port, pin_ctrl->tx_pin);
    gpio_write_pin(pin_ctrl->ptr, pin_ctrl->tx_port, pin_ctrl->tx_pin, 0);
    pin_ctrl->delay_us(break_period_us);
    gpio_write_pin(pin_ctrl->ptr, pin_ctrl->tx_port, pin_ctrl->tx_pin, 1);
    pin_ctrl->delay_us(bit_period_us);
    pin_ctrl->config_uart_pin(ptr);
}

static void hpm_uart_lin_send_sync(UART_Type *ptr)
{
    uart_write_byte(ptr, 0x55); /* sync phase */
}

void hpm_uart_lin_send_wakeup(UART_Type *ptr, uart_lin_master_pin_ctrl_t *pin_ctrl)
{
    pin_ctrl->config_uart_pin_as_gpio(ptr);
    gpio_set_pin_output(pin_ctrl->ptr, pin_ctrl->tx_port, pin_ctrl->tx_pin);
    gpio_write_pin(pin_ctrl->ptr, pin_ctrl->tx_port, pin_ctrl->tx_pin, 0);
    pin_ctrl->delay_us(HPM_UART_LIN_WAKEUP_LENGTH);
    gpio_write_pin(pin_ctrl->ptr, pin_ctrl->tx_port, pin_ctrl->tx_pin, 1);
    pin_ctrl->config_uart_pin(ptr);
}

uart_lin_stat_t hpm_uart_lin_master_send_frame(uart_lin_master_config_t *config)
{
    uint32_t retry;
    UART_Type *ptr = config->ptr;
    uart_lin_data_t data = config->data;
    uint8_t pid = hpm_uart_lin_calculate_protected_id(config->id);
    uint8_t checksum = hpm_uart_lin_calculate_checksum(pid, data.buff, data.length, data.enhance_checksum);
    uint8_t send_data[11] = {0}; /* max 8 data bytes + 1 byte 0x55 + 1 byte pid + 1byte checksum */
    uint8_t length = data.length + 3;

    assert(data.length > 0);

    /* 0x55 - pid  - data - checksum */
    send_data[0] = 0x55;
    send_data[1] = pid;
    memcpy(&send_data[2], data.buff, data.length);
    send_data[data.length + 2] = checksum;

    hpm_uart_lin_send_break(ptr, &(config->pin_ctrl));

    for (uint8_t i = 0; i < length; i++) {
        retry = 0;
        while (!uart_check_status(ptr, uart_stat_tx_slot_avail)) {
            if (retry > HPM_UART_LIN_RETRY_COUNT) {
                break;
            }
            retry++;
        }

        if (retry > HPM_UART_LIN_RETRY_COUNT) {
            return uart_lin_timeout;
        }

        uart_write_byte(ptr, send_data[i]);
    }

    return uart_lin_success;
}


uart_lin_stat_t hpm_uart_lin_master_receive_frame(uart_lin_master_config_t *config)
{
    uint32_t retry = 0;
    UART_Type *ptr = config->ptr;
    uart_lin_data_t data = config->data;
    uint8_t pid = hpm_uart_lin_calculate_protected_id(config->id);
    uint8_t checksum;
    uint8_t *buff = data.buff;

    assert(data.length > 0);

    /* clear data in rx fifo */
    uart_clear_rx_fifo(ptr);

    hpm_uart_lin_send_break(ptr, &(config->pin_ctrl));

    hpm_uart_lin_send_sync(ptr);

    uart_write_byte(ptr, pid);

    /* wait for send 0x55 and pid */
    while (!uart_check_status(ptr, uart_stat_tx_slot_avail)) {
        if (retry > HPM_UART_LIN_RETRY_COUNT * 2) {
            break;
        }
        retry++;
    }

    if (retry > HPM_UART_LIN_RETRY_COUNT * 2) {
        return uart_lin_timeout;
    }

    /* wait for receive complete */
    for (uint8_t i = 0; i < data.length + 3; i++) {
        retry = 0;
        while (!uart_check_status(ptr, uart_stat_data_ready)) {
            if (retry > HPM_UART_LIN_RETRY_COUNT) {
                break;
            }
            retry++;
        }

        if (retry > HPM_UART_LIN_RETRY_COUNT) {
            return uart_lin_timeout;
        }

        if (i < 2) {
            uart_read_byte(ptr);
        } else if (i < data.length + 2) {
            *(buff++) = uart_read_byte(ptr);
        } else {
            checksum = uart_read_byte(ptr);
        }
    }

    if (!hpm_uart_lin_check_checksum(pid, data.buff, data.length, data.enhance_checksum, checksum)) {
        return uart_lin_checksum_error;
    }

    return uart_lin_success;
}

/* generate break with gpio then write 0x55 and pid into uart tx fifo */
void hpm_uart_lin_master_send_head(uart_lin_master_config_t *config)
{
    UART_Type *ptr = config->ptr;
    uint8_t pid = hpm_uart_lin_calculate_protected_id(config->id);

    /* clear data in rx fifo */
    uart_clear_rx_fifo(ptr);

    hpm_uart_lin_send_break(ptr, &(config->pin_ctrl));

    hpm_uart_lin_send_sync(ptr);

    uart_write_byte(ptr, pid);
}

/* write data into uart tx fifo including data and checksum */
void hpm_uart_lin_master_send_data(uart_lin_master_config_t *config)
{
    UART_Type *ptr = config->ptr;
    uart_lin_data_t data = config->data;

    assert(data.length > 0);

    uint8_t pid = hpm_uart_lin_calculate_protected_id(config->id);
    uint8_t checksum = hpm_uart_lin_calculate_checksum(pid, data.buff, data.length, data.enhance_checksum);

    for (uint8_t i = 0; i < data.length; i++) {
        uart_write_byte(ptr, *(data.buff++));
    }

    uart_write_byte(ptr, checksum);
}

/* call this function in rx timeout isr */
/* read data from uart rx fifo */
uart_lin_stat_t hpm_uart_lin_master_receive_data(uart_lin_master_config_t *config)
{
    UART_Type *ptr = config->ptr;
    uart_lin_data_t data = config->data;
    uint8_t pid = hpm_uart_lin_calculate_protected_id(config->id);
    uint8_t checksum = 0;
    uint8_t index = 0;
    uint8_t *buff = data.buff;

    assert(data.length > 0);

    while (uart_check_status(ptr, uart_stat_data_ready)) {
        if (index >= data.length + 3) {
            break;
        }
        if (index < 2) {
            uart_read_byte(ptr); /* read 0x55 and pid */
        } else if (index < data.length + 2) {
            *(buff++) = uart_read_byte(ptr);
        } else {
            checksum = uart_read_byte(ptr);
        }
        index++;
    }

    if (index != data.length + 3) {
        return uart_lin_frame_error;
    }

    if (!hpm_uart_lin_check_checksum(pid, data.buff, data.length, data.enhance_checksum, checksum)) {
        return uart_lin_checksum_error;
    }

    return uart_lin_success;
}

/* write data into uart tx fifo including data and checksum */
void hpm_uart_lin_slave_send_data(uart_lin_slave_config_t *config)
{
    UART_Type *ptr = config->ptr;
    uart_lin_data_t data = config->data;

    assert(data.length > 0);

    uint8_t checksum = hpm_uart_lin_calculate_checksum(config->pid, data.buff, data.length, data.enhance_checksum);

    for (uint8_t i = 0; i < data.length; i++) {
        uart_write_byte(ptr, *(data.buff++));
    }

    uart_write_byte(ptr, checksum);
}

/* read data and checksum */
uart_lin_stat_t hpm_uart_lin_slave_receive_data(uart_lin_slave_config_t *config)
{
    UART_Type *ptr = config->ptr;
    uart_lin_data_t data = config->data;

    assert(data.length > 0);

    uint8_t index = 0;
    uint8_t checksum = 0;

    /* receive data and checksum */
    while (uart_check_status(ptr, uart_stat_data_ready)) {
        if (index == data.length) {
            checksum = uart_read_byte(ptr);
            break;
        }
        *(data.buff + index++) = uart_read_byte(ptr);
    }

    if (index != data.length) {
        return uart_lin_frame_error;
    }

    if (!hpm_uart_lin_check_checksum(config->pid, data.buff, data.length, data.enhance_checksum, checksum)) {
        return uart_lin_checksum_error;
    }

    return uart_lin_success;
}