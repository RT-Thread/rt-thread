/*
 * Copyright (c) 2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_SERIAL_NOR_HOST_H
#define _HPM_SERIAL_NOR_HOST_H
#include "hpm_common.h"
#include "sfdp_def.h"

#define SERIAL_NOR_HOST_SUPPORT_SINGLE_IO_MODE             (1UL << 0)
#define SERIAL_NOR_HOST_SUPPORT_DUAL_IO_MODE               (1UL << 1)
#define SERIAL_NOR_HOST_SUPPORT_QUAD_IO_MODE               (1UL << 2)
#define SERIAL_NOR_HOST_SUPPORT_SPI_INTERFACE              (1UL << 3)
#define SERIAL_NOR_HOST_SUPPORT_DMA                        (1UL << 8)
#define SERIAL_NOR_HOST_CS_CONTROL_AUTO                    (1UL << 9)

/**
 * @brief IO mode of serial nor flash sequence
 */
typedef enum {
    single_io_mode = 0,
    dual_io_mode,
    quad_io_mode
} hpm_serial_nor_seq_io_mode_t;

/**
 * @brief number of address bits of serial nor flash sequence
 */
typedef enum {
    flash_addrlen_24bit = 0,
    flash_addrlen_32bit
} hpm_serial_nor_seq_addr_bit_t;

/**
 * @brief transfer direction serial nor flash sequence
 */
typedef enum {
    write_direction = 0,
    read_direction
} hpm_serial_nor_seq_direction_t;

/**
 * @brief information of serial nor flash
 */
typedef struct {
    uint8_t en_dev_mode_cfg;
    uint8_t sfdp_version;
    uint8_t sector_erase_cmd;
    uint8_t block_erase_cmd;
    uint32_t size_in_kbytes;
    uint16_t page_size;
    uint16_t sector_size_kbytes;
    uint16_t block_size_kbytes;
} hpm_serial_nor_info_t;

/**
 * @brief dma control param of serial nor flash host
 */
typedef struct {
    uint8_t rx_dma_ch;
    uint8_t tx_dma_ch;
    uint8_t rx_dma_req;
    uint8_t tx_dma_req;
    void *dma_base;
    void *dmamux_base;
} hpm_nor_host_dma_control_t;

/**
 * @brief param and operation of serial nor flash host
 */
typedef struct {
    uint8_t pin_or_cs_index;
    hpm_nor_host_dma_control_t dma_control;
    uint32_t clock_name;
    uint32_t frequency;
    uint32_t transfer_max_size;
    void *host_base;
    void (*set_cs)(uint32_t cs_pin, uint8_t state);
    void (*set_frequency)(void *host, uint32_t freq);
} hpm_nor_host_param_t;

/**
 * @brief spi nor read parameters structure
 */
typedef struct {
    uint8_t read_cmd;
    uint8_t data_dummy_count;
    hpm_serial_nor_seq_addr_bit_t addr_bit;
    hpm_serial_nor_seq_io_mode_t data_phase_format;
    hpm_serial_nor_seq_io_mode_t addr_phase_format;
} hpm_sfdp_read_para_t;

/**
 * @brief spi nor program parameters structure
 */
typedef struct {
    bool has_4b_addressing_inst_table;
    bool support_1_4_4_page_program;
    bool support_1_1_4_page_program;
    uint8_t page_program_cmd;
} hpm_sfdp_program_para_t;

/**
 * @brief param of serial nor flash host
 */
typedef struct {
    uint32_t flags;
    hpm_nor_host_param_t param;
    void *user_data;
} hpm_serial_nor_host_param_t;

/**
 * @brief operation sequence of serial nor flash
 *
 * @note it's include command + address(optional) + dummy(optional) + data(optional)
 *
 */
typedef struct {
    /* can choose whether to use DMA in a transfer, even if the flags has DMA*/
    uint8_t use_dma;

    struct {
        uint8_t cmd;
    } cmd_phase;

    struct {
        bool enable;
        hpm_serial_nor_seq_addr_bit_t addr_bit;
        hpm_serial_nor_seq_io_mode_t addr_io_mode;
        uint32_t addr;
    } addr_phase;

    struct {
        uint8_t dummy_count;
    } dummy_phase;

    struct {
        /* the operation direction of the data phase, it's include write and read */
        hpm_serial_nor_seq_direction_t direction;
        /* the SPI operation mode of the data phase, it's include SPI/DUAL SPI/QUAD SPI and so on */
        hpm_serial_nor_seq_io_mode_t data_io_mode;
        uint32_t len;
        uint8_t *buf;
    } data_phase;

} hpm_serial_nor_transfer_seq_t;

/**
 * @brief operation of serial nor flash host
 */
typedef struct {
    hpm_stat_t (*init)(void *host);

    hpm_stat_t (*transfer)(void *host, hpm_serial_nor_transfer_seq_t *command_seq);

    void (*set_cs)(uint32_t cs_pin, uint8_t state);

    void (*set_frequency)(void *host, uint32_t freq);

    void *user_data;
} serial_nor_host_ops_t;

/**
 * @brief serial nor flash host parameters structure
 */
typedef struct {
    hpm_serial_nor_host_param_t host_param;
    serial_nor_host_ops_t host_ops;
    void *user_data;
} hpm_serial_nor_host_t;

/**
 * @brief serial nor flash parameters structure
 */
typedef struct {
    hpm_serial_nor_host_t host;
    hpm_sfdp_read_para_t nor_read_para;
    hpm_sfdp_program_para_t nor_program_para;
    hpm_serial_nor_info_t flash_info;
} hpm_serial_nor_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief serial nor host operation is use spi operation
 * @param [in] dev  serial nor device
 * @return hpm_stat_t: status_success if success
 */
hpm_stat_t serial_nor_host_ops_use_spi(hpm_serial_nor_t *dev);
/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
