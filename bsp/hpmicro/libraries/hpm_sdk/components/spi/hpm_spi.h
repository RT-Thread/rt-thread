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
#ifdef CONFIG_HAS_HPMSDK_DMAV2
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

#ifdef __cplusplus
}
#endif

#endif /* HPM_COMPONENT_SPI_H */
