/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author      Notes
 * 2011-01-07   onelife     Initial creation for EFM32
 * 2011-07-11   onelife     Add lock (semaphore) to prevent simultaneously access
 * 2011-08-04   onelife     Change the usage of the second parameter of Read
 *                            and Write functions from (seldom used) "Offset" to "Slave address"
 * 2011-08-04   onelife     Add a timer to prevent from forever waiting
 * 2011-12-27   onelife     Change IIC read format
 */

#ifndef __DRV_IIC_H__
#define __DRV_IIC_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
struct efm32_iic_int_mode_t
{
    rt_uint8_t  *data_ptr;
    rt_uint8_t  data_size;
    rt_uint32_t read_index, save_index;
};

struct efm32_iic_device_t
{
    /* Counter */
    rt_uint32_t                 counter;
    /* Lock */
    struct rt_semaphore         *lock;
    /* Pointer to timer */
    rt_timer_t                  timer;
    /* Timeout flag */
    volatile rt_bool_t          timeout;
    /* State */
    rt_uint8_t                  state;
    /*  Pointer to IIC device structure */
    I2C_TypeDef                 *iic_device;
    /*  Self address */
    rt_uint16_t                 address;
    /* RX structure */
    struct efm32_iic_int_mode_t *rx_buffer;
};

struct efm32_iic_control_t
{
    rt_uint8_t      config;
    rt_uint16_t     address;
};

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define IIC_STATE_MASTER    (1 << 0)
#define IIC_STATE_BROADCAST (1 << 1)
//#define IIC_STATE_TX_BUSY     (1 << 2)
#define IIC_STATE_RX_BUSY   (1 << 3)
#define IIC_TIMEOUT_PERIOD  (RT_TICK_PER_SECOND)

#define IIC_OP_READ_ONLY    (0xFF)

/* Exported functions --------------------------------------------------------*/
void rt_hw_iic_init(void);

#endif /* __DRV_IIC_H__ */
