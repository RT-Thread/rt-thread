#ifndef SUNXI_HAL_TWI_H
#define SUNXI_HAL_TWI_H

#include "hal_sem.h"
#include "hal_clk.h"
#include "sunxi_hal_common.h"
#include "hal_gpio.h"
#include "sunxi_hal_regulator.h"
#include <twi/platform_twi.h>
#include <twi/common_twi.h>

#ifdef __cplusplus
extern "C" {
#endif

//for debug
#define CONFIG_DRIVERS_TWI_DEBUG
#ifndef CONFIG_DRIVERS_TWI_DEBUG
#define TWI_INFO(fmt, arg...) hal_log_info(fmt, ##arg)
#else
#define TWI_INFO(fmt, arg...) do {}while(0)
#endif

#define TWI_ERR(fmt, arg...) hal_log_err(fmt, ##arg)

typedef enum
{
    TWI_XFER_IDLE    = 0x1,
    TWI_XFER_START   = 0x2,
    TWI_XFER_RUNNING = 0x4,
} twi_xfer_status_t;

/** @brief This enum defines the HAL interface return value. */
typedef enum
{
    TWI_STATUS_ERROR = -4,                        /**<  An error occurred and the transaction has failed. */
    //TWI_STATUS_ERROR_TIMEOUT = -4,                /**<  The TWI bus xfer timeout, an error occurred. */
    TWI_STATUS_ERROR_BUSY = -3,                   /**<  The TWI bus is busy, an error occurred. */
    TWI_STATUS_INVALID_PORT_NUMBER = -2,          /**<  A wrong port number is given. */
    TWI_STATUS_INVALID_PARAMETER = -1,            /**<  A wrong parameter is given. */
    TWI_STATUS_OK = 0                             /**<  No error occurred during the function call. */
} twi_status_t;

typedef enum
{
    TWI_MASTER_0,           /**< TWI master 0. */
    TWI_MASTER_1,           /**< TWI master 1. */
    TWI_MASTER_2,           /**< TWI master 0. */
    TWI_MASTER_3,           /**< TWI master 1. */
    S_TWI_MASTER_0,           /**< S_TWI master 0. */
    TWI_MASTER_MAX              /**< max TWI master number, \<invalid\> */
} twi_port_t;

/** @brief This enum defines the TWI transaction speed.  */
typedef enum
{
    TWI_FREQUENCY_100K = 100000,          /**<  100kbps. */
    TWI_FREQUENCY_200K = 200000,          /**<  200kbps. */
    TWI_FREQUENCY_400K = 400000,          /**<  400kbps. */
} twi_frequency_t;

/** @brief This enum defines the TWI transaction speed.  */
typedef enum
{
    ENGINE_XFER = 0,
    TWI_DRV_XFER = 1,
} twi_mode_t;

typedef struct twi_msg
{
    uint16_t addr;          /* slave address */
    uint16_t flags;
#define TWI_M_RD        0x0001  /* read data, from slave to master
                     * TWI_M_RD is guaranteed to be 0x0001!
                     * */
#define TWI_M_TEN       0x0010  /* this is a ten bit chip address */
    uint16_t len;           /* msg length */
    uint8_t *buf;       /* pointer to msg data */
} twi_msg_t;

typedef struct sunxi_twi
{
    uint8_t port;
    uint8_t result;
    uint8_t already_init;
    uint8_t twi_drv_used;
    uint8_t pkt_interval;

    uint16_t slave_addr;
    uint16_t flags;

    uint32_t timeout;
    uint32_t msgs_num;
    uint32_t msgs_idx;
    uint32_t msgs_ptr;
    unsigned long base_addr;
    uint32_t irqnum;

    struct regulator_dev regulator;
    hal_clk_t pclk;
    hal_clk_t mclk;
    twi_frequency_t freq;

    uint32_t    pinmux;
    uint32_t    pin[TWI_PIN_NUM];
    twi_xfer_status_t   status;
    hal_sem_t   hal_sem;
    twi_msg_t   *msgs;

    struct sunxi_dma_chan *dma_chan;
    hal_sem_t     dma_complete;
} hal_twi_t;

typedef enum
{
    I2C_SLAVE = 0,
    I2C_SLAVE_FORCE = 1,
    I2C_TENBIT = 2,
    I2C_RDWR = 3
} hal_twi_transfer_cmd_t;

//initialize twi port
twi_status_t hal_twi_init(twi_port_t port);
//uninitialize twi port
twi_status_t hal_twi_uninit(twi_port_t port);
//twi write
twi_status_t hal_twi_write(twi_port_t port, unsigned long pos, const void *buf, uint32_t size);
//twi read
twi_status_t hal_twi_read(twi_port_t port, unsigned long pos, void *buf, uint32_t size);
//twi control
twi_status_t hal_twi_control(twi_port_t port, hal_twi_transfer_cmd_t cmd, void *args);

#ifdef __cplusplus
}
#endif

#endif
