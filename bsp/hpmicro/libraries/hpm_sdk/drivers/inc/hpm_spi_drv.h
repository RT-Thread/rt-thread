/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_SPI_DRV_H
#define HPM_SPI_DRV_H
#include "hpm_spi_regs.h"
#include "hpm_soc_feature.h"

/**
 * @brief SPI driver APIs
 * @defgroup spi_interface SPI driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief spi dma enable
 */
typedef enum {
    spi_tx_dma_enable = SPI_CTRL_TXDMAEN_MASK,
    spi_rx_dma_enable = SPI_CTRL_RXDMAEN_MASK
} spi_dma_enable_t;

/**
 * @brief spi interrupt mask
 */
typedef enum {
    spi_rx_fifo_overflow_int  = SPI_INTREN_RXFIFOORINTEN_MASK,
    spi_tx_fifo_underflow_int = SPI_INTREN_TXFIFOURINTEN_MASK,
    spi_rx_fifo_threshold_int = SPI_INTREN_RXFIFOINTEN_MASK,
    spi_tx_fifo_threshold_int = SPI_INTREN_TXFIFOINTEN_MASK,
    spi_end_int               = SPI_INTREN_ENDINTEN_MASK,
    spi_slave_cmd_int         = SPI_INTREN_SLVCMDEN_MASK,
} spi_interrupt_t;

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
 * @param [in,out] cmd spi transfer command address
 * @param [in] addr spi transfer target address
 * @param [in] wbuff spi sent data buff address
 * @param [in] wcount spi sent data count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @param [out] rbuff spi receive data buff address
 * @param [in] rcount spi receive data count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
hpm_stat_t spi_transfer(SPI_Type *ptr,
                        spi_control_config_t *config,
                        uint8_t *cmd, uint32_t *addr,
                        uint8_t *wbuff, uint32_t wcount,  uint8_t *rbuff, uint32_t rcount);

/**
 * @brief spi setup dma transfer
 *
 * @param [in] ptr SPI base address
 * @param [in] config spi_control_config_t
 * @param [in] cmd spi transfer command address
 * @param [in] addr spi transfer target address
 * @param [in] wcount spi sent data count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @param [in] rcount spi receive data count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi setup dma transfer without any error
 */
hpm_stat_t spi_setup_dma_transfer(SPI_Type *ptr,
                        spi_control_config_t *config,
                        uint8_t *cmd, uint32_t *addr,
                        uint32_t wcount, uint32_t rcount);

/**
 * @brief spi wait for idle status
 *
 * @note on slave mode, if CS signal is asserted, take it as busy; if SPI CS signal is de-asserted, take it as idle.
 *
 * @param [in] ptr SPI base address
 * @retval hpm_stat_t status_success if spi in idle status
 */
hpm_stat_t spi_wait_for_idle_status(SPI_Type *ptr);

/**
 * @brief spi wait for busy status
 *
 * @note on slave mode, if CS signal is asserted, take it as busy; if SPI CS signal is de-asserted, take it as idle.
 *
 * @param [in] ptr SPI base address
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t spi_wait_for_busy_status(SPI_Type *ptr);

/**
 * @brief SPI set TX FIFO threshold
 *
 * This function configures SPI TX FIFO threshold.
 *
 * @param ptr SPI base address.
 * @param threshold The FIFO threshold value, the value should not greater than FIFO size.
 */
static inline void spi_set_tx_fifo_threshold(SPI_Type *ptr, uint32_t threshold)
{
    ptr->CTRL = (ptr->CTRL & ~SPI_CTRL_TXTHRES_MASK) | SPI_CTRL_TXTHRES_SET(threshold);
}

/**
 * @brief SPI set RX FIFO threshold
 *
 * This function configures SPI RX FIFO threshold.
 *
 * @param ptr SPI base address.
 * @param threshold The FIFO threshold value, the value should not greater than FIFO size.
 */
static inline void spi_set_rx_fifo_threshold(SPI_Type *ptr, uint32_t threshold)
{
    ptr->CTRL = (ptr->CTRL & ~SPI_CTRL_RXTHRES_MASK) | SPI_CTRL_RXTHRES_SET(threshold);
}

/**
 * @brief Enables the SPI DMA request.
 *
 * This function configures the Rx and Tx DMA mask of the SPI. The parameters are base and a DMA mask.
 *
 * @param ptr SPI base address.
 * @param mask The dma enable mask; Use the spi_dma_enable_t.
 */
static inline void spi_enable_dma(SPI_Type *ptr, uint32_t mask)
{
    ptr->CTRL |= mask;
}

/*!
 * @brief Disables the SPI DMA request.
 *
 * This function configures the Rx and Tx DMA mask of the SPI.  The parameters are base and a DMA mask.
 *
 * @param ptr SPI base address.
 * @param mask The dma enable mask; Use the spi_dma_enable_t.
 */
static inline void spi_disable_dma(SPI_Type *ptr, uint32_t mask)
{
    ptr->CTRL &= ~mask;
}

/**
 * @brief Get the SPI interrupt status.
 *
 * This function gets interrupt status of the SPI.
 *
 * @param ptr SPI base address.
 * @retval SPI interrupt status register value
 */
static inline uint32_t spi_get_interrupt_status(SPI_Type *ptr)
{
    return ptr->INTRST;
}

/**
 * @brief Clear the SPI interrupt status.
 *
 * This function clears interrupt status of the SPI.
 *
 * @param ptr SPI base address.
 * @param mask The interrupt mask; Use the spi_interrupt_t.
 *
 */
static inline void spi_clear_interrupt_status(SPI_Type *ptr, uint32_t mask)
{
    /* write 1 to clear */
    ptr->INTRST = mask;
}

/**
 * @brief Enables the SPI interrupt.
 *
 * This function configures interrupt of the SPI. The parameters are base and a interrupt mask.
 *
 * @param ptr SPI base address.
 * @param mask The interrupt mask; Use the spi_interrupt_t.
 */
static inline void spi_enable_interrupt(SPI_Type *ptr, uint32_t mask)
{
    ptr->INTREN |= mask;
}

/*!
 * @brief Disables the SPI interrupt.
 *
 * This function configures interrupt of the SPI. The parameters are base and a interrupt mask.
 *
 * @param ptr SPI base address.
 * @param mask The interrupt mask; Use the spi_interrupt_t.
 */
static inline void spi_disable_interrupt(SPI_Type *ptr, uint32_t mask)
{
    ptr->INTREN &= ~mask;
}

/**
 * @brief spi write and read data
 *
 * @note Call this function after SPI CONTROL is configured by spi_control_init.
 * The order of reading and writing is controlled by spi_control_init.
 *
 * @param [in] ptr SPI base address
 * @param [in] data_len_in_bytes data length in bytes
 * @param [in] wbuff spi sent data buff address
 * @param [in] wcount spi sent data count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @param [out] rbuff spi receive data buff address
 * @param [in] rcount spi receive data count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
hpm_stat_t spi_write_read_data(SPI_Type *ptr, uint8_t data_len_in_bytes, uint8_t *wbuff, uint32_t wcount, uint8_t *rbuff, uint32_t rcount);

/**
 * @brief spi read data
 *
 * @note Call this function after SPI CONTROL is configured by spi_control_init.
 *
 * @param [in] ptr SPI base address
 * @param [in] data_len_in_bytes data length in bytes
 * @param [out] buff spi receive data buff address
 * @param [in] count spi receive data count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
hpm_stat_t spi_read_data(SPI_Type *ptr, uint8_t data_len_in_bytes, uint8_t *buff, uint32_t count);

/**
 * @brief spi write data
 *
 * @note Call this function after SPI CONTROL is configured by spi_control_init.
 *
 * @param [in] ptr SPI base address
 * @param [in] data_len_in_bytes data length in bytes
 * @param [in] buff spi sent data buff address
 * @param [in] count spi sent data count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
hpm_stat_t spi_write_data(SPI_Type *ptr, uint8_t data_len_in_bytes, uint8_t *buff, uint32_t count);

/**
 * @brief spi write command
 *
 * Writing operations on this register will trigger SPI transfers, call this function on master mode.
 *
 * @param [in] ptr SPI base address
 * @param [in] mode spi mode, use the spi_mode_selection_t
 * @param [in] config point to spi_control_config_t
 * @param [in] cmd command data address
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
hpm_stat_t spi_write_command(SPI_Type *ptr, spi_mode_selection_t mode, spi_control_config_t *config, uint8_t *cmd);

/**
 * @brief spi read command
 *
 * On slave mode, the command field of the last received SPI transaction is stored in this SPI Command Register
 *
 * @param [in] ptr SPI base address
 * @param [in] mode spi mode, use the spi_mode_selection_t
 * @param [in] config point to spi_control_config_t
 * @param [out] cmd command data address
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
hpm_stat_t spi_read_command(SPI_Type *ptr, spi_mode_selection_t mode, spi_control_config_t *config, uint8_t *cmd);

/**
 * @brief spi write address
 *
 * @note Call this function on master mode.
 *
 * @param [in] ptr SPI base address
 * @param [in] mode spi mode, use the spi_mode_selection_t
 * @param [in] config point to spi_control_config_t
 * @param [in] addr point to address
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
hpm_stat_t spi_write_address(SPI_Type *ptr, spi_mode_selection_t mode, spi_control_config_t *config, uint32_t *addr);

/**
 * @brief spi control initialization
 *
 * @param [in] ptr SPI base address
 * @param [in] config point to spi_control_config_t
 * @param [in] wcount spi sent data count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @param [in] rcount spi receive count, not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
hpm_stat_t spi_control_init(SPI_Type *ptr, spi_control_config_t *config, uint32_t wcount, uint32_t rcount);

/**
 * @brief Get the SPI data length in bits.
 *
 * @param ptr SPI base address.
 * @retval SPI data length in bits
 */
static inline uint8_t spi_get_data_length_in_bits(SPI_Type *ptr)
{
    return ((ptr->TRANSFMT & SPI_TRANSFMT_DATALEN_MASK) >> SPI_TRANSFMT_DATALEN_SHIFT) + 1;
}

/**
 * @brief Get the SPI data length in bytes.
 *
 * @param ptr SPI base address.
 * @retval SPI data length in bytes
 */
static inline uint8_t spi_get_data_length_in_bytes(SPI_Type *ptr)
{
    return ((spi_get_data_length_in_bits(ptr) + 7U) / 8U);
}

/**
 * @brief SPI get active status.
 *
 * @param ptr SPI base address.
 * @retval bool true for active, false for inactive
 */
static inline bool spi_is_active(SPI_Type *ptr)
{
    return ((ptr->STATUS & SPI_STATUS_SPIACTIVE_MASK) == SPI_STATUS_SPIACTIVE_MASK) ? true : false;
}

/**
 * @brief SPI enable tx dma
 *
 * @param ptr SPI base address
 */
static inline void spi_enable_tx_dma(SPI_Type *ptr)
{
    ptr->CTRL |= SPI_CTRL_TXDMAEN_MASK;
}

/**
 * @brief SPI disable tx dma
 *
 * @param ptr SPI base address
 */
static inline void spi_disable_tx_dma(SPI_Type *ptr)
{
    ptr->CTRL &= ~SPI_CTRL_TXDMAEN_MASK;
}

/**
 * @brief SPI enable rx dma
 *
 * @param ptr SPI base address
 */
static inline void spi_enable_rx_dma(SPI_Type *ptr)
{
    ptr->CTRL |= SPI_CTRL_RXDMAEN_MASK;
}

/**
 * @brief SPI disable rx dma
 *
 * @param ptr SPI base address
 */
static inline void spi_disable_rx_dma(SPI_Type *ptr)
{
    ptr->CTRL &= ~SPI_CTRL_RXDMAEN_MASK;
}

/**
 * @brief SPI slave get sent data count
 *
 * @param ptr SPI base address
 * @retval uint32_t data count
 */
static inline uint32_t spi_slave_get_sent_data_count(SPI_Type *ptr)
{
    return SPI_SLVDATACNT_WCNT_GET(ptr->SLVDATACNT);
}

/**
 * @brief SPI slave get received data count
 *
 * @param ptr SPI base address
 * @retval uint32_t data count
 */
static inline uint32_t spi_slave_get_received_data_count(SPI_Type *ptr)
{
    return SPI_SLVDATACNT_RCNT_GET(ptr->SLVDATACNT);
}

/**
 * @brief set spi clock phase
 *
 * @param [in] ptr SPI base address
 * @param [in] clock_phase clock phase enum
 */
static inline void spi_set_clock_phase(SPI_Type *ptr, spi_sclk_sampling_clk_edges_t clock_phase)
{
    ptr->TRANSCTRL |= SPI_TRANSFMT_CPHA_SET(clock_phase);
}

/**
 * @brief get spi clock phase
 *
 * @param [in] ptr SPI base address
 * @retval spi_sclk_sampling_clk_edges_t spi_sclk_sampling_odd_clk_edges if CPHA is 0
 */
static inline spi_sclk_sampling_clk_edges_t spi_get_clock_phase(SPI_Type *ptr)
{
    return SPI_TRANSFMT_CPHA_GET(ptr->TRANSCTRL);
}

/**
 * @brief set spi clock polarity
 *
 * @param [in] ptr SPI base address
 * @param [in] clock_polarity clock polarity enum
 */
static inline void spi_set_clock_polarity(SPI_Type *ptr, spi_sclk_idle_state_t clock_polarity)
{
    ptr->TRANSCTRL |= SPI_TRANSFMT_CPOL_SET(clock_polarity);
}

/**
 * @brief get spi clock phase
 *
 * @param [in] ptr SPI base address
 * @retval spi_sclk_idle_state_t spi_sclk_low_idle if CPOL is 0
 */
static inline spi_sclk_idle_state_t spi_get_clock_polarity(SPI_Type *ptr)
{
    return SPI_TRANSFMT_CPOL_GET(ptr->TRANSCTRL);
}

/**
 * @brief set spi the length of each data unit in bits
 *
 * @param [in] nbit the actual bits number of a data
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
static inline hpm_stat_t spi_set_data_bits(SPI_Type *ptr, uint8_t nbits)
{
    if (nbits > 32) {
        return status_invalid_argument;
    } else {
        ptr->TRANSFMT |= SPI_TRANSFMT_DATALEN_SET(nbits - 1);
        return status_success;
    }
}

/**
 * @brief SPI transmit fifo reset
 *
 * @param ptr SPI base address
 */
static inline void spi_transmit_fifo_reset(SPI_Type *ptr)
{
    ptr->CTRL |= SPI_CTRL_TXFIFORST_MASK;
}

/**
 * @brief SPI receive fifo reset
 *
 * @param ptr SPI base address
 */
static inline void spi_receive_fifo_reset(SPI_Type *ptr)
{
    ptr->CTRL |= SPI_CTRL_RXFIFORST_MASK;
}

/**
 * @brief SPI reset
 *
 * @param ptr SPI base address
 */
static inline void spi_reset(SPI_Type *ptr)
{
    ptr->CTRL |= SPI_CTRL_SPIRST_MASK;
}
/**
 * @}
 */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_SPI_DRV_H */
