/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2019-10-23     yuzrain       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "board.h"
#include "drv_i2c.h"
#include "md_i2c.h"
#include "md_gpio.h"

#ifdef RT_USING_I2C

#define TIMEOUT 0xF
/* Define I2C hardware SCL timeout */
#define I2C_TIMING_48MHZ_CLK100KHZ   ((0xBU<<28)|(4<<20)|(2<<16)|(0xF<<8)|(0x13))

/**
  * @brief:  I2C receive.
  * @param:  i2cx, pointer to the I2Cx
  * @param:  addr, address
  * @param:  buf, send data buffer
  * @param:  len, the length of buf
  * @param:  timout, timeout
  * @retval: rt_err_t
  */
static rt_err_t __i2c_master_recv(I2C_TypeDef *i2cx, rt_uint16_t addr,
                          rt_uint8_t  *buf, rt_uint16_t len, rt_uint32_t timout)
{
    rt_uint32_t rt_timout;

    //
    // Config I2C transfer mode
    //
    md_i2c_set_con2_add10(i2cx, MD_I2C_ADDRESSINGMODE_7BIT);
    /* Config slaver address */
    md_i2c_set_con2_sadd(i2cx, addr);
    /* Config data size */
    md_i2c_set_con2_nbytes(i2cx, len);
    /* Reset TX FIFO */
    md_i2c_set_fcon_txfrst(i2cx, MD_I2C_TXFIFO_RESET);
    /* Config mode */
    md_i2c_set_con2_rd_wrn(i2cx, MD_I2C_MASTER_READ);
    /* Config auto-reload */
    md_i2c_set_con2_reload(i2cx, MD_I2C_NORELOAD_MODE);
    /* When NBYTES is matched, the communication will be automatically stop */
    md_i2c_set_con2_autoend(i2cx, MD_I2C_AUTOEND_MODE);
    /* Start the I2C communication */
    md_i2c_set_con2_start(i2cx, MD_I2C_START_GENERATION);

    while (len > 0)
    {
        /* Wait Rx FIFO non-empty */
        rt_timout = timout;
        while (md_i2c_is_active_stat_rxe(i2cx) && (--rt_timout));
        if (rt_timout == 0)
            return RT_ETIMEOUT;

        *buf++ = md_i2c_recv(i2cx);
        len--;
    }

    return RT_EOK;
}

/**
  * @brief:  I2C send.
  * @param:  i2cx, pointer to the I2Cx
  * @param:  addr, address
  * @param:  buf, send data buffer
  * @param:  len, the length of buf
  * @param:  timout, timeout
  * @retval: rt_err_t
  */
static rt_err_t __i2c_master_send(I2C_TypeDef *i2cx, rt_uint16_t addr,
                          rt_uint8_t  *buf, rt_uint16_t len, rt_uint32_t timout)
{
    rt_uint32_t rt_timout;
    rt_uint8_t index;

    //
    // Config I2C transfer mode
    //
    md_i2c_set_con2_add10(i2cx, MD_I2C_ADDRESSINGMODE_7BIT);
    /* Config slaver address */
    md_i2c_set_con2_sadd(i2cx, addr);
    /* Config data size */
    md_i2c_set_con2_nbytes(i2cx, len);
    /* Reset TX FIFO */
    md_i2c_set_fcon_txfrst(i2cx, MD_I2C_TXFIFO_RESET);
    /* Config mode */
    md_i2c_set_con2_rd_wrn(i2cx, MD_I2C_MASTER_WRITE);
    /* Enable auto-end */
    md_i2c_set_con2_autoend(i2cx, MD_I2C_AUTOEND_MODE);

    //
    // Check if the bus is busy
    //
    /* Wait bus to be ready */
    rt_timout   = timout;
    while ((READ_BIT(i2cx->STAT, I2C_STAT_BUSY_MSK) == I2C_STAT_BUSY_MSK) && (--rt_timout));
    if (rt_timout == 0)
        return RT_EBUSY;

    //
    // Start to send
    //
    if (len <= 8)
    {
        for (index = 0; index < len; index++)
            md_i2c_send(i2cx, *buf++);

        len = 0;
    }
    else
    {
        for (index = 0; index < 8; index++)
            md_i2c_send(i2cx, *buf++);

        len -= 8;
    }

    /* Start the I2C communication */
    md_i2c_set_con2_start(i2cx, MD_I2C_START_GENERATION);

    while (len > 0)
    {
        rt_timout   = timout;
        while (md_i2c_is_active_stat_txf(i2cx) && (--rt_timout));
        if (rt_timout == 0)
            return RT_ETIMEOUT;

        md_i2c_send(i2cx, *buf++);
        len--;
    }

    return RT_EOK;
}

static rt_size_t es32f0_master_xfer(struct rt_i2c_bus_device *bus,
                                    struct rt_i2c_msg msgs[],
                                    rt_uint32_t num)
{
    struct rt_i2c_msg *msg;
    rt_uint32_t i;
    rt_err_t ret = RT_ERROR;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        if (msg->flags & RT_I2C_RD)
        {
            if (__i2c_master_recv(bus->priv, msg->addr << 1, msg->buf, msg->len, TIMEOUT) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
        else
        {
            if (__i2c_master_send(bus->priv, msg->addr << 1, msg->buf, msg->len, TIMEOUT) != 0)
            {
                LOG_E("i2c bus write failed,i2c bus stop!\n");
                goto out;
            }
        }
    }

    ret = i;

out:
    LOG_E("send stop condition\n");

    return ret;
}

const struct rt_i2c_bus_device_ops es32f0_i2c_ops =
{
    es32f0_master_xfer,
    RT_NULL,
    RT_NULL,
};

static void _i2c_init(void)
{
    md_i2c_inittypedef I2C_Init =
    {
        .Timing     = CLK100kHz48M,
        .Address1   = 0x55 << 1,
        .AddrSize   = MD_I2C_ADDRESSINGMODE_7BIT,
        .DualAddressMode    = MD_I2C_DUALADDRESS_DISABLE,
        .Address2   = 0xAA,
        .Address2Masks      = MD_I2C_ADDR2_NOMASK
    };

#ifdef BSP_USING_I2C1
    /* Open I2C clock */
    SET_BIT(RCU->APB1EN, RCU_APB1EN_I2C1EN_MSK);

    /* GPIO configuration */
    md_gpio_set_pull        (GPIOC, MD_GPIO_PIN_12,  MD_GPIO_PULL_UP);
    md_gpio_set_pull        (GPIOD, MD_GPIO_PIN_2,   MD_GPIO_PULL_UP);
    md_gpio_set_output_type (GPIOC, MD_GPIO_PIN_12,  MD_GPIO_OUTPUT_OPENDRAIN);
    md_gpio_set_output_type (GPIOD, MD_GPIO_PIN_2,   MD_GPIO_OUTPUT_OPENDRAIN);
    md_gpio_set_mode        (GPIOC, MD_GPIO_PIN_12,  MD_GPIO_MODE_FUNCTION);
    md_gpio_set_mode        (GPIOD, MD_GPIO_PIN_2,   MD_GPIO_MODE_FUNCTION);
    md_gpio_set_function8_15(GPIOC, MD_GPIO_PIN_12,  MD_GPIO_AF1);
    md_gpio_set_function0_7 (GPIOD, MD_GPIO_PIN_2,   MD_GPIO_AF1);

    //
    // Config I2C
    //
    md_i2c_init(I2C1, &I2C_Init);
#endif

#ifdef BSP_USING_I2C2
    /* Open I2C clock */
    SET_BIT(RCU->APB1EN, RCU_APB1EN_I2C2EN_MSK);

    /* GPIO configuration */
    md_gpio_set_pull        (GPIOB, MD_GPIO_PIN_10,  MD_GPIO_PULL_UP);
    md_gpio_set_pull        (GPIOB, MD_GPIO_PIN_11,  MD_GPIO_PULL_UP);
    md_gpio_set_output_type (GPIOB, MD_GPIO_PIN_10,  MD_GPIO_OUTPUT_OPENDRAIN);
    md_gpio_set_output_type (GPIOB, MD_GPIO_PIN_11,  MD_GPIO_OUTPUT_OPENDRAIN);
    md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_10,  MD_GPIO_MODE_FUNCTION);
    md_gpio_set_mode        (GPIOB, MD_GPIO_PIN_11,  MD_GPIO_MODE_FUNCTION);
    md_gpio_set_function8_15(GPIOB, MD_GPIO_PIN_10,  MD_GPIO_AF1);
    md_gpio_set_function8_15(GPIOB, MD_GPIO_PIN_11,  MD_GPIO_AF1);

    //
    // Config I2C
    //
    md_i2c_init(I2C2, &I2C_Init);
#endif
}

#ifdef BSP_USING_I2C2
static struct rt_i2c_bus_device i2c_device2;
#endif

#ifdef BSP_USING_I2C1
static struct rt_i2c_bus_device i2c_device1;
#endif
int rt_hw_i2c_init(void)
{
    _i2c_init();

#ifdef BSP_USING_I2C2
    /* define i2c Instance */
    rt_memset((void *)&i2c_device2, 0, sizeof(struct rt_i2c_bus_device));
    i2c_device2.ops = &es32f0_i2c_ops;
    i2c_device2.priv = I2C2;
    rt_i2c_bus_device_register(&i2c_device2, "i2c2");
#endif

#ifdef BSP_USING_I2C1
    /* define i2c Instance */
    rt_memset((void *)&i2c_device1, 0, sizeof(struct rt_i2c_bus_device));
    i2c_device1.ops = &es32f0_i2c_ops;
    i2c_device1.priv = I2C1;
    rt_i2c_bus_device_register(&i2c_device1, "i2c1");
#endif

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2c_init);

#endif
