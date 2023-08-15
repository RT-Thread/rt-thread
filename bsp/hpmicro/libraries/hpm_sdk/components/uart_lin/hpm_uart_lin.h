/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef UART_LIN_H
#define UART_LIN_H

#include "hpm_clock_drv.h"
#include "hpm_gpio_drv.h"
#include "hpm_uart_drv.h"

/**
 *
 * @brief UART Lin component APIs
 * @defgroup uart_lin_interface UART component APIs
 * @ingroup io_interfaces
 * @{
 */

typedef struct uart_lin_pin {
    GPIO_Type *ptr;
    uint32_t baudrate;
    void (*config_uart_pin)(UART_Type *ptr);
    void (*config_uart_pin_as_gpio)(UART_Type *ptr);
    void (*delay_us)(uint32_t us);
    uint8_t tx_port;
    uint8_t tx_pin;
} uart_lin_master_pin_ctrl_t;

typedef struct {
    uint8_t *buff;
    uint8_t length;
    bool enhance_checksum;
} uart_lin_data_t;

typedef enum {
    uart_lin_success = 0,
    uart_lin_fail    = 1,
    uart_lin_invalid_argument = 2,
    uart_lin_timeout = 3,
    uart_lin_id_parity_error = 4,
    uart_lin_checksum_error = 5,
    uart_lin_frame_error = 6, /*<! data count error */
} uart_lin_stat_t;

typedef struct {
    UART_Type *ptr;
    uint8_t id; /* master use id */
    uart_lin_data_t data;
    uart_lin_master_pin_ctrl_t pin_ctrl;
} uart_lin_master_config_t;

typedef struct {
    UART_Type *ptr;
    uint8_t pid; /* slave use pid */
    uart_lin_data_t data;
} uart_lin_slave_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief calculate lin pid from id
 *
 * @param [in] id id value
 *
 * @return pid pid value
 */
uint8_t hpm_uart_lin_calculate_protected_id(uint8_t id);

/**
 * @brief master send lin frame, including break, sync, pid, data and checksum
 *
 * @note this function using polling way to check uart status
 *
 * @param [in] config uart_lin_master_config_t
 *
 * @return uart_lin_stat_t uart_lin_success if master send without error
 */
uart_lin_stat_t hpm_uart_lin_master_send_frame(uart_lin_master_config_t *config);

/**
 * @brief master receive lin frame. master send break, sync, pid, then receive data and checksum
 *
 * @note this function using polling way to check uart status
 *
 * @param [in] config uart_lin_master_config_t
 *
 * @return uart_lin_stat_t uart_lin_success if master receive without error
 */
uart_lin_stat_t hpm_uart_lin_master_receive_frame(uart_lin_master_config_t *config);

/**
 * @brief master send data and checksum
 *
 * @note this function write 0x55 and pid into tx fifo
 *
 * @param [in] config uart_lin_master_config_t
 */
void hpm_uart_lin_master_send_head(uart_lin_master_config_t *config);

/**
 * @brief master send data and checksum
 *
 * @note this function write data and checksum into tx fifo
 *
 * @param [in] config uart_lin_master_config_t
 */
void hpm_uart_lin_master_send_data(uart_lin_master_config_t *config);

/**
 * @brief master receive and check data&checksum
 *
 * @note this function read data and checksum already in rx fifo
 *
 * @param [in] config uart_lin_master_config_t
 *
 * @return uart_lin_stat_t uart_lin_success if receive without error
 */
uart_lin_stat_t hpm_uart_lin_master_receive_data(uart_lin_master_config_t *config);

/**
 * @brief slave send data and checksum
 *
 * @note this function write data and checksum into tx fifo
 *
 * @param [in] config uart_lin_slave_config_t
 */
void hpm_uart_lin_slave_send_data(uart_lin_slave_config_t *config);

/**
 * @brief salve receive and check data&checksum
 *
 * @note this function read data and checksum already in rx fifo
 *
 * @param [in] config uart_lin_slave_config_t
 *
 * @return uart_lin_stat_t uart_lin_success if receive without error
 */
uart_lin_stat_t hpm_uart_lin_slave_receive_data(uart_lin_slave_config_t *config);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* UART_LIN_H */

