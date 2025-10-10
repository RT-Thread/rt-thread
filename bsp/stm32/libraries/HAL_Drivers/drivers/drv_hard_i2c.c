*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-17     Dyyt587   first version
 * 2024-04-23     Zeidan    fix bugs, test on STM32F429IGTx
 * 2024-12-10     zzk597    add support for STM32F1 series
 */
#include "drv_hard_i2c.h"
/* not fully support for I2C4 */
#if defined(BSP_USING_HARD_I2C1) || defined(BSP_USING_HARD_I2C2) || defined(BSP_USING_HARD_I2C3)
//#define DRV_DEBUG
#define LOG_TAG "drv.i2c.hw"
#include <drv_log.h>
enum
{
#ifdef BSP_USING_HARD_I2C1
    I2C1_INDEX,
#endif /* BSP_USING_HARD_I2C1 */
#ifdef BSP_USING_HARD_I2C2
    I2C2_INDEX,
#endif /* BSP_USING_HARD_I2C2 */
#ifdef BSP_USING_HARD_I2C3
    I2C3_INDEX,
#endif /* BSP_USING_HARD_I2C3 */
};
static struct stm32_i2c_config i2c_config[] =
{
#ifdef BSP_USING_HARD_I2C1
        I2C1_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C1 */
#ifdef BSP_USING_HARD_I2C2
        I2C2_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C2 */
#ifdef BSP_USING_HARD_I2C3
        I2C3_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C3 */
};

static struct stm32_i2c i2c_objs[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

static rt_err_t stm32_i2c_set_speed(struct rt_i2c_bus_device *bus, uint32_t speed)
{
    struct stm32_i2c *i2c_drv = rt_container_of(bus, struct stm32_i2c, i2c_bus);
    I2C_HandleTypeDef *i2c_handle = &i2c_drv->handle;
    rt_err_t ret = RT_EOK;

    RT_ASSERT(bus != RT_NULL);
    RT_ASSERT(speed > 0);

    LOG_D("Setting I2C speed to %d Hz", speed);

    /* De-initialize before reconfigure */
    if (HAL_I2C_DeInit(i2c_handle) != HAL_OK)
    {
        LOG_E("Failed to deinit I2C for speed change");
        return -RT_ERROR;
    }

    /* Reconfigure base parameters */
    rt_memset(i2c_handle, 0, sizeof(I2C_HandleTypeDef));
    i2c_handle->Instance = i2c_drv->config->Instance;

#if defined(SOC_SERIES_STM32H7)
    /* H7 uses Timing field */
    i2c_handle->Init.Timing = i2c_drv->config->timing;
#elif defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F4)
    /* F1/F4 uses ClockSpeed field */
    i2c_handle->Init.ClockSpeed = speed;
    i2c_handle->Init.DutyCycle = I2C_DUTYCYCLE_2;
#endif

    i2c_handle->Init.OwnAddress1 = 0;
    i2c_handle->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    i2c_handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2c_handle->Init.OwnAddress2 = 0;
    i2c_handle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c_handle->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(i2c_handle) != HAL_OK)
    {
        LOG_E("Failed to reinit I2C with new speed");
        return -RT_ERROR;
    }

#if defined(SOC_SERIES_STM32H7)
    /* Optional analog/digital filter settings */
    if (HAL_I2CEx_ConfigAnalogFilter(i2c_handle, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        LOG_E("Failed to configure analog filter");
        ret = -RT_ERROR;
    }

    if (HAL_I2CEx_ConfigDigitalFilter(i2c_handle, 0) != HAL_OK)
    {
        LOG_E("Failed to configure digital filter");
        ret = -RT_ERROR;
    }
#endif

    /* If DMA is enabled, reconfigure DMA and NVIC similar to boot init path */
    if (i2c_drv->i2c_dma_flag & I2C_USING_RX_DMA_FLAG)
    {
        i2c_drv->dma.handle_rx.Instance = i2c_drv->config->dma_rx->Instance;
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
        i2c_drv->dma.handle_rx.Init.Channel = i2c_drv->config->dma_rx->channel;
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
        i2c_drv->dma.handle_rx.Init.Request = i2c_drv->config->dma_rx->request;
#endif
#ifndef SOC_SERIES_STM32U5
        i2c_drv->dma.handle_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
        i2c_drv->dma.handle_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
        i2c_drv->dma.handle_rx.Init.MemInc              = DMA_MINC_ENABLE;
        i2c_drv->dma.handle_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        i2c_drv->dma.handle_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
        i2c_drv->dma.handle_rx.Init.Mode                = DMA_NORMAL;
        i2c_drv->dma.handle_rx.Init.Priority            = DMA_PRIORITY_LOW;
#endif
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7)
        i2c_drv->dma.handle_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
#endif
        HAL_DMA_DeInit(&i2c_drv->dma.handle_rx);
        HAL_DMA_Init(&i2c_drv->dma.handle_rx);
        __HAL_LINKDMA(&i2c_drv->handle, hdmarx, i2c_drv->dma.handle_rx);
        HAL_NVIC_SetPriority(i2c_drv->config->dma_rx->dma_irq, 0, 0);
        HAL_NVIC_EnableIRQ(i2c_drv->config->dma_rx->dma_irq);
    }

    if (i2c_drv->i2c_dma_flag & I2C_USING_TX_DMA_FLAG)
    {
        i2c_drv->dma.handle_tx.Instance = i2c_drv->config->dma_tx->Instance;
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
        i2c_drv->dma.handle_tx.Init.Channel = i2c_drv->config->dma_tx->channel;
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
        i2c_drv->dma.handle_tx.Init.Request = i2c_drv->config->dma_tx->request;
#endif
#ifndef SOC_SERIES_STM32U5
        i2c_drv->dma.handle_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
        i2c_drv->dma.handle_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
        i2c_drv->dma.handle_tx.Init.MemInc              = DMA_MINC_ENABLE;
        i2c_drv->dma.handle_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        i2c_drv->dma.handle_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
        i2c_drv->dma.handle_tx.Init.Mode                = DMA_NORMAL;
        i2c_drv->dma.handle_tx.Init.Priority            = DMA_PRIORITY_LOW;
#endif
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7)
        i2c_drv->dma.handle_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
        i2c_drv->dma.handle_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        i2c_drv->dma.handle_tx.Init.MemBurst            = DMA_MBURST_INC4;
        i2c_drv->dma.handle_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
#endif
        HAL_DMA_DeInit(&i2c_drv->dma.handle_tx);
        HAL_DMA_Init(&i2c_drv->dma.handle_tx);
        __HAL_LINKDMA(&i2c_drv->handle, hdmatx, i2c_drv->dma.handle_tx);
        HAL_NVIC_SetPriority(i2c_drv->config->dma_tx->dma_irq, 1, 0);
        HAL_NVIC_EnableIRQ(i2c_drv->config->dma_tx->dma_irq);
    }
