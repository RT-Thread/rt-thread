/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include <rtthread.h>
#include <rthw.h>

#ifdef RT_USING_I2C

#if defined(BSP_USING_I2C1) || defined(BSP_USING_I2C2) || defined(BSP_USING_I2C3) || \
    defined(BSP_USING_I2C4) || defined(BSP_USING_I2C5) || defined(BSP_USING_I2C6)

#include "drv_i2c.h"

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
#ifndef HC32_I2C_DEBUG
    #define I2C_PRINT_DBG(fmt, args...)
    #define I2C_PRINT_ERR(fmt, args...) rt_kprintf(fmt, ##args);
#else
    #define I2C_PRINT_DBG(fmt, args...) rt_kprintf(fmt, ##args);
    #define I2C_PRINT_ERR(fmt, args...) rt_kprintf(fmt, ##args);
#endif

#define I2C_TIMEOUT                 ((uint32_t)0x10000)
#define FCG_I2C_CLK                 FCG_Fcg1PeriphClockCmd

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
extern rt_err_t rt_hw_board_i2c_init(CM_I2C_TypeDef *I2Cx);

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
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
#ifdef BSP_USING_I2C4
    I2C4_INDEX,
#endif
#ifdef BSP_USING_I2C5
    I2C5_INDEX,
#endif
#ifdef BSP_USING_I2C6
    I2C6_INDEX,
#endif
};

static struct hc32_i2c_config i2c_config[] =
{
#ifdef BSP_USING_I2C1
    I2C1_CONFIG,
#endif
#ifdef BSP_USING_I2C2
    I2C2_CONFIG,
#endif
#ifdef BSP_USING_I2C3
    I2C3_CONFIG,
#endif
#ifdef BSP_USING_I2C4
    I2C4_CONFIG,
#endif
#ifdef BSP_USING_I2C5
    I2C5_CONFIG,
#endif
#ifdef BSP_USING_I2C6
    I2C6_CONFIG,
#endif
};

static void hc32_i2c_dma_configure(struct rt_i2c_bus_device *bus);
static struct hc32_i2c i2c_objs[sizeof(i2c_config) / sizeof(i2c_config[0])] = {0};

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
static rt_err_t hc32_i2c_configure(struct rt_i2c_bus_device *bus)
{
    int ret = -RT_ERROR;
    stc_i2c_init_t i2c_init;
    float32_t f32Error = 0.0F;
    rt_uint32_t I2cSrcClk;
    rt_uint32_t I2cClkDiv;
    rt_uint32_t I2cClkDivReg;
    RT_ASSERT(RT_NULL != bus);

    struct hc32_i2c *i2c_obj = rt_container_of(bus, struct hc32_i2c, i2c_bus);

    /* Enable I2C clock */
    FCG_I2C_CLK(i2c_obj->config->clock, ENABLE);
    if (RT_EOK != rt_hw_board_i2c_init(i2c_obj->config->Instance))
    {
        return -RT_ERROR;
    }
    I2C_DeInit(i2c_obj->config->Instance);

    I2cSrcClk = I2C_SRC_CLK;
    I2cClkDiv = I2cSrcClk / i2c_obj->config->baudrate / I2C_WIDTH_MAX_IMME;
    for (I2cClkDivReg = I2C_CLK_DIV1; I2cClkDivReg <= I2C_CLK_DIV128; I2cClkDivReg++)
    {
        if (I2cClkDiv < (1UL << I2cClkDivReg))
        {
            break;
        }
    }
    i2c_init.u32ClockDiv = I2cClkDivReg;
    i2c_init.u32SclTime = 400UL * I2cSrcClk / (1UL << I2cClkDivReg) / 1000000000UL;  /* SCL time is about 400nS in EVB board */
    i2c_init.u32Baudrate = i2c_obj->config->baudrate;
    ret = I2C_Init(i2c_obj->config->Instance, &i2c_init, &f32Error);
    if (RT_EOK == ret)
    {
        I2C_BusWaitCmd(i2c_obj->config->Instance, ENABLE);
        I2C_Cmd(i2c_obj->config->Instance, ENABLE);
    }
    if ((i2c_obj->i2c_dma_flag & I2C_USING_TX_DMA_FLAG) || (i2c_obj->i2c_dma_flag & I2C_USING_RX_DMA_FLAG))
    {
        hc32_i2c_dma_configure(bus);
    }
    return ret;
}

static void hc32_hw_i2c_reset(struct hc32_i2c *i2c_obj)
{
    I2C_SWResetCmd(i2c_obj->config->Instance, ENABLE);
    I2C_SWResetCmd(i2c_obj->config->Instance, DISABLE);
}

static int hc32_hw_i2c_start(struct hc32_i2c *i2c_obj)
{
    if (LL_OK != I2C_Start(i2c_obj->config->Instance, i2c_obj->config->timeout))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int hc32_hw_i2c_restart(struct hc32_i2c *i2c_obj)
{
    if (LL_OK != I2C_Restart(i2c_obj->config->Instance, i2c_obj->config->timeout))
    {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static int hc32_hw_i2c_send_addr(struct hc32_i2c *i2c_obj,
                                 struct rt_i2c_msg *msg)
{
    rt_uint8_t dir = ((msg->flags & RT_I2C_RD) == RT_I2C_RD) ? (I2C_DIR_RX) : (I2C_DIR_TX);
    if (LL_OK != I2C_TransAddr(i2c_obj->config->Instance, msg->addr, dir, i2c_obj->config->timeout))
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

static int hc32_hw_i2c_stop(struct hc32_i2c *i2c_obj)
{
    if (LL_OK != I2C_Stop(i2c_obj->config->Instance, i2c_obj->config->timeout))
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}

static void hc32_i2c_get_dma_info(void)
{
#ifdef BSP_I2C1_TX_USING_DMA
    static struct dma_config i2c1_tx_dma = I2C1_TX_DMA_CONFIG;
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    i2c_config[I2C1_INDEX].i2c_tx_dma = &i2c1_tx_dma;
#endif
#ifdef BSP_I2C1_RX_USING_DMA
    static struct dma_config i2c1_rx_dma = I2C1_RX_DMA_CONFIG;
    i2c_objs[I2C1_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    i2c_config[I2C1_INDEX].i2c_rx_dma = &i2c1_rx_dma;
#endif

#ifdef BSP_I2C2_TX_USING_DMA
    static struct dma_config i2c2_tx_dma = I2C2_TX_DMA_CONFIG;
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    i2c_config[I2C2_INDEX].i2c_tx_dma = &i2c2_tx_dma;
#endif
#ifdef BSP_I2C2_RX_USING_DMA
    static struct dma_config i2c2_rx_dma = I2C2_RX_DMA_CONFIG;
    i2c_objs[I2C2_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    i2c_config[I2C2_INDEX].i2c_rx_dma = &i2c2_rx_dma;
#endif

#ifdef BSP_I2C3_TX_USING_DMA
    static struct dma_config i2c3_tx_dma = I2C3_TX_DMA_CONFIG;
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    i2c_config[I2C3_INDEX].i2c_tx_dma = &i2c3_tx_dma;
#endif
#ifdef BSP_I2C3_RX_USING_DMA
    static struct dma_config i2c3_rx_dma = I2C3_RX_DMA_CONFIG;
    i2c_objs[I2C3_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    i2c_config[I2C3_INDEX].i2c_rx_dma = &i2c3_rx_dma;
#endif

#ifdef BSP_I2C4_TX_USING_DMA
    static struct dma_config i2c4_tx_dma = I2C4_TX_DMA_CONFIG;
    i2c_objs[I2C4_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    i2c_config[I2C4_INDEX].i2c_tx_dma = &i2c4_tx_dma;
#endif
#ifdef BSP_I2C4_RX_USING_DMA
    static struct dma_config i2c4_rx_dma = I2C4_RX_DMA_CONFIG;
    i2c_objs[I2C4_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    i2c_config[I2C4_INDEX].i2c_rx_dma = &i2c4_rx_dma;
#endif

#ifdef BSP_I2C5_TX_USING_DMA
    static struct dma_config i2c5_tx_dma = I2C5_TX_DMA_CONFIG;
    i2c_objs[I2C5_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    i2c_config[I2C5_INDEX].i2c_tx_dma = &i2c5_tx_dma;
#endif
#ifdef BSP_I2C5_RX_USING_DMA
    static struct dma_config i2c5_rx_dma = I2C5_RX_DMA_CONFIG;
    i2c_objs[I2C5_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    i2c_config[I2C5_INDEX].i2c_rx_dma = &i2c5_rx_dma;
#endif

#ifdef BSP_I2C6_TX_USING_DMA
    static struct dma_config i2c6_tx_dma = I2C6_TX_DMA_CONFIG;
    i2c_objs[I2C6_INDEX].i2c_dma_flag |= I2C_USING_TX_DMA_FLAG;
    i2c_config[I2C6_INDEX].i2c_tx_dma = &i2c6_tx_dma;
#endif
#ifdef BSP_I2C6_RX_USING_DMA
    static struct dma_config i2c6_rx_dma = I2C6_RX_DMA_CONFIG;
    i2c_objs[I2C6_INDEX].i2c_dma_flag |= I2C_USING_RX_DMA_FLAG;
    i2c_config[I2C6_INDEX].i2c_rx_dma = &i2c6_rx_dma;
#endif
}

static void hc32_i2c_dma_configure(struct rt_i2c_bus_device *bus)
{
    stc_dma_init_t stcDmaInit;

    struct hc32_i2c *i2c_obj = rt_container_of(bus, struct hc32_i2c, i2c_bus);

    if (i2c_obj->i2c_dma_flag & I2C_USING_TX_DMA_FLAG)
    {
        /* DMA/AOS FCG enable */
        FCG_Fcg0PeriphClockCmd(i2c_obj->config->i2c_tx_dma->clock, ENABLE);

        (void)DMA_StructInit(&stcDmaInit);
        stcDmaInit.u32BlockSize  = 1UL;
        stcDmaInit.u32TransCount = 0UL;
        stcDmaInit.u32DataWidth  = DMA_DATAWIDTH_8BIT;
        /* Configure TX */
        stcDmaInit.u32SrcAddrInc  = DMA_SRC_ADDR_INC;
        stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_FIX;
        stcDmaInit.u32SrcAddr     = (uint32_t)NULL;
        stcDmaInit.u32DestAddr    = (uint32_t)(&i2c_obj->config->Instance->DTR);
        if (LL_OK != DMA_Init(i2c_obj->config->i2c_tx_dma->Instance, i2c_obj->config->i2c_tx_dma->channel, &stcDmaInit))
        {
            I2C_PRINT_ERR("[%s:%d]I2C TX DMA init error!\n", __func__, __LINE__);
        }
        AOS_SetTriggerEventSrc(i2c_obj->config->i2c_tx_dma->trigger_select, i2c_obj->config->i2c_tx_dma->trigger_event);
        /* Enable DMA unit */
        DMA_Cmd(i2c_obj->config->i2c_tx_dma->Instance, ENABLE);
    }

    if (i2c_obj->i2c_dma_flag & I2C_USING_RX_DMA_FLAG)
    {
        /* DMA/AOS FCG enable */
        FCG_Fcg0PeriphClockCmd(i2c_obj->config->i2c_rx_dma->clock, ENABLE);
        (void)DMA_StructInit(&stcDmaInit);
        stcDmaInit.u32BlockSize  = 1UL;
        stcDmaInit.u32TransCount = 0UL;
        stcDmaInit.u32DataWidth  = DMA_DATAWIDTH_8BIT;
        /* Configure RX */
        stcDmaInit.u32SrcAddrInc  = DMA_SRC_ADDR_FIX;
        stcDmaInit.u32DestAddrInc = DMA_DEST_ADDR_INC;
        stcDmaInit.u32SrcAddr     = (uint32_t)(&i2c_obj->config->Instance->DRR);
        stcDmaInit.u32DestAddr    = (uint32_t)NULL;
        if (LL_OK != DMA_Init(i2c_obj->config->i2c_rx_dma->Instance, i2c_obj->config->i2c_rx_dma->channel, &stcDmaInit))
        {
            I2C_PRINT_ERR("[%s:%d]I2C RX DMA init error!\n", __func__, __LINE__);
        }
        AOS_SetTriggerEventSrc(i2c_obj->config->i2c_rx_dma->trigger_select, i2c_obj->config->i2c_rx_dma->trigger_event);
        /* Enable DMA unit */
        DMA_Cmd(i2c_obj->config->i2c_rx_dma->Instance, ENABLE);
    }
}

static int I2C_Master_Transmit_DMA(struct hc32_i2c *i2c_obj, struct rt_i2c_msg *msg)
{
    rt_uint32_t timeCnt;
    struct dma_config *i2c_tx_dma;
    i2c_tx_dma = i2c_obj->config->i2c_tx_dma;

    if (msg->len > 1U)
    {
        DMA_ClearTransCompleteStatus(i2c_tx_dma->Instance, i2c_tx_dma->flag);
        (void)DMA_SetTransCount(i2c_tx_dma->Instance, i2c_tx_dma->channel, msg->len - 1U);
        (void)DMA_SetSrcAddr(i2c_tx_dma->Instance, i2c_tx_dma->channel, (uint32_t)(&msg->buf[1]));
        (void)DMA_ChCmd(i2c_tx_dma->Instance, i2c_tx_dma->channel, ENABLE);
    }
    I2C_WriteData(i2c_obj->config->Instance, msg->buf[0]);
    if (msg->len > 1U)
    {
        timeCnt = 0;
        /* wait DMA transfer completed */
        while (RESET == DMA_GetTransCompleteStatus(i2c_tx_dma->Instance, i2c_tx_dma->flag) && (timeCnt < i2c_obj->config->timeout))
        {
            rt_thread_mdelay(1);
            timeCnt++;
        }
        if (timeCnt >= i2c_obj->config->timeout)
        {
            return -RT_ETIMEOUT;
        }
    }
    /* wait last I2C data transfer completed */
    timeCnt = 0;
    while ((LL_OK != I2C_WaitStatus(i2c_obj->config->Instance, I2C_FLAG_TX_CPLT, SET, 1)) && (timeCnt < i2c_obj->config->timeout))
    {
        rt_thread_mdelay(1);
        timeCnt++;
    }
    if (timeCnt >= i2c_obj->config->timeout)
    {
        return -RT_ETIMEOUT;
    }
    return RT_EOK;
}

static int I2C_Master_Receive_DMA(struct hc32_i2c *i2c_obj, struct rt_i2c_msg *msg)
{
    rt_uint32_t timeCnt;
    struct dma_config *i2c_rx_dma;
    i2c_rx_dma = i2c_obj->config->i2c_rx_dma;

    if (1UL == msg->len)
    {
        I2C_AckConfig(i2c_obj->config->Instance, I2C_NACK);
    }
    else if (msg->len > 2U)
    {
        DMA_ClearTransCompleteStatus(i2c_rx_dma->Instance, i2c_rx_dma->flag);
        (void)DMA_SetTransCount(i2c_rx_dma->Instance, i2c_rx_dma->channel, msg->len - 2U);
        (void)DMA_SetDestAddr(i2c_rx_dma->Instance, i2c_rx_dma->channel, (uint32_t)(&msg->buf[0]));
        (void)DMA_ChCmd(i2c_rx_dma->Instance, i2c_rx_dma->channel, ENABLE);
    }
    if (msg->len > 2U)
    {
        timeCnt = 0;
        /* Wait DMA finish */
        while ((RESET == DMA_GetTransCompleteStatus(i2c_rx_dma->Instance, i2c_rx_dma->flag)) && (timeCnt < i2c_obj->config->timeout))
        {
            /* Need add timeout release process here */
            rt_thread_mdelay(1);
            timeCnt++;
        }
        if (timeCnt >= i2c_obj->config->timeout)
        {
            return -RT_ETIMEOUT;
        }
    }
    if (msg->len > 1U)
    {
        timeCnt = 0;
        /* Wait data receive finish */
        while ((LL_OK != I2C_WaitStatus(i2c_obj->config->Instance, I2C_FLAG_RX_FULL, SET, 1)) && (timeCnt < i2c_obj->config->timeout))
        {
            rt_thread_mdelay(1);
            timeCnt++;
        }
        if (timeCnt >= i2c_obj->config->timeout)
        {
            return -RT_ETIMEOUT;
        }
        I2C_AckConfig(i2c_obj->config->Instance, I2C_NACK);
        msg->buf[msg->len - 2U] = I2C_ReadData(i2c_obj->config->Instance);
    }
    timeCnt = 0;
    /* Wait last data receive finish */
    while ((LL_OK != I2C_WaitStatus(i2c_obj->config->Instance, I2C_FLAG_RX_FULL, SET, 1)) && (timeCnt < i2c_obj->config->timeout))
    {
        rt_thread_mdelay(1);
        timeCnt++;
    }
    if (timeCnt >= i2c_obj->config->timeout)
    {
        return -RT_ETIMEOUT;
    }
    /* Stop before read last data */
    I2C_ClearStatus(i2c_obj->config->Instance, I2C_FLAG_STOP);
    I2C_GenerateStop(i2c_obj->config->Instance);
    /* read data from register */
    msg->buf[msg->len - 1U] = I2C_ReadData(i2c_obj->config->Instance);
    timeCnt = 0;
    while ((LL_OK != I2C_WaitStatus(i2c_obj->config->Instance, I2C_FLAG_STOP, SET, 1)) && (timeCnt < i2c_obj->config->timeout))
    {
        rt_thread_mdelay(1);
        timeCnt++;
    }
    if (timeCnt >= i2c_obj->config->timeout)
    {
        return -RT_ETIMEOUT;
    }
    I2C_AckConfig(i2c_obj->config->Instance, I2C_ACK);
    return RT_EOK;
}

static int I2C_Master_Transmit(struct hc32_i2c *i2c_obj,
                               struct rt_i2c_msg *msg)
{
    return I2C_TransData(i2c_obj->config->Instance, msg->buf, msg->len, i2c_obj->config->timeout);
}

static int I2C_Master_Receive(struct hc32_i2c *i2c_obj,
                              struct rt_i2c_msg *msg)
{
    if (msg->len == 1UL)
    {
        I2C_AckConfig(i2c_obj->config->Instance, I2C_NACK);
    }
    return I2C_MasterReceiveDataAndStop(i2c_obj->config->Instance, msg->buf, msg->len, i2c_obj->config->timeout);
}

static int hc32_i2c_write(struct hc32_i2c *i2c_obj,
                          struct rt_i2c_msg *msg)
{
    int ret;
    if (i2c_obj->i2c_dma_flag & I2C_USING_TX_DMA_FLAG)
    {
        ret = I2C_Master_Transmit_DMA(i2c_obj, msg);
    }
    else
    {
        ret = I2C_Master_Transmit(i2c_obj, msg);
    }
    return ret;
}

static int hc32_i2c_read(struct hc32_i2c *i2c_obj,
                         struct rt_i2c_msg *msg)
{
    int ret;
    if (i2c_obj->i2c_dma_flag & I2C_USING_RX_DMA_FLAG)
    {
        ret = I2C_Master_Receive_DMA(i2c_obj, msg);
    }
    else
    {
        ret = I2C_Master_Receive(i2c_obj, msg);
    }
    return ret;
}

static rt_ssize_t hc32_i2c_master_xfer(struct rt_i2c_bus_device *bus,
                                       struct rt_i2c_msg msgs[],
                                       rt_uint32_t num)
{
    rt_int32_t i, ret;
    rt_uint16_t ignore_nack;
    struct rt_i2c_msg *msg = msgs;
    struct hc32_i2c *i2c_obj;

    RT_ASSERT((msgs != RT_NULL) && (bus != RT_NULL));

    i2c_obj = rt_container_of(bus, struct hc32_i2c, i2c_bus);

    if (num == 0)
    {
        return 0;
    }

    for (i = 0; i < num; i++)
    {
        msg = &msgs[i];
        ignore_nack = msg->flags & RT_I2C_IGNORE_NACK;
        if (!(msg->flags & RT_I2C_NO_START))
        {
            if (SET == I2C_GetStatus(i2c_obj->config->Instance, I2C_FLAG_BUSY))
            {
                hc32_hw_i2c_restart(i2c_obj);
            }
            else
            {
                hc32_hw_i2c_reset(i2c_obj);
                hc32_hw_i2c_start(i2c_obj);
            }
            /* addr R or W */
            ret = hc32_hw_i2c_send_addr(i2c_obj, msg);
            if ((ret != RT_EOK) && !ignore_nack)
            {
                I2C_PRINT_DBG("receive NACK from device addr 0x%02x msg %d", msgs[i].addr, i);
                goto out;
            }
        }
        if (msg->flags & RT_I2C_RD)
        {
            ret = hc32_i2c_read(i2c_obj, msg);
            if (ret != RT_EOK)
            {
                I2C_PRINT_ERR("[%s:%d]I2C Read error!\n", __func__, __LINE__);
                goto out;
            }
        }
        else
        {
            ret = hc32_i2c_write(i2c_obj, msg);
            if (ret != RT_EOK)
            {
                I2C_PRINT_ERR("[%s:%d]I2C Write error!\n", __func__, __LINE__);
                goto out;
            }
        }
    }
    ret = i;

out:
    if (!(msg->flags & RT_I2C_NO_STOP))
    {
        hc32_hw_i2c_stop(i2c_obj);
        I2C_PRINT_DBG("send stop condition\n");
    }
    return ret;
}

static const struct rt_i2c_bus_device_ops hc32_i2c_ops =
{
    .master_xfer = hc32_i2c_master_xfer,
    RT_NULL,
    RT_NULL
};

int hc32_hw_i2c_init(void)
{
    int ret = -RT_ERROR;
    rt_size_t obj_num = sizeof(i2c_objs) / sizeof(struct hc32_i2c);
    I2C_PRINT_DBG("%s start\n", __func__);

    for (int i = 0; i < obj_num; i++)
    {
        i2c_objs[i].i2c_bus.ops = &hc32_i2c_ops;
        i2c_objs[i].config = &i2c_config[i];
        i2c_objs[i].i2c_bus.timeout = i2c_config[i].timeout;
        hc32_i2c_get_dma_info();
        if (i2c_objs[i].i2c_dma_flag & I2C_USING_TX_DMA_FLAG)
        {
            i2c_objs[i].config->i2c_tx_dma = i2c_config[i].i2c_tx_dma;
        }
        if ((i2c_objs[i].i2c_dma_flag & I2C_USING_RX_DMA_FLAG))
        {
            i2c_objs[i].config->i2c_rx_dma = i2c_config[i].i2c_rx_dma;
        }
        hc32_i2c_configure(&i2c_objs[i].i2c_bus);
        ret = rt_i2c_bus_device_register(&i2c_objs[i].i2c_bus, i2c_objs[i].config->name);
        RT_ASSERT(ret == RT_EOK);
    }
    I2C_PRINT_DBG("%s end\n", __func__);

    return ret;
}

INIT_BOARD_EXPORT(hc32_hw_i2c_init);

#endif

#endif /* RT_USING_I2C */
