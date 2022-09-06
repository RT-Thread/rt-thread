/*
 * Copyright (c) 2021 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef HPM_I2S_DRV_H
#define HPM_I2S_DRV_H
#include "hpm_common.h"
#include "hpm_soc_feature.h"
#include "hpm_i2s_regs.h"
#include "hpm_i2s_common.h"

/**
 * @brief I2S driver APIs
 * @defgroup i2s_interface I2S driver APIs
 * @ingroup io_interfaces
 * @{
 */

/**
 * @brief I2S IRQ mask
 */
#define I2S_IRQ_TX_FIFO_EMPTY I2S_CTRL_TXDNIE_MASK
#define I2S_IRQ_RX_FIFO_DATA_AVAILABLE I2S_CTRL_RXDAIE_MASK
#define I2S_IRQ_ERROR I2S_CTRL_ERRIE_MASK

/**
 * @brief I2S data line
 */
#define I2S_DATA_LINE_0 (0U)
#define I2S_DATA_LINE_1 (1U)
#define I2S_DATA_LINE_2 (2U)
#define I2S_DATA_LINE_3 (3U)
#define I2S_DATA_LINE_MAX I2S_DATA_LINE_3

/* i2s channel slot mask */
#define I2S_CHANNEL_SLOT_MASK(x) ((1U << (x)) & I2S_RXDSLOT_EN_MASK)

/**
 * @brief I2S config
 */
typedef struct i2s_config {
    bool invert_mclk_out;
    bool invert_mclk_in;
    bool use_external_mclk;
    bool invert_bclk_out;
    bool invert_bclk_in;
    bool use_external_bclk;
    bool invert_fclk_out;
    bool invert_fclk_in;
    bool use_external_fclk;
    bool enable_mclk_out;
    bool frame_start_at_rising_edge;
    uint16_t fifo_threshold;
} i2s_config_t;

/**
 * @brief I2S transfer config
 */
typedef struct i2x_transfer_config {
    uint32_t sample_rate;
    bool enable_tdm_mode;
    uint8_t channel_num_per_frame;
    uint8_t channel_length;          /* 16-bit or 32-bit */
    uint8_t audio_depth;             /* 8-bit, 24-bit, 32-bit */
    bool master_mode;
    uint8_t protocol;
    uint8_t data_line;
    uint32_t channel_slot_mask;
} i2s_transfer_config_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief enable TDM
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_enable_tdm(I2S_Type *ptr)
{
    ptr->CFGR |= I2S_CFGR_TDM_EN_MASK;
}

/**
 * @brief disable TDM
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_disable_tdm(I2S_Type *ptr)
{
    ptr->CFGR &= ~I2S_CFGR_TDM_EN_MASK;
}

/**
 * @brief update rx fifo threshold
 *
 * @param [in] ptr I2S base address
 * @param [in] threshold fifo threshold value
 */
static inline void i2s_update_rx_fifo_threshold(I2S_Type *ptr, uint8_t threshold)
{
    ptr->FIFO_THRESH = (ptr->FIFO_THRESH & ~I2S_FIFO_THRESH_RX_MASK)
        | I2S_FIFO_THRESH_RX_SET(threshold);
}

/**
 * @brief update tx fifo threshold
 *
 * @param [in] ptr I2S base address
 * @param [in] threshold fifo threshold value
 */
static inline void i2s_update_tx_fifo_threshold(I2S_Type *ptr, uint8_t threshold)
{
    ptr->FIFO_THRESH = (ptr->FIFO_THRESH & ~I2S_FIFO_THRESH_TX_MASK)
        | I2S_FIFO_THRESH_TX_SET(threshold);
}

/**
 * @brief open BCLK
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_ungate_bclk(I2S_Type *ptr)
{
    ptr->CFGR &= ~I2S_CFGR_BCLK_GATEOFF_MASK;
}

/**
 * @brief gete off BCLK
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_gate_bclk(I2S_Type *ptr)
{
    ptr->CFGR |= I2S_CFGR_BCLK_GATEOFF_MASK;
}

/**
 * @brief open MCLK
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_ungate_mclk(I2S_Type *ptr)
{
    ptr->MISC_CFGR &= ~I2S_MISC_CFGR_MCLK_GATEOFF_MASK;
}

/**
 * @brief gate off MCLK
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_gate_mclk(I2S_Type *ptr)
{
    ptr->MISC_CFGR |= I2S_MISC_CFGR_MCLK_GATEOFF_MASK;
}

/**
 * @brief enable TX dma request
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_enable_tx_dma_request(I2S_Type *ptr)
{
    ptr->CTRL |=I2S_CTRL_TX_DMA_EN_MASK;
}

/**
 * @brief disable TX dma request
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_disable_tx_dma_request(I2S_Type *ptr)
{
    ptr->CTRL &= ~I2S_CTRL_TX_DMA_EN_MASK;
}

/**
 * @brief enable RX dma request
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_enable_rx_dma_request(I2S_Type *ptr)
{
    ptr->CTRL |=I2S_CTRL_RX_DMA_EN_MASK;
}

/**
 * @brief disable RX dma request
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_disable_rx_dma_request(I2S_Type *ptr)
{
    ptr->CTRL &= ~I2S_CTRL_RX_DMA_EN_MASK;
}

/**
 * @brief enable IRQ
 *
 * @param [in] ptr I2S base address
 * @param [in] mask irq bit mask
 */
static inline void i2s_enable_irq(I2S_Type *ptr, uint32_t mask)
{
    ptr->CTRL |= mask;
}

/**
 * @brief disable IRQ
 *
 * @param [in] ptr I2S base address
 * @param [in] mask irq bit mask
 */
static inline void i2s_disable_irq(I2S_Type *ptr, uint32_t mask)
{
    ptr->CTRL &= ~mask;
}

/**
 * @brief I2S enable
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_enable(I2S_Type *ptr)
{
    ptr->CTRL |= ~I2S_CTRL_I2S_EN_MASK;
}

/**
 * @brief I2S disable
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_disable(I2S_Type *ptr)
{
    ptr->CTRL &= ~I2S_CTRL_I2S_EN_MASK;
}

/**
 * @brief I2S enable rx function
 *
 * @param [in] ptr I2S base address
 * @param [in] rx_mask rx data line mask
 */
static inline void i2s_enable_rx(I2S_Type *ptr, uint8_t rx_mask)
{
    ptr->CTRL |= I2S_CTRL_RX_EN_SET(rx_mask);
}

/**
 * @brief I2S disable rx function
 *
 * @param [in] ptr I2S base address
 * @param [in] rx_mask rx data line mask
 */
static inline void i2s_disable_rx(I2S_Type *ptr, uint8_t rx_mask)
{
    ptr->CTRL &= ~I2S_CTRL_RX_EN_SET(rx_mask);
}

/**
 * @brief I2S enable tx function
 *
 * @param [in] ptr I2S base address
 * @param [in] tx_mask tx data line mask
 */
static inline void i2s_enable_tx(I2S_Type *ptr, uint8_t tx_mask)
{
    ptr->CTRL |= I2S_CTRL_TX_EN_SET(tx_mask);
}

/**
 * @brief I2S disbale tx function
 *
 * @param [in] ptr I2S base address
 * @param [in] tx_mask tx data line mask
 */
static inline void i2s_disable_tx(I2S_Type *ptr, uint8_t tx_mask)
{
    ptr->CTRL &= ~I2S_CTRL_TX_EN_SET(tx_mask);
}

/**
 * @brief I2S clear tx fifo
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_clear_tx_fifo(I2S_Type *ptr)
{
    ptr->CTRL |= I2S_CTRL_TXFIFOCLR_MASK;
    while (ptr->CTRL & I2S_CTRL_TXFIFOCLR_MASK) {}
}

/**
 * @brief I2S clear rx fifo
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_clear_rx_fifo(I2S_Type *ptr)
{
    ptr->CTRL |= I2S_CTRL_RXFIFOCLR_MASK;
    while (ptr->CTRL & I2S_CTRL_RXFIFOCLR_MASK) {}
}

/**
 * @brief I2S reset clock generator
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_reset_clock_gen(I2S_Type *ptr)
{
    ptr->CTRL |= I2S_CTRL_SFTRST_CLKGEN_MASK;
    ptr->CTRL &= ~I2S_CTRL_SFTRST_CLKGEN_MASK;
}

/**
 * @brief I2S reset tx function
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_reset_tx(I2S_Type *ptr)
{
    ptr->CTRL |= I2S_CTRL_SFTRST_TX_MASK;
    ptr->CTRL &= ~I2S_CTRL_SFTRST_TX_MASK;
}

/**
 * @brief I2S reset rx function
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_reset_rx(I2S_Type *ptr)
{
    ptr->CTRL |= I2S_CTRL_SFTRST_RX_MASK;
    ptr->CTRL &= ~I2S_CTRL_SFTRST_RX_MASK;
}

/**
 * @brief I2S get tx fifo level
 *
 * @param [in] ptr I2S base address
 *
 * @retval I2S tx fifo level
 */
static inline uint32_t i2s_get_tx_fifo_level(I2S_Type *ptr)
{
    return ptr->TFIFO_FILLINGS;
}

/**
 * @brief I2S get data line tx fifo level
 *
 * @param [in] ptr I2S base address
 * @param [in] line I2S data line
 *
 * @retval I2S data line tx fifo level
 */
static inline uint32_t i2s_get_tx_line_fifo_level(I2S_Type *ptr, uint8_t line)
{
    return i2s_get_tx_fifo_level(ptr) & (0xFF << (line << 3));
}

/**
 * @brief I2S get rx fifo level
 *
 * @param [in] ptr I2S base address
 *
 * @retval I2S rx fifo level
 */
static inline uint32_t i2s_get_rx_fifo_level(I2S_Type *ptr)
{
    return ptr->RFIFO_FILLINGS;
}

/**
 * @brief I2S get data line rx fifo level
 *
 * @param [in] ptr I2S base address
 * @param [in] line I2S data line
 *
 * @retval I2S data line rx fifo level
 */
static inline uint32_t i2s_get_rx_line_fifo_level(I2S_Type *ptr, uint8_t line)
{
    return i2s_get_rx_fifo_level(ptr) & (0xFF << (line << 3));
}

/**
 * @brief I2S get IRQ status
 *
 * @param [in] ptr I2S base address
 *
 * @retval I2S STA register value
 */
static inline uint32_t i2s_get_irq_status(I2S_Type *ptr)
{
    return ptr->STA;
}

/**
 * @brief I2S stop transfer
 *
 * @param [in] ptr I2S base address
 */
static inline void i2s_stop_transfer(I2S_Type *ptr)
{
    i2s_disable(ptr);
}

/**
 * @brief I2S config tx
 *
 * @param [in] ptr I2S base address
 * @param [in] mclk_in_hz mclk frequency in Hz
 * @param [in] config i2s_transfer_config_t
 * @retval hpm_stat_t status_invalid_argument or status_success
 */
hpm_stat_t i2s_config_tx(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config);

/**
 * @brief I2S config rx
 *
 * @param [in] ptr I2S base address
 * @param [in] mclk_in_hz mclk frequency in Hz
 * @param [in] config i2s_transfer_config_t
 * @retval hpm_stat_t status_invalid_argument or status_success
 */
hpm_stat_t i2s_config_rx(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config);

/**
 * @brief I2S config transfer
 *
 * @param [in] ptr I2S base address
 * @param [in] mclk_in_hz mclk frequency in Hz
 * @param [in] config i2s_transfer_config_t
 * @retval hpm_stat_t status_invalid_argument or status_success
 */
hpm_stat_t i2s_config_transfer(I2S_Type *ptr, uint32_t mclk_in_hz, i2s_transfer_config_t *config);

/**
 * @brief I2S send data
 *
 * @param [in] ptr I2S base address
 * @param [in] tx_line_index data line
 * @param [in] src source data buff
 * @param [in] size data size
 */
uint32_t i2s_send_data(I2S_Type *ptr, uint8_t tx_line_index, uint32_t *src, uint32_t size);

/**
 * @brief I2S receive data
 *
 * @param [in] ptr I2S base address
 * @param [in] rx_line_index data line
 * @param [out] dst target data buff
 * @param [in] size data size
 */
uint32_t i2s_receive_data(I2S_Type *ptr, uint8_t rx_line_index, uint32_t *dst, uint32_t size);

/**
 * @brief I2S get default config
 *
 * @param [in] ptr I2S base address
 * @param [out] config i2s_config_t
 */
void i2s_get_default_config(I2S_Type *ptr, i2s_config_t *config);

/**
 * @brief I2S initialization
 *
 * @param [in] ptr I2S base address
 * @param [in] config i2s_config_t
 */
void i2s_init(I2S_Type *ptr, i2s_config_t *config);

/**
 * @brief I2S get default transfer config for pdm
 *
 * @param [out] transfer i2s_transfer_config_t
 */
void i2s_get_default_transfer_config_for_pdm(i2s_transfer_config_t *transfer);

/**
 * @brief I2S get default transfer config for dao
 *
 * @param [out] transfer i2s_transfer_config_t
 */
void i2s_get_default_transfer_config_for_dao(i2s_transfer_config_t *transfer);

/**
 * @brief I2S get default transfer config
 *
 * @param [out] transfer i2s_transfer_config_t
 */
void i2s_get_default_transfer_config(i2s_transfer_config_t *transfer);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* HPM_I2S_DRV_H */
