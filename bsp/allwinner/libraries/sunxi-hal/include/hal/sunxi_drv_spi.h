/*
 * ===========================================================================================
 *
 *       Filename:  sunxi_drv_spi.h
 *
 *    Description:  sunxi_driver headfile.
 *
 *        Version:  Melis3.0
 *         Create:  2019-11-14 17:47:21
 *       Revision:  none
 *       Compiler:  GCC:version 9.2.1 20170904 (release),ARM/embedded-7-branch revision 25520
 *
 *         Author:  bantao@allwinnertech.com
 *   Organization:  SWC-BPD
 *  Last Modified:  2019-11-15 13:19:52
 *
 * ===========================================================================================
 */
#ifndef SUNXI_DRV_SPI_H
#define SUNXI_DRV_SPI_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <sunxi_hal_spi.h>
#include <rtthread.h>

typedef struct sunxi_driver_spi
{
    struct rt_device   base;
    int32_t            dev_id;
    const void        *hal_drv;
} sunxi_driver_spi_t;

#if 0
typedef enum
{
    SPI_WRITE_READ = 0, /**< SPI master is busy. */
    SPI_CONFIG = 1  /**< SPI master is idle. */
} hal_spi_transfer_cmd_t;

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
#endif

typedef struct sunxi_hal_driver_spi
{
    spi_master_status_t (*initialize)(hal_spi_master_port_t port);
    spi_master_status_t (*uninitialize)(hal_spi_master_port_t port);
    spi_master_status_t (*send)(hal_spi_master_port_t port,
                                const void *buf, uint32_t size);
    spi_master_status_t (*receive)(hal_spi_master_port_t port,
                                   void *buf, uint32_t size);
    spi_master_status_t (*hw_config)(hal_spi_master_port_t port, hal_spi_master_config_t *spi_config);
    spi_master_status_t (*transfer)(hal_spi_master_port_t port, hal_spi_master_transfer_t *transfer);
} const sunxi_hal_driver_spi_t;

#ifdef __cplusplus
}
#endif

#endif
