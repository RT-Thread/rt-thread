/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-17     Dyyt587   first version
 * 2024-04-23     Zeidan    fix bugs, test on STM32F429IGTx
 * 2024-12-10     zzk597    add support for STM32F1 series
 * 2024-06-23     wdfk-prog Add blocking modes and distinguish POLL,INT,DMA modes
 * 2024-06-23     wdfk-prog Distinguish STM32 I2C timing semantics by IP generation
 * 2026-04-20     wdfk-prog Stabilize async completion and recovery flow
 */

#include "drv_hard_i2c.h"

#if defined(BSP_HARDWARE_I2C)

// #define DRV_DEBUG
#define LOG_TAG "drv.i2c.hw"
#include <drv_log.h>

/*
 * Default timing values follow the IP generation split declared in
 * drv_hard_i2c.h:
 * - legacy IP  (F1/F4): timing is the bus speed in Hz
 * - TIMINGR IP (F7/H7): timing is the raw I2C_TIMINGR value
 */
#if defined(STM32_I2C_TIMINGR_IP)
#define DEFAULT_I2C_TIMING_VALUE 0x307075B1U    // 100K
#else
#define DEFAULT_I2C_TIMING_VALUE (100*1000U)    //HZ
#endif

/* only buffer length >= DMA_TRANS_MIN_LEN will use DMA mode */
#define DMA_TRANS_MIN_LEN 2

typedef enum
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
#ifdef BSP_USING_HARD_I2C4
    I2C4_INDEX,
#endif /* BSP_USING_HARD_I2C4 */
}i2c_index_t;

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
#ifdef BSP_USING_HARD_I2C4
        I2C4_BUS_CONFIG,
#endif /* BSP_USING_HARD_I2C4 */
};

static struct stm32_i2c i2c_objs[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

static void stm32_i2c_apply_default_config(struct stm32_i2c_config *cfg)
{
    RT_ASSERT(cfg != RT_NULL);

    if (cfg->timing == 0U)
    {
        cfg->timing = DEFAULT_I2C_TIMING_VALUE;
    }
}

#if defined(BSP_I2C_RX_USING_DMA) || defined(BSP_I2C_TX_USING_DMA)
static void stm32_i2c_dma_rollback(struct stm32_i2c *i2c_drv, rt_uint16_t dma_flags)
{
#if defined(BSP_I2C_RX_USING_DMA)
    if ((dma_flags & RT_DEVICE_FLAG_DMA_RX) && (i2c_drv->config->dma_rx != RT_NULL))
    {
        (void)stm32_dma_deinit(&i2c_drv->dma.handle_rx, i2c_drv->config->dma_rx, RT_FALSE);
        i2c_drv->dma.handle_rx.Parent = RT_NULL;
        i2c_drv->handle.hdmarx = RT_NULL;
    }
#endif /* defined(BSP_I2C_RX_USING_DMA) */

#if defined(BSP_I2C_TX_USING_DMA)
    if ((dma_flags & RT_DEVICE_FLAG_DMA_TX) && (i2c_drv->config->dma_tx != RT_NULL))
    {
        (void)stm32_dma_deinit(&i2c_drv->dma.handle_tx, i2c_drv->config->dma_tx, RT_FALSE);
        i2c_drv->dma.handle_tx.Parent = RT_NULL;
        i2c_drv->handle.hdmatx = RT_NULL;
    }
#endif /* defined(BSP_I2C_TX_USING_DMA) */
}
#endif /* defined(BSP_I2C_RX_USING_DMA) || defined(BSP_I2C_TX_USING_DMA) */

static rt_err_t stm32_i2c_init(struct stm32_i2c *i2c_drv)
{
    RT_ASSERT(i2c_drv != RT_NULL);

    I2C_HandleTypeDef *i2c_handle = &i2c_drv->handle;
    struct stm32_i2c_config *cfg = i2c_drv->config;

    rt_memset(i2c_handle, 0, sizeof(I2C_HandleTypeDef));
    stm32_i2c_apply_default_config(cfg);

    i2c_handle->Instance = cfg->Instance;
#if defined(STM32_I2C_TIMINGR_IP)
    i2c_handle->Init.Timing = cfg->timing;
    i2c_handle->Init.OwnAddress2Masks = I2C_OA2_NOMASK;
#else
    i2c_handle->Init.ClockSpeed = cfg->timing;
    i2c_handle->Init.DutyCycle = I2C_DUTYCYCLE_2;
#endif /* defined(STM32_I2C_TIMINGR_IP) */
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
#if defined(STM32_I2C_TIMINGR_IP)
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
#endif /* defined(STM32_I2C_TIMINGR_IP) */
#if defined(BSP_I2C_RX_USING_DMA)
    /* I2C2 DMA Init */
    if (i2c_drv->i2c_dma_flag & RT_DEVICE_FLAG_DMA_RX)
    {
        if (stm32_dma_setup(&i2c_drv->dma.handle_rx,
                            &i2c_drv->handle,
                            &i2c_drv->handle.hdmarx,
                            i2c_drv->config->dma_rx) != RT_EOK)
        {
            stm32_i2c_dma_rollback(i2c_drv, RT_DEVICE_FLAG_DMA_RX);
            return -RT_EFAULT;
        }
    }
#endif /* defined(BSP_I2C_RX_USING_DMA) */
#if defined(BSP_I2C_TX_USING_DMA)
    if (i2c_drv->i2c_dma_flag & RT_DEVICE_FLAG_DMA_TX)
    {
        if (stm32_dma_setup(&i2c_drv->dma.handle_tx,
                            &i2c_drv->handle,
                            &i2c_drv->handle.hdmatx,
                            i2c_drv->config->dma_tx) != RT_EOK)
        {
            stm32_i2c_dma_rollback(i2c_drv, RT_DEVICE_FLAG_DMA_TX | (i2c_drv->i2c_dma_flag & RT_DEVICE_FLAG_DMA_RX));
            return -RT_EFAULT;
        }
    }
#endif /* defined(BSP_I2C_TX_USING_DMA) */
#if defined(BSP_I2C_USING_IRQ)
    if (((i2c_drv->i2c_dma_flag & RT_DEVICE_FLAG_DMA_TX) || (i2c_drv->i2c_dma_flag & RT_DEVICE_FLAG_DMA_RX))
     || ((i2c_drv->i2c_dma_flag & RT_DEVICE_FLAG_INT_TX) || (i2c_drv->i2c_dma_flag & RT_DEVICE_FLAG_INT_RX)))
    {
        /* In the data transfer function stm32_i2c_master_xfer(), the IT transfer function
        HAL_I2C_Master_Seq_Transmit_IT() is used when DMA is not used, so the IT interrupt
        must be enable anyway, regardless of the DMA configuration, otherwise
        the rt_completion_wait() will always timeout. */
        HAL_NVIC_SetPriority(i2c_drv->config->evirq_type, 2, 0);
        HAL_NVIC_EnableIRQ(i2c_drv->config->evirq_type);
        HAL_NVIC_SetPriority(i2c_drv->config->erirq_type, 2, 0);
        HAL_NVIC_EnableIRQ(i2c_drv->config->erirq_type);
    }
#endif /* defined(BSP_I2C_USING_IRQ) */

    return RT_EOK;
}

static rt_err_t stm32_i2c_configure(struct rt_i2c_bus_device *bus)
{
    RT_ASSERT(RT_NULL != bus);
    struct stm32_i2c *i2c_drv = rt_container_of(bus, struct stm32_i2c, i2c_bus);

    return stm32_i2c_init(i2c_drv);
}

/**
 * @brief Start one master receive transfer and report whether wait is required.
 * @param i2c_obj Pointer to the STM32 I2C driver object.
 * @param handle Pointer to the HAL I2C handle.
 * @param msg Pointer to the RT-Thread I2C message descriptor.
 * @param mode HAL sequential transfer mode.
 * @param timeout Timeout in milliseconds for polling transfer.
 * @param async_allowed RT_TRUE when the current context allows IRQ/DMA wait.
 * @param need_wait Output flag set to RT_TRUE when IT/DMA path is used.
 * @return HAL status returned by the selected HAL receive API.
 * @retval HAL_OK Transfer start succeeded.
 * @retval HAL_ERROR Transfer start failed or no receive backend is enabled.
 */
static HAL_StatusTypeDef stm32_i2c_master_receive_start(struct stm32_i2c *i2c_obj,
                                                        I2C_HandleTypeDef *handle,
                                                        struct rt_i2c_msg *msg,
                                                        uint32_t mode,
                                                        rt_uint32_t timeout,
                                                        rt_bool_t async_allowed,
                                                        rt_bool_t *need_wait)
{
    RT_UNUSED(i2c_obj);
    RT_UNUSED(mode);
    RT_UNUSED(timeout);
    RT_ASSERT(i2c_obj != RT_NULL);
    RT_ASSERT(handle != RT_NULL);
    RT_ASSERT(msg != RT_NULL);
    RT_ASSERT(need_wait != RT_NULL);

    *need_wait = RT_FALSE;

#if defined(BSP_I2C_RX_USING_DMA)
    if (async_allowed && (i2c_obj->i2c_dma_flag & RT_DEVICE_FLAG_DMA_RX) && (msg->len >= DMA_TRANS_MIN_LEN))
    {
        *need_wait = RT_TRUE;
        return HAL_I2C_Master_Seq_Receive_DMA(handle, (msg->addr << 1), msg->buf, msg->len, mode);
    }
#endif /* defined(BSP_I2C_RX_USING_DMA) */

#if defined(BSP_I2C_RX_USING_INT)
    if (async_allowed && (i2c_obj->i2c_dma_flag & RT_DEVICE_FLAG_INT_RX))
    {
        *need_wait = RT_TRUE;
        return HAL_I2C_Master_Seq_Receive_IT(handle, (msg->addr << 1), msg->buf, msg->len, mode);
    }
#endif /* defined(BSP_I2C_RX_USING_INT) */

#if defined(BSP_I2C_RX_USING_POLL)
    return HAL_I2C_Master_Receive(handle, (msg->addr << 1), msg->buf, msg->len, timeout);
#else
    return HAL_ERROR;
#endif /* defined(BSP_I2C_RX_USING_POLL) */
}

/**
 * @brief Start one master transmit transfer and report whether wait is required.
 * @param i2c_obj Pointer to the STM32 I2C driver object.
 * @param handle Pointer to the HAL I2C handle.
 * @param msg Pointer to the RT-Thread I2C message descriptor.
 * @param mode HAL sequential transfer mode.
 * @param timeout Timeout in milliseconds for polling transfer.
 * @param async_allowed RT_TRUE when the current context allows IRQ/DMA wait.
 * @param need_wait Output flag set to RT_TRUE when IT/DMA path is used.
 * @return HAL status returned by the selected HAL transmit API.
 * @retval HAL_OK Transfer start succeeded.
 * @retval HAL_ERROR Transfer start failed or no transmit backend is enabled.
 */
static HAL_StatusTypeDef stm32_i2c_master_transmit_start(struct stm32_i2c *i2c_obj,
                                                         I2C_HandleTypeDef *handle,
                                                         struct rt_i2c_msg *msg,
                                                         uint32_t mode,
                                                         rt_uint32_t timeout,
                                                         rt_bool_t async_allowed,
                                                         rt_bool_t *need_wait)
{
    RT_UNUSED(i2c_obj);
    RT_UNUSED(mode);
    RT_UNUSED(timeout);
    RT_ASSERT(i2c_obj != RT_NULL);
    RT_ASSERT(handle != RT_NULL);
    RT_ASSERT(msg != RT_NULL);
    RT_ASSERT(need_wait != RT_NULL);

    *need_wait = RT_FALSE;

#if defined(BSP_I2C_TX_USING_DMA)
    if (async_allowed && (i2c_obj->i2c_dma_flag & RT_DEVICE_FLAG_DMA_TX) && (msg->len >= DMA_TRANS_MIN_LEN))
    {
        *need_wait = RT_TRUE;
        return HAL_I2C_Master_Seq_Transmit_DMA(handle, (msg->addr << 1), msg->buf, msg->len, mode);
    }
#endif /* defined(BSP_I2C_TX_USING_DMA) */

#if defined(BSP_I2C_TX_USING_INT)
    if (async_allowed && (i2c_obj->i2c_dma_flag & RT_DEVICE_FLAG_INT_TX))
    {
        *need_wait = RT_TRUE;
        return HAL_I2C_Master_Seq_Transmit_IT(handle, (msg->addr << 1), msg->buf, msg->len, mode);
    }
#endif /* defined(BSP_I2C_TX_USING_INT) */

#if defined(BSP_I2C_TX_USING_POLL)
    return HAL_I2C_Master_Transmit(handle, (msg->addr << 1), msg->buf, msg->len, timeout);
#else
    return HAL_ERROR;
#endif /* defined(BSP_I2C_TX_USING_POLL) */
}

/**
 * @brief Compute HAL transfer mode for the current message in a sequence.
 * @param index Index of the current message.
 * @param msg Pointer to the current I2C message.
 * @param next_msg Pointer to the next I2C message, or RT_NULL for the last one.
 * @param is_last RT_TRUE when the current message is the last frame.
 * @return HAL sequential transfer option used by the message.
 * @retval I2C_FIRST_AND_NEXT_FRAME Continue transfer without repeated start.
 * @retval I2C_LAST_FRAME_NO_STOP Keep bus active for following frame semantics.
 * @retval I2C_LAST_FRAME End transfer with the last frame behavior.
 */
static uint32_t stm32_i2c_get_xfer_mode(rt_int32_t index,
                                        struct rt_i2c_msg *msg,
                                        struct rt_i2c_msg *next_msg,
                                        rt_bool_t is_last)
{
    if (is_last)
    {
        if (msg->flags & RT_I2C_NO_STOP)
        {
            return I2C_LAST_FRAME_NO_STOP;
        }

        return I2C_LAST_FRAME;
    }

    if (next_msg->flags & RT_I2C_NO_START)
    {
        if ((next_msg->flags & RT_I2C_RD) == (msg->flags & RT_I2C_RD))
        {
            /* The same mode, can use no start */
            return I2C_FIRST_AND_NEXT_FRAME;
        }

        /* Not allowed to use no start, sending address is required when changing direction, user setting error */
        LOG_W("user set flags error msg[%d] flags RT_I2C_NO_START has canceled", index + 1);
    }

    return I2C_LAST_FRAME_NO_STOP;
}

/**
 * @brief Convert HAL transfer mode value to a readable log string.
 * @param mode HAL sequential transfer option.
 * @return Constant string for logging.
 */
const char *stm32_i2c_mode_name(uint32_t mode)
{
    switch (mode)
    {
    case I2C_FIRST_AND_NEXT_FRAME:
        return "I2C_FIRST_AND_NEXT_FRAME";
    case I2C_LAST_FRAME_NO_STOP:
        return "I2C_FIRST_FRAME/I2C_LAST_FRAME_NO_STOP";
    case I2C_LAST_FRAME:
        return "I2C_LAST_FRAME";
    default:
        return "unknown mode";
    }
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
    /* timeout = data_time + dev_addr_time + reserve_time */
#define TIMEOUT_FREQ_KHZ(freq) (((freq) / 1000U) ? ((freq) / 1000U) : 1U)
#define TIMEOUT_CALC(msg) (((msg)->len * 8U) / TIMEOUT_FREQ_KHZ(bus->config.usage_freq) + 1U + 5U)

    rt_uint32_t i = 0;
    rt_int32_t ret = 0;
    struct rt_i2c_msg *msg = RT_NULL;
    struct rt_i2c_msg *next_msg = RT_NULL;
    struct stm32_i2c *i2c_obj;
    rt_bool_t is_last = RT_FALSE;
    uint32_t mode = 0;
    rt_uint32_t timeout_ms;

    if (num == 0)
    {
        return 0;
    }

    RT_ASSERT((msgs != RT_NULL) && (bus != RT_NULL));
    i2c_obj = rt_container_of(bus, struct stm32_i2c, i2c_bus);
    RT_ASSERT(i2c_obj != RT_NULL);
    I2C_HandleTypeDef *handle = &i2c_obj->handle;
    RT_ASSERT(handle != RT_NULL);
#if defined(BSP_I2C_USING_IRQ)
    rt_bool_t need_abort = RT_FALSE;
    struct rt_completion *completion;
    completion = &i2c_obj->completion;
#endif /* defined(BSP_I2C_USING_IRQ) */
    LOG_D("xfer start %d megs", num);
    for (i = 0; i < num; i++)
    {
        rt_bool_t need_wait = RT_FALSE;
        const rt_bool_t scheduler_available = rt_scheduler_is_available();
        const rt_bool_t irq_disabled = rt_hw_interrupt_is_disabled();
        const rt_bool_t async_allowed = (scheduler_available && !irq_disabled);

        msg = &msgs[i];
        is_last = (i == (num - 1));
        next_msg = is_last ? RT_NULL : &msgs[i + 1];
        mode = stm32_i2c_get_xfer_mode(i, msg, next_msg, is_last);
        LOG_D("xfer       msgs[%d] addr=0x%2x buf=0x%x len= 0x%x flags= 0x%x", i, msg->addr, msg->buf, msg->len, msg->flags);
#if defined(STM32_I2C_TIMINGR_IP)
        timeout_ms = bus->timeout ? (bus->timeout * 1000U + RT_TICK_PER_SECOND - 1U) / RT_TICK_PER_SECOND : 100U;
#else
        timeout_ms = TIMEOUT_CALC(msg);
#endif /* defined(STM32_I2C_TIMINGR_IP) */

#if defined(BSP_I2C_USING_IRQ)
        rt_tick_t timeout_tick = rt_tick_from_millisecond(timeout_ms);
        rt_completion_init(completion);
#endif /* defined(BSP_I2C_USING_IRQ) */
        if (msg->flags & RT_I2C_RD)
        {
            LOG_D("xfer  rec  msgs[%d] hal mode = %s", i, stm32_i2c_mode_name(mode));
            ret = stm32_i2c_master_receive_start(i2c_obj, handle, msg, mode, timeout_ms, async_allowed, &need_wait);
            if (ret != HAL_OK)
            {
                LOG_E("I2C[%s] Read error(%d)!", bus->parent.parent.name, ret);
                goto out;
            }
#if defined(BSP_I2C_USING_IRQ)
            if (need_wait)
            {
                ret = rt_completion_wait(completion, timeout_tick);
                if (ret != RT_EOK)
                {
                    need_abort = RT_TRUE;
                    LOG_W("I2C[%s] receive wait failed %d, timeout %u ms", bus->parent.parent.name, ret, timeout_ms);
                    goto out;
                }

                if (handle->ErrorCode != HAL_I2C_ERROR_NONE)
                {
                    need_abort = RT_TRUE;
                    LOG_E("I2C[%s] receive failed, error code: 0x%08x", bus->parent.parent.name, handle->ErrorCode);
                    goto out;
                }
            }
#endif /* defined(BSP_I2C_USING_IRQ) */
        }
        else
        {
            LOG_D("xfer trans msgs[%d] hal mode = %s", i, stm32_i2c_mode_name(mode));
            ret = stm32_i2c_master_transmit_start(i2c_obj, handle, msg, mode, timeout_ms, async_allowed, &need_wait);
            if (ret != HAL_OK)
            {
                LOG_E("I2C[%s] Write error(%d)!", bus->parent.parent.name, ret);
                goto out;
            }
#if defined(BSP_I2C_USING_IRQ)
            if (need_wait)
            {
                ret = rt_completion_wait(completion, timeout_tick);
                if (ret != RT_EOK)
                {
                    need_abort = RT_TRUE;
                    LOG_W("I2C[%s] transmit wait failed %d, timeout %u ms", bus->parent.parent.name, ret, timeout_ms);
                    goto out;
                }

                if (handle->ErrorCode != HAL_I2C_ERROR_NONE)
                {
                    need_abort = RT_TRUE;
                    LOG_E("I2C[%s] transmit failed, error code: 0x%08x", bus->parent.parent.name, handle->ErrorCode);
                    goto out;
                }
            }
#endif /* defined(BSP_I2C_USING_IRQ) */
        }
        if (!is_last)
        {
            LOG_D("xfer  next msgs[%d] addr=0x%2x buf= 0x%x len= 0x%x flags = 0x%x\r\n", i + 1, next_msg->addr, next_msg->buf, next_msg->len, next_msg->flags);
        }
    }
    ret = num;
    LOG_D("xfer  end  %d megs\r\n", num);
    return ret;

out:
    ret = i;
    /*
     * On TIMINGR-based STM32 I2C IPs (currently F7/H7 in this driver),
     * STOPI only enables STOP-event interrupt handling.
     * It does not actively generate a STOP condition on the bus.
     *
     * For legacy STM32 I2C IPs, the HAL error handler already generates a
     * STOP condition on AF in master/memory modes, so this driver does not
     * manually issue another STOP in the AF path.
     */
    if (handle->ErrorCode & HAL_I2C_ERROR_AF)
    {
        LOG_W("I2C[%s] NACK Error", bus->parent.parent.name);
#if defined(STM32_I2C_TIMINGR_IP)
        handle->Instance->CR1 |= I2C_IT_STOPI;
#endif /* defined(STM32_I2C_TIMINGR_IP) */
    }
    if (handle->ErrorCode & HAL_I2C_ERROR_BERR)
    {
        LOG_W("I2C[%s] BUS Error", bus->parent.parent.name);
#if defined(STM32_I2C_TIMINGR_IP)
        handle->Instance->CR1 |= I2C_IT_STOPI;
#else
        handle->Instance->CR1 |= I2C_CR1_STOP;
#endif /* defined(STM32_I2C_TIMINGR_IP) */
    }
#if defined(BSP_I2C_USING_IRQ)
    if (need_abort && (msg != RT_NULL))
    {
        if (HAL_I2C_Master_Abort_IT(handle, (msg->addr << 1)) != HAL_OK)
        {
            LOG_W("I2C[%s] abort start failed, state: %d, error: 0x%08x",
                  bus->parent.parent.name,
                  handle->State,
                  handle->ErrorCode);
        }
        else
        {
            rt_uint32_t timeout = timeout_ms;
            const rt_bool_t scheduler_available = rt_scheduler_is_available();
            const rt_bool_t irq_disabled = rt_hw_interrupt_is_disabled();

            while (HAL_I2C_GetState(handle) != HAL_I2C_STATE_READY)
            {
                if (timeout-- > 0)
                {
                    if (scheduler_available && !irq_disabled)
                    {
                        rt_thread_mdelay(1);
                    }
                    else
                    {
                        rt_hw_us_delay(1000);
                    }
                }
                else
                {
                    LOG_E("I2C[%s] timeout! state did not become READY after abort.", bus->parent.parent.name);
                    break;
                }
            }
        }
    }
#endif /* defined(BSP_I2C_USING_IRQ) */

    return ret;
#undef TIMEOUT_FREQ_KHZ
#undef TIMEOUT_CALC
}

rt_err_t stm_i2c_bus_control(struct rt_i2c_bus_device *bus, int cmd, void *args)
{
    struct stm32_i2c *i2c_obj;
    RT_ASSERT(bus != RT_NULL);

    i2c_obj = rt_container_of(bus, struct stm32_i2c, i2c_bus);
    RT_ASSERT(i2c_obj != RT_NULL);

    switch (cmd)
    {
        case BSP_I2C_CTRL_SET_TIMING:
        {
            if (args == RT_NULL)
            {
                return -RT_EINVAL;
            }

            rt_uint32_t timing = *(rt_uint32_t *)args;
            if(timing <= 0)
            {
                return -RT_ERROR;
            }

            i2c_obj->i2c_bus.config.usage_freq = i2c_obj->config->timing = timing;
            return stm32_i2c_configure(&i2c_obj->i2c_bus);
            break;
        }
        default:
        {
            break;
        }
    }
    return -RT_EINVAL;
}

static const struct rt_i2c_bus_device_ops stm32_i2c_ops =
{
    .master_xfer = stm32_i2c_master_xfer,
#if defined(STM32_I2C_LEGACY_IP)
    .i2c_bus_control = stm_i2c_bus_control,
#endif
    .slave_xfer = RT_NULL,
};

int RT_hw_i2c_bus_init(void)
{
    int ret = -RT_ERROR;
    rt_size_t obj_num = sizeof(i2c_objs) / sizeof(i2c_objs[0]);

    for (int i = 0; i < obj_num; i++)
    {
        i2c_objs[i].i2c_bus.ops = &stm32_i2c_ops;
        i2c_objs[i].config = &i2c_config[i];
        i2c_objs[i].i2c_bus.timeout = i2c_config[i].timeout;
        stm32_i2c_apply_default_config(&i2c_config[i]);
#if defined(STM32_I2C_LEGACY_IP)
        i2c_objs[i].i2c_bus.config.max_hz = i2c_config[i].timing;
        i2c_objs[i].i2c_bus.config.usage_freq = i2c_config[i].timing;
#endif
#if defined(BSP_I2C_USING_IRQ)
        rt_completion_init(&i2c_objs[i].completion);
#endif /* defined(BSP_I2C_USING_IRQ) */
        ret = stm32_i2c_configure(&i2c_objs[i].i2c_bus);
        if (ret != RT_EOK)
        {
            LOG_E("%s bus configure failed %d", i2c_config[i].name, ret);
            return -RT_ERROR;
        }
        ret = rt_i2c_bus_device_register(&i2c_objs[i].i2c_bus, i2c_objs[i].config->name);
        if(ret != RT_EOK)
        {
            LOG_E("%s bus init failed %d", i2c_config[i].name, ret);
        }
        else
        {
            LOG_D("%s bus init done", i2c_config[i].name);
        }
    }
    return ret;
}

static void stm32_get_info(void)
{
#if defined(BSP_USING_HARD_I2C1)
    i2c_objs[I2C1_INDEX].i2c_dma_flag = 0;

#if defined (BSP_I2C1_TX_USING_INT)
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_INT_TX;
#endif /* defined (BSP_I2C1_TX_USING_INT) */
#if defined(BSP_I2C1_TX_USING_DMA)
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static const struct stm32_dma_config I2C1_dma_tx = I2C1_TX_DMA_CONFIG;
    i2c_config[I2C1_INDEX].dma_tx = &I2C1_dma_tx;
#endif /* defined (BSP_I2C1_TX_USING_DMA) */

#if defined (BSP_I2C1_RX_USING_INT)
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_INT_RX;
#endif /* defined (BSP_I2C1_RX_USING_INT) */
#if defined(BSP_I2C1_RX_USING_DMA)
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static const struct stm32_dma_config I2C1_dma_rx = I2C1_RX_DMA_CONFIG;
    i2c_config[I2C1_INDEX].dma_rx = &I2C1_dma_rx;
#endif /* defined (BSP_I2C1_RX_USING_DMA) */

#endif /* defined(BSP_USING_HARD_I2C1) */

#if defined(BSP_USING_HARD_I2C2)
    i2c_objs[I2C2_INDEX].i2c_dma_flag = 0;

#if defined (BSP_I2C2_TX_USING_INT)
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_INT_TX;
#endif /* defined (BSP_I2C2_TX_USING_INT) */
#if defined(BSP_I2C2_TX_USING_DMA)
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static const struct stm32_dma_config I2C2_dma_tx = I2C2_TX_DMA_CONFIG;
    i2c_config[I2C2_INDEX].dma_tx = &I2C2_dma_tx;
#endif /* defined (BSP_I2C2_TX_USING_DMA) */

#if defined (BSP_I2C2_RX_USING_INT)
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_INT_RX;
#endif /* defined (BSP_I2C2_RX_USING_INT) */
#if defined(BSP_I2C2_RX_USING_DMA)
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static const struct stm32_dma_config I2C2_dma_rx = I2C2_RX_DMA_CONFIG;
    i2c_config[I2C2_INDEX].dma_rx = &I2C2_dma_rx;
#endif /* defined (BSP_I2C2_RX_USING_DMA) */

#endif /* defined(BSP_USING_HARD_I2C2) */

#if defined(BSP_USING_HARD_I2C3)
    i2c_objs[I2C3_INDEX].i2c_dma_flag = 0;

#if defined (BSP_I2C3_TX_USING_INT)
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_INT_TX;
#endif /* defined (BSP_I2C3_TX_USING_INT) */
#if defined(BSP_I2C3_TX_USING_DMA)
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static const struct stm32_dma_config I2C3_dma_tx = I2C3_TX_DMA_CONFIG;
    i2c_config[I2C3_INDEX].dma_tx = &I2C3_dma_tx;
#endif /* defined (BSP_I2C3_TX_USING_DMA) */

#if defined (BSP_I2C3_RX_USING_INT)
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_INT_RX;
#endif /* defined (BSP_I2C3_RX_USING_INT) */
#if defined(BSP_I2C3_RX_USING_DMA)
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static const struct stm32_dma_config I2C3_dma_rx = I2C3_RX_DMA_CONFIG;
    i2c_config[I2C3_INDEX].dma_rx = &I2C3_dma_rx;
#endif /* defined (BSP_I2C3_RX_USING_DMA) */

#endif /* defined(BSP_USING_HARD_I2C3) */

#if defined(BSP_USING_HARD_I2C4)
    i2c_objs[I2C4_INDEX].i2c_dma_flag = 0;

#if defined (BSP_I2C4_TX_USING_INT)
    i2c_objs[I2C4_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_INT_TX;
#endif /* defined (BSP_I2C4_TX_USING_INT) */
#if defined(BSP_I2C4_TX_USING_DMA)
    i2c_objs[I2C4_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_TX;
    static const struct stm32_dma_config I2C4_dma_tx = I2C4_TX_DMA_CONFIG;
    i2c_config[I2C4_INDEX].dma_tx = &I2C4_dma_tx;
#endif /* defined (BSP_I2C4_TX_USING_DMA) */

#if defined (BSP_I2C4_RX_USING_INT)
    i2c_objs[I2C4_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_INT_RX;
#endif /* defined (BSP_I2C4_RX_USING_INT) */
#if defined(BSP_I2C4_RX_USING_DMA)
    i2c_objs[I2C4_INDEX].i2c_dma_flag |= RT_DEVICE_FLAG_DMA_RX;
    static const struct stm32_dma_config I2C4_dma_rx = I2C4_RX_DMA_CONFIG;
    i2c_config[I2C4_INDEX].dma_rx = &I2C4_dma_rx;
#endif /* defined (BSP_I2C4_RX_USING_DMA) */

#endif /* defined(BSP_USING_HARD_I2C4) */
}

#ifdef BSP_I2C_USING_IRQ
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
    struct stm32_i2c *i2c_drv = rt_container_of(hi2c, struct stm32_i2c, handle);

    LOG_W("%s error code 0x%08x", i2c_drv->config->name, hi2c->ErrorCode);
#if defined(STM32_I2C_TIMINGR_IP)
    /*
     * Trigger STOP handling immediately in IRQ context so the peripheral can
     * leave the error state before the waiting thread starts its recovery path.
     */
    if (hi2c->ErrorCode & HAL_I2C_ERROR_AF)
    {
        hi2c->Instance->CR1 |= I2C_IT_STOPI;
    }
    if (hi2c->ErrorCode & HAL_I2C_ERROR_BERR)
    {
        hi2c->Instance->CR1 |= I2C_IT_STOPI;
    }
#endif /* defined(STM32_I2C_TIMINGR_IP) */
    rt_completion_done(&i2c_drv->completion);
}

#ifdef BSP_USING_HARD_I2C1
/**
 * @brief This function handles I2C1 event interrupt.
 */
void I2C1_EV_IRQHandler(void)
{
    /* USER CODE BEGIN I2C1_EV_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C1_EV_IRQn 0 */
    HAL_I2C_EV_IRQHandler(&i2c_objs[I2C1_INDEX].handle);
    /* USER CODE BEGIN I2C1_EV_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C1_EV_IRQn 1 */
}

/**
 * @brief This function handles I2C1 error interrupt.
 */
void I2C1_ER_IRQHandler(void)
{
    /* USER CODE BEGIN I2C1_ER_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C1_ER_IRQn 0 */
    HAL_I2C_ER_IRQHandler(&i2c_objs[I2C1_INDEX].handle);
    /* USER CODE BEGIN I2C1_ER_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C1_ER_IRQn 1 */
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
 * @brief This function handles I2C3 event interrupt.
 */
void I2C3_EV_IRQHandler(void)
{
    /* USER CODE BEGIN I2C3_EV_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C3_EV_IRQn 0 */
    HAL_I2C_EV_IRQHandler(&i2c_objs[I2C3_INDEX].handle);
    /* USER CODE BEGIN I2C3_EV_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C3_EV_IRQn 1 */
}

/**
 * @brief This function handles I2C3 error interrupt.
 */
void I2C3_ER_IRQHandler(void)
{
    /* USER CODE BEGIN I2C3_ER_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C3_ER_IRQn 0 */
    HAL_I2C_ER_IRQHandler(&i2c_objs[I2C3_INDEX].handle);
    /* USER CODE BEGIN I2C3_ER_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C2_ER_IRQn 1 */
}
#endif /* BSP_USING_HARD_I2C3 */

#ifdef BSP_USING_HARD_I2C4
/**
 * @brief This function handles I2C4 event interrupt.
 */
void I2C4_EV_IRQHandler(void)
{
    /* USER CODE BEGIN I2C4_EV_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C4_EV_IRQn 0 */
    HAL_I2C_EV_IRQHandler(&i2c_objs[I2C4_INDEX].handle);
    /* USER CODE BEGIN I2C4_EV_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C4_EV_IRQn 1 */
}

/**
 * @brief This function handles I2C4 error interrupt.
 */
void I2C4_ER_IRQHandler(void)
{
    /* USER CODE BEGIN I2C4_ER_IRQn 0 */
    /* enter interrupt */
    rt_interrupt_enter();
    /* USER CODE END I2C4_ER_IRQn 0 */
    HAL_I2C_ER_IRQHandler(&i2c_objs[I2C4_INDEX].handle);
    /* USER CODE BEGIN I2C4_ER_IRQn 1 */
    /* leave interrupt */
    rt_interrupt_leave();
    /* USER CODE END I2C4_ER_IRQn 1 */
}
#endif /* BSP_USING_HARD_I2C4 */
#endif /* BSP_I2C_USING_IRQ */

#ifdef BSP_I2C_USING_DMA
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

#if defined(BSP_USING_HARD_I2C4) && defined(BSP_I2C4_RX_USING_DMA)
/**
 * @brief  This function handles DMA Rx interrupt request.
 * @param  None
 * @retval None
 */
void I2C4_DMA_RX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&i2c_objs[I2C4_INDEX].dma.handle_rx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_HARD_I2C4) && defined(BSP_I2C4_RX_USING_DMA) */

#if defined(BSP_USING_HARD_I2C4) && defined(BSP_I2C4_TX_USING_DMA)
/**
 * @brief  This function handles DMA Rx interrupt request.
 * @param  None
 * @retval None
 */
void I2C4_DMA_TX_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    HAL_DMA_IRQHandler(&i2c_objs[I2C4_INDEX].dma.handle_tx);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif /* defined(BSP_USING_HARD_I2C4) && defined(BSP_I2C4_TX_USING_DMA) */
#endif /* BSP_I2C_USING_DMA */

int rt_hw_hw_i2c_init(void)
{
    stm32_get_info();
    return RT_hw_i2c_bus_init();
}
INIT_BOARD_EXPORT(rt_hw_hw_i2c_init);

#endif /* defined(BSP_HARDWARE_I2C) */
