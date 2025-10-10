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
Comment on lines +52 to +165
Contributor
@wdfk-prog wdfk-prog on Aug 25
这段代码跟stm32_i2c_init重复了吧?
修改stm32_i2c_init名称为stm32_i2c_config,然后进行调用吧?

@kalai85	Reply...

    /* Ensure I2C event IRQ is enabled (needed even without DMA) */
    HAL_NVIC_SetPriority(i2c_drv->config->evirq_type, 2, 0);
    HAL_NVIC_EnableIRQ(i2c_drv->config->evirq_type);

    if (ret == RT_EOK)
    {
        LOG_D("I2C speed changed to %d Hz successfully (DMA/IRQ reconfigured)", speed);
Contributor
@wdfk-prog wdfk-prog on Aug 25
放到control做返回值判断后打印日志更好

@kalai85	Reply...
    }

    return ret;
}

static rt_err_t stm32_i2c_control(struct rt_i2c_bus_device *bus, int cmd, void *args)
{
    RT_ASSERT(bus != RT_NULL);

    switch (cmd)
    {
    case I2C_CTRL_SET_SPEED:
        if (args != RT_NULL)
        {
            uint32_t speed = *(uint32_t*)args;
            return stm32_i2c_set_speed(bus, speed);
        }
        return -RT_EINVAL;

    default:
        return -RT_ENOSYS;
    }
}
Comment on lines +183 to +196
Contributor
@wdfk-prog wdfk-prog on Aug 25
rt-thread/components/drivers/i2c/dev_i2c_dev.c

Lines 63 to 95 in af2c8ae

 static rt_err_t i2c_bus_device_control(rt_device_t dev, 
                                        int         cmd, 
                                        void       *args) 
 { 
     rt_err_t ret; 
     struct rt_i2c_priv_data *priv_data; 
     struct rt_i2c_bus_device *bus = (struct rt_i2c_bus_device *)dev->user_data; 
  
     RT_ASSERT(bus != RT_NULL); 
  
     switch (cmd) 
     { 
     /* set 10-bit addr mode */ 
     case RT_I2C_DEV_CTRL_10BIT: 
         bus->flags |= RT_I2C_ADDR_10BIT; 
         break; 
     case RT_I2C_DEV_CTRL_TIMEOUT: 
         bus->timeout = *(rt_uint32_t *)args; 
         break; 
     case RT_I2C_DEV_CTRL_RW: 
         priv_data = (struct rt_i2c_priv_data *)args; 
         ret = rt_i2c_transfer(bus, priv_data->msgs, priv_data->number); 
         if (ret < 0) 
         { 
             return -RT_EIO; 
         } 
         break; 
     default: 
         return rt_i2c_control(bus, cmd, args); 
     } 
  
     return RT_EOK; 
 } 
建议参考这里的写法
@kalai85	Reply...

static rt_err_t stm32_i2c_init(struct stm32_i2c *i2c_drv)
{
    RT_ASSERT(i2c_drv != RT_NULL);
    I2C_HandleTypeDef *i2c_handle = &i2c_drv->handle;
    struct stm32_i2c_config *cfg = i2c_drv->config;
    rt_memset(i2c_handle, 0, sizeof(I2C_HandleTypeDef));
    i2c_handle->Instance = cfg->Instance;
#if defined(SOC_SERIES_STM32H7)
    i2c_handle->Init.Timing = cfg->timing;
#endif /* defined(SOC_SERIES_STM32H7) */
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F4)
    i2c_handle->Init.ClockSpeed = 100000;
    i2c_handle->Init.DutyCycle = I2C_DUTYCYCLE_2;
#endif /* defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32F4) */
    i2c_handle->Init.OwnAddress1 = 0;
    i2c_handle->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    i2c_handle->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2c_handle->Init.OwnAddress2 = 0;
    i2c_handle->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c_handle->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_DeInit(i2c_handle) != HAL_OK)
    {
        return -RT_EFAULT;
    }
    if (HAL_I2C_Init(i2c_handle) != HAL_OK)
    {
        return -RT_EFAULT;
    }
#if defined(SOC_SERIES_STM32H7)
    /* Configure Analogue filter */
    if (HAL_I2CEx_ConfigAnalogFilter(i2c_handle, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
    {
        return -RT_EFAULT;
    }
    /* Configure Digital filter */
    if (HAL_I2CEx_ConfigDigitalFilter(i2c_handle, 0) != HAL_OK)
    {
        return -RT_EFAULT;
    }
#endif /* defined(SOC_SERIES_STM32H7) */
    /* I2C2 DMA Init */
    if (i2c_drv->i2c_dma_flag & I2C_USING_RX_DMA_FLAG)
    {
        HAL_DMA_Init(&i2c_drv->dma.handle_rx);
        __HAL_LINKDMA(&i2c_drv->handle, hdmarx, i2c_drv->dma.handle_rx);
        /* NVIC configuration for DMA transfer complete interrupt */
        HAL_NVIC_SetPriority(i2c_drv->config->dma_rx->dma_irq, 0, 0);
        HAL_NVIC_EnableIRQ(i2c_drv->config->dma_rx->dma_irq);
    }
    if (i2c_drv->i2c_dma_flag & I2C_USING_TX_DMA_FLAG)
    {
        HAL_DMA_Init(&i2c_drv->dma.handle_tx);
        __HAL_LINKDMA(&i2c_drv->handle, hdmatx, i2c_drv->dma.handle_tx);
        /* NVIC configuration for DMA transfer complete interrupt */
        HAL_NVIC_SetPriority(i2c_drv->config->dma_tx->dma_irq, 1, 0);
        HAL_NVIC_EnableIRQ(i2c_drv->config->dma_tx->dma_irq);
    }
    /* In the data transfer function stm32_i2c_master_xfer(), the IT transfer function
       HAL_I2C_Master_Seq_Transmit_IT() is used when DMA is not used, so the IT interrupt
       must be enable anyway, regardless of the DMA configuration, otherwise
       the rt_completion_wait() will always timeout. */
    HAL_NVIC_SetPriority(i2c_drv->config->evirq_type, 2, 0);
    HAL_NVIC_EnableIRQ(i2c_drv->config->evirq_type);
    return RT_EOK;
}
static rt_err_t stm32_i2c_configure(struct rt_i2c_bus_device *bus)
{
    RT_ASSERT(RT_NULL != bus);
    struct stm32_i2c *i2c_drv = rt_container_of(bus, struct stm32_i2c, i2c_bus);
    return stm32_i2c_init(i2c_drv);
}
/**
 * @brief Hardware I2C driver transfer
 *
 * @param bus Device bus
 * @param msgs Data to be transferred
 * @param num Number of data
 * @return rt_ssize_t Transfer status
 */
static rt_ssize_t stm32_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                                        struct rt_i2c_msg msgs[],
                                        rt_uint32_t num)
{
    /* for stm32 dma may more stability */
#define DMA_TRANS_MIN_LEN 2 /* only buffer length >= DMA_TRANS_MIN_LEN will use DMA mode */
#define TRANS_TIMEOUT_PERSEC 8 /* per ms will trans nums bytes */
    rt_int32_t i, ret;
    struct rt_i2c_msg *msg = msgs;
    struct rt_i2c_msg *next_msg = 0;
    struct stm32_i2c *i2c_obj;
    uint32_t mode = 0;
    uint8_t next_flag = 0;
    struct rt_completion *completion;
    rt_uint32_t timeout;
    if (num == 0)
    {
        return 0;
    }
    RT_ASSERT((msgs != RT_NULL) && (bus != RT_NULL));
    i2c_obj = rt_container_of(bus, struct stm32_i2c, i2c_bus);
    completion = &i2c_obj->completion;
    I2C_HandleTypeDef *handle = &i2c_obj->handle;
    LOG_D("xfer start %d mags", num);
    for (i = 0; i < (num - 1); i++)
    {
        mode = 0;
        msg = &msgs[i];
        LOG_D("xfer       msgs[%d] addr=0x%2x buf=0x%x len= 0x%x flags= 0x%x", i, msg->addr, msg->buf, msg->len, msg->flags);
        next_msg = &msgs[i + 1];
        next_flag = next_msg->flags;
        timeout = msg->len/TRANS_TIMEOUT_PERSEC + 5;
        if (next_flag & RT_I2C_NO_START)
        {
            if ((next_flag & RT_I2C_RD) == (msg->flags & RT_I2C_RD))
            { /* The same mode, can use no start */
                mode = I2C_FIRST_AND_NEXT_FRAME;
            }
            else
            {
                /* Not allowed to use no start, sending address is required when changing direction, user setting error */
                LOG_W("user set flags error msg[%d] flags RT_I2C_NO_START has canceled", i + 1);
                mode = I2C_LAST_FRAME_NO_STOP;
            }
        }
        else
        {
            mode = I2C_LAST_FRAME_NO_STOP;
        }
        if (msg->flags & RT_I2C_RD)
        {
            LOG_D("xfer  rec  msgs[%d] hal mode = %s", i, mode == I2C_FIRST_AND_NEXT_FRAME ? "I2C_FIRST_AND_NEXT_FRAME" : mode == I2C_LAST_FRAME_NO_STOP ? "I2C_FIRST_FRAME/I2C_LAST_FRAME_NO_STOP"
                                                                                                                      : mode == I2C_LAST_FRAME           ? "I2C_LAST_FRAME"
                                                                                                                                                         : "nuknown mode");
            if ((i2c_obj->i2c_dma_flag & I2C_USING_RX_DMA_FLAG) && (msg->len >= DMA_TRANS_MIN_LEN))
            {
                ret = HAL_I2C_Master_Seq_Receive_DMA(handle, (msg->addr<<1), msg->buf, msg->len, mode);
            }
            else
            {
                ret = HAL_I2C_Master_Seq_Receive_IT(handle, (msg->addr<<1), msg->buf, msg->len, mode);
            }
            if (ret != RT_EOK)
            {
                LOG_E("[%s:%d]I2C Read error(%d)!\n", __func__, __LINE__, ret);
                goto out;
            }
            if (rt_completion_wait(completion, timeout) != RT_EOK)
            {
                LOG_D("receive time out");
                                goto out;
            }
        }
        else
        {
            LOG_D("xfer trans msgs[%d] hal mode = %s", i, mode == I2C_FIRST_AND_NEXT_FRAME ? "I2C_FIRST_AND_NEXT_FRAME" : mode == I2C_LAST_FRAME_NO_STOP ? "I2C_FIRST_FRAME/I2C_LAST_FRAME_NO_STOP"
                                                                                                                      : mode == I2C_LAST_FRAME           ? "I2C_LAST_FRAME"
                                                                                                                                                         : "nuknown mode");
            if ((i2c_obj->i2c_dma_flag & I2C_USING_TX_DMA_FLAG) && (msg->len >= DMA_TRANS_MIN_LEN))
            {
                ret = HAL_I2C_Master_Seq_Transmit_DMA(handle, (msg->addr<<1), msg->buf, msg->len, mode);
            }
            else
            {
                ret = HAL_I2C_Master_Seq_Transmit_IT(handle, (msg->addr<<1), msg->buf, msg->len, mode);
            }
            if (ret != RT_EOK)
            {
                LOG_D("[%s:%d]I2C Write error(%d)!\n", __func__, __LINE__, ret);
                goto out;
            }
            if (rt_completion_wait(completion, timeout) != RT_EOK)
            {
                LOG_D("transmit time out");
                                goto out;
            }
        }
        LOG_D("xfer  next msgs[%d] addr=0x%2x buf= 0x%x len= 0x%x flags = 0x%x\r\n", i + 1, next_msg->addr, next_msg->buf, next_msg->len, next_msg->flags);
    }
    /* last msg */
    msg = &msgs[i];
        timeout = msg->len/TRANS_TIMEOUT_PERSEC + 5;
    if (msg->flags & RT_I2C_NO_STOP)
        mode = I2C_LAST_FRAME_NO_STOP;
    else
        mode = I2C_LAST_FRAME;
    LOG_D("xfer  last msgs[%d] addr=0x%2x buf= 0x%x len= 0x%x flags = 0x%x", i, msg->addr, msg->buf, msg->len, msg->flags);
    if (msg->flags & RT_I2C_RD)
    {
        LOG_D("xfer  rec  msgs[%d] hal mode=%s", i, mode == I2C_FIRST_AND_NEXT_FRAME ? "I2C_FIRST_AND_NEXT_FRAME" : mode == I2C_LAST_FRAME_NO_STOP ? "I2C_FIRST_FRAME/I2C_LAST_FRAME_NO_STOP"
                                                                                                                : mode == I2C_LAST_FRAME           ? "I2C_LAST_FRAME"
                                                                                                                                                   : "nuknown mode");
        if ((i2c_obj->i2c_dma_flag & I2C_USING_RX_DMA_FLAG) && (msg->len >= DMA_TRANS_MIN_LEN))
        {
            ret = HAL_I2C_Master_Seq_Receive_DMA(handle, (msg->addr<<1), msg->buf, msg->len, mode);
        }
        else
        {
            ret = HAL_I2C_Master_Seq_Receive_IT(handle,(msg->addr<<1), msg->buf, msg->len, mode);
        }
        if (ret != RT_EOK)
        {
            LOG_D("[%s:%d]I2C Read error(%d)!\n", __func__, __LINE__, ret);
            goto out;
        }
        if (rt_completion_wait(completion, timeout) != RT_EOK)
        {
            LOG_D("receive time out");
            goto out;
        }
    }
    else
    {
        LOG_D("xfer trans msgs[%d] hal mode = %s", i, mode == I2C_FIRST_AND_NEXT_FRAME ? "I2C_FIRST_AND_NEXT_FRAME" : mode == I2C_LAST_FRAME       ? "I2C_LAST_FRAME"
                                                                                                                  : mode == I2C_LAST_FRAME_NO_STOP ? "I2C_FIRST_FRAME/I2C_LAST_FRAME_NO_STOP"
                                                                                                                                                   : "nuknown mode");
        if ((i2c_obj->i2c_dma_flag & I2C_USING_TX_DMA_FLAG) && (msg->len >= DMA_TRANS_MIN_LEN))
        {
            ret = HAL_I2C_Master_Seq_Transmit_DMA(handle, (msg->addr<<1), msg->buf, msg->len, mode);
        }
        else
        {
            ret = HAL_I2C_Master_Seq_Transmit_IT(handle, (msg->addr<<1), msg->buf, msg->len, mode);
        }
        if (ret != RT_EOK)
        {
            LOG_D("[%s:%d]I2C Write error(%d)!\n", __func__, __LINE__, ret);
            goto out;
        }
        if (rt_completion_wait(completion, timeout) != RT_EOK)
        {
            LOG_D("transmit time out");
            goto out;
        }
    }
    ret = num;
    LOG_D("xfer  end  %d mags\r\n", num);
    return ret;
out:
    if (handle->ErrorCode == HAL_I2C_ERROR_AF)
    {
        LOG_D("I2C NACK Error now stoped");
        /* Send stop signal to prevent bus lock-up */
#if defined(SOC_SERIES_STM32H7)
        handle->Instance->CR1 |= I2C_IT_STOPI;
#endif /* defined(SOC_SERIES_STM32H7) */
    }
    if (handle->ErrorCode == HAL_I2C_ERROR_BERR)
    {
        LOG_D("I2C BUS Error now stoped");
        handle->Instance->CR1 |= I2C_CR1_STOP;
        ret=i-1;
    }
    return ret;
}

static const struct rt_i2c_bus_device_ops stm32_i2c_ops =
{
    .master_xfer = stm32_i2c_master_xfer,
    RT_NULL,
    RT_NULL
};
static const struct rt_i2c_bus_device_ops stm32_i2c_ops = {
    .master_xfer = stm32_i2c_master_xfer, .slave_xfer = RT_NULL, .i2c_bus_control = stm32_i2c_control};
Contributor
@wdfk-prog wdfk-prog on Aug 25
按照原来的格式排版^__^
@kalai85	Reply...
Comment on lines +477 to +478
Copilot AI
2 weeks ago
[best_practices/最佳实践]: The structure initialization should follow RT-Thread coding standards with proper formatting.

English: The structure should be formatted with each field on a separate line for better readability and consistency with RT-Thread coding standards.
中文：结构体初始化应遵循RT-Thread编码标准，每个字段占单独一行以提高可读性和保持一致性。

Example/示例:

static const struct rt_i2c_bus_device_ops stm32_i2c_ops =
{
.master_xfer = stm32_i2c_master_xfer,
.slave_xfer = RT_NULL,
.i2c_bus_control = stm32_i2c_control
};
Suggested change
static const struct rt_i2c_bus_device_ops stm32_i2c_ops = {
    .master_xfer = stm32_i2c_master_xfer, .slave_xfer = RT_NULL, .i2c_bus_control = stm32_i2c_control};
static const struct rt_i2c_bus_device_ops stm32_i2c_ops =
{
    .master_xfer = stm32_i2c_master_xfer,
    .slave_xfer = RT_NULL,
    .i2c_bus_control = stm32_i2c_control
};
Copilot uses AI. Check for mistakes.

@kalai85	Reply...

int RT_hw_i2c_bus_init(void)
{
    int ret = -RT_ERROR;
    rt_size_t obj_num = sizeof(i2c_objs) / sizeof(i2c_objs[0]);
    for (int i = 0; i < obj_num; i++)
    {
        i2c_objs[i].i2c_bus.ops = &stm32_i2c_ops;
        i2c_objs[i].config = &i2c_config[i];
        i2c_objs[i].i2c_bus.timeout = i2c_config[i].timeout;
        if ((i2c_objs[i].i2c_dma_flag & I2C_USING_RX_DMA_FLAG))
        {
            i2c_objs[i].dma.handle_rx.Instance = i2c_config[i].dma_rx->Instance;
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
            i2c_objs[i].dma.handle_rx.Init.Channel = i2c_config[i].dma_rx->channel;
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
            i2c_objs[i].dma.handle_rx.Init.Request = i2c_config[i].dma_rx->request;
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#ifndef SOC_SERIES_STM32U5
            i2c_objs[i].dma.handle_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
            i2c_objs[i].dma.handle_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
            i2c_objs[i].dma.handle_rx.Init.MemInc              = DMA_MINC_ENABLE;
            i2c_objs[i].dma.handle_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            i2c_objs[i].dma.handle_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
            i2c_objs[i].dma.handle_rx.Init.Mode                = DMA_NORMAL;
            i2c_objs[i].dma.handle_rx.Init.Priority            = DMA_PRIORITY_LOW;
#endif
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7)
            i2c_objs[i].dma.handle_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
            i2c_objs[i].dma.handle_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
            i2c_objs[i].dma.handle_tx.Init.MemBurst            = DMA_MBURST_INC4;
            i2c_objs[i].dma.handle_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7) */
            {
                rt_uint32_t tmpreg = 0x00U;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32F0)
                /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
                SET_BIT(RCC->AHBENR, i2c_config[i].dma_rx->dma_rcc);
                tmpreg = READ_BIT(RCC->AHBENR, i2c_config[i].dma_rx->dma_rcc);
#elif defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
                SET_BIT(RCC->AHB1ENR, i2c_config[i].dma_rx->dma_rcc);
                /* Delay after an RCC peripheral clock enabling */
                tmpreg = READ_BIT(RCC->AHB1ENR, i2c_config[i].dma_rx->dma_rcc);
#elif defined(SOC_SERIES_STM32MP1)
                __HAL_RCC_DMAMUX_CLK_ENABLE();
                SET_BIT(RCC->MP_AHB2ENSETR, i2c_config[i].dma_rx->dma_rcc);
                tmpreg = READ_BIT(RCC->MP_AHB2ENSETR, i2c_config[i].dma_rx->dma_rcc);
#endif /* defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32F0) */
                UNUSED(tmpreg); /* To avoid compiler warnings */
            }
        }
        if (i2c_objs[i].i2c_dma_flag & I2C_USING_TX_DMA_FLAG)
        {
            i2c_objs[i].dma.handle_tx.Instance = i2c_config[i].dma_tx->Instance;
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7)
            i2c_objs[i].dma.handle_tx.Init.Channel = i2c_config[i].dma_tx->channel;
#elif defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
            i2c_objs[i].dma.handle_tx.Init.Request = i2c_config[i].dma_tx->request;
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) */
#ifndef SOC_SERIES_STM32U5
            i2c_objs[i].dma.handle_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
            i2c_objs[i].dma.handle_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
            i2c_objs[i].dma.handle_tx.Init.MemInc              = DMA_MINC_ENABLE;
            i2c_objs[i].dma.handle_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            i2c_objs[i].dma.handle_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
            i2c_objs[i].dma.handle_tx.Init.Mode                = DMA_NORMAL;
            i2c_objs[i].dma.handle_tx.Init.Priority            = DMA_PRIORITY_LOW;
#endif
#if defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7)
            i2c_objs[i].dma.handle_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
            i2c_objs[i].dma.handle_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
            i2c_objs[i].dma.handle_tx.Init.MemBurst            = DMA_MBURST_INC4;
            i2c_objs[i].dma.handle_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
#endif /* defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32MP1) || defined(SOC_SERIES_STM32H7) */
            {
                rt_uint32_t tmpreg = 0x00U;
#if defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32F0)
                /* enable DMA clock && Delay after an RCC peripheral clock enabling*/
                SET_BIT(RCC->AHBENR, i2c_config[i].dma_tx->dma_rcc);
                tmpreg = READ_BIT(RCC->AHBENR, i2c_config[i].dma_tx->dma_rcc);
#elif defined(SOC_SERIES_STM32F2) || defined(SOC_SERIES_STM32F4) || defined(SOC_SERIES_STM32F7) || defined(SOC_SERIES_STM32L4) || defined(SOC_SERIES_STM32WB) || defined(SOC_SERIES_STM32H7)
                SET_BIT(RCC->AHB1ENR, i2c_config[i].dma_tx->dma_rcc);
                /* Delay after an RCC peripheral clock enabling */
                tmpreg = READ_BIT(RCC->AHB1ENR, i2c_config[i].dma_tx->dma_rcc);
#elif defined(SOC_SERIES_STM32MP1)
                __HAL_RCC_DMAMUX_CLK_ENABLE();
                SET_BIT(RCC->MP_AHB2ENSETR, i2c_config[i].dma_tx->dma_rcc);
                tmpreg = READ_BIT(RCC->MP_AHB2ENSETR, i2c_config[i].dma_tx->dma_rcc);
#endif /* defined(SOC_SERIES_STM32F1) || defined(SOC_SERIES_STM32G0) || defined(SOC_SERIES_STM32F0) */
                UNUSED(tmpreg); /* To avoid compiler warnings */
            }
        }
        rt_completion_init(&i2c_objs[i].completion);
        stm32_i2c_configure(&i2c_objs[i].i2c_bus);
        ret = rt_i2c_bus_device_register(&i2c_objs[i].i2c_bus, i2c_objs[i].config->name);
        RT_ASSERT(ret == RT_EOK);
        LOG_D("%s bus init done", i2c_config[i].name);
    }
    return ret;
}
static void stm32_get_dma_info(void)
{
#ifdef BSP_I2C1_RX_USING_DMA
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C1_dma_rx = I2C1_RX_DMA_CONFIG;
    i2c_config[I2C1_INDEX].dma_rx = &I2C1_dma_rx;
#endif /* BSP_I2C1_RX_USING_DMA */
#ifdef BSP_I2C1_TX_USING_DMA
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C1_dma_tx = I2C1_TX_DMA_CONFIG;
    i2c_config[I2C1_INDEX].dma_tx = &I2C1_dma_tx;
#endif /* BSP_I2C1_TX_USING_DMA */
#ifdef BSP_I2C2_RX_USING_DMA
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C2_dma_rx = I2C2_RX_DMA_CONFIG;
    i2c_config[I2C2_INDEX].dma_rx = &I2C2_dma_rx;
#endif /* BSP_I2C2_RX_USING_DMA */
#ifdef BSP_I2C2_TX_USING_DMA
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C2_dma_tx = I2C2_TX_DMA_CONFIG;
    i2c_config[I2C2_INDEX].dma_tx = &I2C2_dma_tx;
#endif /* BSP_I2C2_TX_USING_DMA */
#ifdef BSP_I2C3_RX_USING_DMA
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    static struct dma_config I2C3_dma_rx = I2C3_RX_DMA_CONFIG;
    i2c_config[I2C3_INDEX].dma_rx = &I2C3_dma_rx;
#endif /* BSP_I2C3_RX_USING_DMA */
#ifdef BSP_I2C3_TX_USING_DMA
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    static struct dma_config I2C3_dma_tx = I2C3_TX_DMA_CONFIG;
    i2c_config[I2C3_INDEX].dma_tx = &I2C3_dma_tx;
#endif /* BSP_I2C3_TX_USING_DMA */
}
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    struct stm32_i2c *i2c_drv = rt_container_of(hi2c, struct stm32_i2c, handle);
    rt_completion_done(&i2c_drv->completion);
}
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    struct stm32_i2c *i2c_drv = rt_container_of(hi2c, struct stm32_i2c, handle);
    rt_completion_done(&i2c_drv->completion);
}
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
#if defined(SOC_SERIES_STM32H7)
    /* Send stop signal to prevent bus lock-up */
    if (hi2c->ErrorCode == HAL_I2C_ERROR_AF)
    {
        LOG_D("I2C NACK Error now stoped");
        hi2c->Instance->CR1 |= I2C_IT_STOPI;
    }
    if (hi2c->ErrorCode == HAL_I2C_ERROR_BERR)
    {
        LOG_D("I2C BUS Error now stoped");
        hi2c->Instance->CR1 |= I2C_IT_STOPI;
    }
#endif /* defined(SOC_SERIES_STM32H7) */
}
#ifdef BSP_USING_HARD_I2C1
/**
 * @brief This function handles I2C2 event interrupt.
 */
void I2C1_EV_IRQHandler(void)
{
    /* USER CODE BEGIN I2C2_EV_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C2_EV_IRQn 0 */
    HAL_I2C_EV_IRQHandler(&i2c_objs[I2C1_INDEX].handle);
    /* USER CODE BEGIN I2C2_EV_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C2_EV_IRQn 1 */
}
/**
 * @brief This function handles I2C2 error interrupt.
 */
void I2C1_ER_IRQHandler(void)
{
    /* USER CODE BEGIN I2C2_ER_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C2_ER_IRQn 0 */
    HAL_I2C_ER_IRQHandler(&i2c_objs[I2C1_INDEX].handle);
    /* USER CODE BEGIN I2C2_ER_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C2_ER_IRQn 1 */
}
#endif /* BSP_USING_HARD_I2C1 */
#ifdef BSP_USING_HARD_I2C2
/**
 * @brief This function handles I2C2 event interrupt.
 */
void I2C2_EV_IRQHandler(void)
{
    /* USER CODE BEGIN I2C2_EV_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C2_EV_IRQn 0 */
    HAL_I2C_EV_IRQHandler(&i2c_objs[I2C2_INDEX].handle);
    /* USER CODE BEGIN I2C2_EV_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C2_EV_IRQn 1 */
}
/**
 * @brief This function handles I2C2 error interrupt.
 */
void I2C2_ER_IRQHandler(void)
{
    /* USER CODE BEGIN I2C2_ER_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C2_ER_IRQn 0 */
    HAL_I2C_ER_IRQHandler(&i2c_objs[I2C2_INDEX].handle);
    /* USER CODE BEGIN I2C2_ER_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C2_ER_IRQn 1 */
}
#endif /* BSP_USING_HARD_I2C2 */
#ifdef BSP_USING_HARD_I2C3
/**
 * @brief This function handles I2C2 event interrupt.
 */
void I2C3_EV_IRQHandler(void)
{
    /* USER CODE BEGIN I2C2_EV_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C2_EV_IRQn 0 */
    HAL_I2C_EV_IRQHandler(&i2c_objs[I2C3_INDEX].handle);
    /* USER CODE BEGIN I2C2_EV_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C2_EV_IRQn 1 */
}
/**
 * @brief This function handles I2C2 error interrupt.
 */
void I2C3_ER_IRQHandler(void)
{
    /* USER CODE BEGIN I2C2_ER_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C2_ER_IRQn 0 */
    HAL_I2C_ER_IRQHandler(&i2c_objs[I2C3_INDEX].handle);
    /* USER CODE BEGIN I2C2_ER_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C2_ER_IRQn 1 */
}
#endif /* BSP_USING_HARD_I2C3 */
#if defined(BSP_USING_HARD_I2C1) && defined(BSP_I2C1_RX_USING_DMA)
/**
 * @brief  This function handles DMA Rx interrupt request.
 * @param  None
 * @retval None
 */
void I2C1_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&i2c_objs[I2C1_INDEX].dma.handle_rx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_HARD_I2C1) && defined(BSP_I2C1_RX_USING_DMA) */
#if defined(BSP_USING_HARD_I2C1) && defined(BSP_I2C1_TX_USING_DMA)
/**
 * @brief  This function handles DMA Rx interrupt request.
 * @param  None
 * @retval None
 */
void I2C1_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&i2c_objs[I2C1_INDEX].dma.handle_tx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_HARD_I2C1) && defined(BSP_I2C1_TX_USING_DMA) */
#if defined(BSP_USING_HARD_I2C2) && defined(BSP_I2C2_RX_USING_DMA)
/**
 * @brief  This function handles DMA Rx interrupt request.
 * @param  None
 * @retval None
 */
void I2C2_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&i2c_objs[I2C2_INDEX].dma.handle_rx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_HARD_I2C2) && defined(BSP_I2C2_RX_USING_DMA) */
#if defined(BSP_USING_HARD_I2C2) && defined(BSP_I2C2_TX_USING_DMA)
/**
 * @brief  This function handles DMA Rx interrupt request.
 * @param  None
 * @retval None
 */
void I2C2_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&i2c_objs[I2C2_INDEX].dma.handle_tx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_HARD_I2C2) && defined(BSP_I2C2_TX_USING_DMA) */
#if defined(BSP_USING_HARD_I2C3) && defined(BSP_I2C3_RX_USING_DMA)
/**
 * @brief  This function handles DMA Rx interrupt request.
 * @param  None
 * @retval None
 */
void I2C3_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&i2c_objs[I2C3_INDEX].dma.handle_rx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_HARD_I2C3) && defined(BSP_I2C3_RX_USING_DMA) */
#if defined(BSP_USING_HARD_I2C3) && defined(BSP_I2C3_TX_USING_DMA)
/**
 * @brief  This function handles DMA Rx interrupt request.
 * @param  None
 * @retval None
 */
void I2C3_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(&i2c_objs[I2C3_INDEX].dma.handle_tx);
    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_HARD_I2C3) && defined(BSP_I2C3_TX_USING_DMA) */
int rt_hw_hw_i2c_init(void)
{
    stm32_get_dma_info();
    return RT_hw_i2c_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_hw_i2c_init);
#endif /* defined(BSP_USING_HARD_I2C1) || defined(BSP_USING_HARD_I2C2) || defined(BSP_USING_HARD_I2C3) */
  3 changes: 3 additions & 0 deletions3  
bsp/stm32/libraries/HAL_Drivers/drivers/drv_hard_i2c.h
Viewed
Original file line number	Diff line number	Diff line change
@@ -22,6 +22,9 @@ extern "C"
{
#endif

/* I2C bus control command ids */
#define I2C_CTRL_SET_SPEED              (0x01U)
Contributor
@wdfk-prog wdfk-prog on Aug 25
这个标志位可以向上提到这里

rt-thread/components/drivers/include/drivers/dev_i2c.h

Lines 180 to 196 in af2c8ae

 #define RT_I2C_WR                0x0000    /*!< i2c wirte flag */ 
 #define RT_I2C_RD               (1u << 0)  /*!< i2c read flag  */ 
 #define RT_I2C_ADDR_10BIT       (1u << 2)  /*!< this is a ten bit chip address */ 
 #define RT_I2C_NO_START         (1u << 4)  /*!< do not generate START condition */ 
 #define RT_I2C_IGNORE_NACK      (1u << 5)  /*!< ignore NACK from slave */ 
 #define RT_I2C_NO_READ_ACK      (1u << 6)  /* when I2C reading, we do not ACK */ 
 #define RT_I2C_NO_STOP          (1u << 7)  /*!< do not generate STOP condition */ 
  
 #define RT_I2C_DEV_CTRL_10BIT        (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x01) 
 #define RT_I2C_DEV_CTRL_ADDR         (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x02) 
 #define RT_I2C_DEV_CTRL_TIMEOUT      (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x03) 
 #define RT_I2C_DEV_CTRL_RW           (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x04) 
 #define RT_I2C_DEV_CTRL_CLK          (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x05) 
 #define RT_I2C_DEV_CTRL_UNLOCK       (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x06) 
 #define RT_I2C_DEV_CTRL_GET_STATE    (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x07) 
 #define RT_I2C_DEV_CTRL_GET_MODE     (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x08) 
 #define RT_I2C_DEV_CTRL_GET_ERROR    (RT_DEVICE_CTRL_BASE(I2CBUS) + 0x09) 
@kalai85	Reply...

struct stm32_i2c_config
{
    const char        *name;
