/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-08-22     Donocean     first version
 */

#include "board.h"

#ifdef RT_USING_I2C_HW

#if defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2) || defined(BSP_USING_I2C3)

#include "drv_i2c.h"
#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.i2c"
#include <drv_log.h>

enum
{
#ifdef BSP_USING_I2C1
    I2C1_INDEX,
#endif
#ifdef BSP_USING_I2C2
    I2C2_INDEX,
#endif
#ifdef BSP_USING_I2C3
    I2C3_INDEX,
#endif
};

static struct stm32_i2c_config i2c_config[] =
{
#ifdef BSP_USING_I2C1
    I2C1_BUS_CONFIG,
#endif

#ifdef BSP_USING_I2C2
    I2C2_BUS_CONFIG,
#endif

#ifdef BSP_USING_I2C3
    I2C3_BUS_CONFIG,
#endif
};

static struct stm32_i2c i2c_bus_obj[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

static rt_err_t _stm32_i2c_configure(struct rt_i2c_bus_device *device, struct rt_i2c_configuration *cfg)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    struct stm32_i2c *i2c_drv = rt_container_of(device, struct stm32_i2c, i2c_bus);
    I2C_HandleTypeDef *i2c_handle = &i2c_drv->handle;

    if (cfg->addr_length != 10)
        i2c_handle->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    else
        i2c_handle->Init.AddressingMode = I2C_ADDRESSINGMODE_10BIT;

    i2c_handle->Instance = i2c_drv->config->Instance;
    i2c_handle->Init.ClockSpeed = cfg->clk_speed;
    i2c_handle->Init.DutyCycle = I2C_DUTYCYCLE_2;
    i2c_handle->Init.OwnAddress1 = cfg->slave_addr;
    i2c_handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2c_handle->Init.OwnAddress2 = 0;
    i2c_handle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c_handle->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(i2c_handle) != HAL_OK)
    {
        return -RT_EIO;
    }

    /* TODO: support DMA configuration */

    LOG_D("%s init done", i2c_drv->config->bus_name);
    return RT_EOK;
}

static rt_ssize_t _i2c_mxfer(struct rt_i2c_bus_device *bus,
                             struct rt_i2c_msg msgs[],
                             rt_uint32_t num)
{
    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(msgs != RT_NULL);

    rt_uint32_t i;
    rt_ssize_t ret = 0;
    struct rt_i2c_msg *msg;
    HAL_StatusTypeDef status;

    struct stm32_i2c *i2c_drv = rt_container_of(bus, struct stm32_i2c, i2c_bus);
    I2C_HandleTypeDef *i2c_handle = &i2c_drv->handle;

    if (num == 0) return 0;

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        if (msg->flags & RT_I2C_RD)
        {
            if (i2c_handle->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
                status = HAL_I2C_Master_Receive(i2c_handle, msg->addr << 1, msg->buf, msg->len, bus->timeout);
            else
                status = HAL_I2C_Master_Receive(i2c_handle, msg->addr, msg->buf, msg->len, bus->timeout);

            if (status != HAL_OK)
                goto out;
            ret += msg->len;
        }
        else
        {
            if (i2c_handle->Init.AddressingMode == I2C_ADDRESSINGMODE_7BIT)
                status = HAL_I2C_Master_Transmit(i2c_handle, msg->addr << 1, msg->buf, msg->len, bus->timeout);
            else
                status = HAL_I2C_Master_Transmit(i2c_handle, msg->addr, msg->buf, msg->len, bus->timeout);

            if (status != HAL_OK)
                goto out;
            ret += msg->len;
        }
    }

out:
    return ret;
}

static const struct rt_i2c_bus_device_ops stm32_i2c_ops =
{
    .master_xfer = _i2c_mxfer,
    .configure = _stm32_i2c_configure,
    .slave_xfer = RT_NULL,
    .i2c_bus_control = RT_NULL,
};

static void _stm32_i2c_get_dma_config(void)
{
#ifdef BSP_USING_I2C1
    i2c_bus_obj[I2C1_INDEX].i2c_dma_flag = 0;
#ifdef BSP_I2C1_RX_USING_DMA
    i2c_bus_obj[I2C1_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config i2c1_dma_rx = I2C1_DMA_RX_CONFIG;
    i2c_config[I2C1_INDEX].dma_rx = &i2c1_dma_rx;
#endif
#ifdef BSP_I2C1_TX_USING_DMA
    i2c_bus_obj[I2C1_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config i2c1_dma_tx = I2C1_DMA_TX_CONFIG;
    i2c_config[I2C1_INDEX].dma_tx = &i2c1_dma_tx;
#endif
#endif

#ifdef BSP_USING_I2C2
    i2c_bus_obj[I2C2_INDEX].i2c_dma_flag = 0;
#ifdef BSP_I2C2_RX_USING_DMA
    i2c_bus_obj[I2C2_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config i2c2_dma_rx = I2C2_DMA_RX_CONFIG;
    i2c_config[I2C2_INDEX].dma_rx = &i2c2_dma_rx;
#endif
#ifdef BSP_I2C2_TX_USING_DMA
    i2c_bus_obj[I2C2_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config i2c2_dma_tx = I2C2_DMA_TX_CONFIG;
    i2c_config[I2C2_INDEX].dma_tx = &i2c2_dma_tx;
#endif
#endif

#ifdef BSP_USING_I2C3
    i2c_bus_obj[I2C3_INDEX].i2c_dma_flag = 0;
#ifdef BSP_I2C2_RX_USING_DMA
    i2c_bus_obj[I2C3_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static struct dma_config i2c3_dma_rx = I2C3_DMA_RX_CONFIG;
    i2c_config[I2C3_INDEX].dma_rx = &i2c3_dma_rx;
#endif
#ifdef BSP_I2C3_TX_USING_DMA
    i2c_bus_obj[I2C3_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static struct dma_config i2c3_dma_tx = I2C3_DMA_TX_CONFIG;
    i2c_config[I2C3_INDEX].dma_tx = &i2c3_dma_tx;
#endif
#endif
}

#if defined(BSP_USING_I2C1)
/**
  * @brief This function handles I2C1 event interrupt.
  */
void I2C1_EV_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    /* USER CODE END I2C1_EV_IRQn 0 */
    HAL_I2C_EV_IRQHandler(&i2c_bus_obj[I2C1_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
/**
  * @brief This function handles I2C1 error interrupt.
  */
void I2C1_ER_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_I2C_ER_IRQHandler(&i2c_bus_obj[I2C1_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_I2C2)
/**
  * @brief This function handles I2C2 event interrupt.
  */
void I2C2_EV_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_I2C_EV_IRQHandler(&i2c_bus_obj[I2C2_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
/**
  * @brief This function handles I2C2 error interrupt.
  */
void I2C2_ER_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_I2C_ER_IRQHandler(&i2c_bus_obj[I2C2_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#if defined(BSP_USING_I2C3)
/**
  * @brief This function handles I2C3 event interrupt.
  */
void I2C3_EV_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_I2C_EV_IRQHandler(&i2c_bus_obj[I2C3_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
/**
  * @brief This function handles I2C3 error interrupt.
  */
void I2C3_ER_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_I2C_ER_IRQHandler(&i2c_bus_obj[I2C3_INDEX].handle);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

int rt_hw_i2c_init(void)
{
    int result = 0;

    _stm32_i2c_get_dma_config();

    for (rt_size_t i = 0; i < sizeof(i2c_bus_obj) / sizeof(i2c_bus_obj[0]); i++)
    {
        /* init I2C object */
        i2c_bus_obj[i].config = &i2c_config[i];
        i2c_bus_obj[i].i2c_bus.ops = &stm32_i2c_ops;

        /* register I2C device */
        result = rt_i2c_bus_device_register(&i2c_bus_obj[i].i2c_bus, i2c_bus_obj[i].config->bus_name);
        RT_ASSERT(result == RT_EOK);

        LOG_D("%s bus init done", i2c_config[i].bus_name);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif /* BSP_USING_I2C1 || BSP_USING_I2C2 || BSP_USING_I2C3 */
#endif /* RT_USING_I2C */
