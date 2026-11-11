/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-12     Vandoul      the first version
 */

#include <rtthread.h>
#include "fsl_i2s.h"
#include "fsl_i2s_dma.h"
#include "drv_i2s.h"

#define DBG_TAG "DRVI2S"
#include "rtdbg.h"

#ifdef BSP_USING_I2S

#if !defined(BSP_USING_I2S0) && \
    !defined(BSP_USING_I2S1) && \
    !defined(BSP_USING_I2S2) && \
    !defined(BSP_USING_I2S3) && \
    !defined(BSP_USING_I2S4) && \
    !defined(BSP_USING_I2S5) && \
    !defined(BSP_USING_I2S6) && \
    !defined(BSP_USING_I2S7)
#error "Please define at least one I2Sx"
#endif

#include <rtdevice.h>

enum {
#ifdef BSP_USING_I2S0
    I2S0_INDEX,
#endif
#ifdef BSP_USING_I2S1
    I2S1_INDEX,
#endif
#ifdef BSP_USING_I2S2
    I2S2_INDEX,
#endif
#ifdef BSP_USING_I2S3
    I2S3_INDEX,
#endif
#ifdef BSP_USING_I2S4
    I2S4_INDEX,
#endif
#ifdef BSP_USING_I2S5
    I2S5_INDEX,
#endif
#ifdef BSP_USING_I2S6
    I2S6_INDEX,
#endif
#ifdef BSP_USING_I2S7
    I2S7_INDEX,
#endif
};

struct lpc_i2s_clock_and_irq_param
{
    clock_attach_id_t i2s_clock;
    reset_ip_name_t i2s_reset_bit;
    IRQn_Type irq_type;
};

struct lpc_i2s
{
    struct rt_device device;
    i2s_handle_t i2s_handle;
    struct lpc_i2s_config config;
    uint32_t index;
    I2S_Type *i2s_base;
    const char *device_name;
};

#define LPC_I2S_CONFIG_MODE_IS_SLAVE(dev)           ((dev)->config.mode == LPC_I2S_CONFIG_MODE_SLAVE)
#define LPC_I2S_CONFIG_MODE_IS_MASTER(dev)          ((dev)->config.mode == LPC_I2S_CONFIG_MODE_MASTER)

#define LPC_I2S_CLOCK_AND_IRQ_PARAM_INIT(index)         {.i2s_clock = kPLL0_DIV_to_FLEXCOMM##index, .i2s_reset_bit = kFC##index##_RST_SHIFT_RSTn, .irq_type = FLEXCOMM##index##_IRQn,}
const static struct lpc_i2s_clock_and_irq_param lpc_i2s_clock_and_irq_param_table[] =
{
#ifdef BSP_USING_I2S0
//    {.i2s_clock = kPLL0_DIV_to_FLEXCOMM0, .i2s_reset_bit = kFC0_RST_SHIFT_RSTn, .irq_type = FLEXCOMM0_IRQn,},
    LPC_I2S_CLOCK_AND_IRQ_PARAM_INIT(0),
#endif
#ifdef BSP_USING_I2S1
    LPC_I2S_CLOCK_AND_IRQ_PARAM_INIT(1),
#endif
#ifdef BSP_USING_I2S2
    LPC_I2S_CLOCK_AND_IRQ_PARAM_INIT(2),
#endif
#ifdef BSP_USING_I2S3
    LPC_I2S_CLOCK_AND_IRQ_PARAM_INIT(3),
#endif
#ifdef BSP_USING_I2S4
    LPC_I2S_CLOCK_AND_IRQ_PARAM_INIT(4),
#endif
#ifdef BSP_USING_I2S5
    LPC_I2S_CLOCK_AND_IRQ_PARAM_INIT(5),
#endif
#ifdef BSP_USING_I2S6
    LPC_I2S_CLOCK_AND_IRQ_PARAM_INIT(6),
#endif
#ifdef BSP_USING_I2S7
    LPC_I2S_CLOCK_AND_IRQ_PARAM_INIT(7),
#endif
};

static struct lpc_i2s lpc_i2s_table[] =
{
#ifdef BSP_USING_I2S0
    {.index = I2S0_INDEX,.i2s_base = I2S0,.device_name = "i2s0"},
#endif
#ifdef BSP_USING_I2S1
    {.index = I2S1_INDEX,.i2s_base = I2S1,.device_name = "i2s1"},
#endif
#ifdef BSP_USING_I2S2
    {.index = I2S2_INDEX,.i2s_base = I2S2,.device_name = "i2s2"},
#endif
#ifdef BSP_USING_I2S3
    {.index = I2S3_INDEX,.i2s_base = I2S3,.device_name = "i2s3"},
#endif
#ifdef BSP_USING_I2S4
    {.index = I2S4_INDEX,.i2s_base = I2S4,.device_name = "i2s4"},
#endif
#ifdef BSP_USING_I2S5
    {.index = I2S5_INDEX,.i2s_base = I2S5,.device_name = "i2s5"},
#endif
#ifdef BSP_USING_I2S6
    {.index = I2S6_INDEX,.i2s_base = I2S6,.device_name = "i2s6"},
#endif
#ifdef BSP_USING_I2S7
    {.index = I2S7_INDEX,.i2s_base = I2S7,.device_name = "i2s7"},
#endif
};

static void transfer_callback(I2S_Type *base, i2s_handle_t *handle, status_t completionStatus, void *userData)
{
    struct lpc_i2s *i2s_dev = rt_container_of(handle, struct lpc_i2s, i2s_handle);
    if(LPC_I2S_CONFIG_MODE_IS_SLAVE(i2s_dev))
    {
        if(i2s_dev->device.rx_indicate != RT_NULL)
        {
            i2s_dev->device.rx_indicate(&i2s_dev->device, completionStatus);
        }
    }
    else
    {
        if(i2s_dev->device.tx_complete != RT_NULL)
        {
            i2s_dev->device.tx_complete(&i2s_dev->device, RT_NULL);
        }
    }
}

static void i2s_clock_and_irq_config(struct lpc_i2s *dev)
{
    const struct lpc_i2s_clock_and_irq_param *clock_and_irq_param = &lpc_i2s_clock_and_irq_param_table[dev->index];
//    CLOCK_SetClkDiv(kCLOCK_DivPll0Clk, 0U, true);
//    CLOCK_SetClkDiv(kCLOCK_DivPll0Clk, 1U, false);
    CLOCK_AttachClk(clock_and_irq_param->i2s_clock);
    RESET_PeripheralReset(clock_and_irq_param->i2s_reset_bit);
    NVIC_ClearPendingIRQ(clock_and_irq_param->irq_type);
    /* Enable interrupts for I2S */
    EnableIRQ(clock_and_irq_param->irq_type);
}
rt_err_t rt_i2s_init(rt_device_t dev)
{
    struct lpc_i2s *i2s_dev = rt_container_of(dev, struct lpc_i2s, device);
    i2s_clock_and_irq_config(i2s_dev);
    return RT_EOK;
}
rt_err_t rt_i2s_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct lpc_i2s *i2s_dev = rt_container_of(dev, struct lpc_i2s, device);
    i2s_config_t config;
    if(i2s_dev->config.mode == LPC_I2S_CONFIG_MODE_SLAVE)
    {
        RT_ASSERT(i2s_dev->config.is_blocking == 0);
        I2S_RxGetDefaultConfig(&config);
        config.divider = CLOCK_GetPll0OutFreq()/i2s_dev->config.sampling_rate/i2s_dev->config.data_bits/i2s_dev->config.channels;
        config.masterSlave = kI2S_MasterSlaveNormalSlave;
        I2S_RxInit(i2s_dev->i2s_base, &config);
        I2S_RxTransferCreateHandle(i2s_dev->i2s_base, &i2s_dev->i2s_handle, transfer_callback, NULL);
    }
    else if(i2s_dev->config.mode == LPC_I2S_CONFIG_MODE_MASTER)
    {
        RT_ASSERT(i2s_dev->config.is_blocking == 0);
        I2S_TxGetDefaultConfig(&config);
        config.divider = CLOCK_GetPll0OutFreq()/i2s_dev->config.sampling_rate/i2s_dev->config.data_bits/i2s_dev->config.channels;
        config.masterSlave = kI2S_MasterSlaveNormalMaster;
        I2S_TxInit(i2s_dev->i2s_base, &config);
        I2S_TxTransferCreateHandle(i2s_dev->i2s_base, &i2s_dev->i2s_handle, transfer_callback, NULL);
    }
    return RT_EOK;
}
rt_err_t rt_i2s_close(rt_device_t dev)
{
    struct lpc_i2s *i2s_dev = rt_container_of(dev, struct lpc_i2s, device);
    I2S_Deinit(i2s_dev->i2s_base);
    return RT_EOK;
}
rt_ssize_t rt_i2s_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    struct lpc_i2s *i2s_dev = rt_container_of(dev, struct lpc_i2s, device);
    if(!LPC_I2S_CONFIG_MODE_IS_SLAVE(i2s_dev))
    {
        return -RT_ERROR;
    }
    i2s_transfer_t transfer;
    transfer.data = buffer;
    transfer.dataSize = size;
    if(kStatus_Success == I2S_RxTransferNonBlocking(i2s_dev->i2s_base, &i2s_dev->i2s_handle, transfer))
        return size;
    else
        return -RT_EBUSY;
}
rt_ssize_t rt_i2s_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    struct lpc_i2s *i2s_dev = rt_container_of(dev, struct lpc_i2s, device);
    if(!LPC_I2S_CONFIG_MODE_IS_MASTER(i2s_dev))
    {
        return -RT_ERROR;
    }
    i2s_transfer_t transfer;
    transfer.data = (uint8_t *)buffer;
    transfer.dataSize = size;
    if(kStatus_Success == I2S_TxTransferNonBlocking(i2s_dev->i2s_base, &i2s_dev->i2s_handle, transfer))
        return size;
    else
        return -RT_EBUSY;
}
rt_err_t rt_i2s_control(rt_device_t dev, int cmd, void *args)
{
    struct lpc_i2s *i2s_dev = rt_container_of(dev, struct lpc_i2s, device);
    rt_err_t ret = RT_EOK;
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(args != RT_NULL);
    switch(cmd)
    {
        case RT_I2S_CTRL_RESET:
            i2s_clock_and_irq_config(i2s_dev);
            break;
        case RT_I2S_CTRL_SET_CONFIG:
        {
            struct lpc_i2s_config *config = (struct lpc_i2s_config *)args;
            i2s_dev->config = *config;
        }
            break;
        default:
            ret = -RT_ERROR;
            break;
    }
    return ret;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops i2s_core_ops =
{
    rt_i2s_init,
    rt_i2s_open,
    rt_i2s_close,
    rt_i2s_read,
    rt_i2s_write,
    rt_i2s_control,
};
#endif /* RT_USING_DEVICE_OPS */

int rt_hw_i2s_init(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;
    int i;

    for (i = 0; i < sizeof(lpc_i2s_table) / sizeof(lpc_i2s_table[0]); i++)
    {
        #ifdef RT_USING_DEVICE_OPS
        lpc_i2s_table[i].device.ops = &i2s_core_ops;
        #else
        lpc_i2s_table[i].device.init = rt_i2s_init;
        lpc_i2s_table[i].device.open = rt_i2s_open;
        lpc_i2s_table[i].device.close = rt_i2s_close;
        lpc_i2s_table[i].device.read = rt_i2s_read;
        lpc_i2s_table[i].device.write = rt_i2s_write;
        lpc_i2s_table[i].device.control = rt_i2s_control;
        #endif

        /* register UART device */
        rt_device_register(&lpc_i2s_table[i].device,
                              lpc_i2s_table[i].device_name,
                              RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX);
    }

    return 0;
}

INIT_BOARD_EXPORT(rt_hw_i2s_init);

#endif

