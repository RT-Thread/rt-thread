/*
 * ===========================================================================================
 *
 *       Filename:  sunxi_hal_spi.h
 *
 *    Description:  SPI HAL definition.
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-18 11:11:56
 *       Revision:  none
 *       Compiler:  GCC:version 9.2.1
 *
 *         Author:  bantao@allwinnertech.com
 *   Organization:  SWC-BPD
 *  Last Modified:  2019-12-03 16:02:11
 *
 * ===========================================================================================
 */

#ifndef SUNXI_HAL_SPI_H
#define SUNXI_HAL_SPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "sunxi_hal_common.h"
#include <hal_gpio.h>
#include <hal_dma.h>
/* #include <sunxi_drv_spi.h> */
#include <hal_sem.h>
#include <hal_clk.h>
#include <spi/platform_spi.h>
#include <spi/common_spi.h>



/*****************************************************************************
 * spi master
 *****************************************************************************/
/** @brief This enum defines the SPI master port.
 *  This chip total has 2 SPI master port
 */
typedef enum
{
    HAL_SPI_MASTER_0 = 0, /**< spi master port 0 */
    HAL_SPI_MASTER_1 = 1, /**< spi master port 1 */
    HAL_SPI_MASTER_2 = 2, /**< spi master port 1 */
    HAL_SPI_MASTER_MAX = SPI_MAX_NUM,   /**< spi master max port number\<invalid\> */
} hal_spi_master_port_t;

typedef struct
{
    const uint8_t *tx_buf; /**< Data buffer to send, */
    uint32_t tx_len; /**< The total number of bytes to send. */
    uint32_t
    tx_single_len; /**< The number of bytes to send in single mode. */
    uint8_t *rx_buf;   /**< Received data buffer, */
    uint32_t rx_len;   /**< The valid number of bytes received. */
    uint8_t tx_nbits : 3;  /**< Data buffer to send in nbits mode */
    uint8_t rx_nbits : 3;  /**< Data buffer to received in nbits mode */
    uint8_t dummy_byte;    /**< Flash send dummy byte, default 0*/
#define SPI_NBITS_SINGLE 0x01  /* 1bit transfer */
#define SPI_NBITS_DUAL 0x02    /* 2bit transfer */
#define SPI_NBITS_QUAD 0x04    /* 4bit transfer */
    uint8_t bits_per_word; /**< transfer bit_per_word */
} hal_spi_master_transfer_t;

typedef enum spi_mode_type
{
    SGLE_HALF_DUPLEX_RX, /* single mode, half duplex read */
    SGLE_HALF_DUPLEX_TX, /* single mode, half duplex write */
    DUAL_HALF_DUPLEX_RX, /* dual mode, half duplex read */
    DUAL_HALF_DUPLEX_TX, /* dual mode, half duplex write */
    QUAD_HALF_DUPLEX_RX, /* quad mode, half duplex read */
    QUAD_HALF_DUPLEX_TX, /* quad mode, half duplex write */
    FULL_DUPLEX_TX_RX,   /* full duplex read and write */
    MODE_TYPE_NULL,
} spi_mode_type_t;

typedef struct spi_dma
{
    struct dma_slave_config config;
    struct sunxi_dma_chan *chan;
} spi_dma_t;

typedef struct sunxi_spi
{
    int8_t result : 2;
#define SPI_XFER_READY 0
#define SPI_XFER_OK 1
#define SPI_XFER_FAILED -1

    bool sem;
    uint16_t irqnum;
    unsigned long base;
    spi_mode_type_t mode_type;

    hal_clk_t pclk; /* PLL clock */
    hal_clk_t bus_clk; /* BUS clock */
    hal_clk_t mclk; /* spi module clock */
    struct reset_control *reset;

    spi_dma_t dma_rx;
    spi_dma_t dma_tx;

    char *align_dma_buf;
#define ALIGN_DMA_BUF_SIZE (4096 + 64)

    hal_sem_t xSemaphore_tx;
    hal_sem_t xSemaphore_rx;

    hal_spi_master_port_t port;
    hal_spi_master_transfer_t *transfer;
} sunxi_spi_t;

typedef enum
{
    SPI_MASTER_ERROR = -6,       /**< SPI master function error occurred. */
    SPI_MASTER_ERROR_NOMEM = -5, /**< SPI master request mem failed. */
    SPI_MASTER_ERROR_TIMEOUT = -4, /**< SPI master xfer timeout. */
    SPI_MASTER_ERROR_BUSY = -3,    /**< SPI master is busy. */
    SPI_MASTER_ERROR_PORT = -2,    /**< SPI master invalid port. */
    SPI_MASTER_INVALID_PARAMETER =
        -1,       /**< SPI master invalid input parameter. */
    SPI_MASTER_OK = 0 /**< SPI master operation completed successfully. */
} spi_master_status_t;

/** @brief selection of spi slave device connected to which cs pin of spi master
*/
typedef enum
{
    HAL_SPI_MASTER_SLAVE_0 =
        0, /**< spi slave device connect to spi master cs0 pin */
    HAL_SPI_MASTER_SLAVE_1 =
        1, /**< spi slave device connect to spi master cs1 pin */
    HAL_SPI_MASTER_SLAVE_MAX /**< spi master max cs pin number\<invalid\> */
} hal_spi_master_slave_port_t;

/** @brief SPI master clock polarity definition */
typedef enum
{
    HAL_SPI_MASTER_CLOCK_POLARITY0 = 0, /**< Clock polarity is 0 */
    HAL_SPI_MASTER_CLOCK_POLARITY1 = 2  /**< Clock polarity is 1 */
} hal_spi_master_clock_polarity_t;

/** @brief SPI master clock format definition */
typedef enum
{
    HAL_SPI_MASTER_CLOCK_PHASE0 = 0, /**< Clock format is 0 */
    HAL_SPI_MASTER_CLOCK_PHASE1 = 1  /**< Clock format is 1 */
} hal_spi_master_clock_phase_t;

/** @brief SPI master transaction bit order definition */
typedef enum
{
    HAL_SPI_MASTER_MSB_FIRST =
        0, /**< Both send and receive data transfer MSB first */
    HAL_SPI_MASTER_LSB_FIRST =
        1 /**< Both send and receive data transfer LSB first */
} hal_spi_master_bit_order_t;

/** @brief SPI master status. */
typedef enum
{
    HAL_SPI_MASTER_STATUS_ERROR =
        -6, /**< SPI master function error occurred. */
    HAL_SPI_MASTER_STATUS_ERROR_NOMEM =
        -5, /**< SPI master request mem failed. */
    HAL_SPI_MASTER_STATUS_ERROR_TIMEOUT =
        -4,                    /**< SPI master xfer timeout. */
    HAL_SPI_MASTER_STATUS_ERROR_BUSY = -3, /**< SPI master is busy. */
    HAL_SPI_MASTER_STATUS_ERROR_PORT = -2, /**< SPI master invalid port. */
    HAL_SPI_MASTER_STATUS_INVALID_PARAMETER =
        -1, /**< SPI master invalid input parameter. */
    HAL_SPI_MASTER_STATUS_OK =
        0 /**< SPI master operation completed successfully. */
} hal_spi_master_status_t;

/** @brief SPI master running status. */
typedef enum
{
    HAL_SPI_MASTER_BUSY = 0, /**< SPI master is busy. */
    HAL_SPI_MASTER_IDLE = 1  /**< SPI master is idle. */
} hal_spi_master_running_status_t;

typedef enum
{
    HAL_SPI_MASTER_CS_AUTO = 0,
    HAL_SPI_MASTER_CS_SOFT = 1,
} hal_spi_master_cs_mode_t;

typedef struct
{
    uint32_t clock_frequency; /**< SPI master clock frequency setting. */
    hal_spi_master_slave_port_t
    slave_port; /**< SPI slave device selection. */
    hal_spi_master_bit_order_t
    bit_order; /**< SPI master bit order setting. 0:MSB first 1:LSB
                 first*/
    hal_spi_master_clock_polarity_t
    cpol; /**< SPI master clock polarity setting. 0:Active high
            polarity(0 = Idle) 1:Active low polarity(1 = Idle) */
    hal_spi_master_clock_phase_t
    cpha; /**< SPI master clock phase setting. 0: Phase 0(Leading edge
            for sample data)  1: Phase 1(Leading edge for setup data)
            */
    hal_spi_master_cs_mode_t csmode;
} hal_spi_master_config_t;

typedef enum
{
    SPI_WRITE_READ = 0, /**< SPI master is busy. */
    SPI_CONFIG = 1  /**< SPI master is idle. */
} hal_spi_transfer_cmd_t;

spi_master_status_t hal_spi_init(hal_spi_master_port_t port, hal_spi_master_config_t *cfg);
spi_master_status_t hal_spi_write(hal_spi_master_port_t port, const void *buf, uint32_t size);
spi_master_status_t hal_spi_deinit(hal_spi_master_port_t port);
spi_master_status_t hal_spi_read(hal_spi_master_port_t port, void *buf, uint32_t size);
spi_master_status_t hal_spi_xfer(hal_spi_master_port_t port, hal_spi_master_transfer_t *transfer);
spi_master_status_t hal_spi_hw_config(hal_spi_master_port_t port, hal_spi_master_config_t *spi_config);
void hal_spi_cs(hal_spi_master_port_t port, uint8_t on_off);

#endif
