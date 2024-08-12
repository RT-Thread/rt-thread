/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_COMPONENT_SPI_H
#define HPM_COMPONENT_SPI_H

#include "hpm_common.h"
#include "hpm_spi_drv.h"
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
#include "hpm_dmav2_drv.h"
#else
#include "hpm_dma_drv.h"
#endif
#include "hpm_dmamux_drv.h"
#include "hpm_misc.h"
#include "hpm_l1c_drv.h"

#ifndef SPI_CS_ACTIVE
#define SPI_CS_ACTIVE 0
#endif

#ifndef USE_DMA_MGR
#define USE_DMA_MGR      (0U)
#endif

/* Every transaction can be delineated by 3 dma descriptions: SPI control, SPI cmd, SPI data */
#define SPI_DMA_DESC_COUNT_PER_TRANS    (3U)

typedef struct {
    DMA_Type *dma_ptr;
    DMAMUX_Type *dmamux_ptr;
    uint8_t rx_dma_ch;
    uint8_t tx_dma_ch;
    uint8_t rx_dmamux_ch;
    uint8_t tx_dmamux_ch;
    uint8_t rx_req;
    uint8_t tx_req;
    uint8_t data_width;
} spi_dma_context_t;

typedef struct {
    SPI_Type *ptr;
    uint32_t cs_pin;
    uint8_t cmd;
    uint8_t *rx_buff;
    uint8_t *tx_buff;
    uint8_t running_core;
    uint32_t addr;
    uint32_t rx_size;
    uint32_t rx_count;
    uint32_t tx_size;
    uint32_t tx_count;
    uint32_t data_len_in_byte;
    uint32_t per_trans_max;
    uint32_t *spi_transctrl;
    void (*write_cs)(uint32_t cs_pin, uint8_t state);
    spi_dma_context_t dma_context;
    dma_linked_descriptor_t *dma_linked_descriptor;
} spi_context_t;

/**
 * @brief spi configuration init structure
 */
typedef struct {
    spi_mode_selection_t mode;               /*!< the spi operating mode */
    spi_data_phase_format_t io_mode;         /*!< the spi data line mode */
    spi_sclk_idle_state_t clk_polarity;      /*!< CPOL */
    spi_sclk_sampling_clk_edges_t clk_phase; /*!< CPHA */
    spi_shift_direction_t direction;                /*!< MSB or LSB data shift direction */
    uint8_t data_len;                        /*!< the unit is bit (1~32bit) */
    bool data_merge;                         /*!< data Merge mode*/
} spi_initialize_config_t;

#if USE_DMA_MGR
typedef void (*spi_dma_complete_cb)(uint32_t channel);
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief hpm_spi setup dma transfer
 *
 * @note if the transferred data count more than SPI_SOC_TRANSFER_COUNT_MAX, this API will using
 * DMA chain descriptors to link SPI transmission.
 *
 * @param[in] spi_context A pointer to the struct of "spi_context_t"
 * @param[in] spi_config A pointer to the struct of "spi_control_config_t"
 * @retval status_success if SPI transfers data successfully.
 */
hpm_stat_t hpm_spi_setup_dma_transfer(spi_context_t *context, spi_control_config_t *config);

/*
 * SPI release gpio pin if gpio use for SPI CS function
 */
/**
 * @brief hpm_spi releases gpio cs pin after SPI transfer completed
 *
 * @param[in] spi_context A pointer to the struct of "spi_context_t"
 * @retval status_success if SPI releases gpio cs pin successfully.
 */
hpm_stat_t hpm_spi_release_gpio_cs(spi_context_t *context);


/**
 * @brief spi get default init config
 *
 * @note it's no command/address/token phase, only data phase.
 *
 * @param [out] config spi_init_config_t
 */
void hpm_spi_get_default_init_config(spi_initialize_config_t *config);

/**
 * @brief initialize for spi
 *
 * @note it's no command/address/token phase, only data phase.
 *
 * @param [in] ptr SPI base address
 * @param [in] config spi_init_config_t struct
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_initialize(SPI_Type *ptr, spi_initialize_config_t *config);

/**
 * @brief set spi sclk frequency for spi master
 *
 * @param [in] ptr SPI base address
 * @param [in] freq spi sclk frequency
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_set_sclk_frequency(SPI_Type *ptr, uint32_t freq);

/**
 * @brief transmit and receive block for spi
 *
 * @note it's no command/address/token phase, only data phase.
 *
 * @param [in] ptr SPI base address
 * @param [in] wbuff spi sent data buff address
 * @param [out] rbuff spi receive data buff address
 * @param [in] size spi sent data count(word unit), not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @param [in] timeout  wait time. unit is millisecond
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_transmit_receive_blocking(SPI_Type *ptr, uint8_t *wbuff, uint8_t *rbuff, uint32_t size, uint32_t timeout);

/**
 * @brief receive block for spi
 *
 * @note it's no command/address/token phase, only data phase.
 *
 * @param [in] ptr SPI base address
 * @param [out] buff spi receive data buff address
 * @param [in] size spi sent data count(word unit), not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @param [in] timeout  wait time. unit is millisecond
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_receive_blocking(SPI_Type *ptr, uint8_t *buff, uint32_t size, uint32_t timeout);

/**
 * @brief transmit block for spi
 *
 * @note it's no command/address/token phase, only data phase.
 *
 * @param [in] ptr SPI base address
 * @param [in] buff spi sent data buff address
 * @param [in] size spi sent data count(word unit), not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @param [in] timeout  wait time. unit is millisecond
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_transmit_blocking(SPI_Type *ptr, uint8_t *buff, uint32_t size, uint32_t timeout);

/**
 * @brief transmit and receive setup dma for spi
 *
 * @note it's no command/address/token phase, only data phase.
 *       main configuration spi dma related, call this API after configuring DMA best
 *
 * @param [in] ptr SPI base address
 * @param [in] size spi sent and receive  data count(word unit), not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_transmit_receive_setup_dma(SPI_Type *ptr, uint32_t size);

/**
 * @brief receive setup dma for spi
 *
 * @note it's no command/address/token phase, only data phase.
 *       main configuration spi dma related, call this API after configuring DMA best
 *
 * @param [in] ptr SPI base address
 * @param [in] size spi receive data count(word unit), not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_receive_setup_dma(SPI_Type *ptr, uint32_t size);

/**
 * @brief transmit setup dma for spi
 *
 * @note it's no command/address/token phase, only data phase.
 *       main configuration spi dma related, call this API after configuring DMA best
 *
 * @param [in] ptr SPI base address
 * @param [in] size spi transmit data count(word unit), not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_transmit_setup_dma(SPI_Type *ptr, uint32_t size);

#if USE_DMA_MGR
/**
 * @brief Install callback for SPI DMA channel transmit and receive complete
 *
 * @note it's no command/address/token phase, only data phase.
 *
 * @param [in] ptr SPI base address
 * @param [in] tx_complete callback for SPI TX DMA
 * @param [in] rx_complete callback for SPI RX DMA
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_dma_install_callback(SPI_Type *ptr,
                                        spi_dma_complete_cb tx_complete,
                                        spi_dma_complete_cb rx_complete);

/**
 * @brief transmit and receive noblock for spi
 *
 * @note it's no command/address/token phase, only data phase. use dma
 *
 * @param [in] ptr SPI base address
 * @param [in] wbuff spi sent data buff address
 * @param [out] rbuff spi receive data buff address
 * @param [in] size spi sent data count(word unit), not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_transmit_receive_nonblocking(SPI_Type *ptr, uint8_t *wbuff, uint8_t *rbuff, uint32_t size);

/**
 * @brief receive noblock for spi
 *
 * @note it's no command/address/token phase, only data phase. use dma
 *
 * @param [in] ptr SPI base address
 * @param [out] buff spi receive data buff address
 * @param [in] size spi sent data count(word unit), not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_receive_nonblocking(SPI_Type *ptr, uint8_t *buff, uint32_t size);

/**
 * @brief transmit noblock for spi
 *
 * @note it's no command/address/token phase, only data phase. use dma
 *
 * @param [in] ptr SPI base address
 * @param [in] buff spi sent data buff address
 * @param [in] size spi sent data count(word unit), not greater than SPI_SOC_TRANSFER_COUNT_MAX
 * @retval hpm_stat_t status_success if spi in busy status
 */
hpm_stat_t hpm_spi_transmit_nonblocking(SPI_Type *ptr, uint8_t *buff, uint32_t size);

#endif

#ifdef __cplusplus
}
#endif

#endif /* HPM_COMPONENT_SPI_H */
