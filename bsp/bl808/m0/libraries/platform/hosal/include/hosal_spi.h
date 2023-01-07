/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef HAL_SPI_H
#define HAL_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup hosal_spi SPI 
 *  HOSAL SPI API
 *
 *  @{
 */

#include <stdint.h>
#include <FreeRTOS.h>
#include <event_groups.h>

#define HOSAL_SPI_MODE_MASTER 0  /**< spi communication is master mode */
#define HOSAL_SPI_MODE_SLAVE  1  /**< spi communication is slave mode */
#define HOSAL_WAIT_FOREVER  0xFFFFFFFFU /**< DMA transmission timeout */

typedef void (*hosal_spi_irq_t)(void *parg); /**< spi irq callback function */

/** 
 * @brief Define spi config args 
 */
typedef struct {
    uint8_t mode;           /**< spi communication mode */
    uint8_t dma_enable;     /**< enable dma tansmission or not */
    uint8_t polar_phase;    /**< spi polar and phase */
    uint32_t freq;          /**< communication frequency Hz */
    uint8_t pin_clk;        /**< spi clk pin */
    uint8_t pin_mosi;       /**< spi mosi pin */
    uint8_t pin_miso;       /**< spi miso pin */
} hosal_spi_config_t;

/** 
 * @brief Define spi dev handle
 */
typedef struct {
    uint8_t port;               /**< spi port */
    hosal_spi_config_t  config; /**< spi config */
    hosal_spi_irq_t cb;         /**< spi interrupt callback */
    void *p_arg;                /**< arg pass to callback */
    void *priv;                 /**< priv data */
} hosal_spi_dev_t;

/**
 * @brief Initialises the SPI interface for a given SPI device
 *
 * @param[in]  spi  the spi device
 *
 * @return  
 *       - 0 : on success 
 *       - other : error
 */
int hosal_spi_init(hosal_spi_dev_t *spi);

/**
 * @brief Spi send
 *
 * @param[in]  spi      the spi device
 * @param[in]  data     spi send data
 * @param[in]  size     spi send data size
 * @param[in]  timeout  timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                      if you want to wait forever
 *
 * @return  
 *       - 0 : on success  
 *       - other : error
 */
int hosal_spi_send(hosal_spi_dev_t *spi, const uint8_t *data, uint32_t size, uint32_t timeout);

/**
 * @brief Spi recv
 *
 * @param[in]   spi      the spi device
 * @param[out]  data     spi recv data
 * @param[in]   size     spi recv data size
 * @param[in]   timeout  timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                       if you want to wait forever
 *
 * @return  
 *       - 0 : success
 *       - other : error
 */
int hosal_spi_recv(hosal_spi_dev_t *spi, uint8_t *data, uint16_t size, uint32_t timeout);

/**
 * @brief spi send data and recv
 *
 * @param[in]  spi      the spi device
 * @param[in]  tx_data  spi send data
 * @param[out] rx_data  spi recv data
 * @param[in]  size     spi data to be sent and recived
 * @param[in]  timeout  timeout in milisecond, set this value to HAL_WAIT_FOREVER
 *                      if you want to wait forever
 *
 * @return  
 *        - 0 : success 
 *        - other : error
 */
int hosal_spi_send_recv(hosal_spi_dev_t *spi, uint8_t *tx_data, uint8_t *rx_data, uint16_t size, uint32_t timeout);

/*
 * @brief set spi irq callback
 *
 * @param spi the spi device
 * @param pfn callback function
 * @param p_arg callback function parameter
 *
 * @return 
 *       - 0 : success
 *       - othe : error
 */
int hosal_spi_irq_callback_set(hosal_spi_dev_t *spi, hosal_spi_irq_t pfn, void *p_arg);

/**
 * @brief spi software set cs pin high/low only for master device
 *
 * @param[in] pin    cs pin
 * @param[in] value  0 or 1
 *
 * @return  
 *       - 0 : success
 *       - other : error
 */
int hosal_spi_set_cs(uint8_t pin, uint8_t value);

/**
 * @brief De-initialises a SPI interface
 *
 *
 * @param[in]  spi  the SPI device to be de-initialised
 *
 * @return 
 *       - 0 : success 
 *       - other : error
 */
int hosal_spi_finalize(hosal_spi_dev_t *spi);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* HAL_SPI_H */

