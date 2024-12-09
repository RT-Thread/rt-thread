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

typedef enum {
    msb_first = 0,
    lsb_first,
} spi_shift_direction_t;

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
#if defined(HPM_IP_FEATURE_SPI_CS_SELECT) && (HPM_IP_FEATURE_SPI_CS_SELECT == 1)
    uint8_t cs_index;
#endif
} spi_common_control_config_t; /*!< value in spi_cs_index_t */

/**
 * @brief spi control config structure
 */
typedef struct {
    spi_master_control_config_t master_config;
    spi_slave_control_config_t  slave_config;
    spi_common_control_config_t common_config;
} spi_control_config_t;

#if defined(HPM_IP_FEATURE_SPI_CS_SELECT) && (HPM_IP_FEATURE_SPI_CS_SELECT == 1)
typedef enum {
    spi_cs_0 = 1,
    spi_cs_1 = 2,
    spi_cs_2 = 4,
    spi_cs_3 = 8,
} spi_cs_index_t;
#endif

typedef enum {
    addrlen_8bit = 0,
    addrlen_16bit,
    addrlen_24bit,
    addrlen_32bit
} spi_address_len_t;

#if defined(HPM_IP_FEATURE_SPI_SUPPORT_DIRECTIO) && (HPM_IP_FEATURE_SPI_SUPPORT_DIRECTIO == 1)
typedef enum {
    hold_pin = 0,
    wp_pin,
    miso_pin,
    mosi_pin,
    sclk_pin,
    cs_pin
} spi_directio_pin_t;

#endif



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
#if defined(HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT) && (HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT == 1)
    return ptr->SLVDATAWCNT;
#else
    return SPI_SLVDATACNT_WCNT_GET(ptr->SLVDATACNT);
#endif
}

/**
 * @brief SPI slave get received data count
 *
 * @param ptr SPI base address
 * @retval uint32_t data count
 */
static inline uint32_t spi_slave_get_received_data_count(SPI_Type *ptr)
{
#if defined(HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT) && (HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT == 1)
    return ptr->SLVDATARCNT;
#else
    return SPI_SLVDATACNT_RCNT_GET(ptr->SLVDATACNT);
#endif
}

/**
 * @brief set spi clock phase
 *
 * @param [in] ptr SPI base address
 * @param [in] clock_phase clock phase enum
 */
static inline void spi_set_clock_phase(SPI_Type *ptr, spi_sclk_sampling_clk_edges_t clock_phase)
{
    ptr->TRANSFMT = (ptr->TRANSFMT & ~SPI_TRANSFMT_CPHA_MASK) | SPI_TRANSFMT_CPHA_SET(clock_phase);
}

/**
 * @brief get spi clock phase
 *
 * @param [in] ptr SPI base address
 * @retval spi_sclk_sampling_clk_edges_t spi_sclk_sampling_odd_clk_edges if CPHA is 0
 */
static inline spi_sclk_sampling_clk_edges_t spi_get_clock_phase(SPI_Type *ptr)
{
    return (spi_sclk_sampling_clk_edges_t)SPI_TRANSFMT_CPHA_GET(ptr->TRANSFMT);
}

/**
 * @brief set spi clock polarity
 *
 * @param [in] ptr SPI base address
 * @param [in] clock_polarity clock polarity enum
 */
static inline void spi_set_clock_polarity(SPI_Type *ptr, spi_sclk_idle_state_t clock_polarity)
{
    ptr->TRANSFMT = (ptr->TRANSFMT & ~SPI_TRANSFMT_CPOL_MASK) | SPI_TRANSFMT_CPOL_SET(clock_polarity);
}

/**
 * @brief get spi clock phase
 *
 * @param [in] ptr SPI base address
 * @retval spi_sclk_idle_state_t spi_sclk_low_idle if CPOL is 0
 */
static inline spi_sclk_idle_state_t spi_get_clock_polarity(SPI_Type *ptr)
{
    return (spi_sclk_idle_state_t)SPI_TRANSFMT_CPOL_GET(ptr->TRANSFMT);
}

/**
 * @brief set spi the length of each data unit in bits
 *
 * @param [in] ptr SPI base address
 * @param [in] nbits the actual bits number of a data
 * @retval hpm_stat_t status_success if spi transfer without any error
 */
static inline hpm_stat_t spi_set_data_bits(SPI_Type *ptr, uint8_t nbits)
{
    if (nbits > 32) {
        return status_invalid_argument;
    } else {
        ptr->TRANSFMT = (ptr->TRANSFMT & ~SPI_TRANSFMT_DATALEN_MASK) | SPI_TRANSFMT_DATALEN_SET(nbits - 1);
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
 * @brief set spi the length of address
 *
 * @param [in] ptr SPI base address
 * @param [in] addrlen address lenth enum
 */
static inline void spi_set_address_len(SPI_Type *ptr, spi_address_len_t addrlen)
{
    ptr->TRANSFMT = (ptr->TRANSFMT & ~SPI_TRANSFMT_ADDRLEN_MASK) | SPI_TRANSFMT_ADDRLEN_SET(addrlen);
}

/**
 * @brief   Enable SPI data merge
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_enable_data_merge(SPI_Type *ptr)
{
    ptr->TRANSFMT |= SPI_TRANSFMT_DATAMERGE_MASK;
}

/**
 * @brief   Disable SPI data merge
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_disable_data_merge(SPI_Type *ptr)
{
    ptr->TRANSFMT &= ~SPI_TRANSFMT_DATAMERGE_MASK;
}

#if defined(HPM_IP_FEATURE_SPI_SUPPORT_DIRECTIO) && (HPM_IP_FEATURE_SPI_SUPPORT_DIRECTIO == 1)
/**
 * @brief enable specific pin output for spi directio
 *
 * @note must be used spi_enable_directio API before enable output function
 *
 * @param [in] ptr SPI base address
 * @param [in] pin spi_directio_pin_t enum
 */
hpm_stat_t spi_directio_enable_output(SPI_Type *ptr, spi_directio_pin_t pin);

/**
 * @brief disable specific pin output for spi directio
 *
 * @param [in] ptr SPI base address
 * @param [in] pin spi_directio_pin_t enum
 */
hpm_stat_t spi_directio_disable_output(SPI_Type *ptr, spi_directio_pin_t pin);

/**
 * @brief write specified pin level  for spi directio
 *
 * @param [in] ptr SPI base address
 * @param [in] pin spi_directio_pin_t enum
 * @param [in] high Pin level set to high when it is set to true
 */
hpm_stat_t spi_directio_write(SPI_Type *ptr, spi_directio_pin_t pin, bool high);

/**
 * @brief   Read specified pin level for spi directio
 *
 * @param [in] ptr SPI base address
 * @param pin spi_directio_pin_t enum
 *
 * @return Pin status
 */
uint8_t spi_directio_read(SPI_Type *ptr, spi_directio_pin_t pin);

/**
 * @brief   Enable SPI directIO control function
 *
 * @note if SPI transmission is required, the function must be disable
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_enable_directio(SPI_Type *ptr)
{
    ptr->DIRECTIO |= SPI_DIRECTIO_DIRECTIOEN_MASK;
}

/**
 * @brief   Disable SPI directIO control function
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_disable_directio(SPI_Type *ptr)
{
    ptr->DIRECTIO &= ~SPI_DIRECTIO_DIRECTIOEN_MASK;
}

/**
 * @brief  get whether spi directio function is enabled
 *
 * @param [in] ptr SPI base address
 *
 * @return if pi directio function is enable, it will return 1
 */
static inline uint8_t spi_get_directio_enable_status(SPI_Type *ptr)
{
    return SPI_DIRECTIO_DIRECTIOEN_GET(ptr->DIRECTIO);
}

#endif

/**
 * @brief  Get valid data size in receive FIFO
 *
 * @param [in] ptr SPI base address
 *
 * @return rx fifo valid data size
 */
static inline uint8_t spi_get_rx_fifo_valid_data_size(SPI_Type *ptr)
{
    return ((SPI_STATUS_RXNUM_7_6_GET(ptr->STATUS) << 5) | SPI_STATUS_RXNUM_5_0_GET(ptr->STATUS));
}

/**
 * @brief  Get valid data size in transmit FIFO
 *
 * @param [in] ptr SPI base address
 *
 * @return tx fifo valid data size
 */
static inline uint8_t spi_get_tx_fifo_valid_data_size(SPI_Type *ptr)
{
    return ((SPI_STATUS_TXNUM_7_6_GET(ptr->STATUS) << 5) | SPI_STATUS_TXNUM_5_0_GET(ptr->STATUS));
}

/**
 * @brief  Get SPI RXFIFO size
 *
 * @param [in] ptr SPI base address
 *
 * @return RXFIFO size, the unit is word
 */
static inline uint8_t spi_get_rx_fifo_size(SPI_Type *ptr)
{
    uint8_t size = SPI_CONFIG_RXFIFOSIZE_GET(ptr->CONFIG);
    return (2 << size);
}

/**
 * @brief  Get SPI TXFIFO size
 *
 * @param [in] ptr SPI base address
 *
 * @return TXFIFO size, the unit is word
 */
static inline uint8_t spi_get_tx_fifo_size(SPI_Type *ptr)
{
    uint8_t size = SPI_CONFIG_TXFIFOSIZE_GET(ptr->CONFIG);
    return (2 << size);
}

/**
 * @brief SPI slave enable only date mode
 *
 * @note This mode only works in the uni-directional regular (single) mode
 * @param [in] ptr SPI base address
 */
static inline void spi_slave_enable_data_only(SPI_Type *ptr)
{
    ptr->TRANSCTRL |= SPI_TRANSCTRL_SLVDATAONLY_MASK;
}

/**
 * @brief SPI slave disable only date mode
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_slave_disable_data_only(SPI_Type *ptr)
{
    ptr->TRANSCTRL &= ~SPI_TRANSCTRL_SLVDATAONLY_MASK;
}

/**
 * @brief SPI master enable command phase
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_master_enable_command_phase(SPI_Type *ptr)
{
    ptr->TRANSCTRL |= SPI_TRANSCTRL_CMDEN_MASK;
}

/**
 * @brief SPI master disable command phase
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_master_disable_command_phase(SPI_Type *ptr)
{
    ptr->TRANSCTRL &= ~SPI_TRANSCTRL_CMDEN_MASK;
}

/**
 * @brief SPI master enable address phase
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_master_enable_address_phase(SPI_Type *ptr)
{
    ptr->TRANSCTRL |= SPI_TRANSCTRL_ADDREN_MASK;
}

/**
 * @brief SPI master disable address phase
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_master_disable_address_phase(SPI_Type *ptr)
{
    ptr->TRANSCTRL &= ~SPI_TRANSCTRL_ADDREN_MASK;
}

/**
 * @brief SPI master set address phase format
 *
 * @param [in] ptr SPI base address
 * @param [in] format spi_addr_phase_format_t enum
 */
static inline void spi_master_set_address_phase_format(SPI_Type *ptr, spi_addr_phase_format_t format)
{
    ptr->TRANSCTRL = (ptr->TRANSCTRL & ~SPI_TRANSCTRL_ADDRFMT_MASK) | SPI_TRANSCTRL_ADDRFMT_SET(format);
}

/**
 * @brief SPI master set transfer mode
 *
 * @param [in] ptr SPI base address
 * @param [in] mode spi_trans_mode_t enum
 */
static inline void spi_set_transfer_mode(SPI_Type *ptr, spi_trans_mode_t mode)
{
    ptr->TRANSCTRL = (ptr->TRANSCTRL & ~SPI_TRANSCTRL_TRANSMODE_MASK) | SPI_TRANSCTRL_TRANSMODE_SET(mode);
}

/**
 * @brief SPI master enable token transfer
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_master_enable_token_transfer(SPI_Type *ptr)
{
    ptr->TRANSCTRL |= SPI_TRANSCTRL_TOKENEN_MASK;
}

/**
 * @brief SPI master disable token transfer
 *
 * @param [in] ptr SPI base address
 */
static inline void spi_master_disable_token_transfer(SPI_Type *ptr)
{
    ptr->TRANSCTRL &= ~SPI_TRANSCTRL_TOKENEN_MASK;
}

/**
 * @brief SPI master set transfer count for write data
 *
 * @param [in] ptr SPI base address
 * @param [in] count the number of units of data to be transmitted to the SPI bus from the Data
 */
static inline void spi_set_write_data_count(SPI_Type *ptr, uint32_t count)
{
#if defined(HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT) && (HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT == 1)
    ptr->WR_TRANS_CNT = (count - 1);
#else
    ptr->TRANSCTRL = (ptr->TRANSCTRL & ~SPI_TRANSCTRL_WRTRANCNT_MASK) | SPI_TRANSCTRL_WRTRANCNT_SET(count - 1);
#endif
}

/**
 * @brief SPI master set transfer count for read data
 *
 * @param [in] ptr SPI base address
 * @param [in] count  the number of units of data to be received from SPI bus and stored to the Data
 */
static inline void spi_set_read_data_count(SPI_Type *ptr, uint32_t count)
{
#if defined(HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT) && (HPM_IP_FEATURE_SPI_NEW_TRANS_COUNT == 1)
    ptr->RD_TRANS_CNT = (count - 1);
#else
    ptr->TRANSCTRL = (ptr->TRANSCTRL & ~SPI_TRANSCTRL_RDTRANCNT_MASK) | SPI_TRANSCTRL_RDTRANCNT_SET(count - 1);
#endif
}

/**
 * @brief SPI master set the value of the one-byte special token following the address phase for SPI read transfers
 *
 * @param [in] ptr SPI base address
 * @param [in] value spi_token_value_t enum
 */
static inline void spi_master_set_token_value(SPI_Type *ptr, spi_token_value_t value)
{
    ptr->TRANSCTRL = (ptr->TRANSCTRL & ~SPI_TRANSCTRL_TOKENVALUE_MASK) | SPI_TRANSCTRL_TOKENVALUE_SET(value);
}

/**
 * @brief SPI master set dummy data count
 *
 * @param [in] ptr SPI base address
 * @param [in] count spi_dummy_count_t enum
 */
static inline void spi_set_dummy_count(SPI_Type *ptr, spi_dummy_count_t count)
{
    ptr->TRANSCTRL = (ptr->TRANSCTRL & ~SPI_TRANSCTRL_DUMMYCNT_MASK) | SPI_TRANSCTRL_DUMMYCNT_SET(count);
}

/**
 * @brief SPI master set the minimum time between the edges of SPI CS and the edges of SCLK
 *
 * @param [in] ptr SPI base address
 * @param [in] duration spi_cs2sclk_duration_t enum
 */
static inline void spi_master_set_cs2sclk_timing(SPI_Type *ptr, spi_cs2sclk_duration_t duration)
{
    ptr->TIMING = (ptr->TIMING & ~SPI_TIMING_CS2SCLK_MASK) | SPI_TIMING_CS2SCLK_SET(duration);
}

/**
 * @brief SPI master get the minimum time between the edges of SPI CS and the edges of SCLK
 *
 * @param [in] ptr SPI base address
 * @retval spi_cs2sclk_duration_t enum
 */
static inline spi_cs2sclk_duration_t spi_master_get_cs2sclk_timing(SPI_Type *ptr)
{
    return (spi_cs2sclk_duration_t)SPI_TIMING_CS2SCLK_GET(ptr->TIMING);
}

/**
 * @brief SPI master set the minimum time that SPI CS should stay HIGH.
 *
 * @param [in] ptr SPI base address
 * @param [in] duration spi_csht_duration_t enum
 */
static inline void spi_master_set_csht_timing(SPI_Type *ptr, spi_csht_duration_t duration)
{
    ptr->TIMING = (ptr->TIMING & ~SPI_TIMING_CSHT_MASK) | SPI_TIMING_CSHT_SET(duration);
}

/**
 * @brief SPI master get the minimum time that SPI CS should stay HIGH.
 *
 * @param [in] ptr SPI base address
 * @retval spi_csht_duration_t enum
 */
static inline spi_csht_duration_t spi_master_get_csht_timing(SPI_Type *ptr)
{
    return (spi_csht_duration_t)SPI_TIMING_CSHT_GET(ptr->TIMING);
}

/**
 * @brief SPI master set the clock frequency ratio between the clock source and SPI SCLK
 *
 * @param [in] ptr SPI base address
 * @param [in] div the frequency ratio value
 */
static inline void spi_master_set_sclk_div(SPI_Type *ptr, uint8_t div)
{
    ptr->TIMING = (ptr->TIMING & ~SPI_TIMING_SCLK_DIV_MASK) | SPI_TIMING_SCLK_DIV_SET(div);
}

/**
 * @brief SPI master get the clock frequency ratio between the clock source and SPI SCLK
 *
 * @param [in] ptr SPI base address
 *
 * @retval return the frequency ratio value
 */
static inline uint8_t spi_master_get_sclk_div(SPI_Type *ptr)
{
    return SPI_TIMING_SCLK_DIV_GET(ptr->TIMING);
}

/**
 * @brief SPI slave set the user defined status flags
 *
 * @note in Non-SlvDataOnly, the command is read status command, such as 0x05\0x15\0x25 command
 *
 * @param [in] ptr SPI base address
 * @param [in] user_status user status value
 */
static inline void spi_slave_set_user_status(SPI_Type *ptr, uint16_t user_status)
{
    ptr->SLVST = (ptr->SLVST & ~SPI_SLVST_USR_STATUS_MASK) | SPI_SLVST_USR_STATUS_SET(user_status);
}

/**
 * @brief SPI master set data phase format
 *
 * @param [in] ptr SPI base address
 * @param [in] format spi_data_phase_format_t enum
 */
static inline void spi_master_set_data_phase_format(SPI_Type *ptr, spi_data_phase_format_t format)
{
    ptr->TRANSCTRL = (ptr->TRANSCTRL & ~SPI_TRANSCTRL_DUALQUAD_MASK) | SPI_TRANSCTRL_DUALQUAD_SET(format);
}

/**
 * @brief SPI master get data phase format
 *
 * @param [in] ptr SPI base address
 *
 * @retval return the data phase format
 */
static inline spi_data_phase_format_t spi_master_get_data_phase_format(SPI_Type *ptr)
{
    return (spi_data_phase_format_t)SPI_TRANSCTRL_DUALQUAD_GET(ptr->TRANSCTRL);
}

/**
 * @brief set spi shift direction
 *
 * @param [in] ptr SPI base address
 * @param [in] shift_direction shift direction enum
 */
static inline void spi_set_shift_direction(SPI_Type *ptr, spi_shift_direction_t shift_direction)
{
    ptr->TRANSFMT = (ptr->TRANSFMT & ~SPI_TRANSFMT_LSB_MASK) | SPI_TRANSFMT_LSB_SET(shift_direction);
}

/**
 * @brief get spi shift direction
 *
 * @param [in] ptr SPI base address
 * @retval spi_shift_direction_t msb_first if frist MSB
 */
static inline spi_shift_direction_t spi_get_shift_direction(SPI_Type *ptr)
{
    return (spi_shift_direction_t)SPI_TRANSFMT_LSB_GET(ptr->TRANSFMT);
}

/**
 * @}
 */

#if defined(__cplusplus)
}
#endif /* __cplusplus */
#endif /* HPM_SPI_DRV_H */
