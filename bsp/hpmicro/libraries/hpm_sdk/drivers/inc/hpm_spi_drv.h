/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SPI_DRV_H
#define HPM_SPI_DRV_H
#include "hpm_spi_regs.h"

/**
 * @brief SPI driver APIs
 * @defgroup spi_interface SPI driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief spi mode selection
 */
typedef enum {
    spi_master_mode = 0,
    spi_slave_mode
} spi_mode_selection_t;

/**
 * @brief spi clock polarity
 */
typedef enum {
    spi_sclk_low_idle = 0,
    spi_sclk_high_idle
} spi_sclk_idle_state_t;

/**
 * @brief spi clock phase
 */
typedef enum {
    spi_sclk_sampling_odd_clk_edges = 0,
    spi_sclk_sampling_even_clk_edges
} spi_sclk_sampling_clk_edges_t;

/**
 * @brief spi cs to sclk edge duration
 */
typedef enum {
    spi_cs2sclk_half_sclk_1 = 0,
    spi_cs2sclk_half_sclk_2,
    spi_cs2sclk_half_sclk_3,
    spi_cs2sclk_half_sclk_4
} spi_cs2sclk_duration_t;

/**
 * @brief spi cs high level duration
 */
typedef enum {
    spi_csht_half_sclk_1 = 0,
    spi_csht_half_sclk_2,
    spi_csht_half_sclk_3,
    spi_csht_half_sclk_4,
    spi_csht_half_sclk_5,
    spi_csht_half_sclk_6,
    spi_csht_half_sclk_7,
    spi_csht_half_sclk_8,
    spi_csht_half_sclk_9,
    spi_csht_half_sclk_10,
    spi_csht_half_sclk_11,
    spi_csht_half_sclk_12,
    spi_csht_half_sclk_13,
    spi_csht_half_sclk_14,
    spi_csht_half_sclk_15,
    spi_csht_half_sclk_16,
} spi_csht_duration_t;

/**
 * @brief spi address phase format
 */
typedef enum {
    spi_address_phase_format_single_io_mode = 0,
    spi_address_phase_format_dualquad_io_mode
} spi_addr_phase_format_t;

/**
 * @brief spi transfer mode
 */
typedef enum {
    spi_trans_write_read_together = 0,
    spi_trans_write_only,
    spi_trans_read_only,
    spi_trans_write_read,
    spi_trans_read_write,
    spi_trans_write_dummy_read,
    spi_trans_read_dummy_write,
    spi_trans_no_data,
    spi_trans_dummy_write,
    spi_trans_dummy_read
} spi_trans_mode_t;

/**
 * @brief spi data phase format
 */
typedef enum {
    spi_single_io_mode = 0,
    spi_dual_io_mode,
    spi_quad_io_mode,
} spi_data_phase_format_t;

/**
 * @brief spi token value
 */
typedef enum {
    spi_token_value_0x00 = 0,
    spi_token_value_0x69
} spi_token_value_t;

/**
 * @brief spi dummy count
 */
typedef enum {
    spi_dummy_count_1 = 0,
    spi_dummy_count_2,
    spi_dummy_count_3,
    spi_dummy_count_4
} spi_dummy_count_t;

/**
 * @brief spi master interface timing config structure
 */
typedef struct {
    uint32_t clk_src_freq_in_hz;
    uint32_t sclk_freq_in_hz;
    uint8_t cs2sclk;
    uint8_t csht;
} spi_master_timing_config_t;

/**
 * @brief spi interface timing config structure
 */
typedef struct {
    spi_master_timing_config_t master_config;
} spi_timing_config_t;

/**
 * @brief spi master transfer format config structure
 */
typedef struct {
    uint8_t addr_len_in_bytes;
} spi_master_format_config_t;

/**
 * @brief spi common format config structure
 */
typedef struct {
    uint8_t data_len_in_bits;
    bool data_merge;
    bool mosi_bidir;
    bool lsb;
    uint8_t mode;
    uint8_t cpol;
    uint8_t cpha;
} spi_common_format_config_t;

/**
 * @brief spi format config structure
 */
typedef struct {
    spi_master_format_config_t master_config;
    spi_common_format_config_t common_config;
} spi_format_config_t;

/**
 * @brief spi master transfer control config structure
 */
typedef struct {
    bool cmd_enable;
    bool addr_enable;
    uint8_t addr_phase_fmt;
    bool token_enable;
    uint8_t token_value;
} spi_master_control_config_t;

/**
 * @brief spi slave transfer control config structure
 */
typedef struct {
    bool slave_data_only;
} spi_slave_control_config_t;

/**
 * @brief spi common transfer control config structure
 */
typedef struct {
    bool tx_dma_enable;
    bool rx_dma_enable;
    uint8_t trans_mode;
    uint8_t data_phase_fmt;
    uint8_t dummy_cnt;
} spi_common_control_config_t;

/**
 * @brief spi control config structure
 */
typedef struct {
    spi_master_control_config_t master_config;
    spi_slave_control_config_t  slave_config;
    spi_common_control_config_t common_config;
} spi_control_config_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
 * @brief spi master get default timing config
 *
 * @param [out] config spi_timing_config_t
 */
void spi_master_get_default_timing_config(spi_timing_config_t *config);

/**
 * @brief spi master get default format config
 *
 * @param [out] config spi_format_config_t
 */
void spi_master_get_default_format_config(spi_format_config_t *config);

/**
 * @brief spi master get default control config
 *
 * @param [out] config spi_control_config_t
 */
void spi_master_get_default_control_config(spi_control_config_t *config);

/**
 * @brief spi slave get default format config
 *
 * @param [out] config spi_format_config_t
 */
void spi_slave_get_default_format_config(spi_format_config_t *config);

/**
 * @brief spi slave get default control config
 *
 * @param [out] config spi_control_config_t
 */
void spi_slave_get_default_control_config(spi_control_config_t *config);

/**
 * @brief spi master timing initialization
 *
 * @param [in] ptr SPI base address
 * @param [in] config spi_timing_config_t
 * @retval hpm_stat_t status_invalid_argument or status_success
 */
hpm_stat_t spi_master_timing_init(SPI_Type *ptr, spi_timing_config_t *config);

/**
 * @brief spi format initialization
 *
 * @param [in] ptr SPI base address
 * @param [in] config spi_format_config_t
 */
void spi_format_init(SPI_Type *ptr, spi_format_config_t *config);

/**
 * @brief spi transfer
 *
 * @param [in] ptr SPI base address
 * @param [in] config spi_control_config_t
 * @param [in] cmd spi transfer mode
 * @param [in] addr spi transfer target address
 * @param [in] wbuff spi sent data buff address
 * @param [in] wsize spi sent data size in byte
 * @param [in] rbuff spi receive data buff address
 * @param [in] rsize spi receive data size
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
hpm_stat_t spi_transfer(SPI_Type *ptr,
                        spi_control_config_t *config,
                        uint8_t *cmd, uint32_t *addr,
                        uint8_t *wbuff, uint32_t wsize,  uint8_t *rbuff, uint32_t rsize);

/**
 * @brief spi setup dma transfer
 *
 * @param [in] ptr SPI base address
 * @param [in] config spi_control_config_t
 * @param [in] cmd spi transfer mode
 * @param [in] addr spi transfer target address
 * @param [in] wsize spi sent data size in byte
 * @param [in] rsize spi receive data size
 * @retval hpm_stat_t status_success if spi setup dma transfer without any error
 */
hpm_stat_t spi_setup_dma_transfer(SPI_Type *ptr,
                        spi_control_config_t *config,
                        uint8_t *cmd, uint32_t *addr,
                        uint32_t wsize, uint32_t rsize);

/**
 * @brief spi wait for idle status
 *
 * @param [in] ptr SPI base address
 * @retval hpm_stat_t status_success if spi in idle status
 */
hpm_stat_t spi_wait_for_idle_status(SPI_Type *ptr);

/**
 * @brief spi wait for busy status
 *
 * @param [in] ptr SPI base address
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t spi_wait_for_busy_status(SPI_Type *ptr);

/**
 * @}
 */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_SPI_DRV_H */
